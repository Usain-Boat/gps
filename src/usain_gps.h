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

    ~UsainGPS() {};

    uint8_t init();

    int get_gps_message(AdafruitUltimateGPS::gprmc_data_t &dest);

    void get_average_gps(double *latitude, double *longitude);

    void calculate_distance(double dest_latitude, double dest_longitude, double *distance_cm,
                            double *bearing_degrees);

    void on_new_message(const Callback<void()> &callback)
    {
        _collision_callback = callback;
        callback_registered = true;
    }


    bool data_received();

private:
    bool callback_registered;

    Callback<void()>  _collision_callback;

    void update();

    Thread _update;

    AdafruitUltimateGPS _gps;


};

#endif //BLINKY_USAIN_GPS_H

