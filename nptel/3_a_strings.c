# include <string.h>
# include <stdio.h>

int main(){
char string3[6], string2[6] = "hello\0", string4[11];
int length, cmp;


strcpy(string3, string2);
printf("string 3: %s\n", string3);
printf("String 2: %s\n", string2);

length = strlen(string3);


cmp = strcmp(string2, string3);
printf("comparison: %d\n", cmp);

strcpy(string4, string2);
strcat(string4, string3);
printf("string 4: %s\n", string4);
}