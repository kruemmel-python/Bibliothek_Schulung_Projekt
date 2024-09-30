#include "CD.hpp"

CD::CD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal)
    : Medien(autor, titel, kategorie, code, regal) {} // Füge Regal hinzu

std::string CD::getTyp() const {
    return "CD";
}
