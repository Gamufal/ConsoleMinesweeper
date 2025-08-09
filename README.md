# ConsoleMinesweeper
Prosta konsolowa implementacja klasycznej gry Saper w języku C++.
Projekt napisany od podstaw z wykorzystaniem programowania obiektowego oraz bibliotek standardowych C++20.

## Funkcjonalności
- 3 poziomy trudności
- Losowe rozmieszczenie min
- Rekurencyjne odkrywanie pustych pól
- Walidacja komend użytkownika
- Zapis/odczyt stanu gry do/z pliku
- Licznik czasu gry

## Struktura projektu
Cell – klasa bazowa reprezentująca pole
MineCell, EmptyCell, NumberCell – specjalizacje
Board – logika planszy, rozmieszczanie min, odkrywanie pól, zapisywanie stanu gry
Game – interakcja z użytkownikiem, sterowanie przebiegiem gry

## Uruchomienie
Kompilacja:
`g++ -std=c++20 main.cpp time.o Cell.cpp Board.cpp Game.cpp -o saper`

Uruchomienie:
`./saper`

## Wymagania
Kompilator C++20

## Autor
Gamufal - Kamil Kotorc

