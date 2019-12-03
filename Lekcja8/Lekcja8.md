# Wstęp do programowania dynamicznego

Na lekcji drugiej mówiliśmy o rekurencyjnym algorytmie
wyszukującym ```n```-tą liczbę Fibonacciego. Przypomnijmy:

```C++
int fib(int n) {
    if (n <= 1) {
        return 1;
    }
    return fib(n-1) + fib(n-2);
}
```

Jeśli rozpiszemy sobie drzewko wywołań rekurencyjnych, to
nietrudno zauważyć, że złożoność jest wykładnicza.

Postaramy się rozwiązać problem szukania liczb Fibonacciego
inną metodą, zwaną programowaniem dynamicznym.

Pomysł jest następujący:
W tablicy fib[i] zapiszemy ```i```-tą liczbę Fibonacciego.
Dla ```i``` równego 0 lub 1 wartość jest znana. Kolejne wartości liczb Fibonacciego będziemy wyznaczali pętlą.

```C++
long long fib[100];
fib[0] = 1;
fib[1] = 1;
for (int i = 2; i < 100; i++) {
    fib[i] = fib[i-1] + fib[i-2];
}
```

Po pierwsze, po obliczeniu raz wartości w tablicy (liniowo!!!), na zapytania o ```k```-tą liczbę Fibonacciego odpowiadamy w czasie stałym.
Cierpi nasza złożoność pamięciowa, ponieważ trzymamy dużą tablicę, ale w tym przypadku nie jest to dużym problemem.

Cała idea tej metody opiera się na poniższym założeniu.

Dla początkowych wartości znam wynik (w tym przypadku dla pierwszych kilku liczb Fibonacciego znam ich wartość) oraz z ```n``` poprzednich elementów potrafię
wyznaczyć ```n+1```-wszy element.

## Przykładowe problemy dynamiczne

### Króliczek marchewka

Zadanie „Króliczek” opowiada o polu marchewkowym i o króliczku.
Pole marchewkowe składa się z jednej grządki, na której rośnie ```n```
  marchewek.
Pierwsza marchewka na grządce ma numer ```1```, a o statnia ma numer ```n```.
Dla każdej marchewki znamy jej smaczność ```marchewki[i]```,
  która jest nieujemną liczbą całkowitą.
Króliczek chce zebrać z grządki pewne marchewki w taki sposób, aby:
* sumaryczna smaczność zebranych marchewek była największa możliwa, oraz aby
* dla każdych dwóch sąsiadujących marchewek, co najmniej jedna z nich
  **nie została** zebrana.

Dla przykładu, niech ```n = 10``` oraz niech
  ```marchewki[] = {𝟱, 0, 4, 𝟭𝟬, 0, 𝟭, 1, 1, 𝟮𝟬, 1}```.
Jeśli króliczek wybierze pogrubione marchewki, to otrzyma sumę smaczności
  ```5 + 10 + 1 + 20 = 36```.
Jest to optymalny sposób wyboru marchewek.

#### Rozwiązanie

Użyjemy metody dynamicznej – dla każdego prefiksu ciągu marchewek obliczymy
  wynik, ale przy pewnych założeniach:
* ```dp[p][OSTATNIA_WZIETA]``` będzie oznaczało jaką największą sumę smaczności
  możemy uzyskać zbierając pewne marchewki spośród marchewek od ```1``` do
  ```p```, ale przy założeniu, że ostatnia marchewka (```p```) została zebrana,
* ```dp[p][OSTATNIA_NIEWZIETA]``` będzie oznaczało jaką największą sumę
  smaczności możemy uzyskać zbierając pewne marchewki spośród marchewek od
  ```1``` do ```p```, ale przy założeniu, że ostatnia marchewka (```p```)
  **nie została** zebrana.

Jakie można wymyślić wartości początkowe?
* ```dp[0][OSTATNIA_NIEWZIETA] = 0``` – jeśli prefiks jest pusty, to nie możemy
  zebrać żadnej marchewki, w szczególności nie możemy wziąć tej ostatniej,
  więc założenie jest spełnione.
* ```dp[0][OSTATNIA_WZIETA] = -oo``` – jeśli prefiks jest pusty, to nie możemy
  zebrać żadnej marchewki, w szczególności nie możemy wziąć tej ostatniej,
  więc założenie nie jest spełnione, więc trzeba wpisać wartość, która będzie
  oznaczać, że takie rozwiązanie nie istnieje (tzn. minus nieskończoność).
* ```dp[1][OSTATNIA_NIEWZIETA] = 0``` – jest do wyboru tylko jedna marchewka,
  ale dodatkowo wiemy, że nie możemy jej wziąć (takie jest założenie),
  zatem najlepszym (jedynym) rozwiązaniem jest niewzięcie żadnej marchewki.
* ```dp[1][OSTATNIA_WZIETA] = marchewki[1]``` – jest do wyboru tylko jedna
  marchewka, ale dodatkowo wiemy, że musimy ją wziąć (takie jest założenie),
  zatem najlepszym (jedynym) rozwiązaniem jest wzięcie tej marchewki.

Jak wygląda wyznaczanie wartości dla prefiksu ```p``` na podstawie wartości
  dla prefiksu ```p - 1```?
* ```dp[p][OSTATNIA_WZIETA] = marchewki[p] + dp[p - 1][OSTATNIA_NIEWZIETA]```
  – jeśli wiemy, że ostatnia marchewka (```p```) musi zostać wzięta, to dodajemy
  jej smaczność do wyniku (```marchewki[p]```); następnie, skoro marchewka
  ```p``` została zebrana, to marchewka ```p - 1``` nie może zostać zebrana
  (z powodu drugiej reguły w zadaniu), zatem doliczamy
  ```dp[p - 1][OSTATNIA_NIEWZIETA]```.
* ```dp[p][OSTATNIA_NIEWZIETA] = max(dp[p - 1][OSTATNIA_WZIETA], dp[p - 1][OSTATNIA_NIEWZIETA])```
  – jeśli wiemy, że ostatnia marchewka (```p```) nie może zostać wzięta,
  to marchewka ```p - 1``` może być albo wzięta albo nie (mamy wolny wybór),
  zatem wybieramy lepszą z tych dwóch opcji.

Jak wygląda odczytanie ostatecznego wyniku (tzn. wyniku dla całego ciągu)?
Wystarczy obliczyć ```max(dp[n][OSTATNIA_NIEWZIETA], dp[n][OSTATNIA_WZIETA])```,
  ponieważ musimy rozważyć dwa przypadki (czy zbieramy ```n```-tą marchewkę czy
  nie), a następnie wybrać lepszy z nich.

Jeśli złożymy te początkowe wartości i przejście z prefiksu ```p - 1```
  do prefiksu ```p```, to otrzymamy następujący kod:
```C++
int OSTATNIA_WZIETA = 0;
int OSTATNIA_NIEWZIETA = 1;
int dp[n + 1][2];

dp[0][OSTATNIA_WZIETA] = 0;
dp[0][OSTATNIA_NIEWZIETA] = -1;  // Wiemy, że wynik jest nieujemny, więc -1
                                 // jest wystarczającą nieskończonością.
for (int p = 1; p <= n; p++) {
  dp[p][OSTATNIA_WZIETA] = marchewki[p] + dp[p - 1][OSTATNIA_NIEWZIETA];
  dp[p][OSTATNIA_NIEWZIETA] = std::max(dp[p - 1][OSTATNIA_WZIETA],
                                       dp[p - 1][OSTATNIA_NIEWZIETA]);
}

int ostateczny_wynik = std::max(dp[n][OSTATNIA_WZIETA],
                                dp[n][OSTATNIA_NIEWZIETA]);
```

Ten kod obliczy następujące wartości w tablicy ```dp```:

|                         ```p``` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|
|--------------------------------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|              ```marchewki[p]``` | – | 5 | 0 | 4 | 10| 0 | 1 | 1 | 1 | 20| 1 |
|    ```dp[p][OSTATNIA_WZIETA]``` | -1| 5 | 0 | 9 | 15| 9 | 16| 16| 17| 36| 18|
| ```dp[p][OSTATNIA_NIEWZIETA]``` | 0 | 0 | 5 | 5 | 9 | 15| 15| 16| 16| 17| 36|

### Żabka muszki
Zadanie „Żabka” opowiada o kamyczkach i o żabce.
Jest sobie ```n``` kamyczków ustawionych w rzędzie i ponumerowanych
  od ```1``` do ```n```.
Nad kamyczkami latają sobie muszki.
Dla każdego kamyczka znamy smaczność muszek fruwających nad nim –
  ```muszki[i]```.
Smaczność jest nieujemną liczbą całkowitą.
Żabka startuje na kamyczku ```1```, chce sobie poskakać tak, aby ostatecznie
  skończyć na kamyczki ```n```.
Żabka może skakać tylko wprzód (tzn. w kierunku rosnących numerów kamyczków)
  o co najmniej ```2``` i co najwyżej ```3```, tzn. z kamyczka ```i``` może
  wskoczyć tylko na jeden z kamyczków: ```i + 2``` lub ```i + 3```.
Za każdym razem gdy żabka znajdzie się na kamyczku, zżera wszystkie muszki,
  które nad tym kamyczkiem szybują.
Pomóż żabce i znajdź taką trasę, aby pochłonąć muszki o jak największej
  sumarycznej smaczności.

Dla przykładu, niech ```n = 10``` oraz niech
  ```muszki[] = {𝟱, 0, 4, 𝟭𝟬, 0, 𝟭, 1, 𝟭, 20, 𝟭}```.
Jeśli muszka będzie skakać po kolejnych pogrubionych kamyczkach, to otrzyma
  sumę smaczoności ```5 + 10 + 1 + 1 + 1 = 18```.
Jest to optymalny sposób spałaszowania muszek.
Zauważ, że żabka nie może wskoczyć na kamyczek, nad którym unoszą się muszki o
  smaczności 20, ponieważ wtedy nie dałaby rady dotrzeć na ostatni kamyczek.

#### Rozwiązanie

Użyjemy metody dynamicznej – dla każdego prefiksu kamyczków obliczymy wynik.
Tzn. ```dp[p]``` będzie oznaczać sumaryczną smaczność muszek z optymalnej trasy,
  która zaczyna się na kamyczku ```1``` i kończy się na kamyczku ```p```.

Jako początkowe wartości jesteśmy w stanie wyznaczyć?
* ```dp[1] = muszki[1]```
* ```dp[2] = -1``` – żabka nie może doskoczyć do kamyczka 2
* ```dp[3] = muszki[1] + muszki[3]```

Jeśli ```p >= 4```, to można zrobić następujące przejście:
  ```dp[p] = muszki[p] + max(dp[p - 2], dp[p - 3])```.
Ostateczny wynik będzie się znajdował pod ```dp[n]```.

Wartość ```-1``` pod ```dp[2]``` pełni bardzo ważną rolę – ```-1``` nie tylko
  oznacza, że doskoczenie na drugi kamyczek jest niemożliwe.
Taka wartośc również gwarantuje, że jeśli użyjemy wartości ```dp[2]``` licząc
  wyniki dla większych ```p```, to ta wartość nie wpłynie na wynik:
* ```dp[4] = muszki[4] + max(dp[2], dp[1]) = muszki[4] + max(-1, dp[1]) = muszki[4] + dp[1]```,
* ```dp[5] = muszki[5] + max(dp[3], dp[2]) = muszki[5] + max(dp[3], -1) = muszki[5] + dp[3]```.

Pełny kod wygląda następująco:
```C++
int dp[n + 1];

dp[1] = muszki[1];
dp[2] = -1;
dp[3] = muszki[1] + muszki[3];
for (int p = 4; p <= n; p++) {
  dp[p] = muszki[p] + std::max(dp[p - 2], dp[p - 3]);
}

int ostateczny_wynik = dp[n];
```

Ten kod obliczy następujące wartości w tablicy ```dp```:

|         ```p``` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|
|----------------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| ```muszki[p]``` | 5 | 0 | 4 | 10| 0 | 1 | 1 | 1 | 20| 1 |
|     ```dp[p]``` | 5 | -1| 9 | 15| 9 | 16| 16| 17| 36| 18|
