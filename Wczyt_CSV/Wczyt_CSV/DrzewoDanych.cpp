/// \file DrzewoDanych.cpp
/// \brief Implementacja klasy DrzewoDanych do obslugi i analizy danych w strukturze drzewa.

#include "DrzewoDanych.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

using namespace std;

/// \brief Dodaje obiekt DaneWiersza do struktury drzewa.
void DrzewoDanych::dodajDane(const DaneWiersza& dw)
{
    string dataPelna = dw.pobierzDate(); // np. "02.03.2023 14:15"
    // Rozdzielamy czesc dzien.miesiac.rok i godzina:minuta
    string dzienStr = dataPelna.substr(0, 2);
    string miesiacStr = dataPelna.substr(3, 2);
    string rokStr = dataPelna.substr(6, 4);
    string godzinaStr = dataPelna.substr(11, 2);
    string minutaStr = dataPelna.substr(14, 2);

    int dzien = stoi(dzienStr);
    int miesiac = stoi(miesiacStr);
    int rok = stoi(rokStr);
    int godzina = stoi(godzinaStr);
    int minuta = stoi(minutaStr);

    int kwadrans = (godzina * 60 + minuta) / 360; // 4 kwadranse na dobe

    lata[rok].rok = rok;
    lata[rok].miesiace[miesiac].miesiac = miesiac;
    lata[rok].miesiace[miesiac].dni[dzien].dzien = dzien;
    lata[rok].miesiace[miesiac].dni[dzien].kwadranse[kwadrans].kwadrans = kwadrans;
    lata[rok].miesiace[miesiac].dni[dzien].kwadranse[kwadrans].godzina = godzina;
    lata[rok].miesiace[miesiac].dni[dzien].kwadranse[kwadrans].minuta = minuta;
    lata[rok].miesiace[miesiac].dni[dzien].kwadranse[kwadrans].wiersze.push_back(dw);
}

/// \brief Wyswietla zawartosc drzewa w czytelny sposob.
void DrzewoDanych::wypisz() const
{
    for (const auto& rokPara : lata)
    {
        const WierzcholekRok& r = rokPara.second;
        cout << "Rok: " << r.rok << endl;

        for (const auto& miesPara : r.miesiace)
        {
            const WierzcholekMiesiac& m = miesPara.second;
            cout << "\tMiesiac: " << m.miesiac << endl;

            for (const auto& dzienPara : m.dni)
            {
                const WierzcholekDzien& d = dzienPara.second;
                cout << "\t\tDzien: " << d.dzien << endl;

                for (const auto& kwPara : d.kwadranse)
                {
                    const WierzcholekKwadrans& kw = kwPara.second;
                    cout << "\t\t\tKwadrans: " << kw.kwadrans
                        << " (Godzina: " << kw.godzina
                        << ", Minuta: " << kw.minuta << ")" << endl;

                    for (const auto& w : kw.wiersze)
                    {
                        w.wypiszDane();
                    }
                }
            }
        }
    }
}

/// \brief Pobiera wiersze danych w okreslonym przedziale czasowym.
vector<DaneWiersza> DrzewoDanych::pobierzWierszeZPrzedzialu(const std::string& dataStart, const std::string& dataKoniec) const
{
    vector<DaneWiersza> rezultat;

    // Konwertujemy obie daty na time_t
    tm tmBuf = {};
    istringstream iss1(dataStart);
    iss1 >> get_time(&tmBuf, "%d.%m.%Y %H:%M");
    time_t czasStart = mktime(&tmBuf);

    tmBuf = {};
    istringstream iss2(dataKoniec);
    iss2 >> get_time(&tmBuf, "%d.%m.%Y %H:%M");
    time_t czasKoniec = mktime(&tmBuf);

    // Iterujemy po strukturze i sprawdzamy, czy kazdy wiersz miesci sie w zakresie
    for (const auto& rokPara : lata)
    {
        const WierzcholekRok& ro = rokPara.second;
        for (const auto& miesPara : ro.miesiace)
        {
            const WierzcholekMiesiac& mie = miesPara.second;
            for (const auto& dPara : mie.dni)
            {
                const WierzcholekDzien& dd = dPara.second;
                for (const auto& kwPara : dd.kwadranse)
                {
                    const WierzcholekKwadrans& kw = kwPara.second;
                    for (const auto& wi : kw.wiersze)
                    {
                        tm tmBuf2 = {};
                        istringstream issTemp(wi.pobierzDate());
                        issTemp >> get_time(&tmBuf2, "%d.%m.%Y %H:%M");
                        time_t czasWiersza = mktime(&tmBuf2);

                        if (czasWiersza >= czasStart && czasWiersza <= czasKoniec)
                        {
                            rezultat.push_back(wi);
                        }
                    }
                }
            }
        }
    }

    return rezultat;
}

/// \brief Oblicza sumy poszczegolnych pol w podanym przedziale.
void DrzewoDanych::obliczSumy(const std::string& dataStart, const std::string& dataKoniec,
    float& sumaAuto, float& sumaEks, float& sumaImp,
    float& sumaPob, float& sumaProd) const
{
    sumaAuto = sumaEks = sumaImp = sumaPob = sumaProd = 0.0f;
    vector<DaneWiersza> dane = pobierzWierszeZPrzedzialu(dataStart, dataKoniec);

    for (const auto& d : dane)
    {
        sumaAuto += d.pobierzAutokonsumpcje();
        sumaEks += d.pobierzEksport();
        sumaImp += d.pobierzImport();
        sumaPob += d.pobierzPobor();
        sumaProd += d.pobierzProdukcje();
    }
}

/// \brief Oblicza srednie poszczegolnych pol w podanym przedziale.
void DrzewoDanych::obliczSrednie(const std::string& dataStart, const std::string& dataKoniec,
    float& sredniaAuto, float& sredniaEks, float& sredniaImp,
    float& sredniaPob, float& sredniaProd) const
{
    float sa = 0.f, se = 0.f, si = 0.f, sp = 0.f, spr = 0.f;
    int licznik = 0;

    vector<DaneWiersza> dane = pobierzWierszeZPrzedzialu(dataStart, dataKoniec);

    for (const auto& dd : dane)
    {
        sa += dd.pobierzAutokonsumpcje();
        se += dd.pobierzEksport();
        si += dd.pobierzImport();
        sp += dd.pobierzPobor();
        spr += dd.pobierzProdukcje();
        licznik++;
    }

    if (licznik > 0)
    {
        sredniaAuto = sa / licznik;
        sredniaEks = se / licznik;
        sredniaImp = si / licznik;
        sredniaPob = sp / licznik;
        sredniaProd = spr / licznik;
    }
    else
    {
        sredniaAuto = sredniaEks = sredniaImp = sredniaPob = sredniaProd = 0.0f;
    }
}

/// \brief Porownuje sumy z dwoch przedzialow czasowych i zwraca roznice.
void DrzewoDanych::porownajZakresy(const std::string& dStart1, const std::string& dKoniec1,
    const std::string& dStart2, const std::string& dKoniec2,
    float& roznicaAuto, float& roznicaEks,
    float& roznicaImp, float& roznicaPob,
    float& roznicaProd) const
{
    float a1, e1, i1, p1, pr1;
    float a2, e2, i2, p2, pr2;

    obliczSumy(dStart1, dKoniec1, a1, e1, i1, p1, pr1);
    obliczSumy(dStart2, dKoniec2, a2, e2, i2, p2, pr2);

    roznicaAuto = a1 - a2;
    roznicaEks = e1 - e2;
    roznicaImp = i1 - i2;
    roznicaPob = p1 - p2;
    roznicaProd = pr1 - pr2;
}

/// \brief Wyszukuje rekordy z tolerancja w podanym przedziale (domyslnie po polu autokonsumpcja).
vector<DaneWiersza> DrzewoDanych::szukajZTolerancja(const std::string& dataPocz, const std::string& dataKon,
    float wartosc, float tolerancja) const
{
    vector<DaneWiersza> rezultat;
    vector<DaneWiersza> wZakresie = pobierzWierszeZPrzedzialu(dataPocz, dataKon);

    for (const auto& d : wZakresie)
    {
        float autoVal = d.pobierzAutokonsumpcje();
        if (fabs(autoVal - wartosc) <= tolerancja)
        {
            rezultat.push_back(d);
        }
    }

    return rezultat;
}
