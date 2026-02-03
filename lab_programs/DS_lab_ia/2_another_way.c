# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main(){
    char o_string[100];
    printf("Enter original string: ");
    scanf("%s", o_string);
    char t_string[100];
    printf("Enter target string: ");
    scanf(" %s", t_string);
    char r_string[100];
    printf("Enter string to replace targer: ");
    scanf(" %s", r_string);
    char new_string[100] = {0};
    
    //starting computation-
    int i = 0;  // represents original string index
    int j = 0;  // represents target string index
    int r_len = strlen(r_string); // represents replacement string length
    int t_len = strlen(t_string); // represents target string length
    char flag_matched = 0;
    while (o_string[i]){
        j = 0;
        while(o_string[i+j]){

            if (t_string[j] == 0){
                flag_matched = 1;
                break;
            }
            
            if (t_string[j] != o_string[i+j]){
                flag_matched = 0;
                break;
            }
            
            j++;
        }

        if (flag_matched){
            strcat(new_string, r_string);
            printf("Added r_string, new string is: %s\n", new_string);
            i+=t_len;
        }
        else{
            int k=-1;
            while(new_string[++k]);
            new_string[k] = o_string[i];
            printf("Added a o_string, new string is: %s\n", new_string);
            i++;
        }
    }

    printf("New string is: %s\n", new_string);
    return 0;
}
