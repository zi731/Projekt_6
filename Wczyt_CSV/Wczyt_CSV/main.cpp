/// \file main.cpp
/// \brief Glowny plik programu do analizy danych z pliku CSV.
/// \details Pozwala na wczytanie danych, ich obrobke, zapis i odczyt z pliku binarnego.
/// Udostepnia funkcje obliczania sum, srednich, porownywania i wyszukiwania z tolerancja.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "DaneWiersza.h"
#include "Rejestrator.h"
#include "DrzewoDanych.h"
#include "WalidacjaWiersza.h"

using namespace std;

/// \brief Wyswietla menu programu w jezyku polskim (bez znakow diakrytycznych).
void pokazMenu()
{
    cout << "\nMenu:\n";
    cout << "1. Wczytaj dane z pliku\n";
    cout << "2. Wyswietl strukture drzewa\n";
    cout << "3. Pobierz dane z przedzialu\n";
    cout << "4. Oblicz sumy z przedzialu\n";
    cout << "5. Oblicz srednie z przedzialu\n";
    cout << "6. Porownaj dane z dwoch przedzialow\n";
    cout << "7. Wyszukaj rekordy z tolerancja\n";
    cout << "8. Zapisz dane do pliku binarnego\n";
    cout << "9. Wczytaj dane z pliku binarnego\n";
    cout << "10. Wyjdz\n";
    cout << "Wpisz swoj wybor: ";
}

/// \brief Funkcja glowna aplikacji.
int main()
{
    DrzewoDanych drzewo;         ///< Struktura drzewa do przechowywania danych.
    vector<DaneWiersza> wiersze; ///< Wektor z wczytanymi wierszami.
    ifstream plikCSV;
    string pojedynczaLinia;
    string dataPocz, dataKon;
    string dataPocz1, dataKon1, dataPocz2, dataKon2;
    float sumaAuto, sumaEks, sumaImp, sumaPob, sumaProd;
    float diffAuto, diffEks, diffImp, diffPob, diffProd;
    float szukanaWartosc, tolerancja;
    vector<DaneWiersza> daneFiltr, daneTol;

    while (true)
    {
        pokazMenu();
        int wybor;
        cin >> wybor;
        cin.ignore(); // ignoruje znak nowej linii

        switch (wybor)
        {
        case 1:
            plikCSV.open("Chart Export.csv");
            if (!plikCSV.is_open())
            {
                cerr << "Blad podczas otwierania pliku CSV" << endl;
                return 1;
            }

            while (getline(plikCSV, pojedynczaLinia))
            {
                if (walidujWiersz(pojedynczaLinia))
                {
                    DaneWiersza dw(pojedynczaLinia);
                    wiersze.push_back(dw);
                    drzewo.dodajDane(dw);
                }
            }

            plikCSV.close();
            cout << "Wczytano dane z pliku CSV." << endl;
            cout << "Liczba wczytanych wierszy: " << wiersze.size() << endl;
            cout << "Znaleziono blednych wierszy: " << licznikBledow << endl;
            cout << "Sprawdz pliki log_* aby uzyskac szczegoly." << endl;
            break;

        case 2:
            drzewo.wypisz();
            break;

        case 3:
            cout << "Podaj date poczatkowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataPocz);
            cout << "Podaj date koncowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataKon);
            daneFiltr = drzewo.pobierzWierszeZPrzedzialu(dataPocz, dataKon);
            cout << "Dane w przedziale " << dataPocz << " - " << dataKon << ":" << endl;
            for (auto& d : daneFiltr)
            {
                d.wypiszCaly();
            }
            break;

        case 4:
            cout << "Podaj date poczatkowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataPocz);
            cout << "Podaj date koncowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataKon);
            drzewo.obliczSumy(dataPocz, dataKon, sumaAuto, sumaEks, sumaImp, sumaPob, sumaProd);
            cout << "Sumy w przedziale " << dataPocz << " - " << dataKon << ":" << endl;
            cout << "Autokonsumpcja: " << sumaAuto << endl;
            cout << "Eksport: " << sumaEks << endl;
            cout << "Import: " << sumaImp << endl;
            cout << "Pobor: " << sumaPob << endl;
            cout << "Produkcja: " << sumaProd << endl;
            break;

        case 5:
            cout << "Podaj date poczatkowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataPocz);
            cout << "Podaj date koncowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataKon);
            drzewo.obliczSrednie(dataPocz, dataKon, sumaAuto, sumaEks, sumaImp, sumaPob, sumaProd);
            cout << "Srednie w przedziale " << dataPocz << " - " << dataKon << ":" << endl;
            cout << "Autokonsumpcja: " << sumaAuto << endl;
            cout << "Eksport: " << sumaEks << endl;
            cout << "Import: " << sumaImp << endl;
            cout << "Pobor: " << sumaPob << endl;
            cout << "Produkcja: " << sumaProd << endl;
            break;

        case 6:
            cout << "Pierwszy zakres:" << endl;
            cout << "Podaj date poczatkowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataPocz1);
            cout << "Podaj date koncowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataKon1);

            cout << "Drugi zakres:" << endl;
            cout << "Podaj date poczatkowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataPocz2);
            cout << "Podaj date koncowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataKon2);

            drzewo.porownajZakresy(dataPocz1, dataKon1, dataPocz2, dataKon2, diffAuto, diffEks, diffImp, diffPob, diffProd);
            cout << "Roznice miedzy zakresami:" << endl;
            cout << "Autokonsumpcja: " << diffAuto << endl;
            cout << "Eksport: " << diffEks << endl;
            cout << "Import: " << diffImp << endl;
            cout << "Pobor: " << diffPob << endl;
            cout << "Produkcja: " << diffProd << endl;
            break;

        case 7:
            cout << "Podaj date poczatkowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataPocz);
            cout << "Podaj date koncowa (dd.mm.yyyy hh:mm): ";
            getline(cin, dataKon);
            cout << "Podaj szukana wartosc: ";
            cin >> szukanaWartosc;
            cout << "Podaj tolerancje: ";
            cin >> tolerancja;
            daneTol = drzewo.szukajZTolerancja(dataPocz, dataKon, szukanaWartosc, tolerancja);
            cout << "Znalezione rekordy:" << endl;
            for (auto& d : daneTol)
            {
                d.wypiszCaly();
            }
            break;

        case 8:
        {
            ofstream binarnyPlik("daneWyjsciowe.bin", ios::binary);
            if (!binarnyPlik.is_open())
            {
                cerr << "Blad otwarcia pliku binarnego do zapisu" << endl;
                return 1;
            }
            for (auto& dw : wiersze)
            {
                dw.zapiszBinarne(binarnyPlik);
            }
            binarnyPlik.close();
            cout << "Dane zapisane do pliku binarnego." << endl;
        }
        break;

        case 9:
        {
            ifstream binarnyPlikWczyt("daneWyjsciowe.bin", ios::binary);
            if (!binarnyPlikWczyt.is_open())
            {
                cerr << "Blad otwarcia pliku binarnego do odczytu" << endl;
                return 1;
            }
            while (binarnyPlikWczyt.peek() != EOF)
            {
                DaneWiersza tmp(binarnyPlikWczyt);
                drzewo.dodajDane(tmp);
            }
            binarnyPlikWczyt.close();
            cout << "Dane wczytane z pliku binarnego." << endl;
        }
        break;

        case 10:
            cout << "Koniec programu." << endl;
            return 0;

        default:
            cout << "Nieprawidlowy wybor, sprobuj ponownie." << endl;
            break;
        }
    }

    return 0;
}
