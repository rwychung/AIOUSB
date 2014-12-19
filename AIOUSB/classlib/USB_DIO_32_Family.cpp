/*
 * $RCSfile: USB_DIO_32_Family.cpp,v $
 * $Revision: 1.4 $
 * $Date: 2009/12/23 22:39:10 $
 * jEdit:tabSize=4:indentSize=4:collapseFolds=1:
 *
 * class USB_DIO_32_Family implementation
 */


#include <iostream>
#include <bits/stl_algo.h>
#include <assert.h>
#include "USBDeviceManager.hpp"
#include "USB_DIO_32_Family.hpp"


using namespace std;

namespace AIOUSB {



IntArray USB_DIO_32_Family::supportedProductIDs;

void USB_DIO_32_Family::initialize() {
	if( supportedProductIDs.empty() ) {
		supportedProductIDs.insert( supportedProductIDs.end(), USB_DIO_32 );
		// sort( supportedProductIDs.begin(), supportedProductIDs.end() ); 	// probably not necessary for an array of one!
	}	// if( supportedProductIDs.empty() )
}	// USB_DIO_32_Family::initialize()





USB_DIO_32_Family::USB_DIO_32_Family( int productID, int deviceIndex )
		: USBDeviceBase( productID, deviceIndex )
		, digitalIOSubsystem( *this )
		, counterSubsystem( *this ) {
	if( ! isSupportedProductID( productID ) )
		throw IllegalArgumentException( "Invalid product ID" );
}	// USB_DIO_32_Family::USB_DIO_32_Family()

USB_DIO_32_Family::~USB_DIO_32_Family() {
	// nothing to do
}	// USB_DIO_32_Family::~USB_DIO_32_Family()





/*
 * properties
 */

/**
 * Gets an array of all the product names supported by this USB device family.
 * <br><br>Although this method is <i>static</i>, an instance of USBDeviceManager must be created
 * and be "open" for use before this method can be used. This stipulation is imposed because the
 * underlying library must be initialized in order for product name/ID lookups to succeed, and that
 * initialization occurs only when an instance of USBDeviceManager is created and its
 * <i>USBDeviceManager::open()</i> method is called.
 * @return An array of product names, sorted in ascending order of product ID.
 */

StringArray USB_DIO_32_Family::getSupportedProductNames() {
	initialize();
	return USBDeviceManager::productIDToName( supportedProductIDs );
}	// USB_DIO_32_Family::getSupportedProductNames()

/**
 * Gets an array of all the product IDs supported by this USB device family.
 * @return An array of product IDs, sorted in ascending order.
 */

IntArray USB_DIO_32_Family::getSupportedProductIDs() {
	initialize();
	return IntArray( supportedProductIDs );
}	// USB_DIO_32_Family::getSupportedProductIDs()

/**
 * Tells if a given product ID is supported by this USB device family.
 * @param productID the product ID to check.
 * @return <i>True</i> if the given product ID is supported by this USB device family; otherwise, <i>false</i>.
 */

bool USB_DIO_32_Family::isSupportedProductID( int productID ) {
	initialize();
	return binary_search( supportedProductIDs.begin(), supportedProductIDs.end(), productID );
}	// USB_DIO_32_Family::isSupportedProductID()

/**
 * Prints the properties of this device and all of its subsystems. Mainly useful for diagnostic purposes.
 * @param out the print stream where properties will be printed.
 * @return The print stream.
 */

ostream &USB_DIO_32_Family::print( ostream &out ) {
	assert( &out != 0 );
	USBDeviceBase::print( out );
	digitalIOSubsystem.print( out );
	counterSubsystem.print( out );
	return out;
}	// USB_DIO_32_Family::print()



}	// namespace AIOUSB

/* end of file */
