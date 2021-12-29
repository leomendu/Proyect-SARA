#ifndef __MQTT_H
#define __MQTT_H

#include "mqtt_client.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "esp_log.h"

#define MQTT_CONFIG_HMS         "hms"
#define MQTT_CONFIG_HMS_SZ      3
#define MQTT_CONFIG_AMOUNT      "amo"
#define MQTT_CONFIG_AMOUNT_SZ   3
#define MQTT_CONFIG_FEED        "feed"
#define MQTT_CONFIG_FEED_SZ     4

void log_error_if_nonzero(const char * message, int error_code);

esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event);

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

int get_mqtt_feed_flag(void);

void set_mqtt_feed_flag(int val);

extern void set_periodic_feeder_amount(int new_amount);

extern void set_periodic_feeder_delay(int new_delay);

#endif