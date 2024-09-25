#include "CSVHandler.hpp"
#include <iostream>
// CSV-Datei lesen
std::vector<std::vector<std::string>> CSVHandler::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}

// CSV-Datei überschreiben
void CSVHandler::writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}

// CSV-Datei anhängen
void CSVHandler::writeCSVAppend(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename, std::ios::app);  // Datei im Anhängemodus öffnen

    if (!file.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei zum Anhängen: " << filename << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}
