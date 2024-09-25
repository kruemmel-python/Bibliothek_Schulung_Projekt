#include "CD.hpp"

CD::CD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code)
    : Medien(autor, titel, kategorie, code) {}

std::string CD::getTyp() const {
    return "CD";
}
