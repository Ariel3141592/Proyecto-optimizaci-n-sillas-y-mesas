#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <SFML/Graphics.hpp>
using namespace std;

// Estructuras globales para mantener la info
float precioMesa, precioSilla;
vector<vector<float>> restricciones; // cada restricción: [coef_x, coef_y, constante]

// Función objetivo
float coefX, coefY; // coeficientes de la función objetivo z = coefX * x + coefY * y

// Función para ingresar precios
void opcion1() {
    cout << "Ingrese el precio de cada mesa: ";
    cin >> precioMesa;
    cout << "Ingrese el precio de cada silla: ";
    cin >> precioSilla;
    cout << fixed << setprecision(2);
    cout << "Los precios fueron registrados: mesas USD " << precioMesa << " y sillas USD " << precioSilla << ".\n";
}

// Función para ingresar restricciones
void opcion2() {
    int n;
    cout << "Ingrese el número de restricciones: ";
    cin >> n;
    restricciones.clear();
    for (int i = 0; i < n; ++i) {
        float a, b, c;
        cout << "Restricción " << i + 1 << ": formato ax + by <= c\n";
        cout << "Ingrese a: "; cin >> a;
        cout << "Ingrese b: "; cin >> b;
        cout << "Ingrese c: "; cin >> c;
        restricciones.push_back({a, b, c});
    }
    cout << "Restricciones registradas correctamente.\n";
}

// Función para ingresar función de ganancia
void opcion3() {
    cout << "Ingrese el coeficiente de x (mesas) en la función de ganancia: ";
    cin >> coefX;
    cout << "Ingrese el coeficiente de y (sillas) en la función de ganancia: ";
    cin >> coefY;
    cout << "Función de ganancia: Max Z = " << coefX << "x + " << coefY << "y\n";
}

// Verifica si un punto (x, y) satisface todas las restricciones
bool esFactible(int x, int y) {
    for (const auto& r : restricciones) {
        if (r[0]*x + r[1]*y > r[2])
            return false;
    }
    return true;
}

// Cálculo de la solución óptima (método de fuerza bruta discreto)
int optX = 0, optY = 0;
float mejorGanancia = -1;
void opcion4() {
    int maxX = 100, maxY = 100;
    mejorGanancia = -1;
    for (int x = 0; x <= maxX; ++x) {
        for (int y = 0; y <= maxY; ++y) {
            if (esFactible(x, y)) {
                float ganancia = coefX * x + coefY * y;
                if (ganancia > mejorGanancia) {
                    mejorGanancia = ganancia;
                    optX = x;
                    optY = y;
                }
            }
        }
    }
    cout << "Solución óptima: No. de sillas = " << optY << ", No. de mesas = " << optX << ", Ganancia máxima = $" << mejorGanancia << "\n";
}

// Opción 5: Visualización gráfica con SFML
void opcion5() {
    const int windowSize = 600;
    const float escala = 6.0f; // para mapear 100x100 en 600x600

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Área Factible y Solución Óptima");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Dibujar área factible
        for (int x = 0; x <= 100; ++x) {
            for (int y = 0; y <= 100; ++y) {
                if (esFactible(x, y)) {
                    sf::RectangleShape punto(sf::Vector2f(1, 1));
                    punto.setFillColor(sf::Color(200, 200, 255));
                    punto.setPosition(x * escala, windowSize - y * escala);
                    window.draw(punto);
                }
            }
        }

        // Dibujar punto óptimo
        sf::CircleShape optimo(4);
        optimo.setFillColor(sf::Color::Red);
        optimo.setPosition(optX * escala - 2, windowSize - optY * escala - 2);
        window.draw(optimo);

        window.display();
    }
}

// Menú principal
int main() {
    int opcion;
    do {
        cout << "MENÚ PRINCIPAL\n";
        cout << "1. Ingreso de precios de venta\n";
        cout << "2. Ingreso de restricciones de producción\n";
        cout << "3. Ingreso de la función de ganancia\n";
        cout << "4. Cálculo de la solución óptima\n";
        cout << "5. Solución gráfica del problema de optimización\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1: opcion1(); break;
            case 2: opcion2(); break;
            case 3: opcion3(); break;
            case 4: opcion4(); break;
            case 5: opcion5(); break;
            case 6: cout << "Saliendo del programa.\n"; break;
            default: cout << "Opción no válida.\n";
        }
    } while (opcion != 6);

    return 0;
}
