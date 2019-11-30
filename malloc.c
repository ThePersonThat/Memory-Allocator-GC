#include "malloc.h"


void* requst_space(size_t size)
{
    if(size + SIZE_META < 4096)
        size = 4096;
    else
        size += SIZE_META;

    global_free_size += size;
    

    void* ptr = sbrk(size);
    if(ptr == (void *)-1)
    {
        print("It doesn't work\n");
        return NULL;
    }

    return ptr;
}

block_meta_t* find_block(size_t size)
{
    block_meta_t* block = global_base;

    while (block != NULL)
    {
        if(block->size >= size && block->status == FREE)
        {
            if(block->size > size + size/2 + SIZE_META)
            {
                size_t free_size = block->size;
                block_meta_t* new_block = block_init(block, size);
        
                new_block->size = free_size - size - SIZE_META;
                new_block->next = block->next;
                new_block->status = FREE;
                block->next = new_block;
                new_block->tail = block;
            }
            block->status = NOT_FREE;
            return block;
        }
        block = block->next;
    }
    
    if(last_block->size >= size)
    {
        return space_init(last_block, size);
    }
        
    requst_space(size);
    return space_init(last_block, size);
}

block_meta_t* first_init(size_t size)
{
    global_base = requst_space(size);
    block_meta_t* ptr = global_base;
    ptr->tail = NULL;
    
    return space_init(ptr, size);
}


void print_blocks()
{
    block_meta_t* block = global_base;

    while (block)
    {
        print("block[%d], block->next[%d], block->tail[%d], block->size[%d], block->status[%d]\n", 
            block, block->next, block->tail, block->size, block->status);
        block = block->next;
    }
}

void* block_init(block_meta_t* block, size_t size)
{
    block->status = NOT_FREE;
    block->size = size;

    ubyte* offset = block;
    offset += size + SIZE_META;

    return offset;
}

block_meta_t* space_init(block_meta_t* block, size_t size)
{
    block_meta_t* next_block = block_init(block, size);

    global_free_size -= size + SIZE_META;
    block->next = next_block; // next block;
    next_block->size = global_free_size;
    next_block->status = UNUSED_SPACE;

    next_block->next = NULL;
    next_block->tail = block;
    last_block = next_block;
    
    return block;
}


void* my_malloc(size_t size)
{
    if(size <= 0)
        return NULL;

    if(global_base == NULL) // first allocation
    {
        block_meta_t* block = first_init(size);
        return block + 1;
    }
    else
    {
        block_meta_t* block = find_block(size);
        return block + 1;
    }
    
    return NULL;
}

void print_buffer(void* buffer, int size)
{
    void* border = buffer + size;
    for(int* ptr = buffer; ptr < border; ptr++)
    {
        print("%d ", *ptr);
    }

    print("\n");
}

void my_free(void* ptr)
{
    if(ptr == NULL) 
        return;

    block_meta_t* block = ptr - SIZE_META;  

    block_meta_t* start_block = block;
    block_meta_t* end_block = block;
    block->status = FREE;
    
    
    while (start_block->tail != NULL && start_block->tail->status == FREE)
    {
        last_block->size += SIZE_META;
        global_free_size = last_block->size;
        start_block = start_block->tail;
    }

    while (end_block->next != NULL && end_block->next->status == FREE)
    {
        last_block->size += SIZE_META;
        global_free_size = last_block->size;
        end_block = end_block->next;   
    }
       
    if(start_block != block || end_block != block)
    {
        merge_block(start_block, end_block);
    }
     
}

void merge_block(block_meta_t* tail_block, block_meta_t* current_block)
{
    tail_block->size += current_block->size;
    tail_block->next = current_block->next;
    current_block->tail = tail_block;
}