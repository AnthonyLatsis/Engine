//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
/////////////////////////////////////////////// STRUCTURES AND GLOBALS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

struct TABLE
{
	int length;
	
	int height;

	char ** array;

	INT_ARRAY * pillars;

}typedef TABLE;


const char * position   = "position";
const char * symbol     = "symbol";
const char * followpos  = "followpos";
const char * condition  = "condition";
const char * transition = "transition";

int HEIGHT = ZERO;

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
/////////////////////////////////////////////// CONSTRUCTERS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––-

TABLE * table_allocate()
{
	TABLE * table = calloc(ONE, sizeof(TABLE));

	return table;
}

char ** char_array_allocate(int height, int length)
{
	char ** array = calloc(height, sizeof(char *));

	int counter = ZERO;

	for (counter = ZERO; counter < height; counter ++)
	
		array[counter] = calloc(length, sizeof(char));

	return array;
} 

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
/////////////////////////////////////////////// CALCULATION ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––-

void int_array_create_set(INT_ARRAY * ARRAY, char * result)
{
	int counter = ZERO, pointer = ONE;

	char * box = calloc(MAX_NUMBER_LENGTH, sizeof(char));

	sprintf(result, "%c", FIGURE_BRACKET_OPEN);

	for (counter = ZERO; counter < (ARRAY -> length); counter ++)
	{
		sprintf(box, "%d", ARRAY -> array[counter]);

		sprintf(result + pointer, "%d", ARRAY -> array[counter]);

		pointer += strlen(box);

		if (counter != (ARRAY -> length - ONE))
		{
			sprintf(result + pointer, "%c", COMA);

			pointer ++;
		}
	}
	sprintf(result + pointer, "%c", FIGURE_BRACKET_CLOSE);

	free(box);
}

int int_array_set_length(INT_ARRAY * ARRAY)
{
	int pointer = ZERO, BOX = ZERO;
	
	for (pointer = ZERO; pointer < (ARRAY -> length); pointer ++)
	{
		array = calloc(MAX_NUMBER_LENGTH, sizeof(char));

		sprintf(array, "%d", 

		ARRAY -> array[pointer]);

		BOX += strlen(array);

		free(array);
	}
	BOX += (ARRAY -> length) + ONE;

	return BOX;
}

int table_pillar_middle(TABLE * table, int pillar_number)
{
	int middle = table -> pillars -> array[pillar_number] + ONE - 

	table -> pillars -> array[pillar_number - ONE];

	return table -> pillars -> array[pillar_number - ONE] + middle / TWO;
}

void table_insert_set(TABLE * table, const char * set, int pillar)
{	
	int counter = ZERO, pointer = ZERO, position = ZERO;

	int middle  = table_pillar_middle(table, pillar);

	int start  = middle - (strlen(set) / TWO);

	position = start;

	for (counter = start; counter < strlen(set) + start; counter ++)
	
		table -> array[HEIGHT][counter] = set[counter - start]; 	
}

int transition_list_largest_transition(TRANSITION_LIST * TRANSITIONS)
{
	if (TRANSITIONS == NULL) return ZERO;

	return 

	(max(int_array_set_length(TRANSITIONS -> transition -> condition ->

	 condition -> name), transition_list_largest_transition(TRANSITIONS -> next)));
}

int condition_list_largest_transition(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return ZERO;

	return 

	(max(transition_list_largest_transition(CONDITIONS -> condition ->

	transitions), condition_list_largest_transition(CONDITIONS -> next)));
}

int condition_list_largest_condition(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return ZERO;

 	if (CONDITIONS -> condition -> transitions == NULL) return ZERO;

	return 

	max(int_array_set_length(CONDITIONS -> condition -> name),

		condition_list_largest_condition(CONDITIONS -> next));
}

//____________________________________________FOLLOWPOS_TABLE______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int table_followpos_height()
{
	return 

	((POSITION_COUNTER + ONE) * TWO) + ONE;
}

int largest_followpos               	(int counter)
{
	if (counter == POSITION_COUNTER) return ZERO;

	return 

	max(int_array_set_length(POSITIONS -> array[counter] . followpos),

									 largest_followpos(counter + ONE));
}

int table_followpos_length(MACHINE * MACHINE, TABLE * table)
{
	int second_pillar = strlen(position) + THREE;

	int third_pillar  = second_pillar + strlen(symbol) + THREE;

	int fourth_pillar = max(largest_followpos(ZERO), strlen(transition))

	+ third_pillar + THREE;

	table -> pillars -> array[ZERO]  = ZERO;

	table -> pillars -> array[ONE]   = second_pillar;

	table -> pillars -> array[TWO]   = third_pillar;

	table -> pillars -> array[THREE] = fourth_pillar;

	return fourth_pillar + ONE;
}

//______________________________________________TRANSITIONS_TABLE__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int transitions_count(TRANSITION_LIST * TRANSITIONS)
{
	if (TRANSITIONS == NULL) return ZERO;

	else return ONE + transitions_count(TRANSITIONS -> next);
}

int table_transition_height(CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return THREE;

	return 

	transitions_count(CONDITIONS -> condition -> transitions) * TWO +

	table_transition_height(CONDITIONS -> next);
}

int table_transition_length(MACHINE * MACHINE, TABLE * table)
{
	int box_1 = condition_list_largest_condition(MACHINE -> machine);

	int box_2 = condition_list_largest_transition(MACHINE -> machine);

	int second_pillar = max(box_1, strlen(condition))  + THREE;

	int third_pillar  = second_pillar + strlen(symbol) + THREE;

	int fourth_pillar = max(box_2, strlen(transition)) + third_pillar + THREE;

	table -> pillars -> array[ZERO]  = ZERO;

	table -> pillars -> array[ONE]   = second_pillar;

	table -> pillars -> array[TWO]   = third_pillar;

	table -> pillars -> array[THREE] = fourth_pillar;

	return fourth_pillar + ONE;
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
/////////////////////////////////////////////// TABLE PRINTING //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

void table_space(TABLE * table)
{
	int counter = ZERO, pointer = ZERO;

	for (counter = ZERO; counter < (table -> height); counter ++)
	{
		for (pointer = ZERO; pointer < (table -> length); pointer ++)

			table -> array[counter][pointer] = SPACE;
	}
}

void table_print(TABLE * table)
{
	int counter = ZERO, pointer = ZERO;

	for (counter = ZERO; counter < (table -> height); counter ++)
	{
		for (pointer = ZERO; pointer < (table -> length); pointer ++)
		
			printf("%c", table -> array[counter][pointer]);
		
		printf("\n");
	}	
	printf("\n");
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
/////////////////////////////////////////////// TABLE FILLING /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

void table_pillars(TABLE * table)
{
	int counter = ZERO, pointer = ZERO;

	int length  = table -> pillars -> length;
	
	for (pointer = ONE; pointer < (table -> height); pointer = pointer + TWO)
	{
		for (counter = ZERO; counter < length; counter ++)
		{
			table -> array[pointer][table -> pillars -> array[counter]]

			= EDGE;
		}
	}
}

void table_strings(TABLE * table)
{
	int counter = ZERO, pointer = ZERO;

	for (counter = ZERO; counter < (table -> height); counter += TWO)
	{
		for (pointer = ZERO; pointer < (table -> length); pointer ++)

			table -> array[counter][pointer] = DASH;
	}
}

//______________________________________________TRANSITIONS_TABLE__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void table_followpos_hat(TABLE * table)
{
	HEIGHT = ONE;

	table_insert_set(table, position, ONE);

	table_insert_set(table, symbol, TWO);

	table_insert_set(table, followpos, THREE);
}

void table_followpos_fill_position(TABLE * table, int marker)
{
	int pointer = ZERO;

	array = calloc(MAX_NUMBER_LENGTH, sizeof(char));

	sprintf(array, "%d", POSITIONS -> array[COUNTER] . position_number);

	int first_pillar = THREE + strlen(position);

	int start = first_pillar / TWO - strlen(array) / TWO;

	for (pointer = start; pointer < (start + strlen(array)); pointer ++)
	
		table -> array[marker][pointer] = array[pointer - start];
}

void table_followpos_fill_symbol(TABLE * table, int marker)
{
	int counter = ZERO;

	int first_pillar  = THREE + strlen(position);

	int second_pillar = THREE + strlen(symbol);

	int start = first_pillar + second_pillar / TWO;

	table -> array[marker][start] = 

	POSITIONS -> array[COUNTER] . position_symbol;
}

void table_followpos_fill(TABLE * table)
{
	COUNTER = ZERO;

	HEIGHT  = THREE;

	for (HEIGHT = THREE; HEIGHT < (table -> height); HEIGHT += TWO)
	{
		table_followpos_fill_position(table, HEIGHT);
		
		table_followpos_fill_symbol  (table, HEIGHT);

		int_array_create_set(POSITIONS -> array[COUNTER] . followpos, array);

		table_insert_set(table, array, THREE);

		COUNTER ++;
	}
}

//______________________________________________TRANSITIONS_TABLE__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void table_transition_hat(TABLE * table)
{
	HEIGHT = ONE;

	table_insert_set(table, condition, ONE);

	table_insert_set(table, symbol, TWO);

	table_insert_set(table, transition, THREE);
}

void table_transition_fill_transitions(TABLE * table, CONDITION_LIST * CONDITION, TRANSITION_LIST * TRANSITIONS)
{
	if (TRANSITIONS == NULL) return;

	array = calloc(ONE, sizeof(char));

	int_array_create_set(CONDITION -> condition -> name, array);

	table_insert_set(table, array, ONE);

	free(array);

	table -> array[HEIGHT][table_pillar_middle(table, TWO)] = 

	TRANSITIONS -> transition -> symbol;

	array = calloc(ONE, sizeof(char));

	int_array_create_set(TRANSITIONS -> transition -> 

			condition -> condition -> name, array);

	table_insert_set(table, array, THREE);

	free(array);

	HEIGHT += TWO;

	table_transition_fill_transitions(table, CONDITION, TRANSITIONS -> next);
}

void table_transition_fill(TABLE * table, CONDITION_LIST * CONDITIONS)
{
	if (CONDITIONS == NULL) return;

	table_transition_fill_transitions(table, CONDITIONS, 

				CONDITIONS -> condition -> transitions);

	table_transition_fill(table, CONDITIONS -> next);
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
/////////////////////////////////////////////// MAIN FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

void table_followpos(MACHINE * MACHINE)
{
	TABLE * table = table_allocate();

	table -> height  = table_followpos_height();

	table -> pillars = int_array_allocate(FOUR);

	table -> pillars -> array = calloc(FOUR, sizeof(int));

	table -> length  = table_followpos_length(MACHINE, table);

	table -> array   = char_array_allocate(table -> height, table -> length);

	table_space(table);
	table_strings(table);
	table_pillars(table);
	table_followpos_hat(table);
	table_followpos_fill(table);
	table_print(table);

	free(table -> array);
	free(table);
}

void table_transitions(MACHINE * MACHINE)
{
	TABLE * table    = table_allocate();

	table -> height  = table_transition_height(MACHINE -> machine);

	table -> pillars = int_array_allocate(FOUR);

	table -> pillars -> array = calloc(FOUR, sizeof(int));

	table -> length  = table_transition_length(MACHINE, table);

	table -> array   = char_array_allocate(table -> height, table -> length);

	table_space(table);
	table_strings(table);
	table_pillars(table);
	table_transition_hat(table);

	HEIGHT = THREE;

	table_transition_fill(table, MACHINE -> machine);

	table_print(table);

	free(table -> array);

	free(table);	

	return;
}

