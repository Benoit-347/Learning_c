#include <stdio.h>

int main(){
int j = 10;
int i = 9;

int k = 0;

for(;i<50; i = i +1, i = i*2){
if(k>10)
break;
printf("hello\n");

printf("%d, %d\n", i, j);
++k;
}
}