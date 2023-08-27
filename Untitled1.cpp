#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
//create file

const float EPSILON = 1.0e-8f;
const int NUM_OF_COEFFS = 3;
const int LIMIT_TEST = 5;
const int LIMIT_OF_COMMAND = 15;
const int NUM_OF_COEFFS_LIN = 2;
const int PROGRAMM_ERROR = -948565;
const char main_programm [LIMIT_OF_COMMAND] = "-go";
const char test_programm_str [LIMIT_OF_COMMAND] = "-test";
const char solve_linear_str [LIMIT_OF_COMMAND] = "-l";

enum RET_CODES {EXIT = 0, CONTINUE = 1};
enum EQUATION_CASES {LINEAR = 0,
SQUARE_2_ROOTS = 1,
INF_ROOTS = 2,
SQUARE_1_ROOT = 3,
NO_ROOTS = 4};
/*
solves a linear equation
*/
void solve_linear (float coeff_n1, float coeff_n2, float *root1);

/*
if the number is negative returns 1 else returns 0
*/
bool is_negative (float number);
/*
if the number is 0 returns 1 else returns 0
*/
int is_null (float result);

/*
solves a square equation and returns number of roots
*/
int solve_square (float coeffs[], float * root1, float * root2);

/*
returns a value of 0 or 1 in case of incorrect and correct reading
If 0 - closing the program, if 1 - an invitation to a new input
*/

/*
print the result on the screen
*/
void print_result(float x1, float x2, int n_roots);

void solve_linear_cmd (char * argv[], int argc);

int single_test(float test_coeff[], float correct_ans[]);

void test_programm (float coeffs[]);

int float_comparison (float compared_value_1 [], float compared_value_2, int num_of_array);

int read_coeffs (float coeffs[], char * argv[], int argc);

int scan_coeff (float coeffs[], int count_of_norm_input);

int main (int argc, char * argv[])
{

    float coeffs[NUM_OF_COEFFS] = {};

    if(argc==1)
    {
        printf("Введите коэффиценты a, b и c, для выхода из программы введите букву q\n");

        while(read_coeffs(coeffs, argv, argc) != EXIT)
        {
            float x1 = 0.0f;
            float x2 = 0.0f;

            print_result(x1, x2, solve_square(coeffs, &x1, &x2));
        }
    }

    else
    {
        if (strcmp(argv[1], main_programm) == 0)
        {
            printf("Введите коэффиценты a, b и c, для выхода из программы введите букву q\n");

            while(read_coeffs(coeffs, argv, argc) != EXIT)
            {
                float x1 = 0.0f;
                float x2 = 0.0f;

                print_result(x1, x2, solve_square(coeffs, &x1, &x2));

            }

        }

        else if (strcmp(argv[1], test_programm_str) == 0)
        {
            test_programm (coeffs);
        }

        else if (strcmp(argv[1], solve_linear_str) == 0)
        {
            printf("Введите коэффиценты a и b, для выхода из программы введите букву q\n");
            solve_linear_cmd(argv, argc);
        }
    }

    return 0;

}

int read_coeffs (float coeffs[], char * argv[], int argc)
{
    int count_of_norm_input = 0;
    int check = 0;
    if(argc > 1)
    {

        if (strcmp(argv[1], solve_linear_str) == 0)
        {
            while (count_of_norm_input < 2)
            {
               check = scan_coeff(coeffs, count_of_norm_input);
               if(check != 1)
               {
                    return EXIT;
               }
               count_of_norm_input++;
            }
            return CONTINUE;
        }


        else
        {
            while (count_of_norm_input < 3)
            {
               check = scan_coeff(coeffs, count_of_norm_input);
               if(check != 1)
               {
                    return EXIT;
               }
               count_of_norm_input++;
            }

            return CONTINUE;
        }
    }

    else
    {
        while (count_of_norm_input < 3)
        {
           check = scan_coeff(coeffs, count_of_norm_input);
           if(check != 1)
           {
                return EXIT;
           }
           count_of_norm_input++;
        }

        return CONTINUE;
    }
}

int scan_coeff (float coeffs[], int count_of_norm_input)
{
    int reader = scanf("%f", &coeffs[count_of_norm_input]);

    while (reader != CONTINUE)
    {
        int trash_bufer = getchar();
        if(trash_bufer == 'q')
        {
            return EXIT;
        }

        printf ("Введите числа  ещё раз \n");

        while (trash_bufer != '\n')
        {
            trash_bufer = getchar();
        }
        reader = scanf("%f", &coeffs[count_of_norm_input]);

    }
    return true;

}


int is_null (float result)
{
    return (fabs(result) < EPSILON);
}

int solve_square (float coeffs[], float * root1, float * root2)
{

    float D = 0.0f;
    D = (coeffs[1]*coeffs[1]) - 4*coeffs[0]*coeffs[2];

    if (D < 0)
    {
        *root1 = 0;
        *root2 = 0;
        return NO_ROOTS;
    }

    if (is_null(coeffs[2]))
    {
        *root2 = 0;
        if (is_null(coeffs[0]) != true)
        {
            solve_linear(coeffs[0], coeffs[1], root1);
        }
    }

    if (is_null(coeffs[0]))
    {
        if (is_null(coeffs[1]))
        {
            if (is_null(coeffs[2]))
            {
                *root1 = 0;
                *root2 = 0;
                return INF_ROOTS;
            }
            *root1 = 0;
            *root2 = 0;
            return INF_ROOTS;
        }

        solve_linear(coeffs[1], coeffs[2], root1);
        *root2 = 0;
        return LINEAR;
    }

    else
    {
        float root_D = sqrtf(D);
        if (D > 0)
        {
            *root1 = (-coeffs[1] + root_D)/2*coeffs[0];
            *root2 = (-coeffs[1] - root_D)/2*coeffs[0];
            return SQUARE_2_ROOTS;
        }
        else
        {
            *root1 = (-coeffs[1] + root_D)/2*coeffs[0];
            *root2 = 0;
            return SQUARE_1_ROOT;
        }

    }



}

/*int read_coeffs (float coeffs[])
{

    int reader = scanf("%f %f %f", &coeffs[0], &coeffs[1], &coeffs[2]);

    while (reader != 3)
    {
        printf ("Введите числа  ещё раз");
        int trash_bufer = getchar();
        if(trash_bufer == 'q')
        {
            return EXIT;
        }
        while (trash_bufer != '\n')
        {
            trash_bufer = getchar();
        }

        reader = scanf("%f %f %f", &coeffs[0], &coeffs[1], &coeffs[2]);
    }

    return CONTINUE;
}
*/

bool is_negative (float number)
{
    if (number > EPSILON)
    {
        return false;
    }
    if (number < -EPSILON)
    {
        return true;
    }

}

void solve_linear (float coeff_n1, float coeff_n2, float *root1)
{
    if (is_null(coeff_n1) != true)
    {
        *root1 = -coeff_n2 / coeff_n1;
    }
}


void print_result(float x1, float x2, int n_roots)
{
    switch (n_roots)
    {

        case LINEAR: printf("Уравнение линейно и имеет корень: %f \n", x1);
                     break;

        case SQUARE_2_ROOTS: printf("Уравнение имеет два корня: %f и %f \n", x1, x2);
                             break;

        case INF_ROOTS: printf("Уравнение имеет бесконечное число корней\n");
                        break;

        case SQUARE_1_ROOT: printf("Уравнение имеет единственный корень: %f\n", x1);
                            break;

        case NO_ROOTS: printf("Корней нет\n");
                       break;

        default: printf("Ошибка\n");

    }
}


void solve_linear_cmd (char * argv[], int argc)
{
    float x_linear = 0.0f;
    float coeffs_linear[NUM_OF_COEFFS_LIN] = {};

    while (read_coeffs(coeffs_linear, argv, argc) != EXIT)
    {
        if (is_null(coeffs_linear[0]) != true)
        {
            solve_linear (coeffs_linear[0], coeffs_linear[1], &x_linear);
            printf("Answer is %f \n", x_linear);
        }
        else
        {
            printf("error: coeff_n1 == 0");
        }
    }
}



int scan_square_equation ()
{

}
/*
int read_coeffs (float coeffs[])
{

    int reader = scanf("%f %f %f", &coeffs[0], &coeffs[1], &coeffs[2]);

    while (reader != 3)
    {
        printf ("Введите числа  ещё раз");
        int trash_bufer = getchar();
        if(trash_bufer == 'q')
        {
            return EXIT;
        }
        while (trash_bufer != '\n')
        {
            trash_bufer = getchar();
        }

        reader = scanf("%f %f %f", &coeffs[0], &coeffs[1], &coeffs[2]);
    }

    return CONTINUE;
}*/


void test_programm (float coeffs[])
{
    int step_root = 0;
    int counter_of_right_answers = 0;

    float all_coeffs [LIMIT_TEST][NUM_OF_COEFFS] =
    {
        {1, 1, 1},
        {1, -2, 1},
        {1, -5, 6},
        {0, 0, 0},
        {0, -2, 4}
    };

    float all_correct_answers[LIMIT_TEST][NUM_OF_COEFFS_LIN] =
    {
        {0, 0},
        {1, 0},
        {3, 2},
        {0, 0},
        {2, 0}
    };

    float correct_ans[2] = {};


    for (int step_test = 0; step_test < LIMIT_TEST; step_test++)
    {
        for (int step_coeff = 0; step_coeff < NUM_OF_COEFFS; step_coeff++)
        {
            coeffs[step_coeff] = all_coeffs[step_test][step_coeff];
            coeffs[step_coeff] = all_coeffs[step_test][step_coeff];
            coeffs[step_coeff] = all_coeffs[step_test][step_coeff];
        }

        for(step_root = 0; step_root < NUM_OF_COEFFS_LIN; step_root++)
        {
            correct_ans[step_root] = all_correct_answers[step_test][step_root];
            correct_ans[step_root] = all_correct_answers[step_test][step_root];
        }

        counter_of_right_answers += single_test(coeffs, correct_ans);



    }
    printf("Amount of right answers: %d", counter_of_right_answers);

}

int float_comparison (float compared_array_value_1 [], float compared_value_2, int num_of_array)
{
    return is_null(compared_array_value_1[num_of_array] - compared_value_2);
}

int single_test(float test_coeff[], float correct_ans[])
{

    float x1 = 0.0f;
    float x2 = 0.0f;
    int counter = 0;

    int num_of_roots = solve_square(test_coeff, &x1, &x2);

    switch (num_of_roots)
    {
        case LINEAR: if (float_comparison(correct_ans, x1, 0))
            {
                counter++;
            }

            else
            {
                printf("ERROR -> correct: x1_expect = %f, programm: x1 = %f, x2 = %f \n", correct_ans[0], x1, x2);
            }
            break;

        case SQUARE_2_ROOTS: if (float_comparison(correct_ans, x1, 0) && float_comparison(correct_ans, x2, 1))
            {
                counter++;
            }

            else
            {
                printf("ERROR -> correct: x1_exp = %f, x2_exp = %f,"
                "programm: x1 = %f, x2 = %f\n", correct_ans[0], correct_ans[1], x1, x2);
            }
            break;

        case INF_ROOTS: if (float_comparison(correct_ans, x1, 0) && float_comparison(correct_ans, x2, 0))
            {
                counter++;
            }

            else
            {
                printf("ERROR -> correct: inf_roots, programm: x1 = %f, x2 = %f\n", x1, x2);
            }
            break;

        case SQUARE_1_ROOT: if (float_comparison(correct_ans, x1, 0) && float_comparison(correct_ans, x2, 1))
            {
                counter++;
            }

            else
            {
                printf("ERROR -> correct: x1_exp = %f, programm: x1 = %f, x2 = %f \n", correct_ans[0], x1, x2);
            }
            break;

        case NO_ROOTS: if (float_comparison(correct_ans, x1, 0) && float_comparison(correct_ans, x2, 0))
            {
                counter++;
            }
            else
            {
                printf("ERROR -> correct: no_roots programm: x1_exp = %f, x2_exp = %f,"
                "x1 = %f, x2 = %f \n", correct_ans[0], correct_ans[1], x1, x2);
            }
            break;

        default: printf("Ошибка\n");
    }

    return counter;
}






