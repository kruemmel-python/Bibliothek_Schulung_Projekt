#include "Medien.hpp"

Medien::Medien(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code)
    : autor(autor), titel(titel), kategorie(kategorie), code(code) {}

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
