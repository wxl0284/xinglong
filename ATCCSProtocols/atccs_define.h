#ifndef ATCCS_DEFINE
#define ATCCS_DEFINE
#pragma once
#pragma pack(1)
namespace ATCCS
{
	/*---------------------------------------------------------------
	* ˵����	���²��ֶ���ȫ�ֱ�������
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
	* �ýṹ�嶨��ATCCSЭ��ͷ���ṹ
	* ��С��							28 B
	* �ֶ�˵����
	* magic��						Э���ʶ�ţ����ֵ������0x1a2b3c4d����ATCCSЭ������
	* majorVersion/minorVersion:	Э��汾�ţ����ڽ�����չ
	* msg��							Э���������е���������
	* length:						���ϸ�ͷ����Э�����ݱ����ܳ���
	* sequence��						���ݱ���Ψһ��ʶ��
	* tv_sec/tv_usec:				Э�����ݱ�ʱ���
	* AT.at/AT.device:				���ݱ�����ָ�����Զ�����豸
	* env��							���ݱ�����ָ��Ļ�������豸
	* ---------------------------------------------------------------------------------------------------
	* ʹ��˵��: ʹ�øýṹ�����char* �ַ���, ʾ�����£�
	* ע��, ȷ��data��ֵ, �����ݳ��ȴ��ڵ��� sizeof(_ATCCSPHeader)
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
	* ���²��ֶ���ATCCSЭ��Ĺ���������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/
	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_MSG_TYPE ö������, ö��_ATCCSPHeader�� 'msg' �ֶε���������
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
	* _AT_AT_TYPE ö������, ö��_ATCCSPHeader�� 'AT.at' �ֶε���������
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
	* _AT_DEVICE_TYPE ö������, ö��_ATCCSPHeader�� 'AT.device' �ֶε���������
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
	* _AT_ENV_TYPE ö������, ö��_ATCCSPHeader�� 'env' �ֶε���������
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
	* �ýṹ�嶨�������豸�Ĺ���������Ϣ
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
	* �ýṹ�嶨�������豸�Ĺ���״̬��Ϣ
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
	* �ýṹ�嶨���·��������豸��ָ��ͷ����Ϣ
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
	* �ýṹ�嶨������豸�ϱ���ָ��ִ�н����Ϣ
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
	* ���²��ֶ���ATCCSЭ����Gimbal (ת̨) ������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_GIMBAL_INSTRUCTION ö������, ö��Gimbal (ת̨) ������ָ�����
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
	* �ýṹ�嶨��Gimbal��������Ϣ
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
	* �ýṹ�嶨��Gimbal��״̬��Ϣ
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
	* �ýṹ�嶨��Gimbal��CCD/Filter/SLAVEDOME/FULLOPENEDDOME/FOCUS/GuideScope (connect) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (FindHonme) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (TrackStar) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (SetObserveName) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (SlewAzEl) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (SlewDerotator) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (ConfigDerotator) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (SetTrackSpeed) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (FixedMove) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (PositionCorrect) ָ������ṹ��
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
	* �ýṹ�嶨��Gimbal (OpenCover) ָ������ṹ��
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
	* ��ͷ�ļ�����ATCCSЭ���� CCD ������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_CCD_INSTRUCTION ö������, ö��CCD������ָ�����
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
	* �ýṹ�嶨��CCD��������Ϣ
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
	* �ýṹ�嶨��CCD��״̬��Ϣ
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
	* �ýṹ�嶨��CCD (SetCoolerT) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetExposureTactics) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (StartExposure) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetGain) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetReadSpeedMode) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetBIN) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetROI) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetShutter) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetFullFrame) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetEM) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetNosieFilter) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetBaseline) ָ������ṹ��
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
	* �ýṹ�嶨��CCD (SetOverScan) ָ������ṹ��
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
	* ��ͷ�ļ�����ATCCSЭ����Dome (Բ��) ��������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_SLAVEDOME_INSTRUCTION ö������, ö��SlaveDome (�涯ʽԲ��) ������ָ�����
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
	* _AT_FULLOPENEDDOME_INSTRUCTION ö������, ö��Full Opened Dome (ȫ��ʽԲ��) ������ָ�����
	* ----------------------------------------------------------------------------------------------------
	*/
	enum _AT_FULLOPENEDDOME_INSTRUCTION
	{
		_AT_FULLOPENEDDOME_CONNECT,
		_AT_FULLOPENEDDOME_OPENDOME
	};



	/*!
	*-----------------------------------------------------------------------------------------------------
	* �ýṹ�嶨��SlaveDome (�涯ʽԲ��) ��������Ϣ
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
	* �ýṹ�嶨��SlaveDome��״̬��Ϣ
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
	* �ýṹ�嶨��SlaveDome (SetDomePosition)(SetShadePosition) ָ��Ĳ�����Ϣ
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
	* �ýṹ�嶨��SlaveDome (SetRotateSpeed) ָ��Ĳ�����Ϣ
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
	* �ýṹ�嶨��SlaveDome (OpenScuttle) ָ��Ĳ�����Ϣ
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
	* �ýṹ�嶨��FullOpenedDome (ȫ��ʽԲ��) ��������Ϣ
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
	* �ýṹ�嶨��FullOpenedDome (ȫ��ʽԲ��) ��״̬��Ϣ
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
	* �ýṹ�嶨��FullOpenedDome (OpenDome) ָ��Ĳ�����Ϣ
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
	* ��ͷ�ļ�����ATCCSЭ����DPM (���ݴ���ģ��) ��������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	*-----------------------------------------------------------------------------------------------------
	* �ýṹ�嶨��DPM��������Ϣ
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
	* �ýṹ�嶨��DPM��״̬��Ϣ
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
	* ��ͷ�ļ�����ATCCSЭ����Filter (�˹�Ƭ) ��������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_FILTER_INSTRUCTION ö������, ö��Filter (�˹�Ƭ) ������ָ�����
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
	* �ýṹ�嶨��Filter��������Ϣ
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
	* �ýṹ�嶨��Filter��״̬��Ϣ
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
	* �ýṹ�嶨��Filter (SetFilterPosition) ָ��Ĳ�����Ϣ
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
	* ��ͷ�ļ�����ATCCSЭ����Focus (����) ��������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_FOCUS_INSTRUCTION ö������, ö��Focus (����) ������ָ�����
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
	* �ýṹ�嶨��Focus��������Ϣ
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
	* �ýṹ�嶨��Focus��״̬��Ϣ
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
	* �ýṹ�嶨��Focus (SetPosition) ָ��Ĳ�����Ϣ
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
	* �ýṹ�嶨��Focus (SetFixedSpeed) ָ��Ĳ�����Ϣ
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
	* �ýṹ�嶨��Focus (EnableTCompensate) ָ��Ĳ�����Ϣ
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
	* �ýṹ�嶨��Focus (SetTCompensate) ָ��Ĳ�����Ϣ
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
	* ��ͷ�ļ�����ATCCSЭ����Guidescope (���Ǿ�) ��������Ϣ
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
	* ���ļ������� (version 1.00.00)
	* ---------------------------------------------------------------------------------------------------
	* version:				1.00.1
	* modified data:		2017-04-06
	* IDE:					VS2010
	* OS:					windows xp sp3
	*
	*/

	/*!
	* ----------------------------------------------------------------------------------------------------
	* _AT_GUIDESCOPE_INSTRUCTION ö������, ö��GuideScope (���Ǿ�) ������ָ�����
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
	* �ýṹ�嶨��GuideScope��������Ϣ
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
	* �ýṹ�嶨��GuideScope��״̬��Ϣ
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
	* �ýṹ�嶨��GuideScope (EnableAutoFocus) ָ��Ĳ�����Ϣ
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