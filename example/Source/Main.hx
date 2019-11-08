package;

import openfl.display.Sprite;

import phidgets.PhidgetRfid;
import phidgets.event.RfidEvent;
import phidgets.event.RfidDataEvent;

class Main extends Sprite {

	public function new () {
		
		super ();

		PhidgetRfid.initialize();

		stage.addEventListener(RfidEvent.DEVICE_ATTACH, handleDeviceFound);
		stage.addEventListener(RfidEvent.DEVICE_DETACH, handleDeviceLost);
		stage.addEventListener(RfidDataEvent.TAG_FOUD, handleTagFound);
		stage.addEventListener(RfidDataEvent.TAG_LOST, handleTagLost);
	
	}

	private function handleTagFound(e:RfidDataEvent) : Void{
		trace('RFID FOUND ${e.data}');
	}

	private function handleTagLost(e:RfidDataEvent) : Void{
		trace('RFID REMOVED ${e.data}');
	}

	private function handleDeviceFound(e:RfidEvent) : Void{
		trace('Device Found: ${e.serialno}');
    }

    private function handleDeviceLost(e:RfidEvent) : Void{
		trace('Device Lost: ${e.serialno}');

    }
}