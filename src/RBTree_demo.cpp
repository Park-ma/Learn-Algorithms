
#include "RBTree.h"

int main(){
    learn_al::RBTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.remove(4);
    tree.remove(5);
    tree.remove(6);
    tree.remove(7);
    tree.remove(8);
    tree.remove(9);
    tree.remove(10);
    tree.remove(2);
    tree.remove(1);
    tree.remove(3);
    return 0;
}

