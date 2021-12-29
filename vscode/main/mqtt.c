#include "include/mqtt.h"
#include "include/uart.h"
#include <stdlib.h>

const char *MQTT_TAG = "MQTT_EXAMPLE";
static int MQTT_feed_flag = 0;

void log_error_if_nonzero(const char * message, int error_code) {
    if (error_code != 0) {
        ESP_LOGE(MQTT_TAG, "Last error %s: 0x%x", message, error_code);
    }
}

esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {

    esp_mqtt_client_handle_t client = event->client;

    switch(event->event_id) {

        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_CONNECTED");
            esp_mqtt_client_publish(client, "/logs", "connected", 10, 1, 0);
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            esp_mqtt_client_publish(client, "/logs", "subscribed", 11, 1, 0);
            break;

        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            
            if(strstr(event->data, MQTT_CONFIG_HMS) != NULL) {
                // if configuring hour-minute-second, it is expected the format:
                // hms:HH:MM:SS, where ':' can be replaced by ANY delimiter.
                char *aux = event->data;
                aux[MQTT_CONFIG_HMS_SZ+1+2] = '\0';
                aux[MQTT_CONFIG_HMS_SZ+1+2+1+2] = '\0';

                set_periodic_feeder_delay(atoi(&aux[MQTT_CONFIG_HMS_SZ+1])*60*60*1000 +
                    atoi(&aux[MQTT_CONFIG_HMS_SZ+1+2+1])*60*1000 + 
                    atoi(&aux[MQTT_CONFIG_HMS_SZ+1+2+1+2+1])*1000);
            }

            if(strstr(event->data, MQTT_CONFIG_AMOUNT) != NULL) {
                // if configuring amount of food, it is expected the format:
                // amo:VOLUME, where ':' can be replaced by ANY delimiter.
                char *aux = event->data;

                set_periodic_feeder_amount(atoi(&aux[MQTT_CONFIG_AMOUNT_SZ+1]));
            }
            
            if(strstr(event->data, MQTT_CONFIG_FEED) != NULL) {
                // if giving the order to feed, it is expected the word feed.
                MQTT_feed_flag = 1;
            }

            break;

        case MQTT_EVENT_ERROR:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_ERROR");
            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
                log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
                log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
                ESP_LOGI(MQTT_TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
            }
            break;

        default:
            ESP_LOGI(MQTT_TAG, "Other event id:%d", event->event_id);
            break;
    }

    return ESP_OK;
}

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    
    ESP_LOGD(MQTT_TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

int get_mqtt_feed_flag(void) {
    return MQTT_feed_flag;
}

void set_mqtt_feed_flag(int val) {
    MQTT_feed_flag = val;
}