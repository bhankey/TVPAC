//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_HASHTABLE_HPP
#define TVPIS_HASHTABLE_HPP

#include "list"
#include "../Allocator.cpp"
#include "Utils.hpp"
namespace ft {
template<typename T>
struct HashTableElement {
    std::string key;
    T value;
};

template<typename T>
class HashTable {
 private:
    static const int default_size = 8;

    ClientMemoryBlock<std::list<HashTableElement<T> > > _Array_list;

    int size;
    int buffer_size;
    constexpr static const double rehash_size = 0.75;

    ::Allocator allocator_;
 public:
    HashTable() : allocator_(Allocator()) {
        _Array_list = allocator_.Allocate<std::list<HashTableElement<T>>>(
            sizeof(std::list<HashTableElement<T>>) * default_size);

        buffer_size = default_size;
        size = 0;
        for (int i = 0; i < buffer_size; i++) {
            _Array_list.PutObjectInArray(i);
        }

    }

    int hash_function(std::string s) // Хеш-функция
    {
        const int p = 31;
        long long hash = 0, p_pow = 1;

        for (int i = 0; i < s.length(); i++) {
            hash += int(s[i] - '0') * p_pow;
            p_pow *= p;
        }

        return abs(hash % buffer_size);
    }
    //Вставка элемента в хеш-таблицу
    void insert(std::string _key, T _value) {
        size++;
        if (float(size) / float(buffer_size) >= rehash_size) {
            this->resize();
        }
        HashTableElement<T> Element;
        Element.key = _key;
        Element.value = _value;

        _Array_list.GetObject()[hash_function(_key)].push_back(Element);
    }

    //Поиск элемента по ключу
    T find(std::string _key) {
        int index = hash_function(_key);
        if (!_Array_list.GetObject()[index].empty()) {
            for (auto iter = _Array_list.GetObject()[index].begin();
                 iter != _Array_list.GetObject()[index].end(); iter++) {
                if (_key == (*iter).key) {
                    return (*iter).value;
                }
            }
        }

        return _Array_list.GetObject()[index].front().value;
    }

    // Удаление элемента по ключу
    void remove(std::string _key) {
        int index = hash_function(_key);
        bool finded = false;
        int number;
        if (!_Array_list.GetObject()[index].empty()) {
            int i = 0;
            for (auto iter = _Array_list.GetObject()[index].begin();
                 iter != _Array_list.GetObject()[index].end(); iter++) {
                if (_key == (*iter).key) {
                    finded = true;
                    number = i;
                    break;
                }
                i++;
            }
            if (finded) {
                auto iter = _Array_list.GetObject()[index].begin();
                advance(iter, number);
                _Array_list.GetObject()[index].erase(iter);
            }
        }
    }

    //Проверка
    void debugList() {
        for (int i = 0; i < buffer_size; i++) {
            std::cout << i << " ";
            if (!_Array_list.GetObject()[i].empty()) {
                std::cout << _Array_list.GetObject()[i].front().key << " "
                          << _Array_list.GetObject()[i].front().value;
            }
            std::cout << "\n";
        }
    }

    //Расширение хеш-таблицы
    void resize() {
        int past_buffer_size = buffer_size;
        buffer_size *= 2;
        size = 0;

        auto newArrayList = allocator_.template Allocate<std::list<HashTableElement<T>>>(
            sizeof(std::list<HashTableElement<T>>) * buffer_size);
        for (int i = 0; i < buffer_size; i++) {
            newArrayList.PutObjectInArray(i);
        }

        for (int i = 0; i < past_buffer_size; i++) {
            newArrayList.GetObject()[i] = _Array_list.GetObject()[i];

            _Array_list.GetObject()[i].clear();
        }

        _Array_list = newArrayList;
    }

};
}
#endif //TVPIS_HASHTABLE_HPP
