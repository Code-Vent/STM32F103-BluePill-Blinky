#include"system.h"

struct system{
	rcc_t*	rcc;
	gpio_t* gpioa;
	gpio_t* gpiob;
	gpio_t* gpioc;
};

const system_t inst = {
	.rcc   = reinterpret_cast<rcc_t*>(0x40021000),
	.gpioa = reinterpret_cast<gpio_t*>(0x40010800),
	.gpiob = reinterpret_cast<gpio_t*>(0x40010C00),
	.gpioc = reinterpret_cast<gpio_t*>(0x40011000)
};

extern "C" {

	void SystemInit(void) {
		clock_init(inst.rcc);
	}

	void SVC_Handler(void) {
		
	}
}

void system_i::enable_peripheral(clock_sel_t c, uint8_t bit)
{
	clock_enable_peripheral(inst.rcc, c, bit);
}

void system_i::configure_gpio(gpio_sel_t sel, gpio_config_t* config) 
{
	switch (sel) {
	case gpio_sel_t::GPIOA:
		gpio_init(inst.gpioa, config);
		break;
	case gpio_sel_t::GPIOB:
		gpio_init(inst.gpiob, config);
		break;
	case gpio_sel_t::GPIOC:
		gpio_init(inst.gpioc, config);
		break;
	}
}

void system_i::write_pin(gpio_sel_t sel, uint8_t pin, bool val)
{
	switch (sel) {
	case gpio_sel_t::GPIOA:
		gpio_write(inst.gpioa, pin, val);
		break;
	case gpio_sel_t::GPIOB:
		gpio_write(inst.gpiob, pin, val);
		break;
	case gpio_sel_t::GPIOC:
		gpio_write(inst.gpioc, pin, val);
		break;
	}
}