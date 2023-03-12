/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RnicEntity.c
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2011��12��06��
  ����޸�   :
  ��������   : RNICʵ�����
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��06��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "v_typdef.h"
#include "ImmInterface.h"
#include "RnicProcMsg.h"
#include "RnicLog.h"
#include "RnicEntity.h"
#include "RnicDebug.h"
/* Added by f00179208 for DSDA Phase I, 2012-11-28, Begin */
#include "RnicCtx.h"
/* Added by f00179208 for DSDA Phase I, 2012-11-28, End */
/* Modified by m00217266 for L-C��������Ŀ, 2014-1-21, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
#include "SdioInterface.h"
#endif
#include "RnicConfigInterface.h"
/* Modified by m00217266 for L-C��������Ŀ, 2014-1-21, end */

/* Added by j00174725 for DTS2014080800660, 2014-08-05, Begin */
#include "product_config.h"
/* Added by j00174725 for DTS2014080800660, 2014-08-05, End */

/* Added by j00174725 for DTS2014080800660, 2014-08-05, Begin */
#if (VOS_WIN32 == VOS_OS_VER)
#include <stdio.h>
#endif
/* Added by j00174725 for DTS2014080800660, 2014-08-05, End */
#include "mdrv.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_RNIC_ENTITY_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/*lint -e762*/
/* Modified by l60609 for AP������Ŀ ��2012-09-03 Begin */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
extern int netif_rx(struct sk_buff *skb);
extern int netif_rx_ni(struct sk_buff *skb);
#else
/* Added by z60575 for DTS2012060902909, 2012-06-09 begin */
extern int netif_rx_ni_balong(struct sk_buff *skb);
/* Added by z60575 for DTS2012060902909, 2012-06-09, End */
#endif
/* Modified by l60609 for AP������Ŀ ��2012-09-03 End */

/*lint +e762*/

/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : RNIC_ProcUlDataInPdpActive
 ��������  : ��PDP�����״̬��RNIC��������ʱ�Ĵ������
 �������  : pstSkb :SKBUF�����׵�ַ
             pstPriv:˽�������׵�ַ
             ucRabid:��·���غ�
             ucNetIndex:����ID
             enIpType:IPv4��IPv6
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��13��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
 3.��    ��   : 2013��6��3��
   ��    ��   : L47619
   �޸�����   : V3R3 Share-PDP��Ŀ�޸�
*****************************************************************************/
VOS_VOID RNIC_SendULDataInPdpActive(
    IMM_ZC_STRU                        *pstImmZc,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucNetIndex,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType
)
{
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    VOS_UINT8                           ucSendAdsRabId;
    MODEM_ID_ENUM_UINT16                enModemId;

    pstUlCtx                            = RNIC_GET_UL_CTX_ADDR(ucNetIndex);
    enModemId                           = RNIC_GET_MODEM_ID_BY_NET_ID(ucNetIndex);

    /* ����Modem Id��װRabId */
    if (MODEM_ID_0 == enModemId)
    {
        ucSendAdsRabId = ucRabId;
    }
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    else if (MODEM_ID_1 == enModemId)
    {
        ucSendAdsRabId = ucRabId | RNIC_RABID_TAKE_MODEM_1_MASK;
    }
#endif
    else
    {
        /* ����Modem0��Modem1���������ݣ�ֱ�Ӷ��� */
        RNIC_DBG_MODEM_ID_UL_DISCARD_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        /* ����ͳ�� */
        pstPriv->stStats.tx_dropped++;
        pstUlCtx->stULDataStats.ulULTotalDroppedPkts++;

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ProcUlDataInPdpActive:Modem Id failed");
        return;
    }

    if (VOS_OK != ADS_UL_SendPacketEx(pstImmZc, enIpType, ucSendAdsRabId))
    {
        RNIC_DBG_SEND_UL_PKT_FAIL_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        /* ����ͳ�� */
        pstPriv->stStats.tx_dropped++;
        pstUlCtx->stULDataStats.ulULTotalDroppedPkts++;

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ProcUlDataInPdpActive:Send packet failed");
        return;
    }

    RNIC_DBG_SEND_UL_PKT_NUM(1, ucNetIndex);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    /* ͳ������������Ϣ */
    pstPriv->stStats.tx_packets++;
    pstPriv->stStats.tx_bytes += pstImmZc->len;

    /* ͳ�Ʒ��͵��������ݰ����������ڰ��貦�ŶϿ� */
    pstUlCtx->stULDataStats.ulULPeriodSndPkts++;

    /* ͳ�Ʒ��͵������ֽ��������������ϱ� */
    pstUlCtx->stULDataStats.ulULPeriodSndBytes += pstImmZc->len;
    pstUlCtx->stULDataStats.ulULTotalSndBytes  += pstImmZc->len;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_TransSkbToImmZC
 ��������  : ��SKBUFת����A�˹����ڴ�
 �������  : pstSkb   :SKBUF���ݰ��׵�ַ
             pstPriv  :����˽�е�ַָ��
             ucNetIndex:����ID
 �������  : pstImmZc : A�˹��������ڴ�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��18��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��27��
   ��    ��   : ����
   �޸�����   : ���ⵥ��:DTS2012042302535,����->A��->���е����ݰ���Ҫ������һ��
                ����ڴ�ת��
 3.��    ��   : 2012��8��30��
   ��    ��   : l60609
   �޸�����   : AP������Ŀ ��V9R1ֻ����ϵͳ�ڴ�
 4.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_TransSkbToImmZC(
    IMM_ZC_STRU                       **pstImmZc,
    struct sk_buff                     *pstSkb,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
)
{
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 Begin */
#if(FEATURE_ON == FEATURE_SKB_EXP)
    RNIC_UL_CTX_STRU                   *pstUlCtx = VOS_NULL_PTR;
    /* Added by f00179208 for DTS2012042302535��2012-04-26 Begin */
    IMM_MEM_STRU                       *pstImmMem = VOS_NULL_PTR;
    /* Added by f00179208 for DTS2012042302535��2012-04-26 Begin */
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    pstUlCtx                            = RNIC_GET_UL_CTX_ADDR(ucNetIndex);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
#endif

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    *pstImmZc = (IMM_ZC_STRU *)pstSkb;

    return VOS_OK;
#else
    /* �����Linuxϵͳ�ṩ�����ݣ���Ҫת���ɿ���ڴ� */
    if (MEM_TYPE_SYS_DEFINED == pstSkb->private_mem.enType)
    {
        *pstImmZc = IMM_ZcStaticCopy((IMM_ZC_STRU *)pstSkb);

        /* �ڴ����ʧ����Ҫ�ͷ��ڴ� */
        if (VOS_NULL_PTR == *pstImmZc)
        {
            /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
             RNIC_DBG_UL_CHANGE_IMMZC_FAIL_NUM(1, ucNetIndex);
            /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

            /* ����ͳ�� */
            pstPriv->stStats.tx_dropped++;
            pstUlCtx->stULDataStats.ulULTotalDroppedPkts++;

            /* �ͷ��ڴ�, �ýӿ��ڲ��������ڴ����Դ */
            IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SkbTransToImmZC:Malloc IMM failed");
            return VOS_ERR;
        }

        /* ת���ɹ����ں˲��ͷ�LINUXϵͳ�ṩ�������ڴ棬��RNICֱ���ͷŵ� */
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
    }
    /* ������û�������ڴ��ṩ������ */
    else
    {
        /* Modified by f00179208 for DTS2012042302535��2012-04-26 Begin */
        pstImmMem = (IMM_MEM_STRU *)pstSkb->private_mem.pMem;

        /* A�˹����ڴ�ص��ڴ�,����Ҫת�� */
        if (IMM_MEM_POOL_ID_SHARE == pstImmMem->enPoolId)
        {
            *pstImmZc = (IMM_ZC_STRU *)pstSkb;
        }
        /* A�˹����ڴ��������ڴ棬��Ҫ����ת��һ�ο���ڴ� */
        else
        {
            *pstImmZc = IMM_ZcStaticCopy((IMM_ZC_STRU *)pstSkb);

            /* �ڴ����ʧ����Ҫ�ͷ��ڴ� */
            if (VOS_NULL_PTR == *pstImmZc)
            {
                /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
                 RNIC_DBG_UL_CHANGE_IMMZC_FAIL_NUM(1, ucNetIndex);
                /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

                /* ����ͳ�� */
                pstPriv->stStats.tx_dropped++;
                pstUlCtx->stULDataStats.ulULTotalDroppedPkts++;

                /* �ͷ��ڴ�, �ýӿ��ڲ��������ڴ����Դ */
                IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
                RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SkbTransToImmZC:Malloc IMM failed");
                return VOS_ERR;
            }

            /* ת���ɹ����ں˲��ͷ�LINUXϵͳ�ṩ�������ڴ棬��RNICֱ���ͷŵ� */
            IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
        }
        /* Modified by f00179208 for DTS2012042302535��2012-04-26 Begin */
    }

    return VOS_OK;
#endif
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 End */
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcUlIpv4Data
 ��������  : RNIC����IPV4����������
 �������  : pstSkb   :SKBUF���ݰ��׵�ַ
             pstNetDev:�����豸ָ��
             ucNetIndex:����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��30��
   ��    ��   : l60609
   �޸�����   : AP������Ŀ����RNIC_TransSkbToImmZC����ͳ��ת��ʧ�ܵĴ���
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_SendULIpv4Data(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
)
{
    VOS_UINT32                          ulRst;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_UINT8                           ucRabId;

    pstImmZc                            = VOS_NULL_PTR;

    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    RNIC_DBG_RECV_UL_IPV4_PKT_NUM(1, ucNetIndex);

    ucRabId = RNIC_GET_SPEC_NET_IPV4_RABID(ucNetIndex);

    /* �Ƿ�RABID */
    if (RNIC_RAB_ID_INVALID == ucRabId)
    {
        RNIC_DBG_RAB_ID_ERR_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);

        /* �澯��Ϣ */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendULIpv4Data:ipv4 is not act!");
        return;
    }

    /* ��Ӧ���·�������ת���ɿ���ڴ� */
    ulRst = RNIC_TransSkbToImmZC(&pstImmZc, pstSkb, pstPriv, ucNetIndex);
    if (VOS_OK != ulRst)
    {
        /* ���ת��ʧ�ܣ�ֱ�ӷ��أ��������������ݴ��� */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendULIpv4Data: TransSkbToImmZC Fail!");
        return;
    }

    /* PDP�������������ݵĴ��� */
    /* Modified by L47619 for V3R3 Share-PDP Project, 2013-6-6, begin */
    RNIC_SendULDataInPdpActive(pstImmZc, pstPriv, ucRabId, ucNetIndex, ADS_PKT_TYPE_IPV4);
    /* Modified by L47619 for V3R3 Share-PDP Project, 2013-6-6, end */
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ProcUlIpv6Data
 ��������  : RNIC����IPV6����������
 �������  : pstSkb   :SKBUF���ݰ��׵�ַ
             pstNetDev:�����豸ָ��
             ucNetIndex:����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��30��
   ��    ��   : l60609
   �޸�����   : AP������Ŀ����RNIC_TransSkbToImmZC����ͳ��ת��ʧ�ܵĴ���
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_SendULIpv6Data(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
)
{
    VOS_UINT32                          ulRst;
    IMM_ZC_STRU                        *pstImmZc;
    VOS_UINT8                           ucRabId;

    pstImmZc                            = VOS_NULL_PTR;

    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    RNIC_DBG_RECV_UL_IPV6_PKT_NUM(1, ucNetIndex);

    ucRabId = RNIC_GET_SPEC_NET_IPV6_RABID(ucNetIndex);

    /* �Ƿ�RABID */
    if (RNIC_RAB_ID_INVALID == ucRabId)
    {
        RNIC_DBG_RAB_ID_ERR_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);

        /* �澯��Ϣ */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendULIpv6Data:ipv6 is net act!");
        return;
    }

     /* ��Ӧ���·�������ת���ɿ���ڴ� */
    ulRst = RNIC_TransSkbToImmZC(&pstImmZc, pstSkb, pstPriv, ucNetIndex);
    if (VOS_OK != ulRst)
    {
        /* ���ת��ʧ�ܣ�ֱ�ӷ��أ��������������ݴ��� */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendULIpv6Data: TransSkbToImmZC Fail!");
        return;
    }

    /* PDP�������������ݵĴ��� */
    /* Modified by L47619 for V3R3 Share-PDP Project, 2013-6-6, begin */
    RNIC_SendULDataInPdpActive(pstImmZc, pstPriv, ucRabId, ucNetIndex, ADS_PKT_TYPE_IPV6);
    /* Modified by L47619 for V3R3 Share-PDP Project, 2013-6-6, end */
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    return;

}


/*****************************************************************************
 �� �� ��  : RNIC_ProcDemDial
 ��������  : RNIC�����貦��
 �������  : struct sk_buff  *pstSkb,
             pBuf -- �洢���ݵĻ����ID

 �������  : ��
 �� �� ֵ  : OK
             ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��19��
    ��    ��   :  ����
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��6��
    ��    ��   : A00165503
    �޸�����   : DTS2012060502819: �����ʽ�������貦��, ����Ƶ���ϱ��¼�
  3.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_ProcDemDial(
    struct sk_buff                     *pstSkb
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    /* Added by A00165503 for DTS2012060502819, 2012-06-06, Begin */
    RNIC_TIMER_STATUS_ENUM_UINT8        enTiStatus;
    /* Added by A00165503 for DTS2012060502819, 2012-06-06, End */
    VOS_UINT32                          ulIpAddr;

    /* ��ȡIP��ַ */
    ulIpAddr = *((VOS_UINT32 *)((pstSkb->data) + RNIC_IP_HEAD_DEST_ADDR_OFFSET));

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode = RNIC_GetDialModeAddr();

    /*����ǹ㲥�����򲻷����貦�ţ�ֱ�ӹ��˵�*/
    if ( RNIC_IPV4_BROADCAST_ADDR == ulIpAddr )
    {
        /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
        RNIC_DBG_UL_RECV_IPV4_BROADCAST_NUM(1, RNIC_RM_NET_ID_0);
        /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

        /* �ͷ��ڴ� */
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
        return VOS_ERR;
    }

    /* Added by A00165503 for DTS2012060502819, 2012-06-06, Begin */
    /* ��ȡ��ǰ���ű�����ʱ����״̬ */
    enTiStatus  = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT);

    /*Ϊ�˷�ֹ���貦���ϱ�̫�죬����һ�����붨ʱ����*/
    if (RNIC_TIMER_STATUS_STOP == enTiStatus)
    {
        /* ֪ͨӦ�ý��в��Ų��� */
        if (RNIC_ALLOW_EVENT_REPORT == pstDialMode->enEventReportFlag)
        {
            if (VOS_OK == RNIC_SendDialEvent(DEVICE_ID_WAN, RNIC_DAIL_EVENT_UP))
            {
                /* �������ű�����ʱ��  */
                RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_PROTECT, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
                /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
                RNIC_DBG_SEND_APP_DIALUP_SUCC_NUM(1, RNIC_RM_NET_ID_0);
                /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
                RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_ProcDemDial: Send dial event succ.");
            }
            else
            {
                /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
                RNIC_DBG_SEND_APP_DIALUP_FAIL_NUM(1, RNIC_RM_NET_ID_0);
                /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
                RNIC_WARNING_LOG(ACPU_PID_RNIC, "RNIC_ProcDemDial: Send dial event fail.");
            }

            RNIC_MNTN_TraceDialConnEvt();
        }
    }
    /* Added by A00165503 for DTS2012060502819, 2012-06-06, End */

    /* �ͷ��ڴ� */
    IMM_ZcFree((IMM_ZC_STRU *)pstSkb);

    return VOS_OK;
}

/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : RNIC_RcvOutsideModemUlData
 ��������  : CDMAģʽ���յ�TCP/IPЭ��ջ����������
 �������  : struct sk_buff                     *pstSkb
             struct net_device                  *pstNetDev
             RNIC_NETCARD_DEV_INFO_STRU         *pstPriv
             VOS_UINT8                           ucNetIndex
 �������  : ��
 �� �� ֵ  : netdev_tx_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��7��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
netdev_tx_t RNIC_RcvOutsideModemUlData(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
)
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucPdnId;
    VOS_ULONG                           ulRslt;
    VOS_UINT32                          ulDataLen;
    RNIC_UL_CTX_STRU                   *pstUlCtx    = VOS_NULL_PTR;

    ulRslt                              = SDIO_ERR;
    ulDataLen                           = pstSkb->len;
    pstUlCtx                            = RNIC_GET_UL_CTX_ADDR(ucNetIndex);

    /* ��ͨ��IP�ײ�Ϊ20�ֽ� */
    /*-------------------------------------------------------------------
      |      0        |       1        |       2        |       3        |
      |---------------|----------------|----------------|----------------|
      |0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7|
      --------------------------------------------------------------------
      | Э��  | �ײ�  |    ��������    |            �ܳ���               |
      | �汾  | ����  |     (TOS)      |           (�ֽ���)              |
      --------------------------------------------------------------------
      |            16λ��ʶ            | ��־ |         13λƬƫ��       |
      --------------------------------------------------------------------
      | ����ʱ��(TTL) |    8λЭ��     |        16λ�ײ�У���           |
      --------------------------------------------------------------------
      |                           32λԴIP��ַ                           |
      --------------------------------------------------------------------
      |                           32λĿ��IP��ַ                         |
      --------------------------------------------------------------------
    */
    /* ��ȡЭ��汾�� */
    ucIpType    = RNIC_GET_IP_VERSION(pstSkb->data[0]);

    /* IP���������ж� */
    switch(ucIpType)
    {
        /* IPv4 ����  IPv6 ���� */
        case RNIC_IPV4_VERSION:
            ucPdnId = RNIC_GET_SPEC_NET_IPV4_PDNID(ucNetIndex);
            break;

        case RNIC_IPV6_VERSION:
            ucPdnId = RNIC_GET_SPEC_NET_IPV6_PDNID(ucNetIndex);
            break;

        default:
            /* ��ά�ɲ� */
            RNIC_DBG_RECV_UL_ERR_PKT_NUM(1, ucNetIndex);
            pstPriv->stStats.tx_dropped++;
            pstUlCtx->stULDataStats.ulULTotalDroppedPkts++;

            /* �ͷ��ڴ� */
            IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
            return NETDEV_TX_OK;
    }

    /* �Ƿ�Pdn Id */
    if (RNIC_PDN_ID_INVALID == ucPdnId)
    {
        RNIC_DBG_PDN_ID_ERR_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);

        return NETDEV_TX_OK;
    }

    ulRslt  = SDIO_UL_SendPacket(pstSkb, ucPdnId);

    if (SDIO_OK != ulRslt)
    {
        RNIC_DBG_SEND_UL_PKT_FAIL_NUM(1, ucNetIndex);
        pstPriv->stStats.tx_dropped++;
        pstUlCtx->stULDataStats.ulULTotalDroppedPkts++;

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstSkb);
    }
    else
    {
        RNIC_DBG_SEND_UL_PKT_NUM(1, ucNetIndex);

        /* ͳ������������Ϣ */
        pstPriv->stStats.tx_packets++;
        pstPriv->stStats.tx_bytes += ulDataLen;

        /* ͳ�Ʒ��͵��������ݰ����� */
        pstUlCtx->stULDataStats.ulULPeriodSndPkts++;

        /* ͳ�Ʒ��͵������ֽ��������������ϱ� */
        pstUlCtx->stULDataStats.ulULPeriodSndBytes += ulDataLen;
        pstUlCtx->stULDataStats.ulULTotalSndBytes  += ulDataLen;
    }

    return NETDEV_TX_OK;
}
#endif
/*****************************************************************************
 �� �� ��  : RNIC_RcvInsideModemUlData
 ��������  : ���յ�TCP/IPЭ��ջ3GPP����������
 �������  : struct sk_buff                     *pstSkb
             struct net_device                  *pstNetDev
             RNIC_NETCARD_DEV_INFO_STRU         *pstPriv
             VOS_UINT8                           ucNetIndex
 �������  : ��
 �� �� ֵ  : netdev_tx_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��7��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
netdev_tx_t RNIC_RcvInsideModemUlData(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
)
{
    VOS_UINT8                           ucIpType;
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 Begin */
    /* Added by A00165503 for DTS2012053004651, 2012-05-31, Begin */
#if(FEATURE_ON == FEATURE_SKB_EXP)
    VOS_UINT32                          ulSndPermitFlg;
#endif
    /* Added by A00165503 for DTS2012053004651, 2012-05-31, End */

#if (FEATURE_ON == FEATURE_SKB_EXP)
    /* Added by A00165503 for DTS2012053004651, 2012-05-31, Begin */
    /* ��ȡ���������ͱ�ʶ */
    ulSndPermitFlg = ADS_UL_IsSendPermit();
#endif

    /* ��������ʱ, ֱ�Ӷ������ݰ� */
#if (FEATURE_ON == FEATURE_SKB_EXP)
    if ((RNIC_FLOW_CTRL_STATUS_START == RNIC_GET_FLOW_CTRL_STATUS(ucNetIndex))
     && (VOS_FALSE == ulSndPermitFlg))
#else
    if (RNIC_FLOW_CTRL_STATUS_START == RNIC_GET_FLOW_CTRL_STATUS(ucNetIndex))
#endif
    /* Modified by l60609 for AP������Ŀ ��2012-09-03 End */
    {
        RNIC_DBG_FLOW_CTRL_UL_DISCARD_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);

        return NETDEV_TX_OK;
    }
    /* Added by A00165503 for DTS2012053004651, 2012-05-31, End */
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    /* ��ͨ��IP�ײ�Ϊ20�ֽ� */
    /*-------------------------------------------------------------------
      |      0        |       1        |       2        |       3        |
      |---------------|----------------|----------------|----------------|
      |0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7||0|1|2|3|4|5|6|7|
      --------------------------------------------------------------------
      | Э��  | �ײ�  |    ��������    |            �ܳ���               |
      | �汾  | ����  |     (TOS)      |           (�ֽ���)              |
      --------------------------------------------------------------------
      |            16λ��ʶ            | ��־ |         13λƬƫ��       |
      --------------------------------------------------------------------
      | ����ʱ��(TTL) |    8λЭ��     |        16λ�ײ�У���           |
      --------------------------------------------------------------------
      |                           32λԴIP��ַ                           |
      --------------------------------------------------------------------
      |                           32λĿ��IP��ַ                         |
      --------------------------------------------------------------------
    */
    /* ��ȡЭ��汾�� */
    ucIpType    = RNIC_GET_IP_VERSION(pstSkb->data[0]);

    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    /* ֻ������0����Żᴥ�����貦�� */
    if ((RNIC_IPV4_VERSION == ucIpType)
     && (AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT == RNIC_GET_DIAL_MODE())
     && (RNIC_PDP_REG_STATUS_DEACTIVE == RNIC_GET_SPEC_NET_IPV4_REG_STATE(ucNetIndex))
     && (RNIC_RM_NET_ID_0 == ucNetIndex))
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
    {

        /* �����貦�� */
        if (VOS_ERR == RNIC_ProcDemDial(pstSkb))
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_StartXmit, the data is discared!");
        }

        return NETDEV_TX_OK;
    }

    /* IP���������ж� */
    switch(ucIpType)
    {
        /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
        /* IPv4 ���� */
        case RNIC_IPV4_VERSION:
            RNIC_SendULIpv4Data(pstSkb, pstNetDev, pstPriv, ucNetIndex);
            break;

        /* IPv6 ���� */
        case RNIC_IPV6_VERSION:
            RNIC_SendULIpv6Data(pstSkb, pstNetDev, pstPriv, ucNetIndex);
            break;

        default:
            RNIC_DBG_RECV_UL_ERR_PKT_NUM(1, ucNetIndex);

            /* �ͷ��ڴ� */
            IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
            break;
        /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
    }

    return NETDEV_TX_OK;
}
/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

/*****************************************************************************
 �� �� ��  : RNIC_AddMacHead
 ��������  : ��IMM_ZC_STRU �㿽���ṹ���MACͷ
 �������  : IMM_ZC_STRU *pstImmZc
             const VOS_UINT8  *pucAddData
             VOS_UINT16 usLen
 �������  : ��
 �� �� ֵ  : VOS_OK ��ӳɹ�
             VOS_ERR ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��2��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 RNIC_AddMacHead (
    IMM_ZC_STRU                        *pstImmZc,
    const VOS_UINT8                    *pucAddData
)
{
    VOS_UINT8                          *pucDestAddr;


    if (VOS_NULL == pstImmZc)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_AddMacHead :pstImmZc ptr is null!");
        return VOS_ERR;
    }

    if (VOS_NULL == pucAddData)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_AddMacHead: pucData ptr is null!");
        return VOS_ERR;
    }

    if(RNIC_ETH_HDR_SIZE > (pstImmZc->data - pstImmZc->head))
    {
        return VOS_ERR;
    }

    pucDestAddr = skb_push(pstImmZc, RNIC_ETH_HDR_SIZE);

    VOS_MemCpy(pucDestAddr, pucAddData, RNIC_ETH_HDR_SIZE);

    return VOS_OK;

}

/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : RNIC_ShowSdioDlData
 ��������  : ��ӡsdioģ�����������
 �������  : pstSkb   :SKBUF�����׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��03��11��
   ��    ��   : m00217266
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowSdioDlData(
    VOS_UINT8                           ucPdnId,
    IMM_ZC_STRU                        *pstImmZc
)
{
    VOS_UINT32                          i;

    /* RNIC �������ݴ�ӡ���أ���ӡȥmacͷ������ */
    if (VOS_TRUE == g_ulRnicPrintDlDataFlg)
    {
        vos_printf("RNIC_ShowSdioDlData : dl data pdn id is %d. \r\n", ucPdnId);
        vos_printf("RNIC_ShowSdioDlData : dl data len is %d. \r\n", pstImmZc->len);
        vos_printf("RNIC_ShowSdioDlData : dl data content is: \r\n");

        for (i = 0; i < pstImmZc->len; i++)
        {
            if (pstImmZc->data[i] > 0xf)
            {
                vos_printf("%x", pstImmZc->data[i]);
            }
            else
            {
                vos_printf("0%x", pstImmZc->data[i]);
            }
        }
        vos_printf("\r\n");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_RcvSdioDlData
 ��������  : ����SDIO����������
 �������  : VOS_UINT8                           ucPdnId
             IMM_ZC_STRU                        *pstData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��6��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_RcvSdioDlData(
    VOS_UINT8                           ucPdnId,
    IMM_ZC_STRU                        *pstImmZc
)
{
    VOS_UINT8                           ucNetIndex;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT8                           ucIpType;
    VOS_UINT32                          ulRet;

    /* ��ν�ɲ⣬��ӡ���ݰ����ݺ�pdn id */
    RNIC_ShowSdioDlData(ucPdnId, pstImmZc);

    /* ����PDNid��ȡ��Ӧ��RMNETid */
    ucNetIndex     = RNIC_GET_RM_NET_ID_BY_PDN_ID(ucPdnId);

    /* ��ȡЭ��汾�� */
    ucIpType    = RNIC_GET_IP_VERSION(pstImmZc->data[0]);

    if (RNIC_IPV4_VERSION == ucIpType)
    {
        enPktType = ADS_PKT_TYPE_IPV4;
    }
    else if (RNIC_IPV6_VERSION == ucIpType)
    {
        enPktType = ADS_PKT_TYPE_IPV6;
    }
    else    /* ���ݰ����������֧�����Ͳ�һ�� */
    {
        RNIC_DBG_RECV_DL_ERR_PKT_NUM(1, ucNetIndex);
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_RcvSdioDlData, Ip Type is !", ucIpType);

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        return RNIC_ERROR;
    }

    ulRet = RNIC_SendDlData(ucNetIndex, pstImmZc, enPktType);
    return ulRet;
}
#endif

/*****************************************************************************
 �� �� ��  : RNIC_RcvAdsDlData
 ��������  : RNIC�յ�ADS��������
 �������  : ucRabid  :��·���غ�
             pstData  :SKBUF���ݰ��׵�ַ
             enPdpType:PDP ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��10��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  RNIC_RcvAdsDlData(
    VOS_UINT8                           ucExRabid,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType,
    VOS_UINT32                          ulExParam
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucRmNetId;

    ucRmNetId = RNIC_GET_RMNETID_FROM_EXPARAM(ulExParam);

    ulRet = RNIC_SendDlData(ucRmNetId, pstImmZc, enPktType);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : RNIC_SendDlData
 ��������  : RNIC_SendDlData��������ʱ�Ĵ������
 �������  : ucNetIndex :����id
             pstData    :SKBUF���ݰ��׵�ַ
             enPdpType  :PDP ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  : VOS_UINT32:RNIC_OK, RNIC_ERROR
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2011��12��06��
    ��    ��   : ����
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��06��08��
    ��    ��   : zhangyizhan 60575
    �޸�����   : DTS2012060708396��ϱ����޸�
  3.��    ��   : 2011��06��09��
    ��    ��   : zhangyizhan 60575
    �޸�����   : DTS2012060902909���������޸ģ�,V3R2/V7R1ͳһ����netif_rx
  4.��    ��   : 2012��6��20��
    ��    ��   : A00165503
    �޸�����   : DTS2012061904440: �����û���ʱ��ͳ��
  5.��    ��   : 2012��6��20��
    ��    ��   : f00179208
    �޸�����   : DTS2012070306267: �����ں˽ӿ�ʧ�ܺ󣬲���Ҫ�ͷ��ڴ�
  6.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: RNIC��ʵ��
  7.��    ��   : 2014��6��13��
    ��    ��   : A00165503
    �޸�����   : DTS2014052607108: ������й����κ˸�λ����
*****************************************************************************/
VOS_UINT32 RNIC_SendDlData(
    VOS_UINT8                           ucNetIndex,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_DL_CTX_STRU                   *pstDlCtx    = VOS_NULL_PTR;
    VOS_UINT8                          *pucAddData  = VOS_NULL_PTR;

    /* Del by j00174725 for RNIC DEV SPLIT, 2014-08-26, begin */
    /* Del by j00174725 for RNIC DEV SPLIT, 2014-08-26, End */

    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    if (ucNetIndex >= RNIC_RM_NET_ID_BUTT)
    {
        RNIC_DBG_NETID_DL_DISCARD_NUM(1, RNIC_RM_NET_ID_0);

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        /* ��ӡ����LOG */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDlData:ucNetIndex is null!");

        return RNIC_INVAL;
    }

    pstDlCtx       = RNIC_GET_DL_CTX_ADDR(ucNetIndex);

    /* ��ȡ����˽�����ݵ�ַ */
    pstPriv        = RNIC_GET_SPEC_PRIV_INFO_ADDR(ucNetIndex);

    /* RNIC��˽������Ϊ�� */
    if (VOS_NULL_PTR == pstPriv)
    {
        RNIC_DBG_NETCAED_DL_DISCARD_NUM(1, ucNetIndex);

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        /* ��ӡ����LOG */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDlData:priv ptr is null!");

        return RNIC_INVAL;
    }

    /* ����δ�� */
    if (RNIC_NETCARD_STATUS_CLOSED == pstPriv->enStatus)
    {
        RNIC_DBG_DISCARD_DL_PKT_NUM(1, ucNetIndex);

        /* ����ͳ�ƣ��ͷ��ڴ� */
        pstPriv->stStats.rx_dropped++;
        pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts++;
        IMM_ZcFree(pstImmZc);

        /* ��ӡ����LOG */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDlData:Netcard is closed!");

        return RNIC_OK;
    }

    /* skb���ݳ��ȳ�����Чֵ(������MACͷ) */
    if ((pstImmZc->len) > RNIC_MAX_PACKET)
    {
        RNIC_DBG_RECV_DL_BIG_PKT_NUM(1, ucNetIndex);

        /* ͳ�ƶ����ʹ����Ϣ */
        pstPriv->stStats.rx_errors++;
        pstPriv->stStats.rx_length_errors++;
        pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts++;

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        /* ��ӡ����LOG */
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDlData:Data is invalid!");

        return RNIC_OK;
    }

    /* ���MAC֡ͷ������ImmZc�ӿڽ�MAC֡ͷ����ImmZc�� */
    if (ADS_PKT_TYPE_IPV4 == enPktType)
    {
        RNIC_DBG_RECV_DL_IPV4_PKT_NUM(1, ucNetIndex);
        pucAddData = (VOS_UINT8*)&g_astRnicManageTbl[ucNetIndex].stIpv4Ethhead;
    }
    else if (ADS_PKT_TYPE_IPV6 == enPktType)
    {
        RNIC_DBG_RECV_DL_IPV6_PKT_NUM(1, ucNetIndex);
        pucAddData = (VOS_UINT8*)&g_astRnicManageTbl[ucNetIndex].stIpv6Ethhead;
    }
    else   /* ���ݰ����������֧�����Ͳ�һ�� */
    {
        RNIC_DBG_RECV_DL_ERR_PKT_NUM(1, ucNetIndex);
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_SendDlData, Rab is different from PktType!", enPktType);

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        return RNIC_ERROR;
    }

    if (VOS_OK != RNIC_AddMacHead(pstImmZc, pucAddData))
    {
        RNIC_DBG_ADD_DL_MACHEAD_FAIL_NUM(1, ucNetIndex);
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDlData, IMM_ZcAddMacHead fail!");

        /* �ͷ��ڴ� */
        IMM_ZcFree(pstImmZc);

        return RNIC_ERROR;
    }

    pstImmZc->protocol = eth_type_trans(pstImmZc, pstPriv->pstNetDev);

    /* ͳ����������������Ϣ */
    pstPriv->stStats.rx_packets++;
    pstPriv->stStats.rx_bytes += pstImmZc->len;

    /* Added by z60575 for DTS2012060902909, 2012-06-09 begin */
    /* ���� netif_rx()���������յ����ݽڵ�ݸ��ں� */
    /* Modify by z60575 for DTS2012060708396, 2012-06-08 begin */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    /* Modify by w00316404 for DTS2015071004300, 2015-08-10 begin */
    if (NET_RX_SUCCESS != netif_rx_ni((struct sk_buff *)pstImmZc))
    /* Modify by w00316404 for DTS2015071004300, 2015-08-10 end */
#else
    if (NET_RX_SUCCESS != netif_rx_ni_balong((struct sk_buff *)pstImmZc))
#endif
    {
        RNIC_DBG_SEND_DL_PKT_FAIL_NUM(1, ucNetIndex);

        /* ����ͳ�ƣ��ͷ��ڴ� */
        pstPriv->stStats.rx_dropped++;
        pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts++;
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_SendDlData:Send data failed!");
        return RNIC_ERROR;
    }
    /* Modify by z60575 for DTS2012060708396, 2012-06-08 end */
    /* Added by z60575 for DTS2012060902909, 2012-06-09 end */

    /* �������з�������ͳ�� */
    RNIC_DBG_SEND_DL_PKT_NUM(1, ucNetIndex);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    /* Del by j00174725 for RNIC DEV SPLIT, 2014-08-26, begin */
    /* Del by j00174725 for RNIC DEV SPLIT, 2014-08-26, End */

    /* ͳ���յ������������ֽ��������������ϱ� */
    pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes += pstImmZc->len;
    pstDlCtx->stDLDataStats.ulDLTotalRcvBytes  += pstImmZc->len;

    return RNIC_OK;

}
/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

/* Added by A00165503 for DTS2012053004651, 2012-05-31, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_StartFlowCtrl
 ��������  : ������������
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  : VOS_OK     - �������سɹ�
             VOS_ERR    - ��������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��31��
   ��    ��   : A00165503
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
unsigned int RNIC_StartFlowCtrl(unsigned char ucRmNetId)
{
    /* Added by f00179208 for DSDA Phase I, 2012-12-10, Begin */
    RNIC_SET_FLOW_CTRL_STATUS(RNIC_FLOW_CTRL_STATUS_START, ucRmNetId);
    /* Added by f00179208 for DSDA Phase I, 2012-12-10, End */

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_StopFlowCtrl
 ��������  : ֹͣ��������
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  : VOS_OK     - ֹͣ���سɹ�
             VOS_ERR    - ֹͣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��31��
   ��    ��   : A00165503
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
unsigned int RNIC_StopFlowCtrl(unsigned char ucRmNetId)
{
    /* Added by f00179208 for DSDA Phase I, 2012-12-10, Begin */
    RNIC_SET_FLOW_CTRL_STATUS(RNIC_FLOW_CTRL_STATUS_STOP, ucRmNetId);
    /* Added by f00179208 for DSDA Phase I, 2012-12-10, End */

    return VOS_OK;
}
/* Added by A00165503 for DTS2012053004651, 2012-05-31, End */

/* Added by m00217266 for L-C��������Ŀ, 2014-1-21, begin */
/*****************************************************************************
 �� �� ��  : RNIC_ConfigRmnetStatus
 ��������  : ���õ�ǰ����״̬���ⲿģ��ӿڣ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : unsigned long
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned long RNIC_ConfigRmnetStatus(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
)
{
    /*��ά�ɲ⣬���������Ϣ*/
    RNIC_MNTN_SndRmnetConfigInfoMsg(pstConfigInfo);
    RNIC_DBG_CONFIGCHECK_ADD_TOTLA_NUM();

    /* ������� */
    /* �ڲ�modem��Ҫ��� rab id�Ƿ��쳣 */
    if (RNIC_MODEM_TYPE_INSIDE == pstConfigInfo->enModemType)
    {
        if (!RNIC_RAB_ID_IS_VALID(pstConfigInfo->ucRabId))
        {
            RNIC_DBG_CONFIGCHECK_ADD_RABID_ERR_NUM();
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild RAB id !");
            return VOS_ERR;
        }
    }
    /* �ⲿmodem��Ҫ��� pdn id�Ƿ��쳣 */
    else if (RNIC_MODEM_TYPE_OUTSIDE == pstConfigInfo->enModemType)
    {
        if (!RNIC_PDN_ID_IS_VALID(pstConfigInfo->ucPdnId))
        {
            RNIC_DBG_CONFIGCHECK_ADD_PDNID_ERR_NUM();
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild Pdn id !");
            return VOS_ERR;
        }
    }
    /* ��ЧMODEM TYPE */
    else
    {
        RNIC_DBG_CONFIGCHECK_ADD_MODEMTYPE_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild modem type!");
        return VOS_ERR;
    }


    /* �������������쳣ֱ�ӷ���error */
    if (!RNIC_RMNET_STATUS_IS_VALID(pstConfigInfo->enRmnetStatus))
    {
        RNIC_DBG_CONFIGCHECK_ADD_RMNETSTATUS_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild Rmnet Status !");
        return VOS_ERR;
    }

    /* IP���ͷǷ�ֱ�ӷ���error */
    if (!RNIC_IP_TYPE_IS_VALID(pstConfigInfo->enIpType))
    {
        RNIC_DBG_CONFIGCHECK_ADD_IPTYPE_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild IP type !");
        return VOS_ERR;
    }

    /* modem id�쳣��飬Ŀǰֻ��������modem0 */
    if (MODEM_ID_0 != pstConfigInfo->usModemId)
    {
        RNIC_DBG_CONFIGCHECK_ADD_MODEMID_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild modem id !");
        return VOS_ERR;
    }

    /* ucRmNetId �쳣��� ĿǰRNIC_RM_NET_ID_3��RNIC_RM_NET_ID_4������ʹ��*/
    if (!RNIC_MODEM_0_RMNET_ID_IS_VALID(pstConfigInfo->ucRmNetId))
    {
        RNIC_DBG_CONFIGCHECK_ADD_RMNETID_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild RmNet id !");
        return VOS_ERR;
    }

    /* �����ڲ���Ϣ */
    if (VOS_OK != RNIC_SndRnicRmnetConfigReq(pstConfigInfo))
    {
        RNIC_DBG_CONFIGCHECK_ADD_SND_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: send pdp status ind fail !");
        return VOS_ERR;
    }

    RNIC_DBG_CONFIGCHECK_ADD_SUCC_NUM();
    return VOS_OK;
}
/* Added by m00217266 for L-C��������Ŀ, 2014-1-21, end */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
