#include <memory.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>

struct node
{
    int data;
    node* left;
    node* right;
};

int treeSize(const node* const tree)
{
    if(!tree)
        return 0;

    return 1 + treeSize(tree->left) + treeSize(tree->right);
}

void printTreeHelper(const node* const tree)
{
    if(!tree) {
        return;
    }
    printTreeHelper(tree->left);
    std::cout << tree->data <<" ";
    printTreeHelper(tree->right);
}

void printTree(const node* const tree)
{
    if(!tree) {
        return;
    }
    printTreeHelper(tree);
    std::cout <<std::endl;
}

void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree)) {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;

        temp->data = val;
        *tree = temp;
        return;
    }
    if(val < (*tree)->data) {
        insert(&(*tree)->left, val);
    } else if(val > (*tree)->data) {
        insert(&(*tree)->right, val);
    }
}

void remove(node ** tree, int val)
{   
    if(!(*tree)) {
        return;
    }
    
    if(val == (*tree)->data) {
        if(!(*tree)->left && !(*tree)->right) {
            delete *tree;
            *tree = NULL;
        } else if((*tree)->right && !(*tree)->left) {
            node* right = (*tree)->right;
            delete *tree;
            *tree = right;
        } else if((*tree)->left && !(*tree)->right) {
            node* left = (*tree)->left;
            delete *tree;
            *tree = left;
        } else {
            if(!(*tree)->right->left) {
                (*tree)->right->left = (*tree)->left;
                node* rightNode =  (*tree)->right; 
                delete *tree;
                *tree = rightNode;
                return;
            }

            /* Наименьший нод из правого поддерева будет новым текущим нодом.
             * при этом правое поддерево этого наименьшего нода достается его родителю 
             * как левый нод
             */

            node *smallestRight = (*tree)->right;
            node *smallestRightParent;

            while(smallestRight->left) {
                smallestRightParent = smallestRight;
                smallestRight = smallestRight->left;
            }

            smallestRightParent->left = smallestRight->right;
            smallestRight->right = (*tree)->right;
            smallestRight->left = (*tree)->left;
            delete *tree;
            *tree = smallestRight;
        }

    } else if(val < (*tree)->data) {
        remove(&(*tree)->left, val);
    } else {
        remove(&(*tree)->right, val);
    }
}


int main()
{   
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    {
        std::cout <<"Удаление элемента без потомков" <<std::endl;
        node* tree = NULL;
        insert(&tree, 1);
        printTree(tree);

        int size = treeSize(tree);
        remove(&tree, 1);
        printTree(tree);
        assert(treeSize(tree) == size - 1);
    }

    {
        std::cout <<"Удаление элемента с одним потомком" <<std::endl;
        node* tree = NULL;
        insert(&tree, 1);
        insert(&tree, 2);
        printTree(tree);

        int size = treeSize(tree);
        remove(&tree, 1);
        printTree(tree);
        assert(treeSize(tree) == size - 1);
    }

    {
        std::cout <<"Удаление элемента с двумя потомками" <<std::endl;
        node* tree = NULL;
        insert(&tree, 1);
        insert(&tree, 2);
        insert(&tree, 0);
        printTree(tree);
        
        int size = treeSize(tree);
        remove(&tree, 1);
        printTree(tree);
        assert(treeSize(tree) == size - 1);
    }

    {
        std::cout <<"Удаление элемента с двумя потомками, у которых есть свои потомки" <<std::endl;
        node* tree = NULL;
        insert(&tree, 10);

        insert(&tree, 20);
        insert(&tree, 21);
        insert(&tree, 19);

        insert(&tree, 5);
        insert(&tree, 7);
        insert(&tree, 4);

        printTree(tree);

        int size = treeSize(tree);
        remove(&tree, 10);
        printTree(tree);
        assert(treeSize(tree) == size - 1);
    }


    {
        std::cout <<"Самый сложный случай" <<std::endl;
        node* tree = NULL;
        insert(&tree, 30);
        insert(&tree, 10);
        insert(&tree, 20);
        insert(&tree, 25);
        insert(&tree, 15);
        insert(&tree, 13);
        insert(&tree, 11);
        insert(&tree, 12);
        insert(&tree, 0);
        printTree(tree);
        
        int size = treeSize(tree);
        remove(&tree, 10);
        printTree(tree);
        assert(treeSize(tree) == size - 1);
    }

    return 0;
}