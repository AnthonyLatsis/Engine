
struct TREE * left_equation_part  = NULL;

struct TREE * right_equation_part = NULL;

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * polinomal_maker (int order, int counter)
{
	if (order < ZERO) return NULL;

	struct TREE * variable    = T_variable(global_variable);

	struct TREE * degree      = T_operator(DEGREE, variable, T_number(order));

	struct TREE * coefficient = T_coefficient(counter);

	struct TREE * summand     = T_operator(MULTIPLICATION, coefficient, variable);

	return T_operator(PLUS, summand, polinomal_maker(order --, counter ++));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int polinomal_order (struct TREE * tree)
{
	if (check_symbol(tree -> info, &PLUS)  == true
	||  check_symbol(tree -> info, &MINUS) == true)
	{
		if (polinomal_order(tree -> left_branch) > polinomal_order(tree -> right_branch))

			 return polinomal_order(tree ->  left_branch);

		else return polinomal_order(tree -> right_branch);
	}

	if (check_symbol(tree -> info, &DEGREE) == true)
	
		return tree -> right_branch -> info . value;
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void create_equation(struct TREE * tree)
{
	left_equation_part        = tree_copy(tree ->  left_branch);

	struct TREE * right_copy  = tree_copy(tree -> right_branch);

	struct TREE * denominator = tree_copy(right_copy -> left_branch);

	right_copy -> right_branch -> info . value --;

	int order_2               = polinomal_order(right_copy -> left_branch);

	int order_1               = (order_2 + ONE) * right_copy -> right_branch -> info . value;
 
	struct TREE * polinomal_2 = polinomal_maker(order_2 - ONE, ZERO);

	struct TREE * polinomal_1 = polinomal_maker(order_1 - ONE, order_2);

	struct TREE * summand_2   = T_operator(MULTIPLICATION, polinomal_2, right_copy);

	struct TREE * rsummand_1  = T_operator(MULTIPLICATION, differentiate(denominator), polinomal_1);

	struct TREE * lsummand_1  = T_operator(MULTIPLICATION, differentiate(polinomal_1), denominator);

	struct TREE * summand_1   = T_operator(MINUS, lsummand_1, rsummand_1);

	right_equation_part 	  = T_operator(PLUS, summand_1, summand_2);
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void power_sealer(struct TREE ** tree)
{
	int Power = ZERO;

	if (check_symbol((* tree) -> info, &DEGREE) == true)
	{
		Power = (* tree) -> right_branch -> info . value;

		(* tree) = T_variable(global_variable)

		(* tree) -> info . power = Power;

		return;
	}
	power_sealer(&((* tree) ->  left_branch));
	power_sealer(&((* tree) -> right_branch));
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

bool check_product(struct TREE * left_branch, struct TREE * right_branch)
{
	if (check_number     (left_branch , NULL) == true
	&&  check_coefficient(right_branch, NULL) == true)
	{

	}

	else if (check_coefficient(left_branch , NULL) == true
    &&       check_number     (right_branch, NULL) == true) return true;

	else if (check_number     (left_branch , NULL) == true
	&&       check_coefficient(right_left  , NULL) == true) return true;

	else if (check_coefficient(left_branch , NULL) == true
	&&       check_number     (right_left  , NULL) == true) return true;

	else return false;

	#undef right_left
}
//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void bla(struct TREE * equation_part)
{
	optimization(&equation_part);

	recursive_parsing(&equation_part);

	show_power(&equation_part);

	product_condenser(&equation_part);

	power_sealer(&equation_part);

}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


