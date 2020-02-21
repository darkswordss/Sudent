//
// Created by Jose Guerrero on 1/30/20.
//

#ifndef SUDENT_BST_H
#define SUDENT_BST_H


#include <vector>
#include <exception>
#include <iostream>
#include <stack>

namespace cop3530 {

    template<typename Key, typename T>
    class bst {
        struct node {
            // key
            Key indentifier;
            // value
            T data;
            // left child
            node *left;
            // right child
            node *right;

            int height = 1;


            node() {
                right = nullptr;
                left = nullptr;

            }

            // Parameterized constructor:
            node(Key k, T t) {
                right = nullptr;
                left = nullptr;
                indentifier = k;
                data = t;
            }
        };
        //node* right;
        //node* left;

        unsigned int nodeCount;

        // root of tree
        node *root;


    public:
        bst();

        ~bst();

        void insert(const Key &key, const T &t);


        node *deleteNode(node *root, const Key &key) {


            // STEP 1: PERFORM STANDARD BST DELETE
            if (root == NULL)
                return root;

            if (key < root->indentifier)
                root->left = deleteNode(root->left, key);

            else if (key > root->indentifier)
                root->right = deleteNode(root->right, key);

            else {

                if ((root->left == NULL) ||
                    (root->right == NULL)) {
                    node *temp = root->left ?
                                 root->left :
                                 root->right;


                    if (temp == NULL) {
                        temp = root;
                        root = NULL;
                    } else
                        *root = *temp;

                    delete(temp);
                } else {

                    node *temp = minValueNode(root->right);
                    root->indentifier = temp->indentifier;
                    root->data = temp->data;
                    root->right = deleteNode(root->right,
                                             temp->indentifier);
                }
            }

            if (root == NULL)
                return root;


            root->height = 1 + max(height(root->left),
                                   height(root->right));

            int balance = getBalance(root);
            if (balance > 1 &&
                getBalance(root->left) >= 0)
                return rightRotate(root);
            // Left Right Case
            if (balance > 1 &&
                getBalance(root->left) < 0) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            // Right Right Case
            if (balance < -1 &&
                getBalance(root->right) <= 0)
                return leftRotate(root);
            // Right Left Case
            if (balance < -1 &&
                getBalance(root->right) > 0) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;
        }


        int max(int a, int b) {
            return (a > b) ? a : b;
        };

        node *leftRotate(node *x) {
            node *y = x->right;
            node *T2 = y->left;


            y->left = x;
            x->right = T2;


            x->height = max(height(x->left),
                            height(x->right)) + 1;
            y->height = max(height(y->left),
                            height(y->right)) + 1;
            if (x == root) {
                root = y;
            }


            return y;
        }

        node *rightRotate(node *y) {
            node *x = y->left;
            node *T2 = x->right;


            x->right = y;
            y->left = T2;


            y->height = max(height(y->left),
                            height(y->right)) + 1;
            x->height = max(height(x->left),
                            height(x->right)) + 1;


            if (y == root) {
                root = x;
            }
            return x;
        }


        int height(node *N) {
            if (N == NULL)
                return 0;
            return N->height;
        }

        node *minValueNode(node *NODE) {
            node *current = NODE;


            while (current->left != NULL)
                current = current->left;

            return current;
        };

        void erase(const Key &key);

        int getBalance(node *N) {
            if (N == NULL)
                return 0;
            return height(N->left) - height(N->right);
        }

        T &at(const Key &key);

        node *insert2(node *pos, const Key &key, const T t) {

            if (root == nullptr) {
                root = new node(key, t);
                nodeCount++;
                return (root);

            }
            if (pos == NULL) {
                nodeCount++;
                return (new node(key, t));
            }

            if (key < pos->indentifier) {
                pos->left = insert2(pos->left, key, t);

            } else if (key > pos->indentifier) {
                pos->right = insert2(pos->right, key, t);

            }


            pos->height = 1 + max(height(pos->left), height(pos->right));
            int balance = getBalance(pos);
            //Left left
            if (balance > 1 && key < pos->left->indentifier)
                return rightRotate(pos);
            // Right Right Case
            if (balance < -1 && key > pos->right->indentifier)
                return leftRotate(pos);

            // Left Right Case
            if (balance > 1 && key > pos->left->indentifier) {
                pos->left = leftRotate(pos->left);

                return rightRotate(pos);
            }

            // Right Left Case
            if (balance < -1 && key < pos->right->indentifier) {
                pos->right = rightRotate(pos->right);
                return leftRotate(pos);
            }

            /* return the (unchanged) node pointer */
            return pos;
        };


        bool contains(const Key &key) const;

        bool empty() const;

        size_t size() const;

        std::vector<std::pair<Key, T>> inorder_contents();

        std::vector<std::pair<Key, T>> preorder_contents();

        node *position;
        int sumNum = 0;

    };

    template<typename Key, typename T>
    bst<Key, T>::bst() {

        this->root = nullptr;
        nodeCount = 0;
        this->position = nullptr;
    }

    template<typename Key, typename T>
    bst<Key, T>::~bst() {

    }


    template<typename Key, typename T>
    void bst<Key, T>::insert(const Key &key, const T &t) {
        if (contains(key)) {
            erase(key);
        }

        insert2(root, key, t);

    }


    template<typename Key, typename T>
    void bst<Key, T>::erase(const Key &key) {

        if (contains(key) && nodeCount != 1) {

            deleteNode(root, key);
            nodeCount--;
        } else if (contains(key) == false) {
            throw std::out_of_range("out of range");
        } else if (nodeCount == 1) {
            nodeCount--;
            root = nullptr;
            return;
        }


    }

    template<typename Key, typename T>
    T &bst<Key, T>::at(const Key &key) {
        if (root == nullptr) {
            throw std::out_of_range("error");

        }

        node *currentPosition = root;
        if (root->indentifier == key) {
            return root->data;
        } else if (currentPosition->indentifier == key) {
            return root->data;
        } else {
            while (currentPosition->indentifier != key) {
                if (key < currentPosition->indentifier && currentPosition->left != nullptr) {
                    currentPosition = currentPosition->left;
                    if (key == currentPosition->indentifier) {
                        return currentPosition->data;
                    }
                } else if (key > currentPosition->indentifier && currentPosition->right != nullptr) {
                    currentPosition = currentPosition->right;
                    if (key == currentPosition->indentifier) {
                        return currentPosition->data;
                    }
                } else throw std::out_of_range("error");
            }
            throw std::out_of_range("error");
        }

    }

    template<typename Key, typename T>
    bool bst<Key, T>::contains(const Key &key) const {
        node *currentPosition = root;
        if (root == nullptr) { return false; }
        if (root->indentifier == key) {
            return true;
        }
        while (currentPosition->indentifier != key) {
            if (key < currentPosition->indentifier) {
                if (currentPosition->left != nullptr) {
                    currentPosition = currentPosition->left;
                }
                if (key == currentPosition->indentifier) {
                    return true;
                } else if (currentPosition->right != nullptr && key == currentPosition->right->indentifier) {
                    return true;

                } else return false;
            } else {
                if (currentPosition->right != nullptr) {
                    currentPosition = currentPosition->right;
                }
                if (key == currentPosition->indentifier) {
                    return true;
                } else if (currentPosition->left != nullptr && key == currentPosition->left->indentifier) {
                    return true;

                } else return false;
            }
        }
        return false;

    }

    template<typename Key, typename T>
    bool bst<Key, T>::empty() const {
        if (nodeCount == 0) {
            return true;
        } else return false;
    }

    template<typename Key, typename T>
    size_t bst<Key, T>::size() const {
        return nodeCount;
    }

    template<typename Key, typename T>
    std::vector<std::pair<Key, T>> bst<Key, T>::inorder_contents() {
        std::vector<std::pair<Key, T>> contents;


        std::stack<node *> s;
        node *curr = root;

        while (curr != nullptr || s.empty() == false) {

            while (curr != nullptr) {

                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            s.pop();
            std::pair<Key, T> myPair(curr->indentifier, curr->data);
            contents.push_back(myPair);

            curr = curr->right;

            if (curr == nullptr && s.empty() == true) { return contents; }
        }
        return contents;
    }

    template<typename Key, typename T>
    std::vector<std::pair<Key, T>> bst<Key, T>::preorder_contents() {
        std::vector<std::pair<Key, T>> contents;


        // Base Case
        if (root == NULL)
            return contents;


        std::stack<node *> nodeStack;
        nodeStack.push(root);


        while (nodeStack.empty() == false) {

            node *node = nodeStack.top();

            std::pair<Key, T> myPair(node->indentifier, node->data);
            contents.push_back(myPair);

            nodeStack.pop();

            if (node->right)
                nodeStack.push(node->right);
            if (node->left)
                nodeStack.push(node->left);
            if (nodeStack.empty() == true) {
                return contents;
            }
        }
        return contents;

    }
}


#endif //SUDENT_BST_H
