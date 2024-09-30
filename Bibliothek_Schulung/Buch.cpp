#include "Buch.hpp"

Buch::Buch(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal)
    : Medien(autor, titel, kategorie, code, regal) {} // Füge Regal hinzu

std::string Buch::getTyp() const {
    return "Buch";
}
