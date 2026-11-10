#include "NODE_T.h"
#include <iostream>


int main(int argc, char* argv[]){
    node_t* add = new add_t;
    symbol_t* a = new symbol_t { "a" };
    frame_t* frame = new frame_t;

    frame->set(a, new integer_t { 37 });

    list_t* ast = new list_t;

    ast->append(add);
    ast->append(new list_t);
    ast->at(1)->as_list()->append(add);
    ast->at(1)->as_list()->append(a);
    ast->at(1)->as_list()->append(new integer_t { 2 });
    ast->append(new integer_t { 3 });

    std::cout << ast->to_string() << " => " << ast->eval(frame)->to_string() << std::endl;

}