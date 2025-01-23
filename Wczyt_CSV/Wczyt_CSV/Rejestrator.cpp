/// \file Rejestrator.cpp
/// \brief Implementacja klasy Rejestrator do obslugi logowania.

#include "Rejestrator.h"
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sstream>

/// \var rejestratorInfo
/// \brief Globalny rejestrator dla komunikatow informacyjnych.
Rejestrator rejestratorInfo("log_info");

/// \var rejestratorBledow
/// \brief Globalny rejestrator dla bledow.
Rejestrator rejestratorBledow("log_error");

/// \var licznikBledow
/// \brief Liczba zarejestrowanych bledow.
int licznikBledow = 0;

/// \brief Konstruktor klasy Rejestrator.
/// \details Tworzy unikalna nazwe pliku logu w oparciu o aktualny czas.
/// \param nazwaPodstawowa Szkielet nazwy dla pliku logu.
Rejestrator::Rejestrator(const std::string& nazwaPodstawowa)
{
    auto t = std::time(nullptr);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream ss;
    ss << nazwaPodstawowa << "_"
        << std::put_time(&tm, "%d%m%Y_%H%M%S")
        << ".txt";

    std::string finalnaNazwa = ss.str();
    // Proba usuniecia starego pliku (jesli istnieje)
    std::remove(finalnaNazwa.c_str());

    strumienLogu.open(finalnaNazwa, std::ios::out | std::ios::app);
    if (!strumienLogu.is_open()) {
        throw std::runtime_error("Nie mozna otworzyc pliku logu");
    }
}

/// \brief Destruktor klasy Rejestrator.
Rejestrator::~Rejestrator()
{
    if (strumienLogu.is_open())
    {
        strumienLogu.close();
    }
}

/// \brief Zapisuje wiadomosc do otwartego pliku logu.
/// \param wiadomosc Tekst do zapisania.
void Rejestrator::log(const std::string& wiadomosc)
{
    if (strumienLogu.is_open())
    {
        auto teraz = std::time(nullptr);
        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &teraz);
#else
        localtime_r(&teraz, &tm);
#endif

        strumienLogu << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << " " << wiadomosc << std::endl;
    }

    // Jesli jest to rejestrator bledow, zwiekszamy globalny licznikBledow
    if (this == &rejestratorBledow)
    {
        licznikBledow++;
    }
}
