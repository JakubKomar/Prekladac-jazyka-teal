# Implementace překladače imperativního jazyka IFJ21 (obdoba Teal)
Práce se zaobírá implementací překladače programovacího jazyka IFJ21(jazyk funkčně podobný jazyku Teal) na jazyk IFJ21code. 

### Struktura překladače
Tento překladač se skládá ze 3 hlavních částí - scanner, parser a generátor. Překlad řídí primárně parser, který se skládá ze dvou modulů - modul pro výrazy, který se stará o zpracování výrazů pomocí precedenční analýzy a modul pro parsování ostatních konstrukcí vstupního jazyka (pomocí LL(1) gramatiky). Řídící logika parseru vhodně přepíná mezi těmito moduly.
Parser pracuje s tokeny, které mu na vyžádání poskytuje skener. Scanner čte vstupní kód po jednotlivých znakách a pomocí konečného automatu rozlišuje jednotlivé tokeny. 


Výstupní kód se generuje přímo v modulech parseru, složitější konstrukce se generují přes modul generátor.


Jednotlivé moduly mezi sebou komunikují pomocí sdílené struktury nebo její části, kterou si předávají pomocí ukazatele. Tato struktura je členěna na části podle účelu. Tento přístup byl zvolen kvůli potřebě přistupovat ke stejným zdrojům z různých modulů.


Pokud nastane v některé části překladu chyba, je zavolána obslužná funkce, která vygeneruje krátký report o chybě a následně skočí do funkce main na návěstí, kde v případě, že chyba nebyla vyvolána chybnou alokací paměti, dealokují zdroje aplikace a program vrátí příslušnou návratovou hodnotu.


#### Scanner
Scanner je implementován podle konečného automatu hladovou  metodou - čte se vstup dokud automat nezhavaruje, pokud byl poslední stav konečný, vrací se jemu odpovídající token, jinak je nahlášena chyba na úrovni lexikální analýzy. Scanner zároveň rozpoznává klíčová slova a volání funkce.

#### Parser
Parser je implementován pomocí metody rekurzivního sestupu. Implementace je stavěna LL(1), kdy neterminál je vyobrazen v programu jako samostatná funkce. Vzhledem k podobnosti některých neterminálů, jsme některé neterminály vhodně spojili. Na principu kontroly tento zásah však nemá vliv. Kontroly deklarací, datových typů, seznamů parametrů, atd. se provádí přímo při průchodu gramatickými pravidly. Stejně tak se provádí generování výsledného kódu. Je tedy zvolen jednoprůchodový způsob parsování vstupního kódu. Situace, kdy nelze generovat kód přímo (např.: dekalarace proměnných ve WHILE cyklu) jsme řešili pomocí pomocného zásobníku, který se ve vhodnou chvíli (typicky při konci WHILE cyklu) vyprázdnil. 

#### Parser pro výrazy
Využívá metody precedenční analýzy. Generování kódu výrazů probíhá během průchodu algoritmem a to s využitím zásobníku(v cílovém kódu). Samotný výpočet se poté kvůli přetypování operátorů a kontrol na výskyt hodnoty nil provádí za pomocí před připravených registů, které jsou par využity u  tříadresních instrukcí.
Algoritmus operuje s precedenční tabulkou, která je v kódu implementovaná jako konstantní dvojrozměrné pole.
##### Precedenční tabulka
Při implementaci se zjistilo, že některé operátory mají stejnou precedenci a tak byly některé operátory v tabulce sjednoceny.
#### Generování
Generování výstupního kódu probíhá při průchodu gramatickými pravidly. Po přečtení hlavičky vstupního kódu se vygeneruje hlavička výsledného kódu s vestavěnými funkcemi. Názvy proměnných se v jednotlivých rozsazích platnosti se odlišují pomocí dekorátoru, který zajišťuje, že daná proměnná nebude redefinována. Stejným způsobem se odlišují jednotlivé vygenerované struktury typu IF/WHILE.  
Předávání argumentů mezi jednotlivými vygenerovanými funkcemi probíhá za pomocí zásobníku. 

#### Datový model/tabulky symbolů
Tabulka symbolů je implementována pomocí binárního stromu. Jednotlivé rozsahy platnosti jsou rozděleny pomocí zásobníku na rámce - každá položka představuje jeden binární strom. Při vyhledání v datovém modelu se jde od hora zásobníku směrem ke spodu. Pokud se ve struktuře vyhledává lokální proměnná, vyhledává se v zásobníku, dokud se nenarazí na zarážku - představuje konec rozsahu platnosti funkce. 

#### Hodnocení projektu
Rozšíření: FUNEXP

- Procentuální hodnocení modulů překladače:
- Lexikální analýza (detekce chyb): 100 % (174/174)
- Syntaktická analýza (detekce chyb): 94 % (182/192)
- Sémantická analýza (detekce chyb): 91 % (270/294)
- Sémantické/běhové chyby (detekce): 100 % (62/62)
- Interpretace přeloženého kódu (základní): 91 % (278/305)
- Interpretace přeloženého kódu (výrazy, vest. funkce): 100 % (198/198)
- Interpretace přeloženého kódu (komplexní): 86 % (295/343)
- BOOLTHEN 0 % (0/170)
- CYCLES 0 % (0/150)
- FUNEXP 33 % (50/150)
- OPERATORS 0 % (0/50)
- Celkem bez rozšíření: 93 % (1459/1568)

#### Autoři:
- Jakub Komárek (xkomar33) 
- Křivánek Jakub (xkriva30) 
- Matušík Adrián (xmatus35) 
- Tverdokhlib Vladyslav V. (xtverd01) 

 
