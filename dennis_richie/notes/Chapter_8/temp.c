# include <unistd.h>
# include <stdio.h>

int main(){
    char c = getc(stdin);
    putc(c, stdout);
    putc('\n', stdout);
    printf("%d", 'a' + 25);
}