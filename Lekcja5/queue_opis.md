# Użytkowanie struktur dostępnych w bibliotece STL

W trakcie rozwiązywania zadań przydatne mogą być niektóre kontenery i algorytmy dostępne w bibliotece STL.
Nie trzeba znać wszystkich, ale kilka skutecznie przyspieszają pracę nad kodem. Poniżej lista najważniejszych moim zdaniem
i krótkie opisy.

## std::queue

Queue (pl: kolejka) to kontener reprezentujący znaną z życia codziennego kolejkę do sklepu :grinning:.
Nowy element trafia na koniec kolejki, a usuwać możemy tylko element na jej początku.

Kolejka przechowuje elementy **jednego** typu, który definiujemy przy tworzeniu kolejki.

```C++
std::queue <int> moja_kolejka;
std::queue <std::string> moja_kolejka2;
```

Powyższe fragmenty kodu tworzą nam puste kolejki o nazwach `` moja_kolejka `` i `` moja_kolejka2 ``, przechowujące
odpowiednio ``inty`` i ``string``.

### Dodanie elementu na koniec kolejki

Aby dodać do kolejki element, korzystamy z polecenia `` push ``. Jako argument podamy wartość, którą chcemy dodać na koniec.

```C++
moja_kolejka.push(5);
moja_kolejka.push("Ala ma kota");
```

### Odczytanie elementu z początku kolejki

Żeby odczytać element z początku kolejki, korzystamy z polecenia `` front ``.

```C++
std::cout << moja_kolejka.front();
std::cout << moja_kolejka2.front();
```

### Usuwanie elementu z początku kolejki

Usuwanie elementu w początku kolejki wykonamy z pomocą polecenia `` pop ``.

```C++
moja_kolejka.pop();
moja_kolejka2.pop();
```

### Sprawdzenie, czy kolejka jest pusta

Aby sprawdzić, czy kolejka ma conajmniej 1 element, wywołamy polecenie ``empty()``,
które zwraca wartość ``true``, gdy kolejka jest pusta.

### Zastosowanie kolejki

Mimo (wydawałoby się) wąskiego wachlarza możliwości, kolejka jest wykorzystywana całkiem często podczas rozwiązywania zadań.
Popularny algorytm **BFS**, który poznacie (lub już znacie) na zajęciach korzysta z kolejki.

Główną zaletą kolejki jest jej szybkość --- wymienione powyżej polecenia są wywołane w czasie stałym.