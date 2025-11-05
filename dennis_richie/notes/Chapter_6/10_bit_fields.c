// bit-fields:
    // They denote bits inside a storage space (called word), and do not have addresses like variables. 
        // The compiler allocates a single word (usually an unsigned int) to store all these bits


// Methods to use bit fiels-

    // 1. The Official Way — Using struct Bit Fields

        #include <stdio.h>

        struct status {
            unsigned int power : 1;   // uses 1 bit
            unsigned int error : 1;   // uses 1 bit
            unsigned int mode  : 2;   // uses 2 bits
            unsigned int code  : 4;   // uses 4 bits
        };                          // total = 1 + 1 + 2 + 4 = 8 bits (not 8 bytes mind you)

    // 2. The Manual Way — Using Bitwise Operators

        // This is the assembly-style, “do-it-yourself” way of creating bitfields without structs.
        // Here you operate directly on the bits of an integer variable.

        // Declaring a Bit Container
        unsigned int reg = 0;  // a 32-bit word

        //🔹 Defining Masks
            // You use macros to define the positions and lengths of fields:

        #define FIELD_A_MASK  0x00000007  // bits 0–2
        #define FIELD_B_MASK  0x000000F8  // bits 3–7
        #define FIELD_A_SHIFT 0
        #define FIELD_B_SHIFT 3     
                                // note (alternative to # define is) enum(FIELD_A_MASK = 0x00000007, FIELD_B_MASK = 0x000000F8, FIELD_A_SHIFT = 0, FIELD_B_SHIFT 3 );
    int main(){

        int value = 10;
        //🔹 Setting a Bit Field
        reg &= ~FIELD_B_MASK;                // clear bits 3–7      // the operators mean:- reg = reg & (R.H.S expr)
        reg |= (value << FIELD_B_SHIFT) & FIELD_B_MASK;  // set value   // the operators mean:- reg = reg | (R.H.S expr

        //🔹 Reading a Bit Field
        unsigned int b_value = (reg & FIELD_B_MASK) >> FIELD_B_SHIFT;
        unsigned int b_value = (reg & FIELD_B_MASK) >> FIELD_B_SHIFT;
        // This gives you full control over the bit layout and is exactly how embedded register programming or protocol bit parsing is done in real-world low-level systems.

    // 3. Hybrid Way — Using Unions
        // Want best of both worlds? Use a union to overlay a bit-field structure on top of an integer.

        union Register {    // IMP: this works only because of union
            unsigned int all;
            struct {
                unsigned int flag  : 1;
                unsigned int mode  : 3;
                unsigned int level : 4;
            } bits;
        };


        union Register r;
            r.all = 0;
            r.bits.flag = 1;
            r.bits.mode = 5;
            printf("Raw word: 0x%X\n", r.all);
        }

        // This way you can:
            // Access the whole register as one number (r.all)
            // Or access individual bits logically (r.bits.mode)

/*
    Typical Use of Bit Fields:
        1. Hardware register mapping (microcontrollers)
        2. Network or protocol headers (like TCP/IP)
        3. Compact storage of flags or configuration options
*/