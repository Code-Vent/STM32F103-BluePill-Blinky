#pragma once
#include<stdint.h>
#include<stdint.h>
#include"clock.h"
#include"gpio.h"

typedef struct system system_t;
typedef struct gpio_config gpio_config_t;
typedef enum : uint8_t { GPIOA, GPIOB, GPIOC }gpio_sel_t;

struct system_i {
	void enable_peripheral(clock_sel_t, uint8_t bit);
	void configure_gpio(gpio_sel_t, gpio_config*);
	void write_pin(gpio_sel_t, uint8_t pin, bool);
	system_i() = default;
};