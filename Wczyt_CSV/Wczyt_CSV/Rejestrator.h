/// \file Rejestrator.h
/// \brief Deklaracja klasy Rejestrator do obslugi logowania komunikatow.

#ifndef REJESTRATOR_H
#define REJESTRATOR_H

#include <fstream>
#include <string>

/// \class Rejestrator
/// \brief Klasa obslugujaca zapisywanie komunikatow do plikow tekstowych.
class Rejestrator {
public:
    /// \brief Konstruktor tworzacy obiekt Rejestrator.
    /// \details Nadaje wyjatkowa nazwe plikowi logu na podstawie czasu systemowego.
    /// \param nazwaPodstawowa Szkielet nazwy pliku logu.
    Rejestrator(const std::string& nazwaPodstawowa);

    /// \brief Destruktor klasy Rejestrator.
    /// \details Zamyka otwarty plik logu.
    ~Rejestrator();

    /// \brief Zapisuje wiadomosc do pliku logu.
    /// \param wiadomosc Tresc do zapisania.
    void log(const std::string& wiadomosc);

private:
    std::ofstream strumienLogu; ///< Strumien do pliku z logami.
};

/// \var rejestratorInfo
/// \brief Globalny rejestrator dla komunikatow informacyjnych.
extern Rejestrator rejestratorInfo;

/// \var rejestratorBledow
/// \brief Globalny rejestrator dla komunikatow o bledach.
extern Rejestrator rejestratorBledow;

/// \var licznikBledow
/// \brief Liczba bledow zarejestrowanych przez rejestratorBledow.
extern int licznikBledow;

#endif // REJESTRATOR_H
