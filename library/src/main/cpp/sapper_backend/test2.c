#include <stdio.h>
struct nau{
    int row;
    short int jon;
};
struct ko{
    int f; // 4
    int* rip;// 8
    struct nau nau;//4 2 2
};

int main(void) {
    struct ko m = {};
    int took = 0;
    
    m.rip = &took;

    printf("%i\n", sizeof(struct ko));
    printf("%p\n",m.rip);
    /*
    struct nau a = {};
    char * ptr = (char *)&a;
    *(ptr+2)=0x36;

    printf("%x\n",  a.row);
    char* ptr_1= (char*)&a;
    *(ptr_1+5)=0xA6;
    printf("%hx\n",a.jon);
    */

    /*
    int sum = 0;
    int *ptr=NULL;
    int *ptr2=NULL;
    int **ptr3=NULL;
    int **ptr4=NULL;
    ptr=&sum;
    ptr3=&ptr;
    int **ptr7 = &ptr;
    **ptr7
    ptr = *ptr7;

    int num89 = 89;
    int *ptr89 = &num89;
    *ptr89;
    int **ptr897 = &ptr89;
    ptr897;
    *ptr897;
    int num67 = 0;
    *ptr897 = &num67;
    *ptr89
    */



    /*
    int num1 = 0;
    int num2 = 0;
    int * ptr = &num1;
    int * ptr1 = &num2;
    int num3 = 0;
    *((short*)ptr + 1) = 0x1934;
    short *ptr3 = (short*)&num3;
    *(ptr3+1)= 0x1934;
    printf("0x%08x\n", *((int *)(ptr3)));
    */

    /*
    int ** ptr =0;
    // int - int *
    int* num = ptr;
    *ptr = num;
    ptr = num;

    int * ptr = &num;
    // int ** - int **
    int ** ptr1 = &ptr;
    // int * - int **
    *ptr1 = &ptr;
    ptr = &num;

    *ptr

    int * ptr = &num;

    int num4 = 0x3;
    int num5 = 0xA;
    int * ptr4 = &num4;
    int ** ptr5 = &ptr4;
    int *** ptr6 = &ptr5;
    int **** ptr7 = &ptr6;
    ptr4=&num5;
    int **ptr = &ptr4;
    int ***ptr_1=&ptr;
    ptr7=&ptr_1;
    
    printf("%x\n",****ptr7);
    printf("addr num4: %p\n", &num4);
    printf("addr ptr4: %p\n", &ptr4);
    printf("addr ptr5: %p\n", &ptr5);

    printf("num4: %x\n", num4);
    printf("ptr4: %p\n", ptr4);
    printf("ptr5: %p\n", ptr5);

    printf("value ptr4: %x\n", *ptr4);
    printf("value ptr5: %p\n", *ptr5);

    printf("value value ptr5: %x\n", **ptr5);
    */

    /*
    printf("%ld, %ld\n", sizeof(num2), sizeof(num3));

    printf("%hhu, %hhu, %hhu, %hhu\n", *(char *)ptr1, 
            *((char *)ptr1 + 1), *((char *)ptr + 2), *((char *)ptr + 3));

    printf("%u\n", -1);
    printf("%d\n", -1);



    int * ptr2 = &num2;
    ptr2 = &num2;
    ptr2 = &num1;
    ptr2 = &num2;

    *ptr2 = 9;



    return 0;
    */
    return 0;
}
