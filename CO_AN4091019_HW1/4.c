// description: matrix muliply without for loop
#include <stdio.h>
int main()
{
    int i = 0;
    int h[9] = {0}, x[3] = {0}, y[3] = {0};
    FILE *input = fopen("../input/4.txt", "r");
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
    asm volatile(
        "addi t0, x0, 0\n\t" // AssemblerTemplate
        "addi t2, x0, 3\n\t"
        "outerloop:\n\t"
        "bge t0, t2, outerexit\n\t"
        "addi t0, t0, 1\n\t"
        "addi t1, x0, 0\n\t"
        "innerloop:\n\t"
        "bge t1, t2, innerexit\n\t"
        "addi t1, t1, 1\n\t"

        "lw t3, 0(%[p_y])\n\t"
        "lw t4, 0(%[p_x])\n\t"
        "lw t5, 0(%[p_h])\n\t"

        "mul t6, t4, t5\n\t"
        "add t3, t3, t6\n\t"
        "sw t3, 0(%[p_y])\n\t"
        "addi %[p_x], %[p_x], 4\n\t"
        "addi %[p_h], %[p_h], 4\n\t"

        "j innerloop\n\t"
        "innerexit:\n\t"
        "addi %[p_x], %[_p_x], 0\n\t"
        "addi %[p_y], %[p_y], 4\n\t"
        "j outerloop\n\t"
        "outerexit:\n\t"
        : [p_y] "+r"(p_y), [p_h] "+r"(p_h), [p_x] "+r"(p_x) // OutputOperands, "=r" means write-only, "+r" means read/write
        : [_p_x] "r"(&x[0])                                 // InputOperands
        : "t0", "t1", "t2", "t3", "t4", "t5", "t6", "x0");  // clobbered resources
    p_y = &y[0];
    for (i = 0; i < 3; i++)
        printf("%d \n", *p_y++);
    return (0);
}