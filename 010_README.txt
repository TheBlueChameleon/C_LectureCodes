Die Dateien in diesem ZIP-Archiv bilden ein zusammenhängendes Projekt, das aus zwei Modulen besteht.
Im Kurs wurde die Technik hierzu als freiwilliger Bonus behandelt; auch ohne diese Einheit ist dieser Code zu verstehen.

Kompilieren:
gcc -std=c11 -Wall -Wextra -Wpedantic 010_main.c 010_linkedlist.c -o linkedlist.exe

Ausführen
linkedlist.exe

Verstehen:
In erster Näherung kann man sich vorstellen, dass der Compiler die einzelnen Code-Dateien wieder zu einem Dokument zusammenfügt. Man erhält dasselbe Ergebnis, wenn man die Dateien in ein Dokument zusammenkopiert, und dabei diese Reihenfolge einhält:

  010_linkedlist.h
  010_linkedlist.c
  010_main.c

Zeile 5 aus 010_linkedlist.c (#include "010_linkedlist.h") und Zeile 11 aus 010_main.c (#include "010_linkedlist.h") müssen dabei natürlich entfernt werden – wenn wir manuell die Code-Elemente zusammenkopieren, dann erledigen wir bereits den Arbeitsschritt "#include".
Ab diesem Zusammenkopieren kann das entstandene Dokument gelesen werden wie "normaler C-Code"


Die Datei 010_linkedlist_oneFile.c enthält eine "Übersetzung" des Codes in eine einzige Datei, also das Ergebnis genau diesen Zusammenkopierens. Die einzelnen Blocks wurden hierbei leicht umsortiert, um eine bessere Gliederung nach Themen zu bieten.
