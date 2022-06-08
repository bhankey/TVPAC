//
// Created by Sergey Shakotko on 08.06.2022.
//
#include "InternalMemory.hpp"

InternalMemoryBlock::InternalMemoryBlock(size_t segmentNum, size_t offsetFromStart,
    size_t _size, bool _isFree, void *_realAddress) {
address = InternalMemoryAddress{};
address.segmentNumber = segmentNum;
address.offsetFromStart = offsetFromStart;

size = _size;
isFree = _isFree;
realAddress = _realAddress;
}