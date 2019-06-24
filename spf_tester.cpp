/**
 * Copyright (c) 2019 Feng Cao
 */

#include "single_pixel_filter.hpp"

//#define PRINT_MAP

/* main program to test spf class functions*/
int main() {
    single_pixel_filter spf;

    // alternative way to setup test map is to use setMap function to copy an input map
    spf.setMapPixel(6, 6, 255);
    spf.setMapPixel(7, 7, 255);
    spf.setMapPixel(17, 12, 127);
    spf.setMapPixel(15, 17, 127);
    spf.setMapPixel(17, 17, 255);

#ifdef PRINT_MAP
    spf.printMap();
#endif

    auto start = std::chrono::high_resolution_clock::now();
    spf.run();
    auto end                              = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

#ifdef PRINT_MAP
    spf.printMap();
#endif

    return 0;
}
