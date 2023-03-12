/******************************************************************************

                  ��Ȩ���� (C), 2003-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasErrorLog.h
  �� �� ��   : ����
  ��    ��   : ����/00179208
  ��������   : 2013��8��21��
  ����޸�   :
  ��������   : ����ERRORLOG������ģʽ�ϱ�ʹ�õ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��08��21��
    ��    ��   : ����/00179208
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NAS_ERRORLOG_H__
#define __NAS_ERRORLOG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "errorlog.h"
#include "omerrorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_FTM_MAX_PTMSI_LEN                           (4)                     /* ����PTMSI�ĳ��� */
#define NAS_FTM_MAX_TMSI_LEN                            (4)                     /* ����TMSI�ĳ��� */

#define TAF_SDC_RING_BUFFER_SIZE                        (1024 * 2)              /* TAF��Ļ��ι������С */
#define NAS_MML_RING_BUFFER_SIZE                        (1024 * 2)              /* MM��Ļ��ι������С */
/* Added by f00179208 for cs_err_log, 2014-10-07 Begin */
#define NAS_CC_RING_BUFFER_SIZE                         (1024 * 2)              /* CC��Ļ��ι������С */
/* Added by f00179208 for cs_err_log, 2014-10-07 End */

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_ERR_LOG_MML_MAX_RAT_NUM                     (3)                     /* ��ǰ֧�ֵĽ��뼼������ */
#else
#define NAS_ERR_LOG_MML_MAX_RAT_NUM                     (2)                     /* ��ǰ֧�ֵ�GU���뼼������ */
#endif

#define NAS_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog�ȼ�δ����*/
#define NAS_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog�ȼ�Ϊ���� */
#define NAS_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog�ȼ�Ϊ��Ҫ */
#define NAS_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog�ȼ�Ϊ��Ҫ */
#define NAS_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog�ȼ�Ϊ��ʾ */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_ERR_LOG_NET_RAT_TYPE_ENUM
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_NET_RAT_TYPE_ENUM
{
    NAS_ERR_LOG_NET_RAT_TYPE_GSM,           /* GSM���뼼�� */
    NAS_ERR_LOG_NET_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    NAS_ERR_LOG_NET_RAT_TYPE_LTE,           /* LTE���뼼�� */
    NAS_ERR_LOG_NET_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT8 NAS_ERR_LOG_NET_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_PS_ACTION_TYPE_ENUM
 �ṹ˵��  : NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU��Ϣ��GMM��������
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_PS_ACTION_TYPE_ENUM
{
    NAS_ERR_LOG_GMM_ACTION_RAU                  = 0,
    NAS_ERR_LOG_GMM_ACTION_ATTACH               = 1,
    NAS_ERR_LOG_GMM_ACTION_COMBINED_RAU         = 2,
    NAS_ERR_LOG_GMM_ACTION_COMBINED_ATTACH      = 3,
    NAS_ERR_LOG_GMM_ACTION_PERIODC_RAU          = 4,
    NAS_ERR_LOG_GMM_ACTION_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_GMM_ACTION_TYPE_ENUM_U32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_REG_DOMAIN_ENUM
 ö��˵��  : ע�������Ϣ
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_REG_DOMAIN_ENUM
{
    NAS_ERR_LOG_REG_DOMAIN_PS    = 0x00,                                        /* ע������ΪPS�� */
    NAS_ERR_LOG_REG_DOMAIN_PS_CS = 0x01,                                        /* ע������ΪCS+PS�� */
    NAS_ERR_LOG_REG_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_REG_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_CALL_EX_STATE_ENUM
 ö��˵��  : ����״̬
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_CALL_EX_STATE_ENUM
{
    NAS_ERR_LOG_CALL_S_ACTIVE,                                                  /* active */
    NAS_ERR_LOG_CALL_S_HELD,                                                    /* held */
    NAS_ERR_LOG_CALL_S_DIALING,                                                 /* dialing (MO call) */
    NAS_ERR_LOG_CALL_S_ALERTING,                                                /* alerting (MO call) */
    NAS_ERR_LOG_CALL_S_INCOMING,                                                /* incoming (MT call) */
    NAS_ERR_LOG_CALL_S_WAITING,                                                 /* waiting (MT call) */
    NAS_ERR_LOG_CALL_S_IDLE,                                                    /* idle */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_ACTIVE,                                     /* CCBS�ȴ�����̬ */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_RECALL,                                     /* CCBS�ȴ��غ�̬ */
    NAS_ERR_LOG_CALL_S_UNKNOWN,                                                 /* unknown state */
    NAS_ERR_LOG_CALL_S_MO_FDN_CHECK,                                            /* FDN check */
    NAS_ERR_LOG_CALL_S_MO_CALL_CONTROL_CHECK,                                   /* CALL CONTROL check */
    NAS_ERR_LOG_CALL_S_BUTT
};
typedef VOS_UINT8  NAS_ERR_LOG_CALL_STATE_ENUM_U8;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_ALM_ID_ENUM
 ö��˵��  : ���ϸ澯ID
 1.��    ��   : 2013��08��27��
   ��    ��   : f00179208
   �޸�����   : �½�
 2.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : CS ERRLOG��Ŀ�����澯ID
*****************************************************************************/
enum NAS_ERR_LOG_ALM_ID_ENUM
{
    NAS_ERR_LOG_ALM_CS_REG_FAIL                             = 0x01,             /* CS��ע��ʧ�� */
    NAS_ERR_LOG_ALM_PS_REG_FAIL                             = 0x02,             /* PS��ע��ʧ�� */
    NAS_ERR_LOG_ALM_SEARCH_NW_FAIL                          = 0x03,             /* ����ʧ�� */
    NAS_ERR_LOG_ALM_CS_CALL_FAIL                            = 0x04,             /* CS����ʧ�ܼ��쳣�Ҷ� */
    NAS_ERR_LOG_ALM_PS_CALL_FAIL                            = 0x05,             /* PS����ʧ�ܼ��쳣�Ҷ� */
    NAS_ERR_LOG_ALM_SMS_FAIL                                = 0x06,             /* ����ʧ�� */
    NAS_ERR_LOG_ALM_VC_OPT_FAIL                             = 0x07,             /* VC����ʧ�� */
    /* Added by f00179208 for cs_err_log, 2014-09-16 Begin */
    NAS_ERR_LOG_ALM_CS_PAGING_FAIL                          = 0x08,             /* CS PAGING fail */
    NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL                         = 0x09,             /* CS MT fail */
    NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL                       = 0x0a,             /* CSFB MT fail */
    NAS_ERR_LOG_ALM_MNTN                                    = 0x0b,             /* ���ϸ澯�Ŀ�ά�ɲ� */
    NAS_ERR_LOG_ALM_NW_DETACH_IND                           = 0x0c,             /* ���緢���DETACHָʾ */
    NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL                         = 0x0d,             /* PS SERVICE�ܾ� */
    /* Added by n00269697 for DTS2014102108104, 2014-10-28 End */
    /* Added by n00269697 for srvcc_imsRedial_chr, 2015-12-5, begin */
    NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO                         = 0x0e,             /* FFT����MCC�Ľ�� */
    /* Added by n00269697 for srvcc_imsRedial_chr, 2015-12-5, end */

    NAS_ERR_LOG_ALM_ID_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_ALM_ID_ENUM_U16;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_ALM_TYPE_ENUM
 ö��˵��  : ���ϸ澯����
 1.��    ��   : 2013��08��27��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_ALM_TYPE_ENUM
{
    NAS_ERR_LOG_ALM_TYPE_COMMUNICATION    = 0x00,                               /* ͨ�� */
    NAS_ERR_LOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x01,                               /* ҵ������ */
    NAS_ERR_LOG_ALM_TYPE_DEAL_WRONG       = 0x02,                               /* ������� */
    NAS_ERR_LOG_ALM_TYPE_DEVICE_FAILURE   = 0x03,                               /* �豸���� */
    NAS_ERR_LOG_ALM_TYPE_ENV_FAILURE      = 0x04,                               /* �������� */
    NAS_ERR_LOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_ALM_TYPE_ENUM_U16;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_FTM_PROJECT_ID_ENUM
 ö��˵��  : ����ģʽ�ϱ��Ĺ���ID
 1.��    ��   : 2013��08��27��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_FTM_PROJECT_ID_ENUM
{
    NAS_FTM_PROJECT_TMSI_RPT,
    NAS_FTM_PROJECT_PTMSI_RPT,

    NAS_FTM_PROJECT_ID_BUTT,
};
typedef VOS_UINT16  NAS_ERR_LOG_FTM_PROJECT_ID_ENUM_U8;

/* Added by f00179208 for cs_err_log, 2014-09-16 Begin */
/*****************************************************************************
 ö����    : NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM
 ö��˵��  : cs paging���������ϱ��Ĵ���ԭ��ֵ
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM
{
    NAS_ERR_LOG_CS_PAGING_CAUSE_MM_STATE_ERR       = 1,                         /* MM״̬����ȷ */
    NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR      = 2,                         /* Ѱ������ */
    NAS_ERR_LOG_CS_PAGING_CAUSE_EST_FAIL           = 3,                         /* ���ӽ���ʧ�� */
    NAS_ERR_LOG_CS_PAGING_CAUSE_EST_TIMEOUT        = 4,                         /* ���ӽ�����ʱ */
    NAS_ERR_LOG_CS_PAGING_CAUSE_EST_RELEASED       = 5,                         /* ���ӽ������ͷ� */
    NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_RELEASED      = 6,                         /* ���ӱ��ͷ� */

    NAS_ERR_LOG_CS_PAGING_CAUSE_BUTT,
};
typedef VOS_UINT32  NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM_U32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM
 ö��˵��  : cs mt call���������ϱ��Ĵ���ԭ��ֵ
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM
{
    /* CC���쳣ԭ��ֵ */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_CODED_AS_111        = 1,                    /* TIֵΪ7 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_INC_SET_TO_1        = 2,                    /* TIֵ������Ϊ1 */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_TI_IS_USED             = 3,                    /* TI��ʹ�� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_CC_CREATE_ENTYTY_FAIL  = 4,                    /* CC����ʵ��ʧ�� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_NEW_CALL_NOT_ALLOW     = 5,                    /* �����ٷ����µĺ��� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_OPTIONAL_IE_ERR        = 6,                    /* SETUP������IE���ʧ�� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_DECODE_FAIL            = 7,                    /* CC����ʧ�� */

    /* CALL���쳣ԭ��ֵ */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_CALL_STATE_CTRL_NOT_SUPPORT  = 8,              /* �������в�֧�� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_BC_CHECK_FAIL          = 9,                    /* BC���ʧ�� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_MT_CALL_NOT_ALLOW      = 10,                   /* ��������MT���� */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_NE_GET_BC_FAIL         = 11,                   /* BCЭ��ʧ�� */

    NAS_ERR_LOG_CS_MT_CALL_CAUSE_BUTT,
};
typedef VOS_UINT32  NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_CSFB_MT_STATE_ENUM
 ö��˵��  : csfb mt��״̬
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_CSFB_MT_STATE_ENUM
{
    NAS_ERR_LOG_CSFB_MT_STATE_NULL                                = 0,          /* ��Чֵ */
    NAS_ERR_LOG_CSFB_MT_STATE_PAGING_RECEIVED                     = 1,          /* CSFB PAGING�Ѿ����� */
    NAS_ERR_LOG_CSFB_MT_STATE_TRAG_NW_SEARCH_FOR_INTER_SYS_BACK   = 2,          /* ��ϵͳʧ�ܻ��˵�LTE, �������� */
    NAS_ERR_LOG_CSFB_MT_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST  = 3,          /* ���յ�LMM��Service Resultָʾ,�������� */
    NAS_ERR_LOG_CSFB_MT_STATE_TRAG_LAU                            = 4,          /* LAI�����ı�,����LAU */
    NAS_ERR_LOG_CSFB_MT_STATE_RCV_SERVICE_REQ                     = 5,          /* CSFB MTҵ����Ϣ�Ѿ����� */

    NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT,
};
typedef VOS_UINT32  NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32;
/* Added by f00179208 for cs_err_log, 2014-09-16 End */

/* Added by n00269697 for cs_err_log, 2014-09-19 Begin */
/*****************************************************************************
ö����    :  NAS_ERR_LOG_PLMN_SELECTION_RESULT_ENUM
�ṹ˵��  :  �������ö��ֵ
1.��    ��   : 2014��9��19��
  ��    ��   : n00269697
  �޸�����   : ����
*****************************************************************************/
enum NAS_ERR_LOG_PLMN_SELECTION_RESULT_ENUM
{
    NAS_ERR_LOG_PLMN_SELECTION_SUCC            = 0,                                 /*����������פ��*/
    NAS_ERR_LOG_PLMN_SELECTION_FAIL            = 1,                                 /*�������ע�ᵼ�¿���Ч*/
    NAS_ERR_LOG_PLMN_SELECTION_ABORTED         = 2,                                 /* PlmnSelection״̬�������*/
    NAS_ERR_LOG_PLMN_SELECTION_INTER_SYS_HRPD  = 3,                                 /* ������������ѡ��HRPD */
    NAS_ERR_LOG_PLMN_SELECTION_NO_RF           = 4,

    NAS_ERR_LOG_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 NAS_ERR_LOG_PLMN_SEL_RSLT_ENUM_UINT32;
/* Added by n00269697 for cs_err_log, 2014-09-19 End */

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
 �ṹ��    : NAS_ERR_LOG_LAI_INFO_STRU
 �ṹ˵��  : λ������Ϣ�Ľṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    MNTN_PLMN_ID_STRU                   stPlmn;
    VOS_UINT32                          ulLac;
}NAS_ERR_LOG_LAI_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU
 �ṹ˵��  : MM��LAU�����Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT32                          ulLuResult;                             /* LU���            */
    NAS_ERR_LOG_NET_RAT_TYPE_ENUM_UINT8 enNetType;                              /* ��ǰע����������� */
    VOS_UINT8                           ucIsComBined;                           /* �Ƿ�Ϊ����ע��   */
    VOS_UINT16                          usRegFailCause;                         /* ����ʧ��ԭ��     */
    VOS_UINT32                          ulServiceStatus;                        /* ����״̬          */
    VOS_UINT32                          ulCsUpdateStatus;                       /* CS �����״̬     */
    VOS_UINT32                          ulLuAttemptCnt;                         /* LU Attempt counter */
    NAS_ERR_LOG_LAI_INFO_STRU           stOldLai;                               /* ��LAI              */
    /* Added by f00179208 for cs_err_log, 2014-09-16 Begin */
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;                         /* λ����Ϣ */
    /* Added by f00179208 for cs_err_log, 2014-09-16 End */
}NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU
 �ṹ˵��  : GMM��Attach/RAU�����Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                    stHeader;
    NAS_ERR_LOG_GMM_ACTION_TYPE_ENUM_U32      enGmmActionType;                  /* GMM�Ĳ������� */
    VOS_UINT32                                ulActionResult;                   /* ע���� */
    NAS_ERR_LOG_REG_DOMAIN_ENUM_UINT32        enReqDomain;                      /* ��ǰע��Ľ����Ps Only��CS_PS */
    NAS_ERR_LOG_REG_DOMAIN_ENUM_UINT32        enRsltDomain;                     /* ��ǰע��Ľ����Ps Only��CS_PS */
    VOS_UINT16                                usRegFailCause;                   /* ����ʧ��ԭ�� */
    NAS_ERR_LOG_NET_RAT_TYPE_ENUM_UINT8       enNetType;                        /* ��ǰע����������� */
    VOS_UINT8                                 ucReserved;                       /* ������ */
    VOS_UINT32                                ulRegCounter;                     /* Attach attempt counter */
    VOS_UINT32                                ulServiceStatus;                  /* ����״̬ */
    /* Added by f00179208 for cs_err_log, 2014-09-16 Begin */
    NAS_MNTN_POSITION_INFO_STRU               stPositionInfo;                   /* λ����Ϣ */
    /* Added by f00179208 for cs_err_log, 2014-09-16 End */
}NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU;

/* Added by n00269697 for DTS2014102108104, 2014-10-28 Begin */
/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU
 �ṹ˵��  : GMM��PS SERVICE ע������Ϣ�ṹ��
 1.��    ��   : 2014��10��28��
   ��    ��   : n00269697
   �޸�����   : �½�
 *******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                    stHeader;
    VOS_UINT32                                enActionResult;                   /* �����Ľ�� */
    VOS_UINT16                                enRegFailCause;                   /* ����ʧ��ԭ�� */
    VOS_UINT8                                 aucReserved[2];
    VOS_UINT32                                ulServiceSts;                     /* ����״̬ */
    NAS_MNTN_POSITION_INFO_STRU               stPositionInfo;                   /* λ����Ϣ */
}NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU;
/* Added by n00269697 for DTS2014102108104, 2014-10-28 End   */

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_RAT_SEARCH_INFO_STRU
 �ṹ˵��  : ���뼼������Ϣ
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSearchAllBand;   /* �Ƿ��ڵ�ǰ���뼼��ִ�й�ȫƵ����, VOS_TRUE:ִ�й�ȫƵ��, VOS_FALSE:δִ�й� */
    VOS_UINT8                           ucCoverageType;    /* ��ǰ���뼼���µ����縲������, 0:�����ڸ��ǣ�1:���ڵ��������縲��,2:���ڸ��������縲�� */
    VOS_UINT8                           ucRatType;         /* ����Ľ��뼼�� */
    VOS_UINT8                           ucReserve;
}NAS_ERR_LOG_RAT_SEARCH_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_SEARCH_NETWORK_RESULT_EVENT_STRU
 �ṹ˵��  : ���������Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    /* Modified by n00269697 for cs_err_log, 2014-09-19 Begin */
    NAS_ERR_LOG_PLMN_SEL_RSLT_ENUM_UINT32       ulSearchResult;                 /*ѡ�����*/
    /* Modified by n00269697 for cs_err_log, 2014-09-19 End */
    VOS_UINT32                                  ulCampFlg;                      /*��ǰ�Ƿ�פ����־,VOS_TRUE:��פ��,VOS_FALSE:δפ��*/
    VOS_UINT32                                  ulRatNum;                       /*�и��ǵĽ��뼼������*/
    NAS_ERR_LOG_RAT_SEARCH_INFO_STRU            astSearchRatInfo[NAS_ERR_LOG_MML_MAX_RAT_NUM];  /*���治ͬ���뼼����������Ϣ*/
}NAS_ERR_LOG_SEARCH_NETWORK_RESULT_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU
 �ṹ˵��  : ���к���ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsUser;
    VOS_UINT8                           ucDiscCallFlag;
    VOS_UINT8                           aucReserved[2];
}NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU
 �ṹ˵��  : ���е�����ص���Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT8                           ucCallId;                               /* call id */
    NAS_ERR_LOG_CALL_STATE_ENUM_U8      enCallState;                            /* Call State */
    /* Added by n00269697 for DTS2014102108104, 2014-10-28 Begin */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserved[1];                         /* ������ */
    /* Added by n00269697 for DTS2014102108104, 2014-10-28 End */
    NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU   stDiscDir;                              /* �Ҷϵ绰�ķ��� */
    VOS_UINT32                          ulCcCause;                              /* ʧ��ԭ��ֵ */
    /* Added by f00179208 for cs_err_log, 2014-09-16 Begin */
    NAS_MNTN_USIM_INFO_STRU             stUsimInfo;                             /* ����Ϣ */
    NAS_MNTN_POSITION_INFO_STRU         stPositionInfo;                         /* λ����Ϣ */
    /* Added by f00179208 for cs_err_log, 2014-09-16 End */
}NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_APS_FSM_CTX_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFsmId;                                /* ��ǰ״̬����ʶ */
    VOS_UINT32                          ulState;                                /* ��ǰ״̬ */
}NAS_ERR_LOG_APS_FSM_CTX_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MNTN_APS_FSM_INFO_STRU
 �ṹ˵��  : APS״̬����Ϣ
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stMainFsm;                              /* ��״̬�� */
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stSubFsm;                               /* ��״̬�� */
    VOS_UINT8                           ucPdpId;                                /* ��ǰ״̬������Ӧ��PDP ID */
    VOS_UINT8                           aucReserve[3];
}NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_PS_CALL_FAIL_EVENT_STRU
 �ṹ˵��  : PS�������ش������Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    NAS_MNTN_USIM_INFO_STRU                     stUsimInfo;                     /* ����Ϣ */
    NAS_MNTN_POSITION_INFO_STRU                 stPositionInfo;                 /* λ����Ϣ */
    VOS_UINT32                                  ulPsRegState;                   /* PSע��״̬ */
    NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU    stApsFsmInfo;                   /* ״̬����Ϣ */
    VOS_UINT32                                  ulPsCause;                      /* ʧ��ԭ�� */
}NAS_ERR_LOG_PS_CALL_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU
 �ṹ˵��  : ���ŷ���ʧ����ش������Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_MNTN_USIM_INFO_STRU                                 stUsimInfo;
    NAS_MNTN_POSITION_INFO_STRU                             stPositionInfo;
    NAS_MNTN_SMS_MO_INFO_STRU                               stMoFail;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enCsStatus;
    NAS_MNTN_SEND_DOMAIN_STATUS_ENUM_UINT32                 enPsStatus;
}NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_VC_FAILURE_EVENT_STRU
 �ṹ˵��  : VCģ����ش������Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT32                              ulOptState;                         /* �������� */
    VOS_UINT32                              ulCasue;                            /* ������� */
    VOS_UINT32                              ulName;                             /* ��Ϣ���� */
}NAS_ERR_LOG_VC_FAILURE_EVENT_STRU;

/* Added by f00179208 for cs_err_log, 2014-09-16 Begin */
/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_CS_PAGING_FAIL_EVENT_STRU
 �ṹ˵��  : �յ�pagingʱ����ش������Ϣ�ṹ��
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : CS ERRLOG��Ŀ����
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* λ����Ϣ */
    NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM_U32    enCause;

    /* Added by f00179208 for CHR optimize, 2015-03-10 begin */
    VOS_UINT8                               ucGMsIdType;                        /* TMSI or IMSI or PTMSI */
    VOS_UINT8                               ucGPagingType;                      /* CS or PS */
    VOS_UINT8                               aucReserve1[2];
    VOS_UINT32                              ulWCnDomainId;                      /* CS DOMAIN��PS DOMAIN��INVALID DOMAIN */
    VOS_UINT32                              ulWPagingType;                      /* Ѱ����Ϣ����:paging type1��paging type2 */
    VOS_UINT32                              ulWPagingCause;                     /* pagingԭ��ֵ */
    VOS_UINT32                              ulWPagingUeId;                      /* Paging Recorder Id */
    /* Added by f00179208 for CHR optimize, 2015-03-10 end */

}NAS_ERR_LOG_CS_PAGING_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU
 �ṹ˵��  : CS MTʱ����ش������Ϣ�ṹ��
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : CS ERRLOG��Ŀ����
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* λ����Ϣ */
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause;
}NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_CSFB_MT_CALL_FAIL_EVENT_STRU
 �ṹ˵��  : CSFB MTʱ����ش������Ϣ�ṹ��
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : CS ERRLOG��Ŀ����
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* λ����Ϣ */
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32      enState;
}NAS_ERR_LOG_CSFB_MT_CALL_FAIL_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_MNTN_EVENT_STRU
 �ṹ˵��  : ���ϸ澯�Ŀ�ά�ɲ���Ϣ�ṹ��
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : CS ERRLOG��Ŀ����
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT32                              ulCount;                            /* ������������� */
}NAS_ERR_LOG_MNTN_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU
 �ṹ˵��  : ����Detachָʾ����Ϣ�ṹ��
 1.��    ��   : 2014��09��16��
   ��    ��   : f00179208
   �޸�����   : CS ERRLOG��Ŀ����
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU             stPositionInfo;                     /* λ����Ϣ */
    VOS_UINT8                               ucDetachType;                       /* detach���� */
    VOS_UINT8                               ucGmmCause;                         /* detachԭ�� */
    VOS_UINT8                               ucForceToStandby;
    VOS_UINT8                               ucCurrNetRat;
}NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU;
/* Added by f00179208 for cs_err_log, 2014-09-16 End */

/* Added by n00269697 for srvcc_imsRedial_chr, 2015-12-5, begin */
/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM
 �ṹ˵��  : SRVCCʧ�ܵ�ԭ��ö��

 �޸ļ�¼  :
 1.��    ��   : 2015��12��5��
   ��    ��   : n00269697
   �޸�����   : ����

*****************************************************************************/
enum NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM
{
    NAS_ERR_LOG_SRVCC_FAIL_NULL                             = 0,
    NAS_ERR_LOG_SRVCC_FAIL_NO_CALL_NUM                      = 1,                /* bsrvccʱ��IMSA��ͬ��call numΪ0 */
    NAS_ERR_LOG_SRVCC_FAIL_RESUME_IND_BACK_TO_LTE           = 2,                /* SRVCC��handoverʧ�ܣ��ֻص�LTE */
    NAS_ERR_LOG_SRVCC_FAIL_BUTT
};

typedef VOS_UINT8 NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM_UINT8;
/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_SRVCC_FAIL_STRU
 �ṹ˵��  : SRVCCʧ�ܵ���Ϣ�ṹ

 �޸ļ�¼  :
 1.��    ��   : 2015��12��5��
   ��    ��   : n00269697
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                                  stHeader;
    NAS_MNTN_POSITION_INFO_STRU                             stPositionInfo;     /* λ����Ϣ */
    NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM_UINT8                 enSrvccFailCause;   /* SRVCCʧ��ԭ�� */
    VOS_UINT8                                               aucReserve[3];
}NAS_ERR_LOG_SRVCC_FAIL_STRU;
/* Added by n00269697 for srvcc_imsRedial_chr, 2015-12-5, end */

/*******************************************************************************
 �ṹ��    : NAS_FTM_TMSI_RPT_EVENT_STRU
 �ṹ˵��  : TMSI���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_UINT8                               aucTmsi[NAS_FTM_MAX_TMSI_LEN];      /* tmsi������ */
}NAS_FTM_TMSI_RPT_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_FTM_PTMSI_RPT_EVENT_STRU
 �ṹ˵��  : PTMSI���ɺ͸��º��ϱ�����Ϣ�ṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_UINT8                               aucPtmsi[NAS_FTM_MAX_PTMSI_LEN];    /* ptmsi������ */
}NAS_FTM_PTMSI_RPT_EVENT_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_ALM_LEVEL_STRU
 �ṹ˵��  : Alm ID��log�����Ӧ�Ľṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : s00190137
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16             enAlmID;        /* �쳣ģ��ID */
    VOS_UINT16                              usLogLevel;     /* �ϱ�log�ȼ� */
}NAS_ERR_LOG_ALM_LEVEL_STRU;

/* Added by f00179208 for ErrLog&FTM, 2013-9-10 Begin */
/*****************************************************************************
 �ṹ��    : NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU
 �ṹ˵��  : MM��ERRLOG���ϸ澯����ʱд���λ���Ĺ����ṹ

 �޸ļ�¼  :
 1.��    ��   : 2013��09��10��
   ��    ��   : f00179208
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
}NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU;
/* Added by f00179208 for ErrLog&FTM, 2013-9-10 End */

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

#endif /* end of NasErrorLog.h */


