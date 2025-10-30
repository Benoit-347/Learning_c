// if we want to have words in a semi sorted manner, we don't have all the words and obtain new words to add to our arr. 
    // we can contantly insert word into our arr by a binary search to find pos right before a greater number (or right after lesser),  but this would have a con of excess sifitng for each input.

// a binary tree is a data strucure that similar to a chained arr i.e the structure within it has the value member and also a position (which is a unique thing to think about)
                                                                    // this position is like the same data type as very stuct it is contained within, the member points to anohter such struct, which also has a member having a pos, tht may as well point to another sturct and so on.

// In a binary tree we maintain 2 pointers in each struct obj (now we call it node)
    // i) greater than ptr (right ptr)
    // ii) lesser than ptr (left ptr)
        // by using these two ptrs and initializing each struct obj's member ptrs as 0, we can arrange any value in a range completely sorted.
        // consider 0, then 0.1, then 0.01, then 0.001: this would create a conection zig zag down with 1 vertical (with successive structs alternating between null left ptr and null right ptr, as the other (respectively right, left) point to the inner structs (more like on the same plane as its a 2D always, but chained) )
    
// a binary tree has 3 members on each node:
    // 1) the actual value              //               our next code:- the text (ptr to char)
    // 2) a ptr to left child node      // +1 member for our next code:- the count of number of words => 4 members then
    // 3) a ptr to right child node

// NOTE: in a binary tree, each node can only have max 2 pointers (pointing to next obj thats like itself).
    // in imagination, virtually, the tree when downward, wont really reach a overhead end; instead it simply follows a sequence, and such sequences (continuous left && continous right) may be in its branch, or in its childs sequence.
        // only drawback is if the tree is not spread out (unbalanced is official word) then only when accessing/ searching an element, it acts as a linear search at worst case scenario (i.e. worst case scenario = input is not random and passed as linear order)
struct node {
    int value;
    struct node * left_child;
    struct node * right_child;  // in mem, we will hold jumping ptrs of each struct, depending on the order of obtaining input; older the holding struct, lesser its ptr would be cmp to its left/right_child struct (by age of input the sturct is also created hence its ptr loc in mem).
};