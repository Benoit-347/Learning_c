QUICKSTART.md

# Quick Start Guide

## 🚀 Get Running in 5 Minutes

This guide gets you from zero to a running server quickly.

---

## Step 1: Install Dependencies (1 minute)

```bash
# Ubuntu/Debian
sudo apt-get update && sudo apt-get install -y build-essential gcc make

# Fedora/RHEL  
sudo dnf install gcc make

# Arch Linux
sudo pacman -S base-devel
```

---

## Step 2: Build the Server (30 seconds)

```bash
# Navigate to project directory
cd /home/claude/

# Compile
make

# Verify build succeeded
ls -lh redis-tcp-server
```

Expected output:
```
-rwxr-xr-x 1 user user 45K Dec 19 10:30 redis-tcp-server
```

---

## Step 3: Run on Loopback (30 seconds)

**Why loopback?** It's safe - won't interfere with your network.

```bash
# Start server (requires sudo for raw sockets)
sudo ./redis-tcp-server --interface lo --ip 127.0.0.1 --port 6379 --log-level 3
```

Expected output:
```
===============================================
  Zero-Copy TCP/IP Stack + Redis Server
  Systems Engineering Learning Project
===============================================

[2024-12-19 10:30:00.000] [INFO] Interface lo MAC: 00:00:00:00:00:00
[2024-12-19 10:30:00.001] [INFO] Raw socket opened on interface lo
[2024-12-19 10:30:00.002] [INFO] Server initialized successfully
[2024-12-19 10:30:00.003] [INFO] Configuration:
[2024-12-19 10:30:00.004] [INFO]   Interface: lo
[2024-12-19 10:30:00.005] [INFO]   IP: 127.0.0.1
[2024-12-19 10:30:00.006] [INFO]   Port: 6379
[2024-12-19 10:30:00.007] [INFO] Entering main packet processing loop
[2024-12-19 10:30:00.008] [INFO] Listening on 127.0.0.1:6379
```

**Server is now running!** Keep this terminal open.

---

## Step 4: Test ARP (1 minute)

Open a **new terminal** and run:

```bash
# Send ARP request to our IP
sudo arping -c 1 -I lo 127.0.0.1
```

In the **server terminal**, you should see:
```
[2024-12-19 10:31:00.123] [DEBUG] Received ARP packet
[2024-12-19 10:31:00.124] [DEBUG] ARP request for our IP, sending reply
```

**✅ Success!** Your server received and responded to an ARP request.

---

## Step 5: Test with Ping (1 minute)

```bash
# From another terminal
ping -c 4 127.0.0.1
```

**Current Status**: Won't work yet (ICMP not fully implemented), but you should see in server logs:
```
[DEBUG] Received TCP packet (type: ICMP)
```

This proves packets are reaching your server!

---

## Step 6: Capture Packets (Optional - 2 minutes)

Watch the packets in real-time:

```bash
# Terminal 3: Start packet capture
sudo tcpdump -i lo -n -v

# Terminal 2: Generate traffic
ping -c 2 127.0.0.1

# Observe output - you'll see:
# - ICMP Echo Request
# - ICMP Echo Reply (from kernel)
# - Your server's packets (if any)
```

---

## Next Steps

### Option A: Study the Code
Follow the **Learning Path** in README.md, starting with Phase 1.

### Option B: Complete the Implementation
See **TODO.md** for missing components to implement:
1. TCP input integration
2. RESP parser integration  
3. Command handlers

### Option C: Run on Real Network

```bash
# Find your network interface
ip addr show

# Example: interface is eth0, your IP is 192.168.1.100
sudo ./redis-tcp-server \
  --interface eth0 \
  --ip 192.168.1.100 \
  --port 6379 \
  --log-level 2
```

**⚠️ Warning**: This will attempt to take over that IP address!

---

## Troubleshooting

### Problem: "Permission denied"
**Solution**: 
```bash
sudo ./redis-tcp-server ...  # Need root for raw sockets
```

### Problem: "Cannot open interface"
**Solution**: Check interface name
```bash
ip link show  # List all interfaces
# Use exact name: lo, eth0, enp0s3, wlan0, etc.
```

### Problem: "Address already in use"
**Solution**: Another process is using that IP
```bash
# Find what's using it
sudo netstat -tuln | grep 6379

# Kill it if necessary
sudo killall redis-server
```

### Problem: No packets received
**Solution**: Verify with tcpdump
```bash
# Watch for any packets on interface
sudo tcpdump -i lo -v

# Generate test traffic
ping 127.0.0.1

# If you see packets, the interface works
```

---

## Quick Reference Commands

```bash
# Build
make clean && make

# Run on loopback (safe)
sudo make run

# Run with debugging
sudo ./redis-tcp-server --interface lo --ip 127.0.0.1 --log-level 3

# Test connectivity
ping -c 1 127.0.0.1
sudo arping -c 1 -I lo 127.0.0.1

# Watch packets
sudo tcpdump -i lo -n

# Stop server
Ctrl+C (in server terminal)
```

---

## What's Working Now?

✅ **Currently Functional**:
- Raw socket creation
- Ethernet frame parsing
- ARP request/reply
- IP checksum validation
- Packet filtering by MAC/IP
- Logging system

🚧 **In Progress**:
- TCP state machine integration
- RESP parsing
- Command execution

❌ **Not Yet Implemented**:
- Full TCP connection handling
- Redis command processing
- Data storage

---

## Files Overview

```
.
├── redis_tcp_server.c    # Main server (START HERE)
├── Makefile              # Build system
├── README.md             # Complete guide
├── QUICKSTART.md         # This file
└── [Other implementation files from documents]
```

---

## Learning Resources

- **Start**: README.md "Learning Path" section
- **Details**: Plan.md for architecture
- **Reference**: RFCs for protocols (RFC 791, 793, 826)

---

## Community & Help

- **Stuck?** Read the "Common Issues" section in README.md
- **Questions?** Check the TODO.md for what needs implementing
- **Learning?** Follow the daily plan in README.md

---

**You're ready to start learning! 🎓**

Go to README.md → "Learning Path" → Phase 1