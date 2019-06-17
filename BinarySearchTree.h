//
// Created by BaiZehong on 2019/6/17.
//

#ifndef ALGORITHM_BINARYSEARCHTREE_H
#define ALGORITHM_BINARYSEARCHTREE_H

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

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

            Node(Node *node){
                this->key = node->key;
                this->value = node->value;
                this->left = node->left;
                this->right = node->right;
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
            destory(root);
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

        // 前序遍历
        void preOrder(){
            preOrder(root);
        }

        // 中序遍历
        void inOrder(){
            inOrder(root);
        }

        // 层序遍历
        void levelOrder(){
            queue<Node*> q;
            q.push(root);
            while (!q.empty()){
                Node *node = q.pop();
                cout << node->key << endl;
                if (node->left != NULL) q.push(node->left);
                if (node->right != NULL) q.push(node->right);
            }
        }

        // 寻找最小值
        Key minimum(){
            assert(count != 0);
            Node *minNode = minimum(root);
        }

        // 删除最小值
        void removeMin(){
            if (root != NULL){
                root = removeMin(root);
            }
        }

        // 删除任意节点
        void remove(Key key){
            if (root != NULL){
                root = remove(root, key);
            }
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

        // 对以node为根的二叉树前序遍历
        void preOrder(Node* node){
            if (node != NULL){
                cout << node->key << endl;
                preOrder(node->left);
                preOrder(node->right);
            }
        }

        void inOrder(Node* node){
            if (node != NULL){
                inOrder(node->left);
                cout << node->key << endl;
                inOrder(node->right);
            }
        }

        void destory(Node* node){
            if (node != NULL){
                destory(node->left);
                destory(node->right);
                delete node;
                count--;
            }
        }

        Node* minimum(Node* node){
            if (node->left == NULL) return node;
            return minimum(node->left);
        }

        // 删除最小节点
        Node* removeMin(Node* node){
            if (node->left == NULL){
                Node* rightNode = node->right;
                delete node;
                count --;
                return rightNode;
            }
            node->left = removeMin(node->left);
            return node;
        }

        Node* remove(Node* node, Key key){
            if (node == NULL) return NULL;

            if (key < node->key){
                node->left = remove(node->left, key);
                return node;
            } else if (key > node->key){
                node->right = remove(node->right, key);
                return node;
            } else {
                if (node->left == NULL){
                    Node *rightNode = node->right;
                    delete node;
                    count --;
                    return rightNode;
                }
                if (node->right == NULL){
                    Node *leftNode = node->left;
                    delete node;
                    count --;
                    return leftNode;
                }
                // node的左右孩子都不为空
                Node *nextRoot = new Node(minimum(node->right));
                nextRoot->right = removeMin(node->right);
                nextRoot->left = node->left;
                delete node;
                // 不需要 count --, 因为在removeMin中已经删除了一个节点
                return nextRoot;
            }
        }
    };
}

#endif //ALGORITHM_BINARYSEARCHTREE_H
