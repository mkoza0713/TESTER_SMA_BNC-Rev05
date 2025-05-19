#include <Arduino.h>

#define ledRed 14
#define ledGreen 15
#define ledBlue 16

#define smaPin1 8
#define smaPin2 12
#define smaShield1 9
#define smaShield2 13
#define testSwitchSma 10

#define bncPin1 7
#define bncPin2 5
#define bncShield1 6
#define bncShield2 4
#define testSwitchBnc 17

// deklaracje zmiennych
void testBnc();
void testSma();
void signatureLed(byte status);
void startLedSignature();

void setup()
{
  Serial.begin(9600);
  pinMode(testSwitchBnc, INPUT_PULLUP);
  pinMode(testSwitchSma, INPUT_PULLUP);
  startLedSignature();
}
void loop()
{
  testSma();
  testBnc();
}
void testBnc()
{
  byte testResult = true;
  static byte testSteps = 0;

  // rozpoczecie testu
  if (digitalRead(testSwitchBnc) == LOW)
  {
    switch (testSteps)
    {
    case 0:
      // TEST CIAGLOSCI ZYLY
      signatureLed(3); // niebieska

      pinMode(bncPin1, INPUT_PULLUP);
      pinMode(bncPin2, OUTPUT);
      digitalWrite(bncPin2, LOW);
      if (digitalRead(bncPin1) == HIGH)
      { // wykryto brak polaczenia
        testResult = false;
        testSteps = 3; // wynik false
        Serial.println("Test zyly BNC NOK");
      }
      else if (digitalRead(bncPin1) == LOW)
      {
        testSteps = 1;
        Serial.println("Test zyly BNC OK");
      }
      break;
    case 1:
      // TEST CIAGLOSCI EKRANU
      signatureLed(3); // niebieska

      pinMode(bncShield1, INPUT_PULLUP);
      pinMode(bncShield2, OUTPUT);
      digitalWrite(bncShield2, LOW);
      if (digitalRead(bncShield1) == HIGH)
      { // wykryto brak polaczenia
        testResult = false;
        testSteps = 3; // wynik false
        Serial.println("Test ekranu BNC NOK");
      }
      else if (digitalRead(bncShield1) == LOW)
      {
        testSteps = 2;
        Serial.println("Test ekranu BNC OK");
      }
      break;
    case 2:
      // TEST ZWARCIA EKRANU Z ZYLA
      pinMode(bncPin2, OUTPUT);
      pinMode(bncShield2, OUTPUT);
      pinMode(bncShield1, OUTPUT);
      pinMode(bncPin1, INPUT_PULLUP);

      digitalWrite(bncPin2, HIGH);
      digitalWrite(bncShield2, LOW);
      digitalWrite(bncShield1, LOW);

      if (digitalRead(bncPin1) == LOW)
      {
        testResult = false;
        testSteps = 3;
        Serial.println("ZWARCIE BNC");
        signatureLed(4);
      }
      else if (digitalRead(bncPin1) == HIGH)
      {
        testSteps = 3;
        Serial.println("Test zwarcia BNC OK");
      }
      break;
    case 3:
      break;
    }
  }

  // wynik testu
  if (testResult && testSteps == 3)
  {
    Serial.println("Test BNC OK");
    Serial.println("");
    testSteps = 0;
    signatureLed(2);
  }
  else if (!testResult && testSteps == 3)
  {
    Serial.println("Test BNC NIEOK");
    Serial.println("");
    testSteps = 0;
    signatureLed(1);
  }

  // stan neutralny po tescie
  pinMode(bncPin2, OUTPUT);
  pinMode(bncShield2, OUTPUT);
  pinMode(bncShield1, OUTPUT);
  pinMode(bncPin1, OUTPUT);

  digitalWrite(bncPin1, LOW);
  digitalWrite(bncPin2, LOW);
  digitalWrite(bncShield2, LOW);
  digitalWrite(bncShield1, LOW);
}
void testSma()
{
  byte testResult = true;
  static byte testSteps = 0;

  // rozpoczecie testu
  if (digitalRead(testSwitchSma) == LOW)
  {
    switch (testSteps)
    {
    case 0:
      // TEST CIAGLOSCI ZYLY
      signatureLed(3); // niebieska

      pinMode(smaPin1, INPUT_PULLUP);
      pinMode(smaPin2, OUTPUT);
      digitalWrite(smaPin2, LOW);
      if (digitalRead(smaPin1) == HIGH)
      { // wykryto brak polaczenia
        testResult = false;
        testSteps = 3; // wynik false
        Serial.println("Test zyly SMA NOK");
      }
      else if (digitalRead(smaPin1) == LOW)
      {
        testSteps = 1;
        Serial.println("Test zyly SMA OK");
      }
      break;

    case 1:
      // TEST CIAGLOSCI EKRANU
      signatureLed(3); // niebieska

      pinMode(smaShield1, INPUT_PULLUP);
      pinMode(smaShield2, OUTPUT);
      digitalWrite(smaShield2, LOW);
      if (digitalRead(smaShield1) == HIGH)
      { // wykryto brak polaczenia
        testResult = false;
        testSteps = 3; // wynik false
        Serial.println("Test ekranu SMA NOK");
      }
      else if (digitalRead(smaShield1) == LOW)
      {
        testSteps = 2;
        Serial.println("Test ekranu SMA OK");
      }
      break;

    case 2:
      // TEST ZWARCIA EKRANU Z ZYLA
      pinMode(smaPin2, OUTPUT);
      pinMode(smaShield2, OUTPUT);
      pinMode(smaShield1, OUTPUT);
      pinMode(smaPin1, INPUT_PULLUP);

      digitalWrite(smaPin2, HIGH);
      digitalWrite(smaShield2, LOW);
      digitalWrite(smaShield1, LOW);

      if (digitalRead(smaPin1) == LOW)
      {
        testResult = false;
        testSteps = 3;
        Serial.println("ZWARCIE SMA");
        signatureLed(4);
      }
      else if (digitalRead(smaPin1) == HIGH)
      {
        testSteps = 3;
        Serial.println("Test zwarcia SMA OK");
      }
      break;

    case 3:
      break;
    }
  }

  // wynik testu
  if (testResult && testSteps == 3)
  {
    Serial.println("Test SMA OK");
    Serial.println("");
    testSteps = 0;
    signatureLed(2);
  }
  else if (!testResult && testSteps == 3)
  {
    Serial.println("Test SMA NIEOK");
    Serial.println("");
    testSteps = 0;
    signatureLed(1);
  }

  // stan neutralny po tescie
  pinMode(smaPin2, OUTPUT);
  pinMode(smaShield2, OUTPUT);
  pinMode(smaShield1, OUTPUT);
  pinMode(smaPin1, OUTPUT);

  digitalWrite(smaPin1, LOW);
  digitalWrite(smaPin2, LOW);
  digitalWrite(smaShield2, LOW);
  digitalWrite(smaShield1, LOW);
}
void signatureLed(byte status)
{
  switch (status)
  {
  case 1: // blad
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, HIGH);
    delay(2000);
    digitalWrite(ledRed, LOW);
    break;
  case 2: // ok
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledGreen, HIGH);
    delay(2000);
    digitalWrite(ledGreen, LOW);
    break;
  case 3: // oczekiwanie na test
    digitalWrite(ledBlue, HIGH);
    break;
  case 4: // zwarcie
    for (byte i = 0; i < 4; i++)
    {
      digitalWrite(ledRed, HIGH);
      delay(100);
      digitalWrite(ledRed, LOW);
      delay(100);
    }
    break;
  }
}
void startLedSignature()
{
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  for (byte i = 0; i < 2; i++)
  {
    digitalWrite(ledRed, HIGH);
    delay(50);
    digitalWrite(ledRed, LOW);
    delay(50);
  }
  for (byte i = 0; i < 2; i++)
  {
    digitalWrite(ledBlue, HIGH);
    delay(50);
    digitalWrite(ledBlue, LOW);
    delay(50);
  }
  for (byte i = 0; i < 2; i++)
  {
    digitalWrite(ledGreen, HIGH);
    delay(50);
    digitalWrite(ledGreen, LOW);
    delay(50);
  }
}