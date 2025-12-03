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

void show_arm(int n){
    for (int i = 1; i<=n; i++)
        printf("Arm_%d\t", i);
    printf("\n");
}

void display_alloc_available_need_matrix(int * available, int num_p, int num_type_r, int cur_alloc_matrix[num_p][num_type_r], int need_matrix[num_p][num_type_r], int * total_resources_arr){
    
    printf("\nThe current allocation matrix: \n");
    show_arm(num_type_r);
    display_matrix(num_p, num_type_r, cur_alloc_matrix);
    
    printf("\nThe current available resources are: \n");
    show_arm(num_type_r);
    display_matrix(1, num_type_r, (int (*)[num_type_r])available);

    printf("\nThe current need matrix is: \n");
    show_arm(num_type_r);
    display_matrix(num_p, num_type_r, need_matrix);
    printf("\n");
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

void request_resource(int * new_request, int process_index, int * available, int num_p, int num_type_r,  int alloc_matrix[num_p][num_type_r], int need_matrix[num_p][num_type_r], int * total_resources_arr){
    
    int i;
    
    for (i = 0; i<num_type_r; i++){
        if (new_request[i] > need_matrix[process_index][i])
            break;
        if (new_request[i] > available[i])
            break;
    }

    if (i == num_type_r){
        printf("Can allocate resource to %d\n", process_index+1);
        for (i = 0; i< num_type_r; i++){
            alloc_matrix[process_index][i] += new_request[i];
            available[i] -= new_request[i];
            need_matrix[process_index][i] -= new_request[i];
        }

    display_alloc_available_need_matrix(available,num_p, num_type_r, alloc_matrix, need_matrix, total_resources_arr);
    }
    else
        printf("Cannot allocate resource\n");
}

int * execute_bankers_algo(int * available, int num_p, int num_type_r, int cur_alloc_matrix[num_p][num_type_r], int need_matrix[num_p][num_type_r], int * total_resources_arr){

    printf("---Normal version! (Does not prempt any process)---\n");
    printf("START:\n");
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
                    available[j] += cur_alloc_matrix[i][j];
                    cur_alloc_matrix[i][j] = 0;
                }
                arr[i] = 1;
                output[count] = i;
                count++;
                printf("\nExecuted experiment %d sucessfully\n", i+1);
                display_alloc_available_need_matrix(available,num_p, num_type_r, cur_alloc_matrix, need_matrix, total_resources_arr);
            }
        }
        if (old_count == count){
            printf("Found a deadlock!\n");
            return 0;
        }
    }
    return output;
}

int * execute_prempt_bankers_algo(int * available, int num_p, int num_type_r, int cur_alloc_matrix[num_p][num_type_r], int need_matrix[num_p][num_type_r], 
                                int * total_resources_arr){
    printf("---Prempt version! (In case of deadlock, deallocates process and tries to obtain safe seq)---\n");
    printf("START:\n");
    int flag= 1;    // need is empty flag
    int count = 0;
    int old_count;
    int holding_process;
    int j, i;  // need to check if all need resource types are available
    int * arr = (int *) calloc(num_p, sizeof(int));
    int * output = (int *) calloc(num_p, sizeof(int));
    int * holding_empty = (int *) calloc(num_p, sizeof(int));

    while (count != num_p){
        old_count = count;
        holding_process = -1;
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
                    available[j] += cur_alloc_matrix[i][j];
                    cur_alloc_matrix[i][j] = 0;
                }
                arr[i] = 1;
                holding_empty[i] =1;
                output[count] = i;
                count++;
                printf("\nExecuted experiment %d sucessfully\n\n", i+1);
                display_alloc_available_need_matrix(available,num_p, num_type_r, cur_alloc_matrix, need_matrix, total_resources_arr);
    
            }
            else if (holding_process == -1 && holding_empty[i] == 0)
                holding_process = i;
        }
        if (old_count == count){
            if (holding_process != -1){
                printf("\nThere is lack of resource for any process to execute!\n\nPreempting process %d.\n", holding_process + 1);
                for (j = 0; j<num_type_r; j++){
                    available[j] += cur_alloc_matrix[holding_process][j];
                    need_matrix[holding_process][j] += cur_alloc_matrix[holding_process][j];
                    cur_alloc_matrix[holding_process][j] = 0;
                    holding_empty[holding_process] = 1;
                }
                display_alloc_available_need_matrix(available,num_p, num_type_r, cur_alloc_matrix, need_matrix, total_resources_arr);
            }
            else{
                printf("Found a deadlock!\n");
                return 0;
            }
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
    printf("\n\nThe allocation matrix: \n");
    show_arm(num_type_r);
    display_matrix(num_p, num_type_r, cur_alloc_matrix);

    // available
    int * total_alloc_arr = get_total_allocation(num_p, num_type_r, cur_alloc_matrix);
    printf("\nThe available resources now is: \n");
    show_arm(num_type_r);
    int * total_available_arr = get_available(total_resources_arr, total_alloc_arr, num_type_r);
    display_matrix(1, num_type_r, (int (*)[num_type_r])total_available_arr);
    printf("\n");
    // obtaining max need of processes-
    flat_array = create_matrix(num_p, num_type_r);
    int (*max_need_matrix)[num_type_r] = (int (*)[num_type_r])flat_array;
    get_max_need(num_p, num_type_r, max_need_matrix);

    printf("\n\nThe maximum need matrix:\n");
    show_arm(num_type_r);
    display_matrix(num_p, num_type_r, max_need_matrix);

    // obtain need matrix:
    flat_array = create_matrix(num_p, num_type_r);
    int (*need_matrix)[num_type_r] = (int (*)[num_type_r])flat_array;
    get_need_matrix(num_p, num_type_r, need_matrix, max_need_matrix, cur_alloc_matrix);

    printf("\nThe need matrix: \n");
    show_arm(num_type_r);
    display_matrix(num_p, num_type_r, need_matrix);


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

    request_resource(request, process_id, total_available_arr, num_p, num_type_r, cur_alloc_matrix, need_matrix, total_resources_arr);
    

    printf("\n\n---Starting bankers algorithm---\n\n");
    // Comment below line and UnComment second line to use prempt version
    int * output = execute_bankers_algo(total_available_arr, num_p, num_type_r, cur_alloc_matrix, need_matrix, total_resources_arr);
    // int * output = execute_prempt_bankers_algo(total_available_arr, num_p, num_type_r, cur_alloc_matrix, need_matrix, total_resources_arr);

    if (!output)
        printf("Not a safe sequence!\n");
    
    else{
        printf("\n---RESULT---:\n\nThe safe seq is: ");
        for (int i = 0; i<num_p; i++)
            printf("> experiment %d ", output[i] + 1);
    }

    printf("\n\nEnd of program!\n\n");
    return 0;
}