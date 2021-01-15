

#ifndef LEARN_ALGORITHMS_BTREE_H
#define LEARN_ALGORITHMS_BTREE_H
#include <vector>
namespace learn_al{
    using std::vector;
    template<typename T>
    struct BTNode{
        BTNode<T>* parent;
        vector<T> key;
        vector<BTNode<T>*> child;
        BTNode(){
            parent = nullptr;
            child.insert(child.begin(), nullptr);
        }
        BTNode(const T& e,BTNode<T>* left = nullptr,BTNode<T>* right = nullptr){
            parent = nullptr;
            key.insert(key.begin(),e);
            child.insert(child.begin(),left);
            child.insert(child.begin()+1,right);
            if(left){    left->parent = this;}
            if(right){   right->parent = this;}
        }
    };
    template<typename T>class BTree{
    private:
        int _order;
        BTNode<T>* _root;
        BTNode<T>* _par;
        int searchIn(const T& e,BTNode<T>* v);
        void Overflow(BTNode<T>* v);
        void Underflow(BTNode<T>* v);

    public:
        BTree(int order){
            _order = order;
            _root = new BTNode<T>();
        }
        int const order(){
            return _order;
        }
        bool empty() const{
            return (!_root);
        }
        BTNode<T>* search(const T&e);
        bool insert(const T& e);
        bool remove(const T& e);
    };

    template<typename T>
    void BTree<T>::Overflow(BTNode<T> *v) {
        if(v->child.size()<=_order) return;
        int m = _order/2;
        BTNode<T>* rc = new BTNode<T>();
        rc->key.insert(rc->key.end(),v->key.begin()+m+1,v->key.end());
        v->key.erase(v->key.begin()+m+1,v->key.end());
        rc->child.erase(rc->child.begin(),rc->child.end());
        rc->child.insert(rc->child.end(),v->child.begin()+m+1,v->child.end());
        v->child.erase(v->child.begin()+m+1,v->child.end());
        if(rc->child[0]!= nullptr){
            for(int i=0;i<rc->child.size();i++)
                rc->child[i]->parent = rc;
        }
        BTNode<T>* p = v->parent;
        if(p== nullptr){
            p = new BTNode<T>();
            p->child[0] = v;
            v->parent = p;
            _root = p;
        }
        int r = searchIn(v->key[0],p);
        p->key.insert(p->key.begin()+r,v->key[m]);
        v->key.erase(v->key.begin()+m);
        p->child.insert(p->child.begin()+r+1,rc);
        rc->parent = p;
        Overflow(p);
    }

    template<typename T>
    void BTree<T>::Underflow(BTNode<T> *v) {
        if(v->child.size()>=(_order+1)/2) return;
        BTNode<T>* p = v->parent;
        if(!p){
            if(!v->key.size()&&v->child[0]){
                _root = v->child[0];
                _root->parent = nullptr;
                v->child[0] = nullptr;
            }
            return;
        }
        int r = 0;
        while (p->child[r]!=v)  r++;
        if(r>0){
            BTNode<T>* lb = p->child[r-1];
            if(lb->child.size()>(_order+1)/2){
                v->key.insert(v->key.begin(),p->key[r-1]);
                p->key[r-1] = lb->key[lb->key.size()-1];
                lb->key.erase(lb->key.end()-1);
                v->child.insert(v->child.begin(),lb->child[lb->child.size()-1]);
                lb->child.erase(lb->child.end()-1);
                if(v->child[0]) v->child[0]->parent = v;
                return;
            }
        }
        if(r<p->child.size()-1){
            BTNode<T>* rb = p->child[r+1];
            if(rb->child.size()>(_order+1)/2){
                v->key.insert(v->key.end(),p->key[r]);
                p->key[r] = rb->key[0];
                rb->key.erase(rb->key.begin());
                v->child.insert(v->child.end(),rb->child[0]);
                rb->child.erase(rb->child.begin());
                if(v->child[v->child.size()-1])
                    v->child[v->child.size()-1]->parent = v;
                return;
            }
        }
        if(r>0){
            BTNode<T>* lb = p->child[r-1];
            lb->key.insert(lb->key.end(),p->key[r-1]);
            p->key.erase(p->key.begin()+r-1);
            p->child.erase(p->child.begin()+r);
            lb->key.insert(lb->key.end(),v->key.begin(),v->key.end());
            lb->child.insert(lb->child.end(),v->child.begin(),v->child.end());
            for(int i=0;i<lb->child.size();i++){
                if(lb->child[i]) lb->child[i]->parent = lb;
            }
        } else{
            BTNode<T>* rb = p->child[r+1];
            rb->key.insert(rb->key.begin(),p->key[r]);
            p->key.erase(p->key.begin()+r);
            p->child.erase(p->child.begin()+r);
            rb->key.insert(rb->key.begin(),v->key.begin(),v->key.end());
            rb->child.insert(rb->child.begin(),v->child.begin(),v->child.end());
            for(int i=0;i<rb->child.size();i++)
                if(rb->child[i])    rb->child[i]->parent = rb;
        }
        Underflow(p);
        return;
    }
    template<typename T>
    bool BTree<T>::remove(const T &e) {
        BTNode<T>* v = search(e);
        if(!v) return false;
        int r = searchIn(e,v);
        if(v->child[0] != nullptr){
            BTNode<T>* u = v->child[r+1];
            while (u->child[0]){
                u = u->child[0];
            }
            v->key[r] = u->key[0];
            v = u;
            r = 0;
        }
        v->key.erase(v->key.begin()+r);
        v->child.erase(v->child.begin()+r+1);
        Underflow(v);
        return true;
    }

    template<typename T>
    bool BTree<T>::insert(const T &e) {
        BTNode<T>* v = search(e);
        if(v) return false;
        int r = searchIn(e,_par);
        _par->key.insert(_par->key.begin()+r,e);
        _par->child.insert(_par->child.begin()+r+1, nullptr);
        Overflow(_par);
        return true;
    }

    template<typename T>
    int BTree<T>::searchIn(const T &e, BTNode<T> *v) {
        int size = v->key.size();
        int i = 0;
        while(i<size){
            if(e>v->key[i])
                i++;
            else
                break;
        }
        return i;
    }
    template<typename T>
    BTNode<T> *BTree<T>::search(const T &e) {
        BTNode<T>* v = _root;
        _par = nullptr;
        while (v){
            int r = searchIn(e,v);
            if((r>=0&&r<v->key.size())&&e==v->key[r])
                return v;
            _par = v;
            v = v->child[r];
        }
        return nullptr;
    }
}

#endif //LEARN_ALGORITHMS_BTREE_H
