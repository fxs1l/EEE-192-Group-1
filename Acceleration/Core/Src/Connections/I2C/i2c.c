#include "i2c.h"

void I2C_Config(){
    // Enable the I2C CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1<<21);  // enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1);  // Enable GPIOB CLOCK


	// Configure the I2C PINs for ALternate Functions
	GPIOB->MODER |= (2<<16) | (2<<18);  // Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9
	GPIOB->OTYPER |= (1<<8) | (1<<9);  //  Bit8=1, Bit9=1  output open drain
	GPIOB->OSPEEDR |= (3<<16) | (3<<18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9
	GPIOB->PUPDR |= (1<<16) | (1<<18);  // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9
	GPIOB->AFR[1] |= (4<<0) | (4<<4);  // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9


	// Reset the I2C
	I2C1->CR1 |= (1<<15);
	I2C1->CR1 &= ~(1<<15);

	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
//	I2C1->CR2 |= (18<<0);  // PCLK1 FREQUENCY in MHz
	I2C1->CR2 |= (36<<0);  // PCLK1 FREQUENCY in MHz

	// Configure the clock control registers
	I2C1->CCR = 180<<0;  // check calculation in PDF

	// Configure the rise time register
	I2C1->TRISE = 37;  // check PDF again

	// Program the I2C_CR1 register to enable the peripheral
	I2C1->CR1 |= (1<<0);  // Enable I2C
}

void I2C_Write (uint8_t data) {
	/**** STEPS FOLLOWED  ************
	1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
	2. Send the DATA to the DR Register
	3. Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
	*/
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set
}

void I2C_Address (uint8_t Address) {
/**** STEPS FOLLOWED  ************
1. Send the Slave Address to the DR Register
2. Wait for the ADDR (bit 1 in SR1) to set. This indicates the end of address transmission
3. clear the ADDR by reading the SR1 and SR2
*/
	I2C1->DR = Address;  //  send the address
	while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
	uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit
}

void I2C_Start (void) {
	/**** STEPS FOLLOWED  ************
	1. Send the START condition
	2. Wait for the SB ( Bit 0 in SR1) to set. This indicates that the start condition is generated
	*/

	I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= (1<<8);  // Generate START
	while (!(I2C1->SR1 & (1<<0)));  // Wait for SB bit to set
}

void I2C_Stop (void) {
	I2C1->CR1 |= (1<<9);  // Stop I2C
}

void I2C_WriteMulti (uint8_t *data, uint8_t size) {
	/**** STEPS FOLLOWED  ************
	1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
	2. Keep Sending DATA to the DR Register after performing the check if the TXE bit is set
	3. Once the DATA transfer is complete, Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
	*/
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	while (size)
	{
		while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
		I2C1->DR = (uint32_t )*data++;  // send data
		size--;
	}

	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF to set
}

void I2C_Read (uint8_t Address, uint8_t *buffer, uint8_t size) {
	/**** STEPS FOLLOWED  ************
	1. If only 1 BYTE needs to be Read
		a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
		b) the Acknowledge disable is made during EV6 (before ADDR flag is cleared) and the STOP condition generation is made after EV6
		c) Wait for the RXNE (Receive Buffer not Empty) bit to set
		d) Read the data from the DR

	2. If Multiple BYTES needs to be read
	  a) Write the slave Address, and wait for the ADDR bit (bit 1 in SR1) to be set
		b) Clear the ADDR bit by reading the SR1 and SR2 Registers
		c) Wait for the RXNE (Receive buffer not empty) bit to set
		d) Read the data from the DR
		e) Generate the Acknowlegment by settint the ACK (bit 10 in SR1)
		f) To generate the nonacknowledge pulse after the last received data byte, the ACK bit must be cleared just after reading the
			 second last data byte (after second last RxNE event)
		g) In order to generate the Stop/Restart condition, software must set the STOP/START bit
		   after reading the second last data byte (after the second last RxNE event)
	 */

	int remaining = size;

	/**** STEP 1 ****/
	if (size == 1)
	{
		/**** STEP 1-a ****/
		I2C1->DR = Address;  //  send the address
		while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set

		/**** STEP 1-b ****/
		I2C1->CR1 &= ~(1<<10);  // clear the ACK bit
		uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit.... EV6 condition
		I2C1->CR1 |= (1<<9);  // Stop I2C

		/**** STEP 1-c ****/
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set

		/**** STEP 1-d ****/
		buffer[size-remaining] = I2C1->DR;  // Read the data from the DATA REGISTER

	}

	/**** STEP 2 ****/
	else
	{
		/**** STEP 2-a ****/
		I2C1->DR = Address;  //  send the address
		while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set

		/**** STEP 2-b ****/
		uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit

		while (remaining>2)
		{
			/**** STEP 2-c ****/
			while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set

			/**** STEP 2-d ****/
			buffer[size-remaining] = I2C1->DR;  // copy the data into the buffer

			/**** STEP 2-e ****/
			I2C1->CR1 |= 1<<10;  // Set the ACK bit to Acknowledge the data received

			remaining--;
		}

		// Read the SECOND LAST BYTE
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = I2C1->DR;

		/**** STEP 2-f ****/
		I2C1->CR1 &= ~(1<<10);  // clear the ACK bit

		/**** STEP 2-g ****/
		I2C1->CR1 |= (1<<9);  // Stop I2C

		remaining--;

		// Read the Last BYTE
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = I2C1->DR;  // copy the data into the buffer
	}

}
/*

// Function to initialize GPIO for I2C
void I2C_GPIO_Init(void) {
    // Enable GPIOB clock
	RCC->APB1ENR |= (1 << 21);
    RCC->AHB1ENR |= (1 << 1);

    // Configure GPIOB pins for I2C (PB6 -> SCL, PB7 -> SDA)
    // PB6 and PB7 AFR mode
    GPIOB->MODER |= (1 << 13);
    GPIOB->MODER &= ~(1 << 12);
    GPIOB->MODER |= (1 << 15);
    GPIOB->MODER &= ~(1 << 14);
    // PB6 and PB7 open-drain
	GPIOB->OTYPER |= (1 << 7);
	GPIOB->OTYPER |= (1 << 6);
    // PB6 and PB7 high speed
    GPIOB->OSPEEDR |= (1 << 13);
	GPIOB->OSPEEDR |= (1 << 12);
	GPIOB->OSPEEDR |= (1 << 15);
	GPIOB->OSPEEDR |= (1 << 14);
	// Pull-up
	GPIOB->PUPDR &= ~(1 << 15);
	GPIOB->PUPDR |= (1 << 14);
	GPIOB->PUPDR &= ~(1 << 13);
	GPIOB->PUPDR |= (1 << 12);
	// According to AF mapping table, AF04 corresponds to I2C1_SDA and I2C1_SCL
	// PB6
	GPIOB->AFR[0] &= ~(1 << 31);
	GPIOB->AFR[0] |= (1 << 30);
	GPIOB->AFR[0] &= ~(1 << 29);
	GPIOB->AFR[0] &= ~(1 << 28);
	// PB7
	GPIOB->AFR[0] &= ~(1 << 27);
    GPIOB->AFR[0] |= (1 << 26);
    GPIOB->AFR[0] &= ~(1 << 25);
    GPIOB->AFR[0] &= ~(1 << 24);

    //	 PB3 input mode
	// GPIOB->MODER &= ~(1 << 6);
	// GPIOB->MODER &= ~(1 << 7);
}

// Function to initialize I2C peripheral
void I2C_Init(void) {
    // Enable I2C1 clock
    RCC->APB1ENR |= (1 << 21);

    // Configure I2C1
    I2C1->CR1 = 0;
    I2C1->CR2 = I2C_PERIPHERAL_CLOCK_FREQ;
    I2C1->CCR = I2C_CLOCK_CONTROL_REGISTER;
    I2C1->TRISE = I2C_MAX_RISE_TIME;
    I2C1->CR1 |= (1 << 0);

}

// Helper function to run I2C commands
void I2C_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
    // Start condition
    I2C1->CR1 |= (1 << 8);
    while (!(I2C1->SR1 & (1 << 0)));

    // Send device address
    I2C1->DR = dev_addr << 1;
    while (!(I2C1->SR1 & (1 << 1)));
    (void)I2C1->SR2; // Clear ADDR flag

    // Send register address
    I2C1->DR = reg_addr;
    while (!(I2C1->SR1 & (1 << 7)));

    // Send data
    I2C1->DR = data;
    while (!(I2C1->SR1 & (1 << 7)));

    // Stop condition
    I2C1->CR1 |= (1 << 9);
}


void I2C_Read(uint8_t slaveAddress, uint8_t regAddress, uint8_t *data, uint32_t numBytes){
	//uint32_t timeout = I2C_TIMEOUT_MS * (SystemCoreClock / 1000);
    // Generate start condition
    I2C1->CR1 |= I2C_CR1_START;

    // Wait until start condition generated
    while (!(I2C1->SR1 & I2C_SR1_SB)) {
//        if (--timeout == 0) return; // Return if timeout
    }

    // Send slave address with write bit
    I2C1->DR = (slaveAddress << 1) & ~(1 << 0);

    // Wait until address sent
    while (!(I2C1->SR1 & I2C_SR1_ADDR)) {
//        if (--timeout == 0) return; // Return if timeout
    }

    // Clear ADDR flag
    (void)I2C1->SR2;

    // Send register address
    I2C1->DR = regAddress;

    // Wait until data register empty
    while (!(I2C1->SR1 & I2C_SR1_TXE)) {
//        if (--timeout == 0) return; // Return if timeout
    }

    // Generate repeated start condition
    I2C1->CR1 |= I2C_CR1_START;

    // Wait until start condition generated
    while (!(I2C1->SR1 & I2C_SR1_SB)) {
//        if (--timeout == 0) return; // Return if timeout
    }

    // Send slave address with read bit
    I2C1->DR = (slaveAddress << 1) | 1;

    // Wait until address sent
    while (!(I2C1->SR1 & I2C_SR1_ADDR)) {
//        if (--timeout == 0) return; // Return if timeout
    }

    // Clear ADDR flag
    (void)I2C1->SR2;

    // Read data
    for (uint32_t i = 0; i < numBytes; ++i) {
        // Wait until data available
        while (!(I2C1->SR1 & I2C_SR1_RXNE)) {
//            if (--timeout == 0) return; // Return if timeout
        }

        // Read data
        data[i] = I2C1->DR;
    }

    // Generate stop condition
    I2C1->CR1 |= I2C_CR1_STOP;
}*/
