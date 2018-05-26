//
// Created by Bas on 23-5-2018.
//

#ifndef BLINKY_USAIN_GPS_H
#define BLINKY_USAIN_GPS_H

#include <mbed.h>
#include "drv_gps.h"




class UsainGPS
{
public:
    UsainGPS();

    ~UsainGPS();

    uint8_t init();

    int get_gps_message(AdafruitUltimateGPS::gprmc_data_t &dest);

    double get_distance_centimeter(AdafruitUltimateGPS::gprmc_data_t &gps_point1, AdafruitUltimateGPS::gprmc_data_t &gps_point2);

    bool data_received();

private:
    void update();

    Thread _update;

    AdafruitUltimateGPS _gps;
};

#endif //BLINKY_USAIN_GPS_H

