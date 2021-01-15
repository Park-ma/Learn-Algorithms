

#ifndef LEARN_ALGORITHMS_BUBBLESORT_H
#define LEARN_ALGORITHMS_BUBBLESORT_H
namespace learn_al{
    template<typename T>
    void bubbleSort(T*a,int lo,int hi){
        bool sorted = false;
        for(int i=lo;i<hi-1&&(!sorted);i++){
            sorted = true;
            for(int j=hi-1;j>i;j--){
                if(a[j]<a[j-1]){
                    sorted= false;
                    std::swap(a[j],a[j-1]);
                }
            }
        }
    }
}
#endif //LEARN_ALGORITHMS_BUBBLESORT_H
