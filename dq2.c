#include <stdlib.h>
#include <stdio.h>

void main() {
    printf("Fork 1 %d\n", fork());
    printf("Fork 2 %d\n", fork());
    exit(0);
}