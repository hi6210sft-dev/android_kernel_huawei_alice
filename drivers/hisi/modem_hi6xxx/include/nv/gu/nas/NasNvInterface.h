/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __NASNVINTERFACE_H__
#define __NASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV��� */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV��δ���� */

/* GPRS GEA �㷨֧�ֺ궨�� */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* ֧��GPRS GEA1�㷨 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* ֧��GEA1ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* ֧��GEA2ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* ֧��GEA3ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* ֧��GEA4ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* ֧��GEA5ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* ֧��GEA6ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* ֧��GEA7ʱ����������ֵ */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* ֧��GPRS GEA2�㷨 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* ֧��GPRS GEA3�㷨 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* ֧��GPRS GEA4�㷨 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* ֧��GPRS GEA5�㷨 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* ֧��GPRS GEA6�㷨 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* ֧��GPRS GEA7�㷨 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV�е�Чplmn���� */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn��Mcc��󳤶� */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn��Mnc��󳤶� */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

/* Added by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-4, begin */
#define NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* �û����õ�EHplmn�ĸ��� */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* ��ֹ���뼼����PLMN ID�������� */
/* Added by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-4, end */
/*Add by wx270776 for DTS2014121701015, 2014-12-19, begin */
#define NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM              (8)                /* ��չ��NV���EHplmn���������*/
/*Add by wx270776 for DTS2014121701015, 2014-12-19, end */
/* Modified by s00190137 for 256 EOPLMN, 2013-11-26, begin */
/* Added by s00190137 for ACC&SPLMN, 2013-10-15 Begin */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN               (8)               /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* �û����õ�OPLMN����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_NUM                   (256)             /* �û����õ�OPLMN�������� */
#define NAS_MMC_NVIM_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* �û����õĴ����뼼��OPLMN������Ԫ���ȣ���6F61�ļ��Ļ������ȵ�ԪΪ5 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN              (500)             /* �û�����OPLMN������ֽ���,����ǰֻ֧��500*/
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN       (1280)            /* ��չ����û�����OPLMN������ֽ���*/
/* Added by s00190137 for ACC&SPLMN, 2013-10-15 End */
/* Modified by s00190137 for 256 EOPLMN, 2013-11-26, end */

/* Added by c00188733 for DPLMN&NPLMN, 2014-7-14, begin */
#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN       (6*128)            /* ��չ����û�����DPLMN������ֽ���*/
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN       (6*128)            /* ��չ����û�����NPLMN������ֽ���*/
#define NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM                   (3*8)
/* Added by c00188733 for DPLMN&NPLMN, 2014-7-14, end */


#define NAS_NVIM_MAX_OPER_SHORT_NAME_LEN                36
#define NAS_NVIM_MAX_OPER_LONG_NAME_LEN                 40

/* Modified by z00161729 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-4-5, begin */
#define NAS_NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */
/* Modified by z00161729 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-4-5, end */
#define NAS_MML_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */
#define NAS_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */

#define NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM          (6)                 /* ģʽ�Զ��л������Ŀ����ù�������� */
#define NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM       (6)                 /* ģʽ�Զ��л������Ŀ�����USIM/IMSI������Ÿ��� */

/* Modified by w00167002 for DTS2015032709270, 2015-4-18, begin */
#define NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM              (8)                 /* ��ֹ���뼼����PLMN ID�������� */
/* Modified by w00167002 for DTS2015032709270, 2015-4-18, end */

#define NAS_SIM_FORMAT_PLMN_LEN                     (3)                     /* Sim����ʽ��Plmn���� */

#define NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, begin */
#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG�Ѳ����ǹ�����Ĺ����������� */
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /* ����ԭ��ֵ����б� */
/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, end */

#define NV_ITEM_NET_CAPABILITY_MAX_SIZE                     (10)

#define NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE            (2)                 /* ��ǰ֧�ֵ�Э��汾 */

#define NAS_MMC_NVIM_MAX_IMSI_LEN                           (9)                     /* ����IMSI�ĳ��� */

#define NVIM_MAX_EPLMN_NUM                                  (16)
#define NVIM_MAX_MCC_SIZE                                   (3)
#define NVIM_MAX_MNC_SIZE                                   (3)

#define NVIM_MAX_FDD_FREQ_BANDS_NUM                         (12)

/* Add by z60575 for multi_ssid, 2012-9-5 end */
/*+CGMI - ��ȡ����������*/

/* Added by l00208543 for RatBlackListAccordSimType, 2013-11-01, begin */
#define NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM         (16)
#define NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM          (8)    /* Ԥ����չ */
#define NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM     (2)

#define NAS_NVIM_FORBIDDEN_RAT_NUM_0                 (0)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_1                 (1)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_2                 (2)
/* Added by l00208543 for RatBlackListAccordSimType, 2013-11-01, end */


/* Added by l00208543 for V9R1 reject 17, 2014-4-29, begin */
#define NAS_NVIM_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM               (8)
/* Added by l00208543 for V9R1 reject 17, 2014-4-29, end */

/* ��NVIDö�ٵ�ת����(PS_NV_ID_ENUM, SYS_NV_ID_ENUM, RF_NV_ID_ENUM) */
typedef VOS_UINT16  NV_ID_ENUM_U16;
#define NV_ITEM_IMEI_SIZE                      16
#define NV_ITEM_SELPLMN_MODE_SIZE              2
#define NV_ITEM_MMA_OPERATORNAME_SIZE          84
#define NV_ITEM_AT_PARA_SIZE                   100
#define NV_ITEM_HPLMN_FIRST_SEARCH_SIZE        1  /* ��һ��HPLMN������ʱ���� */
/* Modified by z00161729 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-4-5, begin */
#define NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */
/* Modified by z00161729 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-4-5, end */

/* Added by w00176964 for CDMA 1X Iteration 1, 2014-8-18, begin */
#define CNAS_NVIM_MAX_1X_MRU_SYS_NUM                            (12)
/* Added by w00176964 for CDMA 1X Iteration 1, 2014-8-18, end */

/* Added by h00285180 for DTS2014110307415, 2014-10-20, begin */
#define NAS_MMC_NVIM_MAX_CAUSE_NUM      (10)     /* NV����ԭ��ֵ������ */
/* Added by h00285180 for DTS2014110307415, 2014-10-20, end   */

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/* �����ȼ�PLMN refresh ����������Ĭ���ӳ�ʱ��: ��λ �� */
#define NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN    (5)
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */
/* Added by j00174725 for DTS2016040901340, 2016-04-10, begin */
#define NAS_MAX_TMSI_LEN                                (4)                     /* ����TMSI�ĳ��� */
#define NAS_SIM_MAX_LAI_LEN                             (6)                     /* SIM���б����LAI��󳤶� */
/* Added by j00174725 for DTS2016040901340, 2016-04-10, end */


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, begin */
/*****************************************************************************
ö����    : NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
�ṹ˵��  : ����ע�ᱻ�ܣ�MMC�Ķ���

1.��    ��   : 2012��6��11��
  ��    ��   : w00166186
  �޸�����   : AT&T&DCM��Ŀ��������

2.��    ��   : 2014��8��19��
  ��    ��   : w00167002
  �޸�����   : DTS2014081905808:������PSע��ܾ�14ʱ������ǰ��HOME PLMN�ϣ������
               ����ѭ��ƹ�ң��޸�Ϊ����ACTION����:�����������ϴ���ѡ������HOME������
               ����Ч�����������̽��д���

*****************************************************************************/
enum NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 0,            /* �������� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 1,            /* ����פ�� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 2,            /* ������ѡ���� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 3,            /* ����פ�� */
    
    /* Added by w00167002 for DTS2014081905808, 2014-8-19, begin */
    NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 4,            /* ������������ע�ᷢ����������HOME�����ϲ���Ч */
    /* Modified by w00167002 for DTS2014081905808, 2014-8-19, end */
    
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;

/*****************************************************************************
ö����    : NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
�ṹ˵��  : ע��ʧ���Զ���ԭ��ֵ

1.��    ��   : 2012��6��11��
  ��    ��   : w00166186
  �޸�����   : AT&T&DCM��Ŀ��������

*****************************************************************************/
enum NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN = 14,
    NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT               = 301,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT16 NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16;

/*****************************************************************************
ö����    : NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8
�ṹ˵��  : ע����

1.��    ��   : 2012��6��11��
  ��    ��   : w00166186
  �޸�����   : AT&T&DCM��Ŀ��������

*****************************************************************************/
enum NAS_MMC_NVIM_REG_DOMAIN_ENUM
{
    NAS_MMC_NVIM_REG_DOMAIN_CS = 1,
    NAS_MMC_NVIM_REG_DOMAIN_PS = 2,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8;
/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, end */

/* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, begin */
/*****************************************************************************
 ö����    : NAS_MMC_UCS2_ENUM
 ö��˵��  : UCS2 ����
 �޸���ʷ  :
 1.��    ��    : 2013��03��11��
   ��    ��    : w00176964
   �޸�����    : �½�
*****************************************************************************/

enum NAS_MMC_UCS2_ENUM
{
    NAS_MMC_UCS2_HAS_PREFER                                = 0,
    NAS_MMC_UCS2_NO_PREFER                                 = 1,

    NAS_MMC_UCS2_BUTT
};

typedef VOS_UINT16 NAS_MMC_UCS2_ENUM_UINT16;
/* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, end */

/*****************************************************************************
 ö����    : NV_MS_MODE_ENUM_UINT8
 �ṹ˵��  :  NV�м�¼���ֻ�ģʽ
  1.��    ��   : 2011��8��18��
    ��    ��   : z00161729
    �޸�����   : ����
  2.��    ��   : 2012��4��23��
    ��    ��   : w00166186
    �޸�����   : DTS2012033104746,�ػ�״̬���÷�����ΪANY����Ч
*****************************************************************************/
enum NV_MS_MODE_ENUM
{
    NV_MS_MODE_CS_ONLY,                                                 /* ��֧��CS�� */
    NV_MS_MODE_PS_ONLY,                                                 /* ��֧��PS�� */
    NV_MS_MODE_CS_PS,                                                   /* CS��PS��֧�� */

    /* Aded by w00166186 for DTS2012033106746, 2012-04-23, begin */
    NV_MS_MODE_ANY,                                                     /* ANY,�൱�ڽ�֧��CS�� */
    /* Aded by w00166186 for DTS2012033106746, 2012-04-23, end */

    NV_MS_MODE_BUTT
};
typedef VOS_UINT8 NV_MS_MODE_ENUM_UINT8;

/* Added by l00208543 for DTS2013111904411, 2013-11-19, begin */
/*****************************************************************************
 ö����    : NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
 �ṹ˵��  : �޸ľܾ�ԭ��ֵ�����շ������������
  1.��    ��   : 2013��11��19��
    ��    ��   : l00208543
    �޸�����   : ����
*****************************************************************************/
enum NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_INACTIVE     = 0,        /* ���ܲ���Ч */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_PS,                   /* �޸�CS+PS�ľܾ�ԭ��ֵ */                                         
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_ONLY,                 /* ���޸�CS��ľܾ�ԭ��ֵ */                                     
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_PS_ONLY,                 /* ���޸�PS��ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8;
/* Added by l00208543 for DTS2013111904411, 2013-11-19, end */

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU
 �ṹ˵��  : NV SrchHplmnFlg_ManualMode�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usManualSearchHplmnFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
 �ṹ˵��  : NV SrchHplmnFlg_ManualMode�Ľṹ�ṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/

typedef struct
{
    /* <BEGIN DTS2014042105131 t00173447 2014/2/24 modified */
    VOS_UINT16 usAutoSearchHplmnFlg; /*Range:[0,3]*/
    /* <END DTS2014042105131 t00173447 2014/2/24 modified */
}NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU
 �ṹ˵��  : NV SrchHplmnFlg_AutoMode�Ľṹ�ṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usEHPlmnSupportFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usStkSteeringOfRoamingSupportFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_SCAN_CTRL_STRU
 �ṹ˵��  : ��¼en_NV_Item_Scan_Ctrl_Para (9080)NV�����ݣ���ʶ�������ƹ����Ƿ�ʹ��
  1.��    ��   : 2012��06��11��
    ��    ��   : l60609
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Scan_Ctrl_Para NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserved;                             /* ���� */
}NVIM_SCAN_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_ID_STRU
 �ṹ˵��  : PLMN�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_NVIM_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_ID_STRU
 �ṹ˵��  : en_NV_Item_Network_Name_From_MM_Info�Ľṹ

 1.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_NVIM_MAX_OPER_SHORT_NAME_LEN];/* ��ǰפ��������Ӫ�̵Ķ����� */
    VOS_UINT8                           aucOperatorNameLong[NAS_NVIM_MAX_OPER_LONG_NAME_LEN];  /* ��ǰפ��������Ӫ�̵ĳ����� */
}NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU
 �ṹ˵��  : en_NV_Item_OPERLOCK_PLMN_INFO NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBlackPlmnLockNum;                     /* ֧�ֺ������ĸ���,����Ϊ0ʱ��ʾ��֧�ֺ����� */
    NAS_NVIM_PLMN_ID_STRU               astBlackPlmnId[NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_AIS_ROAMING_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_AIS_ROAMING_Config NV������
 1.��    ��   : 2012��5��17��
   ��    ��   : z40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* �������Ƿ�� */
    VOS_UINT8                           ucHighPrioRatType;                              /* ����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
    NAS_NVIM_PLMN_ID_STRU               stHighPrioPlmnId;                       /* ����֧�ֵĸ����ȼ���PLMN ID ,��ʹפ����HPLMN��,��PLMNID�����ȼ�Ҳ�ϸ�*/
    NAS_NVIM_PLMN_ID_STRU               stSimHPlmnId;                           /* SIM����HPLMN ID */
}NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU;
 /* Added by l00130025 for DTS2012012903053, 2012-05-15 begin */

/*****************************************************************************
 �ṹ��    : NAS_MML_USER_AUTO_RESEL_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_User_Auto_Resel_Switch NV������,UserResecl�����Ƿ�ʹ��
 1.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton����֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAutoReselActiveFlg;                   /* �Ƿ�����LTE�������α��:VOS_TRUE ��ʾ����LTE�������� VOS_FALSE ��ʾ��ֹLTE�������� */
    VOS_UINT8                           ucReserve;
}NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU;
/* Added by l00130025 for DTS2012012903053, 2012-05-15 end */
/* Added by l00130025 for DTS2012060400029, 2012-06-09 begin */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU
 �ṹ˵��  :  en_NV_Item_PRIO_HPLMNACT_CFG NV��ṹ
 1.��    ��   : 2012��6��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012060400029:��Ӷ�HPLMNAct���Ƚ��뼼���Ķ��ƣ�ĿǰUSim����HPLMNACT�ܶ಻֧��L
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;        /* NV��Ч��־, 1: ��Ч��0����Ч */
	VOS_UINT8                            ucReserved;      /* ���ֽڶ��� */
    VOS_UINT16                           usPrioHplmnAct;      /*���Ƶ����Ƚ��뼼��*/
}NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MML_NVIM_AVAIL_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_SEARCH_TIMER_INFO NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer��ʱ����һ�ε�ʱ�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer��ʱ����һ�εĴ��� */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer��ʱ����˯��ʱ�� */
    VOS_UINT32                          ulDeepSearchTimeCount;
}NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU
 �ṹ˵��  : en_NV_Item_OPERLOCK_PLMN_INFO_WHITE NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWhitePlmnLockNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    NAS_NVIM_PLMN_ID_STRU               astWhitePlmnId[NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_SUPPORT_CPHS_FLAG NV��ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usSupportFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU;

/* Added by l60609 for B060 Project, 2012-2-20, Begin   */
/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : en_NV_Item_PREVENT_TEST_IMSI_REG�ṹ
  1.��    ��   : 2012��2��22��
    ��    ��   : w00199382
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucStatus;                               /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                               ucActFlg;
}NAS_PREVENT_TEST_IMSI_REG_STRU;
/* Added by l60609 for B060 Project, 2012-2-20, End   */
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : en_NV_Item_PREVENT_TEST_IMSI_REG�ṹ
  1.��    ��   : 2012��2��22��
    ��    ��   : w00199382
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnSearchPowerOn;
    VOS_UINT8   ucReserve;
}NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU;

/* Modified by z00161729 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-4-5, begin */

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_NVIM_ITEM_MAX_IMSI_LEN];        /* �ϴα����IMSI������ */
}NAS_NVIM_TIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulAutoStart;
}NAS_MMA_NVIM_AUTO_START_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU
 �ṹ˵��  : en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT NV��ṹ
  1.��    ��   : 2011��8��5��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSingleDomainFailPlmnSrchFlag;         /* DT�������󣬵���ע�ᱻ�ܺ���Ҫ�������� */
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PREVENT_TEST_IMSI_REG_STRU
 �ṹ˵��  : NAS_PREVENT_TEST_IMSI_REG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT8  aucPsLocInfo[NAS_NVIM_PS_LOCI_SIM_FILE_LEN];
}NAS_NVIM_PS_LOCI_SIM_FILES_STRU;

/* Added by j00174725 for DTS2016040901340, 2016-04-10, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_CS_LOCI_SIM_FILES_STRU
 �ṹ˵��  : en_NV_Item_Cs_Loci  NV�ṹ
  1.��    ��   : 2016��4��10��
    ��    ��   : j00174725
    �޸�����   : DTS2016040901340
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucTmsi[NAS_MAX_TMSI_LEN];
    VOS_UINT8                           aucLastLai[NAS_SIM_MAX_LAI_LEN];
    VOS_UINT8                           ucLauStaus;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_CS_LOCI_SIM_FILES_STRU;
/* Added by j00174725 for DTS2016040901340, 2016-04-10, end */

/*****************************************************************************
 �ṹ��    : NAS_MML_NVIM_GPRS_GEA_ALG_CTRL_STRU
 �ṹ˵��  : en_NV_Item_GEA_SUPPORT_CTRL NV��ṹ
 1.��    ��   : 2011��7��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucStatus;                                /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                          ucGeaSupportCtrl;                        /* �ն�����:GPRS GEA�㷨֧�ֿ��� */
}NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_LTE_CS_SERVICE_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item_Lte_Cs_Service_Config NV�����ݣ�LTE֧�ֵ�csҵ������
  1.��    ��   : 2011��10��28��
    ��    ��   : z00161729
    �޸�����   : �½�
  2.��    ��   : 2013��09��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ���޸Ľṹ������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;    /* en_NV_Item_Lte_Cs_Service_Config NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucLteCsServiceCfg;  /* LTE֧�ֵ� cs��ҵ������*/
}NAS_NVIM_LTE_CS_SERVICE_CFG_STRU;
/* Added by z00161729 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-2-14, begin */

/* Added by w00167002 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-2-25, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU
 �ṹ˵��  : NVIM���е�����CSFB HO���̵�ϵͳ��Ϣʱ����NV��δ�����򲻵�ϵͳ��Ϣֱ��ע��
 1.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucWaitSysinfoTimeLen;
}NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU;
/* Added by w00167002 for V7R1C50 CSFB&PPAC&ETWS&ISR, 2012-2-25, end */



/* delete by z00234330 for DTS201300600336, 2013-10-09, begin */
/* delete by z00234330 for DTS201300600336, 2013-10-09, end */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU
 �ṹ˵��  : en_NV_Item_Lte_Internation_Roam_Config NV��ṹ
 1.��    ��   : 2012��3��14��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2012��4��25��
   ��    ��   : w00176964
   �޸�����   : DTS2012042403564:�޸�NV��ȡ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           aucRoamEnabledMccList[20];/* �������εĹ������б� */
}NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU;

/* <BEGIN DTS2014042105131 t00173447 2014/2/24 modified */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ROAM_RPLMN_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_Roam_Search_Rplmn_Config NV��ṹ
 1.��    ��   : 2014��2��24��
   ��    ��   : t00173447
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRoamRplmnflg;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                         aucRoamEnabledMccList[5];/* �������εĹ������б� */
}NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU;
/* END DTS2014042105131 t00173447 2014/2/24 modified> */

/* Modified by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU
 �ṹ˵��  : en_NV_Item_Close_SMS_Capability_Config NV��ṹ
 1.��    ��   : 2013��3��11��
   ��    ��   : w00176964
   �޸�����   : close sms capability NV�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU;
/* Modified by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_STRU
 �ṹ˵��  : en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
  2.��    ��   : 2013��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2013121206933:�Ǹ����ȼ����øߵ����������簴syscfg���ý��뼼�����ȼ�����9055 nv�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWcdmaPriorityGsmFlg;                  /* H3G��������W����������G*/

    /* Modified by z00161729 for DTS2013121206933, 2013-12-13, begin */
    VOS_UINT8                           ucSortAvailalePlmnListRatPrioFlg;    /* �Ƿ�syscfg���ý��뼼�����ȼ�����ߵ����������б��ʶ��1:��; 0:���Ǹ��������簴���������������粻����*/
    /* Modified by z00161729 for DTS2013121206933, 2013-12-13, end */
}NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPsOnlyCsServiceSupportFlg;            /* ����������ΪPS ONLYʱ���Ƿ�֧��CS����źͺ���ҵ��(�������г���)*/
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_NVIM_CCBS_SUPPORT_FLG NV��ṹ
  1.��    ��   : 2012��03��03��
    ��    ��   : S62952
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /* CCBS(��æ�������)ҵ��*/
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_NVIM_CCBS_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU
 �ṹ˵��  : en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT NV��ṹ
 1.��    ��   : 2012��6��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&t&DCM�½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          aulCustommMccList[10];                   /* �������εĹ������б� */
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU;

/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, begin */

/*****************************************************************************
 �ṹ��    : NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_ACTING_PLMN_SUPPORT_FLAG NV��ṹ
  1.��    ��   : 2011��06��11��
    ��    ��   : W00166186
    �޸�����   : AT&T&DCM�½��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved;
}NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU;

/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, end */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU
 �ṹ˵��  : en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG NV��ṹ
  1.��    ��   : 2011��06��11��
    ��    ��   : W00166186
    �޸�����   : AT&T&DCM�½��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU;

/* Added by w00166186 for V7R1C50 AT&T&DCM, 2012-6-11, begin */


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
 �ṹ˵��  : ����ע�ᱻ�ܶ��ƶ����ṹ
 1.��    ��   : 2012��6��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&t&DCM�½�
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enRegCause;
    NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8                      enDomain;
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enAction;
}NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU
 �ṹ˵��  : ����ע�ᱻ�ܶ���en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST�ṹ
 1.��    ��   : 2012��6��11��
   ��    ��   : W00166186
   �޸�����   : AT&T&t&DCM�½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucActiveFlag;
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               auReserv[2];
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU         astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_SIM_FORMAT_PLMN_ID
 �ṹ˵��  : Sim PLMN ID�Ĵ洢�ṹ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_SIM_FORMAT_PLMN_ID;

/*****************************************************************************
 �ṹ��    : NAS_UTRANCTRL_NVIM_CURRENT_UTRAN_MODE_STRU
 �ṹ˵��  : ��¼en_NV_Item_Utran_Mode NV������
 1.��    ��   : 2012��7��13��
   ��    ��   : w00167002
   �޸�����   : V7R1C50_GUTL_PhaseI:�¼�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranMode;                            /* ��ǰ֧�ֵ�UTRANģʽ */
    VOS_UINT8                           ucReserve;
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU;

/* Added by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-8, begin */
/*****************************************************************************
 �ṹ��    : NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU
 �ṹ˵��  : ��¼en_NV_Item_Utran_Mode_Auto_Switch NV������
 1.��    ��   : 2012��8��7��
   ��    ��   : w00167002
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0��UTRANģʽΪFDD 1��UTRANģʽΪTDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* ֧��TD����Ĺ��ҺŸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ����IMS PLMN����UTRANģʽ�Ƿ�AUTO SWITCHʱ����ǰIMSI��PLMN�ڴ��б��еĶ�֧���Զ��л�������̶�ΪWģ */
    VOS_UINT8                           aucReserve[1];

    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU;

/* Added by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-8, end */

/* Added by w00167002 for DTS2013112006986, 2013-11-18, begin */


/*****************************************************************************
 �ṹ��    : NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU
 �ṹ˵��  : en_NV_Item_UTRAN_TDD_SMC_FLAG NV��ṹ
 1.��    ��   : 2013��7��25��
   ��    ��   : w00167002
   �޸�����   : ������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                TD�²�����SMC���̡�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����CS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����PS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU;

/* Added by w00167002 for DTS2013112006986, 2013-11-18, end */

/* Added by s00190137 for ACC&SPLMN, 2013-10-15 Begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU
 �ṹ˵��  : NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU�ṹ�����Ʒ�HPLMN/RPLMN
             ��������ֹ���Ƿ���PLMN���� en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG
 1.��    ��   : 2013��10��15��
   ��    ��   : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   aucReserve[3];
}NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU;


/* Modified by s00190137 for 256 EOPLMN, 2013-11-26, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU
 �ṹ˵��  : NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU NVIM���е��û����õ�OPLMN
 1.��    ��   : 2013��10��15��
   ��    ��   : s00190137
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU
 �ṹ˵��  : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU NVIM���е��û����õ�OPLMN
 1.��    ��   : 2013��11��26��
   �޸�����   : ��NV֧�ֵ����OPLMN������չ��256��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT16                          usOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           aucReserve[3];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU;
/* Added by s00190137 for ACC&SPLMN, 2013-10-15 End */
/* Modified by s00190137 for 256 EOPLMN, 2013-11-26, end */

/* Added by c00188733 for DPLMN&NPLMN, 2014-7-14, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_CMCC_Cfg_Dplmn_Nplmn NVIM
            en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn
            en_NV_Item_CT_Cfg_Dplmn_Nplmn
            �е�DPLMN NPLMN������Ϣ
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����Ż�������������DPLMN NPLMN
 2.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* �������õ�Dplmn�ĸ��� */
    VOS_UINT16                         usNplmnListNum;                                       /* �������õ�Nplmn�ĸ��� */

    /* DPLMN����,ÿ6���ֽڴ���һ��dplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)����6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)*/
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN];

    /* NPLMN����,ÿ6���ֽڴ���һ��nplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)����6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)*/
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN];/* NPLMN����*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU
 �ṹ˵��  : en_NV_Item_CT_Cfg_Dplmn_Nplmn_Flag NVIM
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����Ż�������������DPLMN NPLMNʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usCfgDplmnNplmnFlag;
    VOS_UINT8                          ucCMCCHplmnNum;
    VOS_UINT8                          aucCMCCHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucUNICOMHplmnNum;
    VOS_UINT8                          aucUNICOMHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucCTHplmnNum;
    VOS_UINT8                          aucCTHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          aucReserve[3];
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU;


/* Added by c00188733 for DPLMN&NPLMN, 2014-7-14, end */
/* Added by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-10, begin */

/*****************************************************************************
 �ṹ��    : NAS_MML_USER_CFG_EHPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Ehplmn NVIM���е��û����õ�Ehplmn List
 1.��    ��   : 2012��8��9��
   ��    ��   : w00167002
   �޸�����   : V7R1C50_GUTL_PhaseII:CMCC����EHPLMN����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucEhplmnListNum;                        /* �û����õ�EHplmn�ĸ��� */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astEhPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU;
/* Added by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-10, end */

/* Added by wx270776 for DTS2014121701015, 2014-12-19, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Ehplmn NVIM���е��û����õ������Ehplmn List��
 1.��    ��   : 2014��12��19��
   ��    ��   : wx270776
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulNvimEhplmnNum;
    NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU    astNvimEhplmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM];     
}NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU;
/* Added by wx270776 for DTS2014121701015, 2014-12-19, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PLMN_WITH_RAT_STRU
 �ṹ˵��  : NAS MML PLMN�ͽ��뼼���ṹ
 1.��    ��   : 2012��8��9��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_NVIM_PLMN_WITH_RAT_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_DISABLED_RAT_PLMN_INFO NV��ṹ
  1.��    ��   : 2012��8��15��
    ��    ��   : w00176964
    �޸�����   : �½�
  2.��    ��   : 2015��4��18��
    ��    ��   : w00167002
    �޸�����   : DTS2015032709270:NV������ֹ����ĸ���Ϊ8����  
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDisabledRatPlmnNum;                   /* ֧�ֽ�ֹ���뼼����PLMN����,����Ϊ0��ʾ��֧�ָ����� */

    /* Modified by w00167002 for DTS2015032709270, 2015-4-18, begin */
    NAS_MMC_NVIM_PLMN_WITH_RAT_STRU     astDisabledRatPlmnId[NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM];/* ��ֹ���뼼����PLMN��RAT��Ϣ */
    /* Modified by w00167002 for DTS2015032709270, 2015-4-18, end */
    
}NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU;
/* Added by w00176964 for  V7R1C50_GUTL_PhaseII, 2012-8-15, end */

/* Added by l00208543 for RatBlackListAccordSimType, 2013-11-01, begin */
/*****************************************************************************
 ö����    : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
 �ṹ˵��  :
 1.��    ��: 2013��11��01��
   ��    ��: l00208543
   �޸�����: ����
*****************************************************************************/
enum NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /* ����δ���� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /* �������������� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /* �������������� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
 �ṹ˵��  :
 1.��    ��: 2013��11��01��
   ��    ��: l00208543
   �޸�����: ����
*****************************************************************************/
enum NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRAN����WCDMA/TDS-CDMA */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU
 �ṹ˵��  : en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config NV��ṹ
  1.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : �½�

    ucSwitchFlag        �������ͣ�0�����
                                  1: astImsiPlmnList �����ڵĿ����ý�ֹRAT���ܣ�
                                  2���Բ���astImsiPlmnList �����еĿ����ý�ֹRAT����
    ucImsiPlmnListNum   SIM����Ŀ�����֧��16��
    ucForbidRatListNum  ��ֹRAT����Ŀ�����ֵ֧�� 8����Ŀǰ��֧��NV�����ý�ֹLTE���߽�ֹLTE+UTRAN��
                                                       NV������������ֹ������ʽ�������Ϊ�ǷǷ�������
    astImsiPlmnList     SIM���б����֧��16��
    aucForbidRatList    ��ֹ��RAT�����ֵ֧�� 2����Ŀǰ��֧��NV�����ý�ֹLTE���߽�ֹLTE+UTRAN��
                                                   NV������������ֹ������ʽ�������Ϊ�ǷǷ�������
                        0: GSM
                        1: UTRAN
                        2: E-UTRAN
                        ����ֵΪ��Чֵ
*****************************************************************************/
typedef struct
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8  enSwitchFlag;                                         /*�����Ƿ���Ч�����ܵ�����  */
    VOS_UINT8                                               ucImsiListNum;                                        /*������Ч��SIM����Ŀ(������/������)  */
    VOS_UINT8                                               ucForbidRatNum;                                       /*��ֹRAT����Ŀ  */
    VOS_UINT8                                               aucReserve[1];
    NAS_SIM_FORMAT_PLMN_ID                                  astImsiList[NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM];        /* SIM���б� (������/������) */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            aenForbidRatList[NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM];    /*��ֹ�Ľ��뼼��  */
}NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU;
/* Added by l00208543 for RatBlackListAccordSimType, 2013-11-01, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU
 �ṹ˵��  : NVIM���е�����csfb ��������gu��lai�ı䣬mm�Ƚ���lau�����Ƚ��к���
 1.��    ��   : 2012��8��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT8                           aucRserved[1];
}NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
 �ṹ˵��  : en_NV_Item_PLMN_EXACTLY_COMPARE_FLG NV��ṹ
  1.��    ��   : 2012��08��16��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������,�½��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;
    VOS_UINT8                           aucRsv[3];                         /* ����*/
}NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Hplmn_Register_Ctrl_Flg NV��ṹ
 1.��    ��   : 2012��11��29��
   ��    ��   : w00176964
   �޸�����   : HPLMNע�ᱻ�ܺ��Ƿ�����ע����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMNע����Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU;
/* Added by w00176964 for DTS2012112902395, 2012-11-29, end */
/*****************************************************************************
�ṹ��    : NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU
�ṹ˵��  : �ź����������ϱ����������Ϣ
1.��    ��  : 2012��11��21��
  ��    ��  : z00161729
  �޸�����  : ֧��^cerssi�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSignThreshold;    /* �źű仯����,��RSSI�仯������ֵ��
                                                                                  �������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    /* Modified by t00212959 for DTS2013010809978, 2013-1-9, begin */
    VOS_UINT8                                               ucMinRptTimerInterval;     /* ����ϱ���ʱ��   */
    /* Modified by t00212959 for DTS2013010809978, 2013-1-9, end */
} NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU;
/* Modified by z00161729 for cerssi and cnmr, 2012-11-21, end */

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU
 �ṹ˵��  : en_NV_Item_H3g_Ctrl_Flg NV��ṹ
 1.��    ��   : 2013��4��10��
   ��    ��   : w00176964
   �޸�����   : H3G���Ƴ������Ʊ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucH3gCtrlFlg;                           /* H3G���Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU
 �ṹ˵��  : NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : ��ֲ
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usUcs2Customization;
}NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU;

/*****************************************************************************
 �ṹ��    : SMS_TIMER_LENGTH_STRU
 �ṹ˵��  : ����Э�鶨ʱ��ʱ���ṹ

1. ��    ��   : 2012��12��28��
   ��    ��   : l00167671
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_NVIM_TIMER_LENGTH_STRU;

/* Add by z40661 for DTS2012101809567 , 2012-09-25, end */

/*****************************************************************************
 �ṹ��    : NVIM_PRIVATE_CMD_STATUS_RPT_STRU
 �ṹ˵��  : �Ƿ������ϱ���Ϣ
 1.��    ��   : 2013��5��10��
   ��    ��   : s00217060
   �޸�����   : �����ϱ�AT�������������C����Ŀ�����ϱ�NV�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucStatusRptGeneralControl;        /* ˽�������Ƿ�����״̬�ϱ� 0:���ϱ���1:�ϱ� */
}NVIM_PRIVATE_CMD_STATUS_RPT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SPECIAL_ROAM_STRU
 �ṹ˵��  : en_NV_Item_Special_Roam_Flag NV��ṹ
  1.��    ��   : 2011��7��20��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ����  */
    VOS_UINT8                           ucSpecialRoamFlg;                         /* Vplmn��Hplmn��ͬ������ʱ,�Ƿ�����ص�Hplmn,1:����0:������ */
}NAS_MMC_NVIM_SPECIAL_ROAM_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU
 �ṹ˵��  : NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usEnhancedHplmnSrchFlg;
}NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU
 �ṹ˵��  : NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucCcbsSupportFlg;
    VOS_UINT8   ucReserve;
}NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU;

/* Added by l00208543 for DTS2013082902121, 2013-8-30, begin */
/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_TIMER_LEN_STRU
 �ṹ˵��  : NAS_CC_NVIM_TIMER_LEN_STRU�ṹen_NV_Item_CC_TimerLen
  1.��    ��   : 2013��8��30��
    ��    ��   : l00208543
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucT305Len;
    VOS_UINT8   ucT308Len;
    VOS_UINT8   aucReserve[2];
}NAS_CC_NVIM_TIMER_LEN_STRU;
/* Added by l00208543 for DTS2013082902121, 2013-8-30, end */

/* Added by l00208543 for DTS2013100904573, 2013-10-09, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU
 �ṹ˵��  : NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU�ṹen_NV_Item_ChangeRejectCause_Flg
  1.��    ��   : 2013��10��09��
    ��    ��   : l00208543
    �޸�����   : �½�
  2.��    ��   : 2013��11��19��
    ��    ��   : l00208543
    �޸�����   : �޸ģ�������λ��Ϊö�٣����ӵ������
*****************************************************************************/
typedef struct
{
    /* Added by l00208543 for DTS2013111904411, 2013-11-19, begin */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8           enChangeRegRejCauCfg;
    /* Added by l00208543 for DTS2013111904411, 2013-11-19, end */
    VOS_UINT8   ucPreferredRegRejCau_HPLMN_EHPLMN;             /* HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   ucPreferredRegRejCau_NOT_HPLMN_EHPLMN;         /* ��HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   aucReserve[1];
}NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU;
/* Added by l00208543 for DTS2013100904573, 2013-10-09, end */

/* Added by l00208543 for V9R1 reject 17, 2014-4-29, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU
 �ṹ˵��  : NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU�ṹen_NV_Item_ROAMING_REJECT_NORETRY_CFG
  1.��    ��   : 2014��4��29��
    ��    ��   : l00208543
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucNoRetryRejectCauseNum;
    VOS_UINT8   aucNoRetryRejectCause[NAS_NVIM_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM];
    VOS_UINT8   aucReserve[3];
}NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU;
/* Added by l00208543 for V9R1 reject 17, 2014-4-29, end */

/* Added byl00215384 for DTS2014021006453, 2014-02-18, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU
 �ṹ˵��  : en_NV_Item_Remove_Auth_Rej_CFG NV��ṹ


 1.��    ��   : 2014��2��18��
   ��    ��   : l00215384
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
   VOS_UINT8                           ucIgnoreAuthRejFlg;
   VOS_UINT8                           ucMaxAuthRejNo;
   VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU;
/* Added byl00215384 for DTS2014021006453, 2014-02-18, end */

/*****************************************************************************
 �ṹ��    : NAS_NV_GWMAC_ADDR_STRU
 �ṹ˵��  : NV_GWMAC_ADDR(39026)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved1;
    VOS_UINT8 aucE5GwMacAddr[18];
}NAS_NV_GWMAC_ADDR_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU
 �ṹ˵��  : E5_RoamingWhiteList_Support_Flg(39330)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucE5_RoamingWhiteList_Support_Flg[2];
}NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU
 �ṹ˵��  : NDIS_DIALUP_ADDRESS(39330)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNDIS_DIALUP_ADDRESS;
}NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NV_BREATH_LED_STR_STRU
 �ṹ˵��  : NV_BREATH_LED_STR(9051)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucBreOnTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreOffTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreRiseTime; /*Range:[0,5]*/
    VOS_UINT8 ucBreFallTime; /*Range:[0,5]*/
}NAS_NVIM_NV_BREATH_LED_STR_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NV_WIFI_Key_STRU
 �ṹ˵��  : NV_WIFI_Key(50012)�ṹ(����)
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
VOS_UINT8  aucwlAuthMode[16];
VOS_UINT8  aucBasicEncryptionModes[5];
VOS_UINT8  aucWPAEncryptionModes[5];
VOS_UINT8  aucwlKeys1[27];
VOS_UINT8  aucwlKeys2[27];
VOS_UINT8  aucwlKeys3[27];
VOS_UINT8  aucwlKeys4[27];
VOS_UINT32 ulwlKeyIndex;
VOS_UINT8  aucwlWpaPsk[65];
VOS_UINT8  ucwlWpsEnbl;
VOS_UINT8  ucwlWpsCfg;
VOS_UINT8  ucReserved;
}NAS_NVIM_NV_WIFI_KEY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_NV_PRI_VERSION_STRU
 �ṹ˵��  : NV_PRI_VERSION(50023)�ṹ
  1.��    ��   : 2013��5��22��
    ��    ��   : l00167671
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
VOS_UINT8 aucPRIVersion[32];
VOS_UINT8 aucReserve[32];
}NAS_NVIM_NV_PRI_VERSION_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_SYSTEM_APP_CONFIG_STRU
�ṹ˵��  : en_NV_Item_System_APP_Config(121)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16     usSysAppConfigType;
}NAS_NVIM_SYSTEM_APP_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU
�ṹ˵��  : en_NV_Item_NetworkCapability(8197)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8 aucNetworkCapability[NV_ITEM_NET_CAPABILITY_MAX_SIZE];
}NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_AUTOATTACH_STRU
�ṹ˵��  : en_NV_Item_Autoattach(8202)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usAutoattachFlag;
}NAS_NVIM_AUTOATTACH_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_SELPLMN_MODE_STRU
�ṹ˵��  : en_NV_Item_SelPlmn_Mode(8214)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usSelPlmnMode;
}NAS_NVIM_SELPLMN_MODE_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_ACCESS_MODE_STRU
�ṹ˵��  : en_NV_Item_MMA_AccessMode(8232)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucAccessMode[2];
}NAS_MMA_NVIM_ACCESS_MODE_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_MS_CLASS_STRU
�ṹ˵��  : en_NV_Item_MMA_MsClass(8233)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucMsClass;
    VOS_UINT8   ucReserved;
}NAS_NVIM_MS_CLASS_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_RF_Auto_Test_Flag_STRU
�ṹ˵��  : en_NV_Item_RF_Auto_Test_Flag(8262)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usRfAutoTestFlg;
}NAS_MMA_NVIM_RF_AUTO_TEST_FLAG_STRU;

/*****************************************************************************
�ṹ��    : NAS_NVIM_HPLMN_FIRST_TIMER_STRU
�ṹ˵��  : en_NV_Item_HPlmnFirstTimer(8276)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucHplmnTimerLen;
    VOS_UINT8   ucReserved;
}NAS_NVIM_HPLMN_FIRST_TIMER_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU
�ṹ˵��  : en_NV_Item_NAS_Supported_3GPP_Release(8288)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucSupported3GppRelease[NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE];
}NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_LAST_IMSI_STRU
�ṹ˵��  : en_NV_Item_Last_Imsi(8325)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucValid;
    VOS_UINT8   aucImsi[NAS_MMC_NVIM_MAX_IMSI_LEN];
}NAS_MMC_NVIM_LAST_IMSI_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMA_NVIM_ROAMING_BROKER_STRU
�ṹ˵��  : en_NV_Item_Roaming_Broker(8328)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   aucRoamingBroker[2];
}NAS_MMA_NVIM_ROAMING_BROKER_STRU;

/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU
�ṹ˵��  : en_NV_Item_Use_Single_Rplmn_When_Area_Lost(8343)�ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usUseSingleRplmnFlag;
}NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU;

/* en_NV_Item_EquivalentPlmn 8215 */
/*****************************************************************************
�ṹ��    : NVIM_PLMN_VALUE_STRU
�ṹ˵��  : en_NV_Item_EquivalentPlmn(8215)�ṹ����#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_VALUE_STRU;

/*****************************************************************************
�ṹ��    : NVIM_EQUIVALENT_PLMN_LIST_STRU
�ṹ˵��  : en_NV_Item_EquivalentPlmn(8215)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8             ucCount;
    NVIM_PLMN_VALUE_STRU  struPlmnList[NVIM_MAX_EPLMN_NUM];
    VOS_UINT8             aucReserve[3];   /*NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն�*/
}NVIM_EQUIVALENT_PLMN_LIST_STRU;

/*en_NV_Item_Support_Freqbands 8229*/
/*
NVIM_UE_SUPPORT_FREQ_BAND_STRU�ṹ˵��:
usWcdmaBand��usGsmBand��Bitλ��ʾ�û����õ�Ƶ�Σ�bit1����Ƶ��I,bit2����Ƶ��II,
��������,����λΪ1,��ʾ֧�ָ�Ƶ��.�±��Ǳ���λ��Ƶ�ζ�Ӧ��ϵ:
-------------------------------------------------------------------------------
        bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
-------------------------------------------------------------------------------
WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
        spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
-------------------------------------------------------------------------------
GSMƵ�� 1900(VIII) 1800(VII) E900(VI) R900(V) P900(IV) 850(III)  480(II)  450(I)  oct3
        spare      spare     spare    spare   spare    spare     spare    700(IX) oct4
-------------------------------------------------------------------------------
aucUeSupportWcdmaBand��aucUeSupportGsmBand�������ʾUE֧�ֵ�Ƶ��,���Դ洢˳���
�Ⱥ��ʾƵ������˳��,��0xff��ʾ��Ч.

����:
oct1-oct4�ֱ��ǣ�0x03,0x00,0x7B,0x00
   ������û�����Ƶ��Ϊ��W��WCDMA-I-2100, WCDMA-II-1900
                         G��850(III),P900(IV),R900(V),E900(VI),1800(VII)
oct5-oct16�ֱ���:2,5,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��WƵ��I,II,V,����˳����:II,V,I.
oct17-oct28�ֱ���:4,5,8,7,6,3,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��GƵ��III,IV,V,VI,VII,VIII,����˳����:IV,V,VIII,VII,VI,III.
*/
/*****************************************************************************
�ṹ��    : NAS_NVIM_UE_SUPPORT_FREQ_BAND_STRU
�ṹ˵��  : en_NV_Item_Support_Freqbands(8229)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
2.��    ��   : 2014��8��1��
  ��    ��   : b00269685
  �޸�����   : NV���
*****************************************************************************/
typedef struct
{
    /* Modified by w00176964 for DTS201212345678, 2012-3-5, begin */
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT32                  ulGsmBand;
    /* Modified by w00176964 for DTS201212345678, 2012-3-5, end */
    /* Modified by b00269685 for DTS2014071803206, 2014-8-1, begin */
    VOS_UINT8                   aucReserved1[12];
    VOS_UINT8                   aucReserved2[12];
    VOS_UINT8                   aucReserved[24];        /* Ϊ��֤nv����һ�±��� */
    /* Modified by b00269685 for DTS2014071803206, 2014-8-1, end */
}NVIM_UE_SUPPORT_FREQ_BAND_STRU;

/*en_NV_Item_Roam_Capa 8266*/
/*****************************************************************************
 �ṹ��    : NAS_NVIM_ROAM_CFG_INFO_STRU
 �ṹ˵��  : en_NV_Item_Roam_Capa(8266) NV��ṹ#
  1.��    ��   : 2011��8��18��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*��¼���������Ƿ񼤻�,VOS_FALSE:������,VOS_TRUE:����*/
    VOS_UINT8                               ucRoamCapability;                   /*��¼�û����õ���������*/
}NAS_NVIM_ROAM_CFG_INFO_STRU;

/*en_NV_Item_CustomizeService 8271*/
/*****************************************************************************
�ṹ��    : NAS_NVIM_CUSTOMIZE_SERVICE_STRU
�ṹ˵��  : en_NV_Item_CustomizeService(8271)�ṹ#
            ���ڱ�����Ӫ�̶���Ҫ��ҵ������
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;           /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                          ulCustomizeService; /*�ն�˵������1��byte��Ϊ��û�пն��������4byte����3byte����*/
}NAS_NVIM_CUSTOMIZE_SERVICE_STRU;

/*en_NV_Item_RPlmnWithRat 8275*/
/*****************************************************************************
 �ṹ��    : NAS_MM_NVIM_RPLMN_WITH_RAT_STRU
 �ṹ˵��  : en_NV_Item_RPlmnWithRat(8275) NV��ṹ
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stGRplmn;                               /* G RPLMN��Ϣ */
    NAS_NVIM_PLMN_ID_STRU               stWRplmn;                               /* W RPLMN��Ϣ*/
    VOS_UINT8                           ucLastRplmnRat;                         /* �ϴιػ�ʱפ������Ľ��뼼��0:GSM;1:WCDMA;0xFF:��Чֵ */
    VOS_UINT8                           ucLastRplmnRatEnableFlg;                /* 0:NV δ����; 1:NV���� */
    VOS_UINT8                           aucReserved[2];                          /* ���� */
}NAS_NVIM_RPLMN_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU
 �ṹ˵��  : en_NV_Item_SearchHplmnTtimerValue NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucStatus;                              /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                            ucReserve;                             /* ����δ�� */
    VOS_UINT16                           usSrchHplmnTimerValue;                 /* VPLMN�·��״���HPLMNʱ��,��λ:���� */

}NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG NV��ṹ
 1.��    ��   : 2015��4��28��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTriggerBGSearchFlag;  /* 0: mmc�յ������ȼ�PLMN����ʱ������BG SEARCH; 1:mmc�յ������ȼ�PLMN����ʱ����BG SEARCH */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usSearchDelayLen;             /* BG SEARCH Delay ʱ��, ��λ: ��  */
}NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */


/*en_NV_Item_EFust_Service_Cfg 8285*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU
 �ṹ˵��  : en_NV_Item_EFust_Service_Cfg(8285) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV���Ƿ񼤻�0��δ���1������ */
    VOS_UINT8                           ucForbidReg2GNetWork;                   /* 0��EFust GSM�����־������ȥʹ�ܡ��������������EFust 27��38������GSM���롣
                                                                                   �������ö�������UE����SIM���е�EFust 27��38λ��ȷ���Ƿ�����GSM���룬
                                                                                   ���EFUST�ļ���ֹ����λ��ͬʱ����Ϊ0�������ֹGSM����ע�ᣬ����GSM���Խ��롣
                                                                                   ע�⣺SIM���в�����EFust 27��38λ����˸ù��ܽ����USIM����Ч��1��EFust GSM�����־������ʹ�� */
    VOS_UINT8                           ucForbidSndMsg;                         /* 0��EFust���ŷ��ͱ�־������ȥʹ�ܡ��������������EFust 10��12������SMS���͡�
                                                                                   1��EFust���ŷ��ͱ�־������ʹ�ܡ�NV���ö�������UE����SIM����EFUST��10��12λ��
                                                                                   ȷ���Ƿ��ֹ���ŷ���,�����ֹ����λ��ͬʱ����Ϊ0�������ֹ����SMS�����򣬶��ſ��Է��͡�*/
    VOS_UINT8                           ucReserved[13];
}NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU;

/*en_NV_Item_UE_MSCR_VERSION 8289*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_MSCR_VERSION_STRU
 �ṹ˵��  : en_NV_Item_UE_MSCR_VERSION(8289) NV��ṹ
 1.��    ��   : 2011��7��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeMscrVersion;                        /* �ն��ϱ���SGSN�汾 */
}NAS_MMC_NVIM_MSCR_VERSION_STRU;

/*en_NV_Item_UE_SGSNR_VERSION 8290*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SGSNR_VERSION_STRU
 �ṹ˵��  : en_NV_Item_UE_SGSNR_VERSION(8290) NV��ṹ
 1.��    ��   : 2011��7��14��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeSgsnrVersion;                       /* �ն��ϱ���SGSN�汾 */
}NAS_MMC_NVIM_SGSNR_VERSION_STRU;

/*en_NV_Item_SteeringofRoaming_SUPPORT_CTRL 8292*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU
 �ṹ˵��  : en_NV_Item_SteeringofRoaming_SUPPORT_CTRL(8292) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucCsRejSearchSupportFlg;                /* vodafone��������������,CS��ʧ���Ĵκ��·���������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
}NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU;

/*en_NV_Item_Max_Forb_Roam_La 8320*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU
 �ṹ˵��  : en_NV_Item_Max_Forb_Roam_La(8320) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxForbRoamLaFlg;                     /* NV�����õ�����ֹLA�����Ƿ���Ч: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucMaxForbRoamLaNum;                     /* NV�����õ�����ֹLA���� */
}NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU;

/*en_NV_Item_Default_Max_Hplmn_Srch_Peri 8321*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU
 �ṹ˵��  : en_NV_Item_Default_Hplmn_Srch_Peri(8321) NV��ṹ
  1.��    ��   : 2011��7��20��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDefaultMaxHplmnPeriFlg;               /* Ĭ������HPLMN���������Ƿ���Ч��־,VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucDefaultMaxHplmnTim;                   /* �û����Զ���Ĭ�ϵ�����HPLMN�������� */
}NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU;

/*en_NV_Item_USSD_Apha_To_Ascii 8327*/
/*����USSDת���ַ���*/
/*****************************************************************************
 �ṹ��    : NAS_SSA_NVIM_ALPHA_to_ASCII_STRU
 �ṹ˵��  : en_NV_Item_USSD_Apha_To_Ascii(8327) NV��ṹ
  1.��    ��   : 2011��7��20��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                       ucAlphaTransMode;    /* �ַ���ת��*/
}NAS_SSA_NVIM_ALPHA_to_ASCII_STRU;

/*en_NV_Item_Register_Fail_Cnt 8338*/
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REG_FAIL_CNT_STRU
 �ṹ˵��  : en_NV_Item_Register_Fail_Cnt(8338) NV��ṹ
  1.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvActiveFlag;                         /* ��ǰNV���Ƿ񼤻� */
    VOS_UINT8                           ucRegFailCnt;                           /* NV�����õ�ע��ʧ�ܵĴ�����Ĭ��ֵΪ2����ע��ʧ�����κ��������� */
}NAS_MMC_NVIM_REG_FAIL_CNT_STRU;

/*en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt 8345*/
/* VDF����: CREG/CGREG����<CI>���Ƿ���4�ֽ��ϱ���NV����ƽṹ�� */
/*****************************************************************************
�ṹ��    : NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU
�ṹ˵��  : en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt(8345)�ṹ#
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucStatus;                        /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8   ucCiBytesRpt;                    /* <CI>���ϱ��ֽ�����־��0��2�ֽ��ϱ�, 1��4�ֽ��ϱ� */
}NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU
 �ṹ˵��  : ��¼en_NV_Item__Dell_Reject_Config NV�����ݣ����ű���11,12,13,15,other cause,����ʧ��,����û��Ӧ��ԭ����NV
 1.��    ��   : 2012��3��6��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* ���ű����Ƿ�ʹ�� VOS-TRUE:���ű���֧�� VOS_FALSE:���ű��ܲ�֧�� */
    VOS_UINT8                           aucReserve[1];
}NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU;

/*h00218138, NDIS NV Struct, start, 2013-5-25*/
/* en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME 8344 */
typedef struct
{
    VOS_UINT32                          ulDhcpLeaseHour;    /*Range:[0x1,0x2250]*/
}NDIS_NV_DHCP_LEASE_HOUR_STRU;

typedef struct
{
    VOS_UINT32                          ulIpv6Mtu;          /*Range:[1280,65535]*/
}NDIS_NV_IPV6_MTU_STRU;
/*h00218138, NDIS NV Struct, end, 2013-5-25*/

/*****************************************************************************
�ṹ��    : NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU
�ṹ˵��  : en_NV_Item_CCallState_Rpt_Status nvid 9116(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU
 �ṹ˵��  : PLMN�Ƚ��Ƿ���о�ȷ�Ƚϵķ�ʽ�ı��
 �޸���ʷ  :
 1.��    ��    : 2012��08��7��
   ��    ��    : l00128652
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucPlmnExactlyCompareFlag;               /* PLMN�Ƚ��Ƿ���о�ȷ�Ƚϵķ�ʽ�ı�� */
   VOS_UINT8                            aucRsv[3];                              /* ����λ */
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;

/* Added by z00220246 for DSDA Phase II, 2012-12-25, Begin */
/*****************************************************************************
�ṹ��    : PLATFORM_RAT_TYPE_ENUM
�ṹ˵��  : ���뼼��

  1.��    ��   : 2012��12��25��
    ��    ��   : z00220246
    �޸�����   : ����
*******************************************************************************/
enum PLATFORM_RAT_TYPE_ENUM
{
    PLATFORM_RAT_GSM,                                                       /*GSM���뼼�� */
    PLATFORM_RAT_WCDMA,                                                     /* WCDMA���뼼�� */
    PLATFORM_RAT_LTE,                                                       /* LTE���뼼�� */
    PLATFORM_RAT_TDS,                                                       /* TDS���뼼�� */
    /* Added by Y00213812 for CDMA 1X Iteration 0, 2014-07-15, begin */
    PLATFORM_RAT_1X,                                                        /* CDMA-1X���뼼�� */
    PLATFORM_RAT_EVDO,                                                      /* CDMA-EV_DO���뼼�� */
    /* Added by Y00213812 for CDMA 1X Iteration 0, 2014-07-15, end*/

    PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 PLATFORM_RAT_TYPE_ENUM_UINT16;

#define PLATFORM_MAX_RAT_NUM            (7)                                    /* ���뼼�����ֵ */

/*****************************************************************************
�ṹ��    : PLATAFORM_RAT_CAPABILITY_STRU
�ṹ˵��  : ƽ̨֧�ֵĽ��뼼��

  1.��    ��   : 2012��12��25��
    ��    ��   : z00220246
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                              /* ���뼼������Ŀ*/
    PLATFORM_RAT_TYPE_ENUM_UINT16        aenRatList[PLATFORM_MAX_RAT_NUM];  /* ���뼼�� */
}PLATAFORM_RAT_CAPABILITY_STRU;
/* Added by z00220246 for DSDA Phase II, 2012-12-25, End */

/*en_NV_Item_Rplmn 8216*/
/*****************************************************************************
 �ṹ��    : NAS_NVIM_RPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_Rplmn(8216) NV��ṹ(�ѷ���)
1.��    ��   : 2013��5��22��
  ��    ��   : m00217266
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRplmnInfo[56];
}NAS_NVIM_RPLMN_INFO_STRU;

/* Modified by z00161729 for V9R1_SVLTE, 2013-6-20, begin */
/*****************************************************************************
 �ṹ��    : SVLTE_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_SVLTE_FLAG NV��ṹ
 1.��    ��   : 2013��6��20��
   ��    ��   : z00161729
   �޸�����   : SVLTE�����Ƿ�֧��:0-��֧�֣�1-֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvlteSupportFlag;                     /* SVLTE�����Ƿ�֧��:0-��֧�֣�1-֧�� */
    VOS_UINT8                           aucReserved[3];                         /* ���� */
}SVLTE_SUPPORT_FLAG_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU
 �ṹ˵��  : en_NV_Item_Enable_Lte_Timer_Len NV��ṹ
 1.��    ��   : 2013��6��3��
   ��    ��   : z00161729
   �޸�����   : enable lte��ʱ��ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv��δ���1:nv��� */
    VOS_UINT8                           ucCsPsMode1EnableLteTimerLen;           /* 1)cs ps mode1 L����ע��eps only�ɹ�cs����#16/#17/#22������������disable lteʱ����enable lte��ʱ��ʱ��
                                                                                   2)cs ps mode1 L����ע��cs eps��ʧ��ԭ��ֵother cause ������������disable lte����enable lte��ʱ��ʱ��,��λ:���ӣ� nv���ʱ���Ϊ0Ĭ��54���� */
    VOS_UINT8                           ucCsfbEmgCallEnableLteTimerLen;         /* L�½��������޷�����csfb��gu��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���ӣ� nv���ʱ���Ϊ0Ĭ��5���� */
    VOS_UINT8                           ucReserved;
}NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU;

/* Modified by z00161729 for V9R1_SVLTE, 2013-6-20, end */

/* Added by c00318887 for ��ֲT3402 , 2015-6-17, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU
 �ṹ˵��  : en_NV_Item_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG NV��ṹ
             ucT3402Flag ��������Disable LTE ���ٴΰ�LTE �ָ�����Ķ�ʱ��ʱ��:
             ���ucT3402Flag ��0����Disable LTE ���ٴΰ�LTE �ָ�����Ķ�ʱ��ʱ����NV_Item_Enable_Lte_Timer_Len  0x2404��9220������ֵ����
             ��� ucT3402Flag ����Ϊ 1�������³�����ʹ��LMM_MMC_T3402_LEN_NOTIFY��Ϣ�еĳ���
            1) EPS ONLY�ɹ�,CS����18,CS����16,17,22,other cause,EPS���Դ����ﵽ5��
            2) ����EPSע�ᱻ�� #19, �����ﵽ���ֵ
            3) ����EPSע�ᱻ�� #301, �����ﵽ���ֵ 
            4) ����EPSע�ᱻ�� #other cause, �����ﵽ���ֵ
            5) ����EPSע�ᱻ�� #401, �����ﵽ���ֵ
 1.��    ��   : 2015��4��28��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT3402Flag;                           /* 0: ��ʹ��LMM_MMC_T3402_LEN_NOTIFY��Ϣ�еĳ���; 1:ʹ��LMM_MMC_T3402_LEN_NOTIFY��Ϣ�еĳ��� */
    VOS_UINT8                           ucHighPrioRatTimerNotEnableLteFlag;    /* 1:�����ȼ�RAT HPLMN TIMER ��ʱ������ENABLE lte��0: �����ȼ�RAT HPLMN TIMER ��ʱ����ENABLE lte */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_DISABLE_LTE_START_T3402_ENABLE_LTE_CFG_STRU;

/* Added by c00318887 for ��ֲT3402 , 2015-6-17, end */


/* Added by z00234330 for DTS2013052301419, 2013-05-23, begin */
/*****************************************************************************
�ṹ��    : NAS_MMC_NVIM_ISR_CFG_STRU
�ṹ˵��  : ISR���������Ϣ
1.��    ��  : 2013��05��23��
  ��    ��  : z00234330
  �޸�����  : ISRͨ��NVIM�ж��Ƿ�֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsrSupport;       /* ISR ???? */
    VOS_UINT8                                               ucReserve1;
} NAS_NVIM_ISR_CFG_STRU;

/* Added by z00234330 for DTS2013052301419, 2013-05-23, end */

/* Added by w00242748 for DTS2013072200933, 2013-7-25, begin */
/*****************************************************************************
 �ṹ��    : CSFB_MT_FOLLOW_ON_SUPPORT_FLAG_STRU
 �ṹ˵��  : en_NV_Item_CSFB_MT_RAU_FOLLOW_ON_FLAG NV��ṹ
 1.��    ��   : 2013��7��25��
   ��    ��   : w00242748
   �޸�����   : Csfb mt�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ
 2.��    ��   : 2014��6��10��
   ��    ��   : w00242748
   �޸�����   : Csfb mo�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg;           /* Csfb mt�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg;           /* Csfb mo�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU;
/* Modified by w00242748 for DTS2014053105098, 2014-6-10, end */
/* Added by w00242748 for DTS2013072200933, 2013-7-25, end */

/* Modified by z00161729 for svlte g-tl ps transfer optimize, 2013-11-18, begin */
/*****************************************************************************
 �ṹ��    : NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU
 �ṹ˵��  : en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG NV��ṹ
  ����˵��: ����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ���ǰ֧�ֵĲ���Ϊ��
  1)  ͨ����һModem��PLMN��Ϣ,����FDD�����Ƿ������Ĳ��ԡ�����GUTL+G�İ汾���������Ѿ�פ���ڹ���G����ʱ������������������FDD�����������ƶ�����ֻ��Ҫ֧��TDDģʽ����
  2)  ͨ��Modem1��GSM�ϱ���L��TDS������Ϣ, Modem0��֧��GSM������£�T/L�������ܹ����ݴ��ݵ�����Ƶ�����������TDS/LTE��
 1.��    ��   : 2013��11��18��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usSolutionMask;/*����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ�Bitλ���Ƹ����������ԣ�bitn=0����n�����Թرգ�bitn=1����n�����Կ�����
                                                         Ŀǰֻ��bit0��bit1 ��Ч��
                                                         BIT0������˫Modem��ͨ����һModem��PLMN��Ϣ����FDD�����Ƿ������Ĳ����Ƿ�������
                                                         BIT1��ͨ��Modem1��GSM�ϱ���L��TDS������Ϣ, Modem0��֧��GSM������£�T/L�������ܹ����ݴ��ݵ�����Ƶ�����������TDS/LTE��
                                                               ���Modem1���ݹ�����������Ϣ�����ڵ�����£�Ҳ��ͨ����ʷƵ��֧��NCELL������������������Ƶ����ucSolution2NcellSearchTimer������
                                                         BIT2~BIT15:Ԥ��*/
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer;       /*����Ƶ������������Ե�һ�׶�ʱ��������λ�룩��*/

   /* Modified by z00161729 for DTS2014012305088, 2014-1-26, begin */
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer2;      /* ����Ƶ������������ԵĶ��׶�ʱ��������λ�룩��*/
   VOS_UINT8                            aucAdditonCfg[4];
   /* Modified by z00161729 for DTS2014012305088, 2014-1-26, end */
}NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;

/* Modified by z00161729 for svlte g-tl ps transfer optimize, 2013-11-18, end */

/* added by l65478 for DTS2013102508485 2014-01-13 begin */
/*****************************************************************************
�ṹ��    : NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU
�ṹ˵��  : en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT(9140)�ṹ
1.��    ��   : 2014��01��13��
  ��    ��   : l65478
  �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucRelFlg;
    VOS_UINT8   ucReserve;
}NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU;
/* added by l65478 for DTS2013102508485 2014-01-13 end */

/* Added by f62575 for DTS2014012600456, 2014-02-10,Begin */
/*****************************************************************************
�ṹ��    : NAS_NVIM_WG_RF_MAIN_BAND_STRU
�ṹ˵��  : en_NV_Item_WG_RF_MAIN_BAND�ṹ
  1.��    ��   : 2014��02��10��
    ��    ��   : f62575
    �޸�����   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND�����޸�Ϊ���ڴ��л�ȡ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWband;                                /* ֧�ֵ�WCDMA����ͨ· */
    VOS_UINT32                          ulWbandExt;                             /* ֧�ֵ�WCDMA����ͨ·��չ�ֶ� */
    VOS_UINT32                          ulGband;                                /* ֧�ֵ�GSM����ͨ· */
}NAS_NVIM_WG_RF_MAIN_BAND_STRU;
/* Added by f62575 for DTS2014012600456, 2014-02-10,End   */


/* Added by f00261443 for VoltePhaseIII , 2013-12-16, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT
 �ṹ˵��  : en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT NV��ṹ
 1.��    ��   : 2013��12��16��
   ��    ��   : f00261443
   �޸�����   : ISR����״̬�£���L��ϵͳ��GU�����LAI��RAIδ�����仯���Ƿ���Ҫ
                ����LAU����RAU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;           /* ISR�������ϵͳ��L�任��GU��LAIδ�ı䣬�Ƿ���Ҫǿ��LAU */
    VOS_UINT8                           ucImsVoiceMMEnable;         /* IMS�ƶ��Թ��� NV */
    VOS_UINT8                           aucReserved[2];             /* ���� */
}NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT;
/* Added by f00261443 for VoltePhaseIII , 2013-12-16, end */

/* Modified by z00161729 for DTS2014022206794, 2014-2-25, begin */
/*****************************************************************************
�ṹ��    : NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU
�ṹ˵��  : en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG�ṹ
  1.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;             /* l disabled��rau�Ƿ���Ҫ��l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ��vos_true:��Ҫ��ȡ��vos_false:�����ȡ*/
    VOS_UINT8                           ucReserved[3];
}NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU;

/* Modified by z00161729 for DTS2014022206794, 2014-2-25, end */

/* Add by f62575 for DTS2014012902032, 2014-02-13, begin */
/*****************************************************************************
�ṹ��    : NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU
�ṹ˵��  : en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG�ṹ
  1.��    ��   : 2014��02��13��
    ��    ��   : f62575
    �޸�����   : DTS2014012902032:
                 NV��en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* �Ƿ񼤻�� */
    VOS_UINT8                           ucCsOnlyDataServiceSupportFlg;          /* PSע�ᱻ��ֹ����£��Ƿ���������ҵ�񴥷�ע��ı�־ */
}NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU;
/* Add by f62575 for DTS2014012902032, 2014-02-13, end */
/* Added by w00176964 for High_Rat_Hplmn_Search, 2014-2-19, begin */
/* Modified by b00269685 for DTS2014101301568, 2014-10-29, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_INFO NV��ṹ
 1.��    ��   : 2014��2��19��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2014��10��25��
   ��    ��   : b00269685
   �޸�����   : ��NV�ѷ�������������ֻ��Ϊ�˱���ͨ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /* �ö�ʱ���Ƿ�ʹ�� */                       /* TD��ʼ�����ѵĴ��� */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU;
/* Modified by b00269685 for DTS2014101301568, 2014-10-29, end */
/* Added by w00176964 for High_Rat_Hplmn_Search, 2014-2-19, end */

/* Added by b00269685 for DTS2014101301568, 2014-10-29, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG NV��ṹ
 1.��    ��   : 2014��10��25��
   ��    ��   : b00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                            /* �ö�ʱ���Ƿ�ʹ�� */
    VOS_UINT8                           ucTdThreshold;                          /* TD��ʼ�����ѵĴ��� */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;
/* Added by b00269685 for DTS2014101301568, 2014-10-29, end */


/* Added by s00217060 for ultra_flash_csfb, 2014-05-30, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_Ultra_Flash_Csfb_Support_Flg NV��ṹ
 1.��    ��   : 2014��5��30��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUltraFlashCsfbSupportFLg;                 /* �Ƿ�֧��ultra flash csfb */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU;
/* Added by s00217060 for ultra_flash_csfb, 2014-05-30, end */

/* Added by B00269685 for DTS2014061603311, 2014-6-13, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_3GPP2_Uplmn_Not_Pref_STRU
 �ṹ˵��  : en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg NV��ṹ
 1.��    ��   : 2014��6��13��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           uc3GPP2UplmnNotPrefFlg;                    /* �Ƿ���3GPP2 pref plmn */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU;
/* Added by B00269685 for DTS2014061603311, 2014-6-13, end */

/* Modified by w00242748 for DTS2014063003419, 2014-7-14, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg NV��ṹ
 1.��    ��   : 2014��7��14��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHighPrioRatPlmnSrchFlg;                  /* �Ƿ��������ȼ����뼼������ */
    VOS_UINT8                           aucReserved1[3];
}NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU;
/* Modified by w00242748 for DTS2014063003419, 2014-7-14, end */

/* Added by b00269685 for DSDS IV, 2014-7-17, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU
 �ṹ˵��  : en_NV_Item_DSDS_END_SESSION_DELAY NV��ṹ
 1.��    ��   : 2014��7��17��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;              /* Lau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;              /* Rau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulReserve1;
    VOS_UINT32                           ulReserve2;
} NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU;
/* Added by b00269685 for DSDS IV, 2014-7-17, end */

/* Added by w00176964 for CDMA 1X Iteration 1, 2014-8-18, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SYSTEM_STRU
 �ṹ˵��  : 1x system�ṹ
 1.��    ��   : 2014��8��18��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usChannel;
}CNAS_NVIM_1X_SYSTEM_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_NVIM_1X_MRU_LIST_STRU
 �ṹ˵��  : en_NV_Item_1X_MRU_LIST NV��ṹ
 1.��    ��   : 2014��8��18��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_SYSTEM_STRU            astSystem[CNAS_NVIM_MAX_1X_MRU_SYS_NUM];
}CNAS_NVIM_1X_MRU_LIST_STRU;

/* Added by w00176964 for CDMA 1X Iteration 1, 2014-8-18, end */

/* Added by h00285180 for DTS2014110307415, 2014-10-20, begin */
/*****************************************************************************
�ṹ����    :NAS_MMC_NVIM_ADAPTION_CAUSE_STRU
ʹ��˵��    :�û���������ԭ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnCause;     /* ����ԭ��ֵ */
    VOS_UINT8                           ucHplmnCause;  /* �û�����ƥ��HPLMN��ԭ��ֵ */
    VOS_UINT8                           ucVplmnCause;  /* �û�����ƥ��VPLMN��ԭ��ֵ */
    VOS_UINT8                           aucReserved[1];
}NAS_MMC_NVIM_ADAPTION_CAUSE_STRU;

/*****************************************************************************
�ṹ����    :NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU
ʹ��˵��    :en_NV_Item_ChangeNWCause_CFG NV��ṹ
*****************************************************************************/
typedef struct
{
    /* CS��ע������(LU)�ܾ�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucCsRegCauseNum; 
    VOS_UINT8                           aucReserved1[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* PS��ע������(ATTACH/RAU)�ܾ�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucPsRegCauseNum;   
    VOS_UINT8                           aucReserved2[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* ����GPRS Detach ���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucDetachCauseNum;  
    VOS_UINT8                           aucReserved3[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astDetachAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* GMM service request���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucPsSerRejCauseNum;   
    VOS_UINT8                           aucReserved4[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* MM ABORT���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucMmAbortCauseNum;    
    VOS_UINT8                           aucReserved5[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astMmAbortAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* CM Service���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucCmSerRejCauseNum;   
    VOS_UINT8                           aucReserved6[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCmSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    VOS_UINT8                           ucHplmnPsRejCauseChangTo17MaxNum; /* HPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucHplmnCsRejCauseChangTo17MaxNum; /* HPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucVplmnPsRejCauseChangTo17MaxNum; /* VPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucVplmnCsRejCauseChangTo17MaxNum; /* VPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */    
}NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU;
/* Added by h00285180 for DTS2014110307415, 2014-10-20, end   */

/* Added by h00285180 for DTS2014110307375 , 2014-11-04, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU
 �ṹ˵��  : en_NV_Item_REL_PS_SIGNAL_CON_CFG NV��ṹ
 1.��    ��   : 2014��11��04��
 ��    ��   : h00285180
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRelPsSignalConFlg;/* �Ƿ�������������������� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulT3340Len;         /* ���õ�GMM T3340��ʱ��,��λ:�� */
}NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU;
/* Added by h00285180 for DTS2014110307375 , 2014-11-04, end */

/* Added by h00285180 for DTS2015010401946, 2015-01-05, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU
 �ṹ˵��  : en_NV_Item_LTE_REJ_CAUSE_14_CFG NV��ṹ
 1.��    ��   : 2015��1��5��
   ��    ��   : h00285180
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRejCause14Flg;               /* �Ƿ���LTE #14ԭ��ܾ��Ż���0: δ������1:���� */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLteRejCause14EnableLteTimerLen; /* LTE #14ԭ��ܾ�ʱ��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���� */ 
}NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU;
/* Added by h00285180 for DTS2015010401946, 2014-01-05, end   */

/* Added by b00269685 for DTS2015031909305, 2015-3-20, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU
 �ṹ˵��  : en_NV_Item_Roam_Display_Cfg NV��ṹ
 1.��    ��   : 2015��3��20��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU;
/* Added by b00269685 for DTS2015031909305, 2015-3-20, end */

/* Added by b00269685 for protect_csfb_mt, 2015-5-4, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_MT_CSFB_PAGING_PROCEDURE_LEN_STRU
 �ṹ˵��  : en_NV_Item_Mt_Csfb_Paging_Procedure_Len NV��ṹ
 1.��    ��   : 2015��5��4��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMtCsfbPagingProcedureLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU;
/* Added by b00269685 for protect_csfb_mt, 2015-5-4, end */

/* added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */
typedef struct
{
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU;
/* added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, end */


/* Added by j00174725 for DTS2015051106584, 2015-04-08, begin */
/*****************************************************************************
 ö����    : NAS_SMS_PS_CONCATENATE_ENUM
 �ṹ˵��  : PS�������������ö�ٶ���
  1.��    ��   : 2015��05��18��
    ��    ��   : j00174725
    �޸�����   : ����
*****************************************************************************/
enum NAS_SMS_PS_CONCATENATE_ENUM
{
    NAS_SMS_PS_CONCATENATE_DISABLE      = 0,
    NAS_SMS_PS_CONCATENATE_ENABLE,

    NAS_SMS_PS_CONCATENATE_BUTT
};
typedef VOS_UINT8 NAS_SMS_PS_CONCATENATE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����  : NAS_NV_SMS_PS_CTRL_STRU
 �ṹ˵��  : PS����ſ���

  1.��    ��   : 2015��05��18��
    ��    ��   : j00174725
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8   enSmsConcatenateFlag;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} NAS_NV_SMS_PS_CTRL_STRU;
/* Added by j00174725 for DTS2015051106584, 2015-04-08, End */



/* Added by j00174725 for ECC(DTS2017021705267), 2017-02-18, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_EMC_CATE_SUPPORT_ECALL_CFG_STRU
 �ṹ˵��  : en_NV_Item_Emc_Cate_Support_ECALL_CFG NV��ṹ
 1. ��    ��   : 2017��02��18��
    ��    ��   : j00174725
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmcCateSupportEcallFlag; 
    VOS_UINT8                           ucBit8Is1OtherBitOKFlag;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_EMC_CATE_SUPPORT_ECALL_CFG_STRU;
/* Added by j00174725 for ECC(DTS2017021705267), 2017-02-18, end */


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
