//
// Created by plyus_000 on 22.11.2015.
//

#ifndef LABAKILLER_PRINTTREES_H
#define LABAKILLER_PRINTTREES_H

#include "Tree.h"
#include "../Dotter/Dotter.h"

void NodePrint(int num, Node_t* node)
{
    dtNodeStyle ().shape ("box")
            .style ("rounded, filled");
    char text [130] = "";

    switch(node->type)
    {
        case (NUM):
        {
            dtNodeStyle ().fontcolor ("black") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                    .color     ("black") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                    .fillcolor ("#86E992");  //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!

            sprintf (text, "#%d\n%g", num, node->data);

            break;
        }

        case (VAR):
        {
            dtNodeStyle ().fontcolor ("black") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                    .color     ("black") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                    .fillcolor ("#6BCAE5");  //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!

            sprintf (text, "#%d\n%c", num, (char)node->data);
            break;
        }

        case (OP):
        {
            dtNodeStyle ().fontcolor ("black") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                    .color     ("black") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                    .fillcolor ("#DE7B97");  //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!

            int c;
            switch ((char)node->data)
            {
                case ADD: c = '+'; break;
                case SUB: c = '-'; break;
                case MUL: c = '*'; break;
                case DIV: c = '/'; break;
                case POW: c = '^'; break;
                case LN: c = 'ln'; break;
                case EXP: c = 'exp'; break;
                case SQRT: c = 'sqrt'; break;
                case LOG: c = 'log'; break;
                case SIN: c = 'sin'; break;
                case TG: c = 'tg'; break;
                case COS: c = 'cos'; break;
                case ASIN: c = 'asin'; break;
                case ACOS: c = 'acos'; break;
                case ATG: c = 'atg'; break;
                case SQR: c = 'sqr'; break;
                default: c = 'err'; break;
            }

            char c1 = c % 256;
            c = c / 256;
            char c2 = c % 256;
            c = c / 256;
            char c3 = c % 256;
            c = c / 256;
            char c4 = c % 256;
            c = c / 256;

            if (c4 > 0)
                sprintf (text, "#%d\n%c%c%c%c", num, c4, c3, c2, c1);
            else if (c3 > 0)
                sprintf (text, "#%d\n%c%c%c", num, c3, c2, c1);
            else if (c2 > 0)
                sprintf (text, "#%d\n%c%c", num, c2, c1);
            else
                sprintf (text, "#%d\n%c", num, c1);

            break;
        }

        default:
        {
            dtNodeStyle ().shape ("egg")
                    .color ("yellow")
                    .style ("filled");

            sprintf (text, "%d\nError! Type = %d", num, node->type);
            break;
        }
    }

    dtNode (num, text);
}

int count;
void TreePrint_Sys (Node_t* Tree)
{
    NodePrint(count, Tree);


    if (Tree->left)
    {
        count++;
        TreePrint_Sys(Tree->left);
    }

    if (Tree->right)
    {
        count++;
        TreePrint_Sys(Tree->right);
    }
}

void TreeLinks(Node_t* Tree)
{
    int current = count;
    if (Tree->left)
    {
        count++;
        dtLink(current, count);
        TreeLinks(Tree->left);
    }

    if (Tree->right)
    {
        count++;
        dtLink(current, count);
        TreeLinks(Tree->right);
    }
}

void TreePrint(Node_t* Tree)
{
    size_t size = TreeSize(Tree);
    dtBegin ("TreeDump.dot");
    count = 0;
    TreePrint_Sys(Tree);
    count = 0;
    TreeLinks(Tree);
    dtEnd ();
    dtRender ("TreeDump.dot");
}

#endif //LABAKILLER_PRINTTREES_H
