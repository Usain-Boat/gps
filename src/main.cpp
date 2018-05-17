#include "mbed.h"
#include "drv_gps.h"

DigitalOut led(LED1);
DigitalIn button(USER_BUTTON);
//Serial UART(USBTX, USBRX, 57600);
//Serial GPS(D1, D0);

int main() {
    AdafruitUltimateGPS karel;
    gprmc_data test;
//    karel.writeregister((uint8_t *) "001", (uint8_t *) "604", 3, (uint8_t *)"3", 1); // checksum would be 32
//    karel.writeregister((uint8_t *) "001", (uint8_t *) "001", 3); //checksum would be 2E
//    karel.writeregister((uint8_t *) "000"); //checksum would be 32

//    UART.printf("Started\n\r");
    while (true) {


        karel.parsedata();
        if(karel.messagereceivedstatus()){
            led = led ^ 1;
            karel.GetLastGprmcData(&test);
//            UART.printf("Time stamp is: %s\r\n", &test.time_stamp);
//            UART.printf("validity gps is: %s\r\n", &test.validity);
            karel.messagereceivedstatus(false);
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