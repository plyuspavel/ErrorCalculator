//
// Created by plyus_000 on 22.11.2015.
//

#ifndef LABAKILLER_TREE_H
#define LABAKILLER_TREE_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct elem
{
    int type;
    double data;

    elem* left;
    elem* right;
    elem* parent;

} Node_t;

enum types
{
    NO = 0,
    NUM = 1,
    OP = 2,
    VAR = 3
};

enum operators
{
    NOP = 0,
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    POW = 5,
    LN = 6,
    EXP = 7,
    SQRT = 8, //!
    LOG = 9,
    SIN = 10,
    TG = 11,
    COS = 12,
    ASIN = 13,
    ACOS = 14,
    ATG = 15,
    SQR = 16,
    LAST_OP
};

int Node_t_OK(Node_t* root)
{
    if (!root)
        return 0;

    if (root->left)
    {
        if (!Node_t_OK(root->left))
            return 0;                      //Нужны ли мне родители?
    }

    if (root->right)
    {
        if (!Node_t_OK(root->right))
            return 0;                      //Нужны ли мне родители?
    }

    if (root->type == types::NO)
    { return 0;}

    if (root->type == types::OP)
    {
        if (root->data - trunc(root->data) != 0)
            { return 0;}

        if (root->data > operators:: LAST_OP || root->data < operators::NOP)
            {return 0;}

        if (!root->right && root->data != NOP)
            { return 0;}
    }

    if (root->type == types:: VAR || root->type == types:: NUM)
        if (root->left || root->right)
            return 0;

    return 1;
}

Node_t* Node_t_ctor(int type, double data, Node_t* left, Node_t* right)
{
    Node_t* root = (Node_t*) malloc(sizeof(Node_t));

    if(!root)
        return NULL;

    root->type = type;
    root->data = data;
    root->left = left;
    root->right = right;
    return root;
}
#define CreateNode(type, data, left, right) Node_t_ctor(type, data, left, right)
#define _OP(data, left, right) Node_t_ctor(OP, data, left, right)
#define _NUM(num) Node_t_ctor(NUM, num, NULL, NULL)
#define _VAR(var) Node_t_ctor(VAR, var, NULL, NULL)



void Node_t_dtor(Node_t** root)
{
    if (!root)
        return;
    if(!(*root))
        return;
    if(!Node_t_OK(*root))
    {printf("\nWARNING!\n"); return;}

    if ((*root)->left) Node_t_dtor(&(*root)->left);
    if ((*root)->right) Node_t_dtor(&(*root)->right);
    (*root)->parent = NULL;
    (*root)->type = types:: NO;
    //printf("%g %X\n", (*root)->data, (*root));
    (*root)->data = -7;
    free(*root);
    //(*root) = NULL;
    return;
}

void TreePrint_Infix(Node_t* root)
{
    if (!root)
        return;
    printf("(");
    if (root->left) TreePrint_Infix(root->left);
    printf("%g",root->data);
    if (root->right) TreePrint_Infix(root->right);
    printf(")");
    return;
}

size_t TreeSize (Node_t* tree)
{
    if (!tree)
        return 0;

    size_t size = 1;
    if (tree->left) size += TreeSize(tree->left);
    if (tree->right) size += TreeSize(tree->right);
    return size;
}

#endif //LABAKILLER_TREE_H
