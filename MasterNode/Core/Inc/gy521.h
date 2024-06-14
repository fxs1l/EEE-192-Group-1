#include "i2c.h"
#include "stm32f4xx.h"

void GY521_Read_Gyro(void);
void GY521_Read_Accel(void);

// GY52 Register Addresses
// taken from https://embeddedthere.com/stm32-i2c-protocol-with-hal-code-example/
#define SMPLRT_DIV_REG          0x19
#define GYRO_CONFIG_REG         0x1B
#define ACCEL_CONFIG_REG        0x1C
#define ACCEL_X_OUT_H_REG       0x3B
#define TEMP_OUT_H_REG          0x41
#define GYRO_X_OUT_H_REG        0x43
#define PWR_MGMT_1_REG          0x6B
#define WHO_AM_I_REG            0x75
#define GY521_ADDR              0xD0

extern float Ax, Ay, Az, Gx, Gy, Gz;

//int I2C_PERIPHERAL_CLOCK_FREQ = 42; // Set peripheral clock frequency (42MHz)
//const int I2C_CLOCK_CONTROL_REGISTER = 210;
//const int I2C_MAX_RISE_TIME = 43;

void GY521_Init(void);

