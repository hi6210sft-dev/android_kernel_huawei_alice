/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AtExtendCmd.c
  版 本 号   : 初稿
  作    者   : f62575
  生成日期   : 2011年10月3日
  最近修改   :
  功能描述   : AT扩展命令处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年10月3日
    作    者   : f62575
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"
#include "Taf_Tafm_Remote.h"
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/27, begin */
#include "AtDeviceCmd.h"
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/27, end */
#include "AtCmdPacketProc.h"

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
#include "AtCmdCallProc.h"
/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

#include "AtTestParaCmd.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_EXTENDCMD_C
/*lint +e767 +e960 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 示例: ^CMDX 命令是不受E5密码保护命令，且在+CLAC列举所有命令时不显示，第一个参数是不带双引号的字符串,
        第二个参数是带双引号的字符串，第三个参数是整数型参数

   !!!!!!!!!!!注意: param1和param2是示例，实际定义命令时应尽量定义的简短(可提高解析效率)!!!!!!!!!!!!!

    {AT_CMD_CMDX,
    At_SetCmdxPara, AT_SET_PARA_TIME, At_QryCmdxPara, AT_QRY_PARA_TIME, At_TestCmdxPara, AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_E5_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE,
    (VOS_UINT8*)"^CMDX", (VOS_UINT8*)"(@param1),(param2),(0-255)"},
*/
/* SMS命令表 */

/* Modified by s00217060 for V7R1C50_At_Abort, 2012-9-18, begin */
/* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-25, begin */
/* 主动上报相关命令设置和查询时需要等待回复，添加等待设置回复时间和等待查询回复时间 */
const AT_SMS_CMD_TAB_STRU gastAtSmsCmdTab[]=
{
    /* Modified by f00179208 for DTS2012032205203, 2012-03-27, Begin */
    /* SMS */
    {AT_CMD_CMGS,
    /* Modified by y00245242 for VoLTE_PhaseIII, 2014-1-3, begin */
    At_SetCmgsPara, AT_SMS_CMGS_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
    /* Modified by y00245242 for VoLTE_PhaseIII, 2014-1-3, end */
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMGS",    (VOS_UINT8*)"(da),(0-255)",                                                                    (TAF_UINT8*)"(0-255)"},

    {AT_CMD_CMGW,
    At_SetCmgwPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMGW",    (VOS_UINT8*)"(oa),(0-255),(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")",  (TAF_UINT8*)"(0-255),(0-4)"},

    {AT_CMD_CMGR,
    At_SetCmgrPara, AT_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMGR",    (VOS_UINT8*)"(0-65535)",                                                                       (TAF_UINT8*)"(0-65535)"},

    {AT_CMD_CMGL,
    At_SetCmglPara, AT_SET_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMGL",    (VOS_UINT8*)"(\"REC UNREAD\",\"REC READ\",\"STO UNSENT\",\"STO SENT\",\"ALL\")",               (TAF_UINT8*)"(0-4)"},

    {AT_CMD_CMGC,
    At_SetCmgcPara, AT_SMS_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMGC",    (VOS_UINT8*)"(0-255),(0-255),(0-255),(0-255),(da),(0-255)",                                    (TAF_UINT8*)"(0-255)"},

    {AT_CMD_CMSS,
    /* Modified by y00245242 for VoLTE_PhaseIII, 2014-1-3, begin */
    At_SetCmssPara, AT_SMS_CMSS_SET_PARA_TIME, At_CmdTestProcOK, AT_NOT_SET_TIME,
    /* Modified by y00245242 for VoLTE_PhaseIII, 2014-1-3, end */
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMSS",    (VOS_UINT8*)"(0-255),(da),(0-255)",                                                            (TAF_UINT8*)"(0-255),(da),(0-255)"},

    {AT_CMD_CNMA,
    At_SetCnmaPara, AT_SMS_SET_PARA_TIME, AT_TestCnmaPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CNMA",    TAF_NULL_PTR,                                                                                  (TAF_UINT8*)"(0-2),(0-65535)"},
    /* Modified by f00179208 for DTS2012032205203, 2012-03-27, End */
};

const TAF_UINT16 gusAtSmsCmdNum = sizeof(gastAtSmsCmdTab)/sizeof(AT_SMS_CMD_TAB_STRU);

AT_PAR_CMD_ELEMENT_STRU g_astAtExtendCmdTbl[] =
{
    /* Added by f62575 for AT Project, 2011-10-24, begin */
    /* PHONEBOOK */
    /* Modified by l00198894 for C50_IPC Project, 2012/02/20, begin */
    {AT_CMD_CPBS,
    At_SetCpbsPara,     AT_SET_PARA_TIME,   At_QryCpbsPara,  AT_QRY_PARA_TIME,  AT_TestCpbsPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CPBS",    (TAF_UINT8*)"(\"SM\",\"ON\",\"EN\",\"FD\")"},
    /* Modified by l00198894 for C50_IPC Project, 2012/02/20, end */

    {AT_CMD_CPBR2,
    At_SetCpbr2Para,     AT_SET_PARA_TIME,   TAF_NULL_PTR,    AT_NOT_SET_TIME,   AT_TestCpbrPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CPBR",    (TAF_UINT8*)"(1-65535),(1-65535)"},

    {AT_CMD_CPBW2,
    At_SetCpbwPara2,    AT_SET_PARA_TIME,   TAF_NULL_PTR,    AT_NOT_SET_TIME,   AT_TestCpbrPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CPBW",    (TAF_UINT8*)"(1-65535),(number),(0-255),(text)"},

    {AT_CMD_CNUM,
    At_SetCnumPara,     AT_QRY_PARA_TIME,   TAF_NULL_PTR,    AT_NOT_SET_TIME,   At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CNUM",    TAF_NULL_PTR},

     /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    {AT_CMD_CPBF,
    At_SetCpbfPara,     AT_SET_PARA_TIME,   TAF_NULL_PTR,    AT_NOT_SET_TIME,   AT_TestCpbrPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CPBF",    (TAF_UINT8*)"(number),(text)"},
     /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* USIM */
    {AT_CMD_CSIM,
    At_SetCsimPara, AT_SET_PARA_TIME, TAF_NULL_PTR,    AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_CLAC_IS_INVISIBLE_E5 | CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CSIM",    (TAF_UINT8*)"(1-520),(cmd)"},

    {AT_CMD_CCHO,
    At_SetCchoPara, AT_SET_PARA_TIME, TAF_NULL_PTR,    AT_NOT_SET_TIME,  At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (TAF_UINT8*)"+CCHO",    (TAF_UINT8*)"(dfname)"},

    {AT_CMD_CCHC,
    At_SetCchcPara, AT_SET_PARA_TIME, TAF_NULL_PTR,    AT_NOT_SET_TIME,  At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (TAF_UINT8*)"+CCHC",    (TAF_UINT8*)"(0-4294967295)"},

    /* Added by j00174725 for DTS2015252902036 (CGLA (30->90)), 2015-05-29, begin */
    {AT_CMD_CGLA,
    At_SetCglaPara, AT_SET_CGLA_PARA_TIME, TAF_NULL_PTR,    AT_NOT_SET_TIME,  At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (TAF_UINT8*)"+CGLA",    (TAF_UINT8*)"(0-4294967295),(8-522),(command)"},
    /* Added by j00174725 for DTS2015252902036 (CGLA (30->90)), 2015-05-29, End */

    /* Added by f62575 for AT Project DTS2011110802485, 2011-11-08, begin */
    {AT_CMD_CPIN,
    At_SetCpinPara, AT_SET_PARA_TIME, At_QryCpinPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CPIN",    (TAF_UINT8*)"(@pin),(@newpin)"},
    /* Added by f62575 for AT Project DTS2011110802485, 2011-11-08, end   */

    {AT_CMD_CRSM,
    At_SetCrsmPara,  AT_SET_PARA_TIME, TAF_NULL_PTR,      AT_NOT_SET_TIME,  At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CRSM",  (TAF_UINT8*)"(0-255),(1-65535),(0-255),(0-255),(0-255),(cmd),(pathid)"},

    /* SMS CONFIG */
    /* Added by 傅映君/f62575 for AT Project, SIM卡保护标志确认, 2011/11/15, begin */
    {AT_CMD_CSCS,
    At_SetCscsPara,     AT_NOT_SET_TIME, At_QryCscsPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CSCS",    (TAF_UINT8*)"(\"IRA\",\"UCS2\",\"GSM\")"},

    /* Added by 傅映君/f62575 for AT Project, SIM卡保护标志确认, 2011/11/15, end */
    {AT_CMD_CMEE,
    At_SetCmeePara,     AT_NOT_SET_TIME, At_QryCmeePara,    AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CMEE",    (TAF_UINT8*)"(0-2)"},

    {AT_CMD_CEER,
    At_SetCeerPara,     AT_NOT_SET_TIME, TAF_NULL_PTR,      AT_NOT_SET_TIME ,   At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE,
    (TAF_UINT8*)"+CEER",    TAF_NULL_PTR},

    {AT_CMD_CSDH,
    At_SetCsdhPara,     AT_NOT_SET_TIME, At_QryCsdhPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CSDH",    (TAF_UINT8*)"(0,1)"},

    {AT_CMD_CNMI,
    At_SetCnmiPara,     AT_SET_PARA_TIME,At_QryCnmiPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED,       CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CNMI",    (TAF_UINT8*)"(0-2),(0-3),(0,2),(0-2),(0,1)"},

    {AT_CMD_CMMS,
    At_SetCmmsPara,     AT_SET_PARA_TIME, At_QryCmmsPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMMS",  (VOS_UINT8*)"(0-2)"},

    {AT_CMD_CMGF,
    At_SetCmgfPara,     AT_NOT_SET_TIME,  At_QryCmgfPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CMGF",    (VOS_UINT8*)"(0,1)"},

    {AT_CMD_CGSMS,
    At_SetCgsmsPara,    AT_NOT_SET_TIME,  At_QryCgsmsPara,  AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGSMS",   (VOS_UINT8*)"(0-3)"},

    {AT_CMD_CSCA,
    At_SetCscaPara,     AT_SET_PARA_TIME, At_QryCscaPara,   AT_QRY_PARA_TIME,   At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CSCA",    (VOS_UINT8*)"(sca),(0-255)"},

    {AT_CMD_CSMS,
    At_SetCsmsPara,     AT_SET_PARA_TIME, At_QryCsmsPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CSMS",    (VOS_UINT8*)"(0,1)"},

    {AT_CMD_CSMP,
    At_SetCsmpPara,     AT_SET_PARA_TIME, At_QryCsmpPara,   AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CSMP",    TAF_NULL_PTR},
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)

    {AT_CMD_CPMS,
    At_SetCpmsPara,     AT_SET_PARA_TIME, At_QryCpmsPara,   AT_QRY_PARA_TIME,   AT_TestCpmsPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\",\"ME\"),(\"SM\",\"ME\"),(\"SM\",\"ME\")"},
#else

    {AT_CMD_CPMS,
    At_SetCpmsPara,     AT_SET_PARA_TIME, At_QryCpmsPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"},
#endif

    {AT_CMD_CMGD,
    At_SetCmgdPara,     AT_SET_PARA_TIME, TAF_NULL_PTR,     AT_NOT_SET_TIME ,   At_QryCmgdPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMGD",    (VOS_UINT8*)"(0-254),(0-4)"},
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    {AT_CMD_CSCB,
    At_SetCscbPara,     AT_SET_PARA_TIME, At_QryCscbPara,   AT_QRY_PARA_TIME,   AT_TestCscbPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"+CSCB",    (VOS_UINT8*)"(0,1),(MIDS),(DCSS)"},
#endif
    /* Added by f62575 for AT Project, 2011-10-24, end */

    /* 语音新增AT命令 */
    {AT_CMD_CLVL,
    At_SetClvlPara,     AT_SET_PARA_TIME, At_QryClvlPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CLVL", (VOS_UINT8*)"(0-5)"},

    /* CS */
    {AT_CMD_CHUP,
    At_SetChupPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CHUP", VOS_NULL_PTR},

    /* Modified by A00165503 for DTS2012091405101, 2012-09-12, Begin */
    {AT_CMD_CLCC,
    At_SetClccPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CLCC", VOS_NULL_PTR},
    /* Modified by A00165503 for DTS2012091405101, 2012-09-12, End */

    /* Modified by l00198894 for DTS2013012903698, 2013/01/29, begin */
    {AT_CMD_CPAS,
    At_SetCpasPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    AT_TestCpasPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CPAS", VOS_NULL_PTR},
    /* Modified by l00198894 for DTS2013012903698, 2013/01/29, end */

    {AT_CMD_CBST,
    At_SetCbstPara,     AT_NOT_SET_TIME,  At_QryCbstPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CBST", (VOS_UINT8*)"(134),(1),(0)"},

    {AT_CMD_CMOD,
    At_SetCmodPara,     AT_NOT_SET_TIME,  At_QryCmodPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CMOD", (VOS_UINT8*)"(0)"},

    {AT_CMD_CSTA,
    At_SetCstaPara,     AT_NOT_SET_TIME,  At_QryCstaPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CSTA", (VOS_UINT8*)"(0-255)"},

    {AT_CMD_VTS,
    At_SetVtsPara,      AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_TestVtsPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+VTS", (VOS_UINT8*)"(@key)"},

    {AT_CMD_CRC,
    At_SetCrcPara,      AT_NOT_SET_TIME,  At_QryCrcPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CRC", (VOS_UINT8*)"(0,1)"},

    /* Modified by z00161729 for DTS2013082903019, 2013-9-9, begin */
    {AT_CMD_CLIP,
    At_SetClipPara,     AT_NOT_SET_TIME,  At_QryClipPara,   AT_QRY_SS_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CLIP", (VOS_UINT8*)"(0,1)"},

    {AT_CMD_CLIR,
    At_SetClirPara,     AT_NOT_SET_TIME,  At_QryClirPara,   AT_QRY_SS_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CLIR", (VOS_UINT8*)"(0,1,2)"},

    {AT_CMD_COLP,
    At_SetColpPara,     AT_NOT_SET_TIME,  At_QryColpPara,   AT_QRY_SS_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COLP", (VOS_UINT8*)"(0,1)"},
    /* Modified by z00161729 for DTS2013082903019, 2013-9-9, end */

    {AT_CMD_CCUG,
    At_SetCcugPara,     AT_NOT_SET_TIME,  At_QryCcugPara,   AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CCUG", (VOS_UINT8*)"(0,1),(0-10),(0-3)"},

    {AT_CMD_CSSN,
    At_SetCssnPara,     AT_SET_PARA_TIME,  At_QryCssnPara,   AT_QRY_PARA_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CSSN", (VOS_UINT8*)"(0,1),(0,1)"},
    /* Modified by f62575 for DTS2012111303714 2012-11-14, begin */
    {AT_CMD_CHLD,
    At_SetChldPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CHLD", (VOS_UINT8*)"(0-5,11-19,21-29)"},
    /* Modified by f62575 for DTS2012111303714 2012-11-14, end   */

    {AT_CMD_CUUS1,
    At_SetCuus1Para,    AT_SET_PARA_TIME, At_QryCuus1Para,  AT_QRY_PARA_TIME,   At_TestCuus1Para, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CUUS1", (VOS_UINT8*)"(0,1),(0,1),(0-6)"},

    /* Modified by z00161729 for DTS2013082903019, 2013-9-9, begin */
    /* SSA */
    {AT_CMD_CCWA,
    At_SetCcwaPara,     AT_SET_SS_PARA_TIME, At_QryCcwaPara,   AT_NOT_SET_TIME,     At_TestCcwaPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CCWA", (VOS_UINT8*)"(0,1),(0-2),(1-255)"},

    {AT_CMD_CCFC,
    At_SetCcfcPara,     AT_SET_SS_PARA_TIME, TAF_NULL_PTR,     AT_NOT_SET_TIME,    At_TestCcfcPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CCFC", (VOS_UINT8*)"(0-5),(0-4),(number),(0-255),(1-255),(subaddr),(0-255),(1-30)"},
    /* Modified by z00161729 for DTS2013082903019, 2013-9-9, end */

    {AT_CMD_CUSD,
    /* Modified by y00245242 for VoLTE_PhaseIII, 2014-1-3, begin */
    At_SetCusdPara,     AT_SS_CUSD_SET_PARA_TIME, At_QryCusdPara,   AT_QRY_PARA_TIME,    At_TestCusdPara, AT_NOT_SET_TIME,
    /* Modified by y00245242 for VoLTE_PhaseIII, 2014-1-3, end */
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CUSD", (VOS_UINT8*)"(0-2),(str),(0-255)"},

    {AT_CMD_GMR,
    At_SetCgmrPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+GMR", VOS_NULL_PTR},

    {AT_CMD_GMI,
    At_SetCgmiPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+GMI", VOS_NULL_PTR},

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /* OTHER */
    {AT_CMD_CTFR,
    At_SetCtfrPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_CLAC_IS_INVISIBLE,
    (VOS_UINT8*)"+CTFR", (VOS_UINT8*)"(number),(0-255),(subaddr),(0-255)"},
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* Modified by z00161729 for DTS2013082903019, 2013-9-9, begin */
    {AT_CMD_CPWD,
    At_SetCpwdPara,     AT_SET_SS_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_TestCpwdPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CPWD", (VOS_UINT8*)"(\"P2\",\"SC\",\"AO\",\"OI\",\"OX\",\"AI\",\"IR\",\"AB\",\"AG\",\"AC\",\"PS\"),(@oldpwd),(@newpwd)"},

    {AT_CMD_CLCK,
    At_SetClckPara,     AT_SET_SS_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_TestClckPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CLCK", (VOS_UINT8*)"(\"P2\",\"SC\",\"AO\",\"OI\",\"OX\",\"AI\",\"IR\",\"AB\",\"AG\",\"AC\",\"PS\",\"FD\"),(0-2),(psw),(1-255)"},
    /* Modified by z00161729 for DTS2013082903019, 2013-9-9, end */

    {AT_CMD_CGATT,
    At_SetCgattPara,    AT_CGATT_SET_PARA_TIME,  At_QryCgattPara, AT_QRY_PARA_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGATT",      (VOS_UINT8*)"(0,1)"},

    /* Modified by s46746 for V7R1 phase II , 2011-10-18, begin */
#if(FEATURE_ON == FEATURE_LTE)
    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    At_AbortCopsPara,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2,7)"},
#else

    {AT_CMD_COPS,
    At_SetCopsPara,     AT_COPS_SPEC_SRCH_TIME, At_QryCopsPara,   AT_QRY_PARA_TIME,   At_TestCopsPara, AT_COPS_LIST_SRCH_TIME,
    At_AbortCopsPara,   AT_COPS_LIST_ABORT_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+COPS",       (VOS_UINT8*)"(0,1,3),(0-2),(@oper),(0,2)"},
#endif
    /* Modified by s46746 for V7R1 phase II , 2011-10-18, end */

    {AT_CMD_CGCLASS,
    At_SetCgclassPara,  AT_SET_PARA_TIME, At_QryCgclassPara, AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGCLASS",    (VOS_UINT8*)"(\"A\")"},

    /* Modified by f00179208 for DTS2012060804905, 2012-06-18 Begin */
    {AT_CMD_CFUN,
    At_SetCfunPara,     AT_SET_PARA_TIME, At_QryCfunPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_E5_IS_LOCKED | CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CFUN",       (VOS_UINT8*)"(0,1,4,5,6,7,8),(0,1)"},
    /* Modified by f00179208 for DTS2012060804905, 2012-06-18 End */

    {AT_CMD_CGMI,
    At_SetCgmiPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGMI",VOS_NULL_PTR},

    {AT_CMD_CGMM,
    At_SetCgmmPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGMM",VOS_NULL_PTR},

    {AT_CMD_GMM,
    At_SetCgmmPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+GMM",VOS_NULL_PTR},

    {AT_CMD_CGMR,
    At_SetCgmrPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGMR",VOS_NULL_PTR},
    /* Modified by Y00213812 for IMEI_VERIFY Project, 2013-05-23, begin */
    {AT_CMD_CGSN,
    At_SetCgsnPara,     AT_SET_PARA_TIME,  VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGSN",VOS_NULL_PTR},

    {AT_CMD_GSN,
    At_SetCgsnPara,     AT_SET_PARA_TIME,  VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+GSN", VOS_NULL_PTR},
    /* Modified by Y00213812 for IMEI_VERIFY Project, 2013-05-23, end */

    {AT_CMD_CIMI,
    At_SetCimiPara,     AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_E5_IS_LOCKED,
    (VOS_UINT8*)"+CIMI",VOS_NULL_PTR},

    {AT_CMD_CSQ,
    At_SetCsqPara,      AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CSQ",(VOS_UINT8*)"(0-31,99),(99)"},

    {AT_CMD_CBC,
    At_SetCbcPara,      AT_SET_PARA_TIME, VOS_NULL_PTR,     AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_STICK,
    (VOS_UINT8*)"+CBC",        (VOS_UINT8*)"(0-3),(0-100)"},

    {AT_CMD_CLAC,
    At_SetCLACPara,     AT_NOT_SET_TIME,  VOS_NULL_PTR,     AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CLAC",VOS_NULL_PTR},

    {AT_CMD_GCAP,
    At_SetGcapPara,     AT_NOT_SET_TIME,  VOS_NULL_PTR,     AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+GCAP",VOS_NULL_PTR},

    {AT_CMD_CPLS,
    At_SetCplsPara,     AT_SET_PARA_TIME, At_QryCplsPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CPLS",       (VOS_UINT8*)"(0,1,2)"},

#if(FEATURE_ON == FEATURE_LTE)
    {AT_CMD_CPOL,
    At_SetCpolPara,     AT_SET_PARA_TIME, At_QryCpolPara,   AT_QRY_PARA_TIME,    At_TestCpolPara, AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CPOL",       (VOS_UINT8*)"(1-100),(0-2),(oper),(0,1),(0,1),(0,1),(0,1)"},
#else

    {AT_CMD_CPOL,
    At_SetCpolPara,     AT_SET_PARA_TIME, At_QryCpolPara,   AT_QRY_PARA_TIME,    At_TestCpolPara, AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CPOL",       (VOS_UINT8*)"(1-100),(0-2),(oper),(0,1),(0,1),(0,1)"},
#endif

    /* Modified by s46746 for SS FDN&Call Control, 2013-05-31, begin */
    {AT_CMD_CREG,
    At_SetCregPara,     AT_SET_PARA_TIME,  At_QryCregPara,   AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"+CREG",    (VOS_UINT8*)"(0-2)"},

    {AT_CMD_CGREG,
    At_SetCgregPara,    AT_SET_PARA_TIME,  At_QryCgregPara,  AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"+CGREG",   (VOS_UINT8*)"(0-2)"},

    /* Modified by l00198894 for PS Project, 2012/01/05, begin */
#if(FEATURE_ON == FEATURE_LTE)
    {AT_CMD_CEREG,
    AT_SetCeregPara,    AT_SET_PARA_TIME,  At_QryCeregPara,  AT_QRY_PARA_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"+CEREG",   (VOS_UINT8*)"(0-2)"},
#endif
    /* Modified by s46746 for SS FDN&Call Control, 2013-05-31, end */

    {AT_CMD_CGDCONT,
    AT_SetCgdcontPara, AT_SET_PARA_TIME, AT_QryCgdcontPara, AT_QRY_PARA_TIME, At_TestCgdcont, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGDCONT",     (VOS_UINT8*)CGDCONT_CMD_PARA_STRING},

    {AT_CMD_CGDSCONT,
    AT_SetCgdscontPara, AT_SET_PARA_TIME, AT_QryCgdscontPara, AT_QRY_PARA_TIME, At_TestCgdscont, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGDSCONT",    (VOS_UINT8*)CGDSCONT_CMD_PARA_STRING},

    {AT_CMD_CGTFT,
    AT_SetCgtftPara, AT_SET_PARA_TIME, AT_QryCgtftPara, AT_QRY_PARA_TIME, At_TestCgtft, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGTFT",       (VOS_UINT8*)CGTFT_CMD_PARA_STRING},

    {AT_CMD_CGACT,
    AT_SetCgactPara, AT_ACT_PDP_TIME, AT_QryCgactPara, AT_QRY_PARA_TIME, At_TestCgact, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGACT",       (VOS_UINT8*)CGACT_CMD_PARA_STRING},

    {AT_CMD_CGCMOD,
    AT_SetCgcmodPara, AT_MOD_PDP_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME, At_TestCgcmod, AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGCMOD",      (VOS_UINT8*)CGCMOD_CMD_PARA_STRING},

    {AT_CMD_CGPADDR,
    AT_SetCgpaddrPara, AT_SET_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME, At_TestCgpaddr, AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGPADDR",     (VOS_UINT8*)CGPADDR_CMD_PARA_STRING},

    {AT_CMD_CGEQNEG,
    AT_SetCgeqnegPara,  AT_SET_PARA_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   At_TestCgeqnegPara, AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGEQNEG",     (VOS_UINT8*)CGEQNEG_CMD_PARA_STRING},

    {AT_CMD_CGANS,
    AT_SetCgansPara,    AT_SET_PARA_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   At_TestCgansPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGANS",       (VOS_UINT8*)CGANS_CMD_PARA_STRING},

    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-25, Begin */
    {AT_CMD_CGANS_EXT,
    AT_SetCgansPara,    AT_SET_PARA_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   At_TestCgansExtPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"^CGANS",       (VOS_UINT8*)CGANS_EXT_CMD_PARA_STRING},

    {AT_CMD_APENDPPP,
    AT_SetApEndPppPara,    AT_NOT_SET_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"^APENDPPP",       VOS_NULL_PTR},

    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-25, End */

    {AT_CMD_CGDATA,
    At_SetCgdataPara,   AT_SET_PARA_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   At_TestCgdataPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGDATA",      (VOS_UINT8*)CGDATA_CMD_PARA_STRING},
    /* Modified by l00198894 for PS Project, 2012/01/05, end */

    {AT_CMD_CGEQREQ,
    AT_SetCgeqreqPara,  AT_SET_PARA_TIME, AT_QryCgeqreqPara, AT_QRY_PARA_TIME,  At_TestCgeqreqPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGEQREQ",    (VOS_UINT8*)CGEQREQ_CMD_PARA_STRING},

    /* +CGEQMIN命令的测试显示结果与+CGEQREQ是一致的，故使用同一个测试函数 */
    {AT_CMD_CGEQMIN,
    AT_SetCgeqminPara,  AT_SET_PARA_TIME, At_QryCgeqminPara, AT_QRY_PARA_TIME,  At_TestCgeqreqPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGEQMIN",    (VOS_UINT8*)CGEQMIN_CMD_PARA_STRING},

    /* Modified by l00198894 for PS Project, 2012/01/06, begin */
    {AT_CMD_CGAUTO,
    AT_SetCgautoPara,   AT_SET_PARA_TIME, AT_QryCgautoPara,  AT_QRY_PARA_TIME,  At_TestCgautoPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CGAUTO",    (VOS_UINT8*)"(0,1)"},
    /* Modified by l00198894 for PS Project, 2012/01/06, end */

    {AT_CMD_CTZR,
    At_SetCtzrPara,     AT_SET_PARA_TIME, At_QryCtzrPara,    AT_QRY_PARA_TIME,  VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"+CTZR",    (VOS_UINT8*)"(0,1)"},

/* Added by c00184452 for PS Project 2011-01-07  Begin*/
#if (FEATURE_ON == FEATURE_LTE)

    {AT_CMD_CGCONTRDP,
    atSetCgcontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgcontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGCONTRDP",    (VOS_UINT8*)"(1-31)"},

    {AT_CMD_CGSCONTRDP,
    atSetCgscontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgscontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGSCONTRDP",    (VOS_UINT8*)"(1-31)"},

    {AT_CMD_CGTFTRDP,
    atSetCgtftrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,    AT_NOT_SET_TIME,  At_TestCgtftrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGTFTRDP",    (VOS_UINT8*)"(1-31)"},

    {AT_CMD_CGEQOS,
    atSetCgeqosPara, AT_SET_PARA_TIME, atQryCgeqosPara,   AT_QRY_PARA_TIME,  At_TestCgeqos,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGEQOS",    (VOS_UINT8*)"(1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)"},

    {AT_CMD_CGEQOSRDP,
    atSetCgeqosrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgeqosrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGEQOSRDP",    (VOS_UINT8*)"(1-31)"},

#endif
/* Added by c00184452 for PS Project 2011-01-07  End*/

    /* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/27, begin */
    {AT_CMD_CPOS,
    AT_SetCposPara,          AT_SET_PARA_TIME,   VOS_NULL_PTR,  AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CPOS",    VOS_NULL_PTR},

    {AT_CMD_CPOSR,
    AT_SetCposrPara,          AT_NOT_SET_TIME,   AT_QryCposrPara,  AT_NOT_SET_TIME,  AT_TestCposrPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CPOSR",    (VOS_UINT8 *)"(0,1)"},
    /* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/27, end */

    /* Added by A00165503 for DTS2012091405101, 2012-09-12, Begin */
    {AT_CMD_CMUT,
    AT_SetCmutPara,     AT_SET_PARA_TIME,   AT_QryCmutPara,     AT_QRY_PARA_TIME,   AT_TestCmutPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8 *)"+CMUT",   (VOS_UINT8 *)"(0,1)"},
    /* Added by A00165503 for DTS2012091405101, 2012-09-12, End */
    /* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    {AT_CMD_COPN,
    AT_SetCopnPara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,       AT_NOT_SET_TIME,   At_CmdTestProcOK,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_LIMITED_NULL,
    (VOS_UINT8 *)"+COPN",   VOS_NULL_PTR},
    /* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

    /* Added by m00217266 for FD Optimize, 2014-6-13, begin */
    {AT_CMD_RELEASERRC,
    At_SetReleaseRrc,          AT_SET_PARA_TIME, VOS_NULL_PTR,  AT_NOT_SET_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"+CNMPSD",    VOS_NULL_PTR},
    /* Added by m00217266 for FD Optimize, 2014-6-13, end */

    /* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, begin */
#if (FEATURE_ON == FEATURE_IMS)
    {AT_CMD_CIREG,
    AT_SetCiregPara,     AT_SET_PARA_TIME,   AT_QryCiregPara,       AT_QRY_PARA_TIME,   AT_TestCiregPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
    (VOS_UINT8 *)"+CIREG",   (VOS_UINT8 *)"(0-2)"},

    {AT_CMD_CIREP,
    AT_SetCirepPara,     AT_SET_PARA_TIME,   AT_QryCirepPara,       AT_QRY_PARA_TIME,   AT_TestCirepPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
    (VOS_UINT8 *)"+CIREP",   (VOS_UINT8 *)"(0,1)"},

    /* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, Begin */
    {AT_CMD_CEVDP,
    AT_SetCevdpPara, AT_SET_PARA_TIME,   AT_QryCevdpPara,     AT_QRY_PARA_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
    (VOS_UINT8*)"+CEVDP", (VOS_UINT8*)"(1-4)"},
    /* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, End */

#endif
    /* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, end */

#if (FEATURE_ON == FEATURE_AT_HSUART)
    /* Added by z00189113 for UART-MODEM Project, 2013-9-23 Begin */
    {AT_CMD_IPR,
    AT_SetIprPara,  AT_NOT_SET_TIME,    AT_QryIprPara,  AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    /* Modified by A00165503 for DTS2014031207569, 2014-04-08, Begin */
    (VOS_UINT8 *)"+IPR",    (VOS_UINT8 *)"(0,9600,19200,38400,57600,115200,230400,460800,921600,1152000,1500000,2000000,3000000)"},
    /* Modified by A00165503 for DTS2014031207569, 2014-04-08, End */

    {AT_CMD_ICF,
    AT_SetIcfPara,  AT_NOT_SET_TIME,   AT_QryIcfPara,   AT_NOT_SET_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8 *)"+ICF",    (VOS_UINT8 *)"(1-6),(0-3)"},

    {AT_CMD_IFC,
    AT_SetIfcPara,  AT_NOT_SET_TIME,   AT_QryIfcPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8 *)"+IFC",    (VOS_UINT8 *)"(0,2),(0,2)"},
    /* Added by z00189113 for UART-MODEM Project, 2013-9-23 End */
#endif

    /* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    {AT_CMD_CECALL,
    AT_SetCecallPara,  AT_SET_PARA_TIME,   AT_QryCecallPara,   AT_QRY_PARA_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_ERROR,    CMD_TBL_NO_LIMITED,
    (VOS_UINT8 *)"+CECALL",    (VOS_UINT8 *)"(0-3)"},
#endif
    /* Added by n00269697 for V3R3C60_eCall项目, 2014-3-29, end   */

    /* Add by j00174725 for CCLK, 2014-11-18, Begin */
    {AT_CMD_CCLK,
    AT_SetCclkPara,  AT_NOT_SET_TIME,   AT_QryCclkPara,   AT_NOT_SET_TIME,    VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8 *)"+CCLK",    VOS_NULL_PTR},

    /* Add by j00174725 for CCLK, 2014-11-18, End */
};
/* Modified by s00217060 for V7R1C50_At_Abort, 2012-9-18, end */
/* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-25, end */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* Modified  by s00217060 for V7R1C50_At_Abort, 2012/9/25, begin */

/*****************************************************************************
 函 数 名  : At_RegisterExCmdTable
 功能描述  : 注册扩展命令表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月21日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 At_RegisterExCmdTable(VOS_VOID)
{
    return AT_RegisterCmdTable(g_astAtExtendCmdTbl, sizeof(g_astAtExtendCmdTbl)/sizeof(g_astAtExtendCmdTbl[0]));
}

/* Modified  by s00217060 for V7R1C50_At_Abort, 2012/9/25, end */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
