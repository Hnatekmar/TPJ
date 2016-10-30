#!/usr/bin/python3

import json, sys

from automat import *

class Grammar:
    def __init__(self, nonterminals, sigma, rules, startingSymbol, name):
        self.nonterminals = nonterminals
        self.sigma = sigma
        self.rules = rules
        self.startingSymbol = startingSymbol
        self.name = name

    def __add__(self, g):
        nonterminals = [x + self.name for x in self.nonterminals[:]] +[x + g.name for x in g.nonterminals[:]]
        sigma = set(self.sigma).union(set(g.sigma))
        rules = {}
        for k,v in self.getRenamedRules().items():
            rules[k] = v

        for k,v in g.getRenamedRules().items():
            rules[k] = v
        
        rules["S"] = [self.startingSymbol + "_\{%s\}" % self.name, g.startingSymbol + "_\{%s\}" % g.startingSymbol]
        return Grammar(nonterminals, sigma, rules, "S", self.name + g.name)


    def getRenamedRules(self):
        rules = {}
        for nonterminal in self.nonterminals:
            for rule in self.rules:
                choices = []
                for n2 in self.nonterminals:
                    choices.append([x if x != n2 else x + "_%s" % self.name for x in rule])
                rules[nonterminal + "_%s" % self.name] = choices
        return rules

    def getHeader(self):
        header = "$L_\{%s\}$(" % self.name + str(self.nonterminals) + ", " + str(self.sigma) + ", "
        header += "\{\n"
        for nonterminal in self.nonterminals:
            try:
                header += "$$" + nonterminal + " \\rightarrow " + "|".join(["".join(rewrite) for rewrite in self.rules[nonterminal]])  + "$$"
            except:
                pass

        header += "\},\n"
        header += self.startingSymbol + ")\n"
        return header

    def removeSimpleRules(self):
        pass

    def getUsefulVars(self):
        tau = set(self.startingSymbol)
        text = ""
        i = 0
        """
        Nalezni všechny neterminály ze kterých se na neterminál dostanu
        """
        while True:
            text += ("$$D_%s = \{" % i) + ",".join(sorted(tau)) + "\}$$"
            tau_new = set()
            for nonterminal in [n for n in tau if n in self.nonterminals]:
                for rule in self.rules[nonterminal]:
                    for torn in rule:
                        if not torn in tau:
                            tau_new.add(torn)

            tau = tau.union(tau_new)
            if len(tau_new) == 0:
                self.sigma = [s for s in self.sigma if s in tau]

                self.nonterminals = [n for n in self.nonterminals if n in tau]
                r = {n : self.rules[n] for n in self.nonterminals}
                self.rules = r
                return text

            i += 1


    def getReachableVars(self):
        tau = set(self.sigma)
        tau_new = set()
        text = ""
        i = 0
        """
        Najdi všechny neterminály, které odkazují na terminály
        """
        while True:
            text += ("$$\\uptau_%s = \{" % i) + ",".join(sorted(tau)) + "\}$$"
            tau_new = set()
            for t in tau:
                for nonterminal in self.rules:
                    for rule in self.rules[nonterminal]:
                        if t in rule:
                            if not nonterminal in tau:
                                tau_new.add(nonterminal)
            i += 1
            if len(tau_new) == 0:
                """
                Změna gramatiky
                """
                self.sigma = [s for s in self.sigma if s in tau]
                self.nonterminals = [n for n in self.nonterminals if n in tau]
                r = {n : self.rules[n] for n in self.nonterminals}
                self.rules = r
                return text

            tau = tau.union(tau_new)

    def __str__(self):
        header = self.getHeader()
        header += "\n\subsubsection{Nalezení symbolů, které nejsou zbytečné}"
        validSymbols = self.getReachableVars()
        description = "\subsubsection{Hledání dostupných symbolů}" + self.getUsefulVars()
        description += "\subsubsection{Upravená gramatika}\nPo úpravách dostaváme gramatiku\n"
        header2 = self.getHeader()
        return header + validSymbols + description + header2

if __name__ == '__main__':
    with open(sys.argv[1]) as f:
        data = json.load(f)
        g = Grammar(**data)
    print(str(g))
    Automat(g)
