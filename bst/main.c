#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}*node;
struct Head{
    int count;
    struct Node* root;
    int (*compare)(void* arg1, void* arg2);
}*head;
struct Node* createNode(int data){
    node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
};
struct Head* createBSTree(int (*compare)(int* arg1,int* arg2)){
    head = (struct Head*)malloc(sizeof(struct Head));
    head->count = 0;
    head->root = NULL;
    head->compare = compare;
    return head;
};
bool BST_Insert(struct Head* head, int data);
struct Node* insert(struct Head* head,struct Node* root,struct Node* newptr);
int compare(int arg1,int arg2){
    if(arg1 < arg2)
        return -1;
    else{
        return 0;
    }
}
bool BST_Delete(struct Head* head,int data);
struct Node* deletenode(struct Head* head,struct Node* root,int dataptr,bool* success);
void* BST_Retrieve(struct Head* head,int keyptr);
void* retrieve(struct Head* head,int data,struct Node* root);
void* BST_Traverse(struct Head* tree,void(*process)(int data));
void traverse(struct Node* root,void(*process)(int dataptr));
void process(int data){
    printf("%d ",data);
}

int main()
{
    struct Head* tree = createBSTree(compare);
    int n,number,k;
    scanf("%d",&n);
    do{
        printf("1. Insert a new node.\n2. Delete a node.\n3. Retrieve BST Tree.\n");
        scanf("%d",&k);
        switch(k){
        case 1:
            scanf("%d",&number);
            BST_Insert(tree,number);
            printf("%d\n",tree->count);
            break;
        case 2:
            scanf("%d",&number);
            BST_Delete(tree,number);
            printf("%d\n",tree->count);
            break;
        case 3:
            scanf("%d",&number);
            BST_Traverse(tree,process);
            printf("\n");
            break;

        }
    }while(tree->count < n);
    return 0;
}

bool BST_Insert(struct Head* head, int data){
    struct Node* newptr;
    newptr = (struct Node*)malloc(sizeof(struct Node));
    if(!newptr){
        return false;
    }

    newptr->right = NULL;
    newptr->left = NULL;
    newptr->data = data;

    if(head->count ==0 )
        head->root = newptr;
    else
        insert(head,head->root,newptr);
    head->count++;
    return true;
}

struct Node* insert(struct Head* head,struct Node* root,struct Node* newptr){
    if(!root)
        return newptr;
    if(head->compare(newptr->data,root->data)<0){
        root->left = insert(head,root->left,newptr);
        return root;
    }
    else{
        root->right = insert(head,root->right,newptr);
        return root;
    }
    return root;
}

bool BST_Delete(struct Head* head,int dltkey){
    bool success;
    struct Node* newRoot;
    newRoot = deletenode(head,head->root,dltkey,&success);
    if(success){
        head->root = newRoot;
        head->count--;
        if(head->count == 0)
            head->root = NULL;
    }
    return success;
}

struct Node* deletenode(struct Head* head,struct Node* root,int dataptr,bool* success){
    struct Node* dltptr;
    struct Node* exchptr;
    struct Node* newRoot;
    void* holdptr;
    if(!root){
        *success = false;
        return NULL;
    }
    if(head->compare(dataptr,root->data)<0)
        root->left = deletenode(head,root->left,dataptr,success);
    else if(head->compare(dataptr,root->data)>0)
        root->right = deletenode(head,root->right,dataptr,success);
    else{
        dltptr = root;
        if(!root->left){
            free(root->data);
            newRoot = root->right;
            free(dltptr);
            *success = true;
            return newRoot;
        }
        else{
            if(!root->right){
                newRoot = root->left;
                free(dltptr);
                *success = true;
                return newRoot;
            }
            else{
                exchptr = root->left;
                while(exchptr->right)
                    exchptr = exchptr->right;
                holdptr = root->data;
                root->data = exchptr->data;
                exchptr->data = holdptr;
                root->left = deletenode(head,root->left,exchptr->data,success);
            }
        }
    }
    return root;
}
void* BST_Retrieve(struct Head* head,int keyptr){
    if(head->root)
        return retrieve(head,keyptr,head->root);
    else
        return NULL;
}
void* retrieve(struct Head* head,int data,struct Node* root){
    if(root){
        if(head->compare(data,root->data)<0)
            return retrieve(head,data,root->left);
        else if(head->compare(data,root->data)>0)
            return retrieve(head,data,root->right);
        else
            return root->data;
    }
    else
        return NULL;
}
void* BST_Traverse(struct Head* tree,void(*process)(int data)){
    traverse(tree->root,process);
}
void traverse(struct Node* root,void(*process)(int dataptr)){
    if(root){
        traverse(root->left,process);
        process(root->data);
        traverse(root->right,process);
    }
}
//void PrintBST(struct Node* node){
//    printf("%d ",node->data);
//}
