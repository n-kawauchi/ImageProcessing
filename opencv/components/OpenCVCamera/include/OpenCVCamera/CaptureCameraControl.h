//
// @file   CaptureCameraControl.h
// @brief  OpenCV camera control class.
//

#ifndef CaptureCameraControl_H
#define CaptureCameraControl_H

#include "ConfigurationInfo.h"
#include <rtm/Manager.h>
#include <rtm/ManagerServant.h>

#include <opencv2/opencv.hpp>
using namespace cv;
#if CV_MAJOR_VERSION < 3
#ifndef CAP_PROP_FPS
#define CAP_PROP_FPS CV_CAP_PROP_FPS
#endif
#endif //CV_MAJOR_VERSION

class CaptureCameraControl
{
public:
  CaptureCameraControl(VideoCapture *cap);
  
  bool open_camera(CONFIG_PRM *prm);
  void check_and_set_camera_property(std::string target,
                             double real_camera_value,
                             double config_value,
                             VideoCaptureProperties label);
  void set_camera_property(std::string target,
                           double config_value,
                           VideoCaptureProperties label);

private:
  cv::VideoCapture *m_cap;
  ::RTC::Logger rtclog{"OpenCVCamera:CaptureCameraControl"};

};
#endif
