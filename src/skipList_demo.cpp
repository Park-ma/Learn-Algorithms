#include <iostream>
#include "SkipList.h"
#include "shuffle.h"

int main(){
    learn_al::skipList<int> list;
    int num[100];
    for(int i=0;i<100;i++){
        num[i] = i;
    }
    learn_al::shuffle(num,0,100);
    for(int i=0;i<100;i++){
        list.insert(num[i]);
    }
    for (int i = 0; i < 50; ++i) {
        list.remove(num[i]);
    }
    std::cout<<list.search(100)<<std::endl;
    std::cout<<list.search(1)<<std::endl;

    return 0;
}
