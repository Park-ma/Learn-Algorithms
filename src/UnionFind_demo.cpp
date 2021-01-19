
#include "UnionFind.h"
#include <iostream>
int main(){
    learn_al::Djset djset(8);
    djset.merge(1,2);
    djset.merge(3,2);
    djset.merge(3,7);
    std::cout<<djset.find(3)<<std::endl;
    std::cout<<djset.find(7)<<std::endl;
    std::cout<<djset.find(6)<<std::endl;
    return 0;
}
