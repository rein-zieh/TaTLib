# TaTLib - This and That Library (Modellbahn-Kram)

Die TaTLib ist eine Arduino Klassen-Bibliothek für verschiedene Modellbahn-Basteleien. 
Noch eine Modellbahn-Bibliothek? Ja, es gibt zwar gefühlt für jedes Modellbahn-Problem x verschiedene Bibliothek,
aber da ich gerne selbst Bastel und Programiere, muss es eben auch eine eigene Bibliothek sein ;-) .

Die Klassen-Bibliothek wurde so entwickelt, dass sie von der Logik her für mich passt. 
Es wurde nicht versucht den Code auf Effizienz zu optimieren. 
Im Vordergrund stand für mich die Nachvollziehbarkeit auch für nicht-C++-Experten (zu denen ich auch mich zähle).

## Eigenschaften
Die TaTLib beinhaltet bisher diverse Klassen zur Lösung verschiedener Beleuchtungsprobleme in der Modelbahnwelt. 
Ziel ist es mit einem Arduino mehrere Beleuchtungen gleichzeitig und unabhänging voneinander zu steuern, 
die Verwendung der '''delay'''-Funktion kam daher nicht in Frage. Alle Abläufe werden ausschließlich durch '''timer''' realisiert.

## Klassen

### TaTTimer (TaTBase.h)
Hilfs-Klasse für verschiedene Timer-Funktionen.

### TaTSensor und TaTActor (TaTBase.h)
Basisklassen für alle Sensoren (z.B. Knöpfe und Schalter) und alle Actoren (im wesentlichen Leds).

### TaTButton, TaTButtonInv und TaTButtonOnOff (TaTButtons.h)
Klasse für verschiedene Taster und Schalter.

### TaTLed (TaTLed.h)
Klasse für eine einfache Beleuchtung mittels Led. 

Unterstützt: 
- Ein- und Ausschaltverzögerungen

### TaTTube (TaTTube.h)
Klasse für die Simulation von Neonröhren. 

Unterstützt:
- Ein- und Ausschaltverzögerungen
- Flakern beim Einschalten (Analoge und digitale Muster)
- sporadische Aussetzer
- Flakern beim Wiedereinschalten (Analoge und digitale Muster)

### TaTWelder (TaTWelder.h)
Klasse für die Simulation von Schweißgeräten. 

Unterstützt:
- Einschaltverzögerungen
- Mehrere Flaker-Muster (Analoge und digitale Muster)
- variable Pausen
