import cv2
import numpy as np
import imutils
import os 

lower_red1 = np.array([0,185,10])
upper_red1 = np.array([6,255,255])

lower_red2 = np.array([160,100,20])
upper_red2 = np.array([179,255,125])

lower_blue = np.array([105, 50, 50])
upper_blue = np.array([116, 255, 255])

for filename in os.listdir("H:\embedded\projects\mia\photos"):
    if filename.endswith('.jpg'):
        image_path = os.path.join("H:\embedded\projects\mia\photos", filename)
        image = cv2.imread(image_path)

        blurred = cv2.GaussianBlur(image, (11, 11), 0)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

        mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
        mask1 = cv2.erode(mask1, None, iterations=2)
        mask1 = cv2.dilate(mask1, None, iterations=2)
        # Convert the filtered image to grayscale

        mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
        mask2 = cv2.erode(mask2, None, iterations=2)
        mask2 = cv2.dilate(mask2, None, iterations=2)

        mask = cv2.bitwise_or(mask1, mask2)

        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        # only proceed if at least one contour was found
        if len(cnts) > 0:
            # find the largest contour in the mask, then use
            # it to compute the minimum enclosing circle and
            # centroid
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
            # only proceed if the radius meets a minimum size
            if radius > 5:
                # draw the circle and centroid on the frame,
                # then update the list of tracked points
                cv2.circle(image, (int(x), int(y)), int(radius),
                    (0, 255, 255), 2)
                cv2.circle(image, center, 5, (0, 0, 255), -1)



        mask = cv2.inRange(hsv, lower_blue, upper_blue)
        mask = cv2.erode(mask, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)

        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        # only proceed if at least one contour was found
        if len(cnts) > 0:
            # find the largest contour in the mask, then use
            # it to compute the minimum enclosing circle and
            # centroid
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
            # only proceed if the radius meets a minimum size
            if radius > 5:
                # draw the circle and centroid on the frame,
                # then update the list of tracked points
                cv2.circle(image, (int(x), int(y)), int(radius),
                    (0, 255, 255), 2)
                cv2.circle(image, center, 5, (0, 0, 255), -1)

        cv2.imshow('Balls Detection', image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
        output_path = os.path.join("H:\embedded\projects\mia\photos\output", filename)  #  a directory for output images
        cv2.imwrite(output_path, image)