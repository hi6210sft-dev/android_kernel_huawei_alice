/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RnicTimerMgmt.c
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2011��12��06��
  ����޸�   :
  ��������   : ��ʱ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��06��
    ��    ��   : ����/00179208
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicTimerMgmt.h"
#include "RnicCtx.h"
#include "v_timer.h"
#include "RnicLog.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_TIMERMGMT_C
/*lint -e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : RNIC_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��RNIC��ʼ����Resetʱ������
 �������  : pstRnicTimerCtx:��ʱ���������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  RNIC_InitAllTimers(
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 �� �� ��  : RNIC_StartTimer
 ��������  : ����ָ����RNIC��ʱ��
 �������  : enTimerId:��Ҫ�����Ķ�ʱ��ID
             ulLen    :��ʱ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��22��
    ��    ��   : A00165503
    �޸�����   : DTS2012052202998: ϵͳ������״̬��, ���貦���������ʱ�䵽
                 ���, �����޷��Զ��Ͽ�, ��ʱ����Ҫʹ��32Kʱ��Դ
  3.��    ��   : 2012��6��6��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ�ʱ����׼�����޸�
  4.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulRet;
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;

    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    /* Ŀǰ���貦�ŵĹ���ֻ������0���� */
    pstUlCtx            = RNIC_GetUlCtxAddr(RNIC_RM_NET_ID_0);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    pstRnicTimerCtx     = RNIC_GetTimerAddr();
    enTimerPrecision    = VOS_TIMER_PRECISION_5;

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* ���������� */
    if (0 == ulLen)
    {
        RNIC_ERROR_LOG1(ACPU_PID_ADS_UL, "ADS_StartTimer:ulLen is",ulLen);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    /* Add By z60575 for DTS2012060508406, 2012-6-5 begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* �����δ���û���Դ��־�������ǰ���Ͽ���ʱ���������øñ�־����������32Kʱ��Ϊ����Դ */
    if ((VOS_FALSE == RNIC_GetTimer4WakeFlg())
      && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_SetTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_TRUE);
    }

#endif

    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
     /* ����������ϱ���ʱ���������26Mʱ���ϣ��Խ��͹��� */
    if (RNIC_IS_DSFLOW_TIMER_ID(enTimerId))
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
    {
        enTimerPrecision = VOS_TIMER_NO_PRECISION;
    }
    /* Add By z60575 for DTS2012060508406, 2012-6-5 end */


    /* Modified by A00165503 for DTS2012052202998, 2012-05-22, Begin */
    /* VOS_StartRelTimer ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer),
                              ACPU_PID_RNIC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              enTimerPrecision);
    /* Modified by A00165503 for DTS2012052202998, 2012-05-22, End */
    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");
        return;
    }

    if (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId)
    {
        /* ���貦��ͳ������ */
        pstUlCtx->stULDataStats.ulULPeriodSndPkts = 0;
    }

    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_RUNING;


    /* ��ʱ��״̬�������� */

}


/*****************************************************************************
 �� �� ��  : RNIC_StopTimer
 ��������  : ָֹͣ����RNIC��ʱ��
 �������  : enTimerId:��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��6��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ�ʱ����׼�����޸�
*****************************************************************************/
VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    /* ����ʹ�õĶ�ʱ����Χ�� */
    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return;
    }

    /* û����������Ҫֹͣ */
    if (RNIC_TIMER_STATUS_RUNING  != pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstRnicTimerCtx[enTimerId].hTimer)
    {
        VOS_StopRelTimer(&(pstRnicTimerCtx[enTimerId].hTimer));
    }

    pstRnicTimerCtx[enTimerId].hTimer        = VOS_NULL_PTR;
    pstRnicTimerCtx[enTimerId].enTimerStatus = RNIC_TIMER_STATUS_STOP;

    /* ��ʱ��״̬�������� */
    /* Add By z60575 for DTS2012060508406, 2012-6-5 begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* ����Ѿ������˻���Դ��־�������ǰ���Ͽ���ʱ����������ñ�־����������32Kʱ��Ϊ�ǻ���Դ */
    if ((VOS_TRUE == RNIC_GetTimer4WakeFlg())
     && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
#endif
    /* Add By z60575 for DTS2012060508406, 2012-6-5 end */
}


/*****************************************************************************
 �� �� ��  : RNIC_StopAllTimer
 ��������  : ֹͣRNIC�����ж�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��6��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ�ʱ����׼�����޸�
*****************************************************************************/
VOS_VOID  RNIC_StopAllTimer( VOS_VOID )
{

    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if (RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus)
        {
            /* ֹͣVOS��ʱ�� */
            VOS_StopRelTimer(&(pstRnicTimerCtx[i].hTimer));

            pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
        }
    }

    /* Add By z60575 for DTS2012060508406, 2012-6-5 begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* ����Ѿ������˻���Դ��־��������ñ�־����������32Kʱ��Ϊ�ǻ���Դ */
    if (VOS_TRUE == RNIC_GetTimer4WakeFlg())
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
#endif
    /* Add By z60575 for DTS2012060508406, 2012-6-5 end */
}


/*****************************************************************************
 �� �� ��  : RNIC_GetTimerStatus
 ��������  : ��ѯָ����RNIC��ʱ����״̬
 �������  : enTimerId:��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : RNIC_TIMER_STATUS_ENUM_UINT8:��ʱ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          ulLeftLen;

    pstRnicTimerCtx = RNIC_GetTimerAddr();
    ulLeftLen       = 0;

    if (enTimerId >= RNIC_MAX_TIMER_NUM)
    {
        return RNIC_TIMER_STATUS_STOP;
    }

    if (RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[enTimerId].enTimerStatus)
    {
        if (VOS_OK != (VOS_GetRelTmRemainTime(&(pstRnicTimerCtx[enTimerId].hTimer), &ulLeftLen)))
        {
            RNIC_StopTimer(enTimerId);
            return RNIC_TIMER_STATUS_STOP;
        }
        else
        {
            return RNIC_TIMER_STATUS_RUNING;
        }
    }

    return RNIC_TIMER_STATUS_STOP;

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

