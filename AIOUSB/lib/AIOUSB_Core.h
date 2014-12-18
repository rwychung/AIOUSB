/**
 * @file   AIOUSB_Core.h
 * @author $Format: %an <%ae>$
 * @date   $Format: %ad$
 * @version $Format: %t$
 * @brief  
 */

#ifndef AIOUSB_CORE_H
#define AIOUSB_CORE_H

#define PUBLIC_EXTERN extern
#define PRIVATE

#include "AIODataTypes.h"
#include "AIOUSBDevice.h"
#include "libusb.h"
#include <pthread.h>
#include <semaphore.h>

#ifdef __aiousb_cplusplus
namespace AIOUSB {
#endif

PUBLIC_EXTERN int aio_errno;

/* parameters passed from ADC_BulkAcquire() to its worker thread */
struct BulkAcquireWorkerParams {
    unsigned long DeviceIndex;
    unsigned long BufSize;
    void *pBuf;
};


typedef struct aiousboption {

} AIOOption;

typedef enum {
    AIO_DEVICE_DESCRIPTOR,
    AIO_ADCCONFIG_BLOCK
} AIOArgument;

typedef struct aioerror {
    AIORET_TYPE retval;
    char *error_message;
} AIOError;

typedef union aioeither {
    AIOArgument right;
    AIOError left;
} AIOEither;


#define PROD_NAME_SIZE 40

typedef struct  {
     unsigned int id;
     char name[ PROD_NAME_SIZE + 2 ];
} ProductIDName;


struct ADRange {
  double minVolts;
  double range;
};

extern struct ADRange adRanges[ AD_NUM_GAIN_CODES ];

extern unsigned long AIOUSB_INIT_PATTERN;
extern unsigned long aiousbInit ;

/* PUBLIC_EXTERN unsigned long ADC_CopyConfig(unsigned long DeviceIndex, ADConfigBlock *config  ); */
PUBLIC_EXTERN unsigned long ADC_ResetDevice( unsigned long DeviceIndex  );
PUBLIC_EXTERN AIORET_TYPE AIOUSB_GetDeviceSerialNumber( unsigned long DeviceIndex );
PUBLIC_EXTERN AIORET_TYPE ADC_WriteADConfigBlock( unsigned long DeviceIndex , ADConfigBlock *config );

PUBLIC_EXTERN void PopulateDeviceTableTest(unsigned long *products, int length );


#ifndef SWIG

PUBLIC_EXTERN AIOUSB_BOOL AIOUSB_Lock(void);
PUBLIC_EXTERN AIOUSB_BOOL AIOUSB_UnLock(void);

PUBLIC_EXTERN AIORESULT AIOUSB_InitTest(void);
PUBLIC_EXTERN AIORESULT AIOUSB_Validate( unsigned long *DeviceIndex );
PUBLIC_EXTERN AIORESULT AIOUSB_Validate_Lock(  unsigned long *DeviceIndex ) ;

PUBLIC_EXTERN DeviceDescriptor *DeviceTableAtIndex( unsigned long DeviceIndex );
PUBLIC_EXTERN DeviceDescriptor *DeviceTableAtIndex_Lock( unsigned long DeviceIndex );

PUBLIC_EXTERN DeviceDescriptor *AIOUSB_GetDevice_Lock( unsigned long DeviceIndex , 
                                                        unsigned long *result
                                                        );

DeviceDescriptor *AIOUSB_GetDevice( unsigned long DeviceIndex );
ADConfigBlock *AIOUSB_GetConfigBlock( DeviceDescriptor *dev);



PUBLIC_EXTERN AIORESULT AIOUSB_EnsureOpen( unsigned long DeviceIndex );
/* PUBLIC_EXTERN const char *ProductIDToName( unsigned int productID ); */
PUBLIC_EXTERN unsigned int ProductNameToID( const char *name );
/* PUBLIC_EXTERN const char *GetSafeDeviceName( unsigned long DeviceIndex ); */
PUBLIC_EXTERN struct libusb_device_handle *AIOUSB_GetDeviceHandle( unsigned long DeviceIndex );
PUBLIC_EXTERN struct libusb_device_handle *AIOUSB_GetUSBHandle(DeviceDescriptor *deviceDesc );

PUBLIC_EXTERN unsigned AIOUSB_GetOversample( const ADConfigBlock *config );
PUBLIC_EXTERN void AIOUSB_SetOversample( ADConfigBlock *config, unsigned overSample );


PUBLIC_EXTERN int AIOUSB_BulkTransfer( struct libusb_device_handle *dev_handle,
                                       unsigned char endpoint, unsigned char *data, 
                                        int length, int *transferred, unsigned int timeout );

PUBLIC_EXTERN unsigned ADC_GetOversample_Cached( ADConfigBlock *config );
PUBLIC_EXTERN unsigned ADC_GainCode_Cached( ADConfigBlock *config, unsigned channel);
PUBLIC_EXTERN DeviceDescriptor *AIOUSB_GetDevice_NoCheck( unsigned long DeviceIndex  );
PUBLIC_EXTERN AIORET_TYPE cull_and_average_counts( unsigned long DeviceIndex, 
                                                   unsigned short *counts,
                                                   unsigned *size ,
                                                   unsigned numChannels
                                                   );

AIORESULT AIOUSB_InitConfigBlock(ADConfigBlock *config, unsigned long DeviceIndex, AIOUSB_BOOL defaults);


PUBLIC_EXTERN AIORESULT AIOUSB_GetScan( unsigned long DeviceIndex, unsigned short counts[] );
PUBLIC_EXTERN AIORESULT AIOUSB_ArrayCountsToVolts( unsigned long DeviceIndex, int startChannel,
                                                        int numChannels, const unsigned short counts[], double volts[] );
PUBLIC_EXTERN AIORESULT AIOUSB_ArrayVoltsToCounts( unsigned long DeviceIndex, int startChannel,
                                                        int numChannels, const double volts[], unsigned short counts[] );


PUBLIC_EXTERN AIORESULT GenericVendorRead( unsigned long deviceIndex, unsigned char Request, unsigned short Value, unsigned short Index, void *bufData , unsigned long *bytes_read  );

PUBLIC_EXTERN AIORESULT GenericVendorWrite( unsigned long DeviceIndex, unsigned char Request, unsigned short Value, unsigned short Index, void *bufData, unsigned long *bytes_write );
PUBLIC_EXTERN AIORESULT AIOUSB_Validate_Device( unsigned long DeviceIndex );


#endif




#if 0
/*
 * these will be moved to aiousb.h when they are ready to be made public
 */
extern unsigned long DACOutputProcess( unsigned long DeviceIndex, double *ClockHz, unsigned long NumSamples, unsigned short *pSampleData );
#endif



#ifdef __aiousb_cplusplus
}
#endif


#endif


/* end of file */
