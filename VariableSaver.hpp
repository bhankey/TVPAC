//
// Created by Sergey Shakotko on 08.06.2022.
//

#ifndef TVPIS__VARIABLESAVER_HPP_
#define TVPIS__VARIABLESAVER_HPP_

#include "Containers/HashTable.hpp"
#include "VariableBlock.hpp"

class VariableSaver {
 private:
    HashTable<VariableBlock> variableTable_;

    Allocator allocator_;
 public:
    explicit VariableSaver(const Allocator &allocator = Allocator()) :
        variableTable_(allocator), allocator_(allocator) {}

    ~VariableSaver() = default;

    template<class T>
    void SaveVariable(const std::string &name, const T &variable, VariableType type) {
        auto block = VariableBlock(type, allocator_);
        switch (type) {
            case VARIABLE_TYPE_INT:block.SetInt(variable);

                break;
            case VARIABLE_TYPE_DOUBLE:block.SetDouble(variable);

                break;
            default:throw std::invalid_argument("invalid variable type");
        }

        variableTable_.insert(name, block);
    }

    template<class T>
    T GetVariable(const std::string &name) const {
        auto block = variableTable_.find(name);
        if (!block.isInitialized()) {
            throw std::invalid_argument("variable not found"); // TODO можно кидать исключение, можно и не кидать
        }

        return block.GetElement<T>();
    }

    [[nodiscard]] bool IsVariableExists(const std::string &name) const {
        return variableTable_.find(name).isInitialized();
    }

    VariableType GetVariableType(const std::string &name) const {
        return variableTable_.find(name).GetType();
    }
};

#endif //TVPIS__VARIABLESAVER_HPP_
