# include <stdio.h> 

int main(){
    FILE * my_file_pointer;
    my_file_pointer = fopen("temp.txt", "w");
    char my_var[1000];
    fgets(my_var, 1000, my_file_pointer);
    printf("%s", my_var);
    fprintf(my_file_pointer, "Hi");
    fclose(my_file_pointer);
    return 0;
} 