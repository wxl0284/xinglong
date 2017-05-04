#ifndef ATCCS_DEFINE
#define ATCCS_DEFINE
#pragma once
#pragma pack(1)
namespace ATCCS
{
	/*---------------------------------------------------------------
	* 说明：	以下部分定义全局编译条件
	* Author:	Geniuswei
	* Date:		2017-03-30
	* IDE:		VS2010
	* OS:		windows xp sp3
	*--------------------------------------------------------------*/

#ifndef C11
#define C11 0
#endif

#ifndef C98
#define C98 1
#endif

#ifndef QT
#define QT 0
#endif

#ifndef nullptr
#define nullptr 0
#endif
#ifndef NULL
#define NULL 0
#endif

#ifndef UINT8
	typedef unsigned char UINT8;
#endif
#ifndef UINT16
	typedef unsigned short UINT16;
#endif
#ifndef UINT32
	typedef unsigned int UINT32;
#endif
#ifndef UINT64
	typedef unsigned long long UINT64;
#endif

#ifndef INT8
	typedef signed char INT8;
#endif

#ifndef INT16
	typedef signed short INT16;
#endif

#ifndef INT32
	typedef signed int INT32;
#endif

#ifndef DOUBLE64
	typedef double DOUBLE64;
#endif

#ifndef FLOAT32
	typedef float FLOAT32;
#endif

	const int MAGIC = 0x1a2b3c4d;
	const unsigned short MAJOR = 1;
	const unsigned short MINOR = 1;

	/*!
	* ----------------------------------------------------------------------------------------------------
	* 该结构体定义ATCCS协议头部结构
	* 大小：							28 B
	* 字段说明：
	* magic：						协议标识号，如果值不等于0x1a2b3c4d，非ATCCS协议数据
	* majorVersion/minorVersion:	协议版本号，便于将来扩展
	* msg：							协议数据体中的数据类型
	* length:						加上该头部后，协议数据报的总长度
	* sequence：						数据报的唯一标识号
	* tv_sec/tv_usec:				协议数据报时间戳
	* AT.at/AT.device:				数据报数据指向的望远镜和设备
	* env：							数据报数据指向的环境监测设备
	* ---------------------------------------------------------------------------------------------------
	* 使用说明: 使用该结构体解析char* 字符串, 示例如下：
	* 注意, 确保data有值, 且数据长度大于等于 sizeof(_ATCCSPHeader)
	* char *data;
	* _ATCCSPHeader *header = (_ATCCSPHeader*)data;
	* int seq = header->sequence;
	* int at = header->AT.at;
	* int device = header->device;
	*/
	struct _ATCCSPHeader{
		UINT32 magic;
		UINT16 majorVersion:8,
minorVesion:8;
		UINT16 msg;
		UINT32 length;
		UINT32 sequence;
		UINT32 tv_sec;
		UINT32 tv_usec;
		union
		{
			struct
			{
				UINT16 at;
				UINT16 device;
			}AT;
			UINT32 env;
		};
	};



	/*
	* ---------------------------------------------------------------------------------------------------
	* 以下部分定义ATCCS协议的公共数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/
	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_MSG_TYPE 枚举类型, 枚举_ATCCSPHeader中 'msg' 字段的所有类型
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_MSG_TYPE{
		ENVDATAREPORT = 0x01,
		ATATTRIBUTE,
		ATATTRIBUTEACK,
		ATSTATUSREPORT,
		ATSTATUSACK,
		ATOPERATION,
		ATOPERATIONACK,
		ATPLAN,
		ATPLANACK,
		ATHEARTBEAT
	};

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_AT_TYPE 枚举类型, 枚举_ATCCSPHeader中 'AT.at' 字段的所有类型
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_AT_TYPE{
		AT216 = 0x20,
		AT126,
		AT100,
		AT85,
		AT80,
		AT60,
		AT50,
		ATAE,
		AT_AT_NUM
	};

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_DEVICE_TYPE 枚举类型, 枚举_ATCCSPHeader中 'AT.device' 字段的所有类型
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_DEVICE_TYPE{
		GIMBAL=0x40,
		CCD,
		FILTER,
		SLAVEDOME,
		FULLOPENEDDOME,
		FOCUS,
		GUIDESCOPE,
		DPM
	};

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_ENV_TYPE 枚举类型, 枚举_ATCCSPHeader中 'env' 字段的所有类型
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_ENV_TYPE{
		ASC = 0x60,
		WS,
		CS,
		SQM,
		DIMM,
		DUST
	};

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义所有设备的公共属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author Geniuswei
	* @date 2016-12-26 11:25
	* @size 60Bytes
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct ATPublicAttributes{
		UINT8 id[8];
		UINT8 name[48];
		UINT16 telescope;
		UINT16 type;
	}_AT_PUBLIC_ATTRIBUTES;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义所有设备的公共状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				64B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct ATPublicStatus{
		UINT32 status;
		UINT32 lastStatus;
		UINT32 warning;
		UINT32 error;
		UINT8 errorString[48];
	}_AT_PUBLIC_STATUS;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义下发至具体设备的指令头部信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				16B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct _ATInstructionHeader{
		char user[48];
		UINT32 plan;
		UINT16 at;
		UINT16 device;
		UINT32 sequence;
		UINT32 operation;
	}_AT_INSTRUCTION_HEADER;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义具体设备上报的指令执行结果信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				16B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct _ATInstructionResult{
		UINT32 plan;
		UINT16 at;
		UINT16 device;
		UINT32 sequence;
		UINT32 operation;
		UINT32 result;
	}_AT_INSTRUCTION_RESULT;
	
	/*
	* ---------------------------------------------------------------------------------------------------
	* 以下部分定义ATCCS协议中Gimbal (转台) 数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_GIMBAL_INSTRUCTION 枚举类型, 枚举Gimbal (转台) 的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_GIMBAL_INSTRUCTION
	{
		_AT_GIMBAL_CONNECT = 0x01,
		_AT_GIMBAL_FINDHOME,
		_AT_GIMBAL_TRACKSTAR,
		_AT_GIMBAL_SETOBSERVE,
		_AT_GIMBAL_SLEWAZEL,
		_AT_GIMBAL_SLEWDEROTATOR,
		_AT_GIMBAL_CONFIGDEROTATOR,
		_AT_GIMBAL_STOP,
		_AT_GIMBAL_SETTRACKSPEED,
		_AT_GIMBAL_PARK,
		_AT_GIMBAL_FIXEDMOVE,
		_AT_GIMBAL_POSITIONCORRECT,
		_AT_GIMBAL_COVEROPERATION,
		_AT_GIMBAL_FOCUSOPERATION,
		_AT_GIMBAL_EMERGENCYSTOP,
		_AT_GIMBAL_SAVESYNCDATA,
		_AT_GIMBAL_TRACKSATELLITE,
		_AT_GIMBAL_CONFIGPROPERTIES
	};

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author Geniuswei
	* @date 2016-12-26 11:25
	* @size 216 Bytes
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct GimbalAttributes{
		UINT8 id[8];
		UINT8 name[48];
		UINT16 observatory;
		DOUBLE64 longitude;
		DOUBLE64 latitude;
		DOUBLE64 altitude;
		DOUBLE64 aperture;
		UINT16 type;
		DOUBLE64 maxAxis1Speed;
		DOUBLE64 maxAxis2Speed;
		DOUBLE64 maxAxis3Speed;
		DOUBLE64 maxAxis1Acceleration;
		DOUBLE64 maxAxis2Acceleration;
		DOUBLE64 maxAxis3Acceleration;
		DOUBLE64 axis1ParkPosition;
		DOUBLE64 axis2ParkPosition;
		DOUBLE64 axis3ParkPosition;
		UINT16 haveAxis3;
		UINT16 haveAxis5;
		DOUBLE64 minElevation;
		UINT16 numTemperatureSensor;
		UINT16 numHumiditySensor;
		UINT16 canConnect;
		UINT16 canFindHome;
		UINT16 canTrackStar;
		UINT16 canSetObjectName;
		UINT16 canSlewAzEl;
		UINT16 canSlewDerotator;
		UINT16 canConfigDerotator;
		UINT16 canStop;
		UINT16 canSetTrackSpeed;
		UINT16 canPark;
		UINT16 canFixedMove;
		UINT16 canPositionCorrect;
		UINT16 canCoverOperation;
		UINT16 canFocusOperation;
		UINT16 canScram;
		UINT16 canSaveSyncData;
		UINT16 canTrackSatellite;
		UINT16 canConfigProperity;
	}_AT_GIMBAL_ATTRIBUTES;



	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author Geniuswei
	* @date 2016-12-26 11:25
	* @size 414 Bytes
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct GimbalStatus{
		_AT_PUBLIC_STATUS error;
		DOUBLE64 siderealTime;
		DOUBLE64 hourAngle;
		DOUBLE64 rightAscension;
		DOUBLE64 declination;
		DOUBLE64 J2000RightAscension;
		DOUBLE64 J2000Declination;
		DOUBLE64 azmiuth;
		DOUBLE64 elevation;
		DOUBLE64 derotatorPositon;
		DOUBLE64 targetRightAscension;
		DOUBLE64 targetDeclination;
		DOUBLE64 targetJ2000RightAscension;
		DOUBLE64 targetJ2000Declination;
		DOUBLE64 targetAzmiuth;
		DOUBLE64 targetElevation;
		DOUBLE64 targetDerotatorPosition;
		DOUBLE64 axis1TrackError;
		DOUBLE64 axis2TrackError;
		DOUBLE64 axis3TrackError;
		UINT16 focusTypeIndex;
		DOUBLE64 axis4Angle;
		UINT16 coverIndex;
		DOUBLE64 coverPosition;
		UINT16 targetFocusTypeIndex;
		DOUBLE64 targetAxis4Angle;
		UINT16 targetCoverIndex;
		DOUBLE64 axis1Speed;
		DOUBLE64 axis2Speed;
		DOUBLE64 axis3Speed;
		UINT16 trackType;
		UINT8 trackObjectName[48];
		DOUBLE64 refractionCorrection;
		DOUBLE64 axis1Encoder;
		DOUBLE64 axis2Encoder;
		DOUBLE64 axis3Encoder;
		UINT16 axis3Mode;
		DOUBLE64 axis1PMCorrection;
		DOUBLE64 axis2PMCorrection;
		DOUBLE64 axis3PMCorrection;
		DOUBLE64 axis1ManualCorrection;
		DOUBLE64 axis2ManualCorrection;
		DOUBLE64 axis3ManualCorrection;
		UINT16 pieSide;
		UINT16 targetPieSide;
		UINT16 isAxis1FindHome;
		UINT16 isAxis2FindHome;
		UINT16 isAxis3FindHome;

	}_AT_GIMBAL_STATUS;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal、CCD/Filter/SLAVEDOME/FULLOPENEDDOME/FOCUS/GuideScope (connect) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct ConnectParam{
		//0:disconnect, otherwise:connect
		UINT32 connect;
	}_AT_GIMBAL_CONN_PARAM,_AT_CCD_CONN_PARAM,_AT_FILTER_CONN_PARAM,\
		_AT_SLAVEDOME_CONN_PARAM,_AT_FULLOPENEDOME_CONN_PARAM,\
		_AT_FOCUS_COMM_PARAM,_AT_GUIDESCOPE_CONN_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (FindHonme) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FindHomeParam{
		UINT32 axis;
	}_AT_GIMBAL_FH_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (TrackStar) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				24 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOTrackStarParam{
		DOUBLE64 rightAscension;
		DOUBLE64 declination;
		UINT32 epoch;
		UINT32 speed;
	}_AT_GIMBAL_TS_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (SetObserveName) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				52 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOSetObserveNameParam{
		UINT8 objectName[48];
		UINT32 objectType;
	}_AT_GIMBAL_SON_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (SlewAzEl) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				16 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOSlewAzElParam{
		DOUBLE64 azimuth;
		DOUBLE64 elevation;
	}_AT_GIMBAL_SAZEL_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (SlewDerotator) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOSlewDerotatorParam{
		DOUBLE64 position;
	}_AT_GIMBAL_SD_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (ConfigDerotator) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				12 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOConfigDerotatorParam{
		UINT32 mode;
		DOUBLE64 polarizingAngle; //only used in mode 2
	}_AT_GIMBAL_CD_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (SetTrackSpeed) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOSetTrackSpeedParam{
		DOUBLE64 speed;
	}_AT_GIMBAL_STS_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (FixedMove) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				12 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOFixedMoveParam{
		UINT32 axis;
		DOUBLE64 speed;
	}_AT_GIMBAL_FM_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (PositionCorrect) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				12 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOPositionCorrectParam{
		UINT32 axis;
		DOUBLE64 correction;
	}_AT_GIMBAL_PC_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Gimbal (OpenCover) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SOOpenCoverParam{
		UINT32 action;
	}_AT_GIMBAL_CO_PARAM, _AT_GIMBAL_FO_PARAM;

	/*
	* ---------------------------------------------------------------------------------------------------
	* 该头文件定义ATCCS协议中 CCD 数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_CCD_INSTRUCTION 枚举类型, 枚举CCD的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_CCD_INSTRUCTION
	{
		_AT_CCD_CONNECT = 0x01,
		_AT_CCD_SETCOOLERT,
		_AT_CCD_SETEXPOSUREPARAM,
		_AT_CCD_STARTEXPOSURE,
		_AT_CCD_STOPEXPOSURE,
		_AT_CCD_ABORTEXPOSURE,
		_AT_CCD_SETGAIN,
		_AT_CCD_SETRSMODE,
		_AT_CCD_SETTSMODE,
		_AT_CCD_SETBIN,
		_AT_CCD_SETROI,
		_AT_CCD_SETSHUTTER,
		_AT_CCD_SETFULLFRAME,
		_AT_CCD_SETEM,
		_AT_CCD_SETNOISEFILTER,
		_AT_CCD_SETBASELINE,
		_AT_CCD_SETOVERSCAN
	};

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author Geniuswei
	* @date 2016-12-26 11:25
	* @size 208 Bytes
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		UINT32 xPixel;
		UINT32 yPixel;
		DOUBLE64 xPixelSize;
		DOUBLE64 yPixelSize;
		char sensorName[20];
		UINT16 imageBits;
		UINT16 coolerMode;
		DOUBLE64 minCoolerTemperature;
		DOUBLE64 maxExposureTime;
		DOUBLE64 minExposrueTime;
		UINT32 exposureTimeRatio;
		UINT32 fullWellDepth;
		UINT16 readMode;
		UINT16 readSpeedMode;
		UINT16 transferMode;
		UINT16 gainMode;
		UINT16 numGainGear;
		UINT16 shutterType;
		UINT16 shutterMode;
		UINT16 isFullFrame;
		UINT16 isEM;
		UINT16 isNoiseFilter;
		UINT16 isBaseline;
		UINT16 isOverScan;
		UINT16 isROI;
		UINT32 maxEM;
		UINT32 minEM;
		UINT16 canConnect;
		UINT16 canSetCoolerT;
		UINT16 canSetExposureParam;
		UINT16 canStartExposure;
		UINT16 canStopExposure;
		UINT16 canAbortExposure;
		UINT16 canSetGain;
		UINT16 canSetReadSpeedMode;
		UINT16 canSetTransferSpeedMode;
		UINT16 canSetBin;
		UINT16 canSetROI;
		UINT16 canSetShutter;
		UINT16 canSetFullFrame;
		UINT16 canSetEM;
		UINT16 canNoiseFilter;
		UINT16 canSetBaseline;
		UINT16 canOverScan;
	}_AT_CCD_ATTRIBUTES;


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author Geniuswei
	* @date 2016-12-26 11:25
	* @size 328 Bytes
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDStatus{
		_AT_PUBLIC_STATUS status;
		char observeName[48];
		UINT16 observeType;
		DOUBLE64 J2000RightAscension;
		DOUBLE64 J2000Declination;
		UINT16 epoch;
		char band[8];
		UINT32 binX;
		UINT32 binY;
		UINT32 startX;
		UINT32 startY;
		UINT32 imageWidth;
		UINT32 imageHeight;
		DOUBLE64 exposureTime;
		DOUBLE64 delayTime;
		UINT32 frameSequence;
		UINT32 frameTotal;
		UINT16 indexOfRSMode;
		UINT16 indexOfTSMode;
		UINT16 indexOfGainMode;
		UINT16 indexOfGain;
		DOUBLE64 coolerT;
		DOUBLE64 targetCoolerT;
		char lastTargetName[48];
		UINT32 lastExposureTime;
		DOUBLE64 lastExposureDuration;
		UINT16 readMode;
		DOUBLE64 bitsOfPixel;
		DOUBLE64 exposurePercent;
		UINT16 exposureTriggerMode;
		UINT16 fanOn;
		UINT16 shutterMode;
		UINT16 isFullFrame;
		UINT16 isEM;
		UINT32 EM;
		UINT16 isNoiseFilter;
		UINT16 isBaseline;
		UINT32 baseline;
		DOUBLE64 pixelScaleX;
		DOUBLE64 pixelScaleY;
	}_AT_CCD_STATUS;


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetCoolerT) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetCoolerTParam{
		DOUBLE64 temperature;
	}_AT_CCD_SCT_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetExposureTactics) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				234 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetExposureTactics{
		UINT16 validFlag;
		UINT32 startTime;
		DOUBLE64 duration;
		DOUBLE64 delay;
		UINT8 objectName[24];
		UINT16 objectType;
		DOUBLE64 objectRightAscension;
		DOUBLE64 objectDeclination;
		UINT16 objectEpoch;
		UINT8 objectBand[8];
		UINT16 objectFilter;
		UINT16 isSaveImage;
		UINT32 weatherGatherTime;
		DOUBLE64 temperature;
		DOUBLE64 humidity;
		DOUBLE64 windSpeed;
		DOUBLE64 pressure;
		UINT32 skyGatherTime;
		UINT16 skyState;
		UINT16 clouds;
		UINT32 seeingGatherTime;
		DOUBLE64 seeing;
		UINT32 dustGatherTime;
		DOUBLE64 dust;
		DOUBLE64 AMS;
		UINT32 extinctionGatherTime;
		DOUBLE64 rightAscension;
		DOUBLE64 declination;
		UINT8 band[8];
		DOUBLE64 extinctionFactor1;
		DOUBLE64 extinctionFactor2;
		DOUBLE64 extinctionFactor3;
		DOUBLE64 telescopeRightAscension;
		DOUBLE64 telescopeDeclination;
		DOUBLE64 focusLength;
		UINT32 frameNum;
	}_AT_CCD_SET_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (StartExposure) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				6 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDStartExposureParam{
		UINT16 isReadFrameSeq;
		UINT32 frameSequence;
	}_AT_CCD_SE_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetGain) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetGainParam{
		UINT16 mode;
		UINT16 gear;
	}_AT_CCD_SG_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetReadSpeedMode) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetReadSpeedModeParam{
		UINT32 mode;
	}_AT_CCD_SRSM_PARAM,_AT_CCD_STSM_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetBIN) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetBINParam
	{
		UINT32 binX;
		UINT32 binY;
	}_AT_CCD_SB_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetROI) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				16 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetROIParam
	{
		UINT32 startX;
		UINT32 startY;
		UINT32 imageWidth;
		UINT32 imageHeight;
	}_AT_CCD_SR_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetShutter) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetShutterParam
	{
		UINT32 shutter;
	}_AT_CCD_SS_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetFullFrame) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetFullFrameParam{
		UINT32 isFullFrame;
	}_AT_CCD_SFF_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetEM) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				6 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetEMParam{
		UINT16 isEM;
		UINT32 EM;
	}_AT_CCD_SEM_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetNosieFilter) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				2 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetNosieFilterParam{
		UINT16 isNoiseFilter;
	}_AT_CCD_SNF_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetBaseline) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				6 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetBaselineParam{
		UINT16 isBaseline;
		UINT32 baseline;
	}_AT_CCD_SBL_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义CCD (SetOverScan) 指令参数结构体
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				2 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct CCDSetOverScanParam{
		UINT16 isOverScan;
	}_AT_CCD_SOS_PARAM;

	/*
	* ---------------------------------------------------------------------------------------------------
	* 该头文件定义ATCCS协议中Dome (圆顶) 的数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_SLAVEDOME_INSTRUCTION 枚举类型, 枚举SlaveDome (随动式圆顶) 的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_SLAVEDOME_INSTRUCTION
	{
		_AT_SLAVEDOME_CONNECT,
		_AT_SLAVEDOME_SETDOMEPOSITION,
		_AT_SLAVEDOME_SETSHADEPOSITION,
		_AT_SLAVEDOME_SETROTATESPEED,
		_AT_SLAVEDOME_STOP,
		_AT_SLAVEDOME_SCUTTLEACTION,
		_AT_SLAVEDOME_SHADEACTION
	};

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_FULLOPENEDDOME_INSTRUCTION 枚举类型, 枚举Full Opened Dome (全开式圆顶) 的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_FULLOPENEDDOME_INSTRUCTION
	{
		_AT_FULLOPENEDDOME_CONNECT,
		_AT_FULLOPENEDDOME_OPENDOME
	};



	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义SlaveDome (随动式圆顶) 的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				92B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SlaveDomeAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		UINT16 hasShade;
		DOUBLE64 maxSpeed;
		DOUBLE64 diameter;
		UINT16 canSetDomePosition;
		UINT16 canSetShadePosition;
		UINT16 canSetSpeed;
		UINT16 canStop;
		UINT16 canOpenScuttle;
		UINT16 canSetShadeSpeed;
		UINT16 canConnect;
	}_AT_SLAVEDOME_ATTRIBUTES;



	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义SlaveDome的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				116 B
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SlaveDomeStatus{
		_AT_PUBLIC_STATUS status;
		UINT16 scuttleStatus;
		UINT16 shadeStatus;
		DOUBLE64 domePosition;
		DOUBLE64 scuttlePercent;
		DOUBLE64 shadePosition;
		DOUBLE64 targetDomePosition;
		DOUBLE64 targetScuttlePosition;
		DOUBLE64 targetShadePosition;	
	}_AT_SLAVEDOME_STATUS;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义SlaveDome (SetDomePosition)(SetShadePosition) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SlaveDomeSetPositionParam{
		DOUBLE64 position;
	}_AT_SLAVEDOME_SDP_PARAM, _AT_SLAVEDOME_SSP_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义SlaveDome (SetRotateSpeed) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SlaveDomeSetRotateSpeedParam{
		DOUBLE64 speed;
	}_AT_SLAVEDOME_SRS_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义SlaveDome (OpenScuttle) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct SlaveDomeOpenScuttleParam{
		UINT32 action;
	}_AT_SLAVEDOME_OS_PARAM, _AT_SLAVEDOME_SSS_PARAM;



	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义FullOpenedDome (全开式圆顶) 的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				72B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FullOpenedDomeAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		DOUBLE64 diameter;
		UINT16 canConnect;
		UINT16 canOpenDome;
	}_AT_FULLOPENEDDOME_ATTRIBUTES;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义FullOpenedDome (全开式圆顶) 的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				72B
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FullOpenedDomeStatus{
		_AT_PUBLIC_STATUS status;
		DOUBLE64 domePosition;	
	}_AT_FULLOPENEDDOME_STATUS;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义FullOpenedDome (OpenDome) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FullOpenedDomeOpenDomeParam{
		UINT32 action;
	}_AT_FULLOPENEDOME_OD_PARAM;


	/*
	* ---------------------------------------------------------------------------------------------------
	* 该头文件定义ATCCS协议中DPM (数据处理模块) 的数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义DPM的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				68B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct DPMAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		char detector[8];
	}_AT_DPM_ATTRIBUTES;


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义DPM的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				330B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct DPMStatus{
		char imagePath[48];
		char objectName[48];
		UINT16 objectType;
		DOUBLE64 rightAscension;
		DOUBLE64 declination;
		UINT16 epoch;
		char band[8];
		UINT16 observeStatus;
		UINT32 binX;
		UINT32 binY;
		UINT32 startX;
		UINT32 startY;
		UINT32 imageWidth;
		UINT32 imageHeight;
		DOUBLE64 exposureTime;
		UINT16 indexOfGainMode;
		UINT16 indexOfRSMode;
		UINT16 indexOfTSMode;
		UINT16 indexOfGainGear;
		UINT16 indexOfRMode;
		UINT16 gain;
		DOUBLE64 noise;
		DOUBLE64 coolerT;
		DOUBLE64 targetCoolerT;
		DOUBLE64 bitsOfPixel;
		UINT16 exposureTriggerMode;
		UINT16 indexOfCoolerMode;
		UINT16 fanStatus;
		DOUBLE64 imageMeanValue;
		DOUBLE64 imageRMS;
		DOUBLE64 astrologyHHFW;
		DOUBLE64 imageCenterRightAscension;
		DOUBLE64 imageCenterDeclination;
		DOUBLE64 missX;
		DOUBLE64 missY;
		DOUBLE64 missAxis1;
		DOUBLE64 missAxis2;
		DOUBLE64 atmosphericTransparency;
		UINT16 shutterMode;
		UINT16 isFullFrame;
		UINT16 isEM;
		UINT32 EM;
		UINT16 isNoiseFilter;
		UINT16 isBaseline;
		UINT16 isOverScan;
		DOUBLE64 pixelScaleX;
		DOUBLE64 pixelScaleY;
		DOUBLE64 temperature;
		UINT16 fitsHead;
	}_AT_DPM_STATUS;


	/*
	* ---------------------------------------------------------------------------------------------------
	* 该头文件定义ATCCS协议中Filter (滤光片) 的数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_FILTER_INSTRUCTION 枚举类型, 枚举Filter (滤光片) 的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_FILTER_INSTRUCTION
	{
		_AT_FILTER_CONNECT,
		_AT_FILTER_SETPOSITION,
		_AT_FILTER_FINDHOME
	};



	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Filter的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				82 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FilterAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		UINT16 numFilter;
		UINT32 filterSize[3];
		UINT16 filterShape;
		UINT16 canSetFilterPosition;
		UINT16 canConnect;
		UINT16 canFindHome;
	}_AT_FILTER_ATTRIBUTES;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Filter的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				70 B
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FilterStatus{
		_AT_PUBLIC_STATUS status;
		UINT16 filterPosition;
		UINT16 targetFilterPosition;
		UINT16 isHomed;	
	}_AT_FILTER_STATUS;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Filter (SetFilterPosition) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FilterSetPositionParam{
		UINT32 filter;
	}_AT_FILTER_SP_PARAM;

	/*
	* ---------------------------------------------------------------------------------------------------
	* 该头文件定义ATCCS协议中Focus (焦距) 的数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_FOCUS_INSTRUCTION 枚举类型, 枚举Focus (焦距) 的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_FOCUS_INSTRUCTION
	{
		_AT_FOCUS_CONNECT,
		_AT_FOCUS_SETPOSITION,
		_AT_FOCUS_SETFIXEDSPEED,
		_AT_FOCUS_STOP,
		_AT_FOCUS_ENABLETCOMPENSATE,
		_AT_FOCUS_SETTCOMPENSATE,
		_AT_FCOUS_FINDHOME
	};


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Focus的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				108 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FocusAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		DOUBLE64 maxValue;
		DOUBLE64 minValue;
		DOUBLE64 increment;
		UINT16 isFindHome;
		UINT16 isTCompensate;
		DOUBLE64 maxSpeed;
		UINT16 canConnect;
		UINT16 canSetPosition;
		UINT16 canSetSpeed;
		UINT16 canStop;
		UINT16 canEnableTCompensate;
		UINT16 canFindHome;
	}_AT_FOCUS_ATTRIBUTES;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Focus的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				100 B
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FocusStatus{
		_AT_PUBLIC_STATUS status;
		DOUBLE64 position;
		DOUBLE64 targetPosition;
		UINT16 isHomed;
		DOUBLE64 temperature;
		UINT16 isTCompensation;
		DOUBLE64 TCompenensation;	
	}_AT_FOCUS_STATUS;


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Focus (SetPosition) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FocusSetPositionParam{
		DOUBLE64 position;
	}_AT_FOCUS_SP_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Focus (SetFixedSpeed) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FocusSetFixeSpeedParam{
		DOUBLE64 speed;
	}_AT_FOCUS_SFS_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Focus (EnableTCompensate) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				2 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FocusEnableTCompensateParam{
		UINT16 enbale;
	}_AT_FOCUS_ETC_PARAM;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义Focus (SetTCompensate) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				8 B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct FocusSetTCompensateParam
	{
		DOUBLE64 coefficient;
	}_AT_FOCUS_STC_PARAM;


	/*
	* ---------------------------------------------------------------------------------------------------
	* 该头文件定义ATCCS协议中Guidescope (导星镜) 的数据信息
	* ---------------------------------------------------------------------------------------------------
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
	* ---------------------------------------------------------------------------------------------------
	* 该文件拷贝于 (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_GUIDESCOPE_INSTRUCTION 枚举类型, 枚举GuideScope (导星镜) 的所有指令操作
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_GUIDESCOPE_INSTRUCTION
	{
		_AT_GUIDESCOPE_CONNECT,
		_AT_GUIDESCOPE_COVEROPERATION,
		_AT_GUIDESCOPE_ENABLEAUTOFOCUS
	};


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义GuideScope的属性信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				88B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct GuideScopeAttributes{
		_AT_PUBLIC_ATTRIBUTES header;
		DOUBLE64 aperture;
		UINT16 focusType;
		DOUBLE64 foucsLength;
		UINT16 hasAxis5;
		UINT16 isAutoFocus;
		UINT16 canConnect;
		UINT16 canCoverOperation;
		UINT16 canEnableAutoFocus;
	}_AT_GUIDESCOPE_ATTRIBUTES;


	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义GuideScope的状态信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				76 B
	*-----------------------------------------------------------------------------------------------------
	* @modified-date    2017-04-10
	* @description      relayout the data members, put _AT_PUBLIC_STATUS in the first position.
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct GuideScopeStatus{
		_AT_PUBLIC_STATUS status;
		UINT16 indexOfCover;
		UINT16 targetIndexeOfCover;
		DOUBLE64 positionOfCover;	
	}_AT_GUIDESCOPE_STATUS;

	/*!
	*-----------------------------------------------------------------------------------------------------
	* 该结构体定义GuideScope (EnableAutoFocus) 指令的参数信息
	*-----------------------------------------------------------------------------------------------------
	* @author			Geniuswei
	* @date				2016-12-28
	* @modified-date	2017-03-31
	* @size				4B
	*-----------------------------------------------------------------------------------------------------
	*/
	typedef struct GuideScopeEnableAutoFocusParam{
		UINT16 enable;
	}_AT_GUIDESCOPE_EAF_PARAM;

}
#endif