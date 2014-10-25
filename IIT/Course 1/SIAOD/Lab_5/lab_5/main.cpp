//
//  main.cpp
//  lab_5
//
//  Created by Alex Kuk on 29.05.14.
//  Copyright (c) 2014 Alex. All rights reserved.
//

#include <iostream>

struct Node {
    int data;
    //unsigned int depth;
    Node *parent = nullptr, *left = nullptr, *right = nullptr;
};

class Tree
{
protected:
    Node *root;
    
    Node * node_factory(int data)
    {
        Node *node = new Node();
        node->data = data;
        
        return node;
    }
    
    Node * node_factory(int data, Node *parent)
    {
        Node *node = new Node();
        node->data = data;
        node->parent = parent;
        
        return node;
    }
    
    void add(Node *root, int input_data)
    {
        if (input_data > root->data) {
            if (root->right == nullptr) {
                root->right = node_factory(input_data, root);
            } else {
                add(root->right, input_data);
            }
        } else if (input_data < root->data) {
            if (root->left == nullptr) {
                root->left = node_factory(input_data, root);
            } else {
                add(root->left, input_data);
            }
        }
    }
    
    void remove(Node *root, int input_data)
    {
        Node **tmp = nullptr;
        
        if (root == nullptr) {
            return;
        }
        
        if (input_data > root->data) {
            remove(root->right, input_data);
        } else if (input_data < root->data) {
            remove(root->left, input_data);
        } else {
            if (root->right == nullptr && root->left == nullptr) {
                root = nullptr;
            } else if (root->right != nullptr && root->left != nullptr) {
                
                if (root->right->left == nullptr) {
                    root->right->left = root->left;
                    root = root->right;
                } else {
                    tmp = &(root->right->left);
                    while ((*tmp)->left != nullptr) {
                        *tmp = (*tmp)->left;
                    }
                    root->data = (*tmp)->data;
                    *tmp = nullptr;
                }
            } else {
                if (root->right != nullptr) {
                    root = root->right;
                } else {
                    root = root->left;
                }
            }
        }
    }
    Node * find(Node *root, int input_data)
    {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (root->data == input_data) {
            return root;
        }
        
        if (input_data > root->data) {
            return find(root->right, input_data);
        } else {
            return find(root->left, input_data);
        }
    }
    
    void inflex_traverse(Node *root)
    {
        if (root == nullptr) {
            return;
        }
        inflex_traverse(root->left);
        std::cout << root->data << ", ";
        inflex_traverse(root->right);
    }
    
    void prefix_traverse(Node *root)
    {
        if (root == nullptr) {
            return;
        }
        
        std::cout << root->data << ", ";
        prefix_traverse(root->left);
        prefix_traverse(root->right);
    }
    
    void postfix_traverse(Node *root)
    {
        if (root == nullptr) {
            return;
        }
        
        postfix_traverse(root->left);
        postfix_traverse(root->right);
        std::cout << root->data << ", ";
    }
    
public:
    
    void add(int input_data)
    {
        if (root == nullptr) {
            root = node_factory(input_data);
        } else {
            add(root, input_data);
        }
    }
    
    void remove(int input_data)
    {
        remove(root, input_data);
    }
    
    void find(int input_data)
    {
        Node *tmp = find(root, input_data);
        
        if (tmp == nullptr) {
            std::cout << "Element not found\n";
            return;
        }
        
        std::cout << "Element found, data is - " << tmp->data <<  "\n";
    }
    
    void inflex_traverse()
    {
        std::cout << "inflex traverse: ";
        inflex_traverse(root);
        std::cout << "\n";
    }
    
    void prefix_traverse()
    {
        std::cout << "prefix traverse: ";
        prefix_traverse(root);
        std::cout << "\n";
    }
    
    void postfix_traverse()
    {
        std::cout << "postfix traverse: ";
        postfix_traverse(root);
        std::cout << "\n";
    }
    
};

int main(int argc, const char * argv[])
{
    Tree tree;
    
    tree.add(42);
    tree.add(25);
    tree.add(64);
    tree.add(12);
    tree.add(37);
    tree.add(13);
    tree.add(30);
    tree.add(43);
    tree.add(87);
    tree.add(99);
    tree.add(9);
    tree.add(66);
    tree.add(67);
    tree.add(65);
    
    tree.find(777);
    tree.find(9);
    
    tree.find(64);
    
    std::cout << "Remove 64\n";
    tree.remove(64);
    
    tree.inflex_traverse();
    tree.prefix_traverse();
    tree.postfix_traverse();
    
    return 0;
}

