# Rekurencja i sortowanie merge

Na dzisiejszych zajęciach poznamy sortowanie w dużo lepszej złożoności niż poprzednie
algorytmy -- ***O(nlogn)***

Powiemy sobie również czym jest rekurencja i jak pomaga nam pisać programy.

Wymagana znajomość funkcji C++.

### Rekurencja

Rekurencja, czasem nazywana rekursją, polega na wywołaniu przez funkcję samej siebie.
Większość problemów, które można rozwiązać rekurencją, możemy rozwiązać zwykłą pętlą.
Jednak zaletą rekurencji jest prostota jej zapisu, często nasz kod będzie przejrzystszy.
Zrozumienie jej jest niezbędne w algorytmice, ponieważ implementacje wielu algorytmów na niej polegają.

#### Jak napisać rekurencję dobrze?

To nie tak proste, jakby się mogło wydawać :-). Przede wszystkim musimy zadbać o jej poprawność, w tym
o to, żeby kiedyś zakończyła działanie. NIGDY nie chcemy, żeby funkcja miała możliwość wpadnięcia w nieskończoną
pętlę.

Rozważmy taki problem:

Oblicz silnię z liczby N.

Możemy rozwiązać to zadanie, korzystając z pętli.

```C++
    int wynik = 1;
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        wynik = wynik*i;
    }
    cout << wynik;
```

A jak byśmy zapisali funkcję rekurencyjną, która obliczy silnię?

```C++
    int silnia(int N) {
        if (N == 0) {
            return 1;
        } else {
            return N*silnia(N-1);
        }
    }
```

Rozłóżmy tę naszą funkcję na czynniki pierwsze.

Warunkiem stopu jest warunek ***if (N==0)***. Czy ten warunek zawsze w pewnym momencie będzie spełniony?
W jakim przypadku funkcja nie zatrzyma się i jak możemy ją poprawić?

Poprawiona wersja:

```C++
    int silnia(int N) {
        if (N <= 0) {
            return 1;
        } else {
            return N*(silnia(N-1));
        }
    }
```

Nowy problem:

Oblicz N-tą liczbę Fibonacciego. Przypomnijmy, że ciąg liczb Fibonacciego to taki ciąg, że każda kolejna liczba jest sumą dwóch poprzednich,
przy czym pierwsze dwa elementy ciągu to 1 i 1.

```
Ciąg fibonacciego:
1 1 2 3 5 8 13 21 34 55 ...
```

Rozwiązanie iteracyjne (pętlą):

```C++
    int ostatnia = 1;
    int przedostatnia = 1;
    int N;
    cin >> N;
    if (N == 1 || N == 2) {
        cout << 1;
        return 0;
    }
    N -= 2;
    for (int i = 0; i < N; i++) {
        int temp = ostatnia;
        ostatnia = przedostatnia + ostatnia;
        przedostatnia = temp;
    }
    cout << ostatnia;
```

Rozwiązanie rekurencyjne:

```C++
    int fib(int N) {
        if (N <= 2) {
            return 1;
        } else {
            return fib(N-1) + fib(N-2);
        }
    }
```

Ćwiczenia (oczywiście do rozwiązania funkcją rekurencyjną):
    1) Wypisz N kolejnych liczb naturalnych malejąco
    2) Wypisz na ekranie N gwiazdek
    3) Oblicz 5 do potęgi N-tej
    4) Oblicz sumę liczb od 1 do N
    5) Trudniejsze: Napisz funkcję rekurencyjną, która oblicza NWD dwóch liczb. Do poszperania w internecie, algorytm nazywany algorytmem Euklidesa.

### Sortowanie przez scalanie

#### Na początek problem pomocniczy i niespodzianka :-)

Dane są dwie tablice, jedna ma N elementów, a druga M. Obie są posortowane rosnąco. Jak stworzyć z nich posortowaną tablicę wielkości N+M?
W jakiej złożoności potrafimy to zrobić? Załóżmy, że elementy są nie większe niż miliard.

Pierwsze podejście - znamy sortowanie bąbelkowe, to go użyjmy. Złożoność O(N*N).

Czy da się lepiej? Oczywiście, że się da.

Wiemy, że oba ciągi są posortowane rosnąco. Niech tablica wynikowa to W, a tablice z treści zadania to A[N] i B[M].
Możemy stworzyć tablicę W w złożoności O(N+M).

```C++
    void Polacz(int A[], int B[], int W[]) {
        int i = 0;
        int j = 0;
        int ktora = 0;
        while (i < N && j < M) {
            if (A[i] < B[j]) {
                W[ktora] = A[i];
                i++;
            } else {
                W[ktora] = B[j];
                j++;
            }
            ktora++;
        }

        while (i < N) {
            W[ktora] = A[i];
            i++; ktora++;
        }

        while (j < M) {
            W[ktora] = B[j];
            j++; ktora++;
        }

    }
```

A teraz niespodzianka! Takie zadania możecie spotkać podczas rekrutacji do czołowych firm, takich jak Google i Facebook.
Jesteśmy już o krok od kariery super-programisty ;).

#### No fajnie, ale jak nam to pomaga?

Czy potrafimy posortować tablicę jednoelementową? Oczywiście, że tak. Po prostu nic z nią nie zrobimy.
To w takim razie, korzystając z naszego rozwiązania podproblemu, możemy ,,scalić" dwie tablice jednoelementowe i posortowane
w jedną dwu-elementową tablicę, również posortowaną. Idziemy ,,wyżej'' --- potrafimy scalić szybko dwie tablice dwu-elementowe,
tworząc jedną tablicę cztero-elementową, i tak dalej, i tak dalej.

Zadanie
Posortuj tablicę N-elementową, elementy są nie większe niż miliard, N nie większe niż milion.

Spróbujemy napisać funkcję rekurencyjną, która posortuje nam ciąg. Będzie wyglądała mniej więcej tak:

```C++
    int tablica_do_posortowania[N];
    int tablica_pomocnicza[N];

    void Posortuj(int pocz, int kon) {
        if (kon - pocz == 0) {
            return;
        } else {
            int srodek = (pocz + kon)/2;
            Posortuj(pocz, srodek);
            Posortuj(srodek + 1, kon);
            Scal(pocz, srodek, kon);
        }
    }
```


