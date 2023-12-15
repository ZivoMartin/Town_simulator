#include "common_functions.h"

template <typename K, typename V>
void free_map(std::map<K, V> *map){
    std::vector<K> s;
    for(auto el: (*map)){
        delete (*map)[el.first];
        s.push_back(el.first);
    }
    for(unsigned int i = 0; i<s.size(); i++){
        map->erase(s[i]);
    }
}

template <typename T>
void free_vec(std::vector<T> *vec){
    while(vec->size() != 0){
        delete (*vec)[0];  
        vec->erase(vec->begin());
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
