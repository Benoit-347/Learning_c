# include <stdio.h>
# include <stdlib.h>

struct Employee {
    char ssn[15];
    char name[50];
    char dept[30];
    char phone[15];
    char desig[40];
    float sal;
    struct Employee * llink;
    struct Employee * rlink;
};

typedef struct Employee emp;

# define Accept(X) printf("Enter SSN: "); scanf("%s", X->ssn); printf("Enter name: "); scanf("%s", X-> name); printf("Enter Department: "); scanf("%s", X->dept); printf("Enter phone no: "); scanf("%s", X->phone); printf("Enter designation: "); scanf("%s", X->desig); printf("Enter Salary: "); scanf("%f", &X-> sal); X->llink = 0; X->rlink = 0;

# define Display(X) printf("%s \t|\t%s \t|\t%s \t|\t%s \t|\t%s \t|\t%0.2f\n", X->ssn, X->name, X->dept, X->phone, X->desig, X->sal);


void display(emp * head){
    int count = 1;
    if (head == 0){
        printf("No employee records available\n");
        return;
    }

    emp * temp = head;

    printf("Student records First to Last are: \n");
    while (temp->rlink){
        Display(temp)
        temp = temp-> rlink;
        count++;
    }
    Display(temp)

    printf("Student records Last to First are: \n");
    while(temp){
        Display(temp)
        temp = temp ->llink;
    }
    
    printf("Printed %d no of records!\n", count);
}

emp * createEmployee(emp * head){
    emp * new_emp = 0;
    emp * cur_emp = 0;
    int n;
    printf("Enter number of Records to add: "); scanf("%d", &n);

    for (int i = 0; i<n; i++){
        new_emp = (emp *) malloc(sizeof(emp));
        Accept(new_emp)

        if (head == 0){
            head = new_emp;
            cur_emp = new_emp;
        }
        else{
            cur_emp -> rlink = new_emp;
            new_emp -> llink = cur_emp;
            cur_emp = new_emp;
        }
    }

    return head;
}

emp * insertFront(emp * head){
    emp * new_emp = (emp *) malloc(sizeof(emp));
    emp * temp = head;
    Accept(new_emp)

    head->llink = new_emp;
    new_emp->rlink = head;

    return new_emp;
}

emp * insertEnd(emp * head){
    emp * new_emp = (emp *) malloc(sizeof(emp));
    Accept(new_emp)
    emp * temp = head;

    while (temp->rlink){
        temp = temp -> rlink;
    }
    temp -> rlink = new_emp;
    new_emp -> llink = temp;

    return head;
}

emp * deleteFront(emp * head){
    emp * temp = head;
    head = temp ->rlink;

    free (temp);
    if (head != 0)
        head->llink = 0;
    return head;
}

emp * deleteEnd(emp * head){
    emp * temp = head;
    emp * parent_temp = 0;  // if no. of total nodes from head is 1, parent node is never set. Freeing head, should return 0.

    while (temp->rlink){
        parent_temp = temp;
        temp = temp -> rlink;
    }

    free(temp);
    if (!parent_temp)
        return 0;
    parent_temp -> rlink = 0;
    return head;
}

int main(){
    emp * head = 0;
    head = createEmployee(head);
    display(head);
    head = insertFront(head);
    display(head);
    head = insertEnd(head);
    display(head);
    head = deleteFront(head);
    display(head);
    printf("\nNew output:\n\n");
    deleteEnd(head);
    display(head);
    return 0;
}
