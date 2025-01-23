/// \file DaneWiersza.h
/// \brief Deklaracja klasy DaneWiersza do przechowywania i przetwarzania danych wierszowych z pliku CSV.

#ifndef DANEWIERSZA_H
#define DANEWIERSZA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/// \class DaneWiersza
/// \brief Klasa reprezentujaca dane pojedynczego wiersza z pliku CSV (bez polskich znakow).
class DaneWiersza {
public:
    /// \brief Konstruktor tworzacy obiekt na podstawie wiersza CSV.
    /// \param wiersz Wiersz tekstowy reprezentujacy dane.
    DaneWiersza(const string& wiersz);

    /// \brief Konstruktor odczytujacy dane z pliku binarnego.
    /// \param wejscie Strumien do odczytu binarnego.
    DaneWiersza(ifstream& wejscie);

    /// \brief Wypisuje wszystkie pola obiektu w jednej linii.
    void wypiszCaly() const;

    /// \brief Wypisuje tylko dane liczbowe (bez daty).
    void wypiszDane() const;

    /// \brief Zwraca dane w postaci lancucha znakow.
    /// \return Tekstowy opis danych.
    string pobierzLancuch();

    /// \brief Zapisuje obiekt w formacie binarnym do pliku.
    /// \param wyjscie Strumien binarny do zapisu.
    void zapiszBinarne(ofstream& wyjscie) const;

    /// \brief Odczytuje obiekt z pliku binarnego.
    /// \param wejscie Strumien binarny do odczytu.
    void odczytajBinarne(ifstream& wejscie);

    /// \brief Zwraca date (format tekstowy).
    string pobierzDate() const { return data; }

    /// \brief Zwraca wartosc autokonsumpcji.
    float pobierzAutokonsumpcje() const { return autokonsumpcja; }

    /// \brief Zwraca wartosc eksportu.
    float pobierzEksport() const { return eksport; }

    /// \brief Zwraca wartosc importu.
    float pobierzImport() const { return import; }

    /// \brief Zwraca wartosc poboru.
    float pobierzPobor() const { return pobor; }

    /// \brief Zwraca wartosc produkcji.
    float pobierzProdukcje() const { return produkcja; }

private:
    string data;             ///< Data zdarzenia
    float autokonsumpcja;    ///< Wartosc autokonsumpcji
    float eksport;           ///< Wartosc eksportu
    float import;            ///< Wartosc importu
    float pobor;             ///< Wartosc poboru
    float produkcja;         ///< Wartosc produkcji
};

#endif // DANEWIERSZA_H
