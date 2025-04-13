#include <stdio.h>

//We have 2D arrays (stores data with uniform type; a[3] = { [1,2,3], [10,11,12] }. ) This contains data with each element address that follows, seq row wise. 
//The data at arrays are stored as a collection of individual elements, each stored sequentially

//a struct stores data as is, such that the elements can also be of diff types

int main(){
    struct name { int a; float b;};
    struct name var1 = { 3, 4.0 };

}

// a struct can be of any dimentions

int temp(){
    struct name2 {int a[30]; float roll_number; struct name;};
}   //a struct can contain another struct within themselves