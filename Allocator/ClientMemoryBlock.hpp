//
// Created by Sergey Shakotko on 08.06.2022.
//

#ifndef TVPIS__CLIENT_HPP_
#define TVPIS__CLIENT_HPP_

#include <cstdio>
#include "InternalMemory.hpp"

template<typename T>
class ClientMemoryBlock {
 public:
    InternalMemoryAddress address{};
    unsigned int size{};
    bool isFree{};

 private:
    T *realAddress;
    InternalMemoryBlock *internal{};

 public:
    ClientMemoryBlock(size_t segmentNum, size_t offsetFromStart, size_t _size,
                      bool _isFree, void *_realAddress, InternalMemoryBlock *_internal
                      )
    {
        address = InternalMemoryAddress{};
        address.segmentNumber = segmentNum;
        address.offsetFromStart = offsetFromStart;

        size = _size;
        isFree = _isFree;
        realAddress = (T *)_realAddress;
        internal = _internal;
    }

    ClientMemoryBlock() = default;

    ClientMemoryBlock(ClientMemoryBlock<T> const &other) {
        address = other.address;

        size = other.size;
        isFree = other.isFree;
        realAddress = other.realAddress;
        internal = other.internal;
    }

    ClientMemoryBlock<T> operator=(ClientMemoryBlock<T> other)
    {
        address = other.address;
        size = other.size;
        isFree = other.isFree;
        realAddress = other.realAddress;
        internal = other.internal;

        return *this;
    }

    void Free() {
        isFree = true;
        internal->isFree = true;
    }

    T *GetObject() {
        return realAddress;
    }
    const T *GetObject() const {
        return realAddress;
    }

    void PutObjectInArray(int index) {
        new(realAddress + index) T();
    }


    bool operator==(const ClientMemoryBlock<T>& rhs) {
        if (this->realAddress == rhs.realAddress) {
            return true;
        }

        return false;
    }
    bool operator!=(const ClientMemoryBlock<T>& rhs)  {
        if (this->realAddress != rhs.realAddress) {
            return true;
        }

        return false;
    }
};

#endif //TVPIS__CLIENT_HPP_
