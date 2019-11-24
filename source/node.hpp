#include <iostream>
#include <vector>

class Node {
    std::vector<int64_t> keys;
    int min_degree;
    int current_number_of_keys;
    std::vector<Node*> children;
    bool is_leaf;
public:
    Node(int, bool);
    void traverse();
    void insert_to_unfilled_node(int64_t key);
    void split_child(int child_index, Node* child);
    Node* search(int64_t key);
friend class BTree;
};

Node::Node(int degree, bool _is_leaf) {
    min_degree = degree;
    is_leaf = _is_leaf;
    keys = std::vector<int64_t>(2 * min_degree - 1);
    children = std::vector<Node*>(2 * min_degree);
    current_number_of_keys = 0;
}

/**
 * function for traversing all nodes of subtree,
 * rooted by this node
 */
void Node::traverse() {
    int i;
    for (i = 0; i < current_number_of_keys; i++) {
        if (!is_leaf) {
            children[i]->traverse();
        }

        std::cout << " " << keys[i];
    }
    if (!is_leaf) {
        children[i]->traverse();
    }
}

/**
 * function for searching certain value in
 * subtree, rooted by this node
 */
Node* Node::search(int64_t key) {
    int i = 0;
    while (i < current_number_of_keys && key > keys[i]) {
        i++;
    }

    if (keys[i] == key) {
        return this;
    }

    if (is_leaf) {
        return nullptr;
    }

    return children[i]->search(key);
}

/**
 * function to insert a certain key into the node,
 * on condition that node is not full when function is called
 */
void Node::insert_to_unfilled_node(int64_t key) {
    int i = current_number_of_keys - 1; // index of rightmost element

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

        if (children[i + 1]->current_number_of_keys == 2 * min_degree - 1) {
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
void Node::split_child(int child_index, Node* child) {
    Node* new_node = new Node(child->min_degree, child->is_leaf);
    new_node->current_number_of_keys = min_degree - 1;

    for (int j = 0; j < min_degree - 1; j++) {
        new_node->keys[j] = child->keys[j + min_degree];
    }

    if (!child->is_leaf) {
        for (int j = 0; j < min_degree; j++) {
            new_node->children[j] = child->children[min_degree + j];
        }
    }

    child->current_number_of_keys = min_degree - 1;

    for (int j = current_number_of_keys; j >= child_index + 1; j--) {
        children[j + 1] = children[j];
    }

    children[child_index + 1] = new_node;

    for (int j = current_number_of_keys - 1; j >= child_index; j--) {
        keys[j + 1] = keys[j];
    }

    keys[child_index] = child->keys[min_degree - 1];

    current_number_of_keys++;
}
