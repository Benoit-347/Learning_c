LEARNING_TRACKER.md

# Learning Progress Tracker

## 📊 Your Journey Through the Codebase

Track your understanding and implementation progress. Check off items as you complete them!

---

## Week 1: Foundations

### Day 1: Understanding the Big Picture
- [ ] Read README.md "Project Overview" section
- [ ] Understand why kernel bypass matters
- [ ] Draw the network stack layers (Ethernet → IP → TCP → RESP)
- [ ] Review the architectural diagram in Plan.md
- [ ] Can explain to someone: "What problem does this project solve?"

**Quiz Yourself**:
- What are the 5 layers in our stack?
- Why is zero-copy faster than standard sockets?
- What's the difference between AF_PACKET and AF_XDP?

---

### Day 2: Setting Up & First Run
- [ ] Install dependencies (make deps)
- [ ] Build the project (make)
- [ ] Run server on loopback (sudo make run)
- [ ] See server logs output
- [ ] Send ARP request (arping) and verify response
- [ ] Understand what "raw socket" means

**Lab Exercise**:
```bash
# In Terminal 1:
sudo ./redis-tcp-server --interface lo --ip 127.0.0.1 --log-level 3

# In Terminal 2:
sudo arping -c 1 -I lo 127.0.0.1

# Question: What packets did you see? Why?
```

---

### Day 3: Packet Structures
- [ ] Read `redis_tcp_server.c` lines 170-240 (packet structures)
- [ ] Understand `eth_hdr_t` (Ethernet header)
- [ ] Understand `ip_hdr_t` (IPv4 header)
- [ ] Understand `tcp_hdr_t` (TCP header)
- [ ] Understand `arp_pkt_t` (ARP packet)
- [ ] Know what "network byte order" means (htons, ntohs)

**Hands-On**:
- [ ] Use Wireshark to capture a real packet
- [ ] Compare Wireshark's display with our structures
- [ ] Identify all fields in a TCP packet

**Quiz**:
- What's the size of an Ethernet header? (14 bytes)
- What's the size of an IPv4 header? (20 bytes minimum)
- What's the size of a TCP header? (20 bytes minimum)
- What is ethertype 0x0800? (IPv4)
- What is ethertype 0x0806? (ARP)

---

### Day 4: Checksums & Validation
- [ ] Read `ip_checksum()` function (line ~280)
- [ ] Read `tcp_checksum()` function (line ~298)
- [ ] Understand why TCP includes pseudo-header
- [ ] Understand one's complement arithmetic
- [ ] Calculate a checksum by hand (for practice)

**Lab Exercise**:
```c
// Write a small test program:
uint8_t data[] = {0x45, 0x00, 0x00, 0x28, ...};
uint16_t csum = ip_checksum(data, 20);
printf("Checksum: 0x%04x\n", csum);

// Verify with Wireshark
```

---

### Day 5: ARP Protocol
- [ ] Read `handle_arp_packet()` function (line ~330)
- [ ] Understand ARP request vs. reply
- [ ] Read `arp_cache_lookup()` function
- [ ] Read `arp_cache_add()` function
- [ ] Know why ARP is needed

**Experiments**:
- [ ] Clear your ARP cache: `sudo ip neigh flush all`
- [ ] Ping a machine: `ping 192.168.1.1`
- [ ] Watch ARP in Wireshark
- [ ] See ARP request → ARP reply → ICMP packets

**Quiz**:
- Why can't we send IP packets without ARP?
- What information does ARP provide?
- How long should ARP cache entries last?

---

### Day 6-7: Main Packet Processing Loop
- [ ] Read `main_loop()` function
- [ ] Read `process_packet()` function (line ~390)
- [ ] Understand packet filtering (MAC address check)
- [ ] Understand ethertype switching (ARP vs. IPv4)
- [ ] Trace execution: socket read → parse → process
- [ ] Add your own debug logs and rebuild

**Lab**:
- [ ] Add log statement at start of `process_packet()`
- [ ] Rebuild and run
- [ ] Generate traffic (ping)
- [ ] Confirm your log appears

---

## Week 2: TCP Protocol

### Day 8: TCP State Machine Theory
- [ ] Read RFC 793 (TCP specification) - at least the state diagram
- [ ] Draw TCP state machine by hand (all 11 states)
- [ ] Understand 3-way handshake:
  - Client: CLOSED → SYN_SENT → ESTABLISHED
  - Server: CLOSED → LISTEN → SYN_RCVD → ESTABLISHED
- [ ] Understand 4-way close (FIN handshake)
- [ ] Know what each state means

**States to Memorize**:
- [ ] CLOSED - No connection
- [ ] LISTEN - Waiting for connections
- [ ] SYN_SENT - Sent SYN, waiting for SYN-ACK
- [ ] SYN_RCVD - Received SYN, sent SYN-ACK
- [ ] ESTABLISHED - Connection open, can exchange data
- [ ] FIN_WAIT_1 - Sent FIN, waiting for ACK
- [ ] FIN_WAIT_2 - Received ACK of FIN, waiting for their FIN
- [ ] CLOSE_WAIT - Received FIN, waiting for app to close
- [ ] CLOSING - Both sides closing simultaneously
- [ ] LAST_ACK - Sent FIN, waiting for ACK
- [ ] TIME_WAIT - Waiting 2*MSL before closing

---

### Day 9: TCP Sequence Numbers
- [ ] Understand what sequence numbers track (byte position)
- [ ] Understand `snd_una` (oldest unACKed byte)
- [ ] Understand `snd_nxt` (next byte to send)
- [ ] Understand `rcv_nxt` (next expected byte)
- [ ] Understand why sequence numbers wrap around (32-bit)
- [ ] Learn SEQ_LT, SEQ_GT macros for wraparound comparison

**Practice**:
```
Connection starts with ISN = 1000
Client sends: "GET" (3 bytes)
  seq = 1000, len = 3
  After send: snd_nxt = 1003

Server ACKs:
  ack = 1003 (means "I got bytes 1000-1002")

Client's snd_una updates to 1003
```

---

### Day 10: TCP Implementation Study
- [ ] Read `tcp_connection` structure (from documents)
- [ ] Read `tcp_input()` function (from documents)
- [ ] Trace through LISTEN state handling
- [ ] Trace through SYN_RCVD state handling
- [ ] Trace through ESTABLISHED state handling
- [ ] Understand how data is copied to recv_buf

**Code Reading Exercise**:
```c
// Follow this flow:
1. Packet arrives with SYN flag
2. tcp_input() called
3. Switch to TCP_LISTEN case
4. Create new connection
5. Set state = SYN_RCVD
6. Send SYN-ACK
7. Wait for ACK
8. Receive ACK
9. Switch to TCP_SYN_RCVD case
10. Validate ACK number
11. Set state = ESTABLISHED
```

---

### Day 11-12: TCP Integration
- [ ] Read TODO.md Task #1 (TCP State Machine Integration)
- [ ] Add `tcp_input()` call to `process_packet()`
- [ ] Implement `send_tcp_packet()` function
- [ ] Create listener connection
- [ ] Test 3-way handshake with telnet
- [ ] Verify connection reaches ESTABLISHED state

**Milestone**: `telnet 127.0.0.1 6379` connects successfully

---

### Day 13-14: TCP Data Transfer
- [ ] Understand TCP sliding window
- [ ] Implement data reception (copy to recv_buf)
- [ ] Implement data transmission (MSS segmentation)
- [ ] Test sending data from server
- [ ] Test receiving data from client
- [ ] Verify sequence number updates

---

## Week 3: RESP Protocol

### Day 15: RESP Format Study
- [ ] Read RESP specification (redis.io/docs/reference/protocol-spec/)
- [ ] Understand RESP types:
  - Simple String: `+OK\r\n`
  - Error: `-ERR message\r\n`
  - Integer: `:123\r\n`
  - Bulk String: `$6\r\nfoobar\r\n`
  - Array: `*3\r\n$3\r\nSET\r\n$3\r\nkey\r\n$5\r\nvalue\r\n`
- [ ] Write RESP by hand
- [ ] Parse RESP by hand

**Exercise**:
```bash
# Send raw RESP to Redis (for practice):
echo -ne "*1\r\n\$4\r\nPING\r\n" | nc localhost 6379
# Should receive: +PONG\r\n

# Try SET:
echo -ne "*3\r\n\$3\r\nSET\r\n\$3\r\nkey\r\n\$5\r\nvalue\r\n" | nc localhost 6379
```

---

### Day 16: RESP Parser Study
- [ ] Read `resp_parser` structure (from documents)
- [ ] Read `resp_parse()` function (from documents)
- [ ] Understand state machine states
- [ ] Understand zero-copy parsing (pointers, not copies)
- [ ] Trace parsing of: `*2\r\n$3\r\nGET\r\n$3\r\nkey\r\n`

**State Flow**:
```
RESP_STATE_TYPE → '*'
RESP_STATE_ARRAY_LEN → '2'
RESP_STATE_TYPE → '$'
RESP_STATE_BULK_LEN → '3'
RESP_STATE_BULK_DATA → 'GET'
... (repeat for 2nd element)
RESP_STATE_COMPLETE
```

---

### Day 17-18: RESP Integration
- [ ] Read TODO.md Task #4 (RESP Parser Integration)
- [ ] Add RESP parser to TCP connection
- [ ] Call `resp_parse()` when data available
- [ ] Handle RESP_OK (command complete)
- [ ] Handle RESP_INCOMPLETE (need more data)
- [ ] Handle RESP_ERROR (protocol error)
- [ ] Test with `echo -ne "..." | nc`

**Milestone**: Can receive and parse complete RESP commands

---

### Day 19: Response Encoding
- [ ] Implement `send_simple_string()`
- [ ] Implement `send_error()`
- [ ] Implement `send_integer()`
- [ ] Implement `send_bulk_string()`
- [ ] Implement `send_array_header()`
- [ ] Test each encoding function

---

### Day 20: Command Dispatch
- [ ] Read `dispatch_command()` function
- [ ] Understand command table lookup
- [ ] Implement PING command
- [ ] Implement ECHO command
- [ ] Test with netcat

**Milestone**: PING and ECHO work end-to-end

---

## Week 4: Data Storage

### Day 21: Hash Table Theory
- [ ] Understand hash functions
- [ ] Understand collision resolution:
  - Chaining (linked lists)
  - Open addressing (linear probing)
  - Robin Hood hashing (swap on collision)
- [ ] Understand load factor and resizing
- [ ] Read Robin Hood article (thenumb.at)

**Quiz**:
- What's a good load factor? (0.7-0.8)
- When should we resize? (load > 0.7)
- What's PSL? (Probe Sequence Length)

---

### Day 22: Hash Table Implementation
- [ ] Read `hash_table` structure
- [ ] Read `hash_get()` function
- [ ] Read `hash_set()` function
- [ ] Read `hash_delete()` function (backshift deletion)
- [ ] Understand Robin Hood swapping
- [ ] Write small test program

**Lab**:
```c
hash_table_t *ht = hash_table_create(16);
hash_set(ht, "key1", 4, "value1");
hash_set(ht, "key2", 4, "value2");
char *val = hash_get(ht, "key1", 4);
printf("Got: %s\n", val);
```

---

### Day 23-24: SET/GET Commands
- [ ] Read TODO.md Task #5 (Initialize Database)
- [ ] Create global hash table
- [ ] Implement `cmd_set()` function
- [ ] Implement `cmd_get()` function
- [ ] Implement `cmd_del()` function
- [ ] Test with redis-cli

**Milestone**: Can store and retrieve key-value pairs!

---

### Day 25: Lists (Quicklist)
- [ ] Understand Quicklist design (linked list of arrays)
- [ ] Read ziplist implementation
- [ ] Read quicklist implementation
- [ ] Implement LPUSH command
- [ ] Implement LPOP command
- [ ] Implement LRANGE command

---

### Day 26: Sorted Sets (Skiplist)
- [ ] Understand skiplist design
- [ ] Read skiplist implementation
- [ ] Implement ZADD command
- [ ] Implement ZRANGE command
- [ ] Implement ZREM command

---

### Day 27-28: Testing & Debugging
- [ ] Run redis-benchmark
- [ ] Test all commands
- [ ] Fix bugs found
- [ ] Add more logging
- [ ] Optimize hot paths

---

## Week 5: Advanced Features

### Day 29-30: Key Expiration
- [ ] Understand timing wheel data structure
- [ ] Implement expiration tracking
- [ ] Add TTL to SET command
- [ ] Implement passive expiration (check on GET)
- [ ] Implement active expiration (periodic scan)

---

### Day 31-32: Retransmission
- [ ] Implement retransmission timer
- [ ] Implement RTO calculation
- [ ] Implement exponential backoff
- [ ] Test with packet loss (tc netem)
- [ ] Verify retransmission works

---

### Day 33-34: Performance Optimization
- [ ] Profile with perf
- [ ] Identify hot spots
- [ ] Optimize packet processing
- [ ] Optimize data structures
- [ ] Benchmark before/after

---

### Day 35: Documentation
- [ ] Document all functions
- [ ] Write architecture document
- [ ] Create diagrams
- [ ] Write tutorial
- [ ] Share your learning!

---

## Mastery Checklist

### Understanding
- [ ] Can explain OSI model layers
- [ ] Can explain TCP 3-way handshake
- [ ] Can explain RESP protocol
- [ ] Can explain Robin Hood hashing
- [ ] Can explain skiplist data structure
- [ ] Can explain kernel bypass benefits

### Implementation
- [ ] Completed all TODO.md tasks
- [ ] All tests passing
- [ ] No memory leaks (valgrind)
- [ ] Can connect with redis-cli
- [ ] All basic commands work
- [ ] Handles packet loss gracefully

### Performance
- [ ] Measured latency (p50, p99, p999)
- [ ] Measured throughput (ops/sec)
- [ ] Compared to standard Redis
- [ ] Identified bottlenecks
- [ ] Optimized critical paths

---

## Celebration Milestones 🎉

- [ ] **Week 1**: First packet processed! 🎊
- [ ] **Week 2**: TCP handshake works! 🤝
- [ ] **Week 3**: PING/ECHO work! 🏓
- [ ] **Week 4**: SET/GET work! 💾
- [ ] **Week 5**: Full Redis commands! 🚀
- [ ] **Final**: Production-ready server! 🏆

---

## Daily Learning Log Template

```
Date: ___________

What I learned today:
- 
- 
- 

What I built/fixed:
- 
- 

Challenges faced:
- 

Questions to research:
- 

Tomorrow's goals:
- 
- 
```

---

## Resources Consulted

### Books
- [ ] TCP/IP Illustrated Vol. 1 (Stevens)
- [ ] Computer Networks (Tanenbaum)
- [ ] The Linux Programming Interface (Kerrisk)

### RFCs
- [ ] RFC 791 (IPv4)
- [ ] RFC 793 (TCP)
- [ ] RFC 826 (ARP)

### Articles
- [ ] Robin Hood Hashing
- [ ] Redis Quicklist
- [ ] Kernel Bypass Techniques

### Tools Mastered
- [ ] Wireshark
- [ ] tcpdump
- [ ] GDB
- [ ] Valgrind
- [ ] perf

---

## Skills Acquired

### Systems Programming
- [ ] Raw socket programming
- [ ] Packet parsing
- [ ] Protocol implementation
- [ ] State machines
- [ ] Memory management
- [ ] Concurrency

### Networking
- [ ] OSI model
- [ ] Ethernet
- [ ] IP
- [ ] TCP
- [ ] ARP
- [ ] Checksums

### Data Structures
- [ ] Hash tables
- [ ] Linked lists
- [ ] Skip lists
- [ ] Ring buffers
- [ ] Timing wheels

### Tools & Debugging
- [ ] GDB debugging
- [ ] Packet capture
- [ ] Performance profiling
- [ ] Memory leak detection
- [ ] Network troubleshooting

---

**Remember**: Learning is a journey, not a race. Take your time, experiment, break things, and most importantly, have fun! 🚀

**Current Status**: _____ out of 35 days complete

**Completion Date**: __________

**Favorite Learning Moment**: ______________________________