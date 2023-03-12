/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasOmTrans.h
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��04��27��
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : �����ļ�, DTS2011102200898, ����TRANS��Ϣ��EVENT��Ϣ�Ķ����ṹ��ͬ, 
                 Ϊ��ASN����TRANS��Ϣ, ����ͷ�ļ��е�TRANS��Ϣ��ز�����ȡ��������
                 NasOmTrans.h ��

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
#include  "MmcLmmInterface.h"
/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */
#ifndef __NASOMTRANS_H__
#define __NASOMTRANS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define LEN_PTMSI                       4
#define LEN_TMSI                        4


#define LEN_MOBILE                      16

#define MAX_AVAILABEL_PLMN_NUM          16

#define NAS_OM_PDP_CONTEXT_MAX          11                                      /* ����PDP�����ĵĸ��� */

#define SM_MAX_LENGTH_OF_APN            101
#define SM_IP_ADDR_LEN                  4
#define SM_IPV6_ADDR_LEN                16

/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
#define NAS_MS_ID_GUTI_VALID            (1)
#define NAS_MS_ID_PTMSI_IMSI_VALID      (2)
#define NAS_MAX_TIMER_EVENT             (100)
#define NAS_MAX_IMSI_LEN                (9)
/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */
/*����NAS��OM֮���TRANS_PRIMID*/
#define NAS_OM_TRANS_PRIMID             0x5001


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_OM_TRANS_MSG_TYPE_ENUM
 �ṹ˵��  : NAS͸����Ϣ����ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, ����TRANS��Ϣ��ؽṹ������ͷ�ļ�, ��֧��ANS����

 2.��    ��   : 2012��11��06��
   ��    ��   : l00198894
   �޸�����   : Probe·�⹤�߶Խ���Ŀ��������ҵ�������Ϣ
*****************************************************************************/
enum NAS_OM_TRANS_MSG_TYPE_ENUM
{
    ID_NAS_OM_MM_INQUIRE                                    = 0xC001,
    ID_NAS_OM_MM_CONFIRM                                    = 0xC002,   /*_H2ASN_MsgChoice NAS_OM_MM_CONFIRM_STRU*/
    
    ID_NAS_OM_QOS_INQUIRE                                   = 0xC003,
    ID_NAS_OM_QOS_CONFIRM                                   = 0xC004,   /*_H2ASN_MsgChoice NAS_QOS_STRUCT*/
    
    ID_NAS_OM_PDP_CONTEXT_INQUIRE                           = 0xC005,
    ID_NAS_OM_PDP_CONTEXT_CONFIRM                           = 0xC006,   /*_H2ASN_MsgChoice NAS_OM_PDP_CONTEXT_STRU*/

    /*����GSM CODEC���͵�����*/
    ID_NAS_OM_SET_CODEC_TYPE_REQUIRE                        = 0xC007,   /*_H2ASN_MsgChoice NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU*/ 
    ID_NAS_OM_SET_CODEC_TYPE_CONFIRM                        = 0xC008,   /*_H2ASN_MsgChoice NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU*/

    /*���ӵ�ǰʹ��CODEC���ͺ�GSM CODEC���ϵĲ�ѯ*/
    ID_NAS_OM_CODEC_TYPE_INQUIRE                            = 0xC009,
    ID_NAS_OM_CODEC_TYPE_CONFIRM                            = 0xC00a,   /*_H2ASN_MsgChoice NAS_OM_CURR_CODEC_TYPE_ENUM_U8*/

    /* Added by l00198894 for PROBE Project, 2012/11/06, begin */
    /* ��ѯ����ҵ�����������ʵ� */
    ID_NAS_OM_SET_DSFLOW_RPT_REQ                            = 0xC00B,   /*_H2ASN_MsgChoice NAS_OM_SET_DSFLOW_RPT_REQ_STRU*/
    ID_NAS_OM_SET_DSFLOW_RPT_CNF                            = 0xC00C,   /*_H2ASN_MsgChoice NAS_OM_SET_DSFLOW_RPT_CNF_STRU*/
    ID_NAS_OM_DSFLOW_RPT_IND                                = 0xC00D,   /*_H2ASN_MsgChoice NAS_OM_DSFLOW_RPT_IND_STRU*/
    /* Added by l00198894 for PROBE Project, 2012/11/06, end */

    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    ID_NAS_OM_SMS_INQUIRE                                   = 0xC00E,
    ID_NAS_OM_SMS_CONFIRM                                   = 0xC00F,   

    ID_NAS_OM_CONFIG_TIMER_REPORT_REQ                       = 0xC010,
    ID_NAS_OM_CONFIG_TIMER_REPORT_CNF                       = 0xC011,  
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */

    ID_NAS_OM_TRANS_BUTT
};

typedef VOS_UINT16 NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : NAS_OM_MM_STATE_ENUM
 �ṹ˵��  : MM ״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, ����TRANS��Ϣ��ؽṹ������ͷ�ļ�, ��֧��ANS����
*****************************************************************************/
enum NAS_OM_MM_STATE_ENUM
{
    STATE_MM_NULL                                           = 0,
    STATE_MM_IDLE                                           = 1,
    WAIT_FOR_OUTGOING_MM_CONNECT                            = 9,
    MM_CONNECT_ACT                                          = 10,
    WAIT_FOR_NET_COMMAND                                    = 11,
    WAIT_FOR_RR_CONNECT_MM_CONNECT                          = 12,
    WAIT_FOR_REEST_WAIT_FOR_REEST_REQ                       = 13,
    WAIT_FOR_REEST_WAIT_FOR_EST_CNF                         = 14,
    WAIT_FOR_RR_ACT                                         = 15,
    WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECT                 = 16,
    LOCATION_UPDATING_PEND                                  = 17,
    IMSI_DETACH_PEND                                        = 18,
    MM_WAIT_FOR_ATTCH                                       = 19,
    WAIT_FOR_RR_CONNECT_LOCATION_UPDATING                   = 22,
    LU_INITIATED                                            = 23,
    LU_REJECTED                                             = 24,
    WAIT_FOR_RR_CONNECT_IMSI_DETACH                         = 25,
    IMSI_DETACH_INITIATE                                    = 26,
    PROCESS_CM_SERV_PROMPT                                  = 27,
    TEST_CONTROL_ACT                                        = 31,
    MM_INTER_RAT_CHG                                        = 32,
    MM_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_MM_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MM_UPDATE_STATUS_ENUM
 �ṹ˵��  : MM UPDATE ״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, ����TRANS��Ϣ��ؽṹ������ͷ�ļ�, ��֧��ANS����
 2.��    ��   : 2014��6��16��
   ��    ��   : w00176964
   �޸�����   : DTS2014061006131:MM�����µ�Uֵ
*****************************************************************************/
enum MM_UPDATE_STATUS_ENUM
{
    UPDATE_STATUS_U1                    = 0,                                    /* U1 */
    UPDATE_STATUS_U2                    = 1,                                    /* U2 */
    UPDATE_STATUS_U3                    = 2,                                    /* U3 */
    /* Added by w00176964 for DTS2014061006131, 2014-6-16, begin */    
    UPDATE_STATUS_U4                    = 3,                                    /* U4 */
    /* Added by w00176964 for DTS2014061006131, 2014-6-16, end */
    MM_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 MM_UPDATE_STATUS_ENUM_UINT8;

/* ���¶���ö�ٺ���MS VisualStudio �ж����ͻ��ע��ֵ��ͬ����Ӱ�� */
#ifdef __NAS_OM_UT__
#ifdef DEREGISTERED
#undef DEREGISTERED
#endif
#ifdef REGISTERED
#undef REGISTERED
#endif
#endif

/*****************************************************************************
 ö����    : NAS_OM_GMM_STATE_ENUM
 �ṹ˵��  : GMM ״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, ����TRANS��Ϣ��ؽṹ������ͷ�ļ�, ��֧��ANS����
*****************************************************************************/
enum NAS_OM_GMM_STATE_ENUM
{
    STATE_GMM_NULL                      = 0x00,
    REGISTERED_INITIATED                = 0x01,
    DEREGISTERED_INITIATED              = 0x02,
    ROUTING_AREA_UPDATING_INITIATED     = 0x03,
    SERVICE_REQUEST_INITIATED           = 0x04,
    TC_ACTIVE                           = 0x05,
    GPRS_SUSPENSION                     = 0x06,
    DEREGISTERED                        = 0x10,
    REGISTERED                          = 0X20,
    SUSPENDED_NORMAL_SERVICE            = 0x30,
    SUSPENDED_GPRS_SUSPENSION           = 0x31,
    SUSPENDED_WAIT_FOR_SYSINFO          = 0x32,
    GMM_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_GMM_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GMM_UPDATE_STATUS_ENUM
 �ṹ˵��  : GMM UPDATE ״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
*****************************************************************************/
enum GMM_UPDATE_STATUS_ENUM
{
    UPDATE_STATUS_GU1                   = 0,                                    /* GU1 */
    UPDATE_STATUS_GU2                   = 1,                                    /* GU2 */
    UPDATE_STATUS_GU3                   = 2,                                    /* GU3 */
    GMM_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 GMM_UPDATE_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : PLMN_SEL_MODE_ENUM
 �ṹ˵��  : ѡ��ģʽö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
*****************************************************************************/
enum PLMN_SEL_MODE_ENUM
{
    PLMN_SEL_MODE_AUTO                  = 0,
    PLMN_SEL_MODE_MANUAL                = 1,
    PLMN_SEL_MODE_BUTT
};
typedef VOS_UINT8 PLMN_SEL_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : UE_OPERATE_MODE_ENUM
 �ṹ˵��  : ѡ��ģʽ
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
*****************************************************************************/
enum UE_OPERATE_MODE_ENUM
{
    UE_OPERATE_MODE_NULL                = 0,
    UE_OPERATE_MODE_A                   = 1,
    UE_OPERATE_MODE_CG                  = 2,
    UE_OPERATE_MODE_CC                  = 3,
    UE_OPERATE_MODE_B                   = 4,
    UE_OPERATE_MODE_BUTT
};
typedef VOS_UINT8 UE_OPERATE_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NET_OPERATE_MODE_ENUM
 �ṹ˵��  : ����ģʽö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
*****************************************************************************/
enum NET_OPERATE_MODE_ENUM
{
    NET_OPERATE_MODE_1                  = 0,
    NET_OPERATE_MODE_2                  = 1,
    NET_OPERATE_MODE_3                  = 2,
    NET_OPERATE_MODE_BUTT
};
typedef VOS_UINT8 NET_OPERATE_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NET_TYPE_ENUM
 �ṹ˵��  : ����ģʽö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
*****************************************************************************/
enum NET_TYPE_ENUM
{
    NET_TYPE_GSM                        = 0,
    NET_TYPE_WCDMA                      = 1,
    NET_TYPE_LTE                        = 2,
    NET_TYPE_BUTT
};
typedef VOS_UINT8 NET_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_OM_MM_SUB_STATE_ENUM
 �ṹ˵��  : MM ��״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
 2.��    ��   : 2014��6��16��
   ��    ��   : w00176964
   �޸�����   : DTS2014061006131:MM�����µ�Э��״̬
*****************************************************************************/
enum NAS_OM_MM_SUB_STATE_ENUM
{
    NO_CELL_AVAILABLE                   = 1,
    PLMN_SEARCH                         = 2,
    NORMAL_SERVICE                      = 3,
    LIMITED_SERVICE                     = 4,
    ATTEMPTING_TO_UPDATE                = 5,
    LOCATION_UPDATE_NEEDED              = 6,
    PLMN_SEARCH_NORMAL_SERVICE          = 7,
    NO_IMSI                             = 8,
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-6-11, begin */
    ECALL_INACTIVE                      = 9,
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-6-11, end */
    MM_SUB_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_MM_SUB_STATE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_OM_GMM_SUB_STATE_ENUM
 �ṹ˵��  : GMM ��״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : DTS2011102200898, Ϊ��TRANS��Ϣ��ANS����, ����ͷ�ļ�
*****************************************************************************/
enum NAS_OM_GMM_SUB_STATE_ENUM
{
    DEREGISTERED_NORMAL_SERVICE         = 0x10,
    DEREGISTERED_LIMITED_SERVICE        = 0x11,
    DEREGISTERED_ATTACH_NEEDED          = 0x12,
    DEREGISTERED_ATTEMPTING_TO_ATTACH   = 0x13,
    DEREGISTERED_NO_CELL_AVAILABLE      = 0x14,
    DEREGISTERED_PLMN_SEARCH            = 0x15,
    DEREGISTERED_NO_IMSI                = 0x16,
    REGISTERED_NORMAL_SERVICE           = 0x20,
    REGISTERED_LIMITED_SERVICE          = 0x21,
    REGISTERED_UPDATE_NEEDED            = 0x22,
    REGISTERED_ATTEMPTING_TO_UPDATE     = 0x23,
    REGISTERED_NO_CELL_AVAILABLE        = 0x24,
    REGISTERED_PLMN_SEARCH              = 0x25,
    REGISTERED_ATTEMPTING_TO_UPDATE_MM  = 0x26,
    REGISTERED_IMSI_DETACH_INITIATED    = 0x27,
    REGISTERED_WAIT_FOR_RAU             = 0x28,
    GMM_SUB_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_GMM_SUB_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_OM_SERVICE_STATE_ENUM
 �ṹ˵��  : ����״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : 
*****************************************************************************/
enum NAS_OM_SERVICE_STATE_ENUM
{
    NAS_OM_SERVICE_STATE_NO_SERVICE                         = 0,                /* �޷���״̬       */
    NAS_OM_SERVICE_STATE_LIMITED_SERVICE                    = 1,                /* ���Ʒ���״̬     */
    NAS_OM_SERVICE_STATE_NORMAL_SERVICE                     = 2,                /* ��������״̬     */
    NAS_OM_SERVICE_STATE_REGIONAL_LIMITED_SERVICE           = 3,                /* �����Ƶ�������� */
    NAS_OM_SERVICE_STATE_DEEP_SLEEP                         = 4,                /* ʡ�����˯��״̬ */
    NAS_OM_SERVICE_STATE_BUTT
};
typedef VOS_UINT8 NAS_OM_SERVICE_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_OM_PDP_ACT_TYPE_ENUM
 �ṹ˵��  : PDP��������ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : 
*****************************************************************************/
enum NAS_OM_PDP_ACT_TYPE_ENUM
{
    NAS_OM_PDP_ACT_PRI                  = 0,                                    /* ������PDP */
    NAS_OM_PDP_ACT_SEC,                                                         /* ���μ���PDP */
    NAS_OM_PDP_ACT_BUTT                 = 0xFF
};
typedef VOS_UINT8 NAS_OM_PDP_ACT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_OM_CURR_CODEC_TYPE_ENUM
 �ṹ˵��  : CODEC����ö��
             ��ǰʹ�õ�CODEC����,����CALLģ�鶨���һ��Ŀ����Ϊ��ƥ���ϱ������õĵ�ǰGSM֧�ֵ�CODEC����
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : 
*****************************************************************************/
enum NAS_OM_CURR_CODEC_TYPE_ENUM
{
    NAS_OM_CODEC_TYPE_FR                = 0x01,                                 /* full rate */
    NAS_OM_CODEC_TYPE_HR                = 0x02,                                 /* half rate */
    NAS_OM_CODEC_TYPE_EFR               = 0x04,                                 /* enhanced full rate */
    NAS_OM_CODEC_TYPE_AMR               = 0x08,                                 /* amr */
    NAS_OM_CODEC_TYPE_AMR2              = 0x10,                                 /* amr2 */
    
    /* Modified by z40661 for AMR-WB , 2012-02-09, end */
    NAS_OM_CODEC_TYPE_AMRWB             = 0x20,                                 /* amr2 */
    /* Modified by z40661 for AMR-WB , 2012-02-09, end */

    NAS_OM_CODEC_TYPE_BUTT                                                      /* invalid value */
};
typedef VOS_UINT8 NAS_OM_CURR_CODEC_TYPE_ENUM_U8;

/*****************************************************************************
 ö����    : NAS_OM_GSM_CODEC_CONFIG_ENUM
 �ṹ˵��  : GSM CODEC����ö��
 �޸���ʷ      :
 1.��    ��   : 2012��04��27��
   ��    ��   : L00171473
   �޸�����   : 
*****************************************************************************/
enum NAS_OM_GSM_CODEC_CONFIG_ENUM
{
    NAS_OM_GSM_CODEC_FR                 = 0x01,                                 /* FR */
    NAS_OM_GSM_CODEC_FR_HR              = 0x03,                                 /* FR+HR */
    NAS_OM_GSM_CODEC_FR_EFR             = 0x05,                                 /* FR+EFR */
    NAS_OM_GSM_CODEC_FR_AMR             = 0x09,                                 /* FR+AMR */
    NAS_OM_GSM_CODEC_FR_EFR_HR_AMR      = 0x0F,                                 /* FR+EFR+HR+AMR */
    NAS_OM_GSM_CODEC_BUTT
};
typedef VOS_UINT8 NAS_OM_GSM_CODEC_CONFIG_ENUM_U8;

/* Added by l00198894 for PROBE Project, 2012/11/06, begin */
/*******************************************************************************
 ö����    : NAS_OM_GMM_GPRS_STATE_ENUM
 �ṹ˵��  : GMM GPRS ״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��11��06��
   ��    ��   : l00198894
   �޸�����   : Probe·�⹤�߶Խ���Ŀ����ö��
*******************************************************************************/
enum NAS_OM_GMM_GPRS_STATE_ENUM
{
    NAS_OM_GMM_GPRS_IDLE                                    = 0x00,             /* GPRS����̬ */
    NAS_OM_GMM_GPRS_STANDBY                                 = 0x01,             /* GPRS�ȴ�̬ */
    NAS_OM_GMM_GPRS_READY                                   = 0x02,             /* GPRS����̬ */
    NAS_OM_GMM_GPRS_STATE_BUTT                              = 0xFF              /* GPRS״̬��Чֵ */
};
typedef VOS_UINT8 NAS_OM_GMM_GPRS_STATE_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_OM_REPORT_ACTION_ENUM
 �ṹ˵��  : NAS��OM�����ϱ�״̬ö��
 �޸���ʷ      :
 1.��    ��   : 2012��11��06��
   ��    ��   : l00198894
   �޸�����   : Probe·�⹤�߶Խ���Ŀ����ö��
*******************************************************************************/
enum NAS_OM_REPORT_ACTION_ENUM
{
    NAS_OM_REPORT_STOP                                      = 0x00,             /* ֹͣ�����ϱ� */
    NAS_OM_REPORT_START                                     = 0x01,             /* ���������ϱ� */

    NAS_OM_REPORT_BUTT
};
typedef VOS_UINT8 NAS_OM_REPORT_ACTION_ENUM_UINT8;

/*******************************************************************************
 ö����    : NAS_OM_RESULT_ENUM
 �ṹ˵��  : NAS��OM����������ö��
 �޸���ʷ      :
 1.��    ��   : 2012��11��06��
   ��    ��   : l00198894
   �޸�����   : Probe·�⹤�߶Խ���Ŀ����ö��
*******************************************************************************/
enum NAS_OM_RESULT_ENUM
{
    NAS_OM_RESULT_NO_ERROR                                  = 0,                /* ��Ϣ�������� */
    NAS_OM_RESULT_ERROR                                     = 1,                /* ��Ϣ������� */
    NAS_OM_RESULT_INCORRECT_PARAMETERS,

    NAS_OM_RESULT_BUTT
};
typedef VOS_UINT32 NAS_OM_RESULT_ENUM_UINT32;
/* Added by l00198894 for PROBE Project, 2012/11/06, end */

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*******************************************************************************
 �ṹ��    : MS_ID_STRUCT
 �ṹ˵��  : MS ID �ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           ucMobileIDValue[LEN_MOBILE];
    VOS_UINT8                           ucReserved[3];
}MS_ID_STRUCT;

/*******************************************************************************
 �ṹ��    : PLMN_ID_STRUCT
 �ṹ˵��  : PLMN ID �ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMccDigit[3];
    VOS_UINT8                           ucMncCount;
    VOS_UINT8                           aucMncDigit[3];
    VOS_UINT8                           ucReserved[1];
}PLMN_ID_STRUCT;

/*******************************************************************************
 �ṹ��    : AVAILABLE_PLMN_STRUCT
 �ṹ˵��  : AVAILABLE ID �ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    PLMN_ID_STRUCT                      Plmn;
    NET_TYPE_ENUM_UINT8                 ucRat;
    VOS_UINT8                           ucReserved[3];
}AVAILABLE_PLMN_STRUCT;

/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
/*****************************************************************************
 �ṹ����: NAS_GUMM_PTMSI_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: �� 24.008 10.5.1.4
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPtmsi[NAS_MAX_SIZE_PTMSI];
} NAS_OM_PTMSI_STRU;
/*******************************************************************************
 �ṹ��    : NAS_OM_MS_ID_STRU
 �ṹ˵��  : �ϱ�TINֵ�����ݽṹ
 �޸���ʷ      :
  1.��    ��   : 2013��06��26��
    ��    ��   : l00167671
    �޸�����   : DCM LOGGER��ν�ɲ�SMC SMR״̬�ϱ�
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsId;
    NAS_LMM_GUTI_STRU                   stGuti;
    NAS_OM_PTMSI_STRU                   stPtmsi;
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LEN];
}NAS_OM_MS_ID_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_SMS_CONFIRM_STRU
 �ṹ˵��  : ����OM��MM��Ϣ��͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2013��06��26��
    ��    ��   : l00167671
    �޸�����   : DCM LOGGER��ν�ɲ�SMC SMR״̬�ϱ�
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmcCsMoState;
    VOS_UINT8                           ucSmcCsMtState;
    VOS_UINT8                           ucSmcPsMoState;
    VOS_UINT8                           ucSmcPsMtState;
    VOS_UINT8                           ucSmrMoState;
    VOS_UINT8                           ucSmrMtState;
    VOS_UINT8                           aucReserved[2];
}NAS_OM_SMS_CONFIRM_STRU;
/*****************************************************************************
 ö����    : NAS_OM_PLMN_HUO_TYPE_ENUM
 ö��˵��  : DCMҪ���ڹ�������ʾPLMN������
 1.��    ��   : 2013��06��23��
   ��    ��   : l00167671
   �޸�����   : �½�
 2.��    ��   : 2013��09��3��
   ��    ��   : w00242748
   �޸�����   : DTS2013082909799 ��ѯNAS MM QUERYʱ��RPLMN��ʾ��EHPLMN���ػ�ʱ
                ��ЧPLMN��ʾΪOPLMN������
*****************************************************************************/
/* Modified by w00242748 for DTS2013082909799, 2013-9-3, begin */
enum NAS_OM_PLMN_HUO_TYPE_ENUM
{
   NAS_MMC_HUO_RPLMN        = 0x1,
   NAS_MMC_HUO_HPLMN        = 0x2,
   NAS_MMC_HUO_UPLMN        = 0x3,
   NAS_MMC_HUO_OPLMN        = 0x4,
   NAS_MMC_HUO_OTHER_PLMN   = 0x5,
   NAS_MMC_HUO_INVALID_PLMN = 0x6,
   NAS_MMC_HUO_BUTT
};
typedef VOS_UINT32 NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32;
/* Modified by w00242748 for DTS2013082909799, 2013-9-3, begin */

/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

/*******************************************************************************
 �ṹ��    : NAS_OM_MM_CONFIRM_STRU
 �ṹ˵��  : ����OM��MM��Ϣ��͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   :

  2.��    ��   : 2012��11��06��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ����GPRS״̬
*******************************************************************************/
typedef struct
{
    NAS_OM_MM_STATE_ENUM_UINT8          ucMmState;
    MM_UPDATE_STATUS_ENUM_UINT8         ucMmUpdateStatus;
    VOS_UINT8                           aucTmsi[LEN_TMSI];
    NAS_OM_GMM_STATE_ENUM_UINT8         ucGmmState;
    GMM_UPDATE_STATUS_ENUM_UINT8        ucGmmUpdateStatus;

    VOS_UINT8                           ucPtmsi[LEN_PTMSI];
    VOS_UINT8                           ucMmcFsmId;
    PLMN_SEL_MODE_ENUM_UINT8            enPlmnSelMode;
    UE_OPERATE_MODE_ENUM_UINT8          enUeOperMode;
    NET_OPERATE_MODE_ENUM_UINT8         ucNetMode;

    MS_ID_STRUCT                        IMSI;
    MS_ID_STRUCT                        IMEI;
    MS_ID_STRUCT                        IMEISV;
    PLMN_ID_STRUCT                      SelectedPlmn;
   
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucAvailPlmnNum;

    AVAILABLE_PLMN_STRUCT               AvailablePlmn[MAX_AVAILABEL_PLMN_NUM];

    NAS_OM_MM_SUB_STATE_ENUM_UINT8      ucMmSubState;
    NAS_OM_GMM_SUB_STATE_ENUM_UINT8     ucGmmSubState;
    NAS_OM_SERVICE_STATE_ENUM_UINT8     ucServiceStatus;
    VOS_UINT8                           ucMmcState;

    /* Added by l00198894 for PROBE Project, 2012/11/06, begin */
    NAS_OM_GMM_GPRS_STATE_ENUM_UINT8    enGmmGprsState;
	
	/* Modified by l00167671 for DCM LOGGER Project, 2013/06/24, begin */
    VOS_UINT8                           aucReserved[2];
	/* Modified by l00167671 for DCM LOGGER Project, 2013/06/24, end */
		
    /* Added by l00198894 for PROBE Project, 2012/11/06, end */

    /* Added by l00167671 for DCM LOGGER Project, 2013/06/24, begin */
    VOS_UINT8                           enTinType;
    NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32    enPlmnType;
    NAS_OM_MS_ID_STRU                   stMsId;
    /* Added by l00167671 for DCM LOGGER Project, 2013/06/24, end */    

}NAS_OM_MM_CONFIRM_STRU;

/*******************************************************************************
 �ṹ��    : NAS_QOS_STRUCT
 �ṹ˵��  : ����OM��QOS��Ϣ��͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNSAPI;
    VOS_UINT8                           ucDelayClass;
    VOS_UINT8                           ucReliabilityClass;
    VOS_UINT8                           ucPeakThrough;
    VOS_UINT8                           ucPrecedenceClass;
    VOS_UINT8                           ucMeanThrough;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucDeliverOrder;
    VOS_UINT8                           ucDeliverOfErrSdu;
    VOS_UINT8                           ucReserved1[1];
    VOS_UINT16                          usMaximSduSize;
    VOS_UINT32                          ulMaxBitRateUl;
    VOS_UINT32                          ulMaxBitRateDl;
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;
    VOS_UINT16                          usTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucReserved2[3];
    VOS_UINT32                          ulGuarantBitRateUl;
    VOS_UINT32                          ulGuarantBitRateDl;
}NAS_QOS_STRUCT;

/*******************************************************************************
 �ṹ��    : NAS_PDP_CONTEXT_STRU
 �ṹ˵��  : PDP��������Ϣ�Ľṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucPdpType;
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           ucActivePDPContexts;
    VOS_UINT8                           ucPdpLlcSapi;
    VOS_UINT8                           ucPdpRadioPriority;
    VOS_UINT8                           aucReserved2[1];
    VOS_UINT8                           ucApnLength;
    VOS_UINT8                           aucApn[SM_MAX_LENGTH_OF_APN];
    VOS_UINT8                           aucReserved3[2];
    VOS_UINT8                           aucIpAddr[SM_IP_ADDR_LEN];
    NAS_OM_PDP_ACT_TYPE_ENUM_UINT8      enActType;                              /*��������*/
    VOS_UINT8                           ucLinkedNsapi;                          /*�������NSAPI,�����������Ƕ��μ���,��˳�Ա��Ч*/
    VOS_UINT8                           aucReserved4[2];
    VOS_UINT8                           aucIpv6Addr[SM_IPV6_ADDR_LEN];
}NAS_PDP_CONTEXT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_PDP_CONTEXT_STRU
 �ṹ˵��  : ����OM�ļ����PDP��������Ϣ��͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPdpCnt;                               /* ʵ�ʼ����PDP�����ĸ��� */
    NAS_PDP_CONTEXT_STRU                astPdpContext[NAS_OM_PDP_CONTEXT_MAX];
}NAS_OM_PDP_CONTEXT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU
 �ṹ˵��  : ��OM�յ���CODEC��������
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enGsmCodec;
    VOS_UINT8                           aucReserve[3];
}NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU
 �ṹ˵��  : ����OM��CODEC���ý����͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRet;                                  /* ���ý�� */
}NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_CODEC_TYPE_STRU
 �ṹ˵��  : ����OM�ĵ�ǰCODEC��Ϣ��͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    NAS_OM_CURR_CODEC_TYPE_ENUM_U8      enCurrCodec;                            /* ��ǰʹ�õ�CODEC���� */
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enGsmCodecConfig;                       /* ��ǰGSM֧�ֵ�CODEC���� */
    VOS_UINT8                           aucReserve[2];
}NAS_OM_CODEC_TYPE_STRU;

/* Added by l00198894 for PROBE Project, 2012/11/06, begin */
/*******************************************************************************
 �ṹ��    : NAS_OM_SET_DSFLOW_RPT_REQ_STRU
 �ṹ˵��  : ��OM�յ�������ҵ�������������ϱ���������
 �޸���ʷ      :
  1.��    ��   : 2012��11��06��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ�����ṹ��
*******************************************************************************/
typedef struct
{
    NAS_OM_REPORT_ACTION_ENUM_UINT8     enRptAction;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usRptPeriod;
}NAS_OM_SET_DSFLOW_RPT_REQ_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_SET_DSFLOW_RPT_CNF_STRU
 �ṹ˵��  : ����OM����ҵ�������������ϱ����ý����͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��11��06��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ�����ṹ��
*******************************************************************************/
typedef struct
{
    NAS_OM_RESULT_ENUM_UINT32           enResult;                               /* ���ý�� */
}NAS_OM_SET_DSFLOW_RPT_CNF_STRU;

/*******************************************************************************
 �ṹ��    : NAS_OM_DSFLOW_RPT_IND_STRU
 �ṹ˵��  : ����OM������ҵ�����������ʵ���Ϣ��͸����Ϣ�ṹ����
 �޸���ʷ      :
  1.��    ��   : 2012��11��06��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ�����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurrentSendRate;                      /* ��ǰ�������� */
    VOS_UINT32                          ulCurrentReceiveRate;                   /* ��ǰ�������� */
    VOS_UINT32                          ulDSLinkTime;                           /* DS����ʱ��  */
    VOS_UINT32                          ulDSSendFluxLow;                        /* DS�����������ĸ��ֽ� */
    VOS_UINT32                          ulDSSendFluxHigh;                       /* DS�����������ĸ��ֽ� */
    VOS_UINT32                          ulDSReceiveFluxLow;                     /* DS�����������ĸ��ֽ� */
    VOS_UINT32                          ulDSReceiveFluxHigh;                    /* DS�����������ĸ��ֽ� */
}NAS_OM_DSFLOW_RPT_IND_STRU;
/* Added by l00198894 for PROBE Project, 2012/11/06, end */

/*******************************************************************************
 �ṹ��    : NasOmTrans_MSG
 �ṹ˵��  : NAS��OM��TRANS������Ϣ����
 �޸���ʷ      :
  1.��    ��   : 2012��04��27��
    ��    ��   : l00171473
    �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;                               /*_H2ASN_MsgChoice_Export NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16 */
    VOS_UINT16                          usToolsId;                              /* ����ID */
    VOS_UINT8                           aucData[4];                             /* ������Ϣ������ */

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_OM_TRANS_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/

}NasOmTrans_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/








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

#endif /* end of NasOmTrans.h */

