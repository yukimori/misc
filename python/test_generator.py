# -*- coding:utf-8 -*-

import unittest

"""
 データサイズが大きい内包表記にはジェネレータ式を考える
"""
class TestGeneratorFunctions(unittest.TestCase):

    def setUp(self):
        self.data = [1, 5, 10, 15, 20, 25, 30, 35]
        print "data:", self.data


    def test_listcomprehenstion(self):
        # リスト内包表記
        value = [x for x in self.data]
        expected = self.data
        self.assertEqual(expected, value)

    def test_generator(self):
        # ジェネレータ式は()で囲む
        it = (x for x in self.data)

        # 組み込み関数nextでジェネレータ式から次の出力を生成することができる
        actual = next(it)
        self.assertEqual(1, actual)
        print actual
        actual = next(it)
        self.assertEqual(5, actual)


    def test_complex_generator(self):
        it = (x for x in self.data)

        # 別のジェネレータ式から返されたイテレータを別のジェネレータ式への入力にできる
        roots = ((x, x**0.5) for x in it)
        print (next(roots))
        print (next(roots))
        self.assertEqual((10, 10**0.5), next(roots))
        self.assertEqual((15, 15**0.5), next(roots))

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestGeneratorFunctions)
    unittest.TextTestRunner(verbosity=2).run(suite)
#    unittest.main()

