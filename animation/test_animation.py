# -*- coding:utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import animation as ani
plt.style.use('ggplot')

"""
ref:
http://qiita.com/kenmatsu4/items/573ca0733b192d919d0e

blitを削除したら動作するようになった
"""
num_frame = 80.
x_range= 7

def gen():
    x = 0
    while x < 50:
        yield x
        x += 1

def animate(nframe):
    global num_frame
    plt.clf()
    print "nframe:",nframe
    a = ((5*nframe/num_frame) -.5) * np.pi
    x = np.linspace(-x_range, x_range, 200)
    y = np.sin(x+a)
    plt.xlim(-x_range, x_range)
    plt.ylim(-1.1,1.1)
    plt.plot(x, y, c="b")

fig = plt.figure(figsize=(12,5))
anim = ani.FuncAnimation(fig, animate, frames=int(num_frame))
anim.save('anim_test.gif', writer='imagemagick', fps=5, dpi=64)
#anim.save('anim_test.gif')
