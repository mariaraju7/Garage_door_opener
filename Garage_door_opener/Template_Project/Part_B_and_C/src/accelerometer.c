#include "SPI.h"
#include "SysTimer.h"
#include "accelerometer.h"

void accWrite(uint8_t addr, uint8_t val){
	// TODO access SPI_Transfer_Data
	
	uint16_t transfer = (addr & 0x3F)<<8| val;
	SPI_Transfer_Data(transfer);
}

uint8_t accRead(uint8_t addr){
	// access SPI_Transfer_Data
	
	uint16_t input = ((addr & 0x3F)|0x80) << 8;
	uint8_t read_data = SPI_Transfer_Data(input) & 0xFF; 
	
	return read_data; 
}

void initAcc(void){
	
	//set 100hz
	accWrite(0x2C, 0x0A); //  Register 0x2C—BW_RATE (Read/Write) The default value is 0x0A, which
//translates to a 100 Hz output data rate.
	
	// set full range mode 
	accWrite(0x31, 0x08); // Register 0x31- DATA_FORMAT register: The DATA_FORMAT register controls the presentation of data to
  //Register 0x32 through Register 0x37. 
	
	// enable measurement
	accWrite(0x2D, 0x08); // Register 0x2D—POWER_CTL (Read/Write)
	
	//Set the device to 100Hz output data rate, full resolution mode, and enable measurement.
	
}

void readValues(double* x, double* y, double* z){
	// TODO
	uint8_t x_0 = accRead(0x32); //from datasheet DATAX0, DATAX1.....
	uint8_t x_1 = accRead(0x33);
	uint8_t y_0 = accRead(0x34);
	uint8_t y_1 = accRead(0x35);
	uint8_t z_0 = accRead(0x36);
	uint8_t z_1 = accRead(0x37);
	
	// read values into x,y,z using accRead
	
	//16bit/8bit
	
	double x_data = (int16_t)(((uint16_t)x_1 <<8) | x_0);
	double y_data = (int16_t)(((uint16_t)y_1 <<8) | y_0);
	double z_data = (int16_t)(((uint16_t)z_1 <<8) | z_0);

	
	
	// find scaler from data sheet
	double scaler = 3.9/1000; // 3.9 mg/LSB scale factor 


	*x = x_data * scaler;
	*y = y_data * scaler;
	*z = z_data * scaler;
	
}
