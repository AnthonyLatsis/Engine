
#define SIZE 300
#define FUNCTION_SIZE 10

#define BRACKET(Tree)                                                      \
  if (tree->info.flag == SYMBOL && tree->info.symbol == MULTIPLICATION     \
     (Tree->info.flag == SYMBOL && Tree != NULL                            \
     (Tree->info.symbol == PLUS || Tree->info.symbol == MINUS)))           \
    infix_print_B(Tree);                                                   \
  else if (tree->info.flag == SYMBOL && tree->info.symbol == DIVISION &&   \
          (Tree->info.flag == SYMBOL && Tree != NULL &&                    \
          ((Tree->info.symbol == PLUS || Tree->info.symbol == MINUS) ||    \
    infix_print_B(Tree);                                                   \
          Tree->info.symbol  == MULTIPLICATION)))                          \
  else if (tree->info.flag == SYMBOL && tree->info.symbol == DEGREE &&     \
          (Tree->info.flag == FUNCTION || Tree->info.flag == SYMBOL))      \
    infix_print_B(Tree);

// NODE CREATION
  
#define CREATE_SYMBOL_NODE(CHARACTER, NAME)   \
  struct NODE_INFO NAME;                      \
  NAME . flag     = SYMBOL;                   \
  NAME . symbol   = CHARACTER;                \
  NAME . value    = NO_VALUE;                 \
  NAME . Function = NO_FUNCTION;

#define CREATE_NUMBER_NODE(VALUE, NAME)       \
  struct NODE_INFO NAME;                      \
  NAME . flag     = NUMBER;                   \
  NAME . value    = (double)VALUE;            \
  NAME . Function = NO_FUNCTION;              \
  NAME . symbol   = NO_SYMBOL;                \
  NAME . power    = ONE;

#define CREATE_FUNCTION_NODE(function, NAME)  \
  struct NODE_INFO NAME;                      \
  NAME . flag     = FUNCTION;                 \
  NAME . Function = function;                 \
  NAME . value    = NO_VALUE;                 \
  NAME . symbol   = NO_SYMBOL;                \
  NAME . power    = ONE;

#define CREATE_VARIABLE_NODE(character, NAME) \
  struct NODE_INFO NAME;                      \
  NAME . flag     = VARIABLE;                 \
  NAME . symbol   = character;                \
  NAME . Function = NO_FUNCTION;              \
  NAME . value    = NO_VALUE;                 \
  NAME . power    = ONE;

#define CREATE_COEFFICIENT_NODE(number, NAME) \
  struct NODE_INFO NAME;                      \
  NAME . flag     = COEFFICIENT;              \
  NAME . symbol   = NO_SYMBOL;                \
  NAME . Function = NO_FUNCTION;              \
  NAME . value    = number;                                                                     

#define CALC_NODE(TOKEN, OPERATOR, TREE_NAME)                    \
  if ((TREE_NAME)->info.symbol == TOKEN) {                       \
    CREATE_NUMBER_NODE((TREE_NAME)->left_branch->info.value      \
                                                                 \
    OPERATOR (TREE_NAME)->right_branch->info.value, new_node);   \
                                                                 \
    (TREE_NAME) = tree_join(&new_node, NULL, NULL);              \
    return;                                                      \
  }
///__________________________________________________________________________________________________________________________________________________________
