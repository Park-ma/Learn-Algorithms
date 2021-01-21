#ifndef LEARN_ALGORITHMS_SKIPLIST_H
#define LEARN_ALGORITHMS_SKIPLIST_H
#include <vector>
#include <random>
#define DEFAULT_LEVEL 32
#define P 0.5

namespace learn_al{
    using std::vector;
    template<typename K>
    struct skipNode{
        K key;
        vector<skipNode<K>*> forward;
        skipNode(K _key,int level = DEFAULT_LEVEL){
            key = _key;
            forward.resize(level);
        }
    };
    template<typename K>
    class skipList{
    private:
        skipNode<K>* header;
        int level;
    private:
        int random_level(){
            int res = 1;
            std::random_device rd;
            std::default_random_engine e1(rd());
            std::uniform_real_distribution<float> un_dis(0.0,1.0);
            while (un_dis(e1)<P&&res<DEFAULT_LEVEL){
                res++;
            }
            return res;
        }
        vector<skipNode<K>*> _search(K key){
            skipNode<K>* node = header;
            vector<skipNode<K>*> prevs(DEFAULT_LEVEL);
            for(int i=level-1;i>=0;i--) {
                while (node->forward[i] && node->forward[i]->key < key) {
                    node = node->forward[i];
                }
                prevs[i] = node;
            }
            return prevs;
        }
    public:
        skipList(){
            header = new skipNode<K>(INT16_MIN,DEFAULT_LEVEL);
            level = 0;
        }
        ~skipList(){
            skipNode<K>* cur = header;
            skipNode<K>* next = nullptr;
            while (cur){
                next = cur->forward[0];
                delete cur;
                cur = next;
            }
            header = nullptr;
        }
        bool search(K key){
            skipNode<K>* node = _search(key)[0];
            if(node->forward[0]&&node->forward[0]->key==key){
                return true;
            }
            return false;
        }
        bool insert(K key){
            auto prevs = _search(key);
            skipNode<K>* node = prevs[0];
            if(node == nullptr||node->forward[0]== nullptr||node->forward[0]->key!=key) {
                int new_level = random_level();
                if (new_level > level) {
                    for (int i = level; i < new_level; i++) {
                        prevs[i] = header;
                    }
                    level = new_level;
                }
                skipNode<K> *new_node = new skipNode<K>(key, new_level);
                for (int i = 0; i < new_level; i++) {
                    new_node->forward[i] = prevs[i]->forward[i];
                    prevs[i]->forward[i] = new_node;
                }
                return true;
            }
            return false;
        }
        bool remove(K key){
            auto prevs = _search(key);
            skipNode<K>* node = prevs[0];
            if(node->forward[0]&&node->forward[0]->key==key){
                skipNode<K>* del = node->forward[0];
                for(int i=0;i<level;i++){
                    if(prevs[i]->forward[i]==del){
                        prevs[i]->forward[i] = del->forward[i];
                    }
                }
                delete del;
                del = nullptr;
                while (level>1&&header->forward[level-1]== nullptr){
                    level--;
                }
                return true;
            }
            return false;
        }
    };
}
#endif //LEARN_ALGORITHMS_SKIPLIST_H
