#ifndef TREEMAP_H
#define TREEMAP_H
#include <iostream>

template <class K, class V>
struct treemap_t{
    struct pair_t{
        K key;
        V value;
    };

    struct node_t : treemap_t::pair_t {
    node_t* parent;
    node_t* left;
    node_t* right;
    node_t(node_t* parent);
    };

    node_t* root;
    treemap_t();

    node_t* lookup(node_t** pcur, node_t* parent, const K* key, bool create);
    void set_at(const K key, const V value);
    V at(const K key);
    void display();
    void display(node_t* cur, std::string prefix);


    struct iterator_t{
        node_t* cur;
        iterator_t(node_t* root);
        void next();

    };

    iterator_t begin();
};



template <class K, class V>
treemap_t<K, V>::node_t::node_t(treemap_t<K, V>::node_t* parent)
    : parent {parent}, left{nullptr}, right{nullptr} {
}

template <class K, class V>
treemap_t<K, V>::treemap_t()
    : root {nullptr}{
}

template <class K, class V>
typename treemap_t<K, V>::node_t* treemap_t<K, V>::lookup(node_t** pcur, node_t* parent, const K* key, bool create){
    
    while (*pcur != nullptr and (*pcur)->key != *key){
        if (*key < (*pcur)->key ){
            parent = *pcur;
            pcur = &((*pcur)->left);
        }
        else if (*key > (*pcur)->key ) {
            parent = *pcur;
            pcur = &((*pcur)->right);
        }
    }

    if (create == false){
        if (*pcur == nullptr){
            return nullptr;
        }
    }
    else if (create == true){
        if (*pcur == nullptr){
            *pcur = new node_t { parent };
            (*pcur)->key = *key;
            return *pcur;
        }
    }

    return *pcur;
}

template <class K, class V>
void treemap_t<K, V>::set_at(const K key, const V value){
    node_t* node = lookup(&root, nullptr, &key, true);
    node->value = value;
}

template <class K, class V>
V treemap_t<K, V>::at(const K key){
    node_t* node = lookup(&root, nullptr, &key, false);
    if (node){
        return node->value;
    }
    std::cout << "Key " << key << "does not exist";
    std::exit(EXIT_FAILURE); 
}

template <class K, class V>
void treemap_t<K, V>::display(){
    display(root, "");
}

template <class K, class V>
void treemap_t<K, V>::display(node_t* cur, std::string prefix){
    if(cur != nullptr){
        display(cur->left, prefix+"  ");
        std::cout << prefix << "(" << cur->key << ", " << cur->value << ")"<< "\n";
        display(cur->right, prefix+"  ");
    }
}


template <class K, class V>
treemap_t<K, V>::iterator_t::iterator_t(node_t* root){
    node_t* smallest= root;
    while (smallest != nullptr and smallest->left !=nullptr){
        smallest = smallest->left;
    }
    cur =smallest; 
}


template <class K, class V>
void treemap_t<K, V>::iterator_t::next() {
    if (cur->right != nullptr){
        cur= cur->right;
        while(cur->left != nullptr){
            cur = cur->left;
        }
    }
    else {
        while( cur->parent!=nullptr and cur == cur->parent->right){
            cur = cur->parent;
        }
        cur = cur->parent;
    }
}



template <class K, class V>
treemap_t<K, V>::iterator_t treemap_t<K, V>::begin(){
    return iterator_t( root);
}



#endif