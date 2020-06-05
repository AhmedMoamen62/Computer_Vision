import cv2
import numpy as np
def click_event(event,x,y,flags,param):
    if event == cv2.EVENT_RBUTTONDOWN:
        font = cv2.FONT_HERSHEY_SIMPLEX
        strXY = str(x) + ', ' + str(y)
        cv2.putText(img,strXY,(x,y),font,0.5,(255,255,0),2)
        cv2.imshow('image',img)
    elif event == cv2.EVENT_LBUTTONDOWN:
        blue = img[y,x,0]
        green = img[y,x,1]
        red = img[y,x,2]
        font = cv2.FONT_HERSHEY_SIMPLEX
        strBGR = str(red) + ', ' + str(green) + ', ' + str(blue)
        cv2.putText(img, strBGR, (x, y), font, 0.5, (255, 255, 255), 2)
        cv2.imshow('image', img)

#img = np.zeros((512,512,3),np.uint8)
img = cv2.imread('editable_dog.jpg',1)
cv2.imshow('image',img)
cv2.setMouseCallback('image',click_event)
cv2.waitKey(0)
cv2.destroyAllWindows()


# import cv2
# import numpy as np

# def detectImage(img):
#     v = np.median(img)
#     lower = int(max(0, (1.0 - 0.33) * v))
#     upper = int(min(255, (1.0 + 0.33) * v))
#     edges = cv2.Canny(img, lower, upper)
#     cv2.namedWindow('edges', cv2.WINDOW_FREERATIO)
#     cv2.imshow('edges', edges)
#     kernel = np.ones((3,3),np.uint8)
#     dilate = cv2.dilate(edges,kernel,iterations=4)
#     cv2.namedWindow('dilate', cv2.WINDOW_FREERATIO)
#     cv2.imshow('dilate', dilate)
#     contours,hierarchy = cv2.findContours(dilate,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
#     approx_shapes = []
#     for contour in contours:
#         approx = cv2.approxPolyDP(contour,0.04*cv2.arcLength(contour,True),True)
#         approx_shapes.append(approx)
#     imagesNumber = 0
#     imageParameter = []
#     n = 0
#     image_approx = []
#     while n < len(approx_shapes):
#         if(len(approx_shapes[n]) == 4):
#             triangleNumber = 0
#             for i in range(len(approx_shapes)):
#                 if(hierarchy[0][i][3] == n and len(approx_shapes[i]) == 3):
#                     triangleNumber += 1
#             if(triangleNumber == 4):
#                 width = abs(approx_shapes[n].ravel()[4] - approx_shapes[n].ravel()[0])
#                 height = abs(approx_shapes[n].ravel()[5] - approx_shapes[n].ravel()[1])
#                 centerx = (approx_shapes[n].ravel()[0] + approx_shapes[n].ravel()[4])/2
#                 centery = (approx_shapes[n].ravel()[1] + approx_shapes[n].ravel()[5])/2
#                 imageParameter.append({'CenterX' : centerx,'CenterY' : centery,'Width' : width,'Height' : height})
#                 imagesNumber += 1
#                 image_approx.append(approx_shapes[n])
#                 cv2.drawContours(img, [approx_shapes[n]], 0, (0, 0, 255), 2)
#                 cv2.putText(img, "Image", (int(centerx), int(centery - height/2 - 10)), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 0, 0))
#             n += 1
#         else:
#             n += 1
#     cv2.namedWindow('image', cv2.WINDOW_NORMAL)
#     cv2.imshow('image', img)
#     return  image_approx

# img = cv2.imread('testcase.jpeg')
# imageList = detectImage(img)
# print(imageList)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# img = cv2.imread('shapes.jpg')
# img_gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
# _, thresh = cv2.threshold(img_gray,240,255,cv2.THRESH_BINARY_INV)
# img_copy = thresh.copy()
# contours, _ = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
# for contour in contours:
#     approx = cv2.approxPolyDP(contour,0.01*cv2.arcLength(contour,True),True)
#     cv2.drawContours(img,[approx],0,(255,0,0),2)
#     x = approx.ravel()[0]
#     y = approx.ravel()[1] - 5
#     if len(approx) == 2:
#         cv2.putText(img,"Line",(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,0,0))
#     elif len(approx) == 3:
#         cv2.putText(img,"Triangle",(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,0,0))
#     elif len(approx) == 4:
#         x , y , w, h = cv2.boundingRect(approx)
#         aspectRatio = float(w)/h
#         if aspectRatio >= 0.95 and aspectRatio <= 1.05:
#             cv2.putText(img,"Square",(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,0,0))
#         else:
#             cv2.putText(img, "Rectangle", (x, y), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 0))
#     elif len(approx) == 5:
#         cv2.putText(img,"Pentagon",(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,0,0))
#     elif len(approx) == 10:
#         cv2.putText(img,"Star",(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,0,0))
#     else:
#         cv2.putText(img,"Circle",(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,0,0))
# cv2.imshow('shapes',img)
# cv2.imshow('shapes_gray',img_copy)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# img = cv2.imread('imageBox.png')
# img_gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
# ret, thresh = cv2.threshold(img_gray,127,255,0)
# contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
# cv2.drawContours(img,contours,-1,(255,0,255),1)
# cv2.imshow('image',img)
# cv2.imshow('img_gray',img_gray)
# cv2.waitKey(0)
# cv2.destroyAllWindows()

# import cv2
# import numpy as np
# apple = cv2.imread('apple.png')
# orange = cv2.imread('orange.jpg')
# apple_orange = np.hstack((apple[:, :256], orange[:, 256:]))
# # Gaussian pyramid for apple
# apple_copy = apple.copy()
# gp_apple = [apple_copy]
# for i in range(6):
#     apple_copy = cv2.pyrDown(apple_copy)
#     gp_apple.append(apple_copy)
# # Gaussian pyramid for orange
# orange_copy = orange.copy()
# gp_orange = [orange_copy]
# for i in range(6):
#     orange_copy = cv2.pyrDown(orange_copy)
#     gp_orange.append(orange_copy)
# # Laplacian pyramid for apple
# apple_copy = gp_apple[5]
# lp_apple = [apple_copy]
# for i in range(5,0,-1):
#     gaussian_extended = cv2.pyrUp(gp_apple[i])
#     laplacian = cv2.subtract(gp_apple[i-1],gaussian_extended)
#     lp_apple.append(laplacian)
# # Laplacian pyramid for orange
# orange_copy = gp_orange[5]
# lp_orange = [orange_copy]
# for i in range(5,0,-1):
#     gaussian_extended = cv2.pyrUp(gp_orange[i])
#     laplacian = cv2.subtract(gp_orange[i-1],gaussian_extended)
#     lp_orange.append(laplacian)
#
# apple_orange_pyramid = []
# for apple_lap, orange_lap in zip(lp_apple,lp_orange):
#     cols= apple_lap.shape[1]
#     laplacian = np.hstack((apple_lap[:, 0:int(cols/2)],orange_lap[:, int(cols/2):]))
#     apple_orange_pyramid.append(laplacian)
# apple_orange_reconstruct = apple_orange_pyramid[0]
# for i in range(1,6):
#     apple_orange_reconstruct = cv2.pyrUp(apple_orange_reconstruct)
#     apple_orange_reconstruct = cv2.add(apple_orange_pyramid[i],apple_orange_reconstruct)
# cv2.imshow('apple',lp_apple[5])
# cv2.imshow('orange',lp_orange[5])
# cv2.imshow('apple_orange',apple_orange_pyramid[5])
# cv2.imshow('apple_orange_reconstruct',apple_orange_reconstruct)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# img = cv2.imread('lena.png')
# layer = img.copy()
# gp = [layer]
# for i in range(6):
#     layer = cv2.pyrDown(layer)
#     gp.append(layer)
#     cv2.imshow(str(i+1),layer)
# layer = gp[len(gp)-1]
# cv2.imshow('upper level Gaussian Pyramid',layer)
# lp = [layer]
# for i in range(5,0,-1):
#     gaussian_extended = cv2.pyrUp(gp[i])
#     laplacian = cv2.subtract(gp[i-1],gaussian_extended)
#     cv2.imshow(str(i+1),laplacian)
# cv2.imshow('original image',img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# img = cv2.imread('lena.png')
# layer = img.copy()
# gp = [layer]
# for i in range(6):
#     layer = cv2.pyrDown(layer)
#     gp.append(layer)
#     cv2.imshow(str(i+1),layer)
# cv2.imshow('original image',img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()

# import cv2
# import numpy as np
# from matplotlib import pyplot as plt
# img = cv2.imread('messi.jpg',cv2.IMREAD_GRAYSCALE)
# canny = cv2.Canny(img,100,200)
# titles = ['image','Canny']
# images = [img,canny]
# for i in range(len(images)):
#     plt.subplot(1,2,i+1)
#     plt.imshow(images[i],'gray')
#     plt.title(titles[i])
#     plt.xticks([]),plt.yticks([])
# plt.show()


# import cv2
# import numpy as np
# from matplotlib import pyplot as plt
# img = cv2.imread('sudoku.jpg',cv2.IMREAD_GRAYSCALE)
# lap = cv2.Laplacian(img,cv2.CV_64F,ksize=3)
# lap = np.uint8(np.absolute(lap))
# sobelX = cv2.Sobel(img,cv2.CV_64F,1,0)
# sobelY = cv2.Sobel(img,cv2.CV_64F,0,1)
# sobelX = np.uint8(np.absolute(sobelX))
# sobelY = np.uint8(np.absolute(sobelY))
# sobel = cv2.bitwise_or(sobelY,sobelX)
# titles = ['image','Lap','SobelX','SovelY','Sobel']
# images = [img,lap,sobelX,sobelY,sobel]
# for i in range(len(images)):
#     plt.subplot(2,3,i+1)
#     plt.imshow(images[i],'gray')
#     plt.title(titles[i])
#     plt.xticks([]),plt.yticks([])
# plt.show()


# import cv2
# import numpy as np
# from matplotlib import pyplot as plt
# img = cv2.imread('monaliza.jpg')
# img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
# kernel = np.ones((5,5),np.float32)/25
# dst = cv2.filter2D(img,-1,kernel)
# blur = cv2.blur(img,(5,5))
# gblur = cv2.GaussianBlur(img,(5,5),0)
# median = cv2.medianBlur(img,5,)
# bF = cv2.bilateralFilter(img,9,75,75)
# titles = ['image','2D Convolution','BLur','GaussianBlur','Median','bilateralFilter']
# images = [img,dst,blur,gblur,median,bF]
# for i in range(len(images)):
#     plt.subplot(2,3,i+1)
#     plt.imshow(images[i],'gray')
#     plt.title(titles[i])
#     plt.xticks([]),plt.yticks([])
# plt.show()



# import cv2
# import numpy as np
# from matplotlib import pyplot as plt
# img = cv2.imread('smarties.png', 0)
# _, mask = cv2.threshold(img,220,255,cv2.THRESH_BINARY_INV)
# kernel = np.ones((2,2),np.uint8)
# erosion = cv2.erode(mask,kernel,iterations=2)
# dilation = cv2.dilate(mask,kernel,iterations=2)
# opening = cv2.morphologyEx(mask,cv2.MORPH_OPEN,kernel) # dilation then erosion
# closing = cv2.morphologyEx(mask,cv2.MORPH_CLOSE,kernel) # erosion then dilation
# mg = cv2.morphologyEx(mask,cv2.MORPH_GRADIENT,kernel) # difference between erosion and dilation
# th = cv2.morphologyEx(mask,cv2.MORPH_TOPHAT,kernel)   # difference between opening and image
# titles = ['image','Mask','Dilation','Erosion','Opening','Closing','Morph Gradient','TopHat']
# images = [img,mask,dilation,erosion,opening,closing,mg,th]
# for i in range(len(images)):
#     plt.subplot(2,4,i+1)
#     plt.imshow(images[i],'gray')
#     plt.title(titles[i])
# plt.show()


# import cv2
# from matplotlib import pyplot as plt
# img = cv2.imread('gradient.png', 0)
# _, th1 = cv2.threshold(img,50,255,cv2.THRESH_BINARY)
# _, th2 = cv2.threshold(img,200,255,cv2.THRESH_BINARY_INV)
# _, th3 = cv2.threshold(img,100,255,cv2.THRESH_TRUNC)
# _, th4 = cv2.threshold(img,100,255,cv2.THRESH_TOZERO)
# _, th5 = cv2.threshold(img,200,230,cv2.THRESH_TOZERO_INV)
# titles = ['Original','Binary','Binary Inverse','Trunc','Zero','Zero Inverse']
# images = [img,th1,th2,th3,th4,th5]
# for i in range(len(images)):
#     plt.subplot(2,3,i+1)
#     plt.imshow(images[i],'gray')
#     plt.title(titles[i])
# plt.show()



# import cv2
# from matplotlib import pyplot as plt
# img = cv2.imread('monaliza.jpg', 1)
# cv2.imshow('image',img)
# img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
# #plt.xticks([]) , plt.yticks([])
# plt.imshow(img)
# plt.show()
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# img = cv2.imread('sudoku.jpg', 0)
# _, th1 = cv2.threshold(img,127,255,cv2.THRESH_BINARY)
# th2 = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)
# th3 = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,9,2)
# cv2.imshow('image',img)
# cv2.imshow('th1',th1)
# cv2.imshow('th2',th2)
# cv2.imshow('th3',th3)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# img = cv2.imread('gradient.png', 0)
# _, th1 = cv2.threshold(img,50,255,cv2.THRESH_BINARY)
# _, th2 = cv2.threshold(img,200,255,cv2.THRESH_BINARY_INV)
# _, th3 = cv2.threshold(img,100,255,cv2.THRESH_TRUNC) # to set the value after the threshold level is the same
# _, th4 = cv2.threshold(img,100,255,cv2.THRESH_TOZERO)
# cv2.imshow('image',img)
# cv2.imshow('th1',th1)
# cv2.imshow('th2',th2)
# cv2.imshow('th3',th3)
# cv2.imshow('th4',th4)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# def nothing(x):
#     pass
# cv2.namedWindow('Tracking')
# cv2.createTrackbar('LH','Tracking',0,255,nothing)
# cv2.createTrackbar('LS','Tracking',0,255,nothing)
# cv2.createTrackbar('LV','Tracking',0,255,nothing)
# cv2.createTrackbar('UH','Tracking',0,255,nothing)
# cv2.createTrackbar('US','Tracking',0,255,nothing)
# cv2.createTrackbar('UV','Tracking',0,255,nothing)
# while(1):
#     frame = cv2.imread('smarties.png', cv2.IMREAD_UNCHANGED)
#     hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
#     l_h = cv2.getTrackbarPos('LH','Tracking')
#     l_s = cv2.getTrackbarPos('LS', 'Tracking')
#     l_v = cv2.getTrackbarPos('LV', 'Tracking')
#     u_h = cv2.getTrackbarPos('UH', 'Tracking')
#     u_s = cv2.getTrackbarPos('US', 'Tracking')
#     u_v = cv2.getTrackbarPos('UV', 'Tracking')
#     l_b = np.array([l_h,l_s,l_v])
#     u_b = np.array([u_h,u_s,u_v])
#     mask = cv2.inRange(hsv,l_b,u_b)
#     res = cv2.bitwise_and(frame,frame,mask = mask)
#     cv2.imshow('frame', frame)
#     cv2.imshow('Mask', mask)
#     cv2.imshow('result',res)
#     if cv2.waitKey(1) & 0xFF == 27:
#         break
# cv2.destroyAllWindows()


# import cv2
# import numpy as np
# def blue(x):
#     img[0:300,0:512,0] = x
# def green(x):
#     img[0:300,0:512,1] = x
# def red(x):
#     img[0:300,0:512,2] = x
# img = np.zeros((300,512,3),np.uint8)
# cv2.namedWindow('image')
# cv2.createTrackbar('B','image',0,255,blue)
# cv2.createTrackbar('G','image',0,255,green)
# cv2.createTrackbar('R','image',0,255,red)
# while(1):
#     cv2.imshow('image',img)
#     print(cv2.getTrackbarPos('B','image'))
#     if cv2.waitKey(1) & 0xFF == 27:
#         break
# cv2.destroyAllWindows()

# import cv2
# import numpy as np
# bw = cv2.imread('bw.png')
# print(bw.shape[0])
# print(bw.shape[1])
# print(bw.shape[2])
# img = np.zeros((bw.shape[0],bw.shape[1],bw.shape[2]),np.uint8)
# cv2.rectangle(img,(200,0),(300,100),(255,255,255),-1)
# #bitAnd = cv2.bitwise_and(bw,img)
# bitXor = cv2.bitwise_xor(bw,img)
# cv2.imshow('bw',bw)
# cv2.imshow('mask',img)
# cv2.imshow('bitAnd',bitXor)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# img = cv2.imread('monaliza.jpg',1)
# img2 = cv2.imread('opencv.png',1)
#
# print(img.shape) # tuple of number of rows, cols, channels
# print(img.size) # total number of pixels
# print(img.dtype) # image datatype
# b,g,r = cv2.split(img)
# print(type(b))
# img = cv2.merge((b,g,r))
#
# img2 = cv2.resize(img2,(img.shape[1],img.shape[0]))
#
# #dst = cv2.add(img,img2)
# dst = cv2.addWeighted(img,0.8,img2,0.2,200) # gamma parameter to be add for each channel
# cv2.imshow('image',dst)
# cv2.waitKey(0)
# cv2.destroyAllWindows()



# import cv2
# import datetime
# events = [i for i in dir(cv2) if 'EVENT' in i]
# print(events)
# img = cv2.imread('monaliza.jpg',cv2.IMREAD_COLOR)
# print(img.shape[0])
# cv2.line(img,(0,0),(img.shape[1]-1,img.shape[0]-1),(255,255,0),2)
# cv2.rectangle(img,(0,0),(img.shape[1]-1,img.shape[0]-1),(7,201,245),3,cv2.LINE_8) #give -1 thickness ti fill the shape
# cv2.putText(img,str(datetime.datetime.now()),(10,50),cv2.FONT_ITALIC,0.8,(0,0,255),1,cv2.LINE_AA)
# cv2.imshow('test',img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# import cv2
# cap = cv2.VideoCapture(0)
# fourcc = cv2.VideoWriter_fourcc(*'XVID')
# out = cv2.VideoWriter('output.avi',fourcc,25,(640,480))
# cap.set(3,1208)
# cap.set(4,720)
# while (cap.isOpened()):
#     ret , frame = cap.read()
#     if ret:
#         gray =  cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
#         out.write(frame)
#         print(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
#         print(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
#         cv2.imshow('frame',frame)
#         if cv2.waitKey(1) & 0xFF == ord('q'):
#             break
#     else:
#         break
# cap.release()
# out.release()
#cv2.destroyAllWindows()



# import cv2
# img = cv2.imread('monaliza.jpg',cv2.IMREAD_GRAYSCALE) # 1 for color or 0 (IMREAD_GRAYSCALE) to gray scale or -1 (IMREAD_UNCHANGED)
# cv2.imshow('monaliza',img)
# k = cv2.waitKey(0) & 0xFF
# if k == 27:
#     cv2.destroyAllWindows()
# elif k == ord('s'):
#     cv2.imwrite('monaliza_copy.jpg',img)
#     cv2.destroyWindow('monaliza')