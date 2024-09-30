#ifndef MEDIEN_HPP
#define MEDIEN_HPP

#include <string>

class Medien {
public:
    Medien(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal); // Füge Regal hinzu
    virtual ~Medien() = default;

    std::string getAutor() const;
    std::string getTitel() const;
    std::string getKategorie() const;
    std::string getCode() const;
    std::string getRegal() const; // Füge Methode zum Abrufen des Regals hinzu

    virtual std::string getTyp() const = 0;

protected:
    std::string autor;
    std::string titel;
    std::string kategorie;
    std::string code;
    std::string regal; // Füge Regal als Mitgliedsvariable hinzu
};

#endif // MEDIEN_HPP
