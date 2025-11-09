// consider an error that takes place in the cat program, if the output file accnot be accessed. Then the diagnostic message may appear on screen which will not be a problem. 
    // but if the program is pipelined, the stdout will write the diagnostic into the other file..
// to handle this problem, a second output stream called stderr is assigned to a program (in the same way stdin and stdout are).
    // and the ouput written on stderr even if output is redirected, normally appears on the screen. (hence tackles the pipeline problem).

# include <stdio.h>

void filecopy(FILE *ifp, FILE *ofp){
    int c;
    
    while ( (c = getc(ifp)) != EOF)
        putc(c, ofp);   // every putc and getc, is kept track by a buffer, by a kernel cursor per open file as actual cursor position, and a user-space cursor at buffer for speed.     
}

int main(int argc, char * argv[]){
    FILE *fp;
    char * prog = argv[0];

    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ( (fp = fopen(*++argv, "r")) == NULL){
                fprintf(stderr, "%s can't open %s\n", prog, *argv);
                exit(1);
            }
            else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    
    // in write operation from either stdin to stdout or one among while's body has a error in stdout:
    if (ferror(stdout)){
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }

    // every FILE * stream in C has internal flags, within its FILE struct. ferror checks the error flag. (0 if no errors, non 0 => a error was encountered).
                                                                                                            // possible errors:
                                                                                                                // 1. The terminal or pipe is closed (e.g., broken pipe).
                                                                                                                // 2. The disk is full when redirecting output to a file.
                                                                                                                // 3. The network socket connected to stdout was dropped.
                                                                                                                // 4. fflush(stdout) failed to write pending buffered data.
    exit(0);
}

// exit() fn is exactly same as return; only advantage of exit() being that is can also be called from any fn, unlike return that is only able to exit whole program when return is called at main.
// also since we are using exit() fn in this program, the argument passed to this fn is available to a program (if; our case not) has called this program; i.e. used this program as a sub process to the other program.
// ferror() itself also returns non zero, if the error flags it checked withing the FILE struct are non zero.

// small programs do not require much exit status, but serious programs need to return sensible, useful status information.