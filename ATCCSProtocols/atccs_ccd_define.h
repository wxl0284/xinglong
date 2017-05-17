#ifndef ATCCS_CCD_DEFINE
#define ATCCS_CCD_DEFINE

/*
 * -----------------------------------------------------------------------------
 * This file defines The CCD's enumerates and structrues.
 * -----------------------------------------------------------------------------
 * verion:              1.00.00
 * struct defined by:   Xinglong station of NAOC.
 * file created by:     UKC.
 * modified date:       2016-10-18.
 * CPP version:         C++11/14.
 * compiler:            gcc 4.8.5.
 * IDE:                 Qt 5.6.0.
 * debugger:			gdb 7.6.1.
 * OS:                  CentOS 7.0 64bit.
 * kernel:              3.10.0.
 * -----------------------------------------------------------------------------
 * 
 * -----------------------------------------------------------------------------
 * version:				1.00.1
 * modified data:		2017-04-06
 * IDE:					VS2010
 * OS:					windows xp sp3
 *
 */


#include "atccs_global.h"
#include "atccs_public_define.h"
#pragma once
/*!
* ------------------------------------------------------------------------------
* @brief:   ENUM_AT_CCD_INSTRUCTION enumerates CCD's instruction.
* ------------------------------------------------------------------------------
*/
enum ENUM_AT_CCD_INSTRUCTION
{
    _CCD_INSTRUCTION_CONNECT = 0x01,
    _CCD_INSTRUCTION_SETCOOLERT,            // =2
    _CCD_INSTRUCTION_SETEXPOSURETATIC,      // =3
    _CCD_INSTRUCTION_STARTEXPOSURE,         // =4
    _CCD_INSTRUCTION_STOPEXPOSURE,          // =5
    _CCD_INSTRUCTION_ABORTEXPOSURE,         // =6
    _CCD_INSTRUCTION_SETGAIN,               // =7
    _CCD_INSTRUCTION_SETRSMODE,             // =8
    _CCD_INSTRUCTION_SETTSMODE,             // =9
    _CCD_INSTRUCTION_SETBIN,                // =10
    _CCD_INSTRUCTION_SETROI,                // =11
    _CCD_INSTRUCTION_SETSHUTTER,            // =12
    _CCD_INSTRUCTION_SETFULLFRAME,          // =13
    _CCD_INSTRUCTION_SETEM,                 // =14
    _CCD_INSTRUCTION_SETNOISEFILTER,        // =15
    _CCD_INSTRUCTION_SETBASELINE,           // =16
    _CCD_INSTRUCTION_SETOVERSCAN            // =17
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_CCD_ENUM_STATUS enumerates the CCD's status
 * -----------------------------------------------------------------------------
 */
enum ENUM__AT_CCD_STATUS
{
    _CCD_STATUS_DISCONNECT = 0x01,
    _CCD_STATUS_CONNECTING,
    _CCD_STATUS_DISCONNECTING,
    _CCD_STATUS_WAITINGEXPOSURE,
    _CCD_STATUS_EXPOSING,
    _CCD_STATUS_READING,
    _CCD_STATUS_SAVING,
    _CCD_STATUS_ABORTING,
    _CCD_STATUS_IDLE
};


/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_CCD_ENUM_WARNINGS enumerates the CCD's warnings
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_CCD_WARNINGS
{
    _CCD_WARN_NORMAL,
    _CCD_WARN_TOPCOM,
    _CCD_WARN_COOLER,
    _CCD_WARN_FAN = 0x4,
    _CCD_WARN_IMG_TIMEOUT = 0x8,
    _CCD_WARN_SPACE_LESS100 = 0x10
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_CCD_ENUM_ERRORS enumerates the CCD's errors
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_CCD_ERRORS
{
    _CCD_ERROR_NORMAL,
    _CCD_ERROR_CCDCOM,
    _CCD_ERROR_EXPOSURE_START_TIMEOUT,
    _CCD_ERROR_EXPOSURE_TIMEOUT = 0x4,
    _CCD_ERROR_READ_TIMEOUT = 0x8,
    _CCD_ERROR_EXPOSURE_STOP_TIMEOUT = 0x10,
    _CCD_ERROR_EXPOSURE_ABORT_TIMEOUT = 0x20,
    _CCD_ERROR_SPACE_LESS10 = 0x40
};


/*!
*-------------------------------------------------------------------------------
* @brief:       _AT_CCD_ATTRIBUTES defines CCD's attributes.
*-------------------------------------------------------------------------------
 * @size:       208 bytes.
 * -----------------------------------------------------------------------------
* @author Geniuswei
* @date 2016-12-26 11:25
*-------------------------------------------------------------------------------
*/
#pragma pack(1)
struct _AT_CCD_PROPERTY{
    _AT_PUBLIC_PROPERTY header;
    unsigned int xPixel;
    unsigned int yPixel;
    double xPixelSize;
    double yPixelSize;
    char sensorName[20];
    unsigned short imageBits;
    unsigned short coolerMode;
    double minCoolerTemperature;
    double maxExposureTime;
    double minExposrueTime;
    unsigned int exposureTimeResolution;
    unsigned int fullWellDepth;
    unsigned short shutterType;
    unsigned short isFullFrame;
    unsigned short isEM;
    unsigned short isNoiseFilter;
    unsigned short isBaseline;
    unsigned short isOverScan;
    unsigned short isROI;
    unsigned int maxEM;
    unsigned int minEM;
    unsigned short canConnect;
    unsigned short canSetCoolerT;
    unsigned short canSetExposureParam;
    unsigned short canStartExposure;
    unsigned short canStopExposure;
    unsigned short canAbortExposure;
    unsigned short canSetGain;
    unsigned short canSetReadSpeedMode;
    unsigned short canSetTransferSpeedMode;
    unsigned short canSetBin;
    unsigned short canSetROI;
    unsigned short canSetShutter;
    unsigned short canSetFullFrame;
    unsigned short canSetEM;
    unsigned short canNoiseFilter;
    unsigned short canSetBaseline;
    unsigned short canOverScan;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_STATUS defines CCD's real time status.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   330 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  char: 1 bytes.
 *              double: 8 bytes.
 *              unsigned short: 2 bytes.
 *              unsigned int: 4 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_STATUS{
    _AT_PUBLIC_STATUS status;
    char observeName[48];
    unsigned short observeType;
    unsigned short epoch;
    double J2000RightAscension;
    double J2000Declination;    
    char band[8];
    unsigned int binX;
    unsigned int binY;
    unsigned int startX;
    unsigned int startY;
    unsigned int imageWidth;
    unsigned int imageHeight;
    double exposureTime;
    double delayTime;
    unsigned int frameSequence;
    unsigned int frameTotal;
    unsigned short indexOfRSMode;
    unsigned short indexOfTSMode;
    unsigned short indexOfGainMode;
    unsigned short indexOfGain;
    double coolerT;
    double targetCoolerT;
    char lastTargetName[48];
    unsigned int lastExposureTime;
    double lastExposureDuration;    
    double exposurePercent;
    unsigned short bitsOfPixel;    
    unsigned short readMode;
    unsigned short exposureTriggerMode;
    unsigned short fanOn;
    unsigned short shutterMode;
    unsigned short isFullFrame;
    unsigned short isEM;
    unsigned short isNoiseFilter;
    unsigned short isBaseline;
    unsigned int EM;    
    unsigned int baseline;
    double pixelScaleX;
    double pixelScaleY;	
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_CONNECT defines CCD's
 *          [_CCD_INSTRUCTION_CONNECT] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_CONNECT{
    //1:connect, 2:disconnect
    //according to ENUM_CONNECT
    unsigned short connect;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETCOOLERT defines CCD's
 *          [_CCD_INSTRUCTION_SETCOOLERT] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   8 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETCOOLERT{
    double temperature;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETEXPOSURETATIC defines CCD's
 *          [_CCD_INSTRUCTION_SETEXPOSURETATIC] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   264 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned long long: 8 bytes.
 *              char: 1 bytes.
 *              unsigned int: 4 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETEXPOSURETATIC
{
    unsigned long long validFlag;
    unsigned int startTime;
    double duration;
    double delay;
    char objectName[48];
    unsigned short objectType;
    double objectRightAscension;
    double objectDeclination;
    unsigned short objectEpoch;
    char objectBand[8];
    unsigned short objectFilter;
    unsigned short isSaveImage;
    unsigned int weatherGatherTime;
    double temperature;
    double humidity;
    double windSpeed;
    double pressure;
    unsigned int skyGatherTime;
    unsigned short skyState;
    unsigned short clouds;
    unsigned int seeingGatherTime;
    double seeing;
    unsigned int dustGatherTime;
    double dust;
    double AMS;
    unsigned int extinctionGatherTime;
    double rightAscension;
    double declination;
    char band[8];
    double extinctionFactor1;
    double extinctionFactor2;
    double extinctionFactor3;
    double telescopeRightAscension;
    double telescopeDeclination;
    double focusLength;
    unsigned int frameNum;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_STARTEXPOSURE defines CCD's
 *          [_CCD_INSTRUCTION_STARTEXPOSURE] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   6 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned int: 4 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_STARTEXPOSURE{
    unsigned short isReadFrameSeq;
    unsigned int frameSequence;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETGAIN defines CCD's
 *          [_CCD_INSTRUCTION_SETGAIN] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   4 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETGAIN{
    unsigned short mode;
    unsigned short gear;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETRSMODE defines CCD's
 *          [_CCD_INSTRUCTION_SETRSMODE] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETRSMODE{
    unsigned short mode;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETTSMODE defines CCD's
 *          [_CCD_INSTRUCTION_SETTSMODE] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETTSMODE{
    unsigned short mode;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETBIN defines CCD's
 *          [_CCD_INSTRUCTION_SETBIN] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   8 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETBIN
{
    unsigned int binX;
    unsigned int binY;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETROI defines CCD's
 *          [_CCD_INSTRUCTION_SETROI] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   16 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETROI
{
    unsigned int startX;
    unsigned int startY;
    unsigned int imageWidth;
    unsigned int imageHeight;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETSHUTTER defines CCD's
 *          [_CCD_INSTRUCTION_SETSHUTTER] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETSHUTTER
{
    unsigned short shutter;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETFULLFRAME defines CCD's
 *          [_CCD_INSTRUCTION_SETFULLFRAME] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETFULLFRAME
{
    unsigned short fullFrame;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETEM defines CCD's
 *          [_CCD_INSTRUCTION_SETEM] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   6 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETEM{
    unsigned short isEM;
    unsigned int EM;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETNOISEFILTER defines CCD's
 *          [_CCD_INSTRUCTION_SETNOISEFILTER] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETNOISEFILTER{
    unsigned short isNoiseFilter;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETBASELINE defines CCD's
 *          [_CCD_INSTRUCTION_SETBASELINE] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   6 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETBASELINE{
    unsigned short isBaseline;
    unsigned int baseline;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_CCD_PARAM_SETOVERSCAN defines CCD's
 *          [_CCD_INSTRUCTION_SETOVERSCAN] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   2 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_CCD_PARAM_SETOVERSCAN{
    unsigned short isOverScan;
};
#pragma pack()
#endif
