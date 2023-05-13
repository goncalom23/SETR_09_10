#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>		/* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/
#include <zephyr/sys/printk.h>      /* for printk()*/

#ifndef button_H
#define button_H

/* Use a "big" sleep time to reduce CPU load (button detection int activated, not polled) */
#define SLEEP_TIME_MS   60*1000 

#define LED1_PIN 13

#define GPIO0_NODE DT_NODELABEL(gpio0)


void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

void button_config();


#endif