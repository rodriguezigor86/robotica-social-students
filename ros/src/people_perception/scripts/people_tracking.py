#! /usr/bin/env python3

# ROS node to make NAO track people 
# 
# Copyright 2023 I.Rodriguez UPV/EHU

import rospy
import math
import cv2
from cv_bridge import CvBridge, CvBridgeError

# TODO: include required message/services

class Camera:
    def __init__(self, pos, img_h, img_w, fov_h, fov_v):
        self.camera_pos = pos
        self.image_height = img_h
        self.image_width = img_w
        self.fov_horizontal = fov_h
        self.fov_vertical = fov_v

class Centroid:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class PeopleTracking:
    def __init__(self):
        # Init node
        rospy.init_node('people_tracking')

        self.img_width = 0
        self.img_height = 0
        self.first_image = False
                
        self.cv_bridge = CvBridge()

        # TODO: Get parameters from launch file
    
        # Camera fov obtained from http://doc.aldebaran.com/2-5/family/robots/video_robot.html
        self.top_camera_fov_horizontal = rospy.get_param('top_camera_fov_horizontal', 60.9)
        self.top_camera_fov_vertical = rospy.get_param('top_camera_fov_vertical', 47.6)
       
        # TODO: Define a ROS Publisher to obtain BodyROI (centroid and area) messages.

        # TODO: Define a ROS Publisher to obtain FaceROI (centroid and area) messages.
        
        # TODO: Define required ROS subscriber to obtain Image messages from cameras.

        # TODO: Define a ROS Publisher to publish HeadPosition messages.
        
        # TODO: Define a ROS Publisher to publish Twist messages for robot motion.
        
        # TODO: Define a Service to activate/deactivate people tracking behavior by a SetBool request

        # TODO: Define required variables
        self.find_people_enabled = False
        self.find_people_time_max = 120

    # TODO: Define a ROS service that obtains as input a SetBool request (True/False).
    # If activated: try to find people for a limited time 
    def findPeopleService(self, req):
        rospy.loginfo("Find people service activated")
        # Start time
        start = rospy.get_rostime().secs
        diff = 0

        # Find people activated
        self.find_people_enabled = req.data
        # TODO: Head to init position (0.0, 0.0, 0.5)

        r = rospy.Rate(1)
        # TODO: Wait until find a person and limited time is not exceeded
        




        rospy.loginfo("Person found:%d", self.person_found)
        self.find_people_enabled = False
        # TODO: return as response if a person is found or not

    # Publish Twist messages and wait X seconds
    def publishCmdVel(self, x, y, z, sleep):
        cmd_vel_msg = Twist()
        cmd_vel_msg.linear.x = x
        cmd_vel_msg.linear.y = y
        cmd_vel_msg.angular.z = z
        time = rospy.Duration(sleep)
        self.cmd_vel_pub.publish(cmd_vel_msg)
        rospy.sleep(time)

    # Converts the column of the detected object to an angle in degrees
    # type: horizontal or vertical 
    # img_size: image width or height depends on type 
    def getAngleFromCentroid(self, type, camera, centroid):
        
        # The column with absolute value "central_column" corresponds to FOV_camera / 2
        # rospy.loginfo("image_width: %d, image_height:%f, X:%f, Y:%f", camera.image_width, camera.image_height, centroid.x, centroid.y)
        
        if(type == "horizontal"):
            
            img_size = camera.image_width
            column = centroid.x
            fov_camera = camera.fov_horizontal
        
        elif(type == "vertical"):
        
            img_size = camera.image_height
            column = centroid.y
            fov_camera = camera.fov_vertical
        
        center = img_size / 2.0
    
        diff_center = center - column # centering
        angles_per_column = fov_camera / img_size; # angles per each column
        result_angle = angles_per_column * diff_center
        return math.radians(result_angle); # angle with respect to the middle of the image, check if the sign is ok!!!
    

    # Main loop
    def run(self):
        r = rospy.Rate(1)
        face_area_max = 10000 # To estimate the distance between the human and robot.

        while not rospy.is_shutdown():
            # Do only when find_people service is activated
            if self.find_people_enabled:

                # TODO: When a person is found but not it's face:
                #  - Turn to face the position in which the person is located.
                #  - Move the robot forward to approach the person.
                

                # TODO: When a face is found:
                #  - Move the robot's head to track the person's face.
                #  - Approach the person and stop at an appropriate social distance
                

                # TODO: When neither a face nor a person is found:
                #  - Head to init position
                #  - Define a strategy to make the robot explore



                self.body_detected = False
                self.face_detected = False
            r.sleep()  

    # This callback is only used to obtain camera info    
    def topCameraCallback(self, msg):
        try:
            if not self.first_image:
                cv_image = self.cv_bridge.imgmsg_to_cv2(msg, "bgr8")
                (rows,cols,channels) = cv_image.shape
                self.camera = Camera("top", rows, cols, self.top_camera_fov_horizontal, self.top_camera_fov_vertical)
                self.first_image = True

        except cv2.CvBridgeError as e:
            rospy.logerror("cv_bridge exception: %s", e.what())
            print(e)

    # TODO: Get the head angle position (pitch, yaw) according to the face centroid   
    def faceDetectionCallback(self,face_msg):
        rospy.loginfo("Face centroid: (%f,%f)", face_msg.cx, face_msg.cy)
    
    # TODO: Get the body angle position (pitch, yaw) according to the body centroid
    def bodyDetectionCallback(self, body_msg):
        rospy.loginfo("Body centroid: (%f,%f)", body_msg.cx, body_msg.cy)
            
if __name__ == '__main__':
    people_tracking = PeopleTracking()
    people_tracking.run()
    exit(0)