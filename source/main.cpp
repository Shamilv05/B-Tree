#include "btree.hpp"

int main() {
    BTree t(3);
    t.insert(117);
    t.insert(10); 
    t.insert(20); 
    t.insert(5); 
    t.insert(6); 
    t.insert(12); 
    t.insert(30);
    t.insert(7);
    t.insert(17);

    BTree t2(3);
    t2.insert(210); 
    t2.insert(320); 
    t2.insert(45); 
    t2.insert(65);
    t2.insert(75);
    t2.insert(85); 
    t2.insert(116); 
    t2.insert(2312); 
    t2.insert(12330);

    BTree *b = new BTree(3);
    merge(t, t2, *b);
    std::cout << std::endl;
    std::vector<int64_t> vect = {};
    b->traverse_and_collect(vect);
    std::cout << std::endl;

    return 0;
}