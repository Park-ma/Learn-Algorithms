#include <string>
#include <iostream>

#include "KMP.h"
using std::string;
int main(){
    string S = "abcdabcfabcgabcabchabci";
    string P = "abcabch";
    int start = learn_al::KMP(S,P);
    for(int i=start;i<start+P.size();i++){
        std::cout<<S[i]<<",";
    }
    std::cout<<std::endl;
    return 0;
}