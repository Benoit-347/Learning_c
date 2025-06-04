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
    
    return i + 1;   // leaves 2 uninitialized: at index current and i-1 -> len = 1 for only \n and EOF
 /* New method: allows EOF and \n to give output +1 but not storing it. So to allow ending, chks for count if 1 or lower, stops at readlines 
    if (ch == '\n')
        arr[i++] = ch;
    return i;   //puttin i+1 never gives 0 and here, EOF is not counted, givingn -1 =0 for 2 EOF ending*/ 
}

char *alloc(int n){
    arr_p += n;
    return arr_p - n;
}