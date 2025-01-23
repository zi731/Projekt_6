/// \file test.cpp
/// \brief Zawiera zestaw testow jednostkowych dla modulow DaneWiersza, DrzewoDanych, Rejestrator i WalidacjaWiersza.
/// \details Testy jednostkowe zaimplementowane przy uzyciu frameworka GoogleTest.

#include "pch.h"
#include "../Wczyt_CSV/DaneWiersza.h"
#include "../Wczyt_CSV/DaneWiersza.cpp"
#include "../Wczyt_CSV/DrzewoDanych.h"
#include "../Wczyt_CSV/DrzewoDanych.cpp"
#include "../Wczyt_CSV/Rejestrator.h"
#include "../Wczyt_CSV/Rejestrator.cpp"
#include "../Wczyt_CSV/WalidacjaWiersza.h"

#include <gtest/gtest.h>

using namespace std;

/// \brief Testuje konstruktor klasy DaneWiersza.
/// \details Sprawdza, czy wartosci wczytane z lancucha znakow sa poprawnie przypisane.
TEST(TestDaneWiersza, KonstruktorZTekstu) {
    string linia = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    DaneWiersza obiekt(linia);

    EXPECT_EQ(obiekt.pobierzDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(obiekt.pobierzAutokonsumpcje(), 100.5f);
    EXPECT_FLOAT_EQ(obiekt.pobierzEksport(), 200.5f);
    EXPECT_FLOAT_EQ(obiekt.pobierzImport(), 300.5f);
    EXPECT_FLOAT_EQ(obiekt.pobierzPobor(), 400.5f);
    EXPECT_FLOAT_EQ(obiekt.pobierzProdukcje(), 500.5f);
}

/// \brief Testuje serializacje i deserializacje klasy DaneWiersza.
/// \details Sprawdza, czy dane zapisane do pliku binarnego sa poprawnie odczytywane.
TEST(TestDaneWiersza, Serializacja) {
    string linia = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    DaneWiersza oryginal(linia);

    ofstream wyjscieBin("test.bin", ios::binary);
    ASSERT_TRUE(wyjscieBin.is_open()) << "Nie udalo sie otworzyc pliku binarnego do zapisu.";
    oryginal.zapiszBinarne(wyjscieBin);
    wyjscieBin.close();

    ifstream wejscieBin("test.bin", ios::binary);
    ASSERT_TRUE(wejscieBin.is_open()) << "Nie udalo sie otworzyc pliku binarnego do odczytu.";
    DaneWiersza odczytany(wejscieBin);
    wejscieBin.close();

    EXPECT_EQ(odczytany.pobierzDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(odczytany.pobierzAutokonsumpcje(), 100.5f);
    EXPECT_FLOAT_EQ(odczytany.pobierzEksport(), 200.5f);
    EXPECT_FLOAT_EQ(odczytany.pobierzImport(), 300.5f);
    EXPECT_FLOAT_EQ(odczytany.pobierzPobor(), 400.5f);
    EXPECT_FLOAT_EQ(odczytany.pobierzProdukcje(), 500.5f);
}

/// \brief Testuje funkcje walidujaca puste linie.
/// \details Sprawdza, czy funkcja zwraca false dla pustej linii.
TEST(TestWalidacjaWiersza, PustaLinia) {
    string linia = "";
    EXPECT_FALSE(walidujWiersz(linia));
}

/// \brief Testuje funkcje walidujaca linie z naglowkami.
/// \details Sprawdza, czy funkcja zwraca false dla linii z naglowkiem.
TEST(TestWalidacjaWiersza, LiniaZNaglowkiem) {
    string linia = "Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobor (W),Produkcja (W)";
    EXPECT_FALSE(walidujWiersz(linia));
}

/// \brief Testuje funkcje walidujaca linie z nieprawidlowymi znakami.
/// \details Sprawdza, czy funkcja zwraca false dla linii zawierajacej litery.
TEST(TestWalidacjaWiersza, LiniaZLiterami) {
    string linia = "2023-10-15 12:00:00,X,200.5,300.5,400.5,500.5";
    EXPECT_FALSE(walidujWiersz(linia));
}

/// \brief Testuje dodawanie danych do struktury drzewa.
/// \details Sprawdza, czy dane sa poprawnie przechowywane w strukturze drzewa.
TEST(TestDrzewoDanych, DodajDane) {
    DrzewoDanych drzewo;
    string linia = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    DaneWiersza obiekt(linia);
    drzewo.dodajDane(obiekt);

    vector<DaneWiersza> dane = drzewo.pobierzWierszeZPrzedzialu("15.10.2023 00:00", "15.10.2023 23:59");
    ASSERT_EQ(dane.size(), 1);
    EXPECT_EQ(dane[0].pobierzDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(dane[0].pobierzAutokonsumpcje(), 100.5f);
    EXPECT_FLOAT_EQ(dane[0].pobierzEksport(), 200.5f);
    EXPECT_FLOAT_EQ(dane[0].pobierzImport(), 300.5f);
    EXPECT_FLOAT_EQ(dane[0].pobierzPobor(), 400.5f);
    EXPECT_FLOAT_EQ(dane[0].pobierzProdukcje(), 500.5f);
}

/// \brief Testuje obliczanie sum w strukturze drzewa.
/// \details Sprawdza, czy sumy sa poprawnie obliczane w zadanym przedziale czasowym.
TEST(TestDrzewoDanych, ObliczSumyPrzedzial) {
    DrzewoDanych drzewo;
    string linia1 = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    string linia2 = "15.10.2023 18:00:00,150.5,250.5,350.5,450.5,550.5";
    DaneWiersza obiekt1(linia1);
    DaneWiersza obiekt2(linia2);
    drzewo.dodajDane(obiekt1);
    drzewo.dodajDane(obiekt2);

    float sumaAuto, sumaEks, sumaImp, sumaPob, sumaProd;
    drzewo.obliczSumy("15.10.2023 00:00", "15.10.2023 23:59", sumaAuto, sumaEks, sumaImp, sumaPob, sumaProd);

    EXPECT_FLOAT_EQ(sumaAuto, 251.0f);
    EXPECT_FLOAT_EQ(sumaEks, 451.0f);
    EXPECT_FLOAT_EQ(sumaImp, 651.0f);
    EXPECT_FLOAT_EQ(sumaPob, 851.0f);
    EXPECT_FLOAT_EQ(sumaProd, 1051.0f);
}
