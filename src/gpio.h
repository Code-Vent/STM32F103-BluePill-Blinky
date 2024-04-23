#pragma once
#include<stdint.h>

typedef struct gpio gpio_t;

typedef enum : uint8_t{ IN, OUT_PP, OUT_OD, ALTERNATE_FUNC, ANALOG }mode_sel_t;
typedef enum : uint8_t{ LOW, MEDIUM, HIGH }speed_sel_t;
typedef enum : uint8_t{ NONE, PULL_UP, PULL_DOWN }pull_sel_t;

struct gpio_config {
	uint8_t pin;
	mode_sel_t mode;
	speed_sel_t speed;
	pull_sel_t pull;
};

void gpio_init(gpio_t*, gpio_config*);
void gpio_write(gpio_t*, uint8_t pin, bool l);