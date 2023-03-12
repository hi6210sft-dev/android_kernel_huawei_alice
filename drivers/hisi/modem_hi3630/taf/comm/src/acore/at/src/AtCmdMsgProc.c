/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : AtCmdMsgProc.c
  Author       : ---
  Version      : V100R001
  Date         : 2005-04-19
  Description  : ��C�ļ�������---ģ���ʵ��
  Function List:
            At_PidInit
            At_CmdMsgProc

  History      :
  1. Date:2005-04-19
     Author: ---
     Modification:Create

************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "ATCmdProc.h"
#include "siapppb.h"
#include "siappstk.h"
#include "AtMsgPrint.h"
#include "mdrv.h"
#include "AtPhyInterface.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "AtCmdMsgProc.h"
#include "AtEventReport.h"
#include "AtRabmInterface.h" /* V3R2��V7R1���� z40661 c00149739 20111221 */
#include "AtRnicInterface.h"
#include "AtDeviceCmd.h"
/* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
#include "AtInit.h"
#include "at_common.h"
#include "AcpuReset.h"
/* Added by f00179208 for CCPU RESET, 2013-04-15, End */

/* add by j00174725 for V3R3 Cut Out Memory, 2013-11-06, Begin */
#include "AtInternalMsg.h"
/* add by j00174725 for V3R3 Cut Out Memory, 2013-11-06, end */

#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"

#include "LPsNvInterface.h"
#include "LNvCommon.h"
#include "at_lte_common.h"
#endif

/* Added by z00214637 for Body Sar Project, 2013-03-11, begin */
#include "MtaPhyInterface.h"
/* Added by z00214637 for Body Sar Project, 2013-03-11, end */

/* Added by z00214637 for TEMP PROTECT NAS project, 2013-04-17, begin */
#include "OmApi.h"
/* Added by z00214637 for TEMP PROTECT NAS project, 2013-04-17, begin */
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
/* added by M00217266 for nv, 2013-05-20, begin */
#include "GasNvInterface.h"
/* added by M00217266 for nv, 2013-05-20, end */
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-08-16, begin */
#include "AppVcApi.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-08-16, end */

/* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, begin */
#include "AtCmdImsProc.h"
/* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, end */

/* Modify by j00174725 for V3R3 Cut Out Memory, 2013-11-06, Begin */
#include  "product_config.h"
/* Modify by j00174725 for V3R3 Cut Out Memory, 2013-11-06, end */

#include "AtCmdCallProc.h"

#include  "AtCmdFtmProc.h"
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDMSGPROC_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
  2 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
   3 ȫ�ֱ�������
*****************************************************************************/
/* Added by L60609 for AT Project��2011-10-04,  Begin*/

/*AT ģ�鴦������AT AGENT��Ϣ������Ӧ��*/
const AT_PROC_MSG_FROM_DRV_AGENT_STRU g_astAtProcMsgFromDrvAgentTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
    {DRV_AGENT_MSID_QRY_CNF,                AT_RcvDrvAgentMsidQryCnf},
    {DRV_AGENT_GAS_MNTN_CMD_RSP,            AT_RcvDrvAgentGasMntnCmdRsp},
    {DRV_AGENT_HARDWARE_QRY_RSP,            AT_RcvDrvAgentHardwareQryRsp},
    {DRV_AGENT_FULL_HARDWARE_QRY_RSP,       AT_RcvDrvAgentFullHardwareQryRsp},
    {DRV_AGENT_RXDIV_SET_CNF,               AT_RcvDrvAgentSetRxdivCnf},
    {DRV_AGENT_RXDIV_QRY_CNF,               AT_RcvDrvAgentQryRxdivCnf},
    {DRV_AGENT_SIMLOCK_SET_CNF,             AT_RcvDrvAgentSetSimlockCnf},


    {DRV_AGENT_VERTIME_QRY_CNF,             AT_RcvDrvAgentVertimeQryRsp},
    {DRV_AGENT_YJCX_SET_CNF,                AT_RcvDrvAgentYjcxSetCnf},
    {DRV_AGENT_YJCX_QRY_CNF,                AT_RcvDrvAgentYjcxQryCnf},
    /* Modified by w00181244 for AT Project 2011-10-5  Begin*/
    {DRV_AGENT_GPIOPL_SET_CNF,              AT_RcvDrvAgentSetGpioplRsp},
    {DRV_AGENT_GPIOPL_QRY_CNF,              AT_RcvDrvAgentQryGpioplRsp},
    {DRV_AGENT_DATALOCK_SET_CNF,            AT_RcvDrvAgentSetDatalockRsp},
    {DRV_AGENT_TBATVOLT_QRY_CNF,            AT_RcvDrvAgentQryTbatvoltRsp},
    {DRV_AGENT_VERSION_QRY_CNF,             AT_RcvDrvAgentQryVersionRsp},
    {DRV_AGENT_FCHAN_SET_CNF,               AT_RcvDrvAgentSetFchanRsp},
    {DRV_AGENT_SFEATURE_QRY_CNF,            AT_RcvDrvAgentQrySfeatureRsp},
    {DRV_AGENT_PRODTYPE_QRY_CNF,            AT_RcvDrvAgentQryProdtypeRsp},

    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, begin */
    {DRV_AGENT_CPULOAD_QRY_CNF,             AT_RcvDrvAgentCpuloadQryRsp},
    {DRV_AGENT_MFREELOCKSIZE_QRY_CNF,       AT_RcvDrvAgentMfreelocksizeQryRsp},
    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, end */
    /* Modified by w00181244 for AT Project 2011-10-5  End*/
    /* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */
    {DRV_AGENT_MEMINFO_QRY_CNF,             AT_RcvDrvAgentMemInfoQryRsp},
    /* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */
    /* Added by f62575 for AT Project, 2011-10-04,  Begin */
    {DRV_AGENT_DLOADINFO_QRY_CNF,           AT_RcvDrvAgentDloadInfoQryRsp},
    {DRV_AGENT_FLASHINFO_QRY_CNF,           AT_RcvDrvAgentFlashInfoQryRsp},
    {DRV_AGENT_AUTHORITYVER_QRY_CNF,        AT_RcvDrvAgentAuthorityVerQryRsp},
    {DRV_AGENT_AUTHORITYID_QRY_CNF,         AT_RcvDrvAgentAuthorityIdQryRsp},
    {DRV_AGENT_AUTHVER_QRY_CNF,             AT_RcvDrvAgentAuthVerQryRsp},
    {DRV_AGENT_GODLOAD_SET_CNF,             AT_RcvDrvAgentGodloadSetRsp},

    {DRV_AGENT_PFVER_QRY_CNF,               AT_RcvDrvAgentPfverQryRsp},
    {DRV_AGENT_HWNATQRY_QRY_CNF,            AT_RcvDrvAgentHwnatQryRsp},
    {DRV_AGENT_SDLOAD_SET_CNF,              AT_RcvDrvAgentSdloadSetRsp},
    {DRV_AGENT_APPDMVER_QRY_CNF,            AT_RcvDrvAgentAppdmverQryRsp},
    {DRV_AGENT_DLOADVER_QRY_CNF,            AT_RcvDrvAgentDloadverQryRsp},
    /* Added by f62575 for AT Project, 2011-10-04,  End */

    /* Added by l60609 for AT Project, 2011-11-03,  Begin */
    {DRV_AGENT_IMSICHG_QRY_CNF,             AT_RcvDrvAgentImsiChgQryRsp},
    {DRV_AGENT_INFORBU_SET_CNF,             AT_RcvDrvAgentInfoRbuSetRsp},
    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
#if ( FEATURE_ON == FEATURE_LTE )
    {DRV_AGENT_INFORRS_SET_CNF,             AT_RcvDrvAgentInfoRrsSetRsp},
#endif
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/
    {DRV_AGENT_CPNN_QRY_CNF,                AT_RcvDrvAgentCpnnQryRsp},
    {DRV_AGENT_CPNN_TEST_CNF,               AT_RcvDrvAgentCpnnTestRsp},
    {DRV_AGENT_NVBACKUP_SET_CNF,            AT_RcvDrvAgentNvBackupSetRsp},
    /* Added by l60609 for AT Project, 2011-11-03,  Begin */

    /* Added by f00179208 for AT Project, 2011-11-03,  Begin */
    {DRV_AGENT_NVRESTORE_SET_CNF,           AT_RcvDrvAgentSetNvRestoreCnf},
    {DRV_AGENT_NVRSTSTTS_QRY_CNF,           AT_RcvDrvAgentQryNvRestoreRstCnf},
    {DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF,  AT_RcvDrvAgentNvRestoreManuDefaultRsp},
    /* Added by f00179208 for AT Project, 2011-11-03,  Begin */

    /* Added by w00181244 for AT Project, 2011-11-05,  Begin */
    {DRV_AGENT_ADC_SET_CNF,                 AT_RcvDrvAgentSetAdcRsp},
    /* Added by w00181244 for AT Project, 2011-11-05,  End */
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, Begin   */
    {DRV_AGENT_TSELRF_SET_CNF,              AT_RcvDrvAgentTseLrfSetRsp},
    {DRV_AGENT_HKADC_GET_CNF,               AT_RcvDrvAgentHkAdcGetRsp},
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */

    /* Added by w00181244 for SMALL IMAGE, 2012-1-13,  Begin */
    {DRV_AGENT_TBAT_QRY_CNF,                AT_RcvDrvAgentQryTbatRsp},
    /* Added by w00181244 for SMALL IMAGE, 2012-1-13,  End */
    /* Added by l60609 for B060 Project, 2012-2-21, Begin   */
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
    {DRV_AGENT_SPWORD_SET_CNF,              AT_RcvDrvAgentSetSpwordRsp},
#endif
    /* Added by l60609 for B060 Project, 2012-2-21, End   */

    /* Added by l00198894 for C50_IPC Project, 2012/02/16, begin */
    {DRV_AGENT_NVBACKUPSTAT_QRY_CNF,        AT_RcvDrvAgentNvBackupStatQryRsp},
    {DRV_AGENT_NANDBBC_QRY_CNF,             AT_RcvDrvAgentNandBadBlockQryRsp},
    {DRV_AGENT_NANDVER_QRY_CNF,             AT_RcvDrvAgentNandDevInfoQryRsp},
    {DRV_AGENT_CHIPTEMP_QRY_CNF,            AT_RcvDrvAgentChipTempQryRsp},

    /* Added by l00198894 for C50_IPC Project, 2012/02/16, end */
    /* Added by h59254 for C50 SAR Project, 2012/03/10, begin */
    {DRV_AGENT_ANTSTATE_QRY_IND,            AT_RcvDrvAgentAntStateIndRsp},
    /* Added by h59254 for C50 SAR Project, 2012/03/10, end */

    /* Added by f00179208 for DTS2012031403331, 2012-03-19, Begin */
    {DRV_AGENT_MAX_LOCK_TIMES_SET_CNF,      AT_RcvDrvAgentSetMaxLockTmsRsp},
    /* Added by f00179208 for DTS2012031403331, 2012-03-19, End */

    /* Added by f00179208 for DTS2012060804905, 2012-06-18 Begin */
    {DRV_AGENT_AP_SIMST_SET_CNF,            AT_RcvDrvAgentSetApSimstRsp},
    /* Added by f00179208 for DTS2012060804905, 2012-06-18 End */

    /* Added by l00198894 for AP-Modem Personalisation Project, 2012/04/10, begin */
    {DRV_AGENT_HUK_SET_CNF,                 AT_RcvDrvAgentHukSetCnf},
    {DRV_AGENT_FACAUTHPUBKEY_SET_CNF,       AT_RcvDrvAgentFacAuthPubkeySetCnf},
    {DRV_AGENT_IDENTIFYSTART_SET_CNF,       AT_RcvDrvAgentIdentifyStartSetCnf},
    {DRV_AGENT_IDENTIFYEND_SET_CNF,         AT_RcvDrvAgentIdentifyEndSetCnf},
    {DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF,    AT_RcvDrvAgentSimlockDataWriteSetCnf},
    {DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF,    AT_RcvDrvAgentPhoneSimlockInfoQryCnf},
    {DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF,     AT_RcvDrvAgentSimlockDataReadQryCnf},
    {DRV_AGENT_PHONEPHYNUM_SET_CNF,         AT_RcvDrvAgentPhonePhynumSetCnf},
    {DRV_AGENT_PHONEPHYNUM_QRY_CNF,         AT_RcvDrvAgentPhonePhynumQryCnf},
    {DRV_AGENT_PORTCTRLTMP_SET_CNF,         AT_RcvDrvAgentPortctrlTmpSetCnf},
    {DRV_AGENT_PORTATTRIBSET_SET_CNF,       AT_RcvDrvAgentPortAttribSetCnf},
    {DRV_AGENT_PORTATTRIBSET_QRY_CNF,       AT_RcvDrvAgentPortAttribSetQryCnf},
    {DRV_AGENT_OPWORD_SET_CNF,              AT_RcvDrvAgentOpwordSetCnf},
    /* Added by l00198894 for AP-Modem Personalisation Project, 2012/04/10, end */

    /* Added by s00190137 for DTS2012121901714, 2012/11/24, begin */
    {DRV_AGENT_SWVER_SET_CNF,               AT_RcvDrvAgentSwverSetCnf},
    /* Added by s00190137 for DTS2012121901714, 2012/11/24, end */

#if (FEATURE_ON == FEATURE_VSIM)
    /* Added by L47619 for V9R1 vSIM Project, 2013-8-27, begin */
    {DRV_AGENT_HVPDH_CNF,                   AT_RcvDrvAgentHvpdhSetCnf},
    /* Added by L47619 for V9R1 vSIM Project, 2013-8-27, end */
#endif

    /* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, begin */
    {DRV_AGENT_NVMANUFACTUREEXT_SET_CNF,    AT_RcvNvManufactureExtSetCnf},
    /* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, end */

    /* Added by y00258578 for ANT SWITCH, 2013-11-11 Begin */
    {DRV_AGENT_ANTSWITCH_SET_CNF,           AT_RcvDrvAgentAntSwitchSetCnf},
    {DRV_AGENT_ANTSWITCH_QRY_CNF,           AT_RcvDrvAgentAntSwitchQryCnf},
    /* Added by y00258578 for ANT SWITCH, 2013-11-11 End */
};

/* Added by L60609 for AT Project��2011-10-04,  End*/

/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, begin */
/* ATģ�鴦������MTA��Ϣ������Ӧ��*/
const AT_PROC_MSG_FROM_MTA_STRU g_astAtProcMsgFromMtaTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
    {ID_MTA_AT_CPOS_SET_CNF,                AT_RcvMtaCposSetCnf},
    {ID_MTA_AT_CPOSR_IND,                   AT_RcvMtaCposrInd},
    {ID_MTA_AT_XCPOSRRPT_IND,               AT_RcvMtaXcposrRptInd},
    {ID_MTA_AT_CGPSCLOCK_SET_CNF,           AT_RcvMtaCgpsClockSetCnf},

    /* Added by l00198894 for V7R1C50 ISDB Project, 2012/09/01, begin */
    {ID_MTA_AT_APSEC_SET_CNF,               AT_RcvMtaApSecSetCnf},
    /* Added by l00198894 for V7R1C50 ISDB Project, 2012/09/01, end */

    /* Added by l00198894 for STK&DCM Project, 2012/09/18, begin */
    {ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,       AT_RcvMtaSimlockUnlockSetCnf},
    /* Added by l00198894 for STK&DCM Project, 2012/09/18, end */

    /* Modified by z00161729 for cerssi and cnmr, 2012-11-21, begin */
    {ID_MTA_AT_QRY_NMR_CNF,                 AT_RcvMtaQryNmrCnf},
    /* Modified by z00161729 for cerssi and cnmr, 2012-11-21, end */

    /* Added by m00217266 for DSDA GUNAS C CORE, 2012-12-26, begin */
    {ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,        AT_RcvMtaWrrAutotestQryCnf},
    {ID_MTA_AT_WRR_CELLINFO_QRY_CNF,        AT_RcvMtaWrrCellinfoQryCnf},
    {ID_MTA_AT_WRR_MEANRPT_QRY_CNF,         AT_RcvMtaWrrMeanrptQryCnf},
    {ID_MTA_AT_WRR_FREQLOCK_SET_CNF,        AT_RcvMtaWrrFreqLockSetCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,     AT_RcvMtaWrrRrcVersionSetCnf},
    {ID_MTA_AT_WRR_CELLSRH_SET_CNF,         AT_RcvMtaWrrCellSrhSetCnf},
    {ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,        AT_RcvMtaWrrFreqLockQryCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,     AT_RcvMtaWrrRrcVersionQryCnf},
    {ID_MTA_AT_WRR_CELLSRH_QRY_CNF,         AT_RcvMtaWrrCellSrhQryCnf},
    /* Added by m00217266 for DSDA GUNAS C CORE, 2012-12-26, end */

    /* Added by z00214637 for Body Sar Project, 2013-03-11, begin */
    {ID_MTA_AT_BODY_SAR_SET_CNF,           AT_RcvMtaBodySarSetCnf},
    /* Added by z00214637 for Body Sar Project, 2013-03-11, end */

    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
    {ID_MTA_AT_CURC_QRY_CNF,                AT_RcvMtaQryCurcCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,     AT_RcvMtaSetUnsolicitedRptCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,     AT_RcvMtaQryUnsolicitedRptCnf},
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */

    /* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, begin */
    {ID_MTA_AT_IMEI_VERIFY_QRY_CNF,         AT_RcvMtaImeiVerifyQryCnf},
    {ID_MTA_AT_CGSN_QRY_CNF,                AT_RcvMtaCgsnQryCnf},
    /* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, end */
    /* Added by s00217060 for V9R1_SVLTE, 2013-6-4, begin */
    {ID_MTA_AT_NCELL_MONITOR_SET_CNF,       AT_RcvMtaSetNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_QRY_CNF,       AT_RcvMtaQryNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_IND,           AT_RcvMtaNCellMonitorInd},
    /* Added by s00217060 for V9R1_SVLTE, 2013-6-4, end */

    /* Added by l00198894 for V9R1 AGPS, 2013/07/22, begin */
    {ID_MTA_AT_REFCLKFREQ_SET_CNF,          AT_RcvMtaRefclkfreqSetCnf},
    {ID_MTA_AT_REFCLKFREQ_QRY_CNF,          AT_RcvMtaRefclkfreqQryCnf},
    {ID_MTA_AT_REFCLKFREQ_IND,              AT_RcvMtaRefclkfreqInd},
    /* Added by l00198894 for V9R1 AGPS, 2013/07/22, end */

    /* Added by m00217266 for AP Sensor, 2013-08-07, begin */
    {ID_MTA_AT_HANDLEDECT_SET_CNF,          AT_RcvMtaHandleDectSetCnf},
    {ID_MTA_AT_HANDLEDECT_QRY_CNF,          AT_RcvMtaHandleDectQryCnf},
    /* Added by m00217266 for AP Sensor, 2013-08-07, End */

    /* Added by l00198894 for SVLTE Offline Reselect Project, 2013/10/21, begin */
    {ID_MTA_AT_PS_TRANSFER_IND,             AT_RcvMtaPsTransferInd},
    /* Added by l00198894 for SVLTE Offline Reselect Project, 2013/10/21, end */

    /*added by y00176023 for DSDS II,2014-03-24,begin*/
#if (FEATURE_ON == FEATURE_DSDS)
    {ID_MTA_AT_RRC_PROTECT_PS_CNF,          AT_RcvMtaPsProtectSetCnf},
#endif
    { ID_MTA_AT_PHY_INIT_CNF,               AT_RcvMtaPhyInitCnf},
    /*added by y00176023 for DSDS II,2014-03-24,end*/

    /* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
    {ID_MTA_AT_ECID_SET_CNF,                AT_RcvMtaEcidSetCnf},
    /* Added by l00198894 for ����+ECID����, 2013-12-09, end */

    /* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, Begin */
    {ID_MTA_AT_MIPICLK_QRY_CNF,             AT_RcvMtaMipiInfoCnf},
    {ID_MTA_AT_MIPICLK_INFO_IND,            AT_RcvMtaMipiInfoInd},
    /* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, End */
    /* Added by g00261581 for Jazz DPDT, 2014-04-04, Begin */
    {ID_MTA_AT_SET_DPDTTEST_FLAG_CNF,       AT_RcvMtaSetDpdtTestFlagCnf},
    {ID_MTA_AT_SET_DPDT_VALUE_CNF,          AT_RcvMtaSetDpdtValueCnf},
    {ID_MTA_AT_QRY_DPDT_VALUE_CNF,          AT_RcvMtaQryDpdtValueCnf},
    /* Added by g00261581 for Jazz DPDT, 2014-04-04, End */

    /* Added by g00261581 for V3R3 JAM DETECT Project, 2014-05-04, begin */
    {ID_MTA_AT_SET_JAM_DETECT_CNF,          AT_RcvMtaSetJamDetectCnf},
    {ID_MTA_AT_JAM_DETECT_IND,              AT_RcvMtaJamDetectInd},
    /* Added by g00261581 for V3R3 JAM DETECT Project, 2014-05-04, end */

    /* Added by g00261581 for V7R11 FREQ LOCK Project, 2014-06-11, begin */
    {ID_MTA_AT_SET_FREQ_LOCK_CNF,           AT_RcvMtaSetRatFreqLockCnf},
    /* Added by g00261581 for V7R11 FREQ LOCK Project, 2014-06-11, end */

    /* Added by j00174725 for GU ROAD TEST, 2014-08-05, Begin */
    {ID_MTA_AT_SET_GSM_FREQLOCK_CNF,        AT_RcvMtaSetGFreqLockCnf},
    /* Added by j00174725 for GU ROAD TEST, 2014-08-05, End */
    /* Added by m00217266 for Xpass reselect, 2014-12-25, begin */
    {ID_MTA_AT_XPASS_INFO_IND,              AT_RcvMtaXpassInfoInd},
    /* Added by m00217266 for Xpass reselect, 2014-12-25, end */

    /* Added by l00198894 for NVWR Security Control, 2015-04-04, begin */
    {ID_MTA_AT_NVWRSECCTRL_SET_CNF,         AT_RcvMtaNvwrSecCtrlSetCnf},
    /* Added by l00198894 for NVWR Security Control, 2015-04-04, end */

};
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-21, begin */
const AT_PROC_MSG_FROM_MMA_STRU g_astAtProcMsgFromMmaTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
#ifndef __PS_WIN32_RECUR__
    {AT_MMA_OM_MAINTAIN_INFO_IND,       AT_RcvMmaOmMaintainInfoInd},
#endif

    {AT_MMA_USIM_STATUS_IND,            AT_RcvAtMmaUsimStatusInd},
    {AT_MMA_CRPN_QUERY_RSP,             AT_RcvMmaCrpnQueryRsp},
    {AT_MMA_CMM_SET_CMD_RSP,            AT_RcvMmaCmmSetCmdRsp},
    {AT_MMA_CIPHER_INFO_QUERY_CNF,      AT_RcvMmaCipherInfoQueryCnf},
    {AT_MMA_LOCATION_INFO_QUERY_CNF,    AT_RcvMmaLocInfoQueryCnf},
    {AT_MMA_SIMLOCK_STAUS_QUERY_CNF,    AT_RcvSimLockQryRsp},
    {AT_MMA_AC_INFO_QUERY_CNF,          AT_RcvMmaAcInfoQueryCnf},
    {AT_MMA_CERSSI_INFO_QUERY_CNF,      AT_RcvMmaCerssiInfoQueryCnf},
    {AT_MMA_COPN_INFO_QUERY_CNF,        AT_RcvMmaCopnInfoQueryCnf},
    {AT_MMA_SIM_INSERT_RSP,             AT_RcvMmaSimInsertRsp},
    {AT_MMA_CPOL_INFO_QUERY_CNF,        AT_QryParaRspPrefPlmnProc},
    {ID_TAF_MMA_SYS_CFG_SET_CNF,        AT_RcvMmaSysCfgSetCnf},
    {ID_TAF_MMA_PHONE_MODE_SET_CNF,     AT_RcvMmaPhoneModeSetCnf},
    {ID_TAF_MMA_DETACH_CNF,             AT_RcvMmaDetachCnf},
    /* Added by h00285180 for DTS2015011409018, 2015-01-15, begin */
    {ID_TAF_MMA_SRCHED_PLMN_INFO_IND,   AT_RcvMmaSrchedPlmnInfoInd},
    /* Added by h00285180 for DTS2015011409018, 2014-01-15, end   */
    /* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, Begin */
#if (FEATURE_ON == FEATURE_IMS)
    {ID_TAF_MMA_IMS_SWITCH_SET_CNF,     AT_RcvMmaImsSwitchSetCnf},
    {ID_TAF_MMA_IMS_SWITCH_QRY_CNF,     AT_RcvMmaImsSwitchQryCnf},
    {ID_TAF_MMA_VOICE_DOMAIN_SET_CNF,   AT_RcvMmaVoiceDomainSetCnf},
    {ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF,   AT_RcvMmaVoiceDomainQryCnf},
#endif
    /* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, End */
};
/* Added by w00167002 for L-C��������Ŀ, 2014-2-21, end */

/* AT������������(����AT�������������)��
   ���øû��������ԭ��:���������ڵ���At_CmdStreamPreProc�ӿ�ʱ��ĳЩ������(��ֱ��ʹ�ó����ն˷���AT����),���
   ����AT������һ���ַ�Ϊ��λ���͵�AT����Ϣ�����У�����AT����Ϣ���������������帴λ��*/
AT_DATA_STREAM_BUFFER_STRU              g_aucAtDataBuff[AT_MAX_CLIENT_NUM];

/*CREG/CGREG��<CI>����4�ֽ��ϱ��Ƿ�ʹ��(VDF����)*/

AT_CLIENT_MANAGE_STRU                   gastAtClientTab[AT_MAX_CLIENT_NUM];

TAF_UINT32                              gulPBPrintTag = VOS_FALSE;

/* Added by f00179208 for AT Project��2011-11-04,  Begin*/
extern VOS_BOOL                         g_bSetFlg;
/* Added by f00179208 for AT Project��2011-11-04,  End*/

/*****************************************************************************
   3 ��������������
*****************************************************************************/

/* Added by z00214637 for TEMP PROTECT NAS project, 2013-04-17, begin */
extern VOS_UINT32    AT_ProcTempprtEventInd(
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstMsg
);
/* Added by z00214637 for TEMP PROTECT NAS project, 2013-04-17, end */

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

#ifdef __PS_WIN32_RECUR__

/*****************************************************************************
 �� �� ��  : AT_RestoreClientData
 ��������  : �ָ�ATģ���ϵĿͻ��˿����ݱ�
 �������  : NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST          *pstOutsideCtx
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��17��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��9��30��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc

*****************************************************************************/
TAF_VOID AT_RestoreClientData(
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU    *pstAtClientData
)
{
    TAF_UINT8                                       ucLoop;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        gastAtClientTab[ucLoop].usClientId      = pstAtClientData->gastAtClientTab[ucLoop].usClientId;
        gastAtClientTab[ucLoop].opId            = pstAtClientData->gastAtClientTab[ucLoop].opId;
        gastAtClientTab[ucLoop].ucUsed          = pstAtClientData->gastAtClientTab[ucLoop].ucUsed;
        gastAtClientTab[ucLoop].UserType        = pstAtClientData->gastAtClientTab[ucLoop].UserType;
        gastAtClientTab[ucLoop].Mode            = pstAtClientData->gastAtClientTab[ucLoop].Mode;
        gastAtClientTab[ucLoop].IndMode         = pstAtClientData->gastAtClientTab[ucLoop].IndMode;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_RestoreContextData
 ��������  : �ָ�ATȫ�ֱ�����
 �������  : pMsg   PC�ط���Ϣָ�룻
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2010��02��12��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��7��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ�ţ�DTS2010071402189��֧��ATģ���CLIENT ID�Ļط�
  3.��    ��   : 2013��03��07��
    ��    ��   : f00179208
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 AT_RestoreContextData(
    AT_MSG_STRU                         *pMsg
)
{
    /* Modified by f00179208 for DSDA Phase III, 2013-03-07, Begin */
    NAS_AT_SDT_AT_PART_ST                  *pRcvMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx     = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pRcvMsgCB     = (NAS_AT_SDT_AT_PART_ST *)pMsg;

    if (AT_PC_REPLAY_MSG == pRcvMsgCB->ucType)
    {
        for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
        {
            pstSmsCtx                       = AT_GetModemSmsCtxAddrFromModemId(enModemId);
            pstOutsideCtx                   = &pRcvMsgCB->astOutsideCtx[enModemId];

            gucAtCscsType                   = pstOutsideCtx->gucAtCscsType;
            pstSmsCtx->ucCsdhType           = pstOutsideCtx->gucAtCsdhType;
            g_OpId                          = pstOutsideCtx->g_OpId;
            pstSmsCtx->enCsmsMsgVersion     = pstOutsideCtx->g_enAtCsmsMsgVersion;
            pstSmsCtx->enCmgfMsgFormat      = pstOutsideCtx->g_enAtCmgfMsgFormat;

            PS_MEM_CPY(&(pstSmsCtx->stCnmiType),
                       &pstOutsideCtx->gstAtCnmiType,
                       sizeof(pstSmsCtx->stCnmiType));

            PS_MEM_CPY(&(pstSmsCtx->stCgsmsSendDomain),
                         &pstOutsideCtx->g_stAtCgsmsSendDomain,
                         sizeof(pstSmsCtx->stCgsmsSendDomain));

            PS_MEM_CPY(&(pstSmsCtx->stCscaCsmpInfo),
                         &pstOutsideCtx->g_stAtCscaCsmpInfo,
                         sizeof(pstSmsCtx->stCscaCsmpInfo));

            PS_MEM_CPY(&(pstSmsCtx->stCpmsInfo),
                         &pstOutsideCtx->g_stAtCpmsInfo,
                         sizeof(pstSmsCtx->stCpmsInfo));

            AT_INFO_LOG("MSG: AT_RestoreContextData data is restored.");
        }
    }
    /* Modified by f00179208 for DSDA Phase III, 2013-03-07, End */

    return AT_OK;
}
#endif
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

/*****************************************************************************
 �� �� ��  : At_MmaMsgProc
 ��������  : ATģ�鴦������MMA����Ϣ
 �������  : MSG_HEADER_STRU * pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��22��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��7��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ�ţ�DTS2010071402189��֧��ATģ���CLIENT ID�Ļط�

  3.��    ��   : 2011��10��17��
    ��    ��   : o00132663
    �޸�����   : AT��ֲ��Ŀ������AT����CC��MMAģ�����Ϣ
  4.��    ��   : 2012��4��24��
    ��    ��   : l00171473
    �޸�����   : DTS2012041805606
  5.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : ����mma��С�������ֹ��Ϣ�ϱ���Ϣ�Ĵ���
  6.��    ��   : 2013��2��4��
    ��    ��   : t00212959
    �޸�����   : DTS2013020600770:at^cerssi?���ӷ��ز���
  7.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��֧��+COPN����
  8.��    ��   : 2014��01��15��
    ��    ��   : f62575
    �޸�����   : DTS2014011301359: ���Ӷ�+CPOL��ѯ�������Ӧ��Ϣ����

  9.��    ��   : 2014��3��5��
    ��    ��   : w00167002
    �޸�����   : AT����MMA����Ϣ����Ϊ��񣬽�Ȧ���Ӷ�
*****************************************************************************/
TAF_VOID At_MmaMsgProc(
    MSG_HEADER_STRU                     *pstMsg
)
{
    /* Modified by w00167002 for L-C��������Ŀ, 2014-3-5, begin */
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /*��g_astAtProcMsgFromMmaTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMmaTab)/sizeof(AT_PROC_MSG_FROM_MMA_STRU);

    /*g_astAtProcMsgFromMtaTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMmaTab[i].ulMsgName == pstMsg->ulMsgName)
        {
            ulRst = g_astAtProcMsgFromMmaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_MmaMsgProc: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_MmaMsgProc: Msg Id is invalid!");
    }

    /* Modified by w00167002 for L-C��������Ŀ, 2014-3-5, end */
    return;
}

/*****************************************************************************
Prototype      : At_EventMsgProc
Description    : ATģ����Ϣ������ں������ú���ע���DOPRA���ȡ�
Input          : pMsg -- VOS��Ϣָ��
Output         : None
Return Value   : None
Calls          : None
Called By      : DOPRA

  History        : ---
  1.Date        : 2005-04-19
  Author      : ---
  Modification: Created function
  2. Date:2006-04-12
     Author: w42656
     Modification:�޸�At_MsgProc,���ⵥ��: A32D01851
  3.��    ��   : 2008��6��10��
    ��    ��   : luojian id:00107747
    �޸�����   : ���ⵥ��:AT2D03704
  4.��    ��   : 2010��7��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ�ţ�DTS2010071402189��֧��ATģ���CLIENT ID�Ļط�
  5.��    ��   : 2011��12��20��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��MN_CALLBACK_DATA_FLOW��Ϣ�Ѿ�����ϢID_EVT_TAF
                 _PS_REPORT_DSFLOW_IND�����ɾ����
  6.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ

*****************************************************************************/
TAF_VOID At_EventMsgProc(MN_AT_IND_EVT_STRU *pMsg)
{

    switch(pMsg->usMsgName)
    {
        case MN_CALLBACK_MSG:
            At_SmsMsgProc(pMsg, pMsg->usLen);
            return;

        case MN_CALLBACK_SET:
            At_SetMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_QRY:
            At_QryMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PS_CALL:
            /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
            /* PS���¼����� */
            AT_RcvTafPsEvt((TAF_PS_EVT_STRU*)pMsg);
            /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
            return;

        case MN_CALLBACK_DATA_STATUS:
            At_DataStatusMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_CS_CALL:
            At_CsMsgProc(pMsg,pMsg->usLen);
            return;

        case MN_CALLBACK_SS:
            At_SsMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PHONE:
            At_PhMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_PHONE_BOOK:
            At_TAFPbMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_CMD_CNF:
            At_CmdCnfMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        case MN_CALLBACK_VOICE_CONTROL:
            At_VcMsgProc(pMsg, pMsg->usLen);
            break;
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

        /* Added by A00165503 for DTS2014050700880, 2014-05-07, Begin */
        case MN_CALLBACK_LOG_PRINT:
            AT_LogPrintMsgProc((TAF_MNTN_LOG_PRINT_STRU *)pMsg);
            break;
        /* Added by A00165503 for DTS2014050700880, 2014-05-07, End */

        default:
            AT_LOG1("At_MsgProc: invalid message name.", pMsg->usMsgName);
            return;
    }
}


/*****************************************************************************
 �� �� ��  : AT_E5CheckRight
 ��������  : ����Ƿ���Ȩ�޲���AT����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��18��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��12��25��
    ��    ��   : lijun 00171473
    �޸�����   : DTS2010122500864 �޸�OPENPORT��SSCOM����������⴦��
  3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ :ɾ��NAS_FEATURE_AT_PWD��
*****************************************************************************/
VOS_BOOL AT_E5CheckRight(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    static VOS_BOOL                     bIsRight = VOS_FALSE;
    VOS_UINT8                           aucCmdTmp[20]; /* �����aucQuickCmd[]�ĳ��� */
    VOS_UINT8                           aucQuickCmd[] = "AT^OPENPORT=";
    VOS_UINT16                          usQuickCmdLen;
    VOS_UINT16                          usLeftLen;
    VOS_UINT8                           *pucPwdPos;
    VOS_CHAR                            acPassword[AT_RIGHT_PWD_LEN+1];
    VOS_UINT8                           *pucAtStart ;

    /* ��ǰȨ��δ����,ֱ�ӷ���  */
    if ( AT_RIGHT_OPEN_FLAG_CLOSE == g_stAtRightOpenFlg.enRightOpenFlg )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ���ȡ��Ȩ��,��ֱ�ӷ��� */
    if ( VOS_TRUE == bIsRight )
    {
        return VOS_TRUE;
    }

    /* SSCOM ������ַ���ǰ�� 0x0A */
    pucAtStart = pucData;
    while( (*pucAtStart != 'a') && (*pucAtStart != 'A')  )
    {
        pucAtStart++;
        if ( pucAtStart >= (pucData+usLen) )
        {
            /* δ�ҵ� a �� A break */
            break;
        }
    }
    usLen -= (VOS_UINT16)(pucAtStart - pucData);
    pucData = pucAtStart;

    /* ���ȷǷ�,ֱ�ӷ�����Ȩ�� */
    usQuickCmdLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucQuickCmd);
    if (usLen <= usQuickCmdLen)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_FALSE;
    }

    VOS_MemSet(aucCmdTmp, 0x00, (VOS_SIZE_T)sizeof(aucCmdTmp));
    VOS_MemCpy(aucCmdTmp, pucData, (VOS_SIZE_T)usQuickCmdLen);

    /* ����AT^OPENPORT����ֱ�ӷ�����Ȩ�� */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)aucCmdTmp,
                          (VOS_CHAR *)aucQuickCmd,
                          (VOS_SIZE_T)usQuickCmdLen))
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    usLeftLen = usLen - usQuickCmdLen;
    pucPwdPos = pucData + usQuickCmdLen;

    if ( usLeftLen >= sizeof(aucCmdTmp) )
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    VOS_MemSet(aucCmdTmp, 0x00, sizeof(aucCmdTmp));
    VOS_MemCpy(aucCmdTmp, pucPwdPos, usLeftLen);

    PS_MEM_SET(acPassword,0x00,sizeof(acPassword));
    PS_MEM_CPY(acPassword,g_stAtRightOpenFlg.acPassword,sizeof(g_stAtRightOpenFlg.acPassword));

    /* �Ƚ������Ƿ���ͬ*/
    if ( 0 == VOS_StrCmp(acPassword, (VOS_CHAR *)aucCmdTmp))
    {
        /* �ϱ�OK����¼��Ȩ�� */
        At_FormatResultData(ucIndex, AT_OK);
        bIsRight = VOS_TRUE;
        return VOS_FALSE;
    }

    /* �ϱ�ERROR */
    At_FormatResultData(ucIndex, AT_ERROR);
    return VOS_FALSE;
}

/*****************************************************************************
 Prototype      : At_PppProtocolRelIndProc
 Description    : AT����PPP��·�ͷ����ָʾ��Ϣ
 Input          : pMsg
 Output         : ---
 Return Value   : VOS_VOID
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2010-03-04
    Author      : L47619
    Modification: Created function

  2.��    ��   : 2013��05��27��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  3.��    ��   : 2013��9��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����֧��UART�˿�
*****************************************************************************/
TAF_VOID At_PppProtocolRelIndProc(AT_PPP_PROTOCOL_REL_IND_MSG_STRU *pMsg)
{
    /* Modified by f00179208 for V3R3 PPP RPOJECT 2013-05-27, Begin */
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    usPppId = pMsg->usPppId;
    ucIndex = gastAtPppIndexTab[usPppId];

    /* Modified by j00174725 for UART-MODEM Project, 2013-09-21, begin */
    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    /* Modified by j00174725 for UART-MODEM Project, 2013-09-21, end */
    {
        if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
          && (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
          && (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
        {
            /* ��ATͨ���л�Ϊ����ģʽ */
            At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);

            /* ֹͣ��ʱ�� */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            /* �ظ�NO CARRIER */
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_NO_CARRIER);
        }
    }
    /* Modified by f00179208 for V3R3 PPP RPOJECT 2013-05-27, End */

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ModemMscIndProc
 ��������  : AT���չܽ��źŵĴ���
 �������  : AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2010-03-04
    Author      : L47619
    Modification: Created function

  2.��    ��   : 2011��10��15��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project:��̬���� client id

  3.��    ��   : 2013��05��27��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  4.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����֧��UART�˿�
*****************************************************************************/
VOS_VOID AT_ModemMscIndProc(AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg)
{
    /* Modified by f00179208 for V3R3 PPP RPOJECT 2013-05-27, Begin */
    VOS_UINT8                           ucIndex;

    ucIndex = pMsg->ucIndex;
    /* Modified by f00179208 for V3R3 PPP RPOJECT 2013-05-27, End */

    AT_MNTN_TraceInputMsc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);

    /* Modified by j00174725 for UART-MODEM Project, 2013-09-21, begin */
    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        AT_ModemStatusPreProc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);
    }
    else
    {
        AT_WARN_LOG1("AT_ModemMscIndProc: index %d is unused", ucIndex);
    }
    /* Modified by j00174725 for UART-MODEM Project, 2013-09-21, end */

    return;
}

/*****************************************************************************
Prototype      : At_PppMsgProc
Description    : AT����PPP���͵���Ϣ
Input          : pMsg -- VOS��Ϣָ��
Output         : None
Return Value   : None
Calls          : None
Called By      : DOPRA

  History      : ---
  1.Date       : 2009-09-24
  Author       : L47619
  Modification : Created function
*****************************************************************************/
TAF_VOID At_PppMsgProc(MSG_HEADER_STRU *pMsg)
{
    switch  (pMsg->ulMsgName)
    {
        case AT_PPP_RELEASE_IND_MSG:
            At_PppReleaseIndProc(((AT_PPP_RELEASE_IND_MSG_STRU *)pMsg)->ucIndex);
            break;

        case AT_PPP_MODEM_MSC_IND_MSG:
            AT_ModemMscIndProc((AT_PPP_MODEM_MSC_IND_MSG_STRU *)pMsg);
            break;

        case AT_PPP_PROTOCOL_REL_IND_MSG:
            At_PppProtocolRelIndProc((AT_PPP_PROTOCOL_REL_IND_MSG_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_PppMsgProc: ulMsgName is abnormal!",pMsg->ulMsgName);
            break;
    }
}

/*****************************************************************************
 �� �� ��  : At_RfCfgCnfReturnErrProc
 ��������  : DSP���ص�Rf���ý��ԭ��,�ظ���������Ĵ���
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : ִ�н��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  At_RfCfgCnfReturnErrProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRslt;

    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
       case AT_CMD_SET_FTXON:
           ulRslt = AT_FTXON_SET_FAIL;
           break;

       case AT_CMD_SET_FRXON:
           ulRslt = AT_FRXON_SET_FAIL;
           break;

       case AT_CMD_QUERY_RSSI:
           ulRslt = AT_FRSSI_OTHER_ERR;
           break;

       /* ���������ͷּ�ʱ�յ�DSP�ظ���������·��صĴ�������ͬ */
       case AT_CMD_SET_RXDIV:
       case AT_CMD_SET_RXPRI:
           ulRslt = AT_CME_RX_DIV_OTHER_ERR;
           break;

       default:
           ulRslt = AT_ERROR;
           break;
    }

   return ulRslt;
}

/*****************************************************************************
 �� �� ��  : At_RfCfgCnfReturnSuccProc
 ��������  : DSP���ص�Rf���ý��ԭ��,�ظ��ɹ�����Ĵ���
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  At_RfCfgCnfReturnSuccProc(
    VOS_UINT8                           ucIndex
)
{
    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        case AT_CMD_SET_FTXON:
            g_stAtDevCmdCtrl.ucTxOnOff = (VOS_UINT8)gastAtParaList[0].ulParaValue;

            /* ����Ǵ򿪷������������Ҫ��¼���һ��ִ�е��Ǵ򿪷�������Ǵ򿪽��ջ����� */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucTxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_TXON_OPEN;
            }
            break;

        case AT_CMD_SET_FRXON:
            g_stAtDevCmdCtrl.ucRxOnOff = (VOS_UINT8)gastAtParaList[0].ulParaValue;

            /* ����Ǵ򿪽��ջ���������Ҫ��¼���һ��ִ�е��Ǵ򿪷�������Ǵ򿪽��ջ����� */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucRxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_RXON_OPEN;
            }
            break;

        case AT_CMD_QUERY_RSSI:
            break;

        case AT_CMD_SET_RXDIV:
           if ((AT_OK == At_SaveRxDivPara(g_stAtDevCmdCtrl.usOrigBand, 1))
            && (AT_TMODE_FTM == g_stAtDevCmdCtrl.ucCurrentTMode))
           {
               g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_DIV_ON;
               g_stAtDevCmdCtrl.usRxDiv    = g_stAtDevCmdCtrl.usOrigBand;
           }
           break;

        case AT_CMD_SET_RXPRI:
            g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_PRI_ON;
            g_stAtDevCmdCtrl.usRxPri    = g_stAtDevCmdCtrl.usOrigBand;
            break;

        default:
            break;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : At_HpaRfCfgCnfProc
 ��������  : DSP���ص�Rf���ý��ԭ��
 �������  : pstMsg - DSP�ظ���Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��28��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  At_HpaRfCfgCnfProc(
    HPA_AT_RF_CFG_CNF_STRU              *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*��ȡ���ر�����û�����*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_HpaRfCfgCnfProc: set rfcfg err");
        ulRslt = At_RfCfgCnfReturnErrProc(ucIndex);
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        ulRslt = AT_OK;
        At_RfCfgCnfReturnSuccProc(ucIndex);

        /* ^FRSSI?��GDSP LOAD������յ�ID_HPA_AT_RF_CFG_CNF��Ϣ,�����ϱ�,���յ�
           ID_HPA_AT_RF_RX_RSSI_IND��Ϣʱ���ϱ� */
        if (AT_CMD_QUERY_RSSI != gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_FormatResultData(ucIndex, ulRslt);
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : AT_RfRssiIndProc
 ��������  : ��DSP�ظ���ȡ��ǰ�ŵ�RSSI��Ϣ�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��19��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��18��
    ��    ��   : c00173809
    �޸�����   : AT�ں���Ŀ���޸ĸ��������㡣

*****************************************************************************/
VOS_VOID  At_RfRssiIndProc(
    HPA_AT_RF_RX_RSSI_IND_STRU          *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_INT32                           lRssi;

    /*��ȡ���ر�����û�����*/
    ucIndex  = g_stAtDevCmdCtrl.ucIndex;

    if (AT_DSP_RF_AGC_STATE_ERROR == pstMsg->sAGCGain)  /* ���� */
    {
        AT_WARN_LOG("AT_RfRssiIndProc err");
        ulRslt = AT_FRSSI_OTHER_ERR;
    }
    else
    {
        /*Added by c00173809 for AT Project,2011-10-14,Begin */

        gstAtSendData.usBufLen = 0;

        /*����RSSI����ֵ��λ0.125dBm��Ϊ������������*1000.*/
        lRssi = pstMsg->sRSSI * AT_DSP_RSSI_VALUE_MUL_THOUSAND;

        /*��ȡ��RSSIֵ��������ֵ�ϱ�����ȷ��0.1dBm����ֵ��Ϣ�������ǰ��RSSI
          ֵΪ-85.1dBm������ֵΪ851. ����֮ǰ��1000�����Ծ�ȷ��0.1dBm����Ҫ��100*/
        if (lRssi < 0 )
        {
            lRssi = (-1*lRssi)/100;
        }
        else
        {
            lRssi = lRssi/100;
        }

        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           lRssi);

        /*Added by c00173809 for AT Project,2011-10-14,End */

        gstAtSendData.usBufLen = usLength;
        ulRslt = AT_OK;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return;
}

/*****************************************************************************
 �� �� ��  : At_HpaMsgProc
 ��������  : ��WDSP�ظ���Ϣ�Ĵ���
 �������  : pstMsg - �ظ���Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��28��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  At_HPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU                  *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_HPA_AT_RF_CFG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_WPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

/* Added by d00212987 for PDET status query, 2014-5-6, begin */
        case ID_AT_WPHY_POWER_DET_CNF:
            At_RfFpowdetTCnfProc((PHY_AT_POWER_DET_CNF_STRU *)pstMsg);
            break;
/* Added by d00212987 for PDET status query, 2014-5-6, end */

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}
/*****************************************************************************
 �� �� ��  : At_GHpaMsgProc
 ��������  : ��GDSP�ظ���Ϣ�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��28��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  At_GHPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU         *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_GHPA_AT_RF_MSG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_GHPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_GPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_FormatAtiCmdQryString
 ��������  : ����ATI�����ѯ��Ϣ�ַ���
 �������  : MODEM_ID_ENUM_UINT16                enModemId
             DRV_AGENT_MSID_QRY_CNF_STRU         *pstDrvAgentMsidQryCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
  4.��    ��   : 2013��5��20��
    ��    ��   : Y00213812
    �޸�����   : ��ȡAT�����IMEI����
*****************************************************************************/
VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf
)
{
    TAF_PH_MEINFO_STRU                  stMeInfo;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucTmp[AT_MAX_VERSION_LEN];
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;

    /* ��ʼ�� */
    usDataLen     = 0;
    ulI           = 0;
    ucCheckData   = 0;
    PS_MEM_SET(&stMeInfo, 0, sizeof(TAF_PH_MEINFO_STRU));

    /* Modified by l00171473 for DTS2012121802573, 2012-12-11, begin */

    PS_MEM_SET(aucTmp, 0x00, sizeof(aucTmp));
    /* Modified by l00171473 for DTS2012121802573, 2012-12-11, end */

    /* ��ȡModel��Ϣ */
    if ( (VOS_NULL_PTR == pstDrvAgentMsidQryCnf)
      || (DRV_AGENT_MSID_QRY_NO_ERROR != pstDrvAgentMsidQryCnf->ulResult))
    {
        return AT_ERROR;
    }

    /* ��ȡManufacturer��Ϣ */
    usDataLen = TAF_MAX_MFR_ID_LEN + 1;
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_FMRID, aucTmp, usDataLen))
    {
        AT_WARN_LOG("AT_FormatAtiCmdQryString:WARNING:NVIM Read en_NV_Item_FMRID falied!");
        return AT_ERROR;
    }
    else
    {
        PS_MEM_CPY(stMeInfo.FmrId.aucMfrId, aucTmp, usDataLen);
    }

    /* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, begin */
    /* ��ȡIMEI��Ϣ */
    for (ulI = 0; ulI < TAF_PH_IMEI_LEN; ulI++)
    {
        stMeInfo.ImeisV.aucImei[ulI] = pstDrvAgentMsidQryCnf->aucImei[ulI] + 0x30;
    }

    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        ucCheckData += (TAF_UINT8)(((pstDrvAgentMsidQryCnf->aucImei[ulI])
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1UL] * 2) / 10))
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1UL] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 1] = 0;
    /* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, end */

    /* ���ATI����ؽ�� */
    usDataLen = 0;
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Manufacturer",stMeInfo.FmrId.aucMfrId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Model",  pstDrvAgentMsidQryCnf->acModelId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Revision",pstDrvAgentMsidQryCnf->acSoftwareVerId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","IMEI",stMeInfo.ImeisV.aucImei);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s","+GCAP: +CGSM,+DS,+ES");

    gstAtSendData.usBufLen = usDataLen;

    return AT_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentMsidQryCnf
 ��������  : DRV_AGENT_MSID_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /* ��ʼ�� */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentMsidQryCnf = (DRV_AGENT_MSID_QRY_CNF_STRU *)(pRcvMsg->aucContent);

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentMsidQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_MSID_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetImeiPara: Get modem id fail.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��ATI����� */
    ulResult = AT_FormatAtiCmdQryString(enModemId, pstDrvAgentMsidQryCnf);
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (AT_ERROR == ulResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentGasMntnCmdRsp
 ��������  : DRV_AGENT_GAS_MNTN_CMD_RSP��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_GAS_MNTN_CMD_CNF_STRU    *pstDrvAgentGasMntnCmdCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGasMntnCmdCnf = (DRV_AGENT_GAS_MNTN_CMD_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult                 = AT_OK;
    usLength                 = 0;
    j                        = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGasMntnCmdCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CGAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CGAS����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstDrvAgentGasMntnCmdCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* ����״̬ */
        if (GAS_AT_CMD_NCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            if ((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
             &&((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum%3) == 0))
            {
                for (i = 0; i< (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum/3); i++)
                {
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "%d:%d,",
                                                       (i+1),
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]);
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "0x%X,",
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]&0xff);
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "%d\r\n",
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]);
                }
                gstAtSendData.usBufLen = usLength;
            }
            else if (0 == pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0");
                gstAtSendData.usBufLen = usLength;
            }
            else
            {
                ulResult = AT_ERROR;
            }
        }
        else if (GAS_AT_CMD_SCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            /* ����С��״̬ */
            if (3 != pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                ulResult = AT_ERROR;
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0x%X,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[1]&0xff);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[2]);
                gstAtSendData.usBufLen = usLength;
                ulResult = AT_OK;
            }
        }
        else if (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
        {
            /* �������� */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength +=(TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                  ",%d",
                                                  pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
        else
        {

        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentHardwareQryRsp
 ��������  : DRV_AGENT_HARDWARE_QRY_RSP��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT32                                  ulRet;
    TAF_UINT16                                  usLength;
    VOS_UINT8                                   ucIndex;
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_HARDWARE_QRY_CNF_STRU            *pHardWareCnf;

    /* ��ʼ�� */
    pRcvMsg      = (DRV_AGENT_MSG_STRU*)pMsg;
    pHardWareCnf = (DRV_AGENT_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pHardWareCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pHardWareCnf->ulResult )
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           pHardWareCnf->aucHwVer);

        gstAtSendData.usBufLen = usLength;
        ulRet                  = AT_OK;
    }
    else
    {
        ulRet                  = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentVertimeQryRsp
 ��������  : DRV_AGENT_VERTIME_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_TIME_STRU        *pstDrvAgentVersionTime;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg                     = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentVersionTime      = (DRV_AGENT_VERSION_TIME_STRU *)(pRcvMsg->aucContent);
    ulResult                    = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentVersionTime->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_VERSIONTIME_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^VERTIME����� */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstDrvAgentVersionTime->aucData);

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentYjcxSetCnf
 ��������  : DRV_AGENT_YJCX_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_SET_CNF_STRU            *pstYjcxSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxSetCnf   = (DRV_AGENT_YJCX_SET_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_YJCX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^YJCX��������� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxSetCnf->aucflashInfo);
        gstAtSendData.usBufLen = usDataLen;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentYjcxQryCnf
 ��������  : DRV_AGENT_YJCX_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_QRY_CNF_STRU            *pstYjcxQryCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxQryCnf   = (DRV_AGENT_YJCX_QRY_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_YJCX_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^YJCX��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxQryCnf->aucgpioInfo);

        gstAtSendData.usBufLen = usDataLen;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaCrpnQueryRsp
 ��������  : AT_RcvMmaCrpnQueryRsp��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCrpnQueryRsp(VOS_VOID *pMsg)
{
    MN_MMA_CRPN_QRY_CNF_MSG_STRU       *pstMnMmaCrpnQryCnfMsg;
    MN_MMA_CRPN_QRY_CNF_STRU           *pstMnMmaCrpnQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];

    /* ��ʼ�� */
    pstMnMmaCrpnQryCnfMsg   = (MN_MMA_CRPN_QRY_CNF_MSG_STRU *)pMsg;
    pstMnMmaCrpnQryCnf      = &pstMnMmaCrpnQryCnfMsg->stMnMmaCrpnQryCnf;
    ulResult                = AT_OK;
    usLength                = 0;
    ulLoop                  = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMnMmaCrpnQryCnfMsg->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCrpnQueryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CRPN_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CRPN��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (TAF_ERR_NO_ERROR != pstMnMmaCrpnQryCnfMsg->ulResult)
    {
        ulResult = At_ChgTafErrorCode(ucIndex, (VOS_UINT16)pstMnMmaCrpnQryCnfMsg->ulResult);;
    }
    else
    {
        ulResult = AT_OK;

        for (ulLoop = 0; ulLoop < pstMnMmaCrpnQryCnf->ucTotalNum; ulLoop++)
        {
            if(0 != ulLoop)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            /* ^CRPN:  */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

            /* <PLMN> */
            /* ���ձ�ˣ�����������������PLMN ID�������ʱֱ�Ӳ��������PLMN ID */
            if (2 == pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.ucPlmnType)
            {
                PS_MEM_SET(aucPlmn, 0, sizeof(aucPlmn));
                PS_MEM_CPY(aucPlmn,
                           pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.aucPlmnName,
                           pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.usPlmnNameLen);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "\"%s\"",
                                                   aucPlmn);
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "\"%X%X%X",
                                                   (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 8,
                                                   (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 4,
                                                   (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc));


                if (6 == pstMnMmaCrpnQryCnf->ucMaxMncLen)
                {
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                       "%X",
                                                       (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 8);

                }
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%X%X\"",
                                                   (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 4,
                                                   (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc));
            }

            /* <short name> */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",\"%s\"",
                                               pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameShort);

            /* <long name> */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",\"%s\"",
                                               pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameLong);
        }

        gstAtSendData.usBufLen = usLength;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}



/*****************************************************************************
 �� �� ��  : AT_RcvAtMmaUsimStatusInd
 ��������  : AT_RcvMmaCrpnQueryRsp��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��24��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II
*****************************************************************************/
VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
    AT_MMA_USIM_STATUS_IND_STRU        *pstAtMmaUsimStatusIndMsg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    /* ��ʼ�� */
    pstAtMmaUsimStatusIndMsg   = (AT_MMA_USIM_STATUS_IND_STRU *)pMsg;

    enModemId = VOS_GetModemIDFromPid(pstAtMmaUsimStatusIndMsg->ulSenderPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        return VOS_ERR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* ˢ�¿�״̬ȫ�ֱ��� */
    pstUsimInfoCtx->enCardType   = pstAtMmaUsimStatusIndMsg->enCardType;
    pstUsimInfoCtx->enCardStatus = pstAtMmaUsimStatusIndMsg->enCardStatus;
    pstUsimInfoCtx->ucIMSILen    = pstAtMmaUsimStatusIndMsg->ucIMSILen;
    PS_MEM_CPY(pstUsimInfoCtx->aucIMSI, pstAtMmaUsimStatusIndMsg->aucIMSI, NAS_MAX_IMSI_LENGTH);
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : At_RcvAtCcMsgStateQryCnfProc
 ��������  : AT_CC_MSG_STATE_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg)
{
    AT_CC_STATE_QRY_CNF_MSG_STRU           *pstAtCcStateQryCnfMsg;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              i;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstAtCcStateQryCnfMsg = (AT_CC_STATE_QRY_CNF_MSG_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtCcStateQryCnfMsg->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰδ�ȴ�������ظ� */
    if (AT_CMD_CC_STATE_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CCC��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (0 == pstAtCcStateQryCnfMsg->ucCallNum)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        for ( i = 0 ; i < pstAtCcStateQryCnfMsg->ucCallNum ; i++ )
        {
            AT_ShowCccRst(&pstAtCcStateQryCnfMsg->astCcStateInfoList[i],&usLength);
        }

        if (0 == usLength)
        {
            ulResult = AT_ERROR;
        }
    }

    /* ������ */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaCmmSetCmdRsp
 ��������  : AT_MMA_CMM_SET_CMD_RSP��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg)
{
    MN_MM_TEST_CMD_RSP_MSG_STRU        *pstMnMmTestCmdRspMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                              i;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstMnMmTestCmdRspMsg = (MN_MM_TEST_CMD_RSP_MSG_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMnMmTestCmdRspMsg->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CMM��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMnMmTestCmdRspMsg->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        if (pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum > 0)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentFullHardwareQryRsp
 ��������  : DRV_AGENT_FULL_HARDWARE_QRY_RSP��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg)
{
    TAF_UINT16                                       usLength;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU            *pstEvent;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_FULL_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s ",
                                           pstEvent->aucModelId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s,",
                                           pstEvent->aucRevisionId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s\"",
                                           pstEvent->aucHwVer);

        gstAtSendData.usBufLen = usLength;

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : At_SendRfCfgAntSelToHPA
 ��������  : �ڽ��ջ��򿪺�,���зּ������л�ʱ�����·������������HPA
 �������  : ucDivOrPriOn - Ҫ�����ּ���������
 �������  : ��
 �� �� ֵ  : ���ط��ͽ����AT_FAILURE:����ʧ�ܣ�AT_SUCCESS:���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��18��
   ��    ��   : c00173809
   �޸�����   : AT Project,�ú�����AtSetParaCmd.c�Ƶ����ļ�
*****************************************************************************/
VOS_UINT32 At_SendRfCfgAntSelToHPA(VOS_UINT8 ucDivOrPriOn)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                           ulLength;
    VOS_UINT16                           usMask;

    /* ����AT_HPA_RF_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(AT_HPA_RF_CFG_REQ_STRU));

    /* Modified by L00171473 for DTS2012010901510 DSP PID����, 2012-01-07, begin */

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid        = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid      = DSP_PID_WPHY;
    pstMsg->ulLength           = ulLength;

    /* Modified by L00171473 for DTS2012010901510 DSP PID����, 2012-01-07, end */

    /* ��д��Ϣ�� */
    pstMsg->usMsgID            = ID_AT_HPA_RF_CFG_REQ;
    usMask                     = W_RF_MASK_RX_ARFCN | W_RF_MASK_RX_ANTSEL \
                                 | W_RF_MASK_RX_RXONOFF;

    /* ��λ��ʶ�������� */
    pstMsg->stRfCfgPara.usMask = usMask;

    if (AT_RX_DIV_ON == ucDivOrPriOn)
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_TWO;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ALL_ANT_ON;
    }
    else
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_ONE;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ANT1_ON;
    }

    pstMsg->stRfCfgPara.usRxBand       = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->stRfCfgPara.usRxFreqNum    = g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetSimlockCnf
 ��������  : DRV_AGENT_SIMLOCK_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��3��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2012��2��20��
    ��    ��   : l60609
    �޸�����   : B060 Prj:SIMLOCK��ȫ������C�˴���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_SET_SIMLOCK_CNF_STRU                  *pstEvent;
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_SET_SIMLOCK_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryRxdivCnf
 ��������  : DRV_AGENT_RXDIV_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��22��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_QRY_RXDIV_CNF_STRU                    *pstEvent;
    VOS_UINT32                                       ulUserDivBandsLow;
    VOS_UINT32                                       ulUserDivBandsHigh;
    VOS_UINT32                                       ulDrvDivBandsLow;
    VOS_UINT32                                       ulDrvDivBandsHigh;
    VOS_UINT16                                       usLen;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_QRY_RXDIV_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_QRY_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLen                  = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usDrvDivBands,
                                             &ulDrvDivBandsLow,
                                             &ulDrvDivBandsHigh);
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usCurBandSwitch,
                                             &ulUserDivBandsLow,
                                             &ulUserDivBandsHigh);

        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR*)pgucAtSndCodeAddr,
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        if (0 != ulDrvDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X%08X,",
                                            0,
                                            ulDrvDivBandsHigh,ulDrvDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X,",
                                            0,
                                            ulDrvDivBandsLow);
        }

        if (0 != ulUserDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X%08X",
                                            ulUserDivBandsHigh,
                                            ulUserDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X",
                                            ulUserDivBandsLow);
        }
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "\r\n");
        /* Added by f00179208 for DTS2011061400695,2011-06-29 Begin */
        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        /* Added by f00179208 for DTS2011061400695,2011-06-29 End */
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "%d,%X,%X",
                                        1,
                                        0,
                                        0);
        gstAtSendData.usBufLen = usLen;

        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_CME_UNKNOWN;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetRxdivCnf
 ��������  : DRV_AGENT_RXDIV_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2012��1��16��
    ��    ��   : f62575
    �޸�����   : SMALL IMAGE���Ժ���: V3R1�����ͬ��
                                ���ջ�û�д�����£���ֹ�û����÷ּ�����
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_AT_RXDIV_CNF_STRU                     *pstEvent;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_AT_RXDIV_CNF_STRU *)pRcvMsg->aucContent;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_OTHER_ERR == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

        return VOS_ERR;
    }

    if( AT_DSP_RF_SWITCH_ON == pstEvent->ucRxOnOff )
    {
        if( DRV_AGENT_CME_RX_DIV_BAND_ERR == pstEvent->ulResult )
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

            return VOS_ERR;
        }

        if (AT_FAILURE == At_SendRfCfgAntSelToHPA(AT_RX_DIV_ON))
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

            return VOS_ERR;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_RXDIV;
        g_stAtDevCmdCtrl.ucIndex               = ucIndex;
        g_stAtDevCmdCtrl.usOrigBand            = pstEvent->usSetDivBands;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_ERROR);
        /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetNvRestoreCnf
 ��������  : DRV_AGENT_NVRESTORE_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��03��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                *pstEvent;

    /* ��ʼ�� */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_NVRESTORE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstEvent->ulResult);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryNvRestoreRstCnf
 ��������  : DRV_AGENT_NVRSTSTTS_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��03��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2011��12��1��
    ��    ��   : z60575
    �޸�����   : DTS2012071704644�����߲�ʶ��OK
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRestoreStatus;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* ��ʼ�� */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_NVRSTSTTS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ((AT_NV_RESTORE_RESULT_INIT == pstEvent->ulResult)
     || (AT_NV_RESTORE_RUNNING == pstEvent->ulResult))
    {
        /* Modified by z60575 for DTS2012071704644, 2012-7-28, begin */
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
        /* Modified by z60575 for DTS2012071704644, 2012-7-28, end */
    }
    else if (VOS_OK == pstEvent->ulResult)
    {
        ulRestoreStatus = AT_NV_RESTORE_SUCCESS;
    }
    else
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                     ulRestoreStatus);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentNvRestoreManuDefaultRsp
 ��������  : DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��04��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRst;
    VOS_UINT32                                       ulResult;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* ��ʼ�� */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_F_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulResult = pstEvent->ulResult;
    if ( NV_OK != ulResult )
    {
        ulRst = AT_ERROR;
    }
    else
    {
        g_bSetFlg = VOS_TRUE;

        /* E5֪ͨAPP�ָ��û�����  */
        AT_PhSendRestoreFactParm();

        ulRst = AT_OK;
    }
    At_FormatResultData(ucIndex, ulRst);

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : AT_GetImeiValue
 ��������  : ^PHYNUM ��ȡNV���ȡIMEI
 �������  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT8 aucImei[TAF_PH_IMEI_LEN + 1]
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��3��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32  AT_GetImeiValue(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN + 1]
)
{
    VOS_UINT8                               aucBuf[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                               ucCheckData;
    VOS_UINT32                              ulDataLen;
    VOS_UINT32                              i;

    ucCheckData = 0;
    ulDataLen   = TAF_PH_IMEI_LEN;

    /* Modified by l00171473 for DTS2012121802573, 2012-12-11, begin */

    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));
    /* Modified by l00171473 for DTS2012121802573, 2012-12-11, end */

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_IMEI, aucBuf, ulDataLen))
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    {
        AT_WARN_LOG("TAF_GetImeiValue:Read IMEI Failed!");
        return VOS_ERR;
    }
    else
    {
        ucCheckData = 0;
        for (i = 0; i < (TAF_PH_IMEI_LEN-2); i += 2)
        {
            ucCheckData += aucBuf[i]
                          +((aucBuf[i+1UL] + aucBuf[i+1UL])/10)
                          +((aucBuf[i+1UL] + aucBuf[i+1UL])%10);
        }
        ucCheckData = (10 - (ucCheckData%10))%10;
        AT_DeciDigit2Ascii(aucBuf, (VOS_UINT8)ulDataLen, aucImei);
        aucImei[TAF_PH_IMEI_LEN-2] = ucCheckData+0x30;
        aucImei[TAF_PH_IMEI_LEN-1] = 0;
    }
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetGpioplRsp
 ��������  : ����GPIO���ܽŵ�ƽ�Ļظ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg)
{

    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_GPIOPL_SET_CNF_STRU      *pstDrvAgentGpioSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGpioSetCnf = (DRV_AGENT_GPIOPL_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGpioSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_GPIOPL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE == pstDrvAgentGpioSetCnf->bFail)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ����AT_FormATResultDATa���������� */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryGpioplRsp
 ��������  : ��ѯGPIO�̵ܽ�ƽ�ظ��Ĵ���
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_GPIOPL_QRY_CNF_STRU        *pstGpioQryCnf;
    VOS_UINT16                            usLength;
    VOS_UINT32                            i;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* ��ʼ����Ϣ����ȡucContent */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstGpioQryCnf         = (DRV_AGENT_GPIOPL_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstGpioQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_GPIOPL_QRY */
    if (AT_CMD_GPIOPL_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /*��λAT״̬*/
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstGpioQryCnf->bFail)
    {
        /* ��ӡ��� */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:", g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < DRVAGENT_GPIOPL_MAX_LEN; i++)
        {
           usLength += (VOS_UINT16)At_sprintf (AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%02X", pstGpioQryCnf->aucGpiopl[i]);
        }

        gstAtSendData.usBufLen = usLength;
        ulResult               = AT_OK;
    }
    else
    {
        /* ����AT_FormATResultDATa���������� */
        gstAtSendData.usBufLen = 0;
        ulResult               = AT_ERROR;
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetDatalockRsp
 ��������  : dATalock���ú����ظ��Ĵ���
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_DATALOCK_SET_CNF_STRU    *pstDatalockSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDatalockSetCnf         = (DRV_AGENT_DATALOCK_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDatalockSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_DATALOCK_SET */
    if (AT_CMD_DATALOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstDatalockSetCnf->bFail)
    {
        /* ����dATalock�ѽ��� */
        g_bAtDataLocked    =  VOS_FALSE;
        ulResult           =  AT_OK;
    }
    else
    {
        ulResult           =  AT_ERROR;
    }

    /* ����AT_FormAtResultData����������  */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
 }

/* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
/*****************************************************************************
 �� �� ��  : AT_GetSimLockStatus
 ��������  : AT^SIMLOCKʹ��״̬��ѯ����,
                ����Ӳ���ܸ��ư汾��
                �����ļ���������У��������en_NV_Item_CardlockStatus���̣�
                ����������Ȼ��ȡen_NV_Item_CardlockStatus״̬��
                ���������ý�����            ��en_NV_Item_CustomizeSimLockPlmnInfo��Plmn��Ϣ,
                ��Чʱ����1,��             ����,
                ��������·���0,�Ǽ���;
              ����У�������Ҫ��C����ɣ��˴������첽�������
 �������  :ucIndex --- �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��02��3��
    ��    ��   : f62575
    �޸�����   : B050 SIMLOCK�����Ӳ���ܸ��ƹ���: ��Ϊͨ������У���������״̬������C����ɣ�
                 �޸�Ϊ�첽����
*****************************************************************************/
VOS_UINT32 AT_GetSimLockStatus(VOS_UINT8 ucIndex)
{

    /* ����Ϣ��C�˻�ȡSIMLOCK ״̬��Ϣ */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId, 0,
                                    TAF_PH_SIMLOCK_VALUE_PARA, VOS_NULL_PTR))
    {
        AT_WARN_LOG("AT_GetSimLockStatus: Taf_ParaQuery fail.");
        return VOS_ERR;
    }

    /* ^SIMLOCK=2��ѯUE������״̬����AT�����������̣���Ҫ��������������ʱ�������¶˿�״̬ */
    if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_SIMLOCKSTATUS_READ;

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    return VOS_OK;
}
/* Modified by f62575 for B050 Project, 2012-2-3, end   */

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryTbatvoltRsp
 ��������  : ��ص�ѹ��ѯ�ظ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBATVOLT_QRY_CNF_STRU    *pstTbatvoltQryCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstTbatvoltQryCnf         = (DRV_AGENT_TBATVOLT_QRY_CNF_STRU *)pRcvMsg->aucContent;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstTbatvoltQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_TBATVOLT_QRY*/
    if (AT_CMD_TBATVOLT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ص�ѹ��ѯ����ж� */
    if (VOS_TRUE != pstTbatvoltQryCnf->bFail)
    {

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstTbatvoltQryCnf->lBatVol);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = AT_ERROR;
    }

    /* ����AT_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/* Added by f00179208 for AT Project��2011-10-06,  Begin */
/*****************************************************************************
�� �� ��  : At_RcvVcMsgQryModeCnfProc
��������  : VC��Ϣ��ѯ����ģʽ�ظ��Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2011��10��15��
    ��    ��   : f00179208
    �޸�����   : ��������,����AT����Ľ���ظ�
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  4.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE�������Ͷ������
  5.��    ��   : 2013��10��08��
    ��    ��   : j00174725
    �޸�����   : TQE
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryModeCnfProc(MN_AT_IND_EVT_STRU *pstData)
{

    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, begin*/
    VOS_UINT16                           usVoiceMode;
    /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, end*/
    /* Modified by j00174725 for TQE, 2013-10-08, begin */
    VOS_UINT16                           usDevMode;
    /* Modified by j00174725 for TQE, 2013-10-08, end */
    VOS_UINT32                           ulRet;


    /* ��ʼ�� */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* Modified by j00174725 for TQE, 2013-10-08, begin */
    /* ��ʽ��VMSET����� */
    if (AT_CMD_VMSET_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usDevMode = pstEvent->enDevMode;

        /* ��Ч��ģʽ��ֱ�ӷ���ERROR */
        if (usDevMode >= VC_PHY_DEVICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            usDevMode);
            ulRet = AT_OK;
        }
    }
    /* Modified by j00174725 for TQE, 2013-10-08, end */
    /* ��ʽ��CVOICE����� */
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if ( AT_CMD_CVOICE_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ת��ΪӦ����VC����ģʽ */
        usVoiceMode     = APP_VC_VcPhyVoiceMode2AppVcVoiceMode(pstEvent->enDevMode);

        /* ��Ч��ģʽ��ֱ�ӷ���ERROR */
        if (usVoiceMode >= APP_VC_VOICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen =(VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           "%s: %d, %d, %d, %d",
                                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                           usVoiceMode,
                                                           AT_PCVOICE_SAMPLE_RATE,
                                                           AT_PCVOICE_DATA_BIT,
                                                           AT_PCVOICE_FRAME_PERIOD);
            ulRet = AT_OK;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else
    {
        return;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}

/*****************************************************************************
�� �� ��  : At_RcvVcMsgSetPortCnfProc
��������  : VC��Ϣ���ö˿ڻظ��Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2011��10��15��
    ��    ��   : f00179208
    �޸�����   : ��������,����AT����Ľ���ظ�
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_VOID At_RcvVcMsgSetPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    APP_VC_EVENT_INFO_STRU             *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (VOS_TRUE == pstEvent->bSuccess)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}

/*****************************************************************************
�� �� ��  : At_RcvVcMsgQryPortCnfProc
��������  : VC��Ϣ���ö˿ڻظ��Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޶���¼  :
1.  ��    ��   : 2011��10��17��
    ��    ��   : f00179208
    �޸�����   : ��������,����AT����Ľ���ظ�
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    APP_VC_VOICE_PORT_ENUM_U8            ucVoicePort;                           /* �����豸�˿ں� */
    VOS_UINT32                           ulRet;

    /* ��ʼ�� */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ѯ�Ķ˿ں� */
    ucVoicePort = pstEvent->enVoicePort;

    if (APP_VC_VOICE_PORT_BUTT > ucVoicePort)
    {
        gstAtSendData.usBufLen =
            (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %d",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucVoicePort);
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}
/* Added by f00179208 for AT Project��2011-10-06,  End */

/* Added by f00179208 for PS Project, 2011-12-08,  Begin */
/*****************************************************************************
 �� �� ��  : At_RcvRnicMsgDsflowRspProc
 ��������  : ����RNIC����������ͳ��ָʾ
 �������  : MsgBlock   *pstData
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޶���¼  :
 1.��    ��   : 2011��12��15��
   ��    ��   : f00179208
   �޸�����   : ��������,����RNIC����Ϣ
*****************************************************************************/
VOS_UINT32 AT_RcvRnicDsflowRsp(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_DATA_RATE_STRU                 stCurrentRateInfo;
    RNIC_AT_DSFLOW_RSP_STRU            *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DSFLOW_RSP_STRU *)pstMsg;
    stCurrentRateInfo.ulULDataRate      = pstRcvMsg->stRnicDataRate.ulULDataRate;
    stCurrentRateInfo.ulDLDataRate      = pstRcvMsg->stRnicDataRate.ulDLDataRate;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       stCurrentRateInfo.ulULDataRate);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       stCurrentRateInfo.ulDLDataRate);

    gstAtSendData.usBufLen = usLength;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : AT_RcvRnicDialModeCnf
 ��������  : ����RNIC�����Ĳ���ģʽ��ѯ����
 �������  : MsgBlock   *pstData
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޶���¼  :
 1.��    ��   : 2011��12��21��
   ��    ��   : f00179208
   �޸�����   : ��������,����RNIC����Ϣ
*****************************************************************************/
VOS_UINT32 AT_RcvRnicDialModeCnf(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_AT_DIAL_MODE_CNF_STRU         *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DIAL_MODE_CNF_STRU *)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                        "%s:",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%d",
                                        pstRcvMsg->ulDialMode);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d",
                                        pstRcvMsg->ulEventReportFlag);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                         ",%d",
                                         pstRcvMsg->ulIdleTime);

    gstAtSendData.usBufLen = usLength;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}
/* Added by f00179208 for PS Project, 2011-12-08,  End */

/*****************************************************************************
 Prototype      : At_ZeroReplaceBlankInString
 Description    : ���ڶ��ո��滻��0
 Input          : pData --- �ַ���
                  pLen  --- ����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2011-07-08
    Author      : f00179208
    Modification: Created function for DTS2011070803450

  2.��    ��   : 2011��10��22��
    ��    ��   : w00181244
    �޸�����   : �� V3R1��ֲ����
*****************************************************************************/
VOS_VOID At_ZeroReplaceBlankInString( VOS_UINT8 *pData, VOS_UINT32 ulLen)
{
    TAF_UINT32 ulChkLen  = 0;
    TAF_UINT8  *pWrite   = pData;
    TAF_UINT8  *pRead    = pData;

    /* ���������� */
    while ( ulChkLen < ulLen )
    {
        /* ʱ���ʽ May  5 2011 17:08:00
           ת����   May 05 2011 17:08:00 */
        if (' ' == *pRead++)
        {
            if (' ' == *pRead)
            {
                pWrite++;
                *pWrite = '0';
                pRead++;
                ulChkLen++;
            }
        }
        pWrite++;
        ulChkLen++;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryVersionRsp
 ��������  : version��ѯ���������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2012��04��19��
    ��    ��   : f62575
    �޸�����   : V7����ͬ��:  Ĭ��ֵֵ���汾���֣�������ֲ���
  4.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��3��4��
    ��    ��   : L60609
    �޸�����   : DSDA PHASE III
  6.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_QRY_CNF_STRU     *pstVersionQryCnfInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLen;
    VOS_CHAR                            acTmpTime[AT_AGENT_DRV_VERSION_TIME_LEN] = {0};
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPhyNumIsNull;

    /* DTS2012031701527 c64416 start in 2012-03-29 for ^RSFR/^RSFW */
    VOS_UINT32                          ulOpt;
    /* DTS2012031701527 c64416 end in 2012-03-29 for ^RSFR/^RSFW */
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /* Modified by l00171473 for DTS2012121802573, 2012-12-12, begin */
    stCsver.usCsver = 0;
    /* Modified by l00171473 for DTS2012121802573, 2012-12-12, end */

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &(stCsver.usCsver), sizeof(stCsver.usCsver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    /* ��ʼ����Ϣ����ȡucContent */
    ulLen                        = 0;
    pRcvMsg                      = (DRV_AGENT_MSG_STRU *)pMsg;
    pstVersionQryCnfInfo         = (DRV_AGENT_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstVersionQryCnfInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* DTS2012031701527 c64416 start in 2012-03-29 for ^RSFR/^RSFW */
    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_VERSION_QRY/AT_CMD_RSFR_VERSION_QRY, ^RSFR����Ҳ���ô˽ӿ� */
    if ((AT_CMD_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
        && (AT_CMD_RSFR_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RcvDrvAgentQryVersionRsp: Get modem id fail.");
        return VOS_ERR;
    }

    ulOpt = gastAtClientTab[ucIndex].CmdCurrentOpt;
    /* DTS2012031701527 c64416 end in 2012-03-29 for ^RSFR/^RSFW */

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*��ѯ���� */
    if(DRV_AGENT_VERSION_QRY_NO_ERROR != pstVersionQryCnfInfo->enResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    /*�汾����ʱ���ʽת������ʱ��������������ո�ĺ�һ���ո���0�滻 */
    ulLen = VOS_StrLen(pstVersionQryCnfInfo->acVerTime);
    PS_MEM_CPY(acTmpTime, pstVersionQryCnfInfo->acVerTime, ulLen + 1);
    At_ZeroReplaceBlankInString((VOS_UINT8 *)acTmpTime, ulLen);

    /* �ַ���Ԥ���� */
    usLength = TAF_CDROM_VERSION_LEN;
    At_DelCtlAndBlankCharWithEndPadding(pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, &usLength);

    /* Added by f00179208 for DTS2011070800911, 2011-07-08 Begin */
    /* ��ȡ������Ƿ�Ϊ�յı�ʶ */
    if (AT_OK != AT_PhyNumIsNull(enModemId, AT_PHYNUM_TYPE_IMEI, &bPhyNumIsNull))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp(): AT_PhyNumIsNull Error!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    /* Added by f00179208 for DTS2011070800911, 2011-07-08 End */
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    usLength = 0;

    /* Modified by f00179208 for DTS2011060304946, 2011-06-09 Begin */
    /* �ڲ��汾���ڵ���δд�������ǰ����ѯ����ʵ��ʾ��д������ź����ѯ�汾��ǰδ
       �������ָ��ڲ��汾����ʾΪ�գ�����Ѿ��������ָ��ڲ��汾����ʵ��ʾ */
    /* Modified by f00179208 for DTS2011070800911, 2011-07-08 Begin */
    if (VOS_FALSE == g_bAtDataLocked || (VOS_TRUE == bPhyNumIsNull))
    {
    /* Modified by f00179208 for DTS2011070800911, 2011-07-08 End */
    /* DTS2012031701527 c64416 start in 2012-03-29 for ^RSFR/^RSFW */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo,gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stFullHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stInterModelId.aucModelId, gaucAtCrLf);

        /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s",
                                           "^VERSION", gaucAtCrLf);

        /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");
        /* DTS2012031701527 c64416 end in 2012-03-29 for ^RSFR/^RSFW */

        gstAtSendData.usBufLen = usLength;
    }
    /* Modified by f00179208 for DTS2011060304946, 2011-06-09 Begin */

    /* DTS2012031701527 c64416 start in 2012-03-29 for ^RSFR/^RSFW */
    /* �����^RSFR�����Ĳ�ѯVERSION��Ϣ������,����^RSFR����ȥ���� */
    if(AT_CMD_RSFR_VERSION_QRY == ulOpt)
    {
        AT_SetRsfrVersionCnf(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        /* AT���ص��ַ�����AT_SetRsfrVersionCnf�д��� */
        return VOS_OK;
    }
    /* DTS2012031701527 c64416 end in 2012-03-29 for ^RSFR/^RSFW */

    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : AT_SetGlobalFchan
 ��������  : ����װ��ȫ�ֱ����Ľ���ģʽ
 �������  : VOS_UINT8 ucRATMode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��13��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetGlobalFchan(VOS_UINT8 ucRATMode)
{
    g_stAtDevCmdCtrl.ucDeviceRatMode = ucRATMode;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_SetFchanRspErr
 ��������  : Fchan�����뷵��
 �������  : AT_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetFchanRspErr(DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult)
{
    if(DRV_AGENT_FCHAN_BAND_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_BAND_CHANNEL_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_CHANNEL_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_OTHER_ERR == enResult)
    {
        g_stAtDevCmdCtrl.bDspLoadFlag = VOS_FALSE;
        AT_WARN_LOG("AT_SetFChanPara: DSP Load fail!");
        return AT_FCHAN_OTHER_ERR;
    }

    return DRV_AGENT_FCHAN_SET_NO_ERROR;

}


/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetFchanRsp
 ��������  : Fchan���ú����ظ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_FCHAN_SET_CNF_STRU       *pstFchanSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulError;

    /* ��ʼ�� */
    pRcvMsg          = (DRV_AGENT_MSG_STRU *)pMsg;
    pstFchanSetCnf   = (DRV_AGENT_FCHAN_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstFchanSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_FCHAN_SET */
    if (AT_CMD_FCHAN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �����д���Ĵ��� */
    ulError =  AT_SetFchanRspErr(pstFchanSetCnf->enResult);
    if(DRV_AGENT_FCHAN_SET_NO_ERROR != ulError)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, ulError);
        return VOS_OK;
    }

    /* �����޴���Ĵ��� */
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;
    g_stAtDevCmdCtrl.ucDeviceRatMode = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceRatMode;
    g_stAtDevCmdCtrl.ucDeviceAtBand  = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceAtBand;
    g_stAtDevCmdCtrl.stDspBandArfcn  = pstFchanSetCnf->stFchanSetReq.stDspBandArfcn;
    g_stAtDevCmdCtrl.usFDAC          = 0;                                       /* FDAC���㣬��ֹG/W��Χ���� */

    /* ����AT_FormATResultDATa���������� */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex,AT_OK);
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_GetRxpriErr
 ��������  : Rxpri���ú����ظ������봦��
 �������  : AT_AGENT_RXPRI_SET_ERROR_ENUM_UINT32 enResult
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_GetRxpriErr(DRV_AGENT_ERROR_ENUM_UINT32 enResult)
{
    if(DRV_AGENT_CME_RX_DIV_OTHER_ERR == enResult)
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    if(DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == enResult)
    {
        return AT_CME_RX_DIV_NOT_SUPPORTED;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SupportHsdpa
 ��������  : ^SFEATURE��ѯ�����Ƿ�֧��DPA����
 �������  : AT_UE_CAPA_STRU                    *pstUECapa
 �������  :*pbSupportHsdpa
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��18��
    ��    ��   : z60575
    �޸�����   : DTS2012051806821����ȡ���������NV���޸ģ���νṹ�޸�
*****************************************************************************/
VOS_VOID AT_SupportHsdpa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsdpa
    )
{
    /* Modify by z60575 for DTS2012051806821, 2012-5-18, begin */

    /* ��ʼ��Ϊ��֧��DPA */
    *pbSupportHsdpa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 2)
    {
        if (1 == pstUECapa->ulHspaStatus)
        {
            if (PS_TRUE == pstUECapa->enHSDSCHSupport)
            {
                *pbSupportHsdpa = VOS_TRUE;
            }
        }
        else
        {
            *pbSupportHsdpa = VOS_TRUE;
        }
    }
    /* Modify by z60575 for DTS2012051806821, 2012-5-18, end */
}


/*****************************************************************************
 �� �� ��  : AT_SupportHsupa
 ��������  : ^SFEATURE��ѯ�����Ƿ�֧��UPA����
 �������  : AT_UE_CAPA_STRU                    *pstUECapa
 �������  :*pbSupportHsupa
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��18��
    ��    ��   : z60575
    �޸�����   : DTS2012051806821����ȡ���������NV���޸ģ���νṹ�޸�
*****************************************************************************/
VOS_VOID AT_SupportHsupa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsupa
)
{
    /* Modify by z60575 for DTS2012051806821, 2012-5-18, begin */

    /* ��ʼ��Ϊ��֧��UPA */
    *pbSupportHsupa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 3)
    {
       if (1 == pstUECapa->ulHspaStatus)
       {
           if (PS_TRUE == pstUECapa->enEDCHSupport)
           {
               *pbSupportHsupa = VOS_TRUE;
           }
       }
       else
       {
            *pbSupportHsupa = VOS_TRUE;
       }
    }
    /* Modify by z60575 for DTS2012051806821, 2012-5-18, end */
}

/*****************************************************************************
 �� �� ��  : AT_GetWFeatureInfo
 ��������  : ^SFEATURE��ѯ����3G����
 �������  : AT_AGENT_SFEATURE_QRY_CNF_STRU *pstATAgentSfeATureQryCnf

 �������  :AT_FEATURE_SUPPORT_ST  *pstFeATure,
            VOS_UINT8               aucStrTmp[50]
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��13��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��15��
    ��    ��   : f62575
    �޸�����   : DTS2012051400682��֧��UMTS�ּ�Ƶ�ε����
  3.��    ��   : 2012��5��18��
    ��    ��   : z60575
    �޸�����   : DTS2012051806821����ȡ���������NV���޸�
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  5. ��    ��   : 2012��11��12��
     ��    ��   : t00212959
     �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪVOS_UINT32,AT����һ��
*****************************************************************************/
VOS_UINT32 AT_GetWFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf
)
{
    /* Modify by z60575 for DTS2012051806821, 2012-5-18, begin */
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    VOS_UINT32                          ulLen;
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */
    VOS_BOOL                            bSupportHsdpa;
    VOS_BOOL                            bSupportHsupa;
    VOS_UINT8                           aucStrTmp[50] = {0};
    /* Added by f62575 for DTS2012051400682, 2012-5-15, begin */
    VOS_UINT8                           aucStrDiv[AT_SFEATURE_DIV_STRING_LEN];
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    VOS_UINT32                          ulDivLen;
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */
    /* Added by f62575 for DTS2012051400682, 2012-5-15, end */

    /* Modified by l00171473 for DTS2012082204471, 2012-8-10, begin */

    bSupportHsdpa = VOS_FALSE;
    bSupportHsupa = VOS_FALSE;

    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));

    /* Modified by l00171473 for DTS2012082204471, 2012-8-10, end */

    /* ��ȡHSPA,HSPA+֧������ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_GetWFeatureInfo: en_NV_Item_WAS_RadioAccess_Capa NV Read  Fail!");
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_ERR;
    }

    /* ��ȡWcdmaƵ����Ϣ */
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    ulLen = (VOS_UINT32)AT_GetWcdmaBandStr(aucStrTmp,&(pstAtAgentSfeatureQryCnf->stBandFeature));
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end*/

    /* HSPA+�Ƿ�֧�� */
    if ((stUECapa.enAsRelIndicator >= 4)
     && (PS_TRUE == stUECapa.enMacEhsSupport)
     && (stUECapa.ucHSDSCHPhyCategory >= 10)
     && (0 != stUECapa.ucHSDSCHPhyCategoryExt)
     && (PS_TRUE == stUECapa.enHSDSCHSupport))
     {
        pstFeATure[AT_FEATURE_HSPAPLUS].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSPAPLUS].aucContent, aucStrTmp, ulLen);
     }
    /* Modify by z60575 for DTS2012051806821, 2012-5-18, end */

    /* DPA�Ƿ�֧�� */
    AT_SupportHsdpa(&stUECapa, &bSupportHsdpa);
    if (VOS_TRUE == bSupportHsdpa)
    {
        pstFeATure[AT_FEATURE_HSDPA].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSDPA].aucContent, aucStrTmp, ulLen);
    }

    /*UPA�Ƿ�֧��*/
    AT_SupportHsupa(&stUECapa, &bSupportHsupa);
    if(VOS_TRUE == bSupportHsupa)
    {
        pstFeATure[AT_FEATURE_HSUPA].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSUPA].aucContent, aucStrTmp, ulLen);
    }


    /* �ּ���Ϣ */
    pstFeATure[AT_FEATURE_DIVERSITY].ucFeatureFlag = AT_FEATURE_EXIST;
    /* UMTS�ķּ���Ϣ���*/
    /* Modified by f62575 for DTS2012051400682, 2012-5-15, begin */
    PS_MEM_SET(aucStrDiv, 0x00, sizeof(aucStrDiv));

    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    ulDivLen = (VOS_UINT32)AT_GetWcdmaDivBandStr(aucStrDiv);

    VOS_MemCpy(pstFeATure[AT_FEATURE_DIVERSITY].aucContent, aucStrDiv, ulDivLen);
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */
    /* Modified by f62575 for DTS2012051400682, 2012-5-15, end */

    /* UMTS */
    pstFeATure[AT_FEATURE_UMTS].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_UMTS].aucContent, aucStrTmp, ulLen);

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : AT_GetGFeatureInfo
 ��������  : ^SFEATURE��ѯ����2G����
 �������  : AT_AGENT_SFEATURE_QRY_CNF_STRU *pstATAgentSfeATureQryCnf

 �������  :AT_FEATURE_SUPPORT_ST  *pstFeATure,
            VOS_UINT8               aucStrTmp[50]
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��13��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��02��10��
    ��    ��   : l00171473
    �޸�����   : ���岻֧��Gʱ��SFEATURE�޸�
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2012��11��12��
    ��    ��   : t00212959
    �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪVOS_UINT32,AT����һ��
*****************************************************************************/
VOS_VOID AT_GetGFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstATAgentSfeatureQryCnf
)
{
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    VOS_UINT32                          ulLen;
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */

    VOS_UINT16                          usEgprsFlag;
    VOS_UINT8                           aucStrTmp[50] = {0};

    /* Modified by l00171473 for DTS2012082204471, 2012-8-10, begin */

    usEgprsFlag = 0;

    /* Modified by l00171473 for DTS2012082204471, 2012-8-10, end */

    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    /* ��ȡGSMƵ����Ϣ */
    ulLen = (VOS_UINT32)AT_GetGsmBandStr(aucStrTmp,&(pstATAgentSfeatureQryCnf->stBandFeature));

    /* Modified by l00171473 for ���岻֧��GʱSFEATURE�޸�, 2012-02-10, begin */
    if ( 0 == ulLen )
    {
        vos_printf("AT_GetGFeatureInfo, Not Support G.\n");
        return;
    }
    /* Modified by l00171473 for ���岻֧��GʱSFEATURE�޸�, 2012-02-10, end */

    /* ��ȡEDGE֧������ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Egprs_Flag, &usEgprsFlag,
                        sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_GetGFeatureInfo: en_NV_Item_Egprs_Flag NV Read  Fail!");
        pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_EDGE].aucContent, aucStrTmp, ulLen);
    }
    else
    {
        if (usEgprsFlag != 0)
        {
            pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
            VOS_MemCpy(pstFeATure[AT_FEATURE_EDGE].aucContent, aucStrTmp, ulLen);
        }
    }

    /* GPRS */
    pstFeATure[AT_FEATURE_GPRS].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_GPRS].aucContent, aucStrTmp, ulLen);

    /* GSM */
    pstFeATure[AT_FEATURE_GSM].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_GSM].aucContent, aucStrTmp, ulLen);
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */
}

/* Modified by c64416 for DTS2012111401195, 2012-11-14 begin */
/* added by z00212940 for TDS, DTS2012081503582 2012-8-13 begin */
/*****************************************************************************
 �� �� ��  : AT_GetTdsFeatureInfo
 ��������  : ^SFEATURE��ѯ����TDS����
 �������  : AT_FEATURE_SUPPORT_ST * pstFeATure
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��13��
    ��    ��   : z00212940
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 AT_GetTdsFeatureInfo(AT_FEATURE_SUPPORT_ST * pstFeATure)
{
    VOS_UINT32 ulRst  = 0;
    NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU stTdsFeature;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulLen;

    /* Modified by l00171473 for DTS2012121802573, 2012-12-11, begin */

    PS_MEM_SET(&stTdsFeature, 0x00, sizeof(stTdsFeature));
    /* Modified by l00171473 for DTS2012121802573, 2012-12-11, end */

    ulRst = NV_ReadEx(MODEM_ID_0, en_NV_Item_UTRAN_TDD_FREQ_BAND, &stTdsFeature, sizeof(NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        vos_printf("Read EN_NV_ID_TDS_SUPPORT_FREQ_BAND failed:0x%x.\n", en_NV_Item_UTRAN_TDD_FREQ_BAND);
        return ERR_MSP_FAILURE;
    }
    /* modifyed by M00217266 for nv, 2013-05-20, begin */
    if(stTdsFeature.ucBandCnt > NVIM_TDS_MAX_SUPPORT_BANDS_NUM)
    {
        vos_printf("Read en_NV_Item_UTRAN_TDD_FREQ_BAND stTdsFeature.ucBandCnt:%d.\n", stTdsFeature.ucBandCnt);
        return ERR_MSP_FAILURE;
    }
    /* modifyed by M00217266 for nv, 2013-05-20, end */

    /* ��ȡNV�ɹ���֧��TDS */
    pstFeATure[AT_FEATURE_TDSCDMA].ucFeatureFlag = AT_FEATURE_EXIST;

    ulLen = 0;

    /* BandA:2000Hz, BanE:2300Hz, BandF:1900Hz */
    for(i = 0; i < stTdsFeature.ucBandCnt; i++)
    {
        if(ID_NVIM_TDS_FREQ_BAND_A == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "2000,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_E == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "2300,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_F == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "1900,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }
    }

    if(ulLen > 0)
    {
        /* ���ε����һ������ */
        pstFeATure[AT_FEATURE_TDSCDMA].aucContent[ulLen - 1] = '\0';
    }

    return ERR_MSP_SUCCESS;
}
#endif
/* added by z00212940 for TDS, DTS2012081503582 2012-8-13 end */
/* Modified by c64416 for DTS2012111401195, 2012-11-14 end */

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQrySfeatureRsp
 ��������  : ^SFEATURE��ѯ������������������Բ�ѯ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��13��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
  3.��    ��   : 2012��04��13��
    ��    ��   : f62575
    �޸�����   : V7����ͬ��: ���AT_GetLteFeatureInfo�ӿڹ��ܵĸ���
                    AT_GetLteFeatureInfo�����LTE֧�ֵ�Ƶ����Ϣ
  4.��    ��   : 2012��11��12��
    ��    ��   : t00212959
    �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪVOS_UINT32,AT����һ��
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg)
{
    /* ��ʼ�� */
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf;
    VOS_UINT8                           ucIndex;
    AT_FEATURE_SUPPORT_ST              *pstFeATure;
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    VOS_UINT32                          ulLen;
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */
    VOS_UINT32                          ulReult;
    VOS_UINT8                           ucFeATrueNum;
    VOS_UINT8                           ucIndexTmp;
    VOS_UINT8                           aucFeATureName[][AT_FEATURE_NAME_LEN_MAX] =
                                        {
                                            "LTE",
                                            "HSPA+",
                                            "HSDPA",
                                            "HSUPA",
                                            "DIVERSITY",
                                            "UMTS",
                                            "EVDO",
                                            "EDGE",
                                            "GPRS",
                                            "GSM",
                                            "CDMA1X",
                                            "WIMAX",
                                            "WIFI",
                                            "GPS",
                                            /* added by z00212940 for TDS, DTS2012081503582 2012-8-13 begin */
                                            "TD"
                                            /* added by z00212940 for TDS, DTS2012081503582 2012-8-13 end */
                                        };

    pRcvMsg                      = (DRV_AGENT_MSG_STRU*)pMsg;
    pstAtAgentSfeatureQryCnf     = (DRV_AGENT_SFEATURE_QRY_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtAgentSfeatureQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_SFEATURE_QRY */
    if (AT_CMD_SFEATURE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstFeATure = (AT_FEATURE_SUPPORT_ST*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));
    if (VOS_NULL == pstFeATure)
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp: GET MEM Fail!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    VOS_MemSet(pstFeATure, 0, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));

    ulReult = AT_GetWFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }

/* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)
    ulReult = AT_GetLteFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
#endif
/* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    /* added by z00212940 for TDS, DTS2012081503582 2012-8-13 begin */
#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    ulReult = AT_GetTdsFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
#endif
    /* added by z00212940 for TDS, DTS2012081503582 2012-8-13 end */

    AT_GetGFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        /* WIFI */
        pstFeATure[AT_FEATURE_WIFI].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_sprintf((VOS_CHAR*)pstFeATure[AT_FEATURE_WIFI].aucContent, "B,G,N");
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ����֧�����Եĸ��� */
    ucFeATrueNum = 0;
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        VOS_MemCpy(pstFeATure[ucIndexTmp].aucFeatureName, aucFeATureName[ucIndexTmp],sizeof(aucFeATureName[ucIndexTmp]));
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ucFeATrueNum++;
        }
    }

    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, begin */
    ulLen = 0;
    /* ��ӡ���֧�ֵ������� */
    ulLen = (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucFeATrueNum,
                                   gaucAtCrLf);

    /* ���д�ӡ���֧�ֵ����� */
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                           "%s:%s,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstFeATure[ucIndexTmp].aucFeatureName,
                                           pstFeATure[ucIndexTmp].aucContent,
                                           gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = (VOS_UINT16)(ulLen - (VOS_UINT32)VOS_StrLen((VOS_CHAR*)gaucAtCrLf));
    /* Modified by t00212959 for DTS2012103101740, 2012-11-12, end */

    At_FormatResultData(ucIndex, AT_OK);
    PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryProdtypeRsp
 ��������  : ^PRODTYPE��ѯ�ظ�����
 �������  : VOS_VOID * pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��13��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PRODTYPE_QRY_CNF_STRU    *stProdTypeCnf;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    stProdTypeCnf            = (DRV_AGENT_PRODTYPE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stProdTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PRODTYPE_QRY */
    if (AT_CMD_PRODTYPE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProdTypeCnf->ulProdType);

    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;
}

/* Added by L60609 for AT Project��2011-10-04,  Begin*/
/*****************************************************************************
 �� �� ��  : At_ProcMsgFromDrvAgent
 ��������  : Atģ�鴦������At Agent����Ϣ
 �������  : DRV_AGENT_MSG_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID At_ProcMsgFromDrvAgent(DRV_AGENT_MSG_STRU *pMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*��g_astDrvAgentMsgProcTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromDrvAgentTab)/sizeof(AT_PROC_MSG_FROM_DRV_AGENT_STRU);

    /*����Ϣ���л�ȡMSG ID*/
    ulMsgId  = ((DRV_AGENT_MSG_STRU *)pMsg)->ulMsgId;

    /*g_astDrvAgentMsgProcTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromDrvAgentTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromDrvAgentTab[i].pProcMsgFunc(pMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 Prototype      : At_PB_Unicode2UnicodePrint
 Description    : Unicode��Unicode��ӡת��
 Input          : ucNumType--- ��������
                  pucDst   --- Ŀ���ִ�
                  usDstLen --- Ŀ���ִ�����
                  pucSrc   --- Դ�ִ�
                  usSrcLen --- Դ�ִ�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_PB_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usLen    = 0;
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucHigh1  = 0;
    TAF_UINT8  ucHigh2  = 0;
    TAF_UINT8 *pWrite   = pucDst;
    TAF_UINT8 *pRead    = pucSrc;

    if(((TAF_UINT32)(pucDst - (TAF_UINT8 *)headaddr) + (2 * usSrcLen)) >= MaxLength)
    {
        AT_ERR_LOG("At_Unicode2UnicodePrint too long");
        return 0;
    }

    /* ɨ�������ִ� */
    while( usChkLen < usSrcLen )
    {
        /* ��һ���ֽ� */
        ucHigh1 = 0x0F & (*pRead >> 4);
        ucHigh2 = 0x0F & *pRead;

        if(0x09 >= ucHigh1)   /* 0-9 */
        {
            *pWrite++ = ucHigh1 + 0x30;
        }
        else if(0x0A <= ucHigh1)    /* A-F */
        {
            *pWrite++ = ucHigh1 + 0x37;
        }
        else
        {

        }

        if(0x09 >= ucHigh2)   /* 0-9 */
        {
            *pWrite++ = ucHigh2 + 0x30;
        }
        else if(0x0A <= ucHigh2)    /* A-F */
        {
            *pWrite++ = ucHigh2 + 0x37;
        }
        else
        {

        }

        /* ��һ���ַ� */
        usChkLen++;
        pRead++;


        usLen += 2;    /* ��¼���� */
    }

    return usLen;
}

/*****************************************************************************
 Prototype      : At_PbGsmFormatPrint
 Description    : ��GSM����ĸ�λ��0���
 Input          : usMaxLength ָpucDst����󳤶�
                : pucSrc���������
                : usSrcLen ���������ĳ���
 Output         : pucDst �����GSM����
 Return Value   : ���GSM�����ĳ���

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] ���ĺ������ƣ�
*****************************************************************************/
TAF_UINT16 At_PbGsmFormatPrint(TAF_UINT16 usMaxLength,
                               TAF_UINT8  *pucDst,
                               TAF_UINT8  *pucSrc,
                               TAF_UINT16 usSrcLen)
{
    TAF_UINT32  i;

    if (usSrcLen > usMaxLength)
    {
        AT_ERR_LOG("At_PbGsmFormatPrint error: too long");

        return 0;
    }

    for (i = 0; i < usSrcLen; i++)
    {
        /* �����bit���� */
        pucDst[i] = pucSrc[i] & AT_PB_GSM7_CODE_MAX_VALUE;
    }

    return usSrcLen;
}

/*****************************************************************************
 Prototype      : At_PbOneUnicodeToIra
 Description    : ��һ��UCS2����ת��ΪIRA����
 Input          : usUnicodeChar -- UCS2����
 Output         : pucDst      -- ָ��ת�����ַ�
 Return Value   : AT_SUCCESS -- ת���ɹ�
                  AT_FAILURE -- ת��ʧ��

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_UINT32 At_PbOneUnicodeToIra(TAF_UINT16 usUnicodeChar, TAF_UINT8 *pucDst)
{
    TAF_UINT16 usIndex;

    for(usIndex = 0; usIndex < AT_PB_IRA_MAX_NUM; usIndex++)
    {
        if(usUnicodeChar == g_astIraToUnicode[usIndex].usUnicode)
        {
            *pucDst = g_astIraToUnicode[usIndex].ucOctet;

            return AT_SUCCESS;
        }
    }

    /* δ�ҵ�UCS2��Ӧ��IRA���� */
    AT_LOG1("At_PbOneUnicodeToIra error: no found [%x]",usUnicodeChar);

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_PbUnicodeToIraFormatPrint
 Description    : ��ǰ�ַ���ΪIRA����Ҫ���ucs2�ַ�ת��ΪIRA�ַ�
 Input          : ulMaxLength -- �ܴ洢ת�����ַ�����󳤶�
                  pucSrc      -- ָ���ת���ַ�
                  ulSrcLen    -- ��ת���ַ�����
 Output         : pucDst      -- ָ��ת�����ַ�
 Return Value   : ת�����IRA��������

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_UINT16 At_PbUnicodeToIraFormatPrint(TAF_UINT16 usMaxLength,
                                        TAF_UINT8  *pucDst,
                                        TAF_UINT8  *pucSrc,
                                        TAF_UINT16 usSrcLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usRetLen = 0;
    TAF_UINT8       *pucData = pucSrc;
    TAF_UINT16      usUnicodeChar;

    /* IRA�����ĳ�����UCS2�������ȵ�һ�� */
    usRetLen = usSrcLen >> 1;

    /* ���洢�ռ��Ƿ��㹻 */
    if (usRetLen > usMaxLength)
    {
       AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: too long");

       return 0;
    }

    /* �����UCS2�ַ�ͨ�����ת��ΪIRA���� */
    for (usIndex = 0; usIndex < usRetLen; usIndex++)
    {
        /* �Ƚ�UINT8����תΪUINT16 */
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));
        pucData += 2;

        if (AT_SUCCESS != At_PbOneUnicodeToIra(usUnicodeChar, &pucDst[usIndex]))
        {
            AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: no found");

            return 0;
        }
    }

    return usRetLen;
}

/*****************************************************************************
 Prototype      : At_PbUnicode82FormatPrint
 Description    : ��UCS2������82�����ʽ��ѹ
 Input          : puc82Code �����UCS2 82����,'82'���ͱ�־���ֽ��ѱ��ص�
 Input          :           ��һ��Byte��ʾ����,
                :           �ڶ�������Byte��ʾBaseCode,
                :           ���ĸ����Ժ��Byte��ʾ82ѹ���������
 Output         : pucDst �ǽ�ѹ�Ժ������
                : pulDstLen �ǽ�ѹ�Ժ�������ĳ���
 Return Value   : ��

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_VOID At_PbUnicode82FormatPrint(TAF_UINT8  *puc82Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{

    TAF_UINT16      usIndex;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    /* ȡ��82����ĳ��� */
    usSrcLen = puc82Code[0];

    /* ȡ��82�����Basecode */
    usBaseCode = (puc82Code[1] << 8) | puc82Code[2];

    if((SI_PB_ALPHATAG_MAX_LEN < usSrcLen)||(0xFFFF == usBaseCode)) /*���ݳ��ȴ���*/
    {
        *pusDstLen = 0;

        return;
    }

    /* ȡ��82���������, ���ĸ����Ժ��Byte��ʾ82ѹ��������� */
    pucSrc = puc82Code + 3;

    /* �ӵ��ĸ��ֽڿ�ʼ��82��������� */
    for(usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
           && ((usIndex + usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if(0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 82 �����Ƚ���8bit���������������� */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbUnicode8FormatPrint
 Description    : ��UCS2������81�����ʽ��ѹ
 Input          : puc81Code �����UCS2 81����,'81'���ͱ�־���ֽ��ѱ��ص�
                :           ��һ��Byte��ʾ����,
                :           �ڶ���Byte��ʾ��ָ��,
                :           ���������Ժ��Byte��ʾ81ѹ���������
 Output         : pucDst �ǽ�ѹ�Ժ������
                : pulDstLen �ǽ�ѹ�Ժ�������ĳ���
 Return Value   : ��

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_VOID At_PbUnicode81FormatPrint(TAF_UINT8  *puc81Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    if(SI_PB_ALPHATAG_MAX_LEN < puc81Code[0])    /*�ַ��������ܴ������������ֵ*/
    {
        *pusDstLen = 0;

        return;
    }

    /* ȡ��81����ĳ��� */
    usSrcLen = puc81Code[0];

    /* ȡ��81����Ļ�ָ�� */
    usBaseCode = puc81Code[1] << 7;

    /* ȡ��81���������, ���������Ժ��Byte��ʾ81ѹ��������� */
    pucSrc = puc81Code + 2;

    /* �ӵ������ֽڿ�ʼ��81��������� */
    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while ((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
            && ((usIndex+usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if (0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 81�����Ƚ���8bit���������������� */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbUnicode80FormatPrint
 Description    : ��UCS2������80��ʽ����
 Input          : pucSrc -- �����UCS2����
                : ulSrcLen -- �����UCS2��������
 Output         : pucDst -- ת��UCS2 80�������
                : pulDstLen -- ת��UCS2 80�����������
 Return Value   : ��

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_VOID At_PbUnicode80FormatPrint(TAF_UINT8  *pucSrc,
                                   TAF_UINT16 usSrcLen,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    if((0xFF == pucSrc[0])&&(0xFF == pucSrc[1]))   /*�����ַ�ΪFFFF����Ϊ��ǰ����Ϊ��*/
    {
        *pusDstLen = 0;
    }
    else
    {
        /* ����80��־λ */
        VOS_MemCpy(pucDst, pucSrc, usSrcLen);

        *pusDstLen = usSrcLen;
    }

    return;
}

/*****************************************************************************
 Prototype      :At_PbGsmExtToUnicode
 Description    :����GSM��UNICODE��չ���ҵ��򷵻سɹ������򷵻�ʧ��
 Input          : ucGsmExtChar -- GSM�ַ�
 Output         : pusUnicodeChar --  UCS2�ַ�
 Return Value   : AT_SUCCESS��AT_FAILURE

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_UINT32 At_PbGsmExtToUnicode(TAF_UINT8 ucGsmExtChar, TAF_UINT16 *pusUnicodeChar)
{
    TAF_UINT16      usIndex;

    /* ����GSM��UNICODE��չ���ҵ��򷵻سɹ������򷵻�ʧ�� */
    for (usIndex = 0; usIndex < AT_PB_GSM7EXT_MAX_NUM; usIndex++)
    {
        if (ucGsmExtChar == g_astGsm7extToUnicode[usIndex].ucOctet)
        {
            *pusUnicodeChar = g_astGsm7extToUnicode[usIndex].usUnicode;

            return AT_SUCCESS;
        }
    }

    AT_LOG1("At_PbGsmExtToUnicode warning: no found [0x%x]", ucGsmExtChar);

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      :At_PbGsmToUnicode
 Description    :��ǰ�ַ���ΪUCS2��IRA�����洢��ʽΪGSM7bit����Ҫ�Ƚ�GSM7bit���ת��ΪUCS2
 Input          : pucSrc -- �����GSM����
                : ulSrcLen -- �����GSM��������
 Output         : pucDst -- ת��UCS2�������
                : pulDstLen -- ת��UCS2�����������
 Return Value   : ��

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_VOID At_PbGsmToUnicode(TAF_UINT8  *pucSrc,
                           TAF_UINT16 usSrcLen,
                           TAF_UINT8  *pucDst,
                           TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicodeLen = 0;
    TAF_UINT16      *pusUnicode  = (TAF_UINT16 *)pucDst;
    TAF_UINT16      usUnicodeChar;

    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        /* Ϊ������Щƽ̨��GSMģʽ��д���¼ʱδ�����BIT���� */
        pucSrc[usIndex] = pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE;

        /* ��0x1B�ַ���ֱ�Ӳ�GSM��UNICODE������ */
        if (AT_PB_GSM7EXT_SYMBOL != pucSrc[usIndex])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* ��ǰGSM����Ϊ0x1bʱ,����Ϊ��չ��־ */
        if ((usSrcLen - usIndex) < 2)
        {
            /* ���һ���ֽ�Ϊ0x1B����GSM��UNICODE������, ��0x1B��ΪSPACE */
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* ����0x1B 0x1B���������Ϊ���ǲ�֧�ֵ�������չ�����ֱ�ӽ�0x1B
            0x1B��ΪSPACE SPACE */
        if (AT_PB_GSM7EXT_SYMBOL == pucSrc[usIndex + 1])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex + 1]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usIndex++;
            usUnicodeLen += 2;

            continue;
        }

        /* 0x1B����Ϊ��־������GSM��UNICODE��չ�� */
        if (AT_SUCCESS == At_PbGsmExtToUnicode(pucSrc[usIndex + 1], &usUnicodeChar))
        {
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usIndex++;
            usUnicodeLen++;

            continue;
        }

       /* ����1BXX��δ����չ���У���XX��Ϊ0x1B���������ΪSPACE+XX��Ӧ���ַ� */
       usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
       AT_UNICODE2VALUE(usUnicodeChar);
       *pusUnicode = usUnicodeChar;
       pusUnicode++;
       usUnicodeLen++;
    }

    /* GSM7BIT �����п�������չ�����ַ���GSM7bit��UNICODEת�����Ȳ�һ����ԭ�������ȵ�2�� */
    *pusDstLen = (TAF_UINT16)(usUnicodeLen << 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbRecordToUnicode
 Description    : �����������ֶδ洢��ʽת��ΪUCS2��
 Input          : pEvent -- �¼�����
 Output         : pucDecode -- ת�����UCS2��
                : pusDecodeLen -- ת�����UCS2�볤��
 Return Value   : ��

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_VOID At_PbRecordToUnicode(SI_PB_EVENT_INFO_STRU *pstEvent,
                              TAF_UINT8             *pucDecode,
                              TAF_UINT16            *pusDecodeLen)
{
    TAF_UINT16      usDecodeLen = 0;

    switch(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
    {
        case SI_PB_ALPHATAG_TYPE_GSM:
            At_PbGsmToUnicode(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                              pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                              pucDecode,
                              &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_80:
            At_PbUnicode80FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_81:
            At_PbUnicode81FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_82:
            At_PbUnicode82FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        default:
            AT_ERR_LOG("At_PbRecordToUnicode error: not support code type");

            break;
    }

    *pusDecodeLen = usDecodeLen;

    return;
}

/*****************************************************************************
 Prototype      : At_Pb_AlaphPrint
 Description    : �绰����ȡ�������ݴ�ӡ����
 Input          : pEvent -- �¼�����
                : pusDataLen -- ���pgucAtSndCrLfAddr��ƫ�Ƴ���
 Output         : pucData  -- ���������
 Return Value   : AT_SUCCESS�� AT_FAILURE

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_UINT32 At_Pb_AlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* ��GSM�ַ����£���֧��UCS2���� */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {
            usReturnLen = 0;

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_FAILURE;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* ��ǰ�ַ���ΪUCS2��IRAʱ */
    {
        /* ��ǰ�ַ���ΪUCS2��IRAʱ���ȸ��ݴ洢��ʽת��ΪUCS2���� */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* ��ǰ�ַ���ΪIRAʱ����UCS2ת��ΪIRA�������*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* ��ǰ�ַ���ΪUCS2ʱ����UCS2ת��Ϊ��ӡ��ʽ���*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {
        gstAtSendData.usBufLen = 0;

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_FAILURE;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}

/* Modified by d00212987 for DTS2012042501978, 2012/05/05, begin */
/*****************************************************************************
 Prototype      : At_Pb_CnumAlaphPrint
 Description    : �绰����ȡ�������ݴ�ӡ����
 Input          : pEvent -- �¼�����
                : pusDataLen -- ���pgucAtSndCrLfAddr��ƫ�Ƴ���
 Output         : pucData  -- ���������
 Return Value   : AT_SUCCESS�� AT_FAILURE

 History        :
  1.Date        : 2011-01-19
    Author      : j00168360
    Modification: [�绰���ڶ��׶�] Created function
*****************************************************************************/
TAF_UINT32 At_Pb_CnumAlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* ��GSM�ַ����£���֧��UCS2���� */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_SUCCESS;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* ��ǰ�ַ���ΪUCS2��IRAʱ */
    {
        /* ��ǰ�ַ���ΪUCS2��IRAʱ���ȸ��ݴ洢��ʽת��ΪUCS2���� */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* ��ǰ�ַ���ΪIRAʱ����UCS2ת��ΪIRA�������*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* ��ǰ�ַ���ΪUCS2ʱ����UCS2ת��Ϊ��ӡ��ʽ���*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_SUCCESS;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}
/* Modified by d00212987 for DTS2012042501978, 2012/05/05, end */

/*****************************************************************************
 Prototype      : AT_Pb_NumberPrint
 Description    : �绰����ȡ���뼰�������ʹ�ӡ����
 Input          : pEvent -- �¼�����
                : pusDataLen -- ���pgucAtSndCrLfAddr��ƫ�Ƴ���
 Output         : pusDataLen  -- ������pgucAtSndCrLfAddr��ƫ�Ƴ���
 Return Value   : AT_SUCCESS�� AT_FAILURE

 History        :
  1.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS] Created function�����ݲ�Ʒ�����������Ϊ��ʱ����������ʾΪ129
*****************************************************************************/
TAF_VOID AT_Pb_NumberPrint(TAF_UINT16 *pusDataLen, SI_PB_EVENT_INFO_STRU *pstEvent, TAF_UINT8 *pucData)
{
    TAF_UINT16      usLength = *pusDataLen;

    if(0 == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData+usLength,
                                           ",\"\",129");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",\"");

        if (PB_NUMBER_TYPE_INTERNATIONAL == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucData,
                                               (TAF_CHAR *)pucData+usLength,
                                               "+");
        }

        PS_MEM_CPY(pucData + usLength, pstEvent->PBEvent.PBReadCnf.PBRecord.Number,
                   pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength);

        usLength += (TAF_UINT16)pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",%d",
                                           pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType);
    }

    *pusDataLen  = usLength;

    return;
}

/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : �绰����ȡ���ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_PbCNUMCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    if(SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)
    {
        return AT_SUCCESS;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
         /* Modified by d00212987 for DTS2012042501978, 2012/05/05, begin */
         ulResult = At_Pb_CnumAlaphPrint(&usLength, pEvent, pucData);
         /* Modified by d00212987 for DTS2012042501978, 2012/05/05, end */

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");

    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, begin */

    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);
    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, end */

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : �绰����ȡ���ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
  2.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS2011041403381],���ݲ�Ʒ����������绰����Ϊ��ʱ����������ʾΪ129
*****************************************************************************/
TAF_UINT32 At_PbCPBR2CmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);

    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, begin */

    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);
    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, end */

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
        ulResult = At_Pb_AlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}


/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : �绰����ȡ���ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
  2.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS2011041403381],���ݲ�Ʒ����������绰����Ϊ��ʱ����������ʾΪ129
*****************************************************************************/
TAF_UINT32 At_PbCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);

    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, begin */

    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);
    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, end */

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                                (TAF_CHAR *)pucData+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pucData,
                                        pucData+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*����������������Ҫ���油��FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            PS_MEM_CPY((TAF_CHAR *)pucData + usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",1");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",0");
    }

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbEmailPrint
 Description    : ��GSM7BIT��ʽ�洢��emailת��ΪIRA�ϱ�
 Input          : pucSrc -- �����GSM����
                : ulSrcLen -- �����GSM��������
 Output         : pucDst -- ת��IRA�������
                : pulDstLen -- ת��IRA�����������
 Return Value   : ��
 Calls          : At_PbGsmToUnicode��At_PbUnicodeToIraFormatPrint
 Called By      : At_PbSCPBRCmdPrint

 History        :
  1.Date        : 2011-01-27
    Author      : j00168360
    Modification: [�绰���ڶ���]Created function

  2.��    ��    : 2012��8��10��
    ��    ��    : y00213812
    �޸�����    : DTS2012082204471, TQE����
*****************************************************************************/
TAF_VOID At_PbEmailPrint(TAF_UINT8  *pucSrc,
                         TAF_UINT16 usSrcLen,
                         TAF_UINT8  *pucDst,
                         TAF_UINT16 *pusDstLen)
{
    TAF_UINT8   aucUCS2Code[2 * SI_PB_EMAIL_MAX_LEN];
    TAF_UINT16  usUCS2CodeLen;
    TAF_UINT16  usEMailLen = usSrcLen;

    /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, begin*/
    TAF_UINT16  usReturnLen;

    /* ��EMAIL���ȴ���64Byte�����нضϴ��� */
    if(SI_PB_EMAIL_MAX_LEN < usEMailLen)
    {
        usEMailLen = SI_PB_EMAIL_MAX_LEN;
    }

    /* �Ƚ�GSMģʽת��UCS2ģʽ */
    At_PbGsmToUnicode(pucSrc, usEMailLen, aucUCS2Code, &usUCS2CodeLen);

    /* �ٽ�UCS2ģʽת��IRAģʽ */
    usReturnLen = At_PbUnicodeToIraFormatPrint(usSrcLen, pucDst, aucUCS2Code, usUCS2CodeLen);
    if (0 == usReturnLen)
    {
        AT_INFO_LOG("At_PbEmailPrint error: usReturnLen = 0");
        return;
    }
    /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, end*/

    *pusDstLen = (TAF_UINT16)(usUCS2CodeLen >> 1);

    return;
}

/*****************************************************************************
 Prototype      : At_PbSCPBRCmdPrint
 Description    : �绰����ȡ���ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : m00128685
  1.Date        : 2009-06-18
    Author      : ---
    Modification: Created function
  2.Date        : 2011-01-27
    Author      : j00168360
    Modification: [�绰���ڶ���]���޸�EMAIL�ֶζ�ȡ
  3.Date        : 2011-04-21
    Author      : j00168360
    Modification: [DTS2011041403381],���ݲ�Ʒ����������绰����Ϊ��ʱ����������ʾΪ129
*****************************************************************************/
TAF_UINT32 At_PbSCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              i;
    TAF_UINT16              usEmailLen = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);

    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, begin */

    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pgucAtSndCrLfAddr);
    /* Modified by j00168360 for DTS2011041403381, 2011-04-21, end */

    for(i = 0; i < 3; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

        if(0 == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\",129");

            continue;
        }

        if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "+");
        }

        PS_MEM_CPY(pgucAtSndCrLfAddr + usLength,pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].Number,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength);

        usLength += (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",%d",
                                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType);
    }

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCrLfAddr,
                                        pgucAtSndCrLfAddr+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*����������������Ҫ���油��FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr + usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    if (AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",1");
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",0");
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

    if ( 0 != pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen )
    {
        At_PbEmailPrint(pEvent->PBEvent.PBReadCnf.PBRecord.Email.Email,
                        (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen,
                        (TAF_UINT8 *)(pgucAtSndCrLfAddr + usLength),
                        &usEmailLen);

        usLength += usEmailLen;

    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbSearchCnfProc
 Description    : �绰���������ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : h59254
  1.Date        : 2009-03-14
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_VOID At_PbSearchCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT16              usLength = 0;

    gulPBPrintTag = TAF_TRUE;

/*
    if(0 != usLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
    }
*/
    if(pEvent->PBEvent.PBSearchCnf.PBRecord.ValidFlag == SI_PB_CONTENT_INVALID)/*��ǰ��������Ч*/
    {
        return;              /*���ز�����*/
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pEvent->PBEvent.PBSearchCnf.PBRecord.Index);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",\"");

    if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"+");
    }

    PS_MEM_CPY(pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.Number, pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength);
    usLength += (TAF_UINT16)pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d,",pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    /* PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag, pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength); */
    /* usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength; */

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType & 0x80))  /* DATA:IRA */
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr+usLength,"%X",pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType);

        usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);

        if((pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength%2) == 0)/*����������������Ҫ���油��FF*/
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"FF");
        }
    }
    else                                    /* DATA:UCS2 */
    {
        if(AT_CSCS_UCS2_CODE == gucAtCscsType)       /* +CSCS:UCS2 */
        {
            usLength += (TAF_UINT16)At_Ascii2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
        }
        else
        {
            PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
            usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength;
        }
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    if(AT_V_ENTIRE_TYPE == gucAtVType)
    {
        PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*Codeǰ���\r\n*/
        At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usLength+2);
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);
    }
}


/*****************************************************************************
 Prototype      : At_PbReadCnfProc
 Description    : �绰����ȡ���ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : z00100318
  1.Date        : 2008-11-10
    Author      : ---
    Modification: Created function
  2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ :oamȷ�ϵ绰����E5��LCARDɾ����
*****************************************************************************/
TAF_UINT32 At_PbReadCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usPBReadPrintLength;
    ulResult                            = AT_FAILURE;
    usPBReadPrintLength                 = 0;

    if (SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)/*��ǰ��������Ч*/
    {
        return AT_SUCCESS;              /*���ز�����*/
    }
    else
    {
        if (TAF_FALSE == gulPBPrintTag)
        {
             usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr,"%s","\r\n");
        }

        gulPBPrintTag = TAF_TRUE;

        if(AT_CMD_CPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� ^CPBR �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_CPBR2_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� +CPBR �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbCPBR2CmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� ^SCPBR �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbSCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pEvent);
        }
        else if(AT_CMD_CNUM_READ == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� CNUM �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbCNUMCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else
        {
            AT_ERR_LOG1("At_PbReadCnfProc: the Cmd Current Opt %d is Unknow", gastAtClientTab[ucIndex].CmdCurrentOpt);

            return AT_FAILURE;
        }
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if(AT_SUCCESS == ulResult)
    {
        usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr + usPBReadPrintLength,
                                                "%s","\r\n");
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usPBReadPrintLength);

    PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*AT���Buffer��ǰ�����ֽڻָ�Ϊ\r\n*/

    return ulResult;
}


/*****************************************************************************
 Prototype      : At_PbCallBackFunc
 Description    : �绰�������ϱ�����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
  3.��    ��   : 2007��06��11��
    ��    ��   : h44270
    �޸�����   : ���ⵥA32D11418
  4.��    ��   : 2007��11��22��
    ��    ��   : z00100318
    �޸�����   : PB�Ż�
  5.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT32 ulSendMsg = 0;
    TAF_UINT8  ucIndex;

    if(TAF_NULL_PTR == pEvent)      /*��������*/
    {
        AT_WARN_LOG("At_PbCallBackFunc pEvent NULL");

        return;
    }

    if(AT_FAILURE == At_ClientIdToUserId(pEvent->ClientId, &ucIndex))/*�ظ��Ŀͻ������ݴ���*/
    {
        //At_SendReportMsg(MN_CALLBACK_PHONE_BOOK, (TAF_UINT8*)pEvent, sizeof(SI_PB_EVENT_INFO_STRU));

        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_PbMsgProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if(AT_CMD_CNUM == gastAtClientTab[ucIndex].CmdIndex)
    {
        pEvent->PBError = ((TAF_ERR_PB_NOT_FOUND == pEvent->PBError)?TAF_ERR_NO_ERROR:pEvent->PBError);
    }

    if(TAF_ERR_NO_ERROR != pEvent->PBError)/*����������Ϣ����*/
    {
        ulSendMsg = SI_TRUE;
    }
    else if(((pEvent->PBEventType == SI_PB_EVENT_READ_CNF)||(pEvent->PBEventType == SI_PB_EVENT_SREAD_CNF))
        && (pEvent->PBLastTag != SI_PB_LAST_TAG_TRUE))/*���ڶ�ȡ������Ҫ����˲���ͨ��һ���Ե���Ϣ�������ݽ��д���*/
    {
        if ( AT_SUCCESS != At_PbReadCnfProc(ucIndex,pEvent) )
        {
            AT_WARN_LOG("At_PbCallBackFunc:At_PbReadCnfProc Error");
        }

        ulSendMsg = SI_FALSE;
    }
    else if(pEvent->PBEventType == SI_PB_EVENT_SEARCH_CNF)
    {
        if( SI_PB_LAST_TAG_TRUE == pEvent->PBLastTag )
        {
            ulSendMsg = SI_TRUE;
        }
        else
        {
            At_PbSearchCnfProc(ucIndex,pEvent);
            return;
        }
    }
    else        /*�����Ļظ�����ͨ����Ϣ����һ���Է��ʹ���*/
    {
        ulSendMsg = SI_TRUE;
    }

    if (SI_TRUE == ulSendMsg)
    {
        At_SendReportMsg(MN_CALLBACK_PHONE_BOOK,(TAF_UINT8*)pEvent,sizeof(SI_PB_EVENT_INFO_STRU));
    }

    return;
}

/* Added by L60609 for AT Project��2011-10-04,  End*/

/* Added by z00214637 for DSDA GUNAS C CORE, 2012-12-28, begin */
/*****************************************************************************
�� �� ��  : At_RcvVcMsgSetGroundCnfProc
��������  : VC ǰ̨����̨ģʽ���ûظ���Ϣ�Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2012��12��28��
    ��    ��   : ����/z00214637
    �޸�����   : ��������,����AT����Ľ���ظ�
*****************************************************************************/
VOS_VOID At_RcvVcMsgSetGroundCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CBG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    if (VOS_OK == pstData->aucContent[0])
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ������ý�� */
    gstAtSendData.usBufLen = 0;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}

/*****************************************************************************
�� �� ��  : At_RcvVcMsgQryGroundRspProc
��������  : VC��Ϣ��ѯǰ̨ģʽ�ظ��Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2012��12��28��
    ��    ��   : ����/z00214637
    �޸�����   : ��������,����AT����Ľ���ظ�
*****************************************************************************/
VOS_VOID At_RcvVcMsgQryGroundRspProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_QRY_GROUNG_RSP_STRU         *pstQryRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CBG_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    /* ��ʼ�� */
    pstQryRslt = (APP_VC_QRY_GROUNG_RSP_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryRslt->ucQryRslt)
    {
        /* �����ѯ��� */
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "^CBG:%d",
                                                        pstQryRslt->enGround);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}

/* Added by z00214637 for DSDA GUNAS C CORE, 2012-12-28, end */

/* Added by f00179208 for AT Project��2011-10-06,  Begin */
/*****************************************************************************
 �� �� ��  : At_ProcMsgFromVc
 ��������  : Atģ�鴦������VC����Ϣ
 �������  : MN_AT_IND_EVT_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��06��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��28��
    ��    ��   : ����/z00214637
    �޸�����   : ^CBG����ʵ��
  3.��    ��   : 2014��3��27��
    ��    ��   : j00174725
    �޸�����   : Ecall��Ŀ
*****************************************************************************/
VOS_VOID At_ProcMsgFromVc(MN_AT_IND_EVT_STRU *pMsg)
{
    switch(pMsg->usMsgName)
    {
        case APP_VC_MSG_CNF_QRY_MODE:
            At_RcvVcMsgQryModeCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_SET_PORT:
            At_RcvVcMsgSetPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_QRY_PORT:
            At_RcvVcMsgQryPortCnfProc(pMsg);
            break;

        /* Added by z00214637 for DSDA GUNAS C CORE, 2012-12-28, begin */
        case APP_VC_MSG_SET_FOREGROUND_CNF:
        case APP_VC_MSG_SET_BACKGROUND_CNF:
            /*AT ���� VC �ϱ���ǰ̨ģʽ����̨ģʽCNF MSG*/
            At_RcvVcMsgSetGroundCnfProc(pMsg);
            break;

        case APP_VC_MSG_FOREGROUND_RSP:
            /*AT ����VC �ϱ��Ĳ�ѯǰ̨ģʽ�ظ���Ϣ*/
            At_RcvVcMsgQryGroundRspProc(pMsg);
            break;
        /* Added by z00214637 for DSDA GUNAS C CORE, 2012-12-28, end */

        /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        case APP_VC_MSG_SET_MSD_CNF:
            AT_RcvVcMsgSetMsdCnfProc(pMsg);
            break;

        case APP_VC_MSG_QRY_MSD_CNF:
            AT_RcvVcMsgQryMsdCnfProc(pMsg);
            break;

        case APP_VC_MSG_QRY_ECALL_CFG_CNF:
            AT_RcvVcMsgQryEcallCfgCnfProc(pMsg);
            break;
#endif
        /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

        /* Added by g00261581 for V3R3 DTMF Decoder Project, 2014-05-09, begin */
        case APP_VC_MSG_DTMF_DECODER_IND:
            At_RcvVcMsgDtmfDecoderIndProc(pMsg);
            break;
        /* Added by g00261581 for V3R3 DTMF Decoder Project, 2014-05-09, end */

        default:
            return;
    }
    return;
}
/* Added by f00179208 for AT Project��2011-10-06,  End */

/* Added by f00179208 for PS Project��2011-12-08,  Begin */
/*****************************************************************************
 �� �� ��  : At_ProcMsgFromVc
 ��������  : Atģ�鴦������RNIC����Ϣ
 �������  : MN_AT_IND_EVT_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��08��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_RcvRnicMsg(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulRst;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader                        = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        /* ����RNIC�����������ϱ� */
        case ID_RNIC_AT_DSFLOW_RSP:

            ulRst = AT_RcvRnicDsflowRsp(pstMsg);
            break;

        /* ����RNIC�����Ĳ���ģʽ��ѯ�ظ� */
        case ID_RNIC_AT_DIAL_MODE_CNF:

            ulRst = AT_RcvRnicDialModeCnf(pstMsg);
            break;

        default:
            ulRst = VOS_OK;
            break;
    }
    return ulRst;
}
/* Added by f00179208 for PS Project��2011-12-08,  End */

/* Added by o00132663 for AT Project��2011-10-06,  Begin */
/*****************************************************************************
 �� �� ��  : At_ProcMsgFromCc
 ��������  : Atģ�鴦������CC����Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��06��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID At_ProcMsgFromCc(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case AT_CC_MSG_STATE_QRY_CNF:
            At_RcvAtCcMsgStateQryCnfProc(pMsg);
            break;

        default:
            break;
    }
    return;
}
/* Added by o00132663 for AT Project��2011-10-06,  End */

/* Added by A00165503 for AT Project, 2011-10-20, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvNdisMsg
 ��������  : NDISģ����Ϣ����
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_RcvNdisMsg(MsgBlock* pMsg)
{
    VOS_UINT32                          ulResult;
    AT_FW_MSG_STRU                     *pstAtFwMsg;
    AT_FW_CMD_BINARY_MSG_STRU          *pstBinaryInfo;
    AT_NDIS_MSG_STRU                   *pstNdisMsg;

    pstAtFwMsg      = (AT_FW_MSG_STRU*)(pMsg->aucValue);
    pstBinaryInfo   = (AT_FW_CMD_BINARY_MSG_STRU*)(pstAtFwMsg->pMsgParam);
    pstNdisMsg      = (AT_NDIS_MSG_STRU*)pstBinaryInfo;

    switch (pstNdisMsg->ulMsgId)
    {
        case ID_AT_NDIS_PDNINFO_CFG_CNF:
            ulResult = AT_RcvNdisPdnInfoCfgCnf(&pstNdisMsg->unMsg.stNdisPdnInfoCfgCnf);
            break;

        case ID_AT_NDIS_PDNINFO_REL_CNF:
            ulResult = AT_RcvNdisPdnInfoRelCnf(&pstNdisMsg->unMsg.stNdisPdnInfoRelCnf);
            break;

        default:
            AT_WARN_LOG("AT_RcvNdisMsg: Unexpected MSG is received.");
            ulResult = VOS_ERR;
            break;
    }

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_RcvNdisMsg: Process message failed. <MsgId>",
                    (VOS_INT32)pstNdisMsg->ulMsgId);
    }

    return;
}
/* Added by A00165503 for AT Project, 2011-10-20, end */

/* Added by h44270 for V7R1 phase III, 2011-10-18, begin */
/*****************************************************************************
 �� �� ��  : AT_ProcRabmSetFastDormParaCnf
 ��������  : ������ϢID_RABM_AT_SET_FASTDORM_PARA_CNF
 �������  : pstMsg - ����RABM����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��19��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32    AT_ProcRabmSetFastDormParaCnf(
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_ProcRabmSetFastDormParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ������ý�� */
    gstAtSendData.usBufLen = 0;
    ulRslt = AT_ERROR;
    if (AT_RABM_PARA_SET_RSLT_SUCC == pstMsg->enRslt)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_ProcRabmQryFastDormParaCnf
 ��������  : ������ϢRABM_AT_QRY_FASTDORM_PARA_CNF_STRU
 �������  : pstMsg - ����RABM����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��19��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

 2.��    ��   : 2012��3��20��
   ��    ��   : l60609
   �޸�����   : B070 Project:ֱ�Ӷ�дNV�����ٵ��õ���ӿ�

*****************************************************************************/
VOS_UINT32    AT_ProcRabmQryFastDormParaCnf(
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    ulResult = AT_ERROR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* Added by l60609 for B070 Project, 2012/03/20, begin */
    if (VOS_TRUE == pstMsg->ucRslt)
    {
        /* �����ѯ��� */
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"^FASTDORM:%d",pstMsg->stFastDormPara.enFastDormOperationType);

        if (AT_RABM_FASTDORM_STOP_FD_ASCR != pstMsg->stFastDormPara.enFastDormOperationType)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",pstMsg->stFastDormPara.ulTimeLen);
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        ulResult = AT_OK;
        gstAtSendData.usBufLen = usLength;
    }
    /* Added by l60609 for B070 Project, 2012/03/20, end */

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/* Added by M00217266 for Optimize RIL, 2013-7-11, Begin */
/*****************************************************************************
 �� �� ��  : AT_ProcRabmReleaseRrcCnf
 ��������  : ���ٲ��rrc����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : M00217266
    �޸�����  : Optimize RIL:

*****************************************************************************/
VOS_UINT32 AT_ProcRabmReleaseRrcCnf(RABM_AT_RELEASE_RRC_CNF_STRU *pstMsg)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    ulRslt = AT_ERROR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmReleaseRrcCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ������ý�� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK == pstMsg->ulRslt)
    {
        ulRslt = AT_OK;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}
/* Added by M00217266 for Optimize RIL, 2013-7-11, End */

/*****************************************************************************
 �� �� ��  : AT_RabmMsgProc
 ��������  : ATģ�鴦������Rabm����Ϣ
 �������  : MSG_HEADER_STRU * pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��19��
   ��    ��   : h44270
   �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��11��
    ��    ��   : M00217266
    �޸�����  : Optimize RIL:

*****************************************************************************/
TAF_VOID AT_RabmMsgProc(
    MSG_HEADER_STRU                    *pstMsg
)
{
    switch(pstMsg->ulMsgName)
    {
        case ID_RABM_AT_SET_FASTDORM_PARA_CNF:
            AT_ProcRabmSetFastDormParaCnf((RABM_AT_SET_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_QRY_FASTDORM_PARA_CNF:
            AT_ProcRabmQryFastDormParaCnf((RABM_AT_QRY_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        /* Added by M00217266 for Optimize RIL, 2013-7-11, Begin */
        case ID_RABM_AT_SET_RELEASE_RRC_CNF:
            AT_ProcRabmReleaseRrcCnf((RABM_AT_RELEASE_RRC_CNF_STRU*)pstMsg);
            break;
        /* Added by M00217266 for Optimize RIL, 2013-7-11, End */
        default:
            AT_WARN_LOG("At_RabmMsgProc:WARNING:Wrong Msg!");
            break;
    }
}

/* Added by h44270 for V7R1 phase III, 2011-10-18, end */

/*****************************************************************************
 �� �� ��  : At_MsgProc
 ��������  : ATģ����Ϣ������ں���
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
  3.��    ��   : 2011��10��4��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ����AT AGENT�Ĵ���
  4.��    ��   : 2011��10��23��
    ��    ��   : A00165503
    �޸�����   : AT Project: NDIS��Ϣ����
  5.��    ��   : 2011��10��23��
    ��    ��   : f00179208
    �޸�����   : AT Project: ����VC��Ϣ����
  6.��    ��   : 2011��12��08��
    ��    ��   : f00179208
    �޸�����   : PS Project: ����RNIC��Ϣ����
  7.��    ��   : 2012��12��20��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II
*****************************************************************************/
TAF_VOID At_MsgProc(MsgBlock* pMsg)
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSliceStart;
    VOS_UINT32                          ulSliceEnd;
    VOS_UINT32                          ulType;

    ulSliceStart = VOS_GetSlice();
    ulSendPid    = pMsg->ulSenderPid;
    ulMsgName    = ((MSG_HEADER_STRU *)pMsg)->ulMsgName;

    /* ��ʱ���� */
    if ( VOS_PID_TIMER == pMsg->ulSenderPid )
    {
        At_TimeOutProc((REL_TIMER_MSG*)pMsg);
        ulSliceEnd = VOS_GetSlice();
        AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);

        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        case WUEPS_PID_AT:
            At_CmdMsgDistr((AT_MSG_STRU*)pMsg);
            ulSliceEnd = VOS_GetSlice();
            ulType     = ((AT_MSG_STRU*)pMsg)->ucType;
            ulMsgName  = (ulType<<16) | ulMsgName;
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
            At_EventMsgProc((MN_AT_IND_EVT_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            ulMsgName = ((MN_AT_IND_EVT_STRU *)pMsg)->usMsgName;
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case PS_PID_APP_PPP:
            At_PppMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case PS_PID_APP_NDIS:
            AT_RcvNdisMsg(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case DSP_PID_WPHY:
            At_HPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_DSP_PID_GPHY:
        case I1_DSP_PID_GPHY:
            At_GHPAMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_MMA:
        case I1_WUEPS_PID_MMA:
            At_MmaMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_DRV_AGENT:
        case I1_WUEPS_PID_DRV_AGENT:
            At_ProcMsgFromDrvAgent((DRV_AGENT_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_VC:
        case I1_WUEPS_PID_VC:
            At_ProcMsgFromVc((MN_AT_IND_EVT_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case ACPU_PID_RNIC:
            At_RcvRnicMsg(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_CC:
        case I1_WUEPS_PID_CC:
            At_ProcMsgFromCc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        /* Modify by z60575 for DTS2013070407286, 2013-7-5 begin */
        #if (FEATURE_ON == FEATURE_LTE)
        /* Modify by z60575 for DTS2013070407286, 2013-7-5 end */
        case MSP_L4_L4A_PID:
            at_L4aCnfProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case MSP_SYS_FTM_PID:
            At_FtmEventMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
        #endif

        case I0_MAPS_STK_PID:
        case I1_MAPS_STK_PID:
            At_STKMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_PB_PID:
        case I1_MAPS_PB_PID:
            At_PbMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_MAPS_PIH_PID:
        case I1_MAPS_PIH_PID:
            At_PIHMsgProc(pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        case I0_WUEPS_PID_RABM:
        case I1_WUEPS_PID_RABM:
            AT_RabmMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
/* Modified by z00214637 for TEMP PROTECT NAS project, 2013-04-17, begin */

        case WUEPS_PID_SPY:
            AT_SpyMsgProc((MSG_HEADER_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
/* Modified by z00214637 for TEMP PROTECT NAS project, 2013-04-17, end */

        case I0_UEPS_PID_MTA:
        case I1_UEPS_PID_MTA:
            At_ProcMtaMsg((AT_MTA_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;

        /* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, begin */
#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
            AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)pMsg);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
#endif
        /* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, end */

        default:
            AT_LOG1("At_MsgProc other PID msg",pMsg->ulSenderPid);
            ulSliceEnd = VOS_GetSlice();
            AT_RecordAtMsgInfo(ulSendPid, ulMsgName, ulSliceStart, ulSliceEnd);
            return;
    }
}

/* Added by f62575 for AT Project, 2011/10/22, begin */
/*****************************************************************************
 �� �� ��  : AT_EventReport
 ��������  : ��OM�ϱ�AT�¼�
 �������  : VOS_UINT32 ulPid                   ��Ҫ�ϱ��¼���ģ��ID
             NAS_OM_EVENT_ID_ENUM enEventId     ��Ҫ�ϱ����¼�ID
             VOS_VOID *pPara                    �¼��еĿ�ѡ����
             VOS_UINT32 ulLen                   ��ѡ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��22��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��08��
    ��    ��   : j00174725
    �޸�����   : TQE
*****************************************************************************/
VOS_VOID AT_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    PS_OM_EVENT_IND_STRU               *pstEvent;
    VOS_VOID                           *pData;

    pData = pPara;
    if ((VOS_NULL_PTR == pData) && (ulLen > 0))
    {
        /* �����ӡ */
        AT_WARN_LOG("AT_EventReport:pPara is NULL.");
        return;
    }

    if (4 < ulLen)
    {
        pstEvent = (PS_OM_EVENT_IND_STRU*)PS_MEM_ALLOC(ulPid,
                              ((sizeof(PS_OM_EVENT_IND_STRU)-4)+ulLen));
    }
    else
    {
        pstEvent = (PS_OM_EVENT_IND_STRU*)PS_MEM_ALLOC(ulPid,
                              sizeof(PS_OM_EVENT_IND_STRU));
    }
    if (VOS_NULL_PTR == pstEvent)
    {
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "AT_EventReport:Alloc mem fail.");
        return;
    }
    PS_MEM_SET(pstEvent->aucData, 0x0, ((ulLen>4)?ulLen:4));

    /* ulLength ָ��usEventId��ʼ����β�ĳ��� */
    pstEvent->ulLength        = 8 + ulLen;
    pstEvent->usEventId       = enEventId;
    pstEvent->usReserved      = 0x0;
    pstEvent->ulModuleId      = ulPid;
    /* ulLen>0ʱ��ͨ����������pPara������Ϊ��ָ�� */
    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pstEvent->aucData, pData, pstEvent->ulLength-8);
    }

    /* Modified by j00174725 for TQE, 2013-10-08, begin */
#ifdef DMT
    if (VOS_OK != OM_Event(pstEvent))
#else
    if (VOS_OK != OM_AcpuEvent(pstEvent))
#endif
    {
        AT_WARN_LOG("AT_EventReport:OM_AcpuEvent Fail.");
    }
    /* Modified by j00174725 for TQE, 2013-10-08, end */

    PS_MEM_FREE(ulPid, pstEvent);

    return;
}

/* Added by f62575 for AT Project, 2011/10/22, end */

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetAdcRsp
 ��������  : ^ADC�Ĳ�ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��5��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��1��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011112602473������Զ�Ӧ��������±�����������
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_ADC_SET_CNF_STRU                *pstAdcCnf;
    VOS_UINT8                                  ucIndex;
    VOS_UINT32                                 ulResult;

    /* ��ʼ����Ϣ */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAdcCnf       = (DRV_AGENT_ADC_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAdcCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_ADC_SET */
    if (AT_CMD_ADC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*��������ֵ�Ƿ�ɹ� */
    if (VOS_TRUE != pstAdcCnf->bFail)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ����AT_FormATResultDATa���������� */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentQryTbatRsp
 ��������  : ^TBAT�Ĳ�ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��13��
    ��    ��   : w00181244
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBAT_QRY_CNF_STRU        *stTbatTypeCnf;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg                = (DRV_AGENT_MSG_STRU *)pMsg;
    stTbatTypeCnf          = (DRV_AGENT_TBAT_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stTbatTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /*�Զ�Ӧ��������±�����������*/
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_TBAT_QRY */
    if (AT_CMD_TBAT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stTbatTypeCnf->ulTbatType);

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : AT_RcvSimLockQryRsp
 ��������  : ^SIMLOCK=2��ѯSIMLOCK״̬�Ļظ�������
     VOS_UINT8                           ucIndex,
     VOS_UINT8                           OpId,
     VOS_VOID                           *pPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��03��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��2��21��
    ��    ��   : w00167002
    �޸�����   : ������������ֵΪVOS_UINT32
*****************************************************************************/
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, begin */
VOS_UINT32 AT_RcvSimLockQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_MMA_SIMLOCK_STATUS_STRU         *pstEvent;

    pstEvent = (AT_MMA_SIMLOCK_STATUS_STRU *)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvSimLockQryRsp: AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKSTATUS_READ��AT_CMD_CSDFLT_READ */
    if ((AT_CMD_SIMLOCKSTATUS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
     && (AT_CMD_CSDFLT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    if (AT_CMD_SIMLOCKSTATUS_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        "SIMLOCK",
                                                        pstEvent->bSimlockEnableFlg);
        ulRet                  = AT_OK;

    }
    else
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        ulRet                  = AT_OutputCsdfltDefault(ucIndex, pstEvent->bSimlockEnableFlg);
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, end */

/* Added by f62575 for B050 Project, 2012-2-3, end   */

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 �� �� ��  : WuepsATFidInit
 ��������  : AT FID��ʼ��������ST���ԣ�
 �������  : VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���/PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 WuepsATFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRslt = VOS_OK;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
        /* Added by L60609 for AT Project��2011-10-20,  Begin*/
        #if (VOS_WIN32 == VOS_OS_VER)
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AT,
                                           (Init_Fun_Type)At_PidInit,
                                           (Msg_Fun_Type)At_MsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
        #endif
            /* Added by L60609 for AT Project��2011-10-20,  Begin*/

            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_AT, VOS_PRIORITY_P6);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        default:
            break;
    }

    return VOS_OK;
}
#endif
#endif

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetSpwordRsp
 ��������  : ����DRV_AGENT_SPWORD_SET_CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_SPWORD_SET_CNF_STRU             *pstSpwordSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstSpwordSetCnf = (DRV_AGENT_SPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSpwordSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SPWORD_SET */
    if (AT_CMD_SPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ����У��ͨ�������������Ҫ���� */
    if (VOS_OK == pstSpwordSetCnf->ulResult)
    {
        g_stSpWordCtx.ucShellPwdCheckFlag = VOS_TRUE;
        g_stSpWordCtx.ucErrTimes          = 0;

        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_OK);
    }
    /* ����У��ʧ�ܣ����������1 */
    else
    {
        g_stSpWordCtx.ucErrTimes++;

        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

#endif
/* Added by l00198894 for B050 Project, 2012/02/02, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMmaCipherInfoQueryCnf
 ��������  : AT_MMA_CIPHER_INFO_QUERY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��02��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg)
{
    MN_MMA_CIPHER_QRY_CNF_STRU         *pstCipherQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstCipherQryCnf     = (MN_MMA_CIPHER_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCipherQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_CIPERQRY_READ */
    if (AT_CMD_CIPERQRY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CIPERQRY��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstCipherQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   pstCipherQryCnf->ucCipherInfo);
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaLocInfoQueryCnf
 ��������  : AT_MMA_LOCATION_INFO_QUERY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��02��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg)
{
    MN_MMA_LOCATION_INFO_CNF_STRU      *pstLocInfoCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstLocInfoCnf       = (MN_MMA_LOCATION_INFO_CNF_STRU *)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstLocInfoCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_LOCINFO_READ */
    if (AT_CMD_LOCINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CIPERQRY��ѯ����� */
    if (VOS_OK != pstLocInfoCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* �ϱ�MCC��MNC */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f00) >> 8,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f0000) >> 16);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f00) >> 8);

        /* MNC���һλ������F����MNCΪ��λ������Ϊ��λ */
        if (0x0f != ((pstLocInfoCnf->ulMnc & 0x0f0000) >> 16))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f0000) >> 16);
        }

        /* Lac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->usLac);

        /* Rac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ucRac);

        /* Cell ID */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ulCellid);

        gstAtSendData.usBufLen = usLength;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by l00198894 for B050 Project, 2012/02/02, end */

/* Added by l00198894 for C50_IPC Project, 2012/02/16, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentNvBackupStatQryRsp
 ��������  : AT^NVBACKUPSTAT�Ĳ�ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NVBACKUPSTAT_READ */
    if ( AT_CMD_NVBACKUPSTAT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        if ( NV_OK == pstEvent->ulNvBackupStat )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_TRUE);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_FALSE);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentNandBadBlockQryRsp
 ��������  : AT^NANDBBC�Ĳ�ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDBBC_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              uli;
    VOS_UINT32                              ulMaxBBNum;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDBBC_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;
    uli             = 0;
    ulMaxBBNum      = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NANDBBC_READ */
    if ( AT_CMD_NANDBBC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->ulBadBlockNum);

        ulMaxBBNum = (pstEvent->ulBadBlockNum > DRV_AGENT_NAND_BADBLOCK_MAX_NUM) ? DRV_AGENT_NAND_BADBLOCK_MAX_NUM : pstEvent->ulBadBlockNum;
        for (uli = 0; uli < ulMaxBBNum; uli++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s: %d",
                                               gaucAtCrLf,
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstEvent->aulBadBlockIndex[uli]);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentNandDevInfoQryRsp
 ��������  : AT^NANDVER�Ĳ�ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDVER_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDVER_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NANDVER_READ */
    if ( AT_CMD_NANDVER_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* �����ѯ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,\"%s\",%d,\"%s\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->stNandDevInfo.ulMufId,
                                           pstEvent->stNandDevInfo.aucMufName,
                                           pstEvent->stNandDevInfo.ulDevId,
                                           pstEvent->stNandDevInfo.aucDevSpec);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentChipTempQryRsp
 ��������  : AT^CHIPTEMP�Ĳ�ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_CHIPTEMP_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_CHIPTEMP_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CHIPTEMP_READ */
    if ( AT_CMD_CHIPTEMP_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* �����ѯ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,%d,%d,%d,%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->lGpaTemp,
                                           pstEvent->lWpaTemp,
                                           pstEvent->lLpaTemp,
                                           pstEvent->lSimTemp,
                                           pstEvent->lBatTemp);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/* Added by l00198894 for C50_IPC Project, 2012/02/16, end */

/* Added by l00171473 for DTS2012041805606, 2012-4-24, begin */

#ifndef __PS_WIN32_RECUR__
/*****************************************************************************
 �� �� ��  : AT_RcvMmaOmMaintainInfoInd
 ��������  : ��������MMA��PC���߿�ν�ɲ�������Ϣ
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��24��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/

/* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, begin */
VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
)
{
    ATMMA_OM_MAINTAIN_INFO_IND_STRU    *pstOmMaintainInfo;

    pstOmMaintainInfo = (ATMMA_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    if ( (VOS_TRUE == pstOmMaintainInfo->ucOmConnectFlg)
      && (VOS_TRUE == pstOmMaintainInfo->ucOmPcRecurEnableFlg) )
    {
        AT_MNTN_TraceContextData();
        AT_MNTN_TraceClientData();
    }

    return VOS_OK;
}
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, end */
#endif
/* Added by l00171473 for DTS2012041805606, 2012-4-24, end */

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentAntStateIndRsp
 ��������  : ^ANTSTATE ��ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 �޸���ʷ      :
  1.��    ��   : 2012��2��25��
    ��    ��   : w00184875
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��25��
    ��    ��   : l00227485
    �޸�����   : DSDA PhaseII
  3.��    ��   : 2013��5��30��
    ��    ��   : z60575
    �޸�����   :DTS2013060307614, DSDA_SAR�޸�
  4.��    ��   : 2013��8��2��
    ��    ��   : z60575
    �޸�����   :DTS2013073103769,��C�˲�ѯ����״̬
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT16                          usLength = 0;
    /* Modified by l00227485 for DSDA PhaseII, 2012-12-25, begin */
    DRV_AGENT_ANT_STATE_IND_STRU       *pstAntState = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    gstAtSendData.usBufLen  = 0;
    pRcvMsg                 = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAntState             = (DRV_AGENT_ANT_STATE_IND_STRU *)pRcvMsg->aucContent;
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstAntState->stAtAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntStateIndRsp: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       "%s:%d%s",
                                       "^ANTSTATE",
                                       pstAntState->usAntState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    /* Modified by l00227485 for DSDA PhaseII, 2012-12-25, end */

    /* Deleted by z60575 for DTS2013073103769, 2013-8-2, begin */
    /* Deleted by z60575 for DTS2013073103769, 2013-8-2, end */

    return VOS_OK;
}
/* Added by f00179208 for DTS2012031403331, 2012-03-19, Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetMaxLockTmsRsp
 ��������  : DRV_AGENT_MAX_LOCK_TIMES_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU       *pstMaxlockTmsSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstMaxlockTmsSetCnf = (DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMaxlockTmsSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_MAXLCKTMS_SET */
    if (AT_CMD_MAXLCKTMS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^MAXLCKTMS��������� */
    if (VOS_OK != pstMaxlockTmsSetCnf->ulResult)
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_DEVICE_OTHER_ERROR);
    }
    else
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}
/* Added by f00179208 for DTS2012031403331, 2012-03-19, Begin */

/* Added by f00179208 for DTS2012060804905, 2012-06-18 Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSetApSimstRsp
 ��������  : DRV_AGENT_AT_DEACT_SIM_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��18��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSetApSimstRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_AP_SIMST_SET_CNF_STRU           *pstApSimStSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstApSimStSetCnf    = (DRV_AGENT_AP_SIMST_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstApSimStSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_APSIMST_SET */
    if (AT_CMD_APSIMST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^APSIMST��������� */
    if (VOS_OK != pstApSimStSetCnf->ulResult)
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}
/* Added by f00179208 for DTS2012060804905, 2012-06-18 End */


/* Added by l00198894 for AP-Modem Personalisation Project, 2012/04/10, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentHukSetCnf
 ��������  : ^HUK�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_HUK_SET_CNF_STRU             *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_HUK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_HUK_SET */
    if (AT_CMD_HUK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if (DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult)
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentFacAuthPubkeySetCnf
 ��������  : ^FACAUTHPUBKEY�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_FACAUTHPUBKEY_SET */
    if ( AT_CMD_FACAUTHPUBKEY_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentIdentifyStartSetCnf
 ��������  : ^IDENTIFYSTART�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              i;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_IDENTIFYSTART_SET */
    if ( AT_CMD_IDENTIFYSTART_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucRsaText[i]);
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentIdentifyEndSetCnf
 ��������  : ^IDENTIFYEND�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYEND_SET_CNF_STRU     *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYEND_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_IDENTIFYEND_SET */
    if ( AT_CMD_IDENTIFYEND_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSimlockDataWriteSetCnf
 ��������  : ^SIMLOCKDATAWRITE�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKDATAWRITE_SET */
    if ( AT_CMD_SIMLOCKDATAWRITE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_Num2AsciiNum
 ��������  : ʮ���ƻ�ʮ����������תASCII��
 �������  : VOS_UINT8          ucNum           -- ��ת������
 �������  : ��
 �� �� ֵ  : VOS_CHAR       -- ת�����ASCII�룬ʧ�ܷ���'*'
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��28��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_CHAR AT_Num2AsciiNum(VOS_UINT8 ucNum)
{
    if (9 >= ucNum)
    {
        return (VOS_CHAR)('0' + ucNum);
    }
    else if (0x0F >= ucNum)
    {
        return (VOS_CHAR)('A' + (ucNum - 0x0A));
    }
    else
    {
        return '*';
    }
}

/*****************************************************************************
 �� �� ��  : AT_CheckSimlockCodeLast2Char
 ��������  : ����������������ַ��������λ�ĺϷ���
 �������  : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory
 �������  : VOS_CHAR          *pcStrLast2Char        -- �������������ַ�
 �� �� ֵ  : VOS_OK     -- ���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��14��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_CheckSimlockCodeLast2Char(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrLast2Char
)
{
    VOS_UINT8                           i           = 0;

    /* ��������λ����Ч��, NET������ */
    if (DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK < enCategory)
    {
        for (i = 0; i < 2; i++)
        {
            /* NETSUB֧�ַ�Χ: 0x00~0x99 */
            if ( ('0' <= pcStrLast2Char[i]) && ('9' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            /* SP֧�ַ�Χ: 0x00~0xFF */
            else if ( (DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == enCategory)
                   && ('A' <= pcStrLast2Char[i]) && ('F' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            else
            {
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : AT_CheckSimlockCodeStr
 ��������  : ����������������ַ����Ϸ��ԣ��������ַ���������
 �������  : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory
 �������  : VOS_CHAR          *pcStrCode       -- ������ַ���
 �� �� ֵ  : VOS_OK     -- ���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��14��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_CheckSimlockCodeStr(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrCode
)
{
    VOS_UINT8                           i           = 0;
    VOS_UINT8                           j           = 0;
    VOS_UINT8                           ucLen;              /* �������볤�� */
    VOS_CHAR                           *pcTmpStr;

    pcTmpStr    = pcStrCode;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucLen = AT_PERSONALIZATION_NET_CODE_LEN;
            break;
        default:
            ucLen = AT_PERSONALIZATION_CODE_LEN;
            break;
    }

    /* ���PLMN�Ϸ��Լ���λ�� */
    for (i = 0; i < AT_PERSONALIZATION_NET_CODE_LEN; i++)
    {
        if ( ('0' <= pcTmpStr[i]) && ('9' >= pcTmpStr[i]) )
        {
            continue;
        }
        else if ( ((AT_PERSONALIZATION_NET_CODE_LEN - 1) == i)
               && ('F' == pcTmpStr[i]) )
        {
            for (j = i + 1; j < ucLen; j++)
            {
                pcTmpStr[j - 1] = pcTmpStr[j];
            }
            ucLen = ucLen - 1;
            break;
        }
        else
        {
            return VOS_ERR;
        }
    }

    pcTmpStr[ucLen] = 0;

    /* ��������������������λ�ĺϷ��� */
    if (VOS_OK != AT_CheckSimlockCodeLast2Char(enCategory, &pcTmpStr[ucLen - 2]))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SimlockCodeBcd2Str
 ��������  : ���������Ŷ�BCD��ת�ַ���
 �������  : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory
             VOS_UINT8         *pucBcdNum       -- ��ת���Ŷ�BCD��
 �������  : VOS_CHAR          *pcStrNum        -- ת������ַ���
 �� �� ֵ  : VOS_OK     -- ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_SimlockCodeBcd2Str(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_UINT8                                      *pucBcdNum,
    VOS_CHAR                                       *pcStrNum
)
{
    VOS_UINT8                           i               = 0;
    VOS_UINT8                           ucDecodeLen;
    VOS_UINT8                           ucFirstNum;
    VOS_UINT8                           ucSecondNum;
    VOS_CHAR                           *pcStrTmp        = pcStrNum;
    VOS_CHAR                            cTmpChar;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucDecodeLen = AT_PERSONALIZATION_NET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
            ucDecodeLen = AT_PERSONALIZATION_SUBNET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
            ucDecodeLen = AT_PERSONALIZATION_SP_CODE_BCD_LEN;
            break;
        default:
            return VOS_ERR;
    }

    /* ����������������иߵ��ֽ�ת�� */
    for (i = 0; i < ucDecodeLen; i++)
    {
        /* �ֱ�ȡ���ߵ��ֽ� */
        ucFirstNum  = (VOS_UINT8)((*(pucBcdNum + i)) & 0x0F);
        ucSecondNum = (VOS_UINT8)(((*(pucBcdNum + i)) >> 4) & 0x0F);

        *pcStrTmp++ = AT_Num2AsciiNum(ucFirstNum);
        *pcStrTmp++ = AT_Num2AsciiNum(ucSecondNum);
    }

    /* ������λ������Ƶ�����λ(����߶Խ�) */
    pcStrTmp        = &pcStrNum[AT_PERSONALIZATION_CODE_FOURTH_CHAR_INDEX];
    cTmpChar        = pcStrTmp[0];
    pcStrTmp[0]     = pcStrTmp[1];
    pcStrTmp[1]     = pcStrTmp[2];
    pcStrTmp[2]     = cTmpChar;

    /* �Ըߵ��ֽ�ת�������������������кϷ��Լ�� */
    if (VOS_OK != AT_CheckSimlockCodeStr(enCategory, pcStrNum))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_PhoneSimlockInfoPrint
 ��������  : ����������Ϣ��ӡ����
 �������  : DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstPhoneSimlockInfo
             VOS_UINT8                                   ucIndex
             VOS_UINT16                                 *pusLength
 �������  : ��
 �� �� ֵ  : VOS_UINT16     -- ��ӡ�ַ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������
  2.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE����AT_PhoneSimlockInfoPrint�ڶ�������
                 �����ݽṹ��Ϊ���ݽṹָ��
*****************************************************************************/
VOS_UINT32 AT_PhoneSimlockInfoPrint(
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstPhoneSimlockInfo,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;
    VOS_UINT8                                   ucGroupIndex    = 0;
    VOS_CHAR                                    acCodeBegin[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_CHAR                                    acCodeEnd[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_UINT32                                  ucCodeBeginRslt;
    VOS_UINT32                                  ucCodeEndRslt;

    PS_MEM_SET(acCodeBegin,    0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    PS_MEM_SET(acCodeEnd,      0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    ucCodeBeginRslt = VOS_NULL;
    ucCodeEndRslt   = VOS_NULL;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^PHONESIMLOCKINFO: <cat>,<indicator> [,(<code_begin>,<code_end>)...] */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch (pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator)
        {
            for (ucGroupIndex = 0; ucGroupIndex < pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].ucGroupNum; ucGroupIndex++)
            {
                ucCodeBeginRslt = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeBegin,
                                                        acCodeBegin);
                ucCodeEndRslt   = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeEnd,
                                                        acCodeEnd);
                if ( (VOS_OK == ucCodeBeginRslt)
                  && (VOS_OK == ucCodeEndRslt) )
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                       ",(%s,%s)",
                                                       acCodeBegin,
                                                       acCodeEnd);
                }
                else
                {
                    return VOS_ERR;
                }
            }
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentPhoneSimlockInfoQryCnf
 ��������  : ^PHONESIMLOCKINFO�����ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������
  2.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE����AT_PhoneSimlockInfoPrint�ڶ�������
                 �����ݽṹ��Ϊ���ݽṹָ��
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHONESIMLOCKINFO_READ */
    if ( AT_CMD_PHONESIMLOCKINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
        /* ��ӡ��� */
        /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, begin*/
        if (VOS_OK != AT_PhoneSimlockInfoPrint(pstEvent, ucIndex, &usLength))
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }   /*modified by Y00213812 for DTS2012082204471 TQE����, 2012-08-10, end*/
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SimlockDataReadPrint
 ��������  : ����������ȫ���ݴ�ӡ����
 �������  : DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU     stSimlockDataRead
             VOS_UINT8                                  ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT16  *pusLength   -- ��ӡ�ַ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_SimlockDataReadPrint(
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU      stSimlockDataRead,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^SIMLOCKDATAREAD: <cat>,<indicator>,<lock_status>,<max_times>,<remain_times> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch(stSimlockDataRead.astCategoryData[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator)
        {
            switch (stSimlockDataRead.astCategoryData[ucCatIndex].enStatus)
            {
            case DRV_AGENT_PERSONALIZATION_STATUS_READY:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",READY,,");
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PIN:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PIN,%d,%d",
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucMaxUnlockTimes,
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucRemainUnlockTimes);
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PUK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PUK,,");
                break;
            default:
                return VOS_ERR;
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",,,");
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentSimlockDataReadQryCnf
 ��������  : ^SIMLOCKDATAREAD�����ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU     *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKDATAREAD_READ */
    if ( AT_CMD_SIMLOCKDATAREAD_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
        /* ��ӡ��� */
        if (VOS_OK != AT_SimlockDataReadPrint(*pstEvent, ucIndex, &usLength))
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentPhonePhynumSetCnf
 ��������  : ^SIMLOCKINFO�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHONEPHYNUM_SET */
    if ( AT_CMD_PHONEPHYNUM_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentPhonePhynumQryCnf
 ��������  : ^PHONEPHYNUM�����ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHONEPHYNUM_READ */
    if ( AT_CMD_PHONEPHYNUM_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
        /* ��ʽ�������ѯ��� */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: IMEI,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucImeiRsa[i]);
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s%s: SN,",
                                           gaucAtCrLf,
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucSnRsa[i]);
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_PortCtrlTmpSndMsg
 ��������  : ����У��ͨ��֮����OM��HSIC����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_OK  ���û��ѯ�����ɹ�
             VOS_ERR ���û��ѯ����ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : y00213812
    �޸�����   : AP-Modem����������Ŀ��������

 *****************************************************************************/
VOS_UINT32  AT_PortCtrlTmpSndMsg(VOS_VOID)
{
    OM_HSIC_CONNECT_MSG_STRU           *pstMsg;

    pstMsg = (OM_HSIC_CONNECT_MSG_STRU*)PS_ALLOC_MSG(WUEPS_PID_AT,
                                                     sizeof(OM_HSIC_CONNECT_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return AT_ERROR;
    }

    pstMsg->ulReceiverPid  = ACPU_PID_OM;
    pstMsg->ulMsgName      = AT_OM_HSIC_PORT_CONNECT;

    if (VOS_OK !=  PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentPortctrlTmpSetCnf
 ��������  : ^PORTCTRLTMP�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PORTCTRLTMP_SET */
    if ( AT_CMD_PORTCTRLTMP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ��OM����Ϣ��OM�˿� */
        ulResult    = AT_PortCtrlTmpSndMsg();
        if ( AT_OK != ulResult)
        {
             ulResult    = AT_ERROR;
        }
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult         = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentPortAttribSetCnf
 ��������  : ^PORTATTRIBSET�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *pstEvent;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PORTATTRIBSET_SET */
    if ( AT_CMD_PORTATTRIBSET_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentPortAttribSetQryCnf
 ��������  : ^PORTATTRIBSET�����ѯ�ظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                                     *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU                   *pstEvent;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PORTATTRIBSET_READ */
    if ( AT_CMD_PORTATTRIBSET_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        if( (DRV_AGENT_PORT_STATUS_OFF  == pstEvent->enPortStatus)
         || (DRV_AGENT_PORT_STATUS_ON   == pstEvent->enPortStatus))
        {
            ulResult = AT_OK;
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstEvent->enPortStatus);
        }
        else
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by y00213812 for AP-Modem Personalisation Project, 2012/04/18, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentOpwordSetCnf
 ��������  : ^OPWORD�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��18��
    ��    ��   : y00213812
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                      *pRcvMsg;
    DRV_AGENT_OPWORD_SET_CNF_STRU           *pstEvent;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_OPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_OPWORD_SET */
    if ( AT_CMD_OPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ����ȶԳɹ�����ȡȨ�� */
        g_enATE5RightFlag   = AT_E5_RIGHT_FLAG_YES;
        ulResult            = AT_OK;
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by y00213812 for AP-Modem Personalisation Project, 2012/04/18, end */

/* Added by y00258578 for ANT SWITCH, 2013-11-11 Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentAntSwitchSetCnf
 ��������  : ��ӦANTSWITCH���ô�����
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��1��
    ��    ��   : y00258578
    �޸�����   : �¼Ӻ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentAntSwitchSetCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_SET_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_SET_CNF_STRU *)pRcvMsg->aucContent;
    /* ����ClientID��ȡͨ������ */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ATģ���ڵȴ�^ANTSWITCH����Ĳ�������¼��ϱ� */
    if (AT_CMD_ANTSWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Error Option!");
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK != pstAntSwitchCnf->ulResult)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}
/* Added by y00258578 for ANT SWITCH, 2013-11-11 End */

/* Added by y00258578 for ANT SWITCH, 2013-11-11 Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvDrvAgentAntSwitchQryCnf
 ��������  : ��ӦANTSWITCH��ѯ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��1��
    ��    ��   : y00258578
    �޸�����   : �¼Ӻ���
*****************************************************************************/
VOS_UINT32 AT_RcvDrvAgentAntSwitchQryCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_QRY_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ����ClientID��ȡͨ������ */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ATģ���ڵȴ�^ANTSWITCH����Ĳ�������¼��ϱ� */
    if (AT_CMD_ANTSWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Error Option!");
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;

    if(pstAntSwitchCnf->ulResult == VOS_OK)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstAntSwitchCnf->ulState);

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}
/* Added by y00258578 for ANT SWITCH, 2013-11-11 End */


/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaCposSetCnf
 ��������  : +CPOS�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                  *pstCposMsg;
    MTA_AT_CPOS_CNF_STRU             *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ��ʼ����Ϣ���� */
    pstCposMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOS_CNF_STRU*)pstCposMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCposMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CPOS_SET */
    if ( AT_CMD_CPOS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:Not AT_CMD_CPOS_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult            = AT_OK;
    }
    else
    {
        ulResult            = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormatResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaCposrInd
 ��������  : +CPOSR�����ϱ��������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstCposrMsg;
    MTA_AT_CPOSR_IND_STRU              *pstEvent;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ��ʼ����Ϣ���� */
    pstCposrMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOSR_IND_STRU*)pstCposrMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCposrMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposrInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ���ݵ�ǰ��AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enCposrReport��ֵ�ж��Ƿ����������ϱ��������ݺ�ָʾ */
    if (AT_CPOSR_ENABLE == pstAgpsCtx->enCposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s+CPOSR: %s%s",
                                                        gaucAtCrLf, pstEvent->acXmlText, gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaXcposrRptInd
 ��������  : ^XCPOSRRPT�����ϱ��������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstXcposrRptMsg;
    MTA_AT_XCPOSRRPT_IND_STRU          *pstEvent;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ��ʼ����Ϣ���� */
    pstXcposrRptMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent        = (MTA_AT_XCPOSRRPT_IND_STRU*)pstXcposrRptMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstXcposrRptMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXcposrRptInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ���ݵ�ǰ��AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enXcposrReport��ֵ�ж��Ƿ������ϱ������������ */
    if (AT_XCPOSR_ENABLE == pstAgpsCtx->enXcposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "^XCPOSRRPT: %d",
                                                        pstEvent->ulClearFlg);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaCgpsClockSetCnf
 ��������  : ^CGPSCLOCK�������ûظ�������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                  *pRcvMsg;
    MTA_AT_CGPSCLOCK_CNF_STRU        *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;
    /* ��ʼ����Ϣ���� */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_CGPSCLOCK_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CGPSCLOCK_SET */
    if ( AT_CMD_CGPSCLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:Not AT_CMD_CGPSCLOCK_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : At_ProcMtaMsg
 ��������  : ��������MTAģ�����Ϣ
 �������  : MTA_MSG_STRU *pMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*��g_astAtProcMsgFromMtaTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMtaTab)/sizeof(AT_PROC_MSG_FROM_MTA_STRU);

    /*����Ϣ���л�ȡMSG ID*/
    ulMsgId  = ((AT_MTA_MSG_STRU *)pstMsg)->ulMsgId;

    /*g_astAtProcMsgFromMtaTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMtaTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromMtaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMtaMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMtaMsg: Msg Id is invalid!");
    }

    return;
}
/* Added by y00213812 for V7R1C50 A-GPS Project, 2012/06/28, end */

/* Added by l00198894 for V7R1C50 ISDB Project, 2012/08/28, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaApSecSetCnf
 ��������  : ATģ���յ�MTAģ����Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��31��
    ��    ��   : ���Ͻ�/00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaApSecSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_APSEC_CNF_STRU              *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_APSEC_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_APSEC_SET */
    if (AT_CMD_APSEC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* ������ý�� */
        ulResult    = AT_OK;

        /* ����ɹ��������ȫ�������ӡ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (ulLoop = 0; ulLoop < pstEvent->ulSPLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstEvent->aucSecPacket[ulLoop]);
        }
    }
    else
    {
        /* �쳣���, ���ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by l00198894 for V7R1C50 ISDB Project, 2012/08/28, end */

/* Added by l00198894 for STK&DCM Project, 2012/09/18, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaSimlockUnlockSetCnf
 ��������  : ATģ���յ�MTAģ����Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��19��
    ��    ��   : ���Ͻ�/00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaSimlockUnlockSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU      *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_SIMLOCKUNLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKUNLOCK_SET */
    if (AT_CMD_SIMLOCKUNLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* �����ɹ������OK */
        ulResult    = AT_OK;
    }
    else
    {
        /* ����ʧ�ܣ����ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by l00198894 for STK&DCM Project, 2012/09/18, end */

/* Modified by z00161729 for cerssi and cnmr, 2012-11-21, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaQryNmrCnf
 ��������  : ATģ���յ�ID_MTA_AT_QRY_NMR_CNFģ����Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryNmrCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pRcvMsg      = VOS_NULL_PTR;
    MTA_AT_QRY_NMR_CNF_STRU            *pstQryNmrCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulNmrDataIndex;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pRcvMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstQryNmrCnf = (MTA_AT_QRY_NMR_CNF_STRU *)(pRcvMsg->aucContent);

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CNMR_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if (MTA_AT_RESULT_ERROR == pstQryNmrCnf->enResult)
    {
        /* ��ѯʧ��ֱ���ϱ�error */
        gstAtSendData.usBufLen = 0;

        /* ��λAT״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ������ */
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    usLength = 0;

    /* ��AT^CNMR��ѯ����ؽ�����㷵�ص�����������ʾ�ϱ� */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (0 == pstQryNmrCnf->ucTotalIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d,%d",
                                           0,
                                           0);

        gstAtSendData.usBufLen = usLength;

        /* ��λAT״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ������ */
        At_FormatResultData(ucIndex, AT_OK);
        return VOS_OK;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,",
                                       pstQryNmrCnf->ucTotalIndex,
                                       pstQryNmrCnf->ucCurrIndex);

    for (ulNmrDataIndex = 0; ulNmrDataIndex < pstQryNmrCnf->usNMRLen; ulNmrDataIndex++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%02x",
                                           pstQryNmrCnf->aucNMRData[ulNmrDataIndex]);
    }

    if (pstQryNmrCnf->ucTotalIndex != pstQryNmrCnf->ucCurrIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

         At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }


    if (pstQryNmrCnf->ucTotalIndex == pstQryNmrCnf->ucCurrIndex)
    {
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        gstAtSendData.usBufLen = 0;

        /* ��λAT״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ������ */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}
/* Modified by z00161729 for cerssi and cnmr, 2012-11-21, end */

/* Added by m00217266 for DSDA GUNAS C CORE, 2012-12-26, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrAutotestQryCnf
 ��������  : ִ��^CWAS���յ�MTA�Ļظ������
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrAutotestQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU   *pstWrrAutotestCnf   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrAutotestCnf   = (MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CWAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : Current Option is not AT_CMD_CWAS_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CWAS����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrAutotestCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum > 0)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d",
                                                             pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[0]);

            for (i = 1; i < pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum; i++)
            {
                gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                                 ",%d",
                                                                 pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[i]);
            }
        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrCellinfoQryCnf
 ��������  : ִ��^CELLINFO���յ�MTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrCellinfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg              = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU   *pstWrrCellinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellinfoQryCnf    = (MTA_AT_WRR_CELLINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CELLINFO_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : Current Option is not AT_CMD_CELLINFO_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CELLINFO����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellinfoQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /*û�л�ȡ��С����Ϣ����ӡ0*/
        if ( 0 == pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum )
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                               "no cellinfo rslt");
        }

        for (i = 0; i< pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d,%d,%d,%d\r\n",
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usCellFreq,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usPrimaryScramCode,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichRscp,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichEcN0);
        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrMeanrptQryCnf
 ��������  : at�·�^CELLINFO������յ�MTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrMeanrptQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU    *pstWrrMeanrptQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;
    VOS_UINT32                          ulCellNumLoop;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrMeanrptQryCnf     = (MTA_AT_WRR_MEANRPT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    usLength                = 0;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_MEANRPT_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : Current Option is not AT_CMD_MEANRPT_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^MEANRPT����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrMeanrptQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                           "%d",
                                           pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum);

        for ( i = 0 ; i < pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum; i++ )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "\r\n0x%X,%d",
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usEventId,
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum );
            for ( ulCellNumLoop = 0; ulCellNumLoop < pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum; ulCellNumLoop++ )
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].ausPrimaryScramCode[ulCellNumLoop]);
            }

        }
        gstAtSendData.usBufLen = usLength;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrCellSrhSetCnf
 ��������  : ͨ��at����^CELLSRCH���ú��յ�mTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrCellSrhSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU    *pstWrrCellSrhSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhSetCnf = (MTA_AT_WRR_CELLSRH_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_WAS_MNTN_SET_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : Current Option is not AT_CMD_WAS_MNTN_SET_CELLSRH.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CELLSRH����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrCellSrhQryCnf
 ��������  : ͨ��AT����^CELLSRCH��ѯ���յ�mTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrCellSrhQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU    *pstWrrCellSrhQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhQryCnf = (MTA_AT_WRR_CELLSRH_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_WAS_MNTN_QRY_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : Current Option is not AT_CMD_WAS_MNTN_QRY_CELLSRH.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrCellSrhQryCnf->ucCellSearchType);

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrFreqLockSetCnf
 ��������  : ͨ��at����^FREQLOCK������Ƶ��Ϣ���յ�MTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrFreqLockSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : Current Option is not AT_CMD_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrFreqLockQryCnf
 ��������  : ͨ��at����^FREQLOCK��ѯ��Ƶ��Ϣ���յ�MTAde�ظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrFreqLockQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_FREQLOCK_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : Current Option is not AT_CMD_FREQLOCK_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (VOS_FALSE == pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable)
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable);
        }
        else
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.usLockedFreq);
        }

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrRrcVersionSetCnf
 ��������  : ͨ��at����^HSPA����RRC VERSION��Ϣ���յ�MTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrRrcVersionSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    *pstWrrVersionSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionSetCnf     = (MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_RRC_VERSION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : Current Option is not AT_CMD_RRC_VERSION_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionSetCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* ���óɹ������¶�дһ��NV */
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
        AT_ReadWasCapabilityNV();
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : AT_RcvMtaWrrRrcVersionQryCnf
 ��������  : ͨ��at����^HSPA��ѯRRC VERSION��Ϣ���յ�MTA�Ļظ�
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��30��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaWrrRrcVersionQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    *pstWrrVersionQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionQryCnf = (MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_RRC_VERSION_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrVersionQryCnf->ucRrcVersion);

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by m00217266 for DSDA GUNAS C CORE, 2012-12-26, end */

/* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMmaAcInfoQueryCnf
 ��������  : AT_MMA_AC_INFO_QUERY_CNF��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaAcInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_AC_INFO_QUERY_CNF_STRU     *pstAcInfoQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstAcInfoQueryCnf       = (TAF_MMA_AC_INFO_QUERY_CNF_STRU*)pstMsg;
    usLength                = 0;
    ulResult                = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAcInfoQueryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_LOCINFO_READ */
    if (AT_CMD_ACINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ����Ƿ�ʧ��,���ʧ���򷵻�ERROR */
    if (VOS_OK != pstAcInfoQueryCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucSrvDomain),/* �ϱ������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.enCellAcType),/* �ϱ�С����ֹ�������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictRegister),/* �ϱ��Ƿ�ע������ */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictPagingRsp));/* �ϱ��Ƿ�Ѱ������ */

        /* ���� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

        usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucSrvDomain),/* �ϱ������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.enCellAcType),/* �ϱ�С����ֹ�������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictRegister),/* �ϱ��Ƿ�ע������ */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictPagingRsp));/* �ϱ��Ƿ�Ѱ������ */

        gstAtSendData.usBufLen = usLength;

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaQryCurcCnf
 ��������  : AT�յ�MTA ID_MTA_AT_QRY_CURC_CNF��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryCurcCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU               *pstMtaAtQryCurcCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;
    VOS_UINT8                               ucLoop;

    /* ��ʼ�� */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCurcCnf  = (MTA_AT_CURC_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CURC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CURC��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCurcCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCurcCnf->enCurcRptType);

        /* ���<mode>����Ϊ2����Ҫ��ӡ����<report_cfg> */
        if (AT_MTA_RPT_GENERAL_CONTROL_CUSTOM == pstMtaAtQryCurcCnf->enCurcRptType)
        {
            usLength    += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  ",0x");

            for (ucLoop = 0; ucLoop < AT_CURC_RPT_CFG_MAX_SIZE; ucLoop++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%02X",
                                                   pstMtaAtQryCurcCnf->aucRptCfg[ucLoop]);
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetUnsolicitedRptCnf
 ��������  : AT�յ�MTA ID_MTA_AT_SET_UNSOLICITED_RPT_CNF��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU    *pstSetUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_UNSOLICITED_RPT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetUnsolicitedCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaQryUnsolicitedRptCnf
 ��������  : AT�յ�MTA AT�յ�ID_MTA_AT_QRY_UNSOLICITED_RPT_CNF��Ϣ��������Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��5��25��
    ��    ��   : s00217060
    �޸�����   : DTS2013052406352

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_UNSOLICITED_RPT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ����ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstQryUnsolicitedCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* Modified by s00217060 for DTS2013052406352, 2013-5-25, begin */
        /* ucIndex���������� */
        ulResult = AT_ProcMtaUnsolicitedRptQryCnf(ucIndex, pstMsg);
        /* Modified by s00217060 for DTS2013052406352, 2013-5-25, end */
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_ProcMtaUnsolicitedRptQryCnf
 ��������  : AT�����ѯ��Ϣ����
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��5��25��
    ��    ��   : s00217060
    �޸�����   : for DTS2013052406352:
                 ucIndex���󣬸�������at^time=0,��ѯʱ��ʾ+ctzr: 0

*****************************************************************************/
VOS_UINT32 AT_ProcMtaUnsolicitedRptQryCnf(
    VOS_UINT8                               ucIndex,
    VOS_VOID                               *pstMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    /* Modified by s00217060 for DTS2013052406352, 2013-5-25, begin */
    /* ucIndexͨ���ϲ㺯�������� */

    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    /* Modified by s00217060 for DTS2013052406352, 2013-5-25, end */

    switch (pstQryUnsolicitedCnf->enReqType)
    {
        /* TIME��ѯ�Ĵ��� */
        case AT_MTA_QRY_TIME_RPT_TYPE:
            gstAtSendData.usBufLen =
                (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR*)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucTimeRptFlg);
            break;

        /* CTZR��ѯ�Ĵ��� */
        case AT_MTA_QRY_CTZR_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucCtzvRptFlg);
            break;

        /* CSSN��ѯ�Ĵ��� */
        case AT_MTA_QRY_CSSN_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssiRptFlg,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssuRptFlg);
            break;

        /* CUSD��ѯ�Ĵ��� */
        case AT_MTA_QRY_CUSD_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,"%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.ucCusdRptFlg);
            break;

        default:
            ulResult = AT_CME_UNKNOWN;

    }

    return ulResult;
}

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */
/* Modified by z00161729 for DTS2013020600770, 2013-2-4, begin */

/*****************************************************************************
 �� �� ��  : AT_RcvMmaCerssiInfoQueryCnf
 ��������  : TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��4��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
 2.��    ��   : 2013��4��20��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_UINT32 AT_RcvMmaCerssiInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU *pstCerssiInfoQueryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;


    /* ��ʼ�� */
    pstCerssiInfoQueryCnf   = (TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU*)pstMsg;
    usLength                = 0;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCerssiInfoQueryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_CERSSI_READ */
    if (AT_CMD_CERSSI_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ����Ƿ�ʧ��,���ʧ���򷵻�ERROR */
    if (VOS_OK != pstCerssiInfoQueryCnf->ucRslt)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }
    else
    {
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-20, begin */
        if (TAF_PH_RAT_GSM == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                               gaucAtCrLf,
                                               gastAtStringTab[AT_STRING_CERSSI].pucText,
                                               pstNetCtx->ucCerssiReportType,
                                               pstNetCtx->ucCerssiMinTimerInterval,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,
                                               0,
                                               255,
                                               0,
                                               0,
                                               0,
                                               0,
                                               gaucAtCrLf);

            gstAtSendData.usBufLen = usLength;

            /* ������ */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }

        if (TAF_PH_RAT_WCDMA == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            if (TAF_UTRANCTRL_UTRAN_MODE_FDD == pstCerssiInfoQueryCnf->stCerssi.ucCurrentUtranMode)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sEcioValue,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);

                gstAtSendData.usBufLen = usLength;

                /* ������ */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;
            }
            else
            {
                /* ��fdd 3g С����ecioֵΪ��Чֵ255 */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   255,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);



                gstAtSendData.usBufLen = usLength;

                /* ������ */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;

            }
        }

        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-20, end */

        /* Added by s00217060 for Service_State_Optimize_PhaseI, 2014-12-6, begin */
#if ( FEATURE_ON == FEATURE_LTE )
        if (TAF_PH_RAT_LTE == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            /* LTE�µ�cerssi��ѯ������L4A�Ƶ�NAS����atCerssiInfoCnfProc�Ĵ�����ͬ */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s%d,%d,0,0,255,%d,%d,%d,%d,%d,%d%s",
                                               gaucAtCrLf,
                                               gastAtStringTab[AT_STRING_CERSSI].pucText,
                                               pstNetCtx->ucCerssiReportType,
                                               pstNetCtx->ucCerssiMinTimerInterval,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrp,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrq,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.lSINR,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.usRI,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0],
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1],
                                               gaucAtCrLf);

            gstAtSendData.usBufLen = usLength;
            
            /* ������ */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }
        /* Added by s00217060 for Service_State_Optimize_PhaseI, 2014-12-6, end */
#endif
    }

    /* �տ���û�н���ģʽ��������������Чֵ */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_CERSSI].pucText,
                                        pstNetCtx->ucCerssiReportType,
                                        pstNetCtx->ucCerssiMinTimerInterval,
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,      /* rssi */
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                        255,
                                        0,
                                        0,
                                        0,
                                        0,
                                        gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    /* ������ */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/* Modified by z00161729 for DTS2013020600770, 2013-2-4, end */

/* Added by z00214637 for Body Sar Project, 2013-03-11, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaBodySarSetCnf
 ��������  : AT_MMA_AC_INFO_QUERY_CNF��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaBodySarSetCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU             *pstBodySarSetCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg          = (AT_MTA_MSG_STRU*)pstMsg;
    pstBodySarSetCnf = (MTA_AT_RESULT_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_BODYSARON_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* Modifed by Y00213812 for IMEI_VERIFY Project, 2013-05-23, begin */
        return VOS_ERR;
        /* Modifed by Y00213812 for IMEI_VERIFY Project, 2013-05-23, end */
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstBodySarSetCnf->enResult)
    {
        ulResult    = AT_OK;

        /* ����BODYSAR ״̬ */
        if (MTA_BODY_SAR_OFF == g_enAtBodySarState)
        {
            g_enAtBodySarState = MTA_BODY_SAR_ON;
        }
        else
        {
            g_enAtBodySarState = MTA_BODY_SAR_OFF;
        }
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by z00214637 for Body Sar Project, 2013-03-11, end */

/* Added by f00179208 for CCPU RESET, 2013-04-17, Begin */
/*****************************************************************************
 �� �� ��  : AT_ReportResetCmd
 ��������  : �ϱ�^RESET����
 �������  : enCause��λԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s%s%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_RESET].pucText,
                                        enCause,
                                        gaucAtCrLf);

    /* Added by f00179208 for DTS2013091408561, 2013-09-14, Begin */
    /* ��Ҫ�ϱ����ϲ��˫RIL */
    At_SendResultData(AT_CLIENT_ID_APP,  pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_PCUI, pgucAtSndCodeAddr, usLength);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    At_SendResultData(AT_CLIENT_ID_APP5, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_CTRL, pgucAtSndCodeAddr, usLength);
#endif
    /* Added by f00179208 for DTS2013091408561, 2013-09-14, Begin */

    return;
}

/*****************************************************************************
 �� �� ��  : AT_StopAllTimer
 ��������  : ֹͣAT���еĶ�ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��11��
   ��    ��   : l00198894
   �޸�����   : V9R1 STK������Ŀ
 3.��    ��   : 2014��03��13��
   ��    ��   : f00179208
   �޸�����   : DTS2014031305234: AT�������úͲ�ѯ��ʱ��û��ֹͣ
*****************************************************************************/
VOS_VOID AT_StopAllTimer(VOS_VOID)
{
    VOS_UINT8                           ucModemIndex;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT32                          ulTimerName;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx         = VOS_NULL_PTR;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;
    /* Added by f00179208 for DTS2014031305234, 2014-03-13 begin */
    AT_CLIENT_MANAGE_STRU              *pstClientContext = VOS_NULL_PTR;
    /* Added by f00179208 for DTS2014031305234, 2014-03-13 end */

    for (ucModemIndex = 0; ucModemIndex < MODEM_ID_BUTT; ucModemIndex++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucModemIndex);

        /* ֹͣS0��ʱ�� */
        if (VOS_TRUE == pstCcCtx->stS0TimeInfo.bTimerStart)
        {
            ulTimerName = pstCcCtx->stS0TimeInfo.ulTimerName;

            AT_StopRelTimer(ulTimerName, &(pstCcCtx->stS0TimeInfo.s0Timer));
            pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;
            pstCcCtx->stS0TimeInfo.ulTimerName = 0;
        }

        /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */
    }

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstParseContext->hTimer);

        /* Added by f00179208 for DTS2014031305234, 2014-03-13 begin */
        pstClientContext = &(gastAtClientTab[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstClientContext->hTimer);
        /* Added by f00179208 for DTS2014031305234, 2014-03-13 end */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ResetParseCtx
 ��������  : ����PHARE CTX
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ResetParseCtx(VOS_VOID)
{
    VOS_UINT8                           ucClientIndex;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);

        pstParseContext->ucClientStatus = AT_FW_CLIENT_STATUS_READY;

        /* ������еĻ����AT���� */
        AT_ClearBlockCmdInfo(ucClientIndex);

        /* ����AT��������������Ϣ */
        At_ResetCombinParseInfo(ucClientIndex);

        pstParseContext->ucMode    = AT_NORMAL_MODE;
        pstParseContext->usDataLen = 0;
        pstParseContext->usCmdLineLen = 0;

        PS_MEM_SET(pstParseContext->aucDataBuff, 0x00, AT_CMD_MAX_LEN);

        if (NULL != pstParseContext->pucCmdLine)
        {
            AT_FREE(pstParseContext->pucCmdLine);
            pstParseContext->pucCmdLine = NULL;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_ResetClientTab
 ��������  : ����CLIENT TAB
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

 2.��    ��   : 2013��05��22��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT

  3.��    ��   : 2013��11��12��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: ����HSAURT�˿�
*****************************************************************************/
VOS_VOID AT_ResetClientTab(VOS_VOID)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucClientIndex;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        /* ��ն�Ӧ���� */
        PS_MEM_SET(&gastAtClientTab[ucClientIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));
    }

    /* USB PCUI */
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_COM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB Control */
    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_CTRL;
    gastAtClientTab[ucIndex].ucPortNo        = AT_CTR_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_CTR_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB MODEM */
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* NDIS MODEM */
    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_NDIS;
    gastAtClientTab[ucIndex].ucPortNo        = AT_NDIS_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_NDIS_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB UART */
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_UART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_UART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_UART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

#if (FEATURE_ON == FEATURE_AT_HSUART)
    /* Added by A00165503 for UART-MODEM Project, 2013-11-12, Begin */
    /* HSUART */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_HSUART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_HSUART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_HSUART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
    /* Added by A00165503 for UART-MODEM Project, 2013-11-12, End */
#endif

    /* SOCK */
    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_SOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* APP SOCK */
    ucIndex = AT_CLIENT_TAB_APPSOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_APPSOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_APP_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_APP_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* HSIC */
    for (ucLoop = 0; ucLoop < AT_HSIC_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = g_astAtHsicCtx[ucLoop].ucAtClientTabIdx;
        gastAtClientTab[ucIndex].usClientId  = g_astAtHsicCtx[ucLoop].enAtClientId;
        gastAtClientTab[ucIndex].ucPortNo    = g_astAtHsicCtx[ucLoop].ucHsicPort;
        gastAtClientTab[ucIndex].UserType    = g_astAtHsicCtx[ucLoop].ucHsicUser;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }
#endif
    /* MAX ��NV�����Ƶģ�CLIENT TAB�����÷��� AT_MuxInit���� */

    /* APP */
    for (ucLoop = 0; ucLoop < AT_VCOM_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = AT_CLIENT_TAB_APP_INDEX + ucLoop;
        gastAtClientTab[ucIndex].usClientId  = AT_CLIENT_ID_APP + ucLoop;
        gastAtClientTab[ucIndex].ucPortNo    = APP_VCOM_DEV_INDEX_0 + ucLoop;
        gastAtClientTab[ucIndex].UserType    = AT_APP_USER;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-27, Begin */
    /* HSIC MODEM */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_HSIC_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_HSIC_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_HSIC_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-27, End */
#endif

}

/*****************************************************************************
 �� �� ��  : AT_ResetOtherCtx
 ��������  : ����ɢ���ڸ��ļ���ȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��06��03��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ResetOtherCtx(VOS_VOID)
{
    /* <CR> */
    ucAtS3          = 13;

    /* Added by l60609 for DTS2013082605951 2013-08-27, Begin */
    gaucAtCrLf[0]   = ucAtS3;
    /* Added by l60609 for DTS2013082605951 2013-08-27, End */

    /* <LF> */
    ucAtS4          = 10;

    /* Added by l60609 for DTS2013082605951 2013-08-27, Begin */
    gaucAtCrLf[1]   = ucAtS4;
    /* Added by l60609 for DTS2013082605951 2013-08-27, End */

    /* <DEL> */
    ucAtS5          = 8;

    /* ָʾ����������� */
    gucAtVType      = AT_V_ENTIRE_TYPE;

    /* ָʾTE�������� */
    gucAtCscsType   = AT_CSCS_IRA_CODE;

    gucAtEType      = AT_E_ECHO_CMD;

    /* CONNECT <text> result code is given upon entering online data state.
       Dial tone and busy detection are disabled. */
    gucAtXType      = 0;
}

/*****************************************************************************
 �� �� ��  : AT_RcvCcpuResetStartInd
 ��������  : AT�յ�AT��ϢID_CCPU_AT_RESET_START_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��6��1��
    ��    ��   : z60575
    �޸�����   : DTS2012060100769��modem state�����ӿ�

*****************************************************************************/
VOS_UINT32 AT_RcvCcpuResetStartInd(
    VOS_VOID                           *pstMsg
)
{
    /* �ϱ�^RESET:0���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_START);

    /* ֹͣ�����������ڲ���ʱ�� */
    AT_StopAllTimer();

    /* ��ʼ����������Ϣ */
    AT_InitCtx();

    /* ��ȡNV�� */
    AT_ReadNV();

    /* װ����ʼ�� */
    AT_InitDeviceCmd();

    /* STK��ʼ�� */
    AT_InitStk();

    /* ATģ������ĳ�ʼ�� */
    AT_InitPara();

    /* ���ÿͻ��˽�����Ϣ */
    AT_ResetParseCtx();

    /* �����û���Ϣ */
    AT_ResetClientTab();

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* ��ʼ��MAXͨ�� */
    AT_MuxInit();
#endif

    /* ��������ɢ���ȫ�ֱ��� */
    AT_ResetOtherCtx();

    /* Added by z60575 for DTS2012060100769, 2013-6-1, begin */
    /* C�˵�����λ�������豸�ڵ㣬��ǰδ���� */
    mdrv_set_modem_state(PS_FALSE);
    /* Added by z60575 for DTS2012060100769, 2013-6-1, end */

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(AT_GetResetSem());

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : AT_RcvCcpuResetEndInd
 ��������  : AT�յ�AT��ϢID_CCPU_AT_RESET_END_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvCcpuResetEndInd(
    VOS_VOID                           *pstMsg
)
{
    /* ���ø�λ��ɵı�־ */
    AT_SetResetFlag(VOS_FALSE);

    /* �ϱ�^RESET:1���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_END);

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : AT_RcvHifiResetStartInd
 ��������  : AT�յ�AT��ϢID_HIFI_AT_RESET_START_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvHifiResetStartInd(
    VOS_VOID                           *pstMsg
)
{
    /* �ϱ�^RESET:2���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_START);

    AT_DBG_SAVE_HIFI_RESET_NUM(1);

    return VOS_OK;
}
/* Added by f00179208 for CCPU RESET, 2013-04-17, End */

/* Added by s00190137 for HIFI Reset End Report, 2013/07/04, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvHifiResetEndInd
 ��������  : AT�յ�AT��ϢID_HIFI_AT_RESET_END_IND�Ĵ���
 �������  : VOS_VOID                           *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvHifiResetEndInd(
    VOS_VOID                           *pstMsg
)
{
    /* �ϱ�^RESET:3���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_END);

    return VOS_OK;
}
/* Added by s00190137 for HIFI Reset End Report, 2013/07/04, end */

/* Added by z00214637 for TEMP PROTECT NAS project, 2013-04-17, begin */
/*****************************************************************************
 �� �� ��  : AT_SpyMsgProc
 ��������  : AT Spy Pid��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��17��
    ��    ��   : z00214637
    �޸�����   : ��at_lte_eventreport.c��ֲ
*****************************************************************************/
VOS_UINT32 AT_SpyMsgProc(VOS_VOID* pstMsg)
{
    VOS_UINT32 ulRet = VOS_OK;
    TEMP_PROTECT_EVENT_AT_IND_STRU* pDataMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pstMsg;

    switch(pDataMsg->ulMsgId)
    {
#if ( FEATURE_ON == FEATURE_LTE )
        case ID_TEMPPRT_AT_EVENT_IND:
            ulRet = AT_ProcTempprtEventInd(pDataMsg);
            break;
#endif

        case ID_TEMPPRT_STATUS_AT_EVENT_IND:
            ulRet = AT_RcvTempprtStatusInd(pDataMsg);
            break;

        default:
            AT_WARN_LOG("AT_SpyMsgProc:WARNING:Wrong Msg!\n");
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : AT_RcvTempprtStatusInd
 ��������  : �±������ϱ�״̬��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��17��
    ��    ��   : z00214637
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��08��
    ��    ��   : j00174725
    �޸�����   : TQE

*****************************************************************************/
VOS_UINT32 AT_RcvTempprtStatusInd(VOS_VOID *pMsg)
{
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstTempPrt = VOS_NULL_PTR;
    TAF_TEMP_PROTECT_CONFIG_STRU        stTempProtectPara;
    VOS_UINT32                          ulResult;

    /* Modified by j00174725 for TQE, 2013-10-08, begin */
    PS_MEM_SET(&stTempProtectPara, 0x0, sizeof(stTempProtectPara));
    /* Modified by j00174725 for TQE, 2013-10-08, end */

    /* ��ȡ�¶ȱ���״̬�����ϱ�NV�� */
    ulResult = NV_ReadEx(MODEM_ID_0,
                         en_NV_Item_TEMP_PROTECT_CONFIG,
                         &stTempProtectPara,
                         sizeof(TAF_TEMP_PROTECT_CONFIG_STRU));

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_RcvTempprtStatusInd: Read NV fail");
        return VOS_ERR;
    }

    if (AT_TEMPPRT_STATUS_IND_ENABLE == stTempProtectPara.ucSpyStatusIndSupport)
    {
        pstTempPrt = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pMsg;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^THERM: %d%s",
                                                         gaucAtCrLf, pstTempPrt->ulTempProtectEvent, gaucAtCrLf);

        At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        return VOS_OK;
    }

    return VOS_OK;
}
/* Added by z00214637 for TEMP PROTECT NAS project, 2013-04-17, end */

/* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaImeiVerifyQryCnf
 ��������  : �յ�IMEIУ���ѯ�Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��23��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvMtaImeiVerifyQryCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg       = VOS_NULL_PTR;
    VOS_UINT32                         *pulImeiVerify = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg       = (AT_MTA_MSG_STRU*)pstMsg;
    pulImeiVerify = (VOS_UINT32*)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_IMEI_VERIFY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ӡ^IMEIVERIFY */
    usLength  = 0;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^IMEIVERIFY: ");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       *pulImeiVerify);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaCgsnQryCnf
 ��������  : �յ�UE��Ϣ�ϱ��Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��23��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCgsnQryCnf(VOS_VOID *pstMsg)
{
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_CGSN_QRY_CNF_STRU           *pstCgsn;
    VOS_UINT8                           aucImeiAscii[TAF_PH_IMEI_LEN];

    /* ��ʼ�� */
    ucCheckData   = 0;
    PS_MEM_SET(aucImeiAscii, 0x00, TAF_PH_IMEI_LEN);

    pstRcvMsg = (AT_MTA_MSG_STRU*)pstMsg;
    pstCgsn   = (MTA_AT_CGSN_QRY_CNF_STRU *)pstRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CGSN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ȡIMEI��Ϣ */
    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        aucImeiAscii[ulI]     = pstCgsn->aucImei[ulI] + 0x30;
        aucImeiAscii[ulI + 1UL] = pstCgsn->aucImei[ulI + 1UL] + 0x30;

        ucCheckData += (TAF_UINT8)(pstCgsn->aucImei[ulI]
                       +((pstCgsn->aucImei[ulI + 1UL] * 2) / 10)
                       +((pstCgsn->aucImei[ulI + 1UL] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    aucImeiAscii[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    aucImeiAscii[TAF_PH_IMEI_LEN - 1] = 0;

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s",
                                      aucImeiAscii);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

/* Added by Y00213812 for IMEI_VERIFY Project, 2013-05-23, end */

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMmaCopnInfoQueryCnf
 ��������  : TAF_MMA_COPN_INFO_QUERY_CNF_STRU��Ϣ������
 �������  : VOS_VOID *pMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��֧��+COPN����
  2.��    ��   : 2013��05��24��
    ��    ��   : W00176964
    �޸�����   : SS FDN&Call Control��Ŀ:UT�޸�,���Ӷ��ŷָ���
  3.��    ��   : 2014��01��15��
    ��    ��   : f62575
    �޸�����   : DTS2014011301359: ���շ�PID��ԭ����WUEPS_PID_MMA�޸�ΪI0_WUEPS_PID_MMA
*****************************************************************************/
VOS_UINT32 AT_RcvMmaCopnInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_COPN_INFO_QUERY_CNF_STRU   *pstCopnInfo = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_STRU          *pstPlmnName = VOS_NULL_PTR;
    TAF_MMA_COPN_INFO_QUERY_REQ_STRU    stCopnInfo;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    pstCopnInfo   = (TAF_MMA_COPN_INFO_QUERY_CNF_STRU *)pMsg;
    usLength      = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCopnInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_COPN_QRY */
    if (AT_CMD_COPN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ����+COPS��^MMPLMNINFO����� */
    pstPlmnName = (TAF_PH_OPERATOR_NAME_STRU *)pstCopnInfo->aucContent;

    for (ulLoop = 0; ulLoop < pstCopnInfo->usPlmnNum; ulLoop++)
    {
        /*  +COPN: <operator in numeric format><operator in long alphanumeric format>     */
        /* ��������� */
        /* Modified by w00176964 for SS FDN&Call Control, 2013-5-24, begin */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        /* Modified by w00176964 for SS FDN&Call Control, 2013-5-24, end */

        /* ������ָ�ʽ��Ӫ������ */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "\"%X%X%X",
                                           (TAF_MMA_PLMN_MCC_DIGIT3_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT3_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT2_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT1_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT1_OFFSET);

        if (TAF_MMA_PLMN_MNC_DIGIT3_MASK != (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%X",
                                               (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT3_OFFSET);

        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%X%X\"",
                                           (TAF_MMA_PLMN_MNC_DIGIT2_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MNC_DIGIT1_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT1_OFFSET);

        /* Added by w00176964 for SS FDN&Call Control, 2013-5-24, begin */
        /* ��Ӷ��ŷָ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"");
        /* Added by w00176964 for SS FDN&Call Control, 2013-5-24, end */

        /* �����Ӫ�̳��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           pstPlmnName->aucOperatorNameLong);

        /* ������� */
        /* Modified by w00176964 for SS FDN&Call Control, 2013-5-24, begin */
        /* ��Ӷ��ŷָ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s",
                                           gaucAtCrLf);
        /* Modified by w00176964 for SS FDN&Call Control, 2013-5-24, end */

        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        /* Added by w00176964 for SS FDN&Call Control, 2013-5-24, begin */
        usLength = 0;
        /* Added by w00176964 for SS FDN&Call Control, 2013-5-24, end */

        pstPlmnName++;

    }

    /*
    ATģ�����MMA�ϱ�����Ӫ�̸�����ȷ����Ӫ����Ϣ�Ƿ��ռ����: С���������Ӫ��
    ��������Ϊ��Ӫ����Ϣ�Ѿ��ռ���ɣ�ԭ����������:
    ATģ��ÿ������50����Ӫ����Ϣ����ʼλ��Ϊ�Ѿ���������һ����Ӫ�̵���һ����Ӫ����Ϣ����
    ������������Ӫ����Ϣ��������50������ʵ�ʵ������
    �����Ӫ����Ϊ50�ı�������AT���ٷ�һ����Ӫ����Ϣ����MMA�ظ�����Ӫ����Ϣ����Ϊ0
    */
    if (pstCopnInfo->usPlmnNum < TAF_MMA_COPN_PLMN_MAX_NUM)
    {
        /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        stCopnInfo.usFromIndex  = pstCopnInfo->usFromIndex + pstCopnInfo->usPlmnNum;
        stCopnInfo.usPlmnNum    = TAF_MMA_COPN_PLMN_MAX_NUM;

        /* Modifeded by f62575 for DTS2014011301359, 2014-01-15,Begin */
        ulRet                   = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                        0,
                                                        TAF_MSG_MMA_COPN_INFO_QUERY_REQ,
                                                        &stCopnInfo,
                                                        sizeof(stCopnInfo),
                                                        I0_WUEPS_PID_MMA);
        /* Modifeded by f62575 for DTS2014011301359, 2014-01-15,End */
        if (TAF_SUCCESS != ulRet)
        {
            /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
        }
    }
    return VOS_OK;
}

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

/* Added by s00217060 for V9R1_SVLTE, 2013-6-4, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetNCellMonitorCnf
 ��������  : AT�յ�MTA ID_MTA_AT_SET_NCELL_MONITOR_CNF��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��31��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                 *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetCnf    = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_NCELL_MONITOR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaQryNCellMonitorCnf
 ��������  : AT�յ�MTA ID_MTA_AT_NCELL_MONITOR_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU      *pstMtaAtQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCnf      = (MTA_AT_NCELL_MONITOR_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_NCELL_MONITOR_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_READ.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^NCELLMONITOR��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* ��ѯʱ������Ҫ�ϱ�����״̬ */
        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d,%d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCnf->ucSwitch,
                                                  pstMtaAtQryCnf->ucNcellState);

    }

    gstAtSendData.usBufLen = usLength;

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaNCellMonitorInd
 ��������  : AT�յ�MTA ID_MTA_AT_NCELL_MONITOR_IND��Ϣ������
 �������  : VOS_VOID *pstMsg - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMtaNCellMonitorInd(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_IND_STRU          *pstMtaAtInd    = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtInd         = (MTA_AT_NCELL_MONITOR_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;
    usLength            = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNCellMonitorInd : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^NCELLMONITOR: %d%s",
                                       gaucAtCrLf,
                                       pstMtaAtInd->ucNcellState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}

/* Added by s00217060 for V9R1_SVLTE, 2013-6-4, end */

/* Added by s00190137 for SIM Insert, 2013/07/04, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMmaSimInsertRsp
 ��������  : SIMINSERT��������ķ��ش���
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSimInsertRsp(VOS_VOID *pMsg)
{
    TAF_MMA_SIM_INSERT_RSP_STRU        *pstSimInsertRsp;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstSimInsertRsp = (TAF_MMA_SIM_INSERT_RSP_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSimInsertRsp->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMINSERT_SET */
    if (AT_CMD_SIMINSERT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstSimInsertRsp->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by s00190137 for SIM Insert, 2013/07/04, end */

/* Added by l00198894 for V9R1 AGPS, 2013/07/22, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaRefclkfreqSetCnf
 ��������  : ATģ���յ�MTA�ظ���REFCLKFREQ_SET_CNF��Ϣ�Ĵ�����
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRefclkfreqSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RESULT_CNF_STRU             *pstRltCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstMtaMsg   = (AT_MTA_MSG_STRU *)pMsg;
    pstRltCnf   = (MTA_AT_RESULT_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_SET */
    if ( AT_CMD_REFCLKFREQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstRltCnf->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaRefclkfreqQryCnf
 ��������  : ATģ���յ�MTA�ظ���REFCLKFREQ_QRY_CNF��Ϣ�Ĵ�����
 �������  : pMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRefclkfreqQryCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU     *pstRefclkfreqCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU *)pMsg;
    pstRefclkfreqCnf    = (MTA_AT_REFCLKFREQ_QRY_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_REFCLKFREQ_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstRefclkfreqCnf->enResult )
    {
        /* ���GPS�ο�ʱ����Ϣ������汾��Ĭ��Ϊ0 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: 0,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstRefclkfreqCnf->ulFreq,
                                                        pstRefclkfreqCnf->ulPrecision,
                                                        pstRefclkfreqCnf->enStatus);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult    = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaRefclkfreqInd
 ��������  : ATģ���յ�MTA�ظ���REFCLKFREQ_IND��Ϣ�Ĵ�����
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_RcvMtaRefclkfreqInd(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_IND_STRU         *pstRefclkfreqInd;

    /* ��ʼ����Ϣ���� */
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstRefclkfreqInd    = (MTA_AT_REFCLKFREQ_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ���GPS�ο�ʱ����Ϣ������汾��Ĭ��Ϊ0 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: 0,%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_REFCLKFREQ].pucText,
                                                    pstRefclkfreqInd->ulFreq,
                                                    pstRefclkfreqInd->ulPrecision,
                                                    pstRefclkfreqInd->enStatus,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}
/* Added by l00198894 for V9R1 AGPS, 2013/07/22, end */

/* Added by m00217266 for AP Sensor, 2013-08-07, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaHandleDectSetCnf
 ��������  : ����MTA����cp���ֳ�λ��CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_UINT32 AT_RcvMtaHandleDectSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU     *pstSetCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf           = (MTA_AT_HANDLEDECT_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_HANDLEDECT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : Current Option is not AT_CMD_HANDLEDECT_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaHandleDectQryCnf
 ��������  : ����MTA��ѯcp���ֳ�λ��CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_UINT32 AT_RcvMtaHandleDectQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU     *pstQryCnf         = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstQryCnf           = (MTA_AT_HANDLEDECT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_HANDLEDECT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : Current Option is not AT_CMD_HANDLEDECT_QRY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^HANDLEDECT?��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT16)pstQryCnf->usHandle);

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by m00217266 for AP Sensor, 2013-08-07, End */

/* Added by l00198894 for SVLTE Offline Reselect Project, 2013/10/21, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaPsTransferInd
 ��������  : �ϱ�^PSTRANSFER����֪ͨӦ��ִ��PS��Ǩ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : V9R1C50 SVLTE������ѡ��Ŀ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaPsTransferInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_PS_TRANSFER_IND_STRU        *pstPsTransferInd;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstPsTransferInd    = (MTA_AT_PS_TRANSFER_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsTransferInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^PSTRANSFER: %d%s",
                                                    gaucAtCrLf,
                                                    pstPsTransferInd->ucCause,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}
/* Added by l00198894 for SVLTE Offline Reselect Project, 2013/10/21, end */

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaMipiInfoInd
 ��������  : ^mipiclk�����ϱ�֪ͨӦ�ò����LCD
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaMipiInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_IND_STRU     *pstMipiClkCnf;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^MIPICLK: %d%s",
                                                    gaucAtCrLf,
                                                    pstMipiClkCnf->usMipiClk,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaMipiInfoCnf
 ��������  : �ظ�^mipiclk��ѯ֪ͨӦ�ò����LCD
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaMipiInfoCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_CNF_STRU     *pstMipiClkCnf;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_CNF_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_MIPI_CLK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMipiClkCnf->usResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstMipiClkCnf->usMipiClk);
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, End */

/* Added by A00165503 for UART-MODEM Project, 2013-09-23, Begin */
/*****************************************************************************
 �� �� ��  : AT_RcvSwitchCmdModeMsg
 ��������  : ����˿��л�����ģʽ��Ϣ
 �������  : ucIndex - �˿�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_RcvSwitchCmdModeMsg(VOS_UINT8 ucIndex)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;

    pstLineCtrl = AT_GetUartLineCtrlInfo();

    /* ����ԭ��(enPortIndex��Ӧ�Ķ˿�):
     * (1) ONLINE-DATAģʽ - �ϱ�OK
     * (2) ����ģʽ        - ����
     */

    /* �˿�������� */
    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return;
    }

    /* ֻ����UART�˿ڼ�⵽���л����� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return;
    }

    /* Ŀǰֻ֧��PPP��IPģʽ���л�ΪONLINE-COMMANDģʽ */
    if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
      && ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
        || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode) ) )
    {
        if (AT_UART_DSR_MODE_CONNECT_ON == pstLineCtrl->enDsrMode)
        {
            AT_CtrlDSR(ucIndex, AT_IO_LEVEL_LOW);
        }

        At_SetMode(ucIndex, AT_ONLINE_CMD_MODE, AT_NORMAL_MODE);
        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}
/* Added by A00165503 for UART-MODEM Project, 2013-09-23, End */

/*added by y00176023 for DSDS II,2014-03-24,begin*/
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : AT_RcvMtaPsProtectSetCnf
 ��������  : ATģ���յ�MTA������ID_MTA_AT_RRC_PROTECT_PS_CNF������Ϣ�Ĵ�����
 �������  : pMsg   -- MTA���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��25��
    ��    ��   : y00176023
    �޸�����   : ����^PSPROTECTMODE����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaPsProtectSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pRcvMsg;
    MTA_AT_RRC_PROTECT_PS_CNF_STRU     *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    /* ��ʼ����Ϣ���� */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_RRC_PROTECT_PS_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsProtectSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaPsProtectSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PSPROTECTMODE_SET */
    if ( AT_CMD_PSPROTECTMODE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:Not AT_CMD_CGPSCLOCK_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : AT_RcvMtaPhyInitCnf
 ��������  : ATģ���յ�MTA������ ID_MTA_AT_PHY_INIT_CNFȷ����Ϣ�Ĵ�����
 �������  : pMsg   -- MTA���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��25��
    ��    ��   : y00176023
    �޸�����   : ����^PHYINIT����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaPhyInitCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pRcvMsg;
    MTA_AT_PHY_INIT_CNF_STRU           *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_PHY_INIT_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHYINIT_SET */
    if ( AT_CMD_PHYINIT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaPhyInitCnf: WARNING:Not AT_CMD_PHYINIT!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


/*added by y00176023 for DSDS II,2014-03-24,end*/

/* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaEcidSetCnf
 ��������  : ATģ���յ�MTA�ظ���ECID_SET_CNF��Ϣ�Ĵ�����
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaEcidSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_ECID_SET_CNF_STRU           *pstEcidSetCnf;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex         = 0;
    pstMtaMsg       = (AT_MTA_MSG_STRU*)pMsg;
    pstEcidSetCnf   = (MTA_AT_ECID_SET_CNF_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_ECID_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEcidSetCnf->enResult )
    {
        /* �����ѯ����ǿ��С����Ϣ */
        /* +ECID=<version>,<rat>,[<cell_description>] */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s=%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstEcidSetCnf->aucCellInfoStr);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult    = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by l00198894 for ����+ECID����, 2013-12-09, end */

/* Added by s00261364 for L-C��������Ŀ, 2014-1-27, begin */

/*****************************************************************************
 �� �� ��  : AT_RcvMmaSysCfgSetCnf
 ��������  : ��������MMAģ��ID_TAF_MMA_SYS_CFG_CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaSysCfgSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYS_CFG_CNF_STRU           *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCnfMsg = (TAF_MMA_SYS_CFG_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        /* Modified by s00217060 for VOLTE SWITCH, 2015-2-11, begin */
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
        /* Modified by s00217060 for VOLTE SWITCH, 2015-2-11, end */
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaPhoneModeSetCnf
 ��������  : ��������MMAģ��ID_TAF_MMA_PHONE_MODE_SET_CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaPhoneModeSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;
#if(FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucSptLteFlag;
    VOS_UINT8                           ucSptUtralTDDFlag;
#endif

    pstCnfMsg           = (TAF_MMA_PHONE_MODE_SET_CNF_STRU *)pMsg;
    ucIndex             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    enModemId           = MODEM_ID_0;
    ulResult            = AT_FAILURE;

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG1("AT_RcvMmaPhoneModeSetCnf:Get ModemID From ClientID fail,ClientID=%d", ucIndex);

        return VOS_ERR;
    }

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        /* Modified by s00217060 for VOLTE SWITCH, 2015-2-11, begin */
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);       /* �������� */
        /* Modified by s00217060 for VOLTE SWITCH, 2015-2-11, end */
    }


    if (TAF_PH_MODE_FULL == pstCnfMsg->ucPhMode)
    {
        IMM_MntnAcpuCheckPoolLeak();
    }

    /* Added by c64416 for ^PSTANDBY low power proc, 2013-9-13, Begin */
    /* V7R2 ^PSTANDBY����ùػ��������� */
#ifdef FEATURE_UPGRADE_TL
    if(AT_CMD_PSTANDBY_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        return VOS_OK;
    }
#endif
    /* Added by c64416 for ^PSTANDBY low power proc, 2013-9-13, End */

    /* Begin: Modified by l00169177 20130829 DTS2013082901597 */
#if((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS))
    /* Modified by z00220246 for DSDA Phase II, 2012-12-25, Begin */
    /* ���GU��������ȷ�����͵�TL�Ⲣ�ȴ���� */
    if (ulResult == AT_OK)
    {
        /* Added by l60609 for DTS2013082205690, 2013-08-22, begin */
        ucSptLteFlag        = AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE);
        ucSptUtralTDDFlag   = AT_IsModemSupportUtralTDDRat(enModemId);

        if ((VOS_TRUE       == ucSptLteFlag)
         || (VOS_TRUE       == ucSptUtralTDDFlag))
        /* Added by l60609 for DTS2013082205690, 2013-08-22, end */
        {
            if ((AT_CMD_TMODE_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
             || (AT_CMD_SET_TMODE == gastAtClientTab[ucIndex].CmdCurrentOpt))
            {
                AT_ProcOperModeWhenLteOn(ucIndex);
                return VOS_OK;
            }
        }
    }
    /* Modified by z00220246 for DSDA Phase II, 2012-12-25, End */
#endif
   /* End: Modified by l00169177 20130829 DTS2013082901597 */

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaDetachCnf
 ��������  : ��������MMAģ��ID_TAF_MMA_DETACH_CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_DETACH_CNF_STRU            *pstDetachCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstDetachCnf = (TAF_MMA_DETACH_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDetachCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstDetachCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        /* Modified by s00217060 for VOLTE SWITCH, 2015-2-11, begin */
        gastAtClientTab[ucIndex].ulCause = pstDetachCnf->enErrorCause;
        /* Modified by s00217060 for VOLTE SWITCH, 2015-2-11, end */
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/* Added by s00261364 for L-C��������Ŀ, 2014-1-27, end */

/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
�� �� ��  : AT_RcvVcMsgSetMsdCnfProc
��������  : VC�ظ�AT ����eCall��Ϣ�Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2014��3��27��
    ��    ��   : j00174725
    �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_UINT32 AT_RcvVcMsgSetMsdCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    APP_VC_SET_MSD_CNF_STRU            *pstRslt  = VOS_NULL_PTR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgSetMsdCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgSetMsdCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_ECLMSD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvVcMsgSetMsdCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return VOS_ERR;
    }

    pstRslt = (APP_VC_SET_MSD_CNF_STRU *)pstData->aucContent;

    if (VOS_OK == pstRslt->ucRslt)
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : AT_RcvVcMsgQryMsdCnfProc
��������  : VC�ظ�AT ��ѯeCall MSD ��Ϣ�Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2014��3��27��
    ��    ��   : j00174725
    �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_UINT32 AT_RcvVcMsgQryMsdCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_MSG_QRY_MSD_CNF_STRU        *pstQryMsd  = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          i;
    VOS_UINT16                          usLength;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryMsdCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryMsdCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_ECLMSD_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvVcMsgQryMsdCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return VOS_ERR;
    }

    /* ��ʼ�� */
    pstQryMsd = (APP_VC_MSG_QRY_MSD_CNF_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryMsd->ucQryRslt)
    {
        /* �����ѯ��� */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: \"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < APP_VC_MSD_DATA_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                        "%02x",
                                                        pstQryMsd->aucMsdData[i]);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                        "\"");

        gstAtSendData.usBufLen = usLength;
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : AT_RcvVcMsgQryEcallCfgCnfProc
��������  : VC�ظ�AT ��ѯeCall ������Ϣ�Ĵ�����
�������  : MN_AT_IND_EVT_STRU   *pstData
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޶���¼  :
  1.��    ��   : 2014��3��27��
    ��    ��   : j00174725
    �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_UINT32 AT_RcvVcMsgQryEcallCfgCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU  *pstQryCfg  = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;



    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryEcallCfgCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvVcMsgQryEcallCfgCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_ECLCFG_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvVcMsgQryEcallCfgCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return VOS_ERR;
    }

    /* ��ʼ�� */
    pstQryCfg  = (APP_VC_MSG_QRY_ECALL_CFG_CNF_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryCfg->ucQryRslt)
    {
        /* �����ѯ��� */
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstQryCfg->enMode,
                                                        pstQryCfg->enVocConfig);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}
#endif
/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

/* Added by h00285180 for DTS2015011409018, 2015-01-15, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMmaSrchedPlmnInfoInd
 ��������  : ����ID_TAF_MMA_SRCHED_PLMN_INFO_IND
 �������  :  VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : h00285180
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvMmaSrchedPlmnInfoInd(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSrchedPlmnInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength    = 0;
    enModemId   = MODEM_ID_0;
    pstSrchedPlmnInfo  = (TAF_MMA_SRCHED_PLMN_INFO_IND_STRU*)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstSrchedPlmnInfo->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSrchedPlmnInfoInd At_ClientIdToUserId FAILURE");
        return VOS_ERR;
    }

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_RcvMmaSrchedPlmnInfoInd: Get modem id fail.");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s",
                                       gaucAtCrLf,
                                       gastAtStringTab[AT_STRING_SRCHEDPLMNINFO].pucText);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d",
                                       pstSrchedPlmnInfo->enRat,
                                       pstSrchedPlmnInfo->ulLaiNum);

    for (i = 0; i < pstSrchedPlmnInfo->ulLaiNum; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%x%x%x",
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0x0f00) >> 8,
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0xf0) >> 4,
                                           (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mcc & 0x0f));

        if (0x0f00 == (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f00))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x,",
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0xf0) >> 4,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f));
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%x%x%x,",
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f00) >> 8,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0xf0) >> 4,
                                               (pstSrchedPlmnInfo->astLai[i].stPlmnId.Mnc & 0x0f));
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d",
                                           pstSrchedPlmnInfo->astLai[i].usLac);
    }


    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    return VOS_OK;
}
/* Added by h00285180 for DTS2015011409018, 2014-01-15, end   */
/* Added by m00217266 for Xpass reselect, 2014-12-25, begin */
/*****************************************************************************
 �� �� ��  : AT_RcvMtaXpassInfoInd
 ��������  : ATģ���յ�MTA�����ϱ���xpass��Ϣ
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : m00217266
    �޸�����   : ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaXpassInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg       = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU         *pstXpassInfoInd = VOS_NULL_PTR;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstXpassInfoInd     = (MTA_AT_XPASS_INFO_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXpassInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^XPASSINFO: %d,%d%s",
                                                    gaucAtCrLf,
                                                    pstXpassInfoInd->enGphyXpassMode,
                                                    pstXpassInfoInd->enWphyXpassMode,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}
/* Added by m00217266 for Xpass reselect, 2014-12-25, end */

/* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, Begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : AT_RcvMmaImsSwitchSetCnf
 ��������  : ����ID_TAF_MMA_IMS_SWITCH_SET_CNF
 �������  :  VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvMmaImsSwitchSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_CNF_STRU   *pstCnfMsg = VOS_NULL_PTR;
    VOS_UINT8                          ucIndex;
    VOS_UINT32                         ulResult;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pstCnfMsg = (TAF_MMA_IMS_SWITCH_SET_CNF_STRU*)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* �㲥��Ϣ������ */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ�������� */
    if (AT_CMD_IMS_SWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchSetCnf: WARNING:Not AT_CMD_IMS_SWITCH_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaImsSwitchQryCnf
 ��������  : ����ID_TAF_MMA_IMS_SWITCH_QRY_CNF
 �������  :  VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvMmaImsSwitchQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_IMS_SWITCH_QRY_CNF_STRU    *pstSwitchQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstSwitchQryCnf     = (TAF_MMA_IMS_SWITCH_QRY_CNF_STRU *)pMsg;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSwitchQryCnf->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_IMS_SWITCH_QRY */
    if (AT_CMD_IMS_SWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaImsSwitchQryCnf: WARNING:Not AT_CMD_IMS_SWITCH_QRY!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSwitchQryCnf->enImsSwitch);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaVoiceDomainSetCnf
 ��������  : ����ID_TAF_MMA_VOICE_DOMAIN_SET_CNF
 �������  :  VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvMmaVoiceDomainSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU  *pstCnfMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    ucIndex   = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    pstCnfMsg = (TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU *)pMsg;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* �㲥��Ϣ������ */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ�������� */
    if (AT_CMD_VOICE_DOMAIN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainSetCnf: WARNING:Not AT_CMD_VOICE_DOMAIN_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->enErrorCause);
    }

    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_VoiceDomainTransToOutputValue
 ��������  : modem���Ӧ��voice domainֵת��ΪAT�����ֵ
 �������  : enVoiceDomain
 �������  : ��
 �� �� ֵ  : ulValue
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_VoiceDomainTransToOutputValue(
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDoman,
    VOS_UINT32                         *pulValue
)
{
    VOS_UINT32                          ulRst;

    ulRst = VOS_TRUE;

    switch (enVoiceDoman)
    {
        case TAF_MMA_VOICE_DOMAIN_CS_ONLY:
            *pulValue = AT_VOICE_DOMAIN_TYPE_CS_ONLY;
            break;

        case TAF_MMA_VOICE_DOMAIN_IMS_PS_ONLY:
            *pulValue = AT_VOICE_DOMAIN_TYPE_IMS_PS_ONLY;
            break;

        case TAF_MMA_VOICE_DOMAIN_CS_PREFERRED:
            *pulValue = AT_VOICE_DOMAIN_TYPE_CS_PREFERRED;
            break;

        case TAF_MMA_VOICE_DOMAIN_IMS_PS_PREFERRED:
            *pulValue = AT_VOICE_DOMAIN_TYPE_IMS_PS_PREFERRED;
            break;

        default:
            *pulValue = AT_VOICE_DOMAIN_TYPE_BUTT;
            ulRst = VOS_FALSE;
            break;
    }

    return ulRst;

}

/*****************************************************************************
 �� �� ��  : AT_RcvMmaVoiceDomainQryCnf
 ��������  : ����ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF
 �������  :  VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_RcvMmaVoiceDomainQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU  *pstDomainQryCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulValue             = 0;
    pstDomainQryCnf     = (TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU *)pMsg;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDomainQryCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf : AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_VOICE_DOMAIN_QRY */
    if (AT_CMD_VOICE_DOMAIN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMmaVoiceDomainQryCnf: WARNING:Not AT_CMD_VOICE_DOMAIN_QRY!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != AT_VoiceDomainTransToOutputValue(pstDomainQryCnf->enVoiceDomain, &ulValue))
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = 0;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       "%s: %d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ulValue);
    }

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

#endif
/* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, End */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

