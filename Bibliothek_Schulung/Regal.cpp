#include "Regal.hpp"
#include <iostream>

Regal::Regal(const std::string& name, int capacity) : name(name), capacity(capacity) {}

bool Regal::addMedium(std::shared_ptr<Medien> medium) {
    if (medienListe.size() >= capacity) {
        return false;  // Regal ist voll
    }
    medienListe.push_back(medium);
    return true;
}

bool Regal::removeMedium(const std::string& title) {
    for (auto it = medienListe.begin(); it != medienListe.end(); ++it) {
        if ((*it)->getTitel() == title) {
            medienListe.erase(it);
            return true;
        }
    }
    return false;
}

// Anzeige aller Medien im Regal
void Regal::displayInhalte() const {
    for (const auto& medium : medienListe) {
        std::cout << "Typ: " << medium->getTyp()
            << " | Autor: " << medium->getAutor()
            << " | Titel: " << medium->getTitel()
            << " | Kategorie: " << medium->getKategorie()
            << " | Code: " << medium->getCode() << std::endl;
    }
}

// Anzeige nur der Bücher im Regal
void Regal::displayBooks() const {
    for (const auto& medium : medienListe) {
        if (medium->getTyp() == "Buch") {
            std::cout << "Autor: " << medium->getAutor()
                << " | Titel: " << medium->getTitel()
                << " | Kategorie: " << medium->getKategorie()
                << " | Code: " << medium->getCode() << std::endl;
        }
    }
}

const std::string& Regal::getName() const {
    return name;
}
