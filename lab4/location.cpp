#include "location.h"
#include <iostream>
#include <numbers>
#include <cmath>


location_t::location_t (std::string name, double latitude, double longitude)
    :name {name}, latitude {latitude}, longitude {longitude}{
}

void location_t::set_neighbors(location_t* list[]){
    int i{0};
    while (list[i]!= nullptr){
        i+=1;
    }
    neighbors =  new location_t*[i];
    for(int j =0; j<i; j++){
        neighbors[j] = list[j];
    }
    nb_neighbors = i;


}

location_t::~location_t (){
    delete[] neighbors;
}

double location_t::distance_to(location_t* to){
    double lat1{latitude};
    double long1{longitude};
    double lat2{to->latitude};
    double long2(to->longitude);
    return 6378 * (std::numbers::pi/2 - std::asin(std::sin(lat2) * std::sin(lat1) + std::cos(long2 - long1) * std::cos(lat2) * std::cos(lat1)));
}

