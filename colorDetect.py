import cv2
import numpy as np

blur = (3, 3)
thresh = 20
                                               

colorDict = {
    'red' : np.array([[0, 141, 84], [10, 230, 255]]),
    'yellow' : np.array([[22, 133, 170], [30, 214, 255]]),
    'blue' : np.array([[100, 91, 55], [127, 231, 196]]),

    # 'blue_sticker' : np.array([[92, 112, 103], [109, 174, 181]]),
    # 'green_sticker' : np.array([[38, 52, 145], [57, 140, 190]]),
    # 'yellow_sticker' : np.array([[18, 64, 200], [34, 144, 255]]),
    # 'pink_sticker' : np.array([[147, 150, 174], [179, 187, 255]]),
    # 'orange_sticker' : np.array([[0, 95, 239], [10, 145, 255]]),
}
outputColors = []


#path = 'images\colors.jpg'                                 # путь к фото/видео

cap = cv2.VideoCapture(0)                                   # видео с камеры
                                                            # (при желании можно указать путь к видео при помощи переменной path)

#cap.set(10, 1)                                             # настройка яркости видео, если поддерживается камерой(число вместо 0)


while True:
                                                            # Работа с видео:
    success, img = cap.read()                               # захват кадра

    if not success:                                         # проверка наkичия видео
        print('No video(')              
        break                           
    img = cv2.flip(img, 1)                                  # отзеркаливание изображение по оси Y (удобно для фронтальной камеры)


                                                            # Работа с фото:
    # img = cv2.imread(path)                                  # считывание изображение




    imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)           # перевод изображения в формат Hue, Saturation, Value (оттенок, насыщенность, яркость)

    for color in colorDict:

        checkingColor = colorDict[color]
        
        h_min = checkingColor[0][0]
        h_max = checkingColor[1][0]
        s_min = checkingColor[0][1]
        s_max = checkingColor[1][1]
        v_min = checkingColor[0][2]
        v_max = checkingColor[1][2]

        lower = np.array([h_min, s_min, v_min])             # нижняя граница для фильтра
        upper = np.array([h_max, s_max, v_max])             # верхняя граница для фильтра

        mask = cv2.inRange(imgHSV, lower, upper)            # создание фильтра
        imgMask = cv2.bitwise_and(img, img, mask=mask)      # наложение фильтра

        cv2.imshow("Result", imgMask)                       # вывод видео 
        cv2.waitKey(50)                    

        gray_image = cv2.cvtColor(imgMask, cv2.COLOR_BGR2GRAY)                                      # ч/б формат
        blurred = cv2.GaussianBlur(gray_image, blur, 0)                                             # размытие 
        _, thresh_img = cv2.threshold(blurred, thresh, 255, cv2.THRESH_BINARY)                      # двоичный ч/б формат
        contours, _ = cv2.findContours(thresh_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)      # поиск контуров 
        #                                   🠕                 🠕                      🠕
        #                             (изображение, только внешние контуры, простая аппроксимация(упрощение сложных контуров))

        for cnt in contours:
            if cv2.contourArea(cnt) > 400:                  # проверка размеров найденного контура
                outputColors.append(color)                  # добавление название цвета в список вывода
                break

        

    print(*outputColors)                                    # вывод найденных цветов
    outputColors.clear()                                    # очистка 
    
    if cv2.waitKey(1) == ord('q'):                          # проверка нажатия на клавишу выхода
        break                                               # выход из цикла

cv2.destroyAllWindows()
cap.release()
