// Directing stdio and stdout
// Using UNIX features:
    // 1. By passing output and input to/from a file instead of stdout/stdio
        // Eg- ./temp.exe > file_out.txt
        // Eg- ./temp.exe < file_2.txt

    // 2. Pipelining:
        // Feeding output from one program to the input of another. 
        // Eg- ./temp.exe | ./a.out
    
    // 3. Making changes to stdio and stdout by opening/closing file streams within C program.

        #include <stdio.h>

        int main(void) {
            // Redirect input from a file instead of keyboard
            freopen("input.txt", "r", stdin);

            // Redirect output to a file instead of screen
            freopen("output.txt", "w", stdout);

            char word[100];
            while (scanf("%s", word) != EOF) {
                printf("Read word: %s\n", word);
            }



    // 4. Using system calls within the C program
        #include <unistd.h>
        #include <fcntl.h>

            int fd = open("input.txt", O_RDONLY);
            dup2(fd, STDIN_FILENO);  // replace stdin with file
            close(fd);
        printf("Content inside file");
        }