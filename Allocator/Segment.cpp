//
// Created by Sergey Shakotko on 08.06.2022.
//

#include "Segment.hpp"

Segment::Segment(size_t size, size_t segmentNum) : allocatedMemory(size), segmentNumber(segmentNum) {
    memory = static_cast<std::byte *>(malloc(size));
    if (memory == nullptr) {
        throw std::out_of_range("failed to allocate system memory");
    }

    auto firstBlock = new InternalMemoryBlock(segmentNum, 0, size, true, memory);
    blocks.push_back(firstBlock);
}

void Segment::AllocateBlock(int index, size_t needToAlloc) {
    if (!blocks[index]->isFree) {
        throw std::out_of_range("failed to allocate not empty mem");
    }

    blocks[index]->size = needToAlloc;
    blocks[index]->isFree = false;

    if (blocks.size() <= index + 1) {
        auto nextBlockStart = blocks[index]->address.offsetFromStart + blocks[index]->size;
        auto nextBlockSize = allocatedMemory - nextBlockStart;

        auto memBlock = new InternalMemoryBlock(segmentNumber, nextBlockStart, nextBlockSize,
                                                true, memory + nextBlockStart);

        blocks.push_back(memBlock);
    }
}

void Segment::PrintAllBlocks() {
    auto i = 0;
    for (auto &block: blocks) {
        printf("\tblock №%i address: (%zu, %zu) with state %s\n", i++, block->address.segmentNumber, block->address.offsetFromStart, block->isFree? "true" : "false");
    }
}

void Segment::Free(size_t offsetFromStart) {
    for (int i = 0; i < blocks.size(); ++i) {
        if (blocks[i]->address.offsetFromStart == offsetFromStart) {
            blocks[i]->isFree = true;
            auto freeMemoryStartIndex = i;
            while((freeMemoryStartIndex > 0 && blocks[freeMemoryStartIndex - 1]->isFree)) {
                --freeMemoryStartIndex;
            }

            size_t allFreeMemory{};
            int freeMemoryEndIndex = freeMemoryStartIndex;
            while (freeMemoryEndIndex < blocks.size() && blocks[freeMemoryEndIndex]->isFree) {
                allFreeMemory += blocks[freeMemoryEndIndex]->size;
                freeMemoryEndIndex++;
            }

            if (freeMemoryStartIndex + 1 < freeMemoryEndIndex) {
                auto firstToDelete = std::next(blocks.begin(), freeMemoryStartIndex + 1);
                auto lastToDelete = std::next(blocks.begin(), freeMemoryEndIndex);
                blocks.erase(firstToDelete, lastToDelete);
            }

            blocks[freeMemoryStartIndex]->isFree = true;
            blocks[freeMemoryStartIndex]->size = allFreeMemory;

            return;
        }
    }

    throw std::out_of_range("failed to free not exist memory");
}

InternalMemoryBlock *Segment::FindAndAllocate(size_t size) {
    for (int i = 0; i < blocks.size(); ++i) {
        if (!blocks[i]->isFree) {
            continue;
        }

        if (blocks[i]->size >= size) {
            AllocateBlock(i, size);

            return blocks[i];
        }
    }

    return nullptr;
}