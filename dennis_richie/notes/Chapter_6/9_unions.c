// unions make possible for a single variable to hold objects of different sizes and data types -> managed by the compiler (while also keeping track of alignment).
    // use: for using multiple data types at a single storage space. (and mainly, avoiding machine dependent coding)

// usage eg:

# include <stdio.h>

union u_tag{
    int ival;
    float fval;
    char * sval;
    char cval;
};

int main(){
    union u_tag tag_1;
    // creates a 8 byte region (ptr thts why)

    tag_1.ival = 10;
    // writes to first 4 bytes (the value 10 in the int format. thts it, 'ival' just denotes how to store the value of assignment.
    
    // a simple, legal way to write:
    int a = 0112;
    char b = a;
    printf("b, \tint: %d char: %c\n", a, b);
    // or:
    union u_tag tag_2;
    tag_2.ival = 0112;
    printf("tag_2, \tint: %d char: %c\n", tag_2.ival, tag_2.cval);

    // the offset is always 0 for a union, but note tht union (its not a ptr) obj is not a arr format like a struct (hence struct can use offsets, as structs base is a ptr)
    // initialization of a union is not universal of its members, only pass value of its first member type.
}

//performance difference bw a struct and a union (except memory)
    // 1. less cache misses for union as need lesser footprint. (cache-light: as all fields occupy the same space). 
    // 2. no offset calc req for members    (One addition saved, thts it)