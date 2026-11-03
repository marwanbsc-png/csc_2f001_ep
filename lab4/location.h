#ifndef LOCATION_H
#define LOCATION_H
#include <string>


struct location_t {
    std::string name;
    double latitude;
    double longitude;
    location_t** neighbors;
    int nb_neighbors;
    location_t(std::string name, double latitude, double longitude);
    void set_neighbors(location_t* list[]);
    ~location_t();
    double distance_to(location_t* to);
};

#endif
