#include "rb_tree.hpp"
#include <string>
int main(){
    red_black_tree<int> tree;
    for (int i = 0; i < 9; i++){
        tree.insert_node(i);
    }
    tree.print();
    cout << "Insert good" << endl;
    for (int i = 0; i < 1; i++){
        tree.delete_node(i);
        tree.print();
    }

}
