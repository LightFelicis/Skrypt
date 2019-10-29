# Użytkowanie struktur dostępnych w bibliotece STL

W trakcie rozwiązywania zadań przydatne mogą być niektóre kontenery i algorytmy dostępne w bibliotece STL.
Nie trzeba znać wszystkich, ale kilka skutecznie przyspieszają pracę nad kodem. Poniżej lista najważniejszych moim zdaniem
i krótkie opisy.

## std::priority_queue

To drugi, po `` std::queue `` typ nazywany kolejką, tym razem priorytetową. W ,,zwykłej'' kolejce warunkiem decydującym,
który element będzie kolejnym, był czas dodania. W kolejce priorytetowej tym warunkiem będzie wartość obiektu.

Wartości w kolejce priorytetowej są **jednego** typu (deklarowanego przy tworzeniu kolejki).
Są przechowywane posortowane malejąco.

```C++
std::priority_queue<int> moja_kolejka;
std::priority_queue<std::pair<int, int>> moja_kolejka2;
```
### Dodawanie elementu

Dodawanie elementu do kolejki priorytetowej jest identyczne jak w przypadku zwykłej.

```C++
moja_kolejka.push(1);
moja_kolejka.push(7);
```

### Odczytanie pierwszego elementu i usunięcie go

Usuwamy tak samo, poleceniem ``pop``.
Odczytanie największego elementu w kolejce wykonujemy za pomocą polecenia ``top``.

```C++
std::cout << moja_kolejka.top() << " ";
moja_kolejka.pop();
std::cout << moja_kolejka.top();
```

Zostanie wypisane ``7 1``, ponieważ po usunięciu największego elementu ``7``
największym stanie się ``1``.

### Zastosowanie kolejki priorytetowej i złożoność czasowa

Kolejki priorytetowej użyjemy np podczas implementacji algorytmu Dijkstra.

W przeciwieństwie do std::queue, dodanie i usunięcie elementu nie wykonuje się w czasie stałym,
a w złożoności logarytmicznej od wielkości kolejki. Odczytanie wykonuje
się w czasie stałym.
