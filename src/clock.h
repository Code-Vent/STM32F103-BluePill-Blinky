#pragma once 
#include<stdint.h>

constexpr uint8_t GPIOC_EN = 4;

typedef struct rcc rcc_t;
typedef enum { AHB, APB1, APB2 }clock_sel_t;

void clock_init(rcc_t*);
void clock_enable_peripheral(rcc_t*, clock_sel_t, uint8_t bit);