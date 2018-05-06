//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiator(struct TREE ** tree);

struct TREE * differentiate (struct TREE * tree);

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_number         (struct TREE ** tree)
{
        substitute(tree, T_number(ZERO));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_variable       (struct TREE ** tree)
{
        substitute(tree, T_number(ONE));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_sum            (struct TREE ** tree)
{
    differentiator(&((* tree) ->  left_branch));
    differentiator(&((* tree) -> right_branch));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_product        (struct TREE ** tree)
{                                                                                                      
    struct TREE * left_copy1  = tree_copy((* tree) -> left_branch);
    struct TREE * left_copy2  = tree_copy((* tree) -> left_branch); 

    struct TREE * right_copy1 = tree_copy((* tree) -> right_branch);     
    struct TREE * right_copy2 = tree_copy((* tree) -> right_branch);

    struct TREE * left  = T_operator(MULTIPLICATION, differentiate(left_copy1), right_copy1);

    struct TREE * right = T_operator(MULTIPLICATION, differentiate(right_copy1) ,left_copy2);

    (* tree)            = T_operator(PLUS, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_division       (struct TREE ** tree)
{
    struct TREE * left_copy1  = tree_copy((* tree) -> left_branch);
    struct TREE * left_copy2  = tree_copy((* tree) -> left_branch); 

    struct TREE * right_copy1 = tree_copy((* tree) -> right_branch);     
    struct TREE * right_copy2 = tree_copy((* tree) -> right_branch);

    struct TREE * summand1    = T_operator(MULTIPLICATION, differentiate(left_copy1), right_copy1);
    struct TREE * summand2    = T_operator(MULTIPLICATION, differentiate(right_copy2), left_copy2);

    struct TREE * left        = T_operator(MINUS, summand1, summand2);

    struct TREE * right       = T_operator(DEGREE, tree_copy((* tree) -> right_branch), T_number(TWO));

    (* tree)                  = T_operator(DIVISION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_degree         (struct TREE ** tree)
{
    struct TREE * copy        = tree_copy(* tree);

    struct TREE * coefficient = T_number(copy -> right_branch -> info . value);

    copy -> right_branch -> info . value -- ;

    struct TREE * derivative  = differentiate(copy -> left_branch);

    struct TREE * multiplier  = T_operator(MULTIPLICATION, derivative, copy);

    (* tree)                  = T_operator(MULTIPLICATION, coefficient, multiplier);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_sine           (struct TREE ** tree)
{
    struct TREE * right_copy = tree_copy((* tree) -> right_branch);

    struct TREE * right      = T_function(COSINE, tree_copy((* tree) -> right_branch));
        
    (* tree)                 = T_operator(MULTIPLICATION, differentiate(right_copy), right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_cosine         (struct TREE ** tree)
{
    struct TREE * right_copy = tree_copy((* tree) -> right_branch);

    struct TREE * right      = T_function(SINE, tree_copy((* tree) -> right_branch));

    struct TREE * derivative = T_operator(MULTIPLICATION, differentiate(right_copy), right);

    (* tree)                 = T_operator(MINUS, NULL, derivative);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_tangent        (struct TREE ** tree)
{
    struct TREE * right_copy  = tree_copy((* tree) -> right_branch);

    struct TREE * left        = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * denominator = T_function(COSINE, right_copy);

    struct TREE * right       = T_operator(DEGREE, left, T_number(TWO));

    (* tree)                  = T_operator(DIVISION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_cotangent      (struct TREE ** tree)
{
    struct TREE * right_copy  = tree_copy((* tree) -> right_branch);

    struct TREE * left        = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * denominator = T_function(SINE, right_copy);

    struct TREE * right       = T_operator(DEGREE, denominator, T_number(TWO));

    struct TREE * derivative  = T_operator(DIVISION, left, right);

    (* tree)                  = T_operator(MINUS, NULL, derivative);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_exponent       (struct TREE ** tree)
{
    struct TREE * copy       = tree_copy(* tree);
    struct TREE * copy_right = tree_copy((* tree) -> right_branch);

    (* tree)                 = T_operator(MULTIPLICATION, differentiate(copy_right), copy);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_logarithm      (struct TREE ** tree)
{
    struct TREE * right_copy = tree_copy((* tree) -> right_branch);

    struct TREE * left       = differentiate(tree_copy((* tree) -> right_branch));

    (* tree)                 = T_operator(DIVISION, left, right_copy);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_inv_sin_cos    (struct TREE ** tree, char * function)
{       
    struct TREE * copy_right = tree_copy((* tree) -> right_branch);

    struct TREE * left       = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * Sqrt_right = T_operator(DEGREE, copy_right, T_number(TWO));

    struct TREE * Sqrt       = T_operator(MINUS, T_number(ONE), Sqrt_right);

    struct TREE * right      = T_function(SQUARE_ROOT, Sqrt);

    (* tree)                 = T_operator(DIVISION, left, right);

    if (function == SINE) return;

    else (* tree)            = T_operator(MINUS, NULL, (* tree));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_inv_tan_cot    (struct TREE ** tree, char * function)
{
    struct TREE * right_copy = tree_copy((* tree) -> right_branch);

    struct TREE * left       = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * Sqr        = T_operator(DEGREE, right_copy, T_number(TWO));

    struct TREE * right      = T_operator(PLUS, T_number(ONE), Sqr);

    (* tree)                 = T_operator(DIVISION, left, right);

    if (function == TANGENT) return;

    else (* tree) = T_operator(MINUS, NULL, (* tree));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_hyp_sin_cos    (struct TREE ** tree, char * function)
{
    struct TREE * copy_right = tree_copy((* tree) -> right_branch);                

    struct TREE * left       = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * right      = T_function(function, copy_right);

    (* tree)                 = T_operator(MULTIPLICATION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_hyp_tan_cot    (struct TREE ** tree, char * function)
{
    struct TREE * copy_right  = tree_copy((* tree) -> right_branch);

    struct TREE * left        = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * denominator = T_function(function, copy_right);

    struct TREE * right       = T_operator(DEGREE, denominator, T_number(TWO));

    (* tree)                  = T_operator(DIVISION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_inv_hyp_sin    (struct TREE ** tree)
{
    struct TREE * right_copy = tree_copy((* tree) -> right_branch);

    struct TREE * left       = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * Sqr        = T_operator(DEGREE, right_copy, T_number(TWO));

    struct TREE * Sqrt       = T_operator(PLUS, T_number(ONE), Sqr);

    struct TREE * right      = T_function(SQUARE_ROOT, Sqrt);

    (* tree)                 = T_operator(DIVISION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_inv_hyp_cos    (struct TREE ** tree)
{
    struct TREE * right_copy1 = tree_copy((* tree) -> right_branch);
    struct TREE * right_copy2 = tree_copy((* tree) -> right_branch);
    
    struct TREE * left = differentiate(tree_copy((* tree) -> right_branch));

    struct TREE * summand1 = T_operator(PLUS , right_copy1, T_number(ONE));
    struct TREE * summand2 = T_operator(MINUS, right_copy2, T_number(ONE));
    
    struct TREE * sqrt1    = T_function(SQUARE_ROOT, summand1);
    struct TREE * sqrt2    = T_function(SQUARE_ROOT, summand2);

    struct TREE * right    = T_operator(MULTIPLICATION, sqrt1, sqrt2);

    (* tree)               = T_operator(DIVISION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiate_inv_hyp_tan_cot(struct TREE ** tree)
{
    struct TREE * copy_right = tree_copy((* tree) -> right_branch);

    struct TREE * left       = differentiate(tree_copy((* tree) -> right_branch));   

    struct TREE * Sqr        = T_operator(DEGREE, copy_right, T_number(TWO));

    struct TREE * right      = T_operator(MINUS , T_number(ONE), Sqr);

    (* tree)                 = T_operator(DIVISION, left, right);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void differentiator               (struct TREE ** tree)
{
        #include "differentiator_macros.h"

        if ((* tree) -> info . flag     == VARIABLE)
        {differentiate_variable(tree);  return;}

        if ((* tree) -> info . flag     == NUMBER)
        {differentiate_number(tree);    return;}
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * differentiate       (struct TREE * tree)
{
        struct TREE * derivative = tree_copy(tree);

        differentiator(&derivative);  

        optimization(&derivative); 

        return derivative;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


