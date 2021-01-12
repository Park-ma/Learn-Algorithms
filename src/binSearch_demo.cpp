//
// Created by park on 2021/1/11.
//
#include <iostream>
#include "binSearch.h"
int main(){
    int t[10]={1,2,3,4,5,6,7,8,9,10};
    int fi = learn_al::binSearch(t,0,10,3);
    std::cout<<"find index:\t"<<fi<<std::endl;
    int notfi = learn_al::binSearch(t,0,10,11);
    std::cout<<"find index:\t"<<notfi<<std::endl;
    return 0;
}
