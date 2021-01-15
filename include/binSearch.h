

#ifndef LEARN_ALGORITHMS_BINSEARCH_H
#define LEARN_ALGORITHMS_BINSEARCH_H
namespace learn_al{
    template<typename T>
    static int binSearch(T*A,int lo,int hi,T const&tar){
        while (lo<hi){
            int mi = lo+(hi-lo)/2;
            if(tar<A[mi])
                hi = mi;
            else
                lo=mi+1;
        }
        if(A[lo-1]==tar) return --lo;
        return -1;
    }
}

#endif //LEARN_ALGORITHMS_BINSEARCH_H
