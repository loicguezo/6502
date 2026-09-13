// main script used as a debug interface for the 6502 processor kit
// from Ben Eater [https://eater.net]. This arduino script is
// originally made for the arduino uno r3.

#define CLOCK_PIN 13
#define INPUT_PINS 8
#define CLOCK_MS 10

int inputs[INPUT_PINS] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{
  Serial.begin(9600);
  pinMode(10, INPUT);

  for (int i = 0; i < INPUT_PINS; i++)
  {
    pinMode(inputs[i], INPUT);
  }

  pinMode(CLOCK_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(CLOCK_PIN, HIGH);
  delay(CLOCK_MS);

  byte value = 0;
  for (int i = 0; i < INPUT_PINS; i++)
  {
    int bitValue = digitalRead(inputs[i]);
    value |= (bitValue << i);
  }

  bool resetPressed = (digitalRead(10) == LOW);

  Serial.print("Bus = 0x");
  if (value < 0x10) Serial.print("0");
  Serial.print(value, HEX);
  Serial.print("  (");
  for (int i = INPUT_PINS - 1; i >= 0; i--)
  {
    Serial.print((value >> i) & 1);
  }
  Serial.print(")");
  Serial.print("  RESET=");
  Serial.println(resetPressed ? "true" : "false");

  digitalWrite(CLOCK_PIN, LOW);
  delay(CLOCK_MS);
  Serial.flush();
}
