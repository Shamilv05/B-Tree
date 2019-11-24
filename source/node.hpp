#include <iostream>
#include <vector>

class Node {
    std::vector<int64_t> keys;
    uint16_t min_degree;
    uint16_t current_number_of_keys;
    std::vector<std::shared_ptr<Node>> children;
    bool is_leaf;
public:
    Node(uint16_t, bool);
    void traverse();
    Node* search(int64_t key);
};

Node::Node(uint16_t degree, bool _is_leaf) {
    min_degree = degree;
    is_leaf = _is_leaf;
    keys = std::vector<int64_t>(2 * min_degree - 1);
    children = std::vector<std::shared_ptr<Node>>(2 * min_degree);
    current_number_of_keys = 0;
}

void Node::traverse() {
    uint16_t i = 0;
    for (i = 0; i < current_number_of_keys; i++) {
        if (is_leaf == false) {
            children[i]->traverse();
        }

        std::cout << " " << keys[i];
    }
    if (is_leaf == false) {
        std::cout << " " << keys[i];
    }
}