
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcCtx.c
  �� �� ��   : ����
  ��    ��   : f00179208
  ��������   : 2011��12��06��
  ����޸�   :
  ��������   : RNIC CTX�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��06��
    ��    ��   : f00179208
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicCtx.h"
#include "RnicEntity.h"
#include "PsCommonDef.h"
#include "AtRnicInterface.h"
#include "RnicProcMsg.h"
#include "RnicDemandDialFileIO.h"
#include "RnicLog.h"
/* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
#include "RnicDebug.h"
/* Added by f00179208 for CCPU RESET, 2013-04-15, End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_CTX_C
/*lint +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* RNIC CTX,���ڱ���RNIC��ȫ�ֱ��� */
RNIC_CTX_STRU                           g_stRnicCtx;

/* Added by j00174725 for clean warning, 2013-07-22, Begin */
extern RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
/* Added by j00174725 for clean warning, 2013-07-22, End */

/*****************************************************************************
 �� �� ��  : RNIC_RnicCtxInit
 ��������  : ��ʼ��RNIC��CTX
 �������  : pstRnicCtx:RNIC�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��05��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ����������޸�
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
 3.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : C�˵�����λ��Ŀ:��ʼ����λ�ź���
 4.��    ��   : 2013��07��222��
   ��    ��   : j00177245
   �޸�����   : �������warning
 5.��    ��   : 2014��02��14��
   ��    ��   : m00217266
   �޸�����   : ��ʼ��L-C��������Ŀ�����ӵ�ȫ�ֱ���
 6.��    ��   : 2014��6��3��
   ��    ��   : m00217266
   �޸�����   : DTS2014052902453
*****************************************************************************/
VOS_VOID RNIC_InitCtx(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    VOS_UINT8                           ucIndex;

    /* Added by j00174725 for clean warning, 2013-07-22, Begin */
    PS_MEM_SET(g_astRnicStats, 0, sizeof(g_astRnicStats));
    /* Added by j00174725 for clean warning, 2013-07-22, End */

    /* Added by m00217266 for L-C��������Ŀ, 2014-2-19, begin */
    PS_MEM_SET((VOS_VOID *)&g_stRnicRmnetConfigCheckInfo, 0, sizeof(g_stRnicRmnetConfigCheckInfo));
    /* Added by m00217266 for L-C��������Ŀ, 2014-2-19, end */

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* ��ʼ��RNIC���������� */
        RNIC_InitUlCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stUlCtx));

        /* ��ʼ��RNIC���������� */
        RNIC_InitDlCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stDlCtx));

        /* ��ʼ��RNIC PDP������ */
        RNIC_InitPdpCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stPdpCtx), ucIndex);

        /* Added by A00165503 for DTS2012053004651, 2012-05-31, Begin */
        /* ��ʼ������״̬ */
        pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_STOP;
        /* Added by A00165503 for DTS2012053004651, 2012-05-31, End */

        /* ��ʼ������ͳ�ƶ�ʱ�� */
        pstRnicCtx->astSpecCtx[ucIndex].enTiDsFlowStats  = TI_RNIC_DSFLOW_STATS_0 + ucIndex;

        /* ��ʼ��ģ��ID */
        /* ��ʼ����ʱ����Ѿ�ȷ��������������Ӧ�ĸ�MODEM */
        pstRnicCtx->astSpecCtx[ucIndex].enModemId        = RNIC_GET_MODEM_ID_BY_NET_ID(ucIndex);

        /* Added by m00217266 for DTS2014052902453, 2014-6-3, begin */
        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
        pstRnicCtx->astSpecCtx[ucIndex].enModemType      = RNIC_MODEM_TYPE_INSIDE;
        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */
        /* Added by m00217266 for DTS2014052902453, 2014-6-3, end */

        /* Del by j00174725 for RNIC DEV SPLIT, 2014-08-26, begin */
        /* Del by j00174725 for RNIC DEV SPLIT, 2014-08-26, End */
    }

    /* ��ʼ��RABID��Ϣ */
    for (ucIndex = 0 ; ucIndex < RNIC_MODEM_ID_MAX_NUM ; ucIndex++)
    {
        RNIC_InitRabidInfo(&pstRnicCtx->astRabIdInfo[ucIndex]);
    }

    /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, begin */
    /* ��ʼ��PDNID��Ϣ */
    RNIC_InitPdnIdInfo(&pstRnicCtx->stPdnIdInfo);
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, end */

    /* ��ʼ��RNIC��ʱ�������� */
    RNIC_InitAllTimers(pstRnicCtx->astTimerCtx);

    /* ��ʼ������ģʽ��Ϣ */
    RNIC_InitDialMode(&(pstRnicCtx->stDialMode));
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    /* ��ʼ�����ŶϿ���ʱ����ʱ��������ͳ�� */
    RNIC_ClearTiDialDownExpCount();

    /* Add By z60575 for DTS2012060508406, 2012-6-5 begin */
    RNIC_SetTimer4WakeFlg(VOS_FALSE);
    /* Add By z60575 for DTS2012060508406, 2012-6-5 end */

    /* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
    /* ��ʼ����λ�ź��� */
    RNIC_InitResetSem();
    /* Added by f00179208 for CCPU RESET, 2013-04-15, End */

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitRabidInfo
 ��������  : ��ʼ��Rabid��Ӧ����Ϣ
 �������  : pstRabIdInfo:RabId��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��12��10��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitRabidInfo(
    RNIC_RABID_INFO_STAU               *pstRabIdInfo
)
{

    PS_MEM_SET(pstRabIdInfo->aucRmNetId,
               RNIC_RM_NET_ID_BUTT,
               RNIC_RAB_ID_MAX_NUM);

    return;
}

/* Added by m00217266 for L-C��������Ŀ, 2014-2-8, begin */
/*****************************************************************************
 �� �� ��  : RNIC_InitPdnIdInfo
 ��������  : ��ʼ��Pdnid��Ӧ����Ϣ
 �������  : pstPdnIdInfo:PdnId��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��02��08��
   ��    ��   : m00217266
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitPdnIdInfo(
    RNIC_PDNID_INFO_STAU               *pstPdnIdInfo
)
{

    PS_MEM_SET(pstPdnIdInfo->aucRmNetId,
               RNIC_RM_NET_ID_BUTT,
               RNIC_PDN_ID_MAX);

    return;
}
/* Added by m00217266 for L-C��������Ŀ, 2014-2-8, end */

/*****************************************************************************
 �� �� ��  : RNIC_InitDlCtx
 ��������  : ��ʼ��RNIC���е�CTX
 �������  : pstDlCtx:�����������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitDlCtx(
    RNIC_DL_CTX_STRU                   *pstDlCtx
)
{
    pstDlCtx->stDLDataStats.ulDLCurDataRate         = 0;
    pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts    = 0;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvPkts       = 0;
    pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes      = 0;
    pstDlCtx->stDLDataStats.ulDLTotalRcvBytes       = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitUlCtx
 ��������  : ��ʼ��RNIC���е�CTX
 �������  : pstUlCtx:�����������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitUlCtx(
    RNIC_UL_CTX_STRU                   *pstUlCtx
)
{
    pstUlCtx->stULDataStats.ulULTotalRcvPktsInDeactive  = 0;
    pstUlCtx->stULDataStats.ulULCurDataRate             = 0;
    pstUlCtx->stULDataStats.ulULTotalDroppedPkts        = 0;
    pstUlCtx->stULDataStats.ulULPeriodSndPkts           = 0;
    pstUlCtx->stULDataStats.ulULPeriodSndBytes          = 0;
    pstUlCtx->stULDataStats.ulULTotalSndBytes           = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitPdpCtx
 ��������  : ��ʼ��ָ������PDP������
 �������  : pstPdpCtx:PDP�������׵�ַ
             ucRmNetId:����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_InitPdpCtx(
    RNIC_PDP_CTX_STRU                  *pstPdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_InitIpv4PdpCtx(&(pstPdpCtx->stIpv4PdpInfo));
    RNIC_InitIpv6PdpCtx(&(pstPdpCtx->stIpv6PdpInfo));

    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, Begin */
    RNIC_InitIpv4v6PdpCtx(&(pstPdpCtx->stIpv4v6PdpInfo), ucRmNetId);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, End */

    return;
}

/* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_ResetDialMode
 ��������  : ���ò���ģʽ��Ϣ
 �������  : pstDialMode:����ģʽ�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ResetDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    return;
}
/* Added by f00179208 for CCPU RESET, 2013-04-15, End */

/*****************************************************************************
 �� �� ��  : RNIC_InitDialMode
 ��������  : ��ʼ������ģʽ��Ϣ
 �������  : pstDialMode:����ģʽ�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��1��31��
   ��    ��   : w00199382
   �޸�����   : ��ʼ��/proc/dial�µ��ļ�
*****************************************************************************/
VOS_VOID RNIC_InitDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    VOS_UINT32                          ulRlst;

    pstDialMode->enDialMode             = AT_RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    ulRlst                              = RNIC_InitDemandDialFile();

    if ( VOS_ERR == ulRlst)
    {
       RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialMode:RNIC_InitDemandDialFile ERR!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIpv4PdpCtx
 ��������  : ��ʼ��IPV4 PDP������
 �������  : pstIpv4PdpCtx:IPV4 PDP�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitIpv4PdpCtx(
    RNIC_IPV4_PDP_INFO_STRU            *pstIpv4PdpCtx
)
{
    pstIpv4PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstIpv4PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    pstIpv4PdpCtx->ucPdnId     = RNIC_PDN_ID_INVALID;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */
    pstIpv4PdpCtx->ulIpv4Addr  = 0;
    pstIpv4PdpCtx->aucRsv[0]   = 0;
    pstIpv4PdpCtx->aucRsv[1]   = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIpv6PdpCtx
 ��������  : ��ʼ��IPV6 PDP������
 �������  : pstIpv4PdpCtx:IPV6 PDP�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitIpv6PdpCtx(
    RNIC_IPV6_PDP_INFO_STRU            *pstIpv6PdpCtx
)
{
    pstIpv6PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstIpv6PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    pstIpv6PdpCtx->ucPdnId     = RNIC_PDN_ID_INVALID;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */
    pstIpv6PdpCtx->aucRsv[0]   = 0;
    pstIpv6PdpCtx->aucRsv[1]   = 0;

    PS_MEM_SET(pstIpv6PdpCtx->aucIpv6Addr,
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIpv4v6PdpCtx
 ��������  : ��ʼ��ָ������IPV4V6 PDP������
 �������  : pstIpv4v6PdpCtx:IPV4V6 PDP�������׵�ַ
             ucRmNetId:����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_InitIpv4v6PdpCtx(
    RNIC_IPV4V6_PDP_INFO_STRU          *pstIpv4v6PdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, Begin */
    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                              = RNIC_GetPdpCtxAddr(ucRmNetId);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, End */

    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstIpv4v6PdpCtx->enRegStatus            = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstIpv4v6PdpCtx->ucRabId                = RNIC_RAB_ID_INVALID;
    pstIpv4v6PdpCtx->ucPdnId                = RNIC_PDN_ID_INVALID;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;

    pstIpv4v6PdpCtx->ulIpv4Addr             = 0;
    pstIpv4v6PdpCtx->aucRsv[0]   = 0;
    pstIpv4v6PdpCtx->aucRsv[1]   = 0;

    PS_MEM_SET(pstIpv4v6PdpCtx->aucIpv6Addr,
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);
}

/* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_InitResetSem
 ��������  : ��ʼ��RNIC��λ���ź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_InitResetSem(VOS_VOID)
{
    g_stRnicCtx.hResetSem  = VOS_NULL_PTR;

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "RNIC", 0, VOS_SEMA4_FIFO, &g_stRnicCtx.hResetSem))
    {
        vos_printf("Create rnic acpu cnf sem failed!\r\n");
        RNIC_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        RNIC_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        RNIC_DBG_SAVE_BINARY_SEM_ID(g_stRnicCtx.hResetSem);
    }

    RNIC_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}
/* Added by f00179208 for CCPU RESET, 2013-04-15, End */

/*****************************************************************************
 �� �� ��  : RNIC_GetRnicCtxAddr
 ��������  : ��ȡ��ǰRNIC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰRNIC��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
RNIC_CTX_STRU* RNIC_GetRnicCtxAddr(VOS_VOID)
{
    return &(g_stRnicCtx);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetRnicTiDialDownExpCount
 ��������  : ��ȡ����ģʽͳ�Ʋ��ŶϿ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ģʽͳ�Ʋ��ŶϿ�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_GetTiDialDownExpCount( VOS_VOID)
{
    return (g_stRnicCtx.ulTiDialDownExpCount);
}


/*****************************************************************************
 �� �� ��  : RNIC_TiDialDownExpCountPlusOne
 ��������  : �ۼӲ���ģʽͳ�Ʋ��ŶϿ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_IncTiDialDownExpCount( VOS_VOID)
{
    (g_stRnicCtx.ulTiDialDownExpCount)++;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearRnicTiDialDownExpCount
 ��������  : ����ģʽͳ�Ʋ��ŶϿ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ClearTiDialDownExpCount( VOS_VOID)
{
    g_stRnicCtx.ulTiDialDownExpCount = 0;

    return;
}

/* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_GetCurrentUlRate
 ��������  : ��ȡָ����������������
 �������  : ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : ��ǰRNIC���ʵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_GetCurrentUlRate(VOS_UINT8 ucRmNetId)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, Begin */
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stUlCtx.stULDataStats.ulULCurDataRate);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, End */
}

/*****************************************************************************
 �� �� ��  : RNIC_SetCurrentUlRate
 ��������  : ����ָ����������������
 �������  : ulULDataRate:��������
             ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��13��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_SetCurrentUlRate(
    VOS_UINT32                          ulULDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, Begin */
    g_stRnicCtx.astSpecCtx[ucRmNetId].stUlCtx.stULDataStats.ulULCurDataRate = ulULDataRate;
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, End */

    return;
}


/*****************************************************************************
 �� �� ��  : RNIC_GetCurrentDlRate
 ��������  : ��ȡָ����������������
 �������  : ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : ��ǰRNIC���ʵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_GetCurrentDlRate(VOS_UINT8 ucRmNetId)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, Begin */
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDlCtx.stDLDataStats.ulDLCurDataRate);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, End */
}

/*****************************************************************************
 �� �� ��  : RNIC_SetCurrentDlRate
 ��������  : ����ָ����������������
 �������  : ulDLDataRate:��������
             ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_SetCurrentDlRate(
    VOS_UINT32                          ulDLDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, Begin */
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDlCtx.stDLDataStats.ulDLCurDataRate = ulDLDataRate;
    /* Modified by f00179208 for DSDA Phase I, 2012-11-28, End */

    return;
}
/* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

/*****************************************************************************
 �� �� ��  : RNIC_GetDialModeAddr
 ��������  : ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���貦��ģʽ��ʱ���ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_DIAL_MODE_STRU* RNIC_GetDialModeAddr(VOS_VOID)
{
    return &(g_stRnicCtx.stDialMode);
}

/* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_GetPdpCtxAddr
 ��������  : ��ȡRNICģ��ָ������PDP�����ĵĵ�ַ
 �������  : ucRmNetId -- ��������
 �������  : ��
 �� �� ֵ  : RNICģ��ָ������PDP�����ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
RNIC_PDP_CTX_STRU* RNIC_GetPdpCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId].stPdpCtx);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetUlCtxAddr
 ��������  : ��ȡRNICģ��ָ���������������ĵĵ�ַ
 �������  : ucRmNetId -- ��������
 �������  : ��
 �� �� ֵ  : RNICģ��ָ���������������ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
RNIC_UL_CTX_STRU* RNIC_GetUlCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId].stUlCtx);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetDlCtxAddr
 ��������  : ��ȡRNICģ��ָ���������������ĵĵ�ַ
 �������  : ucRmNetId -- ��������
 �������  : ��
 �� �� ֵ  : RNICģ��ָ���������������ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
RNIC_DL_CTX_STRU* RNIC_GetDlCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId].stDlCtx);
}
/* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

/*****************************************************************************
 �� �� ��  : RNIC_GetTimerAddr
 ��������  : ��ȡRNIC CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
RNIC_TIMER_CTX_STRU*  RNIC_GetTimerAddr( VOS_VOID )
{
    return g_stRnicCtx.astTimerCtx;
}

/* Add By z60575 for DTS2012060508406, 2012-6-5 begin */
/*****************************************************************************
 �� �� ��  : RNIC_GetTimer4WakeFlg
 ��������  : ��ȡRNIC CTXģ�����Ƿ�����Timer4���ѱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��5��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406, �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_GetTimer4WakeFlg(VOS_VOID)
{
    return g_stRnicCtx.ulSetTimer4WakeFlg;
}

/*****************************************************************************
 �� �� ��  : RNIC_SetTimer4WakeFlg
 ��������  : ����RNIC CTXģ�����Ƿ�����Timer4���ѱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��5��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406, �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_SetTimer4WakeFlg(VOS_UINT32 ulFlg)
{
    g_stRnicCtx.ulSetTimer4WakeFlg = ulFlg;
}
/* Add By z60575 for DTS2012060508406, 2012-6-5 end */

/* Added by f00179208 for DSDA Phase I, 2012-11-22, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_GetSpecNetCardPrivateAddr
 ��������  : ��ȡRNICģ��ָ������˽����������ַ
 �������  : ucRmNetId -- ��������
 �������  : ��
 �� �� ֵ  : RNICģ��ָ������˽����������ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��24��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_NETCARD_DEV_INFO_STRU *RNIC_GetSpecNetCardPrivateAddr(VOS_UINT8 ucRmNetId)
{
    return g_stRnicCtx.astSpecCtx[ucRmNetId].pstNetDevInfo;
}

/*****************************************************************************
 �� �� ��  : RNIC_SetSpecNetCardPrivate
 ��������  : ����RNICģ��ָ������˽���������
 �������  : pstPriv:˽������ָ��
             ucRmNetId -- ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��24��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_SetSpecNetCardPrivate(
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].pstNetDevInfo = pstPriv;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetSpecNetCardCtxAddr
 ��������  : ��ȡRNICָ��������������
 �������  : ucIndex -- ��������
 �������  : ��
 �� �� ֵ  : RNICָ�������������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��24��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_SPEC_CTX_STRU *RNIC_GetSpecNetCardCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId]);
}

/* Added by f00179208 for DSDA Phase I, 2012-11-22, End */

/* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_GetResetSem
 ��������  : ��ȡRNIC��λ�ź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : RNIC��λ�ź���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_SEM RNIC_GetResetSem(VOS_VOID)
{
    return g_stRnicCtx.hResetSem;
}
/* Added by f00179208 for CCPU RESET, 2013-04-15, End */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

