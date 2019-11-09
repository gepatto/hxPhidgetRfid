#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif

#include <hx/CFFI.h>
#include <string.h>
#include "hxPhidgetRfid.h"

using namespace hxphidgetrfid;

/**
*
*/
AutoGCRoot* dispatchCallback;

static void hxphidgetrfid_set_haxe_callback_for_dispatching_events(value haxeCallback)
{
   dispatchCallback = new AutoGCRoot(haxeCallback);
   hxphidgetrfid::SetHaxeCallbackForDispatchingEvents(dispatchCallback);
}
DEFINE_PRIM(hxphidgetrfid_set_haxe_callback_for_dispatching_events, 1);

/**
*
*/
static void hxphidgetrfid_initialize()
{
	initialize();	
}
DEFINE_PRIM (hxphidgetrfid_initialize, 0);

/**
*
*/
static void hxphidgetrfid_shutdown()
{
  shutdown();
}
DEFINE_PRIM(hxphidgetrfid_shutdown, 0);


/**
*
*/
static void hxphidgetrfid_setOutputState(value output, value state)
{
   hxphidgetrfid::setOutputState(val_int(output), val_int(state) );
}
DEFINE_PRIM(hxphidgetrfid_setOutputState, 2);
/**
*
*/
static void hxphidgetrfid_setLedState(value state)
{
   hxphidgetrfid::setLedState(val_int(state) );
}
DEFINE_PRIM(hxphidgetrfid_setLedState, 1);

/**
*
*/
extern "C" void hxphidgetrfid_main () {
	
	val_int(0); // Fix Neko init
	
}
DEFINE_ENTRY_POINT (hxphidgetrfid_main);

extern "C" int hxphidgetrfid_register_prims () { return 0; }
