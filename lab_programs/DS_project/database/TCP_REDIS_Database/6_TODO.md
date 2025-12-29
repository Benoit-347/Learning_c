TODO.md

# Implementation TODO List

## 📋 What's Missing and How to Complete It

This document provides a detailed roadmap for completing the implementation. Each section includes code snippets and integration points.

---

## 🔴 CRITICAL: Must Implement for Basic Functionality

### 1. TCP State Machine Integration (Priority: HIGHEST)

**File**: `redis_tcp_server.c` or create `tcp_stack.c`

**What's Missing**: The `tcp_input()` function exists in your documents but isn't called from the main packet processor.

**Implementation**:

```c
// In process_packet() function, add after IP validation:

if (ip->protocol == IP_PROTO_TCP) {
    // Parse TCP header
    size_t ip_hdr_len = (ip->version_ihl & 0x0F) * 4;
    tcp_hdr_t *tcp = (tcp_hdr_t*)((uint8_t*)ip + ip_hdr_len);
    
    // Verify TCP checksum
    size_t tcp_total_len = ntohs(ip->total_length) - ip_hdr_len;
    uint16_t orig_csum = tcp->checksum;
    tcp->checksum = 0;
    uint16_t calc_csum = tcp_checksum(ip->src_ip, ip->dst_ip, tcp, tcp_total_len);
    tcp->checksum = orig_csum;
    
    if (orig_csum != calc_csum) {
        log_msg(LOG_DEBUG, "TCP checksum mismatch, dropping");
        return;
    }
    
    // Extract TCP data
    size_t tcp_hdr_len = ((tcp->data_offset_flags >> 4) & 0x0F) * 4;
    uint8_t *tcp_data = (uint8_t*)tcp + tcp_hdr_len;
    size_t tcp_data_len = tcp_total_len - tcp_hdr_len;
    
    // Call TCP input handler
    tcp_input(
        g_conn_pool,              // Connection pool
        ntohl(ip->src_ip),        // Source IP
        ntohs(tcp->src_port),     // Source port
        ntohl(ip->dst_ip),        // Destination IP
        ntohs(tcp->dst_port),     // Destination port
        ntohl(tcp->seq_num),      // Sequence number
        ntohl(tcp->ack_num),      // ACK number
        tcp->flags,               // TCP flags
        ntohs(tcp->window),       // Window size
        tcp_data,                 // Payload data
        tcp_data_len              // Payload length
    );
}
```

**Integration Points**:
1. Add connection pool global: `conn_pool_t *g_conn_pool;`
2. Initialize in `main()`: `g_conn_pool = conn_pool_create();`
3. Include TCP functions from your documents

**Testing**:
```bash
# After implementing, test with telnet
telnet 127.0.0.1 6379

# Should see in logs:
# [DEBUG] TCP SYN received, creating connection
# [DEBUG] Sent SYN-ACK
# [DEBUG] Connection ESTABLISHED
```

---

### 2. TCP Packet Transmission (Priority: HIGHEST)

**What's Missing**: `send_tcp_segment()` function builds packets but doesn't send them.

**Implementation**:

```c
// Add to redis_tcp_server.c

void send_tcp_packet(tcp_connection_t *conn, uint8_t flags,
                     uint32_t seq, uint32_t ack,
                     const uint8_t *data, size_t data_len) {
    
    // Lookup destination MAC from ARP cache
    uint8_t dst_mac[6];
    if (arp_cache_lookup(conn->remote_ip, dst_mac) < 0) {
        log_msg(LOG_WARN, "No ARP entry for destination, dropping");
        // TODO: Send ARP request and queue packet
        return;
    }
    
    // Build complete packet
    uint8_t packet[2048];
    size_t offset = 0;
    
    // Ethernet header
    eth_hdr_t *eth = (eth_hdr_t*)packet;
    memcpy(eth->dst_mac, dst_mac, 6);
    memcpy(eth->src_mac, g_config.mac_address, 6);
    eth->ethertype = htons(0x0800);
    offset += sizeof(eth_hdr_t);
    
    // IP header
    ip_hdr_t *ip = (ip_hdr_t*)(packet + offset);
    ip->version_ihl = 0x45;
    ip->tos = 0;
    ip->total_length = htons(sizeof(ip_hdr_t) + sizeof(tcp_hdr_t) + data_len);
    ip->identification = htons(rand());
    ip->flags_fragment = htons(0x4000);  // Don't fragment
    ip->ttl = 64;
    ip->protocol = IP_PROTO_TCP;
    ip->checksum = 0;
    ip->src_ip = conn->local_ip;
    ip->dst_ip = conn->remote_ip;
    ip->checksum = ip_checksum(ip, sizeof(ip_hdr_t));
    offset += sizeof(ip_hdr_t);
    
    // TCP header
    tcp_hdr_t *tcp = (tcp_hdr_t*)(packet + offset);
    tcp->src_port = htons(conn->local_port);
    tcp->dst_port = htons(conn->remote_port);
    tcp->seq_num = htonl(seq);
    tcp->ack_num = htonl(ack);
    tcp->data_offset_flags = 0x50;  // 20 byte header
    tcp->flags = flags;
    tcp->window = htons(conn->rcv_wnd);
    tcp->checksum = 0;
    tcp->urgent_ptr = 0;
    offset += sizeof(tcp_hdr_t);
    
    // Payload
    if (data && data_len > 0) {
        memcpy(packet + offset, data, data_len);
        offset += data_len;
    }
    
    // Calculate TCP checksum
    tcp->checksum = tcp_checksum(ip->src_ip, ip->dst_ip,
                                 tcp, sizeof(tcp_hdr_t) + data_len);
    
    // Send packet
    send_raw_packet(g_raw_socket, packet, offset);
    
    log_msg(LOG_DEBUG, "Sent TCP %s%s%s seq=%u ack=%u len=%zu",
            (flags & TCP_SYN) ? "SYN " : "",
            (flags & TCP_ACK) ? "ACK " : "",
            (flags & TCP_FIN) ? "FIN " : "",
            seq, ack, data_len);
}
```

**Integration**: Replace stub `send_tcp_segment()` calls with this function.

---

### 3. Create Listener Connection (Priority: HIGHEST)

**What's Missing**: No connection exists in LISTEN state.

**Implementation**:

```c
// Add to main() after initializing conn_pool

tcp_connection_t* create_listener(conn_pool_t *pool) {
    tcp_connection_t *listener = create_connection(
        pool,
        g_config.bind_ip,        // Local IP
        g_config.bind_port,      // Local port (6379)
        0,                       // Remote IP (wildcard)
        0                        // Remote port (wildcard)
    );
    
    if (!listener) {
        log_msg(LOG_ERROR, "Failed to create listener");
        return NULL;
    }
    
    listener->state = TCP_LISTEN;
    log_msg(LOG_INFO, "Created TCP listener on port %d", g_config.bind_port);
    
    return listener;
}

// In main():
tcp_connection_t *listener = create_listener(g_conn_pool);
if (!listener) {
    return EXIT_FAILURE;
}
```

---

### 4. RESP Parser Integration (Priority: HIGH)

**What's Missing**: Parser exists but isn't called when TCP data arrives.

**Implementation**:

```c
// In tcp_input(), when data is received in ESTABLISHED state:

if (conn->recv_count > 0) {
    // Get or create parser
    resp_parser_t *parser = (resp_parser_t*)conn->app_data;
    if (!parser) {
        parser = malloc(sizeof(resp_parser_t));
        resp_parser_init(parser);
        conn->app_data = parser;
    }
    
    // Parse data from receive buffer
    size_t consumed;
    resp_result_t result = resp_parse(
        parser,
        conn->recv_buf + conn->recv_tail,
        conn->recv_count,
        &consumed
    );
    
    if (result == RESP_OK) {
        // Complete command received
        log_msg(LOG_DEBUG, "Parsed command: %.*s (argc=%d)",
                (int)parser->cmd.arg_lens[0],
                parser->cmd.args[0],
                parser->cmd.argc);
        
        // Dispatch command
        dispatch_command(conn, g_database,
                        parser->cmd.args,
                        parser->cmd.arg_lens,
                        parser->cmd.argc);
        
        // Consume parsed bytes
        conn->recv_tail = (conn->recv_tail + consumed) % TCP_RECV_BUF_SIZE;
        conn->recv_count -= consumed;
        
        // Reset parser for next command
        resp_parser_init(parser);
        
    } else if (result == RESP_ERROR) {
        log_msg(LOG_ERROR, "RESP parse error: %s", parser->error_msg);
        send_error(conn, parser->error_msg);
        
        // Close connection on protocol error
        tcp_close(g_conn_pool, conn);
    }
    // If RESP_INCOMPLETE, wait for more data
}
```

---

### 5. Initialize Database (Priority: HIGH)

**What's Missing**: Hash table database not created.

**Implementation**:

```c
// Add global
hash_table_t *g_database;

// In main():
g_database = hash_table_create(1024);  // Initial size
if (!g_database) {
    log_msg(LOG_ERROR, "Failed to create database");
    return EXIT_FAILURE;
}

log_msg(LOG_INFO, "Database initialized");
```

---

### 6. Implement send_tcp_segment() Wrapper (Priority: HIGH)

**What's Missing**: TCP stack calls `send_tcp_segment()` but it doesn't exist in main file.

**Implementation**:

```c
// Add this wrapper that tcp_input() can call
void send_tcp_segment(tcp_connection_t *conn, uint8_t flags,
                     uint32_t seq, uint32_t ack,
                     const uint8_t *data, size_t len) {
    send_tcp_packet(conn, flags, seq, ack, data, len);
}
```

---

## 🟡 HIGH PRIORITY: Essential Features

### 7. Retransmission Timer Integration (Priority: HIGH)

**Implementation**:

```c
// Add to main_loop(), after processing packets:

void process_timers(conn_pool_t *pool) {
    uint64_t now_us = get_time_us();
    
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        tcp_connection_t *conn = &pool->connections[i];
        
        if (conn->state == TCP_CLOSED) {
            continue;
        }
        
        // Check retransmission timer
        if (conn->retrans_timer.active &&
            now_us >= conn->retrans_timer.expire_us) {
            
            if (conn->retrans_count >= TCP_MAX_RETRIES) {
                log_msg(LOG_WARN, "Connection timeout, closing");
                destroy_connection(pool, conn);
                continue;
            }
            
            // Retransmit unACKed data
            log_msg(LOG_DEBUG, "Retransmitting (attempt %d)",
                    conn->retrans_count + 1);
            
            // TODO: Retransmit logic
            
            conn->rto_us *= 2;  // Exponential backoff
            conn->retrans_count++;
            conn->retrans_timer.expire_us = now_us + conn->rto_us;
        }
        
        // Check TIME_WAIT timeout
        if (conn->state == TCP_TIME_WAIT) {
            // TIME_WAIT is 2*MSL (usually 2 minutes)
            // For simplicity, use 60 seconds
            if (now_us >= conn->retrans_timer.expire_us) {
                log_msg(LOG_DEBUG, "TIME_WAIT expired, closing");
                destroy_connection(pool, conn);
            }
        }
    }
}

// Helper function
uint64_t get_time_us(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000ULL + tv.tv_usec;
}

// In main_loop():
while (g_running) {
    // ... read packets ...
    process_packet(buffer, len);
    
    // Process timers every iteration
    process_timers(g_conn_pool);
}
```

---

### 8. ICMP Echo Reply (Priority: MEDIUM)

**Implementation**:

```c
void handle_icmp(const uint8_t *packet, size_t len,
                uint32_t src_ip, uint32_t dst_ip) {
    
    // Parse ICMP header
    if (len < 8) return;  // Minimum ICMP header
    
    uint8_t type = packet[0];
    uint8_t code = packet[1];
    
    if (type == 8 && code == 0) {  // Echo Request
        log_msg(LOG_DEBUG, "ICMP Echo Request from %08x", ntohl(src_ip));
        
        // Build Echo Reply
        uint8_t reply_pkt[2048];
        size_t offset = 0;
        
        // Ethernet header (lookup MAC)
        uint8_t dst_mac[6];
        if (arp_cache_lookup(src_ip, dst_mac) < 0) {
            log_msg(LOG_WARN, "No ARP entry for ICMP reply");
            return;
        }
        
        eth_hdr_t *eth = (eth_hdr_t*)reply_pkt;
        memcpy(eth->dst_mac, dst_mac, 6);
        memcpy(eth->src_mac, g_config.mac_address, 6);
        eth->ethertype = htons(0x0800);
        offset += sizeof(eth_hdr_t);
        
        // IP header
        ip_hdr_t *ip = (ip_hdr_t*)(reply_pkt + offset);
        ip->version_ihl = 0x45;
        ip->tos = 0;
        ip->total_length = htons(sizeof(ip_hdr_t) + len);
        ip->identification = htons(rand());
        ip->flags_fragment = htons(0x4000);
        ip->ttl = 64;
        ip->protocol = 1;  // ICMP
        ip->checksum = 0;
        ip->src_ip = dst_ip;
        ip->dst_ip = src_ip;
        ip->checksum = ip_checksum(ip, sizeof(ip_hdr_t));
        offset += sizeof(ip_hdr_t);
        
        // ICMP reply
        uint8_t *icmp = reply_pkt + offset;
        memcpy(icmp, packet, len);
        icmp[0] = 0;  // Type = Echo Reply
        
        // Recalculate ICMP checksum
        uint16_t *csum_ptr = (uint16_t*)(icmp + 2);
        *csum_ptr = 0;
        *csum_ptr = ip_checksum(icmp, len);
        offset += len;
        
        // Send
        send_raw_packet(g_raw_socket, reply_pkt, offset);
        log_msg(LOG_DEBUG, "Sent ICMP Echo Reply");
    }
}

// In process_packet(), add:
if (ip->protocol == IP_PROTO_ICMP) {
    size_t ip_hdr_len = (ip->version_ihl & 0x0F) * 4;
    uint8_t *icmp_data = (uint8_t*)ip + ip_hdr_len;
    size_t icmp_len = ntohs(ip->total_length) - ip_hdr_len;
    
    handle_icmp(icmp_data, icmp_len, ip->src_ip, ip->dst_ip);
}
```

---

### 9. Response Encoding Functions (Priority: HIGH)

**What's Missing**: RESP response encoding functions need `tcp_send_data()` implementation.

**Implementation**:

```c
int tcp_send_data(tcp_connection_t *conn, const uint8_t *data, size_t len) {
    // Simple implementation: send immediately
    // Production version would buffer and batch
    
    const size_t MSS = 1460;
    size_t sent = 0;
    
    while (sent < len) {
        size_t chunk = len - sent;
        if (chunk > MSS) chunk = MSS;
        
        send_tcp_packet(conn, TCP_ACK | TCP_PSH,
                       conn->snd_nxt, conn->rcv_nxt,
                       data + sent, chunk);
        
        conn->snd_nxt += chunk;
        sent += chunk;
    }
    
    return sent;
}
```

---

## 🟢 MEDIUM PRIORITY: Completing the Stack

### 10. Flush Send Buffers (Priority: MEDIUM)

```c
void flush_connection_buffers(conn_pool_t *pool) {
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        tcp_connection_t *conn = &pool->connections[i];
        
        if (conn->state != TCP_ESTABLISHED) {
            continue;
        }
        
        // If send buffer has data, transmit it
        if (conn->send_count > 0) {
            size_t to_send = conn->send_count;
            if (to_send > 1460) to_send = 1460;  // MSS
            
            uint8_t temp[1460];
            for (size_t i = 0; i < to_send; i++) {
                temp[i] = conn->send_buf[conn->send_tail];
                conn->send_tail = (conn->send_tail + 1) % TCP_SEND_BUF_SIZE;
            }
            conn->send_count -= to_send;
            
            send_tcp_packet(conn, TCP_ACK | TCP_PSH,
                           conn->snd_nxt, conn->rcv_nxt,
                           temp, to_send);
            
            conn->snd_nxt += to_send;
        }
    }
}

// Call in main_loop()
```

---

### 11. Complete Command Handlers (Priority: MEDIUM)

See documents for full implementations. Wire them up:

```c
// Already in documents:
// - cmd_ping()
// - cmd_echo()
// - cmd_set()
// - cmd_get()
// - cmd_del()
// - cmd_lpush()
// - cmd_lpop()
// - cmd_lrange()

// Add to command_table in dispatch_command()
```

---

## 🔵 LOW PRIORITY: Advanced Features

### 12. Key Expiration (Priority: LOW)

**Implementation**: Use timing wheel from documents

```c
// In main():
timing_wheel_t *g_expiration_wheel = timing_wheel_create();

// In cmd_set() when expiration is specified:
timing_wheel_add(g_expiration_wheel, key, key_len, expire_ms,
                expire_key_callback, db);

// In main_loop():
timing_wheel_tick(g_expiration_wheel);
```

---

### 13. Multi-threading (Priority: LOW)

Implement after single-threaded version works perfectly.

---

### 14. Persistence (AOF/RDB) (Priority: LOW)

Add after all data structures work.

---

## 📊 Integration Checklist

Use this to track your progress:

```
Phase 1: Basic Connectivity
[ ] TCP state machine integrated
[ ] Packet transmission working
[ ] Listener created
[ ] 3-way handshake completes
[ ] Can telnet to port 6379

Phase 2: Protocol Layer
[ ] RESP parser integrated
[ ] Commands dispatched
[ ] Responses encoded
[ ] Can send PING via redis-cli

Phase 3: Data Layer
[ ] Database initialized
[ ] SET/GET working
[ ] Hash table integrated
[ ] Can store/retrieve keys

Phase 4: Advanced Data Structures
[ ] Lists (LPUSH/LPOP/LRANGE)
[ ] Sorted sets (ZADD/ZRANGE)
[ ] Key expiration
[ ] All commands working

Phase 5: Reliability
[ ] Retransmission working
[ ] Out-of-order handling
[ ] Connection cleanup
[ ] Stress test passes

Phase 6: Performance
[ ] Benchmark vs Redis
[ ] Profile and optimize
[ ] Multi-threading
[ ] AF_XDP integration
```

---

## 🧪 Testing After Each Phase

### Phase 1 Test:
```bash
telnet 127.0.0.1 6379
# Should: Connect successfully, see ESTABLISHED in logs
```

### Phase 2 Test:
```bash
echo -ne "*1\r\n\$4\r\nPING\r\n" | nc 127.0.0.1 6379
# Should: Receive "+PONG\r\n"
```

### Phase 3 Test:
```bash
redis-cli -h 127.0.0.1 -p 6379 SET key value
# Should: Receive "OK"

redis-cli -h 127.0.0.1 -p 6379 GET key
# Should: Receive "value"
```

---

## 🎯 Recommended Implementation Order

1. **Week 1**: Phase 1 (TCP connectivity)
   - Start here: TCP state machine
   - Then: Packet transmission  
   - Then: Listener creation
   - Goal: Complete 3-way handshake

2. **Week 2**: Phase 2 (RESP protocol)
   - Start: RESP parser integration
   - Then: Command dispatch
   - Then: Response encoding
   - Goal: PING/ECHO work

3. **Week 3**: Phase 3 (Data storage)
   - Start: Database initialization
   - Then: SET/GET handlers
   - Then: More commands
   - Goal: Basic Redis functionality

4. **Week 4**: Phase 4 (Advanced features)
   - Lists and sorted sets
   - Key expiration
   - Testing and debugging

---

## 📝 Notes

- **Don't try to implement everything at once!**
- **Test after each small change**
- **Use logs liberally (--log-level 3)**
- **Capture packets with tcpdump/Wireshark**
- **Refer to the documents for complete implementations**

---

**Ready to start? Begin with Task #1: TCP State Machine Integration! 🚀**