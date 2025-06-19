/* Ways to pass input: i) Aready in program by assigning
                        ii) By terminal at runtime using stdio
                        iii) By passing input strings while running file
                        */
//we can pass two arguments to main; by convention, first one is called- argc; second one is called- argv.
    // arcv: an array of pointers, pointers to strings.
    // consider than we pass arguments at terminal when running files; eg- file_1 hello world
        // passes 3 strings: "file_1", "hello", "world".
    // at this instance the subcategory of arguments passed during file_running is passed to argv as its pointers into an array. (pointers i.e begginig of that soecific string)
    // the no. of strings/sub arguments passed to argv is counted from 1 by argc.

#include <stdio.h>

int main(int argc, char *argv[]){   //since arr contains strings meaning, arr of pointers, pointing to strings.
    for (int i = 0; i<argc; i++)
        printf("Element %d of argv is: %s\n",i , argv[i]);


    //also
    //printing words with space b/w and ignoring file_name
    printf("\nsection 1:\n");   int temp = argc;
    while (argc-- >0){
        printf("%s%c", *argv++, argc>=0? ' ' : 0);
    }

    //printing words with space b/w and ignoring file_name
    printf("\nsection 2:\n");   argc = temp;    argv = argv - argc;
    while (--argc >0){
        printf("%s%c", *++argv, argc>0? ' ' : 0);
    }

    printf("\n");
    return 0;
}