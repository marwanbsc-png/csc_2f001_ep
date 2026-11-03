#include "shortest_path.h"
#include <iostream>




shortest_path_t::shortest_path_t(location_t* from, location_t* to)
    :origin {from}, destination{to}{
        head = new node_t;
        head->location = origin;
        head->total = origin->distance_to(destination) ;
        head->from_origin = 0;
        head->next = nullptr;
        head->from = nullptr;
        head->visited = false;
    }


shortest_path_t::~shortest_path_t(){
    while(head!=nullptr){
        node_t* next= head->next;
        delete head;
        head=next;
    }
}

void shortest_path_t::compute(){
    

    bool done {false};
    while(not done ){
        base = nullptr;
        double total{1e300};
        node_t* current = head;
        while (current != nullptr){
            if (not current->visited){
                if (current->total < total){
                    base= current;
                    total = current->total;
                }
            }
            current= current->next;
        }
        if (base == nullptr){
            break;
        }
        if (base->location == destination){
            done= true;
            break;
        }

        base->visited= true;

        for (int i=0; i < base->location->nb_neighbors; i++){
            location_t* cur = base->location->neighbors[i];
            double from_origin =  base->from_origin+ cur->distance_to(base->location);
            double total = from_origin + cur->distance_to(destination);


            node_t* current = head;
            while (current->next != nullptr and current->location != cur){
                current= current->next;       
            }

            if (current->next == nullptr and current->location != cur){
                node_t* n= new node_t;
                n->location = cur;
                n->from_origin = from_origin;
                n->total = total;
                n->from = base;
                n->visited = false;
                n->next = head;
                head = n;
            }
            else{
                if (current->from_origin < from_origin){}
                else {
                    current->from= base;
                    current->from_origin = from_origin,
                    current->total = total;
                    current->visited= false;
                }
            }

        }
    }
}

// prints the path that ends at node n, origin first (recursion reverses the from chain)
static void display_from(node_t* n, location_t* origin){
    if (n == nullptr){
        return;
    }
    display_from(n->from, origin);
    std::cout << "  * " << n->location->name << " at " << n->from_origin
              << " km from " << origin->name << std::endl;
}

void shortest_path_t::display(){
    node_t* current = head;
    while (current != nullptr and current->location != destination){
        current = current->next;
    }
    if (current == nullptr){
        std::cout << "unable to find a path from " << origin->name
                  << " to " << destination->name << std::endl;
        return;
    }
    std::cout << "path from " << origin->name << " to " << destination->name << std::endl;
    display_from(current, origin);
}
