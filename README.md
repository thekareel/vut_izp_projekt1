# Projekt 1 - Práce s textem

Analýza a kontrola hesel na vstupu zda splňují požadovaná bezpečnostní kritéria.

Program se spouští v následující podobě:
```sh
./pwcheck LEVEL PARAM [--stats]
```

**LEVEL** celé číslo v intervalu [1,4], které určuje požadovanou úroveň bezpečnostni
**PARAM** kladné celé číslo, které určuje dodatečný parametr pravidel
**--stats** pokud jse zadaná, určuje, zda se na konci programu mají vypsat souhrné statistika analyzovaných hesel

## Seznam pravidel
1. Heslo obsahuje alespoň 1 velké a 1 malé písmeno.
2. Heslo obsahuje znaky z alespoň X skupiny. Uvažované skupiny jsou:
  - malá písmena (a-z)
  - velká písmena (A-Z)
  - čísla (0-9)
  - speciální znaky
3. Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
4. Heslo neobsahuje sva stejné podřetězce délky alespoň X.

## Příklad spuštění
```sh
./pwcheck 1 1 < hesla.txt
```
