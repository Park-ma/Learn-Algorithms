//
// Created by park on 2021/1/13.
//

#ifndef LEARN_ALGORITHMS_SPLAYTREE_H
#define LEARN_ALGORITHMS_SPLAYTREE_H
namespace learn_al{
    template<typename T>
    struct splayNode{
        T val;
        struct splayNode<T>* left;
        struct splayNode<T>* right;
        struct splayNode<T>* parent;
        splayNode(const T& e){
            val = e;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };
    template<typename T>
    class splayTree{
    private:
        splayNode<T>* _root;

        splayNode<T>* search(splayNode<T>* &root,T e,splayNode<T>* &parent);
        splayNode<T>* splay(splayNode<T>* v);
        splayNode<T>* zag(splayNode<T>* v){
            splayNode<T>* p = v->right;
            v->right= p->left;
            if(v->right) v->right->parent = v;
            p->left = v;
            p->parent = v->parent;
            v->parent = p;
            if(p->parent){
                if(v==p->parent->left)
                    p->parent->left = p;
                else
                    p->parent->right = p;
            }
            return  p;
        }
        splayNode<T>*  zig(splayNode<T>* v){
            splayNode<T>* p = v->left;
            v->left = p->right;
            if(v->left) v->left->parent = v;
            p->right = v;
            p->parent = v->parent;
            v->parent = p;
            if(p->parent){
                if(v==p->parent->left)
                    p->parent->left = p;
                else
                    p->parent->right = p;
            }
            return  p;
        }

    public:
        splayTree(const T& e){
            _root = new splayNode<T>(e);
        }
        splayNode<T>* search(const T& e);
        splayNode<T>* insert(const T& e);
        splayNode<T>* remove(const T& e);
    };
    template<typename T>
    splayNode<T>* splayTree<T>::splay(splayNode<T>* v){
        if(!v) return nullptr;
        splayNode<T>* p ;
        splayNode<T>* g ;
        while ((p=v->parent)&&(g=p->parent)){
            splayNode<T>* gg = g->parent;
            if(p->left==v){
                if(g->left==p){
                    v = zig(g);
                    v = zig(v);
                }else{
                    v = zig(p);
                    v = zag(g);
                }

            }else{
                if(g->left==p){
                    v = zag(p);
                    v = zig(g);
                }else{
                    v = zag(g);
                    v = zag(v);
                }
            }
        }
        if((p=v->parent)){
            if(p->left==v){
                v = zig(p);
            }else{
                v = zag(p);
            }
        }
        v->parent = nullptr;
        return v;

    }

    template<typename T>
    splayNode<T> *splayTree<T>::remove(const T& e) {
        if(!_root||(e!=search(e)->val)) return nullptr;
        splayNode<T>* v = _root;
        if(!v->left||!v->right){
            _root = (v->left)?v->left:v->right;
            if(_root) v->parent = nullptr;
        }else{
            splayNode<T>* lt = v->left;
            lt->parent = nullptr;
            v->left = nullptr;
            _root = v->right;
            _root->parent = nullptr;
            search(e);
            _root->left = lt;
            lt->parent = _root;
        }
        delete v;
        v = nullptr;
    }

    template<typename T>
    splayNode<T> *splayTree<T>::insert(const T& e) {
        if(!_root){
            _root = new splayNode<T>(e);
            return _root;
        }
        if(e==search(e)->val)   return _root;
        auto* v = new splayNode<T>(e);
        splayNode<T>* t = _root;
        if(_root->val<e){
            v->right = t->right;
            if(v->right)   v->right->parent = v;
            t->right = nullptr;
            v->left = t;
            t->parent = v;
            _root = v;
        }else{
            v->left = t->left;
            if(v->left) v->left->parent = v;
            t->left = nullptr;
            v->right = t;
            t->parent = v;
            _root = v;
        }
        return _root;
    }

    template<typename T>
    splayNode<T> *splayTree<T>::search(splayNode<T>* &root, T e,splayNode<T>* &parent) {
        if(!root||root->val==e) return root;
        parent = root;
        return search((e<root->val)?root->left:root->right,e,parent);
    }

    template<typename T>
    splayNode<T> *splayTree<T>::search(const T &e) {
        splayNode<T>* parent = nullptr;
        splayNode<T>* p = search(_root,e,parent);
        _root = splay(p?p:parent);
        return _root;
    }


}
#endif //LEARN_ALGORITHMS_SPLAYTREE_H
