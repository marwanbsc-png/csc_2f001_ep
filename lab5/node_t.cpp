#include "NODE_T.h"
#include <iostream>

void error(std::string str) __attribute__((noreturn));

void error(std::string str) {
    std::cout << "Error: " << str << std::endl;
    exit(1);
}
    
node_t* node_t::apply(list_t* list, frame_t*){
    error("apply error");

}

node_t* node_t::eval(frame_t*){
    return this;
}

std::string node_t::to_string(){
    return "???";
}

list_t* node_t::as_list(){
    error("as list error");
}


integer_t::integer_t( uintptr_t integer)
    : integer {integer} {}


std::string integer_t::to_string() { 
        return std::to_string(integer);
    }
    
list_t::list_t()
    : elements{nullptr}, nb_elements{0}, capacity{0} {}


list_t* list_t::as_list(){
    return this;
}

size_t list_t::size(){
    return nb_elements;
}

node_t* list_t::at(size_t i){
    if (i<nb_elements){
        return elements[i];
    }
    else {
        error("index out of bounds");
    }
}

void list_t::set_at(size_t i, node_t* value){
        if (i<nb_elements){
            elements[i]=value;
    }
    else {
        error("index out of bounds");
    }
}

void list_t::append(node_t* value){
    if (nb_elements == capacity){
        if (capacity == 0){
            node_t** new_list=  new node_t*[1];
            new_list[0] = value;
            elements = new_list;
            capacity=1;
        }
    
        else {
            node_t** new_list=  new node_t*[capacity*2];
            for (size_t i {0}; i<nb_elements; i++ ){
                new_list[i] = elements[i];
            }
            elements = new_list;
            capacity *= 2;
        }
    }
    elements[nb_elements] = value;
    nb_elements += 1;
}

std::string list_t::to_string(){
    std::string s= "(" ;
    for (size_t i {0}; i<nb_elements; i++){
        if (i > 0) s += " ";
        s += elements[i]->to_string();
    }
    s+= ")" ;
    return s;
}

node_t* list_t::eval(frame_t* frame){
    return elements[0]->eval(frame)->apply(this, frame);
}


uintptr_t  node_t::int_value(){
    error("not an integer");
}


uintptr_t  integer_t::int_value(){
    return integer;
}

node_t* add_t::apply(list_t* list, frame_t* frame){
    uintptr_t sum {0};
    for (size_t i {1}; i<list->nb_elements; i++){
        sum += list->at(i)->eval(frame)->int_value();
    }
    node_t* s = new integer_t {sum};
    return s ;
}

bool symbol_t::is(std::string id){
    if (this->id == id){
        return true;
    }
    else {
        return false;
    }
}

symbol_t::symbol_t(std::string id)
    : id {id} {}


void frame_t::set(node_t* sym, node_t* value){
    bool found {false};
    for (size_t i {0}; i<nb_elements; i++){
        if (sym->is(at(i)->as_list()->at(0)->to_string())){
            elements[i]->as_list()->set_at(1, value);
            found = true;
            break;
        }
    }
    if (not found ){
        node_t* frame = new list_t {};
        frame->as_list()->append(sym);
        frame->as_list()->append(value);
        append(frame);
    }
}

node_t* frame_t::get(node_t* sym){
    for (size_t i {0}; i<nb_elements; i++){
        if (sym->is(at(i)->as_list()->at(0)->to_string()))
            return elements[i]->as_list()->at(1);
        }
        error("symbol not found");
}

node_t* symbol_t::eval(frame_t* frame){
    return frame->get(this);
}


node_t* set_t::apply(list_t* list, frame_t* frame){
    node_t* value { list->at(2)->eval(frame)};
    frame->set(list->at(1), value);
    return value;
}
