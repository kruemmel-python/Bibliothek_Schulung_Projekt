#include <winsock2.h> // Für Windows Konsolen-Codierung
#include "Bibliothek.hpp"
#include "Terminal.hpp"
#include "GUI.hpp"
#include <iostream>

int main(int argc, char** argv) {
    // Setze die Konsolen-Codierung auf UTF-8 für die Ausgabe und Eingabe
    SetConsoleOutputCP(CP_UTF8);  // Setzt die Konsolen-Ausgabe auf UTF-8
    SetConsoleCP(CP_UTF8);        // Setzt die Konsolen-Eingabe auf UTF-8
    // wxWidgets-Anwendung starten

    int auswahl = 0;
    std::cout << "Wählen Sie den Modus:\n";
    std::cout << "1. Konsolenmodus (Terminal)\n";
    std::cout << "2. GUI-Modus (wxWidgets)\n";
    std::cout << "Auswahl: ";
    std::cin >> auswahl;

    if (auswahl == 1) {
        // Bibliothek initialisieren
        Bibliothek bibliothek("bibliothek.db");
        Terminal terminal(bibliothek);
        // Terminal starten
        terminal.start();
    }
    else if (auswahl == 2) {
        // wxWidgets GUI starten
        wxDISABLE_DEBUG_SUPPORT();  // wxWidgets spezifisch für Debug-Builds

        if (!wxEntryStart(argc, argv)) {
            return -1;  // Fehler beim Starten von wxWidgets
        }

        // Event-Schleife starten
        wxTheApp->CallOnInit();
        wxTheApp->OnRun();

        // wxWidgets aufräumen
        wxEntryCleanup();
    }
    else {
        std::cout << "Ungültige Auswahl. Programm wird beendet." << std::endl;
    }

    return 0;
}
