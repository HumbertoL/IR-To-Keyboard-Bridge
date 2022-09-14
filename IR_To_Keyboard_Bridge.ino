#include <IRremote.h>
#include <Keyboard.h>

int RECV_PIN = 3; // IR sensor output pin
int POWER_PIN = 2; // Supply power from an I/O pin for convinience

// Easily disable serial ouput once done debugging
int ENABLE_SERIAL = 1;

IRrecv irrecv(RECV_PIN);

struct IRkeyboardMappings {
  int IRCode;
  int KeyboardCode;
};

int IR_CODE_RIGHT = 4060970624;
int IR_CODE_LEFT = 4094393984;
int IR_CODE_DOWN = 4044258944;
int IR_CODE_UP = 4077682304;
int IR_CODE_ENTER = 4228087424;
int IR_CODE_BACK = 4244799104;


// Receive IR_CODE_UP -> Press KEY_UP_ARROW key
IRkeyboardMappings keyboardMappings[] = {
  {IR_CODE_UP, KEY_UP_ARROW},
  {IR_CODE_DOWN, KEY_DOWN_ARROW},
  {IR_CODE_RIGHT, KEY_RIGHT_ARROW},
  {IR_CODE_LEFT, KEY_LEFT_ARROW},
  {IR_CODE_ENTER, KEY_RETURN},
  {IR_CODE_BACK, KEY_ESC}
  // add additional mappings here
};


void setup()
{
  // The board layour might make it easier to supply power via IO pin instead of 5V rail
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

    if (ENABLE_SERIAL == 1) {
      printMessage("Code: ");
      Serial.println(code);
    }

    processIrCode(code);

    irrecv.resume(); // Restart the ISR state machine and Receive the next value
  }
}

void processIrCode(int code) {
  // array size is total size divided by the size of a single element
  int size = sizeof keyboardMappings / sizeof keyboardMappings[0];

  // Go through each mapping and press the corresponding key if it exists
  for (int i = 0; i < size; i++)
  {
    IRkeyboardMappings mapping = keyboardMappings[0];
    if (code == mapping.IRCode)
    {
      pressKey(mapping.KeyboardCode);
      break;
    }
  }
}

void pressKey(int keyCode)
{
  Keyboard.press(keyCode);
  delay(100);
  Keyboard.releaseAll();
}

void printMessage(String message)
{
  if (ENABLE_SERIAL == 1) {
    Serial.println(message);
  }
}
