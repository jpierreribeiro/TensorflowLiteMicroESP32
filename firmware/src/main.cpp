#include <Arduino.h>
#include "NeuralNetwork.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

NeuralNetwork *nn;

char buffer[100];
char buffer2[100];

void setup()
{
  Serial.begin(115200);
  nn = new NeuralNetwork();
}

void loop()
{
  float number1 = random(100) / 100.0;
  float number2 = random(100) / 100.0;

  nn->getInputBuffer()[0] = number1;
  nn->getInputBuffer()[1] = number2;

  float result = nn->predict();

  const char *expected = number2 > number1 ? "True" : "False";

  const char *predicted = result > 0.5 ? "True" : "False";

  sprintf(buffer, "NUM 1: %.2f NUM2: %.2f - Resultado %.2f", number1, number2, result);
  sprintf(buffer2, " - Esperado %s, Previsto %s\n", expected, predicted);

  //Serial.println(buffer); testes e debug

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 45);
  tft.println(buffer);
  tft.println(buffer2);


  delay(10000);
}