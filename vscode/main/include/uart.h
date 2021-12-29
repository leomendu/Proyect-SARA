#ifndef __UART_H
#define __UART_H

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_log.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#define TXD_PIN (GPIO_NUM_4)
#define RXD_PIN (GPIO_NUM_5)

void initialise_uart(void);
int sendData(const char* logName, const char* data);
//void tx_task(void *arg);
void rx_task(void *arg);

#endif