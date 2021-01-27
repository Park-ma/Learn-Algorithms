
#ifndef LEARN_ALGORITHMS_KMP_H
#define LEARN_ALGORITHMS_KMP_H
#include <string>
#include <vector>

namespace learn_al{
    using std::string;
    using std::vector;

    vector<int> genNext(string& P);
    int KMP(string& S,string& P){
        vector<int> next = genNext(P);
        int n = S.size();
        int m = P.size();
        int i = 0;
        int j = 0;
        while (i<n&&j<m){
            if(j==-1||S[i]==P[j]){
                i++;
                j++;
            }else{
                j = next[j];
            }
        }
        if(j==m)    return i-m;
        return  -1;
    }
    vector<int> genNext(string& P){
        int m = P.size();
        vector<int> next(m,0);
        int j = -1;
        next[0] = j;
        int i = 0;
        while (i<m){
            if(j==-1||P[j]==P[i]){
                i++;
                j++;
                next[i] = (P[i]!=P[j]?j:next[j]);
            }else{
                j = next[j];
            }
        }
        return next;
    }

}
#endif //LEARN_ALGORITHMS_KMP_H
