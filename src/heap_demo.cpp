#include "heap.h"
#include <iostream>
int main(){

    learn_al::heap<int> hp;
    hp.push(9);
    hp.push(94);
    hp.push(90);
    hp.push(90);
    hp.push(99);
    hp.push(0);
    hp.push(30);
    hp.push(50);
    std::cout<<hp.getMax()<<std::endl;
    while (hp.pop())
        std::cout<<hp.getMax()<<std::endl;
    return 0;
}
