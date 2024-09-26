#include "Nutzer.hpp"

using namespace std;

Nutzer::Nutzer(const string& vorname, const string& nachname, const string& strasse, int hausnummer,
    const string& plz, const string& ort, const string& email, const string& telefonnummer,
    const string& mitgliedsnummer)
    : vorname(vorname), nachname(nachname), strasse(strasse), hausnummer(hausnummer), plz(plz), ort(ort),
    email(email), telefonnummer(telefonnummer), mitgliedsnummer(mitgliedsnummer) {}

string Nutzer::getVorname() const {
    return vorname;
}

string Nutzer::getNachname() const {
    return nachname;
}

string Nutzer::getStrasse() const {
    return strasse;
}

int Nutzer::getHausnummer() const {
    return hausnummer;
}

string Nutzer::getPLZ() const {
    return plz;
}

string Nutzer::getOrt() const {
    return ort;
}

string Nutzer::getEmail() const {
    return email;
}

string Nutzer::getTelefonnummer() const {
    return telefonnummer;
}

string Nutzer::getMitgliedsnummer() const {
    return mitgliedsnummer;
}
