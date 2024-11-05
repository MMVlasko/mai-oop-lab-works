#pragma once

#include <vector>

class StackMemoryResource : public std::pmr::memory_resource {
    struct Block {
        size_t offset;
        size_t size;
        bool free;
    };

    static constexpr size_t max_size = 1024;

    char buffer[max_size];
    std::vector<Block> blocks;

    protected:
        void *do_allocate(size_t bytes, size_t alignment) override;
        void do_deallocate(void *ptr, size_t bytes, size_t alignment) override;
        bool do_is_equal(const memory_resource &other) const noexcept override;

    public:
        ~StackMemoryResource() override;
};