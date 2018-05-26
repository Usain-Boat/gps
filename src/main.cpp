#include "mbed.h"
#include "drv_gps.h"
#include "usain_gps.h"

DigitalOut led(LED1);
DigitalIn button(USER_BUTTON);
//Serial GPS(D1, D0);
//Serial UART(USBTX, USBRX, 57600);

int main() {
//    AdafruitUltimateGPS karel;
    AdafruitUltimateGPS::gprmc_data_t test;
    UsainGPS gpsje;

    UART.printf("STARTUP\r\n");
    char error = gpsje.init();

    if (error & 0x01)
    {
        UART.printf("COLD START FAILED\r\n");
    }
    if (error & 0x02)
    {
        UART.printf("UART baudrate FAILED\r\n");
    }
    if (error & 0x04)
    {
        UART.printf("UART REFRESHRATE FAILED\r\n");
    }

//    switch(karel.setupdaterate("200")){
//        case GPS_ACK_INVALID_COMMAND:
//            UART.printf("SETUPDATERATE: INVALID COMMAND\r\n");
//            break;
//        case GPS_ACK_UNSUPPORTED_COMMAND:
//            UART.printf("SETUPDATERATE: UNSUPPORTED COMMAND\r\n");
//            break;
//        case GPS_ACK_ACTION_FAILED:
//            UART.printf("SETUPDATERATE: ACTION FAILED\r\n");
//            break;
//        case GPS_ACK_SUCCES:
//            UART.printf("SETUPDATERATE: SUCCES\r\n");
//            break;
//        case '4':
//            UART.printf("SETUPDATERATE: CODE ERROR\r\n");
//            break;
//        default:
//            UART.printf("SYSTEM FAULT!\r\n");
//            break;
//    }

    while (true)
    {


//        karel.parsedata();

        if (!gpsje.get_gps_message(test))
        {
            if (*test.validity == 'A')
            {
                //gps data = LLDD.DD lat = LL + (DD.DD / 60)
                UART.printf("dingentje are: %s, %s \r\n", test.latitude, test.longitude);
                UART.printf("Coördinates are: %f, %f \r\n", test.latitude_fixed, test.longitude_fixed);
            }
            else
            {
                UART.printf("searching for GPS %s\r\n", &test.validity);
            }
        }

    }

    return 0;
}

//class MotorControl{
//public:
//    MotorControl():  {
//
//    }
//    ~MotorControl();
//private:
//    PwmOut _motor_links;
//    PwmOut _motor_rechts;
//    PwmIn   _steer;
//    PwmIn   _throttle;
//};