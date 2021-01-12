//
// Created by park on 2021/1/12.
//

#ifndef LEARN_ALGORITHMS_RPN_H
#define LEARN_ALGORITHMS_RPN_H
#include <string>
#include <vector>
#include <stack>
#include <cctype>
namespace learn_al{
    const char pri[9][9] = { //运算符优先等级 [栈顶] [当前]
            /*              |-------------------- 当 前 运 算 符 --------------------| */
            /*              +      -      *      /      ^      !      (      )      \0 */
            /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
            /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
            /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
            /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
            /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
            /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
            /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
            /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
            /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
    };

    using std::vector;
    using std::string;
    using std::stack;
    char orderBetween(char c1,char c2);
    int optr2int ( char op );

    vector<string> inToPost(vector<string> const &infix){
        vector<string> postfix;
        stack<char> optr;
        optr.push('\0');
        int i = 0;
        while (!optr.empty()&&i<infix.size()){
            if(infix[i].size() > 1 || (infix[i].size() == 1) && std::isdigit(infix[i][0])){
                postfix.push_back(infix[i]);
                i++;
            }else{
                char c = static_cast<char>(infix[i][0]);
                switch (orderBetween(optr.top(),c)) {
                    case '<':
                        optr.push(c);
                        i++;
                        break;
                    case '=':
                        optr.pop();
                        i++;
                        break;
                    case '>':{
                        char op = optr.top();
                        postfix.emplace_back(1, op);
                        optr.pop();
                        break;
                    }
                    default:
                        exit(-1);
                }
            }
        }
        return postfix;
    }
    char orderBetween(char c1,char c2){
        int i1 = optr2int(c1);
        int i2 = optr2int(c2);
        return pri[i1][i2];
    }
    int optr2int ( char op ) { //由运算符转译出编号
        switch ( op ) {
            case '+' : return 0; //加
            case '-' : return 1; //减
            case '*' : return 2; //乘
            case '/' : return 3; //除
            case '^' : return 4; //乘方
            case '!' : return 5; //阶乘
            case '(' : return 6; //左括号
            case ')' : return 7; //右括号
            case '\0': return 8; //起始符与终止符
            default  : exit ( -1 ); //未知运算符
        }
    }
}
#endif //LEARN_ALGORITHMS_RPN_H
