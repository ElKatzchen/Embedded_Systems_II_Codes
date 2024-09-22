const int ledPin = 2;
String command = "";

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) 
  {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "ON")
    {
      digitalWrite(ledPin, LOW);
      Serial.print("LED TURNED ON\n");
    }
    else if (command == "OFF")
    {
      digitalWrite(ledPin, HIGH);
      Serial.print("LED TURNED OFF\n");
    }
  }
}
