#ifndef CD_HPP
#define CD_HPP

#include "Medien.hpp"

class CD : public Medien {
public:
    CD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code);

    std::string getTyp() const override;
};

#endif // CD_HPP
