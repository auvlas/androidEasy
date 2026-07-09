#include <stdio.h>

int main(void) {
    int num = 0;
    printf("num: %p\n", &num);
    int num2 = 0;
    printf("num2: %p\n", &num2);
    int * ptr = &num; // prt записывается ссылка на num
    void * ptrVoid = &num;
    ptrVoid = &num;
    *(int *)ptrVoid = 6;
    printf("ptrVoid: %p, %d\n", ptrVoid, *(int *)ptrVoid);
    printf("%p, %d\n", ptr, *ptr);
    *ptr = 9; // по указателю в ptr записаваем значение в переменную num
    printf("%p, %d\n", ptr, *ptr);
    ptr = &num2; // В ptr записывается ссылка на num2
    printf("%p, %d\n", ptr, *ptr);
    *ptr = 8; // по указателю в ptr записаваем значение в переменную num2
    printf("%p, %d\n", ptr, *ptr);
    num2 = *ptr; // по указателю в ptr записаваем значение в переменную num2
    printf("%p, %d\n", ptr, *ptr);
    *ptr = num; // по указателю в ptr
    printf("%p, %d\n", ptr, *ptr);
    printf("\n\n\n\n");
    //num = 9;

    printf("%d\n", num);

    printf("%d\n", num2);

    printf("%d\n", *ptr);

    printf("%p\n", ptr);

    printf("%p\n", &num);


    return 0;
}
