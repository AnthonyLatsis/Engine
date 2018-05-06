

const int MAX_NUMBER_LENGTH = 11;

char * array;

//__________________________________________________________________________________________________________________________________________________________

struct PICTURE
{
    char ** array;

    int length;

    int height;

    int depth;

}typedef PICTURE;

//__________________________________________________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________________________________________________

int max(int first, int second)
{
    if (first > second) return first;

    else return second;
}

//__________________________________________________________________________________________________________________________________________________________

int abs(int value)
{
	if (value < zero)

		return value + TWO * value;

	else return value;
}

//__________________________________________________________________________________________________________________________________________________________

int tree_depth(struct TREE * tree)              
{
    if (tree -> left_branch  == NULL
    &&  tree -> right_branch == NULL)

        return ZERO;
    
    return max(tree_depth(tree -> left_branch),

               tree_depth(tree -> right_branch)) + ONE;
}

//__________________________________________________________________________________________________________________________________________________________

int box_size_for_number(TREE * tree)
{
    int box;

    array = calloc(MAX_NUMBER_LENGTH, sizeof(char));

    sprintf(array, "%d", tree -> info . value);

    box = (int)strlen(array);

    free(array);

    if (box % TWO == zero)

         return box + THREE;

    else return box + FOUR;
}

//__________________________________________________________________________________________________________________________________________________________

int box_size(struct TREE * tree)         
{
    if (tree -> info . flag == SYMBOL
    ||  tree -> info . flag == VARIABLE) return THREE + TWO;

    if (tree -> info . flag == NUMBER)

        return box_size_for_number(tree);

    if (tree -> info . flag == FUNCTION)
    {
        if (strlen(tree -> info . Function) % TWO == zero)

            return  strlen(tree -> info . Function) + THREE;

        else return strlen(tree -> info . Function) + FOUR;
    }
    else return ZERO;    
}

//__________________________________________________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________________________________________________

void picture_draw_number_label(PICTURE * picture, TREE * tree)
{
    int timer = ZERO;

    array = calloc(MAX_NUMBER_LENGTH, sizeof(char));

    sprintf(array, "%d", tree -> info . value);

    for (timer = ONE; timer < strlen(array) + ONE; timer ++)
    
        picture -> array[ONE][timer] = array[timer - ONE];
    
    free(array);    
}

//__________________________________________________________________________________________________________________________________________________________

void picture_draw_label(PICTURE * picture, TREE * tree)
{
    int timer = ZERO, box = ZERO;

    switch (tree -> info . flag)
    {
        case NUMBER   : 

        picture_draw_number_label(picture, tree);

        break;

        case SYMBOL   :
        case VARIABLE :

        picture -> array[ONE][TWO] = tree -> info . symbol;

        break;

        case FUNCTION : 
        
        box = strlen(tree -> info . Function);

        for (timer = ONE; timer < (box + ONE); timer ++)
        {
            picture -> array[ONE][timer] = 

            tree -> info . Function[timer - ONE];
        }
        break;
    }
}

//__________________________________________________________________________________________________________________________________________________________

void picture_draw_ceiling(PICTURE * picture)
{
    int counter = ZERO;

    int box     = picture -> length;

    for (counter = ONE; counter < (box - THREE) / TWO + ONE; counter ++)

        picture -> array[ZERO][counter] = UNDERSCORE;

    picture -> array[ZERO][box / TWO] = EDGE;

    for (counter = box / TWO + ONE; counter < box - ONE; counter ++)

        picture -> array[ZERO][counter] = UNDERSCORE;    
}

//__________________________________________________________________________________________________________________________________________________________

void picture_draw_body(PICTURE * picture, TREE * tree)
{
    picture -> array[ONE][ZERO] = EDGE;

    picture_draw_label(picture, tree);

    picture -> array[ONE][(picture -> length) - ONE] = EDGE;
}

//__________________________________________________________________________________________________________________________________________________________

void picture_draw_base(PICTURE * picture)
{
    int counter = ZERO;

    int box     = picture -> length;

    picture -> array[TWO][ZERO] = EDGE;

    for (counter = ONE; counter < box - ONE; counter ++)
    
        picture -> array[TWO][counter] = UNDERSCORE;
    
    picture -> array[TWO][box - ONE] = EDGE;
}

//__________________________________________________________________________________________________________________________________________________________

PICTURE * draw_box(struct TREE * tree)
{
    PICTURE * picture = calloc(ONE, sizeof(PICTURE));

    picture -> length = box_size(tree);

    picture -> depth  = ZERO;

    picture -> height = THREE;

    picture -> array  = calloc(THREE, sizeof(char *));

    int counter  = ZERO;

    for (counter = ZERO; counter < THREE; counter ++)
    {
        picture -> array[counter] = 

        calloc(picture -> length, sizeof(char));
    }
    picture_draw_ceiling(picture);
    picture_draw_base   (picture);
    picture_draw_body   (picture, tree);

    return picture;
}

//__________________________________________________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________________________________________________

void insert_left_and_parent(PICTURE * new, PICTURE * parent, PICTURE * left)
{
	int counter = ZERO, counter_1 = ZERO;

    for (counter = FOUR; counter < FOUR + (left -> height); counter ++)
    {
        for (counter_1 = ZERO; counter_1 < left -> length; counter_1 ++)
        {
            new -> array[counter][counter_1] = 

            left -> array[counter - FOUR][counter_1];
        }
    }   
    int box = left -> length - ONE;

    for (counter_1 = ZERO; counter_1 < THREE; counter_1 ++)
    {
    	for (counter = box; counter < box + parent -> length; counter ++)
    	{
    		new -> array[counter_1][counter] = 

    		parent -> array[counter_1][counter - box];
    	}
    }
}

//__________________________________________________________________________________________________________________________________________________________

void insert_right(PICTURE * new, PICTURE * right)
{   
    int counter = ZERO, counter_1 = ZERO;

    int box = new -> length - right -> length;

    for (counter = FOUR; counter < FOUR + (right -> height); counter ++)
    {
        for (counter_1 = box; counter_1 < new -> length; counter_1 ++)
        {
            new -> array[counter][counter_1] = 

            right -> array[counter - FOUR][counter_1 - box];
        }
    }
}

//__________________________________________________________________________________________________________________________________________________________

void insert_daughter(PICTURE * new, PICTURE * daughter)
{
    int counter_1 = ZERO, counter = ZERO;

    int box = abs((new -> length) - (daughter -> length)) / TWO;

    for (counter_1 = THREE; counter_1 < new -> height; counter_1 ++)
    {
        for (counter = box; counter < (new -> length) + box; counter ++)
        {
            new -> array[counter_1][counter] = 

            daughter -> array[counter_1 - THREE][counter - box];
        }
    }
}

//__________________________________________________________________________________________________________________________________________________________

void insert_parent_1(PICTURE * new, PICTURE * parent)
{
    int marker = ZERO, counter = ZERO, counter_1 = ZERO;
    
    for (counter = ZERO; counter < (new -> length); counter ++)
    
    	if (new -> array[THREE][counter] == EDGE) marker = counter; 

    int box = marker - (parent -> length) / TWO; 

    for (counter_1 = ZERO; counter_1 < THREE; counter_1 ++)
    {
        for (counter = box; counter < box + (parent -> length); counter ++)
        {
            new -> array[counter_1][counter] = 

            parent -> array[counter_1][counter - box];
        }
    }
}

//__________________________________________________________________________________________________________________________________________________________

void insert_branch(PICTURE * new, PICTURE * parent, PICTURE * left)
{
	int box = (left -> length) + (parent -> length / TWO) - ONE; 

	int marker_1 = ZERO, marker_2 = ZERO;int counter_1, counter_2;

	int counter = ZERO;

	for (counter = ZERO; counter < (left -> length); counter ++)
	
		if (new -> array[FOUR][counter] == EDGE) marker_1 = counter;

	for (counter = marker_1; counter < (new -> length); counter ++)
	
		if (new -> array[FOUR][counter] == EDGE) marker_2 = counter;

	for (counter = marker_1 + ONE; counter < marker_2; counter ++)
	{
		new -> array[THREE][counter] = UNDERSCORE;
	}
	new -> array[THREE][box] = EDGE;
}

//__________________________________________________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________________________________________________

PICTURE * one_branch(PICTURE * parent, PICTURE * daughter)
{
    PICTURE * new = calloc(ONE, sizeof(PICTURE));

    new -> depth  = daughter -> depth + ONE;

    new -> height = parent -> height + daughter -> height;

    new -> array  = calloc(new -> height, sizeof(char *));

    new -> length = max(parent -> length, daughter -> length);

    int pointer = ZERO;

    for (pointer = ZERO; pointer < new -> height; pointer ++)
    
        new -> array[pointer] = calloc(new -> length, sizeof(char));

	insert_daughter(new, daughter);

    insert_parent_1(new, parent);

    free(parent);
    free(daughter);

    return new;
}

//__________________________________________________________________________________________________________________________________________________________

PICTURE * two_branch(PICTURE * parent, PICTURE * left, PICTURE * right)
{
    PICTURE * new = calloc(ONE, sizeof(PICTURE));

    new -> depth  = max(left -> depth, right -> depth) + ONE;

    new -> height = (new -> depth) * FOUR + THREE;

    new -> array  = calloc(new -> height, sizeof(char *));

    new -> length = parent -> length + left -> length

                  + right -> length - TWO;

    int pointer = ZERO;

    for (pointer = ZERO; pointer < new -> height; pointer ++)
    
        new -> array[pointer] = calloc(new -> length, sizeof(char));

    insert_left_and_parent(new, parent, left);
    insert_right   		  (new, right);
    insert_branch 		  (new, parent, left);

    free(parent);
    free(left);
    free(right);

    return new;
}

//__________________________________________________________________________________________________________________________________________________________

PICTURE * picture_merge(struct TREE * tree, PICTURE * first, PICTURE * second)
{
    if (first  == NULL && second == NULL)

        return draw_box(tree);

    if (first  == NULL) 

        return one_branch(draw_box(tree), second);

    if (second == NULL) 

        return one_branch(draw_box(tree), first);

    return two_branch(draw_box(tree), first, second);
}

//__________________________________________________________________________________________________________________________________________________________

PICTURE * picture_tree(struct TREE * tree)
{
    if (tree == NULL) return NULL;
    
    return picture_merge(tree, picture_tree(tree -> left_branch),

                               picture_tree(tree -> right_branch));
}

//__________________________________________________________________________________________________________________________________________________________

void tree_image(struct TREE * tree)
{
	mother_fill(tree);

	PICTURE * image = picture_tree(tree);

	int counter_1 = ZERO, counter = ZERO;
	
	for (counter_1 = ZERO; counter_1 < (image -> height); counter_1 ++)
	{
		for (counter = ZERO; counter < (image -> length); counter ++)
		{
			if (image -> array[counter_1][counter] == 0)
				
				image -> array[counter_1][counter] = SPACE;
		}
	}
	for (counter_1 = ZERO; counter_1 < (image -> height); counter_1 ++)
	{
		for (counter = ZERO; counter < (image -> length); counter ++)
		{
			printf("%c", image -> array[counter_1][counter]);
		}
		printf("\n");
	}
	printf("\n\n");

    free(image);

	return;
}
