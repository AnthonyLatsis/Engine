//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


#define INTEGRALF(TOKEN, INTEGRAL_FUNC) 					\
															\
if ((* tree) -> info . Function == TOKEN) 					\
{															\
	if (arg_structure_LP((* tree) -> right_branch) == ONE)	\
	 														\
		{(* tree) = INTEGRAL_FUNC; }  						\
															\
	return;													\
}															\

#define INTEGRALS(TOKEN, INTEGRAL_FUNC) 					\
															\
if ((* tree) -> info . flag   == SYMBOL 					\
&&  (* tree) -> info . symbol == TOKEN) 					\
															\
	{INTEGRAL_FUNC; return;}								\

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

INTEGRALF(SINE                     , sine_integral_LP           (* tree))
INTEGRALF(COSINE                   , cosine_integral_LP         (* tree))
INTEGRALF(TANGENT                  , tangent_integral_LP        (* tree))
INTEGRALF(EXPONENT       	       , exponent_integral_LP       (* tree))
INTEGRALF(LOGARITHM      	       , logarithm_integral_LP      (* tree))
INTEGRALF(COTANGENT                , cotangent_integral_LP      (* tree))
INTEGRALF(ALT_TANGENT              , tangent_integral_LP        (* tree))
INTEGRALF(INVERSE_SINE        	   , inv_sin_cos_integral_LP    ((* tree), PLUS ))
INTEGRALF(ALT_COTANGENT            , cotangent_integral_LP      (* tree))
INTEGRALF(INVERSE_COSINE           , inv_sin_cos_integral_LP    ((* tree), MINUS))
INTEGRALF(HYPERBOLIC_SINE      	   , hyp_sin_integral_LP        (* tree))
INTEGRALF(INVERSE_TANGENT          , inv_tan_cot_integral_LP    ((* tree), PLUS ))
INTEGRALF(INVERSE_HYP_SINE         , inv_hyp_sin_integral_LP    (* tree))
INTEGRALF(HYPERBOLIC_COSINE    	   , hyp_cos_integral_LP        (* tree))
INTEGRALF(INVERSE_COTANGENT        , inv_tan_cot_integral_LP    ((* tree), MINUS))
INTEGRALF(INVERSE_HYP_COSINE       , inv_hyp_cos_integral_LP    (* tree))
INTEGRALF(HYPERBOLIC_TANGENT   	   , hyp_tan_integral_LP        (* tree))
INTEGRALF(INVERSE_ALT_TANGENT      , inv_tan_cot_integral_LP    ((* tree), PLUS ))
INTEGRALF(HYPERBOLIC_ALT_SINE      , hyp_sin_integral_LP        (* tree))
INTEGRALF(INVERSE_HYP_TANGENT      , inv_hyp_tan_cot_integral_LP(* tree))
INTEGRALF(HYPERBOLIC_COTANGENT 	   , hyp_cot_integral_LP        (* tree))
INTEGRALF(INVERSE_ALT_HYP_SINE     , inv_hyp_sin_integral_LP    (* tree))
INTEGRALF(HYPERBOLIC_ALT_COSINE    , hyp_cos_integral_LP        (* tree))
INTEGRALF(INVERSE_ALT_COTANGENT    , inv_tan_cot_integral_LP    ((* tree), MINUS))
INTEGRALF(INVERSE_HYP_COTANGENT    , inv_hyp_tan_cot_integral_LP(* tree))
INTEGRALF(INVERSE_ALT_HYP_COSINE   , inv_hyp_cos_integral_LP    (* tree))
INTEGRALF(HYPERBOLIC_ALT_TANGENT   , hyp_tan_integral_LP        (* tree))
INTEGRALF(INVERSE_ALT_HYP_TANGENT  , inv_hyp_tan_cot_integral_LP(* tree))
INTEGRALF(HYPERBOLIC_ALT_COTANGENT , hyp_cot_integral_LP        (* tree))
INTEGRALF(INVERSE_ALT_HYP_COTANGENT, inv_hyp_tan_cot_integral_LP(* tree))

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

INTEGRALS(PLUS          , integrate_sum       (tree))
INTEGRALS(MINUS         , integrate_sum       (tree))
INTEGRALS(MULTIPLICATION, integrate_product   (tree))
INTEGRALS(DIVISION      , integrate_division  (tree))
INTEGRALS(DEGREE        , integrate_degree    (tree))

//____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

