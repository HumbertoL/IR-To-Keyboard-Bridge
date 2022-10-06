#include <IRremote.h>
#include <Keyboard.h>

int RECV_PIN = 3;   // IR sensor output pin
int POWER_PIN = 2;  // Supply power from an I/O pin for convinience

// Easily disable serial ouput once done debugging
int ENABLE_SERIAL = 0;

IRrecv irrecv(RECV_PIN);

struct IRkeyboardMappings {
  uint32_t IRCode;
  int KeyboardCode;
};

uint32_t IR_CODE_RIGHT = 4060970624;
uint32_t IR_CODE_LEFT = 4094393984;
uint32_t IR_CODE_DOWN = 4044258944;
uint32_t IR_CODE_UP = 4077682304;
uint32_t IR_CODE_ENTER = 4228087424;
uint32_t IR_CODE_BACK = 4244799104;


// Receive IR_CODE_UP -> Press KEY_UP_ARROW key
IRkeyboardMappings keyboardMappings[] = {
  { IR_CODE_UP, KEY_UP_ARROW },
  { IR_CODE_DOWN, KEY_DOWN_ARROW },
  { IR_CODE_RIGHT, KEY_RIGHT_ARROW },
  { IR_CODE_LEFT, KEY_LEFT_ARROW },
  { IR_CODE_ENTER, KEY_RETURN },
  { IR_CODE_BACK, KEY_ESC }
  // add additional mappings here
};

// In some cases, holding down the button will send Code 0.
// We can simulate pressing the button multiple times if we track the previous code.
int prevKeyboardCode = 0;

void setup() {
  // The board layour might make it easier to supply power via IO pin instead of 5V rail
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);

  Keyboard.begin();
  irrecv.enableIRIn();

  if (ENABLE_SERIAL == 1) {
    Serial.begin(9600);
    printMessage("program started");
  }
}

void loop() {
  // Returns 0 if no data ready, 1 if data ready.
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    if (ENABLE_SERIAL == 1) {
      printMessage("Code: ");
      Serial.println(code);
    }

    int keyboardCode = processIrCode(code, prevKeyboardCode);

    if (keyboardCode != 0) {
      prevKeyboardCode = keyboardCode;
      pressKey(keyboardCode);
    }

    irrecv.resume();  // Restart the ISR state machine and Receive the next value
  }
}

int processIrCode(uint32_t code, int prevKeyboardCode) {
  // array size is total size divided by the size of a single element
  int size = sizeof keyboardMappings / sizeof keyboardMappings[0];

  // If the IR code 0 is sent, repeat the previous keypress
  if (code == 0)
  {
    return prevKeyboardCode;
  }

  // Go through each mapping and press the corresponding key if it exists
  for (int i = 0; i < size; i++) {
    IRkeyboardMappings mapping = keyboardMappings[i];
    if (code == mapping.IRCode) {
      return mapping.KeyboardCode;
    }
  }

  return 0;
}

void pressKey(int keyCode) {
  Keyboard.press(keyCode);
  delay(10);
  Keyboard.releaseAll();
}

void printMessage(String message) {
  if (ENABLE_SERIAL == 1) {
    Serial.println(message);
  }
}
