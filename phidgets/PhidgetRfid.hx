package phidgets;

import openfl.events.Event;
import openfl.events.IEventDispatcher;
import phidgets.event.RfidEvent;
import openfl.display.Sprite;
import openfl.display.Stage;
//import haxe.Json;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end


class PhidgetRfid {
	
	private static var s_initialized:Bool = false;
	private static var hxphidgetrfid_set_haxe_callback_for_dispatching_events = null;
	private static var s_nextEventDispatcherId:Int = 1;
	private static var s_eventDispatcherMap:Map<Int, IEventDispatcher> = new Map<Int, IEventDispatcher>();
 	public static var stage(get, never) : Stage;

 	/**
 	*
 	*/
	public static function initialize():Void{
		
		if(s_initialized) return;
		
		hxphidgetrfid_set_haxe_callback_for_dispatching_events = Lib.load("hxphidgetrfid", "hxphidgetrfid_set_haxe_callback_for_dispatching_events", 1);
		hxphidgetrfid_set_haxe_callback_for_dispatching_events(CreateAndDispatchEvent);

		hxphidgetrfid_initialize();
		s_initialized = true;
	
		stage.dispatchEvent(new RfidEvent(RfidEvent.LIB_INIT, "Library Initialized", 0));
	}
	private static var hxphidgetrfid_initialize = Lib.load ("hxphidgetrfid", "hxphidgetrfid_initialize", 0);


	public static function setLed (state:Int ):Void {
		if(!s_initialized) return;
		hxphidgetrfid_setLedState(state);
	}
	private static var hxphidgetrfid_setLedState 	= Lib.load ("hxphidgetrfid", "hxphidgetrfid_setLedState", 1);
	/**
 	*
 	*/
	public static function shutdown():Void{
		hxphidgetrfid_shutdown();
	}
	private static var hxphidgetrfid_shutdown = Lib.load ("hxphidgetrfid", "hxphidgetrfid_shutdown", 0);


	public static function RegisterEventDispatcher(obj:IEventDispatcher) : Int
	{
		var id = s_nextEventDispatcherId++;
		s_eventDispatcherMap.set(id, obj);
		return id;
	}
	
	public static function UnregisterEventDispatcher(eventDispatcherId:Int) : Void
	{
		s_eventDispatcherMap.remove(eventDispatcherId);
	}


	/**
     * Creates an event object from the specific package & class spec, and constructor
     * arguments. Then, dispatches the event on the stage.
     */
    private static function CreateAndDispatchEvent(eventDispatcherId:Int, eventPackageAndClass:String, args:Array<Dynamic>) : Void
    {
       // TraceEvent(eventPackageAndClass, args);
      
        var eventClass = Type.resolveClass(eventPackageAndClass);
        if (eventClass == null)
        {
            trace("[ERROR] Unable to find event class '" + eventPackageAndClass + "'");
            return;
        }

        var event = Type.createInstance(eventClass, args);
        if (event == null)
        {
            trace("[ERROR] Unable to instantiate event class '" + eventPackageAndClass + "'");
            return;
        }

		var target:IEventDispatcher = stage;
		if (eventDispatcherId > 0)
		{
			var newtarget:IEventDispatcher = s_eventDispatcherMap.get(eventDispatcherId);
			if (newtarget != null)
			{
				target = newtarget;
	
			}
		}

		target.dispatchEvent(event);
    }


 private static function TraceEvent(eventPackageAndClass:String, args:Array<Dynamic>) : Void
    {
        var sb:StringBuf = new StringBuf();
        var a = [];
        sb.add("Dispatching event ");
        sb.add(eventPackageAndClass);
        sb.add("(");
        for (p in args)
        {
            if (Std.is(p, String))
            {
                a.push("\"" + p + "\"");
            }
            else
            {
                a.push(p);
            }
        }
        sb.add(a.join(", "));
        sb.add(")");
        trace(sb.toString());
    }

    private static function get_stage() : Stage
    {
        return openfl.Lib.current.stage;
    }
}