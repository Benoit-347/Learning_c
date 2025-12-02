# include <stdio.h>
# include <stdlib.h>


int * create_matrix(int num_p, int num_type_r){
    return (int *) malloc(sizeof(int) * num_p * num_type_r);
}

void display_matrix(int num_p, int num_type_r, int matrix[num_p][num_type_r]){

    for (int i = 0; i<num_p; i++){
        for (int j = 0; j<num_type_r; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

}

void get_allocation_matrix(int num_p, int num_type_r, int cur_alloc_matrix[num_p][num_type_r]){

    for (int i = 0; i<num_p; i++){
        printf("Enter the number of arms ALLOCATED to process %d:-\n", i+1);
        for (int j = 0; j<num_type_r; j++){
            printf("Arm type %d: ", j+1);
            scanf("%d", &cur_alloc_matrix[i][j]);
        }
    }
}

void get_max_need(int num_p, int num_type_r, int max_need_matrix[num_p][num_type_r]){

    for (int i = 0; i<num_p; i++){
        printf("Enter the number of arms REQUIRED to process %d:-\n", i+1);
        for (int j = 0; j<num_type_r; j++){
            printf("Arm type %d: ", j+1);
            scanf("%d", &max_need_matrix[i][j]);
        }
    }
}

void get_need_matrix(int num_p, int num_type_r, int need_matrix[num_p][num_type_r], int max_need_matrix[num_p][num_type_r], int cur_alloc_matrix[num_p][num_type_r]){

    for (int i = 0; i<num_p; i++){
        for (int j = 0; j<num_type_r; j++){
            need_matrix[i][j] = max_need_matrix[i][j] - cur_alloc_matrix[i][j];
        }
    }
}

int * get_total_allocation(int num_p, int num_type_r, int cur_allocation_matrix[num_p][num_type_r]){
    
    int * output_arr = create_matrix(1, num_type_r);
    int sum;

        sum = 0;
    for (int j = 0; j<num_type_r; j++){
        sum = 0;
        for (int i = 0; i<num_p; i++){
            sum += cur_allocation_matrix[i][j];
        }

        *(output_arr + j) = sum;
    }

    return output_arr;
}

int * get_available(int * total_resource, int * total_alloc, int num_type_r){

    int * output = create_matrix(1, num_type_r);
    for (int i = 0; i<num_type_r; i++){
        output[i] = total_resource[i] - total_alloc[i];
    }
    return output;
}

void request_resource(int * new_request, int process_index, int * available, int num_p, int num_type_r,  int alloc_matrix[num_p][num_type_r], int need_matrix[num_p][num_type_r]){
    
    int i;
    
    for (i = 0; i<num_type_r; i++){
        if (new_request[i] > need_matrix[process_index][i])
            break;
        if (new_request[i] > available[i])
            break;
    }

    if (i == num_type_r){
        printf("Can allocate resource to %d\n", process_index+1);
        for (i = 0; i< num_type_r; i++)
            alloc_matrix[process_index][i] += new_request[i];
    printf("New allocation of experiment %d is:\n", process_index + 1);
    display_matrix(num_p, num_type_r, alloc_matrix);
    }
    else
        printf("Cannot allocate resource\n");
}

int * execute_bankers_algo(int * available, int num_p, int num_type_r, int need_matrix[num_p][num_type_r], int cur_alloc_matrix[num_p][num_type_r]){

    int flag= 1;    // need is empty flag
    int count = 0;
    int old_count;
    int j, i;  // need to check if all need resource types are available
    int * arr = (int *) calloc(num_p, sizeof(int));
    int * output = (int *) calloc(num_p, sizeof(int));
    while (count != num_p){
        old_count = count;
        for (i = 0; i<num_p; i++){
            if (arr[i] == 1)
                continue;
            for (j = 0; j<num_type_r; j++){
                if (available[j] < need_matrix[i][j])
                    break;
            }
            // If chk pass, executes process, and add alloc to available
            if (j == num_type_r){ // chk pass
                for (j = 0; j<num_type_r; j++){
                    available[i] += cur_alloc_matrix[i][j];
                    cur_alloc_matrix[i][j] = 0;
                }
                arr[i] = 1;
                output[count] = i;
                count++;
                printf("Executed experiment %d sucessfully\n\n", i+1);
                printf("New allocation of arms is:\n");
                display_matrix(num_p, num_type_r, cur_alloc_matrix);
                printf("\n");
            }
        }
        if (old_count == count){
            printf("Found a deadlock!\n");
            return 0;
        }
    }
    return output;
}

int main(){
    int num_p, num_type_r;
    int * total_resources_arr;
    printf("Enter the number of types of arms (types of resource): ");
    scanf("%d", &num_type_r);
    printf("\n");

    // obtain total resources existing:
    total_resources_arr = create_matrix(1, num_type_r);

    for (int i = 0; i<num_type_r; i++){
        printf("Enter total number of arms exists in lab, of type %d: ", i+1);
        scanf("%d", total_resources_arr + i);
    }

    printf("\nEnter number of experiments (processes): ");
    scanf("%d", &num_p);

    printf("\n");
    // obtain current allocation to processes-
    int * flat_array = create_matrix(num_p, num_type_r);
    int (*cur_alloc_matrix)[num_type_r] = (int (*)[num_type_r])flat_array; // enalbe using array[][] format instead of direct pointer usage
    get_allocation_matrix(num_p, num_type_r, cur_alloc_matrix);
    printf("\nThe allocation matrix: \n");
    display_matrix(num_p, num_type_r, cur_alloc_matrix);

    printf("\n");
    
    // obtaining max need of processes-
    flat_array = create_matrix(num_p, num_type_r);
    int (*max_need_matrix)[num_type_r] = (int (*)[num_type_r])flat_array;
    get_max_need(num_p, num_type_r, max_need_matrix);

    printf("\nThe maximum need matrix:\n");
    display_matrix(num_p, num_type_r, max_need_matrix);


    printf("\n");
    // obtain need matrix:
    flat_array = create_matrix(num_p, num_type_r);
    int (*need_matrix)[num_type_r] = (int (*)[num_type_r])flat_array;
    get_need_matrix(num_p, num_type_r, need_matrix, max_need_matrix, cur_alloc_matrix);


    printf("\nThe need matrix: \n");
    display_matrix(num_p, num_type_r, need_matrix);

    printf("\n");

    // available
    int * total_alloc_arr = get_total_allocation(num_p, num_type_r, cur_alloc_matrix);
    printf("The available resources now is: \n");
    int * total_available_arr = get_available(total_resources_arr, total_alloc_arr, num_type_r);
    /*
    display_matrix(total_resources_arr, 1, num_type_r);
    display_matrix(total_alloc_arr, 1, num_type_r);
    */
    display_matrix(1, num_type_r, (int (*)[5])total_available_arr);


    // Solution i) When request new resources from system.
    int process_id;
    printf("\nEnter which process to request for: ");
    scanf("%d", &process_id);
    process_id--;   // convert position to index

    int * request = create_matrix(1, num_type_r);
    printf("Enter the new request for arms (resources):\n");
    for (int i = 0; i< num_type_r; i++){
        printf("Arm type %d: ", i + 1);
        scanf("%d", request + i);
    }

    request_resource(request, process_id, total_available_arr, num_p, num_type_r, cur_alloc_matrix, need_matrix);
    

    printf("\n---Starting bankers algorithm---\n\n");
    int * output = execute_bankers_algo(total_available_arr, num_p, num_type_r, cur_alloc_matrix, need_matrix);

    if (!output)
        printf("Not a safe sequence!\n");
    
    else{
        printf("The safe seq is: ");
        for (int i = 0; i<num_p; i++)
            printf("> experiment %d ", output[i] + 1);
    }

    printf("\nEnd of program!\n");
    return 0;
}