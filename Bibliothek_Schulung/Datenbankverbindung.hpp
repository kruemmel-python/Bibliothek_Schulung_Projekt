#ifndef DATENBANKVERBINDUNG_HPP
#define DATENBANKVERBINDUNG_HPP

#include <sqlite3.h>
#include <string>

class Datenbankverbindung {
public:
    // Konstruktor: Öffnet die Datenbank
    Datenbankverbindung(const std::string& dbName);

    // Destruktor: Schließt die Datenbankverbindung
    ~Datenbankverbindung();

    // Führt eine SQL-Abfrage aus, gibt true zurück, wenn erfolgreich
    bool executeQuery(const std::string& query);

    // Überprüft, ob die Datenbankverbindung aktiv ist
    bool isConnected() const;

private:
    sqlite3* db;  // Datenbank-Handle
};

#endif // DATENBANKVERBINDUNG_HPP
