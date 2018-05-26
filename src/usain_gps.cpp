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
    status = _gps.setupdaterate((char *) "100");
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
    if (*dest.validity == 'V')
    {
        return -2; // data not valid
    }
    return 0;
}

//haversine method
double UsainGPS::get_distance_centimeter(AdafruitUltimateGPS::gprmc_data_t &gps_point1,
                                        AdafruitUltimateGPS::gprmc_data_t &gps_point2) {
    const double R = 6371e3;
    double latitude1 = deg2rad(gps_point1.latitude_fixed);
    double latitude2 = deg2rad(gps_point2.latitude_fixed);
    double latitude12 = deg2rad(gps_point2.latitude_fixed - gps_point1.latitude_fixed);//(lat2-lat1).toRadians();
    double longitude12 = deg2rad(gps_point2.longitude_fixed - gps_point1.longitude_fixed);//(lon2-lon1).toRadians();

    double a = sin(latitude12/2) * sin(latitude12/2) +
            cos(latitude1) * cos(latitude2) *
            sin(longitude12/2) * sin(longitude12/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
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

