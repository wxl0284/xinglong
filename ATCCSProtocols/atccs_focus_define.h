#ifndef ATCCS_FOCUS_DEFINE
#define ATCCS_FOCUS_DEFINE

/*
 * ---------------------------------------------------------------------------------------------------
 * atccs_focus_define.h defines Focus's data structure.
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
* ----------------------------------------------------------------------------------------------------
* @brief    ENUM_AT_FOCUS_INSTRUCTION enumerates Focus's instrution.
* ----------------------------------------------------------------------------------------------------
*/
enum ENUM_AT_FOCUS_INSTRUCTION
{
    _FOCUS_INSTRUCTION_CONNECT = 0x01,          // =1
    _FOCUS_INSTRUCTION_SETPOSITION,             // =2
    _FOCUS_INSTRUCTION_SETFIXEDSPEED,           // =3
    _FOCUS_INSTRUCTION_STOP,                    // =4
    _FOCUS_INSTRUCTION_ENABLETCOMPENSATE,       // =5
    _FOCUS_INSTRUCTION_SETTCOMPENSATE,          // =6
    _FOCUS_INSTRUCTION_FINDHOME                 // =7
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_FOCUS_STATUS enumerates the Filter's status
 * -----------------------------------------------------------------------------
 */
enum ENUM__AT_FOCUS_STATUS
{
    _FOCUS_STATUS_DISCONNECT = 0x01,
    _FOCUS_STATUS_CONNECTING,                   // =2
    _FOCUS_STATUS_DISCONNECTING,                // =3
    _FOCUS_STATUS_FREEZING,                     // =4
    _FOCUS_STATUS_FREEZED,                      // =5
    _FOCUS_STATUS_SLEWING,                      // =6
    _FOCUS_STATUS_SLEWED,                       // =7
    _FOCUS_STATUS_NOTFINDHOME,                  // =8
    _FOCUS_STATUS_HOMING,                       // =9
    _FOCUS_STATUS_EMERGENCYING,                 // =10
    _FOCUS_STATUS_EMERGENCY                     // =11
};



#pragma pack(1)
typedef struct FocusAttributes{
    _AT_PUBLIC_PROPERTY header;
    double maxValue;
    double minValue;
    double increment;
    unsigned short isFindHome;
    unsigned short isTCompensate;
    double maxSpeed;
    unsigned short canConnect;
    unsigned short canSetPosition;
    unsigned short canSetSpeed;
    unsigned short canStop;
    unsigned short canEnableTCompensate;
    unsigned short canFindHome;
}_AT_FOCUS_ATTRIBUTES;
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FOCUS_STATUS defines CCD's real time status.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   108 bytes.
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
struct _AT_FOCUS_STATUS{    
    _AT_PUBLIC_STATUS status;
    double position;
    double targetPosition;
    double temperature;    
    double TCompenensation;
    unsigned short isHomed;
    unsigned short isTCompensation;    
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FOCUS_PARAM_CONNECT defines Focus's
 *          [_FOCUS_INSTRUCTION_CONNECT] parameter.
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
struct _AT_FOCUS_PARAM_CONNECT{
    //1:connect, 2:disconnect
    //according to ENUM_CONNECT
    unsigned short connect;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FOCUS_PARAM_SETPOSITION defines Focus's
 *          [_FOCUS_INSTRUCTION_SETPOSITION] parameter.
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
struct _AT_FOCUS_PARAM_SETPOSITION{
    double position;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FOCUS_PARAM_SETFIXEDSPEED defines Focus's
 *          [_FOCUS_INSTRUCTION_SETFIXEDSPEED] parameter.
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
struct _AT_FOCUS_PARAM_SETFIXEDSPEED{
    double speed;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FOCUS_PARAM_ENABLETCOMPENSATE defines Focus's
 *          [_FOCUS_INSTRUCTION_ENABLETCOMPENSATE] parameter.
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
struct _AT_FOCUS_PARAM_ENABLETCOMPENSATE{
    unsigned short enbale;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FOCUS_PARAM_SETTCOMPENSATE defines Focus's
 *          [_FOCUS_INSTRUCTION_SETTCOMPENSATE] parameter.
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
struct _AT_FOCUS_PARAM_SETTCOMPENSATE
{
    double coefficient;
};
#pragma pack()
#endif
