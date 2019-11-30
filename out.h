
/*
*   I use my analogue of the printf function 
*   because printf can call malloc. 
*   And this is not good :D
*/

#include <stdarg.h>
#include <string.h>

void print(const char* format, ...);
void swap(char *ch_1, char *ch_2);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
