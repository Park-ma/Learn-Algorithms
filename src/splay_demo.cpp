//
// Created by park on 2021/1/13.
//
#include <splayTree.h>

int main(){
    learn_al::splayTree<int> tree(0);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(-1);
    return 0;
}