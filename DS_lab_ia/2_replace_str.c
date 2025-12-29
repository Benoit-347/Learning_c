# include <stdio.h>

# define MAX_STR 1000

int strlen(char * c_ptr){
    int i = 0;
    while (*c_ptr++)
        i++;
    return i;
}

void replace(char * original_str, char * t_str, char * r_str, char * new_str){

int o_ind = 0;
    int t_len = strlen(t_str);
    int r_len = strlen(r_str);
    int n_ind = 0;

    int t_ind;
    while(original_str[o_ind]){
        
        // method: 2- infite inner loop until end of target (concatenate, update main loop vars), or mismatch; after break, flag tells if match or mismatch. if mismatch, add cur char to new string. code at next file.
        // Method: 1- maintain loop with cur index and end index, exit in between only if mismatch. If mismatch => break out. The cur_index and end_index will tell about flag info; depending- concatenate, updating main loop vars, else add cur char to new string.
        for (t_ind = 0; t_ind <t_len; t_ind ++)     // loop over target, if perfect match replace. else skip to next char (infinte loop or in rare case, end of original string)
            if (t_str[t_ind] != original_str[o_ind + t_ind])
                break;

        if (t_ind == t_len){
            for (int i = 0; i< r_len; i++)      // or int i = 0; while(r_str[i]) new_str[n_ind++] = r_str[i];
                new_str[n_ind++] = r_str[i];
            o_ind += t_ind;
        }

        else
            new_str[n_ind++] = original_str[o_ind++];
        
    }
    new_str[n_ind] = 0;
}

int main(){
    char original_str[MAX_STR];
    char t_str[MAX_STR];
    char r_str[MAX_STR];
    char new_str[MAX_STR] = {0};

    printf("Enter string to replace: ");
    scanf("%s", original_str);
    printf("Enter target string: ");
    scanf("%s", t_str);
    printf("Enter replace with string: ");
    scanf("%s", r_str);

    replace(original_str, t_str, r_str, new_str);

    printf("New string is: %s\n", new_str);
}