
#include <iostream>
#include "bubbleSort.h"
#include "mergeSort.h"
#include "shuffle.h"
template<typename T>
void test(T *t,int lo,int hi,void(*fun)(T*,int,int));
int main(){
    int t[12]={1,2,3,4,5,6,7,8,9,10,16,14};
    test(t,0,10,learn_al::shuffle);
    test(t,0,10,learn_al::bubbleSort);
    test(t,0,10,learn_al::shuffle);
    test(t,0,10,learn_al::mergeSort);
    test(t,0,10,learn_al::shuffle);
    test(t,0,10,learn_al::mergeSort2);
    return 0;
}
template<typename T>
void test(T *t,int lo,int hi,void(*fun)(T*,int,int)){
    fun(t,lo,hi);
    for(int i=lo;i<hi;i++){
        std::cout<<t[i]<<'\t';
    }
    std::cout<<std::endl;
}