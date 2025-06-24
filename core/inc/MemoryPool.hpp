#include <iostream>
#include <cstdlib>
#include <cassert>

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

/*
A simple bump allocator that uses a pre-enabled block of memory for faster allocation. Useful for
short lived allocations like IK solvers. 

1) allocates a single large chunk of memory up front using cmalloc
2) keeps a pointer (offset) to that chunk
3) allocates memory by moving offset forward (like a stack)

Ensures not using heap. 
*/

class MemoryPool {

private:
    char* pool;         // pointer to begining of allocated memory block || nullptr
    size_t offset;      // current position in the pool
    size_t capacity;    // max allowed size 

public:
    // 'delete' tells compiler MemoryPool cannot be copied or moved 
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    MemoryPool(MemoryPool&&) = delete;
    MemoryPool& operator=(MemoryPool&&) = delete;
    
    /* constructor
    allocates a contiguous chunk of memory and casts it to a char*
    so we can perform bytewise pointer arithmetic on it 
    */ 
    MemoryPool(size_t totalBytes)
    {
        pool = static_cast<char*>(std::malloc(totalBytes));
        if (nullptr == pool){
            throw std::bad_alloc();
        }
        capacity = totalBytes; 
        offset = 0; 
    } 
    
    /*
    adjust offset and ensure returned pointer is properly aligned
    */
    void* allocate(size_t size, size_t alignment = alignof(double)) {
        //  round offset up to the next multiple of alignment
        size_t alignedOffset = (offset + alignment - 1) &  ~(alignment - 1);
        if (alignedOffset + size > capacity){
            std::cout << "Memory pool out of space!" << std::endl;
            throw std::bad_alloc();
        }
        // void* ptr that points to raw (untyped) memory address, must cast to dereference
        void*  ptr = pool + alignedOffset;
        offset = alignedOffset + size;

        return ptr;
    }

    // helpers 
    size_t used() const { return offset; }
    size_t remaining() const { return capacity - offset; }
    void reset() { offset = 0; }

    // destructor
    ~MemoryPool() { std::free(pool); pool=nullptr; }
};


#endif