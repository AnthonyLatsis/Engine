

struct INT_ARRAY {
	int * array;
	int length;

}typedef INT_ARRAY;

struct POSITION {
	int position_number;
	char position_symbol;

	struct INT_ARRAY * followpos;

}typedef POSITION;

struct POSITION_ARRAY {
	struct POSITION * array;

	int length;

}typedef POSITION_ARRAY;

struct NODE {
	bool nullable;
	int flag;
	char symbol;
	int number;

}typedef NODE;

struct MACHINE_TREE {
	struct INT_ARRAY * firstpos;
	struct INT_ARRAY * lastpos;

	struct NODE info;

	struct MACHINE_TREE * left_branch;
	struct MACHINE_TREE * right_branch;

}typedef MACHINE_TREE;

struct TRANSITION {
	char symbol;

	struct CONDITION_LIST * condition;

}typedef TRANSITION;

struct TRANSITION_LIST {
	int number;

	struct TRANSITION * transition;
	struct TRANSITION_LIST * next;
	struct TRANSITION_LIST * prev;
}typedef TRANSITION_LIST;

struct CONDITION {
	bool flag;
	int number;

	struct INT_ARRAY * name; 
	struct TRANSITION_LIST * transitions;

}typedef CONDITION;

struct CONDITION_LIST {
	int number;

	struct CONDITION * condition;
	struct CONDITION_LIST * next;
	struct CONDITION_LIST * prev;

}typedef CONDITION_LIST;

struct MACHINE {
	struct CONDITION_LIST * machine;
	struct MACHINE_TREE * re_tree;

	char * alphabet;

}typedef MACHINE;

/////////////////////////////////////////////// GLOBAL VARIABLES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int COUNTER = 0;
char CHARACTER;

INT_ARRAY * CONDITION_NAME_BOX;

POSITION_ARRAY * POSITIONS;


void machine_condition_search(MACHINE * MACHINE, CONDITION_LIST * NODE);

bool int_array_belongs(INT_ARRAY * ARRAY, int ELEMENT);

////////////////////////////////////////////// MEMORY ALLOCATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MACHINE * machine_allocate()
{
	MACHINE * machine     = calloc(ONE, sizeof(MACHINE));

	machine->alphabet   = calloc(POSITION_COUNTER, sizeof(char));

	return machine;
}

CONDITION_LIST * condition_list_create()
{
	CONDITION_LIST * list = calloc(ONE, sizeof(CONDITION_LIST));

	return list;
}

TRANSITION_LIST * transition_list_create()
{
	TRANSITION_LIST * list = calloc(ONE, sizeof(TRANSITION_LIST));

	return list;
}

INT_ARRAY * int_array_allocate(int length)
{
	INT_ARRAY * RESULT = calloc(ONE, sizeof(INT_ARRAY));

	RESULT->length = length;

	return RESULT;
}

void position_array_allocate()
{
	int COUNTER = ZERO;

	POSITIONS = calloc(ONE, sizeof(POSITION_ARRAY));

	POSITIONS->length = POSITION_COUNTER;

	POSITIONS->array  = calloc(POSITION_COUNTER, sizeof(POSITION));

	for (COUNTER = ZERO; COUNTER < POSITION_COUNTER; COUNTER ++)
	
		POSITIONS->array[COUNTER].followpos = int_array_allocate(ZERO);
}

////////////////////////////////////////////// LIST MANIPULATING //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CONDITION_LIST * condition_list_add(CONDITION_LIST * NODE, CONDITION * CONDITION)
{
	if (NODE == NULL)
	{
		NODE = condition_list_create();

		NODE->condition = CONDITION;

		return NODE;
	}
	if (NODE->next == NULL)
	{
		NODE->next = condition_list_add(NODE->next, CONDITION);

		NODE->next->prev = NODE;

		return NODE;
	}
	NODE->next = condition_list_add(NODE->next, CONDITION);

	return NODE;
}

TRANSITION_LIST * transition_list_add(TRANSITION_LIST * NODE, TRANSITION * TRANSITION)
{
	if (NODE == NULL)
	{
		NODE = transition_list_create();

		NODE->transition = TRANSITION;

		return  NODE;
	}
	if (NODE->next == NULL)
	{
		NODE->next = transition_list_add(NODE->next, TRANSITION);

		NODE->next->prev = NODE;

		return NODE;
	}
	NODE->next = transition_list_add(NODE->next, TRANSITION);

	return NODE;
}

////////////////////////////////////////////// PRINTING  METHODS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void machine_print_alphabet(MACHINE * MACHINE)
{
	assert(MACHINE != NULL);

	int COUNTER = ZERO;

	printf("T = {");

	for (COUNTER = ZERO; COUNTER < strlen(MACHINE->alphabet); COUNTER ++)
	{
		if (COUNTER == strlen(MACHINE->alphabet) - ONE) 

			printf("%c", MACHINE->alphabet[COUNTER]);

		else printf("%c,", MACHINE->alphabet[COUNTER]);
	}
	printf("}\n\n");
}

void int_array_print(INT_ARRAY * ARRAY)
{
	assert(ARRAY != NULL);

	int COUNTER = ZERO;

	printf("{");

	for (COUNTER = ZERO; COUNTER < (ARRAY->length); COUNTER ++)
	{
		if (COUNTER == (ARRAY->length) - ONE) 

			printf("%d" , ARRAY->array[COUNTER]);
		else 
			printf("%d,", ARRAY->array[COUNTER]);
	}
	printf("}");
}

void condition_list_print(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return;
		
	int_array_print(CONDITIONS->condition->name);

	if (CONDITIONS->next != NULL) printf(",");

	condition_list_print(CONDITIONS->next);
}

void condition_list_print_conditions(CONDITION_LIST * CONDITIONS)
{
	assert(CONDITIONS != NULL);

	printf("Q = {");

	condition_list_print(CONDITIONS);

	printf("}\n\n");
}

bool condition_list_check_set_end(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return true;

	if (int_array_belongs(CONDITIONS->condition->name, POSITION_COUNTER))
	
		return false;

	else return true && condition_list_check_set_end(CONDITIONS->next);
}

void condition_list_print_ending_conditions(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return;

	if (int_array_belongs(CONDITIONS->condition->name, POSITION_COUNTER))
	{
		int_array_print(CONDITIONS->condition->name);

		if(!condition_list_check_set_end(CONDITIONS->next)) printf(",");
	}
	condition_list_print_ending_conditions(CONDITIONS->next);
}

void condition_list_print_first(CONDITION_LIST * CONDITIONS)
{
	printf("q = ");

	int_array_print(CONDITIONS->condition->name);

	printf("\n\n");
}

void machine_print_ending_conditions(MACHINE * MACHINE)
{
	printf("F = {");

	condition_list_print_ending_conditions(MACHINE->machine);

	printf("}\n\n");
}

////////////////////////////////////////////// RE_TREE MANIPULATION ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TREE * re_tree_initialize()
{
	pointer_for_input         = ZERO;

    pointer_for_struct        = ZERO;

    second_pointer_for_struct = ZERO;

    Counter                   = ZERO;

    input         = calloc(SIZE, sizeof(char));

    parced_input  = calloc(SIZE, sizeof(struct NODE_INFO));

    gets(input);

    distribution_func_RE();

    return GET_EXPRESSION();
}

MACHINE_TREE * re_tree_convert(TREE * TREE)
{
	if (TREE == NULL) return NULL;
	
	struct MACHINE_TREE * NEW = calloc(ONE, sizeof(MACHINE_TREE));

	NEW->firstpos 	      = int_array_allocate(ZERO);
	NEW->lastpos 		      = int_array_allocate(ZERO);

	NEW->info.symbol 	  = TREE->info.symbol;
	NEW->info.flag  	  = TREE->info.flag;
	NEW->info.number 	  = TREE->info.value; 

	NEW->left_branch        = re_tree_convert(TREE->left_branch);
	NEW->right_branch       = re_tree_convert(TREE->right_branch);

	return NEW;	 
}

void re_tree_modification(TREE * TREE)
{
	assert(TREE != NULL);

	if (TREE->left_branch  != NULL)

		re_tree_modification(TREE->left_branch);

	if (TREE->right_branch != NULL)

		re_tree_modification(TREE->right_branch);

	if (TREE->info.flag   == SYMBOL &&

	    TREE->info.symbol == DEGREE)
	{
		TREE->right_branch  = NULL;

		TREE->info.flag   = VARIABLE;

		TREE->info.symbol = ITERATION;
	}
}

struct TREE * re_tree_add_end(TREE ** TREE)
{
	assert(* TREE != NULL);

	(* TREE) = T_operator(MULTIPLICATION, (* TREE), T_variable(END));

	return (* TREE);
}

////////////////////////////////////////////// METHODS FOR INT_ARRAYS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool int_array_belongs(INT_ARRAY * ARRAY, int ELEMENT)
{
	assert(ARRAY != NULL);

	int COUNTER = ZERO;

	for (COUNTER = ZERO; COUNTER < (ARRAY->length); COUNTER ++)

		if (ARRAY->array[COUNTER] == ELEMENT) return true;
	
	return false;
}

void int_array_add_element(INT_ARRAY * ARRAY, int ELEMENT)
{
	assert(ARRAY != NULL);

	ARRAY->length ++;

	ARRAY->array = 

	realloc(ARRAY->array, (ARRAY->length) * sizeof(int));
	
	ARRAY->array[ARRAY->length - ONE] = ELEMENT;
}

INT_ARRAY * int_array_intersection(INT_ARRAY * FIRST, INT_ARRAY * SECOND)
{
	assert(FIRST != NULL && SECOND != NULL);

	int counter_1 = ZERO, counter_2 = ZERO; 

	int LENGTH_1 = FIRST->length;

	int LENGTH_2 = SECOND->length;

	INT_ARRAY * RESULT = int_array_allocate(ZERO);

	for (counter_1 = ZERO; counter_1 < LENGTH_1; counter_1 ++)
	{
		for (counter_2 = ZERO; counter_2 < LENGTH_2; counter_2 ++)
		{
			if (FIRST->array[counter_1] == SECOND->array[counter_2])

				int_array_add_element(RESULT, FIRST->array[counter_1]);
		}
	}
	return RESULT;
}
	
bool int_array_compare(INT_ARRAY * FIRST, INT_ARRAY * SECOND)
{
	assert(FIRST != NULL && SECOND != NULL);

	if (FIRST->length != SECOND->length) return false;

	int counter_1 = ZERO, counter_2 = ZERO, flag = ZERO;

	int LENGTH_1  = FIRST->length;

	for (counter_1 = ZERO; counter_1 < LENGTH_1; counter_1 ++)
	{
		for (counter_2 = ZERO; counter_2 < LENGTH_1; counter_2 ++)
		{
			if (FIRST->array[counter_1] == SECOND->array[counter_2])

				flag ++;
		}
		if (flag == ONE) flag --;

		else return false;
	}
	return true;
}


INT_ARRAY * int_array_combine(INT_ARRAY * FIRST, INT_ARRAY * SECOND)
{
	assert(FIRST != NULL && SECOND != NULL);

	INT_ARRAY * INTERSECTION = int_array_intersection(FIRST, SECOND);

	INT_ARRAY * RESULT = int_array_allocate(ZERO);

	int counter = ZERO;

	for (counter = ZERO; counter < (FIRST->length); counter ++)
	{
		if (!int_array_belongs(INTERSECTION, FIRST->array[counter]))

			int_array_add_element(RESULT, FIRST->array[counter]); 
	}
	for (counter = ZERO; counter < (SECOND->length); counter ++)
	{
		if (!int_array_belongs(INTERSECTION, SECOND->array[counter]))

			int_array_add_element(RESULT, SECOND->array[counter]);
	}	
	for (counter = ZERO; counter < (INTERSECTION->length); counter ++)
	
		int_array_add_element(RESULT, INTERSECTION->array[counter]);
	
	free(INTERSECTION); return RESULT;
}

////////////////////////////////////////////// FIRSTPOS LASTPOS FOLLOWPOS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void machine_tree_fill_positions(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	if (TREE->left_branch == NULL && TREE->right_branch == NULL)
	{
		int_array_add_element(TREE->firstpos, COUNTER);

		int_array_add_element(TREE->lastpos , COUNTER);

		TREE->info.nullable = false;

		POSITIONS->array[COUNTER].position_number = COUNTER;

		POSITIONS->array[COUNTER ++].position_symbol = 

									TREE->info.symbol;
	}
	if (TREE->left_branch != NULL)

	machine_tree_fill_positions(TREE->left_branch);
	
	if (TREE->right_branch != NULL)

	machine_tree_fill_positions(TREE->right_branch);
}


void machine_fill_alphabet(MACHINE * MACHINE, MACHINE_TREE * TREE)
{
	assert(MACHINE != NULL);

	int counter = ZERO;   bool flag = false;

	int alphabet_length = strlen(MACHINE->alphabet);
	
	if (TREE->left_branch == NULL && TREE->right_branch == NULL)
	{	
		for (counter = ZERO; counter < alphabet_length; counter ++)
		{
			if (MACHINE->alphabet[counter] == TREE->info.symbol) 
			{
				flag = true;

				break;
			}
		}
	 	if (flag == false && TREE->info.symbol != END)

	 		MACHINE->alphabet[alphabet_length] = TREE->info.symbol;
	 	
	 	flag = false;		
	}
	if (TREE->left_branch  != NULL)

		machine_fill_alphabet(MACHINE, TREE->left_branch);

	if (TREE->right_branch != NULL) 

		machine_fill_alphabet(MACHINE, TREE->right_branch);
}

void machine_tree_concatenation_firstpos(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	if (TREE->left_branch->info.nullable)
	{
		TREE->firstpos =

		int_array_combine(TREE->left_branch ->firstpos, 

						  TREE->right_branch->firstpos);
	}
	else
		TREE->firstpos = TREE->left_branch->firstpos;
}

void machine_tree_concatenation_lastpos(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	if (TREE->right_branch->info.nullable)
	{
		TREE->lastpos =

		int_array_combine(TREE->left_branch ->lastpos, 

						  TREE->right_branch->lastpos);
	}
	else
		TREE->lastpos = TREE->right_branch->lastpos;
}

void machine_tree_concatenation(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	machine_tree_concatenation_firstpos(TREE);

	machine_tree_concatenation_lastpos (TREE);

	TREE->info.nullable = (TREE->left_branch ->info.nullable)
		
				  		   && (TREE->right_branch->info.nullable);
}

void machine_tree_union(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	TREE->firstpos = int_array_combine(TREE->left_branch ->firstpos, 

				                         TREE->right_branch->firstpos);

	TREE->lastpos  = int_array_combine(TREE->left_branch ->lastpos,
				
					  					 TREE->right_branch->lastpos);

	TREE->info.nullable = (TREE->left_branch ->info.nullable)
	
				    	   || (TREE->right_branch->info.nullable);
}

void machine_tree_first_last_pos(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	if (TREE->left_branch  != NULL)

		machine_tree_first_last_pos(TREE->left_branch);

	if (TREE->right_branch != NULL) 

		machine_tree_first_last_pos(TREE->right_branch);

	if (TREE->info.flag   == SYMBOL 

	&&  TREE->info.symbol == MULTIPLICATION)

		machine_tree_concatenation(TREE);
	
	if (TREE->info.flag   == SYMBOL 

	&&  TREE->info.symbol == EDGE)
	
		machine_tree_union(TREE);

	if (TREE->info.flag   == VARIABLE 

	&&  TREE->info.symbol == ITERATION)
	{
		TREE->firstpos = TREE->left_branch->firstpos;

		TREE->lastpos  = TREE->left_branch->lastpos;

		TREE->info.nullable  = true;
	}
}

void machine_tree_concatenation_followpos(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	int counter = ZERO, pointer = ZERO;

	int box     = TREE->left_branch->lastpos->length;

	for (counter = ZERO; counter < box; counter ++)
	{
		pointer = TREE->left_branch->lastpos->array[counter];

		POSITIONS->array[pointer].followpos =

		int_array_combine(POSITIONS->array[pointer].followpos,

								TREE->right_branch->firstpos);
	}
}

void machine_tree_iteration_followpos(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);

	int counter = ZERO, pointer = ZERO;

	int box     = TREE->left_branch->lastpos->length;

	for (counter = ZERO; counter < box; counter ++)
	{
		pointer = TREE->left_branch->lastpos->array[counter];

		POSITIONS->array[pointer].followpos = 

		int_array_combine(POSITIONS->array[pointer].followpos,

								 TREE->left_branch->firstpos);
	}
}
	
void machine_tree_find_followpos(MACHINE_TREE * TREE)
{
	assert(TREE != NULL);
	
	if (TREE->left_branch != NULL) 

		machine_tree_find_followpos(TREE->left_branch);

	if (TREE->right_branch != NULL) 

		machine_tree_find_followpos(TREE->right_branch);
	
	if (TREE->info.flag   == SYMBOL 

	&&  TREE->info.symbol == MULTIPLICATION)
	
			machine_tree_concatenation_followpos(TREE);
	
	if (TREE->info.flag   == VARIABLE 

	&&  TREE->info.symbol == ITERATION)
	
			machine_tree_iteration_followpos(TREE);
}

////////////////////////////////////////////// MACHINE CONSTRUCTION ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
CONDITION_LIST * machine_find_condition(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return NULL;

	if (int_array_compare(CONDITION_NAME_BOX, 

			CONDITIONS->condition->name))

		return CONDITIONS;

	return machine_find_condition(CONDITIONS->next);
}

void machine_add_condition(CONDITION_LIST ** CONDITIONS)
{
	CONDITION * NEW = calloc(ONE, sizeof(CONDITION));

	NEW->flag     = false;

	NEW->name     = calloc(ONE, sizeof(INT_ARRAY));

	* (NEW->name) = * CONDITION_NAME_BOX;

	* CONDITIONS = condition_list_add(* CONDITIONS, NEW);
}

void machine_add_transition(CONDITION_LIST * CONDITION, CONDITION_LIST * TRANSITION, int letter)
{
	assert(CONDITION != NULL && TRANSITION != NULL);

	struct TRANSITION * new = calloc(ONE, sizeof(TRANSITION));

	new->symbol = letter;

	new->condition = TRANSITION;

	CONDITION->condition->transitions = 

	transition_list_add(CONDITION->condition->transitions, new);
}

void machine_new_condition(MACHINE * MACHINE, CONDITION_LIST * CONDITION, char CHARACTER)
{
	assert(MACHINE != NULL);

	if (CONDITION_NAME_BOX->length == ZERO || CONDITION_NAME_BOX == NULL)

		return;

	CONDITION_LIST * new = machine_find_condition(MACHINE->machine);

	if (new == NULL)
	{
		machine_add_condition(&(MACHINE->machine));

		new = machine_find_condition(MACHINE->machine);
		
		machine_add_transition(CONDITION, new, CHARACTER);
	}
	else

 		machine_add_transition(CONDITION, new, CHARACTER);

 	CONDITION_NAME_BOX->length = ZERO;
}

////////////////////////////////////////////// CONDITION CREATING ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void condition_mark(CONDITION_LIST * CONDITION)
{
	assert(CONDITION != NULL);

	CONDITION->condition->flag = true;
}

void machine_create_condition(MACHINE * MACHINE, CONDITION_LIST * CONDITION)
{
	assert(MACHINE != NULL);

	condition_mark(CONDITION);

	int pointer = ZERO, counter = ZERO, box_1 = ZERO;

	char box_2 = ZERO;

	int alphabet_length  = strlen(MACHINE->alphabet);

	int condition_length = CONDITION->condition->name->length;

	for (pointer = ZERO; pointer < alphabet_length; pointer ++)
	{	
		for (counter = ZERO; counter < condition_length; counter ++)
		{	
			box_1 = CONDITION->condition->name->array[counter];

			box_2 = POSITIONS->array[box_1].position_symbol;

			if (box_2 == MACHINE->alphabet[pointer])
			{
				CONDITION_NAME_BOX = 

				int_array_combine(CONDITION_NAME_BOX,

				POSITIONS->array[box_1].followpos);
			}

			CHARACTER = MACHINE->alphabet[pointer];
		}
		machine_new_condition(MACHINE, CONDITION, CHARACTER);
	}
	machine_condition_search(MACHINE, MACHINE->machine);	
}

void machine_condition_search(MACHINE * MACHINE, CONDITION_LIST * NODE)
{
	assert(MACHINE != NULL);

	if (NODE == NULL) return;
	
	if (NODE->condition->flag)
	{
		machine_condition_search(MACHINE, NODE->next);

		return;
	}
	machine_create_condition(MACHINE, NODE);
}

void machine_first_condition(MACHINE * MACHINE)
{
	assert(MACHINE != NULL);
	
	CONDITION_NAME_BOX = int_array_allocate(ZERO);

	CONDITION_NAME_BOX = 

	int_array_combine(CONDITION_NAME_BOX, 

		 MACHINE->re_tree->firstpos);

	machine_add_condition(&(MACHINE->machine));	

	CONDITION_NAME_BOX->length = ZERO;
}

////////////////////////////////////////////// MAIN FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "table.h"

MACHINE * machine_constructer()
{
	MACHINE * MACHINE  = machine_allocate();

	struct TREE * TREE = re_tree_initialize(); 	
	
	TREE = re_tree_add_end(&TREE);

	re_tree_modification(TREE);

	MACHINE->re_tree = re_tree_convert(TREE);

	COUNTER = ZERO;
	
	position_array_allocate();

	machine_tree_fill_positions(MACHINE->re_tree);

	machine_fill_alphabet(MACHINE, MACHINE->re_tree);

	printf("\nM = {Q,T,D,q,F}\n\n");

	machine_print_alphabet (MACHINE);
	
	machine_tree_first_last_pos(MACHINE->re_tree);

	machine_tree_find_followpos(MACHINE->re_tree); 

	machine_first_condition(MACHINE);

	machine_condition_search(MACHINE, MACHINE->machine);

	condition_list_print_conditions(MACHINE->machine); 

	machine_print_ending_conditions(MACHINE);

	condition_list_print_first(MACHINE->machine);

	table_followpos(MACHINE);

	table_transitions(MACHINE);

	tree_image(TREE); free(TREE);

	return MACHINE;
}

