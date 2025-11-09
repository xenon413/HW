# Lab 13 Serial Communications
For this lab we are going to use the hardware setup from experiment #1with one change. The guide has the signal wire connecting to board pin13 and for our lab we will have the signal wire connected to board pin 11.

A part of the setup function have your program to output an ASCII string to the serial port as part of the main initialization. The string may be anything you want but must be readable characters and make sense.

For the loop function your program must:

* Read the serial port expecting to receive a typed number of 0 to 9.
* Any other received characters must be ignored.
* The ASCII values 0x30 - 0x39 represent the numbers 0 - 9.
* Convert the received ASCII value to a number and use that number to control the brightness of the LED.
* The easiest way to convert this ASCII value to a number and check if it's the right value is the subtract 0x30 from the ASCII value. if the result is less than zero, or the result is greater than nine, then we know that we can ignore the typed character.
Use the PWM function we have already written to control the LED. Since this function takes a value of 0 to 255 and we have a received number value of 0 - 9 we can normalize the received number by multiplying by 25. This will allow you to convert the received number into a proper value for the PWM function.

Summit your project as an archive along with a video showing the program execution.

Add the following file to a tab for your project. This is the serial code that you will need in order to read and write to the seal port.

