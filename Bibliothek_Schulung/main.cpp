#include <winsock2.h> // Für Windows Konsolen-Codierung
#include "Bibliothek.hpp"
#include "Terminal.hpp"
#include "GUI.hpp"
#include <iostream>
#include <wx/wx.h>

// Definiere die App-Klasse für wxWidgets
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    Bibliothek bibliothek("bibliothek.db"); // Bibliothek-Objekt erstellen
    MyFrame* frame = new MyFrame("Bibliothek Management", bibliothek); // Bibliothek an Frame übergeben
    frame->Show(true);
    return true;
}

int main(int argc, char** argv) {
    // Setze die Konsolen-Codierung auf UTF-8 für die Ausgabe und Eingabe
    SetConsoleOutputCP(CP_UTF8);  // Setzt die Konsolen-Ausgabe auf UTF-8
    SetConsoleCP(CP_UTF8);        // Setzt die Konsolen-Eingabe auf UTF-8

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
        // GUI wird über wxWidgets-Framework automatisch gestartet
        return wxEntry(argc, argv);  // wxWidgets Anwendung starten
    }
    else {
        std::cout << "Ungültige Auswahl. Programm wird beendet." << std::endl;
    }

    return 0;
}
