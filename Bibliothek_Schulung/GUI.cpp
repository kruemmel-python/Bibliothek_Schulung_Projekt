#include "GUI.hpp"

// Konstruktor der GUI, erstellt ein einfaches Fenster mit Titel
MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    // Leeres Fenster, keine Widgets hinzugefügt
}
