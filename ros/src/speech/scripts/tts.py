#! /usr/bin/env python3
# ROS node to convert text into speech using gTTS
# 
# Copyright 2018 I.Rodriguez EHU

import rospy
import os
from gtts import gTTS
from speech.srv import SayTextSrv, SayTextSrvResponse
from speech.msg import SayTextMsg
from std_msgs.msg import Bool

class TTS:
    def __init__(self):
      # ROS Init node
      rospy.init_node('tts')
      
      self.audio_path = rospy.get_param('~audio_path','audio/')
      tts_text_topic = rospy.get_param('~tts_text_topic','speech/tts/text')
      tts_status_topic = rospy.get_param('~tts_status_topic','speech/tts/status')
      # ROS Services Server
      say_text_service = rospy.Service("speech/tts/say_text", SayTextSrv, self.sayTextService)
      # ROS Subscriber
      tts_text_sub = rospy.Subscriber(tts_text_topic, SayTextMsg, self.sayTextMessage, queue_size = 1)
      # ROS Publisher
      self.tts_status_pub = rospy.Publisher(tts_status_topic,Bool, queue_size=10)

    def run(self):
        # ROS spin loop
        r = rospy.Rate(10) # 10hz
        while not rospy.is_shutdown():
            r.sleep()
        #rospy.spin()

    # Task: Define a service server that generates an audio giving the text and the language
    def sayText(self, language, text):
        # Publish status
        self.tts_status_pub.publish(True)    
        # Generate audio and save it using gTTS
        tts = gTTS(text=text, lang=language)
        filename = self.audio_path + "say_text.wav"
        tts.save(filename)

        try:
            open(filename, "r")
            cmd_vlc = 'cvlc --play-and-exit ' + filename
            os.system(cmd_vlc)
            self.tts_status_pub.publish(False)
        except Exception as e:
            rospy.logerr(str(e))
    ################################## Services ######################################
    def sayTextService(self, req):
        self.sayText(req.language, req.text)
        return SayTextSrvResponse(True)
    
    def sayTextMessage(self, msg):
        self.sayText(msg.language, msg.text)

if __name__ == '__main__':

    tts = TTS()
    tts.run()

    rospy.loginfo("Stopping face_detection module ...")
    exit(0)
