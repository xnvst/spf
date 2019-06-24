/**
 * Copyright (c) 2019 Feng Cao
 */

#include "single_pixel_filter.hpp"

single_pixel_filter::single_pixel_filter() {
    for(int x = 0; x < _map_size; x++) {
        for(int y = 0; y < _map_size; y++) { _map[x][y] = 0; }
    }
    _obstacle_list.clear();
}

void single_pixel_filter::printMap() {
    std::cout << std::endl << "--------------map------------------" << std::endl;
    for(int x = 0; x < _map_size; x++) {
        for(int y = 0; y < _map_size; y++) {
            switch(_map[x][y]) {
            case 0:
                std::cout << 0 << " ";
                break;
            case 127:
                std::cout << 1 << " ";
                break;
            case 255:
                std::cout << 2 << " ";
                break;
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
}

void single_pixel_filter::setMap(int **input_map) {
    if(input_map == NULL) { return; }
    for(int x = 0; x < _map_size; x++) {
        for(int y = 0; y < _map_size; y++) { _map[x][y] = input_map[x][y]; }
    }
}

bool single_pixel_filter::check_single_obstacle(const point_s &p) {
    // no in the center of mask
    if(p.x - _mask_radius < 0) {
        return false;
    } else if(p.x + _mask_radius > _map_size - 1) {
        return false;
    } else if(p.y - _mask_radius < 0) {
        return false;
    } else if(p.y + _mask_radius > _map_size - 1) {
        return false;
    }
    for(int x = p.x + _mask_radius; x >= p.x - _mask_radius; x--) {
        for(int y = p.y + _mask_radius; y >= p.y - _mask_radius; y--) {
            if(x == p.x && y == p.y) { continue; }
            if(_map[x][y] != 0) {
                if(_map[x][y] == 255) { update_obstacle_map(point_s(x, y)); }
                return false;
            }
        }
    }
    return true;
}

bool single_pixel_filter::close_to_known_obstacle(const point_s &p) {
    for(int i = 0; i < _obstacle_list.size(); i++) {
        if(get_distance(_obstacle_list[i], p) <= _mask_radius) { return true; }
    }
    return false;
}

void single_pixel_filter::update_obstacle_map(const point_s &p) { _obstacle_list.push_back(p); }

void single_pixel_filter::filter() {
    for(int x = 0; x < _map_size; x++) {
        for(int y = 0; y < _map_size; y++) {
            if(_map[x][y] == 255) {
                point_s obstacle = point_s(x, y);
                if(close_to_known_obstacle(obstacle)) {
                    update_obstacle_map(obstacle);
                } else {
                    if(check_single_obstacle(obstacle)) {
                        _map[x][y] = 0;
                    } else {
                        update_obstacle_map(obstacle);
                    }
                }
                y += _mask_radius + 1;
            }
        }
    }
}
