#include "Nutzer.hpp"

Nutzer::Nutzer(const std::string& vorname, const std::string& nachname, const std::string& strasse, int hausnummer,
    const std::string& plz, const std::string& ort, const std::string& email, const std::string& telefonnummer,
    const std::string& mitgliedsnummer)
    : vorname(vorname), nachname(nachname), strasse(strasse), hausnummer(hausnummer), plz(plz), ort(ort),
    email(email), telefonnummer(telefonnummer), mitgliedsnummer(mitgliedsnummer) {}

std::string Nutzer::getVorname() const {
    return vorname;
}

std::string Nutzer::getNachname() const {
    return nachname;
}

std::string Nutzer::getStrasse() const {
    return strasse;
}

int Nutzer::getHausnummer() const {
    return hausnummer;
}

std::string Nutzer::getPLZ() const {
    return plz;
}

std::string Nutzer::getOrt() const {
    return ort;
}

std::string Nutzer::getEmail() const {
    return email;
}

std::string Nutzer::getTelefonnummer() const {
    return telefonnummer;
}

std::string Nutzer::getMitgliedsnummer() const {
    return mitgliedsnummer;
}
