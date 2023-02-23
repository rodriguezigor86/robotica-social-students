#! /usr/bin/env python3
# 
# Copyright 2023 I.Rodriguez EHU
#
# ROS node to teleop the robot by speech commands

import rospy
import numpy as np
from std_msgs.msg import String
from geometry_msgs.msg import Twist

class TeleopSpeech:
    def __init__(self):
        rospy.init_node("teleop_speech")
        # TODO: Get topic names from launch file
        
        # TODO: Define required ROS publishers and subscribers

        # Define voice commands
        self.commands_list = ["adelante", "atrás", "paso izquierda", "paso derecha", "giro izquierda", "giro derecha", "detener"]
        self.current_command = "detener"
        
        # On shutdown signal received execute stop function
        rospy.on_shutdown(self.stop) 
    
    def run(self):
        r = rospy.Rate(1)
        while not rospy.is_shutdown():
            # TODO: Publish current command continuously, except for stop command
            

            r.sleep()
        
        rospy.loginfo("Stopping teleop_speech module ...")
        exit(0)
    
    def stop(self):
        cmd_vel_msg_ = Twist()
        cmd_vel_msg_.linear.x  = 0 
        cmd_vel_msg_.linear.y  = 0
        cmd_vel_msg_.angular.z = 0.0
        self.cmd_vel_pub.publish( cmd_vel_msg_ )
        # print("Stopping")
    
    # TODO: Define a speech recognition subscriber callback function that creates velocity commands
    # according to the given voice order.
    def speechRecognitionCallback(self, msg):
        # Voice commands:
        # Forward: Adelante
        # Backward: Atrás
        # Step right: Paso izquierda
        # Step left: Paso derecha
        # Turn right: Giro izquierda
        # Turn left: Giro derecha
        rospy.logingo("Msg: %s", msg.data)
        
if __name__ == '__main__':
    teleop_speech = TeleopSpeech()
    teleop_speech.run()
    exit(0)


