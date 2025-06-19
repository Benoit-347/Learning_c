char ** argv; // pointer pointing to a char.
char (*daytab)[10]; // a pointer to an array of 10 elements of char
char *daytab[10];    // an array of 10 elements of pointers of char
void *comp();    //a fn returning a pointer of void type.
void (*comp)();  // a pointer, that points to a fn that returns void
char (*(*x())[])(); // a function returning a pointer to an array, that points to a funtion, that returns a char.
char (*(*x[3])())[5]; // the array[3] of pointer to function returning pointer to array[5] of char.