
const int WITH_COEFFICIENT    = ONE;

const int WITHOUT_COEFFICIENT = ZERO;

//_______________________________________________TEMPLATES_FOR_TREE_CONSTRUCTION_AND_COMPARISON________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * proportional(int coefficient_existence)  //template for tree ax
{
	CREATE_NUMBER_NODE(NO_VALUE      ,  number)
	CREATE_SYMBOL_NODE(MULTIPLICATION, product)

	struct NODE_INFO Variable;

	Variable . flag = VARIABLE;

	struct TREE * Number = tree_join(&number, NULL, NULL);

	struct TREE * Var    = tree_join(&Variable, NULL, NULL);

	struct TREE * prop   = tree_join(&product, Number, Var);

	return prop;
}

struct TREE * linear(int coefficient_existence)  // template for tree (ax ± b)
{
	CREATE_NUMBER_NODE(NO_VALUE      , number_1)
	CREATE_NUMBER_NODE(NO_VALUE      , number_2)
	CREATE_SYMBOL_NODE(MULTIPLICATION,  product)
	CREATE_SYMBOL_NODE(PLUS_MINUS    ,       PM)

	struct NODE_INFO Variable;

	Variable . flag = VARIABLE;

	struct TREE * Number_1 = tree_join(&number_1, NULL, NULL);
	struct TREE * Number_2 = tree_join(&number_2, NULL, NULL);

	struct TREE * Var       = tree_join(&Variable, NULL, NULL);

	struct TREE * summand_1 = tree_join(&product, Number_1, Var);

	struct TREE * linear    = tree_join(&PM, summand_1, Number_2);

	return linear;	
}

//__________________________________________________TEMPLATES_FOR_INTEGRALS_OF_ELEMENTARY_FUNCTIONS___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * number_integral(struct TREE * tree) // template for constant
{
	struct TREE * Var      = T_variable(global_variable);

	return T_operator(MULTIPLICATION, tree_copy(tree), Var); 
}

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct TREE * variable_in_power_integral(struct TREE * tree) // template for x^a
{
    struct TREE * copy = tree_copy(tree); 

    CREATE_SYMBOL_NODE(DEGREE  ,   degree)
	CREATE_SYMBOL_NODE(DIVISION, division)
	CREATE_NUMBER_NODE(ZERO    ,  var_deg)

	struct TREE * denominator;

	struct TREE * integral;

    if (tree -> info . flag   == SYMBOL 
    &&  tree -> info . symbol == DEGREE)
    {
    	copy -> right_branch -> info . value ++;

    	var_deg . value  = copy -> right_branch -> info . value;

    	denominator      = tree_join(&var_deg, NULL, NULL);

       	integral         = tree_join(&division, copy, denominator);

       	return integral;
    }
    var_deg . value      = TWO;

	denominator          = tree_join(&var_deg, NULL, NULL);

	struct TREE * Two    = tree_join(&var_deg, NULL, NULL);

	struct TREE * factor = tree_join(&degree, copy, Two);

	integral             = tree_join(&division, factor, denominator);

    return integral;
}

struct TREE * number_in_power_integral(struct TREE * tree) // template for a^(bx) and a^(bx + c)
{
	struct TREE * argument_derivative = differentiate(tree -> right_branch);

	struct TREE * Logarithm           = T_function(LOGARITHM, tree_copy(tree -> left_branch));

	struct TREE * denominator         = T_operator(MULTIPLICATION, argument_derivative, Logarithm);

	return T_operator(DIVISION, tree_copy(tree), denominator);
}

struct TREE * sine_integral_LP(struct TREE * tree) // template for sin(ax) and sin(ax + b)
{
	struct TREE * argument_derivative = differentiate(tree -> right_branch);

    struct TREE * Cosine      = T_function(COSINE, tree_copy(tree -> right_branch));

    struct TREE * M_integral  = T_operator(DIVISION , Cosine, argument_derivative);

    return T_operator(MINUS, NULL, M_integral);
}

struct TREE * cosine_integral_LP(struct TREE * tree) // template for cos(ax) and cos(ax + b)
{      
    struct TREE * Sine = T_function(SINE, tree_copy(tree -> right_branch));
	
	return T_operator(DIVISION, Sine, differentiate(tree -> right_branch));
}

struct TREE * tan_derivative_integral_LP(struct TREE * tree) // template for 1/(cos(ax + b))^2 and 1/(cos(ax))^2
{
return NULL;
}

struct TREE * cot_derivative_integral_LP(struct TREE * tree) // template for 1/(sin(ax + b))^2 and 1/(sin(ax))^2
{
return NULL;     
}

struct TREE * hyp_sin_integral_LP(struct TREE * tree) //template for sh(ax) and sh(ax + b)
{
	struct TREE * argument_copy       = tree_copy(tree -> right_branch);

    struct TREE * Hypcos   = T_function(HYPERBOLIC_COSINE, argument_copy);

    return T_operator(DIVISION, Hypcos, differentiate(tree -> right_branch));
}

struct TREE * hyp_cos_integral_LP(struct TREE * tree) //template for ch(ax) and ch(ax + b)
{      
	struct TREE * argument_copy = tree_copy(tree -> right_branch);
 
    struct TREE * Hypsin        = T_function(HYPERBOLIC_SINE, argument_copy);

   	return T_operator(DIVISION, Hypsin, differentiate(tree -> right_branch));
}

struct TREE * exponent_integral_LP(struct TREE * tree) //template for exp(ax) and exp(ax + b)
{
	struct TREE * argument_derivative = differentiate(tree -> right_branch);

	struct TREE * Exponent = T_function(EXPONENT, tree_copy(tree -> right_branch));

    return T_operator(DIVISION, Exponent, argument_derivative);
}

struct TREE * tangent_integral_LP(struct TREE * tree) //template for tan(ax) and tan(ax + b)
{
	struct TREE * argument_derivative = differentiate(tree -> right_branch);

	struct TREE * Cosine     = T_function(COSINE, tree_copy(tree -> right_branch));

	struct TREE * Logarithm  = T_function(LOGARITHM, Cosine);

	struct TREE * M_integral = T_operator(DIVISION, Logarithm, argument_derivative);

	return T_operator(MINUS, NULL, M_integral);
}

struct TREE * cotangent_integral_LP(struct TREE * tree) //template for cot(ax) and cot(ax + b)
{
	struct TREE * Sine       = T_function(SINE, tree_copy(tree -> right_branch));

	struct TREE * Logarithm  = T_function(LOGARITHM, Sine);

	return T_operator(DIVISION, Logarithm, differentiate(tree -> right_branch));
}

struct TREE * hyp_tan_integral_LP(struct TREE * tree) //template for tanh(ax) and tanh(ax + b)
{
	struct TREE * log_argument = T_function(HYPERBOLIC_COSINE, tree_copy(tree -> right_branch));
	
	struct TREE * Log          = T_function(LOGARITHM, log_argument);

	return T_operator(DIVISION, Log, differentiate(tree-> right_branch));
}

struct TREE * hyp_cot_integral_LP(struct TREE * tree) //template for coth(ax) and coth(ax + b)
{
	struct TREE * log_argument = T_function(HYPERBOLIC_SINE, tree_copy(tree -> right_branch));
	
	struct TREE * Log          = T_function(LOGARITHM, log_argument);

	return T_operator(DIVISION, Log, differentiate(tree -> right_branch));
}

struct TREE * logarithm_integral_LP(struct TREE * tree) //template for ln(ax) and ln(ax + b)
{
	struct TREE * argument_copy_2 = tree_copy(tree -> right_branch);

	struct TREE * Logarithm   = T_function(LOGARITHM, tree_copy(tree -> right_branch));

	struct TREE * Var 		  = T_variable(global_variable);

	struct TREE * summand_1   = T_operator(MULTIPLICATION, argument_copy_2, Logarithm);

	struct TREE * Summand_2   = T_operator(MULTIPLICATION, differentiate(tree -> right_branch), Var);

	struct TREE * factor      = T_operator(MINUS, summand_1, Summand_2);

	return T_operator(DIVISION, factor, differentiate(tree -> right_branch));
}

struct TREE * inv_sin_cos_integral_LP(struct TREE * tree, char factor_symbol) // template for arccos(ax), arccos(ax + b) and arcsin(ax), arcsin(ax + b)
{    
	struct TREE * copy          = tree_copy(tree);

	struct TREE * Sqrt_summand2 = T_operator(DEGREE, tree_copy(tree -> right_branch), T_number(TWO));

	struct TREE * Sqrt_inside   = T_operator(MINUS, T_number(ONE), Sqrt_summand2);

	struct TREE * Sqrt          = T_function(SQUARE_ROOT, Sqrt_inside);

	struct TREE * Summand_2     = T_operator(MULTIPLICATION, tree_copy(tree -> right_branch), copy);
	
	struct TREE * factor        = T_operator(factor_symbol, Summand_2, Sqrt);

	return T_operator(DIVISION, factor, differentiate(tree -> right_branch));
}

struct TREE * inv_tan_cot_integral_LP(struct TREE * tree, char factor_symbol) // template for arccot(ax), arccot(ax + b) and arctan(ax), arctan(ax + b)
{
	struct TREE * argument_derivative = differentiate(tree -> right_branch);

	struct TREE * copy          = tree_copy(tree);

	struct TREE * log_summand_1 = T_operator(DEGREE, tree_copy(tree -> right_branch), T_number(TWO));

	struct TREE * log_argument  = T_operator(PLUS, log_summand_1, T_number(ONE));

	struct TREE * Log           = T_function(LOGARITHM, log_argument);

	struct TREE * summand_1     = T_operator(MULTIPLICATION, tree_copy(tree -> right_branch), copy);

	struct TREE * two_summand_1 = T_operator(MULTIPLICATION, T_number(TWO), summand_1);

	struct TREE * factor        = T_operator(factor_symbol, Log, two_summand_1);

	struct TREE * denominator   = T_operator(MULTIPLICATION, T_number(TWO), argument_derivative);

	return T_operator(DIVISION, factor, denominator);
}

struct TREE * inv_hyp_sin_integral_LP(struct TREE * tree) //template for arccosh(ax) and arccosh(ax + b)
{	
	struct TREE * copy       = tree_copy(tree);

	struct TREE * summand_1  = T_operator(MULTIPLICATION, tree_copy(tree -> right_branch), copy);
	
	struct TREE * sqrt_arg_1 = T_operator(MINUS, tree_copy(tree -> right_branch), T_number(ONE));
	struct TREE * sqrt_arg_2 = T_operator(PLUS , tree_copy(tree -> right_branch), T_number(ONE));

	struct TREE * sqrt_1     = T_function(SQUARE_ROOT, sqrt_arg_1);
	struct TREE * sqrt_2     = T_function(SQUARE_ROOT, sqrt_arg_2);

	struct TREE * Sqrt       = T_operator(MULTIPLICATION, sqrt_1, sqrt_2);

	struct TREE * factor     = T_operator(MINUS, summand_1, Sqrt);

	return T_operator(DIVISION, factor , differentiate(tree -> right_branch));
}	


struct TREE * inv_hyp_cos_integral_LP(struct TREE * tree) //template for arcsinh(ax) and arcsinh(ax + b)
{
	struct TREE * copy      = tree_copy(tree);

	struct TREE * summand_1 = T_operator(MULTIPLICATION, tree_copy(tree -> right_branch), copy);

	struct TREE * sqrt_1    = T_operator(DEGREE, tree_copy(tree -> right_branch), T_number(TWO));

	struct TREE * sqrt_arg  = T_operator(PLUS, sqrt_1, T_number(ONE));

	struct TREE * Sqrt      = T_function(SQUARE_ROOT, sqrt_arg);

	struct TREE * factor    = T_operator(MINUS, summand_1, Sqrt);

	return T_operator(DIVISION, factor, differentiate(tree -> right_branch));
}

struct TREE * inv_hyp_tan_cot_integral_LP(struct TREE * tree) //template for arctanh(ax), arccoth(ax) and arctanh(ax + b), arccoth(ax + b)
{
	struct TREE * argument_derivative = differentiate(tree -> right_branch);

	struct TREE * copy          = tree_copy(tree);

	struct TREE * summand_1     = T_operator(MULTIPLICATION, tree_copy(tree -> right_branch), copy);

	struct TREE * two_summand_1 = T_operator(MULTIPLICATION, T_number(TWO), summand_1);

	struct TREE * log_arg_2     = T_operator(DEGREE, tree_copy(tree -> right_branch), T_number(TWO));

	struct TREE * log_arg       = T_operator(MINUS, T_number(ONE), log_arg_2);

	struct TREE * Log           = T_function(LOGARITHM, log_arg);

	struct TREE * factor        = T_operator(PLUS, two_summand_1, Log);

	struct TREE * denominator   = T_operator(MULTIPLICATION, T_number(TWO), argument_derivative);

	return T_operator(DIVISION, factor, denominator); 
}

