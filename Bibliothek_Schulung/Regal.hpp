#ifndef REGAL_HPP
#define REGAL_HPP

#include "Medien.hpp"
#include <vector>
#include <string>
#include <memory>

class Regal {
public:
    Regal(const std::string& name, int capacity);

    bool addMedium(std::shared_ptr<Medien> medium);
    bool removeMedium(const std::string& title);
    void displayInhalte() const;

    // Methode, um nur Bücher im Regal anzuzeigen
    void displayBooks() const;

    const std::string& getName() const;

private:
    std::string name;
    int capacity;
    std::vector<std::shared_ptr<Medien>> medienListe;
};

#endif
