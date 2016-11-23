# -*- coding:utf-8 -*-

import cv2

img = cv2.imread('image.png')
cv2.imshow('python', img)
# command-qで終了できる
cv2.waitKey(0)
