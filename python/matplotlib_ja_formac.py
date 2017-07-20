# -*- coding: utf-8 -*-
"""
Mac OSXのmatplotlibで日本語フォント(Osaka)を使うサンプル
python2.7(anaconda-2.1.0)
cf. http://matplotlib.org/users/customizing.html
"""
# デフォルトの文字コードを変更する．
import sys
# reload(sys)
sys.setdefaultencoding('utf-8')
# import
import matplotlib.pyplot as plt
import matplotlib.font_manager
from matplotlib.font_manager import FontProperties
from matplotlib.backends.backend_pdf import PdfPages

# for Mac
font_path = '/Library/Fonts/Osaka.ttf'

font_prop = matplotlib.font_manager.FontProperties(fname=font_path)
matplotlib.rcParams['font.family'] = font_prop.get_name()
# pdfのフォントをTrueTypeに変更
matplotlib.rcParams['pdf.fonttype'] = 42
# defaultのdpi=100から変更
matplotlib.rcParams['savefig.dpi'] = 300
# 数式（Latex)のフォントを変更
matplotlib.rcParams['mathtext.default'] = 'regular'

pdf = PdfPages("test.pdf")

plt.figure()
plt.plot(range(10))
plt.title(u'日本語のテスト')
plt.xlabel(u'Latexのテスト' + r'  $y=a x^{2} \alpha \beta $')
plt.ylabel(u'y軸 (m)')

plt.savefig('test.png')
pdf.savefig()
pdf.close()
