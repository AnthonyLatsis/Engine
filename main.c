//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "defines.h"

/*<><><><><><><><><><><><><><><><><> CONSTANTS <><><><><><><><><><><><><><><><><><>*/

const int ZERO                      = 0;
const int zero                      = 0;
const int ONE                       = 1;           
const int TWO                       = 2;
const int THREE                     = 3;
const int FOUR                      = 4;


const char * integral               = "∫";
const char PLUS_MINUS               = '#';
const char PLUS                     = '+';
const char MINUS                    = '-';
const char MULTIPLICATION           = '*';
const char DEGREE                   = '^';
const char DIVISION                 = '/';         
const char OPENING_BRACKET          = '(';  
const char CLOSING_BRACKET          = ')';          
const char SPACE                    = ' ';
const char DASH                     = '-';
const char EDGE                     = '|';
const char UNDERSCORE               = '_';
const char ITERATION                = 'i';
const char END                      = '#';
const char FIGURE_BRACKET_OPEN      = '{';
const char FIGURE_BRACKET_CLOSE     = '}';
const char COMA                     = ',';


/*<><><><><><><><><><><><><> LEXICAL ANALISYS TOOLS <><><><><><><><><><><><><><><><>*/

FILE * file;

char global_variable                = 'x';

char * input;                                       

int pointer_for_struct              = 0;
int pointer_for_input               = 0;

int second_pointer_for_struct       = 0;

/*<><><><><><><><><><><><><><><><> VOIDS FOR EMPTY FIELDS <><><><><><><><><><><><><><>*/

char * NO_FUNCTION                  = "0";

const int NO_VALUE                  = 0;         
const char NO_SYMBOL                = '0';
const char * VOID_BOX               = "           ";

/*<><><><><><><><><><><><><><><><><> TREE FLAGS <><><><><><><><><><><><><><><><><><><>*/

const int NUMBER                    = 0;
const int SYMBOL                    = 1;
const int FUNCTION                  = 2;          
const int VARIABLE                  = 3;
const int VOID						= 4;

/*<><><><><><><><><><><><><><><><> OPTIMIZATION TOOLS <><><><><><><><><><><><><><><><>*/

int tree_comparison                 = 0;

int similarity_number               = 0;         

struct TREE * COPY                  = NULL;                                  

/*<><><><><><><><><><><><><><><><> MATHEMATICAL_FUNCTIONS <><><><><><><><><><><><><><><><><>*/

char * SINE                         = "sin";
char * COSINE                       = "cos";
char * SECANT                       = "sec";
char * COSECANT                     = "scs";
char * TANGENT                      = "tan";
char * ALT_TANGENT                  = "tg";
char * ALT_COTANGENT                = "ctg";
char * COTANGENT                    = "cot";
char * EXPONENT                     = "exp";
char * LOGARITHM                    = "ln";
char * INVERSE_SINE                 = "arcsin";
char * INVERSE_COSINE               = "arccos";
char * INBERSE_SECANT               = "arcsec";
char * INVERSE_COSECANT             = "arccsc";
char * INVERSE_TANGENT              = "arctan";
char * INVERSE_ALT_TANGENT          = "arctg";
char * INVERSE_COTANGENT            = "arccot";
char * INVERSE_ALT_COTANGENT        = "arcctg";
char * HYPERBOLIC_SINE              = "sinh";
char * HYPERBOLIC_ALT_SINE          = "sh";
char * HYPERBOLIC_ALT_COSINE        = "ch";         
char * HYPERBOLIC_COSINE            = "cosh";
char * HYPERBOLIC_TANGENT           = "tanh";
char * HYPERBOLIC_COTANGENT         = "coth";
char * HYPERBOLIC_ALT_TANGENT       = "th";
char * HYPERBOLIC_ALT_COTANGENT     = "cth";
char * INVERSE_HYP_SINE             = "arcsinh";
char * INVERSE_ALT_HYP_SINE         = "arcsh";
char * INVERSE_HYP_COSINE           = "arccosh";
char * INVERSE_ALT_HYP_COSINE       = "arcch";
char * INVERSE_HYP_TANGENT          = "arctanh";
char * INVERSE_ALT_HYP_TANGENT      = "arcth";
char * INVERSE_HYP_COTANGENT        = "arccoth";
char * INVERSE_ALT_HYP_COTANGENT    = "arccth";
char * SQUARE_ROOT                  = "sqrt";
char * CUBE_ROOT                    = "cbrt";
char * ABSOLUTE_VALUE               = "abs";
char * SIGNUM_FUNCTION              = "sign";
char * ALT_SIGNUM_FUNCTION          = "sgn";

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

#include "tree.h"

struct NODE_INFO * parced_input;

#include "Matrix_library.h"
#include "recursive_descent.h"
#include "tree_image.h"
#include "tree_optimization.h"
#include "differentiator.h"
#include "integral_templates.h"
#include "integrator.h"
#include "lexical_analisys.h"
#include "machine.h"


/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

int main()
{
   /* struct MACHINE * machine = machine_constructer();


    free(machine);
    return 0;*/


    //command_input();
    pointer_for_input         = 0;

    pointer_for_struct        = 0;

    second_pointer_for_struct = 0;

    Counter                   = 0;

    input = calloc(SIZE, sizeof(char));

    parced_input = calloc(SIZE, sizeof(struct NODE_INFO));
    
    gets(input);

    distribution_func();

    //printf_boxes();

    struct TREE * tree = GET_EXPRESSION();

    printf("\nderivative expression:\n\n");

    struct TREE * derivative = differentiate(tree);

    infix_print(derivative);
    //full_optimization(&derivative);

    printf("\n\ngiven expression tree:\n");

    tree_image(tree);

    printf("\n\nderivative tree:\n");

    tree_image(derivative);
    //full_optimization(&tree);
}
//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
