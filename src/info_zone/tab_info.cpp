#include "tab_info.h"
#include "../Game.h"

TabInfo::TabInfo(Game *game, Xy dim, Xy pos, Xy case_size, std::string name){
    this->name = name;
    this->game = game;
    this->dim = dim;
    this->pos = pos;
    this->case_size = case_size;

    tab_info.resize(dim.x);
    for(int i = 0; i < dim.x; i++){
        for(int j=0; j<dim.y; j++){
            tab_info[i].push_back(new InfoZone(game, {pos.x + i*case_size.x, pos.y+j*case_size.y}, case_size, "", game->get_color("reverse_info_color"), RECT, "random_case"));
        }
    }
}

TabInfo::~TabInfo(){
    for(int i = 0; i < dim.x; i++){
        for(int j=0; j<dim.y; j++){
            delete tab_info[i][j];
        }
    }
}

void TabInfo::set_base_text(Xy coord, QString new_txt){
    tab_info[coord.x][coord.y]->set_base_text(new_txt);
}

void TabInfo::set_text_size(Xy coord, int x){
    tab_info[coord.x][coord.y]->set_txt_size(x);   
}

void TabInfo::decal_txt(Xy coord, Xy decal){
    tab_info[coord.x][coord.y]->decal_txt(decal);
}

std::string TabInfo::get_name(){
    return this->name;
}

void TabInfo::set_color(Xy coord, QColor color){
    tab_info[coord.x][coord.y]->set_color(color);
}

void TabInfo::set_value(Xy coord, float value){
    tab_info[coord.x][coord.y]->set_value(value);
}

float TabInfo::get_value(Xy coord){
    return tab_info[coord.x][coord.y]->get_value();
}

Xy TabInfo::get_pos(){
    return pos;
}

void TabInfo::add(){
    for(int i = 0; i < dim.x; i++){
        for(int j=0; j<dim.y; j++){
            tab_info[i][j]->add();
        }
    }
}
void TabInfo::remove(){
    for(int i = 0; i < dim.x; i++){
        for(int j=0; j<dim.y; j++){
            tab_info[i][j]->remove();
        }
    }
}

void TabInfo::set_pos(Xy pos){
    this->pos = pos;
    for(int i = 0; i < dim.x; i++){
        for(int j=0; j<dim.y; j++){
            tab_info[i][j]->set_pos(pos);
        }
    }
}