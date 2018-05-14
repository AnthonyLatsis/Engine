
void integrator(struct TREE ** tree);

int arg_structure_LP(struct TREE * arg)
{
    int comparison_1 = ZERO;
    int comparison_2 = ZERO;
    int comparison_3 = ZERO;
    int comparison_4 = ZERO;

    //structure_compare(arg, proportional(WITH_COEFFICIENT)   , comparison_1);
    //structure_compare(arg, proportional(WITHOUT_COEFFICIENT), comparison_2);
    //structure_compare(arg, linear      (WITH_COEFFICIENT)   , comparison_3);
    //structure_compare(arg, linear      (WITHOUT_COEFFICIENT), comparison_4);

    if (comparison_1 == ZERO || comparison_2 == ZERO 
    ||  comparison_3 == ZERO || comparison_4 == ZERO)

    return ONE;

    else return ZERO;
}

void integrate_sum(struct TREE ** tree) {
    integrator(&((* tree) ->  left_branch));
    integrator(&((* tree) -> right_branch));
}

void integrate_number(struct TREE ** tree) {
    (* tree) = number_integral(* tree);
    return;
}

void integrate_degree(struct TREE ** tree)
{
    if ((* tree) -> info . flag == VARIABLE
    ||  (* tree) -> right_branch -> info . flag == NUMBER)  
    {
        (* tree) = variable_in_power_integral(* tree);

        return;
    }
    if ((* tree) -> left_branch  -> info . flag == NUMBER)
    {
        (* tree) = number_in_power_integral(* tree);

        return;
    }
}

void integrate_product(struct TREE ** tree)
{
    if ((* tree) -> left_branch -> info . flag == NUMBER)

        {integrator(&((* tree) -> right_branch)); return;}
}

void integrate_division(struct TREE ** tree)
{
    if ((* tree) -> right_branch -> info . flag == NUMBER)
    {
        integrator(&((* tree) -> left_branch));

        return;
    }
}

void integrator(struct TREE ** tree)
{
    #include "integrator_macros.h"

    if ((* tree) -> info . flag == NUMBER)

        {integrate_number(tree);   return;}  

    if ((* tree) -> info . flag == VARIABLE)

        {integrate_degree(tree);   return;}
}

struct TREE * integrate(struct TREE ** tree)
{
    struct TREE * integral = tree_copy(* tree);

    //recursive_parcing(&integral); optimization(&integral); constant_condenser(&integral);

    integrator(&integral); optimization(&integral);

    return integral;
}

/*
void parcial_integrating (struct TREE ** tree)
{
        struct TREE * integr_left = integrate    (&((* tree)  ->   left_branch));
        struct TREE * copy_right  = tree_copy    ((* tree)    ->   right_branch);
        struct TREE * deriv_right = differentiate((* tree)    ->   right_branch);

        struct TREE * integr_sec  = tree_copy    (integr_left);

        CREATE_SYMBOL_NODE  (MINUS         ,   minus)
        CREATE_SYMBOL_NODE  (MULTIPLICATION, product)

        struct TREE * left       = tree_join(&product, integr_left,  copy_right);
        struct TREE * right      = tree_join(&product, integr_sec , deriv_right);

        comparison = 0;

        tree_compare(left , right);

        if (comparison == 0)
        {
                struct TREE * copyl      = tree_copy((* tree)  ->   left_branch);
                struct TREE * copyr      = tree_copy((* tree)  ->  right_branch);

                NULL_BR_P

                (* tree) -> left_branch  = copyr;
                (* tree) -> right_branch = copyl;

                 parcial_integrating(tree); return;
        }
        comparison = 0;

        optimization(&right);    right = integrate(&right);  optimization(&left);

        (* tree) -> info                 = minus;
        (* tree) -> left_branch          = left;
        (* tree) -> right_branch         = right;
}
*/                
  
