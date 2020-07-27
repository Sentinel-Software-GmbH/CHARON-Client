typedef enum UDS_Reset_Type_public {
    UDS_Reset_Reserved00 = 0x00,
    UDS_HardReset = 0x01,
    UDS_KeyOffOnReset = 0x02,
    UDS_SoftReset = 0x03,
    UDS_enableRapidPowerShutDown = 0x04,
    UDS_disableRapidPowerShutDown = 0x05,
} UDS_Reset_t;