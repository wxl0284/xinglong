#ifndef ATCCS_DOME_DEFINE
#define ATCCS_DOME_DEFINE

/*
 * ---------------------------------------------------------------------------------------------------
 * atccs_dome_define.h defines Dome's data structure.
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
* ------------------------------------------------------------------------------
* @brief    ENUM_AT_SLAVEDOME_INSTRUCTION enumerates slavedome's instruction.
* ------------------------------------------------------------------------------
*/
enum ENUM_AT_SLAVEDOME_INSTRUCTION
{
    _SLAVEDOME_INSTRUCTION_CONNECT,
    _SLAVEDOME_INSTRUCTION_SETDOMEPOSITION,
    _SLAVEDOME_INSTRUCTION_SETSHADEPOSITION,
    _SLAVEDOME_INSTRUCTION_SETROTATESPEED,
    _SLAVEDOME_INSTRUCTION_STOP,
    _SLAVEDOME_INSTRUCTION_SCUTTLEACTION,
    _SLAVEDOME_INSTRUCTION_SHADEACTION
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_SLAVEDOME_STATUS enumerates the SlaveDome's status
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_SLAVEDOME_STATUS
{
    _SLAVEDOME_STAUTS_DISCONNECT = 0x01,
    _SLAVEDOME_STAUTS_CONNECTING,
    _SLAVEDOME_STAUTS_DISCONNECTING,
    _SLAVEDOME_STAUTS_FREEZING,
    _SLAVEDOME_STAUTS_FREEZED,
    _SLAVEDOME_STAUTS_PARKING,
    _SLAVEDOME_STAUTS_PARKED,
    _SLAVEDOME_STAUTS_SLEWING,
    _SLAVEDOME_STAUTS_SLEWED,
    _SLAVEDOME_STAUTS_WAITINGFOLLOWING,
    _SLAVEDOME_STAUTS_FOLLOWING,    
    _SLAVEDOME_STAUTS_ERROR
};



/*!
* ----------------------------------------------------------------------------------------------------
* @brief    _AT_FULLOPENEDDOME_INSTRUCTION enumerates Full Opened Dome's instruction
* ----------------------------------------------------------------------------------------------------
*/
enum ENUM_AT_FULLOPENEDDOME_INSTRUCTION
{
     _FULLOPENEDDOME_INSTRUCTION_CONNECT = 0x01,
     _FULLOPENEDDOME_INSTRUCTION_OPENDOME
};

/**
 * -----------------------------------------------------------------------------
 * @brief ENUM_AT_FULLOPENEDDOME_STATUS enumerates the FullOpenedDome's status
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_FULLOPENEDDOME_STATUS
{
    _FULLOPENEDDOME_STATUS_DISCONNECT = 0x01,
    _FULLOPENEDDOME_STATUS_CONNECTING,
    _FULLOPENEDDOME_STATUS_DISCONNECTING,
    _FULLOPENEDDOME_STATUS_FREEZING,
    _FULLOPENEDDOME_STATUS_FREEZED,
    _FULLOPENEDDOME_STATUS_OPENING,
    _FULLOPENEDDOME_STATUS_CLOSING,
    _FULLOPENEDDOME_STATUS_OPENED,
    _FULLOPENEDDOME_STATUS_CLOSED
};


#pragma pack(1)
typedef struct SlaveDomeAttributes{
    _AT_PUBLIC_PROPERTY header;
    unsigned short hasShade;
    double maxSpeed;
    double diameter;
    unsigned short canSetDomePosition;
    unsigned short canSetShadePosition;
    unsigned short canSetSpeed;
    unsigned short canStop;
    unsigned short canOpenScuttle;
    unsigned short canSetShadeSpeed;
    unsigned short canConnect;
}_AT_SLAVEDOME_ATTRIBUTES;
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_STATUS defines SlaveDome's real time status.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   124 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_SLAVEDOME_STATUS{
    _AT_PUBLIC_STATUS status;
    unsigned short scuttleStatus;
    unsigned short shadeStatus;
    double domePosition;
    double scuttlePercent;
    double shadePosition;
    double targetDomePosition;
    double targetScuttlePosition;
    double targetShadePosition;	
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_PARAM_CONNECT defines Gimbal's
 *          [_SLAVEDOME_INSTRUCTION_CONNECT] parameter.
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
struct _AT_SLAVEDOME_PARAM_CONNECT{
    //1:connect, 2:disconnect
    //according to ENUM_CONNECT
    unsigned short connect;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_PARAM_SETDOMEPOSITION defines FullOpenedDome's
 *          [_SLAVEDOME_INSTRUCTION_SETDOMEPOSITION] parameter.
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
struct _AT_SLAVEDOME_PARAM_SETDOMEPOSITION{
    double position;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_PARAM_SETSHADEPOSITION defines FullOpenedDome's
 *          [_SLAVEDOME_INSTRUCTION_SETSHADEPOSITION] parameter.
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
struct _AT_SLAVEDOME_PARAM_SETSHADEPOSITION{
    double position;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_PARAM_SETROTATESPEED defines FullOpenedDome's
 *          [_SLAVEDOME_INSTRUCTION_SETROTATESPEED] parameter.
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
struct _AT_SLAVEDOME_PARAM_SETROTATESPEED{
    double speed;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_PARAM_SHUTTERACTION defines FullOpenedDome's
 *          [_SLAVEDOME_INSTRUCTION_SHUTTERACTION] parameter.
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
struct _AT_SLAVEDOME_PARAM_SHUTTERACTION{
    unsigned short action;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_SLAVEDOME_PARAM_SHADEACTION defines FullOpenedDome's
 *          [_SLAVEDOME_INSTRUCTION_SHADEACTION] parameter.
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
struct _AT_SLAVEDOME_PARAM_SHADEACTION{
    unsigned short action;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FULLOPENEDDOME_STATUS defines FullOpenedDome's property.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   72 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_FULLOPENEDDOME_PROPERTY{
    _AT_PUBLIC_PROPERTY header;
    double diameter;
    unsigned short canConnect;
    unsigned short canOpenDome;
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FULLOPENEDDOME_STATUS defines FullOpenedDome's real time status.
 * -----------------------------------------------------------------------------
 * @version:2.00.00 
 * @size:   80 bytes.
 * @date:   2017-05-15
 * @author: Geniuswei
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_FULLOPENEDDOME_STATUS{
    _AT_PUBLIC_STATUS status;
    double domePosition;
	
};
#pragma pack()



/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FULLOPENEDDOME_PARAM_CONNECT defines FullOpenedDome's
 *          [_FULLOPENEDDOME_INSTRUCTION_CONNECT] parameter.
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
struct _AT_FULLOPENEDDOME_PARAM_CONNECT{
    //1:connect, 2:disconnect
    //according to ENUM_CONNECT
    unsigned short connect;
};
#pragma pack()


/**
 * -----------------------------------------------------------------------------
 * @brief:  _AT_FULLOPENEDOME_PARAM_OPENDOME defines FullOpenedDome's
 *          [_FULLOPENEDDOME_INSTRUCTION_OPENDOME] parameter.
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
typedef struct _AT_FULLOPENEDOME_PARAM_OPENDOME{
    unsigned short action;
};
#pragma pack()
#endif
