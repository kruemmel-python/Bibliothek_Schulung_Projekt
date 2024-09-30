import csv
import random
import tkinter as tk
from tkinter import messagebox
from faker import Faker
from datetime import datetime

# Funktion, um eine Mitgliedsnummer mit dem Präfix "MGN" zu erstellen
def create_membership_number():
    numbers = [random.randint(0, 9) for _ in range(4)]
    check_digit = sum(numbers) % 10
    return f"MGN{''.join(map(str, numbers))}{check_digit}"

# Funktion zum Generieren von Regaldaten
def assign_shelf():
    shelf_number = random.randint(1, 10)  # Erzeugt zufällige Regalnummern zwischen 1 und 10
    return f"Regal-{shelf_number}"

# Funktion zum Generieren von Medien-Datensätzen
def generate_media_record(fake):
    media_type = random.choice(["Buch", "CD", "DVD"])
    author = fake.name()
    title = fake.sentence(nb_words=4)
    category = random.choice(["Roman", "Sachbuch", "Punkrock", "Pop", "Horror", "Comedy"])
    code = fake.isbn13() if media_type == "Buch" else fake.ean13()
    user = fake.name()
    timestamp = fake.date_time_this_year().strftime("%Y-%m-%d %H:%M:%S") if random.choice([True, False]) else ""
    title_list = fake.sentence(nb_words=6) if media_type == "CD" else ""
    shelf = assign_shelf()  # Regaldaten hinzufügen
    
    return {
        "Medientyp": media_type,
        "Autor": author,
        "Titel": title,
        "Titelliste": title_list,
        "Kategorie": category,
        "Code": code,
        "Letzter Nutzer": user,
        "Verleihdatum": timestamp,
        "Regal": shelf  # Zuordnung zum Regal
    }

# Funktion zum Generieren von Nutzer-Datensätzen (aufgeteilt in Vorname, Nachname, Straße, Hausnummer, PLZ, Ort)
def generate_user_record(fake):
    full_name = fake.name()
    first_name, last_name = full_name.split(" ", 1)  # Teilt den Namen in Vorname und Nachname auf
    street_address = fake.street_address().split()
    street = " ".join(street_address[:-1])  # Straße (alles außer die letzte Zahl)
    house_number = street_address[-1]  # Hausnummer (die letzte Zahl)
    postcode = fake.postcode()
    city = fake.city()
    email = fake.email()
    phone = fake.phone_number()
    membership_number = create_membership_number()  # Erzeugt eine Mitgliedsnummer mit MGN-Präfix
    
    return {
        "Vorname": first_name,
        "Nachname": last_name,
        "Straße": street,
        "Hausnummer": house_number,
        "PLZ": postcode,
        "Ort": city,
        "Email": email,
        "Telefonnummer": phone,
        "Mitgliedsnummer": membership_number
    }

# Funktion, um die Daten in eine CSV-Datei zu schreiben
def generate_csv(entries_count, country_code):
    try:
        entries_count = int(entries_count)
    except ValueError:
        messagebox.showerror("Fehler", "Bitte eine gültige Zahl eingeben!")
        return

    # Erzeuge den Faker für das ausgewählte Land
    fake = Faker(country_code)
    
    with open("bibliothek.csv", mode="w", newline="", encoding="utf-8") as file:
        fieldnames = ["Medientyp", "Autor", "Titel", "Titelliste", "Kategorie", "Code", "Letzter Nutzer", "Verleihdatum", "Regal"]
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        
        for _ in range(entries_count):
            writer.writerow(generate_media_record(fake))
    
    with open("nutzer.csv", mode="w", newline="", encoding="utf-8") as file:
        fieldnames = ["Vorname", "Nachname", "Straße", "Hausnummer", "PLZ", "Ort", "Email", "Telefonnummer", "Mitgliedsnummer"]
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        
        for _ in range(entries_count):
            writer.writerow(generate_user_record(fake))
    
    messagebox.showinfo("Erfolg", f"{entries_count} Datensätze wurden erfolgreich erstellt und in CSV-Dateien gespeichert!")

# Funktion zum Starten der GUI
def start_gui():
    root = tk.Tk()
    root.title("Bibliothek Datensatz Generator")
    
    # Label und Eingabefeld für Anzahl der Datensätze
    tk.Label(root, text="Anzahl der Datensätze:").pack(pady=10)
    
    entry = tk.Entry(root)
    entry.pack(pady=10)
    
    # Label und Dropdown-Menü für Länderauswahl
    tk.Label(root, text="Land auswählen:").pack(pady=10)
    
    country_var = tk.StringVar(value="de")
    country_menu = tk.OptionMenu(root, country_var, "de", "en")
    country_menu.pack(pady=10)
    
    # Button zum Generieren der CSV-Dateien
    generate_button = tk.Button(root, text="CSV generieren", 
                                command=lambda: generate_csv(entry.get(), country_var.get()))
    generate_button.pack(pady=20)
    
    root.mainloop()

# Starten der GUI
if __name__ == "__main__":
    start_gui()