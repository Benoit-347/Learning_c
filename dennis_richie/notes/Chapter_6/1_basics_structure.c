// structures are collection of data elements of (not compulsory) multilple data types.
    // they are all grouped under a single name (stuct obj name)
        // unlike an arr where we obtain elements by offsetting index, we can only obtain elements of a structure by the names of the members (its elements). (These names are defined while creating the class)

// pros:
    // we can use names instead of indexes to obtain elements
    // in large programs, a group of related variables can be treated as a single unit
    
// new structures related features added to C (at ANSI standard) (exists since many years but now formally defined):
    // structures can be copied, assigned to, or passed to functions and returned by functions.


// CREATING A STRUCT
/*
struct <name> {
    <data_type> <member_1>;
    <data_type> <member_2>;
};
*/

    // struct keyword: introduces a structure declaration
    // name (<optional> called as tag) represents this kind of structure (used for creating real data objects of this structure type  && pointers as well)
    // '{' and '}' to denoted the list of members within a structure. while members denoted by each ones data type and its recognized name.
    // end of declaration is not right after '}' as compiler gives space for immediate creation of struct objects.
        // ends declaration with ';'

        // The struct declaration is also analogous to a data type such that we can do:
            // eg-          struct name {...}   x, y, z;
            // similar to   int                 x, y, z;

// a struct now followed by a list of variables does not reserve storage, but only describes the template of its data object.


// obtaining members- by using the '.' operator. 
    // Syntax:  struct_obj.member_name     -it connects the respective struct with its member name.


// Nested possible?
    // In C, yes, structures can be nested.



// consider a structure that contains x and y integers (later multiple such points in nestes struct)

# include <stdio.h>

struct point{ int x; int y; };

struct multiple_points{ struct point point_1; struct point point_2; };

int main(){
    
    // input
    struct point pt = {1, 2};
    printf("For struct point, obj 'pt' has \tmember 'x': %d \tmember 'y': %d\n\n", pt.x, pt.y);

    struct multiple_points points = { {1, 2}, {3, 4} };
    printf("For struct multiple_points, obj 'points' has members 'point_1' and 'point_2'\nmember 'point_1': \tnested member x: %d \tmember y: %d \nmember 'point_2': \tnested member x: %d \tmember y: %d\n", points.point_1.x, points.point_1.y, points.point_2.x, points.point_2.y);
    return 0;
}