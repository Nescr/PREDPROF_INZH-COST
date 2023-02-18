import cv2
import numpy as np

def empty(a):
    pass


# blue_sticker = np.array([[92, 112, 103], [109, 174, 181]])
# green_sticker = np.array([[38, 52, 145], [57, 140, 190]])
# yellow_sticker = np.array([[24, 34, 86], [147, 197, 255]])
# pink_sticker = np.array([[163, 173, 114], [255, 214, 255]])
# orange_sticker = np.array([[0, 10, 101], [140, 168, 255]])




path = 'Python\images\colors.jpg'

cv2.namedWindow("TrackBars")
cv2.resizeWindow("TrackBars", 640, 240)
cv2.createTrackbar("Hue Min", "TrackBars", 0, 179, empty)
cv2.createTrackbar("Hue Max", "TrackBars", 179, 179, empty)
cv2.createTrackbar("Sat Min", "TrackBars", 0, 255, empty)
cv2.createTrackbar("Sat Max", "TrackBars", 255, 255, empty)
cv2.createTrackbar("Val Min", "TrackBars", 0, 255, empty)
cv2.createTrackbar("Val Max", "TrackBars", 255, 255, empty)

cap = cv2.VideoCapture(0)
cap.set(10, 10)
while True:
    _, img = cap.read()
    img = cv2.flip(img, 1)

    #img = cv2.imread(path)
    imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    h_min = cv2.getTrackbarPos("Hue Min", "TrackBars")
    h_max = cv2.getTrackbarPos("Hue Max", "TrackBars")
    s_min = cv2.getTrackbarPos("Sat Min", "TrackBars")
    s_max = cv2.getTrackbarPos("Sat Max", "TrackBars")
    v_min = cv2.getTrackbarPos("Val Min", "TrackBars")
    v_max = cv2.getTrackbarPos("Val Max", "TrackBars")

    lower = np.array([h_min, s_min, v_min])
    upper = np.array([h_max, s_max, v_max])
    mask = cv2.inRange(imgHSV, lower, upper)
    imgMask = cv2.bitwise_and(img, img, mask=mask)

    

    cv2.imshow("Result", imgMask)

    print(h_min, s_min, v_min, h_max, s_max, v_max)


    if cv2.waitKey(10) == ord('q'):
        break
cv2.destroyAllWindows()
