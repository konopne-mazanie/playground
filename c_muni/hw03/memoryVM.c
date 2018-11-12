#include <stdlib.h>

//***********************************************
//              IMPORTANT NOTICE                *
//***********************************************
//  If you need to add more headers, which      *
//  you CAN, add them AFTER THIS LINE           *
#include <string.h>
//  but BEFORE the following one:               *
#include "memoryVM.h"
//  otherwise your code MAY FAIL TO COMPILE!    *
//                                              *
//  You have been warned.                       *
//***********************************************
// Here goes your glorious implementation.
typedef struct
{
    int count_of_elems;
    int ref_counter;
    bool is_2d;

    void *pointer;
} memory_object;

memory_object *mem = NULL;
int count_objects = 0;

bool initVM(void)
{
    return true;
}

bool newstruct(int count_of_elems, bool is_2d, void *pointer)
{
    memory_object *otpstruct = NULL;
    for (int i = 0; i < count_objects; i++)
    {
        if (mem[i].pointer == NULL)
        {
            otpstruct = &mem[i];
            break;
        }
    }
    if (!otpstruct)
    {
        void *newmemory = realloc(mem, sizeof(memory_object) * (count_objects + 1));
        if (!newmemory)
        {
            return false;
        }
        mem = newmemory;
        count_objects++;
        otpstruct = &mem[count_objects - 1];
    }
    otpstruct->pointer = pointer;
    otpstruct->count_of_elems = count_of_elems;
    otpstruct->ref_counter = 1;
    otpstruct->is_2d = is_2d;
    return true;
}

void *allocate(size_t size)
{
    return allocateArray(size, 1);
}

void *allocateArray(size_t elementSize, size_t elementCount)
{
    void *pointer_on_array = malloc(elementSize * elementCount);
    if (!pointer_on_array)
    {
        return NULL;
    }
    memset(pointer_on_array, 0, elementSize * elementCount);

    if (newstruct(elementCount, false, pointer_on_array) == false)
    {
        free(pointer_on_array);
        return NULL;
    }
    return pointer_on_array;
}

void **allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts)
{
    bool iselem = true;
    if (!elementCounts)
    {
        iselem = false;
        elementCounts = malloc(subarrays * sizeof(size_t));
        if (!elementCounts)
        {
            return NULL;
        }
        for (size_t o = 0; o < subarrays; o++)
        {
            elementCounts[o] = subarrays;
        }
    }
    void **array = (void **)malloc(sizeof(void *) * subarrays);

    if (!array)
    {
        if (!iselem)
        {
            free(elementCounts);
        }
        return NULL;
    }
    for (unsigned int i = 0; i < subarrays; i++)
    {
        array[i] = allocateArray(elementSize, elementCounts[i]);
        if (!array[i])
        {
            for (unsigned int j = 0; j < i; j++)
            {
                release(array[j]);
            }
            free(array);
            if (!iselem)
            {
                free(elementCounts);
            }
            return NULL;
        }
        memset(array[i], 0, elementSize * elementCounts[i]);
    }

    if (!iselem)
    {
        free(elementCounts);
    }

    if (newstruct(subarrays, true, array) == false)
    {
        for (unsigned int k = 0; k < subarrays; k++)
        {
            release(array[k]);
        }
        free(array);
        return NULL;
    }

    return array;
}

void acquire(void *memory)
{
    for (int i = 0; i < count_objects; i++)
    {
        if (mem[i].pointer == memory)
        {
            mem[i].ref_counter++;
            if (mem[i].is_2d)
            {
                void **nptr = (void **)memory;
                for (int j = 0; j < mem[i].count_of_elems; j++)
                {
                    acquire(nptr[j]);
                }
            }
            break;
        }
    }
}

void acquireArray2D(void **array)
{
    void *nptr = (void *)array;
    acquire(nptr);
}

bool release(void *memory)
{
    unsigned int index = 0;
    for (int i = 0; i < count_objects; i++)
    {
        if (mem[i].pointer == memory)
        {
            index = i;
            mem[i].ref_counter--;
            if (mem[i].is_2d)
            {
                void **nptr = (void **)memory;
                for (int j = 0; j < mem[i].count_of_elems; j++)
                {
                    release(nptr[j]);
                }
            }
            break;
        }
    }

    if (mem[index].ref_counter == 0)
    {
        free(mem[index].pointer);
        mem[index].pointer = NULL;
        return true;
    }
    return false;
}

bool releaseArray2D(void **array)
{
    void *nptr = (void *)array;
    return (release(nptr));
}

void clearVM(void)
{
    free(mem);
    count_objects = 0;
}