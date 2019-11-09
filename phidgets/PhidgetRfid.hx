package phidgets;

import openfl.events.Event;
import openfl.events.EventDispatcher;
import phidgets.event.RfidEvent;
import phidgets.event.RfidDataEvent;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

class PhidgetRfid extends EventDispatcher {
	public static var instance(default, null):PhidgetRfid = new PhidgetRfid();

	private static var s_initialized:Bool = false;
	private static var hxphidgetrfid_set_haxe_callback_for_dispatching_events = null;

	private function new() {
		super();
	}

	/**
	 *
	 */
	public static function initialize():PhidgetRfid {
		if (s_initialized)
			return instance;

		hxphidgetrfid_set_haxe_callback_for_dispatching_events = Lib.load("hxphidgetrfid", "hxphidgetrfid_set_haxe_callback_for_dispatching_events", 1);
		hxphidgetrfid_set_haxe_callback_for_dispatching_events(CreateAndDispatchEvent);
		hxphidgetrfid_initialize();
		s_initialized = true;

		return instance;
	}

	private static var hxphidgetrfid_initialize = Lib.load("hxphidgetrfid", "hxphidgetrfid_initialize", 0);

	/**
	 * [Description]
	 * Toggles Led on (1) or Off (1) 
	 * @param state 
	 */
	public static function setLed(state:Int):Void {
		if (!s_initialized)
			return;
		hxphidgetrfid_setLedState(state);
	}

	private static var hxphidgetrfid_setLedState = Lib.load("hxphidgetrfid", "hxphidgetrfid_setLedState", 1);
	
	/**
	 * [Description] 
	 * shutdown connection and release hardware
	 */
	public static function shutdown():Void {
		hxphidgetrfid_shutdown();
		s_initialized = false;
	}

	private static var hxphidgetrfid_shutdown = Lib.load("hxphidgetrfid", "hxphidgetrfid_shutdown", 0);


	/**
	 * [Description]
	 * Creates an event object from the specific package & class spec, and constructor arguments. 
	 * @param eventPackageAndClass 
	 * @param args 
	 */
	private static function CreateAndDispatchEvent(eventPackageAndClass:String, args:Array<Dynamic>):Void {
		TraceEvent(eventPackageAndClass, args);

		var eventClass = Type.resolveClass(eventPackageAndClass);
		if (eventClass == null) {
			trace("[ERROR] Unable to find event class '" + eventPackageAndClass + "'");
			return;
		}

		var event = Type.createInstance(eventClass, args);
		if (event == null) {
			trace("[ERROR] Unable to instantiate event class '" + eventPackageAndClass + "'");
			return;
		}

		if (instance != null) {
			instance.dispatchEvent(event);
		}
	}

	/**
	 * [Description] Trace Sent Events
	 * @param eventPackageAndClass 
	 * @param args 
	 */
	private static function TraceEvent(eventPackageAndClass:String, args:Array<Dynamic>):Void {
		var sb:StringBuf = new StringBuf();
		var a = [];
		sb.add("Dispatching event ");
		sb.add(eventPackageAndClass);
		sb.add("(");
		for (p in args) {
			if (Std.is(p, String)) {
				a.push("\"" + p + "\"");
			} else {
				a.push(p);
			}
		}
		sb.add(a.join(", "));
		sb.add(")");
		trace(sb.toString());
	}
}
