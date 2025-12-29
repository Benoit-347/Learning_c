PROJECT_STRUCTURE.md

# Project Structure and Organization

## 📁 Complete File Layout

This document explains how to organize the codebase and integrate all components from the uploaded documents.

---

## Current Status

### ✅ Files Created
```
/home/claude/
├── redis_tcp_server.c     # Main server implementation (COMPLETE)
├── Makefile               # Build system (COMPLETE)
├── README.md              # Comprehensive learning guide (COMPLETE)
├── QUICKSTART.md          # Quick start guide (COMPLETE)
├── TODO.md                # Implementation roadmap (COMPLETE)
└── PROJECT_STRUCTURE.md   # This file
```

### 📄 Files from Documents (Need to Extract and Create)
```
├── tcp_stack.c           # From "TCP/IP Stack + Redis Implementation.txt"
├── tcp_stack.h           # Header file
├── data_structures.c     # From "Data Structures & Protocol Handlers.txt"
├── data_structures.h     # Header file
├── packet_utils.c        # From "Packet Construction & Utility Functions.txt"
├── packet_utils.h        # Header file
└── tests/                # Unit tests (to be created)
```

---

## Recommended Project Structure

### Option 1: Single-File (Current - Good for Learning)

**Pros**: Easy to navigate, everything in one place
**Cons**: Large file, harder to compile selectively

```
redis-tcp-server/
├── redis_tcp_server.c    # All code in one file
├── Makefile
├── README.md
├── QUICKSTART.md
└── TODO.md
```

**Usage**: Great for initial learning and prototyping.

---

### Option 2: Modular Structure (Recommended for Development)

**Pros**: Clean separation, easier to maintain
**Cons**: More files to manage

```
redis-tcp-server/
├── src/
│   ├── main.c                 # Main entry point (from redis_tcp_server.c)
│   ├── network/
│   │   ├── raw_socket.c       # Socket operations
│   │   ├── raw_socket.h
│   │   ├── arp.c              # ARP handling
│   │   ├── arp.h
│   │   ├── checksum.c         # Checksums
│   │   └── checksum.h
│   ├── tcp/
│   │   ├── tcp_stack.c        # TCP state machine
│   │   ├── tcp_stack.h
│   │   ├── tcp_conn.c         # Connection management
│   │   └── tcp_conn.h
│   ├── protocol/
│   │   ├── resp_parser.c      # RESP parsing
│   │   ├── resp_parser.h
│   │   ├── resp_encoder.c     # RESP encoding
│   │   └── resp_encoder.h
│   ├── engine/
│   │   ├── hash_table.c       # Robin Hood hash
│   │   ├── hash_table.h
│   │   ├── quicklist.c        # List data structure
│   │   ├── quicklist.h
│   │   ├── skiplist.c         # Sorted sets
│   │   ├── skiplist.h
│   │   ├── timing_wheel.c     # Expiration
│   │   └── timing_wheel.h
│   ├── commands/
│   │   ├── cmd_string.c       # SET, GET, etc.
│   │   ├── cmd_list.c         # LPUSH, RPOP, etc.
│   │   ├── cmd_zset.c         # ZADD, ZRANGE, etc.
│   │   └── commands.h
│   └── util/
│       ├── logging.c          # Logging system
│       ├── logging.h
│       └── common.h           # Common definitions
├── include/
│   └── redis_tcp.h            # Public API
├── tests/
│   ├── test_hash_table.c
│   ├── test_tcp.c
│   └── test_resp.c
├── docs/
│   ├── ARCHITECTURE.md        # Original plan
│   ├── LEARNING_PATH.md       # Detailed learning guide
│   └── API.md                 # API documentation
├── Makefile
├── README.md
├── QUICKSTART.md
└── TODO.md
```

---

## How to Reorganize

### Step 1: Extract from Documents

The uploaded documents contain complete implementations. Here's how to extract them:

#### Extract TCP Stack
```bash
# From "TCP/IP Stack + Redis Implementation.txt"
# Lines ~1-600 contain TCP implementation
# Create tcp_stack.c and tcp_stack.h
```

#### Extract Data Structures
```bash
# From "Data Structures & Protocol Handlers.txt"
# Contains:
# - Ziplist implementation
# - Quicklist implementation  
# - Skiplist implementation
# - Timing wheel
# Create data_structures.c and data_structures.h
```

#### Extract Packet Utilities
```bash
# From "Packet Construction & Utility Functions.txt"
# Contains:
# - Packet building functions
# - Checksum calculations
# - Response encoding
# Create packet_utils.c and packet_utils.h
```

---

### Step 2: Create Header Files

Example: `tcp_stack.h`

```c
#ifndef TCP_STACK_H
#define TCP_STACK_H

#include <stdint.h>
#include <stddef.h>

/* TCP States */
typedef enum {
    TCP_CLOSED,
    TCP_LISTEN,
    TCP_SYN_RCVD,
    TCP_ESTABLISHED,
    // ... etc
} tcp_state_t;

/* TCP Connection Structure */
typedef struct tcp_connection {
    uint32_t local_ip;
    uint32_t remote_ip;
    uint16_t local_port;
    uint16_t remote_port;
    tcp_state_t state;
    // ... etc
} tcp_connection_t;

/* Connection Pool */
typedef struct conn_pool conn_pool_t;

/* Function Prototypes */
conn_pool_t* conn_pool_create(void);
void conn_pool_destroy(conn_pool_t *pool);

tcp_connection_t* create_connection(conn_pool_t *pool,
                                   uint32_t local_ip, uint16_t local_port,
                                   uint32_t remote_ip, uint16_t remote_port);

tcp_connection_t* find_connection(conn_pool_t *pool,
                                 uint32_t local_ip, uint16_t local_port,
                                 uint32_t remote_ip, uint16_t remote_port);

void destroy_connection(conn_pool_t *pool, tcp_connection_t *conn);

void tcp_input(conn_pool_t *pool,
              uint32_t src_ip, uint16_t src_port,
              uint32_t dst_ip, uint16_t dst_port,
              uint32_t seq, uint32_t ack, uint8_t flags,
              uint16_t window, const uint8_t *data, size_t len);

void tcp_close(conn_pool_t *pool, tcp_connection_t *conn);

void send_tcp_segment(tcp_connection_t *conn, uint8_t flags,
                     uint32_t seq, uint32_t ack,
                     const uint8_t *data, size_t len);

#endif /* TCP_STACK_H */
```

---

### Step 3: Updated Makefile for Modular Build

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -O2 -g
CFLAGS += -D_GNU_SOURCE -Iinclude
LDFLAGS = -lpthread -lm

# Source directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target binary
TARGET = $(BIN_DIR)/redis-tcp-server

# Default target
all: $(TARGET)

# Create directories
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Build target
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Install
install: $(TARGET)
	sudo install -m 755 $(TARGET) /usr/local/bin/

.PHONY: all clean install
```

---

## Integration Strategy

### Phase 1: Keep Single File (CURRENT)

**Recommendation**: Start here! The single-file approach is perfect for learning.

**Pros**:
- Easy to navigate
- No header confusion
- Quick iteration
- All code visible

**Process**:
1. Work with `redis_tcp_server.c`
2. Add missing implementations from documents
3. Test each component
4. Get everything working

**When to move on**: When file exceeds 3000 lines or you need to share code.

---

### Phase 2: Split Major Components

When single file becomes unwieldy:

1. **Split out TCP stack**:
   ```bash
   # Extract tcp_* functions to tcp_stack.c
   # Create tcp_stack.h
   # Update main.c to include tcp_stack.h
   ```

2. **Split out data structures**:
   ```bash
   # Extract hash_table, quicklist, skiplist
   # Create data_structures.c/.h
   ```

3. **Split out protocol**:
   ```bash
   # Extract RESP parser/encoder
   # Create protocol.c/.h
   ```

---

### Phase 3: Full Modular Structure

For production or collaboration:

1. Create directory structure (see Option 2 above)
2. Move each component to its own module
3. Create comprehensive header files
4. Update Makefile for modular build
5. Add unit tests for each module

---

## Code Organization Best Practices

### 1. Header File Guards
```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

// ... declarations ...

#endif /* MODULE_NAME_H */
```

### 2. Forward Declarations
```c
// Use opaque pointers in headers
typedef struct connection connection_t;

// Define structure in .c file
struct connection {
    // ... implementation details ...
};
```

### 3. Static Functions
```c
// Make internal functions static
static void internal_helper(void) {
    // Only visible in this .c file
}
```

### 4. Clear Module Boundaries
```c
/* network/raw_socket.c - Handles raw socket operations */
int socket_open(const char *interface);
void socket_close(int sock);
ssize_t socket_send(int sock, const void *data, size_t len);

/* tcp/tcp_stack.c - TCP state machine */
void tcp_input(...);
void tcp_output(...);

/* protocol/resp.c - RESP protocol */
resp_result_t resp_parse(...);
void resp_encode(...);
```

---

## Current Integration Points

### Where Code Needs to Connect

1. **main.c → tcp_stack.c**
   ```c
   // In main.c:
   #include "tcp/tcp_stack.h"
   
   tcp_input(pool, src_ip, src_port, ...);
   ```

2. **tcp_stack.c → resp_parser.c**
   ```c
   // In tcp_stack.c:
   #include "protocol/resp_parser.h"
   
   resp_parse(parser, data, len, &consumed);
   ```

3. **resp_parser.c → commands.c**
   ```c
   // In resp_parser.c:
   #include "commands/commands.h"
   
   dispatch_command(conn, db, args, argc);
   ```

4. **commands.c → data_structures.c**
   ```c
   // In commands.c:
   #include "engine/hash_table.h"
   #include "engine/quicklist.h"
   
   hash_get(db, key, len);
   quicklist_push(list, data, len);
   ```

---

## Build System Evolution

### Stage 1: Simple (Current)
```makefile
all:
	gcc -o redis-tcp-server redis_tcp_server.c
```

### Stage 2: With Dependencies
```makefile
OBJS = main.o tcp_stack.o data_structures.o

all: $(OBJS)
	gcc -o redis-tcp-server $(OBJS)
```

### Stage 3: Modular with Auto-dependencies
```makefile
# Automatically finds all .c files
SRCS = $(shell find src -name '*.c')
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	gcc -o redis-tcp-server $(OBJS)

# Auto-generate dependencies
-include $(OBJS:.o=.d)
```

---

## Testing Structure

### Unit Tests Organization
```
tests/
├── unit/
│   ├── test_hash_table.c
│   ├── test_tcp_state.c
│   ├── test_resp_parser.c
│   └── test_quicklist.c
├── integration/
│   ├── test_connection.c
│   └── test_commands.c
└── Makefile
```

### Test Makefile
```makefile
# tests/Makefile
CC = gcc
CFLAGS = -I../include -g

TESTS = test_hash_table test_tcp_state

all: $(TESTS)

test_hash_table: test_hash_table.c ../src/engine/hash_table.c
	$(CC) $(CFLAGS) -o $@ $^

test_tcp_state: test_tcp_state.c ../src/tcp/tcp_stack.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTS)

.PHONY: all clean
```

---

## Documentation Structure

```
docs/
├── ARCHITECTURE.md      # High-level design
├── API.md               # Function documentation
├── PROTOCOL.md          # Wire protocol details
├── PERFORMANCE.md       # Tuning guide
└── diagrams/
    ├── tcp_state.png
    ├── packet_flow.png
    └── data_structures.png
```

---

## Development Workflow

### Daily Routine

1. **Morning** (30 min):
   - Review TODO.md
   - Read one component's code
   - Plan day's work

2. **Implementation** (2-3 hours):
   - Make small, incremental changes
   - Test after each change
   - Commit frequently

3. **Testing** (30 min):
   - Run unit tests
   - Packet captures
   - Integration tests

4. **Documentation** (15 min):
   - Update comments
   - Note lessons learned
   - Update TODO.md

---

## Version Control Best Practices

### Commit Messages
```
[component] Brief description

Detailed explanation of what changed and why.

- Specific change 1
- Specific change 2

Testing: Description of tests performed
```

### Example:
```
[tcp] Implement retransmission timer

Added support for TCP retransmission with exponential backoff.
Timer fires when ACK is not received within RTO period.

- Added timer expiration check in process_timers()
- Implemented exponential backoff (double RTO on timeout)
- Max 5 retries before closing connection

Testing: Verified with packet loss simulation using tc netem
```

---

## Recommended Next Steps

1. **Start with Single File**: Use `redis_tcp_server.c` as-is
2. **Add Missing Implementations**: Follow TODO.md
3. **Test Each Component**: Use QUICKSTART.md tests
4. **Refactor When Ready**: Split into modules after everything works
5. **Add Tests**: Create unit tests for each module
6. **Document**: Write detailed API docs

---

## Quick Reference

### File Sizes (Approximate)
```
redis_tcp_server.c    ~1500 lines (current, incomplete)
tcp_stack.c           ~800 lines (from documents)
data_structures.c     ~1200 lines (from documents)
packet_utils.c        ~600 lines (from documents)
commands.c            ~400 lines (from documents)
```

### Total Project Size (Complete)
- Source code: ~5000-6000 lines
- Header files: ~1000 lines
- Tests: ~2000 lines
- Documentation: ~3000 lines

---

**Recommendation**: Keep the single-file structure until you complete the TODO.md tasks. Then reorganize into modules for easier maintenance.

**Current Priority**: Focus on integration (TODO.md) not organization!