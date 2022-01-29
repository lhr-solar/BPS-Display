#ifndef CAN_BUS_H
#define CAN_BUS_H

// CAN Drivers

/**
 * Initialize and configure a singular CANBus
 * Currently set up for CAN2
 */

#include "stm32f4xx.h"

/**
 * Filter and RX_FIFO configurations
 * Set FILTER_MASK_ID_LOW/HIGH to 0 to recieve all can messages
 */
#define CAN_RX_FIFO_NUMBER      CAN_RX_FIFO0
#define FILTER_BANK             14          /* 0 - 13 for CAN1, 14 - 27 for CAN2 */
#define FILTER_ID_LOW           0x0000
#define FILTER_ID_HIGH          0x0000
#define FILTER_MASK_ID_LOW      0x0000
#define FILTER_MASK_ID_HIGH     0x0000

/** CAN Config
 * @brief Initialize CAN, configure CAN filters/interrupts, and start CAN
 * 
 * @param mode CAN_MODE_NORMAL or CAN_MODE_LOOPBACK for operation mode
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_Config(uint32_t mode);

/** CAN Transmit Message
 * @brief Transmit message over CAN
 * 
 * @param StdId Message ID (Standard)
 * @param TxData Data to transmit
 * @param len Length of data (Bytes) to transmit (MAX 8B)
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_TransmitMessage(
        uint32_t StdId,
        uint8_t *TxData,
        uint8_t len);


#endif /* CAN_BUS_H */