#include "esp_common.h"

#include "task_main.h"
#include "task_smartconfig.h"


void task_main(void *pvParameters)
{
    bool bFirst = true;

    while (true) {
        //1秒ごとにチェック
        for (int lp = 0; lp < 30; lp++) {
            STATION_STATUS st = wifi_station_get_connect_status();
            if (st == STATION_GOT_IP) {
                goto LABEL_LIVE;
            }
            printf(".");
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
        if (bFirst) {
            //見つからなかったので、smart configモードに映る
            printf("start SmartConfig\n");
            xTaskCreate(task_smartconfig, "task_smartconfig", 256, NULL, 2, NULL);
            bFirst = false;
        }
    }

LABEL_LIVE:
    printf("start MainLoop\n");
    vTaskDelete(NULL);
}
