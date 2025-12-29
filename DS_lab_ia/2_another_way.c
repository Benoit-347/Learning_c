# include <stdio.h>
# include <string.h>

# define MAX_STR 1000

int main(){
    char string_1[MAX_STR];
    char t_str[MAX_STR];
    char r_str[MAX_STR];
    char new_string[MAX_STR] = {0};

    printf("Enter string to replace: ");
    scanf("%s", string_1);
    printf("Enter target string: ");
    scanf("%s", t_str);
    printf("Enter replace with string: ");
    scanf("%s", r_str);

    int i = 0;
    int j = 0;
    int t_len = strlen(t_str);
    int r_len = strlen(r_str);
    int n_len = 0;
    char flag;
    while(string_1[i]){
        j = 0;
        while (string_1[i + j]){      // loop over target, if perfect match replace. else skip to next char (infinte loop or in rare case, end of original string)
            if (t_str[j] == 0){
                strcat(new_string, r_str);  // we chk for match and do the concatenation at main loop body in method: 1. Hence even the vars are updated outside.

                // to skip over i bytes, as this is removed from original.
                i += t_len;
                n_len += r_len; // keeping track of len of new str, to minimize strlen usage and add unmatched letters to new_string's end
                flag = 1;   // to know if it matched, then dont cpy to end of new string
                break;
            }

            else{   // continue while(j) as long as matches and not 0
                if (t_str[j] != string_1[i+j]){
                    flag = 0;
                    break;
                }
            }
            
            j++;

        }
        if (!flag){
            new_string[n_len++] = string_1[i];
            i++;
        }
    }

    printf("New string is: %s\n", new_string);
}