#include "Medien.hpp"

Medien::Medien(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal)
    : autor(autor), titel(titel), kategorie(kategorie), code(code), regal(regal) {} // Initialisiere das Regal

std::string Medien::getAutor() const {
    return autor;
}

std::string Medien::getTitel() const {
    return titel;
}

std::string Medien::getKategorie() const {
    return kategorie;
}

std::string Medien::getCode() const {
    return code;
}

std::string Medien::getRegal() const {
    return regal; // Füge Methode zum Abrufen des Regals hinzu
}
