//
// Created by Sergey Shakotko on 08.06.2022.
//

#ifndef TVPIS_ALLOCATOR_ALLOCATOR_HPP_
#define TVPIS_ALLOCATOR_ALLOCATOR_HPP_

#include <vector>
#include "Segment.hpp"
#include "ClientMemoryBlock.hpp"

class Allocator {
 private:
    std::vector<Segment> segments{};

    const unsigned int maxSegmentSize = 2048;
 public:
    void PrintAllSegments() {
        auto i = 0;
        for (auto &segment: segments) {
            printf("segment №%i:\n", i++);
            segment.PrintAllBlocks();
        }
    }

    template<typename T>
    ClientMemoryBlock<T> Allocate(size_t size) {
        if (size > maxSegmentSize) {
            throw std::invalid_argument("try allocate more than allowed once time");
        }

        for (auto &segment: segments) {
            auto memory = segment.FindAndAllocate(size);
            if (memory == nullptr) {
                continue;
            }

            ClientMemoryBlock<T> clientBlock = ClientMemoryBlock<T> (
                memory->address.segmentNumber, memory->address.offsetFromStart, memory->size, memory->isFree, memory->realAddress, memory);

            return clientBlock;
        }

        auto newSegment = Segment(maxSegmentSize, segments.size());
        auto memory = newSegment.FindAndAllocate(size);
        if (memory == nullptr) {
            throw std::out_of_range("failed to allocate memory");
        }

        segments.push_back(newSegment);

        ClientMemoryBlock<T> clientBlock = ClientMemoryBlock<T> (
            memory->address.segmentNumber, memory->address.offsetFromStart, memory->size, memory->isFree, memory->realAddress, memory);

        return clientBlock;
    }

    template<typename T>
    void Free(ClientMemoryBlock<T> &memory_block) {
        if (memory_block.address.segmentNumber > segments.size()) {
            throw std::out_of_range("can't free this memory");
        }

        segments[memory_block.address.segmentNumber].Free(memory_block.address.offsetFromStart);
        memory_block.Free();
    }
};

#endif //TVPIS_ALLOCATOR_ALLOCATOR_HPP_
