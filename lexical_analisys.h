

void command_input();

void command_identify();

int POSITION_COUNTER = ZERO;


const int first       = 1;
const int second      = 2;
const int third       = 3;
const int fourth      = 4;
const int fifth       = 5;
const int sixth       = 6;
const int seventh     = 7;
const int eighth      = 8;
const int ninth       = 9;
const int tenth       = 10;
const int eleventh    = 11;
const int twelvth     = 12;
const int thirteenth  = 13;
const int fourteenth  = 14;
const int fifteenth   = 15;
const int sixteenth   = 16;
const int seventeenth = 17;
const int eighteenth  = 18;
const int nineteenth  = 19;
const int twenty      = 20;
const int thirty      = 30;
const int fourty      = 40;
const int fifty       = 50;
const int sixty       = 60;
const int seventy     = 70;
const int eighty      = 80;
const int ninety      = 90;
const int twentieth   = 20;
const int thirtieth   = 30;
const int fourtieth   = 40;
const int fiftieth    = 50;
const int sixtieth    = 60;
const int seventieth  = 70;
const int eightieth   = 80;
const int ninetieth   = 90;
const int hundredth   = 100;

int Counter           = ZERO;

struct TREE * answer  = NULL;
struct TREE * Input   = NULL;

//_______________________________________________________LEXICAL_ANALISYS_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void printf_boxes()
{
    int timer;

    for (timer = zero; timer < pointer_for_struct; timer ++)
    {
        if (parced_input[timer] . flag == NUMBER)

            printf("flag = %d ,box_number %d = %d\n", parced_input[timer].flag, timer , parced_input[timer].value);

        if (parced_input[timer] . flag == SYMBOL
        ||  parced_input[timer] . flag == VARIABLE)

            printf("flag = %d ,box_number %d = %c\n", parced_input[timer].flag, timer ,parced_input[timer].symbol);

        if (parced_input[timer] . flag == FUNCTION)

            printf("flag = %d ,box_number %d = %s\n", parced_input[timer].flag, timer , parced_input[timer].Function);
    }
}

void FUNC(double value, char * func, char symbol, int Flag)
{
    if (pointer_for_struct != zero && ((Flag != SYMBOL || symbol == OPENING_BRACKET)
    && ((parced_input[pointer_for_struct - ONE] . flag != SYMBOL
    &&   parced_input[pointer_for_struct - ONE] . flag != FUNCTION)
    ||   parced_input[pointer_for_struct - ONE] . symbol == CLOSING_BRACKET)))

        FUNC(NO_VALUE, NO_FUNCTION, MULTIPLICATION, SYMBOL);

    parced_input[pointer_for_struct] . value       = (double)value;

    parced_input[pointer_for_struct] . symbol      = symbol;

    parced_input[pointer_for_struct] . flag        = Flag;

    parced_input[pointer_for_struct ++] . Function = func;

    return;
}

void number_analyze()
{
    int pointer_for_numbers = zero;

    char functions[FUNCTION_SIZE];

    while (input[pointer_for_input] >= '0' && input[pointer_for_input] <= '9')
    
       functions[pointer_for_numbers ++] = input[pointer_for_input ++];
    
    if (pointer_for_numbers == ONE)
    {
        FUNC((input[pointer_for_input - ONE] - '0'), NO_FUNCTION, NO_SYMBOL, NUMBER);

        return;
    }
    functions[pointer_for_numbers] = '\0';

    FUNC(atoi(functions), NO_FUNCTION, NO_SYMBOL, NUMBER);

    return;
}

void function_analyze()
{
    int pointer_for_functions = zero;

    char functions[FUNCTION_SIZE];

    while ((input[pointer_for_input] >= 'a' && input[pointer_for_input] <= 'z')
    || (input[pointer_for_input] >= 'A' && input[pointer_for_input] <= 'Z'))

        functions[pointer_for_functions ++] = input[pointer_for_input ++];

    if (pointer_for_functions == ONE)
    {
        global_variable = input[pointer_for_input - ONE];

        FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input - ONE], VARIABLE);

        return;
    }

    #include "box_distribution_macros.h"
}

//______________________________________________________DISTRIBUTION__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void auxiliary_for_letters()
{
    if (pointer_for_input != ZERO)
    {
        if (((input[pointer_for_input] >= 'a' && input[pointer_for_input] <= 'z')
        ||   (input[pointer_for_input] >= 'A' && input[pointer_for_input] <= 'Z'))

        &&  ((input[pointer_for_input - ONE] >= 'a' && input[pointer_for_input - ONE] <= 'z')
        ||   (input[pointer_for_input - ONE] >= 'A' && input[pointer_for_input - ONE] <= 'Z')))
        {
            FUNC(NO_VALUE, NO_FUNCTION, MULTIPLICATION, SYMBOL); 
        
            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], VARIABLE);

            POSITION_COUNTER ++;
        }
    }
    if ((input[pointer_for_input] >= 'a' && input[pointer_for_input] <= 'z')
    ||  (input[pointer_for_input] >= 'A' && input[pointer_for_input] <= 'Z'))
    {
        FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], VARIABLE);

        POSITION_COUNTER ++;
    }
}

void distribution_func_RE()
{
    int expression_length = strlen(input);

    while (pointer_for_input < expression_length)
    {
        if (input[pointer_for_input] == ' ') pointer_for_input ++;

        if (input[pointer_for_input] == EDGE)

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        if (input[pointer_for_input] == MULTIPLICATION)
        {
            FUNC(NO_VALUE, NO_FUNCTION, DEGREE, SYMBOL); 

            FUNC(NO_VALUE, NO_FUNCTION, ITERATION, VARIABLE);

            pointer_for_input ++;
        }
        if (input[pointer_for_input] == OPENING_BRACKET) 

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        if (input[pointer_for_input] == CLOSING_BRACKET) 

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        auxiliary_for_letters(); 
    }   
}

void distribution_func()
{
    int expression_length = strlen(input);

    while (pointer_for_input < expression_length)
    {
        if (input[pointer_for_input] == ' ') pointer_for_input ++;

        if (input[pointer_for_input] == PLUS || input[pointer_for_input] == MINUS)

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        if (input[pointer_for_input] == MULTIPLICATION || input[pointer_for_input] == DIVISION)

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        if (input[pointer_for_input] == OPENING_BRACKET || input[pointer_for_input] == CLOSING_BRACKET)

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        if (input[pointer_for_input]  == DEGREE)

            FUNC(NO_VALUE, NO_FUNCTION, input[pointer_for_input ++], SYMBOL);

        if ((input[pointer_for_input] >= 'a' && input[pointer_for_input] <= 'z')
        ||  (input[pointer_for_input] >= 'A' && input[pointer_for_input] <= 'Z'))

            function_analyze();

        if (input[pointer_for_input] >= '0' && input[pointer_for_input] <= '9')

            number_analyze();
    }
}

//______________________________________________________COMMAND_OPERATION_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * auxiliary(char * postfix)
{
    struct TREE * tree;

    if (strcmp(postfix, "last") == ZERO) tree = tree_copy(Input);

    else if (strcmp(postfix, "answer") == ZERO) tree = tree_copy(answer);

    else {distribution_func(); tree = GET_EXPRESSION();}

    Input  = tree_copy(tree);

    return tree;
}

void command_expression()
{
    distribution_func();

    struct TREE * tree = GET_EXPRESSION();

    struct TREE * derivative = differentiate(tree);

    struct TREE * integral   = integrate(&tree);

    struct TREE * image      = tree_copy(tree);

    printf("\n"); tree_image(image);

    printf("\n\nderivative : ");

    infix_print(derivative);

    printf("\n\nintegral   : ");

    infix_print(integral);

    printf("\n\n");

    command_input();
}

void command_tree_image(char * command)
{
    distribution_func();

    struct TREE * tree = GET_EXPRESSION();

    struct TREE * image = tree_copy(tree);

    printf("\n");

    tree_image(image);

    command_input();
}

void command_derivative(char * command, char * postfix, int repetitions)
{
    int box = pointer_for_input, counter = ZERO;

    if (repetitions == ZERO) repetitions = ONE;

    struct TREE * tree = auxiliary(postfix);

    switch_to_Exponent(tree);

    for (counter = ZERO; counter < repetitions; counter ++)

        tree = differentiate(tree);

    printf("\n\nd^%d(", repetitions);

    if (strcmp(postfix, "last") == ZERO) infix_print(Input);

    else if (strcmp(postfix, "answer") == ZERO) infix_print(answer);

    else printf("%s", input + box);

    answer = tree_copy(tree);

    printf(")/d%c^%d = ", global_variable, repetitions);

    infix_print(tree); printf("\n\n");

    command_input();
}

void command_integral  (char * command, char * postfix, int repetitions)
{
    int box = pointer_for_input, counter = ZERO;

    struct TREE * tree = auxiliary(postfix);

    if (repetitions == ZERO) repetitions = ONE;

    for (counter = ZERO; counter < repetitions; counter ++)

        tree = integrate(&tree);

    printf("\n\n");

    for (counter = ZERO; counter < repetitions; counter ++)

        printf("∫(");

    if (strcmp(postfix, "last") == ZERO) infix_print(Input);

    else if (strcmp(postfix, "answer") == ZERO) infix_print(answer);

    else printf("%s", input + box);

    answer = tree_copy(tree);

    printf(")");

    for (counter = ZERO; counter < repetitions; counter ++)

        printf("d%c", global_variable);

    printf(" = ");

    infix_print(tree); printf("+ constant\n\n");

    command_input();
}

void command_determinant()
{
    int order = ZERO;

    printf("\nmatrix order : ");

    scanf("%d", &order);

    printf("\n\n");

    printf("Δ = %d",print_determinant(order));

    printf("\n\n");

    command_input();
}

void command_system_solution()
{
    int order, counter = ZERO;

    printf("\nmatrix order : ");

    scanf("%d", &order);

    printf("\n");

    struct MATRIX_E * matrix = linear_system_solution(order);

    printf("\n");

    for (counter = ZERO; counter < order; counter ++)
    
        printf("x%d = %f, ", counter + ONE, matrix -> variables[counter]);

    printf("\n\n");
    
    command_input();
}

void command_exit()
{
    return;
}

void command_identify()
{
    if (input[pointer_for_input] == SPACE)  
    {
        pointer_for_input ++;

        command_identify();

        return;
    }

    #include "command_macros.h"

    //else command_expression();
}

void command_input()
{
    pointer_for_input         = ZERO;

    pointer_for_struct        = ZERO;

    second_pointer_for_struct = ZERO;

    Counter                   = ZERO;

    input                     = calloc(SIZE, sizeof(char));

    parced_input              = calloc(SIZE, sizeof(struct NODE_INFO));

    gets(input);

    command_identify();
}


