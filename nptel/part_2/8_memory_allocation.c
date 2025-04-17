/* initializing space statically using 
        array[n] vs malloc:

i) the memory is allocated to heap in malloc whereas in arr it is allocated at stack (heap has larger size upto RAM, stack in linux is 1-8 MB)
ii) the allocation in malloc can be cleared up to free space whereas in arr, it is defined until scope
iii) size can be redifined in malloc, whereas it can not be, in arr.
*/


# include <stdio.h>

int main(){
    malloc (100);   // bytes, 1 each
    int *pointer = (int *)  malloc (100);      // malloc returns a  pointer to the first element of allocated space

    // two arguments: the number of elements and the size of each element:
    calloc(100, 1); // used to initialize with the allocated values all being 0.

    free(pointer);  // it clears up the space taken by the malloc at this contigious block

    // how does the free fn know until where to free?
    // Each malloc has a header block right next to it, that stores the meat data about the blocks size (16 bytes)
    // does not read byte-by-byte until a marker (like \0 in strings). Instead, 
    // it uses a convention-based offset from the passed pointer to locate the header.

    realloc(pointer, 50);
}