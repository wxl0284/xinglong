#ifndef GIMBAL_DEFINE
#define GIMBAL_DEFINE

/*
 * ---------------------------------------------------------------------------------------------------
 * @brief   atccs_gimbal_define.h defines Gimbal's data structrue.
 * ---------------------------------------------------------------------------------------------------
 * version:             1.00.00
 * struct defined by:   Xinglong station of NAOC.
 * file created by:     UKC.
 * modified date:       2016-10-18.
 * CPP version:         C++11/14.
 * compiler:            gcc 4.8.5.
 * IDE:                 Qt 5.6.0.
 * debugger:		gdb 7.6.1.
 * OS:                  CentOS 7.0 64bit.
 * kernel:              3.10.0.
 *
 */

#include "atccs_global.h"
#include "atccs_public_define.h"
#pragma once

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_GIMBAL_INSTRUCTION enumerates the gimbal's instruction.
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_GIMBAL_INSTRUCTION
{
    _GIMBAL_INSTRUCTION_CONNECT = 1,    
    _GIMBAL_INSTRUCTION_FINDHOME,               // =2
    _GIMBAL_INSTRUCTION_TRACKSTAR,              // =3
    _GIMBAL_INSTRUCTION_SETOBJECTNAME,          // =4
    _GIMBAL_INSTRUCTION_SLEWAZEL,               // =5
    _GIMBAL_INSTRUCTION_SLEWDEROTATOR,          // =6
    _GIMBAL_INSTRUCTION_CONFIGDEROTATOR,        // =7
    _GIMBAL_INSTRUCTION_STOP,                   // =8
    _GIMBAL_INSTRUCTION_SPEEDCORRECT,           // =9
    _GIMBAL_INSTRUCTION_PARK,                   // =10
    _GIMBAL_INSTRUCTION_FIXEDMOVE,              // =11
    _GIMBAL_INSTRUCTION_POSITIONCORRECT,        // =12
    _GIMBAL_INSTRUCTION_COVERACTION,            // =13
    _GIMBAL_INSTRUCTION_FOCUSACTION,            // =14
    _GIMBAL_INSTRUCTION_EMERGENCYSTOP,          // =15
    _GIMBAL_INSTRUCTION_SAVESYNCDATA,           // =16
    _GIMBAL_INSTRUCTION_TRACKSATELLITE,         // =17
    _GIMBAL_INSTRUCTION_CONFIGPROPERTIES        // =18
};
/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_GIMBAL_STATUS enumerates the Gimbal's status.
 * ----------------------------------------------------------------------------- 
 */
enum ENUM_AT_GIMBAL_STATUS 
{
    _GIMBAL_STATUS_DISCONNECT = 1,
    _GIMBAL_STATUS_CONNECTING,                  // =2
    _GIMBAL_STATUS_DISCONNECTING,               // =3
    _GIMBAL_STATUS_NOTFINDHOME,                 // =4
    _GIMBAL_STATUS_HOMING,                      // =5
    _GIMBAL_STATUS_FREEZING,                    // =6
    _GIMBAL_STATUS_FREEZED,                     // =7
    _GIMBAL_STATUS_EMERGENCYING,                // =8
    _GIMBAL_STATUS_EMERGENCY,                   // =9
    _GIMBAL_STATUS_PARKING,                     // =10
    _GIMBAL_STATUS_PARKED,                      // =11
    _GIMBAL_STATUS_WAITINGTEACKING,             // =12    
    _GIMBAL_STATUS_TRACKING,                    // =13
    _GIMBAL_STATUS_TRACKINGBIASSPEED,           // =14
    _GIMBAL_STATUS_TRACKINGBIASPOS,             // =15
    _GIMBAL_STATUS_WAITINGMOVING,               // =16    
    _GIMBAL_STATUS_MOVING,                      // =17
    _GIMBAL_STATUS_SLEWING,                     // =18
    _GIMBAL_STATUS_SLEWED,                      // =19
    _GIMBAL_STATUS_WAITINGRUNNING,              // =20
    _GIMBAL_STATUS_RUNNING,                     // =21
    _GIMBAL_STATUS_ERROR                        // =22
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_GIMBAL_WARNINGS enumerates the Gimbal's warnings.
 * ----------------------------------------------------------------------------- 
 */
enum ENUM_AT_GIMBAL_WARNINGS
{
    _GIMBAL_WARN_NORMAL = 0x0,
    _GIMBAL_WARN_ENCODER = 0x1,
    _GIMBAL_WARN_ENCODER_AXIS1 =0x2,
    _GIMBAL_WARN_ENCODER_AXIS2 = 0x4,
    _GIMBAL_WARN_ENCODER_AXIS3 = 0x8,
    _GIMBAL_WARN_ENCODER_AXIS4 = 0x10,
    _GIMBAL_WARN_ENCODER_AXIS5 = 0x20,
    _GIMBAL_WARN_LIMIT_AXIS1 = 0x40,
    _GIMBAL_WARN_LIMIT_AXIS2 = 0x80,
    _GIMBAL_WARN_LIMIT_AXIS3 = 0x100,
    _GIMBAL_WARN_LIMIT_AXIS4 = 0x200,
    _GIMBAL_WARN_LIMIT_AXIS5 = 0x400
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_GIMBAL_ERRORS enumerates the Gimbal's errors.
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_GIMBAL_ERRORS
{
    _GIMBAL_ERROR_NORMAL = 0x0,
    _GIMBAL_ERROR_BOTTOMCOM = 0x1,
    _GIMBAL_ERROR_TOPCOM = 0x2,
    _GIMBAL_ERROR_LIMIT_AXIS1 = 0x4,
    _GIMBAL_ERROR_LIMIT_AXIS2 = 0x8,
    _GIMBAL_ERROR_LIMIT_AXIS3 = 0x10,
    _GIMBAL_ERROR_LIMIT_AXIS4 = 0x20,
    _GIMBAL_ERROR_LIMIT_AXIS5 = 0x40,
    _GIMBAL_ERROR_VELOCITY_AXIS1 = 0x100,
    _GIMBAL_ERROR_VELOCITY_AXIS2 = 0x200,
    _GIMBAL_ERROR_VELOCITY_AXIS3 = 0x400,
    _GIMBAL_ERROR_VELOCITY_AXIS4 = 0x800,
    _GIMBAL_ERROR_VELOCITY_AXIS5 = 0x1000,
    _GIMBAL_ERROR_POSITION_AXIS1 = 0x2000,
    _GIMBAL_ERROR_POSITION_AXIS2 = 0x4000,
    _GIMBAL_ERROR_POSITION_AXIS3 = 0x8000,
    _GIMBAL_ERROR_POSITION_AXIS4 = 0x10000,
    _GIMBAL_ERROR_POSITION_AXIS5 = 0x20000,
    _GIMBAL_ERROR_STOP_AXIS1 = 0x40000,
    _GIMBAL_ERROR_STOP_AXIS2 = 0x80000,
    _GIMBAL_ERROR_STOP_AXIS3 = 0x100000,
    _GIMBAL_ERROR_STOP_AXIS4 = 0x200000,
    _GIMBAL_ERROR_STOP_AXIS5 = 0x400000,
    _GIMBAL_ERROR_ENCODER_AXIS1 = 0x800000,
    _GIMBAL_ERROR_ENCODER_AXIS2 = 0x1000000,
    _GIMBAL_ERROR_ENCODER_AXIS3 = 0x2000000,
    _GIMBAL_ERROR_ENCODER_AXIS4 = 0x4000000,
    _GIMBAL_ERROR_ENCODER_AXIS5 = 0x8000000,
    _GIMBAL_ERROR_SLIP_AXIS1 = 0x10000000,
    _GIMBAL_ERROR_SLIP_AXIS2 = 0x20000000,
    _GIMBAL_ERROR_SLIP_AXIS3 = 0x40000000,
    _GIMBAL_ERROR_SLIP_AXIS4 = 0x80000000,
    _GIMBAL_ERROR_SLIP_AXIS5 = 0x100000000,
    _GIMBAL_ERROR_LIMITLEVEL1_AXIS1 = 0x200000000,
    _GIMBAL_ERROR_LIMITLEVEL1_AXIS2 = 0x400000000,
    _GIMBAL_ERROR_LIMITLEVEL1_AXIS3 = 0x800000000,
    _GIMBAL_ERROR_LIMITLEVEL1_AXIS4 = 0x1000000000,
    _GIMBAL_ERROR_LIMITLEVEL1_AXIS5 = 0x2000000000,
    _GIMBAL_ERROR_LIMITLEVEL2_AXIS1 = 0x4000000000,
    _GIMBAL_ERROR_LIMITLEVEL2_AXIS2 = 0x8000000000,
    _GIMBAL_ERROR_LIMITLEVEL2_AXIS3 = 0x10000000000,
    _GIMBAL_ERROR_LIMITLEVEL2_AXIS4 = 0x20000000000,
    _GIMBAL_ERROR_LIMITLEVEL2_AXIS5 = 0x40000000000,
    _GIMBAL_ERROR_SERVO_AXIS1 = 0x80000000000,
    _GIMBAL_ERROR_SERVO_AXIS2 = 0x100000000000,
    _GIMBAL_ERROR_SERVO_AXIS3 = 0x200000000000,
    _GIMBAL_ERROR_SERVO_AXIS4 = 0x400000000000,
    _GIMBAL_ERROR_SERVO_AXIS5 = 0x800000000000
};






/*!
*-------------------------------------------------------------------------------
 * @brief:   _AT_GIMBAL_ATTRIBUTES defines Gimbal's property.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   396 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
*-------------------------------------------------------------------------------
 * @type-info:  char: 1 bytes.
 *              unsigned short: 0-65535 2 bytes.
 *              double: 8 bytes.
*-------------------------------------------------------------------------------
*/
#pragma pack(1)
struct _AT_GIMBAL_PROPERTY{
    char id[8];
    char name[48];
    unsigned short observatory;
    double longitude;
    double latitude;
    double altitude;
    double aperture;
    unsigned short type;
    unsigned short focusType[10];
    double focusRatio[10];
    double focusLength[10];
    double maxAxis1Speed;
    double maxAxis2Speed;
    double maxAxis3Speed;
    double maxAxis1Acceleration;
    double maxAxis2Acceleration;
    double maxAxis3Acceleration;
    double axis1ParkPosition;
    double axis2ParkPosition;
    double axis3ParkPosition;
    unsigned short haveAxis3;
    unsigned short haveAxis5;
    double minElevation;
    unsigned short numTemperatureSensor;
    unsigned short numHumiditySensor;
    unsigned short canConnect;
    unsigned short canFindHome;
    unsigned short canTrackStar;
    unsigned short canSetObjectName;
    unsigned short canSlewAzEl;
    unsigned short canSlewDerotator;
    unsigned short canConfigDerotator;
    unsigned short canStop;
    unsigned short canSetTrackSpeed;
    unsigned short canPark;
    unsigned short canFixedMove;
    unsigned short canPositionCorrect;
    unsigned short canCoverOperation;
    unsigned short canFocusOperation;
    unsigned short canScram;
    unsigned short canSaveSyncData;
    unsigned short canTrackSatellite;
    unsigned short canConfigProperity;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_STATUS defines Gimbal's real time status.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   614 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_STATUS{
    _AT_PUBLIC_STATUS status;
    double siderealTime;
    double hourAngle;
    double rightAscension;
    double declination;
    double J2000RightAscension;
    double J2000Declination;
    double azmiuth;
    double elevation;
    double derotatorPositon;
    double targetRightAscension;
    double targetDeclination;
    double targetJ2000RightAscension;
    double targetJ2000Declination;
    double targetAzmiuth;
    double targetElevation;
    double targetDerotatorPosition;
    double axis1TrackError;
    double axis2TrackError;
    double axis3TrackError;
    unsigned short focusTypeIndex;
    unsigned short targetFocusTypeIndex;
    unsigned short coverIndex;
    unsigned short targetCoverIndex;
    double axis4Angle;    
    double coverPosition;    
    double targetAxis4Angle;    
    double axis1Speed;
    double axis2Speed;
    double axis3Speed;
    unsigned short trackType;
    unsigned short axis3Mode;
    char trackObjectName[48];
    double refractionCorrection;
    double axis1Encoder;
    double axis2Encoder;
    double axis3Encoder;    
    double axis1PMCorrection;
    double axis2PMCorrection;
    double axis3PMCorrection;
    double axis1ManualCorrection;
    double axis2ManualCorrection;
    double axis3ManualCorrection;
    double temperature[12];
    double humidity[12];
    unsigned short pieSide;
    unsigned short targetPieSide;
    unsigned short isAxis1FindHome;
    unsigned short isAxis2FindHome;
    unsigned short isAxis3FindHome;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_CONNECT defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_CONNECT] parameter.
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
struct _AT_GIMBAL_PARAM_CONNECT{
    //1:connect, 2:disconnect
    //according to ENUM_CONNECT
    unsigned short connect;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_FINDHOME defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_FINDHOME] parameter.
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
struct _AT_GIMBAL_PARAM_FINDHOME{
    unsigned short axis;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_TRACKSTAR defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_TRACKSTAR] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   20 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_TRACKSTAR{
    double rightAscension;
    double declination;
    unsigned short epoch;
    unsigned short speed;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_SETOBJECTNAME defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_SETOBJECTNAME] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   50 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  char: 1 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_SETOBJECTNAME{
    char objectName[48];
    unsigned short objectType;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_SLEWAZEL defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_SLEWAZEL] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   16 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_SLEWAZEL{
    double azimuth;
    double elevation;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_SLEWDEROTATOR defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_SLEWDEROTATOR] parameter.
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
struct _AT_GIMBAL_PARAM_SLEWDEROTATOR{
    double position;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_CONFIGDEROTATOR defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_CONFIGDEROTATOR] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   10 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_CONFIGDEROTATOR{
    unsigned short mode;
    double polarizingAngle; //only used in mode 2
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_SPEEDCORRECT defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_SPEEDCORRECT] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   10 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_SPEEDCORRECT{
    unsigned short axis;
    double correction;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_FIXEDMOVE defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_FIXEDMOVE] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   10 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_FIXEDMOVE{
    unsigned short axis;
    double speed;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_POSITIONCORRECT defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_POSITIONCORRECT] parameter.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   10 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  double: 8 bytes.
 *              unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_GIMBAL_PARAM_POSITIONCORRECT{
    unsigned short axis;
    double correction;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_COVERACTION defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_COVERACTION] parameter.
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
struct _AT_GIMBAL_PARAM_COVERACTION{
    unsigned short action;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_GIMBAL_PARAM_FOCUSACTION defines Gimbal's
 *          [_GIMBAL_INSTRUCTION_FOCUSACTION] parameter.
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
struct _AT_GIMBAL_PARAM_FOCUSACTION{
    unsigned short action;
};
#pragma pack()

#endif
