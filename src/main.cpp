#include "mbed.h"
#include "drv_gps.h"
#include "usain_gps.h"
#include <math.h>

UsainGPS gpsje;

void printmessage(AdafruitUltimateGPS::gprmc_data_t gps_data)
{
    double distance, bearing;
        if (*gps_data.validity == 'A')
        {
//                gps data = LLDD.DD lat = LL + (DD.DD / 60)
            UART.printf("Coördinates are: %f, %f \r\n", gps_data.latitude_fixed, gps_data.longitude_fixed);
            gpsje.calculate_distance(51.987475, 5.950763, &distance, &bearing);
            UART.printf("average coordinates are: %f meters, %f degrees\r\n", distance, bearing);
        }
}

int main() {
//    AdafruitUltimateGPS karel;S
    UART.printf("STARTUP\r\n");
    char error = gpsje.init();
    UART.printf("INITIALIZED");
    if (error & 0x01)
    {
        UART.printf("COLD START FAILED\r\n");
    }
    if (error & 0x02)
    {
        UART.printf("UART REFRESHRATE FAILED\r\n");
    }
    if (error & 0x04)
    {
        UART.printf("UART gprmc FAILED\r\n");
    }
    UART.printf("INITIALIZED");

    gpsje.on_new_message(callback(printmessage));
    while (true)
    {



    }
    return 0;
}
