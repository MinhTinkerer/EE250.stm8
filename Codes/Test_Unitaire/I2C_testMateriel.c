#include "stm8s.h"
#include "stm8s_i2c.h"

main() {
	I2C_DeInit();
	I2C_Init(I2C_MAX_STANDARD_FREQ, 0x00F0, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, I2C_MAX_INPUT_FREQ);
	
	I2C_GenerateSTART(ENABLE);


	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_Send7bitAddress(0x0F13, I2C_DIRECTION_TX);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(0x02);


	I2C_GenerateSTOP(ENABLE);

	TODO_Close();
}