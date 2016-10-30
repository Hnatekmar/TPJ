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
        print("\subsubsection{Generování automatu}")
        self.nonterminals.append("F")
        print("Stavy automatu \{" + ",".join(["$Q_{" + x + "}$" for x in self.nonterminals]) + "\}")
        self.transferTable["$Q_{\hat{F}}$"] = []
        for rule in self.rules:
            for choice in self.rules[rule]:
                if len(choice) > 2:
                    raise Exception("Gramatika není typu 3 nelze z ní sestrojit automat")

                if not choice[0] in self.sigma:
                    raise Exception("Gramatika není pravě regulární! Pravidlo %s" % choice)

                if len(choice) == 2:
                    try:
                        self.transferTable[("$Q_{%s}$" % rule, choice[0])].append("$Q_{%s}$" % choice[1])
                        self.transferTable[("$Q_{%s}$" % rule, choice[0])] = list(set(self.transferTable[("$Q_{%s}$" % rule, choice[0])]))
                    except:
                        self.transferTable[("$Q_{%s}$" % rule, choice[0])] = ["$Q_{%s}$" % choice[1]]
                else:
                    try:
                        self.transferTable[("$Q_{%s}$" % rule, choice[0])].append("$Q_{\hat{F}}$")
                    except:
                        self.transferTable[("$Q_{%s}$" % rule, choice[0])] = ["$Q_{\hat{F}}$"]

        print("Determinizace automatu")

        print("||" + "|".join(self.sigma) + "|")
        print("|" + "-|" * (len(self.sigma) + 1))
        rules = [rule[0] for rule in self.transferTable]
        for rule in rules:
            print("|%s" % rule, end = "")
            for c in self.sigma:
                try:
                    print("|%s" % self.transferTable[(rule, c)], end = "")
                except:
                    print("|", end = "")
            print("|")

        start = ["$Q_{%s}$" % self.startingSymbol]
        visited = []
        while len(start):
            node = start.pop()
            if node in visited:
                continue
            visited.append(node)
            for c in self.sigma:
                try:
                    if len(self.transferTable[(node, c)]) > 1:
                        print("Nedeterministický stav (%s, %s) = %s" % (node, c, self.transferTable[(node, c)]))
                        state = "".join(self.transferTable[(node, c)])
                        start.append(state)
                        print("Generuji kompozitní stav %s" % state)
                        for sc in self.sigma:
                            newTransition = []
                            for compositeState in self.transferTable[(node, c)]:
                                try:
                                    newTransition = newTransition + self.transferTable[(compositeState, sc)]
                                except:
                                    pass

                            self.transferTable[(state, sc)] = list(set(newTransition))
                        self.transferTable[(node, c)] = state
                        print("Nový stav (%s, %s) = %s" % (node, c, state))

                    else:
                        start.append(self.transferTable[(node, c)][0])
                except:
                    pass

        print("||" + "|".join(self.sigma) + "|")
        print("|" + "-|" * (len(self.sigma) + 1))
        rules = [rule[0] for rule in self.transferTable]
        for rule in rules:
            print("|%s" % rule, end = "")
            for c in self.sigma:
                try:
                    print("|%s" % self.transferTable[(rule, c)], end = "")
                except:
                    print("|", end = "")
            print("|")

if __name__ == "__main__":
    files = sys.argv[1:]
    grammars = []
    for f in files:
        with open(f) as fH:
            data = json.load(fH)
            g = Grammar(**data)
            grammars.append(g)
    ng = grammars[0]
    Automat(ng)
