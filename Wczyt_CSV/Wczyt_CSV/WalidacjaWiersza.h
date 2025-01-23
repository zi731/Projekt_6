/// \file WalidacjaWiersza.h
/// \brief Zawiera funkcje do sprawdzania poprawnosci wierszy z pliku CSV.

#ifndef WALIDACJAWIERSZA_H
#define WALIDACJAWIERSZA_H

#include <string>
#include <cctype>
#include <algorithm>
#include "Rejestrator.h"

/// \brief Sprawdza poprawnosc wiersza danych z pliku CSV.
/// \details Weryfikuje czy wiersz nie jest pusty, nie zawiera naglowka oraz ma wymagana liczbe pol.
/// \param linia Tekst wiersza.
/// \return true, jesli wiersz jest poprawny; false w przeciwnym razie.
bool walidujWiersz(const std::string& linia)
{
    if (linia.empty())
    {
        rejestratorBledow.log("Pusty wiersz");
        return false;
    }
    else if (linia.find("Time") != std::string::npos)
    {
        rejestratorBledow.log("Znaleziono naglowek: " + linia);
        return false;
    }
    else if (std::any_of(linia.begin(), linia.end(), [](char c) { return std::isalpha(c); }))
    {
        rejestratorBledow.log("Znaleziono litery: " + linia);
        return false;
    }
    else if (std::count(linia.begin(), linia.end(), ',') != 5)
    {
        rejestratorBledow.log("Nieprawidlowa liczba pol: " + linia);
        return false;
    }
    else
    {
        return true;
    }
}

#endif // WALIDACJAWIERSZA_H
