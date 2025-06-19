# include <stdio.h>

void go_back(char * path, int * i){
    path[*i+1] = 0;
    while (path[*i] != '/'){
        printf("The path: %c index: %d\n", path[*i], *i);
        path[(*i)--] = 0;}
    (*i)++;
        
}


char new_string[100] = {0};
char* simplifyPath(char* path) {
    char back_path[5] = {'/', '.', ',', '/'};
    char cur_path[4] = "/./";
    int j, k;
    char chk = 0;
    char loop_slash = 0;

    int l = 0;
    printf("path: %c back_path: %d", *path, *back_path);
    while (path[l++] == back_path[l++])
    printf("true");
            if (!back_path[l]){
                new_string[0] = '/';
                new_string[1] = '/';
                return new_string;
            }

    int new_string_index = 0;
    for (int i = 0; path[i]; i++){
        j = 0, k  = i, chk = 0;

        if (path[i] == '/' && path[i+1] == '/')
            continue;
        
        new_string[new_string_index++] = path[i];
        printf("0. The string: %s\n", new_string);
        
        while (path[k++] == back_path[j++])
            if (!back_path[j]){
                chk = 1;
                break;
            }
            else if (!path[k]){
                chk = 0;
                break;
            }
        if (chk){
            new_string_index = new_string_index-2;
            i = i + 1;
            printf("chk 1. The string: %s\n", new_string);
            go_back(new_string, &new_string_index);
        }

        j = 0, k = i;
        while (path[k++] == cur_path[j++])
            if (!cur_path[j]){
                chk = 1;
                break;
            }
            else if (!path[k] || !cur_path[j]){
                chk = 0;
                break;
            }
        if (chk){
            i = i + 1;
            new_string[--new_string_index] = 0;
            printf("chk 2. The string: %s\n", new_string);
        }

    }
    if (new_string[1])
        if (new_string[--new_string_index] == '/')
            new_string[new_string_index] = 0;
    return new_string;

}

int main(){
    char arr[] = "/../"; //
    int i = 15;
    char * arr_1 = simplifyPath(arr);
    printf("The string: %s\n", arr_1);
}