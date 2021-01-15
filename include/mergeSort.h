

#ifndef LEARN_ALGORITHMS_MERGESORT_H
#define LEARN_ALGORITHMS_MERGESORT_H
namespace learn_al{
    template<typename T>
    void merge(T*a,int lo,int mi,int hi);
    template<typename T>
    void mergeSort(T*A,int lo,int hi){
        if(hi-lo<2) return;
        int mi = lo+(hi-lo)/2;
        mergeSort(A,lo,mi);
        mergeSort(A,mi,hi);
        merge(A,lo,mi,hi);
    }
    template<typename T>
    void merge(T*a,int lo,int mi,int hi){
        T *A = a+lo;
        int lb = mi-lo;
        T*B = new T[lb];
        for(int i=0;i<lb;i++)
            B[i]=A[i];
        int lc = hi-mi;
        T*C = a+mi;
        for(int i=0,j=0,k=0;(j<lb)||(k<lc);){
            if((j<lb)&&(!(k<lc)||(B[j]<=C[k])))
                A[i++] = B[j++];
            if((k<lc)&&(!(j<lb)||(C[k]<B[j])))
                A[i++] = C[k++];
        }
        delete []B;
    }
    template<typename T>
    void mergeSort2(T*A,int lo,int hi){
        int length = hi-lo;
        int cur = lo;
        for(int step=1;step<2*length;step*=2){
            while (cur<hi){
                int left = cur;
                int right  = (cur+step>=hi)?hi:cur+step;
                int mi = left+step/2;
                merge(A,left,mi,right);
                cur = right;
            }
            cur = lo;
        }
    }
}

#endif //LEARN_ALGORITHMS_MERGESORT_H
