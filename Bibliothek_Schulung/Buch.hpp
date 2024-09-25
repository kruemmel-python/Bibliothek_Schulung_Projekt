#ifndef BUCH_HPP
#define BUCH_HPP

#include "Medien.hpp"

class Buch : public Medien {
public:
    Buch(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code);

    std::string getTyp() const override;
};

#endif // BUCH_HPP
