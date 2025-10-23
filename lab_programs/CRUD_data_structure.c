# include <stdio.h>
# include <stdlib.h>

/*
CRUD 1- 
*/

// going with slower arr of pointers for each record -> allows easy insert and del on drive and no of r/w op
int main(){

    // 1. determing the total size of whole arr
    char * arr_ptrs[1000] = {0};
    int len_name = 100, len_title = 50;
    int column_size = len_name + len_title;

    int command;
    int row_count = 0;
    char * ptr_row; // base ptr of each record from malloc

    printf("Enter command: ");
    scanf("%d", &command);

    /*Menu:
        1 -> add a rec
        2 -> Display all rec
        3 -> Display a particular rec
        4 -> insert a rec at a specific pos of arr of rec
        5 -> del a specific rec (rec_count strarting from 1)
        6 -> del all
        7 -> rewrite a rec
    */ 

    while((command >0) && (command <= 7)){

        if (command == 1){
            ptr_row = malloc(column_size);
            //  using row_count variable to skip ahead by rec_len for each input rec

            printf("Enter record details: \n");
            printf("Enter name: ");
            scanf(" %s", ptr_row);
            printf("Enter title: ");
            scanf(" %s", ptr_row+len_name);    // offset but still pointer here
            arr_ptrs[row_count] = ptr_row;
            row_count++;
        }

        else if (command == 2){

            // while keeping vars of rows input unchanged
            int row_count_temp = 0;

            // print all the info on all the records
            while (row_count_temp < row_count){
                ptr_row = arr_ptrs[row_count_temp];
                printf("Name: %s\n", ptr_row);
                printf("Title: %s\n", ptr_row + len_name);
                row_count_temp++;
            }
        }

        else if (command == 3){
            int count;
            printf("Enter the rec you want to read (index from 1): ");
            scanf(" %d",  &count);
            count--;
            printf("Name: %s\n", arr_ptrs[count]);
            printf("Title: %s\n", arr_ptrs[count]+ len_name);
        }

        else if (command == 4){
            int count;
            printf("Enter count of rec insertion (index strating from 1): ");
            scanf(" %d", &count);
            for (int i = row_count-1; i>count-2; i--){
                arr_ptrs[i+1] = arr_ptrs[i];
            }
            
            ptr_row = malloc(column_size);
            //  using row_count variable to skip ahead by rec_len for each input rec

            printf("Enter record details: \n");
            printf("Enter name: ");
            scanf(" %s", ptr_row);
            printf("Enter title: ");
            scanf(" %s", ptr_row+len_name);
            arr_ptrs[count -1] = ptr_row;
            row_count++;
        }

        else if (command == 5){
            int count;
            printf("Enter the number of the rec u wanna del: ");
            scanf(" %d", &count);
            free(arr_ptrs[count-1]);
            for (int i = count-1; i<row_count-1; i++){  // index offset setting meaning- the input count is pos -> index of arr; cond true until including row_count -1 -1 (the extra overahead && -1 for lower celing since body does i +1)
                arr_ptrs[i] = arr_ptrs[i+1];
            }
            row_count--;
        }

        else if (command == 6){
            for (int i = 0; i< row_count; i++)
                free(arr_ptrs[i]);  // the pointer still holds the same memory address, but the memory it points to is no longer valid for use. (The now memory locaiton, by the allocator also holds free state meta data)
                                    // if still written to this freed ptr, it will still store data to this non formally allocated memory location (also called a dangling pointer):- dangerous side effect of using a dangling pointer
                                        // writing new data directly into a block of memory that the allocator considers free.
                                            // The operating system/runtime environment did not immediately detect this illegal write, because the memory page containing 0xABC was still mapped to your process.
            row_count = 0;
            printf("Forgotten all records (freed)\n");
        }

        else if (command == 7){
            int count;
            printf("Enter pos of rec to rewrite: ");
            scanf(" %d", &count);
            if (row_count<count){
                printf("Position entered not already defined to perform rewrite operation\n");
                printf("\nEnter command: ");
                scanf("%d", &command);
                continue;

            }
            ptr_row = arr_ptrs[count-1];

            printf("Enter record details\nEnter Name: ");
            scanf(" %s", ptr_row);
            printf("Enter Title: ");
            scanf(" %s", ptr_row + len_name);
        }

        printf("\nEnter command: ");
        scanf("%d", &command);
    }
    printf("Loop ended command typed: %d\n\nEND", command);
}