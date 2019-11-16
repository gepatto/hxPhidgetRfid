package;

import openfl.display.Sprite;

import phidgets.PhidgetRfid;
import phidgets.event.RfidEvent;
import phidgets.event.RfidDataEvent;

class Main extends Sprite {

	private var rfidReader:PhidgetRfid;

	public function new () {
		
		super ();

		// Get PhidgetRfid singleton Instance
		rfidReader = PhidgetRfid.initialize();
		rfidReader.setLed(1);

		rfidReader.addEventListener(RfidEvent.DEVICE_ATTACH, handleDeviceFound);
		rfidReader.addEventListener(RfidEvent.DEVICE_DETACH, handleDeviceLost);
		rfidReader.addEventListener(RfidDataEvent.TAG_FOUD, handleTagFound);
		rfidReader.addEventListener(RfidDataEvent.TAG_LOST, handleTagLost);
	
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