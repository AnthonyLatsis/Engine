/*_________________________________________________________________*/

#define DISTRIBUTE_FUNCS(function)                                  \
                                                                    \
if (strncmp(functions, function, pointer_for_functions) == zero)    \
                                                                    \
{FUNC(ZERO, function, NO_SYMBOL, FUNCTION); return;}

/*_________________________________________________________________*/

///__________________Trigonometric functions_________________________

    DISTRIBUTE_FUNCS(SINE);
    DISTRIBUTE_FUNCS(COSINE                  );
    DISTRIBUTE_FUNCS(TANGENT                 );
    DISTRIBUTE_FUNCS(ALT_TANGENT             );
    DISTRIBUTE_FUNCS(COTANGENT               );
    DISTRIBUTE_FUNCS(ALT_COTANGENT           );

///__________________Degree functions________________________________

    DISTRIBUTE_FUNCS(EXPONENT                );
    DISTRIBUTE_FUNCS(LOGARITHM               );

///_______________Inverse trigonometric functions____________________

    DISTRIBUTE_FUNCS(INVERSE_SINE            );
    DISTRIBUTE_FUNCS(INVERSE_COSINE          );
    DISTRIBUTE_FUNCS(INVERSE_TANGENT         );
    DISTRIBUTE_FUNCS(INVERSE_COTANGENT       );
    DISTRIBUTE_FUNCS(INVERSE_ALT_TANGENT     );
    DISTRIBUTE_FUNCS(INVERSE_ALT_COTANGENT   );

///_____________Hyperbolic trigonometric functions___________________

    DISTRIBUTE_FUNCS(HYPERBOLIC_SINE         );
    DISTRIBUTE_FUNCS(HYPERBOLIC_ALT_SINE     );
    DISTRIBUTE_FUNCS(HYPERBOLIC_COSINE       );
    DISTRIBUTE_FUNCS(HYPERBOLIC_ALT_COSINE   );
    DISTRIBUTE_FUNCS(HYPERBOLIC_ALT_TANGENT  );
    DISTRIBUTE_FUNCS(HYPERBOLIC_TANGENT      );
    DISTRIBUTE_FUNCS(HYPERBOLIC_COTANGENT    );
    DISTRIBUTE_FUNCS(HYPERBOLIC_ALT_COTANGENT);

///______Inverse_hyperbolic_trigonometric_functions__________________

    DISTRIBUTE_FUNCS(INVERSE_HYP_SINE         );
    DISTRIBUTE_FUNCS(INVERSE_ALT_HYP_SINE     );
    DISTRIBUTE_FUNCS(INVERSE_HYP_COSINE       );
    DISTRIBUTE_FUNCS(INVERSE_ALT_HYP_COSINE   );
    DISTRIBUTE_FUNCS(INVERSE_ALT_HYP_TANGENT  );
    DISTRIBUTE_FUNCS(INVERSE_HYP_TANGENT      );
    DISTRIBUTE_FUNCS(INVERSE_HYP_COTANGENT    );
    DISTRIBUTE_FUNCS(INVERSE_ALT_HYP_COTANGENT);
///__________________________________________________________________


