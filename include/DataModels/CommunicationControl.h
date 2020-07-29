#ifndef _UDS_COMMUNICATION_CONTROL_H_
#define _UDS_COMMUNICATION_CONTROL_H_

typedef enum CommunicationControlSubfunction_public {
    ComCtrl_enableRxAndTx = 0x00,
    ComCtrl_enableRxAndDisableTx = 0x01,
    ComCtrl_disableRxAndEnableTx = 0x02,
    ComCtrl_disableRxAndTx = 0x03,
    ComCtrl_enableRxAndDisableTxWithEnhancedAddressInformation = 0x04,
    ComCtrl_enableRxAndTxWithEnhancedAddressInformation = 0x05
} CommunicationControlSubfunction_t;

typedef enum Com_public {
    Com_normalCommunicationMessages = 0x01,
    Com_networkManagementCommunicationMessages = 0x02,
    Com_networkManagementCommunicationMessagesAndNormalCommunicationMessages = 0x03
} Com_t;

#endif // _UDS_COMMUNICATION_CONTROL_H_