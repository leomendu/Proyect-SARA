#include "main.h"
#include "wifi.h"
#include "mqtt.h"
#include "uart.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0    18
#define GPIO_OUTPUT_IO_1    19
#define GPIO_INPUT_IO_0     5
#define GPIO_OUTPUT_PIN_SEL ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_PIN_SEL  1ULL<<GPIO_INPUT_IO_0
#define MS_TO_TICKS         10
#define FLOW                200

static int amount = 130; // default volume of food (ml)
static int delay_MS = 4000; // default delay between rations (ms)

void set_periodic_feeder_delay(int new_delay) {
    delay_MS = new_delay;
}

void set_periodic_feeder_amount(int new_amount) {
    amount = new_amount;
}

void periodic_feeder_task(void *arg){

    int amount_MS = 1000*amount/FLOW;

    while(1) {
        amount_MS = 1000*amount/FLOW;

        gpio_set_level(GPIO_OUTPUT_IO_0, 1);
        vTaskDelay(amount_MS/MS_TO_TICKS);
        
        gpio_set_level(GPIO_OUTPUT_IO_0, 0);
        vTaskDelay((delay_MS-amount_MS)/MS_TO_TICKS);
    }
    
}

void manual_feeder_task(void *arg){
    int buttonStatus = 0;
    int oldButtonStatus = 0;

    while(1) {

        oldButtonStatus = buttonStatus;
        buttonStatus = gpio_get_level(GPIO_INPUT_IO_0);

        if((buttonStatus==0)) {
            gpio_set_level(GPIO_OUTPUT_IO_0, 1);
        }

        else if((buttonStatus==1) && (oldButtonStatus==0)) {
            gpio_set_level(GPIO_OUTPUT_IO_0, 0);
        }

        if(get_mqtt_feed_flag() == 1) {
            int amount_MS = 1000*amount/FLOW;
            gpio_set_level(GPIO_OUTPUT_IO_0, 1);
            vTaskDelay(amount_MS/MS_TO_TICKS);
            gpio_set_level(GPIO_OUTPUT_IO_0, 0);
            set_mqtt_feed_flag(0);
        }

        vTaskDelay(2);        
    }
}

void app_main(void)
{
    gpio_config_t io_conf_out;
    gpio_config_t io_conf_in;

    // output gpio initialization
    io_conf_out.intr_type = GPIO_INTR_DISABLE; // interrupts -> disabled
    io_conf_out.mode = GPIO_MODE_OUTPUT; // mode -> output
    io_conf_out.pin_bit_mask = GPIO_OUTPUT_PIN_SEL; // mask of bits to configure
    io_conf_out.pull_down_en = 0; // pull-down -> disabled
    io_conf_out.pull_up_en = 0; // pull-up -> disabled
    gpio_config(&io_conf_out); // configure with the parameters above

    // input gpio initialization
    io_conf_in.intr_type = GPIO_INTR_DISABLE; // interrupts -> disabled
    io_conf_in.mode = GPIO_MODE_INPUT; // mode -> input
    io_conf_in.pin_bit_mask = GPIO_INPUT_PIN_SEL; // mask of bits to configure
    io_conf_in.pull_down_en = 0; // pull-down -> disabled
    io_conf_in.pull_up_en = 1; // pull-up -> enabled
    gpio_config(&io_conf_in); // configure with the parameters above

    // nvs flash initialization
    ESP_ERROR_CHECK(nvs_flash_init());

    initialise_wifi();
    //initialise_uart();

    //xTaskCreate(rx_task, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(periodic_feeder_task, "periodic_feeder_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(manual_feeder_task, "manual_feeder_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
    //xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL);

    /* wait for wifi connection */
    do{
        if(get_wifi_status() == SMARTCONFIG_OVER)
            break;

        printf("Waiting for Wi-Fi, use ESPTouch app.\n");
        vTaskDelay(T_CONFIG_TICKS);

    } while(1);

    /* MQTT config */
    esp_mqtt_client_config_t mqtt_cfg = {
        .host="192.168.0.23",
        .port=1883,
        .transport= MQTT_TRANSPORT_OVER_TCP,
    };

    /* MQTT client init */
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);

    /* example messages and topics definitions */
    const char *log_topic = "/home/log";
    const char *config_topic = "/home/config";
    const char *msg = "ESP ready to configure";

    /* example messages and topics executions */
    esp_mqtt_client_publish(client, log_topic, msg, strlen(msg), 1, false);
    esp_mqtt_client_subscribe(client, config_topic, 1);

}