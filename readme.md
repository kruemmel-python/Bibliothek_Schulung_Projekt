# Bibliothek Schulung Projekt

Das **Bibliothek Schulung Projekt** ist eine C++-Konsolenanwendung zur Verwaltung von Bibliotheksmedien und Nutzern. Das Programm ermöglicht das Speichern und Laden von Medien und Nutzern in CSV-Dateien sowie die Verwendung einer SQLite-Datenbank für die Speicherung und Verwaltung von Datensätzen.

## Inhaltsverzeichnis

- [Installation](#installation)
- [Verwendung](#verwendung)
- [Projektstruktur](#projektstruktur)
- [Funktionen](#funktionen)
- [Beispieleingabe](#beispieleingabe)
- [Technologien](#technologien)
- [Verbesserungsvorschläge](#verbesserungsvorschläge)
- [Lizenz](#lizenz)

## Installation

### Voraussetzungen

- C++ Compiler (z.B. g++, MSVC)
- [SQLite3](https://www.sqlite.org/download.html) Bibliothek (für Datenbankfunktionalität)
- [CMake](https://cmake.org/) (optional, für den Build-Prozess)

### Schritte

1. Klone das Repository auf deinen lokalen Computer:

    ```bash
    git clone https://github.com/kruemmel-python/Bibliothek_Schulung_Projekt.git
    ```

2. Öffne das Projekt in deiner bevorzugten IDE (z.B. Visual Studio).

3. Stelle sicher, dass du die **SQLite3**-Bibliothek installiert hast und sie in deinem Projekt korrekt eingebunden ist.

4. Führe das Programm aus.

### Optional: Konsolen-Codierung unter Windows auf UTF-8 setzen

Füge die folgenden Zeilen in **main.cpp** ein, um die Konsolencodierung auf UTF-8 zu ändern und Sonderzeichen korrekt darzustellen:

```cpp
#include <windows.h>
SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);
```

## Verwendung

Nach dem Start des Programms wird das Bibliotheksterminal angezeigt. Hier sind die verfügbaren Aktionen:

```plaintext
Bibliothek-Terminal
1. Medien auflisten
2. Nutzer auflisten
3. Medien aus CSV laden
4. Nutzer aus CSV laden
5. Medium hinzufügen
6. Nutzer hinzufügen
7. Beenden
```

### Beispielaktionen:

- **Medien auflisten**: Zeigt alle gespeicherten Medien (Bücher, CDs, DVDs) an.
- **Nutzer auflisten**: Zeigt alle registrierten Nutzer der Bibliothek an.
- **Medien/Nutzer aus CSV laden**: Lädt Daten aus den CSV-Dateien `bibliothek.csv` und `nutzer.csv`.
- **Medium/Nutzer hinzufügen**: Fügt neue Medien oder Nutzer zur Bibliothek hinzu, speichert sie in CSV-Dateien und optional in die Datenbank.
- **Beenden**: Beendet das Programm.

## Projektstruktur

```plaintext
.
├── Bibliothek.cpp             # Implementierung der Bibliothekslogik
├── Bibliothek.hpp             # Header für Bibliothek-Klasse
├── Terminal.cpp               # Implementierung des Terminal-Menüs
├── Terminal.hpp               # Header für Terminal-Klasse
├── CSVHandler.cpp             # Implementierung für das Lesen und Schreiben von CSV-Dateien
├── CSVHandler.hpp             # Header für CSV-Handling
├── Datenbankverbindung.cpp    # Implementierung der SQLite-Datenbankanbindung
├── Datenbankverbindung.hpp    # Header für SQLite-Datenbankanbindung
├── Medien.cpp                 # Implementierung der Medienlogik (Buch, CD, DVD)
├── Medien.hpp                 # Header für Medien
├── Nutzer.cpp                 # Implementierung der Nutzerlogik
├── Nutzer.hpp                 # Header für Nutzer
├── Regal.hpp                  # Header für Regal-Klasse
├── main.cpp                   # Haupt-Einstiegspunkt für das Programm
├── bibliothek.csv             # CSV-Datei für Medien
├── nutzer.csv                 # CSV-Datei für Nutzer
├── bibliothek.db              # SQLite-Datenbankdatei für Medien und Nutzer (optional)
└── README.md                  # Diese README-Datei
```

## Funktionen

1. **CSV-Handling**:
   - Medien und Nutzerdaten werden in den Dateien `bibliothek.csv` und `nutzer.csv` gespeichert und können von dort geladen werden.

2. **Datenbankunterstützung**:
   - Daten werden optional auch in einer SQLite-Datenbank (`bibliothek.db`) gespeichert, um eine persistente Speicherung und spätere Abfragen zu ermöglichen.

3. **Modulares Design**:
   - Die Anwendung ist modular aufgebaut, sodass neue Medientypen oder Funktionen einfach hinzugefügt werden können.

## Beispieleingabe

Beim Hinzufügen eines Mediums fragt das Programm nach den folgenden Informationen:

```plaintext
Medientyp (Buch/CD/DVD): Buch
Autor: Max Mustermann
Titel: C++ für Einsteiger
Kategorie: Programmierung
Code: 978-3-16-148410-0
```

Beim Hinzufügen eines Nutzers wird folgendes abgefragt:

```plaintext
Vorname: Maria
Nachname: Müller
Strasse: Hauptstr.
Hausnummer: 12
PLZ: 12345
Ort: Berlin
Email: maria.mueller@example.com
Telefonnummer: +49(0)1234 56789
Mitgliedsnummer: MGN12345
```

## Technologien

- **C++**: Hauptprogrammiersprache
- **SQLite**: Für die Datenbankintegration
- **CSV**: Zum Speichern und Laden von Daten
- **Visual Studio** oder **CMake**: Zum Verwalten und Bauen des Projekts

## Verbesserungsvorschläge

- **Grafische Benutzeroberfläche (GUI)**: Eine zukünftige Version könnte eine GUI anstelle der Konsolenausgabe verwenden.
- **Erweiterte Fehlerbehandlung**: Bessere Fehlerbehandlung bei ungültigen Eingaben und CSV-Daten.
- **Tests**: Implementierung von Unit-Tests zur Verbesserung der Codequalität.

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz. Siehe die [LICENSE](LICENSE)-Datei für weitere Details.
```

### Hinweise:
- **Installation**: Ich habe Schritte hinzugefügt, um sicherzustellen, dass SQLite korrekt eingebunden wird. Falls es zusätzliche Abhängigkeiten gibt, kannst du sie dort erwähnen.
- **Projektstruktur**: Ich habe die genaue Struktur basierend auf deiner Dateiliste eingebaut, damit Nutzer leicht verstehen, wie die Dateien organisiert sind.
- **Verbesserungsvorschläge**: Falls du weitere Ideen hast, kannst du diesen Abschnitt erweitern.

