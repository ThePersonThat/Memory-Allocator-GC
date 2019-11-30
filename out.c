#include "out.h"


void print(const char* format, ...)
{
    va_list vl;
    int i = 0, j = 0;
    char buffer[100] = { 0 };
    char temp[20];

    va_start(vl, format);

    while (format[i])
    {
        if(format[i] == '%')
        {
            i++;
            itoa(va_arg(vl, int), temp, 10);
            strcpy(&buffer[j], temp);
            j += strlen(temp);
        }
        else
        {
            buffer[j] = format[i];
            j++;
        }
        i++;
    }
    
    write(1, buffer, strlen(buffer));
    va_end(vl);
}


void swap(char *ch_1, char *ch_2)
{
    char temp;
    temp = *ch_1;
    *ch_1 = *ch_2;
    *ch_2 = temp;
}

void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length - 1; 
    while (start < end) 
    { 
        swap(str + start, str + end); 
        start++; 
        end--; 
    } 
} 

char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    int isNegative = 0; 
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
    if (num < 0 && base == 10) 
    { 
        isNegative = 1; 
        num = -num; 
    } 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    }  
    if (isNegative) 
        str[i++] = '-'; 
    str[i] = '\0';
    reverse(str, i); 
    return str; 
} 


