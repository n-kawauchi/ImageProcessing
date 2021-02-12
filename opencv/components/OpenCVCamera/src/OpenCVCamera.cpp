// -*- C++ -*-
/*!
 * @file  OpenCVCamera.cpp
 * @brief USB Camera Acquire component
 * @date $Date$
 *
 * $Id$
 */

#include "OpenCVCamera.h"
#include <chrono>
#include <iostream>

// Module specification
// <rtc-template block="module_spec">
static const char* opencvcamera_spec[] =
  {
    "implementation_id", "OpenCVCamera",
    "type_name",         "OpenCVCamera",
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
    "conf.default.hue", "0",
    "conf.default.gain", "64",
    "conf.default.auto_exposure", "3",
    "conf.default.exposure", "166",
    "conf.default.video_file", "video.mp4",
    "conf.default.capture_mode", "0",

    // Widget
    "conf.__widget__.device_num", "text",
    "conf.__widget__.frame_width", "text",
    "conf.__widget__.frame_height", "text",
    "conf.__widget__.frame_rate", "text",
    "conf.__widget__.brightness", "slider.1",
    "conf.__widget__.contrast", "slider.1",
    "conf.__widget__.saturation", "slider.1",
    "conf.__widget__.hue", "slider.1",
    "conf.__widget__.gain", "slider.1",    
    "conf.__widget__.auto_exposure", "radio",
    "conf.__widget__.exposure", "slider.1",
    "conf.__widget__.video_file", "text",
    "conf.__widget__.capture_mode", "radio",
    // Constraints
    "conf.__constraints__.brightness", "0<=x<=255",
    "conf.__constraints__.contrast", "0<=x<=255",
    "conf.__constraints__.saturation", "0<=x<=255",
    "conf.__constraints__.hue", "-180<=x<=180",
    "conf.__constraints__.gain", "0<=x<=255",   
    "conf.__constraints__.auto_exposure", "(1,3)",
    "conf.__constraints__.exposure", "1<=x<=100000",
    "conf.__constraints__.capture_mode", "(0,1)",

    "conf.__type__.device_num", "int",
    "conf.__type__.frame_width", "int",
    "conf.__type__.frame_height", "int",
    "conf.__type__.frame_rate", "int",
    "conf.__type__.brightness", "int",
    "conf.__type__.contrast", "int",
    "conf.__type__.saturation", "int",
    "conf.__type__.hue", "int",
    "conf.__type__.gain", "int",   
    "conf.__type__.auto_exposure", "int",
    "conf.__type__.exposure", "int",
    "conf.__type__.video_file", "string",
    "conf.__type__.capture_mode", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
OpenCVCamera::OpenCVCamera(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out),

    // </rtc-template>
    m_currentBrightness(128),
    m_currentContrast(32),
    m_currentSaturation(32),
    m_currentHue(0),
    m_currentGain(64),    
    m_currentAutoExposure(3),
    m_currentExposure(166),  
    dummy(0)
{
}

/*!
 * @brief destructor
 */
OpenCVCamera::~OpenCVCamera()
{
}



RTC::ReturnCode_t OpenCVCamera::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers

  // Set OutPort buffer
  addOutPort("out", m_outOut);

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
  bindParameter("hue", m_hue, "0");
  bindParameter("gain", m_gain, "64");
  bindParameter("exposure", m_exposure, "166");
  bindParameter("auto_exposure", m_auto_exposure, "3");
  bindParameter("video_file", m_video_file, "video.mp4");
  bindParameter("capture_mode", m_capture_mode, "0");
  // </rtc-template>
 
  m_device_id = -1;
  

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OpenCVCamera::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCamera::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCamera::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t OpenCVCamera::onActivated(RTC::UniqueId ec_id)
{
  using std::cout;
  using std::endl;
  m_CamCtl = new CaptureCameraControl(&m_capture);

  if (m_capture_mode == 0) // Camera Mode
  {
    copy_config_camera_property("all");
    
    m_device_id = m_device_num;
    if (m_CamCtl->open_camera(&m_config_prm))
    {
      cout << "Camera device opened." << endl;
      RTC_TRACE(("*** onActivated: Camera device opened. "));
    }
    else
    {
      return RTC::RTC_ERROR;
    }
    
    m_current_frame_width = m_frame_width;
    m_current_frame_height = m_frame_height;
    m_current_frame_rate = m_frame_rate;
    m_current_video_file = m_video_file;
    
    get_real_camera_property();
  }
  else
  {
    m_capture.open(m_video_file);
    cout << "CAP_FPS: " << m_capture.get(CAP_PROP_FPS) << endl;
    double fps = m_capture.get(CAP_PROP_FPS);
    if (!m_capture.isOpened())
    {
      cout << "No Video File" << endl;
      return RTC::RTC_ERROR;
    }
  }
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t OpenCVCamera::onDeactivated(RTC::UniqueId ec_id)
{
  delete m_CamCtl;
  m_capture.release();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t OpenCVCamera::onExecute(RTC::UniqueId ec_id)
{
  using std::cout;
  using std::endl;
  static auto tmOld = std::chrono::system_clock::now();
  static int count = 0;
  const int DISPLAY_PERIOD_FRAME_NUM = 100;
  cv::Mat cam_frame;

  if (!check_config_parameters())
  {
    return RTC::RTC_ERROR;
  }
  try
  {
    if (!m_capture.read(cam_frame))
    {
      if (m_capture_mode == 0)
      {
        cout << "Bad frame or no frame!!" << endl;
        return RTC::RTC_ERROR;
      }
      else
      {
        std::cout << "Frame End" << std::endl;
        // m_capture.set(CV_CAP_PROP_FRAME_COUNT, 0.0);
        // return RTC::RTC_OK;
        m_capture.release(); // 
        m_capture.open(m_video_file);

        if (!m_capture.isOpened())
        {
          cout << "No Video File" << endl;
          return RTC::RTC_ERROR;
        }
        return RTC::RTC_OK;
      }
    }
  }
  catch (...)
  {
    std::cout << "Exception" << std::endl;
    if (m_capture_mode == 0)
    {
      std::cout << "Frame End (exception)" << std::endl;
      m_capture.release(); // set(CV_CAP_PROP_FRAME_COUNT, 0.0);
      m_capture.open(m_video_file);

      if (!m_capture.isOpened())
      {
        cout << "No Video File" << endl;
        return RTC::RTC_ERROR;
      }
    }
  }
  
  cv::Mat frame;
  frame = cam_frame;
  
  int len = frame.channels() * frame.size().width * frame.size().height;
  m_out.pixels.length(len);
  m_out.width = frame.size().width;
  m_out.height = frame.size().height;

  memcpy((void *)&(m_out.pixels[0]), frame.data, len);

  m_outOut.write();

  if (count++ > DISPLAY_PERIOD_FRAME_NUM)
  {
    auto tmNow = std::chrono::system_clock::now();
    double sec(std::chrono::duration<double>(tmNow - tmOld).count());

    if (sec > 1.0)
    {
      cout << (DISPLAY_PERIOD_FRAME_NUM / sec) << " [FPS]" << endl;
      tmOld = tmNow;
    }
    count = 0;
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OpenCVCamera::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCamera::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCamera::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCamera::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t OpenCVCamera::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

bool OpenCVCamera::check_config_parameters()
{
  using std::cout;
  using std::endl;

  if (m_capture_mode == 0)
  {
    if (m_device_num != m_device_id)
    {
      copy_config_camera_property("basic");
      m_device_id = m_device_num;
      
      if (m_CamCtl->open_camera(&m_config_prm))
      {
        cout << "Changed camera device opened." << endl;
        RTC_TRACE(("*** onExecute: Changed camera device opened. "));
      }
      else
      {
        return false;
      }
      get_real_camera_property();
    }
  }
  else
  {
    if (m_current_video_file != m_video_file)
    {
      m_current_video_file = m_video_file;
      m_capture.open(m_video_file);

      if (!m_capture.isOpened())
      {
        cout << "No Video File" << endl;
        return false;
      }
    }
  }

  if (m_current_frame_width != m_frame_width &&
          m_current_frame_height != m_frame_height)
  {
    copy_config_camera_property("frame_width");
    copy_config_camera_property("frame_height");
    m_current_frame_width = m_frame_width;
    m_current_frame_height = m_frame_height;
    
    m_CamCtl->set_camera_property("frame_width", m_frame_width, CAP_PROP_FRAME_WIDTH);    
    m_CamCtl->set_camera_property("frame_height", m_frame_height, CAP_PROP_FRAME_HEIGHT);    
  }
  
  if (m_current_frame_rate != m_frame_rate)
  {
    copy_config_camera_property("frame_rate");
    m_current_frame_rate = m_frame_rate;
    m_CamCtl->set_camera_property("frame_rate", m_frame_rate, CAP_PROP_FPS);    
  }
  
  if (m_currentBrightness != m_brightness)
  {
    copy_config_camera_property("brightness");
    m_currentBrightness = m_brightness;
    m_CamCtl->check_and_set_camera_property("Brightness", 
                m_real_camera_Brightness, m_brightness, CAP_PROP_BRIGHTNESS);    
  }
  
  if (m_currentContrast != m_contrast)
  {
    copy_config_camera_property("contrast");
    m_currentContrast = m_contrast;
    m_CamCtl->check_and_set_camera_property("Contrast", 
                m_real_camera_Contrast, m_contrast, CAP_PROP_CONTRAST);    
  }
  
  if (m_currentSaturation != m_saturation)
  {
    copy_config_camera_property("saturation");
    m_currentSaturation = m_saturation;
    m_CamCtl->check_and_set_camera_property("Saturation", 
                m_real_camera_Saturation, m_saturation, CAP_PROP_SATURATION);
  }
  
  if (m_currentHue != m_hue)
  {
    copy_config_camera_property("hue");
    m_currentHue = m_hue;
    m_CamCtl->check_and_set_camera_property("Hue", 
                m_real_camera_Hue, m_hue, CAP_PROP_HUE);
  }
  
  if (m_currentGain != m_gain)
  {
    copy_config_camera_property("gain");
    m_currentGain = m_gain;
    m_CamCtl->check_and_set_camera_property("Gain", 
                m_real_camera_Gain, m_gain, CAP_PROP_GAIN);
  }
  
  if (m_currentExposure != m_exposure)
  {
    copy_config_camera_property("exposure");
    m_currentExposure = m_exposure;
    m_CamCtl->check_and_set_camera_property("Exposure", 
                m_real_camera_Exposure, m_exposure, CAP_PROP_EXPOSURE);
  }
  
  if(m_currentAutoExposure != m_auto_exposure)
  {
    copy_config_camera_property("auto_exposure");
    m_currentAutoExposure = m_auto_exposure;
    m_CamCtl->check_and_set_camera_property("AutoExposure", 
                m_real_camera_AutoExposure, m_auto_exposure, CAP_PROP_AUTO_EXPOSURE);
  }
  
  return true;
}

void OpenCVCamera::copy_config_camera_property(std::string target)
{
  if (target == "all" || target == "basic")
  {
    m_config_prm.device_num = m_device_num;
    m_config_prm.frame_width = m_frame_width;
    m_config_prm.frame_height = m_frame_height;
    m_config_prm.frame_rate = m_frame_rate;
  }
  if (target == "all" || target == "brightness")
  {
    m_config_prm.brightness = m_brightness;
  }
  if (target == "all" || target == "contrast")
  {
    m_config_prm.contrast = m_contrast;
  }
  if (target == "all" || target == "saturation")
  {
    m_config_prm.saturation = m_saturation;
  }
  if (target == "all" || target == "hue")
  {
    m_config_prm.hue = m_hue;
  }
  if (target == "all" || target == "gain")
  {
    m_config_prm.gain = m_gain;
  }
  if (target == "all" || target == "exposure")
  {
    m_config_prm.exposure = m_exposure;
  }
  if (target == "all" || target == "auto_exposure")
  {
    m_config_prm.auto_exposure = m_auto_exposure;
  }
}

void OpenCVCamera::get_real_camera_property()
{
  m_real_camera_Brightness = m_CamCtl->get_camera_property("Brightness", cv::CAP_PROP_BRIGHTNESS);
  m_real_camera_Contrast = m_CamCtl->get_camera_property("Contrast", cv::CAP_PROP_CONTRAST);
  m_real_camera_Saturation = m_CamCtl->get_camera_property("Saturation", cv::CAP_PROP_SATURATION);  
  m_real_camera_Hue = m_CamCtl->get_camera_property("Hue", cv::CAP_PROP_HUE);
  m_real_camera_Gain = m_CamCtl->get_camera_property("Gain", cv::CAP_PROP_GAIN);
  m_real_camera_Exposure = m_CamCtl->get_camera_property("Exposure", cv::CAP_PROP_EXPOSURE);
  m_real_camera_AutoExposure = m_CamCtl->get_camera_property("AutoExposure", cv::CAP_PROP_AUTO_EXPOSURE);
}

extern "C"
{

  void OpenCVCameraInit(RTC::Manager* manager)
  {
    coil::Properties profile(opencvcamera_spec);
    manager->registerFactory(profile,
                             RTC::Create<OpenCVCamera>,
                             RTC::Delete<OpenCVCamera>);
  }

};


