// printf is used to send chars at stdout, with inserting chars during printing.
    // the printf arguments first is the foramt string (called named variable), and a variable length of arguments beyond the format string (the additional  arguments are called un-named arguments).
                            // the count of these unnamed arguments are not known by the compiler. (as the compiler only knows the fn printf() in code not the parameters within it, due to the principal of C language that more power is given to the programmer rather than the compiler keeping track).
                            // when calling printf, the additional (un-named data items) are pushed onto the stack (available registers first- around 6).
                            //  The `va_list` struct (implementation-dependent) stores info to walk these arguments:    
                            // then a struct called va_list is loaded with 2 members storing offset info, 1 member storing stack pointer eactly to the arguments it would recive from stack and 1 member storing register area
                                    // futher when printing the string in fmt, upon encountering a '%' (the respective format is matched) the first argument item is retrived by va_start(ap, int) => sets pointer ap to mem loc of first argument
                                                                                                                                                                // and every subsequest fn va_arg(ap, int) side effects va_list struct to walk on va_list, pointing to next argement (va_arg and also va_start gets data from arg then puts pointer to location after the current member i.e. next arg)

// THE BELOW VA_LIST AND ITS FUNCTIONS WILL NOT WORK WHEN COMPILED HERE AND RUN AS THEY ARE ONLY PEROPERLY DEFINED IN THE STDARG HEADER. NEED TO DO INLINE ASM TO HANDLE ALL VA RELATED FNS
# include <stdio.h>
// # include <stdarg.h>

int printf(const char *fmt, ...);   // here fmt is a string pointer (char *)
float num = 10.5;
printf("%-4.2f", num);
                                    // btw u can also do s = "hello world", printf(s); as long as the string of s does not contain %(d, s, x..)
/* New va_list
                                    typedef struct {
    unsigned int gp_offset;   // offset for general-purpose registers
    unsigned int fp_offset;   // offset for floating-point registers
    void *overflow_arg_area;  // pointer to stack arguments
    void *reg_save_area;      // saved registers area

} __va_list[1];
 */

 // old va_list
 typedef char * va_list_2;



    // the printf() fn is forwarded to the min_print() fn: 
    // THe following function work on va_list to perform retrival:
    // va_start: set ptr ap to the loc of first argument.
    #define va_start(ap, last_named_param) (ap = (char *)&last_named_param + sizeof(last_named_param))

    // va_arg: Retrives the an arg, and returns it. Then Move ap forward by sizeof(type).
    #define va_arg(ap, type)  (*(type *)((ap += sizeof(type)) - sizeof(type)))

    // va_end: set ap to NULL to prevent dangling pointer.
    #define va_end(ap) (ap = (va_list_2)0)

    // these macros are only for old x86 computers, on modern x86_64, these macros perform much more complex logic.



 void minprintf(char *fmt, ...) {     // minprintf: minimal printf with variable argument list
    
    va_list_2 ap; /* points to each unnamed arg in turn */

    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                    break;
            default:
                    putchar(*p);
                    break;
        }
    }

    va_end(ap); /* clean up when done */
}


int main(){
    minprintf("%d %f %c %s\n", 10, 3.14, 'A', "Hello");
    // The compiler pushes arguments onto the stack in right-to-left order:


}