//
// Created by park on 2021/1/12.
//

#ifndef LEARN_ALGORITHMS_NQUEENS_H
#define LEARN_ALGORITHMS_NQUEENS_H
#include <vector>
#include <string>
namespace learn_al {
    using std::string;
    using std::vector;

    class Queens {
    private:
        vector<vector<string>> result;
        int count;
        int size;
        void dfs(vector<int>&board,int row){
            if(row==board.size()){
                count++;
                vector<string> tmp = print(board);
                result.push_back(tmp);
                return;
            }
            for(int col=0;col<board.size();col++){
                if(isValid(board,row,col)){
                    board[row] = col;
                    dfs(board,row+1);
                    board[row] = -1;
                }
            }
        }
        bool isValid(vector<int>&board,int row,int col){
            for(int i=0;i<row;++i){
                if(board[i]==col||board[i]+i==row+col||board[i]-i==col-row)
                    return false;
            }
            return true;
        }
        vector<string> print(vector<int> const&board){
            vector<string> res(board.size(),string(board.size(),'.'));
            for(int i=0;i<board.size();i++){
                res[i][board[i]]='Q';
            }
            return res;
        }
    public:
        Queens(int n):size(n){
            vector<int>board(size,-1);
            dfs(board,0);
        }
        int getNum(){
            return count;
        }
        vector<vector<string>> getBoard(){
            return result;
        }
    };
}
#endif //LEARN_ALGORITHMS_NQUEENS_H
