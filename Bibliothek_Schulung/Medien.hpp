#ifndef MEDIEN_HPP
#define MEDIEN_HPP

#include <string>

class Medien {
public:
    Medien(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code);
    virtual ~Medien() = default;

    std::string getAutor() const;
    std::string getTitel() const;
    std::string getKategorie() const;
    std::string getCode() const;

    virtual std::string getTyp() const = 0;

protected:
    std::string autor;
    std::string titel;
    std::string kategorie;
    std::string code;
};

#endif // MEDIEN_HPP
