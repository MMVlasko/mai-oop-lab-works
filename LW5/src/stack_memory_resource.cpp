#include <algorithm>
#include <stdexcept>

#include <stack_memory_resource.h>

StackMemoryResource::~StackMemoryResource() {
    for (auto& block : blocks)
        block.free = true;
}

void *StackMemoryResource::do_allocate(const size_t bytes, size_t alignment) {
    for (auto&[offset, size, free] : blocks)
        if (free && size >= bytes) {
            free = false;
            return buffer + offset;
        }

    size_t offset = 0;
    if (!blocks.empty()) {
        const auto& last_block = blocks.back();
        offset = last_block.offset + last_block.size;
    }

    if (offset + bytes > max_size)
        throw std::bad_alloc();

    blocks.push_back({offset, bytes, false});
    return buffer + offset;
}

void StackMemoryResource::do_deallocate(void *ptr, size_t bytes, size_t alignment) {
    auto offset = static_cast<char*>(ptr) - buffer;

    for (Block &b: blocks)
        if (b.offset == offset && b.size == bytes && !b.free) {
            b.free = true;
            return;
        }

    throw std::logic_error("This pointer wasn't allocated.");
}

bool StackMemoryResource::do_is_equal(const memory_resource &other) const noexcept {
    return this == &other;
}