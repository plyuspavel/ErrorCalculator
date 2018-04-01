//
// Created by plyus_000 on 02.12.2015.
//

#ifndef LABAKILLER_DERIVATIVES_H
#define LABAKILLER_DERIVATIVES_H

#include "Tree.h"
#include "TexMaking.h"
#include "RecursiveDescent.h"

Node_t* copy (Node_t* node)
{
    if (node == NULL)
        return NULL;
    return Node_t_ctor(node->type, node->data, copy(node->left), copy(node->right));
}

#define L tree->left
#define R tree->right
#define DATA tree->data

Node_t* diff(Node_t* tree, char var, FILE* output)
{
    switch (tree->type)
    {
        case NUM:
            return _NUM(0);
            break;
        case VAR:
            if (DATA == var)
                return _NUM(1);
            else
                return  _NUM(0);
            break;
        case OP:
        {
            if (DATA == ADD)
                return OutFormulaInFileF(output, _OP(ADD, diff(L, var, output), diff(R, var, output)), tree);

            else if (DATA == SUB)
                return OutFormulaInFileF(output, _OP(SUB, diff(L, var, output), diff(R, var, output)), tree);

            else if (DATA == MUL)
                return OutFormulaInFileF(output, _OP(ADD, _OP(MUL, diff(L, var, output), copy(R)),
                                                 _OP(MUL, copy(L), diff(R, var, output))), tree);

            else if (DATA == DIV)
                return OutFormulaInFileF(output, _OP(DIV, _OP(SUB, _OP(MUL, diff(L, var, output), copy(R)),
                                                                   _OP(MUL, copy(L), diff(R, var, output))),
                                                          _OP(SQR, NULL, copy(R))), tree);

            else if (DATA == LN)
                return OutFormulaInFileF(output, _OP(MUL, _OP(DIV, _NUM(1), copy(R)), diff(R, var, output)), tree);

            else if (DATA == EXP)
                return OutFormulaInFileF(output, _OP(MUL, _OP(EXP, NULL, copy(R)), diff(R, var, output)), tree);

            else if (DATA == LOG)
                //return _OP(DIV, _OP(MUL, _OP(DIV, _NUM(1), copy(L)), diff(L, var)), _OP(LN, NULL, R));
                return OutFormulaInFileF(output, diff(_OP(DIV, _OP(LN, NULL, copy(L)), _OP(LN, NULL, copy(R))), var, output), tree);

            else if (DATA == SIN)
                return OutFormulaInFileF(output, _OP(MUL, _OP(COS, NULL, copy(R)), diff(R, var, output)),tree);

            else if (DATA == COS)
                return OutFormulaInFileF(output, _OP(MUL, _NUM(-1), _OP(MUL, _OP(SIN, NULL, copy(R)), diff(R, var, output))), tree);

            else if (DATA == TG)
                //return _OP(MUL, _OP(DIV, _NUM(1), _OP(MUL, _OP(COS, NULL, copy(R)), _OP(COS, NULL, copy(R)))), diff(R, var, output));
                return OutFormulaInFileF(output, _OP(MUL, _OP(DIV, _NUM(1), _OP(SQR, NULL, _OP(COS, NULL, copy(R)))), diff(R, var, output)), tree);
            else if (DATA == ASIN)
                return OutFormulaInFileF(output, _OP(MUL, _OP(DIV, _NUM(1), _OP(SQRT, NULL, _OP(SUB, _NUM(1), _OP(SQR, NULL, copy(R))))), diff(R, var, output)), tree);

            else if (DATA == ACOS)
                return OutFormulaInFileF(output, _OP(MUL,_NUM(-1),_OP(MUL, _OP(DIV, _NUM(1), _OP(SQRT, NULL, _OP(SUB, _NUM(1), _OP(SQR, NULL, copy(R))))), diff(R, var, output))), tree);

            else if (DATA == ATG)
                return OutFormulaInFileF(output, _OP(MUL, _OP(DIV, _NUM(1), _OP(ADD, _NUM(1), _OP(SQR, NULL, copy(R)))), diff(R, var, output)), tree);

            else if (DATA == POW)
                return OutFormulaInFileF(output, _OP(MUL, copy(tree), diff(_OP(MUL, copy(R), _OP(LN, NULL, copy(L))), var, output)), tree);

            else if (DATA == SQRT)
                return OutFormulaInFileF(output, _OP(MUL, _OP(DIV, _NUM(1), _OP(MUL, _NUM(2), copy(tree))), diff(R, var, output)), tree);

            else if (DATA == SQR)
                return OutFormulaInFileF(output, _OP(MUL, _OP(MUL, _NUM(2), copy(R)), diff(R, var, output)), tree);

            else printf("ERROR! No OPERATOR\n");
        }
        default: return NULL;
    }
}

#include <math.h>
#include <float.h>
#include <limits.h>

#undef DATA

#define LEFT (*tree)->left
#define RIGHT (*tree)->right
#define TYPE (*tree)->type
#define DATA (*tree)->data


int convolution(Node_t** tree, FILE* output)
{
    int result = 0;

    if (!tree)
        return 0;

    if (LEFT) result += convolution(&LEFT, output);
    if (RIGHT) result+= convolution(&RIGHT, output);

    Node_t* temp;
    if ((*tree)->type == OP)
    {
        if (RIGHT && LEFT)
            if (RIGHT->type == NUM && LEFT->type == NUM)
            {
                if (DATA == ADD)
                {
                    temp = _NUM(LEFT->data + RIGHT->data);

                    fprintf(output, getSimple_P());
                    fprintf(output,"\\begin{center}$");
                    _OutFormulaInFile(output, *tree);
                    fprintf(output," = ");

                    Node_t_dtor(tree);
                    (*tree) = temp;

                    _OutFormulaInFile(output, *tree);
                    fprintf(output,"$ \\end{center}");
                    result += 1;
                } else if (DATA == MUL)
                {
                    temp = _NUM(LEFT->data * RIGHT->data);

                    fprintf(output, getSimple_P());
                    fprintf(output,"\\begin{center}$");
                    _OutFormulaInFile(output, *tree);
                    fprintf(output," = ");

                    Node_t_dtor(tree);
                    (*tree) = temp;

                    _OutFormulaInFile(output, *tree);
                    fprintf(output,"$ \\end{center}");

                    result += 1;
                } else if (DATA == SUB)
                {
                    temp = _NUM(LEFT->data - RIGHT->data);

                    fprintf(output, getSimple_P());
                    fprintf(output,"\\begin{center}$");
                    _OutFormulaInFile(output, *tree);
                    fprintf(output," = ");

                    Node_t_dtor(tree);
                    (*tree) = temp;

                    _OutFormulaInFile(output, *tree);
                    fprintf(output,"$ \\end{center}");

                    result += 1;
                } else if (DATA == DIV)
                {
                    temp = _NUM(LEFT->data / RIGHT->data);

                    fprintf(output, getSimple_P());
                    fprintf(output,"\\begin{center}$");
                    _OutFormulaInFile(output, *tree);
                    fprintf(output," = ");

                    Node_t_dtor(tree);
                    (*tree) = temp;

                    _OutFormulaInFile(output, *tree);
                    fprintf(output,"$ \\end{center}");

                    result += 1;
                }
            }
    }

    return result;
}

#define zero(tree) (tree->type == NUM && tree->data == 0)
#define unit(tree) (tree->type == NUM && tree->data == 1)

#define deleteNode Node_t_dtor(tree); \
    (*tree) = temp;\
    result ++;\
    return result;

int dumpySimplific(Node_t** tree)
{
    int result = 0;
    if (!tree)
        return 0;

    if (LEFT) result += dumpySimplific(&LEFT);
    if (RIGHT) result += dumpySimplific(&RIGHT);

    if (TYPE == OP && DATA == MUL)
    {
        if (zero(LEFT) || zero(RIGHT))
        {
            Node_t* temp = _NUM(0);
            deleteNode;
        }

        if (unit(LEFT))
        {
            Node_t* temp = copy(RIGHT);
            deleteNode;
        }

        if (unit(RIGHT))
        {
            Node_t* temp = copy(LEFT);
            deleteNode;
        }
    }

    if (TYPE == OP && DATA == ADD)
    {
        if (zero(LEFT))
        {
            Node_t* temp = copy(RIGHT);
            deleteNode;
        }

        if (zero(RIGHT))
        {
            Node_t* temp = copy(LEFT);
            deleteNode;
        }
    }

    if (TYPE == OP && DATA == SUB)
    {
        if (zero(LEFT))
        {
            Node_t* temp = _OP(MUL, _NUM(-1),copy(RIGHT));
            deleteNode;
        }

        if (zero(RIGHT))
        {
            Node_t* temp = copy(LEFT);
            deleteNode;
        }
    }

    if (TYPE == OP && DATA == DIV)
    {
        if (zero(LEFT))
        {
            Node_t* temp = _NUM(0);
            deleteNode;
        }
    }
    return result;
}

#undef LEFT
#undef RIGHT
#undef TYPE
#undef DATA

void simplification(Node_t** tree, FILE* output)
{
    while(dumpySimplific(tree))
        while(convolution(tree, output))
            ;

    while(convolution(tree, output))
        dumpySimplific(tree);
            ;
}

#undef zero
#undef unit

#define TYPE tree->type
#define DATA tree->data
double CalcDer(Node_t* tree)
{
    if (!Node_t_OK(tree))
    {
        errno = ENXIO;
        return 0;
    }

    if (TYPE == NUM)
        return DATA;

    if (TYPE == VAR)
        return Values[(char)DATA].value;

    if (TYPE == OP)
    {
        if (DATA == ADD)
        {
            double val1 = CalcDer(L);
            double val2 = CalcDer(R);
            return val1 + val2;
        }
        else if (DATA == SUB)
        {
            double val1 = CalcDer(L);
            double val2 = CalcDer(R);
            return val1 - val2;
        }
        else if (DATA == MUL)
        {
            double val1 = CalcDer(L);
            double val2 = CalcDer(R);
            return val1 * val2;
        }
        else if (DATA == DIV)
        {
            double val1 = CalcDer(L);
            double val2 = CalcDer(R);
            if (val2 > DBL_EPSILON)
                return val1 / val2;
            else                            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            {
                errno = EPERM;
                return val1/val2;
            }
        }
        else if (DATA == POW)
        {
            double val1 = CalcDer(L);
            double val2 = CalcDer(R);
            return pow(val1, val2);
        }
        else if (DATA == LN)
        {
            double val1 = CalcDer(R);
            return log(val1);
        }
        else if (DATA == LOG)
        {
            double val1 = CalcDer(L);
            double val2 = CalcDer(R);
            return log(val1)/log(val2);
        }
        else if (DATA == EXP)
        {
            double val1 = CalcDer(R);
            return exp(val1);
        }
        else if (DATA == SQRT)
        {
            double val1 = CalcDer(R);
            return sqrt(val1);
        }
        else if (DATA == SIN)
        {
            double val1 = CalcDer(R);
            return sin(val1);
        }
        else if (DATA == COS)
        {
            double val1 = CalcDer(R);
            return cos(val1);
        }
        else if (DATA == TG)
        {
            double val1 = CalcDer(R);
            return tan(val1);
        }
        else if (DATA == ASIN)
        {
            double val1 = CalcDer(R);
            return asin(val1);
        }
        else if (DATA == ACOS)
        {
            double val1 = CalcDer(R);
            return acos(val1);
        }
        else if (DATA == ATG)
        {
            double val1 = CalcDer(R);
            return atan(val1);
        }
        else if (DATA == SQR)
        {
            double val1 = CalcDer(R);
            return val1*val1;
        }
        else
        {
            errno = EIO;
            return 0;
        }

    }

    return 0;
}


#undef DATA
#undef TYPE
#undef R
#undef L

#endif //LABAKILLER_DERIVATIVES_H
