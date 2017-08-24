#ifndef RBTREE
#define RBTREE

/*CONTENTION:
all letters in function should be in lowercase
*/

template <class T>
class red_black_tree_node{
//private:

public:
    T key;
    bool red;
    //don't define a class contain itself
    //the object would be infinitely large, use pointers
    red_black_tree_node<T>* left;
    red_black_tree_node<T>* right;
    red_black_tree_node<T>* parent;

    red_black_tree_node();
    red_black_tree_node(T);
    // set_left(red_black_tree_node<T>*);
    // set_right(red_black_tree_node<T>*);
    void set_parent(red_black_tree_node<T>*);

};
//To operate with general types
template <class T>
class red_black_tree{
private:
    red_black_tree_node<T>* root;
    red_black_tree_node<T>* nil;
    void insert_fixup(red_black_tree_node<T>*);
    void delete_fixup(red_black_tree_node<T>*);
    void left_rotate(red_black_tree_node<T>*);
    void right_rotate(red_black_tree_node<T>*);
    void transplant(red_black_tree_node<T>*, red_black_tree_node<T>*);
    red_black_tree_node<T>* get_minimum(red_black_tree_node<T>*);
public:
    red_black_tree();
    ~red_black_tree();
    // declaration only need to contain types
    void delete_node(T);
    void insert_node(T);
    void print();
    //make sure predecessor and successor cannot change any member variable
    red_black_tree_node<T>* search(T) const;
    red_black_tree_node<T>* predecessor(red_black_tree_node<T>*) const;
    red_black_tree_node<T>* successor(red_black_tree_node<T>*) const;

};
#include "rb_tree.cpp" // avoid making the define of template class in cpp file here
#endif
