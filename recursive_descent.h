//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

TREE * GET_EXPRESSION    ();
TREE * GET_DEGREE        ();
TREE * GET_MULTIPLICATION();
TREE * GET_BRACKETS      ();
TREE * GET_NUMBER        ();
TREE * GET_FUNCTION      ();

void switch_to_Exponent  ();

///____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


TREE * GET_NUMBER        ()
{
    if(parced_input[second_pointer_for_struct] . flag == NUMBER
    || parced_input[second_pointer_for_struct] . flag == VARIABLE)
    {
        TREE * new_tree = 

        tree_join(&parced_input[second_pointer_for_struct ++], NULL, NULL);

        return new_tree;
    }
    else
    
        return GET_FUNCTION();
}

///____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


TREE * GET_BRACKETS      ()
{
    if (parced_input[second_pointer_for_struct] . symbol == OPENING_BRACKET)
    {
        second_pointer_for_struct ++;

        TREE * new_tree = GET_EXPRESSION();

        second_pointer_for_struct ++;

        return new_tree;
    }
    else
        return GET_NUMBER();
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

TREE * GET_EXPRESSION    ()
{
    TREE * new_tree = GET_MULTIPLICATION();

    while (parced_input[second_pointer_for_struct] . symbol == PLUS
    ||     parced_input[second_pointer_for_struct] . symbol == MINUS
    ||     parced_input[second_pointer_for_struct] . symbol == EDGE)
    {
        NODE_INFO BUFFER = parced_input[second_pointer_for_struct ++];

        new_tree = tree_join(&BUFFER, new_tree, GET_MULTIPLICATION());
    }
    return new_tree;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

TREE * GET_MULTIPLICATION()
{
    TREE * new_tree = GET_DEGREE();

    while (parced_input[second_pointer_for_struct] . symbol == MULTIPLICATION
    ||     parced_input[second_pointer_for_struct] . symbol == DIVISION)
    {
        NODE_INFO BUFFER = parced_input[second_pointer_for_struct ++];

        new_tree = tree_join(&BUFFER, new_tree, GET_DEGREE());
    }
    return new_tree;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

TREE * GET_DEGREE        ()
{
    TREE * new_tree = GET_BRACKETS();

    while (parced_input[second_pointer_for_struct] . symbol == DEGREE)
    {
        NODE_INFO BUFFER = parced_input[second_pointer_for_struct ++];

        new_tree = tree_join(&BUFFER, new_tree, GET_BRACKETS());
    }
    return new_tree;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

TREE * GET_FUNCTION()
{
    if (parced_input[second_pointer_for_struct] . flag == FUNCTION)
    {
        NODE_INFO BUFFER = parced_input[second_pointer_for_struct ++];

        TREE * new_tree  = tree_join(&BUFFER, NULL, GET_BRACKETS());

        return new_tree;
    }
    else return NULL;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void switch_to_Exponent(TREE * tree)
{
    if (tree -> info . symbol == DEGREE
        
    &&  tree -> right_branch -> info . flag != NUMBER)
    {
        CREATE_FUNCTION_NODE(EXPONENT ,  exponent);
        CREATE_FUNCTION_NODE(LOGARITHM, logarithm);

        CREATE_SYMBOL_NODE  (MULTIPLICATION, product);

        TREE * left_copy     = tree_copy(tree -> left_branch);
        TREE * right_copy    = tree_copy(tree -> right_branch);

        tree -> info         = exponent;

        tree -> right_branch = tree_join(&product, right_copy, 

                               tree_join(&logarithm, NULL, left_copy));
    }
    if (tree -> left_branch  != NULL) 

        switch_to_Exponent(tree -> left_branch);

    if (tree -> right_branch != NULL) 

        switch_to_Exponent(tree -> right_branch);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
