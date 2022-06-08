//
// Created by Sergey Shakotko on 08.06.2022.
//

#ifndef TVPIS__VARIABLEBLOCK_HPP_
#define TVPIS__VARIABLEBLOCK_HPP_

#include <utility>

#include "Allocator/Allocator.hpp"

enum VariableType {
    VARIABLE_TYPE_NONE,
    VARIABLE_TYPE_INT,
    VARIABLE_TYPE_DOUBLE,
};

class VariableBlock {
 private:
    VariableType type_;
    bool isInitialized_ = false;
    ClientMemoryBlock<void> address_;

 public:
    VariableBlock() = default;

    explicit VariableBlock(VariableType type, Allocator allocator = Allocator()):
    type_(type), isInitialized_(false) {
        if (type_ == VARIABLE_TYPE_INT) {
            address_ = allocator.Allocate<void>(sizeof(int));
        } else if (type_ == VARIABLE_TYPE_DOUBLE) {
            address_ = allocator.Allocate<void>(sizeof(double));
        }
    }

    VariableBlock(const VariableBlock &other) = default;

    ~VariableBlock() = default;

    template<class T>
    T GetElement() const {
        if (!isInitialized_) {
            throw std::invalid_argument("variable is not initialized");
        }

        switch (type_) {
            case VARIABLE_TYPE_INT:
                return *(int *)(address_.GetObject());
            case VARIABLE_TYPE_DOUBLE:
                return *(double *)(address_.GetObject());
            default:
                throw std::invalid_argument("invalid variable type");
        }
    }

    [[nodiscard]] VariableType GetType() const {
        return type_;
    }

    [[nodiscard]] bool isInitialized() const {
        return isInitialized_;
    }

    void SetInt(int value) {
        if (type_ != VARIABLE_TYPE_INT) {
            throw std::invalid_argument("variable is not int type");
        }
        isInitialized_ = true;
        *(int *)(address_.GetObject()) = value;
    }

    void SetDouble(double value) {
        if (type_ != VARIABLE_TYPE_DOUBLE) {
            throw std::invalid_argument("variable is not double type");
        }
        isInitialized_ = true;
        *(double *)(address_.GetObject()) = value;
    }
};

#endif //TVPIS__VARIABLEBLOCK_HPP_
