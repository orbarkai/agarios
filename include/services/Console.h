#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>

typedef std::map<std::string, std::string> MapSS;

class Console
{

    public:
        class Logger
        {
            private:
                std::string name;
                bool printedLogger;
                std::string loggerConsoleColor;
                std::string messageConsoleColor;

            public:
                Logger();
                Logger(std::string name, std::string loggerConsoleColor);
                Logger(std::string name, std::string loggerConsoleColor, std::string messageConsoleColor);
                ~Logger();

            public:
                template<class T>
                Logger& operator<<(const T &message) {
                    if (!this->printedLogger && this->name.length() > 0) {
                        std::cout << this->loggerConsoleColor << this->name << ": " << Console::resetColor;
                        this->printedLogger = true;
                    }

                    std::cout << this->messageConsoleColor << message << Console::resetColor;

                    return *this;
                }
        };

    public:
        const static std::string endl;
        const static std::string tab;

    public:
        static Logger log(std::string director, std::string directorColor) noexcept;
        static Logger log(std::string director) noexcept;
        static Logger log() noexcept;
        static Logger error(std::string director) noexcept;

        static void startSection(std::string title) noexcept;
        static void endSection() noexcept;

        static std::string paint(std::string color, std::string message);

    private:
        const static MapSS colorsMap;
        static MapSS directorsMap;
        static int nextColor;
        const static std::string resetColor;
        const static int sectionLength;

        
    private:
        Console() = default;

    private:
        static std::string getColor(std::string director);
};

#endif