#include <stdio.h>
#include <stdint.h>

void check_endianness() {
    unsigned int x = 1;
    char *c = (char*)&x;
    if (*c)
        printf("System is: Little Endian\n\n");
    else
        printf("System is: Big Endian\n\n");
}


void print_bytes(unsigned int num) {
    unsigned char *bytePtr = (unsigned char*)&num;
    printf("Bytes: ");
    for (int i = 0; i < sizeof(unsigned int); i++)
        printf("0x%02x ", bytePtr[i]);
    printf("\n");
}


unsigned int swap_endian(unsigned int num) {
    unsigned int swapped = 0;
    unsigned char *src = (unsigned char*)&num;
    unsigned char *dst = (unsigned char*)&swapped;
    for (int i = 0; i < sizeof(unsigned int); i++)
        dst[i] = src[sizeof(unsigned int)-1-i];
    return swapped;
}

int main() {
    unsigned int num, swapped;
   
    check_endianness();

  
    printf("Enter an unsigned integer: ");
    scanf("%u", &num);

  
    printf("Original number: %u\n", num);
    print_bytes(num);

   
    swapped = swap_endian(num);

    
    printf("After endianness swap: %u\n", swapped);
    print_bytes(swapped);

    return 0;
}

