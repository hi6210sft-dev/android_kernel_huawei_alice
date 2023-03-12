/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : TafMmaApi.c
  Author       : ---
  Version      : V200R002
  Date         : 2005-09-10
  Description  : ��C�ļ�������MMAģ���Զ��ʵ��
                        1������γ����ݴ��������mux��
                        2�������ϱ����¼������ݴ���APP��AT


  Function List:
        1) Taf_DefPhAccessMode
        2) Taf_DefPhBand
        3) Taf_DefPhClassType
        4) Taf_DefPhMode
        5) Taf_InitEventInfoOP
        6) Taf_MmaGetInfo
        7) Taf_PhoneAttach
        8) Taf_PhoneDetach
        9) Taf_PhonePinHandle
       10) Taf_PhonePlmnList
       11) Taf_PhonePlmnResel
       12) Taf_PhonePlmnUserSel
       13) Taf_PhoneStart
       14) Taf_PhoneStartInfoInd
       15) Taf_PhoneStop

  History      :
  1. Date:2005-09-10
     Author: ���r
     Modification:Create

  1.��    ��   : 2006��2��23��
    ��    ��   : liuyang id:48197
    �޸�����   : ARM�ڴ��������Ҫ��4�ֽڿ�ʼ��λ�û�ȡ,Taf_PhonePlmnUserSel
                 ������������λ.���ⵥ��:A32D02119

  2.��    ��   : 2006��3��24��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D02738

  3. x51137 A32D06630 2006/10/25
Date         Updated By      PR Number
2006-10-26   Li Jilin        A32D06630
  5.��    ��   : 2007��02��11��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D08708
  6.Date        : 2007-10-16
    Author      : F62575
    Modification: ���ⵥA32D13062(�ĵ�У�Է�������)
  7.��    ��   : 2007��10��9��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ�����A32D13994
  8.��    ��   : 2008��3��17��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:AT2D02570,NAS B005�汾�����������
  9.��    ��   : 2008��06��17��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�AT2D03804,
                 ���� ^HS����
************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "TafClientApi.h"
/* Modified by o00132663 for At Project, 2011-10-3, Begin */

/* #include "MnComm.h" */
#include "MnCommApi.h"
/* Modified by o00132663 for At Project, 2011-10-3, End */
#include "TafAppMma.h"


#ifdef  __cplusplus
 #if  __cplusplus
extern "C" {
 #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID PS_FILE_ID_TAF_MMA_API_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

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


/**********************************************************
 Function:       Taf_DefPhServiceMode
 Description:    ҵ��ģʽ����
 Calls:          APP/AT
 Data Accessed:
 Data Updated:
 Input:      ClientId     - APP/AT��ʶ
             OpId         - ������ʶ
             ServiceMode  - ͨ�Ų���
 Output:
 Return:         TAF_SUCCESS - �ɹ�
                 TAF_FAILURE - ʧ��
 Others:
    1.Date        : 2007-10-16
      Author      : F62575
      Modification: ���ⵥA32D13062(�ĵ�У�Է�������)
**********************************************************/
TAF_UINT32  Taf_DefPhClassType ( MN_CLIENT_ID_T       ClientId,
                                 MN_OPERATION_ID_T    OpId,
                                 TAF_PH_MS_CLASS_TYPE MsClass)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_MS_CLASS,
                                   &MsClass,
                                   sizeof(TAF_PH_MS_CLASS_TYPE),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 �� �� ��  : Taf_DefPhMode
 ��������  :  �����ն˹��ܼ��𣨣�CFUN�����������󣩣�
              ͨ�����ûص���������
 �������  :  ClientId  - APP/AT��ʶ
              OpId      - ������ʶ
              PhModeSet - �ֻ�����ģʽ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��8��25��
    ��    ��   : liuyang
    �޸�����   : V200R001�汾�����ɺ���
  2.��    ��   : 2014��2��14��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:���ػ���������,AT�Ŀ��ػ���ѯ��ȷ
*****************************************************************************/
VOS_UINT32 Taf_DefPhMode(MN_CLIENT_ID_T   ClientId,
                         MN_OPERATION_ID_T   OpId,
                         TAF_PH_OP_MODE_STRU PhModeSet)
{
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-19, begin */
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_FUN_QUERY,
                                   &PhModeSet,
                                   sizeof(TAF_PH_OP_MODE_STRU),
                                   I0_WUEPS_PID_MMA);
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-19, end */
}

/*****************************************************************************
 �� �� ��  : Taf_PhonePinHandle
 ��������  : +CPIN USIM�ṩ��PIN������API
             void Api_PIN_Handle(VOS_UINT8 ucClientId,VOS_UINT8 ucCmdType, VOS_UINT8
             ucPINType,\
             VOS_UINT8 *pucOldPIN, VOS_UINT8 *pucNewPIN)��
 �������  : ClientId - APP/AT��ʶ
                 OpId - ������ʶ
*pPinData - �ֻ�PIN��������ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��8��25��
    ��    ��   : liuyang
    �޸�����   : V200R001�汾���ɺ���
  2.��    ��   : 2007��10��16��
    ��    ��   : F62575
    �޸�����   : ���ⵥA32D13062(�ĵ�У�Է�������)
*****************************************************************************/
TAF_UINT32 Taf_PhonePinHandle ( MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                TAF_PH_PIN_DATA_STRU   *pPinData)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_OP_PIN_REQ,
                                   pPinData,
                                   sizeof(TAF_PH_PIN_DATA_STRU),
                                   I0_WUEPS_PID_MMA);
}


/*****************************************************************************
 �� �� ��  : Taf_MePersonalisationHandle
 ��������  : ����״̬��ѯ
 �������  : pMsg  ��Ϣ��
 �������  : ClientId - APP/AT��ʶ
             OpId - ������ʶ
 �� �� ֵ  : �ɹ���ʧ��
 �޸���ʷ      :
  1.��    ��   : 2007��9��28��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 Taf_MePersonalisationHandle(MN_CLIENT_ID_T          ClientId,
                                       MN_OPERATION_ID_T                 OpId,
                                       TAF_ME_PERSONALISATION_DATA_STRU *pMePersonalData)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_ME_PERSONAL_REQ,
                                   pMePersonalData,
                                   sizeof(TAF_ME_PERSONALISATION_DATA_STRU),
                                   I0_WUEPS_PID_MMA);
}

/**********************************************************/
/*                      �绰����API                       */
/**********************************************************/

/**********************************************************
 Function:       Taf_PhonePlmnResel
 Description:    PLMN��ѡ
 Calls:          APP/AT
 Data Accessed:  2005-09-16
 Data Updated:
 Input:          ClientId  - APP/AT��ʶ
                 OpId      - ������ʶ
                 ReselType - ��ѡ����
 Output:
 Return:         TAF_SUCCESS - �ɹ�
                 TAF_FAILURE - ʧ��
 Others:
    1.Date        : 2007-10-16
      Author      : F62575
      Modification: ���ⵥA32D13062(�ĵ�У�Է�������)
**********************************************************/
TAF_UINT32 Taf_PhonePlmnResel ( MN_CLIENT_ID_T           ClientId,
                                MN_OPERATION_ID_T        OpId,
                                TAF_PLMN_RESEL_MODE_TYPE ReselType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_RESEL,
                                   &ReselType,
                                   sizeof(TAF_PLMN_RESEL_MODE_TYPE),
                                   I0_WUEPS_PID_MMA);
}
/*****************************************************************************
 �� �� ��  : TAF_PhonePlmnUserSel
 ��������  : �û�ָ������
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��16��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��2��
    ��    ��   : �����/00130025
    �޸�����   : ���ⵥDTS2011122605064��ATû�д���ָ��������ʱ��Ϣ
*******************************************************************************/
VOS_UINT32 TAF_PhonePlmnUserSel(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PLMN_USER_SEL_STRU             *pstPlmnUserSel
)
{
    VOS_UINT32                           ulRst;

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */

    /* ������Ϣ TAF_MSG_MMA_PLMN_USER_SEL �� MMA ����
       ����Ϣ��TAF_PLMN_USER_SEL_STRU���͵Ĳ����ṹ */
    ulRst = MN_FillAndSndAppReqMsg(ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_USER_SEL,
                                   (VOS_UINT8*)pstPlmnUserSel, /*Ҫ���ѯPS��ע��״̬��*/
                                   sizeof(TAF_PLMN_USER_SEL_STRU),
                                   I0_WUEPS_PID_MMA);


    /* Modified by l00130025 for DTS2011122605064, 2012-1-2, begin */

    if (TAF_SUCCESS == ulRst )
    {
        return VOS_TRUE;
    }
    /* Modified by l00130025 for DTS2011122605064, 2012-1-2, end */

    return VOS_FALSE;

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */
}

/*****************************************************************************
 �� �� ��  : Taf_PhoneAttach
 ��������  : +CGATT ATTACH��ͨ����������ص������ϱ����ؽ��
 �������  : ClientId    - APP/AT��ʶ
             OpId        - ������ʶ
             AttachType  - ��������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��8��25��
    ��    ��   : liuyang
    �޸�����   :V200R001�汾 �����ɺ���
  2.��    ��   : 2007��10��16��
    ��    ��   : F62575
    �޸�����   : ���ⵥA32D13062(�ĵ�У�Է�������)

*****************************************************************************/
TAF_UINT32 Taf_PhoneAttach ( MN_CLIENT_ID_T     ClientId,
                             MN_OPERATION_ID_T  OpId,
                             TAF_PH_ATTACH_TYPE AttachType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_ATTACH,
                                   &AttachType,
                                   sizeof(TAF_PH_ATTACH_TYPE),
                                   I0_WUEPS_PID_MMA);
}

/**********************************************************
 Function:       Taf_PhonePlmnList
 Description:    ����PLMN����
 Calls:          APP/AT
 Data Accessed:  2005-09-16
 Data Updated:
 Input:          ClientId - APP/AT��ʶ
                 OpId     - ������ʶ
                 ListType - ��������
 Output:
 Return:         TAF_SUCCESS - �ɹ�
                 TAF_FAILURE - ʧ��
 Others:
    1.Date        : 2007-10-16
    Author      : F62575
    Modification: ���ⵥA32D13062(�ĵ�У�Է�������)
**********************************************************/
TAF_UINT32 Taf_PhonePlmnList ( MN_CLIENT_ID_T           ClientId,
                               MN_OPERATION_ID_T        OpId,
                               TAF_AVAIL_PLMN_LIST_TYPE ListType)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_LIST,
                                   &ListType,
                                   sizeof(TAF_AVAIL_PLMN_LIST_TYPE),
                                   I0_WUEPS_PID_MMA);
}

/* Added by l00171473 for V7R1C50_At_Abort, 2012-9-19, begin */

/*****************************************************************************
 �� �� ��  : Taf_AbortPlmnList
 ��������  : AT��MMA�������б��ѵ�����
 �������  : ClientId
             OpId
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��19��
    ��    ��   : l00171473
    �޸�����   : ��������,AT��MMA�������б��ѵ�����

*****************************************************************************/
VOS_UINT32 TAF_AbortPlmnListReq (
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_PLMN_LIST_ABORT_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA );
}

/* Added by l00171473 for V7R1C50_At_Abort, 2012-9-19, end */


/* Deleted by w00167002 for L-C��������Ŀ, 2014-2-17, begin */

/* Deleted by w00167002 for L-C��������Ŀ, 2014-2-17, end */
/*****************************************************************************
 �� �� ��  : Taf_PhoneStartInfoInd
 ��������  : ��������������ϱ���Ϣ���ú��������趨�Ƿ��ϱ��ź�������С��ID����Ϣ��
             ����ϵͳ��Ϣ�����¼��ж����óɹ����
 �������  : stStartInfoInd -- �ο��ӿڶ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32 -- 0:���óɹ�
                           1:����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��12��13��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���
  2.��    ��   : 2007��10��16��
    ��    ��   : F62575
    �޸�����   : ���ⵥA32D13062(�ĵ�У�Է�������)
*****************************************************************************/
TAF_UINT32 Taf_PhoneStartInfoInd ( MN_CLIENT_ID_T          ClientId,
                                   MN_OPERATION_ID_T       OpId,
                                   TAF_START_INFO_IND_STRU StartInfoInd)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_INFO_REPORT,
                                   &StartInfoInd,
                                   sizeof(TAF_START_INFO_IND_STRU),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 �� �� ��  : TAF_DefQuickStart
 ��������  : ���ÿ��ٿ���
 �������  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
             TAF_UINT32 ulSetValue
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��9��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 TAF_DefQuickStart(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, TAF_UINT32 ulSetValue)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_SET_QUICKSTART,
                                   &ulSetValue,
                                   sizeof(TAF_UINT32),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 �� �� ��  : Taf_DefPhAutoAttach
 ��������  : �����Զ�ע��
 �������  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
             TAF_UINT32 ulSetValue
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��02��19��
    ��    ��   : x00115505
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 Taf_DefPhAutoAttach(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, TAF_UINT32 ulSetValue)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_SET_AUTOATTACH,
                                   &ulSetValue,
                                   sizeof(TAF_UINT32),
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 �� �� ��  : TAF_DefLoadDefault
 ��������  : �ָ���������
 �������  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��22��
    ��    ��   : H59254
    �޸�����   : creat function
*****************************************************************************/
TAF_UINT32 TAF_DefLoadDefault(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_SET_LOADDEFAULT,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA);
}

/*****************************************************************************
 �� �� ��  : Taf_UsimRestrictedAccessCommand
 ��������  : ����֧�������ƵĿ���������
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��10��25��
    ��    ��   : h59254
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 Taf_UsimRestrictedAccessCommand(MN_CLIENT_ID_T               ClientId,
                                           MN_OPERATION_ID_T            OpId,
                                           TAF_SIM_RESTRIC_ACCESS_STRU *pPara)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_USIM_RESTRICTED_ACCESS,
                                   pPara,
                                   sizeof(TAF_SIM_RESTRIC_ACCESS_STRU),
                                   I0_WUEPS_PID_MMA);
}



/*****************************************************************************
 �� �� ��  : Taf_IndPhFreq
 ��������  : ָ��Ƶ������
 �������  : MN_CLIENT_ID_T ClientId
             MN_OPERATION_ID_T   OpId
             TAF_IND_FREQ_STRU Freq
 �������  : TAF_SUCCESS or TAF_FAILURE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��10��24��
    ��    ��   : x51137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Taf_IndPhFreq(MN_CLIENT_ID_T     ClientId,
                         MN_OPERATION_ID_T        OpId,
                         TAF_IND_FREQ_STRU        Freq)
{
    VOS_UINT16 temp_Freq;
    VOS_UINT16 temp_value;

    switch (Freq.RatType)
    {
    case TAF_SYS_SUBMODE_GSM:
        temp_value   = Freq.GsmBand;
        temp_value <<= 12;
        temp_Freq   = temp_value;
        temp_value  = Freq.IndFreq;
        temp_value &= 0x0fff;
        temp_Freq |= temp_value;

        /* write temp_GSM_Freq to NVIM */
        if (NV_OK != NV_Write( en_NV_Item_Gsm_Ind_Freq, &temp_Freq, sizeof(VOS_UINT16)))
        {
            return TAF_FAILURE;
        }

        break;

    case TAF_SYS_SUBMODE_WCDMA:

        /*write Freq to NVIM */
        temp_Freq = Freq.IndFreq;
        if (NV_OK != NV_Write( en_NV_Item_Wcdma_Ind_Freq, &temp_Freq, sizeof(VOS_UINT16)))
        {
            return TAF_FAILURE;
        }

        break;

    default:
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : Taf_FplmnHandle
 ��������  : FPLMNͨ�ò�������
 �������  :  ClientId  - APP/AT��ʶ
              OpId      - ������ʶ
              PhModeSet - �ֻ�����ģʽ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
1.��    ��   : 2007��10��9��
  ��    ��   : luojian id:107747
  �޸�����   : �����ɺ�����A32D13994
*****************************************************************************/
TAF_UINT32 Taf_FplmnHandle(MN_CLIENT_ID_T            ClientId,
                           MN_OPERATION_ID_T         OpId,
                           TAF_PH_FPLMN_OPERATE_STRU stFplmnOperate)
{
    return MN_FillAndSndAppReqMsg( ClientId,
                                   OpId,
                                   TAF_MSG_MMA_FPLMN_HANDLE,
                                   &stFplmnOperate,
                                   sizeof(TAF_PH_FPLMN_OPERATE_STRU),
                                   I0_WUEPS_PID_MMA);
}

/* Modified by z00161729 for V7R1 phase II , 2011-06-29, begin */
/*****************************************************************************
 �� �� ��  : Taf_SysCfgHandle
 ��������  : ����syscfg����
 �������  : TAF_CLIENT_ID        ClientId
             TAF_ID OpId
             TAF_PH_SYS_CFG_STRU    stSysCfg
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��11��10��
    ��    ��   : l00130025
    �޸�����   : ���ⵥAT2D06577,���Բ�֧�����ε����÷ŵ�MMC���
  3.��    ��   : 2011��07��05��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase II for syscfgex
  4.��    ��   : 2014��2��13��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:����SYSCFG�����ò�ѯ�ӿ�
*****************************************************************************/

/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, begin */
VOS_UINT32 Taf_SysCfgHandle(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfg
)
{

    return MN_FillAndSndAppReqMsg(ClientId,
                                  OpId,
                                  TAF_MSG_MMA_SYSCFG_QUERY_REQ,
                                  &stSysCfg,
                                  sizeof(stSysCfg),
                                  I0_WUEPS_PID_MMA);
}
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, end */

/* Modified by z00161729 for V7R1 phase II , 2011-06-29, end */

/* Added by w00242748 for NETSCAN, 2013-10-15, begin */
/*****************************************************************************
 �� �� ��  : Taf_NetScanHandle
 ��������  : ����netscan����
 �������  : TAF_CLIENT_ID        ClientId
             TAF_ID OpId
             TAF_MMA_NET_SCAN_REQ_STRU    pstNetScan
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��15��
    ��    ��   : w00167002
    �޸�����   : �ɼ��̹淶�޸�
*****************************************************************************/

/* Modified by w00167002 for NETSCAN, 2013-11-11, begin */
VOS_UINT32 Taf_NetScanHandle(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScan
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_NET_SCAN_REQ,
                                  pstNetScan,
                                  sizeof(TAF_MMA_NET_SCAN_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}
/* Modified by w00167002 for NETSCAN, 2013-11-11, end */


/* Modified by c00318887 for file refresh��Ҫ����������, 2015-3-9, begin */
/*****************************************************************************
 �� �� ��  : TAF_SetRefreshStub
 ��������  : ģ��pih��ָ��ģ�鷢��refresh��Ϣ
 �������  : TAF_CLIENT_ID        ClientId
             TAF_ID OpId
             TAF_MMA_REFRESH_STUB_SET_REQ_STRU  *pstRefreshStub
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��31��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_UINT32 TAF_SetRefreshStub(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_MMA_REFRESH_STUB_SET_REQ_STRU  *pstRefreshStub
)
{
    return MN_FillAndSndAppReqMsg(usClientId,
                                  ucOpId,
                                  TAF_MSG_MMA_REFRESH_STUB_SET_REQ,
                                  pstRefreshStub,
                                  sizeof(TAF_MMA_REFRESH_STUB_SET_REQ_STRU),
                                  I0_WUEPS_PID_MMA);
}

/* Modified by c00318887 for file refresh��Ҫ����������, 2015-3-9, end */

/*****************************************************************************
 �� �� ��  : Taf_AbortNetScan
 ��������  : AT��MMA������NetScan������
 �������  : ClientId
             OpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : w00242748
    �޸�����   : ��������,AT��MMA������NETSCAN������
  2.��    ��   : 2013��10��15��
    ��    ��   : w00167002
    �޸�����   : �ɼ��̹淶�޸�
*****************************************************************************/

/* Modified by w00167002 for NETSCAN, 2013-11-11, begin */
VOS_UINT32 Taf_AbortNetScan (
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
)
{
    return MN_FillAndSndAppReqMsg( usClientId,
                                   ucOpId,
                                   TAF_MSG_MMA_ABORT_NET_SCAN_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA );
}
/* Modified by w00167002 for NETSCAN, 2013-11-11, end */

/* Added by w00242748 for NETSCAN, 2013-10-15, end */

/*****************************************************************************
 �� �� ��  : TAF_QryUsimInfo
 ��������  :
 �������  :
 �������  : Icctype
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��9��19��
    ��    ��   : z40661
    �޸�����   : ��������,��ѯUSIM���������Ϣ

*****************************************************************************/
TAF_UINT32 TAF_QryUsimInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    if ( (TAF_PH_ICC_UNKNOW == pstInfo->Icctype)
      || (pstInfo->Icctype > TAF_PH_ICC_USIM))
    {
        return TAF_FAILURE;
    }

    if (pstInfo->enEfId > TAF_PH_OPL_FILE)
    {
        return TAF_FAILURE;
    }
    return MN_FillAndSndAppReqMsg( ClientId,
                             OpId,
                             TAF_MSG_MMA_USIM_INFO,
                             pstInfo,
                             sizeof(TAF_PH_QRY_USIM_INFO_STRU),
                             I0_WUEPS_PID_MMA);

}

/*****************************************************************************
 �� �� ��  : TAF_QryCpnnInfo
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��9��19��
    ��    ��   : z40661
    �޸�����   : ��������,��ѯUSIM���������Ϣ

*****************************************************************************/
TAF_UINT32 TAF_QryCpnnInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_ICC_TYPE                     IccType
)
{
    if ( (TAF_PH_ICC_UNKNOW == IccType)
      || (IccType > TAF_PH_ICC_USIM))
    {
        return TAF_FAILURE;
    }

    return MN_FillAndSndAppReqMsg( ClientId,
                             OpId,
                             TAF_MSG_MMA_CPNN_INFO,
                             &IccType,
                             sizeof(IccType),
                             I0_WUEPS_PID_MMA);
}

/* Added by s00190137 for ACC&SPLMN, 2013-10-15 Begin */
/*****************************************************************************
 �� �� ��  : Taf_SetEOPlmnHandle
 ��������  : ����EOPLMN����
 �������  : TAF_CLIENT_ID        ClientId
             TAF_ID OpId
             TAF_MMA_SET_EOPLMN_LIST_STRU        *pstEOPlmnCfg
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Taf_SetEOPlmnHandle(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnCfg
)
{

    return MN_FillAndSndAppReqMsg(ClientId,
                                  OpId,
                                  TAF_MSG_MMA_EOPLMN_SET_REQ,
                                  pstEOPlmnCfg,
                                  sizeof(TAF_MMA_SET_EOPLMN_LIST_STRU),
                                  I0_WUEPS_PID_MMA);
}
/* Added by s00190137 for ACC&SPLMN, 2013-10-15 End */

/* Added by s00246516 for L-C��������Ŀ, 2014-01-29, Begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_PhoneModeSetReq
 ��������  : �ֻ�ģʽ���ýӿ�
 �������  : ulModuleId       ---  �ⲿģ��PID
             usCliendId       ---  �ⲿģ��CliendId
             ucOpId           ---  �ⲿģ��OpId
             pstPhoneModePara ---  Phone mode���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_PhoneModeSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PHONE_MODE_PARA_STRU       *pstPhoneModePara
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (VOS_NULL_PTR == pstPhoneModePara)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_PHONE_MODE_SET_REQ_STRU */
    pstMsg = (TAF_MMA_PHONE_MODE_SET_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                       ulSenderPid,
                                       sizeof(TAF_MMA_PHONE_MODE_SET_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_PHONE_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverPid               = ulReceiverPid;
    pstMsg->ulMsgName                   = ID_TAF_MMA_PHONE_MODE_SET_REQ;
    pstMsg->stCtrl.ulModuleId           = ulModuleId;
    pstMsg->stCtrl.usClientId           = usClientId;
    pstMsg->stCtrl.ucOpId               = ucOpId;
    PS_MEM_CPY(&(pstMsg->stPhoneModePara), pstPhoneModePara, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetSysCfgReq
 ��������  : �ֻ�ϵͳ���ýӿ�
 �������  : ulModuleId      ---  �ⲿģ��PID
            : usCliendId     ---  �ⲿģ��CliendId
            ucOpId           ---  �ⲿģ��OpId
            pstSysCfgPara    ---  Sys Cfg���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_SetSysCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (VOS_NULL_PTR == pstSysCfgPara)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_SYS_CFG_REQ_STRU */
    pstMsg = (TAF_MMA_SYS_CFG_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_SYS_CFG_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_SYS_CFG_REQ_STRU */
    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_SYS_CFG_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&(pstMsg->stSysCfgPara), pstSysCfgPara, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_AcqBestNetworkReq
 ��������  : ��ȡ����ӿ�
 �������  : ulModuleId      ---  �ⲿģ��PID
            : usCliendId     ---  �ⲿģ��CliendId
            ucOpId           ---  �ⲿģ��OpId
            pstAcqPara       ---  Acq���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_AcqBestNetworkReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_ACQ_PARA_STRU              *pstAcqPara
)
{
    TAF_MMA_ACQ_REQ_STRU               *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (VOS_NULL_PTR == pstAcqPara)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_ACQ_REQ_STRU */
    pstMsg = (TAF_MMA_ACQ_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_ACQ_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_ACQ_BEST_NETWORK_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    PS_MEM_CPY(&(pstMsg->stAcqPara), pstAcqPara, sizeof(TAF_MMA_ACQ_PARA_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RegReq
 ��������  : ע������ӿ�
 �������  : ulModuleId      ---  �ⲿģ��PID
            : usCliendId     ---  �ⲿģ��CliendId
            ucOpId           ---  �ⲿģ��OpId
            pstRegPara       ---  REG���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RegReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_REG_PARA_STRU              *pstRegPara
)
{
    TAF_MMA_REG_REQ_STRU               *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (VOS_NULL_PTR == pstRegPara)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_REG_REQ_STRU */
    pstMsg = (TAF_MMA_REG_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ulSenderPid,
                                             sizeof(TAF_MMA_REG_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_REG_REQ_STRU */
    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_REG_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    PS_MEM_CPY(&(pstMsg->stRegPara), pstRegPara, sizeof(TAF_MMA_REG_PARA_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_PowerSaveReq
 ��������  : Power Save�ӿ�
 �������  : ulModuleId      ---  �ⲿģ��PID
            : usCliendId     ---  �ⲿģ��CliendId
            ucOpId           ---  �ⲿģ��OpId
            pstPowerSavePara ---  Power Save���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_PowerSaveReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_POWER_SAVE_PARA_STRU       *pstPowerSavePara
)
{

    TAF_MMA_POWER_SAVE_REQ_STRU        *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (VOS_NULL_PTR == pstPowerSavePara)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_POWER_SAVE_REQ_STRU */
    pstMsg = (TAF_MMA_POWER_SAVE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_POWER_SAVE_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_POWER_SAVE_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    PS_MEM_CPY(&(pstMsg->stPowerSavePara), pstPowerSavePara, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_DetachReq
 ��������  : Detach�ӿ�
 �������  : ulModuleId      ---  �ⲿģ��PID
            : usCliendId     ---  �ⲿģ��CliendId
            ucOpId           ---  �ⲿģ��OpId
            pstDetachPara    ---  Detach���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_DetachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_DETACH_PARA_STRU           *pstDetachPara
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (VOS_NULL_PTR == pstDetachPara)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_DETACH_REQ_STRU */
    pstMsg = (TAF_MMA_DETACH_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_DETACH_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_DETACH_REQ_STRU */
    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_DETACH_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    PS_MEM_CPY(&(pstMsg->stDetachPara), pstDetachPara, sizeof(TAF_MMA_DETACH_PARA_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-29, End */

#if(FEATURE_ON == FEATURE_DSDS)
/* Modified by w00242748 for DSDS III, 2014-6-17, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SrvAcqReq
 ��������  : SPMģ���MMAģ�鷢������ָʾ
 �������  : enSrvType:��������
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��17��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_SrvAcqReq(
    TAF_MMA_SRV_TYPE_ENUM_UINT8         enSrvType
)
{
    TAF_MMA_SRV_ACQ_REQ_STRU           *pstMsg  = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_SRV_ACQ_REQ_STRU */
    pstMsg = (TAF_MMA_SRV_ACQ_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_TAF,
                                             sizeof(TAF_MMA_SRV_ACQ_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SRV_ACQ_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ����PIDͳһ��дΪWUEPS_PID_TAF */
    pstMsg->ulSenderPid       = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid     = WUEPS_PID_MMA;
    pstMsg->ulMsgName         = ID_TAF_MMA_SRV_ACQ_REQ;
    pstMsg->enSrvType         = enSrvType;


    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/* Modified by w00242748 for DSDS III, 2014-6-17, end */
#endif

/* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, Begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_SetImsSwitchReq
 ��������  : IMSSwitch�ӿ�
 �������  : ulModuleId     ---  �ⲿģ��PID
             usCliendId     ---  �ⲿģ��CliendId
             ucOpId         ---  �ⲿģ��OpId
             ucImsSwitch    ---  IMS ״̬���ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_SetImsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_IMS_SWITCH_SET_ENUM_UINT8   enImsSwitch
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if ((TAF_MMA_IMS_SWITCH_SET_POWER_OFF != enImsSwitch)
     && (TAF_MMA_IMS_SWITCH_SET_POWER_ON  != enImsSwitch))
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_IMS_SWITCH_SET_REQ_STRU */
    pstMsg = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_IMS_SWITCH_SET_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SWITCH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_IMS_SWITCH_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_SWITCH_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enImsSwitch       = enImsSwitch;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_QryImsSwitchReq
 ��������  : IMSSwitch�ӿ�
 �������  : ulModuleId     ---  �ⲿģ��PID
             usCliendId     ---  �ⲿģ��CliendId
             ucOpId         ---  �ⲿģ��OpId
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_QryImsSwitchReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_IMS_SWITCH_QRY_REQ_STRU    *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif


    /* ������Ϣ��TAF_MMA_IMS_SWITCH_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_IMS_SWITCH_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_IMS_SWITCH_QRY_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_IMS_SWITCH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_IMS_SWITCH_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_IMS_SWITCH_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetVoiceDomainReq
 ��������  : VoiceDomain�ӿ�
 �������  : ulModuleId       ---  �ⲿģ��PID
             usCliendId       ---  �ⲿģ��CliendId
             ucOpId           ---  �ⲿģ��OpId
             enVoiceDomain    ---  ���������ò���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_SetVoiceDomainReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU  *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������� */
    if (enVoiceDomain >= TAF_MMA_VOICE_DOMAIN_BUTT)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU */
    pstMsg = (TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_VOICE_DOMAIN_SET_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;
    pstMsg->enVoiceDomain     = enVoiceDomain;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_QryVoiceDomainReq
 ��������  : VoiceDomain�ӿ�
 �������  : ulModuleId      ---  �ⲿģ��PID
             usCliendId      ---  �ⲿģ��CliendId
             ucOpId          ---  �ⲿģ��OpId
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ɹ�,VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_QryVoiceDomainReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU  *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSenderPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    ulReceiverPid = AT_GetDestPid(usClientId, WUEPS_PID_MMA);
    ulSenderPid   = AT_GetDestPid(usClientId, WUEPS_PID_TAF);
#else
    ulReceiverPid = WUEPS_PID_MMA;
    ulSenderPid   = WUEPS_PID_TAF;
#endif

    /* ������Ϣ��TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU */
    pstMsg = (TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           ulSenderPid,
                                           sizeof(TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU */
    pstMsg->ulSenderPid       = ulSenderPid;
    pstMsg->ulReceiverPid     = ulReceiverPid;
    pstMsg->ulMsgName         = ID_TAF_MMA_VOICE_DOMAIN_QRY_REQ;
    pstMsg->stCtrl.ulModuleId = ulModuleId;
    pstMsg->stCtrl.usClientId = usClientId;
    pstMsg->stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSenderPid, pstMsg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif
/* Added by zwx247453 for VOLTE SWITCH, 2015-02-02, End */
/*lint +e958*/

#ifdef  __cplusplus
 #if  __cplusplus
}
 #endif
#endif
