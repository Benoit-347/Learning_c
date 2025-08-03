// other use of pointer to fns:
    // Dynamic Dispatch in State Machines
    // (Or even, an array of fns):

# include <stdio.h>
void red() { printf("Red Light\n"); }
void green() { printf("Green Light\n"); }

//typedef void (*State)();
void (*states[])() = {red, green};

int main() {
    int state = 0;
    states[state](); // Calls red()
    state = 1;
    states[state](); // Calls green()
    return 0;
}