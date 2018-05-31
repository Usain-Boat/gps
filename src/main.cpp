#include "mbed.h"
#include "drv_gps.h"
#include "usain_gps.h"
#include <math.h>

static Serial UART(USBTX, USBRX, 115200);

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
        UART.printf("UART REFRESHRATE FAILED\r\n");
    }
    if (error & 0x04)
    {
        UART.printf("UART gprmc FAILED\r\n");
    }
    while (true)
    {

        if (!gpsje.get_gps_message(test))
        {
            if (*test.validity == 'A')
            {
                //gps data = LLDD.DD lat = LL + (DD.DD / 60)
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
