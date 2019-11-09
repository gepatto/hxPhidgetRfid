#ifndef HXPHIDGETRFID_H
#define HXPHIDGETRFID_H

namespace hxphidgetrfid 
{		
	
	enum
    {
        CEND,
        CSTRING,
        CINT,
        CDOUBLE
    };

    void DispatchEventToHaxe(const char* eventClassSpec, ...);
	void DispatchEventToHaxeInstance(int eventDispatcherId, const char* eventClassSpec, ...);
    
    AutoGCRoot* GetHaxeCallbackForDispatchingEvents();
    void SetHaxeCallbackForDispatchingEvents(AutoGCRoot* haxeCallback);
	void InvokeHaxeCallbackFunctionForDispatchingEvents(int eventDispatcherId, const char* eventClassSpec, va_list params);

    void initialize();
    void shutdown();
    void setLedState(int state);
    void setOutputState(int output, int state);
}

#endif