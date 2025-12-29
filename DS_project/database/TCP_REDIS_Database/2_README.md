README.md

# Zero-Copy TCP/IP Stack + Redis-like Database

## 📚 Complete Learning and Deployment Guide

This project implements a **kernel-bypass TCP/IP stack** with a **Redis-compatible in-memory database** from scratch in C. It's designed as a comprehensive learning resource for systems programming, networking, and high-performance computing.

---

## 🎯 Project Overview

### What You'll Learn

This project covers advanced systems programming concepts:

1. **Low-Level Networking**
   - Raw packet I/O (AF_PACKET sockets)
   - Ethernet frame parsing
   - IP/TCP protocol implementation
   - ARP and ICMP handling
   - Checksum calculations

2. **TCP/IP Stack Implementation**
   - TCP state machine (11 states)
   - Sequence number management
   - Sliding window protocol
   - Retransmission timers
   - Out-of-order packet reassembly

3. **Protocol Design**
   - RESP (Redis Serialization Protocol) parser
   - Zero-copy parsing techniques
   - State machine design

4. **Data Structures**
   - Robin Hood hash tables
   - Quicklists (ziplist + linked list hybrid)
   - Skiplists for sorted sets
   - Timing wheels for expiration

5. **Performance Optimization**
   - Cache-friendly data layouts
   - Memory alignment
   - Lock-free sharding
   - Batch processing

---

## 📖 Learning Path: Where to Start

### Phase 1: Understanding the Architecture (Days 1-3)

**Goal**: Understand how all components fit together

#### Start Here:
1. **Read the Plan Document** (`Plan.md`)
   - Skip the code initially
   - Focus on: "Part 1: Architecture Overview"
   - Understand the layer diagram
   - Note how packets flow: NIC → Ethernet → IP → TCP → RESP → Commands

2. **Review Main Server File** (`redis_tcp_server.c`)
   - Start with `main()` function (line ~700)
   - Trace execution flow:
     ```
     main() 
       ↓
     open_raw_socket()        // Opens AF_PACKET socket
       ↓
     main_loop()              // Receives packets
       ↓
     process_packet()         // Parses Ethernet/IP
       ↓
     handle_arp_packet()      // Handles ARP
     ```

3. **Understand Key Concepts**:
   - **Why bypass the kernel?**
     - Normal sockets: App → Kernel → NIC (2+ context switches)
     - Raw sockets: App → NIC directly (0 context switches)
     - 10x latency reduction
   
   - **Why raw Ethernet frames?**
     - We implement our own TCP/IP stack
     - Full control over packet processing
     - Can optimize for our specific use case

#### Learning Exercise:
Draw the packet flow diagram by hand. Label each layer.

---

### Phase 2: Network Fundamentals (Days 4-7)

**Goal**: Understand packet structures and parsing

#### Files to Study:
1. **Packet Structures** (`redis_tcp_server.c` lines 170-240)
   ```c
   eth_hdr_t    // Ethernet: MAC addresses + ethertype
   ip_hdr_t     // IPv4: addresses, protocol, checksum
   tcp_hdr_t    // TCP: ports, seq/ack, flags, window
   arp_pkt_t    // ARP: IP↔MAC mapping
   ```

2. **Key Functions**:
   - `ip_checksum()` - Line 280
   - `tcp_checksum()` - Line 298
   - `handle_arp_packet()` - Line 330
   - `process_packet()` - Line 390

#### Hands-On Exercise:
1. Use Wireshark to capture real packets on your machine
2. Compare Wireshark's dissection with our structures
3. Calculate a checksum manually for a packet

#### Deep Dive Questions:
- Why does TCP checksum include a "pseudo-header"?
- What happens if you send a packet with wrong checksum?
- Why is ARP necessary?

---

### Phase 3: TCP State Machine (Days 8-12)

**Goal**: Master the TCP protocol implementation

#### Files to Study:
1. **TCP Stack** (`tcp_stack_impl.c` - from documents)
   - TCP states enum (lines 50-65)
   - Connection structure (lines 80-150)
   - `tcp_input()` function (lines 400-650)

2. **Critical Concepts**:
   - **Three-way handshake**:
     ```
     Client               Server
        |                    |
        |------ SYN -------->|  (SYN_SENT)
        |                    |  (SYN_RCVD)
        |<--- SYN+ACK -------|
        |                    |
        |------ ACK -------->|  (ESTABLISHED)
     ```
   
   - **Sequence Numbers**: Track every byte
     - `snd_una`: Oldest unACKed byte
     - `snd_nxt`: Next byte to send
     - `rcv_nxt`: Next expected byte
   
   - **Out-of-Order Handling**:
     - Packets can arrive in wrong order
     - Buffer them until gaps are filled

#### Learning Exercise:
1. Trace a complete TCP connection establishment
2. Draw the state diagram for connection close
3. Simulate packet loss: what happens?

#### Code Reading Path:
```
tcp_input()
  ├─ TCP_LISTEN state
  │    └─ Receives SYN → Creates connection → Sends SYN-ACK
  ├─ TCP_SYN_RCVD state  
  │    └─ Receives ACK → ESTABLISHED
  ├─ TCP_ESTABLISHED state
  │    ├─ Process ACK (update snd_una)
  │    ├─ Process data (copy to recv buffer)
  │    └─ Handle FIN (close request)
  └─ Other states (FIN_WAIT, CLOSE_WAIT, etc.)
```

---

### Phase 4: RESP Protocol Parser (Days 13-15)

**Goal**: Understand Redis protocol and zero-copy parsing

#### Files to Study:
1. **RESP Parser** (`resp_parser_impl.c` - from documents)
   - Parser state machine (lines 50-100)
   - `resp_parse()` function (lines 150-400)

2. **RESP Format Examples**:
   ```
   Command: SET key value
   Wire format:
   *3\r\n              # Array with 3 elements
   $3\r\n              # Bulk string, 3 bytes
   SET\r\n             # "SET"
   $3\r\n              # Bulk string, 3 bytes  
   key\r\n             # "key"
   $5\r\n              # Bulk string, 5 bytes
   value\r\n           # "value"
   ```

3. **Zero-Copy Technique**:
   ```c
   // BAD: Copy strings
   char *key = malloc(key_len);
   memcpy(key, buffer, key_len);
   
   // GOOD: Just store pointer
   uint8_t *key = buffer + offset;  // No copy!
   ```

#### Learning Exercise:
1. Write RESP commands by hand and send via `netcat`:
   ```bash
   echo -ne "*1\r\n\$4\r\nPING\r\n" | nc localhost 6379
   ```
2. Parse the response
3. Try pipelining: send multiple commands at once

#### Deep Dive Questions:
- Why use length-prefixed format vs. null-terminated?
- How does zero-copy parsing improve performance?
- What happens if client sends malformed RESP?

---

### Phase 5: Data Structures (Days 16-20)

**Goal**: Understand high-performance data structure design

#### 5.1 Robin Hood Hash Table

**Location**: `hash_table_impl.c` (from documents)

**Key Insight**: Minimize variance in probe distances
```
Traditional linear probing:
  Slot: [0] [1] [2] [3] [4] [5]
  Data: [A] [B] [C] [D] [E] [ ]
  If adding X that hashes to 0:
    A has PSL=0, B has PSL=1, C has PSL=2...
    X probes 6 times (slow!)

Robin Hood probing:
  Steal from "rich" entries (low PSL)
  If X probes 3 times but slot has PSL=1:
    Swap X and slot's entry
  Result: More balanced probe lengths
```

**Study**:
1. `hash_get()` - Line ~100
2. `hash_set()` - Line ~140  
3. `hash_delete()` - Line ~200 (backshift deletion)

#### 5.2 Quicklist (Redis Lists)

**Location**: `quicklist_impl.c` (from documents)

**Design**: Linked list of small arrays
```
[Node1: ziplist]-->[Node2: ziplist]-->[Node3: ziplist]
   [a][b][c]          [d][e][f]          [g][h]
   
Benefits:
- Fast O(1) push/pop at both ends
- Cache-friendly: arrays are contiguous
- Memory-efficient: compressed representation
```

**Study**:
1. `quicklist_push_head()` - Creates nodes as needed
2. `quicklist_iter()` - Efficient traversal

#### 5.3 Skiplist (Sorted Sets)

**Location**: `skiplist_impl.c` (from documents)

**Design**: Probabilistic balanced tree
```
Level 3:  [Header]------------------------>[Node D]->NULL
Level 2:  [Header]-------->[Node B]-------->[Node D]->NULL  
Level 1:  [Header]-->[Node A]->[Node B]->[Node C]->[Node D]->NULL
Level 0:  [Header]-->[Node A]->[Node B]->[Node C]->[Node D]->NULL
          
Lookup time: O(log N) average
Simpler than red-black trees!
```

**Study**:
1. `skiplist_insert()` - Random level generation
2. `skiplist_range()` - Efficient range queries

#### Learning Exercise:
Implement a simple version of each data structure and benchmark it.

---

### Phase 6: Command Handlers (Days 21-23)

**Goal**: Implement Redis commands

#### Files to Study:
1. **Command Dispatch** (`command_handlers.c` - from documents)
   - `dispatch_command()` - Finds and executes commands
   - Command table (lines 50-80)

2. **Example Commands**:
   - `cmd_set()` - Store key-value
   - `cmd_get()` - Retrieve value  
   - `cmd_lpush()` - Push to list
   - `cmd_lrange()` - Range query

#### Implementation Pattern:
```c
void cmd_get(conn_t *conn, hash_table_t *db,
             uint8_t **args, size_t *arg_lens, int argc) {
    // 1. Parse arguments
    uint8_t *key = args[1];
    size_t key_len = arg_lens[1];
    
    // 2. Lookup in database
    db_value_t *val = hash_get(db, key, key_len);
    
    // 3. Type checking
    if (val->type != DB_TYPE_STRING) {
        send_error(conn, "WRONGTYPE");
        return;
    }
    
    // 4. Send response
    send_bulk_string(conn, val->string.data, val->string.len);
}
```

#### Learning Exercise:
Add a new command (e.g., `INCR` for atomic increment).

---

## 🚀 Building and Running

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y build-essential gcc make git

# Fedora/RHEL
sudo dnf install gcc make git

# Arch Linux
sudo pacman -S base-devel git
```

### Compilation

```bash
# Clone or navigate to project directory
cd redis-tcp-server/

# Build
make

# Or manually:
gcc -Wall -Wextra -O2 -o redis-tcp-server redis_tcp_server.c -lpthread -lm
```

### Running the Server

**⚠️ IMPORTANT: Requires root privileges** (for raw sockets)

#### Option 1: Loopback (Safe for Testing)
```bash
sudo ./redis-tcp-server \
  --interface lo \
  --ip 127.0.0.1 \
  --port 6379 \
  --log-level 3
```

#### Option 2: Real Network Interface
```bash
# Find your interface
ip addr show

# Run server
sudo ./redis-tcp-server \
  --interface eth0 \
  --ip 192.168.1.100 \
  --port 6379 \
  --log-level 2
```

### Testing Connectivity

#### 1. ARP Test
```bash
# In another terminal
ping 192.168.1.100

# You should see in server logs:
# [INFO] ARP request for our IP, sending reply
```

#### 2. TCP Connection Test
```bash
# Try connecting (this will fail initially since TCP is incomplete)
telnet 192.168.1.100 6379

# You should see:
# [DEBUG] Received TCP packet
```

---

## 🔧 Development Workflow

### Daily Development Cycle

1. **Morning**: Read one component's code (30 min)
2. **Implementation**: Add/modify feature (2-3 hours)
3. **Testing**: Verify with packet capture (30 min)
4. **Documentation**: Update notes (15 min)

### Debugging Tools

#### 1. Wireshark (Packet Capture)
```bash
# Install
sudo apt-get install wireshark

# Run (requires sudo)
sudo wireshark

# Filter for your IP
ip.addr == 192.168.1.100

# Save captures for analysis
```

#### 2. tcpdump (Command-Line Capture)
```bash
# Capture packets on interface
sudo tcpdump -i eth0 -w capture.pcap

# Read capture file
tcpdump -r capture.pcap -v

# Filter by port
sudo tcpdump -i eth0 port 6379
```

#### 3. GDB (Debugger)
```bash
# Compile with debug symbols
gcc -g -O0 -o redis-tcp-server redis_tcp_server.c

# Run in debugger
sudo gdb ./redis-tcp-server

(gdb) break process_packet
(gdb) run --interface lo --ip 127.0.0.1
(gdb) next
(gdb) print *eth
```

#### 4. Valgrind (Memory Leaks)
```bash
# Install
sudo apt-get install valgrind

# Run (slow but thorough)
sudo valgrind --leak-check=full ./redis-tcp-server
```

### Logging Best Practices

```c
// Add debug logs liberally
log_msg(LOG_DEBUG, "Entering function X");
log_msg(LOG_DEBUG, "Variable Y = %d", y);

// Run with high verbosity
sudo ./redis-tcp-server --log-level 3
```

---

## 📊 Testing Strategy

### Unit Tests (TODO - Not Yet Implemented)

```bash
# Compile tests
gcc -o test_hash tests/test_hash_table.c hash_table.c

# Run
./test_hash
```

### Integration Tests

#### Test 1: ARP Resolution
```bash
# Terminal 1: Start server
sudo ./redis-tcp-server --interface eth0 --ip 192.168.1.100

# Terminal 2: Send ARP request
arping -c 1 192.168.1.100

# Expected: Server responds with its MAC address
```

#### Test 2: ICMP Echo (Ping)
```bash
# Once ICMP handler is implemented
ping -c 4 192.168.1.100

# Expected: 0% packet loss
```

#### Test 3: TCP Connection
```bash
# Once TCP stack is complete
telnet 192.168.1.100 6379

# Expected: Connection established
```

#### Test 4: Redis Commands
```bash
# Once full stack is implemented
redis-cli -h 192.168.1.100 -p 6379

127.0.0.1:6379> PING
PONG
127.0.0.1:6379> SET mykey "Hello"
OK
127.0.0.1:6379> GET mykey
"Hello"
```

---

## 🐛 Common Issues and Solutions

### Issue 1: "Permission denied" when opening socket
**Solution**: Run with `sudo`
```bash
sudo ./redis-tcp-server ...
```

### Issue 2: "Cannot bind to interface"
**Solution**: Check interface exists
```bash
ip link show
# Use correct interface name (eth0, enp0s3, wlan0, etc.)
```

### Issue 3: "ARP replies not working"
**Solution**: Check firewall rules
```bash
# Disable firewall temporarily (testing only!)
sudo iptables -F
sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT
```

### Issue 4: Packets not arriving
**Solution**: Use Wireshark to verify
```bash
# 1. Check packets are on wire
sudo tcpdump -i eth0 -n

# 2. Verify MAC address
ip link show eth0

# 3. Confirm IP configuration
ip addr show eth0
```

### Issue 5: Segmentation fault
**Solution**: Use GDB
```bash
sudo gdb ./redis-tcp-server
(gdb) run --interface lo --ip 127.0.0.1
# When it crashes:
(gdb) backtrace
(gdb) print variable_name
```

---

## 📈 Performance Benchmarking

### Once Complete:

#### 1. Latency Test
```bash
# Using redis-benchmark
redis-benchmark -h 192.168.1.100 -p 6379 -t ping,set,get -n 100000

# Expected results:
# PING: <100μs p99
# SET:  <200μs p99  
# GET:  <150μs p99
```

#### 2. Throughput Test
```bash
redis-benchmark -h 192.168.1.100 -p 6379 -t set -n 1000000 -c 50

# Expected: 200K+ ops/sec (single-threaded)
```

#### 3. Compare vs. Kernel Stack
```bash
# Standard Redis (kernel TCP)
redis-benchmark -h 127.0.0.1 -p 6380 -t get -n 100000

# Our server (userspace TCP)
redis-benchmark -h 192.168.1.100 -p 6379 -t get -n 100000

# Compare latency histograms
```

---

## 🎓 Advanced Topics (After Completing Basics)

### 1. Multi-Threading (Week 4-5)
- Per-core sharding
- Lock-free data structures
- SO_REUSEPORT for connection distribution

### 2. AF_XDP Integration (Week 6)
- True zero-copy I/O
- UMEM configuration
- XDP program attachment

### 3. Persistence (Week 7)
- AOF (Append-Only File)
- RDB snapshots
- Background saving with fork()

### 4. Replication (Week 8)
- Master-slave architecture
- Partial resync
- Replication log

---

## 📚 Recommended Reading

### Books
1. **"TCP/IP Illustrated, Volume 1"** by W. Richard Stevens
   - The Bible of TCP/IP
   - Read chapters: 2 (Link Layer), 3 (IP), 17-24 (TCP)

2. **"Computer Networks"** by Andrew Tanenbaum
   - Chapters on data link, network, transport layers

3. **"The Linux Programming Interface"** by Michael Kerrisk
   - Chapter 61: Sockets - Advanced Topics

### Online Resources
1. **RFCs (Request for Comments)**
   - RFC 791: Internet Protocol
   - RFC 793: Transmission Control Protocol
   - RFC 826: Ethernet Address Resolution Protocol

2. **Redis Documentation**
   - RESP Protocol: https://redis.io/docs/reference/protocol-spec/
   - Internal Data Structures: https://redis.io/docs/data-types/

3. **Articles**
   - "Robin Hood Hashing": https://programming.guide/robin-hood-hashing.html
   - "Redis Quicklist": https://matt.sh/redis-quicklist
   - "Kernel Bypass": https://blog.cloudflare.com/kernel-bypass/

---

## 🤝 Contributing

This is a learning project! Ways to contribute:

1. **Fix Bugs**: Submit pull requests
2. **Add Features**: Implement missing commands
3. **Improve Documentation**: Clarify confusing sections
4. **Share Your Experience**: Write blog posts about your learning journey

---

## 📝 Project Status

### ✅ Implemented
- [x] Raw socket initialization
- [x] Ethernet frame parsing
- [x] ARP handling
- [x] ARP cache
- [x] IP checksum validation
- [x] Basic packet filtering
- [x] Logging system
- [x] Configuration

### 🚧 In Progress (Need to Complete)
- [ ] TCP state machine integration
- [ ] TCP segment transmission
- [ ] RESP parser integration
- [ ] Command dispatch wiring
- [ ] Hash table integration
- [ ] Retransmission timers

### 📋 TODO
- [ ] ICMP echo reply
- [ ] TCP out-of-order reassembly
- [ ] All Redis commands
- [ ] Lists (Quicklist)
- [ ] Sorted sets (Skiplist)
- [ ] Key expiration
- [ ] Persistence (AOF)
- [ ] Multi-threading
- [ ] AF_XDP support

---

## 🎯 Learning Milestones

### Week 1: Network Basics
- [ ] Understand OSI model
- [ ] Parse Ethernet frame
- [ ] Implement ARP reply
- [ ] Calculate checksums

### Week 2: TCP Foundation
- [ ] Understand TCP state diagram
- [ ] Implement 3-way handshake
- [ ] Handle sequence numbers
- [ ] Send/receive data

### Week 3: Application Layer
- [ ] Parse RESP protocol
- [ ] Implement SET/GET commands
- [ ] Add error handling
- [ ] Test with redis-cli

### Week 4: Data Structures
- [ ] Robin Hood hash table
- [ ] Quicklist for lists
- [ ] Skiplist for sorted sets
- [ ] Benchmark performance

### Week 5: Advanced Features
- [ ] Key expiration
- [ ] Retransmission
- [ ] Multi-threading
- [ ] Persistence

---

## 💡 Tips for Success

1. **Start Small**: Don't try to implement everything at once
2. **Test Frequently**: Verify each component before moving on
3. **Read Real Packets**: Use Wireshark constantly
4. **Draw Diagrams**: Visualize state machines and data flows
5. **Take Notes**: Document your understanding
6. **Ask Questions**: Join networking/systems programming communities
7. **Be Patient**: This is complex! It's okay to take time

---

## 🆘 Getting Help

### When Stuck:

1. **Check Logs**: Increase log level to DEBUG
2. **Packet Capture**: See what's actually on the wire
3. **Read RFCs**: The specifications are authoritative
4. **Draw It Out**: State diagrams help immensely
5. **Take a Break**: Come back with fresh eyes

### Communities:
- Stack Overflow: [network-programming] tag
- Reddit: r/networking, r/systems
- IRC: ##networking on Libera.Chat

---

## 📄 License

This project is for educational purposes. See LICENSE file for details.

---

## 🙏 Acknowledgments

- Based on Redis architecture and algorithms
- Inspired by DPDK and AF_XDP projects
- Educational resources from Stevens, Tanenbaum, and others

---

## 📞 Contact

For questions about this implementation, open an issue on the repository.

**Happy Learning! 🚀**

---

*Last Updated: 2024*
*Project Status: Educational/Learning Implementation*