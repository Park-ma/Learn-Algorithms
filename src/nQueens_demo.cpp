//
// Created by park on 2021/1/12.
//
#include "nQueens.h"
#include <iostream>
#include <vector>
#include <string>
int main(){
    learn_al::Queens q(4);
    std::cout<<q.getNum()<<std::endl;
    std::vector<std::vector<std::string>> res = q.getBoard();
    int n = 1;
    for(auto &b:res){
        std::cout<<"NO."<<n++<<std::endl;
        for(auto &s:b)
            std::cout<<s<<std::endl;
    }
    return 0;
}