#include "GUI.hpp"

wxIMPLEMENT_APP(GUI);

bool GUI::OnInit() {
    MyFrame* frame = new MyFrame("wxWidgets Beispiel");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxButton* button = new wxButton(panel, wxID_ANY, "Schließen", wxPoint(10, 10));

    // Button-Klick mit Event-Handler verknüpfen
    Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
}

void MyFrame::OnButtonClick(wxCommandEvent& event) {
    Close(true);  // Schließt das Fenster
}
