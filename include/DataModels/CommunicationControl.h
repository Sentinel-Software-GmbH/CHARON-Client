#ifndef _UDS_COMMUNICATION_CONTROL_H_
#define _UDS_COMMUNICATION_CONTROL_H_

/** @brief How the Server should modify the @ref <tt>Communication Type</tt>
 * @note ISO 14229-1 Chapter 9.5
 */
typedef enum CommunicationControlSubfunction_public {
    UDS_ComCtrl_enableRxAndTx = 0x00,                                       /**< Enable RX and TX Channels on the Server */ 
    UDS_ComCtrl_enableRxAndDisableTx = 0x01,                                /**< Enable RX and Disable TX Channels on the Server*/
    UDS_ComCtrl_disableRxAndEnableTx = 0x02,                                /**< Disable RX and Enable TX Channels on the Server */
    UDS_ComCtrl_disableRxAndTx = 0x03,                                      /**< Disable RX and TX Channels on the Server */
    UDS_ComCtrl_enableRxAndDisableTxWithEnhancedAddressInformation = 0x04,  /**< Enable RX and Disable TX Channels while using vendor-specific Enhanced Address Information on the Server */
    UDS_ComCtrl_enableRxAndTxWithEnhancedAddressInformation = 0x05          /**< Enable RX and TX Channels while using vendor-specific Enhanced Address Information on the Server */
} UDS_CommunicationControlSubfunction_t;

/** Communication Type of the Server that should be modified
 * @note ISO 14229-1 Chapter 9.5
 */
typedef enum Com_public {
    UDS_Com_normalCommunicationMessages = 0x01,                                             /**< This value references all application-related communication (interapplication signal exchange between multiple in-vehicle servers). @note ISO 14229-1 Pg. 333 */
    UDS_Com_networkManagementCommunicationMessages = 0x02,                                  /**< This value references all network management related communication. @note ISO 14229-1 Pg. 333 */
    UDS_Com_networkManagementCommunicationMessagesAndNormalCommunicationMessages = 0x03     /**< This value references all network management and application-related communication. @note ISO 14229-1 Pg. 333 */
} UDS_CommunicationType_t;

#endif // _UDS_COMMUNICATION_CONTROL_H_