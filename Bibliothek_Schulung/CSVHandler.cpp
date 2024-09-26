#include "CSVHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// CSV-Datei lesen
vector<vector<string>> CSVHandler::readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}

// CSV-Datei überschreiben
void CSVHandler::writeCSV(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);

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
void CSVHandler::writeCSVAppend(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename, ios::app);  // Datei im Anhängemodus öffnen

    if (!file.is_open()) {
        cerr << "Fehler beim Öffnen der Datei zum Anhängen: " << filename << endl;
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
