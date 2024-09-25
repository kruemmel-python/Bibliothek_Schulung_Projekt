#include "Buch.hpp"

Buch::Buch(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code)
    : Medien(autor, titel, kategorie, code) {}

std::string Buch::getTyp() const {
    return "Buch";
}
