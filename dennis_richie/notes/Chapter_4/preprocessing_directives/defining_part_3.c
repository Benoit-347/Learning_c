/* Conditional Inlusion and Definitions
    //Possible to control preprocessing directives with conditional statements evaluated at the preprocessing stage itself.

    context: We have conditionals at main using if else, but they are not available outside main due to how C program executes in nature.
        */

//Conditional define- Allow to include code selectively
    //#if evaluates a constant integer expression (during preprocessing stage)
        // the whole code under #if is considered if block, until it is terminated by #endif or #elif or #else

// Use case 1:

#if !defined(HDR)
    #define HDR 5
#endif
// alternatively- Use #ifdef <cond> for #if defined(<cond>) and #ifndef <cond> for #if !defined(<cond>)

#ifndef HDR2
#define HDR2 5
#endif


/*
Enumerations are unique types with values ranging over a set of named constants called enumerators. The
form of an enumeration specifier borrows from that of structures and unions.
enum−specifier:
enum identifieropt { enumerator−list }
enum identifier
enumerator−list:
enumerator
enumerator−list , enumerator
enumerator:
identifier
identifier = constant−expression
*/