//
// Created by park on 2021/1/11.
//

#ifndef LEARN_ALGORITHMS_SHUFFLE_H
#define LEARN_ALGORITHMS_SHUFFLE_H
#include <random>
//[1,2,<---origin--->,9,10,<-random->]
//   |-------swap-------|
//[1,10,<---origin-->9,2,<--random--->]
namespace learn_al{
    template<typename T>
    void shuffle(T& array, int len){
        std::random_device rd;
        std::default_random_engine e1(rd());
        std::uniform_int_distribution<int> un_dis(0,len-1);
        for(int i=len;i>0;i--){
            int j = un_dis(e1)%i;
            using std::swap;
            swap(array[i-1],array[j]);
        }
    }
}
#endif //LEARN_ALGORITHMS_SHUFFLE_H
