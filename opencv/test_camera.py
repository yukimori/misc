#coding:utf-8
import cv2
import numpy as np


def readCamera():
    cap = cv2.VideoCapture(0) #Videoを利用する
    cap.grab()
    while(cap.isOpened()):
        ret, frame = cap.read()

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) #Gray colorに変換

        cv2.imshow('frame',gray)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    readCamera()
