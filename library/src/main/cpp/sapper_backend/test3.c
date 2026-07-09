/*
#define основная main
#define число int
#define нихуя 0


#define сын #include
#define пох  int 
сын  <stdio.h>
пох 
*/

#include <stdio.h>
#include <stdlib.h>

char * mop(int num1) {
    char * str = NULL;
    asprintf(&str, "%d", num1);
    return str;
}

int main(void) {
    int num1 = 0, num2 = 0;
    char * ptr = NULL;
    scanf("%d %d", &num1, &num2);
    ptr = mop(num1);
    printf("%s\n", ptr);
    free(ptr);
    return 0;
}
