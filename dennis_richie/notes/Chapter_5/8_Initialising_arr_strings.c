//Consider a arr of strings for the months of a year, so now you can obatain the string of respective month by index of the array.
    //You can initialize it, with the way how strings work

#include <stdio.h>
char *arr_month[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int main(){
    printf("Month 3 = %s\n", arr_month[2]);
    return 0;
}