// other use cases of pointer to functions:
// Implementing Polymorphism
    // Use: Function pointers enable runtime polymorphism, similar to virtual functions in OOP

# include <stdio.h>

void print_add(int);
void print_mult(int);

typedef struct {
    void (*operation)(int);
} Object;

int main() {
    Object obj;
    obj.operation = print_add; // Assign add function
    obj.operation(5); // Prints 15
    obj.operation = print_mult; // Switch to multiply
    obj.operation(5); // Prints 10
    return 0;
}

void print_add(int n){
    printf("Addtion of %d with itself: %d\n", n, n+n);
}

void print_mult(int n){
    printf("Multiplication of %d with itself: %d\n", n, n*n);
}
