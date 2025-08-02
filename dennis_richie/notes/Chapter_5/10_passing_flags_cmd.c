// To input the configuration of program directly from running files, we can pass flags

// find -x -n (or) -xn 
    // the '-' denotes a unique char here, signalling a upcomming flag
        // we force a convention of only 1 len long char of flag, so we can match only 1 char for each flag.


# include <stdio.h>
# include <string.h>
#define MAXLINE 1000

// int getline(char *line, int max);

int getline_(char *arr, int len){
    int i = 0;
    char ch;
    while ((ch = getchar()) != EOF && ch != '\n' && i<len-1)
        arr[i++] = ch;
    arr[i] = 0;
    return i;
}

main(int argc, char *argv[]){
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c){
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = -1;
                    found = -1;
                    break;
            }
    // if -x, find a match with the reverse of pattern
    // if -n, do numbering while printing matches
    if (argc != 1)
        printf("Usage: find -x -n pattern: %d\n", argc);
    else
        while (getline_(line, MAXLINE) > 0){
            lineno++;
            if ((strstr(line, *argv) != NULL) != except){
                if (number)
                    printf("%ld: ", lineno);
                printf("%s\n", line);
                found++;
            }
        }
    return found;
}
          