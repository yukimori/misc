#!/usr/bin/env python
# -*- coding: utf-8 -*-

from itertools import combinations, product
from collections import namedtuple
# from __future__ import 

"""
http://qiita.com/Tsutomu-KKE@github/items/5ae93e735265eb925b52
20160421 python3でないと動かない
"""

Union = namedtuple('Union', 'l r') # 和
Produ = namedtuple('Produ', 'l r') # 積
Combi = namedtuple('Combi', 'e') # 組
class Edge:
    def __init__(self, u, v, e):
        self.u = u
        self.v = v
        self.e = e
    def __repr__(self):
        return '<%s %s %s>'%(self.u, self.v, self.e)

class Graph:
    def __init__(self, num_nodes, edges):
        self.nodes = [[] for _ in range(num_nodes)]
        self.edges = []
        for i, (u, v) in enumerate(edges):
            self.edges.append(Edge(u, v, chr(97 + i)))
            self.nodes[u].append(i)
            self.nodes[v].append(i)
    def __repr__(self):
        return str(self.edges)
    def spanning_tree(self):
        res = Graph._reduct(self.nodes.copy(), self.edges.copy())
        return sorted(Graph._expand(res))
    @staticmethod
    def _reduct(nodes, edges):
        if not edges:
            return '' if len(nodes) == 1 else None
        for i, e in enumerate(edges): # 自己ループ
            if e.u == e.v:
                Graph._erase(nodes, edges, i)
                return Produ(l=Combi(e=e.e), r=Graph._reduct(nodes, edges))
        for con in nodes: # 次数=1
            if len(con) == 1:
                e = edges[con[0]]
                Graph._erase(nodes, edges, con[0])
                return Produ(l=e.e, r=Graph._reduct(nodes, edges))
        for con in nodes: # 次数=2
            if len(con) == 2:
                e = edges[con[0]]
                edges[con[0]] = Edge(e.u, e.v, Produ(l=edges[con[0]].e,
                                                     r=edges[con[1]].e))
                Graph._shrink(nodes, edges, con[1])
                return Graph._reduct(nodes, edges)
        e = edges[0]
        nodes2, edges2 = nodes.copy(), edges.copy()
        Graph._erase(nodes, edges, 0)
        Graph._shrink(nodes2, edges2, 0)
        return Union(l=Produ(l=Combi(e=e.e), r=Graph._reduct(nodes, edges)),
                     r=Produ(l=e.e, r=Graph._reduct(nodes2, edges2)))
    @staticmethod
    def _erase(nodes, edges, k):
        for a, con in enumerate(nodes):
            nodes[a] = [b if b < k else b-1 for b in con if b != k]
        del edges[k]
    @staticmethod
    def _shrink(nodes, edges, k):
        e = edges[k]
        dn = max(e.u, e.v)
        sn = e.u+e.v-dn
        nodes[sn] = nodes[sn] + nodes[dn]
        for a, con in enumerate(nodes):
            nodes[a] = [b if b < k else b-1 for b in con if b != k]
        for a, ed in enumerate(edges):
            u = sn if ed.u == dn else ed.u if ed.u < dn else ed.u-1
            v = sn if ed.v == dn else ed.v if ed.v < dn else ed.v-1
            edges[a] = Edge(u, v, ed.e)
        del edges[k]
        del nodes[dn]
    @staticmethod
    def _expand(ex):
        if ex is None:
            return set()
        elif isinstance(ex, str):
            return set(ex) if ex else {''}
        elif isinstance(ex, Combi):
            exe = Graph._expand(ex.e)
            return set.union(*(set(''.join(s) for s in
                combinations(e, len(e)-1)) for e in exe))
        exl = Graph._expand(ex.l)
        exr = Graph._expand(ex.r)
        if isinstance(ex, Union):
            return exl.union(exr)
        return {''.join(sorted((i+j))) for i, j in product(exl, exr)}

if __name__ == "__main__":
    g = Graph(3, [(0,1), (1,2), (2,0)])
    print g.spanning_tree()

    g = Graph(4, [(0,1), (1,2), (2,3), (3,0), (0,2), (1,3)])
    print(g.spanning_tree())
