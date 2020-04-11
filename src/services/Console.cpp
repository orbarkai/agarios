#include <iostream>
#include <regex>
#include "services/Console.h"

int Console::nextColor = 0;

const int Console::sectionLength = 30;

const MapSS Console::colorsMap = {
    {"red", "\x1B[1;31m"},
    {"green", "\x1B[1;32m"},
    {"yellow", "\x1B[1;33m"},
    {"blue", "\x1B[1;34m"},
    {"magenta", "\x1B[1;35m"},
    {"cyan", "\x1B[1;36m"},
    {"white", "\x1B[1;37m"},
};

const std::string Console::resetColor = "\x1B[0m";

const std::string Console::endl = "\n";
const std::string Console::tab = "\t";

MapSS Console::directorsMap = { };

Console::Logger::Logger() : Console::Logger("", "") { }

Console::Logger::Logger(std::string name, std::string loggerConsoleColor) : Console::Logger(name, loggerConsoleColor, "") { };

Console::Logger::Logger(std::string name, std::string loggerConsoleColor, std::string messageConsoleColor) {
    this->name = name;
    this->printedLogger = false;
    this->loggerConsoleColor = loggerConsoleColor;
    this->messageConsoleColor = messageConsoleColor;
};

Console::Logger::~Logger() {
    std::cout << Console::endl;
};

std::string Console::getColor(std::string director) {
    MapSS::const_iterator directorI = directorsMap.find(director);
    std::string directorColor;
    if (directorI != directorsMap.end()) {
        directorColor = directorI->second;
    } else {
        MapSS::const_iterator it = colorsMap.begin();
        for( int i = 0; i < nextColor; i++ ) {
            ++it;
            if (it == colorsMap.end()) {
                it = colorsMap.begin();
            }
        }
        nextColor++;
        directorColor = it->second;
        directorsMap[director] = directorColor;
    }
    return directorColor;
}

std::string Console::paint(std::string color, std::string message) {
    MapSS::const_iterator colorI = colorsMap.find(color);
    std::string consoleColor = "";

    for (colorI = colorsMap.begin(); colorI != colorsMap.end(); ++colorI) {
        if (color.compare(colorI->first) == 0 || color.compare(colorI->second) == 0) {
            consoleColor = colorI->second;
        }
    }
    
    return consoleColor + message + resetColor;
}

Console::Logger Console::log(std::string director, std::string directorColor) noexcept {
    std::string consoleColor = "";
    MapSS::const_iterator colorI = colorsMap.find(directorColor);
    if (colorI != colorsMap.cend()) consoleColor = colorI->second;
    return Logger(director, consoleColor);
}

Console::Logger Console::log(std::string director) noexcept {
    std::string directorColor = getColor(director);
    return Logger(director, directorColor);
}

Console::Logger Console::log() noexcept {
    return Logger();
}

Console::Logger Console::error(std::string director) noexcept {
    std::string directorColor = getColor(director);
    Logger logger = Logger(director, directorColor, colorsMap.find("red")->second);
    logger << "An error was found" << endl << tab;
    return logger;
}

void Console::startSection(std::string title) noexcept {
    std::regex regex("\x1B\\[..\\d?\\dm");
    std::string titleNoColor = std::regex_replace(title, regex, "");
    const int minimized = (sectionLength / 2) - (titleNoColor.size() / 2);

    for (int i = 0; i < minimized; i++) {
        std::cout << "-";
    }

    std::cout << " " << title << " ";

    for (int i = 0; i < minimized; i++) {
        std::cout << "-";
    }

    std::cout << std::endl;
}

void Console::endSection() noexcept {
    for (int i = 0; i < sectionLength; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}