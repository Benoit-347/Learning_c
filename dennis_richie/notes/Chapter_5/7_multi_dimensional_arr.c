//we prev used a collection of pointers to strings into an pointer array. (int ** arr)
//here we use a vanilla sequence of 1-D array, whose divisions at certain intervals (column) gives us a 2D arr


#include <stdio.h>

//consider the problem: to convert day of the month with month given to day of the year and vice versa
    // int month_day(1988, 60, &m, &d);

    //months of the year table, 2 sets for: 1- no leap,  2- leap year
char arr_month_days[2][12] = { {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} };
//in the book
    // the put months starting with 0: {0, 31, 28, ...} 
        // later in algo, they started for loop with i = 1, instead of 0.
int day_of_the_year(int year, int month, int day_){
    
    //leap year flag
    char leap_flag = (year%4 == 0 && year%100 != 0 || year%400 ==0)? 1 : 0; //Also since this flag can act as index in a 2 row arr when the row depends on this flag.. We use this flag to index directly
    int day = 0;

    //to find day, add all months until prev month

    for (int i = 0; i<month-1; i++)    //index of arr  -> [month -1]; from 1st month to prev month -> [0 to month-2] 
        day += arr_month_days[leap_flag][i];

    day += day_;
    
    return day;

}

int month_day(int day, char leap, char *m, char *d){
    int month_index = 0;
    int month = 1;
    int current_month;
    while ( day > (current_month = arr_month_days[leap][month_index++]) )   // equivalent to a for loop with month as index, removing month from day until day is smaller that month.
        day -= current_month;
    *m = month_index;
    *d = day;
}

int main(){
    int day_answer = day_of_the_year(2024, 3, 5);

    printf("The day at %d-%d-%d is: %d\n", 2024, 3, 5, day_answer);
    
    char *m, *d;
    month_day(day_answer, 1, m, d);
    printf("Month of above is %d, at day: %d\n", *m, *d );
    return 0;
}

// The rightmost index; i,e. the column index varies fastest in an arr.
// consider tht you want to pass a 2D arr to a fn. Then you must specify the column count to the fn, for it to be able to obtains the raw 1-D arr as typical 2-D
/*Eg of passing 2D to a fn:
    f(int daytab[2][12]);
    //or
    f(int daytab[][12]);
//consider
    f(int (*daytab)[12]);
    //here the parameter daytab is a array of pointers.
//consider
    f(int *daytab[12]);
    //here the parameter is, dereference of (dereference of (daytab + 12) ) since [] has higher precedence than *.  */
//Observable Note: Only the first Dimension of an arr index during specialization can be left free. (arr[][12])