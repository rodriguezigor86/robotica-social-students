/**
 * @file BHInterface.cpp
 * This file implements an UDP communication interface between a NAO and a external computer running ROS
 *
 * This file uses part of the BHuman Code Release 2016 <a href="https://github.com/bhuman/BHumanCodeRelease"</a>)
 *
 * @author <a href="mailto:mmattamala@ing.uchile.cl">Matias Mattamala</a>
 */

#ifndef NAOCONTROLLER_CPP
#define NAOCONTROLLER_CPP

#include "NaoController.h"
#include <iostream>

namespace nao_webots{

int rgb2hex(int r, int g, int b, bool with_head)
{
  std::stringstream ss;
  int x;
  if (with_head)
    ss << "0x";
  ss << std::hex << (r << 16 | g << 8 | b );
  ss >> x;
  return x;
}

NaoController::NaoController() :
    node_handle_("~"),
    webots::Robot()
{
    // Read communication parameters from parameter server
    node_handle_.param("rate_sensors", rate_sensors_, 100);
    node_handle_.param("rate_camera", rate_camera_, 30);

    // Motion: Gestures
    node_handle_.param("motion_hand_wave", wb_file_motion_hand_wave_, std::string("motions/NAO/Stand/Gestures/HandWave.motion"));
    node_handle_.param("motion_standup_front", wb_file_motion_standup_front_, std::string("motions/NAO/Stand/Gestures/StandUpFromFront.motion"));
    node_handle_.param("motion_taichi", wb_file_motion_taichi_, std::string("motions/NAO/Stand/Gestures/TaiChi.motion"));

    // Motion: Walking
    node_handle_.param("motion_forward", wb_file_motion_forward_, std::string("motions/NAO/Walking/Forwards.motion"));
    node_handle_.param("motion_backwards", wb_file_motion_backward_, std::string("motions/NAO/Walking/Backwards.motion"));
    node_handle_.param("motion_side_step_left", wb_file_motion_side_step_left_, std::string("motions/NAO/Walking/SideStepLeft.motion"));
    node_handle_.param("motion_side_step_right", wb_file_motion_side_step_right_, std::string("motions/NAO/Walking/SideStepRight.motion"));
    node_handle_.param("motion_turn_left", wb_file_motion_turn_left_, std::string("motions/NAO/Walking/TurnLeft20.motion"));
    node_handle_.param("motion_turn_right", wb_file_motion_turn_right_, std::string("motions/NAO/Walking/TurnRight20.motion"));
    
    // Motion: Speaking
    node_handle_.param("motion_BodyTalk_1", wb_file_motion_BodyTalk_1_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_1.motion"));
    node_handle_.param("motion_BodyTalk_2", wb_file_motion_BodyTalk_2_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_2.motion"));
    node_handle_.param("motion_BodyTalk_3", wb_file_motion_BodyTalk_3_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_3.motion"));
    node_handle_.param("motion_BodyTalk_4", wb_file_motion_BodyTalk_4_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_4.motion"));
    node_handle_.param("motion_BodyTalk_5", wb_file_motion_BodyTalk_5_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_5.motion"));
    node_handle_.param("motion_BodyTalk_6", wb_file_motion_BodyTalk_6_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_6.motion"));
    node_handle_.param("motion_BodyTalk_7", wb_file_motion_BodyTalk_7_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_7.motion"));
    node_handle_.param("motion_BodyTalk_8", wb_file_motion_BodyTalk_8_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_8.motion"));
    node_handle_.param("motion_BodyTalk_9", wb_file_motion_BodyTalk_9_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_9.motion"));
    node_handle_.param("motion_BodyTalk_10", wb_file_motion_BodyTalk_10_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_10.motion"));
    node_handle_.param("motion_BodyTalk_11", wb_file_motion_BodyTalk_11_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_11.motion"));
    node_handle_.param("motion_BodyTalk_12", wb_file_motion_BodyTalk_12_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_12.motion"));
    node_handle_.param("motion_BodyTalk_13", wb_file_motion_BodyTalk_13_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_13.motion"));
    node_handle_.param("motion_BodyTalk_14", wb_file_motion_BodyTalk_14_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_14.motion"));
    node_handle_.param("motion_BodyTalk_15", wb_file_motion_BodyTalk_15_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_15.motion"));
    node_handle_.param("motion_BodyTalk_16", wb_file_motion_BodyTalk_16_, std::string("motions/NAO/Stand/BodyTalk/Speaking/BodyTalk_16.motion"));
    // Motion: Listening
    node_handle_.param("motion_Listening_1", wb_file_motion_Listening_1_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_1.motion"));
    node_handle_.param("motion_Listening_2", wb_file_motion_Listening_2_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_2.motion"));
    node_handle_.param("motion_Listening_3", wb_file_motion_Listening_3_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_3.motion"));
    node_handle_.param("motion_Listening_4", wb_file_motion_Listening_4_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_4.motion"));
    node_handle_.param("motion_Listening_5", wb_file_motion_Listening_5_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_5.motion"));
    node_handle_.param("motion_Listening_6", wb_file_motion_Listening_6_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_6.motion"));
    node_handle_.param("motion_Listening_7", wb_file_motion_Listening_7_, std::string("motions/NAO/Stand/BodyTalk/Listening/Listening_7.motion"));
    // Motion: Thinking
    node_handle_.param("motion_Remember_1", wb_file_motion_Remember_1_, std::string("motions/NAO/Stand/BodyTalk/Thinking/Remember_1.motion"));
    node_handle_.param("motion_Remember_2", wb_file_motion_Remember_2_, std::string("motions/NAO/Stand/BodyTalk/Thinking/Remember_2.motion"));
    node_handle_.param("motion_Remember_3", wb_file_motion_Remember_3_, std::string("motions/NAO/Stand/BodyTalk/Thinking/Remember_3.motion"));
    node_handle_.param("motion_ThinkingLoop_1", wb_file_motion_ThinkingLoop_1_, std::string("motions/NAO/Stand/BodyTalk/Thinking/ThinkingLoop_1.motion"));
    node_handle_.param("motion_ThinkingLoop_2", wb_file_motion_ThinkingLoop_2_, std::string("motions/NAO/Stand/BodyTalk/Thinking/ThinkingLoop_2.motion"));


    // ROS Callbacks
    // Joy
    joy_subscriber_ = node_handle_.subscribe<sensor_msgs::Joy>("joy", 1, &NaoController::callbackJoy, this);
    // LEDs
    leds_subscriber_ = node_handle_.subscribe<naoqi_bridge_msgs::FadeRGB>("/leds", 1, &NaoController::callbackLEDs, this);
    // Command Velocities
    cmd_vel_subscriber_ = node_handle_.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, &NaoController::callbackCmdVel, this);
    // Head Control
    head_control_subscriber_ = node_handle_.subscribe<naoqi_bridge_msgs::HeadPosition>("/head_position", 1, &NaoController::callbackHeadPosition, this);

    // Create communication interfaces
    // IMU
    imu_publisher_ = node_handle_.advertise<sensor_msgs::Imu>("/imu/data_raw", 1);
    // FSR
    fsr_publisher_ = node_handle_.advertise<std_msgs::Float64MultiArray>("/fsr", 1);
    fsr_l_publisher_ = node_handle_.advertise<naoqi_bridge_msgs::FloatArrayStamped>("/fsr_l", 1);
    fsr_r_publisher_ = node_handle_.advertise<naoqi_bridge_msgs::FloatArrayStamped>("/fsr_r", 1);
    fsr_l_total_publisher_ = node_handle_.advertise<naoqi_bridge_msgs::FloatStamped>("/fsr_l_total", 1);
    fsr_r_total_publisher_ = node_handle_.advertise<naoqi_bridge_msgs::FloatStamped>("/fsr_r_total", 1);
    // Sonar
    sonar_l_publisher_ = node_handle_.advertise<sensor_msgs::Range>("/sonar/left", 1);
    sonar_r_publisher_ = node_handle_.advertise<sensor_msgs::Range>("/sonar/right", 1);
    // Contact
    bumper_lfoot_publisher_ = node_handle_.advertise<naoqi_bridge_msgs::Bumper>("/bumper/left", 1);
    bumper_rfoot_publisher_ = node_handle_.advertise<naoqi_bridge_msgs::Bumper>("/bumper/right", 1);
    // Joints state
    joint_state_publisher_ = node_handle_.advertise<sensor_msgs::JointState>("/joint_states", 1);

    // Image topic
    image_transport::ImageTransport it(node_handle_);
    cam_upper_publisher_  = it.advertiseCamera("/camera/top/image_raw", 1);
    cam_lower_publisher_  = it.advertiseCamera("/camera/bottom/image_raw", 1);

    // Initialize robot
    time_step_ = getBasicTimeStep();
    ROS_INFO("TIME STEP: %d", time_step_);

    // Init devices
    initWebotsDevices();

    // Init head position
    wb_head_pitch_sensor_->getMotor()->setPosition(0.0);
    wb_head_yaw_sensor_->getMotor()->setPosition(0.0);

    // Prepare timers for publication
    ros::Timer timer_sensors = node_handle_.createTimer(ros::Duration(1.0/rate_sensors_), &NaoController::callbackSensors, this);
    ros::Timer timer_camera  = node_handle_.createTimer(ros::Duration(1.0/rate_camera_), &NaoController::callbackCamera, this);
    ros::Timer timer_keyboard  = node_handle_.createTimer(ros::Duration(1.0/rate_camera_), &NaoController::callbackKeyboard, this);

    // Load motion files
    loadMotionFiles();

    // ROS Services
    play_motion_server_ = node_handle_.advertiseService("/motion/play", &NaoController::playMotionService, this);

    wb_motion_hand_wave_->setLoop(true);
    wb_motion_hand_wave_->play();

    // until a key is pressed
    int key = -1;
    do {
        simulationStep();
        key = wb_keyboard_->getKey();
    }
    while (key >= 0);

    // stop looping this motion
    wb_motion_hand_wave_->setLoop(false);

    ros::spin();
}

NaoController::~NaoController()
{
    // Gestures
    delete wb_motion_hand_wave_;
    delete wb_motion_standup_front_;
    delete wb_motion_taichi_;
    // Walking
    delete wb_motion_forward_;
    delete wb_motion_backward_;
    delete wb_motion_side_step_left_;
    delete wb_motion_side_step_right_;
    delete wb_motion_turn_left_;
    delete wb_motion_turn_right_;
    // Speaking
    delete wb_motion_BodyTalk_1_;
    delete wb_motion_BodyTalk_2_;
    delete wb_motion_BodyTalk_3_;
    delete wb_motion_BodyTalk_4_;
    delete wb_motion_BodyTalk_5_;
    delete wb_motion_BodyTalk_6_;
    delete wb_motion_BodyTalk_7_;
    delete wb_motion_BodyTalk_8_;
    delete wb_motion_BodyTalk_9_;
    delete wb_motion_BodyTalk_10_;
    delete wb_motion_BodyTalk_11_;
    delete wb_motion_BodyTalk_12_;
    delete wb_motion_BodyTalk_13_;
    delete wb_motion_BodyTalk_14_;
    delete wb_motion_BodyTalk_15_;
    delete wb_motion_BodyTalk_16_;
    // Listening
    delete wb_motion_Listening_1_;
    delete wb_motion_Listening_2_;
    delete wb_motion_Listening_3_;
    delete wb_motion_Listening_4_;
    delete wb_motion_Listening_5_;
    delete wb_motion_Listening_6_;
    delete wb_motion_Listening_7_;
    // Thinking
    delete wb_motion_Remember_1_;
    delete wb_motion_Remember_2_;
    delete wb_motion_Remember_3_;
    delete wb_motion_ThinkingLoop_1_;
    delete wb_motion_ThinkingLoop_2_;
}

bool NaoController::simulationStep()
{
    bool response = true;
    if (step(time_step_) == -1)
        response = false;
    return response;
}

#ifndef USE_SUPERVISOR
void NaoController::callbackKeyboard(const ros::TimerEvent &event)
{
    simulationStep();

    int key = wb_keyboard_->getKey();

    switch (key)
    {
    case webots::Keyboard::LEFT:
        startMotion(wb_motion_side_step_left_);
        break;
    case webots::Keyboard::RIGHT:
        startMotion(wb_motion_side_step_right_);
        break;
    case webots::Keyboard::UP:
        startMotion(wb_motion_forward_);
        break;
    case webots::Keyboard::DOWN:
        startMotion(wb_motion_backward_);
        break;
    case webots::Keyboard::LEFT | webots::Keyboard::SHIFT:
        startMotion(wb_motion_turn_left_);
        break;
    case webots::Keyboard::RIGHT | webots::Keyboard::SHIFT:
        startMotion(wb_motion_turn_right_);
        break;
    case webots::Keyboard::PAGEUP:
        startMotion(wb_motion_standup_front_);
        break;
    }
}
#endif

bool NaoController::playMotionService(naoqi_bridge_msgs::PlayMotion::Request &req, naoqi_bridge_msgs::PlayMotion::Response &res){

    std::map<std::string, webots::Motion*> current_map;
    res.success = false;
    if(req.type == MOTION_TYPE_GESTURE) current_map = map_stand_gesture_;
    else if(req.type == MOTION_TYPE_SPEAKING) current_map = map_stand_speaking_;
    else if(req.type == MOTION_TYPE_LISTENING) current_map = map_stand_listening_;
    else if(req.type == MOTION_TYPE_THINKING) current_map = map_stand_thinking_;
    if (req.type != "")
    {
        webots::Motion* motion = current_map[req.name.c_str()];
        startMotion(motion);
        res.success = true;
    }
    return true;
}

void NaoController::callbackCmdVel(const geometry_msgs::Twist cmd_vel)
{
    simulationStep();

    if (cmd_vel.linear.x > 0) startMotion(wb_motion_forward_);
    else if (cmd_vel.linear.x < 0) startMotion(wb_motion_backward_);
    else if (cmd_vel.linear.y > 0) startMotion(wb_motion_side_step_left_);
    else if (cmd_vel.linear.y < 0) startMotion(wb_motion_side_step_right_);
    else if (cmd_vel.angular.z > 0) startMotion(wb_motion_turn_left_);
    else if (cmd_vel.angular.z < 0) startMotion(wb_motion_turn_right_);

}

void NaoController::callbackCamera(const ros::TimerEvent& event)
{
    simulationStep();

    ros::Time time = ros::Time::now();

    publishCamera(time, wb_camera_top_, cam_upper_publisher_, "/CameraTop_optical_frame");
    publishCamera(time, wb_camera_bottom_, cam_lower_publisher_, "/CameraBottom_optical_frame");
}

void NaoController::callbackLEDs(const naoqi_bridge_msgs::FadeRGB::ConstPtr& led)
{
    simulationStep();
    
    std::string led_name = led->led_name;
    float r = led->color.r;
    float g = led->color.g;
    float b = led->color.b;
    float a = led->color.a; 

    int color = rgb2hex(r, g, b, true);

    if (led_name == LED_CHEST) wb_chest_led_->set(color);
    if (led_name == LED_RFOOT) wb_rfoot_led_->set(color);
    if (led_name == LED_LFOOT) wb_lfoot_led_->set(color);
    if (led_name == LED_REYE) wb_reye_led_->set(color);
    if (led_name == LED_LEYE) wb_leye_led_->set(color);
    if (led_name == LED_REAR) wb_rear_led_->set(color);
    if (led_name == LED_LEAR) wb_lear_led_->set(color);
    if (led_name == LED_FACE) 
    {
        wb_reye_led_->set(color);
        wb_leye_led_->set(color);
    }
    if (led_name == LED_EARS) 
    {
        wb_rear_led_->set(rgb2hex(0, 0, 255, true));
        wb_lear_led_->set(rgb2hex(0, 0, 255, true));
    }
    if (led_name == LED_FEET) 
    {
        wb_rfoot_led_->set(color);
        wb_lfoot_led_->set(color);
    }
    if (led_name == LED_ALL) 
    {
        wb_reye_led_->set(color);
        wb_leye_led_->set(color);
        wb_rear_led_->set(rgb2hex(0, 0, 255, true));
        wb_lear_led_->set(rgb2hex(0, 0, 255, true));
        wb_chest_led_->set(color);
        wb_rfoot_led_->set(color);
        wb_lfoot_led_->set(color);
    }

}

void NaoController::callbackHeadPosition(naoqi_bridge_msgs::HeadPosition msg)
{
    simulationStep();

    wb_head_pitch_sensor_->getMotor()->setVelocity(msg.velocity);
    wb_head_yaw_sensor_->getMotor()->setVelocity(msg.velocity);
    wb_head_pitch_sensor_->getMotor()->setPosition(msg.pitch);
    wb_head_yaw_sensor_->getMotor()->setPosition(msg.yaw);
    // float pitch = wb_head_pitch_sensor_->getValue() + msg.pitch;
    // float yaw = wb_head_yaw_sensor_->getValue() + msg.yaw;
    // wb_head_pitch_sensor_->getMotor()->setPosition(pitch);
    // wb_head_yaw_sensor_->getMotor()->setPosition(yaw);
    // float pitch = 0;
    // if (wb_head_pitch_sensor_->getValue() + msg.pitch < -0.67) pitch = -0.67;
    // else if(wb_head_pitch_sensor_->getValue() + msg.pitch > 0.51) pitch = 0.51;
    // float yaw = wb_head_yaw_sensor_->getValue() + msg.yaw;
    // ROS_INFO("PITCH:%f", pitch);
    // wb_head_pitch_sensor_->getMotor()->setPosition(pitch);
    // wb_head_yaw_sensor_->getMotor()->setPosition(yaw);
}

void NaoController::publishCamera(ros::Time& time, webots::Camera *webots_camera, image_transport::CameraPublisher& camera_publisher, const std::string &topic)
{
    // update upper camera
    int image_width  = webots_camera->getWidth();
    int image_height = webots_camera->getHeight();

    // read rgb pixel values from the camera
    const unsigned char *image = webots_camera->getImage();

    sensor_msgs::Image ros_image;
    sensor_msgs::CameraInfo ros_cam_info;

    // fill image
    ros_image.encoding = "rgb8";
    ros_image.height   = image_height;
    ros_image.width    = image_width;
    ros_image.step     = 3 * image_width;

    size_t st0 = (ros_image.step * ros_image.height);
    ros_image.data.resize(st0);
    ros_image.is_bigendian = 0;

    for (int y = 0; y < image_height; y++)
    {
        for (int x = 0; x < image_width; x++)
        {
            ros_image.data[3*(y*image_width + x)    ] = webots_camera->imageGetRed(image, image_width, x, y);
            ros_image.data[3*(y*image_width + x) + 1] = webots_camera->imageGetGreen(image, image_width, x, y);
            ros_image.data[3*(y*image_width + x) + 2] = webots_camera->imageGetBlue(image, image_width, x, y);
        }
    }

    // fill camera info
    ros_cam_info.height = image_height;
    ros_cam_info.width = image_width;
    ros_cam_info.header.stamp = time;
    ros_cam_info.header.frame_id = topic;

    // publish image
    camera_publisher.publish(ros_image, ros_cam_info);
}

void NaoController::callbackSensors(const ros::TimerEvent& event)
{
    simulationStep();

    ros::Time time = ros::Time::now();

    // publish joints
    publishJointState(time);
    publishIMU(time);
    publishFSR(time);
    publishSonar(time, wb_sonar_left_, sonar_l_publisher_, "/LSonar_frame");
    publishSonar(time, wb_sonar_right_, sonar_r_publisher_, "/RSonar_frame");
    publishBumper(time, wb_lfoot_bumper_right_, wb_lfoot_bumper_left_, bumper_lfoot_publisher_, "/LFootBumper_frame", 1);
    publishBumper(time, wb_rfoot_bumper_right_, wb_rfoot_bumper_left_, bumper_rfoot_publisher_, "/RFootBumper_frame", 0);
}

void NaoController::publishJointState(ros::Time& time)
{
    //ROS_INFO("SENSORS CALLBACK");
    sensor_msgs::JointState ros_joints;

    ros_joints.name.resize(26);
    ros_joints.position.resize(26);

    // Head angles
    ros_joints.name[0]      = "HeadYaw";
    ros_joints.position[0]  = wb_head_yaw_sensor_->getValue();

    ros_joints.name[1]      = "HeadPitch";
    ros_joints.position[1]  = wb_head_pitch_sensor_->getValue();

    // Left leg
    ros_joints.name[2]      = "LHipYawPitch";
    ros_joints.position[2]  = wb_l_hip_yaw_pitch_sensor_->getValue();

    ros_joints.name[3]      = "LHipRoll";
    ros_joints.position[3]  = wb_l_hip_roll_sensor_->getValue();

    ros_joints.name[4]      = "LHipPitch";
    ros_joints.position[4]  = wb_l_hip_pitch_sensor_->getValue();

    ros_joints.name[5]      = "LKneePitch";
    ros_joints.position[5]  = wb_l_knee_pitch_sensor_->getValue();

    ros_joints.name[6]      = "LAnklePitch";
    ros_joints.position[6]  = wb_l_ankle_pitch_sensor_->getValue();

    ros_joints.name[7]      = "LAnkleRoll";
    ros_joints.position[7]  = wb_l_ankle_roll_sensor_->getValue();

    // Right Leg
    ros_joints.name[8]      = "RHipYawPitch";
    ros_joints.position[8]  = wb_r_hip_yaw_pitch_sensor_->getValue();

    ros_joints.name[9]      = "RHipRoll";
    ros_joints.position[9]  = wb_r_hip_roll_sensor_->getValue();

    ros_joints.name[10]     = "RHipPitch";
    ros_joints.position[10] = wb_r_hip_pitch_sensor_->getValue();

    ros_joints.name[11]     = "RKneePitch";
    ros_joints.position[11] = wb_r_knee_pitch_sensor_->getValue();

    ros_joints.name[12]     = "RAnklePitch";
    ros_joints.position[12] = wb_r_ankle_pitch_sensor_->getValue();

    ros_joints.name[13]     = "RAnkleRoll";
    ros_joints.position[13] = wb_r_ankle_roll_sensor_->getValue();

    // Left arm
    ros_joints.name[14]     = "LShoulderPitch";
    ros_joints.position[14] = wb_l_shoulder_pitch_sensor_->getValue();

    ros_joints.name[15]     = "LShoulderRoll";
    ros_joints.position[15] = wb_l_shoulder_roll_sensor_->getValue();

    ros_joints.name[16]     = "LElbowYaw";
    ros_joints.position[16] = wb_l_elbow_yaw_sensor_->getValue();

    ros_joints.name[17]     = "LElbowRoll";
    ros_joints.position[17] = wb_l_elbow_roll_sensor_->getValue();

    ros_joints.name[18]     = "LWristYaw";
    ros_joints.position[18] = 0.0;

    ros_joints.name[19]     = "LHand";
    ros_joints.position[19] = 0.0;

    // Right arm
    ros_joints.name[20]     = "RShoulderPitch";
    ros_joints.position[20] = wb_r_shoulder_pitch_sensor_->getValue();

    ros_joints.name[21]     = "RShoulderRoll";
    ros_joints.position[21] = wb_r_shoulder_roll_sensor_->getValue();

    ros_joints.name[22]     = "RElbowYaw";
    ros_joints.position[22] = wb_r_elbow_yaw_sensor_->getValue();

    ros_joints.name[23]     = "RElbowRoll";
    ros_joints.position[23] = wb_r_elbow_roll_sensor_->getValue();

    ros_joints.name[24]     = "RWristYaw";
    ros_joints.position[24] = 0.0;

    ros_joints.name[25]     = "RHand";
    ros_joints.position[25] = 0.0;

    // fill header
    ros_joints.header.stamp = time;
    joint_state_publisher_.publish(ros_joints);
}

void NaoController::publishIMU(ros::Time &time)
{
    sensor_msgs::Imu ros_imu;
    ros_imu.header.stamp = time;
    ros_imu.header.frame_id = "/ImuTorsoGyrometer_frame";

    // fill orientation
    const double* roll_pitch_yaw = wb_inertial_unit_->getRollPitchYaw();
    tf::Quaternion q;
    q.setRPY(roll_pitch_yaw[0], roll_pitch_yaw[1], roll_pitch_yaw[2]);
    ros_imu.orientation.x = q.x();
    ros_imu.orientation.y = q.y();
    ros_imu.orientation.z = q.z();
    ros_imu.orientation.w = q.w();
    //rosIMU.orientation = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    // fill gyro
    const double* gyro = wb_gyro_->getValues();
    ros_imu.angular_velocity.x = gyro[0];
    ros_imu.angular_velocity.y = gyro[1];
    ros_imu.angular_velocity.z = gyro[2];
    //rosIMU.angular_velocity_covariance = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    // fill accelerometer
    const double* acc = wb_accelerometer_->getValues();
    ros_imu.linear_acceleration.x = acc[0];
    ros_imu.linear_acceleration.y = acc[1];
    ros_imu.linear_acceleration.z = acc[2];
    //rosIMU.linear_acceleration = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    // publish sensors
    imu_publisher_.publish(ros_imu);
}

void NaoController::publishFSR(ros::Time &time)
{
    naoqi_bridge_msgs::FloatArrayStamped ros_fsr_l;
    ros_fsr_l.header.stamp = time;
    ros_fsr_l.header.frame_id = "/l_sole";

    naoqi_bridge_msgs::FloatArrayStamped ros_fsr_r;
    ros_fsr_r.header.stamp = time;
    ros_fsr_r.header.frame_id = "/r_sole";

    naoqi_bridge_msgs::FloatStamped ros_fsr_l_total;
    ros_fsr_l_total.header.stamp = time;
    ros_fsr_l_total.header.frame_id = "/l_sole";

    naoqi_bridge_msgs::FloatStamped ros_fsr_r_total;
    ros_fsr_r_total.header.stamp = time;
    ros_fsr_r_total.header.frame_id = "/r_sole";

    const double* l_fsr = wb_fsr_left_->getValues();
    const double* r_fsr = wb_fsr_right_->getValues();

    double l[4], r[4];
    // here we use the same equations as nao_demo.wrbt C code
    l[0] = l_fsr[2]/3.4 + 1.5*l_fsr[0] + 1.15*l_fsr[1]; // Left Foot Front Left
    l[1] = l_fsr[2]/3.4 + 1.5*l_fsr[0] - 1.15*l_fsr[1]; // Left Foot Front Right
    l[2] = l_fsr[2]/3.4 - 1.5*l_fsr[0] - 1.15*l_fsr[1]; // Left Foot Rear Right
    l[3] = l_fsr[2]/3.4 - 1.5*l_fsr[0] + 1.15*l_fsr[1]; // Left Foot Rear Left

    r[0] = r_fsr[2]/3.4 + 1.5*r_fsr[0] + 1.15*r_fsr[1]; // Right Foot Front Left
    r[1] = r_fsr[2]/3.4 + 1.5*r_fsr[0] - 1.15*r_fsr[1]; // Right Foot Front Right
    r[2] = r_fsr[2]/3.4 - 1.5*r_fsr[0] - 1.15*r_fsr[1]; // Right Foot Rear Right
    r[3] = r_fsr[2]/3.4 - 1.5*r_fsr[0] + 1.15*r_fsr[1]; // Right Foot Rear Left

    double l_total = 0;
    double r_total = 0;
    for(int i=0;i<4; i++)
    {
        l[i] = clamp(l[i], 0.0, 25.0);
        r[i] = clamp(r[i], 0.0, 25.0);
        l_total += l[i];
        r_total += r[i];
    }

    // fill left foot
    ros_fsr_l.data.push_back(l[0]);
    ros_fsr_l.data.push_back(l[1]);
    ros_fsr_l.data.push_back(l[2]);
    ros_fsr_l.data.push_back(l[3]);
    ros_fsr_l_total.data = l_total;

    // fill right foot
    ros_fsr_r.data.push_back(l[0]);
    ros_fsr_r.data.push_back(l[1]);
    ros_fsr_r.data.push_back(l[2]);
    ros_fsr_r.data.push_back(l[3]);
    ros_fsr_r_total.data = r_total;

    // publish
    fsr_l_publisher_.publish(ros_fsr_l);
    fsr_r_publisher_.publish(ros_fsr_r);
    fsr_l_total_publisher_.publish(ros_fsr_l_total);
    fsr_r_total_publisher_.publish(ros_fsr_r_total);
}


void NaoController::publishFSR2(ros::Time &time)
{
    std_msgs::Float64MultiArray ros_fsr;

    // fill left fsr data
    std_msgs::MultiArrayDimension lfsr_fl;     // left foot front left
    std_msgs::MultiArrayDimension lfsr_fr;     // left foot front right
    std_msgs::MultiArrayDimension lfsr_rl;     // left foot rear left
    std_msgs::MultiArrayDimension lfsr_rr;     // left foot rear right
    std_msgs::MultiArrayDimension lfsr_total;  // left foot total weight

    std_msgs::MultiArrayDimension rfsr_fl;     // right foot front left
    std_msgs::MultiArrayDimension rfsr_fr;     // right foot front right
    std_msgs::MultiArrayDimension rfsr_rl;     // right foot rear left
    std_msgs::MultiArrayDimension rfsr_rr;     // right foot rear right
    std_msgs::MultiArrayDimension rfsr_total;  // right foot total weight

    lfsr_fl.size = 1;
    lfsr_fl.stride = 1;
    lfsr_fl.label = "LFsrFL";
    lfsr_fr.size = 1;
    lfsr_fr.stride = 1;
    lfsr_fr.label = "LFsrFR";
    lfsr_rl.size = 1;
    lfsr_rl.stride = 1;
    lfsr_rl.label = "LFsrRL";
    lfsr_rr.size = 1;
    lfsr_rr.stride = 1;
    lfsr_rr.label = "LFsrRR";
    lfsr_total.size = 1;
    lfsr_total.stride = 1;
    lfsr_total.label = "LFsrTotal";

    rfsr_fl.size = 1;
    rfsr_fl.stride = 1;
    rfsr_fl.label = "RFsrFL";
    rfsr_fr.size = 1;
    rfsr_fr.stride = 1;
    rfsr_fr.label = "RFsrFR";
    rfsr_rl.size = 1;
    rfsr_rl.stride = 1;
    rfsr_rl.label = "RFsrRL";
    rfsr_rr.size = 1;
    rfsr_rr.stride = 1;
    rfsr_rr.label = "RFsrRR";
    rfsr_total.size = 1;
    rfsr_total.stride = 1;
    rfsr_total.label = "RFsrTotal";

    ros_fsr.layout.dim.push_back(lfsr_fl);
    ros_fsr.layout.dim.push_back(lfsr_fr);
    ros_fsr.layout.dim.push_back(lfsr_rl);
    ros_fsr.layout.dim.push_back(lfsr_rr);
    ros_fsr.layout.dim.push_back(lfsr_total);
    ros_fsr.layout.dim.push_back(rfsr_fl);
    ros_fsr.layout.dim.push_back(rfsr_fr);
    ros_fsr.layout.dim.push_back(rfsr_rl);
    ros_fsr.layout.dim.push_back(rfsr_rr);
    ros_fsr.layout.dim.push_back(rfsr_total);

    const double* l_fsr = wb_fsr_left_->getValues();
    const double* r_fsr = wb_fsr_right_->getValues();

    double l[4], r[4];
    // here we use the same equations as nao_demo.wrbt C code
    l[0] = l_fsr[2]/3.4 + 1.5*l_fsr[0] + 1.15*l_fsr[1]; // Left Foot Front Left
    l[1] = l_fsr[2]/3.4 + 1.5*l_fsr[0] - 1.15*l_fsr[1]; // Left Foot Front Right
    l[2] = l_fsr[2]/3.4 - 1.5*l_fsr[0] - 1.15*l_fsr[1]; // Left Foot Rear Right
    l[3] = l_fsr[2]/3.4 - 1.5*l_fsr[0] + 1.15*l_fsr[1]; // Left Foot Rear Left

    r[0] = r_fsr[2]/3.4 + 1.5*r_fsr[0] + 1.15*r_fsr[1]; // Right Foot Front Left
    r[1] = r_fsr[2]/3.4 + 1.5*r_fsr[0] - 1.15*r_fsr[1]; // Right Foot Front Right
    r[2] = r_fsr[2]/3.4 - 1.5*r_fsr[0] - 1.15*r_fsr[1]; // Right Foot Rear Right
    r[3] = r_fsr[2]/3.4 - 1.5*r_fsr[0] + 1.15*r_fsr[1]; // Right Foot Rear Left

    double l_total = 0;
    double r_total = 0;
    for(int i=0;i<4; i++)
    {
        l[i] = clamp(l[i], 0.0, 25.0);
        r[i] = clamp(r[i], 0.0, 25.0);
        l_total += l[i];
        r_total += r[i];
    }

    ros_fsr.data.push_back(l[0]);
    ros_fsr.data.push_back(l[1]);
    ros_fsr.data.push_back(l[2]);
    ros_fsr.data.push_back(l[3]);
    ros_fsr.data.push_back(l_total);
    ros_fsr.data.push_back(r[0]);
    ros_fsr.data.push_back(r[1]);
    ros_fsr.data.push_back(r[2]);
    ros_fsr.data.push_back(r[3]);
    ros_fsr.data.push_back(r_total);

    fsr_publisher_.publish(ros_fsr);
}

void NaoController::publishSonar(ros::Time &time, webots::DistanceSensor *webots_sonar, ros::Publisher& sonar_publisher, const std::string &frame_id)
{
    sensor_msgs::Range ros_range;
    ros_range.header.stamp = time;
    ros_range.header.frame_id = frame_id;
    ros_range.min_range = webots_sonar->getMinValue();
    ros_range.max_range = webots_sonar->getMaxValue();
    ros_range.field_of_view = webots_sonar->getAperture();
    ros_range.radiation_type = webots_sonar->getType();
    ros_range.range = webots_sonar->getValue();

    sonar_publisher.publish(ros_range);
}

void NaoController::publishBumper(ros::Time &time, webots::TouchSensor *webots_lfoot_bumper_right, webots::TouchSensor *webots_lfoot_bumper_left, ros::Publisher& bumper_publisher, const std::string &frame_id, const int bumper)
{
    naoqi_bridge_msgs::Bumper ros_bumper;
    ros_bumper.header.stamp = time;
    ros_bumper.header.frame_id = frame_id;
    ros_bumper.bumper = bumper;
    double state = webots_lfoot_bumper_right->getValue() || webots_lfoot_bumper_left->getValue();
    ros_bumper.state = state;
    bumper_publisher.publish(ros_bumper);
}


void NaoController::callbackJoy(const sensor_msgs::Joy::ConstPtr& joy)
{
    simulationStep();
}

void NaoController::initWebotsDevices()
{    
    wb_camera_top_              = getCamera("CameraTop");
    wb_camera_bottom_           = getCamera("CameraBottom");
    wb_accelerometer_           = getAccelerometer("accelerometer");
    wb_gyro_                    = getGyro("gyro");
    wb_gps_                     = getGPS("gps");
    wb_inertial_unit_           = getInertialUnit("inertial unit");
    wb_sonar_left_              = getDistanceSensor("Sonar/Left");
    wb_sonar_right_             = getDistanceSensor("Sonar/Right");
    wb_fsr_left_                = getTouchSensor("LFsr");
    wb_fsr_right_               = getTouchSensor("RFsr");
    wb_lfoot_bumper_right_      = getTouchSensor("LFoot/Bumper/Left");
    wb_lfoot_bumper_left_       = getTouchSensor("LFoot/Bumper/Right");
    wb_rfoot_bumper_right_      = getTouchSensor("RFoot/Bumper/Left");
    wb_rfoot_bumper_left_       = getTouchSensor("RFoot/Bumper/Right");
    wb_chest_led_               = getLED("ChestBoard/Led");
    wb_rfoot_led_               = getLED("RFoot/Led");
    wb_lfoot_led_               = getLED("LFoot/Led");
    wb_reye_led_                = getLED("Face/Led/Right");
    wb_leye_led_                = getLED("Face/Led/Left");
    wb_rear_led_                = getLED("Ears/Led/Right");
    wb_lear_led_                = getLED("Ears/Led/Left");
    // wb_lear_speaker_            = getSpeaker("Ears/Speaker/Left");

    wb_head_yaw_sensor_         = getPositionSensor("HeadYawS");
    wb_head_pitch_sensor_       = getPositionSensor("HeadPitchS");
    
    wb_r_shoulder_pitch_sensor_ = getPositionSensor("RShoulderPitchS");
    wb_r_shoulder_roll_sensor_  = getPositionSensor("RShoulderRollS");
    wb_r_elbow_yaw_sensor_      = getPositionSensor("RElbowYawS");
    wb_r_elbow_roll_sensor_     = getPositionSensor("RElbowRollS");
    
    wb_l_shoulder_pitch_sensor_ = getPositionSensor("LShoulderPitchS");
    wb_l_shoulder_roll_sensor_  = getPositionSensor("LShoulderRollS");
    wb_l_elbow_yaw_sensor_      = getPositionSensor("LElbowYawS");
    wb_l_elbow_roll_sensor_     = getPositionSensor("LElbowRollS");
    
    wb_r_hip_yaw_pitch_sensor_  = getPositionSensor("RHipYawPitchS");
    wb_r_hip_roll_sensor_       = getPositionSensor("RHipRollS");
    wb_r_hip_pitch_sensor_      = getPositionSensor("RHipPitchS");
    wb_r_knee_pitch_sensor_     = getPositionSensor("RKneePitchS");
    wb_r_ankle_pitch_sensor_    = getPositionSensor("RAnklePitchS");
    wb_r_ankle_roll_sensor_     = getPositionSensor("RAnkleRollS");
    
    wb_l_hip_yaw_pitch_sensor_  = getPositionSensor("LHipYawPitchS");
    wb_l_hip_roll_sensor_       = getPositionSensor("LHipRollS");
    wb_l_hip_pitch_sensor_      = getPositionSensor("LHipPitchS");
    wb_l_knee_pitch_sensor_     = getPositionSensor("LKneePitchS");
    wb_l_ankle_pitch_sensor_    = getPositionSensor("LAnklePitchS");
    wb_l_ankle_roll_sensor_     = getPositionSensor("LAnkleRollS");
    wb_keyboard_                = getKeyboard();

    // enable devices
    wb_camera_top_->enable(time_step_);
    wb_camera_bottom_->enable(time_step_);
    wb_accelerometer_->enable(time_step_);
    wb_gyro_->enable(time_step_);
    wb_gps_->enable(time_step_);
    wb_inertial_unit_->enable(time_step_);
    wb_sonar_left_->enable(time_step_);
    wb_sonar_right_->enable(time_step_);
    wb_fsr_left_->enable(time_step_);
    wb_fsr_right_->enable(time_step_);
    wb_lfoot_bumper_right_->enable(time_step_);
    wb_lfoot_bumper_left_->enable(time_step_);
    wb_rfoot_bumper_right_->enable(time_step_);
    wb_rfoot_bumper_left_->enable(time_step_);
    // wb_chest_led_->enable(time_step_);
    // wb_rfoot_led_->enable(time_step_);
    // wb_lfoot_led_->enable(time_step_);
    // wb_reye_led_->enable(time_step_);
    // wb_leye_led_->enable(time_step_);
    // wb_rear_led_->enable(time_step_);
    // wb_lear_led_->enable(time_step_);
    wb_head_yaw_sensor_->enable(time_step_);
    wb_head_pitch_sensor_->enable(time_step_);
    wb_r_shoulder_pitch_sensor_->enable(time_step_);
    wb_r_shoulder_roll_sensor_->enable(time_step_);
    wb_r_elbow_yaw_sensor_->enable(time_step_);
    wb_r_elbow_roll_sensor_->enable(time_step_);
    wb_l_shoulder_pitch_sensor_->enable(time_step_);
    wb_l_shoulder_roll_sensor_->enable(time_step_);
    wb_l_elbow_yaw_sensor_->enable(time_step_);
    wb_l_elbow_roll_sensor_->enable(time_step_);
    wb_r_hip_yaw_pitch_sensor_->enable(time_step_);
    wb_r_hip_roll_sensor_->enable(time_step_);
    wb_r_hip_pitch_sensor_->enable(time_step_);
    wb_r_knee_pitch_sensor_->enable(time_step_);
    wb_r_ankle_pitch_sensor_->enable(time_step_);
    wb_r_ankle_roll_sensor_->enable(time_step_);
    wb_l_hip_yaw_pitch_sensor_->enable(time_step_);
    wb_l_hip_roll_sensor_->enable(time_step_);
    wb_l_hip_pitch_sensor_->enable(time_step_);
    wb_l_knee_pitch_sensor_->enable(time_step_);
    wb_l_ankle_pitch_sensor_->enable(time_step_);
    wb_l_ankle_roll_sensor_->enable(time_step_);
    wb_keyboard_->enable(time_step_);
}

void NaoController::startMotion(webots::Motion *motion)
{
    if(wb_motion_current_)
        wb_motion_current_->stop();

    wb_motion_current_ = motion;
    wb_motion_current_->play();
}


void NaoController::loadMotionFiles()
{
    // Gestures
    wb_motion_hand_wave_       = new webots::Motion(wb_file_motion_hand_wave_);
    wb_motion_standup_front_   = new webots::Motion(wb_file_motion_standup_front_);
    wb_motion_taichi_          = new webots::Motion(wb_file_motion_taichi_);
    // Walking
    wb_motion_forward_         = new webots::Motion(wb_file_motion_forward_);
    wb_motion_backward_        = new webots::Motion(wb_file_motion_backward_);
    wb_motion_side_step_left_  = new webots::Motion(wb_file_motion_side_step_left_);
    wb_motion_side_step_right_ = new webots::Motion(wb_file_motion_side_step_right_);
    wb_motion_turn_left_       = new webots::Motion(wb_file_motion_turn_left_);
    wb_motion_turn_right_      = new webots::Motion(wb_file_motion_turn_right_);
    // Speaking
    wb_motion_BodyTalk_1_      = new webots::Motion(wb_file_motion_BodyTalk_1_);
    wb_motion_BodyTalk_2_      = new webots::Motion(wb_file_motion_BodyTalk_2_);
    wb_motion_BodyTalk_3_      = new webots::Motion(wb_file_motion_BodyTalk_3_);
    wb_motion_BodyTalk_4_      = new webots::Motion(wb_file_motion_BodyTalk_4_);
    wb_motion_BodyTalk_5_      = new webots::Motion(wb_file_motion_BodyTalk_5_);
    wb_motion_BodyTalk_6_      = new webots::Motion(wb_file_motion_BodyTalk_6_);
    wb_motion_BodyTalk_7_      = new webots::Motion(wb_file_motion_BodyTalk_7_);
    wb_motion_BodyTalk_8_      = new webots::Motion(wb_file_motion_BodyTalk_8_);
    wb_motion_BodyTalk_9_      = new webots::Motion(wb_file_motion_BodyTalk_9_);
    wb_motion_BodyTalk_10_     = new webots::Motion(wb_file_motion_BodyTalk_10_);
    wb_motion_BodyTalk_11_     = new webots::Motion(wb_file_motion_BodyTalk_11_);
    wb_motion_BodyTalk_12_     = new webots::Motion(wb_file_motion_BodyTalk_12_);
    wb_motion_BodyTalk_13_     = new webots::Motion(wb_file_motion_BodyTalk_13_);
    wb_motion_BodyTalk_14_     = new webots::Motion(wb_file_motion_BodyTalk_14_);
    wb_motion_BodyTalk_15_     = new webots::Motion(wb_file_motion_BodyTalk_15_);
    wb_motion_BodyTalk_16_     = new webots::Motion(wb_file_motion_BodyTalk_16_);
    // Listening
    wb_motion_Listening_1_     = new webots::Motion(wb_file_motion_Listening_1_);
    wb_motion_Listening_2_     = new webots::Motion(wb_file_motion_Listening_2_);
    wb_motion_Listening_3_     = new webots::Motion(wb_file_motion_Listening_3_);
    wb_motion_Listening_4_     = new webots::Motion(wb_file_motion_Listening_4_);
    wb_motion_Listening_5_     = new webots::Motion(wb_file_motion_Listening_5_);
    wb_motion_Listening_6_     = new webots::Motion(wb_file_motion_Listening_6_);
    wb_motion_Listening_7_     = new webots::Motion(wb_file_motion_Listening_7_);
    // Thinking
    wb_motion_Remember_1_      = new webots::Motion(wb_file_motion_Remember_1_);
    wb_motion_Remember_2_      = new webots::Motion(wb_file_motion_Remember_2_);
    wb_motion_Remember_3_      = new webots::Motion(wb_file_motion_Remember_3_);
    wb_motion_ThinkingLoop_1_  = new webots::Motion(wb_file_motion_ThinkingLoop_1_);
    wb_motion_ThinkingLoop_2_  = new webots::Motion(wb_file_motion_ThinkingLoop_2_);
    
    // Map: Gestures
    map_stand_gesture_["HandWave"] = wb_motion_hand_wave_;
    map_stand_gesture_["StandUpFromFront"] = wb_motion_standup_front_;
    map_stand_gesture_["TaiChi"] = wb_motion_taichi_;

    // Map: Speaking
    map_stand_speaking_["BodyTalk_1"] = wb_motion_BodyTalk_1_;
    map_stand_speaking_["BodyTalk_2"] = wb_motion_BodyTalk_2_;
    map_stand_speaking_["BodyTalk_3"] = wb_motion_BodyTalk_3_;
    map_stand_speaking_["BodyTalk_4"] = wb_motion_BodyTalk_4_;
    map_stand_speaking_["BodyTalk_5"] = wb_motion_BodyTalk_5_;
    map_stand_speaking_["BodyTalk_6"] = wb_motion_BodyTalk_6_;
    map_stand_speaking_["BodyTalk_7"] = wb_motion_BodyTalk_7_;
    map_stand_speaking_["BodyTalk_8"] = wb_motion_BodyTalk_8_;
    map_stand_speaking_["BodyTalk_9"] = wb_motion_BodyTalk_9_;
    map_stand_speaking_["BodyTalk_10"] = wb_motion_BodyTalk_10_;
    map_stand_speaking_["BodyTalk_11"] = wb_motion_BodyTalk_11_;
    map_stand_speaking_["BodyTalk_12"] = wb_motion_BodyTalk_12_;
    map_stand_speaking_["BodyTalk_13"] = wb_motion_BodyTalk_13_;
    map_stand_speaking_["BodyTalk_14"] = wb_motion_BodyTalk_14_;
    map_stand_speaking_["BodyTalk_15"] = wb_motion_BodyTalk_15_;
    map_stand_speaking_["BodyTalk_16"] = wb_motion_BodyTalk_16_;
    // Map: Listening
    map_stand_listening_["Listening_1"] = wb_motion_Listening_1_;
    map_stand_listening_["Listening_2"] = wb_motion_Listening_2_;
    map_stand_listening_["Listening_3"] = wb_motion_Listening_3_;
    map_stand_listening_["Listening_4"] = wb_motion_Listening_4_;
    map_stand_listening_["Listening_5"] = wb_motion_Listening_5_;
    map_stand_listening_["Listening_6"] = wb_motion_Listening_6_;
    map_stand_listening_["Listening_7"] = wb_motion_Listening_7_;
    // Map: Thinking
    map_stand_thinking_["Remember_1"] = wb_motion_Remember_1_;
    map_stand_thinking_["Remember_2"] = wb_motion_Remember_2_;
    map_stand_thinking_["Remember_3"] = wb_motion_Remember_3_;
    map_stand_thinking_["ThinkingLoop_1"] = wb_motion_ThinkingLoop_1_;
    map_stand_thinking_["ThinkingLoop_2"] = wb_motion_ThinkingLoop_2_;


    wb_motion_current_ = NULL;
}

double NaoController::clamp(double value, double min, double max)
{
    if (min > max)
    {
        assert(0);
        return value;
    }
    return value < min ? min : value > max ? max : value;
}

} //nao_webots

#endif // NAOCONTROLLER_CPP
