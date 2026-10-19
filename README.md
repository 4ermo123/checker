Checker – porównywanie plików
Opis programu

Program służy do porównywania zawartości dwóch plików tekstowych. Wczytuje ich dane do list, wyszukuje elementy unikalne dla każdego pliku oraz elementy wspólne. Wyniki zapisuje w pliku wynik.txt.

Pliki projektu
main.cpp – kod programu zawierający klasę Checker.
plik1.txt – pierwszy plik wejściowy.
plik2.txt – drugi plik wejściowy.
wynik.txt – raport z porównania.
README.md – dokumentacja projektu.
Opis funkcji
wczytajPlik() – otwiera plik i wczytuje jego zawartość do wektora.
wczytajDane() – wczytuje dane z obu plików wejściowych.
tylkoWPliku1() – wyszukuje elementy występujące tylko w pierwszym pliku.
tylkoWPliku2() – wyszukuje elementy występujące tylko w drugim pliku.
wspolne() – wyszukuje elementy znajdujące się w obu plikach.
zapiszSekcje() – zapisuje nagłówek i elementy jednej sekcji raportu.
zapiszRaport() – tworzy plik wynikowy i zapisuje w nim wszystkie wyniki.
Format raportu

Raport zawiera trzy sekcje:

PLIK 1: – elementy występujące wyłącznie w pierwszym pliku.
PLIK 2: – elementy występujące wyłącznie w drugim pliku.
W OBU PLIKACH: – elementy występujące w obu plikach.
Kompilacja

W terminalu, w katalogu projektu, wykonaj polecenie:

g++ -std=c++11 -Wall -Wextra main.cpp -o checker

Uruchomienie

Linux lub macOS:

./checker


Windows:

checker.exe


Po uruchomieniu raport zostanie zapisany w pliku wynik.txt.

Uwagi

Każda linia pliku jest traktowana jako osobny element. Porównywanie uwzględnia wielkość liter. Puste linie są pomijane, a powtarzające się elementy są wypisywane w raporcie tylko raz.