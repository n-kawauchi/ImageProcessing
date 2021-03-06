﻿// -*- C++ -*-
/*!
 * @file  OpenCVCamera.h
 * @brief USB Camera Acquire component
 * @date  $Date$
 *
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 */

#ifndef OPENCVCAMERA_H
#define OPENCVCAMERA_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include "CaptureCameraControl.h"

#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define FRAME_RATE 30

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "InterfaceDataTypesStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class OpenCVCamera
 * @brief USB Camera Acquire component
 *
 */
class OpenCVCamera
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  OpenCVCamera(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~OpenCVCamera();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  capture_mode
   * - DefaultValue: camera
   */
  std::string m_capture_mode;
  /*!
   * 
   * - Name:  device_num
   * - DefaultValue: 0
   */
  int m_device_num;
  /*!
   * 
   * - Name:  video_file
   * - DefaultValue: video.mp4
   */
  std::string m_video_file;
  /*!
   * 
   * - Name:  URL
   * - DefaultValue:  
   */
  std::string m_URL;
  /*!
   * 
   * - Name:  frame_width
   * - DefaultValue: 640
   */
  int m_frame_width;
  /*!
   * 
   * - Name:  frame_height
   * - DefaultValue: 480
   */
  int m_frame_height;
  /*!
   * 
   * - Name:  frame_rate
   * - DefaultValue: 30
   */
  int m_frame_rate;
  /*!
   * 
   * - Name:  brightness
   * - DefaultValue: 128
   */
  int m_brightness;
  /*!
   * 
   * - Name:  contrast
   * - DefaultValue: 32
   */
  int m_contrast;
  /*!
   * 
   * - Name:  saturation
   * - DefaultValue: 32
   */
  int m_saturation;
  /*!
   * 
   * - Name:  hue
   * - DefaultValue: 0
   */
  int m_hue;
  /*!
   * 
   * - Name:  gain
   * - DefaultValue: 64
   */
  int m_gain;
  /*!
   * 
   * - Name:  exposure_mode
   * - DefaultValue: auto
   */
  std::string m_exposure_mode;
  /*!
   * 
   * - Name:  exposure_absolute
   * - DefaultValue: 166
   */
  int m_exposure_absolute;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::CameraImage m_out;
  /*!
   */
  RTC::OutPort<RTC::CameraImage> m_outOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>
  cv::VideoCapture      m_capture;
  CaptureCameraControl* m_CamCtl;
  CONFIG_PRM            m_config_prm;
  
  bool check_config_parameters();
  void copy_config_camera_property(std::string target);
  void get_real_camera_property();
  int  get_exposure_mode_menu_number(std::string config_val);
  
  int m_current_device_num;
  std::string m_current_video_file;
  std::string m_current_URL;
  int m_current_frame_width;
  int m_current_frame_height;
  int m_current_frame_rate;
  
  int m_currentBrightness;
  int m_currentContrast;
  int m_currentSaturation;
  int m_currentHue;
  int m_currentGain;
  int m_currentExposureMode;
  int m_currentExposure;
  
  int m_real_camera_Brightness;
  int m_real_camera_Contrast;
  int m_real_camera_Saturation;
  int m_real_camera_Hue;
  int m_real_camera_Gain;
  int m_real_camera_ExposureMode;
  int m_real_camera_Exposure;
    
  
  int dummy;
};


extern "C"
{
  DLL_EXPORT void OpenCVCameraInit(RTC::Manager* manager);
};

#endif // OPENCVCAMERA_H
