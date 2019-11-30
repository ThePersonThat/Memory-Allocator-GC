#include "out.h"
#include <stddef.h>
#include <unistd.h>

static void* global_base = NULL;
static size_t global_free_size = 0;

typedef unsigned char ubyte;

enum
{
    NOT_FREE,
    FREE,
    UNUSED_SPACE
};

typedef struct block_meta
{
    struct block_meta* next;
    struct block_meta* tail;
    size_t size;
    ubyte status;
}block_meta_t;

static block_meta_t* last_block = NULL;

void* my_malloc(size_t size);
void* requst_space(size_t size);
block_meta_t* first_init(size_t size);
block_meta_t* space_init(block_meta_t* block, size_t size);
void* block_init(block_meta_t* block, size_t size);
block_meta_t* find_block(size_t size);
void my_free(void* ptr);
void merge_block(block_meta_t* tail_block, block_meta_t* current_block);
void print_buffer(void* buffer, int size); // for debug
void print_blocks(); // for debug 


#define SIZE_META       sizeof(block_meta_t)

