
#include <splayTree.h>

int main(){
    learn_al::splayTree<int> tree(1);
    for(int i=2;i<=4;i++)
        tree.insert(i);
    tree.insert(-1);
    tree.remove(4);
    return 0;
}