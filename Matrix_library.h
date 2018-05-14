

struct MATRIX_M
{
    int ** Matrix;

    int width;
    int altitude;

    struct MATRIX_M ** Minors;
};


struct MATRIX_E
{
    struct MATRIX_M * HEAD;
    struct MATRIX_M * EXTN;

    struct MATRIX_M ** SUBS;

    int head_order;

    float * variables;
};

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int power_number(int number, int power)
{
    int timer,  box = ONE;

    for(timer = zero; timer < power; timer ++)
    {
        box *= number;
    }
    return box;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void print_matrix(struct MATRIX_M * matrix)
{
    if (matrix == NULL) return;

    int timer_f, timer_s;

    for (timer_f = zero; timer_f < (matrix -> altitude); timer_f ++)
    {
        for (timer_s = zero; timer_s < (matrix -> width); timer_s ++)
        {
            printf(" %d ", matrix -> Matrix[timer_f][timer_s]);
        }
        printf("\n,");
    }
}

//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void matrix_filling(struct MATRIX_M * matrix)
{
    int timer_f, timer_s;

    for (timer_f = zero; timer_f < (matrix -> altitude); timer_f ++)
    {
        for (timer_s = zero; timer_s < (matrix -> width); timer_s ++)
        {
            scanf("%d", &matrix -> Matrix[timer_f][timer_s]);
        }
    }
}

struct MATRIX_M * matrix_initializer(int Width, int Altitude)
{
    struct MATRIX_M * matrix      = calloc(ONE , sizeof(struct MATRIX_M));

    matrix -> Matrix              = calloc(Altitude, sizeof(int *));

    int timer;

    for (timer = zero; timer < Altitude; timer ++)
    {
        matrix -> Matrix[timer]   = calloc(Width, sizeof(int));
    }
    matrix -> width               = Width;
    matrix -> altitude            = Altitude;

    return matrix;
}

struct MATRIX_M * minor_initializer(int Width)
{
    if (Width == zero) 
        return NULL;

    struct MATRIX_M * matrix    = matrix_initializer(Width, Width);  int timer;

    matrix -> Minors            = calloc(Width, sizeof(struct MATRIX_M *));

    for (timer = zero; timer < Width; timer ++)
    {
        matrix -> Minors[timer] = minor_initializer(Width - ONE);
    }
    return matrix;
}

struct MATRIX_E * matrix_E_initializer(int Order)
{
    struct MATRIX_E * matrix = calloc(ONE, sizeof(struct MATRIX_E));

    matrix -> head_order     = Order;

    matrix -> HEAD           = calloc(ONE, sizeof(struct MATRIX_M));
    matrix -> EXTN           = calloc(ONE, sizeof(struct MATRIX_M));

    matrix -> HEAD           = minor_initializer(Order);

    int timer;

    matrix -> SUBS           = calloc(Order, sizeof(struct MATRIX_M *));

    for (timer = zero; timer < Order; timer ++)
    {
            matrix -> SUBS[timer] = minor_initializer(Order);
    }
    matrix -> variables      = calloc(Order, sizeof(float));

    matrix -> EXTN           = matrix_initializer(ONE, Order);

    matrix -> EXTN -> Minors = NULL;           return matrix;
}

void minor_constructor(struct MATRIX_M * matrix, int minor_number)
{
    int timerF, timerS;

    for (timerF = ONE; timerF < matrix -> width; timerF ++)
    {
        for (timerS = zero; timerS < minor_number; timerS ++)
        {
            matrix -> Minors[minor_number] -> Matrix[timerF - ONE][timerS] =

            matrix -> Matrix[timerF][timerS];
        }
    }
    for (timerF = ONE; timerF < (matrix -> width); timerF ++)
    {
        for (timerS = minor_number + ONE; timerS < (matrix -> width); timerS ++)
        {
            matrix -> Minors[minor_number] -> Matrix[timerF - ONE][timerS - ONE] =

            matrix -> Matrix[timerF][timerS];
        }
    }
}

void minor_recursive_run(struct MATRIX_M * matrix)
{
    int timer;

    for (timer = zero; timer < (matrix -> width); timer ++)
    {
        minor_constructor(matrix, timer);
    }
    for (timer = zero; timer < (matrix -> width); timer ++)
    {
        if (matrix -> Minors[timer] != NULL)

        minor_recursive_run(matrix -> Minors[timer]);
    }
}

int determinant(struct MATRIX_M * matrix)
{
    if (matrix -> width == ONE) return (matrix -> Matrix[zero][zero]);

    int timer, Determinant = zero;

    for (timer = zero; timer < (matrix -> width); timer ++)
    {
        Determinant = Determinant + power_number(-ONE, timer)*

        (matrix -> Matrix[zero][timer]) * determinant(matrix -> Minors[timer]);
    }
    return Determinant;
}

void substitute_column(struct MATRIX_E * matrix, int column_number)
{
    int timerS, timerF;

    for (timerS = zero; timerS < (matrix -> head_order); timerS ++)
    {
        for (timerF = zero; timerF < column_number; timerF ++)
        {
            matrix -> SUBS[column_number] -> Matrix[timerS][timerF] =

            matrix -> HEAD -> Matrix[timerS][timerF];
        }
        for (timerF = column_number + ONE; timerF < (matrix -> head_order); timerF ++)
        {
            matrix -> SUBS[column_number] -> Matrix[timerS][timerF] =

            matrix -> HEAD -> Matrix[timerS][timerF];
        }
    }
    for (timerS = zero; timerS < (matrix -> head_order); timerS ++)
    {
        for (timerF = column_number; timerF < (column_number + ONE); timerF ++)
        {
            matrix -> SUBS[column_number] -> Matrix[timerS][timerF] =

            matrix -> EXTN -> Matrix[timerS][zero];
        }
    }
}

void create_solution_matrix(struct MATRIX_E * matrix)
{
    int timer;

    for (timer = zero; timer < (matrix -> head_order); timer ++)
    {
        substitute_column(matrix, timer);
    }
}

void Cramer_solution(struct MATRIX_E * matrix)
{
    int timer = ZERO;

    for (timer = zero; timer < (matrix -> head_order); timer ++)
    {
        matrix -> variables[timer] = 

        (float)(determinant(matrix -> SUBS[timer]))/(float)(determinant(matrix -> HEAD));
    }
}

void matrix_destroy(struct MATRIX_M * matrix)
{
    if (matrix == NULL) return;

    int timer;

    for (timer = zero; timer < (matrix -> altitude); timer ++)
    {
        free(matrix -> Matrix[timer]);
    }
    free(matrix -> Matrix);

    for (timer = zero; timer < (matrix -> altitude); timer ++)
    {
        matrix_destroy(matrix -> Minors[timer]);
    }
    free(matrix -> Minors);
}

void matrix_E_destroy(struct MATRIX_E * matrix)
{
    matrix_destroy(matrix -> HEAD); matrix_destroy(matrix -> EXTN);

    int timer;

    for (timer = zero; timer < (matrix -> head_order); timer ++)
    {
        matrix_destroy(matrix -> SUBS[timer]);
    }
    free(matrix -> SUBS);

    free(matrix -> variables);
}

struct MATRIX_E * linear_system_solution(int Order)
{
    int timer = ZERO;

    struct MATRIX_E * matrix = matrix_E_initializer(Order);

    matrix_filling     (matrix -> HEAD);

    matrix_filling     (matrix -> EXTN);

    minor_recursive_run(matrix -> HEAD);

    create_solution_matrix(matrix);

    for (timer = ZERO; timer < Order; timer ++)

        minor_recursive_run(matrix -> SUBS[timer]);

    Cramer_solution    (matrix);

    return matrix;
}

int print_determinant(int Order)
{
    struct MATRIX_M * matrix = minor_initializer(Order);
    
    matrix_filling     (matrix);

    printf("\n\n");

    minor_recursive_run(matrix);

    return determinant(matrix);
}

void transpond(struct MATRIX_M * matrix)
{
    struct MATRIX_M * matrix_t = matrix_initializer(matrix -> altitude, matrix -> width);

    int timer_1 = ZERO, timer_2 = ZERO;

    for (timer_1 = ZERO; timer_1 < matrix -> altitude; timer_1 ++)
    {
        for (timer_2 = ZERO; timer_2 < matrix -> width; timer_2 ++)
        {
            matrix_t -> Matrix[timer_2][timer_1] = matrix -> Matrix[timer_2][timer_1];
        }
    }
    print_matrix(matrix_t);
}
 
      
 