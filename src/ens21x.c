/*
 * ens21x.c
 *
 *  Created on: 19 oct. 2025
 *      Author: Ludo
 */

#include "ens21x.h"

#ifndef ENS21X_DRIVER_DISABLE_FLAGS_FILE
#include "ens21x_driver_flags.h"
#endif
#include "ens21x_hw.h"
#include "types.h"

#ifndef ENS21X_DRIVER_DISABLE

/*** ENS21x local macros ***/

#define ENS21X_MEASURE_COMMAND_BUFFER_SIZE  2
#define ENS21X_MEASURE_DATA_BUFFER_SIZE     6

#define ENS21X_CONVERSION_TIME_MS           150

#define ENS21X_TEMPERATURE_SLOPE            64
#define ENS21X_TEMPERATURE_OFFSET           174816
#define ENS21X_TEMPERATURE_FACTOR           10

#define ENS21X_HUMIDITY_SLOPE               512

/*** ENS21x local structures ***/

/*******************************************************************/
typedef enum {
    ENS21X_REGISTER_PART_ID = 0x00,
    ENS21X_REGISTER_DIE_REV = 0x02,
    ENS21X_REGISTER_UID = 0x04,
    ENS21X_REGISTER_SYS_CTRL = 0x10,
    ENS21X_REGISTER_SYS_STAT = 0x11,
    ENS21X_REGISTER_SENS_RUN = 0x21,
    ENS21X_REGISTER_SENS_START = 0x22,
    ENS21X_REGISTER_SENS_STOP = 0x23,
    ENS21X_REGISTER_SENS_STAT = 0x24,
    ENS21X_REGISTER_T_VAL = 0x30,
    ENS21X_REGISTER_H_VAL = 0x33,
    ENS21X_REGISTER_LAST
} ENS21X_register_t;

/*** ENS21x functions ***/

/*******************************************************************/
ENS21X_status_t ENS21X_init(void) {
    // Local variables.
    ENS21X_status_t status = ENS21X_SUCCESS;
    // Init hardware interface.
    status = ENS21X_HW_init();
    return status;
}

/*******************************************************************/
ENS21X_status_t ENS21X_de_init(void) {
    // Local variables.
    ENS21X_status_t status = ENS21X_SUCCESS;
    // Release hardware interface.
    status = ENS21X_HW_de_init();
    return status;
}

/*******************************************************************/
ENS21X_status_t ENS21X_get_temperature_humidity(uint8_t i2c_address, int32_t* temperature_tenth_degrees, int32_t* humidity_percent) {
    // Local variables.
    ENS21X_status_t status = ENS21X_SUCCESS;
    uint8_t measure_command[ENS21X_MEASURE_COMMAND_BUFFER_SIZE] = { ENS21X_REGISTER_SENS_START, 0x03 };
    uint8_t measure_buf[ENS21X_MEASURE_DATA_BUFFER_SIZE] = { 0x00 };
    uint8_t data_register_address = ENS21X_REGISTER_T_VAL;
    int32_t data_16bits = 0;
    // Check parameters.
    if ((temperature_tenth_degrees == NULL) || (humidity_percent == NULL)) {
        status = ENS21X_ERROR_NULL_PARAMETER;
        goto errors;
    }
    // Trigger high repeatability measurement with clock stretching disabled.
    status = ENS21X_HW_i2c_write(i2c_address, measure_command, ENS21X_MEASURE_COMMAND_BUFFER_SIZE, 1);
    if (status != ENS21X_SUCCESS) goto errors;
    // Wait for conversion to complete (maximum 130ms).
    status = ENS21X_HW_delay_milliseconds(ENS21X_CONVERSION_TIME_MS);
    if (status != ENS21X_SUCCESS) goto errors;
    // Read data.
    status = ENS21X_HW_i2c_write(i2c_address, &data_register_address, 1, 0);
    if (status != ENS21X_SUCCESS) goto errors;
    status = ENS21X_HW_i2c_read(i2c_address, measure_buf, ENS21X_MEASURE_DATA_BUFFER_SIZE);
    if (status != ENS21X_SUCCESS) goto errors;
    // Check temperature validity flag.
    if ((measure_buf[2] & 0x01) == 0) {
        status = ENS16X_ERROR_TEMPERATURE_TIMEOUT;
        goto errors;
    }
    // Compute temperature.
    data_16bits = (int32_t) ((measure_buf[1] << 8) + measure_buf[0]);
    (*temperature_tenth_degrees) = (((data_16bits * ENS21X_TEMPERATURE_FACTOR) - ENS21X_TEMPERATURE_OFFSET) / (ENS21X_TEMPERATURE_SLOPE));
    // Check humidity validity flag.
    if ((measure_buf[5] & 0x01) == 0) {
        status = ENS16X_ERROR_HUMIDITY_TIMEOUT;
        goto errors;
    }
    // Compute humidity.
    data_16bits = (int32_t) ((measure_buf[4] << 8) + measure_buf[3]);
    (*humidity_percent) = (data_16bits / ENS21X_HUMIDITY_SLOPE);
errors:
    return status;
}

#endif /* ENS21X_DRIVER_DISABLE */
