/******************************************************************************
 */
/*
 */
/*                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾
 */
/*
 */
/******************************************************************************
 */
/*  �� �� ��   : at_lte_common.h
 */
/*  �� �� ��   : V1.0
 */
/*  ��    ��   : �޾�ǿ/64416
 */
/*  ��������   : 2011-03-10
 */
/*  ��������   : AT FW���ڲ��ӿڶ���
 */
/*  �����б�   :
 */
/*  �޸���ʷ   :
 */
/*  1.��    �� : 2011-03-10
 */
/*    ��    �� : �޾�ǿ/64416
 */
/*    �޸����� : �����ļ�
 */
/*
 */
/******************************************************************************
 */

#ifndef __AT_LTE_COMMON_H__
#define __AT_LTE_COMMON_H__

#include "gen_msg.h"
#include "AtParse.h"

#include "AppEsmInterface.h"
#include "AppMmInterface.h"
#include "AppRrcInterface.h"
#include "ATCmdProc.h"


#ifdef __cplusplus
extern "C"
{
#endif

#define AT_LTE_EVENT_NULL_SIZE              0

#define AT_RSSI_LOW                             (-113)
#define AT_RSSI_HIGH                            (-51)
#define AT_CSQ_RSSI_LOW                         (0)
#define AT_CSQ_RSSI_HIGH                        (31)
#define AT_RSSI_UNKNOWN                         (99)

#define AT_BER_UNKNOWN                          (99)

enum
{
    EN_SERVICE_CELL_ID,
    EN_SYN_FREQ_CELL_ID,
    EN_ASYN_FREQ_CELL_ID,
    EN_ASYN_UMTS_CELL_ID,
    EN_ASYN_GSM_CELL_ID,
    EN_CELL_ID_BUTT
};

typedef enum
{
    AT_CMD_LTE_BEGIN = AT_CMD_COMM_BUTT,
    AT_CMD_LWCLASH,
    AT_CMD_RADVER,
    AT_CMD_ISMCOEX,	/*added by c64416 for lte wifi 20131013*/
    AT_CMD_LCELLINFO,
    AT_CMD_F_FCALIIP2SMRF,
    AT_CMD_F_FCALIDCOCSMRF,
    /*begin : added by l00169177 for common command 20131012 DTS2013102611180 */
	AT_CMD_LTCOMMCMD,
    /*end   : added by l00169177 for common command 20131012 DTS2013102611180 */ 
    /* DTS2014061903983 y0017698 cacell Begin: */
    AT_CMD_LCACELL,
    /* DTS2014061903983 y0017698 cacell End! */
    AT_CMD_LTE_BUTT
}AT_LTE_CMD_INDEX_ENUM;

typedef enum
{
    AT_CMD_LTE_CURR_BEGIN = AT_CMD_COMM_CURRENT_OPT,
    AT_CMD_LWCLASH_READ,
    AT_CMD_ISMCOEX_SET,	/*added by c64416 for lte wifi 20131013*/
    AT_CMD_RADVER_SET,
    AT_CMD_LCELLINFO_QUERY,
    AT_CMD_CERSSI_QUERY,
    AT_CMD_FCALIIP2SMRF_SET,
    AT_CMD_FCALIIP2SMRF_READ,
    AT_CMD_FCALIDCOCSMRF_SET,
    AT_CMD_FCALIDCOCSMRF_READ,
    AT_CMD_PSTANDBY_SET,
    /*begin : added by l00169177 for common command 20131012 DTS2013102611180 */
	AT_CMD_LTCOMMCMD_SET,    
    AT_CMD_LTCOMMCMD_READ,    
    /*end   : added by l00169177 for common command 20131012 DTS2013102611180 */ 
    AT_CMD_FPLLSTATUS_READ,    
	/* DTS2014061903983 y0017698 cacell Begin: */
    AT_CMD_LCACELL_QUERY,
    /* DTS2014061903983 y0017698 cacell End! */
    AT_CMD_LTE_CURR_BUTT
}AT_LTE_CMD_CURRENT_OPT_ENUM;

typedef struct
{
    VOS_UINT32 ulSrcError;   /* USIM,NAS...
 */
    VOS_UINT32 ulATError;    /* AT������
 */
}AT_ERROR_CODE_TABLE_STRU;

/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct{
    VOS_UINT32 ulMsgId;
    PFN_AT_FW_MSG_PROC   pfnCnfMsgProc;
}AT_FTM_CNF_MSG_PROC_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/


/*+CSQ
 */
typedef struct
{
    VOS_UINT8 ucRssiValue;
    VOS_UINT8 ucChannalQual;
}TAF_RSSI_STRU;

extern AT_SEND_DATA_BUFFER_STRU gstLAtSendData;
extern VOS_UINT8 *pgucLAtSndCodeAddr;

VOS_UINT32 initParaListS16( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_INT16* pausList);
VOS_UINT32 initParaListU16( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_UINT16* pausList);


extern VOS_VOID CmdErrProc(VOS_UINT8 ucClientId, VOS_UINT32 ulErrCode, VOS_UINT16 usBufLen, VOS_UINT8* pucBuf);

extern VOS_UINT32 atSetSdloadCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock);


/* ATģ���FTM ģ�鷢����Ϣ
 */
extern VOS_UINT32 atSendFtmDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_UINT32 ulClientId, VOS_VOID* pData, VOS_UINT32 uLen);

/* DTS2012090705475 c64416 start in 2012-08-23 for ^LWCLASH */
extern VOS_UINT32 atSendDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_VOID* pData, VOS_UINT32 uLen);
/* DTS2012090705475 c64416 end in 2012-08-23 for ^LWCLASH */
/* BEGIN: Added by l00169177 V9R1_Hi6361 Verification */
extern VOS_UINT32 atSetFCALIIP2SPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCALIIP2SParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFCALIIP2SPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCALIIP2SParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFCALIDCOCSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCALIDCOCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFCALIDCOCSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCALIDCOCSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFGAINSTATESPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFGAINSTATESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFGAINSTATESPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFGAINSTATESParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
/* END: Added by l00169177 V9R1_Hi6361 Verification */

/* Modified By Y00171698 For V9R1_Hi6361, Begin: */
extern VOS_UINT32 atSetFDBBATTSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFDBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFDBBATTSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFDBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFBBATTSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFBBATTSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFBBATTSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFCALITXIQSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCALITXIQSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFCALITXIQSPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCALITXIQSParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
/* Modified By Y00171698 For V9R1_Hi6361, End! */

extern VOS_UINT32 atSetFWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID * pMsgBlock);



/* Added by w00182550 for DTS2013010805263, 2013/01/10, begin */
extern VOS_UINT32 At_SetLCellInfoPara(VOS_UINT8 ucIndex);
/* Added by w00182550 for DTS2013010805263, 2013/01/10/, end */

/* Begin: Added by l00169177 FOR Multi-RF 20130904 */
extern VOS_UINT32 atSetFCALIIP2SMRFPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCALIIP2SMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFCALIIP2SMRFPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCALIIP2SMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

extern VOS_UINT32 atSetFCALIDCOCSMRFPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetFCALIDCOCSMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
extern VOS_UINT32 atQryFCALIDCOCSMRFPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFCALIDCOCSMRFParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);
/* End: Added by l00169177 FOR Multi-RF 20130904 */
extern VOS_UINT32 AT_SetLFastDormPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetLIndCfgReq(VOS_UINT8 ucIndex,L4A_IND_CFG_STRU* pstIndCfgReq);
extern VOS_UINT32 AtQryLCerssiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetLFromConnToIdlePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryLwclashPara(VOS_UINT8 ucIndex);

/* DTS2014061903983 y0017698 cacell Begin: */
extern VOS_UINT32 AT_QryLcacellPara(VOS_UINT8 ucIndex);
/* DTS2014061903983 y0017698 cacell End! */

/*Added by y00228784 for ^inforbu , &f  LTE AT��������Ƶ�A�� 2013-8-28 begin*/
extern VOS_UINT32 atSetNVFactoryBack(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetNVFactoryRestore(VOS_UINT8 ucClientId);
/*Added by y00228784 for ^inforbu , &f  LTE AT��������Ƶ�A�� 2013-8-28 end*/

/* begin : added by l00169177 20131012 for common command DTS2013102611180 */
extern VOS_UINT32 atSetLTCommCmdPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atSetLTCommCmdParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID * pMsgBlock);
extern VOS_UINT32 atQryLTCommCmdPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryLTCommCmdParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID * pMsgBlock);
/* end   : added by l00169177 20131012 for common command DTS2013102611180 */


extern VOS_UINT32 At_RegisterTLCmdTable(VOS_VOID);

/*begin_added by c64416 for lte wifi 20131013*/
extern VOS_UINT32 AT_SetIsmcoexPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryIsmcoexPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atIsmcoexCnfProc(VOS_VOID *pMsgBlock);
/*end_added by c64416 for lte wifi 20131013*/

extern VOS_UINT32 AT_SetRadverPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetRadverCnfProc(VOS_VOID *pMsgBlock);



extern VOS_UINT32 atQryFPllStatusPara(VOS_UINT8 ucClientId);
extern VOS_UINT32 atQryFPllStatusParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);

#ifdef __cplusplus
}
#endif


#endif /*__AT_H__
 */



