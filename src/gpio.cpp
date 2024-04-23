#include"gpio.h"
#include"def.h"

struct gpio {
	reg_type CRL;
	reg_type CRH;
	reg_type IDR;
	reg_type ODR;
	reg_type BSRR;
	reg_type BRR;
	reg_type LCKR;
};

void input_output_config(gpio_t* gpio, gpio_config* config);
void alternate_func_config(gpio_t* gpio, gpio_config* config);
void analog_config(gpio_t* gpio, gpio_config* config);

void gpio_init(gpio_t* gpio, gpio_config* config) {
	if (config->mode == mode_sel_t::IN ||
		config->mode == mode_sel_t::OUT_OD ||
		config->mode == mode_sel_t::OUT_PP
		)
	{
		input_output_config(gpio, config);
	}
	else if (config->mode == mode_sel_t::ALTERNATE_FUNC) {
		alternate_func_config(gpio, config);
	}
	else {
		analog_config(gpio, config);
	}
}

void input_output_config(gpio_t* gpio, gpio_config* config) {
	reg_type* crlh;
	uint8_t bit = config->pin;

	if (config->pin < 8) {
		crlh = &gpio->CRH;
	}
	else if (config->pin < 16) {
		crlh = &gpio->CRL;
		bit -= 8;
	}
	else {
		return;
	}
	reg_type mask = (1u << (4 * bit));
	if (config->mode == mode_sel_t::IN) {
		*crlh &= ~mask;
		mask <<= 1;
		*crlh &= ~mask;
		mask <<= 1;
	}
	else if (config->mode == mode_sel_t::OUT_OD || config->mode == mode_sel_t::OUT_PP) {
		switch (config->speed) {
		case speed_sel_t::LOW:
			*crlh &= ~mask;
			mask <<= 1;
			*crlh |= mask;
			mask <<= 1;
			break;
		case speed_sel_t::MEDIUM:
			*crlh |= mask;
			mask <<= 1;
			*crlh &= ~mask;
			mask <<= 1;
			break;
		case speed_sel_t::HIGH:
			*crlh |= mask;
			mask <<= 1;
			*crlh |= mask;
			mask <<= 1;
			break;
		}
	}

	//configure
	if (config->mode == mode_sel_t::IN) {
		switch (config->pull) {
		case pull_sel_t::PULL_DOWN:
		case pull_sel_t::PULL_UP:
			*crlh |= mask;
			mask <<= 1;
			*crlh &= ~mask;
			mask <<= 1;
			break;
		case pull_sel_t::NONE:
			*crlh &= ~mask;
			mask <<= 1;
			*crlh |= mask;
			mask <<= 1;
			break;
		}
	}
	else if (config->mode == mode_sel_t::OUT_OD || config->mode == mode_sel_t::OUT_PP) {
		switch (config->mode) {
		case mode_sel_t::OUT_OD:
			*crlh |= mask;
			mask <<= 1;
			*crlh |= mask;
			mask <<= 1;
			break;
		case mode_sel_t::OUT_PP:
			*crlh |= mask;
			mask <<= 1;
			*crlh |= mask;
			mask <<= 1;
			break;
		default:
			break;
		}
	}
}

void alternate_func_config(gpio_t* gpio, gpio_config* config) {

}

void analog_config(gpio_t* gpio, gpio_config* config) {}

void gpio_write(gpio_t* g_gpio, uint8_t pin, bool l)
{
	if (l)
		g_gpio->ODR |= (1u << pin);
	else
		g_gpio->ODR &= ~(1u << pin);
}