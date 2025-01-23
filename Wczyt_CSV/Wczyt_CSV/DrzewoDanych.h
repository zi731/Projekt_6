/// \file DrzewoDanych.h
/// \brief Deklaracja klasy DrzewoDanych do analizy danych w strukturze drzewa.

#ifndef DRZEWODANYCH_H
#define DRZEWODANYCH_H

#include <map>
#include <string>
#include <vector>
#include "DaneWiersza.h"

/// \class DrzewoDanych
/// \brief Klasa obslugujaca hierarchiczna strukture danych na podstawie obiektow DaneWiersza.
class DrzewoDanych {
public:
    /// \struct WierzcholekKwadrans
    /// \brief Reprezentuje dane w podziale na kwadranse w ciagu dnia.
    struct WierzcholekKwadrans {
        int kwadrans; ///< Numer kwadransu (0-3).
        int godzina; ///< Godzina rozpoczecia.
        int minuta; ///< Minuta rozpoczecia.
        std::vector<DaneWiersza> wiersze; ///< Zbior wierszy w tym kwadransie.
    };

    /// \struct WierzcholekDzien
    /// \brief Reprezentuje dane dzienne.
    struct WierzcholekDzien {
        int dzien; ///< Numer dnia.
        std::map<int, WierzcholekKwadrans> kwadranse; ///< Dane w kwadransach danego dnia.
    };

    /// \struct WierzcholekMiesiac
    /// \brief Reprezentuje dane miesieczne.
    struct WierzcholekMiesiac {
        int miesiac; ///< Numer miesiaca.
        std::map<int, WierzcholekDzien> dni; ///< Dane dzienne w miesiacu.
    };

    /// \struct WierzcholekRok
    /// \brief Reprezentuje dane roczne.
    struct WierzcholekRok {
        int rok; ///< Rok.
        std::map<int, WierzcholekMiesiac> miesiace; ///< Dane miesieczne w roku.
    };

    /// \brief Dodaje nowy wiersz danych do drzewa.
    void dodajDane(const DaneWiersza& dw);

    /// \brief Wyswietla pelna strukture drzewa.
    void wypisz() const;

    /// \brief Pobiera wiersze w okreslonym przedziale czasowym.
    std::vector<DaneWiersza> pobierzWierszeZPrzedzialu(const std::string& dataStart, const std::string& dataKoniec) const;

    /// \brief Oblicza sumy w okreslonym przedziale czasowym.
    void obliczSumy(const std::string& dataStart, const std::string& dataKoniec,
        float& sumaAuto, float& sumaEks, float& sumaImp,
        float& sumaPob, float& sumaProd) const;

    /// \brief Oblicza srednie w okreslonym przedziale czasowym.
    void obliczSrednie(const std::string& dataStart, const std::string& dataKoniec,
        float& sredniaAuto, float& sredniaEks, float& sredniaImp,
        float& sredniaPob, float& sredniaProd) const;

    /// \brief Porownuje dane miedzy dwoma przedzialami.
    void porownajZakresy(const std::string& dStart1, const std::string& dKoniec1,
        const std::string& dStart2, const std::string& dKoniec2,
        float& roznicaAuto, float& roznicaEks,
        float& roznicaImp, float& roznicaPob,
        float& roznicaProd) const;

    /// \brief Wyszukuje rekordy w zadanym przedziale z uwzglednieniem tolerancji.
    std::vector<DaneWiersza> szukajZTolerancja(const std::string& dataPocz, const std::string& dataKon,
        float wartosc, float tolerancja) const;

private:
    std::map<int, WierzcholekRok> lata; ///< Mapa lat do przechowywania danych w hierarchii.
};

#endif // DRZEWODANYCH_H
