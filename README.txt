Die Dateien in diesem ZIP-Archiv bilden ein zusammenhängendes Projekt, das aus zwei Modulen besteht.
Im Kurs wurde die Technik hierzu als freiwilliger Bonus behandelt; auch ohne diese Einheit ist dieser Code zu verstehen.

Kompilieren:
gcc -std=c11 -Wall -Wextra -Wpedantic 998_main.c 998_linkedlist.c -o linkedlist.exe

Ausführen
linkedlist.exe

Verstehen:
In erster Näherung kann man sich vorstellen, dass der Compiler die einzelnen Code-Dateien wieder zu einem Dokument zusammenfügt. Man erhält dasselbe Ergebnis, wenn man die Dateien in ein Dokument zusammenkopiert, und dabei diese Reihenfolge einhält:

  998_linkedlist.h
  998_linkedlist.c
  998_main.c

Zeile 5 aus 998_linkedlist.c (#include "998_linkedlist.h") und Zeile 11 aus 998_main.c (#include "998_linkedlist.h") müssen dabei natürlich entfernt werden – wenn wir manuell die Code-Elemente zusammenkopieren, dann erledigen wir bereits den Arbeitsschritt "#include".
Ab diesem Zusammenkopieren kann das entstandene Dokument gelesen werden wie "normaler C-Code"


Die Datei 998_linkedlist_oneFile.c enthält eine "Übersetzung" des Codes in eine einzige Datei, also das Ergebnis genau diesen Zusammenkopierens. Die einzelnen Blocks wurden hierbei leicht umsortiert, um eine bessere Gliederung nach Themen zu bieten.
