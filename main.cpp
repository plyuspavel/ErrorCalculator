#include "RecursiveDescent.h"
#include "PrintTrees.h"
#include "Derivatives.h"

const int MAX_NAME = 1000;

int main()
{
    srand((unsigned) time(0));
    printf("Enter new formula:\n");

    char string[MAX_NAME] = "";
    scanf("%s", string);

    Node_t* tree = getG0(string);

    if (!tree)
        return 1;

    FILE* output = makeNewTexFile();

    Simple_comment = InitSimple_comment("simple_comments.txt");  //Инициализация массивов комментариев
    Double_comment = InitDouble_comment("double_comments.txt");

    bool calc = false;

    printf("Would you like to calculate your function and it's error\n");
    scanf("%s", string);

    if (!strcmp(string ,"yes") || !strcmp(string, "y"))
        calc = true;

    if (calc)
        for (int i = 0; i <nVars; i++)
        {
            printf("Please, enter the value of %c:", Variables[i]);
            scanf("%lg +- %lg", &Values[Variables[i]].value, &Values[Variables[i]].error);
        }

    PrintStartFunction(output, tree, calc);


    for (int i = 0; i < nVars; i++)
    {
        BeforeDiff(output, Variables[i]);
        Node_t* diffTree = diff(tree, Variables[i], output);
        BeforeSimplification(output);
        simplification(&diffTree, output);
        DerivativeInFile(output, tree, diffTree, Variables[i]);
        if (calc)
            Values[Variables[i]].diffError = CalculatedInFile(output, diffTree);
        Node_t_dtor(&diffTree);
    }

    if (calc)
    {
        double error = PrintingFunctError(output, tree);
        PrintFileResult(output, tree, error);
    }
    //TreePrint(tree);

    Node_t_dtor(&tree);
    endTexFile(output);
    system("pdflatex.exe -synctex=1 -interaction=nonstopmode \"document\".tex");
    system("document.pdf");


    return 0;
}

