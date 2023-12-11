#ifndef safe_common_func
#define safe_common_func
#include "../struct.h"
#include <iostream>
#include <random>


int random(int min, int max);
int get_dist(Xy *coord1, Xy *coord2);

template <typename K, typename V> void free_map(std::map<K, V> *map);
template <typename T> void free_vec(std::vector<T> *vec);


#endif