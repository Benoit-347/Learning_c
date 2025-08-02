# include <stdio.h>
# include <string.h>
# include <ctype.h>

# define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;          // type of last token
char token[MAXTOKEN];   // last token string
char name[MAXTOKEN];    // identifier name
char datatype[MAXTOKEN];//the storage data type (like char, int, etc..)
char out[100];          //output string

int buf[100];
int bufp = 0;

int main(){
    while (gettoken() != EOF){
        strcpy(datatype, token);
        out[0] = 0;
        dcl();
        
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

int gettoken(void){
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '('){
        if ((c = getch()) == ')'){
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '{';
        }
    } else if (c == '['){
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = 0;
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)){
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = 0;
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}


void dcl(void){
    int ns;

    for (ns = 0; gettoken() == '*'; ns++)
        ;
    
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void){
    int type;

    if (tokentype = '('){
            dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    
    while ((type= gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
            }
}

int getch(){
    extern int buf[];
    extern int bufp;
    return (bufp>0? buf[--bufp]: getchar()); 
}   // only 1 max: return (bufp>0? buf[--bufp]: getchar()); (exer 4.8)

void ungetch(int c){
    extern int buf[];
    extern int bufp;
    buf[bufp++] = c;
}   // only 1 max: buf[0] = c; bufp = 1;