
#ifndef LEARN_ALGORITHMS_UNIONFIND_H
#define LEARN_ALGORITHMS_UNIONFIND_H
#include <vector>
namespace learn_al{
    using std::vector;
    class Djset{
    private:
        vector<int> parent;
        vector<int> rank;
        int _size;
    public:
        Djset(int n):parent(vector<int>(n)),rank(vector<int>(n)),_size(n){
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
                rank[i] = 1;
            }
        }
        int find(int x){
            if(parent[x]!=x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        void merge(int i,int j){
            int i_root = find(i);
            int j_root = find(j);
            if(i_root==j_root)
                return;
            if(rank[i_root]<rank[j_root]){
                int tmp = i_root;
                i_root = j_root;
                j_root = tmp;
            }
            parent[j_root] = i_root;
            if(rank[j_root]==rank[i_root])
                rank[i_root]+=1;
        }
        bool isUnion(int i,int j){
            return find(i)==find(j);
        }
        int size(){
            return _size;
        }

    };
}
#endif //LEARN_ALGORITHMS_UNIONFIND_H
