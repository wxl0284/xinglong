#ifndef ATCCS_PUBLIC_DEFINE
#define ATCCS_PUBLIC_DEFINE
/*
 * ---------------------------------------------------------------------------------------------------
 * This file defines the public enumerates and structs of ATCCS.
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
 *  (version 1.00.00)
 * ---------------------------------------------------------------------------------------------------
 * version:				1.00.1
 * modified data:		2017-04-06
 * IDE:					VS2010
 * OS:					windows xp sp3
 *
 */

#include "atccs_global.h"


/*!
* ----------------------------------------------------------------------------------------------------
* @brief:   ENUM_AT_MSG_TYPE enumerates ATCCS's message.
* ----------------------------------------------------------------------------------------------------
*/
enum ENUM_AT_MSG_TYPE
{
    ENVDATAREPORT = 0x01,
    ATATTRIBUTE,
    ATATTRIBUTEACK,
    ATSTATUSREPORT,
    ATSTATUSACK,
    ATINSTRUCTION,
    ATINSTRUCTIONACK,
    ATPLAN,
    ATPLANACK,
    ATHEARTBEAT,
    ATTAKEOVER,
};

/*!
* ----------------------------------------------------------------------------------------------------
* @brief:   ENUM_AT_AT_TYPE enumerates ATCCS's at.
* ----------------------------------------------------------------------------------------------------
*/
enum ENUM_AT_AT_TYPE
{
    AT216 = 32,
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
* @brief:   ENUM_AT_DEVICE_TYPE enumerates ATCCS's devices of AT.
* ----------------------------------------------------------------------------------------------------
*/
enum ENUM_AT_DEVICE_TYPE{
    GIMBAL=64,
    CCD,
    FILTER,
    SLAVEDOME, //67
    FULLOPENEDDOME, //68
    FOCUS,  //69
    GUIDESCOPE,
    DPM
};

/*!
* ----------------------------------------------------------------------------------------------------
* @brief:   ENUM_AT_ENV_TYPE enumerates ATCCS's environmental devices.
* ----------------------------------------------------------------------------------------------------
*/
enum ENUM_AT_ENV_TYPE{
    ASC = 0x60,
    WS,
    CS,
    SQM,
    DIMM,
    DUST
};

/**
 * -----------------------------------------------------------------------------
 * @brief:  ENUM_AT_INSTRUCTION_RESULT enumerates ATCCS's instruction result.
 * -----------------------------------------------------------------------------
 */
enum ENUM_AT_INSTRUCTION_RESULT
{
    NOTEXECUTED,
    SUCCESS,
    PARAMOUTOFRANGE,
    CANNTEXECUTE,    
    SENDERROR
};

const int MAGIC = 0x1a2b3c4d;
const unsigned short VERSION = 1;
const unsigned int SIZE_ATCCSPHEADER = 28;
const unsigned int SIZE_INSTRUCTIONHEADER = 20;

enum ENUM_CONNECT{
    CONNECT = 1,
    DISCONNECT = 2
};

enum ENUM_ACTION
{
    OPEN = 0x01,
    CLOSE
};

enum ENUM_EPOCH
{
    
};


/**
 * -----------------------------------------------------------------------------
 * @brief:  _ATCCSPHeader defines ATCCS's message header.
 * -----------------------------------------------------------------------------
 * @magic:      =MAGIC, identify the ATCCS's message.
 * @version:    =VERSION, identify the ATCCS' message's version.
 * @msg:        =ENUM_AT_MSG_TYPE, identify the ATCCS's message's type.
 * @length:     =sizeof(_ATCCSPHeader)+length(data),identify the ATCCS's message's length.
 * @sequence:   identify the ATCCS's message's sequence.
 * @tv_sev:     timestamp in UTC seconds.
 * @tv_usec:    microsecond of timestamp.
 * @at:         ENUM_AT_AT_TYPE, identify the ATCCS's at.
 * @device:     ENUM_AT_DEVICE_TYPE, identify the ATCCS's device.
 * @env:        ENUM_AT_ENV_TYPE, identify the ATCCS's environmental device.
 * -----------------------------------------------------------------------------
 * @size:       28 bytes.
 * -----------------------------------------------------------------------------
 * @author:     Geniuswei
 * @date:       2017-05-12
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _ATCCSPHeader{
    UINT32 magic;
    unsigned short version;
    unsigned short msg;
    UINT32 length;
    UINT32 sequence;
    UINT32 tv_sec;
    UINT32 tv_usec;
    union
    {
        struct
        {
            unsigned short at;
            unsigned short device;
        }AT;
        UINT32 env;
    };
};
#pragma pack()



/**
 *------------------------------------------------------------------------------
 * @brief:      _AT_PUBLIC_PROPERTY defines AT Device's public property.
 *------------------------------------------------------------------------------
 * @version:    2.00.00
 * @size:       60 bytes.
 * @author:     Geniuswei
 * @date:       2017-05-15
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned short: 2 bytes.
 *              char: 1 bytes.
 *------------------------------------------------------------------------------
*/
#pragma pack(1)
struct _AT_PUBLIC_PROPERTY{
    char id[8];
    char name[48];
    unsigned short telescope;
    unsigned short type;
};
#pragma pack()
/**
 *------------------------------------------------------------------------------
 * @brief:      _AT_PUBLIC_STATUS defines AT Device's public status.
 *------------------------------------------------------------------------------
 * @version:    2.00.00
 * @size:       72 bytes.
 * @author:     Geniuswei
 * @date:       2017-05-15
 * -----------------------------------------------------------------------------
 * @type-info:  unsigned int: 4 bytes.
 *              unsigned long long: 8 bytes.
 *              char: 1 bytes.
 *------------------------------------------------------------------------------
*/
#pragma pack(1)
struct _AT_PUBLIC_STATUS{
    unsigned int status;
    unsigned int lastStatus;
    unsigned long long warning;
    unsigned long long  error;
    char errorString[48];
};
#pragma pack()

/**
 * -----------------------------------------------------------------------------
 * @brief:      _AT_OCCUPATION defines AT occupation.
 * -----------------------------------------------------------------------------
 * @size:       20 bytes.
 * -----------------------------------------------------------------------------
 * @author:     Geniuswei
 * @date:       2017-05-12
 * -----------------------------------------------------------------------------
 */
#pragma pack(1)
struct _AT_OCCUPATION
{
    unsigned int _user;
    unsigned short _at;
    unsigned short _occupation;
    unsigned int _start;
    unsigned int _end;
    unsigned int _priority;
};
#pragma pack()



/*!
 *------------------------------------------------------------------------------
 * @brief:      _AT_INSTRUCTION_HEADER defines AT instruction header.
 *------------------------------------------------------------------------------
 * @user:       The instruction's user.
 * @plan:       The instruction's plan.
 * @at:         The AT that execute the instruction.
 * @device:     The device that execute the instruction.
 * @sequence:   The instruction's sequence.
 * @operation:  The instruction identifier, = ENUM_*_INSTRUCTION.
 * -----------------------------------------------------------------------------
 * @size:       20 bytes.
 * -----------------------------------------------------------------------------
 * @author      Geniuswei
 * @date	2016-12-28
 * @modified	2017-03-31
 *------------------------------------------------------------------------------
*/
#pragma pack(1)
struct _AT_INSTRUCTION_HEADER{
    unsigned int user;
    unsigned int plan;
    unsigned short at;
    unsigned short device;
    unsigned int sequence;
    unsigned int operation;
};
#pragma pack()
/*!
 *------------------------------------------------------------------------------
 * @brief:       _AT_INSTRUCTION_RESULT defines the instruction's result.
 *------------------------------------------------------------------------------
 * @user:       The instruction's user.
 * @plan:       The instruction's plan.
 * @at:         The AT that execute the instruction.
 * @device:     The device that execute the instruction.
 * @sequence:   The instruction's sequence.
 * @operation:  The instruction's identifier, = ENUM_*_INSTRUCTION.
 * @result:     The instruction's result, = ENUM_AT_INSTRUCTION_RESULT.
 * -----------------------------------------------------------------------------
 * @size:       28 bytes.
 * -----------------------------------------------------------------------------
 * @author	Geniuswei
 * @date	2016-12-28
 * @modified    2017-03-31
 *------------------------------------------------------------------------------
*/
#pragma pack(1)
struct _AT_INSTRUCTION_RESULT{
    unsigned int user;
    unsigned int plan;
    unsigned short at;
    unsigned short device;
    unsigned int sequence;
    unsigned int timeout;
    unsigned int operation;
    unsigned int result;
};
#pragma pack()

#endif
