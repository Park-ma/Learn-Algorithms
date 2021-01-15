
#include <string>
#include <vector>
#include <iostream>
#include "RPN.h"
using std::vector;
using std::string;
int main(){

    vector<string> infix = {
            "1.2","+","3","*","2.5","\0"
    };
    vector<string>post = learn_al::inToPost(infix);
    for(auto &c:post)
        std::cout<<c<<'\t';
    std::cout<<std::endl;
    return 0;
}
