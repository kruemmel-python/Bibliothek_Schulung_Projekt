#ifndef CD_HPP
#define CD_HPP

#include "Medien.hpp"

class CD : public Medien {
public:
    CD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal); // Füge Regal hinzu

    std::string getTyp() const override;
    std::string getRegal() const; // Methode zum Abrufen des Regals

private:
    std::string regal; // Füge das Regal als Mitgliedsvariable hinzu
};

#endif // CD_HPP
