// description: matrix muliply with two-level for loop
#include <stdio.h>
int main()
{
    int f, i = 0;
    int h[9] = {0}, x[3] = {0}, y[3] = {0};
    FILE *input = fopen("../input/3.txt", "r");
    for (i = 0; i < 9; i++)
        fscanf(input, "%d", &h[i]);
    for (i = 0; i < 3; i++)
        fscanf(input, "%d", &x[i]);
    for (i = 0; i < 3; i++)
        fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];

    for (i = 0; i < 3; i++)
    {
        p_x = &x[0];
        for (f = 0; f < 3; f++)
            asm volatile(
                "mul t0, %[h], %[x]\n\t"                                   // AssemblerTemplate
                "add %[y], %[y], t0\n\t"                                   // AssemblerTemplate
                : [y] "+r"(*(p_y + i)), [h] "+r"(*p_h++), [x] "+r"(*p_x++) // OutputOperands, "=r" means write-only, "+r" means read/write
                :                                                          // InputOperands
                : "t0");                                                   // clobbered resources
    }
    p_y = &y[0];
    for (i = 0; i < 3; i++)
        printf("%d \n", *p_y++);
    return (0);
}