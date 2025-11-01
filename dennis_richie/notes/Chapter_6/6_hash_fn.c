// a hash fn turn a group of chars or a word into a single numberical value, that can be compared to quickly access it in say a lookup table

# include <stdio.h>

# define HASHSIZE 101

int hash(char * word){
    char ele = *word++;
    unsigned int result = 0;
    while (ele){
        result = result*31 + ele;
        ele = *word++;
    }
    return result % 101;    // This produces the starting pos in an hastab arr
}

int main(){
    char word[] = "GUB";
    printf("Answer is: %d\n", hash(word));
    return 0;
}