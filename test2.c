#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char*argv[]) {
    int* test = malloc(sizeof(int));
    int* test2 = malloc(sizeof(int));

    *test = 2;
    *test2 = 4;

    int res = *test + *test2;
    printf("%d", res);

    free(test);
    return 0;
}