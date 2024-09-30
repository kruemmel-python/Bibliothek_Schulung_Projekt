#ifndef GUI_HPP
#define GUI_HPP

#include <wx/wx.h>

class GUI : public wxApp {
public:
    virtual bool OnInit();  // wxWidgets Initialisierung
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnButtonClick(wxCommandEvent& event);  // Event-Handler für den Button
};



#endif
