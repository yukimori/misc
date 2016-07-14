import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

"""
ref:
http://qiita.com/Tatejimaru137/items/3fdcc38cf8247b7056aa

20160708 動作する
"""
fig = plt.figure()
x = np.arange(0, 10, 0.1)

ims = []
for a in range(50):
    y = np.sin(x - a)
    im = plt.plot(x, y, "r")
    ims.append(im)
    
ani = animation.ArtistAnimation(fig, ims)
plt.show()
                
