#include <stdio.h>
#include <stdlib.h>

void enqueue(int *queue, int *rear, int *count, int size, int ticket){
    if (*count == size)
        printf("Queue Overflow\n");
    else{
        *rear = (*rear + 1) % size;
        queue[*rear] = ticket;
        (*count)++;
    }
}

void dequeue(int *queue, int *front, int *rear, int *count, int size){
    if (*count == 0)
        printf("Queue Underflow\n");
    else{
        printf("Ticket #%d has been deleted.\n", queue[*front]);
        *front = (*front + 1) % size;
        (*count)--;
    }
}

void display(int *queue, int front, int count, int size){
    if (count == 0)
        printf("Circular queue empty: No Calls\n");
    else{
        printf("Waiting Calls in Queue:\n");
        for (int i = 0; i < count; i++){
            printf("Ticket #%d\n", queue[front]);
            front = (front + 1) % size;
        }
    }
}

int main(){
    int size;
    printf("Enter size of queue ");
    scanf("%d", &size);
    int *queue = (int *)malloc(size * sizeof(int));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int front = 0, rear = -1, count = 0;
    int choice, ticket;

    while (1) {
        printf("\n--- Call Center Queue System ---\n");
        printf("1. Add New Call (Enqueue)\n");
        printf("2. Serve Next Call (Dequeue)\n");
        printf("3. Display Waiting Calls\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Enter Ticket Number: ");
                scanf("%d", &ticket);
                enqueue(queue, &rear, &count, size, ticket);
                break;
            case 2:
                dequeue(queue, &front, &rear, &count, size);
                break;
            case 3: 
                display(queue, front, count, size);
                break;
            case 4:
                free(queue);
                return 0;
        }
    }
}