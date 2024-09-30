#ifndef DVD_HPP
#define DVD_HPP

#include "Medien.hpp"

class DVD : public Medien {
public:
    DVD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal); // Füge Regal hinzu

    std::string getTyp() const override;
    std::string getRegal() const; // Methode zum Abrufen des Regals

private:
    std::string regal; // Füge das Regal als Mitgliedsvariable hinzu
};

#endif // DVD_HPP
