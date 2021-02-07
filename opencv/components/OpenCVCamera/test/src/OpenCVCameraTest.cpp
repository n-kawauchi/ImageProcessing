// -*- C++ -*-
/*!
 * @file  OpenCVCameraTest.cpp
 * @brief USB Camera Acquire component
 * @date $Date$
 *
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 */

#include "OpenCVCameraTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* opencvcamera_spec[] =
  {
    "implementation_id", "OpenCVCameraTest",
    "type_name",         "OpenCVCameraTest",
    "description",       "USB Camera Acquire component",
    "version",           "1.2.3",
    "vendor",            "AIST",
    "category",          "opencv-rtcs",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.device_num", "0",
    "conf.default.frame_width", "640",
    "conf.default.frame_height", "480",
    "conf.default.frame_rate", "30",
    "conf.default.brightness", "128",
    "conf.default.contrast", "32",
    "conf.default.saturation", "32",
    "conf.default.hue", "0.2",
    "conf.default.gain", "0.5",
    "conf.default.exposure", "0.5",
    "conf.default.auto_exposure", "0.25",
    "conf.default.video_file", "video.mp4",
    "conf.default.capture_mode", "0",

    // Widget
    "conf.__widget__.device_num", "text",
    "conf.__widget__.frame_width", "text",
    "conf.__widget__.frame_height", "text",
    "conf.__widget__.frame_rate", "text",
    "conf.__widget__.brightness", "text",
    "conf.__widget__.contrast", "text",
    "conf.__widget__.saturation", "text",
    "conf.__widget__.hue", "slider.0.01",
    "conf.__widget__.gain", "slider.0.01",
    "conf.__widget__.exposure", "slider.0.01",
    "conf.__widget__.auto_exposure", "slider.0.01",
    "conf.__widget__.video_file", "text",
    "conf.__widget__.capture_mode", "radio",
    // Constraints
    "conf.__constraints__.hue", "0.0<=x<=1.0",
    "conf.__constraints__.gain", "0.0<=x<=1.0",
    "conf.__constraints__.exposure", "0.0<=x<=1.0",
    "conf.__constraints__.auto_exposure", "0.0<=x<=1.0",
    "conf.__constraints__.capture_mode", "(0,1)",

    "conf.__type__.device_num", "int",
    "conf.__type__.frame_width", "int",
    "conf.__type__.frame_height", "int",
    "conf.__type__.frame_rate", "int",
    "conf.__type__.brightness", "int",
    "conf.__type__.contrast", "int",
    "conf.__type__.saturation", "int",
    "conf.__type__.hue", "double",
    "conf.__type__.gain", "double",
    "conf.__type__.exposure", "double",
    "conf.__type__.auto_exposure", "double",
    "conf.__type__.video_file", "string",
    "conf.__type__.capture_mode", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
OpenCVCameraTest::OpenCVCameraTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
OpenCVCameraTest::~OpenCVCameraTest()
{
}



RTC::ReturnCode_t OpenCVCameraTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("out", m_outIn);

  // Set OutPort buffer

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("device_num", m_device_num, "0");
  bindParameter("frame_width", m_frame_width, "640");
  bindParameter("frame_height", m_frame_height, "480");
  bindParameter("frame_rate", m_frame_rate, "30");
  bindParameter("brightness", m_brightness, "128");
  bindParameter("contrast", m_contrast, "32");
  bindParameter("saturation", m_saturation, "32");
  bindParameter("hue", m_hue, "0.2");
  bindParameter("gain", m_gain, "0.5");
  bindParameter("exposure", m_exposure, "0.5");
  bindParameter("auto_exposure", m_auto_exposure, "0.25");
  bindParameter("video_file", m_video_file, "video.mp4");
  bindParameter("capture_mode", m_capture_mode, "0");
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OpenCVCameraTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCameraTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCameraTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t OpenCVCameraTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t OpenCVCameraTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t OpenCVCameraTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OpenCVCameraTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCameraTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCameraTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCameraTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCameraTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void OpenCVCameraTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(opencvcamera_spec);
    manager->registerFactory(profile,
                             RTC::Create<OpenCVCameraTest>,
                             RTC::Delete<OpenCVCameraTest>);
  }

};


