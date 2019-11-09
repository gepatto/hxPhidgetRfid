#include <hx/CFFI.h>
#include <stdio.h>
#include <stdarg.h>
#if defined(HX_WINDOWS)
#include "windows/phidget21.h"
#endif
#if defined(HX_MACOS)
#include "mac/phidget21.h"
#endif
#if defined(HX_LINUX)
#include <phidget21.h>
#endif
#include "hxPhidgetRfid.h"


struct AutoHaxe
{
	int base;
	const char *message;
	AutoHaxe(const char *inMessage)
	{  
		base = 0;
		message = inMessage;
		gc_set_top_of_stack(&base,true);
	}
	~AutoHaxe()
	{
		printf("removing AutoHaxe %d\n",base);
		gc_set_top_of_stack(0,true);
	}
};

namespace hxphidgetrfid {

	static AutoGCRoot* g_haxeCallbackForDispatchingEvents = NULL;

	//Declare an RFID handle
	CPhidgetRFIDHandle rfid = 0;

	AutoGCRoot* GetHaxeCallbackForDispatchingEvents()
    {
        return g_haxeCallbackForDispatchingEvents;
    }

	/**
	 * 
	 */
    void SetHaxeCallbackForDispatchingEvents(AutoGCRoot* haxeCallback)
    {
        if (g_haxeCallbackForDispatchingEvents)
        {
            delete g_haxeCallbackForDispatchingEvents;
        }

        g_haxeCallbackForDispatchingEvents = haxeCallback;
    }

	/**
	 * 
	 */
	void InvokeHaxeCallbackFunctionForDispatchingEvents(const char* eventClassSpec, va_list params)
	{
		bool foundAllArgs = false;
		value ar = alloc_array(0);

		while (!foundAllArgs)
		{
			int type = va_arg(params, int);
			switch (type)
			{
				case CEND:
					foundAllArgs = true;
					break;

				case CSTRING:
					val_array_push(ar, alloc_string(va_arg(params, char*)));
					break;

				case CINT:
					val_array_push(ar, alloc_int(va_arg(params, int)));
					break;

				case CDOUBLE:
					val_array_push(ar, alloc_float(va_arg(params, double)));
					break;

				default:
					printf("InvokeHaxeCallbackFunctionForDispatchingEvents() received invalid type %d, aborting.\n", type);
					return;
			}
		}

		AutoGCRoot* haxeCallback = GetHaxeCallbackForDispatchingEvents();
		if (haxeCallback != NULL)
		{
			val_call2(haxeCallback->get(), alloc_string(eventClassSpec), ar);
		}
	}
	
	/**
	*
	*/
	void DispatchEventToHaxe(const char* eventClassSpec, ...)
	{
		::AutoHaxe haxe("DispatchEventToHaxe");
        va_list params;
        va_start(params, eventClassSpec);
		InvokeHaxeCallbackFunctionForDispatchingEvents( eventClassSpec, params);
		va_end(params);
	}
	
	/**
	 * 
	 */ 
	void setLedState(int state){
		if (rfid!=NULL){
			CPhidgetRFID_getLEDOn(rfid, &state);
		}
	}

	/**
	 *
	 */
	int CCONV AttachHandler(CPhidgetHandle RFID, void *userptr)
	{
		int serialNo;
		const char *name;

		CPhidget_getDeviceName (RFID, &name);
		CPhidget_getSerialNumber(RFID, &serialNo);

		printf("%s %10d attached!\n", name, serialNo);
		
		DispatchEventToHaxe( "phidgets.event.RfidEvent", 
			hxphidgetrfid::CSTRING,  "rfid_event_device_attach",
			hxphidgetrfid::CSTRING, name,
			hxphidgetrfid::CINT, serialNo,
		 	hxphidgetrfid::CEND); 
		return 0;
	}

	/**
	 *
	 */
	int CCONV DetachHandler(CPhidgetHandle RFID, void *userptr)
	{
		int serialNo;
		const char *name;

		CPhidget_getDeviceName (RFID, &name);
		CPhidget_getSerialNumber(RFID, &serialNo);

		printf("%s %10d detached!\n", name, serialNo);
		
		DispatchEventToHaxe( "phidgets.event.RfidEvent", 
			hxphidgetrfid::CSTRING,  "rfid_event_device_detach",
			hxphidgetrfid::CSTRING, name,
			hxphidgetrfid::CINT, serialNo,
		 	hxphidgetrfid::CEND); 
		return 0;
	}

	/**
	 *
	 */
	int CCONV ErrorHandler(CPhidgetHandle RFID, void *userptr, int ErrorCode, const char *unknown)
	{
		//printf("Error handled. %d - %s\n", ErrorCode, unknown);
		return 0;
	}

	/**
	 *
	 */
	int CCONV OutputChangeHandler(CPhidgetRFIDHandle RFID, void *usrptr, int Index, int State)
	{
		if(Index == 0 || Index == 1)
		{
			//printf("Output: %d > State: %d\n", Index, State);
		}
		return 0;
	}

	/**
	 *
	 */
	int CCONV TagHandler(CPhidgetRFIDHandle RFID, void *usrptr, char *TagVal, CPhidgetRFID_Protocol proto)
	{
		//turn on the Onboard LED
		CPhidgetRFID_setLEDOn(RFID, 1);

		//printf("TagFound: %s\n", TagVal);
		DispatchEventToHaxe( "phidgets.event.RfidDataEvent", hxphidgetrfid::CSTRING,  "rfid_data_event_tag_found",	hxphidgetrfid::CSTRING,  TagVal,  hxphidgetrfid::CEND); 

		return 0;
	}

	/**
	 *
	 */
	int CCONV TagLostHandler(CPhidgetRFIDHandle RFID, void *usrptr, char *TagVal, CPhidgetRFID_Protocol proto)
	{
		//turn off the Onboard LED
		CPhidgetRFID_setLEDOn(RFID, 0);
		//printf("TagLost:  %s \n", TagVal);
		DispatchEventToHaxe( "phidgets.event.RfidDataEvent", CSTRING,  "rfid_data_event_tag_lost",	hxphidgetrfid::CSTRING,  TagVal,  hxphidgetrfid::CEND); 
		
		return 0;
	}

	/**
	 * Display the properties of the attached phidget to the screen.  
	 * We will be displaying the name, serial number and version of the attached device.
	 * We will also display the nu,mber of available digital outputs
	 */
	int display_properties(CPhidgetRFIDHandle phid)
	{
		int serialNo, version, numOutputs, antennaOn, LEDOn;
		const char* ptr;

		CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
		CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
		CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

		CPhidgetRFID_getOutputCount (phid, &numOutputs);
		CPhidgetRFID_getAntennaOn (phid, &antennaOn);
		CPhidgetRFID_getLEDOn (phid, &LEDOn);


		printf("%s\n", ptr);
		printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
		printf("# Outputs: %d\n\n", numOutputs);
		printf("Antenna Status: %d\nOnboard LED Status: %d\n", antennaOn, LEDOn);

		return 0;
	}

	/**
	 *
	 */
	void shutdown()
	{
		CPhidget_close((CPhidgetHandle)rfid);
		CPhidget_delete((CPhidgetHandle)rfid);
		printf("Releasing Phidhget hardware handles");
	}
	
	/**
	 *
	 */
	void initialize()
	{
		int result;
		const char *err;

		//create the RFID object
		CPhidgetRFID_create(&rfid);

		//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
		CPhidget_set_OnAttach_Handler((CPhidgetHandle)rfid, AttachHandler, NULL);
		CPhidget_set_OnDetach_Handler((CPhidgetHandle)rfid, DetachHandler, NULL);
		CPhidget_set_OnError_Handler((CPhidgetHandle)rfid, ErrorHandler, NULL);

		//Registers a callback that will run if an output changes.
		//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetRFID_set_OnOutputChange_Handler(rfid, OutputChangeHandler, NULL);

		//Registers a callback that will run when a Tag is read.
		//Requires the handle for the PhidgetRFID, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetRFID_set_OnTag2_Handler(rfid, TagHandler, NULL);

		//Registers a callback that will run when a Tag is lost (removed from antenna read range).
		//Requires the handle for the PhidgetRFID, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetRFID_set_OnTagLost2_Handler(rfid, TagLostHandler, NULL);

		//open the RFID for device connections
		CPhidget_open((CPhidgetHandle)rfid, -1);

		//get the program to wait for an RFID device to be attached
		printf("Waiting for RFID to be attached....\n");
		if((result = CPhidget_waitForAttachment((CPhidgetHandle)rfid, 100)))
		{
		 	CPhidget_getErrorDescription(result, &err);
		 	printf("Problem waiting for attachment: %s\n", err);
		}
		else
		{
			CPhidgetRFID_setAntennaOn(rfid, 1);
		}
	}
}