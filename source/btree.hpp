#include "node.hpp"

class BTree {
    Node* root;
    int min_deg;
public:
    BTree(int);
    void traverse_and_collect(std::vector<int64_t> &keys_arr);
    void delete_node(int64_t key);
    void insert(int64_t key);
    Node* search(int64_t key);
};

void merge(BTree &first_tree, BTree &second_tree, BTree &res_tree) {
    std::vector<int64_t> vect;
    first_tree.traverse_and_collect(vect);
    second_tree.traverse_and_collect(vect);

    for (int i = 0; i < vect.size(); i++) {
        res_tree.insert(vect[i]);
    }
}

BTree::BTree(int degree) {
    root = nullptr;
    min_deg = degree;
}

void BTree::traverse_and_collect(std::vector<int64_t> &keys_arr) {
    std::cout << "BEGIN" << std::endl;
    if (root != nullptr) {
        root->traverse_and_collect(keys_arr);
    }
    std::cout << std::endl;
}

Node* BTree::search(int64_t key) {
    return (root == nullptr) ? nullptr : root->search(key);
}

void BTree::delete_node(int64_t key) {
    Node* deleted = search(key);
    if (deleted != nullptr) {
        deleted->is_deleted = true;
    }
}

void BTree::insert(int64_t key) {
    if (root == nullptr) {
        root = new Node(min_deg, true);
        root->keys[0] = key;
        root->current_number_of_keys = 1;
    } else {
        if (search(key) == nullptr) {
            if (root->current_number_of_keys == 2 * min_deg - 1) {
                Node* new_root = new Node(min_deg, false);
                new_root->children[0] = root;
                new_root->split_child(0, root);

                int index_of_key = 0;
                if (new_root->keys[0] < key) {
                    index_of_key++;
                }
                new_root->children[index_of_key]->insert_to_unfilled_node(key);
                root = new_root;
            } else {
                root->insert_to_unfilled_node(key);
        }
        }
    }
}
