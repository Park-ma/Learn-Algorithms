//
// Created by park on 2021/1/11.
//
#include <iostream>
#include "shuffle.h"
#include <vector>
int main(){
    std::cout<<"hello,world"<<std::endl;
    int t[10]={1,2,3,4,5,6,7,8,9,10};
    std::vector<int> a(std::begin(t),std::end(t));
    learn_al::shuffle(t,10);
    return 0;
}