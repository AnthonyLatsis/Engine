

#define non_expression_command(COMMAND_STR, FUNCTION)	\
																											\
else if (strncmp(COMMAND_STR, 												\
								 input + pointer_for_input,						\
								 strlen(COMMAND_STR)) == ZERO) {			\
	FUNCTION;																						\
	return;																							\
}																											\

#define number_command(NUMBER_STR, NUMBER) 			\
																								\
else if (strncmp(NUMBER_STR, 										\
								input + pointer_for_input, 			\
								strlen(NUMBER_STR)) == ZERO) {	\
	Counter += NUMBER;														\
	pointer_for_input += strlen(NUMBER_STR);     	\
	command_identify();														\
	return;																				\
} 																							\

#define operation_command(COMMAND_STR, FUNCTION) 	\
																									\
else if (strncmp(COMMAND_STR, 										\
								 input + pointer_for_input, 			\
							   strlen(COMMAND_STR)) == ZERO) {	\
	pointer_for_input += strlen(COMMAND_STR) + ONE;	\
	FUNCTION;																				\
	return;																					\
}

operation_command("derivate last"    , command_derivative("derivate last "    , "last"  , Counter))
operation_command("derivate answer"  , command_derivative("derivate answer "  , "answer", Counter))
operation_command("derivative last"  , command_derivative("derivative last "  , "last"  , Counter))
operation_command("derivative answer", command_derivative("derivative answer ", "answer", Counter))
operation_command("integral last"    , command_integral  ("integral last"     , "last"  , Counter))
operation_command("integral answer"  , command_integral  ("integral answer"   , "answer", Counter))
operation_command("integrate last"   , command_integral  ("integrate last"    , "last"  , Counter))
operation_command("integrate answer" , command_integral  ("integrate answer"  , "answer", Counter))
operation_command("derivative"       , command_derivative("derivative "       , "void"  , Counter))
operation_command("derivate"         , command_derivative("derivate "         , "void"  , Counter))
operation_command("integral"         , command_integral  ("integral "         , "void"  , Counter))
operation_command("integrate"        , command_integral  ("integrate "        , "void"  , Counter))
operation_command("tree image"       , command_tree_image("tree image "))

non_expression_command("exit"              			 , command_exit       	  ())
non_expression_command("matrix determinant"			 , command_determinant	  ())
non_expression_command("determinant matrix"			 , command_determinant    ())
non_expression_command("determinant"       			 , command_determinant    ())
non_expression_command("system solution"   			 , command_system_solution())
non_expression_command("equation system"             , command_system_solution())
non_expression_command("solve linear system"         , command_system_solution())
non_expression_command("solve equation system"       , command_system_solution())
non_expression_command("system"                      , command_system_solution())
non_expression_command("solve"                       , command_system_solution())
non_expression_command("solve system"                , command_system_solution())
non_expression_command("linear equation system"      , command_system_solution())
non_expression_command("solve linear equation system", command_system_solution())

number_command("first"      ,      first) 
number_command("second"     ,     second)
number_command("third"      ,      third)
number_command("fourth"     ,     fourth)
number_command("fifth"      ,      fifth)
number_command("sixth"      ,      sixth)
number_command("seventh"    ,    seventh)
number_command("eighth"     ,     eighth)
number_command("ninth"      ,      ninth)
number_command("tenth"      ,      tenth)
number_command("eleventh"   ,   eleventh)
number_command("twelvth"    ,    twelvth)
number_command("thirteenth" , thirteenth)
number_command("fifteenth"  ,  fifteenth)
number_command("sixteenth"  ,  sixteenth)
number_command("seventeenth",seventeenth)
number_command("eighteenth" , eighteenth)
number_command("nineteenth" , nineteenth)
number_command("twentieth"  ,  twentieth)
number_command("twenty"     ,     twenty)
number_command("thirty"     ,     thirty)
number_command("fourty"     ,     fourty)
number_command("fifty"      ,      fifty)
number_command("sixty"      ,      sixty)
number_command("seventy"    ,    seventy)
number_command("eighty"     ,     eighty)
number_command("ninety"     ,     ninety)
number_command("thirtieth"  ,  thirtieth)
number_command("fourtieth"  ,  fourtieth)
number_command("fiftieth"   ,   fiftieth)
number_command("sixtieth"   ,   sixtieth)
number_command("seventieth" , seventieth)
number_command("eightieth"  ,  eightieth)
number_command("nintieth"   ,  ninetieth)
number_command("hundredth"  ,  hundredth)








