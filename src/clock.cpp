#include"clock.h"
#include"def.h"

struct rcc {
	reg_type CR;
	reg_type CFGR;
	reg_type CIR;
	reg_type APB2RSTR;
	reg_type APB1RSTR;
	reg_type AHBENR;
	reg_type APB2ENR;
	reg_type APB1ENR;
	reg_type BDCR;
	reg_type CSR;
};

void clock_init(rcc_t* rcc) {
	rcc->CR |= 0x00010000;
	while (!(rcc->CR & 0x00020000));
	uint32_t temp = 0;
	temp &= ~0x00000003;
	temp |= 0x00000001;
	rcc->CFGR = temp;
	while (!((rcc->CFGR & 0x0000000C) == 0x00000004));
}

void clock_enable_peripheral(rcc_t* g_rcc, clock_sel_t clk, uint8_t bit)
{
	uint32_t mask = (1u << bit);
	switch (clk) {
	case clock_sel_t::AHB:
		g_rcc->AHBENR |= mask;
		break;
	case clock_sel_t::APB1:
		g_rcc->APB1ENR |= mask;
		break;
	case clock_sel_t::APB2:
		g_rcc->APB2ENR |= mask;
		break;
	}
}