# Użytkowanie struktur dostępnych w bibliotece STL

W trakcie rozwiązywania zadań przydatne mogą być niektóre kontenery i algorytmy dostępne w bibliotece STL.
Nie trzeba znać wszystkich, ale kilka skutecznie przyspieszają pracę nad kodem. Poniżej lista najważniejszych moim zdaniem
i krótkie opisy.

## std::map

Kiedy idziemy do supermarketu, to każdy produkt ma przypisaną konkretną cenę. Snickers kosztuje 1,89zł, a Mars 1,69zł.
Gdybyśmy spróbowali przedstawić asortyment sklepu za pomocą zwykłej tablicy, musielibyśmy zapewne użyć dwóch tablic.
Jednej, która każdemu produktowi nadawałaby indeks, druga tablica każdemu indeksowi nadawałaby cenę.
Szybkie odpowiadanie na zapytanie np. o cenę czekolady Kinder również nie byłoby trywialne.
Z pomocą map (pl: mapy) możemy zaprezentować powyższą sytuację w bardzo wygodny sposób.

Mapa przechowuje pary `` {klucz, wartość} ``. O kluczu możemy myśleć jak o nazwie batonika, a wartością będzie jego cena.
Przy tworzeniu nowej mapy musimy podać jakiego typu będzie klucz i jakiego typu będzie wartość.

```C++
std::map <std::string, double> batoniki;
std::map <int, std::string> dziennik_lekcyjny;
```
W pierwszej mapie `` batoniki `` kluczem są ``string``, a wartościami są ``double``.
W drugiej mapie ``dziennik_lekcyjny`` kluczem są ``int``, a wartościami są ``string``.

### Dodanie elementu do mapy

Aby dodać element do mapy, możemy skorzystać z zapisu jak przy nadawaniu wartości w tablicy.

```C++
batoniki["Snickers"] = 1.89;
dziennik_lekcyjny[1] = "Małgosia Kowalska";
```

Możemy też skorzystać z polecenia `` insert ``. Jako argument podajemy parę ``{klucz wartość}``.

```C++
batoniki.insert({"Snickers", 1.89});
dziennik_lekcyjny.insert({1, "Małgosia Kowalska"});
```

### Odczytanie elementu z mapy

Element z mapy odczytujemy tak, jak z tablicy.

```C++
std::cout << batoniki["Mars"];
std::cout << dziennik_lekcyjny[103];
```

### Usuwanie elementu z mapy

Element z mapy możemy usunąć za pomocą np. klucza, korzystając z polecenia ``erase``. Jako argument podajemy wartość klucza.

```C++
batoniki.erase("Kinder Country");
dziennik_lekcyjny.erase(5);
```

### Zastosowanie mapy

Mapa jest potężnym narzędziem, które pozwala nam tworzyć ,,tablicę'' o dowolnych argumentach.
Możemy jej użyć np gdy mamy milion liczb wielkosci ``1e18``, to możemy je **przeskalować**
do liczb rzędu miliona. Przydaje się przy algorytmie zamiatania.
