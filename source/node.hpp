#include <iostream>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
    std::vector<int64_t> keys;
    uint16_t min_degree;
    uint16_t current_number_of_keys;
    std::vector<std::shared_ptr<Node>> children;
    bool is_leaf;
public:
    Node(uint16_t, bool);
    void traverse();
    void insert_to_unfilled_node(int64_t key);
    void split_child(uint16_t child_index, std::shared_ptr<Node> node);
    std::shared_ptr<Node> search(int64_t key);
friend class BTree;
};

Node::Node(uint16_t degree, bool _is_leaf) {
    min_degree = degree;
    is_leaf = _is_leaf;
    keys = std::vector<int64_t>(2 * min_degree - 1);
    children = std::vector<std::shared_ptr<Node>>(2 * min_degree);
    current_number_of_keys = 0;
}

/**
 * function for traversing all nodes of subtree,
 * rooted by this node
 */
void Node::traverse() {
    uint16_t i = 0;
    for (i = 0; i < current_number_of_keys; i++) {
        if (is_leaf == false) {
            children[i]->traverse();
        }

        std::cout << " " << keys[i];
    }
    if (is_leaf == false) {
        children[i]->traverse();
    }
}

/**
 * function for searching certain value in
 * subtree, rooted by this node
 */
std::shared_ptr<Node> Node::search(int64_t key) {
    uint16_t i = 0;
    while (i < current_number_of_keys && keys[i] < key) {
        i++;
    }

    if (keys[i] == key) {
        return shared_from_this();
    }

    if (is_leaf == true) {
        return nullptr;
    }

    return children[i]->search(key);
}

/**
 * function to insert a certain key into the node,
 * on condition that node is not full when function is called
 */
void Node::insert_to_unfilled_node(int64_t key) {
    uint16_t i = current_number_of_keys - 1; // index of rightmost element

    if (is_leaf) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = key;
        current_number_of_keys++;
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }

        if (children[i + 1]->current_number_of_keys == 2 * min_degree + 1) {
            split_child(i + 1, children[i + 1]);

            if(keys[i + 1] < key) {
                i++;
            }
        }
        children[i + 1]->insert_to_unfilled_node(key);
    }
}

/**
 * function to split a certain node,
 * on condition that node is full when function is called
 */
void Node::split_child(uint16_t child_index, std::shared_ptr<Node> child) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(child->min_degree, child->is_leaf);
    new_node->current_number_of_keys = min_degree - 1;

    for (uint16_t i = 0; i < min_degree - 1; i++) {
        new_node->keys[i] = child->keys[i + min_degree];
    }

    if (child->is_leaf == false) {
        for (uint16_t i = 0; i < min_degree; i++) {
            new_node->children[i] = child->children[min_degree + i];
        }
    }

    child->current_number_of_keys = min_degree - 1;

    for (uint16_t j = current_number_of_keys; j >= child_index; j--) {
        children[j + 1] = children[j];
    }

    children[child_index + 1] = new_node;
    for (uint16_t j = current_number_of_keys - 1; j >= child_index; j--) {
        keys[j + 1] = keys[j];
    }

    keys[child_index] = child->keys[min_degree - 1];

    current_number_of_keys++;
}
