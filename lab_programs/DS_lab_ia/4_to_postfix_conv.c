# include<stdio.h>
# include<string.h>

# define MAX_ELE 30

int f(char s){
    switch(s){
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '$':
        case '^': return 5;
        case '(': return 0;
        case '#': return -1;
        default: return 8;
    }
}

int g(char s) {
    switch(s){
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 3;
        case '$':
        case '^': return 6;
        case '(': return 9;
        case ')': return 0;
        default: return 7;
    }
}

int main(){
    char c, s[MAX_ELE]={'#'};
    char inf[MAX_ELE];
    char pf[MAX_ELE];
    int top=0,i,j=0;//top=0 because '#' is already stored in stack
    printf("enter the infix expression\n");
    scanf("%s",inf);
    int temp;
    for(i=0;i<strlen(inf);i++){

        temp = top;
        printf("\nStack now:\n");
        while(s[temp]!= '#')
            printf("%c\n", s[temp--]);
            
        c = inf[i];
        //STEP 1
        while( f( s[top] ) > g(c) ){
            pf[j++]=s[top--];
        }
        //STEP 2
        if( f( s[top] ) != g( c ) )     // if not: s[top] == '(' and c == ')'; then push c into s[top]
            s[++top]=c;
        else
            top--;      // skip the '(' in stack, from c- '()' is NULL/redundant
    }
    while(s[top]!='#')
        pf[j++]=s[top--];
    pf[j]='\0';
    printf("the postfix expression:%s\n",pf);
    return 0;
}