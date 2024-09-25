#include "DVD.hpp"

DVD::DVD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code)
    : Medien(autor, titel, kategorie, code) {}

std::string DVD::getTyp() const {
    return "DVD";
}
