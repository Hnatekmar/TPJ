# Programovací jazyk Mirage
Mirage je čistě funkcionální jazyk, který slouží k popisu a tvorbě vektorových obrázků napsaný jako semestralní projekt do předmětu TPJ.

# Základy jazyka
## Výrazy

### Aplikace (volání funkcí/maker)
```clojure
(<funkce nebo makro> <vyrazy (argumenty)>)
```
Například 

```clojure
(+ 1 2)
```
Se vyhodnotí jako 3, protože se za symbolem + nachází funkce, pro sčítání čísel

### Atomy
* čísla (například ```100.5```)
* řetězce (například ```"mirage"```)
* boolean (```$p``` nebo ```$n```)
* symboly (například ```+```)

### Expanze
Expanze je syntaktický cukr pro volání funkce s jedním parametrem. Například:

```clojure
(importuj "mirage/mirage.mir")
```
lze s pomocí expanze zapsat jako
```clojure
#importuj "mirage/mirage.mir"
```
### Užitečné funkce/makra/formy
#### definuj
Přiřadí k danému symbolu hodnutu.
Například:
```clojure
(definuj PI 3.14)
```
#### funkce
Vytvoří funkci. Přebírá list argumentů a tělo funkce. List argumentů se může skládat pouze ze symbolů 
Například:
```clojure
; Funkce, která vrátí to, co přebrala
(definuj identita (funkce (x) x))
(identita (+ 5 6)) ; 11
```
V listu lze použít speciální symbol ```...```, který označuje, že se jedná o variadickou funkci. Všechny argumenty jsou přeloženy do listu. Příklad:
```clojure
(definuj prvniArgument (funkce (...) (prvni ...)))
(prvniArgument 1 2 3) ; 1
```
Symbol ```...``` musí být vždy na konci seznamu argumentů.

Každá funkce má svůj vlastní scope a při její tvorbě si pamatuje celý scope v době jejího vytvoření. Lze tedy například vytvořit list jen s pomocí funkcí:

```clojure
(definuj mujList (funkce (hlava telo)
                         (funkce (f)
                                 (f hlava telo))))
(definuj prvni (funkce (hlava telo) hlava))
(definuj zbytek (funkce (hlava telo) telo))
(definuj konecListu -1)
(definuj cisla (mujList 0 (mujList 2 (mujList 3 konecListu))))

(prvni cisla) ; 1
(prvni (zbytek cisla)) ; 2
```
#### Listy
Funkce list vrací list položek například:
```clojure
(list (+ 1 3) 5 "ahoj") ; (4 5 "ahoj")
```
Nad listy lze dělat několik základních operací:
Získat první prvek (v případě, že je list prázdný program spadne)
```clojure
(definuj cisla (list 1 2 3))
(prvni cisla) ; 1
```
Získat zbytek listu (bez prvního prvku)
```clojure
(definuj cisla (list 1 2 3))
(zbytek cisla) ; (2 3)
```
Získat počet prvků v listu
```clojure
(definuj cisla (list 1 2 3))
(velikost cisla) ; 3
```
Všechny tyto operace lze provádět i nad řetězcem (s tím rozdílem, že vrací řetězec)

#### Nevyhodnocuj/Vyhodnot
Jelikož je Mirage homoikonický lze jakýkoliv jeho výraz konvertovat na reprezentaci přímo v jazyce. Tohoto lze dosáhnout s pomocí makra nevyhodnocuj, které přebírá libovolný výraz a vrací jeho reprezentaci v miragi.
Zde je několik příkladů
```clojure
(nevyhodnocuj 5) ; vrátí číslo 5
(nevyhodnocuj mirage) ; vrátí symbol mirage (ne jeho hodnotu)
(nevyhodnocuj (+ 1 2)) ; vrátí list se symbolem + 1 a 2 ekvivalent (list (nevyhodnocuj +) 1 2)
(nevyhodnocuj (1 2 4 (5 6))) ; ekvivalent (list 1 2 5 (list 5 6))
```
Opakem makra nevyhodnocuj je funkce vyhodnoť, která na základě dané reprezentace vrátí hodnotu.
```clojure
(vyhodnot 5) ; číslo 5
(definuj PI 3.14)
(vyhodnot (nevyhodnocuj PI)) ; 3.14
(vyhodnot (list + 1 2)) ; 3
```

#### Makra
Makra jsou funkce, která nevyhodnocují svoje argumenty ale vyhodnocují svůj výstup. Makra jsou velmi mocná a je na ní založená část [standardní knihovny](https://github.com/Hnatekmar/TPJ/blob/master/project/mirage/makra/makra.mir) Mirage Dobrým příkladem užitečnosti maker je makro defn:
```clojure
(definuj defn (makro (nazev argumenty ...)
	(list definuj nazev
  (spoj (list funkce argumenty) ...))))
```
Makro defn nahrazuje dosud používané spojení 

```clojure
(definuj nazev (funkce () telo))
```  
za
```clojure
(defn nazev () telo)
```
což je čitelnější.
