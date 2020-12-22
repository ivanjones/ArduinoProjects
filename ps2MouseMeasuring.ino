// include the library code:
#include <LiquidCrystal.h>
#include <ps2.h>
// initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int feed = 0;
int feedcm = 0;
// initialize the Mouse library with the numbers of the interface pins. Pin 6 is data, Pin7 is clock
PS2 mouse(7,6);

/*
* initialize the mouse. Reset it, and place it into remote
* mode, so we can get the encoder data on demand.
*/
void mouse_init()
{
mouse.write(0xff); // reset
mouse.read(); // ack byte
mouse.read(); // blank */
mouse.read(); // blank */
// mouse.write(0xf0); // remote mode
mouse.read(); // ack
delayMicroseconds(100);
}


void setup() {
// set up the LCD's number of columns and rows: 
lcd.begin(16, 2); 
}


void loop() {
char mstat; //mstat is button press. Eg left button =9, right button =10, middle button = 12, no buttons = 8
char mx; //x value (relative, so will be -1 or +1 when moving, or 0 when stopped.
char my; //y value (relative, so will be -1 or +1 when moving, or 0 when stopped.

/* get a reading from the mouse */
mouse.write(0xeb); // get me the data!
mouse.read(); // ignore ack
mstat = mouse.read(); // read button value
mx = mouse.read(); // read x value
my = mouse.read(); // read y value
feed = feed + my; // calculate feed
feedcm = feed / 167.3; // covert to CM - I worked out that an 'my' value of 1673 = approx 10cm, con conversion factor is 167.3 
/* send the data back up */
//lcd.print(mstat, BIN);
//lcd.setCursor(0,0);
//lcd.print("X=");
//lcd.setCursor(3, 0); //move cursor to column 3, 2nd row
//lcd.print(mstat, DEC);//experimented printing button value
//lcd.print(" ");
lcd.setCursor(0, 1);
lcd.print("Feed(cm) = ");
lcd.setCursor(12, 1);//move cursor to column 12
lcd.print(feedcm, DEC);//print the cm value
lcd.print(" ");//over-write with a space to clear the previous value
//lcd.println();
//lcd.setCursor(0, 1);
//lcd.clear();

//delay(0); /* twiddle */
//lcd.print("got here too!"); //error capturing!!

}