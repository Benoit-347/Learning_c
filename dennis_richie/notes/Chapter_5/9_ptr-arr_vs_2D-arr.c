//Pointer arrays:
    //Its elements can have real different lenghts in memory    -> Memory advantage
    //Can have different elements stored at different parts of memory   -> niche case memory advantage

//2D arr:
    //Memory on defualt is stored consequtively -> faster performance dur to chache efficiency
    //Constant coulumn width of the elements of an array.

#include <stdio.h>

//consider taking input from user from stdio
char arr[10][1000]; //takes up 10*1000 bytes of memory (excluding overhead)

char *arr[10] = {"Length8", "Length 9", "length  10"};

