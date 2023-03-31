//
// Created by fumoumou on 23-3-20.
//

#ifndef TCPCLIENT_PORTOCOL_H
#define TCPCLIENT_PORTOCOL_H

#include "stdlib.h"
#include "unistd.h"
#include "string.h"

typedef unsigned int uint;

#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed : name existed"

#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed : name or pwd error or relogin"



enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUDEST,      /*注册请求*/
    ENUM_MSG_TYPE_REGIST_RESPOND,       /*注册回复*/

    ENUM_MSG_TYPE_LOGIN_REQUEST,        /*登录请求*/
    ENUM_MSG_TYPE_LOGIN_RESPOND,        /*登录回复*/
//    ENUM_MSG_TYPE_REGIST_RESPOND,
//    ENUM_MSG_TYPE_REGIST_RESPOND,
//    ENUM_MSG_TYPE_REGIST_RESPOND,
//    ENUM_MSG_TYPE_REGIST_RESPOND,
//    ENUM_MSG_TYPE_REGIST_RESPOND,
//    ENUM_MSG_TYPE_REGIST_RESPOND,
    ENUM_MSG_TYPE_MAX = 0x00ffffff
};


struct PDU{
    uint uiPDULen;       //协议单元大小
    uint uiMsgType;
    char caData[64];
    uint uiMsgLen;
    int caMsg[];
};

PDU *mkPDU(uint uiMsgLen);

#endif //TCPCLIENT_PORTOCOL_H
