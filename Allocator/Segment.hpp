//
// Created by Sergey Shakotko on 08.06.2022.
//

#ifndef TVPIS_ALLOCATOR_SEGMENT_HPP_
#define TVPIS_ALLOCATOR_SEGMENT_HPP_

#include "InternalMemory.hpp"
#include <vector>

class Segment {
 public:
    std::byte *memory;
    std::vector<InternalMemoryBlock *> blocks;

    const size_t segmentNumber;
    const size_t allocatedMemory;

    Segment(size_t size, size_t segmentNum);

    InternalMemoryBlock *FindAndAllocate(size_t size);
    void Free(size_t offsetFromStart);
    void PrintAllBlocks();

 private:
    void AllocateBlock(int index, size_t needToAlloc);
};

#endif //TVPIS_ALLOCATOR_SEGMENT_HPP_
