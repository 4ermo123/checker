#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Checker {
private:
    // Listy przechowujace dane z obu plikow.
    vector<string> lista1;
    vector<string> lista2;

    // Odczytuje plik i zapisuje jego zawartosc do listy.
    bool wczytajPlik(const string& nazwaPliku,
                     vector<string>& lista) {
        ifstream plik(nazwaPliku);

        if (!plik.is_open()) {
            cerr << "Nie mozna otworzyc pliku: "
                 << nazwaPliku << endl;
            return false;
        }

        string linia;

        while (getline(plik, linia)) {
            if (!linia.empty()) {
                lista.push_back(linia);
            }
        }

        plik.close();
        return true;
    }

    // Znajduje elementy, ktore sa tylko w pierwszym pliku.
    vector<string> tylkoWPliku1() const {
        unordered_set<string> zbior2(
            lista2.begin(), lista2.end()
        );

        unordered_set<string> odwiedzone;
        vector<string> wynik;

        for (const string& element : lista1) {
            // Sprawdza, czy elementu nie ma w drugim pliku.
            // Nie dodaje ponownie tego samego elementu.
            if (zbior2.find(element) == zbior2.end()
                && odwiedzone.insert(element).second) {
                wynik.push_back(element);
            }
        }

        return wynik;
    }

    // Znajduje elementy, ktore sa tylko w drugim pliku.
    vector<string> tylkoWPliku2() const {
        unordered_set<string> zbior1(
            lista1.begin(), lista1.end()
        );

        unordered_set<string> odwiedzone;
        vector<string> wynik;

        for (const string& element : lista2) {
            // Sprawdza, czy elementu nie ma w pierwszym pliku.
            if (zbior1.find(element) == zbior1.end()
                && odwiedzone.insert(element).second) {
                wynik.push_back(element);
            }
        }

        return wynik;
    }

    // Wyszukuje elementy wystepujace w obu plikach.
    vector<string> wspolne() const {
        unordered_set<string> zbior2(
            lista2.begin(), lista2.end()
        );

        unordered_set<string> odwiedzone;
        vector<string> wynik;

        for (const string& element : lista1) {
            // Jesli element wystepuje w drugim pliku,
            // dodaje go do listy elementow wspolnych.
            if (zbior2.find(element) != zbior2.end()
                && odwiedzone.insert(element).second) {
                wynik.push_back(element);
            }
        }

        return wynik;
    }

    // Zapisuje naglowek i elementy jednej sekcji raportu.
    void zapiszSekcje(ofstream& plik,
                      const string& tytul,
                      const vector<string>& dane) const {
        plik << tytul << '\n';

        if (dane.empty()) {
            plik << "(brak)\n";
        } else {
            for (const string& element : dane) {
                plik << element << '\n';
            }
        }

        plik << '\n';
    }

public:
    // Wczytuje dane z obu plikow do odpowiednich list.
    bool wczytajDane(const string& nazwa1,
                     const string& nazwa2) {
        lista1.clear();
        lista2.clear();

        if (!wczytajPlik(nazwa1, lista1)) {
            return false;
        }

        if (!wczytajPlik(nazwa2, lista2)) {
            lista1.clear();
            return false;
        }

        return true;
    }

    // Zapisuje wyniki porownania obu plikow do raportu.
    bool zapiszRaport(const string& nazwaWyniku) const {
        ofstream wynik(nazwaWyniku);

        if (!wynik.is_open()) {
            cerr << "Nie mozna utworzyc pliku: "
                 << nazwaWyniku << endl;
            return false;
        }

        // Zapisuje elementy z pierwszego pliku.
        zapiszSekcje(
            wynik, "PLIK 1:", tylkoWPliku1()
        );

        // Zapisuje elementy z drugiego pliku.
        zapiszSekcje(
            wynik, "PLIK 2:", tylkoWPliku2()
        );

        // Zapisuje elementy wspolne dla obu plikow.
        zapiszSekcje(
            wynik, "W OBU PLIKACH:", wspolne()
        );

        wynik.close();
        return true;
    }
};

int main() {
    Checker checker;

    // Wczytuje oba pliki. W przypadku bledu konczy program.
    if (!checker.wczytajDane("plik1.txt", "plik2.txt")) {
        cerr << "Blad wczytywania plikow." << endl;
        return 1;
    }

    // Tworzy raport z wynikami porownania.
    if (!checker.zapiszRaport("wynik.txt")) {
        return 1;
    }

    cout << "Raport zapisano w pliku wynik.txt." << endl;

    return 0;
}
