/**
 * @file NaoWebots.h
 * This file implements a communication interface between ROS and Webots
 *
 * It is based on the NAO Demo C file available in Webots
 *
 * @author <a href="mailto:mmattamala@ing.uchile.cl">Matias Mattamala</a>
 */

 #ifndef NAOCONTROLLER_H
 #define NAOCONTROLLER_H

// Webots stuff
#include <webots/utils/Motion.hpp>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Camera.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Accelerometer.hpp>
#include <webots/GPS.hpp>
#include <webots/Gyro.hpp>
#include <webots/InertialUnit.hpp>
#include <webots/TouchSensor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/LED.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Speaker.hpp>

// ROS Dependencies
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64MultiArray.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <naoqi_bridge_msgs/FloatArrayStamped.h>
#include <naoqi_bridge_msgs/FloatStamped.h>
#include <naoqi_bridge_msgs/Bumper.h>
#include <naoqi_bridge_msgs/FadeRGB.h>
#include <naoqi_bridge_msgs/HeadPosition.h>
#include <naoqi_bridge_msgs/PlayMotion.h>

// Boost
//#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

// Other C++ dependencies
#include <unistd.h>
#include <string.h>
#include <algorithm>

#define LED_CHEST "ChestBoard/Led"
#define LED_RFOOT "RFoot/Led"
#define LED_LFOOT "LFoot/Led"
#define LED_REYE "Face/Led/Right"
#define LED_LEYE "Face/Led/Left"
#define LED_REAR "Ears/Led/Right"
#define LED_LEAR "Ears/Led/Left"
#define LED_FACE "Face/Led"
#define LED_EARS "Ears/Led"
#define LED_FEET "Feet/Led"
#define LED_ALL "All/Led"

#define MOTION_TYPE_GESTURE "Gesture"
#define MOTION_TYPE_SPEAKING "Speaking"
#define MOTION_TYPE_LISTENING "Listening"
#define MOTION_TYPE_THINKING "Thinking"


namespace nao_webots {

class NaoController :
        public webots::Robot
{
public:
    // Default Constructor
    NaoController();

    // Default destructor
    ~NaoController();

private:
    // Callbacks
    void callbackJoy(const sensor_msgs::Joy::ConstPtr& joy);
    void callbackCamera(const ros::TimerEvent& event);
    void callbackSensors(const ros::TimerEvent& event);
    void callbackKeyboard(const ros::TimerEvent& event);
    void callbackLEDs(const naoqi_bridge_msgs::FadeRGB::ConstPtr& led);
    void callbackCmdVel(geometry_msgs::Twist msg);
    void callbackHeadPosition(naoqi_bridge_msgs::HeadPosition msg);

    // Services
    bool playMotionService(naoqi_bridge_msgs::PlayMotion::Request &req, naoqi_bridge_msgs::PlayMotion::Response &res);
    
    // Print currently used parameters
    void printParameters();

    // Initialize webots devices
    void initWebotsDevices();

    // Load motion files
    void loadMotionFiles();
    void startMotion(webots::Motion* motion);

    // Publish ROS data
    void publishCamera(ros::Time &time, webots::Camera *webots_camera, image_transport::CameraPublisher &camera_publisher, const std::string &topic);
    void publishJointState(ros::Time& time);
    void publishIMU(ros::Time& time);
    void publishFSR(ros::Time& time);
    void publishFSR2(ros::Time& time);
    void publishSonar(ros::Time &time, webots::DistanceSensor *webots_sonar, ros::Publisher& sonar_publisher, const std::string &frame_id);
    void publishBumper(ros::Time &time, webots::TouchSensor *webots_lfoot_bumper_right, webots::TouchSensor *webots_lfoot_bumper_left, ros::Publisher& bumper_publisher, const std::string &frame_id, const int bumper);
    void publishGroundTruth(ros::Time& time);

    // run simulation step
    bool simulationStep();

    // utils
    double clamp(double value, double min, double max);

private:
    int time_step_;

    // Node handle
    ros::NodeHandle node_handle_;

    // ROS publishers and subscribers
    ros::Publisher imu_publisher_;
    ros::Publisher joint_state_publisher_;
    ros::Publisher fsr_l_publisher_, fsr_l_total_publisher_;
    ros::Publisher fsr_r_publisher_, fsr_r_total_publisher_;
    ros::Publisher fsr_publisher_;
    ros::Publisher sonar_l_publisher_;
    ros::Publisher sonar_r_publisher_;
    ros::Publisher bumper_lfoot_publisher_;
    ros::Publisher bumper_rfoot_publisher_;

    image_transport::CameraPublisher cam_upper_publisher_;
    image_transport::CameraPublisher cam_lower_publisher_;

    ros::Subscriber joy_subscriber_;
    ros::Subscriber leds_subscriber_;
    ros::Subscriber cmd_vel_subscriber_;
    ros::Subscriber head_control_subscriber_;

    // ROS services
    ros::ServiceServer play_motion_server_; 

    // Parameters
    int rate_sensors_;
    int rate_camera_;

    // Webots Motions files
    // Files: Gestures
    std::string wb_file_motion_hand_wave_;
    std::string wb_file_motion_standup_front_;
    std::string wb_file_motion_taichi_;
    // Files: Walking
    std::string wb_file_motion_forward_;
    std::string wb_file_motion_backward_;
    std::string wb_file_motion_side_step_left_;
    std::string wb_file_motion_side_step_right_;
    std::string wb_file_motion_turn_left_;
    std::string wb_file_motion_turn_right_;
    // Files: Speaking
    std::string wb_file_motion_BodyTalk_1_;
    std::string wb_file_motion_BodyTalk_2_;
    std::string wb_file_motion_BodyTalk_3_;
    std::string wb_file_motion_BodyTalk_4_;
    std::string wb_file_motion_BodyTalk_5_;
    std::string wb_file_motion_BodyTalk_6_;
    std::string wb_file_motion_BodyTalk_7_;
    std::string wb_file_motion_BodyTalk_8_;
    std::string wb_file_motion_BodyTalk_9_;
    std::string wb_file_motion_BodyTalk_10_;
    std::string wb_file_motion_BodyTalk_11_;
    std::string wb_file_motion_BodyTalk_12_;
    std::string wb_file_motion_BodyTalk_13_;
    std::string wb_file_motion_BodyTalk_14_;
    std::string wb_file_motion_BodyTalk_15_;
    std::string wb_file_motion_BodyTalk_16_;
    // Files: Listening
    std::string wb_file_motion_Listening_1_;
    std::string wb_file_motion_Listening_2_;
    std::string wb_file_motion_Listening_3_;
    std::string wb_file_motion_Listening_4_;
    std::string wb_file_motion_Listening_5_;
    std::string wb_file_motion_Listening_6_;
    std::string wb_file_motion_Listening_7_;
    // Files: Thinking
    std::string wb_file_motion_Remember_1_;
    std::string wb_file_motion_Remember_2_;
    std::string wb_file_motion_Remember_3_;
    std::string wb_file_motion_ThinkingLoop_1_;
    std::string wb_file_motion_ThinkingLoop_2_;

    // Webots Motions
    webots::Motion* wb_motion_current_;
    // Motion: Gestures
    webots::Motion* wb_motion_hand_wave_;
    webots::Motion* wb_motion_standup_front_;
    webots::Motion* wb_motion_taichi_;
    // Motion: Walking
    webots::Motion* wb_motion_forward_;
    webots::Motion* wb_motion_backward_;
    webots::Motion* wb_motion_side_step_left_;
    webots::Motion* wb_motion_side_step_right_;
    webots::Motion* wb_motion_turn_left_;
    webots::Motion* wb_motion_turn_right_;
    // Motion: Speaking
    webots::Motion* wb_motion_BodyTalk_1_;
    webots::Motion* wb_motion_BodyTalk_2_;
    webots::Motion* wb_motion_BodyTalk_3_;
    webots::Motion* wb_motion_BodyTalk_4_;
    webots::Motion* wb_motion_BodyTalk_5_;
    webots::Motion* wb_motion_BodyTalk_6_;
    webots::Motion* wb_motion_BodyTalk_7_;
    webots::Motion* wb_motion_BodyTalk_8_;
    webots::Motion* wb_motion_BodyTalk_9_;
    webots::Motion* wb_motion_BodyTalk_10_;
    webots::Motion* wb_motion_BodyTalk_11_;
    webots::Motion* wb_motion_BodyTalk_12_;
    webots::Motion* wb_motion_BodyTalk_13_;
    webots::Motion* wb_motion_BodyTalk_14_;
    webots::Motion* wb_motion_BodyTalk_15_;
    webots::Motion* wb_motion_BodyTalk_16_;
    // Motion: Listening
    webots::Motion* wb_motion_Listening_1_;
    webots::Motion* wb_motion_Listening_2_;
    webots::Motion* wb_motion_Listening_3_;
    webots::Motion* wb_motion_Listening_4_;
    webots::Motion* wb_motion_Listening_5_;
    webots::Motion* wb_motion_Listening_6_;
    webots::Motion* wb_motion_Listening_7_;
    // Motion: Thinking
    webots::Motion* wb_motion_Remember_1_;
    webots::Motion* wb_motion_Remember_2_;
    webots::Motion* wb_motion_Remember_3_;
    webots::Motion* wb_motion_ThinkingLoop_1_;
    webots::Motion* wb_motion_ThinkingLoop_2_;

    // Webots motions maps
    std::map<std::string, webots::Motion*> map_stand_gesture_;
    std::map<std::string, webots::Motion*> map_stand_speaking_;
    std::map<std::string, webots::Motion*> map_stand_listening_;
    std::map<std::string, webots::Motion*> map_stand_thinking_;

    // Webots devices
    // Cameras
    webots::Camera* wb_camera_top_;
    webots::Camera* wb_camera_bottom_;

    // Accelerometer
    webots::Accelerometer* wb_accelerometer_;

    // Gyro
    webots::Gyro* wb_gyro_;

    // GPS (ground truth)
    webots::GPS* wb_gps_;

    // Inertial Unit (Orientation)
    webots::InertialUnit* wb_inertial_unit_;

    // Ultrasound sensors
    webots::DistanceSensor* wb_sonar_left_;
    webots::DistanceSensor* wb_sonar_right_;

    // Foot sensors
    webots::TouchSensor* wb_fsr_left_;
    webots::TouchSensor* wb_fsr_right_;

    // Foot bumpers
    webots::TouchSensor* wb_lfoot_bumper_right_;
    webots::TouchSensor* wb_lfoot_bumper_left_;
    webots::TouchSensor* wb_rfoot_bumper_right_;
    webots::TouchSensor* wb_rfoot_bumper_left_;

    // Joint encoders
    std::vector<webots::PositionSensor*> wb_joints_;
    webots::PositionSensor* wb_head_yaw_sensor_;
    webots::PositionSensor* wb_head_pitch_sensor_;
    webots::PositionSensor* wb_r_shoulder_pitch_sensor_;
    webots::PositionSensor* wb_r_shoulder_roll_sensor_;
    webots::PositionSensor* wb_r_elbow_yaw_sensor_;
    webots::PositionSensor* wb_r_elbow_roll_sensor_;
    webots::PositionSensor* wb_l_shoulder_pitch_sensor_;
    webots::PositionSensor* wb_l_shoulder_roll_sensor_;
    webots::PositionSensor* wb_l_elbow_yaw_sensor_;
    webots::PositionSensor* wb_l_elbow_roll_sensor_;
    webots::PositionSensor* wb_r_hip_yaw_pitch_sensor_;
    webots::PositionSensor* wb_r_hip_roll_sensor_;
    webots::PositionSensor* wb_r_hip_pitch_sensor_;
    webots::PositionSensor* wb_r_knee_pitch_sensor_;
    webots::PositionSensor* wb_r_ankle_pitch_sensor_;
    webots::PositionSensor* wb_r_ankle_roll_sensor_;
    webots::PositionSensor* wb_l_hip_yaw_pitch_sensor_;
    webots::PositionSensor* wb_l_hip_roll_sensor_;
    webots::PositionSensor* wb_l_hip_pitch_sensor_;
    webots::PositionSensor* wb_l_knee_pitch_sensor_;
    webots::PositionSensor* wb_l_ankle_pitch_sensor_;
    webots::PositionSensor* wb_l_ankle_roll_sensor_;

    // Leds
    webots::LED* wb_chest_led_;
    webots::LED* wb_rfoot_led_;
    webots::LED* wb_lfoot_led_;
    webots::LED* wb_leye_led_;
    webots::LED* wb_reye_led_;
    webots::LED* wb_lear_led_;
    webots::LED* wb_rear_led_;

    // Speakers
    // webots::Speaker* wb_lear_speaker_;
    // webots::Speaker* wb_rear_speaker_;

    // Keyboard
    webots::Keyboard* wb_keyboard_;
};


} //nao_webots
#endif // NAOCONTROLLER_H
