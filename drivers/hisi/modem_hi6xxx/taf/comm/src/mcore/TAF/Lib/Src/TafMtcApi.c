/************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtcApi.c
  �� �� ��   : ����
  ��    ��   : j00174725
  ��������   : 2014��06��16��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ļ�

************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "pslog.h"
#include "TafMtcApi.h"




#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTC_API_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

#if (FEATURE_MULTI_MODEM == FEATURE_ON)

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    extern VOS_UINT32 AT_GetDestPid(
        MN_CLIENT_ID_T                      usClientId,
        VOS_UINT32                          ulRcvPid
    );
#endif

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MTC_SndMsg
 ��������  : ����MTC��Ϣ
 �������  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MTC_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    TAF_PS_MSG_STRU                    *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult = VOS_OK;

    /* ������Ϣ */
    pstMsg = (TAF_PS_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                UEPS_PID_MTC,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->stHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    /* ��д��Ϣ���� */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* ������Ϣ */
    ulResult = PS_SEND_MSG(UEPS_PID_MTC, pstMsg);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTC_SetCdmaServiceConnStateInfo
 ��������  : �����ⲿCDMA Modem������״̬(PS&CS)
 �������  : ulModuleId                 - ģ��ID(����Pid)
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstCdmsStatus              - ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MTC_SetCdmaServiceConnStateInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmaState
)
{
    TAF_MTC_CDMA_STATE_IND_STRU         stSetCdmaConnSt;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetCdmaConnSt, 0x00, sizeof(TAF_MTC_CDMA_STATE_IND_STRU));

    /* ����ID_MSG_MTC_CDMA_CONN_STATUS��Ϣ */
    TAF_API_CTRL_HEADER(&stSetCdmaConnSt.stCtrl, pstCtrl->ulModuleId,
                        pstCtrl->usClientId, pstCtrl->ucOpId);

    PS_MEM_CPY(&stSetCdmaConnSt.stCdmaState, pstCdmaState, sizeof(TAF_MTC_CDMA_STATE_INFO_STRU));

    /* ������Ϣ */
    ulResult = TAF_MTC_SndMsg(UEPS_PID_MTC,
                             ID_MSG_MTC_CDMA_CONN_STATE_IND,
                             &stSetCdmaConnSt,
                             sizeof(TAF_MTC_CDMA_STATE_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_MTC_SetModemServiceConnState
 ��������  : ����modem״̬��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             pstModemConnSt  ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 TAF_MTC_SetModemServiceConnState(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemConnSt
)
{
    TAF_MTC_MODEM_CONN_STATUS_IND_STRU  stModemConnSt;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stModemConnSt, 0x00, sizeof(TAF_MTC_MODEM_CONN_STATUS_IND_STRU));

    /* ����ID_MSG_MTC_CDMA_CONN_STATUS��Ϣ */
    TAF_API_CTRL_HEADER(&(stModemConnSt.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    PS_MEM_CPY(&stModemConnSt.stModemConnStateInfo, pstModemConnSt, sizeof(TAF_MTC_SRV_CONN_STATE_INFO_STRU));

    /* ������Ϣ */
    ulResult = TAF_MTC_SndMsg(UEPS_PID_MTC,
                             ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND,
                             &stModemConnSt,
                             sizeof(TAF_MTC_MODEM_CONN_STATUS_IND_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_MTC_SetModemUsimmState
 ��������  : ���ÿ�״̬��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             pstModemConnSt  ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 TAF_MTC_SetModemUsimmState(
    TAF_CTRL_STRU                           *pstCtrl,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimState
)
{
    TAF_MTC_USIMM_STATUS_IND_STRU       stUsimmState;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stUsimmState, 0x00, sizeof(TAF_MTC_USIMM_STATUS_IND_STRU));

    /* ����ID_MSG_MTC_CDMA_CONN_STATUS��Ϣ */
    TAF_API_CTRL_HEADER(&(stUsimmState.stCtrl), pstCtrl->ulModuleId, pstCtrl->usClientId, pstCtrl->ucOpId);

    stUsimmState.enUsimmState = enUsimState;

    /* ������Ϣ */
    ulResult = TAF_MTC_SndMsg(UEPS_PID_MTC,
                             ID_MSG_MTC_USIMM_STATE_IND,
                             &stUsimmState,
                             sizeof(TAF_MTC_USIMM_STATUS_IND_STRU));

    return ulResult;
}
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

