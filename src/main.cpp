#include"system.h"

auto config = gpio_config_t{
		.pin = 13,
		.mode = mode_sel_t::OUT_PP,
		.speed = speed_sel_t::LOW,
		.pull = pull_sel_t::NONE
};

int main() {	
	system_i s;
	s.enable_peripheral(clock_sel_t::APB2, GPIOC_EN);
	s.configure_gpio(gpio_sel_t::GPIOC, &config);
	for (;;) {
		s.write_pin(gpio_sel_t::GPIOC, config.pin, true);
		for (uint32_t i = 0; i < 80000; ++i);
		s.write_pin(gpio_sel_t::GPIOC, config.pin, false);
	}
}