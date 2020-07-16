/****************************************************
 *  UDSClientLib.h                                         
 *  Created on: 16-Jul-2020 09:30:00                      
 *  Implementation of the Class UDSClientLib       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_CAE719C6_0CEB_4c4b_ADB7_E1E052BA52FE__INCLUDED_)
#define EA_CAE719C6_0CEB_4c4b_ADB7_E1E052BA52FE__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include "DiagnosticCommunicationManager.h"
#include "DataTransmitter.h"
#include "StoredDataTransmitter.h"
#include "InputOutputController.h"
#include "Routine.h"
#include "UploadDownload.h"

DiagnosticCommunicationManager *m_DiagnosticCommunicationManager;
DataTransmitter *m_DataTransmitter;
StoredDataTransmitter *m_StoredDataTransmitter;
InputOutputController *m_InputOutputController;
Routine *m_Routine;
UploadDownload *m_UploadDownload;


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_CAE719C6_0CEB_4c4b_ADB7_E1E052BA52FE__INCLUDED_)*/
 