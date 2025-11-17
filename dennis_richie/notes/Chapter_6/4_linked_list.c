// this is a chained struct, whr each struct has a member to another struct, of same data type.

# include <stdlib.h>
# include <stdio.h>

struct linked_list{
    int data;
    struct linked_list * node;  // creates a arr (more like chain)
};

void insert_(struct linked_list * p, int val){
    while (p-> node)
        p = p-> node;
    p-> data = val;
    p-> node = (struct linked_list *) malloc( sizeof(struct linked_list));
}

void tree_print(struct linked_list * p){
    struct linked_list * q;
    int i = 0;
    while (p->node){
        printf("Node %d, value: %d\n", i, p-> data);
        p = p-> node;
        i++;
    }
}

struct linked_list * delete_all(struct linked_list * p){
    if (p-> node){
        free(delete_all(p-> node));
        p -> node = 0;
        return p;
        }
    else
        free(p);
}

struct linked_list * delete_node_with_element(struct linked_list * p, int in_var){
    struct linked_list * parent = 0;
    struct linked_list * root = p;
    while (p-> node){
        if (p-> data != in_var){
            parent = p;
            p = p-> node;
        }
        else
            break;
    }
    if (p-> data == in_var){
        printf("Deleting %d\n", in_var);
        if (parent == 0){
            root = p->node;
            free(p);
        }
        else{
            parent -> node = p -> node;
            free(p);
        }
    }
    return root;
}
int main(){
    struct linked_list * root =  (struct linked_list *) malloc(sizeof(struct linked_list));

    int command;
    printf("Enter command: ");
    scanf("%d", &command);
    int in_var;


    while (command<5 && command >0){

        switch (command){
            case 1:
                printf("Enter val to insert: ");
                scanf("%d", &in_var);
                insert_(root, in_var);
                break;
            case 2:
                tree_print(root);
                break;
            case 3:
                printf("Enter to delete corresponding node a val: ");
                scanf("%d", &in_var);
                root = delete_node_with_element(root, in_var);
                break;
            case 4:
                delete_all(root);
                break;
        }
        printf("Enter command: ");
        scanf("%d", &command);
    }

    tree_print(root);
}