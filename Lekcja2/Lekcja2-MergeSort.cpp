/*
    Alicja Kluczek
    kod rozwiązujący problem: Posortuj tablicę liczb, która ma N elementów.
    Algorytm przedstawiony: Merge sort
*/
#include <iostream>
using namespace std;

// O potęgach dwójki się dobrze myśli w kontekście merge sorta,
// więc nasze tablice to 2 do 19, trochę więcej niż 500 000.
int tablica[1024*512]; // tablica z elementami, które będziemy sortować.
                        // Duży plot-twist, nie musimy tworzyć nowych tablic, podczas sortowania.
                        // wystarczy jedna pomocnicza.
int pomocnicza[1024*512]; // pomocnicza tablica, do funkcji scal

// Funkcja scalająca, przyjmuje przedzial do scalenia
// (mamy dwa takiej samej długości, jeden [pocz, srodek], a drugi [srodek+1, kon])
// Używamy tablicy pomocniczej, ponieważ nie chcemy sobie nadpisywać tablicy tablica.
void scal(int pocz, int srodek, int kon) {
    int i = pocz;
    int j = srodek + 1;
    int ktora = 0;
    while (i <= srodek && j <= kon) {
        if (tablica[i] < tablica[j]) {
            pomocnicza[ktora] = tablica[i];
            i++;
        } else {
            pomocnicza[ktora] = tablica[j];
            j++;
        }
        ktora++;
    }

    while (i <= srodek) {
        pomocnicza[ktora] = tablica[i];
        i++; ktora++;
    }

    while (j <= kon) {
        pomocnicza[ktora] = tablica[j];
        j++; ktora++;
    }

    // Przepisujemy z tablicy pomocniczej do tablicy tablica.
    ktora = 0;
    for (int k = pocz; k <= kon; k++) {
        tablica[k] = pomocnicza[ktora];
        ktora++;
    }
}

// Funkcja właściwa sortująca
// Przyjmuje przedział tablicy, który ma posortować.
void posortuj_przez_scalanie(int pocz, int kon) {
    if (kon - pocz == 0) { // czyli mam przypadek 1 elementu.
        return; // posortowane!
    } else {
        int srodek = (pocz + kon)/2;
        // sortuje moich ,,synków''
        posortuj_przez_scalanie(pocz, srodek);
        posortuj_przez_scalanie(srodek + 1, kon);
        // synkowie się posortowali, to znaczy, że przedziały [pocz, kon/2] i [kon/2+1, kon]
        // w tablicy tablica są posortowane.
        scal(pocz, srodek, kon);
    }
}


int main() {
    int N;
    cin >> N;

    // Cała tablica jest na początku wypełniona ,,nieskończonością''.
    // Normalnie globalne się tworzą z zerami. To dość kluczowe, żeby tę pętlę odpalić.
    for (int i = 0; i < 1024*512; i++) {
        tablica[i] = 1000000005; // Jakaś duża liczba :)
    }

    for (int i = 0; i < N; i++) {
        cin >> tablica[i];
    }
    // Chcemy posortować całą, więc [0, N-1]
    posortuj_przez_scalanie(0, N-1);
    for (int i = 0; i < N; i++) {
        cout << tablica[i] << " ";
    }
}