# postprozessor

Dient dem Umwandeln und optimieren der WOP-Ausgabe des CAD-Programms

Unterstützte Importformate:
- *.fmc(IMAWOP4)

Unterstützte Exportformate:
- eigenes Format des Postprozessors
- *.fmx(IMAWOP4)
- *.ganx
- *.ggf(GCodeGenerator)

Funktionsumfang:
- Einstellbares Werkzeugmagazin für jedes Export-Format
- Quelldateinen erhalten/löschen
- Datei-Umbenennung in Standartnamen (einstellbare Liste)
- Bauteile drehen einschließlich auto-Drehen
- Zustelltiefen von Fräsbahnen gemäß Werkzeugmagazin nach Wunsch
- Unterdrüchen von kurzen Fräsbahnen (Fehlausgaben CAD)
- Fräsbahnen optional heraus löschen die deckungsgleich auf 
  einer der Werkstückkanten liegen

Funktionsweise:
- Einlesen aller Dateinen aus einem definierten Quell-Ordner
- Internes Speichern der Daten in einem Programmeigenen Zwischenformat
  (textbasiert)
- Umwandeln des Zwischenformates in gewünschtes Zielformat und speichern als Datei
