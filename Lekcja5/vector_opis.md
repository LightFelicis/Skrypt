# Użytkowanie struktur dostępnych w bibliotece STL

W trakcie rozwiązywania zadań przydatne mogą być niektóre kontenery i algorytmy dostępne w bibliotece STL.
Nie trzeba znać wszystkich, ale kilka skutecznie przyspieszają pracę nad kodem. Poniżej lista najważniejszych moim zdaniem
i krótkie opisy.

## std::vector

Vector (pl: wektor) to kontener bardzo podobny do tablicy, jednak ma kilka użytecznych możliwości, które sprawiają, że dobrze go znać.
Co więcej, można zupełnie zrezygnować z tablic na rzecz wektora bez większej straty dla naszych zadań :grinning:
Jego główną zaletą jest zmienny rozmiar, możemy do niego dodawać elementy i je usuwać.

Wektor, tak jak tablica, trzyma w sobie wiele elementów **jednego** typu. Przy tworzeniu nowego wektora należy się zatem zdecydować, co
on będzie przechowywał.

```C++
std::vector <int> moj_wektor;
std::vector <std::string> moj_wektor2;
```

Powyższe fragmenty kodu tworzą nam puste wektory o nazwach `` moj_wektor `` i `` moj_wektor2 ``, przechowujące
odpowiednio ``inty`` i ``string``.

### Dodawanie elementu do wektora

Tak jak wspomniałam, do wektora można dodawać elementy, bez potrzeby zdefiniowania jego wielkości na początku.
Służy do tego metoda ``push_back()``.

```C++
moj_wektor.push_back(5);
moj_wektor2.push_back("Ala ma kota");
```

Na koniec wektora ``moj_wektor`` zostanie dodana wartość `5`, a na koniec ``moj_wektor2`` zostanie dodany ``string`` ``"Ala ma kota"``.

### Odczytywanie elementu z wektora

Odczytywanie z wektora wartości jest takie samo, jak odczytywanie z tablicy.

```C++
std::vector <std::string> slowa;
slowa.push_back("Sprzatanie");
slowa.push_back("Informatyka");
slowa.push_back("jest super");
std::cout << slowa[0] << " " << slowa[2];
```

W konsoli pojawi się nam napis `Sprzatanie jest super`.

### Usuwanie elementu z wektora

Są plusy ujemne i są plusy dodatnie. Możemy usuwać elementy z wektora, ale tylko ostatni może być usuwany w złożoności `O(1)`.
Służy do tego metoda `pop_back()`

```C++
slowa.pop_back();
```

Po wykonaniu takiej operacji na wektorze `slowa` zniknie z niego `"jest super"`.

### Nadanie rozmiaru

Możemy nadać wektorowi konkretny rozmiar za pomocą metody `resize()`

```C++
std::vector <int> moj_wektor;
moj_wektor.resize(5);
std::vector <int> moj_wektor2;
moj_wektor2.resize(20, -1);
```

W pierwszym przypadku `moj_wektor` będzie wielkości 5.
Drugi argument `resize()` jest opcjonalny i oznacza jaką wartością początkową chcemy zapełnić wektor. Przydatne w dynamikach :grinning:

`moj_wektor2` będzie wielkości 20 i będzie wypełniony `-1`.

### Kilka protipów

Wektor może imitować tablicę dwuwymiarową równie dobrze, jak jednowymiarową.

```C++
std::vector<std::vector<int>> oceny_uczniow;
oceny_uczniow.resize(5);
oceny_uczniow[0].push_back(1);
```

`oceny_uczniów` możemy sobie wyobrazić jako 5 szufladek, które możemy dowolnie daleko "wysunąć", dokładając kolejne liczby.
W powyższym przypadku uczeń o numerze `0` dostał ocenę `1`... Ale może kiedyś dostanie lepszą :smile:

```C++
std::vector<std::vector<int>> oceny_uczniow;
oceny_uczniow.resize(5, std::vector<int>(5));
```

W tym przypadku `oceny_uczniow` są identyczne tablicy o wymiarach 5x5.

#### Wyrzucanie w złożoności O(1) elementu nie z końca, to w końcu się tak da??

Da się, tylko jest to sztuczka, którą nie zawsze możemy zastosować. Załóżmy, że chcemy wyrzucić element na indeksie `2` z wektora
intów `moj_wektor` o wielkości `10`.

```C++
moj_wektor[2] = moj_wektor[9];
moj_wektor.pop_back();
```

Element z indeksu `2` został wyrzucony, z wektora, ostatni element w nim pozostał. Z tą różnicą, że teraz elementy w wektorze są
w innej kolejności od tej przed zmianą (ostatni element jest na indeksie `2`). Ta sztuczka jest użyteczna, kiedy nie interesuje nas
kolejność elementów. W sytuacji, gdy np. chcemy, żeby elementy w wektorze były posortowane, sztuczka nie zadziała.
