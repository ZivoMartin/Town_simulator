#include "settings.h"
#include "../Game.h"

Setting::Setting(Game *game, Xy pos, Xy size, Setting *reverse) : QGraphicsRectItem(0, 0, size.x, size.y){
    this->game = game;
    this->pos = pos;
    this->scene = game->get_view()->get_scene(); 
    this->size = size;
    this->close_button = new PushButton(game, pos, *(game->get_img_size("close_button")), &Game::close_current_setting, "closing", game->get_img("close_button"));    
    this->brush = new QBrush(game->get_color("settings"));
    setBrush(*brush);
    this->setPos(pos.x, pos.y);
    if(reverse == nullptr){
        this->reverse_setting = new Setting(this->game, pos, size, this);
    }else{
        set_reverse_button();
        this->reverse_setting = reverse; 
    }
    
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
    if(have_to_delete_reverse){
        reverse_setting->switch_have_to_delete_reverse();
        delete reverse_setting;
    }
}

void Setting::set_color(QColor new_color){
    brush->setColor(new_color);
    this->setBrush(*brush);
}

void Setting::switch_have_to_delete_reverse(){
    have_to_delete_reverse = false;
}

Setting *Setting::reverse(){
    this->close();
    reverse_setting->open();
    return reverse_setting;
}

void Setting::set_reverse_button(){
    reverse_button = new PushButton(game, {pos.x + size.x - 30, pos.y}, *game->get_img_size("info"), &Game::reverse_current_setting, "reverse_button", game->get_img("info"));
    if(is_open){
        reverse_button->add();
    }
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
    for(auto el: tab_info_map){
        tab_info_map[el.first]->remove();
    }
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        static_img_vec[i]->remove_img();
    }
    if(reverse_button != nullptr){
        reverse_button->remove();
    }
    is_open = false;
}

void Setting::open(){
    this->scene->addItem(this);
    close_button->add();
    for(auto el: button_map){
        button_map[el.first]->add();
    }
    for(auto el: infozone_map){
        infozone_map[el.first]->add();
    }
    for(auto el: tab_info_map){
        tab_info_map[el.first]->add();
    }
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        static_img_vec[i]->add_img();
    }
    if(reverse_button != nullptr){
        reverse_button->add();
    }
    is_open = true;
}

void Setting::set_pos(Xy pos){
    if(pos.x != this->pos.x || pos.y != this->pos.y){
        close_button->set_pos(pos);
        for(auto el: button_map){
            Xy w_pos = button_map[el.first]->get_pos();
            button_map[el.first]->set_pos({pos.x+(w_pos.x - this->pos.x), pos.y+(w_pos.y - this->pos.y)});
        }
        for(auto el: infozone_map){
            Xy w_pos = infozone_map[el.first]->get_pos();
            infozone_map[el.first]->set_pos({pos.x+(w_pos.x - this->pos.x), pos.y+(w_pos.y - this->pos.y)});
        }
        for(auto el: tab_info_map){
            Xy w_pos = tab_info_map[el.first]->get_pos();
            tab_info_map[el.first]->set_pos({pos.x+(w_pos.x - this->pos.x), pos.y+(w_pos.y - this->pos.y)});
        }
        for(unsigned int i=0; i<static_img_vec.size(); i++){
            Xy *w_pos = static_img_vec[i]->get_pos();
            static_img_vec[i]->set_pos_img({pos.x+(w_pos->x - this->pos.x), pos.y+(w_pos->y - this->pos.y)});
        }
        if(reverse_button != nullptr){
            Xy w_pos = reverse_button->get_pos();
            reverse_button->set_pos({pos.x+(w_pos.x - this->pos.x), pos.y+(w_pos.y - this->pos.y)});
        }
        setPos(pos.x, pos.y);
        this->pos = pos;
        reverse_setting->set_pos(pos);
    }
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

void Setting::add_tab_info(TabInfo *new_tab){
    tab_info_map[new_tab->get_name()] = new_tab;
}

TabInfo *Setting::get_tab_info(std::string name){
    return tab_info_map[name];
}

void Setting::erase_img(GraphicsPixmapItem *img){
    for(unsigned int i=0; i<static_img_vec.size(); i++){
        if(static_img_vec[i] == img){
            static_img_vec.erase(static_img_vec.begin()+i);
            break;
        }
    }
}

Xy Setting::get_pos(){
    return pos;
}

Setting *Setting::get_reverse(){
    return reverse_setting;
}   

bool Setting::get_is_open(){
    return is_open;
}

bool Setting::is_it(Xy *coord){
    return coord->x < pos.x+size.x && coord->x > pos.x && coord->y < pos.y+size.y && coord->y > pos.y;
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

