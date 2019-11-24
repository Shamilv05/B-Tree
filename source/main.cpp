#include "btree.hpp"

void test_presence(BTree t, int64_t key) {
    Node* s = t.search(key);
    if (s == nullptr) {
        std::cout << "Not in B-Tree" << std::endl;
    } else {
        std::cout << "In B-Tree" << std::endl;
    }
}

int main() {
    BTree t(3);
    t.insert(10); 
    t.insert(20); 
    t.insert(5); 
    t.insert(6); 
    t.insert(12); 
    t.insert(30); 
    t.insert(7); 
    t.insert(17);

    t.traverse();
    std::cout << std::endl;

    test_presence(t, 3);
    test_presence(t, 12);


    return 0;
}