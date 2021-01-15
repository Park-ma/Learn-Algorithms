#include "avlTree.h"

int main(){
    int t[10] = {1,2,3,4,5,6,7,8,9,10};
    learn_al::avlTree<int> tree(0);
    for(auto n:t)
        tree.insert(n);
    tree.printTree();
    return 0;
}