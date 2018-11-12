#include <stdio.h>
#include <stdlib.h>

#include "dataDef.h"
#include "memoryVM.h"
#include "memoryVMObject.h"

#define UNUSED(VAR) ((void) VAR)

/*
 * This file is not submitted as your homework.
 *
 * You should only use it to test and play with your iimplementation.
 */

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    printf("%d\n",initVM());
    allocate(1000000000000000000);
    int *integer_array = allocateArray(1,5);
    integer_array[4] = 250;
    printf("%d\n", integer_array[2]);

    int **integer_2d = (int **)allocateArray2D(sizeof(int), 12, NULL);
    //int *integer_1d = (int *) integer_2d[0];
    //int result = integer_1d[0];
    printf("%d\n", integer_2d[0][0]);
    return EXIT_SUCCESS;
}
