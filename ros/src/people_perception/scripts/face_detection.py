#! /usr/bin/env python3

# ROS node to detect faces in the camera image using OpenCV
# 
# Copyright 2023 I.Rodriguez UPV/EHU

import rospy
import os 
import cv2
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image

# TODO: include required message/services

class FaceDetector:
  def __init__(self):
    rospy.init_node("face_detection")
    # TODO: Get parameters from launch file

    # Load Face detector classifier model
    casc_path = os.path.split(os.path.dirname(__file__))[0]+"/cfg/haarcascades/haarcascade_frontalface_alt.xml"
    self.detector = cv2.CascadeClassifier(casc_path)

    # ROS Publishers and Subscribers
    # TODO: Define a ROS Publisher to publish FaceROI (centroid and area) messages.
        
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

  # TODO: Detect faces on the image and publish: FaceROI and image
  def cameraCallback(self, msg):
    try:
      # Get OpenCV Mat image from ROS image
      cv_image = CvBridge().imgmsg_to_cv2(msg, "bgr8")

      # Publish the face image in a ROS topic
      face_img_msg = CvBridge().cv2_to_imgmsg(cv_image)

      cv2.imshow('Face', cv_image)
      cv2.waitKey(1)
          
    except CvBridgeError as e:
      rospy.logerror("cv_bridge exception: %s", e.what())
      print(e)

if __name__=="__main__":
    try:
      face_detector = FaceDetector()
      face_detector.run()
    except rospy.ROSInterruptException: pass
