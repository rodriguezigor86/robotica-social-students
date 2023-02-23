#! /usr/bin/env python3

# ROS node to detect faces in the camera image using OpenCV
# 
# Copyright 2018 I.Rodriguez EHU

import rospy

# TODO: include required message/services

class CognitiveControl:
    def __init__(self):
        # ROS Init node
        rospy.init_node('cognitive_control')

        # TODO: Get parameters from launch file.

        # TODO: Define a ROS Publisher to publish SayTextMsg messages.
        
        # TODO: Define a ROS subscriber to obtain recognized speech String messages.
        
        # TODO: Define the required service clients to find people and play motion.
        rospy.wait_for_service('/perception/find_people')
        rospy.wait_for_service('/speech/tts/say_text')
        

        # TODO: Define the voice commands NAO must understand.

        # On shutdown signal received execute stop function
        rospy.on_shutdown(self.stop)

    def run(self):
        # ROS spin loop
        r = rospy.Rate(10) # 10hz
        while not rospy.is_shutdown():
            r.sleep()

    def stop(self):
        rospy.loginfo("Stopping cognitive_control module ...")
    
    # TODO: Define the task or sequence of tasks the robot must execute when a voice command is understood/misunderstood
    def speechRecognitionText(self, msg):
        rospy.loginfo("Speech recognition: %s", msg.data)

if __name__ == '__main__':
    rospy.loginfo("Initializing cognitive_control module...")
    cognitive_control = CognitiveControl()
    cognitive_control.run()
    
    exit(0)
