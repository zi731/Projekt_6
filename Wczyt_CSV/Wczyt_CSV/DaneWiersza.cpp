/// \file DaneWiersza.cpp
/// \brief Implementacja klasy DaneWiersza do obslugi danych wierszowych z pliku CSV.

#include "DaneWiersza.h"
#include "Rejestrator.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

/// \brief Konstruktor tworzacy obiekt na podstawie ciagu CSV.
/// \param wiersz Wiersz zawierajacy dane.
DaneWiersza::DaneWiersza(const string& wiersz)
{
    vector<string> pola;
    stringstream ss(wiersz);
    string element;

    while (getline(ss, element, ','))
    {
        // Usuwa ewentualne cudzyslowy
        element.erase(remove(element.begin(), element.end(), '\"'), element.end());
        pola.push_back(element);
    }

    this->data = pola[0];
    this->autokonsumpcja = stof(pola[1]);
    this->eksport = stof(pola[2]);
    this->import = stof(pola[3]);
    this->pobor = stof(pola[4]);
    this->produkcja = stof(pola[5]);

    rejestratorInfo.log("Wczytano wiersz: " + this->pobierzLancuch());
}

/// \brief Konstruktor odczytujacy dane z pliku binarnego.
/// \param wejscie Strumien do odczytu binarnego.
DaneWiersza::DaneWiersza(ifstream& wejscie)
{
    odczytajBinarne(wejscie);
}

/// \brief Wypisuje wszystkie dane na ekran.
void DaneWiersza::wypiszCaly() const
{
    cout << data << " " << autokonsumpcja << " " << eksport << " "
        << import << " " << pobor << " " << produkcja << endl;
}

/// \brief Wypisuje tylko dane liczbowe (bez daty).
void DaneWiersza::wypiszDane() const
{
    cout << "\t\t\t\t"
        << autokonsumpcja << " " << eksport << " "
        << import << " " << pobor << " " << produkcja << endl;
}

/// \brief Zwraca lancuch reprezentujacy wszystkie dane.
string DaneWiersza::pobierzLancuch()
{
    return data + " " + to_string(autokonsumpcja) + " " + to_string(eksport) + " "
        + to_string(import) + " " + to_string(pobor) + " " + to_string(produkcja);
}

/// \brief Zapisuje obiekt do pliku binarnego.
void DaneWiersza::zapiszBinarne(ofstream& wyjscie) const
{
    size_t rozmiarDaty = data.size();
    wyjscie.write(reinterpret_cast<const char*>(&rozmiarDaty), sizeof(rozmiarDaty));
    wyjscie.write(data.c_str(), rozmiarDaty);
    wyjscie.write(reinterpret_cast<const char*>(&autokonsumpcja), sizeof(autokonsumpcja));
    wyjscie.write(reinterpret_cast<const char*>(&eksport), sizeof(eksport));
    wyjscie.write(reinterpret_cast<const char*>(&import), sizeof(import));
    wyjscie.write(reinterpret_cast<const char*>(&pobor), sizeof(pobor));
    wyjscie.write(reinterpret_cast<const char*>(&produkcja), sizeof(produkcja));
}

/// \brief Odczytuje obiekt z pliku binarnego.
void DaneWiersza::odczytajBinarne(ifstream& wejscie)
{
    size_t rozmiarDaty;
    wejscie.read(reinterpret_cast<char*>(&rozmiarDaty), sizeof(rozmiarDaty));
    data.resize(rozmiarDaty);
    wejscie.read(&data[0], rozmiarDaty);
    wejscie.read(reinterpret_cast<char*>(&autokonsumpcja), sizeof(autokonsumpcja));
    wejscie.read(reinterpret_cast<char*>(&eksport), sizeof(eksport));
    wejscie.read(reinterpret_cast<char*>(&import), sizeof(import));
    wejscie.read(reinterpret_cast<char*>(&pobor), sizeof(pobor));
    wejscie.read(reinterpret_cast<char*>(&produkcja), sizeof(produkcja));
}
