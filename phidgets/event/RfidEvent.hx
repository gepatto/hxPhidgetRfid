package phidgets.event;
import openfl.events.Event;

class RfidEvent extends Event
{
    public static inline var DEVICE_ATTACH  = "rfid_event_device_attach";
    public static inline var DEVICE_DETACH  = "rfid_event_device_detach";

    public var devicename(default, null) : String;
    public var serialno(default, null) : Int;

    public function new( type:String,  devicename:String, serialno:Int)
    {
        super(type, true, true);
        this.devicename = devicename;
        this.serialno   = serialno;
    }

    public override function clone() : Event
    {
		return new RfidEvent( type, this.devicename, this.serialno );
	}

	public override function toString() : String
    {
       return "[RfidEvent type=" + type + " devicename=" + this.devicename + " serialno=" + this.serialno;
	}
}