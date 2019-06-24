/**
 * Copyright (c) 2019 Feng Cao
 */

#ifndef SINGLE_PIXEL_FILTER_HPP_
#define SINGLE_PIXEL_FILTER_HPP_

// A C++ program for in-place conversion of Binary Tree to DLL
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct point_t {
    int x;
    int y;
    point_t(int _x, int _y) : x(_x), y(_y) {}
} point_s;

// single pixel filter class
class single_pixel_filter {
public:
    single_pixel_filter();
    ~single_pixel_filter() = default;

    /**
     * @brief print map as 2d matrix
     *
     */
    void printMap();

    /**
     * @brief set test map value for selected pixel
     *
     * @param x, y, val
     */
    void setMapPixel(int x, int y, int val) { _map[x][y] = val; }

    /**
     * @brief set test map with input map
     *
     * @param input_map
     */
    void setMap(int **input_map);

    void run() { this->filter(); }

private:
    /**
     * @brief check if given point is single pixel obstacle
     *
     * @param p
     */
    bool check_single_obstacle(const point_s &p);

    /**
     * @brief get euclidean distance between points
     *
     * @param p1,p2
     */
    int inline get_distance(const point_s &p1, const point_s &p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); }

    /**
     * @brief check if givin point is close to known obstacles
     *
     * @param p
     */
    bool close_to_known_obstacle(const point_s &p);

    /**
     * @brief update obstacle data structure cache
     *
     * @param p
     */
    void update_obstacle_map(const point_s &p);

    /**
     * @brief mian filter function
     *
     */
    void filter();

    static constexpr int _map_size                = 256;
    static constexpr int _mask_size               = 41;
    static constexpr int _mask_radius             = _mask_size / 2;
    static constexpr int _near_obstacle_pixel_val = 1;

    int _map[_map_size][_map_size];
    std::vector<point_s> _obstacle_list;
};

#endif /* SINGLE_PIXEL_FILTER_HPP_ */
