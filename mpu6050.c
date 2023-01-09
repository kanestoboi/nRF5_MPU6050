
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_drv_twi.h"
#include "mpu6050.h"

bool mpu6050_register_write(MPU6050 *sensor, uint8_t register_address, uint8_t value)
{
    ret_code_t err_code;
    uint8_t tx_buf[MPU6050_ADDRESS_LEN+1];
	
    //Write the register address and data into transmit buffer
    tx_buf[0] = register_address;
    tx_buf[1] = value;

    //Set the flag to false to show the transmission is not yet completed
    sensor->mTransferDone = false;
    
    //Transmit the data over TWI Bus
    err_code = nrf_drv_twi_tx(sensor->mHandle, MPU6050_ADDRESS, tx_buf, MPU6050_ADDRESS_LEN+1, false);
    
    //Wait until the transmission of the data is finished
    while (sensor->mTransferDone == false) {}

    // if there is no error then return true else return false
    if (NRF_SUCCESS != err_code)
    {
        return false;
    }
    
    return true;	
}

bool mpu6050_register_read(MPU6050 *sensor, uint8_t register_address, uint8_t * destination, uint8_t number_of_bytes)
{
    ret_code_t err_code;

    //Set the flag to false to show the receiving is not yet completed
    sensor->mTransferDone = false;
    
    // Send the Register address where we want to write the data
    err_code = nrf_drv_twi_tx(sensor->mHandle, MPU6050_ADDRESS, &register_address, 1, true);
	  
    //Wait for the transmission to get completed
    while (sensor->mTransferDone == false){}
    
    // If transmission was not successful, exit the function with false as return value
    if (NRF_SUCCESS != err_code)
    {
        return false;
    }

    //set the flag again so that we can read data from the MPU6050's internal register
    sensor->mTransferDone = false;
	  
    // Receive the data from the MPU6050
    err_code = nrf_drv_twi_rx(sensor->mHandle, MPU6050_ADDRESS, destination, number_of_bytes);
		
    //wait until the transmission is completed
    while (sensor->mTransferDone == false){}
	
    // if data was successfully read, return true else return false
    if (NRF_SUCCESS != err_code)
    {
        return false;
    }
    
    return true;
}

bool mpu6050_verify_product_id(MPU6050 *sensor)
{
  uint8_t readId; // create a variable to hold the who am i value

  if (!mpu6050_register_read(sensor, MPU6050_WHO_AM_I_REG, &readId, 1))
  {
    return false;
  }
  
  if (readId != MPU6050_WHO_AM_I)
  {
    return false;
  }

  return true;
}

/*
  Function to initialize the MPU6050
*/ 
bool mpu6050_init(MPU6050 *sensor, const nrf_drv_twi_t *m_twi)
{   

  sensor->mHandle = m_twi;
  sensor->mTransferDone = false;
  sensor->initialised = false;

  //Check the id to confirm that we are communicating with the right device
  if (mpu6050_verify_product_id(sensor) == false)
  {
    return false;
  }

  sensor->initialised = true;

  return true;
}


/*
  A Function to read accelerometer's values from the internal registers of MPU6050
*/ 
bool mpu6050_ReadAcc(MPU6050 *sensor, int16_t *pACC_X , int16_t *pACC_Y , int16_t *pACC_Z )
{
  uint8_t buf[6];
  bool ret = false;

  if(mpu6050_register_read(sensor, MPU6050_ACC_OUT, buf, 6) == true)
  {
    
    *pACC_X = (buf[0] << 8) | buf[1];

    *pACC_Y= (buf[2] << 8) | buf[3];

    *pACC_Z = (buf[4] << 8) | buf[5];
		
    ret = true;
  }
  
  
  return ret;
}

