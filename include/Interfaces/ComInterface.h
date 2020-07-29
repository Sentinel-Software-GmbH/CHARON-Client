/****************************************************
 *  ComInterface.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Interface ComInterface       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_F8F6B55A_280A_47fe_A337_41AB995A9668__INCLUDED_)
#define EA_F8F6B55A_280A_47fe_A337_41AB995A9668__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/** @brief Used to initialize the Communication Interface.
 * The user should set all the appropriate Addresses, default baudrate and everything else
 * that's used to connect to a default uds session here.
 * 
 * This will get called when the Session and Transport Manager initializes with the given ComInterface.
 * 
 * @note Set Addresses, default Baudrate and other communication relevant settings in this function.
 * 
 * @return Return true if init was successful.
 */
typedef bool (*initFunc)(void);

/** @brief Takes a uds message starting at SID and send it to the server.
 * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
 * 
 * This will get called any time a request is send.
 * 
 * @note Implement the uds conform transport protocol here.
 * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
 * 
 * @param buffer The data to be sent. This is the inner message, this does not include the application layer protocol frames.
 * @param length Size of the data in bytes.
 * @return How many bytes have been sent. Returns a negative number when an error ocurred.
 */
typedef int32_t (*sendFunc)(uint8_t* data, uint32_t length);

/** @brief Should only receive the A_DATA part of the response message.
 * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
 * 
 * This will get called any time a request is send.
 * This should not be blocking, because we still need to meet certain timing requirements,
 * instead the function should return false, when no message is available.
 * 
 * @note Implement the uds conform transport protocol here. Only write the A_DATA part into the buffer.
 * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
 * 
 * @param buffer The buffer of the data to be received, only write the A_DATA into this buffer.
 * @param count Tries to read up to @c count bytes.
 * @return How many bytes have been read. If it's negative, there was an error.
 */
typedef int32_t (*recvFunc)(uint8_t* buffer, uint32_t count);

/** @brief Adjusts the Baudrate of the Connection.
 * 
 * After a LinkControl Request was successful, the baudrate of the connection
 * needs to be adjusted to the new connection Speed.
 * So the Interface must provide a function to adjust the baudrate.
 * 
 * @note Depending on the Server this might be optional.
 * 
 * @param speed Baudrate in B/s
 * @return True, if it succeeded.
 */
typedef bool (*setSpeedFunc)(uint32_t speed);

/** Provides Functions to communicate through the user implemented connection driver. */
typedef struct ComInterface_public {
    /** @brief Used to initialize the Communication Interface.
     * The user should set all the appropriate Addresses, default baudrate and everything else
     * that's used to connect to a default uds session here.
     * 
     * This will get called when the Session and Transport Manager initializes with the given ComInterface.
     * 
     * @note Set Addresses, default Baudrate and other communication relevant settings in this function.
     */
    initFunc init;
    /** @brief Takes a uds message starting at SID and send it to the server.
     * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
     * 
     * This will get called any time a request is send.
     * 
     * @note Implement the uds conform transport protocol here.
     * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
     */
    sendFunc send;
    /**
     * @brief Should only receive the A_DATA part of the response message.
     * The user should implement the uds conform transport protocol (or if necessary the application protocol frame).
     * 
     * This will get called any time a request is send.
     * 
     * @note Implement the uds conform transport protocol here. Only write the A_DATA part into the buffer.
     * Refer to @b ISO @b 14229-3,-4,-5,-6,-7 @c UDSon... Standard Documents.
     */
    recvFunc receive;
    /** @brief Adjusts the Baudrate of the Connection.
     * 
     * After a LinkControl Request was successful, the baudrate of the connection
     * needs to be adjusted to the new connection Speed.
     * So the Interface must provide a function to adjust the baudrate.
     * 
     * @note Depending on the Server this might be optional.
     */
    setSpeedFunc setSpeed;
    /** @brief The Ability to adjust the Baudrate of the Interface.
     * 
     * If the Interface cannot change its Baudrate, there is no use to send a LinkControl request.
     * So the usage of LinkControl should not allowed.
     * 
     */
    bool speedIsAdjustable;
} ComInterface;


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_F8F6B55A_280A_47fe_A337_41AB995A9668__INCLUDED_)*/
 