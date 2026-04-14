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
	SWCLK = 3,
	SWDIO = 4,
	OTG_FS_ID = 5,
	OTG_FS_DM = 6,
	USART2_RX = 7,
	USART2_TX = 8,
	SPI2_RESET = 9,
	SPI2_NSS = 10,
	SPI2_SCK = 11,
	SPI2_MISO = 12,
	SPI2_MOSI = 13,
	PWM = 14,
	PWM_EMU =15,
	IC = 16,
	IC_EMU = 17,
	CS_I2C = 18,
	OTG_FS_PowerSwitchOn = 19,
	PDM_OUT = 20,
	B1 = 21,
	LD4 = 22,
	LD5 = 23,
	LD6 = 24,
	LD3 = 25,
	SPI1_SCK = 26,
	SPI1_MISO = 27,
	SPI1_MOSI = 28,
	BOOT1 = 29,
	CLK_IN = 30, 
	I2S3_MCK = 31, 
	I2S3_SCK = 32,
	I2S3_SD = 33,
	VBUS_FS = 34,
	OTG_FS_OverCurrent = 35,
	Audio_RST = 36,
	Audio_SCL = 37, 
	Audio_SDA = 38,
	OTG_FS_DP = 39,
	SWO = 40,
	MEMS_INT2 = 41,
	I2S3_WS = 42
};

typedef struct Pinout_struct{
	char *pin_name;
	TIM_HandleTypeDef *htim;
	uint32_t tim_channel;
	GPIO_TypeDef *GPIO_Port;
	uint32_t GPIO_Pin;
	enum Pin_Mode mode;
} Pinout_struct;

struct Pinout_struct Pinout[84]={
	{"PE2",0, 0, GPIOE, GPIO_PIN_2, None},
	{"PE3",0, 0, GPIOE, GPIO_PIN_3, CS_I2C},
	{"PE4",0, 0, GPIOE, GPIO_PIN_4, None},
	{"PE5", &htim9, TIM_CHANNEL_1, GPIOE, GPIO_PIN_5, None},
	{"PE6", &htim9, TIM_CHANNEL_2, GPIOE, GPIO_PIN_6, None},
	{"PC13", 0, 0, GPIOC, GPIO_PIN_13, None},
	{"PC14", 0, 0, GPIOC, GPIO_PIN_14, RCC_OSC_IN},
	{"PC15", 0, 0, GPIOC, GPIO_PIN_15, RCC_OSC_OUT},
	{"PH0", 0, 0, GPIOH, GPIO_PIN_0, RCC_OSC_IN},
	{"PH1", 0, 0, GPIOH, GPIO_PIN_1, RCC_OSC_OUT},
	{"PC0", 0, 0, GPIOC, GPIO_PIN_0, OTG_FS_PowerSwitchOn},
	{"PC1", 0, 0, GPIOC, GPIO_PIN_1, None},
	{"PC2", 0, 0, GPIOC, GPIO_PIN_2, SPI2_MISO},
	{"PC3", 0, 0, GPIOC, GPIO_PIN_3, PDM_OUT},
	{"PA0", 0, 0, GPIOA, GPIO_PIN_0, B1},
	{"PA1", &htim2, TIM_CHANNEL_2, GPIOA, GPIO_PIN_1, None},
	{"PA2", &htim2, TIM_CHANNEL_3, GPIOA, GPIO_PIN_2, USART2_TX},
	{"PA3", &htim2, TIM_CHANNEL_4, GPIOA, GPIO_PIN_3, USART2_RX},
	{"PA4", 0, 0, GPIOA, GPIO_PIN_4, I2S3_WS},
	{"PA5", &htim2, TIM_CHANNEL_1, GPIOA, GPIO_PIN_5, SPI1_SCK},
	{"PA6", &htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_6, SPI1_MISO},
	{"PA7", &htim3, TIM_CHANNEL_2, GPIOA, GPIO_PIN_7, SPI1_MOSI},
	{"PC4", 0, 0, GPIOC, GPIO_PIN_4, None},
	{"PC5", 0, 0, GPIOC, GPIO_PIN_5, None},
	{"PB0", &htim3, TIM_CHANNEL_3, GPIOB, GPIO_PIN_0, None},
	{"PB1", &htim3, TIM_CHANNEL_4, GPIOB, GPIO_PIN_1, None},
	{"PB2", 0, 0, GPIOB, GPIO_PIN_2, BOOT1},
	{"PE7", 0, 0, GPIOE, GPIO_PIN_7, None},
	{"PE8", 0, 0, GPIOE, GPIO_PIN_8, None},
	{"PE9", &htim1, TIM_CHANNEL_1, GPIOE, GPIO_PIN_9, None},
	{"PE10", 0, 0, GPIOE, GPIO_PIN_10, None},
	{"PE11", &htim1, TIM_CHANNEL_2, GPIOE, GPIO_PIN_11, None},
	{"PE12", 0, 0, GPIOE, GPIO_PIN_12, None},
	{"PE13", &htim1, TIM_CHANNEL_3, GPIOE, GPIO_PIN_13, None},
	{"PE14", &htim1, TIM_CHANNEL_4, GPIOE, GPIO_PIN_14, None},
	{"PE15", 0, 0, GPIOE, GPIO_PIN_15, None},
	{"PB10", &htim2, TIM_CHANNEL_3, GPIOB, GPIO_PIN_10, CLK_IN},
	{"PB11", &htim2, TIM_CHANNEL_4, GPIOB, GPIO_PIN_11, None},
	{"PB12", 0, 0, GPIOB, GPIO_PIN_12, SPI2_RESET},
	{"PB13", 0, 0, GPIOB, GPIO_PIN_13, SPI2_SCK},
	{"PB14", &htim12, TIM_CHANNEL_1, GPIOB, GPIO_PIN_14, SPI2_NSS},
	{"PB15", &htim12, TIM_CHANNEL_2, GPIOB, GPIO_PIN_15, SPI2_MOSI},
	{"PD8", 0, 0, GPIOD, GPIO_PIN_8, None},
	{"PD9", 0, 0, GPIOD, GPIO_PIN_9, None},
	{"PD10", 0, 0, GPIOD, GPIO_PIN_10, None},
	{"PD11", 0, 0, GPIOD, GPIO_PIN_11, None},
	{"PD12", &htim4, TIM_CHANNEL_1, GPIOD, GPIO_PIN_12, LD4},
	{"PD13", &htim4, TIM_CHANNEL_2, GPIOD, GPIO_PIN_13, LD3},
	{"PD14", &htim4, TIM_CHANNEL_3, GPIOD, GPIO_PIN_14, LD5},
	{"PD15", &htim4, TIM_CHANNEL_4, GPIOD, GPIO_PIN_15, LD6},
	{"PC6", &htim3, TIM_CHANNEL_1, GPIOC, GPIO_PIN_6, None},
	{"PC7", &htim3, TIM_CHANNEL_2, GPIOC, GPIO_PIN_7, I2S3_MCK},
	{"PC8", &htim3, TIM_CHANNEL_3, GPIOC, GPIO_PIN_8, None},
	{"PC9", &htim3, TIM_CHANNEL_4, GPIOC, GPIO_PIN_9, None},
	{"PA8", &htim1, TIM_CHANNEL_1, GPIOA, GPIO_PIN_8, None},
	{"PA9", &htim1, TIM_CHANNEL_2, GPIOA, GPIO_PIN_9, VBUS_FS},
	{"PA10", &htim1, TIM_CHANNEL_3, GPIOA, GPIO_PIN_10, OTG_FS_ID},
	{"PA11", &htim1, TIM_CHANNEL_4, GPIOA, GPIO_PIN_11, OTG_FS_DM},
	{"PA12", 0, 0, GPIOA, GPIO_PIN_12, OTG_FS_DP},
	{"PA13", 0, 0, GPIOA, GPIO_PIN_13, SWDIO},
	{"PA14", 0, 0, GPIOA, GPIO_PIN_14, SWCLK},
	{"PA15", &htim2, TIM_CHANNEL_1, GPIOA, GPIO_PIN_15, None},
	{"PC10", 0, 0, GPIOC, GPIO_PIN_10, I2S3_SCK},
	{"PC11", 0, 0, GPIOC, GPIO_PIN_11, None},
	{"PC12", 0, 0, GPIOC, GPIO_PIN_12, I2S3_SD},
	{"PD0", 0, 0, GPIOD, GPIO_PIN_0, None},
	{"PD1", 0, 0, GPIOD, GPIO_PIN_1, None},
	{"PD2", 0, 0, GPIOD, GPIO_PIN_2, None},
	{"PD3", 0, 0, GPIOD, GPIO_PIN_3, None},
	{"PD4", 0, 0, GPIOD, GPIO_PIN_4, Audio_RST},
	{"PD5", 0, 0, GPIOD, GPIO_PIN_5, OTG_FS_OverCurrent},
	{"PD6", 0, 0, GPIOD, GPIO_PIN_6, None},
	{"PD7", 0, 0, GPIOD, GPIO_PIN_7, None},
	{"PB3", &htim2, TIM_CHANNEL_2, GPIOB, GPIO_PIN_3, SWO},
	{"PB4", &htim3, TIM_CHANNEL_1, GPIOB, GPIO_PIN_4, None},
	{"PB5", &htim3, TIM_CHANNEL_2, GPIOB, GPIO_PIN_5, None},
	{"PB6", &htim4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_6, Audio_SCL},
	{"PB7", &htim4, TIM_CHANNEL_2, GPIOB, GPIO_PIN_7, None},
	{"PB8", &htim4, TIM_CHANNEL_3, GPIOB, GPIO_PIN_8, None},
	{"PB9", &htim4, TIM_CHANNEL_4, GPIOB, GPIO_PIN_9, Audio_SDA},
	{"PE0", 0, 0, GPIOE, GPIO_PIN_0, None},
	{"PE1", 0, 0, GPIOE, GPIO_PIN_1, MEMS_INT2}
};

const char* pin_mode_to_string(enum Pin_Mode mode) {
    switch(mode) {
        case None: return "None";
        case RCC_OSC_IN: return "RCC_OSC_IN";
        case RCC_OSC_OUT: return "RCC_OSC_OUT";
        case SWCLK: return "SWCLK";
        case SWDIO: return "SWDIO";
        case OTG_FS_ID: return "OTG_FS_ID";
        case OTG_FS_DM: return "OTG_FS_DM";
        case USART2_RX: return "USART2_RX";
        case USART2_TX: return "USART2_TX";
        case SPI2_RESET: return "SPI1_RESET";
        case SPI2_NSS: return "SPI2_NSS";
        case SPI2_SCK: return "SPI2_SCK";
        case SPI2_MISO: return "SPI2_MISO";
        case SPI2_MOSI: return "SPI2_MOSI";
        case PWM: return "PWM";
        case PWM_EMU: return "PWM_EMU";
        case IC: return "IC";
        case IC_EMU: return "IC_EMU";
		case CS_I2C: return "CS_I2C";
		case OTG_FS_PowerSwitchOn: return "OTG_FS_PowerSwitchOn";
		case PDM_OUT: return "PDM_OUT";
		case B1: return "B1";
		case LD4: return "LD4";
		case LD5: return "LD5";
		case LD6: return "LD6";
		case LD3: return "LD3";
		case SPI1_SCK: return "SPI1_SCK";
		case SPI1_MISO: return "SPI1_MISO";
		case SPI1_MOSI: return "SPI1_MOSI";
		case BOOT1: return "BOOT1";
		case CLK_IN: return "CLK_IN";
		case I2S3_MCK: return "I2S3_MCK";
		case I2S3_SCK: return "I2S3_SCK";
		case I2S3_SD: return "I2S3_SD";
		case VBUS_FS: return "VBUS_FS";
		case OTG_FS_OverCurrent: return "OTG_FS_OverCurrent";
		case Audio_RST: return "Audio_RST";
		case Audio_SCL: return "Audio_SCL";
		case Audio_SDA: return "Audio_SDA";
		case OTG_FS_DP: return "OTG_FS_DP";
		case SWO: return "SWO";
		case MEMS_INT2: return "MEMS_INT2";
		case I2S3_WS: return "I2S3_WS";
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
		HAL_UART_Transmit_IT(&huart2, str, len);
	}
	// Send Anser to ETH
	else if (last_connection_item==3){
		UDP_Send_Data(str, len);
	}
}

