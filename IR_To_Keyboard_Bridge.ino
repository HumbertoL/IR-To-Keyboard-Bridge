#include <IRremote.h>  //including infrared remote header file     
#include <Keyboard.h>

int RECV_PIN = 3; // the pin where you connect the output pin of IR sensor
int POWER_PIN = 2; // Supply power from an I/O pin for convinience

int ENABLE_SERIAL = 1;

IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);
  Keyboard.begin();


  irrecv.enableIRIn();

  if (ENABLE_SERIAL == 1)
  {
    Serial.begin(9600);
    printMessage("program started");
  }

}

void loop()
{
  // Returns 0 if no data ready, 1 if data ready.
  if (IrReceiver.decode())
  {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    printMessage(" ");
    Serial.print("Code: ");

    //char buffer[10];
    //sprintf(buffer, "%d", code);
    //printMessage(buffer); //prints the value a a button press
    //printMessage(" ");

    if (ENABLE_SERIAL == 1) {
      Serial.println(code);
    }

    // on 16753245
    // off 16769565
    // right 4060970624
    // left 4094393984
    // down 4044258944
    // up 4077682304
    // enter 4228087424
    // back 4244799104


    if (code == 4094393984) {
      // KEY_LEFT_ARROW
      Serial.print("LEFT ");
      pressKey(KEY_LEFT_ARROW);
    } else if (code == 4060970624) {
      Serial.print("RIGHT ");
      pressKey(KEY_RIGHT_ARROW);
    } else if (code == 4077682304) {
      Serial.print("UP ");
      pressKey(KEY_UP_ARROW);
    } else if (code == 4044258944) {
      Serial.print("DOWN ");
      pressKey(KEY_DOWN_ARROW);
    } else if (code == 4228087424) {
      pressKey(KEY_RETURN);
    } else if (code == 4244799104) {
      pressKey(KEY_ESC);
    }

    irrecv.resume(); // Restart the ISR state machine and Receive the next value
  }
}

void pressKey(int keyCode)
{
  Keyboard.press(keyCode); //left key
  delay(100);
  Keyboard.releaseAll();
}

void printMessage(String message)
{
  if (ENABLE_SERIAL == 1) {
    Serial.println(message);
  }

}
