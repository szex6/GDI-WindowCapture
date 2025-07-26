import gdi
import numpy as np
import cv2 as cv
from time import time

pt = time()
fps, max, min = 0, 0, 100000
avg, count, amount = 0, 0, 0

window = gdi.GDI("File Explorer")

for i in range(6000):
    
    img = window.capture()
    #print(window.rect())

    if img is not None:
        cv.imshow("ss", img)

    fps = 1 / (time() - pt)

    if (fps > max):
        max = fps
    
    if (fps < min):
        min = fps

    count += 1
    amount += fps
    avg = amount / count

    print(f"#FPS: {fps:.1f}\tMIN: {min:.1f}\tMAX: {max:.1f}\tAVG: {avg:.1f}")
    pt = time()

    cv.waitKey(1)
cv.destroyAllWindows()