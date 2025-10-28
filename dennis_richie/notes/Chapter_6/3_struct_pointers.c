// pointers to structs are very similar syn to var
    // syn: struct <struct_name> *

// for large structures, it is more efficient to pass pointers of a struct_obj, instead of copying all the members of the structure.
    // normal struct reference from fn: cpy struct obj (all elements included) to itself, then obtain elements;
    // pointer struct: get obtain pointer to the struct obj and obtain elements directly by the pointer dereferencing.

# include <stdio.h>

struct struct_ints {
    int a;
    int b;
};

struct struct_nested{
    struct struct_ints point_1;
    struct struct_ints point_2;
};

int main(){

    // creating struct obj
    struct struct_ints obj_1;
    obj_1.a = 10;
    obj_1.b = 20;
    struct struct_nested obj_2;
    obj_2.point_1.a = 10;
    obj_2.point_1.a = 20;   // all this is at runtime a offset memory assignment

    // creating pointer to the struct obj
    struct struct_ints * struct_ptr;
    struct_ptr = &obj_1;

    struct struct_nested * struct_ptr_ptr;
    struct_ptr_ptr = &obj_2;

    // using a struct pointer
    pritnf("The member inside pointer pointing to struct is: %d\n", (*struct_ptr).a);
    
    //note: the precedence of:  .    ()  []  is among the top of precedence hierarchy
        // hence when obtaining the member of a struct pointer, we need to put parenthesis on the pointer dereference, then do '.' operation to obatian member.
    
    //ways to obtain member:
    obj_1.a;
    (*struct_ptr).a;
    struct_ptr -> a;
// the '->' operator is used do multiple steps, 1. to dereference the struct pointer. 2. To obtain the member from the derefernced.

    // ways to obtain a nested member
    int c = (*struct_ptr_ptr).point_1.a;
        c = struct_ptr_ptr -> point_1.a;
        struct struct_ints * struct_ptr_2 = & (struct_ptr_ptr -> point_1);   // pointer to the struct withing nested struct

}