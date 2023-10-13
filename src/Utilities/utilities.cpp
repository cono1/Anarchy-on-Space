#include "utilities.h"

#include <raylib.h>

namespace game
{
Vector2 GetRandomPositionNearEdges(int margin)
{
    Vector2 pos = { 0,0 };
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();;

    // Genera un valor aleatorio para determinar el lado del borde.
    // 0: Izquierda, 1: Derecha, 2: Arriba, 3: Abajo.
    int side = GetRandomValue(0, 4);

    switch (side)
    {
    case 0: // Izquierda
        pos.x = static_cast<float>(GetRandomValue(1, margin)); // Valores cercanos al borde izquierdo.
        pos.y = static_cast<float>(GetRandomValue(0, windowHeight));
        break;

    case 1: // Derecha
        pos.x = windowWidth - static_cast<float>(GetRandomValue(1, margin)); // Valores cercanos al borde derecho.
        pos.y = static_cast<float>(GetRandomValue(0, windowHeight));                  // Cualquier posición vertical.
        break;

    case 2: // Arriba
        pos.x = static_cast<float>(GetRandomValue(0, windowWidth));  // Cualquier posición horizontal.
        pos.y = static_cast<float>(GetRandomValue(1, margin)); // Valores cercanos al borde superior.
        break;

    case 3: // Abajo
        pos.x = static_cast<float>(GetRandomValue(0, windowWidth));      // Cualquier posición horizontal.
        pos.y = windowHeight - static_cast<float>(GetRandomValue(1, margin)); // Valores cercanos al borde inferior.
        break;
    }
    return pos;
}
}