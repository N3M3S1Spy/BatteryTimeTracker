# BatteryTimeTracker

## Beschreibung
BatteryTimeTracker ist ein C++-Programm, das die Laufzeit eines Laptops protokolliert. Es speichert die Startzeit, die letzte aktuelle Zeit und die gesamte Laufzeit in einer Textdatei.

## Features
- Startzeit und aktuelle Zeit in einer Datei speichern.
- Laufzeit in Stunden und Minuten berechnen.
- Daten werden automatisch aktualisiert, auch nach einem Neustart des Laptops.

## Voraussetzungen
- Windows-Betriebssystem
- C++17 oder höher
- Ein C++-Compiler (z. B. MSVC, g++)

## Installation
1. Klone das Repository:
   ```bash
   git clone https://github.com/dein-benutzername/BatteryTimeTracker.git
   ```
2. Öffne die Projektdatei in Visual Studio oder einem anderen Editor.
3. Kompiliere und führe das Programm aus.

## Benutzung
1. Führe das Programm aus.
2. Die Datei `battery_time.txt` wird erstellt und enthält:
   - Startzeit
   - Letzte aktualisierte Zeit
   - Gesamtlaufzeit

## Beispielausgabe
```
Startzeit: 10-12-2024 14:00:00
Letzte aktualisierte Zeit: 10-12-2024 15:30:00
Gesamtlaufzeit: 1 Stunde und 30 Minuten
```

## To-Do
- Mehrsprachige Unterstützung (Deutsch/Englisch).
- Unterstützung für Batteriestatus-Überwachung.
- GUI-Implementierung.

## Lizenz
Dieses Projekt ist unter der MIT-Lizenz lizenziert. Siehe die Datei [LICENSE](LICENSE) für Details.

---

### 5. **Hochladen zu GitHub**
1. Initialisiere dein Repository:
   ```bash
   git init
   ```
2. Füge die Dateien hinzu:
   ```bash
   git add .
   ```
3. Committe die Änderungen:
   ```bash
   git commit -m "Initial commit"
   ```
4. Erstelle ein Repository auf GitHub:
   - Gehe auf [GitHub](https://github.com) und erstelle ein neues Repository mit dem Namen `BatteryTimeTracker`.
5. Verknüpfe dein lokales Repository mit GitHub:
   ```bash
   git remote add origin https://github.com/dein-benutzername/BatteryTimeTracker.git
   ```
6. Lade die Dateien hoch:
   ```bash
   git push -u origin main
   ```

---
