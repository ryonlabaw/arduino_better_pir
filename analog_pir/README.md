## Analog PIR
Get better, more stable values from your cheap PIR motion sensor.

## Synopsis
Posting some promising results in the PIR area, of which most online discussions revolve around the same code + technique.

Analog PIR motion detection

Uses the standard HC-SR501 or any motion sensor using the BISS0001 chip

To acquire the analog signal you need to solder a wire to PIN 12 of the BISS0001 chip.
Pin 12 is the Analog Output from an Op-amp ... at 0 to 3.3v

No motion: ~ 1.65v

Motion: 0v to 3.3v

As motion takes place, the analog signal will reflect the motion it sees.


Example of how to read ANALOG signals from PIR in a more stable format.
This method seems to work better than other methods and code samples available on the net.

Using simple timestamps and binary flags to track motion status.

## Code Example

See analog_pir.ino for arduino IDE example.

## Wiring Diagram

will be provided later

![BISS0001 pinout](https://www.insidegadgets.com/wp-content/uploads/2012/11/alarm5-1.png)


## Contributors

ryon labaw

## License

Public Domain
