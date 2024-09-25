#include <windows.h>  // Nur erforderlich für Windows, um die Konsolen-Codierung zu ändern
#include "Bibliothek.hpp"
#include "Terminal.hpp"

int main() {
    // Setze die Konsolen-Codierung auf UTF-8 für die Ausgabe und Eingabe
    SetConsoleOutputCP(CP_UTF8);  // Setzt die Konsolen-Ausgabe auf UTF-8
    SetConsoleCP(CP_UTF8);        // Setzt die Konsolen-Eingabe auf UTF-8

    // Bibliothek initialisieren
    Bibliothek bibliothek("bibliothek.db");
    Terminal terminal(bibliothek);

    // Terminal starten
    terminal.start();

    return 0;
}
