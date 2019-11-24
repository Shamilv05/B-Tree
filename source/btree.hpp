#include "node.hpp"

class BTree {
    std::shared_ptr<Node> root;
    uint16_t min_deg;
public:
    BTree(uint16_t);
    void traverse();
    std::shared_ptr<Node> search(int64_t key);
};

BTree::BTree(uint16_t degree) {
    root = nullptr;
    min_deg = degree;
}

void BTree::traverse() {
    return root->traverse();
}

std::shared_ptr<Node> BTree::search(int64_t key) {
    return (root = nullptr) ? nullptr : root->search(key);
}
