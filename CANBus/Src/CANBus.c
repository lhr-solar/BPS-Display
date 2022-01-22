// CAN Drivers

#include "CANBus.h"



/** CAN Config
 * @brief Configure CAN filters/interrupts and start CAN
 * 
 * @param hcan Initialized CAN#
 * @param RxFifo Fifo to use for recieving messages
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_Config(
        CAN_HandleTypeDef *hcan,
        uint32_t RxFifo) {

    HAL_StatusTypeDef configstatus;
    
    CAN_FilterTypeDef filterconfig;
    filterconfig.FilterBank = FILTER_BANK;
    filterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    filterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    filterconfig.FilterIdLow = FILTER_ID_LOW;
    filterconfig.FilterIdHigh = FILTER_ID_HIGH;
    filterconfig.FilterMaskIdLow = FILTER_MASK_ID_LOW;
    filterconfig.FilterMaskIdHigh = FILTER_MASK_ID_HIGH;
    filterconfig.FilterFIFOAssignment = RxFifo;
    filterconfig.FilterActivation = CAN_FILTER_ENABLE;
    filterconfig.SlaveStartFilterBank = 14;

    // Setup filter
    configstatus = HAL_CAN_ConfigFilter(hcan, &filterconfig);
    if (configstatus != HAL_OK) return configstatus;

    // Start actual CAN
    configstatus = HAL_CAN_START(hcan);
    if (configstatus != HAL_OK) return configstatus;

    // Enable interrupt for pending rx message
    configstatus = HAL_CAN_ActivateNotification(hcan, 
        (RxFifo == CAN_RX_FIFO0) ? 
            CAN_IT_RX_FIFO0_MSG_PENDING : CAN_IT_RX_FIFO1_MSG_PENDING);
    if (configstatus != HAL_OK) return configstatus;

    return HAL_OK;
}

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
        uint32_t *TxMailbox) {

    HAL_StatusTypeDef transmitstatus;

    CAN_TxHeaderTypeDef txheader;

    // ExtID and extended mode are unused/not configured
    txheader.StdId = StdId;
    txheader.RTR = CAN_RTR_DATA;
    txheader.IDE = CAN_ID_STD;
    txheader.DLC = len;
    txheader.TransmitGlobalTime = DISABLE;

    transmitstatus = HAL_CAN_AddTxMessage(hcan, &txheader, TxData, TxMailbox);
    if (transmitstatus != HAL_OK) return transmitstatus;

    return HAL_OK;
}