#include <iostream>
#include <exception>

#include "containers/HashTable.hpp"
using namespace std;
int main() {
    ft::HashTable<int> ht = ft::HashTable<int>();
    string key = "клюшка";
    int value = 5;
    ht.insert(key, value);
    ht.insert("1", 1);
    ht.insert("ebane45", 10);
    ht.insert("tema",234);
    ht.insert("Vika",564);
    ht.insert("Sergey",782);
    ht.insert("Kolya",3627);
    ht.insert("Kirill",674332);
    ht.debugList();
    //ht.insert(key, 7);
//    cout << ht.find(key);
//    cout << ht.find("1");
//    ht.ebalvrot();
//    ht.resize();
//    cout << "\n" << "new";
//    ht.ebalvrot();
//    cout << ht.find(key);
//    ht.remove(key);
//    cout << "\n";
//    ht.ebalvrot();
    return 0;
}