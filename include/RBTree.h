
#ifndef LEARN_ALGORITHMS_RBTREE_H
#define LEARN_ALGORITHMS_RBTREE_H
namespace learn_al{
    enum Color {RED,BLACK};
    template<typename T>
    struct RBNode{
        RBNode<T>* parent;
        RBNode<T>* left;
        RBNode<T>* right;
        T val;
        Color color;
        RBNode(const T&e){
            val = e;
            color = RED;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };
    template<typename T>
    class RBTree{
    private:
        RBNode<T>* _root;
        bool isBlack(RBNode<T>* v){
            if(!v||v->color==BLACK)
                return true;
            return false;
        }
        RBNode<T>* getSucc(RBNode<T>* root){
            if(!root)   return root;
            root = root->right;
            while (root->left)
                root = root->left;
            return root;
        }
        RBNode<T>* getPos(RBNode<T>* root){
            if(!root)   return root;
            root = root->left;
            while (root->right)
                root = root->right;
            return root;
        }
        RBNode<T>* zig(RBNode<T>* v);
        RBNode<T>* zag(RBNode<T>* v);
        void solveDoubleRed(RBNode<T>* v);
        void solveDoubleBlack(RBNode<T>* p,RBNode<T> *n);
        RBNode<T>* search(RBNode<T>* &par,const T&e);
    public:
        RBTree(){
            _root = nullptr;
        }
        RBNode<T>* search(const T &e);
        void remove(const T &e);
        void insert(const T &e);

    };

    template<typename T>
    RBNode<T> *RBTree<T>::search(const T &e) {
        RBNode<T>* p = nullptr;
        return search(p,e);
    }

    template<typename T>
    void RBTree<T>::insert(const T &e) {
        RBNode<T>* p = nullptr;
        if(search(p,e)) return;
        if(_root == nullptr){
            auto* t = new RBNode<T>(e);
            t->color = BLACK;
            _root = t;
            return;
        }
        if(e<p->val){
            auto *t = new RBNode<T>(e);
            t->parent = p;
            p->left = t;
            solveDoubleRed(t);
        } else{
            auto *t = new RBNode<T>(e);
            t->parent = p;
            p->right = t;
            solveDoubleRed(t);
        }
    }

    template<typename T>
    void RBTree<T>::remove(const T &e) {
        RBNode<T>* s = search(e);
        if(s== nullptr) return;
        if(s->left&&s->right){
            RBNode<T>* t  = getPos(s);
            s->val = t->val;
            s = t;
        }
        RBNode<T>* p = s->parent;
        if(p== nullptr){
            _root = (s->left)?s->left:s->right;
            if(_root) {
                _root->parent = nullptr;
                _root->color = BLACK;
            }
            return;
        }
        RBNode<T>* n = (s->left)?s->left:s->right;
        if(s->color==RED){
            (p->left==s)?p->left=n:p->right=n;
            if(n)   n->parent = p;
        }else {
            if(n&&n->color == RED){
                n->color = BLACK;
                (p->left==s)?p->left=n:p->right=n;
                n->parent = p;
            }else{
                (p->left == s) ? p->left = n : p->right = n;
                if(n)   n->parent = p;
                solveDoubleBlack(p,n);
            }
        }
    }

    template<typename T>
    void RBTree<T>::solveDoubleBlack(RBNode<T> *p,RBNode<T> *n) {
        if(p== nullptr) return;
        RBNode<T>* tmp = nullptr;
        while (n!=_root&&isBlack(n)){
            RBNode<T>* b = (p->left==n)?p->right:p->left;
            if(p->left==n){
                if (b->color == RED) {
                    b->color = BLACK;
                    p->color = RED;
                    tmp = b->left;
                    zig(p);
                    b = tmp;
                }
                if (isBlack(b->left)&&isBlack(b->right)) {
                    b->color = RED;
                    n = p;
                    p = n->parent;
                    continue;
                }else if(!isBlack(b->left)){
                    b->left->color = BLACK;
                    b->color = RED;
                    tmp = b->left;
                    zag(b);
                    b = tmp;
                }
                if (!isBlack(b->right)){
                    b->color = p->color;
                    p->color = BLACK;
                    b->right->color = BLACK;
                    zig(p);
                    return;
                }
            }else{
                if (b->color == RED) {
                    b->color = BLACK;
                    p->color = RED;
                    tmp = b->right;
                    zag(p);
                    b = tmp;
                }
                if (isBlack(b->left)&&isBlack(b->right)) {
                    b->color = RED;
                    n = p;
                    p = n->parent;
                    continue;
                }else if(!isBlack(b->right)){
                    b->right->color = BLACK;
                    b->color = RED;
                    tmp = b->right;
                    zig(b);
                    b = tmp;
                }
                if(!isBlack(b->left)){
                    b->color = p->color;
                    p->color = BLACK;
                    b->left->color = BLACK;
                    zag(p);
                    return;
                }
            }
        }
        n->color = BLACK;
    }

    template<typename T>
    void RBTree<T>::solveDoubleRed(RBNode<T> *v) {
        if(v==_root){
            _root->color = BLACK;
            return;
        }
        RBNode<T>* p = v->parent;
        if(isBlack(p)) return;
        RBNode<T>* g = p->parent;
        RBNode<T>* u = (g->left==p)?g->right:g->left;
        if(!isBlack(u)){
            g->color = RED;
            p->color = BLACK;
            u->color = BLACK;
        }
        else{
            if(g->left==p) {
                if (p->right == v) {
                    zig(p);
                    p = g->left;
                    v = p->left;
                }
                p->color = BLACK;
                g->color = RED;
                zag(g);
            } else{
                if(p->left==v){
                    zag(p);
                    p = g->right;
                    v = p->right;
                }
                p->color = BLACK;
                g->color = RED;
                zig(g);
            }
        }
        solveDoubleRed(g);
    }

    template<typename T>
    RBNode<T> *RBTree<T>::search(RBNode<T>* &par, const T &e) {
        RBNode<T>* cur = _root;
        while (cur){
            if(e<cur->val){
                par = cur;
                cur = cur->left;
            }else if(e>cur->val){
                par = cur;
                cur = cur ->right;
            } else{
                return cur;
            }
        }
        return cur;
    }

    template<typename T>
    RBNode<T>* RBTree<T>::zag(RBNode<T> *v) {
        RBNode<T>* y = v->left;
        v->left = y->right;
        if(y->right)
            y->right->parent = v;
        y->parent = v->parent;
        if(v==_root){
            _root = y;
        } else
            (v==v->parent->left)?v->parent->left = y
                :v->parent->right = y;
        y->right = v;
        v->parent = y;
        return y;
    }

    template<typename T>
    RBNode<T>* RBTree<T>::zig(RBNode<T> *v) {
        RBNode<T>* y = v->right;
        v->right = y->left;
        if(y->left)
            y->left->parent = v;
        y->parent = v->parent;
        if(v==_root)
            _root = y;
        else
            (v==v->parent->left)?v->parent->left = y:
                v->parent->right = y;
        y->left = v;
        v->parent = y;
        return y;
    }

}
#endif //LEARN_ALGORITHMS_RBTREE_H
