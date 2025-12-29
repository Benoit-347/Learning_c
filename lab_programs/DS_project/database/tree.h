# define _GNU_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# include <assert.h>
# include <errno.h>

# define TagRoot 1  /* 00 01*/
# define TagNode 2  /* 00 10*/
# define TagLeaf 4  /* 01 00*/

typedef unsigned char Tag;
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_node {
    Tag tag;
    struct s_node *north;
    struct s_node *west;
    struct s_leaf *east;
    int8 path[256];  // 0 to 255 = 256 length
};
typedef struct s_node Node;

struct s_leaf {
    Tag tag;
    union u_tree *west;
    struct s_leaf *east;
    int8 key[128];
    int8 *value;    // this can be a ptr to a large json struct.
};
typedef struct s_leaf Leaf;

union u_tree {
    Node n;
    Leaf l;
};
typedef union u_tree Tree;