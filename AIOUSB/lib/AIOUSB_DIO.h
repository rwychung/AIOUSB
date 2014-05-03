/**
 * @file   AIOUSB_DIO.h
 * @author $Format: %an <%ae>$
 * @date   $Format: %ad$
 * @release $Format: %t$
 */
#ifndef _AIOUSB_DIO_H
#define _AIOUSB_DIO_H

#include "AIOUSB_Core.h"
#include "DIOBuf.h"
#include "AIODataTypes.h"

#include <arpa/inet.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#ifdef __aiousb_cplusplus
namespace AIOUSB
{
#endif

PUBLIC_EXTERN unsigned long DIO_Configure(
                                          unsigned long DeviceIndex,
                                          unsigned char bTristate,
                                          void *pOutMask,
                                          void *pData
                                          );
PUBLIC_EXTERN unsigned long DIO_ConfigureEx( 
                                            unsigned long DeviceIndex, 
                                            void *pOutMask, 
                                            void *pData, 
                                            void *pTristateMask 
                                             );

PUBLIC_EXTERN unsigned long DIO_ConfigurationQuery(
                                                   unsigned long DeviceIndex,
                                                   void *pOutMask,
                                                   void *pTristateMask
                                                   );

PUBLIC_EXTERN unsigned long DIO_WriteAll(
                                         unsigned long DeviceIndex,
                                         void *pData
                                         );

PUBLIC_EXTERN unsigned long DIO_Write8(
                                       unsigned long DeviceIndex,
                                       unsigned long ByteIndex,
                                       unsigned char Data
                                       );


PUBLIC_EXTERN unsigned long DIO_Write1(
                                       unsigned long DeviceIndex,
                                       unsigned long BitIndex,
                                       unsigned char bData
                                       );


PUBLIC_EXTERN unsigned long DIO_ReadAll(
                                        unsigned long DeviceIndex,
                                        DIOBuf *buf
                                        );
PUBLIC_EXTERN unsigned long DIO_ReadAllToCharStr(
                                                 unsigned long DeviceIndex,
                                                 char *buf,
                                                 unsigned size
                                                 );

PUBLIC_EXTERN unsigned long DIO_Read8(
                                      unsigned long DeviceIndex,
                                      unsigned long ByteIndex,
                                      int *pdat
                                      );

PUBLIC_EXTERN unsigned long DIO_Read1(
                                      unsigned long DeviceIndex,
                                      unsigned long BitIndex,
                                      int *bit
                                      );

PUBLIC_EXTERN unsigned long DIO_StreamOpen(
                                           unsigned long DeviceIndex,
                                           unsigned long bIsRead
                                           );

PUBLIC_EXTERN unsigned long DIO_StreamClose(
                                            unsigned long DeviceIndex
                                            );

PUBLIC_EXTERN unsigned long DIO_StreamSetClocks(
                                                unsigned long DeviceIndex,
                                                double *ReadClockHz,
                                                double *WriteClockHz
                                                );

PUBLIC_EXTERN unsigned long DIO_StreamFrame(
                                            unsigned long DeviceIndex,
                                            unsigned long FramePoints,
                                            unsigned short *pFrameData,
                                            unsigned long *BytesTransferred
                                            );

#ifdef __aiousb_cplusplus
} // namespace
#endif

#endif
