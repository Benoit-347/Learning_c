# include <stdio.h>

//filecopy- to copy file 'ifp' to 'ofp'
void filecopy(FILE *ifp, FILE *ofp){
    int c;
    
    while ( (c = getc(ifp)) != EOF)
        putc(c, ofp);   // every putc and getc, is kept track by a buffer, by a kernel cursor per open file as actual cursor position, and a user-space cursor at buffer for speed.     
}

int main(int argc, char *argv[]){
    FILE *fp;
    void filecopy(FILE *, FILE *);

    // if no arguments were passed (apart from the exe), during terminal application run command.
    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL){ // argv holds whole args as elements, i.e. arr of pointers.
                printf("cat: can't open %s\n", *argv);
                return 1;
            }
            else {
                filecopy(fp, stdout);   // our defined fn => putc all chars in fp to stdout.    while stdin and stdout are both FILE * type, note that these are constants.
                fclose(fp);
            }
    
    return 0;
}