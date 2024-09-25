#ifndef NUTZER_HPP
#define NUTZER_HPP

#include <string>

class Nutzer {
public:
    Nutzer(const std::string& vorname, const std::string& nachname, const std::string& strasse, int hausnummer,
        const std::string& plz, const std::string& ort, const std::string& email, const std::string& telefonnummer,
        const std::string& mitgliedsnummer);

    std::string getVorname() const;
    std::string getNachname() const;
    std::string getStrasse() const;
    int getHausnummer() const;
    std::string getPLZ() const;
    std::string getOrt() const;
    std::string getEmail() const;
    std::string getTelefonnummer() const;
    std::string getMitgliedsnummer() const;

private:
    std::string vorname;
    std::string nachname;
    std::string strasse;
    int hausnummer;
    std::string plz;
    std::string ort;
    std::string email;
    std::string telefonnummer;
    std::string mitgliedsnummer;
};

#endif // NUTZER_HPP
