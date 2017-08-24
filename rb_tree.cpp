#include "rb_tree.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
using namespace std;
template<class T>
red_black_tree_node<T>::red_black_tree_node(){
    red = 0;
}

template<class T>
red_black_tree_node<T>::red_black_tree_node(T val){
    red = 0;
    key = val;
}

template<class T>
red_black_tree<T>::red_black_tree(){
    nil = new red_black_tree_node<T>();
    nil->left = nil->right = nil->parent = nil;
    nil->red = 0;
    root = nil;
}

template<class T>
red_black_tree<T>::~red_black_tree(){

}

template<class T>
void red_black_tree<T>::insert_node(T val){
    red_black_tree_node<T>* x_p = nil;
    red_black_tree_node<T>* x = root;
    if (search(val) != nil){
        cout << "Error: Val " << val <<" already exists!\n";
        exit(0);
    }
    while(x != nil){
        x_p = x;
        if (x->key < val) x = x->right;
        else x = x->left;
    }
    red_black_tree_node<T>* new_node = new red_black_tree_node<T>(val);
    new_node->parent = x_p;
    if (x_p == nil){
        root = new_node;
    }else{
        if (x_p->key < val) x_p->right = new_node;
        else x_p->left = new_node;
    }
    new_node->left = nil;
    new_node->right = nil;
    new_node->red = 1;
    insert_fixup(new_node);
}

template<class T>
void red_black_tree<T>::insert_fixup(red_black_tree_node<T>* node){
    while(node->parent->red == 1){
        red_black_tree_node<T>* gp = node->parent->parent;
        if (node->parent == gp->left){
            if (gp->right->red == 1){
                node->parent->red = 0;
                gp->red = 1;
                gp->right->red = 0;
                node = gp;
            }else{
                if (node == node->parent->right){
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->red = 0;
                node->parent->parent->red = 1;
                right_rotate(node->parent->parent);
            }
        }else{
            if (gp->left->red == 1){
                node->parent->red = 0;
                gp->left->red = 0;
                gp->red = 1;
                node = gp;
            }else{
                if (node == node->parent->left){
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->red = 0;
                node->parent->parent->red = 1;
                left_rotate(node->parent->parent);
            }
        }
    }
    root->red = 0;
}

template<class T>
void red_black_tree<T>::left_rotate(red_black_tree_node<T>* node){
    red_black_tree_node<T>* y = node->right;
    node->right = y->left;
    if (y->left != nil) y->left->parent = node;
    y->parent = node->parent;
    if (node->parent == nil) root = y;
    else{
        if (node->parent->right == node) node->parent->right = y;
        else node->parent->left = y;
    }
    node->parent = y;
    y->left = node;
}

template<class T>
void red_black_tree<T>::right_rotate(red_black_tree_node<T>* node){
    red_black_tree_node<T>* y = node->left;
    node->left = y->right;
    if (y->right != nil) y->right->parent = node;
    y->parent = node->parent;
    if (node->parent == nil) root = y;
    else{
        if (node->parent->right == node) node->parent->right = y;
        else node->parent->left = y;
    }
    node->parent = y;
    y->right = node;
}

template<class T>
void red_black_tree<T>::print(){
    queue< red_black_tree_node<T>* > node_queue;
    node_queue.push(root);
    vector<T> keys;
    vector<int> colors;
    while(!node_queue.empty()){
        red_black_tree_node<T>* node = node_queue.front();
        cout << "node " << node->key;
        if (node->left != nil){
            node_queue.push(node->left);
            cout << " left_child: " << node->left->key;
        }
        if (node->right != nil){
            node_queue.push(node->right);
            cout << " right_child: " << node->right->key;
        }
        cout << endl;
        keys.push_back(node->key);
        colors.push_back(node->red);
        node_queue.pop();
    }
    cout << "KEYS: ";
    for (int i = 0; i < keys.size(); i++) cout << keys[i] << " ";
    cout << endl;
    cout << "colors: ";
    for (int i = 0; i < colors.size(); i++) cout << colors[i] << " ";
    cout << endl;
}

template<class T>
void red_black_tree<T>::delete_node(T val){
    red_black_tree_node<T>* node;
    red_black_tree_node<T>* fix_node;
    while ((node = search(val)) != nil){
        int ori_color = node->red;
        if(node->left == nil){
            fix_node = node->right;
            transplant(node, node->right);
        }else if(node->right == nil){
            fix_node = node->left;
            transplant(node,node->left);
        }else{
            red_black_tree_node<T>* y = get_minimum(node->right);
            ori_color = y->red;
            red_black_tree_node<T>* x = y->right;
            if (node->right != y){
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->red = node->red;
            fix_node = x;
            delete(node);
        }
        if (ori_color == 0) delete_fixup(fix_node);
    }
}

template<class T>
void red_black_tree<T>::transplant(red_black_tree_node<T>* dnode, \
    red_black_tree_node<T>* inode){
        if (dnode->parent == nil) root = inode;
        else if (dnode->parent->left == dnode)
            dnode->parent->left = inode;
        else
            dnode->parent->right = inode;
        inode->parent = dnode->parent;
}

template<class T>
red_black_tree_node<T>* red_black_tree<T>::search(T val) const{
    red_black_tree_node<T>* x = root;
    while(x != nil){
        if (x->key < val){
            x = x->right;
        }
        if(x->key > val){
            x = x->left;
        }
        if(x->key == val){
            return x;
        }
    }
    return nil;
}

template<class T>
red_black_tree_node<T>* red_black_tree<T>::get_minimum(red_black_tree_node<T>* root){
    while(root->left != nil) root = root->left;
    return root;
}

template<class T>
void red_black_tree<T>::delete_fixup(red_black_tree_node<T>* node){
    while(node != root && node->red == 0){
        if (node->parent->left == node){
            red_black_tree_node<T>* w = node->parent->right;
            if (w->red == 0){
                if (w->left->red == 0 && w->right->red == 0){
                    w->red = 1;
                    node = node->parent;
                }
                else{
                    if (w->right->red == 0){
                        w->left->red = 0;
                        w->red = 1;
                        right_rotate(w);
                        w = w->parent;
                    }
                    w->red = 0;
                    node->parent->red = 0;
                    w->right->red = 0;
                    left_rotate(node->parent);
                    node = root;
                }
            }else{
                node->parent->red = 1;
                w->red = 0;
                left_rotate(node->parent);
                w = node->parent->right;
            }
        }else{
            red_black_tree_node<T>* w = node->parent->left;
            if (w->red == 0){
                if (w->left->red == 0 && w->right->red == 0){
                    w->red = 1;
                    node = node->parent;
                }
                else{
                    if (w->left->red == 0){
                        w->right->red = 0;
                        w->red = 1;
                        left_rotate(w);
                        w = w->parent;
                    }
                    w->red = 0;
                    node->parent->red = 0;
                    w->left->red = 0;
                    right_rotate(node->parent);
                    node = root;
                }
            }else{
                node->parent->red = 1;
                w->red = 0;
                right_rotate(node->parent);
                w = node->parent->left;
            }
        }
    }
    node->red = 0;
}
