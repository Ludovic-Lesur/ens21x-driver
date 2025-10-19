/*
 * ens21x.h
 *
 *  Created on: 19 oct. 2025
 *      Author: Ludo
 */

#ifndef __ENS21X_H__
#define __ENS21X_H__

#ifndef ENS21X_DRIVER_DISABLE_FLAGS_FILE
#include "ens21x_driver_flags.h"
#endif
#include "error.h"
#include "types.h"

/*** ENS21x structures ***/

/*!******************************************************************
 * \enum ENS21X_status_t
 * \brief ENS21X driver error codes.
 *******************************************************************/
typedef enum {
    // Driver errors.
    ENS21X_SUCCESS = 0,
    ENS21X_ERROR_NULL_PARAMETER,
    ENS16X_ERROR_TEMPERATURE_TIMEOUT,
    ENS16X_ERROR_HUMIDITY_TIMEOUT,
    // Low level drivers errors.
    ENS21X_ERROR_BASE_I2C = ERROR_BASE_STEP,
    ENS21X_ERROR_BASE_DELAY = (ENS21X_ERROR_BASE_I2C + ENS21X_DRIVER_I2C_ERROR_BASE_LAST),
    // Last base value.
    ENS21X_ERROR_BASE_LAST = (ENS21X_ERROR_BASE_DELAY + ENS21X_DRIVER_DELAY_ERROR_BASE_LAST)
} ENS21X_status_t;

#ifndef ENS21X_DRIVER_DISABLE

/*** ENS21x functions ***/

/*!******************************************************************
 * \fn ENS21X_status_t ENS21X_init(void)
 * \brief Init ENS21X driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
ENS21X_status_t ENS21X_init(void);

/*!******************************************************************
 * \fn ENS21X_status_t ENS21X_de_init(void)
 * \brief Release ENS21X driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
ENS21X_status_t ENS21X_de_init(void);

/*!******************************************************************
 * \fn ENS21X_status_t ENS21X_get_temperature_humidity(uint8_t i2c_address, int32_t* temperature_tenth_degrees, int32_t* humidity_percent)
 * \brief Perform temperature and humidity measurements.
 * \param[in]   i2c_address: I2C address of the sensor.
 * \param[out]  temperature_tenth_degrees: Pointer to integer that will contain the temperature in 1/10 Celsius degrees.
 * \param[out]  humidity_percent: Pointer to integer that will contain the humidity in percent.
 * \retval      Function execution status.
 *******************************************************************/
ENS21X_status_t ENS21X_get_temperature_humidity(uint8_t i2c_address, int32_t* temperature_tenth_degrees, int32_t* humidity_percent);

/*******************************************************************/
#define ENS21X_exit_error(base) { ERROR_check_exit(ens21x_status, ENS21X_SUCCESS, base) }

/*******************************************************************/
#define ENS21X_stack_error(base) { ERROR_check_stack(ens21x_status, ENS21X_SUCCESS, base) }

/*******************************************************************/
#define ENS21X_stack_exit_error(base, code) { ERROR_check_stack_exit(ens21x_status, ENS21X_SUCCESS, base, code) }

#endif /* ENS21X_DRIVER_DISABLE */

#endif /* __ENS21X_H__ */
