///_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void infix_print_B (struct TREE * tree);
void infix_print   (struct TREE * tree);

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct NODE_INFO
{
    int flag;

    int value;

    int depth;

    char symbol;
    int power;
    char * Function;

}typedef NODE_INFO;

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE
{
    struct TREE * left_branch;
    struct TREE * right_branch;

    struct TREE * mother;

    struct NODE_INFO info;

}typedef TREE;

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool check_null                 (struct TREE * tree)
{
    if (tree == NULL) return true;

    else return false;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool check_number               (struct TREE * tree, const int * number)
{
    if (tree == NULL) return false;

    if (tree != NULL && tree -> info . flag == NUMBER)
    {
        if (number == NULL) return true;

        if (number != NULL && tree -> info . value == (* number))

            return true;

        return  false;
    }
    else return false;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool check_symbol               (struct TREE * tree, const char CHARACTER)
{
    if (tree == NULL) return false;

    if (tree -> info . flag == SYMBOL 

    &&  tree -> info . symbol == CHARACTER)

        return true;

    else return false;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool check_function             (struct TREE * tree, char ** function)
{
    if (tree != NULL && tree -> info . flag == FUNCTION)
    {
        if (function == NULL) return true;

        if (function != NULL && strcmp(tree -> info . Function, * function) == ZERO)

            return true;

        else return false;
    }
    else return false;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool check_variable             (struct TREE * TREE, char CHARACTER)
{
    assert(TREE != NULL);

    if (TREE -> info . symbol == CHARACTER 

    &&  TREE -> info . flag   == VARIABLE)
        
        return true;

    else return false;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * tree_join         (struct NODE_INFO * Info, struct TREE * left_branch, struct TREE * right_branch)
{
        struct TREE * tree   = (struct TREE *)calloc(ONE, sizeof(struct TREE));

        tree -> left_branch  = left_branch;
        
        tree -> right_branch = right_branch;

        if (tree -> left_branch  != NULL) 

            tree -> left_branch  -> mother  = tree;
        
        if (tree -> right_branch != NULL) 

            tree -> right_branch -> mother  = tree;

        tree -> info = * Info;

        return tree;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * tree_copy         (struct TREE * tree)
{
        if (check_null(tree) == true)   return tree;

        struct TREE * new_tree = (struct TREE *)calloc(ONE, sizeof(struct TREE));

        new_tree -> info . value       = tree -> info . value;
        new_tree -> info . symbol      = tree -> info . symbol;
        new_tree -> info . flag        = tree -> info . flag;
        new_tree -> info . Function    = tree -> info . Function;

        new_tree -> left_branch     = tree_copy(tree -> left_branch);
        new_tree -> right_branch    = tree_copy(tree -> right_branch);

        if (new_tree -> left_branch  != NULL) 

            new_tree -> left_branch  -> mother = new_tree;
        
        if (new_tree -> right_branch != NULL) 

            new_tree -> right_branch -> mother = new_tree;

        return new_tree;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void bracket_condition          (struct TREE * tree)
{

        BRACKET(tree -> left_branch)

        else if (tree -> left_branch != NULL)    infix_print(tree -> left_branch);                                                                                
                                                                                                        
        if  (tree -> info . flag == NUMBER)      printf("%d", tree -> info .      value);                    
                                                                                                    
        if ((tree -> info . flag == SYMBOL && tree -> info . symbol !=   MULTIPLICATION)                 
        
        ||  (tree -> info . flag == VARIABLE))   printf("%c", tree -> info .     symbol);                                           
                                                                                                    
        if  (tree -> info . flag == FUNCTION)    printf("%s", tree -> info .   Function);                  

        BRACKET(tree -> right_branch)

        else if (tree -> info . flag == FUNCTION)    infix_print_B(tree -> right_branch);

        else if (tree -> right_branch != NULL)       infix_print  (tree -> right_branch);
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void infix_print_B              (struct TREE * tree)
{
        printf("%c", OPENING_BRACKET);

        bracket_condition(tree);

        printf("%c", CLOSING_BRACKET);
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void infix_print                (struct TREE * tree)
{
        if (tree == NULL) return;

        bracket_condition(tree);
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
        
void tree_destroy               (struct TREE * tree)
{
    if (tree -> left_branch  != NULL) 

        tree_destroy(tree -> left_branch);

    if (tree -> right_branch != NULL) 

        tree_destroy(tree -> right_branch);

    free(tree);
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void tree_compare               (struct TREE * first, struct TREE * second)//УДАЛИТЬ НАХУЙ
{
    if (first == NULL && second == NULL) return;

    if ((first == NULL && second != NULL)
    ||  (first != NULL && second == NULL))
    {
        tree_comparison = ONE; return;
    }
    if (first -> info . flag != second -> info . flag)
    {  
        tree_comparison = ONE; return;
    }   
    else
    {
        if ((first -> info . flag == NUMBER   && first -> info . value    != second -> info . value)
        ||  (first -> info . flag == SYMBOL   && first -> info . symbol   != second -> info . symbol)
        ||  (first -> info . flag == FUNCTION && first -> info . Function != second -> info . Function)
        ||  (first -> info . flag == VARIABLE && first -> info . symbol   != second -> info . symbol))

            {tree_comparison = ONE; return;}
    }
    if  (first -> left_branch  != NULL && second -> left_branch != NULL)

    tree_compare(first -> left_branch,  second -> left_branch);

    if  (first -> right_branch != NULL && second -> right_branch != NULL)

    tree_compare(first -> right_branch, second -> right_branch);
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool compare_tree                (struct TREE * first, struct TREE * second)
{
    if (first == NULL && second == NULL) return true;

    if ((first == NULL && second != NULL)
    ||  (first != NULL && second == NULL))

        return false;

    if (first -> info . flag != second -> info . flag)

        return false; 

    if ((first -> info . value    != second -> info . value)
    ||  (first -> info . symbol   != second -> info . symbol)
    ||  (first -> info . Function != second -> info . Function)
    ||  (first -> info . symbol   != second -> info . symbol))

        return false;
    
    if (!compare_tree(first -> left_branch,  second ->  left_branch)
    ||  !compare_tree(first -> right_branch, second -> right_branch))

        return false;

    else return true;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * T_function        (char * function, struct TREE * argument)
{
    CREATE_FUNCTION_NODE(function, name)

    struct TREE * result = tree_join(&name, NULL, argument);

    return result;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * T_operator        (char Operator, struct TREE * L_operand, struct TREE * R_operand)
{
    CREATE_SYMBOL_NODE(Operator, name)

    struct TREE * result = tree_join(&name, L_operand, R_operand);

    return result;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * T_number          (int number)
{
    CREATE_NUMBER_NODE(number, name)

    struct TREE * Number = tree_join(&name, NULL, NULL);

    return Number;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * T_variable        (char variable)
{
    CREATE_VARIABLE_NODE(variable, name)

    struct TREE * Variable = tree_join(&name, NULL, NULL);

    return Variable;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void mother_fill                (struct TREE * tree)
{
    if (check_null(tree)) return;

    if (!check_null(tree -> left_branch))

        tree -> left_branch  -> mother = tree;

    if (!check_null(tree -> right_branch))
    
        tree -> right_branch -> mother = tree;

    mother_fill(tree ->  left_branch);
    mother_fill(tree -> right_branch);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void substitute                 (struct TREE ** tree, struct TREE * New)//УДАЛИТЬ НАХУЙ,ВОЗМОЖНО
{
    if ((* tree) != NULL) New -> mother = (* tree) -> mother;

    (* tree) = New;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


