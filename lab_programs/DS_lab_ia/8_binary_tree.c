# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct tree {
    char isbn[14];  // contains key, the tree, which is at 1-D ptr chain, such each node has pointers to 2 nodes, a less than and greater than. All chilren of its lesser then will also be lesser than the cur node. 
    char btitle[14];    // associated value to node.
    struct tree * rlink;
    struct tree * llink;
};

typedef struct tree TNODE;

# define TRAVERSE(A, B, C) if (A == 0) printf("Tree is empty\n"); else{ printf(C); B(A); }  // A is head; B is fn to traverse; C is 

TNODE * search(TNODE * root, char * key){
    if (root!= 0){
        if (strcmp(key, root->isbn) == 0)
            return root;
        else if (strcmp(key, root->isbn) < 0)
            return search(root->llink, key);
        else
            return search(root->rlink, key);
    }
    else
        return 0;
}

void preorder(TNODE * root){
    if (root != 0){
        printf("%s: %s\n", root->isbn, root->btitle);
        preorder(root->llink);
        preorder(root->rlink);
    }
}

void postorder(TNODE * root){
    if (root != 0){
        postorder(root -> llink);
        postorder(root->rlink);
        printf("%s: %s\n", root->isbn, root->btitle);
    }
}

void inorder(TNODE * root){
    if (root != 0){
        postorder(root -> llink);
        printf("%s: %s\n", root->isbn, root->btitle);
        postorder(root->rlink);
    }
}

TNODE * insert(TNODE * root){
    int n, i, cv;
    TNODE * cur, * prev;
    TNODE * new;        // TNODE t = { .rlink = 0, .llink = 0};

    printf("Enter number of nodes: ");
    scanf("%d", &n);
    
    for (int i = 0; i< n; i++){
        new = (TNODE *) malloc(sizeof(TNODE));  
        printf("Enter ISBN and Book-Title: ");
        scanf("%s", new->isbn);         // scanf("%s", t.isbn);
        scanf("%s", new->btitle);       // scanf("%s", t.btitle);
        new->llink = 0;                 // start (* new) = t;
        new->rlink = 0;                 // end

        if (root == 0){
            root = new;
            continue;
        }
        prev = root;
        cur = root;

        while(cur){    // while start (the insertion into tree at right spot)
            prev = cur;
            cv = strcmp(new->isbn, cur->isbn);

            if (cv == 0){
                printf("Redundant data!\n");
                free(new);
                break;
            }
            else if (cv < 0)
                cur = cur -> llink;
            else
                cur = cur -> rlink;
        }   // while end; mostly because cur ptr is now 0.

        if (cv){
            if (cv < 0)
                prev -> llink = new;
            else
                prev -> rlink = new;
        }
    }
    return root;
}

int main(){
    TNODE *root= NULL;
    TNODE * cur = 0;
    int choice, ele;
    char isbn[14];

    while (1) {
        printf("Enter\n1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n5. Search\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: root=insert(root); break;
            case 2: TRAVERSE(root,inorder,"Inorder Traversal\n");
            break;
            case 3: TRAVERSE(root,preorder,"Preorder Traversal\n");
            break;
            case 4: TRAVERSE(root,postorder,"Postorder Traversal\n");
            break;
            case 5: printf("Enter the node to be searched:\n");
            scanf("%s", isbn);
            cur = search(root, isbn);
            if(cur){
                printf("Successful search!!!\n");
                printf("Associated title: %s\n", cur->btitle);
            }
            else
                printf("Unsuccessful search!!!\n");
            break;
            case 6: exit(0);
            }
        }
    }