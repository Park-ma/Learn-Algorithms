
#include "BTree.h"

int main(){
    learn_al::BTree<int> tree(10);
    for(int i=1;i<1000;i++){
        tree.insert(i);
    }
    for(int i=500;i>0;i--)
        tree.remove(i);
    return 0;
}
