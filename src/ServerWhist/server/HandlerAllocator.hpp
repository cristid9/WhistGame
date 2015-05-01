#ifndef HANDLERALLOCATOR_HPP
#define HANDLERALLOCATOR_HPP

#include <cstdlib>
#include <type_traits>

#define maxSizeBuffer 1024

class HandlerAllocator
{
    public:
        HandlerAllocator() : used(false)
        {
        
        }

        HandlerAllocator(const HandlerAllocator&) = delete;
        HandlerAllocator& operator=(const HandlerAllocator&) = delete;

        void* Allocate(std::size_t size)
        {
            if (!used && size < sizeof(storage))
            {
                used = true;
                return &storage;
            }
            else
            {
                return ::operator new (size);
            }
        }

        void Deallocate(void *pointer)
        {
            if (pointer == &storage)
                used = false;
            else
                ::operator delete(pointer);
        }

    private:
        typename std::aligned_storage<maxSizeBuffer>::type storage;
        bool used;
};

#endif

