/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafAgentCtx.c
  �� �� ��   : ����
  ��    ��   : c00173809
  ��������   : 2012��01��02��
  ����޸�   :
  ��������   : ��ʼ��TAFAGENTȫ�ֱ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��01��02��
    ��    ��   : C00173809
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafAgentCtx.h"
#include  "TafAgentLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

    /*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_AGENT_CTX_C
    /*lint -e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

TAFAGENT_CTX_STRU                       g_stTafAgentCtx = {0};
TAF_AGENT_STATS_INFO_STRU               g_stTafAgentStats = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : Taf_Agent_InitCtx
 ��������  : ��ʼ��Taf Agentȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��4��
    ��    ��   : A00165503
    �޸�����   : DTS2012042102488: TAF AGENTģ�����������Ϣ, ���ڶ�λ���API
                 ����ʧ������

  3.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ
*****************************************************************************/
VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = VOS_NULL_PTR;

    /* ���以���ź��� */
    if (VOS_OK != VOS_SmMCreate("SYNC", VOS_SEMA4_FIFO, &g_stTafAgentCtx.hTafAcpuSyncSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu sycn sem failed!");
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, Begin */
        TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, End */
        return VOS_ERR;
    }
    else
    {
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, Begin */
        TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(g_stTafAgentCtx.hTafAcpuSyncSem);
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, End */
    }

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "CNF", 0, VOS_SEMA4_FIFO, &g_stTafAgentCtx.hTafAcpuCnfSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu cnf sem failed!");
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, Begin */
        TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, End */
        return VOS_ERR;
    }
    else
    {
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, Begin */
        TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(g_stTafAgentCtx.hTafAcpuCnfSem);
        /* Added by A00165503 for DTS2012042102488, 2012-07-04, End */
    }

    /* Added by A00165503 for DTS2012042102488, 2012-07-04, Begin */
    g_stTafAgentCtx.ulInitFlg = VOS_TRUE;
    /* Added by A00165503 for DTS2012042102488, 2012-07-04, End */

    /* Added by A00165503 for DTS2012071607302, 2012-07-17, Begin */
    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);
    /* Added by A00165503 for DTS2012071607302, 2012-07-17, End */

    TAF_AGENT_ClearMsg();

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_AGETN_GetTafAcpuSyncSem
 ��������  : ��ȡSYNC�ź���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_SEM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuSyncSem;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetTafAcpuCnfSem
 ��������  : ��ȡCnf�ź���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_SEM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID)
{
    return g_stTafAgentCtx.hTafAcpuCnfSem;
}

/*****************************************************************************
 �� �� ��  : TAF_AGETN_GetTafAcpuCnfMsg
 ��������  : ��ȡ��Ϣ��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : MsgBlock*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID)
{
    return g_stTafAgentCtx.pucTafAcpuCnfMsg;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_SetTafAcpuCnfMsg
 ��������  : ������Ϣ��ַ
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = pMsg;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_ClearMsg
 ��������  : �����Ϣ����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID)
{
    PS_MEM_SET(g_stTafAgentCtx.aucMsg,0,sizeof(g_stTafAgentCtx.aucMsg));
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_SaveMsg
 ��������  : ������Ϣ����
 �������  :
 �������  : VOS_UINT8*
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
)
{
    if ((TAFAGENT_APS_MAX_MSG_LEN - VOS_MSG_HEAD_LENGTH) >= ulLen)
    {
        /* ���ݻظ���Ϣ */
        PS_MEM_CPY(g_stTafAgentCtx.aucMsg, pucMsg, ulLen + VOS_MSG_HEAD_LENGTH);

        return &(g_stTafAgentCtx.aucMsg[0]);
    }
    else
    {
        vos_printf("TAF_AGENT_SaveMsg-->msg len too big\n");
        return VOS_NULL_PTR;
    }
}

/* Added by A00165503 for DTS2012042102488, 2012-07-04, Begin */
/*****************************************************************************
 �� �� ��  : TAF_AGENT_ShowStats
 ��������  : ��ʾTAF AGENTģ��������Ϣ, ���ڶ�λ���API����ʧ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��4��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ
*****************************************************************************/
VOS_VOID TAF_AGENT_ShowStats(VOS_VOID)
{
    vos_printf("********************TAF AGENTͳ����Ϣ*******************\n");
    vos_printf("ģ���ʼ����ʶ                              %d\n", g_stTafAgentCtx.ulInitFlg);
    vos_printf("��ǰ�Ļ����ź���                            %x\n", g_stTafAgentCtx.hTafAcpuSyncSem);
    vos_printf("��ǰ�Ļ����ź���                            %x\n", g_stTafAgentCtx.hTafAcpuCnfSem);
    vos_printf("�����Ļ����ź���                            %p\n", g_stTafAgentStats.ulMutexSemId);
    vos_printf("�����Ķ������ź���                          %p\n", g_stTafAgentStats.ulBinarySemId);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_stTafAgentStats.ulCreateMutexSemFailNum);
    vos_printf("�����������ź���ʧ�ܴ���                    %d\n", g_stTafAgentStats.ulCreateBinarySemFailNum);
    vos_printf("�������ź���ʧ�ܴ���                        %d\n", g_stTafAgentStats.ulLockMutexSemFailNum);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_stTafAgentStats.ulLockBinarySemFailNum);
    vos_printf("���һ���������ź���ʧ��ԭ��                %x\n", g_stTafAgentStats.ulLastMutexSemErrRslt);
    vos_printf("���һ�����������ź���ʧ��ԭ��              %x\n", g_stTafAgentStats.ulLastBinarySemErrRslt);
    vos_printf("ͬ����ϢΪ�մ���                            %d\n", g_stTafAgentStats.ulSyncMsgIsNullNum);
    vos_printf("ͬ����Ϣ��ƥ�����                          %d\n", g_stTafAgentStats.ulSyncMsgNotMatchNum);

    vos_printf("\r\n");

}
/* Added by A00165503 for DTS2012042102488, 2012-07-04, End */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
