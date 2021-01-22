#ifndef LEARN_ALGORITHMS_HEAP_H
#define LEARN_ALGORITHMS_HEAP_H
#define DEFAULT_SIZE 10
#include <vector>
namespace learn_al{
    using std::vector;
    template<typename T>
    class heap{
    private:
        vector<T> _elem;
        int _size;
    public:
        heap(){
            _size = 0;
        }
        bool isEmpty(){
            return _size==0;
        }
        T getMax(){
            if(_size>0)
                return _elem[0];
            else
                return NULL;
        }
        bool push(T key){
            _elem.push_back(key);
            _size++;
            int i=_size-1;
            while (i>0){
                int parent = (i-1)/2;
                if(_elem[i]>_elem[parent]){
                    std::swap(_elem[i],_elem[parent]);
                    i = parent;
                }else{
                    break;
                }
            }
            return true;
        }
        bool pop(){
            if(_size==0)    return false;
            _elem[0] = _elem[_size-1];
            _elem.erase(_elem.end()-1);
            _size--;
            int i=0;
            while (i<_size){
                int leftC = i*2+1;
                int rightC = i*2+2;
                if(leftC>=_size)
                    break;
                else {
                    int maxC;
                    if (leftC<_size&&rightC < _size) {
                        maxC = _elem[leftC] > _elem[rightC] ? leftC : rightC;
                    }else{
                        maxC = leftC;
                    }
                    if (_elem[i] < _elem[maxC]){
                        std::swap(_elem[i],_elem[maxC]);
                        i = maxC;
                    }else{
                        break;
                    }
                }
            }
            return true;
        }
    };
}

#endif //LEARN_ALGORITHMS_HEAP_H
