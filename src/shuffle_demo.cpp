//
// Created by park on 2021/1/11.
//
#include <iostream>
#include "shuffle.h"
int main(){
    int t[10]={1,2,3,4,5,6,7,8,9,10};
    learn_al::shuffle(t,0,10);
    for(auto n:t)
        std::cout<<n<<'\t';
    std::cout<<std::endl;
    return 0;
}