//
// Created by Bas on 23-5-2018.
//

#include "usain_gps.h"
#include "drv_gps.h"

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

    Timer delaytje;
    delaytje.reset();
    delaytje.start();

    while (delaytje.read() < 5);

    status = _gps.setbaudrateto115200();
    if (status == -1)
    {
        UART.printf("commando good, action failed: %02x ", status);
    }
    else if (status == -2)
    {
        UART.printf("program error: %02x ", status);
    }
    else if (status == -3)
    {
        UART.printf("invalid command error: %02x ", status);
    }
    if (status)
    {
        return_value |= 0x02;
    }


    delaytje.reset();
    delaytje.start();

    while (delaytje.read() < 5);

    status = _gps.setupdaterate((char *) "300");
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
                if(_update.start(callback(this, &UsainGPS::update)) == osOK){
                    UART.printf("Thread Started\r\n");
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

bool UsainGPS::data_received() {
    return _gps.ReceievedNewGPRMC();
}

void UsainGPS::update() {
    while (1)
    {
        _gps.parsedata();
    }
}




