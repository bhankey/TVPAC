//
// Created by Sergey Shakotko on 08.06.2022.
//

#ifndef TVPIS_ALLOCATOR_INTERNALMEMORY_HPP_
#define TVPIS_ALLOCATOR_INTERNALMEMORY_HPP_

#include <cstdio>
struct InternalMemoryAddress {
    size_t segmentNumber;
    size_t offsetFromStart;
};

class InternalMemoryBlock {
 public:
    InternalMemoryAddress address{};
    unsigned int size{};
    bool isFree{};
    void *realAddress{};

    InternalMemoryBlock(
        size_t segmentNum,
        size_t offsetFromStart,
        size_t _size,
        bool _isFree,
        void *_realAddress
        );
};

#endif //TVPIS_ALLOCATOR_INTERNALMEMORY_HPP_
