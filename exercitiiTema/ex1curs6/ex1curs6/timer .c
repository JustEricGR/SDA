/* fisierul timer.c */
#include <time.h>
#include "timer.h"

static clock_t start = 0, end = 0;

void starton() {
    start = clock();
}

double startoff() {
    
    double used = 0;
    end = clock();
    used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Total time:%.10g\n", used);
}