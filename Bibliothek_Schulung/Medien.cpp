#include "Medien.hpp"

using namespace std;

Medien::Medien(const string& autor, const string& titel, const string& kategorie, const string& code)
    : autor(autor), titel(titel), kategorie(kategorie), code(code) {}

string Medien::getAutor() const {
    return autor;
}

string Medien::getTitel() const {
    return titel;
}

string Medien::getKategorie() const {
    return kategorie;
}

string Medien::getCode() const {
    return code;
}
