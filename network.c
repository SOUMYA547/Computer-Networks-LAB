#include<stdio.h>

int main(){
    int a  = 12345;
    char *ptr = (char *)&a;
    int i;
    printf("Address of a: %p\n", (void*)&a);
    printf("Value of a: %d\n", a);
    printf("Address of ptr: %p\n", (void*)&ptr);
    printf("Value of ptr: %p\n", (void*)ptr);
    printf("Value pointed to by ptr: %d\n", *(int *)ptr);
    printf("Values pointed to by ptr in reverse order:\n"); 
    for(i = sizeof(a) - 1; i >= 0; i--) {
        printf("%02x ", (unsigned char)ptr[i]);
    }
    printf("\n");
    printf("Size of a: %zu bytes\n", sizeof(a));        
        
    printf("Size of ptr: %zu bytes\n", sizeof(ptr));
    printf("Size of int: %zu bytes\n", sizeof(int));    
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of long: %zu bytes\n", sizeof(long));

    printf("Size of long long: %zu bytes\n", sizeof(long long));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of void pointer: %zu bytes\n", sizeof(void *));
}