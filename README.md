# IR_TO_KEYBOARD_BRIDGE
This sketch allows you to convert incoming IR signals to Keyboard Inputs.

This is useful for controlling USB enabled devices with a TV remote.

For example, you can use this to control an NVidia Shield without using HDMI CEC. This should also work with any Android TV devices, as well as Windows or Mac machines.

# Requirements
 - Arduino Pro Micro, Arduino Leonardo or any other board with a ATmega32U4 chip
 - IR Receiver Module
 - USB cable

 That's it!
 
Depending on your module, you should be able to connect it directly to the board like this. Double check that the pintout on the sensor matches this before attempting this.
 
 ![Micro_IR_Connection](https://user-images.githubusercontent.com/8048702/190041020-3f523a0b-dd62-477c-895a-ea116d76ab17.png)


 # Usage

 Connect the IR Receiver to the board. For convinient use with the Pro Mini, I recommend connecting the sensor's power to pin 2 and the output to pin 3. If done correctly, the ground pin will be connected to one of the board's GND pins.

Make sure `ENABLE_SERIAL` is set to 1. This will output all debugging information. Upload the sketch to your device and open Serial Monitor.

 Point your remote at the receiver and press a button. You should see the corresponding code printed in the monitor.

 Copy that code to the section at the top with the values that look like `IR_CODE_`. Repeat for each key that you plan to use.

 Now add these to the keyboard mappings array. The first value is the IR Code and the second is the desired keypress:

 ```c
IRkeyboardMappings keyboardMappings[] = {
  {IR_CODE_CUSTOM, KEY_UP_ARROW},
  // ...
};
 ```

 Now connect your board to the device that you want to control. When you press the key on the remote, it should trigger the correponding keypress.
