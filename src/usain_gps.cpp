//
// Created by Bas on 23-5-2018.
//

#include "usain_gps.h"
#include "drv_gps.h"

#define pi 3.14159265358979323846

double deg2rad(double deg);

double rad2deg(double rad);

UsainGPS::UsainGPS() {}

UsainGPS::~UsainGPS() {

}

uint8_t UsainGPS::init() {
    uint8_t return_value = 0;
    int status;
    status = _gps.coldstart();
    if (status)
    {
        return_value |= 0x01;
    }


    while (_gps.setbaudrateto115200());
    Timer delaytje;
    delaytje.reset();
    delaytje.start();
    while (delaytje.read() < 1);
    while(_gps.setupdaterate((char *) "100"));
    if (status)
    {
        return_value |= 0x02;
    }
    status = _gps.onlyreceivegprmcdata();
    if (status)
    {
        return_value |= 0x04;
    }

//    Timer timer;
//    timer.reset();
//    timer.start();
//    AdafruitUltimateGPS::gprmc_data_t gps_data_check;
//    while (timer.read() < (60 * 5))// wait 5 minutes on valid message
//    {
//        _gps.parsedata();
//        if (_gps.ReceievedNewGPRMC())
//        {
//            _gps.ReceievedNewGPRMC(false);
//            _gps.GetLastGprmcData(&gps_data_check);
//            if (*gps_data_check.validity == 'A')
//            {
    if (_update.start(callback(this, &UsainGPS::update)) == osOK)
    {
    };
//                return return_value;
//            }
//        }
//    }
    return return_value;
}

int UsainGPS::get_gps_message(AdafruitUltimateGPS::gprmc_data_t &dest) {
    _gps.GetLastGprmcData(&dest);
    if (!_gps.ReceievedNewGPRMC())
    {
        return -1;
    }
    _gps.ReceievedNewGPRMC(false);
//    if (*dest.validity == 'V')
//    {
//        return -2; // data not valid
//    }
    return 0;
}

//haversine method
void UsainGPS::get_distance_centimeter(AdafruitUltimateGPS::gprmc_data_t &home_position,
                                        AdafruitUltimateGPS::gprmc_data_t &destination_position, double *distance_cm, double *bearing_degrees) {
    const double R = 6371e3;
    double home_latitude = deg2rad(home_position.latitude_fixed);
    double dest_latitude = deg2rad(destination_position.latitude_fixed);
    double differenceLat = deg2rad(destination_position.latitude_fixed - home_position.latitude_fixed);//(lat2-lat1).toRadians();
    double differenceLon = deg2rad(destination_position.longitude_fixed - home_position.longitude_fixed);//(lon2-lon1).toRadians();

    double a = sin(differenceLat/2) * sin(differenceLat/2) +
            cos(home_latitude) * cos(dest_latitude) *
            sin(differenceLon/2) * sin(differenceLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));





    double rad_bearing = atan2(sin(differenceLon) * cos(dest_latitude),
                              cos(home_latitude) * sin(dest_latitude)
                              - sin(home_latitude) * cos(dest_latitude) * cos(differenceLon));

    *distance_cm = R * c;
    *bearing_degrees = (rad2deg(rad_bearing) - 90) < 0 ? (rad2deg(rad_bearing) - 90) + 360: (rad2deg(rad_bearing) - 90);
}


bool UsainGPS::data_received() {
    return _gps.ReceievedNewGPRMC();
}

void UsainGPS::update() {
    while (1)
    {
        _gps.parsedata();
    }
}


double deg2rad(double deg) {

    return (deg * pi / 180);

}

double rad2deg(double rad) {

    return (rad * 180 / pi);

}

