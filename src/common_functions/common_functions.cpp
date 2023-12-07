#include "common_functions.h"



template <typename K, typename V>
void free_map(std::map<K, V> map){
    for(auto el: map){
        delete map[el.first];
    }
}

template <typename T>
void free_vec(std::vector<T> vec){
    for(unsigned int i=0; i<vec.size(); i++){
        delete vec[i];
    }
}


int random(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> random_nbr(min, max);
    return(random_nbr(generator));
}


int get_dist(Xy *coord1, Xy *coord2){
    return (coord1->x-coord2->x)*(coord1->x-coord2->x) + (coord1->y-coord2->y)*(coord1->y-coord2->y);
}
