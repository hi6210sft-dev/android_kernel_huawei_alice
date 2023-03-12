/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : AtCmdMsgProc.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2011��10��4��
  ����޸�   :
  ��������   : AtCmdMsgProc.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��10��4��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __ATCMDMSGPROC_H__
#define __ATCMDMSGPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "AtTypeDef.h"
#include  "AtCtx.h"
#include  "AcpuReset.h"
#include  "TafDrvAgent.h"
#include  "AtMtaInterface.h"
#include  "AtInternalMsg.h"
/* Added by y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include  "AtImsaInterface.h"
#endif
/* Added by y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-22, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/* Added by f62575 for AT Project, 2011/10/19, begin */
extern VOS_INT8                         g_acATE5DissdPwd[AT_DISSD_PWD_LEN+1];
/* Added by f62575 for AT Project, 2011/10/19, end */


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*��Ϣ������ָ��*/
typedef VOS_UINT32 (*pAtProcMsgFromDrvAgentFunc)(VOS_VOID *pMsg);

/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, begin */
/*AT��MTAģ�����Ϣ������ָ��*/
typedef VOS_UINT32 (*AT_MTA_MSG_PROC_FUNC)(VOS_VOID *pMsg);
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-21, begin */

/*AT��MMAģ�����Ϣ������ָ��*/
typedef VOS_UINT32 (*AT_MMA_MSG_PROC_FUNC)(VOS_VOID *pMsg);
/* Added by w00167002 for L-C��������Ŀ, 2014-2-21, end */



/*****************************************************************************
 �ṹ��    : DRV_AGENT_MSG_PROC_STRU
 �ṹ˵��  : ��Ϣ���Ӧ�������Ľṹ
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    DRV_AGENT_MSG_TYPE_ENUM_UINT32       ulMsgType;
    pAtProcMsgFromDrvAgentFunc           pProcMsgFunc;
}AT_PROC_MSG_FROM_DRV_AGENT_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

/*****************************************************************************
 Structure      : NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST
 Description    : PC�طŹ��̣��洢����AT��ص�ȫ�ֱ�����Ŀǰ���ж������ȫ�ֱ���
 Message origin :
 Note:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /* ָʾ��ǰ�����Ƿ��ѱ�ʹ�� */
    AT_USER_TYPE                        UserType;                               /* ָʾ��ǰ�û����� */
    AT_MODE_TYPE                        Mode;                                   /* ָʾ��ǰ����ģʽ��ֻ���MUX��APP */
    AT_IND_MODE_TYPE                    IndMode;                                /* ָʾ��ǰ����ģʽ��ֻ���MUX��APP */
    VOS_UINT16                          usClientId;                             /* ָʾ��ǰ�û��� */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID, ��ʶ���β���             */
    VOS_UINT8                           aucReserved[1];
}NAS_AT_CLIENT_MANAGE_SIMPLE_STRU;

/*****************************************************************************
 Structure      : NAS_AT_SDT_AT_CLIENT_TABLE_STRU
 Description    : PC�طŹ��̣�����AT��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    /* Modify by j00174725 for V3R3 Cut Out Memory, 2013-11-06, Begin */
    AT_INTER_MSG_ID_ENUM_UINT32             enMsgID;
    /* Modify by j00174725 for V3R3 Cut Out Memory, 2013-11-06, End */
    VOS_UINT8                               ucType;
    VOS_UINT8                               aucReserved[3];                     /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_AT_CLIENT_MANAGE_SIMPLE_STRU        gastAtClientTab[AT_MAX_CLIENT_NUM];
}NAS_AT_SDT_AT_CLIENT_TABLE_STRU;

typedef struct
{
    AT_CSCS_TYPE                        gucAtCscsType;
    AT_CSDH_TYPE                        gucAtCsdhType;
    MN_OPERATION_ID_T                   g_OpId;
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     g_enAtCsmsMsgVersion;
    AT_CNMI_TYPE_STRU                   gstAtCnmiType;
    AT_CMGF_MSG_FORMAT_ENUM_U8          g_enAtCmgfMsgFormat;
    VOS_UINT8                           aucReserved[3];                         /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    AT_CGSMS_SEND_DOMAIN_STRU           g_stAtCgsmsSendDomain;
    AT_CSCA_CSMP_INFO_STRU              g_stAtCscaCsmpInfo;
    AT_MSG_CPMS_STRU                    g_stAtCpmsInfo;
}NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST;

/*****************************************************************************
 Structure      : NAS_AT_SDT_AT_PART_ST
 Description    : PC�طŹ��̣�����AT��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    /* Modify by j00174725 for V3R3 Cut Out Memory, 2013-11-06, Begin */
    AT_INTER_MSG_ID_ENUM_UINT32             enMsgID; /* ƥ��AT_MSG_STRU��Ϣ�е�ulMsgID  */
    VOS_UINT8                               ucType;  /* ֮ǰ��ucMsgIDs */
    /* Modify by j00174725 for V3R3 Cut Out Memory, 2013-11-06, end */
    VOS_UINT8                               aucReserved[3];                     /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    /* Added by f00179208 for DSDA Phase III, 2013-03-07, Begin */
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST  astOutsideCtx[MODEM_ID_BUTT];
    /* Added by f00179208 for DSDA Phase III, 2013-03-07, End */
}NAS_AT_SDT_AT_PART_ST;

/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, begin */
/*****************************************************************************
 �ṹ��    : AT_PROC_MSG_FROM_MTA_STRU
 �ṹ˵��  : AT��MTA��Ϣ���Ӧ�������Ľṹ
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    AT_MTA_MSG_TYPE_ENUM_UINT32         ulMsgType;
    AT_MTA_MSG_PROC_FUNC                pProcMsgFunc;
}AT_PROC_MSG_FROM_MTA_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-21, begin */
/*****************************************************************************
 �ṹ��    : AT_PROC_MSG_FROM_MTA_STRU
 �ṹ˵��  : AT��MTA��Ϣ���Ӧ�������Ľṹ
*****************************************************************************/
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    VOS_UINT32                          ulMsgName;
    AT_MMA_MSG_PROC_FUNC                pProcMsgFunc;
}AT_PROC_MSG_FROM_MMA_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/
/* Added by w00167002 for L-C��������Ŀ, 2014-2-21, end */
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU         *pstDrvAgentMsidQryCnf
);
/* Modified by l60609 for DSDA Phase III, 2013-3-5, End */
VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg);

VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMmaCrpnQueryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg);

/* Added by f00179208 for AT Project, 2011-11-03  Begin*/
VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg);
/* Added by f00179208 for AT Project, 2011-11-03  End */

/* Modified by w00181244 for AT Project 2011-10-5  Begin*/
VOS_UINT32 AT_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
);
/* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
VOS_UINT32  AT_GetImeiValue(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8 aucImei[TAF_PH_IMEI_LEN + 1]
);
/* Modified by l60609 for DSDA Phase III, 2013-3-5, End */
VOS_BOOL AT_IsSimLockPlmnInfoValid(VOS_VOID);

VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQrySecuBootRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg);

/* Modified by w00181244 for AT Project 2011-10-5  End*/

extern VOS_VOID At_CmdMsgDistr(AT_MSG_STRU *pstMsg);

extern VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
    VOS_UINT16                          usCurBandSwitch,
    VOS_UINT32                         *pulUserDivBandsLow,
    VOS_UINT32                         *pulUserDivBandsHigh
);

/* Added by w00181244 for AT Project, 2011-11-5, Begin*/
extern VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg);
/* Added by w00181244 for AT Project, 2011-11-5, End*/

/* Modified by f62575 for B050 Project, 2012-2-3, begin   */
extern VOS_BOOL AT_E5CheckRight(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);
/* Modified by f62575 for B050 Project, 2012-2-3, end */

/* Added by f62575 for SMALL IMAGE, 2012-1-3, Begin   */
VOS_UINT32 AT_RcvDrvAgentTseLrfSetRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentHkAdcGetRsp(VOS_VOID *pMsg);

/* Added by f62575 for SMALL IMAGE, 2012-1-3, End     */
/* Added by w00181244 for SMALL IMAGE, 2012-1-13, Begin*/
VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg);
/* Added by w00181244 for SMALL IMAGE, 2012-1-13, End*/

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg);
#endif
/* Added by f62575 for B050 Project, 2012-2-3, Begin   */
VOS_UINT32 AT_RcvDrvAgentSetSecuBootRsp(VOS_VOID *pMsg);
/* Added by f62575 for B050 Project, 2012-2-3, end   */

/* Added by l00198894 for B050 Project, 2012/02/02, begin */
extern VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg);
/* Added by l00198894 for B050 Project, 2012/02/02, end */

/* Added by l00198894 for C50_IPC Project, 2012/02/16, begin */
VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg);

/* Added by l00198894 for C50_IPC Project, 2012/02/16, end */

/* Added by h59254 for SAR Project, 2012/04/24, begin */
VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg);
/* Added by h59254 for SAR Project, 2012/04/24, end */


/* Modified by z60575 for DTS2012032600572 2012-04-19, begin */
VOS_VOID  AT_ReadSystemAppConfigNV(VOS_VOID);
/* Modified by z60575 for DTS2012032600572 2012-04-19, end */

/* Added by l00171473 for DTS2012041805606, 2012-4-24, begin */

/* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, begin */
VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
);
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, end */
/* Added by l00171473 for DTS2012041805606, 2012-4-24, end */
/* Added by f00179208 for DTS2012031403331, 2012-03-19, Begin */
VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg);
/* Added by f00179208 for DTS2012031403331, 2012-03-19, End */

/* Added by f00179208 for DTS2012060804905, 2012-06-18 Begin */
VOS_UINT32 AT_RcvDrvAgentSetApSimstRsp(VOS_VOID *pMsg);
/* Added by f00179208 for DTS2012060804905, 2012-06-18 Begin */

/* Added by l00198894 for AP-Modem Personalisation Project, 2012/04/10, begin */
VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg);
/* Added by l00198894 for AP-Modem Personalisation Project, 2012/04/10, end */

/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, begin */
extern VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg);
extern VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pMsg);
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, end */

/* Added by l00198894 for V7R1C50 ISDB Project, 2012/08/28, begin */
extern VOS_UINT32 AT_RcvMtaApSecSetCnf( VOS_VOID *pMsg );
/* Added by l00198894 for V7R1C50 ISDB Project, 2012/08/28, end */

/* Added by l00198894 for STK&DCM Project, 2012/09/18, begin */
extern VOS_VOID AT_Rpt_NV_Read( VOS_VOID );

extern VOS_UINT32 AT_RcvMtaSimlockUnlockSetCnf( VOS_VOID *pMsg );
/* Added by l00198894 for STK&DCM Project, 2012/09/18, end */

/* Modified by z00161729 for cerssi and cnmr, 2012-11-21, begin */
VOS_UINT32 AT_RcvMtaQryNmrCnf( VOS_VOID *pMsg );

/* Modified by z00161729 for cerssi and cnmr, 2012-11-21, end */
/* Added by m00217266 for DSDA GUNAS C CORE, 2012-12-26, begin */
VOS_UINT32 AT_RcvMtaWrrAutotestQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrCellinfoQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrMeanrptQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrCellSrhSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrCellSrhQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrFreqLockSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrFreqLockQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrRrcVersionSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrRrcVersionQryCnf( VOS_VOID *pMsg );
/* Added by m00217266 for DSDA GUNAS C CORE, 2012-12-26, end */

/* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
VOS_UINT32 AT_RcvMmaAcInfoQueryCnf(VOS_VOID *pstMsg);

/* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

/* Modified by l60609 for DSDA Phase III, 2013-2-26, Begin */
extern VOS_VOID AT_ReadWasCapabilityNV(VOS_VOID);
/* Modified by l60609 for DSDA Phase III, 2013-2-26, End */

/* Added by z00214637 for Body Sar Project, 2013-03-11, begin */
VOS_UINT32 AT_RcvMtaBodySarSetCnf(VOS_VOID *pstMsg);
/* Added by z00214637 for Body Sar Project, 2013-03-11, end */

/* Added by f00179208 for CCPU RESET, 2013-04-17, Begin */
extern VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause);
extern VOS_VOID AT_StopAllTimer(VOS_VOID);
extern VOS_VOID AT_ResetParseCtx(VOS_VOID);
extern VOS_VOID AT_ResetClientTab(VOS_VOID);
extern VOS_VOID AT_ResetOtherCtx(VOS_VOID);
extern VOS_UINT32 AT_RcvCcpuResetStartInd(
    VOS_VOID                           *pstMsg
);
extern VOS_UINT32 AT_RcvCcpuResetEndInd(
    VOS_VOID                           *pstMsg
);
extern VOS_UINT32 AT_RcvHifiResetStartInd(
    VOS_VOID                           *pstMsg
);
/* Added by f00179208 for CCPU RESET, 2013-04-17, End */

/* Added by s00190137 for HIFI Reset End Report, 2013/07/04, begin */
VOS_UINT32 AT_RcvHifiResetEndInd(
    VOS_VOID                           *pstMsg
);
/* Added by s00190137 for HIFI Reset End Report, 2013/07/04, end */

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
#endif

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
VOS_UINT32 AT_RcvMtaQryCurcCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaSetUnsolicitedRptCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaQryUnsolicitedRptCnf(VOS_VOID *pstMsg);
/* Modified by s00217060 for DTS2013052406352, 2013-5-25, begin */
VOS_UINT32 AT_ProcMtaUnsolicitedRptQryCnf(
    VOS_UINT8                               ucIndex,
    VOS_VOID                               *pstMsg
);
/* Modified by s00217060 for DTS2013052406352, 2013-5-25, end */

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */
/* Modified by z00161729 for DTS2013020600770, 2013-2-4, begin */
VOS_UINT32 AT_RcvMmaCerssiInfoQueryCnf(VOS_VOID *pstMsg);
/* Modified by z00161729 for DTS2013020600770, 2013-2-4, end */

/* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaImeiVerifyQryCnf
 ��������  : �յ�IMEIУ���ѯ�Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_RcvMtaImeiVerifyQryCnf(VOS_VOID *pstMsg);
/*****************************************************************************
 �� �� ��  : AT_RcvMtaCgsnQryCnf
 ��������  : �յ�UE��Ϣ�ϱ��Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCgsnQryCnf(VOS_VOID *pstMsg);

/* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, end */

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
VOS_UINT32 AT_RcvMmaCopnInfoQueryCnf(VOS_VOID *pMsg);
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

/* Added by s00217060 for V9R1_SVLTE, 2013-6-4, begin */
VOS_UINT32 AT_RcvMtaSetNCellMonitorCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaQryNCellMonitorCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaNCellMonitorInd(VOS_VOID *pstMsg);
/* Added by s00217060 for V9R1_SVLTE, 2013-6-4, end */

/* Added by s00190137 for SIM Insert, 2013/07/04, begin */
VOS_UINT32 AT_RcvMmaSimInsertRsp(VOS_VOID *pMsg);
/* Added by s00190137 for SIM Insert, 2013/07/04, end */

/* Added by l00198894 for V9R1 AGPS, 2013/07/22, begin */
VOS_UINT32 AT_RcvMtaRefclkfreqSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaRefclkfreqQryCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaRefclkfreqInd(VOS_VOID *pMsg);
/* Added by l00198894 for V9R1 AGPS, 2013/07/22, end */

/* Added by m00217266 for AP Sensor, 2013-08-07, begin */
VOS_UINT32 AT_RcvMtaHandleDectSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaHandleDectQryCnf(
    VOS_VOID                           *pMsg
);
/* Added by m00217266 for AP Sensor, 2013-08-07, End */

/* Added by l00198894 for SVLTE Offline Reselect Project, 2013/10/21, begin */
VOS_UINT32 AT_RcvMtaPsTransferInd(VOS_VOID *pMsg);
/* Added by l00198894 for SVLTE Offline Reselect Project, 2013/10/21, end */

/*added by y00176023 for DSDS II,2014-03-25,begin*/
#if (FEATURE_ON == FEATURE_DSDS)
VOS_UINT32 AT_RcvMtaPsProtectSetCnf(VOS_VOID *pMsg);
#endif
VOS_UINT32 AT_RcvMtaPhyInitCnf(VOS_VOID *pMsg);
/*added by y00176023 for DSDS II,2014-03-25,end*/

/* Added by A00165503 for UART-MODEM Project, 2013-09-23, Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvSwitchCmdModeMsg
 ��������  : ����˿��л�����ģʽ��Ϣ
 �������  : ucIndex - �˿�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_RcvSwitchCmdModeMsg(VOS_UINT8 ucIndex);
/* Added by A00165503 for UART-MODEM Project, 2013-09-23, End */

/* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
VOS_UINT32 AT_RcvMtaEcidSetCnf(VOS_VOID *pMsg);
/* Added by l00198894 for ����+ECID����, 2013-12-09, end */

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, Begin */
VOS_UINT32 AT_RcvMtaMipiInfoCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaMipiInfoInd(
    VOS_VOID                           *pMsg
);

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, End */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, begin */

VOS_UINT32 AT_RcvMmaSysCfgSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMmaPhoneModeSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
);
/* Added by w00167002 for L-C��������Ŀ, 2014-2-18, end */

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT32 AT_RcvVcMsgSetMsdCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_UINT32 AT_RcvVcMsgQryMsdCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_UINT32 AT_RcvVcMsgQryEcallCfgCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
);
#endif

/* Added by h00285180 for DTS2015011409018, 2015-01-15, begin */
extern VOS_UINT32 AT_RcvMmaSrchedPlmnInfoInd(
    VOS_VOID                           *pMsg
);
/* Added by h00285180 for DTS2015011409018, 2014-01-15, end   */
/* Added by m00217266 for Xpass reselect, 2014-12-25, begin */
VOS_UINT32 AT_RcvMtaXpassInfoInd(
    VOS_VOID                           *pMsg
);
/* Added by m00217266 for Xpass reselect, 2014-12-25, end */

/* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, Begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 AT_RcvMmaImsSwitchSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMmaImsSwitchQryCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMmaVoiceDomainSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_VoiceDomainTransToOutputValue(
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDoman,
    VOS_UINT32                         *pulValue
);

VOS_UINT32 AT_RcvMmaVoiceDomainQryCnf(
    VOS_VOID                           *pMsg
);
#endif
/* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, End */

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtCmdMsgProc.h */

