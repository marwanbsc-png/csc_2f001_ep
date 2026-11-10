#ifndef NODE_T
#define NODE_T
#include <string>

struct list_t ;

struct symbol_t;

struct frame_t;

struct node_t{
    virtual node_t* eval(frame_t*);
    virtual node_t* apply(list_t* list, frame_t* frame);
    virtual std::string to_string();
    virtual list_t* as_list();
    virtual uintptr_t int_value();
    virtual bool is(std::string id) {return false;};

};

struct integer_t : node_t {
    uintptr_t integer;
    integer_t( uintptr_t integer);
    std::string to_string();
    uintptr_t int_value();
};
 
struct list_t : node_t {
    node_t** elements;
    size_t nb_elements;
    size_t capacity;
    list_t();
    list_t* as_list();
    size_t size();
    node_t* at(size_t i);
    void set_at(size_t i, node_t* value);
    void append(node_t* value);
    std::string to_string();
    node_t* eval(frame_t*);
};

struct keyword_t : node_t{
    std::string id;
    keyword_t(std::string id): id {id} {};
    std::string to_string(){ return "<"+ id +">" ;} ;
};

struct add_t : keyword_t {
    add_t () : keyword_t("+") {};
    node_t* apply(list_t* list, frame_t* frame);

};

struct symbol_t : node_t {
    std::string id;
    symbol_t(std::string id);
    bool is(std::string id);
    std::string to_string(){return id;};
    node_t* eval(frame_t *frame);
};

struct frame_t : list_t {
    void set(node_t* sym, node_t* value);
    node_t* get(node_t* sym);
};

struct set_t : keyword_t {
    set_t() : keyword_t{"set!"} {}
    node_t* apply( list_t* list, frame_t* frame);
};


#endif