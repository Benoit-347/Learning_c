#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char * lineptr[MAXLINES];

int readlines(char * lineptr[], int nlines);
void writelines(char * lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

// sort input lines

int main(){
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES))>= 0) {
        qsort(lineptr, 0, nlines -1);
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort\n");
        return 1;
    }


}

#define MAXLEN 1000
int getline_(char *arr, int len);
char * alloc(int);

static char arr_buf[MAXLINES*MAXLEN];
static char *arr_p = arr_buf;

//readlines; read input lines
int readlines(char *lineptr[], int maxlines){
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len  = getline_(line, MAXLEN)) > 1){
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1]  = 0; // this deletes newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }}
    return nlines;
}

//writelines; write output lines
void writelines(char *lineptr[], int nlines){
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

// qsort; sort into increasing order
void qsort(char *v[], int left, int right){
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i<=right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last -1);
    qsort(v, last+1, right);
}

//swap; interchange v[i] and v[j]
void swap(char *v[], int i, int j){
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int getline_(char *arr, int len){
    int i = 0;
    char ch;
    while ((ch = getchar()) != EOF && ch != '\n' && i<len-1)
        arr[i++] = ch;
    
    return i + 1;   

    /*The getline takes input including \n or only the string
    If only string;
        "abc" -> returns i as 3 from above algo.
        need to assign \o at end: arr[len] = 0;
    if end with \n;
        "abc\n -> returns i as 4 from above algo
        need to assign \n at end: arr[len - 1] = 0;
        
        here \n acts as a placeholder for \0, whereas in only str, we assgned \0 at new space
            but when using placeholder of \n, we cannot end input by EOF + EOF as this would make us add EOF to arr. (which if added, solves the problem)
                hence using permenent i + 1 to create a constant space after exit, so able to maintain the same code as book, and also end with EOF
                
    Or we can use only str as output arr, pass len of str and let the program handle adding 0 at end by arr[line +1] = 0; 
        (the was solved by the \n problem, where \n from getline was replaced with \0 here.) */

        
    // leaves 2 uninitialized: at index current and i-1 -> len = 1 for only \n and EOF
 /* New method: allows EOF and \n to give output +1 but not storing it. So to allow ending, chks for count if 1 or lower, stops at readlines 
    if (ch == '\n')
        arr[i++] = ch;
    return i;   //puttin i+1 never gives 0 and here, EOF is not counted, givingn -1 =0 for 2 EOF ending*/ 
}

char *alloc(int n){
    arr_p += n;
    return arr_p - n;
}