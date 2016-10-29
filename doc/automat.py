#!/usr/bin/python3
import sys
from grammar import *

class Automat:
    def __init__(self, grammar):
        self.nonterminals = grammar.nonterminals
        self.sigma = grammar.sigma
        self.rules = grammar.rules
        self.startingSymbol = grammar.startingSymbol
        self.transferTable = {}
        self.generateTransferTable()

    def generateTransferTable(self):
        print("\\subsubsection{Generování automatu}")
        self.nonterminals.append("F")
        print("Stavy automatu \{" + ",".join(["$Q_{" + x + "}$" for x in self.nonterminals]) + "\}")

if __name__ == "__main__":
    files = sys.argv[1:]
    grammars = []
    for f in files:
        with open(f) as fH:
            data = json.load(fH)
            g = Grammar(**data)
            grammars.append(g)
    ng = grammars[0]
    for i in range(1, len(grammars)):
        ng += grammars[i]

    print(str(ng))
    Automat(ng)
