#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student data
struct Student 
{
    char usn[20];
    char name[50];
    char program[30];
    int sem;
    char phone[15];
    struct Student *next;
};

typedef struct Student* NODE;

NODE head = NULL;

// Function to create a new node
NODE createNode() {
    
    char usn[20], name[50], program[30], phone[15];
    int sem;
    printf("\nEnter details:\n");
    printf("USN: "); scanf("%s", usn);
    printf("Name: "); scanf("%s", name);
    printf("Programme: "); scanf("%s", program);
    printf("Semester: "); scanf("%d", &sem);
    printf("Phone: "); scanf("%s", phone);

    NODE newNode = (NODE)malloc(sizeof(struct Student));
    strcpy(newNode->usn, usn);
    strcpy(newNode->name, name);
    strcpy(newNode->program, program);
    newNode->sem = sem;
    strcpy(newNode->phone, phone);
    newNode->next = NULL;
    return newNode;
}

// a) Create list using front insertion
void createList(int n)
{
    char usn[20], name[50], program[30], phone[15];
    int sem;
    for (int i = 0; i < n; i++) 
    {
        NODE newNode = createNode();
        newNode->next = head;  // front insertion
        head = newNode;
    }
}

// b) Display all student records
void displayList() 
{
    NODE temp = head;
    int count = 0;

    if (head == NULL) 
    {
        printf("\nList is empty.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (temp != NULL) 
    {
        printf("USN: %s | Name: %s | Programme: %s | Sem: %d | Phone: %s\n",
               temp->usn, temp->name, temp->program, temp->sem, temp->phone);
        temp = temp->next;
        count++;
    }
    printf("Total number of student records: %d\n", count);
}

// c) Insert at end
void insertEnd()
{
    char usn[20], name[50], program[30], phone[15];
    int sem;


    NODE newNode = createNode();

    if (head == NULL) 
    {
        head = newNode;
        return;
    }

    NODE temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

// c) Delete at end
void deleteEnd() 
{
    if (head == NULL)
    {
        printf("\nList is empty. Nothing to delete.\n");
        return;
    }

    NODE temp = head, prev = NULL;

    if (head->next == NULL)
    { // only one node
        printf("\nDeleted record: %s\n", head->usn);
        free(head);
        head = NULL;
        return;
    }

    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    printf("\nDeleted record: %s\n", temp->usn);
    free(temp);
    prev->next = NULL;
}

// d) Insert at front (Stack Push)
void insertFront() 
{
    char usn[20], name[50], program[30], phone[15];
    int sem;


    NODE newNode = createNode();
    newNode->next = head;
    head = newNode;
}

// d) Delete at front (Stack Pop)
void deleteFront() 
{
    if (head == NULL) 
    {
        printf("\nList is empty. Nothing to delete.\n");
        return;
    }

    NODE temp = head;
    printf("\nDeleted record: %s\n", head->usn);
    head = head->next;
    free(temp);
}

// Main menu
int main() 
{
    int choice, n;

    while (1) 
    {
        printf("\n===== STUDENT DATABASE MENU =====\n");
        printf("1. Create List (Front Insertion)\n");
        printf("2. Display List & Count\n");
        printf("3. Insert at End\n");
        printf("4. Delete from End\n");
        printf("5. Insert at Front (Stack Push)\n");
        printf("6. Delete from Front (Stack Pop)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
        case 1: printf("Enter number of students: "); 
                scanf("%d", &n);
                createList(n);  break;
        case 2: displayList();  break;
        case 3: insertEnd(); break;
        case 4: deleteEnd(); break;
        case 5: insertFront(); break;
        case 6: deleteFront(); break;
        case 7: printf("Exiting program.\n"); exit(0);
        default:  printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}