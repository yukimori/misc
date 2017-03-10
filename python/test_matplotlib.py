# -*- coding:utf-8 -*-

import matplotlib.pyplot as plt

def change_color_each_point():
    """
    データごとに色を変える
    """

    print("change color each point")
    
    list_x = [0, 1, 2, 3]
    list_y = [0, 1, 2, 3]
    colors = ['red', 'green', 'red', 'green']
    plt.scatter(list_x, list_y, c=colors)
    plt.show()

if __name__ == '__main__':
    change_color_each_point()
    
