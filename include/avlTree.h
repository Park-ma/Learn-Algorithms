//
// Created by park on 2021/1/12.
//

#ifndef LEARN_ALGORITHMS_AVLTREE_H
#define LEARN_ALGORITHMS_AVLTREE_H
#include <string>
#include <queue>
#include <iostream>


namespace learn_al{
    using std::string;
    using std::queue;
    using std::cout;
    template<typename T>
    struct avlNode{
        T val;
        struct avlNode<T>* left;
        struct avlNode<T>* right;
        avlNode(const T e){
            val = e;
            left = nullptr;
            right = nullptr;
        }
    };
    template<typename T>
    class avlTree{
    private:
        avlNode<T>* _root;
        avlNode<T>* connect34(avlNode<T>*a,avlNode<T>*b,avlNode<T>*c,
                       avlNode<T>*T0,avlNode<T>*T1,avlNode<T>*T2,avlNode<T>*T3);

        avlNode<T>* rotateAt(avlNode<T>* v);
        avlNode<T>* getSucc(avlNode<T>* v){
            if(!v)  return v;
            while (v->right)
                v = v->right;
            return v;
        }
        avlNode<T>* getPos(avlNode<T>* v){
            if(!v)  return v;
            while (v->left)
                v = v->left;
            return v;
        }
        bool isBalanced(avlNode<T>* root);
        int getHeight(avlNode<T>*root);
        avlNode<T>* search(avlNode<T> *v,T e);
        avlNode<T>* remove(avlNode<T>* root,T e);
        avlNode<T>* insert(avlNode<T>*root,T e);
        avlNode<T>* reBalance(avlNode<T>* root);
        void printTree(avlNode<T>* root);
    public:
        avlTree(const T e){
            _root = new avlNode<T>(e);
        }
        int getHeight();
        void insert(T e);
        void remove(T e);
        avlNode<T>* search(T e);
        void printTree(){
            printTree(_root);
        }
    };
    template<typename T>
    avlNode<T>* avlTree<T>::connect34(avlNode<T>*a,avlNode<T>*b,avlNode<T>*c,
                                      avlNode<T>*T0,avlNode<T>*T1,avlNode<T>*T2,avlNode<T>*T3){
        a->left = T0;
        a->right = T1;
        c->left = T2;
        c->right = T3;
        b->left = a;
        b->right = c;
        return b;
    }
    template<typename T>
    avlNode<T>* avlTree<T>::insert(avlNode<T> *root, T e) {
        if(!root){
            auto* p = new avlNode<T>(e);
            return p;
        }
        if(e<root->val){
            root->left = insert(root->left,e);
            root = reBalance(root);
        }else{
            root->right = insert(root->right,e);
            root = reBalance(root);
        }
        return root;
    }
    template<typename T>
    void avlTree<T>::insert(T e){
        _root = insert(_root,e);
    }
    template<typename T>
    avlNode<T>* avlTree<T>::remove(avlNode<T> *root, T e) {
        if(!search(e))  return root;
        if(!root)   return root;
        if(root->val==e){
            if(!root->left||!root->right){
                avlNode<T>* d= root;
                root = (root->left)?root->left:root->right;
                delete d;
                d = nullptr;
            }else{
                int leftH = getHeight(root->left);
                int rightH = getHeight(root->right);
                avlNode<T>* tmp = (leftH>rightH)?getPos(root):getSucc(root);
                root->val = tmp->val;
                (leftH>rightH)?root->left = remove(root->left,tmp->val)
                        :root->right = remove(root->right,tmp->val);

            }
        }else if(e<root->val){
            root->left = remove(root->left,e);
        }else{
            root->right = remove(root->right,e);
        }
        return root;
    }
    template<typename T>
    void avlTree<T>::remove(T e){
        _root = remove(_root,e);
        _root = reBalance(_root);
    }
    template<typename T>
    avlNode<T>* avlTree<T>::search(T e) {
        return search(_root,e);
    }
    template<typename T>
    avlNode<T>* avlTree<T>::search(avlNode<T> *v, T e) {
        if(!v||(e==v->val)) return v;
        return search((e < v->val) ? v->left : v->right, e);
    }
    template<typename T>
    int avlTree<T>::getHeight(avlNode<T>* root) {
        if(!root) return 0;
        int leftH = getHeight(root->left);
        int rightH = getHeight(root->right);
        return (leftH>rightH)?leftH+1:rightH+1;
    }
    template<typename T>
    int avlTree<T>::getHeight() {
        return getHeight(_root);
    }
    template<typename T>
    bool avlTree<T>::isBalanced(avlNode<T> *root) {
        if(!root)   return true;
        int leftH = getHeight(root->left);
        int rightH = getHeight(root->right);
        return (leftH>rightH)?leftH-rightH<=1:rightH-leftH<=1;
    }
    template<typename T>
    avlNode<T>* avlTree<T>::reBalance(avlNode<T> *root) {
        if(isBalanced(root))    return root;
        return rotateAt(root);
    }
    template<typename T>
    avlNode<T>* avlTree<T>::rotateAt(avlNode<T> *v) {
        int leftH1 = getHeight(v->left);
        int rightH1 = getHeight(v->right);
        if(leftH1>rightH1){
            int leftH2 = getHeight(v->left->left);
            int rightH2 = getHeight(v->left->right);
            if(leftH2>rightH2)
                 v = connect34(v->left->left,v->left,v,
                          v->left->left->left,v->left->left->right,
                          v->left->right,v->right);
            else
                v = connect34(v->left,v->left->right,v,
                          v->left->left,v->left->right->left,
                          v->left->right->right,v->right);
        }else{
            int leftH2 = getHeight(v->right->left);
            int rightH2 = getHeight(v->right->right);
            if(leftH2>rightH2)
                v = connect34(v,v->right->left,v->right,
                          v->left,v->right->left->left,
                          v->right->left->right,v->right->right);
            else
                v = connect34(v,v->right,v->right->right,
                          v->left,v->right->left,
                          v->right->right->left,v->right->right->right);
        }
        return v;
    }

    template<typename T>
    void avlTree<T>::printTree(avlNode<T> *root) {
        queue<avlNode<T>*> q;
        if(root) q.push(root);
        while (!q.empty()){
            int size = q.size();
            for(int i=0;i<size;i++){
                avlNode<T>* p = q.front();
                q.pop();
                if(p->left)
                    q.push(p->left);
                if(p->right)
                    q.push(p->right);
                cout<<'\t'<<p->val<<'\t';
            }
            cout<<std::endl;
        }
    }
}
#endif //LEARN_ALGORITHMS_AVLTREE_H
