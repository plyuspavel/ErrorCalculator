//
// Created by plyus_000 on 22.11.2015.
//

#ifndef LABAKILLER_RECURSIVEDESCENT_H
#define LABAKILLER_RECURSIVEDESCENT_H

#include <assert.h>
#include <errno.h>
#include "Tree.h"

struct magnitude
{
    double value;
    double error;
    double diffError;
};

char* s;
char Variables[50] = {};
int nVars = 0;
magnitude Values[255] = {};

int search(char c)
{
    for (int i = 0; i < nVars; i++)
        if (c == Variables[i])
            return 1;

    return 0;
}

void addVar(char c)
{
    Variables[nVars++] = c;
}

Node_t* getP();

Node_t* getN()
{
    int val = 0;
    while ('0' <= *s && *s <= '9')
    {
        val = val * 10 + *s - '0';
        s++;
    }
    if (*s != '.')
        return _NUM(val);

    double drob = 0;
    int count = 1;
    s++;
    while ('0' <= *s && *s <= '9')
    {
        drob = drob + (*s - '0')/pow(10, count++);
        s++;
    }
    drob = drob + val;
    return _NUM(drob);
}

Node_t* getT()
{
    Node_t* node = getP();
    while (*s == '*' || *s == '/')
    {
        int operat = *s;
        s++;
        Node_t* node2 = getP();
        if (operat == '*') node = CreateNode(OP, MUL, node, node2);
        if (operat == '/') node = CreateNode(OP, DIV, node, node2);
    }
    return node;
}

Node_t* getE()
{
    Node_t* node = getT();
    while (*s == '+'|| *s == '-')
    {
        if (*s == '+')
        {
            s++;
            Node_t* node2 = getT();
            node = CreateNode(OP, ADD, node, node2);
        }
        if (*s == '-')
        {
            s++;
            Node_t* node2 = getT();
            node = CreateNode(OP, SUB, node, node2);
        }

    }
    return node;
}


Node_t* getId() //Внимание! Переменная - любой одиночный символ
{
    char c = *s;
    s++;
    if (!search(c))
        addVar(c);

    return _VAR(c);
}

Node_t* getArcsin()
{
    Node_t* node;
    if (!(*s == 'a' && *(s+1) == 'r' && *(s+2) == 'c' && *(s+3) == 's' && *(s+4) == 'i' && *(s+5) == 'n'))
        return _OP(NOP, NULL, NULL);

    s += 6;
    node = getP();
    return _OP(ASIN, NULL, node);
}

Node_t* getArccos()
{
    Node_t* node;
    if (!(*s == 'a' && *(s+1) == 'r' && *(s+2) == 'c' && *(s+3) == 'c' && *(s+4) == 'o' && *(s+5) == 's'))
        return _OP(NOP, NULL, NULL);

    s += 6;
    node = getP();
    return _OP(ACOS, NULL, node);
}

Node_t* getArctan()
{
    Node_t* node;
    if (!(*s == 'a' && *(s+1) == 'r' && *(s+2) == 'c' && *(s+3) == 't' && *(s+4) == 'g'))
        return _OP(NOP, NULL, NULL);

    s += 5;
    node = getP();
    return _OP(ATG, NULL, node);
}

Node_t* getLog()
{
    Node_t* node;
    if(!(*s == 'l' && *(s+1) == 'o' && *(s+2) == 'g'))
        return _OP(NOP, NULL, NULL);

    s += 3;
    assert((*s == '('));
    s++;

    node = getE();
    assert((*s) == ',');
    s++;
    Node_t* node2 = getE();

    assert(*s == ')');
    s++;

    return _OP(LOG, node, node2);
}

Node_t* getSqrt()
{
    Node_t* node;
    if(!(*s == 's' && *(s+1) == 'q' && *(s+2) == 'r' && *(s+3) == 't'))
        return _OP(NOP, NULL, NULL);

    s += 4;

    node = getP();
    return _OP(SQRT, NULL, node);
}



Node_t* getSin()
{
    Node_t* node;
    if (!(*s == 's' && *(s+1) == 'i' && *(s+2) == 'n'))
        return _OP(NOP, NULL, NULL);

    s += 3;

    node = getP();
    return _OP(SIN, NULL, node);
}

Node_t* getCos()
{
    Node_t* node;
    if (!(*s == 'c' && *(s+1) == 'o' && *(s+2) == 's'))
        return _OP(NOP, NULL, NULL);

    s += 3;

    node = getP();
    return _OP(COS, NULL, node);
}

Node_t* getTg()
{
    Node_t* node;
    if (!(*s == 't' && *(s+1) == 'g'))
        return _OP(NOP, NULL, NULL);

    s += 2;

    node = getP();
    return _OP(TG, NULL, node);
}

const double M_E = 2.71828182845904523536;

Node_t* getLn()
{
    Node_t* node;
    if(!(*s == 'l' && *(s+1) == 'n'))
        return _OP(NOP, NULL, NULL);
    s += 2;

    node = getP();

    return _OP(LN, NULL, node);

}

Node_t* getExp()
{
    Node_t* node;
    if (!(*s == 'e' && *(s+1) == 'x' && *(s+2) == 'p'))
        return _OP(NOP, NULL, NULL);

    s += 3;

    node = getP();

    return _OP(EXP, NULL, node);
}

Node_t* getSqr()
{
    Node_t* node;
    if (!(*s == 's' && *(s+1) == 'q' && *(s+2) == 'r'))
        return _OP(NOP, NULL, NULL);

    s += 3;

    node = getP();

    return _OP(SQR, NULL, node);
}

Node_t* getD()
{
    Node_t* node;
    char* test = s;

    node = getArcsin();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getLog();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getLn();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getExp();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getSqrt();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getSin();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getCos();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getTg();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getArctan();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getArccos();
    if (test != s)
        return node;

    Node_t_dtor(&node);
    node = getSqr();
    if (test != s)
        return node;


    return _OP(NOP, NULL, NULL);

}


Node_t* getP()
{
    Node_t* node;
    if (*s == '(')
    {
        s++;
        node = getE();
        assert(*s == ')');
        s++;

    }
    else
    {
        char* test = s;

        node = getD();

        if (test == s)
        {
            Node_t_dtor(&node);
            node = getN();

            if (test == s) {
                Node_t_dtor(&node);
                node = getId();
            }
        }
    }

    if (*s == '^')
    {
        s++;
        Node_t* node2 = getP();
        node = _OP(POW, node, node2);
    }
    return node;

}

Node_t* getG0(const char* string)
{
    s = (char*) string;
    Node_t* node = getE();
    if (*s != 0)
    {
        errno = EIO;
        printf ("Syntax error: '%c' found", *s);
        return NULL;
    }
    return node;
}
#endif //LABAKILLER_RECURSIVEDESCENT_H
