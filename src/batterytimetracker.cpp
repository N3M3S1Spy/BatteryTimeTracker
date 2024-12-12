#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <string>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include <Wbemidl.h>

// Globale Konstante für den Dateinamen
const std::string FILENAME = "battery_time.txt";

// Zeit als lesbare Zeichenkette formatieren
std::string formatTime(time_t rawTime) {
    char buffer[80];
    struct tm timeInfo;
    localtime_s(&timeInfo, &rawTime); // Sichere Variante

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeInfo);
    return std::string(buffer);
}

// Differenzzeit formatieren (Laufzeit)
std::string formatDuration(time_t start, time_t end) {
    time_t duration = end - start;
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;

    std::ostringstream oss;
    oss << hours << " Stunden und " << minutes << " Minuten";
    return oss.str();
}

// Start-, End- und Laufzeit in Datei speichern
void saveTimes(const std::string& startTime, const std::string& currentTime, const std::string& duration) {
    std::ofstream file(FILENAME);
    if (file.is_open()) {
        file << startTime << std::endl; // Startzeit in der ersten Zeile
        file << currentTime << std::endl; // Letzte aktuelle Zeit in der zweiten Zeile
        file << duration << std::endl; // Laufzeit in der dritten Zeile
        file.close();
    }
}

// Start-, End- und Laufzeit aus Datei laden
void loadTimes(std::string& startTime, std::string& endTime, std::string& duration) {
    std::ifstream file(FILENAME);
    if (file.is_open()) {
        std::getline(file, startTime); // Erste Zeile: Startzeit
        std::getline(file, endTime);  // Zweite Zeile: Endzeit
        std::getline(file, duration); // Dritte Zeile: Laufzeit
        file.close();
    }
}

// Funktion, um den Akkustand zu überprüfen
int getBatteryPercentage() {
    SYSTEM_POWER_STATUS status;
    if (GetSystemPowerStatus(&status)) {
        return status.BatteryLifePercent;  // Akkustand als Prozentsatz
    }
    return -1;  // Fehler, falls der Akkustand nicht ermittelt werden kann
}

int main() {
    // Aktuelle Zeit als Startzeit
    time_t rawStartTime = std::time(nullptr);
    std::string startTime = formatTime(rawStartTime);
    std::string currentTime = startTime;
    std::string duration = "0 Stunden und 0 Minuten";

    // Speichern der Startzeit, initialen Endzeit und Laufzeit
    saveTimes(startTime, currentTime, duration);

    while (true) {
        // Akkustand überprüfen
        int batteryPercent = getBatteryPercentage();
        if (batteryPercent == -1) {
            std::cerr << "Fehler beim Abrufen des Akkustands!" << std::endl;
            break;
        }

        // Wenn der Akkustand 1% erreicht, das Programm beenden
        if (batteryPercent <= 1) {
            std::cout << "Akkustand ist bei 1%. Das Programm wird geschlossen." << std::endl;
            break;
        }

        // Aktualisieren der aktuellen Zeit
        time_t rawCurrentTime = std::time(nullptr);
        currentTime = formatTime(rawCurrentTime);

        // Laufzeit berechnen
        duration = formatDuration(rawStartTime, rawCurrentTime);

        // Zeiten speichern
        saveTimes(startTime, currentTime, duration);

        // Anzeige der Zeiten im Terminal
        system("cls");
        std::cout << "Startzeit: " << startTime << std::endl;
        std::cout << "Letzte aktualisierte Zeit: " << currentTime << std::endl;
        std::cout << "Laufzeit: " << duration << std::endl;
        std::cout << "Akkustand: " << batteryPercent << "%" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 Sekunde warten
    }

    return 0;
}
