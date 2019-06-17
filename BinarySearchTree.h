//
// Created by BaiZehong on 2019/6/17.
//

#ifndef ALGORITHM_BINARYSEARCHTREE_H
#define ALGORITHM_BINARYSEARCHTREE_H

namespace BinarySearchTree{

    template <typename Key, template Value>
    class BST{

    private:
        struct Node{
            Key key;
            Value value;
            Node *left;
            Node *right;

            Node(Key key, Value value){
                this ->key = key;
                this ->value = value;
                this -> left = this -> right = NULL;
            }
        };
        Node *root;
        int count;

    public:
        BST(){
            root = NULL;
            count = 0;
        }
        ~BST(){
            // TODO
        }

        int size(){ return  count;}
        bool isEmpty(){ return count == 0;}

        void insert(Key key, Value value){
            root = insert(root, key, value);
        }

        bool contain(Key key){
            return contain(root, key);
        }

        // 返回指向value的指针，如果没找到返回null
        Value* search(Key key){
            return search(root, key);
        }

    private:
        // 返回插入节点后的新根
        Node* insert(Node *node, Key key, Value value){
            if (node == NULL){
                count++;
                return new Node(key, value);
            }
            if (node->key == key){
                node->value = value;
            }
            if (node->key > key){
                node->left = insert(node->left, key, value);
            } else if (node->key < key){
                node->right = insert(node->right, key, value);
            }
            return node;
        }

        // 在node为根的二叉树中查找是否包含key
        bool contain(Node* node, Key key){
            if (node == NULL) return false;
            if (key == node->key) return true;
            else if (key < node->key) return contain(node->left, key);
            else return contain(node->right, key);
        }

        Value* search(Node* node, Key key){
            if (node == NULL) return NULL;
            if (key == node->key) return &(node->value);
            else if (key < node->key) return search(node->left, key);
            else return search(node->right, key);
        }
    };
}

#endif //ALGORITHM_BINARYSEARCHTREE_H
