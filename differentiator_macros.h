

#define  DIFF(TOKEN, DIFF_FUNC) if ((*tree)->info.Function == TOKEN) {DIFF_FUNC; return;}
#define DIFFS(TOKEN, DIFF_FUNC) if ((*tree)->info.symbol == TOKEN) {DIFF_FUNC; return;}

DIFF(SINE         , differentiate_sine(tree))
DIFF(COSINE       , differentiate_cosine(tree))
DIFF(TANGENT      , differentiate_tangent(tree))
DIFF(COTANGENT    , differentiate_cotangent(tree))
DIFF(ALT_TANGENT  , differentiate_tangent(tree))
DIFF(ALT_COTANGENT, differentiate_cotangent(tree))

DIFF(EXPONENT , differentiate_exponent(tree))
DIFF(LOGARITHM, differentiate_logarithm(tree))

DIFF(INVERSE_SINE         , differentiate_inv_sin_cos(tree, SINE))
DIFF(INVERSE_COSINE       , differentiate_inv_sin_cos(tree, COSINE))
DIFF(INVERSE_TANGENT      , differentiate_inv_tan_cot(tree, TANGENT))
DIFF(INVERSE_COTANGENT    , differentiate_inv_tan_cot(tree, COTANGENT))
DIFF(INVERSE_ALT_TANGENT  , differentiate_inv_tan_cot(tree, TANGENT))
DIFF(INVERSE_ALT_COTANGENT, differentiate_inv_tan_cot(tree, COTANGENT))

DIFF(HYPERBOLIC_SINE         , differentiate_hyp_sin_cos(tree, HYPERBOLIC_COSINE))
DIFF(HYPERBOLIC_COSINE       , differentiate_hyp_sin_cos(tree, HYPERBOLIC_SINE))
DIFF(HYPERBOLIC_ALT_SINE     , differentiate_hyp_sin_cos(tree, HYPERBOLIC_COSINE))
DIFF(HYPERBOLIC_ALT_COSINE   , differentiate_hyp_sin_cos(tree, HYPERBOLIC_SINE))
DIFF(HYPERBOLIC_TANGENT      , differentiate_hyp_tan_cot(tree, HYPERBOLIC_COSINE))
DIFF(HYPERBOLIC_COTANGENT    , differentiate_hyp_tan_cot(tree, HYPERBOLIC_SINE))
DIFF(HYPERBOLIC_ALT_TANGENT  , differentiate_hyp_tan_cot(tree, HYPERBOLIC_COSINE))
DIFF(HYPERBOLIC_ALT_COTANGENT, differentiate_hyp_tan_cot(tree, HYPERBOLIC_SINE))

DIFF(INVERSE_HYP_SINE         , differentiate_inv_hyp_sin(tree))
DIFF(INVERSE_HYP_COSINE       , differentiate_inv_hyp_cos(tree))
DIFF(INVERSE_ALT_HYP_SINE     , differentiate_inv_hyp_sin(tree))
DIFF(INVERSE_ALT_HYP_COSINE   , differentiate_inv_hyp_cos(tree))
DIFF(INVERSE_HYP_TANGENT      , differentiate_inv_hyp_tan_cot (tree))
DIFF(INVERSE_HYP_COTANGENT    , differentiate_inv_hyp_tan_cot (tree))
DIFF(INVERSE_ALT_HYP_TANGENT  , differentiate_inv_hyp_tan_cot (tree))
DIFF(INVERSE_ALT_HYP_COTANGENT, differentiate_inv_hyp_tan_cot (tree))

DIFFS(PLUS          , differentiate_sum(tree))
DIFFS(MINUS         , differentiate_sum(tree))
DIFFS(MULTIPLICATION, differentiate_product(tree))
DIFFS(DIVISION      , differentiate_division(tree))
DIFFS(DEGREE        , differentiate_degree(tree))

