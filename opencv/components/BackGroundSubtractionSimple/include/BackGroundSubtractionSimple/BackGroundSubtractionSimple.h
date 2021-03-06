﻿// -*- C++ -*-
/*!
 * @file  BackGroundSubtractionSimple.h
 * @brief BackGroundSubtractionSimple component
 * @date  $Date$
 *
 * $Id$
 */

#ifndef BACKGROUNDSUBTRACTIONSIMPLE_H
#define BACKGROUNDSUBTRACTIONSIMPLE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <opencv2/opencv.hpp>
using namespace cv;
#if CV_MAJOR_VERSION < 3
#ifndef COLOR_BGR2Lab
#define COLOR_BGR2Lab CV_BGR2Lab
#endif
#endif //CV_MAJOR_VERSION

#define THRESHOLD_MAX_VALUE	255				/* 2値化の際に使用する最大値 */
#define	SCALE				( 1.0 / 255.0 )	/* L*a*b*に変換するために必要なスケールファクタ */

#define COLOR_DIFFERENCE  0   /* RGB各成分における差分算出のフラグ値 */
#define LAB_DIFFERENCE    1   /* L*a*b*表色系における差分算出のフラグ値 */
#define GRAY_DIFFERENCE   2   /* グレースケールにおける差分算出のフラグ値 */
#define NOISE_KEEP        0   /* ノイズを除去しないフラグ値 */
#define	NOISE_MORPHOLOGY  1   /* モルフォロジー演算によるノイズ除去のフラグ値 */
#define NOISE_MEDIAN      2   /* メディアンフィルタによるノイズ除去のフラグ値 */


// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "InterfaceDataTypesStub.h"
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class BackGroundSubtractionSimple
 * @brief BackGroundSubtractionSimple component
 *
 */
class BackGroundSubtractionSimple
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  BackGroundSubtractionSimple(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~BackGroundSubtractionSimple();

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
   * - Name:  cont_mode
   * - DefaultValue: b
   */
  char m_cont_mode;
  /*!
   * 
   * - Name:  diff_mode
   * - DefaultValue: 0
   */
  char m_diff_mode;
  /*!
   * 
   * - Name:  noise_mode
   * - DefaultValue: 0
   */
  char m_noise_mode;
  /*!
   * 
   * - Name:  threshold_level
   * - DefaultValue: 20
   */
  int m_threshold_level;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::CameraImage m_img_orig;
  /*!
   */
  RTC::InPort<RTC::CameraImage> m_img_origIn;
  RTC::TimedLong m_key;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_keyIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::CameraImage m_img_curr;
  /*!
   */
  RTC::OutPort<RTC::CameraImage> m_img_currOut;
  RTC::CameraImage m_img_resu;
  /*!
   */
  RTC::OutPort<RTC::CameraImage> m_img_resuOut;
  RTC::CameraImage m_img_back;
  /*!
   */
  RTC::OutPort<RTC::CameraImage> m_img_backOut;
  
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
  void colorDifference( void );
  void labDifference( void );
  void grayScaleDifference( void );
	
  cv::Mat m_currentImage;
  cv::Mat m_backgroundImage;
  cv::Mat m_resultImage;
	
  int m_differenceMode;   /* 差分の計算モード */
  int m_noiseMode;        /* ノイズを除去するモード */
  int m_temp_w;
  int m_temp_h;

};


extern "C"
{
  DLL_EXPORT void BackGroundSubtractionSimpleInit(RTC::Manager* manager);
};

#endif // BACKGROUNDSUBTRACTIONSIMPLE_H
