#ifndef GUI_HPP
#define GUI_HPP

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

#endif // GUI_HPP
