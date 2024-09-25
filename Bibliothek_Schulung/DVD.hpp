#ifndef DVD_HPP
#define DVD_HPP

#include "Medien.hpp"

class DVD : public Medien {
public:
    DVD(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code);

    std::string getTyp() const override;
};

#endif // DVD_HPP
