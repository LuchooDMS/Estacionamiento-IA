String datos = "";

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 0 = libre, 1 = ocupado
int lugares[8] = {0,1,0,1,0,0,1,0};

void dibujarNumeros() {
  display.setTextSize(3);
  display.setTextColor(WHITE);

  for(int i=0; i<4; i++){
    display.setCursor(8 + i*32, 5);
    display.print(i+1);
  }

  for(int i=0; i<4; i++){
    display.setCursor(8 + i*32, 35);
    display.print(i+5);
  }
}

void dibujarEstados() {

  for(int i=0; i<4; i++){
    int x = 8 + i*32;
    int y = 5;

    if(lugares[i] == 1){
      display.drawLine(x, y, x+20, y+20, WHITE);
      display.drawLine(x+20, y, x, y+20, WHITE);
    } else {
      display.drawLine(x, y+10, x+8, y+18, WHITE);
      display.drawLine(x+8, y+18, x+20, y, WHITE);
    }
  }

  for(int i=0; i<4; i++){
    int x = 8 + i*32;
    int y = 35;

    if(lugares[i+4] == 1){
      display.drawLine(x, y, x+20, y+20, WHITE);
      display.drawLine(x+20, y, x, y+20, WHITE);
    } else {
      display.drawLine(x, y+10, x+8, y+18, WHITE);
      display.drawLine(x+8, y+18, x+20, y, WHITE);
    }
  }
}

// 🔥 transición simple (dos veces)
void transicionSuave() {
  display.invertDisplay(true);
  delay(80);
  display.invertDisplay(false);
  delay(80);
  display.invertDisplay(true);
  delay(80);
  display.invertDisplay(false);
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(115200);
}

void loop() {

  // 📥 leer datos desde Python
  if (Serial.available()) {

    datos = Serial.readStringUntil('\n');

    int index = 0;

    for (int i = 0; i < 8; i++) {
      int coma = datos.indexOf(',', index);

      if (coma == -1) {
        lugares[i] = datos.substring(index).toInt();
      } else {
        lugares[i] = datos.substring(index, coma).toInt();
        index = coma + 1;
      }
    }
  }

  // 🔢 pantalla números
  display.clearDisplay();
  dibujarNumeros();
  display.display();
  delay(2500);

  transicionSuave();

  // ❌✔ pantalla estado
  display.clearDisplay();
  dibujarEstados();
  display.display();
  delay(2500);

  transicionSuave();
}
