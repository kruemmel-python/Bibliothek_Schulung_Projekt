#ifndef DATENBANKVERBINDUNG_HPP
#define DATENBANKVERBINDUNG_HPP

#include <sqlite3.h>
#include <string>

class Datenbankverbindung {
public:
    // Konstruktor: �ffnet die Datenbank
    Datenbankverbindung(const std::string& dbName);

    // Destruktor: Schlie�t die Datenbankverbindung
    ~Datenbankverbindung();

    // F�hrt eine SQL-Abfrage aus, gibt true zur�ck, wenn erfolgreich
    bool executeQuery(const std::string& query);

    // �berpr�ft, ob die Datenbankverbindung aktiv ist
    bool isConnected() const;

private:
    sqlite3* db;  // Datenbank-Handle
};

#endif // DATENBANKVERBINDUNG_HPP
