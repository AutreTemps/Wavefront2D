#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using StringVec = std::vector<std::stringstream>;

class Log {
public:
    template <class ...Args>
    static void Info(char const *fmt, Args ...args)
    {
        std::cout << "INFO: ";
        Print(fmt, args...);
    }

    template <class ...Args>
    static void Debug(char const *fmt, Args ...args)
    {
        std::cout << "DEBUG: ";
        Print(fmt, args...);
    }

    template <class ...Args>
    static void Warn(char const *fmt, Args ...args)
    {
        std::cout << "WARNING: ";
        Print(fmt, args...);
    }

    template <class ...Args>
    static void Error(char const *fmt, Args ...args)
    {
        std::cout << "ERROR: ";
        Print(fmt, args...);
    }

private:
    static void Print(char const *fmt)
    {
        StringVec sv;

        while (*fmt != '\0') {
            std::cout << *fmt;
            ++fmt;
        }

        std::cout << std::endl;
    }

    template <class ...Args>
    static void Print(char const *fmt, Args ...args)
    {
        StringVec sv;
        ParseArgs(sv, args...);

        unsigned int i = 0;
        bool braceOpened = false;
        bool lessArgs = false;

        while (*fmt != '\0') {
            if (*fmt == '{') {
                braceOpened = true;
                ++fmt;
                continue;
            }

            if ((*fmt == '}') & braceOpened) {
                if (i == sv.size()) {
                    lessArgs = true;
                    ++fmt;
                    continue;
                }
                std::string tmp;
                sv[i++] >> tmp;
                std::cout << tmp;
                braceOpened = false;
                ++fmt;
                continue;
            }

            braceOpened = false;
            std::cout << *fmt;
            ++fmt;
        }

        std::cout << std::endl;

        if (i != sv.size()) {
            Warn("Log: Were taken more arguments than needed");
        }

        if (lessArgs) {
            Warn("Log: Were taken less arguments than needed");
        }
    }


    template <typename T>
    static void ParseArgs(StringVec &sv, T t)
    {
        std::stringstream ss;
        ss << t;
        sv.push_back(std::move(ss));
    }

    template <typename T, class ...Args>
    static void ParseArgs(StringVec &sv, T t, Args ...args)
    {
        std::stringstream ss;
        ss << t;
        sv.push_back(std::move(ss));
        ParseArgs(sv, args...);
    }

    Log() = default;
    ~Log() = default;
};
