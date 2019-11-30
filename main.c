#include "malloc.h"
#include "out.h"

int main()
{  
    int* ptr = my_malloc(sizeof(int));
    *ptr = 2;
    print("%d\n", *ptr);
    my_free(ptr);

    return 0;
}
