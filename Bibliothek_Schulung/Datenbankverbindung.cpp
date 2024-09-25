#include "Datenbankverbindung.hpp"
#include <iostream>

// Konstruktor: Verbindet mit der SQLite-Datenbank
Datenbankverbindung::Datenbankverbindung(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Kann die Datenbank nicht öffnen: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

// Destruktor: Schließt die SQLite-Datenbank
Datenbankverbindung::~Datenbankverbindung() {
    if (db) {
        sqlite3_close(db);
    }
}

// Führt eine SQL-Abfrage aus, gibt true zurück, wenn erfolgreich
bool Datenbankverbindung::executeQuery(const std::string& query) {
    if (!db) {
        std::cerr << "Fehler: Keine gültige Datenbankverbindung." << std::endl;
        return false;
    }

    char* errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL-Fehler: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

// Überprüft, ob die Datenbankverbindung aktiv ist
bool Datenbankverbindung::isConnected() const {
    return db != nullptr;
}
