#PhidgetRFID Extension for OpenFL

This openfl extension is an attempt to allow the use of an (older)  
[Phidgets RFID USB interface](http://www.phidgets.com/products.php?category=14&product_id=1024_0)  
that enables you to Read RFID tags

### NOT READY FOR PRODUCTION ENVIRONMENT, USE AT YOUR OWN RISK ###

On Linux tested on a Raspberry Pi on Stretch
On Mac tested on 10.13
On Win tested on Windows10 version 1903

![Phidgets 1024](https://www.phidgets.com/images/1024_0_Web.jpg)

v 0.3.0
-
**Requirements**

###Linux/Raspberry Pi
- [ read on phidget website ](https://www.phidgets.com/docs21/OS_-_Linux)
- download and install [libphidget_2.1.9.20190409]( https://www.phidgets.com/downloads/phidget21/libraries/linux/libphidget/libphidget_2.1.9.20190409.tar.gz) 
- install `libusb-dev`
- udev rule `30-phidget.rules` from dependencies folder installed (copied to) to /etc/udev/rules.d/

###Windows
- download and install [`Phidget-x64_2.1.9.20191106.exe`] (https://www.phidgets.com/downloads/phidget21/libraries/windows/Phidget-x64.exe)


###Mac
- Download and install [Phidget_2.1.9.20191008.dmg](https://www.phidgets.com/downloads/phidget21/libraries/macos/Phidget/Phidget_2.1.9.20191008.dmg)


--

###Installation###

go to your haxelib dev directory and clone from git:   
`git clone https://github.com/gepatto/hxPiPhidgetRfid.git`  

point haxelib to the (dev)extension
`haxelib dev hxPhidgetRfid hxPhidgetRfid`

go into the directory:   
`cd hxPiPhidgetRfid`

build the libary:   
`lime rebuild ./ rpi -clean`.  
or   
`lime rebuild ./ windows -clean`  
or   
`lime rebuild ./ mac -clean`


***Look at the example project.***

--

###Known limitations###
version 0.3 only handles 1 device.