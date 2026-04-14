/*
 * command_handler.h
 *
 *  Created on: Mar 21, 2026
 *      Author: dekki
 */

#ifndef INC_COMMAND_HANDLER_H_
#define INC_COMMAND_HANDLER_H_

#include "main.h"
#include <string.h>
#include "ctype.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_PARAM_LEN 64
#define MAX_PARAMS 8

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim12;
extern UART_HandleTypeDef huart2;
extern SPI_HandleTypeDef hspi2;

// PWM variables
extern TIM_HandleTypeDef *last_PWM_htim;
extern uint32_t last_PWM_TIM_CHANNEL;
extern GPIO_TypeDef *last_PWM_GPIO_Port;
extern uint32_t last_PWM_Pin;
extern uint8_t last_PWM_Pinout;
extern uint8_t last_PWM_usetim;

// IC variables
extern TIM_HandleTypeDef *last_IC_htim;
extern uint32_t last_IC_TIM_CHANNEL;
extern GPIO_TypeDef *last_IC_GPIO_Port;
extern uint32_t last_IC_Pin;
extern uint8_t last_IC_Pinout;

// IC parameters
extern uint32_t IC_measure_buf[100];
extern uint8_t IC_measure_cnt;
extern uint8_t IC_avg;
extern uint8_t IC_filter;	// 0-None 1-median 2-mean
extern uint16_t IC_timeout;
extern uint32_t IC_measure_summary;

extern void CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
extern void UDP_Send_Data(uint8_t *data, uint16_t len);
extern void print_UART1(const char *str);

extern void PWM_config(TIM_HandleTypeDef *htim, uint32_t TIM_CHANNEL, GPIO_TypeDef *GPIO_Port, uint32_t Pin, uint32_t freq, uint32_t duty);
extern void PWM_start(TIM_HandleTypeDef *htim, uint32_t TIM_CHANNEL);
extern void PWM_stop(TIM_HandleTypeDef *htim, uint32_t TIM_CHANNEL);
extern void PWM_EMU_config(TIM_HandleTypeDef *htim, GPIO_TypeDef *GPIO_Port, uint32_t Pin, uint32_t freq, uint8_t duty);
extern void PWM_EMU_start(TIM_HandleTypeDef *htim);
extern void PWM_EMU_stop(TIM_HandleTypeDef *htim);

extern void IC_config(TIM_HandleTypeDef *htim, uint32_t TIM_CHANNEL, GPIO_TypeDef *GPIO_Port, uint32_t Pin);
extern void IC_EMU_config(TIM_HandleTypeDef *htim, GPIO_TypeDef *GPIO_Port, uint32_t Pin);
extern void IC_param(uint8_t avg, uint8_t filter, uint16_t timeout);
extern uint32_t IC_freq();


typedef struct {
    char command[MAX_PARAM_LEN];
    char params[MAX_PARAMS][MAX_PARAM_LEN];
    int param_count;
} ParsedData;

ParsedData Parse_package(uint8_t *str, uint32_t len);
void Send_Answer();

// Variable "last_connection_item" update any time while receive command from interface
// 0: None last receive interface
// 1: USB-CDC
// 2: USART
// 3: Ethernet
extern uint8_t last_connection_item;

#endif /* INC_COMMAND_HANDLER_H_ */
