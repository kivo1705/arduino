#include <Esplora.h>  // Librería para el Arduino Esplora
#include <TFT.h>      // Librería para la pantalla TFT

// Definir colores en formato RGB
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define YELLOW 0xFFE0

void setup() {
  // Inicializar la pantalla del Esplora
  EsploraTFT.begin();
  EsploraTFT.background(255, 255, 255); // Fondo blanco
}

void loop() {
  // Leer el estado de los botones
  bool stateSquare = Esplora.readButton(SWITCH_DOWN);   // Botón hacia abajo
  bool stateCircle = Esplora.readButton(SWITCH_LEFT);   // Botón hacia la izquierda
  bool stateTriangle = Esplora.readButton(SWITCH_UP);   // Botón hacia arriba
  bool stateDiamond = Esplora.readButton(SWITCH_RIGHT); // Botón hacia la derecha

  static int size = 10; // Tamaño inicial de las figuras
  static int prevButton = -1; // Para seguir la figura anterior

  // Borrar la pantalla si se presiona un botón diferente
  if ((stateSquare && prevButton != SWITCH_DOWN) ||
      (stateCircle && prevButton != SWITCH_LEFT) ||
      (stateTriangle && prevButton != SWITCH_UP) ||
      (stateDiamond && prevButton != SWITCH_RIGHT)) {
    EsploraTFT.background(255, 255, 255); // Borrar pantalla
    prevButton = (stateSquare ? SWITCH_DOWN : 
                  (stateCircle ? SWITCH_LEFT :
                   (stateTriangle ? SWITCH_UP : 
                    (stateDiamond ? SWITCH_RIGHT : prevButton))));
  }

  // Coordenadas centrales
  int centerX = 64;
  int centerY = 64;

  // Dibujar la figura correspondiente al botón presionado
  if (stateSquare) {
    EsploraTFT.fillRect(centerX - size / 2, centerY - size / 2, size, size, BLUE);
  } else if (stateCircle) {
    EsploraTFT.fillCircle(centerX, centerY, size, RED);
  } else if (stateTriangle) {
    int x1 = centerX, y1 = centerY - size;
    int x2 = centerX - size, y2 = centerY + size;
    int x3 = centerX + size, y3 = centerY + size;
    EsploraTFT.fillTriangle(x1, y1, x2, y2, x3, y3, GREEN);
  } else if (stateDiamond) {
    int x = centerX;
    int y = centerY;
    EsploraTFT.fillTriangle(x, y - size, x - size, y, x + size, y, YELLOW);
    EsploraTFT.fillTriangle(x, y + size, x - size, y, x + size, y, YELLOW);
  }

  // Incrementar el tamaño si se mantiene el botón presionado
  if (stateSquare || stateCircle || stateTriangle || stateDiamond) {
    size++;
    delay(100);  // Controlar la velocidad de crecimiento de la figura
  } else {
    size = 10;  // Reiniciar el tamaño si no se presiona ningún botón
  }
}
