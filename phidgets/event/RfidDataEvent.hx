package phidgets.event;
import openfl.events.Event;

class RfidDataEvent extends Event
{
    public static inline var TAG_FOUD = "rfid_data_event_tag_found";
    public static inline var TAG_LOST = "rfid_data_event_tag_lost";

    public var data(default, null) : String = null;

    public function new( type:String,  ?data:String)
    {
        super(type, true, true);
        this.data = data;
    }

	public override function clone() : Event
    {
		return new RfidDataEvent( type, data);
	}

	public override function toString() : String
    {
        var s = "[RfidDataEvent type=" + type + " data=" + data;
        return s;
	}
}