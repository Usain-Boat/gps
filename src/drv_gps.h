//
// Created by Bas on 18-4-2018.
//

#ifndef BLINKY_DRV_GPS_H
#define BLINKY_DRV_GPS_H

#include "mbed.h"
#include "databuffer.h"
#include <string.h>

struct ultimate_gps_message {
    uint8_t messagetype[10];
    uint8_t number_of_parameters;
    uint8_t parameters[20][50];
} ;

struct gprmc_data{
    uint8_t time_stamp[10];
    uint8_t validity[10];
    uint8_t latitude[10];
    uint8_t north_south;
    uint8_t longitude[10];
    uint8_t east_west[10];
    uint8_t speed[10];
    uint8_t course[10];
    uint8_t date_stamp[10];
    uint8_t variation_degrees[10];
    uint8_t variation_east_west[10];
    uint8_t mode_indicator[10];
};

class AdafruitUltimateGPS
{
public:

    AdafruitUltimateGPS();
    ~AdafruitUltimateGPS();

    void writeregister(uint8_t *PacketType);
    void writeregister(uint8_t *packet_type, uint8_t *parameter1_data, uint8_t parameter1_size);
    void writeregister(uint8_t *packet_type, uint8_t *parameter1_data, uint8_t parameter1_size,
                                            uint8_t *parameter2_data, uint8_t parameter2_size);

    void parsedata();
    void GetLastGprmcData(gprmc_data* gpsdata);
    bool messagereceivedstatus();
    void messagereceivedstatus(bool status);

private:
    Serial _UART;
    Databuffer _sendstring;
    Databuffer _receivestring;
    ultimate_gps_message _last_received_message;
    gprmc_data _last_received_gprmc;

    void _RXInterrupt();
    bool _CRCCheck(char* gps_string);

    //status flags
    bool _flag_message_received = false;
    bool _flag_received_valid_string = false;

};


#endif //BLINKY_DRV_GPS_H
