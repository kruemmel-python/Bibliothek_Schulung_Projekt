#include "wx/wx.h"
#include "Bibliothek.hpp"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, Bibliothek& bibliothek);

private:
    Bibliothek& bibliothek;
    void OnListeMedien(wxCommandEvent& event);
    void OnListeNutzer(wxCommandEvent& event);
    void OnLadeMedienAusCSV(wxCommandEvent& event);
    void OnLadeNutzerAusCSV(wxCommandEvent& event);
    void OnMediumHinzufuegen(wxCommandEvent& event);
    void OnNutzerHinzufuegen(wxCommandEvent& event);
    void OnMediumEntfernen(wxCommandEvent& event);
    void OnNutzerEntfernen(wxCommandEvent& event);
    void OnSucheMedien(wxCommandEvent& event);
    void OnSucheNutzer(wxCommandEvent& event);
    void OnSucheRegal(wxCommandEvent& event);
    void OnBeenden(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_ListeMedien = 1,
    ID_ListeNutzer,
    ID_LadeMedienAusCSV,
    ID_LadeNutzerAusCSV,
    ID_MediumHinzufuegen,
    ID_NutzerHinzufuegen,
    ID_MediumEntfernen,
    ID_NutzerEntfernen,
    ID_SucheMedien,
    ID_SucheNutzer,
    ID_SucheRegal,
    ID_Beenden
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_ListeMedien, MyFrame::OnListeMedien)
EVT_MENU(ID_ListeNutzer, MyFrame::OnListeNutzer)
EVT_MENU(ID_LadeMedienAusCSV, MyFrame::OnLadeMedienAusCSV)
EVT_MENU(ID_LadeNutzerAusCSV, MyFrame::OnLadeNutzerAusCSV)
EVT_MENU(ID_MediumHinzufuegen, MyFrame::OnMediumHinzufuegen)
EVT_MENU(ID_NutzerHinzufuegen, MyFrame::OnNutzerHinzufuegen)
EVT_MENU(ID_MediumEntfernen, MyFrame::OnMediumEntfernen)
EVT_MENU(ID_NutzerEntfernen, MyFrame::OnNutzerEntfernen)
EVT_MENU(ID_SucheMedien, MyFrame::OnSucheMedien)
EVT_MENU(ID_SucheNutzer, MyFrame::OnSucheNutzer)
EVT_MENU(ID_SucheRegal, MyFrame::OnSucheRegal)
EVT_MENU(ID_Beenden, MyFrame::OnBeenden)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, Bibliothek& bibliothek)
    : wxFrame(NULL, wxID_ANY, title), bibliothek(bibliothek) {
    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_ListeMedien, "Medien auflisten");
    menuFile->Append(ID_ListeNutzer, "Nutzer auflisten");
    menuFile->Append(ID_LadeMedienAusCSV, "Medien aus CSV laden");
    menuFile->Append(ID_LadeNutzerAusCSV, "Nutzer aus CSV laden");
    menuFile->Append(ID_MediumHinzufuegen, "Medium hinzufügen");
    menuFile->Append(ID_NutzerHinzufuegen, "Nutzer hinzufügen");
    menuFile->Append(ID_MediumEntfernen, "Medium entfernen");
    menuFile->Append(ID_NutzerEntfernen, "Nutzer entfernen");
    menuFile->Append(ID_SucheMedien, "Medien suchen");
    menuFile->Append(ID_SucheNutzer, "Nutzer suchen");
    menuFile->Append(ID_SucheRegal, "Regal suchen und Bücher anzeigen");
    menuFile->Append(ID_Beenden, "Beenden");
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);
}

void MyFrame::OnListeMedien(wxCommandEvent& event) {
    bibliothek.listeMedien();
}

void MyFrame::OnListeNutzer(wxCommandEvent& event) {
    bibliothek.listeNutzer();
}

void MyFrame::OnLadeMedienAusCSV(wxCommandEvent& event) {
    bibliothek.ladeMedienAusCSV();
}

void MyFrame::OnLadeNutzerAusCSV(wxCommandEvent& event) {
    bibliothek.ladeNutzerAusCSV();
}

void MyFrame::OnMediumHinzufuegen(wxCommandEvent& event) {
    // Implementiere die Logik zum Hinzufügen eines Mediums
}

void MyFrame::OnNutzerHinzufuegen(wxCommandEvent& event) {
    // Implementiere die Logik zum Hinzufügen eines Nutzers
}

void MyFrame::OnMediumEntfernen(wxCommandEvent& event) {
    // Implementiere die Logik zum Entfernen eines Mediums
}

void MyFrame::OnNutzerEntfernen(wxCommandEvent& event) {
    // Implementiere die Logik zum Entfernen eines Nutzers
}

void MyFrame::OnSucheMedien(wxCommandEvent& event) {
    // Implementiere die Logik zum Suchen von Medien
}

void MyFrame::OnSucheNutzer(wxCommandEvent& event) {
    // Implementiere die Logik zum Suchen von Nutzern
}

void MyFrame::OnSucheRegal(wxCommandEvent& event) {
    // Implementiere die Logik zum Suchen eines Regals und Anzeigen der Bücher
}

void MyFrame::OnBeenden(wxCommandEvent& event) {
    Close(true);
}
