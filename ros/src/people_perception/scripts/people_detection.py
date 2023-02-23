#! /usr/bin/env python3

# ROS node to detect people in the camera image using OpenCV
# 
# Copyright 2023 I.Rodriguez UPV/EHU

import rospy
import os 
import cv2
import imutils
import numpy as np
from cv_bridge import CvBridge, CvBridgeError

# TODO: include required message/services 


class PeopleDetector:
    def __init__(self):
        rospy.init_node("people_detection")
        # TODO: Get parameters from launch file

        # Load People detector classifier model
        self.hog = cv2.HOGDescriptor()
        self.hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

        # ROS Publishers and Subscribers
        # TODO: Define a ROS Publisher to publish BodyROI (centroid and area) messages.
        
        # TODO: Define a ROS Publishers to publish Image messages.
        
        # TODO: Define required ROS subscriber to obtain Image messages from cameras.

        # On shutdown signal received execute stop function
        rospy.on_shutdown(self.stop) 
  
    def run(self):
        r = rospy.Rate(10)
        while not rospy.is_shutdown():
            r.sleep()
        
    def stop(self):
        rospy.loginfo("Stopping people_detection module ...")
        cv2.destroyAllWindows()
        exit(0)

    def drawCross(self, img, x, y, color, d):
        cv2.line(img, (x+d, y-d), (x-d, y+d), color, 2)
        cv2.line(img, (x-d, y-d), (x+d, y+d), color, 2)

    # TODO: Detect people on the image and publish: BodyROI and image
    def cameraCallback(self, msg):
        try:
            # Get OpenCV Mat image from ROS image
            cv_image = CvBridge().imgmsg_to_cv2(msg, "bgr8")

            # Publish the body image in a ROS topic
            body_img_msg = CvBridge().cv2_to_imgmsg(cv_image)

            cv2.imshow('Body', cv_image)
            cv2.waitKey(1)
                
        except CvBridgeError as e:
            rospy.logerror("cv_bridge exception: %s", e.what())
            print(e) 

if __name__=="__main__":
    try:
        rospy.loginfo("Starting... people_detection node")
        people_detector = PeopleDetector()
        people_detector.run()
    except rospy.ROSInterruptException: pass
