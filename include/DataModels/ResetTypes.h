#ifndef UDS_RESET_H_
#define UDS_RESET_H_

/** @brief How the Server should Reset on an ECU Reset Request.
 * 
 */
typedef enum UDS_Reset_Type_public {
    UDS_Reset_Reserved00 = 0x00,                /** ISO Reserved*/
    UDS_HardReset = 0x01,                       /** Force a Hard Reset on the Server. */
    UDS_KeyOffOnReset = 0x02,                   /** Simulate an Ignition Off and On Event. */
    UDS_SoftReset = 0x03,                       /** Softreset the ECU. */
    UDS_enableRapidPowerShutDown = 0x04,        /** Enable a rapid Shutdown on ECUs that support this. */
    UDS_disableRapidPowerShutDown = 0x05,       /** Disable a rapid Shutdown on ECUs that support this. */
} UDS_Reset_t;

#endif /* UDS_RESET_H_ */
