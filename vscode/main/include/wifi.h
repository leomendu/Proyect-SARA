#ifndef __WIFI_H
#define __WIFI_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "nvs_flash.h"

typedef enum {
    STATUS_OK,
    SMARTCONFIG_OVER,
} app_wifi_t;

/* FreeRTOS event group to signal when we are connected & ready to make a request */
EventGroupHandle_t s_wifi_event_group;

app_wifi_t ST_APP;

void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

void initialise_wifi(void);

void smartconfig_example_task(void * parm);

app_wifi_t get_wifi_status(void);

#endif