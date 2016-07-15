# -*- coding:utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from moviepy.editor import *
from matplotlib import animation as ani

"""
ref:
http://qiita.com/kenmatsu4/items/c25b2003fb9faf7a783e

20160708 動作未検証
"""

data= np.loadtxt('cars.csv',delimiter=',',skiprows=1)
data[:,1] = map(lambda x: x * 1.61, data[:,1])    # mph から km/h に変換
data[:,2] = map(lambda y: y * 0.3048, data[:,2])  # ft から  m に変換

def animate(nframe):
    plt.clf()        # clear graph canvas
    slope = 0.746606334842 * (float(nframe)/50) *2   # 引数のnframeが変わることによりslopeが変わる
    intercept = - 5.41583710407
    x = np.linspace(0,50,50)
    y = slope * x + intercept
    plt.ylim(-10,80)
    plt.xlim(0,50)
    plt.xlabel("speed(km/h)")
    plt.ylabel("distance(m)")
    plt.scatter(data[:,1],data[:,2])
    # draw errors
    se = 0
    i = 0
    for d in data:
        plt.plot([d[1],d[1]],[d[2],d[1]*slope+intercept],"k")
        se += (y[i] - d[2]) ** 2
        i += 1
    plt.title("Stopping Distances of Cars (slope=%.3f, sum of square errors=%5d)" % (slope, se))
    # based line: y = 0.74x -5
    plt.plot(x,y)


fig = plt.figure(figsize=(10,6))

anim = ani.FuncAnimation(fig, animate, frames=50, blit=True)

anim.save('regression_anim.mp4', fps=13)

clip = VideoFileClip("regression_anim.mp4")
clip.write_gif("regression_anim.gif")
