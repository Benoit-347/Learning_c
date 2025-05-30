/*This program tackles converting int n to string number, 2 ways for this: 
                                                            i) create an arr of lower digits to giher by n/10 meth, then print arr in reverse
                                                            ii) do a recursive print such the nested calls print first and then the body*/

# include <stdio.h>

void printd(int n){
    if (n<0){
        n = -n;
        putchar('-');
    }
    if  (n/10)
        printd(n/10);
    putchar('0' + n%10);

}

int main(){
    int num = 219;
    printd(219);
    return 0;
}