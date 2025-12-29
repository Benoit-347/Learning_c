/*
 * main.c - High-performance Packet Capture & Filter Engine
    Not able to see- Surrounding devices trrafic, need:
        Special drivers
        Tools like airodump-ng
        Different link-layer parsing
 * terminal- Need to run cmd:
 *              sudo apt install gcc tcpdump libpcap-dev wireshark
 * Build:   gcc -O2 -Wall -Wextra -o pktcap main.c -lpcap
 *          # '-02' optimization level while compiling; 'Wall' to enable most common error warnings; 'Wextra' enable remaining warning not covered by 'Wall' '-l' is a linker flag 'pcap' name of library to link.
 * Capture packets- 
 *      help:-  ip link-
                lists names of connected lanes in PCIe, ./pktcap -i name.
                    en- Ehternet; p2- PCI bus 2; s0- Slot 0.
                    enp0s2
                    wl- Wireless Lan; p0 PCI bus 0; s2- Slot 20; f3 function number 3.
                    wlp0s20f3
                    lo- is loopback (TCP/IP lives)
                        localhost services come here, very useful to track intra machine server comms (via kernel)
                        Especially browsers. (local cache, DNS prefetchers; even when idle)
 *      1. sudo tcpdump -i lo -w test_packets.pcap -c 20        (capture from lo, write to test_packets.pcap, upto 20 lines)
 *              curl http://127.0.0.1
 *      2. sudo ./pktcap -i wlp0s20f3
 *              curl https://www.google.com/


 * Usage:   ./pktcap -i <interface> [-f "filter"] [-r <file>]   (iterfaces: 'lo', 'wlp0s20f3', 'enp2s0'- but idle tho)
 * Example: ./pktcap -i wlp0s20f3 -f "proto tcp and port dst 80"
 *
 * Logic:   Captures via libpcap, parses custom filter AST, evaluates packet headers.
 * Safety:  Standard endianness handling, bounds checking, minimal allocations.

 * Test: ./pktcap -r test_packets.pcap  (test_packets is a test file)
 * Test_2: ./pktcap -r test_packets.pcap -f "proto tcp and port dst 80"     (-f is flag to filter; give tcp packets, dst port as 80)
 * Live_Test: sudo ./pktcap -i wlp0s20f3 -f "proto tcp [and port dst 80]"   ('[]' mean optional)
                After ~10-20 sec- ctrl + c
 * Pass case:   Every printed line says tcp
                The destination port is 80
 * Test_3: ./pktcap -r test_packets.pcap -f "proto icmp and port dst 80"
 * Pass case: No output

 * Optional: Comparing ouput with a trusted tool
    sudo apt update
    sudo apt install tshark

    tshark -r test_packets.pcap -Y "tcp.dstport == 80" | wc -l
    ./pktcap -r test_packets.pcap -f "proto tcp and port dst 80" | wc -l
    
    Pass case: Ouputs Match (output is an integer (~ 3 digits))

 */

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <time.h>

// --- Data Structures ---

typedef struct {
    uint32_t s_ip, d_ip;    // Source Ip address; Destination Ip address
    uint16_t s_port, d_port;    // Source port; Destination port
    uint8_t  proto;     // Protocol
} PktMeta;  

typedef enum { 
    OP_AND, OP_OR, OP_NOT, 
    T_SIP, T_DIP, T_SPORT, T_DPORT, T_PROTO, T_TRUE 
} NodeType;
// Enums are used for using as contant ints, for purpose of matching. (Like in a calc program if 0 is add, 1 is sub;
    // we can define enum and ADD, SUB is defined as enum, we can use ADD without user declaring any value to it;
    // The compiler handles it in backend. Hence the use can simply try if (user_input == ADD) continue; )
        // At backend these enums body, var names are all ints. Where compiler assigns them each a value; with compiler ensuring- every enum var value being unique.

typedef struct Node {
    NodeType type;      // an enum value.
    uint32_t v32; // IPs (Network Byte Order)
    uint16_t v16; // Ports (Network Byte Order)
    uint8_t  v8;  // Proto
    struct Node *l, *r;     // this statement is why we declared Node in struct's namespace as well.
} Node;

// --- Globals for Parsing ---
char **tokens;  // will be an array of pointers to char. (Holds Multiple strings in arr; each element is a string)
int tok_pos = 0, tok_count = 0; //tok_pos- index to tokens arr. tok_count- max no. of strings/ elements in arr.

// --- Helpers ---
void die(const char *msg) { perror(msg); exit(1); }
    // Used as a quick form of exiting a program & writing a error message.




Node* new_node(NodeType t, Node *l, Node *r) {
    // create a Node obj, assign its Type member, its 2 (self ref) pointers (pointers to left and right (another Node obj) )
    Node *n = calloc(1, sizeof(Node));
    if(!n) die("malloc");
    n->type = t; n->l = l; n->r = r;
    return n;
}

// --- Recursive Descent Parser ---
// Grammar: Expr -> Term { 'or' Term }, Term -> Factor { 'and' Factor }
// Factor -> 'not' Factor | '(' Expr ')' | Condition

Node* parse_expr(); // Forward decl

const char* peek() { return (tok_pos < tok_count) ? tokens[tok_pos] : ""; } // obtain current string ptr in tokens.
const char* next() { return (tok_pos < tok_count) ? tokens[tok_pos++] : ""; }   // obain current string ptr in tokens, and incr index by 1. (point to next string)
int match(const char *s) { if (strcmp(peek(), s) == 0) { next(); return 1; } return 0; }    // simply a alias for strcmp. Difference being only 2nd string is passed to 1 parameter. 2nd parameter is taken from current string in tokens arr- hence peek(). AlSO feature- It incr tokens index if matched.

Node* parse_condition() {
    const char *k = next();
    Node *n = new_node(T_TRUE, 0, 0);
    if (strcmp(k, "proto") == 0) {  // token matched to "proto"; if both strings are equal
        n->type = T_PROTO;
        const char *v = next();             // then chk for subsequent strings as well. If it matched to "tcp".
        if (!strcmp(v,"tcp")) n->v8 = IPPROTO_TCP;
        else if (!strcmp(v,"udp")) n->v8 = IPPROTO_UDP;
        else if (!strcmp(v,"icmp")) n->v8 = IPPROTO_ICMP;
        else die("Unknown proto");
    } else if (strcmp(k, "ip") == 0) {  // else first token matched "ip"
        int is_src = match("src"); match("dst"); // will contain for sure, either src or dst. // why use match() when it is pointing to "ip" right now? the next() was called before the conditions here when assigning k. So index is at new string other than k already.
        n->type = is_src ? T_SIP : T_DIP;   // from our is_src flag value, we know if it is src or dst.
        inet_pton(AF_INET, next(), &n->v32); // Stores in NBO
    } else if (strcmp(k, "port") == 0) {    // token matched to "port".
        int is_src = match("src"); match("dst");    // find if src or dst && consume.
        n->type = is_src ? T_SPORT : T_DPORT;           // assign type
        n->v16 = htons(atoi(next())); // Store in NBO
    } else {
        die("Syntax error in condition");
    }
    return n;
}

Node* parse_factor() {
    if (match("not")) return new_node(OP_NOT, parse_factor(), NULL);    // if matched (true is 1 for matched, unlike strcmp which returns 0 for equal strings)
    if (match("(")) {
        Node *n = parse_expr();
        if (!match(")")) die("Missing ')'");
        return n;
    }
    return parse_condition();
}

Node* parse_term() {
    Node *l = parse_factor();
    while (match("and")) l = new_node(OP_AND, l, parse_factor());
    return l;
}

Node* parse_expr() {
    Node *l = parse_term();
    while (match("or")) l = new_node(OP_OR, l, parse_term());
    return l;
}

void tokenize(char *str) {
    char *p = strtok(str, " ");
    while (p) {
        tokens = realloc(tokens, sizeof(char*) * (tok_count + 1));
        tokens[tok_count++] = p;
        p = strtok(NULL, " ");
    }
}

// --- Filter Evaluation ---
int eval(Node *n, PktMeta *p) {
    if (!n) return 1;
    switch (n->type) {
        case OP_AND:  return eval(n->l, p) && eval(n->r, p);
        case OP_OR:   return eval(n->l, p) || eval(n->r, p);
        case OP_NOT:  return !eval(n->l, p);
        case T_SIP:   return p->s_ip == n->v32;
        case T_DIP:   return p->d_ip == n->v32;
        case T_SPORT: return p->s_port == n->v16;
        case T_DPORT: return p->d_port == n->v16;
        case T_PROTO: return p->proto == n->v8;
        default: return 1;
    }
}

// --- Packet Processing ---
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    Node *filter_root = (Node*)args;
    struct ether_header *eth = (struct ether_header *)packet;

    if (ntohs(eth->ether_type) != ETHERTYPE_IP) return; // IPv4 only

    struct ip *iph = (struct ip *)(packet + sizeof(struct ether_header));
    // Basic bounds check
    if (header->caplen < sizeof(struct ether_header) + sizeof(struct ip)) return;
    
    int ip_hl = iph->ip_hl * 4;
    PktMeta meta = { .s_ip = iph->ip_src.s_addr, .d_ip = iph->ip_dst.s_addr, .proto = iph->ip_p, .s_port=0, .d_port=0 };

    if (iph->ip_p == IPPROTO_TCP) {
        struct tcphdr *tcp = (struct tcphdr *)((u_char*)iph + ip_hl);
        meta.s_port = tcp->source; meta.d_port = tcp->dest;
    } else if (iph->ip_p == IPPROTO_UDP) {
        struct udphdr *udp = (struct udphdr *)((u_char*)iph + ip_hl);
        meta.s_port = udp->source; meta.d_port = udp->dest;
    }

    if (eval(filter_root, &meta)) {
        char ts[64], s_str[INET_ADDRSTRLEN], d_str[INET_ADDRSTRLEN];
        struct tm *ltime = localtime(&header->ts.tv_sec);
        strftime(ts, sizeof(ts), "%Y-%m-%dT%H:%M:%S", ltime);
        
        inet_ntop(AF_INET, &meta.s_ip, s_str, sizeof(s_str));
        inet_ntop(AF_INET, &meta.d_ip, d_str, sizeof(d_str));
        const char *pname = (meta.proto == IPPROTO_TCP) ? "tcp" : (meta.proto == IPPROTO_UDP) ? "udp" : "icmp";
        
        printf("%s.%06ld %s:%d -> %s:%d %s len=%d\n", 
            ts, header->ts.tv_usec, 
            s_str, ntohs(meta.s_port), d_str, ntohs(meta.d_port), 
            pname, header->len);
    }
}

// --- Main ---
int main(int argc, char *argv[]) {
    char *dev = NULL, *pcap_file = NULL, *filter_str = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    int cnt = -1;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-i") && i+1 < argc) dev = argv[++i];
        else if (!strcmp(argv[i], "-r") && i+1 < argc) pcap_file = argv[++i];
        else if (!strcmp(argv[i], "-f") && i+1 < argc) filter_str = argv[++i];
        else if (!strcmp(argv[i], "-n") && i+1 < argc) cnt = atoi(argv[++i]);
    }

    if ((!dev && !pcap_file) || (dev && pcap_file)) {
        fprintf(stderr, "Usage: %s -i <iface> | -r <file> [-f \"filter\"] [-n <cnt>]\n", argv[0]);
        return 1;
    }

    Node *root = NULL;
    if (filter_str) {
        char *fs_copy = strdup(filter_str); // Modify copy for strtok
        tokenize(fs_copy);
        root = parse_expr();
        free(fs_copy);
    }

    pcap_t *handle;
    if (pcap_file) {
        handle = pcap_open_offline(pcap_file, errbuf);
    } else {
        handle = pcap_open_live(dev, 65535, 1, 1000, errbuf);
    }
    
    if (!handle) die(errbuf);

    if (pcap_datalink(handle) != DLT_EN10MB) {
        fprintf(stderr, "Error: Only Ethernet headers supported.\n");
        return 2;
    }

    printf("Capturing on %s...\n", dev ? dev : pcap_file);
    pcap_loop(handle, cnt, got_packet, (u_char*)root);

    pcap_close(handle);
    free(tokens); // Minimal cleanup
    return 0;
}