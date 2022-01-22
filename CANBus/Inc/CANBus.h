#ifndef CAN_BUS_H
#define CAN_BUS_H

// CAN Drivers

/**
 * External variables required are:
 * (CAN_RxHeaderTypeDef) RxHeader
 * (uint8_t*) 8-byte Rx buffer
 * (uint32_t) TxMailbox
 */

#include "stm32f4xx_hal_can.h"

#define FILTER_BANK             14          /* 0 - 13 for CAN1, 14 - 27 for CAN2 */
#define FILTER_ID_LOW           0x0000
#define FILTER_ID_HIGH          0x0000
#define FILTER_MASK_ID_LOW      0x0000
#define FILTER_MASK_ID_HIGH     0x0000

/** CAN Config
 * @brief Configure CAN filters/interrupts and start CAN
 * 
 * @param hcan Initialized CAN#
 * @param RxData Buffer to store recieved data
 * @param RxFifo Fifo to use for recieving messages
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_Config(
        CAN_HandleTypeDef *hcan,
        uint8_t *RxData,
        uint32_t RxFifo);

/** CAN Transmit Message
 * @brief Transmit message over CAN
 * 
 * @param hcan CAN#
 * @param StdId Message ID (Standard)
 * @param TxData Data to transmit
 * @param len Length of data (Bytes) to transmit (MAX 8B)
 * @param TxMailbox Pointer to TxMailbox
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_TransmitMessage(
        CAN_HandleTypeDef *hcan,
        uint32_t StdId,
        uint8_t *TxData,
        uint8_t len,
        uint32_t *TxMailbox);


#endif /* CAN_BUS_H */