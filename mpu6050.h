#ifndef MPU6050_H__
#define MPU6050_H__


//MPU6050 Registers addresses, see datasheet for more info and each register's function


#define MPU6050_ADDRESS_LEN  1         //MPU6050
#define MPU6050_ADDRESS     (0xD0>>1)  //MPU6050 Device Address
#define MPU6050_WHO_AM_I     0x68U     //MPU6050 ID


#define MPU6050_GYRO_OUT        0x43
#define MPU6050_ACC_OUT         0x3B

#define ADDRESS_WHO_AM_I          (0x75U) //  WHO_AM_I register identifies the device. Expected value is 0x68.
#define ADDRESS_SIGNAL_PATH_RESET (0x68U) // 

#define MPU6050_GYRO_OUT        0x43
#define MPU6050_ACC_OUT         0x3B

//MPU6050 Registers addresses, see datasheet for more info and each register's function
#define MPU6050_SELF_TEST_X_REG		0x0D	
#define MPU6050_SELF_TEST_Y_REG		0x0E	
#define MPU6050_SELF_TEST_Z_REG		0x0F	
#define MPU6050_SELF_TEST_A_REG		0x10	
#define MPU6050_SAMPLE_RATE_REG		0x19	
#define MPU6050_CONFIG_REG              0x1A	
#define MPU6050_GYRO_CONFIG_REG		0x1B	
#define MPU6050_ACCEL_CONFIG_REG        0x1C	
#define MPU6050_FIFO_EN_REG             0x23	
#define MPU6050_I2C_MST_CTRL_REG	0x24	
#define MPU6050_I2C_SLV0_ADDR_REG       0x25	
#define MPU6050_I2C_SLV0_REG		0x26	
#define MPU6050_I2C_SLV0_CTRL_REG       0x27	
#define MPU6050_I2C_SLV1_ADDR_REG       0x28	
#define MPU6050_I2C_SLV1_REG		0x29	
#define MPU6050_I2C_SLV1_CTRL_REG       0x2A	
#define MPU6050_I2C_SLV2_ADDR_REG       0x2B	
#define MPU6050_I2C_SLV2_REG		0x2C	
#define MPU6050_I2C_SLV2_CTRL_REG       0x2D	
#define MPU6050_I2C_SLV3_ADDR_REG       0x2E	
#define MPU6050_I2C_SLV3_REG		0x2F	
#define MPU6050_I2C_SLV3_CTRL_REG       0x30	
#define MPU6050_I2C_SLV4_ADDR_REG       0x31	
#define MPU6050_I2C_SLV4_REG		0x32	
#define MPU6050_I2C_SLV4_DO_REG		0x33	
#define MPU6050_I2C_SLV4_CTRL_REG       0x34	
#define MPU6050_I2C_SLV4_DI_REG		0x35	
#define MPU6050_I2C_MST_STA_REG		0x36	
#define MPU6050_INT_BP_CFG_REG		0x37	
#define MPU6050_INT_EN_REG		0x38	
#define MPU6050_INT_STA_REG		0x3A	
#define MPU6050_I2C_MST_DELAY_REG       0x67	
#define MPU6050_SIG_PATH_RST_REG	0x68	
#define MPU6050_USER_CTRL_REG		0x6A	
#define MPU6050_PWR_MGMT1_REG		0x6B	
#define MPU6050_PWR_MGMT2_REG		0x6C	
#define MPU6050_FIFO_COUNTH_REG		0x72	
#define MPU6050_FIFO_COUNTL_REG		0x73	
#define MPU6050_FIFO_RW_REG		0x74	
#define MPU6050_WHO_AM_I_REG		0x75

typedef struct MPU6050 
{
  const nrf_drv_twi_t *mHandle;

  bool mTransferDone;
} MPU6050;

bool mpu6050_init(MPU6050 *sensor, const nrf_drv_twi_t *m_twi);

/**
  @brief Function for writing a MPU6050 register contents over TWI.
  @param[in]  register_address Register address to start writing to
  @param[in] value Value to write to register
  @retval true Register write succeeded
  @retval false Register write failed
*/
bool mpu6050_register_write(MPU6050 *sensor, uint8_t register_address, const uint8_t value);

/**
  @brief Function for reading MPU6050 register contents over TWI.
  Reads one or more consecutive registers.
  @param[in]  register_address Register address to start reading from
  @param[in]  number_of_bytes Number of bytes to read
  @param[out] destination Pointer to a data buffer where read data will be stored
  @retval true Register read succeeded
  @retval false Register read failed
*/
bool mpu6050_register_read(MPU6050 *sensor, uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes);

/**
  @brief Function for reading and verifying Analog Devices ID.
  @retval true ID is what was expected
  @retval false ID was not what was expected
*/  
bool mpu6050_verify_product_id(MPU6050 *sensor);
bool mpu6050_verify_mems_id(MPU6050 *sensor);
bool mpu6050_verify_part_id(MPU6050 *sensor);

bool mpu6050_ReadAcc(MPU6050 *sensor, int16_t *pACC_X , int16_t *pACC_Y , int16_t *pACC_Z );
bool mpu6050_ReadTemp(MPU6050 *sensor, uint16_t *pTemp );
bool mpu6050_DataReady(MPU6050 *sensor);

#endif


