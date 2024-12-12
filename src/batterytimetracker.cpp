#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <string>
#include <sstream>
#include <cstdlib>  // Für system() und popen()

const std::string FILENAME = "battery_time.txt";

// Zeit als lesbare Zeichenkette formatieren
std::string formatTime(time_t rawTime) {
    char buffer[80];
    struct tm timeInfo;
    
    // Verwendung von localtime_r für plattformübergreifende Kompatibilität
    localtime_r(&rawTime, &timeInfo); // Safe Variante für plattformübergreifende Verwendung

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
        file << startTime << std::endl;
        file << currentTime << std::endl;
        file << duration << std::endl;
        file.close();
    }
}

// Start-, End- und Laufzeit aus Datei laden
void loadTimes(std::string& startTime, std::string& endTime, std::string& duration) {
    std::ifstream file(FILENAME);
    if (file.is_open()) {
        std::getline(file, startTime);
        std::getline(file, endTime);
        std::getline(file, duration);
        file.close();
    }
}

// Funktion, um den Akkustand zu überprüfen (Windows ohne windows.h)
int getBatteryPercentage() {
    // Kommando zur Abfrage des Akkustands mit WMIC
    FILE* fp = popen("wmic path win32_battery get estimatedchargeremaining", "r");
    if (fp == nullptr) {
        std::cerr << "Fehler beim Abrufen des Akkustands!" << std::endl;
        return -1;
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        result += buffer;
    }

    fclose(fp);

    // Die Ausgabe enthält den Akkustand in der zweiten Zeile
    size_t pos = result.find("\n");
    if (pos != std::string::npos) {
        std::string batteryPercentStr = result.substr(pos + 1);
        return std::stoi(batteryPercentStr);
    }

    return -1;  // Fehler, falls der Akkustand nicht extrahiert werden konnte
}

int main() {
    time_t rawStartTime = std::time(nullptr);
    std::string startTime = formatTime(rawStartTime);
    std::string currentTime = startTime;
    std::string duration = "0 Stunden und 0 Minuten";

    saveTimes(startTime, currentTime, duration);

    while (true) {
        int batteryPercent = getBatteryPercentage();
        if (batteryPercent == -1) {
            std::cerr << "Fehler beim Abrufen des Akkustands!" << std::endl;
            break;
        }

        if (batteryPercent <= 1) {
            std::cout << "Akkustand ist bei 1%. Das Programm wird geschlossen." << std::endl;
            break;
        }

        time_t rawCurrentTime = std::time(nullptr);
        currentTime = formatTime(rawCurrentTime);

        duration = formatDuration(rawStartTime, rawCurrentTime);

        saveTimes(startTime, currentTime, duration);

        system("cls");  // Auf Windows: Konsolenbildschirm löschen
        std::cout << "Startzeit: " << startTime << std::endl;
        std::cout << "Letzte aktualisierte Zeit: " << currentTime << std::endl;
        std::cout << "Laufzeit: " << duration << std::endl;
        std::cout << "Akkustand: " << batteryPercent << "%" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
