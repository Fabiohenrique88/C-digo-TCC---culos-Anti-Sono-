#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

BluetoothSerial SerialBT;
#define buzzer 26
#define out 27

// Pinos do led RGB

// Variaveis cores
int red = 0;
int green = 0;
int blue = 0;

void setup()
{
  pinMode(out, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("TCC_FABIO");
  Serial.println("O dispositivo já pode ser pareado!");
}

void loop()
{
  // Detecta a cor
  color();

  if (red < 50 && blue < 50 && green < 50)
  {
    digitalWrite(buzzer, HIGH);
    SerialBT.write((uint8_t *)"C", 1); // Envia o caracter C para o aplicativo acionar a notificação
    delay(10);
  }
  else
    digitalWrite(buzzer, LOW);
  delay(1000);
}

void color()
{
  // Rotina que le o valor das cores
  // count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  // count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  // count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}