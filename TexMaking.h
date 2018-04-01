//
// Created by plyus_000 on 04.12.2015.
//

#ifndef LABAKILLER_TEXMAKING_H
#define LABAKILLER_TEXMAKING_H
#include "../OneginSorting/myHeader.h"
#include "Derivatives.h"
#include <time.h>

FILE* makeNewTexFile()
{
    size_t sizeTexStart;
    String* texStart = ReadAllFile("texDocument.shab", &sizeTexStart);
    FILE* output = fopen("document.tex", "wb");
    if (WriteInFile(output, texStart, sizeTexStart) == 0)
        return output;
    else return NULL;
}

void PrintUsefulLiterature(FILE* output);
void endTexFile(FILE* output)
{
    PrintUsefulLiterature(output);
    fprintf(output, "\n\\end{document}");
    fclose(output);
}

typedef struct _comment
{
    String* comment;
    size_t size;
} simple_comment;


typedef struct __comment
{
    String* comment[2];
    size_t size;
} double_comment;

/*!
 * Инициализирует массив односложных вводных конструкций. Возвращает указатель на полученный массив
 * в случае успеха. Иначе возвращает NULL и ставит errno в некоторое положение.
 */
simple_comment* InitSimple_comment(const char* name)
{
    if (!name)
    {
        errno = ENXIO;
        return NULL;
    }

    simple_comment* com = (simple_comment*)calloc(1, sizeof(*com));

    if (!com)
    {
        errno = ENOMEM;
        return NULL;
    }

    com->comment = ReadAllFile(name, &com->size);

    if (com->comment)
        return com;
    else
    {        //errno и так уже в необходимом положении
        return NULL;
    }
}

/*!
 * Инициализирует массив двусложных вводных конструкций. Возвращает указатель на полученный массив
 * в случае успеха. Иначе возвращает NULL и ставит errno в некоторое положение.
 */
double_comment* InitDouble_comment(const char* name)
{
    if (!name)
    {
        errno = ENXIO;
        return NULL;
    }

    size_t size;
    String* temp = ReadAllFile(name, &size);

    if (!temp)
    {
        //errno и так уже в необходимом положении
        return NULL;
    }

    /*if (size % 2 == 1)
    {
        errno = EIO;
        return NULL;
    }*/

    double_comment* comment = (double_comment*) calloc(1, sizeof(*comment));
    if (!comment)
    {
        errno = ENOMEM;
        return NULL;
    }
    comment->comment[0] = (String*) calloc(size / 2, sizeof(*comment->comment[0]));
    comment->comment[1] = (String*) calloc(size / 2, sizeof(*comment->comment[1]));

    if (!comment->comment[0] || !comment->comment[1])
    {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0; i < size / 2; i++)
    {
        comment->comment[0][i] = temp[2 * i];
        comment->comment[1][i] = temp[2 * i + 1];
    }

    comment->size = size / 2;

    return comment;
}

double_comment* Double_comment;

#define first_com Double_comment->comment[0]
#define second_com Double_comment->comment[1]

simple_comment* Simple_comment;

char* getSimpleComment()
{
    if (!Simple_comment)
    {
        errno = ENXIO;
        return NULL;
    }

    if (!Simple_comment->comment)
    {
        errno = ENXIO;
        return NULL;
    }

    return Simple_comment->comment[rand() % Simple_comment->size].str;
}

void getDoubleComment(char** first, char** second)
{
    if(!first || !second)
    {
        errno = EIO;
        return;
    }
    if (!Double_comment)
    {
        errno = ENXIO;
        (*first) = NULL;
        (*second) = NULL;
        return;
    }

    if (!first_com)
    {
        errno = ENXIO;
        (*first) = NULL;
        (*second) = NULL;
        return;
    }

    if (!second_com)
    {
        errno = ENXIO;
        (*first) = NULL;
        (*second) = NULL;
        return;
    }

    int index = rand() % Double_comment->size;

    (*first) = first_com[index].str;
    (*second) = second_com[index].str;
}

char SimpleCommentDefault[100] = "После недолгих преобразований получаем:";
char DoubleCommentFirstDefault[100] = "Очевидно, что ";
char DoubleCommentSecondDefault[100] = "равно ";

char* getSimple_P()
{
    char* temp = getSimpleComment();
    if (temp && !errno)
        return temp;

    errno = 0;
    return SimpleCommentDefault;
}

void getDouble_P(char** first, char** second)
{
    getDoubleComment(first, second);

    if (!(*first) || !(*second) || errno)
    {
        errno = 0;
        (*first) = DoubleCommentFirstDefault;
        (*second) = DoubleCommentSecondDefault;
    }
    return;
}

void _OutFormulaInFile(FILE* output, Node_t* tree)
{
    if (!output || !tree)
        return;

    switch(tree->type)
    {
        case (NUM):
        {
            fprintf(output, "%g", tree->data);
            break;
        }
        case (VAR):
        {
            fprintf(output, "%c", (char) tree->data);
            break;
        }
        case (OP):
        {

            switch ((char)tree->data)
            {
                case ADD:   _OutFormulaInFile(output, tree->left);
                            fprintf(output, " + ");
                            _OutFormulaInFile(output, tree->right);
                            break;
                case SUB:   _OutFormulaInFile(output, tree->left);
                            fprintf(output, " - ");
                            _OutFormulaInFile(output, tree->right);
                            break;
                case MUL:
                            if(tree->left->type == NUM && tree->left->data == -1)
                            {
                                fprintf(output, "-");

                                if(tree->right->type == OP)
                                    fprintf(output, "(");
                                _OutFormulaInFile(output, tree->right);
                                if(tree->right->type == OP)
                                    fprintf(output, ")");
                                break;
                            }

                            if(tree->right->type == NUM && tree->right->data == -1)
                            {
                                fprintf(output, "-");

                                if(tree->left->type == OP)
                                    fprintf(output, "(");
                                _OutFormulaInFile(output, tree->left);
                                if(tree->left->type == OP)
                                    fprintf(output, ")");
                                break;
                            }

                            if(tree->left->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->left);
                            if(tree->left->type == OP)
                                fprintf(output, ")");

                            if ((tree->left->type == OP || tree->right->type == OP)
                                    || (tree->left->type == NUM && tree->right->type == NUM))
                                fprintf(output, " \\cdot ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case DIV:   fprintf(output, "\\frac{");
                            _OutFormulaInFile(output, tree->left);
                            fprintf(output, "}{");
                            _OutFormulaInFile(output, tree->right);
                            fprintf(output, "}");
                            break;
                case POW:   if(tree->left->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->left);
                            if(tree->left->type == OP)
                                fprintf(output, ")");

                            fprintf(output, " ^ ");

                            if(tree->right->type == OP)
                                fprintf(output, "{");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, "}");
                            break;
                case LN:    fprintf(output, " \\ln ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case EXP:   fprintf(output, " \\exp ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case SQRT:  fprintf(output, " \\sqrt ");
                            fprintf(output, "{");
                            _OutFormulaInFile(output, tree->right);
                            fprintf(output, "}");
                            break;
                case LOG:   fprintf(output, "\\log( ");
                            _OutFormulaInFile(output, tree->left);
                            fprintf(output, " , ");
                            _OutFormulaInFile(output, tree->right);
                            fprintf(output, ")");
                            break;
                case SIN:   fprintf(output, " \\sin ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case TG:    fprintf(output, " \\tan ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case COS:   fprintf(output, " \\cos ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case ASIN:  fprintf(output, " \\arcsin ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case ACOS:  fprintf(output, " \\arccos ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case ATG:   fprintf(output, " \\arctan ");

                            if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            break;
                case SQR:   if(tree->right->type == OP)
                                fprintf(output, "(");
                            _OutFormulaInFile(output, tree->right);
                            if(tree->right->type == OP)
                                fprintf(output, ")");
                            fprintf(output, "^ 2");
                            break;
                default:    printf("Some problems with printout: %g type of operation has found",
                                   tree->data);
                            break;
            }
            break;
        }
        default: printf("Some problems with printout: %d type of node has found", tree->type);
    }
    return;
}

Node_t* OutFormulaInFile(FILE* output, Node_t* tree)
{
    fprintf(output,"\\begin{center}$");
    _OutFormulaInFile(output, tree);
    fprintf(output,"$ \\end{center}");
    return tree;
}

Node_t* OutFormulaInFileF(FILE* output, Node_t* diffNode, Node_t* node)
{
    char* first, *second;
    getDouble_P(&first, &second);
    fprintf(output, first);
    fprintf(output, "\n");
    OutFormulaInFile(output, node);
    fprintf(output, second);
    fprintf(output, "\n");
    OutFormulaInFile(output, diffNode);
    //fprintf(output, "\\\\");
    return diffNode;
}

Node_t* OutFormulaInFileComment(FILE* output, Node_t* tree)
{
    fprintf(output, "\\\\%s\n", getSimple_P());
    fprintf(output,"\\\\$");
    _OutFormulaInFile(output, tree);
    fprintf(output,"$\\\\");
    return tree;
}

void PrintUsefulLiterature(FILE* output)
{
    size_t sizeLit;
    String* literature = ReadAllFile("Literature.txt", &sizeLit);
    if (errno)
    {
        errno = 0;
        fprintf(output, "{\\LARGE \\bfseries \\center Спасибо за внимание!\\\\}");
        return;
    }
    fprintf(output, "{\\LARGE \\bfseries \\center Список использованной литературы:\\\\}");
    WriteInFile(output, literature, sizeLit);
    fprintf(output, "{\\LARGE \\bfseries \\center Спасибо за внимание!\\\\}");
}

void BeforeSimplification(FILE* output)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Упростим полученную производную. \\\\}");
}

void BeforeDiff(FILE* output, char x)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Вычислим производную функции по переменной %c \\\\}", x);
}

void DerivativeInFile(FILE* output, Node_t* tree, Node_t* diff, char x)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Итак, производная функции равна \\\\}");
    fprintf(output,"\\begin{center}$\\frac{d(");
    _OutFormulaInFile(output, tree);
    fprintf(output, ")}{d%c} = ", x);
    _OutFormulaInFile(output, diff);
    fprintf(output,"$ \\end{center}");
}


void _OutNumbersInFile(FILE* output, Node_t* tree)
{
    if (!output || !tree)
        return;

    switch(tree->type)
    {
        case (NUM):
        {
            fprintf(output, "%g", tree->data);
            break;
        }
        case (VAR):
        {
            fprintf(output, "%g", Values[(char)tree->data].value);
            break;
        }
        case (OP):
        {

            switch ((char)tree->data)
            {
                case ADD:   _OutNumbersInFile(output, tree->left);
                    fprintf(output, " + ");
                    _OutNumbersInFile(output, tree->right);
                    break;
                case SUB:   _OutNumbersInFile(output, tree->left);
                    fprintf(output, " - ");
                    _OutNumbersInFile(output, tree->right);
                    break;
                case MUL:
                    if(tree->left->type == NUM && tree->left->data == -1)
                    {
                        fprintf(output, "-");

                        if(tree->right->type == OP)
                            fprintf(output, "(");
                        _OutNumbersInFile(output, tree->right);
                        if(tree->right->type == OP)
                            fprintf(output, ")");
                        break;
                    }

                    if(tree->right->type == NUM && tree->right->data == -1)
                    {
                        fprintf(output, "-");

                        if(tree->left->type == OP)
                            fprintf(output, "(");
                        _OutNumbersInFile(output, tree->left);
                        if(tree->left->type == OP)
                            fprintf(output, ")");
                        break;
                    }

                    if(tree->left->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->left);
                    if(tree->left->type == OP)
                        fprintf(output, ")");


                    fprintf(output, " \\cdot ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case DIV:   fprintf(output, "\\frac{");
                    _OutNumbersInFile(output, tree->left);
                    fprintf(output, "}{");
                    _OutNumbersInFile(output, tree->right);
                    fprintf(output, "}");
                    break;
                case POW:   if(tree->left->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->left);
                    if(tree->left->type == OP)
                        fprintf(output, ")");

                    fprintf(output, " ^ ");

                    if(tree->right->type == OP)
                        fprintf(output, "{");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, "}");
                    break;
                case LN:    fprintf(output, " \\ln ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case EXP:   fprintf(output, " \\exp ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case SQRT:  fprintf(output, " \\sqrt ");
                    fprintf(output, "{");
                    _OutNumbersInFile(output, tree->right);
                    fprintf(output, "}");
                    break;
                case LOG:   fprintf(output, "\\log( ");
                    _OutNumbersInFile(output, tree->left);
                    fprintf(output, " , ");
                    _OutNumbersInFile(output, tree->right);
                    fprintf(output, ")");
                    break;
                case SIN:   fprintf(output, " \\sin ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case TG:    fprintf(output, " \\tan ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case COS:   fprintf(output, " \\cos ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case ASIN:  fprintf(output, " \\arcsin ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case ACOS:  fprintf(output, " \\arccos ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case ATG:   fprintf(output, " \\arctan ");

                    if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    break;
                case SQR:   if(tree->right->type == OP)
                        fprintf(output, "(");
                    _OutNumbersInFile(output, tree->right);
                    if(tree->right->type == OP)
                        fprintf(output, ")");
                    fprintf(output, "^ 2");
                    break;
                default:    printf("Some problems with printout: %g type of operation has found",
                                   tree->data);
                    break;
            }
            break;
        }
        default: printf("Some problems with printout: %d type of node has found", tree->type);
    }
    return;
}

void OutNumbersInFile(FILE* output, Node_t* tree)
{
    fprintf(output,"\\begin{center}$");
    _OutNumbersInFile(output, tree);
    fprintf(output,"$ \\end{center}");
}

double CalcDer(Node_t* tree);
double CalculatedInFile(FILE* output, Node_t* diffTree)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Вычислим конкретное значение по полученной формуле \\\\}");
    fprintf(output,"\\begin{center}$");
    _OutNumbersInFile(output, diffTree);
    double result = CalcDer(diffTree);
    fprintf(output, " = %g", result);
    fprintf(output,"$ \\end{center}");
    return result;
}

#define SQR_FUNCT(x) (x)*(x)
double PrintingFunctError(FILE* output, Node_t* tree)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Вычислим погрешность значения исходной формулы \\\\}");
    fprintf(output,"\\begin{center}$");
    fprintf(output, "\\Delta(");
    _OutFormulaInFile(output, tree);

    fprintf(output, ") = \\sqrt{");

    for(int i = 0; i < nVars - 1; i++)
    {
        fprintf(output,"(\\frac{d(");
        _OutFormulaInFile(output, tree);
        fprintf(output, ")}{d%c} \\cdot \\Delta(%c)) ^ {2} + ", Variables[i], Variables[i]);
    }

    fprintf(output,"(\\frac{d(");
    _OutFormulaInFile(output, tree);
    fprintf(output, ")}{d%c} \\cdot \\Delta(%c)) ^ {2}", Variables[nVars - 1], Variables[nVars - 1]);

    fprintf(output,  "} = \\sqrt{");
    double error = 0;
    for(int i = 0; i < nVars - 1; i++)
    {
        fprintf(output,"(%g \\cdot %g)^2 + ", Values[Variables[i]].diffError, Values[Variables[i]].error);
        error += SQR_FUNCT(Values[Variables[i]].diffError) * SQR_FUNCT(Values[Variables[i]].error);

    }

    fprintf(output,"(%g \\cdot %g)^2", Values[Variables[nVars - 1]].diffError, Values[Variables[nVars - 1]].error);
    error += SQR_FUNCT(Values[Variables[nVars - 1]].diffError) * SQR_FUNCT(Values[Variables[nVars - 1]].error);

    error = sqrt(error);
    fprintf(output, "} = %g", error);

    fprintf(output,"$ \\end{center}");
    return error;
}
#undef SQR_FUNCT

void PrintStartFunction(FILE* output, Node_t* tree, bool calc)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Исходная формула: \\\\}");
    fprintf(output,"\\begin{center}$");
    _OutFormulaInFile(output, tree);
    if (calc)
    {
        fprintf(output, " = ");
        _OutNumbersInFile(output, tree);
        fprintf(output, " = %g", CalcDer(tree));
    }
    fprintf(output,"$\\end{center}");
}

void PrintFileResult(FILE* output, Node_t* tree, double error)
{
    fprintf(output, "{\\LARGE \\bfseries \\center Таким образом получаем, что \\\\}");
    fprintf(output,"\\begin{center}$");
    _OutFormulaInFile(output, tree);
    double result = CalcDer(tree);
    fprintf(output, " = %g \\pm (%g)", result, error);
    fprintf(output,"$\\end{center}");
    fprintf(output, "{\\large \\bfseries \\center "
            "Т.е полученная величина известна нам с ошикой в не более чем %g\\%%\\\\}", error / result * 100);
}
#endif //LABAKILLER_TEXMAKING_H

