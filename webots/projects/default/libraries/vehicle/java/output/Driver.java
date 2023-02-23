/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.cyberbotics.webots.controller.vehicle;

import com.cyberbotics.webots.controller.Supervisor;

public class Driver extends Supervisor {
  private transient long swigCPtr;

  protected Driver(long cPtr, boolean cMemoryOwn) {
    super(vehicleJNI.Driver_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Driver obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        vehicleJNI.delete_Driver(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static boolean isInitialisationPossible() {
    return vehicleJNI.Driver_isInitialisationPossible();
  }

  public Driver() {
    this(vehicleJNI.new_Driver(), true);
  }

  public static Driver getDriverInstance() {
    long cPtr = vehicleJNI.Driver_getDriverInstance();
    return (cPtr == 0) ? null : new Driver(cPtr, false);
  }

  public int step() {
    return vehicleJNI.Driver_step(swigCPtr, this);
  }

  public void setSteeringAngle(double steeringAngle) {
    vehicleJNI.Driver_setSteeringAngle(swigCPtr, this, steeringAngle);
  }

  public double getSteeringAngle() {
    return vehicleJNI.Driver_getSteeringAngle(swigCPtr, this);
  }

  public void setCruisingSpeed(double speed) {
    vehicleJNI.Driver_setCruisingSpeed(swigCPtr, this, speed);
  }

  public double getTargetCruisingSpeed() {
    return vehicleJNI.Driver_getTargetCruisingSpeed(swigCPtr, this);
  }

  public double getCurrentSpeed() {
    return vehicleJNI.Driver_getCurrentSpeed(swigCPtr, this);
  }

  public void setThrottle(double throttle) {
    vehicleJNI.Driver_setThrottle(swigCPtr, this, throttle);
  }

  public double getThrottle() {
    return vehicleJNI.Driver_getThrottle(swigCPtr, this);
  }

  public void setBrakeIntensity(double intensity) {
    vehicleJNI.Driver_setBrakeIntensity(swigCPtr, this, intensity);
  }

  public double getBrakeIntensity() {
    return vehicleJNI.Driver_getBrakeIntensity(swigCPtr, this);
  }

  public void setIndicator(int state) {
    vehicleJNI.Driver_setIndicator(swigCPtr, this, state);
  }

  public void setHazardFlashers(boolean state) {
    vehicleJNI.Driver_setHazardFlashers(swigCPtr, this, state);
  }

  public int getIndicator() {
    return vehicleJNI.Driver_getIndicator(swigCPtr, this);
  }

  public boolean getHazardFlashers() {
    return vehicleJNI.Driver_getHazardFlashers(swigCPtr, this);
  }

  public void setDippedBeams(boolean state) {
    vehicleJNI.Driver_setDippedBeams(swigCPtr, this, state);
  }

  public void setAntifogLights(boolean state) {
    vehicleJNI.Driver_setAntifogLights(swigCPtr, this, state);
  }

  public boolean getDippedBeams() {
    return vehicleJNI.Driver_getDippedBeams(swigCPtr, this);
  }

  public boolean getAntifogLights() {
    return vehicleJNI.Driver_getAntifogLights(swigCPtr, this);
  }

  public double getRpm() {
    return vehicleJNI.Driver_getRpm(swigCPtr, this);
  }

  public int getGear() {
    return vehicleJNI.Driver_getGear(swigCPtr, this);
  }

  public void setGear(int gear) {
    vehicleJNI.Driver_setGear(swigCPtr, this, gear);
  }

  public int getGearNumber() {
    return vehicleJNI.Driver_getGearNumber(swigCPtr, this);
  }

  public int getControlMode() {
    return vehicleJNI.Driver_getControlMode(swigCPtr, this);
  }

  public void setWiperMode(int mode) {
    vehicleJNI.Driver_setWiperMode(swigCPtr, this, mode);
  }

  public int getWiperMode() {
    return vehicleJNI.Driver_getWiperMode(swigCPtr, this);
  }

  public void setBrake(double brake) {
    vehicleJNI.Driver_setBrake(swigCPtr, this, brake);
  }

  public void setWipersMode(int mode) {
    vehicleJNI.Driver_setWipersMode(swigCPtr, this, mode);
  }

  public int getWipersMode() {
    return vehicleJNI.Driver_getWipersMode(swigCPtr, this);
  }

  // IndicatorState 
  public final static int INDICATOR_OFF = 0;
  public final static int INDICATOR_RIGHT = INDICATOR_OFF + 1;
  public final static int INDICATOR_LEFT = INDICATOR_RIGHT + 1;

  // ControlMode 
  public final static int SPEED = 0;
  public final static int TORQUE = SPEED + 1;

  // WiperMode 
  public final static int DOWN = 0;
  public final static int SLOW = DOWN + 1;
  public final static int NORMAL = SLOW + 1;
  public final static int FAST = NORMAL + 1;

}
