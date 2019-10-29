# Użytkowanie struktur dostępnych w bibliotece STL

W trakcie rozwiązywania zadań przydatne mogą być niektóre kontenery i algorytmy dostępne w bibliotece STL.
Nie trzeba znać wszystkich, ale kilka skutecznie przyspieszają pracę nad kodem. Poniżej lista najważniejszych moim zdaniem
i krótkie opisy.

## std::sort()

Pisanie samodzielnie sorta może być zmorą dla początkującego programisty, szczególnie, kiedy goni czas.
Z pomocą przychodzi biblioteka STL, która pozwala w prosty sposób posortować zarówno tablicę, jak i wektor.

```C++

int tab[] = {1, 4, 2, 7, 2};
std::vector <int> V = {1, 4, 2, 7, 2};

sort(tab, tab+5);
sort(V.begin(), V.end());

```

Domyślnie ``sort()`` sortuje rosnąco w złożoności ``O(nlogn)``, gdzie ``n`` to liczba elementów.

### Własny komparator

Załóżmy, że chcemy, żeby nasza funkcja sortująca sortowała malejąco. Nic prostszego :grinning:.
``sort()`` pozwala na dodanie trzeciego argumentu, który nazwiemy  **komparatorem**.
Jest to funkcja zwracająca wartość ``bool``, przyjmująca dwa elementy **tego samego** typu, które ma porównać.

```C++

bool moj_komparator(int A, int B) {
    return A > B;
}

sort(tab, tab+5, moj_komparator);

```

Teraz tablica tab zostanie posortowana rosnąco.

Nie musimy się ograniczać do ``int``. Możemy jako argumenty komparatora podać np ``std::pair <int, int>`` i sortować
rosnąco po pierwszym elemencie pary, a malejąco po drugim. Ogranicza nas tylko wyobraźnia :grinning: .