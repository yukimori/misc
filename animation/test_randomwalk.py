# -*- coding:utf-8 -*-
from matplotlib import pyplot as plt
from matplotlib import animation as animation
import numpy as np
import random

def gen():
    x, y = 0, 0
    cnt = 0
    while cnt < 101:
        yield x, y
        x += 1
        if random.random() < 0.5:
            y += 1
        else:
            y += -1
        cnt += 1

fig = plt.figure()
def func():
    ax = fig.add_subplot(111)
    line, = ax.plot([], [], lw=2)
    ax.grid()
    xdata, ydata = [], []
    ax.set_ylim(-1, 1)
    ax.set_xlim(0, 25)
    def f(data):
        x, y = data
        xdata.append(x)
        ydata.append(y)
        # グラフがはみ出そうになったら上（下）限値をセットし直す
        xmin, xmax = ax.get_xlim()
        ymin, ymax = ax.get_ylim()
        if x >= xmax:
            ax.set_xlim(xmin, 2*xmax)
            ax.figure.canvas.draw()
        if y >= ymax:
            ax.set_ylim(ymin, 2*ymax)
            ax.figure.canvas.draw()
        if ymin >= y:
            ax.set_ylim(2*ymin, ymax)
            ax.figure.canvas.draw()
        line.set_data(xdata, ydata)
        return line,
    return f

ani = animation.FuncAnimation(fig,
        func(), gen, blit=True, interval=5, repeat=False)

ani.save("random_walk.mp4")
plt.show()
