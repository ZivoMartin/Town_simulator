#include "settings.h"
#include "../Game.h"

Setting::Setting(Game *game, Xy pos, Xy size) : QGraphicsRectItem(0, 0, size.x, size.y){
    this->game = game;
    this->pos = pos;
    this->scene = game->get_view()->get_scene(); 
    this->size = size;
    this->close_button = new PushButton(game, pos, *(game->get_img_size("close_button")), &Game::close_current_setting, "closing", game->get_img("close_button"));    
    this->brush = new QBrush(game->get_color("settings"));
    setBrush(*brush);
    this->setPos(pos.x, pos.y);
}

Setting::~Setting(){
    if(is_open){
        close();
    }
    delete brush;
    delete close_button;
    free_map(&button_map);
    free_map(&infozone_map);
    free_vec(&static_img_vec);
}

void Setting::close(){
    scene->removeItem(this);
    close_button->remove();
    for(auto el: button_map){
        button_map[el.first]->remove();
    }
    for(auto el: infozone_map){
        infozone_map[el.first]->remove();
    }
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        static_img_vec[i]->remove_img();
    }
    is_open = false;
}

void Setting::open(){
    scene->addItem(this);
    close_button->add();
    for(auto el: button_map){
        button_map[el.first]->add();
    }
    for(auto el: infozone_map){
        infozone_map[el.first]->add();
    }
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        static_img_vec[i]->add_img();
    }
    is_open = true;
}

void Setting::set_pos(Xy pos){
    close_button->set_pos(pos);
    for(auto el: button_map){
        Xy w_pos = button_map[el.first]->get_pos();
        button_map[el.first]->set_pos({pos.x+(w_pos.x - this->pos.x), pos.y+(w_pos.y - this->pos.y)});
    }
    for(auto el: infozone_map){
        Xy w_pos = infozone_map[el.first]->get_pos();
        infozone_map[el.first]->set_pos({pos.x+(w_pos.x - this->pos.x), pos.y+(w_pos.y - this->pos.y)});
    }
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        Xy *w_pos = static_img_vec[i]->get_pos();
        static_img_vec[i]->set_pos_img({pos.x+(w_pos->x - this->pos.x), pos.y+(w_pos->y - this->pos.y)});
    }
    setPos(pos.x, pos.y);
    this->pos = pos;
}

void Setting::add_button(PushButton *new_button){
    button_map[new_button->get_name()] = new_button;
}

void Setting::erase_button(std::string name){
    button_map.erase(name);
}

void Setting::add_info_zone(InfoZone *new_zone){
    infozone_map[new_zone->get_name()] = new_zone;
}

void Setting::erase_info_zone(std::string name){
    infozone_map.erase(name);
}

InfoZone *Setting::get_info_zone(std::string name){
    return Setting::infozone_map[name];
}

PushButton *Setting::get_button(std::string name){
    return button_map[name];
}

void Setting::add_img(GraphicsPixmapItem *new_img){
    static_img_vec.push_back(new_img);
}

void Setting::erase_img(GraphicsPixmapItem *img){
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        if(static_img_vec[i] == img){
            static_img_vec.erase(static_img_vec.begin()+i);
            break;
        }
    }
}

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

bool Setting::get_is_open(){
    return is_open;
}