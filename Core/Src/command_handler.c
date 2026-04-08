/*
 * command_handler.c
 *
 *  Created on: Mar 21, 2026
 *      Author: dekki
 */

#include "command_handler.h"

enum Pin_Mode{
	None = 0,
	RCC_OSC_IN = 1,
	RCC_OSC_OUT = 2,
	SYS_JTCK_SWCLK = 3,
	SYS_JTMS_SWDIO = 4,
	USB_DP = 5,
	USB_DM = 6,
	USART1_RX = 7,
	USART1_TX = 8,
	SPI1_RESET = 9,
	SPI1_NSS = 10,
	SPI1_SCK = 11,
	SPI1_MISO = 12,
	SPI1_MOSI = 13,
	PWM = 14,
	PWM_EMU =15,
	IC = 16,
	IC_EMU = 17
};

typedef struct Pinout_struct{
	char *pin_name;
	TIM_HandleTypeDef *htim;
	uint32_t tim_channel;
	GPIO_TypeDef *GPIO_Port;
	uint32_t GPIO_Pin;
	enum Pin_Mode mode;
} Pinout_struct;

struct Pinout_struct Pinout[37]={
		  {"PC13",0, 0, GPIOC, GPIO_PIN_13, None},
		  {"PC14",0, 0, GPIOC, GPIO_PIN_14, None},
		  {"PC15",0, 0, GPIOC, GPIO_PIN_15, None},
		  {"PD0", 0, 0, GPIOD, GPIO_PIN_0, RCC_OSC_IN},
		  {"PD1", 0, 0, GPIOD, GPIO_PIN_1, RCC_OSC_OUT},
		  {"PA0", &htim2, TIM_CHANNEL_1, GPIOA, GPIO_PIN_0, None},
		  {"PA1", &htim2, TIM_CHANNEL_2, GPIOA, GPIO_PIN_1, None},
		  {"PA2", &htim2, TIM_CHANNEL_3, GPIOA, GPIO_PIN_2, None},
		  {"PA3", &htim2, TIM_CHANNEL_4, GPIOA, GPIO_PIN_3, SPI1_RESET},
		  {"PA4", 0, 0, GPIOA, GPIO_PIN_4, SPI1_NSS},
		  {"PA5", 0, 0, GPIOA, GPIO_PIN_5, SPI1_SCK},
		  {"PA6", &htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_6, SPI1_MISO},
		  {"PA7", &htim3, TIM_CHANNEL_2, GPIOA, GPIO_PIN_7, SPI1_MOSI},
		  {"PB0", &htim3, TIM_CHANNEL_3, GPIOB, GPIO_PIN_0, None},
		  {"PB1", &htim3, TIM_CHANNEL_4, GPIOB, GPIO_PIN_1, None},
		  {"PB2", 0, 0, GPIOB, GPIO_PIN_2, None},
		  {"PB10",&htim2, TIM_CHANNEL_3, GPIOB, GPIO_PIN_10, None},
		  {"PB11",&htim2, TIM_CHANNEL_4, GPIOB, GPIO_PIN_11, None},
		  {"PB12",0, 0, GPIOB, GPIO_PIN_12, None},
		  {"PB13",0, 0, GPIOB, GPIO_PIN_13, None},
		  {"PB14",0, 0, GPIOB, GPIO_PIN_14, None},
		  {"PB15",0, 0, GPIOB, GPIO_PIN_15, None},
		  {"PA8", &htim1, TIM_CHANNEL_1, GPIOA, GPIO_PIN_8, None},
		  {"PA9", &htim1, TIM_CHANNEL_2, GPIOA, GPIO_PIN_9, None},
		  {"PA10",&htim1, TIM_CHANNEL_3, GPIOA, GPIO_PIN_10, None},
		  {"PA11",&htim1, TIM_CHANNEL_4, GPIOA, GPIO_PIN_11, USB_DM},
		  {"PA12",0, 0, GPIOA, GPIO_PIN_12, USB_DP},
		  {"PA13",0, 0, GPIOA, GPIO_PIN_13, SYS_JTMS_SWDIO},
		  {"PA14",0, 0, GPIOA, GPIO_PIN_14, SYS_JTCK_SWCLK},
		  {"PA15",&htim2, TIM_CHANNEL_1, GPIOA, GPIO_PIN_15, None},
		  {"PB3", &htim2, TIM_CHANNEL_2, GPIOB, GPIO_PIN_3, None},
		  {"PB4", &htim3, TIM_CHANNEL_1, GPIOB, GPIO_PIN_4, None},
		  {"PB5", &htim3, TIM_CHANNEL_2, GPIOB, GPIO_PIN_5, None},
		  {"PB6", 0, 0, GPIOB, GPIO_PIN_6, USART1_TX},
		  {"PB7", 0, 0, GPIOB, GPIO_PIN_7, USART1_RX},
		  {"PB8", 0, 0, GPIOB, GPIO_PIN_8, None},
		  {"PB9", 0, 0, GPIOB, GPIO_PIN_9, None}
};

const char* pin_mode_to_string(enum Pin_Mode mode) {
    switch(mode) {
        case None: return "None";
        case RCC_OSC_IN: return "RCC_OSC_IN";
        case RCC_OSC_OUT: return "RCC_OSC_OUT";
        case SYS_JTCK_SWCLK: return "SYS_JTCK_SWCLK";
        case SYS_JTMS_SWDIO: return "SYS_JTMS_SWDIO";
        case USB_DP: return "USB_DP";
        case USB_DM: return "USB_DM";
        case USART1_RX: return "USART1_RX";
        case USART1_TX: return "USART1_TX";
        case SPI1_RESET: return "SPI1_RESET";
        case SPI1_NSS: return "SPI1_NSS";
        case SPI1_SCK: return "SPI1_SCK";
        case SPI1_MISO: return "SPI1_MISO";
        case SPI1_MOSI: return "SPI1_MOSI";
        case PWM: return "PWM";
        case PWM_EMU: return "PWM_EMU";
        case IC: return "IC";
        case IC_EMU: return "IC_EMU";
        default: return "Unknown";
    }
}

enum filter_type{
	none = 0,
	mean = 1,
	median = 2,
	min = 3,
	max = 4,
	Unknown = 5
};

const char* filter_type_to_string(enum filter_type filter) {
    switch(filter) {
        case none: return "none";
        case mean: return "mean";
        case median: return "median";
        case min: return "min";
        case max: return "max";
        default: return "Unknown";
    }
}

uint8_t string_to_filter_type(const char* str){
    if (strncasecmp(str, "none", 4) == 0) {
        return none;
    }
    else if (strncasecmp(str, "mean", 4) == 0) {
        return mean;
    }
    else if (strncasecmp(str, "median", 6) == 0) {
        return median;
    }
    else if (strncasecmp(str, "min", 3) == 0) {
        return min;
    }
    else if (strncasecmp(str, "max", 3) == 0) {
        return max;
    }
    else {
    	return Unknown;
    }
}


int case_insensitive_strcmp(const char *str1, const char *str2) {
    while (*str1 && tolower((unsigned char)*str1) == tolower((unsigned char)*str2)) {
        str1++;
        str2++;
    }
    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}


uint32_t string_to_uint32(const char *str) {
    char *endptr;
    errno = 0;
    unsigned long val = strtoul(str, &endptr, 10);
    // Check for errors
    if (errno == ERANGE || val > UINT32_MAX) {
        return UINT32_MAX;
    }
    if (endptr == str) {
        return UINT32_MAX;
    }
    return (uint32_t)val;
}

ParsedData Parse_package(uint8_t *str, uint32_t len){
	ParsedData result = { .param_count = 0 };
	static char Answer_str[64];
	static uint32_t Answer_len;

	// Check empty package
	if (str == NULL || len == 0) {
		memset(Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "ERROR: Receiver data in NULL.\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
		return result;
	}

	// Copy buffer
	char buffer[len + 1];
	memcpy(buffer, str, len);
	buffer[len] = '\0';

	char *token = strtok(buffer, " ");

	// Get command (first word)
	if (token != NULL) {
		strncpy(result.command, token, MAX_PARAM_LEN - 1);
		result.command[MAX_PARAM_LEN - 1] = '\0';

		// Get parameters (others words)
		while ((token = strtok(NULL, " ")) != NULL && result.param_count < MAX_PARAMS) {
			strncpy(result.params[result.param_count], token, MAX_PARAM_LEN - 1);
			result.params[result.param_count][MAX_PARAM_LEN - 1] = '\0';
			result.param_count++;
		}
	}


	//Command handler

	// HELP //
	if (!case_insensitive_strcmp(result.command, "help")){
		memset(Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "HELP: echo, pinout, config_gen, gen, config_measure, ");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
		HAL_Delay(5);
		memset(Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "measure_params, freq.\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
	}

	// ECHO //
	else if (!case_insensitive_strcmp(result.command, "echo")){
		memset(Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "ECHO: ");
		for (uint8_t i=0; i<result.param_count; i++){
			strcat(Answer_str, result.params[i]);
			strcat(Answer_str, " ");
		}
		strcat(Answer_str, "\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
	}

	// PINOUT //
	else if (!case_insensitive_strcmp(result.command, "pinout")){
		const uint8_t Pinout_size = sizeof(Pinout) / sizeof(Pinout[0]);
		for (uint8_t i=0; i<Pinout_size ; i++){
			memset(Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, Pinout[i].pin_name);
			strcat(Answer_str,": ");
			strcat(Answer_str, pin_mode_to_string(Pinout[i].mode));
			if (Pinout[i].htim==0){
				strcat(Answer_str," (no TIM)\n");
			}
			else{
				strcat(Answer_str," (have TIM)\n");
			}
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
		}
	}

	// CONFIG_GEN //
	else if (!case_insensitive_strcmp(result.command, "config_gen")){
		// Check parameters
		if (result.param_count!= 3){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for CONFIG_GEN command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, " Need 3 parameters (pin, freq, duty).\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}
		const uint8_t Pinout_size = sizeof(Pinout) / sizeof(Pinout[0]);
		for (uint8_t i=0; i<Pinout_size ; i++){
			if (!case_insensitive_strcmp(result.params[0], Pinout[i].pin_name)){
				// Check mode
				if (Pinout[i].mode!=None && Pinout[i].mode!=PWM && Pinout[i].mode!=PWM_EMU){
					// Send Error
					memset(Answer_str, 0, sizeof(Answer_str));
					strcat(Answer_str, "ERROR: pin ");
					strcat(Answer_str, Pinout[i].pin_name);
					strcat(Answer_str, " already use for ");
					strcat(Answer_str,pin_mode_to_string(Pinout[i].mode));
					strcat(Answer_str, ".\n");
					Answer_len =strlen(Answer_str);
					Send_Answer(Answer_str, Answer_len);
					return result;
				}
				// Erase last PWM mode
				Pinout[last_PWM_Pinout].mode=None;

				// Check hardware TIM
				if (Pinout[i].htim!=0){
					uint32_t freq = string_to_uint32(result.params[1]);
					uint32_t duty = string_to_uint32(result.params[2]);
					// Check freq for hardware PWM
					if (freq<=10000 && freq>0 ){
						// Check duty
						if (duty<=100 && duty>=0){
							if (last_PWM_htim!=0){PWM_stop(last_PWM_htim, last_PWM_TIM_CHANNEL);}
							last_PWM_htim = Pinout[i].htim;
							last_PWM_TIM_CHANNEL = Pinout[i].tim_channel;
							last_PWM_GPIO_Port = Pinout[i].GPIO_Port;
							last_PWM_Pin = Pinout[i].GPIO_Pin;
							last_PWM_Pinout= i;
							PWM_config(Pinout[i].htim, Pinout[i].tim_channel, Pinout[i].GPIO_Port, Pinout[i].GPIO_Pin, freq, duty);
							Pinout[i].mode=PWM;
							memset (Answer_str, 0, sizeof(Answer_str));
							strcat(Answer_str, "GEN CONFIGURED on ");
							strcat(Answer_str, result.params[0]);
							strcat(Answer_str, ": ");
							strcat(Answer_str, result.params[1]);
							strcat(Answer_str, " Hz, ");
							strcat(Answer_str, result.params[2]);
							strcat(Answer_str, "% (hardware)\n");
							Answer_len =strlen(Answer_str);
							Send_Answer(Answer_str, Answer_len);
							return result;
						}
						else{
							memset (Answer_str, 0, sizeof(Answer_str));
							strcat(Answer_str, "ERROR: get invalid parameters for CONFIG_GEN command.");
							Answer_len =strlen(Answer_str);
							Send_Answer(Answer_str, Answer_len);
							HAL_Delay(5);
							memset (Answer_str, 0, sizeof(Answer_str));
							strcat(Answer_str, " Duty must be from 0 to 100.\n");
							Answer_len =strlen(Answer_str);
							Send_Answer(Answer_str, Answer_len);
							return result;
						}
					}
					else {
						memset (Answer_str, 0, sizeof(Answer_str));
						strcat(Answer_str, "ERROR: get invalid parameters for CONFIG_GEN command.");
						Answer_len =strlen(Answer_str);
						Send_Answer(Answer_str, Answer_len);
						HAL_Delay(5);
						memset (Answer_str, 0, sizeof(Answer_str));
						strcat(Answer_str, " Freq must be from 1 to 10000 Hz.\n");
						Answer_len =strlen(Answer_str);
						Send_Answer(Answer_str, Answer_len);
						return result;
					}
				}
				else{
					uint32_t freq = string_to_uint32(result.params[1]);
					uint32_t duty = string_to_uint32(result.params[2]);
					// Check freq for software PWM
					if (freq<=10000 && freq>0 ){
						// Check duty
						if (duty<=100 && duty>=0){
							if (last_IC_htim == &htim1){
								last_PWM_htim = &htim2;
								last_PWM_TIM_CHANNEL = Pinout[i].tim_channel;
								last_PWM_GPIO_Port = Pinout[i].GPIO_Port;
								last_PWM_Pin = Pinout[i].GPIO_Pin;
								last_PWM_Pinout= i;
								if (last_PWM_htim!=0){PWM_EMU_stop(last_PWM_htim);}
								PWM_EMU_config(&htim2, Pinout[i].GPIO_Port, Pinout[i].GPIO_Pin, freq, duty);
							}
							else {
								last_PWM_htim = &htim1;
								last_PWM_TIM_CHANNEL = Pinout[i].tim_channel;
								last_PWM_GPIO_Port = Pinout[i].GPIO_Port;
								last_PWM_Pin = Pinout[i].GPIO_Pin;
								last_PWM_Pinout= i;
								if (last_PWM_htim!=0){PWM_EMU_stop(last_PWM_htim);}
								PWM_EMU_config(&htim1, Pinout[i].GPIO_Port, Pinout[i].GPIO_Pin, freq, duty);
							}
							Pinout[i].mode=PWM_EMU;
							memset (Answer_str, 0, sizeof(Answer_str));
							strcat(Answer_str, "GEN CONFIGURED on ");
							strcat(Answer_str, result.params[0]);
							strcat(Answer_str, ": ");
							strcat(Answer_str, result.params[1]);
							strcat(Answer_str, " Hz, ");
							strcat(Answer_str, result.params[2]);
							strcat(Answer_str, "% (software)\n");
							Answer_len =strlen(Answer_str);
							Send_Answer(Answer_str, Answer_len);
							return result;
						}
						else{
							memset (Answer_str, 0, sizeof(Answer_str));
							strcat(Answer_str, "ERROR: get invalid parameters for CONFIG_GEN command.");
							Answer_len =strlen(Answer_str);
							Send_Answer(Answer_str, Answer_len);
							HAL_Delay(5);
							memset (Answer_str, 0, sizeof(Answer_str));
							strcat(Answer_str, " Duty must be from 0 to 100.\n");
							Answer_len =strlen(Answer_str);
							Send_Answer(Answer_str, Answer_len);
							return result;
						}
					}
					else {
						memset (Answer_str, 0, sizeof(Answer_str));
						strcat(Answer_str, "ERROR: get invalid parameters for CONFIG_GEN command.");
						Answer_len =strlen(Answer_str);
						Send_Answer(Answer_str, Answer_len);
						HAL_Delay(5);
						memset (Answer_str, 0, sizeof(Answer_str));
						strcat(Answer_str, " Freq must be from 1 to 10000 Hz.\n");
						Answer_len =strlen(Answer_str);
						Send_Answer(Answer_str, Answer_len);
						return result;
					}
				}
			}
		}
		memset (Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "ERROR: pin ");
		strcat(Answer_str, result.params[0]);
		strcat(Answer_str, " dont exist.\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
		return result;
	}

	// GEN //
	else if (!case_insensitive_strcmp(result.command, "gen")){
		// Check parameters
		if (result.param_count!= 1){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for GEN command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, " Need 1 parameter (start or stop).\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}
		// Check PWM last pin
		if (last_PWM_Pin == 0){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: PWM not configurated. Use config_gen.\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}
		else {
			if (!case_insensitive_strcmp(result.params[0], "start")){
				if (last_PWM_usetim == 0){
					PWM_EMU_start(last_PWM_htim);
				}
				else {
					PWM_start(last_PWM_htim, last_PWM_TIM_CHANNEL);
				}
				memset (Answer_str, 0, sizeof(Answer_str));
				strcat(Answer_str, "GEN STARTED\n");
				Answer_len =strlen(Answer_str);
				Send_Answer(Answer_str, Answer_len);
				return result;
			}
			else if (!case_insensitive_strcmp(result.params[0], "stop")){
				if (last_PWM_htim == 0){
					PWM_EMU_stop(last_PWM_htim);
				}
				else {
					PWM_stop(last_PWM_htim, last_PWM_TIM_CHANNEL);
				}
				memset (Answer_str, 0, sizeof(Answer_str));
				strcat(Answer_str, "GEN STOPPED\n");
				Answer_len =strlen(Answer_str);
				Send_Answer(Answer_str, Answer_len);
				return result;
			}
		}
	}

	// CONFIG_MEASURE //
	else if (!case_insensitive_strcmp(result.command, "config_measure")){
		// Check parameters
		if (result.param_count!= 1){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for CONFIG_MEASURE command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, " Need 1 parameter (pin name).\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}
		const uint8_t Pinout_size = sizeof(Pinout) / sizeof(Pinout[0]);
		for (uint8_t i=0; i<Pinout_size ; i++){
			if (!case_insensitive_strcmp(result.params[0], Pinout[i].pin_name)){
				// Check mode
				if (Pinout[i].mode!=None && Pinout[i].mode!=IC && Pinout[i].mode!=IC_EMU){
					// Send Error
					memset(Answer_str, 0, sizeof(Answer_str));
					strcat(Answer_str, "ERROR: pin ");
					strcat(Answer_str, Pinout[i].pin_name);
					strcat(Answer_str, " already use for ");
					strcat(Answer_str,pin_mode_to_string(Pinout[i].mode));
					strcat(Answer_str, ".\n");
					Answer_len =strlen(Answer_str);
					Send_Answer(Answer_str, Answer_len);
					return result;
				}

				// Erase last PWM mode
				Pinout[last_IC_Pinout].mode=None;

				// Check hardware TIM
				if (Pinout[i].htim!=0 && Pinout[i].htim!=last_PWM_htim){
					IC_config(Pinout[i].htim, Pinout[i].tim_channel, Pinout[i].GPIO_Port, Pinout[i].GPIO_Pin);
					Pinout[i].mode=IC;
					last_IC_htim = Pinout[i].htim;
					last_IC_TIM_CHANNEL = Pinout[i].tim_channel;
					last_IC_GPIO_Port = Pinout[i].GPIO_Port;
					last_IC_Pin = Pinout[i].GPIO_Pin;
					last_IC_Pinout = i;
					memset (Answer_str, 0, sizeof(Answer_str));
					strcat(Answer_str, "MEASURE CONFIGURED on ");
					strcat(Answer_str, result.params[0]);
					strcat(Answer_str, " (hardware)\n");
					Answer_len =strlen(Answer_str);
					Send_Answer(Answer_str, Answer_len);
					return result;
				}
				else{
					if (last_PWM_htim == &htim1){
						last_IC_htim = &htim2;
						last_IC_TIM_CHANNEL = Pinout[i].tim_channel;
						last_IC_GPIO_Port = Pinout[i].GPIO_Port;
						last_IC_Pin = Pinout[i].GPIO_Pin;
						last_IC_Pinout= i;
						IC_EMU_config(&htim2, Pinout[i].GPIO_Port, Pinout[i].GPIO_Pin);
						Pinout[i].mode=IC_EMU;
					}
					else {
						last_IC_htim = &htim1;
						last_IC_TIM_CHANNEL = Pinout[i].tim_channel;
						last_IC_GPIO_Port = Pinout[i].GPIO_Port;
						last_IC_Pin = Pinout[i].GPIO_Pin;
						last_IC_Pinout= i;
						IC_EMU_config(&htim1, Pinout[i].GPIO_Port, Pinout[i].GPIO_Pin);
						Pinout[i].mode=IC_EMU;
					}
					memset (Answer_str, 0, sizeof(Answer_str));
					strcat(Answer_str, "MEASURE CONFIGURED on ");
					strcat(Answer_str, result.params[0]);
					strcat(Answer_str, " (software)\n");
					Answer_len =strlen(Answer_str);
					Send_Answer(Answer_str, Answer_len);
					return result;
				}
			}
		}
		memset (Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "ERROR: pin ");
		strcat(Answer_str, result.params[0]);
		strcat(Answer_str, " dont exist.\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
		return result;
	}

	// MEASURE_PARAMS //
	else if (!case_insensitive_strcmp(result.command, "measure_params")){
		// Check parameters
		if (result.param_count!= 2 && result.param_count!= 3){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for MEASURE_PARAMS command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, " Need 2 or 3 parameter (avg, filter, [timeout]).\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}

		// Check avg
		uint32_t avg = string_to_uint32(result.params[0]);
		if (avg<1 || avg>100){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for MEASURE_PARAMS command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "Avg must be from 1 to 100.\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}

		// Check filter
		uint8_t filter = string_to_filter_type(result.params[1]);
		if (filter == Unknown){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for MEASURE_PARAMS command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "Filter must be: none, mean, median, min, max.\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}

		// Check timeout
		uint32_t timeout = string_to_uint32(result.params[2]);
		if ((timeout<10 || timeout >1000) && result.param_count== 3){
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "ERROR: get invalid parameters for MEASURE_PARAMS command.");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			HAL_Delay(5);
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "Timeout must be from 10 to 1000.\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}

		if (result.param_count==3){
			IC_measure_cnt = 0;
			IC_avg = avg;
			IC_filter = filter;
			IC_timeout = timeout;
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "MEASURE PARAMS: avg=");
			strcat(Answer_str, result.params[0]);
			strcat(Answer_str, ", filter=");
			strcat(Answer_str, result.params[1]);
			strcat(Answer_str, ", timeout=");
			strcat(Answer_str, result.params[2]);
			strcat(Answer_str, "\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}
		else if (result.param_count==2){
			IC_measure_cnt = 0;
			IC_avg = avg;
			IC_filter = filter;
			memset (Answer_str, 0, sizeof(Answer_str));
			strcat(Answer_str, "MEASURE PARAMS: avg=");
			strcat(Answer_str, result.params[0]);
			strcat(Answer_str, ", filter=");
			strcat(Answer_str, result.params[1]);
			strcat(Answer_str, "\n");
			Answer_len =strlen(Answer_str);
			Send_Answer(Answer_str, Answer_len);
			return result;
		}
	}

	// FREQ //
	else if (!case_insensitive_strcmp(result.command, "freq")){
		memset (Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "FREQ ");

	    char num_str[7];
	    sprintf(num_str, "%u", (unsigned int)IC_freq());
	    strcat(Answer_str, num_str);
	    strcat(Answer_str, "Hz (avg=");
	    sprintf(num_str, "%u", IC_avg);
	    strcat(Answer_str, num_str);
	    strcat(Answer_str, ", filter=");
	    strcat(Answer_str, filter_type_to_string(IC_filter));
	    strcat(Answer_str, ")\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
		return result;
	}

	// Unknown command //
	else{
		memset (Answer_str, 0, sizeof(Answer_str));
		strcat(Answer_str, "ERROR: Unknown command.\n");
		Answer_len =strlen(Answer_str);
		Send_Answer(Answer_str, Answer_len);
	}

	return result;
}

void Send_Answer(uint8_t *str, uint32_t len){
	// Send Answer to USB
	if (last_connection_item==1){
		CDC_Transmit_FS(str, len);
	}
	// Send Answer to UART
	else if (last_connection_item==2){
		HAL_UART_Transmit_IT(&huart1, str, len);
	}
//	// Send Anser to ETH
//	else if (last_connection_item==3){
//		UDP_Send_Data(str, len);
//	}
}

