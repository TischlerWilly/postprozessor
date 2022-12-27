# postprozessor

Dient dem Umwandeln und optimieren der WOP-Ausgabe des CAD-Programms

Mögliche Importformate:
  *.FMC (IMAWOP4)
  *.fmc  (IMAWOP4)
  *.DXF mit Versionskennung AC1009
  *.dxf mit Versionskennung AC1009

Hinweis zum GANX-Export:
  Fräskonturen werden nicht ausgegeben.


--- Leistungsumfang ----

Import von fmc:
- Werkstückgröße [PGKOPF40]
- Kanteninformation (über Kommentare)
- Gehrung [ZYSCHN40]
- Einzelbohrung vertikal [VBDMES40]
- HBE x+ [HBXPLU40]
- HBE x- [HBXMIN40]
- HBE y+ [HBYPLU40]
- HBE y- [HBYMIN40]
- Bohrbild in X [VBX_40]
- Bohrbild in Y [VBY_40]
- Lochreihe Anfang-Ende [VBLAEN40]
- Lochreihe Mitte-Anfang [VBLMIT40]
- Topfbandbohrung [VBTOPF41]
- Kreistasche [ZYKTFR40]
- Rechtecktasche [ZYRTFR40]
- Nut [ZYSNUT40]
- Falz [ZYFALZ40]
- Aufruf Fräser [KAFRAE40]
- Gerade Fräsbahn [G1]
- Bogen fräsen im UZS [G2]
- Bogen fräsen im GUZS [G3]


Import von dxf:
- Werkstückgröße (Polilinie)
- Einzelbohrung vertikal (Kreis)
- Einzelbohrung horizontal (2 Linien)
- Nut vertikal (2 oder 4 Linien)
- Kreistasche vertikal (Kreis)
- Rechtecktasche vertikal (4 Linien)
- Fräsung vertikal (Linien, Bögen)


Bearbeitungsoptimierungen:
- Drehen AUTO
- Borraster-Erkennung
- Durchgangsbohungen splitten
- Automatische Werkzeugzuweisung
- Plausibilitätsprüfung (Warnungen)


Weiteren Funktionen:
- Doppelte (identische) Bohrungen werden beim Import ignoriert
- Werkzeugmagazin für jedes Exportformat
- Werkstücke beim Import automatisch benennen
- Werkstücke dem Namen nach sortieren (bei Import)
- Werkstücke umbenennen
- Exportübersicht
- Werkstücke bearbeiten
- Kurze Geraden ignorieren mit Angabe des Schwellenwertes (fmc)
- Formartierungen aufbrechen (fmc)
- Werkstück vergrößern als Zugabe für Gehrungen (fmc)
- Werkstücke ausblenden
- Export in hierarchischen Projekt-Unterordnern

