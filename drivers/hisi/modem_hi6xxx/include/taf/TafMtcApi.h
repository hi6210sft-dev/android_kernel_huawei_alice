/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtcApi.h
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

******************************************************************************/
#ifndef _TAF_MTC_API_H_
#define _TAF_MTC_API_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "TafApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MTC_MSG_ID_BASE             (0x1000)                               /* MTC �ṩ����ϢID����, ��0x1001��ʼ����ҪΪ�˱�����������Ϣ�غ� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö������: TAF_MTC_MSG_ID_ENUM
 ö��˵��: MTC�ڲ���ϢID

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_MSG_ID_ENUM
{
    /* ���CDMA����״̬ */
    ID_MSG_MTC_CDMA_CONN_STATE_IND      = TAF_MTC_MSG_ID_BASE + 0x0001,        /* _H2ASN_MsgChoice  TAF_MTC_CDMA_STATE_IND_STRU */
    ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND,                                    /* _H2ASN_MsgChoice  TAF_MTC_MODEM_CONN_STATUS_IND_STRU */
    ID_MSG_MTC_USIMM_STATE_IND,                                                 /* _H2ASN_MsgChoice  TAF_MTC_USIMM_STATUS_IND_STRU */

    ID_MSG_MTC_BUTT
};
typedef VOS_UINT32 TAF_MTC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
ö����    : TAF_MTC_SRV_CONN_STATE_ENUM
�ṹ˵��  : ҵ������״̬ö�ٶ���

  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_SRV_CONN_STATE_ENUM
{
    TAF_MTC_SRV_NO_EXIST                = 0,                                    /* ������ */
    TAF_MTC_SRV_EXIST,                                                          /* ������ */

    TAF_MTC_SRV_CONN_STATE_BUTT
};
typedef VOS_UINT8 TAF_MTC_SRV_CONN_STATE_ENUM_UINT8;

/*****************************************************************************
ö����    : TAF_MTC_POWER_STATE_ENUM
�ṹ˵��  : ����״̬ö�ٶ���

  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_POWER_STATE_ENUM
{
    TAF_MTC_POWER_OFF                  = 0,                                     /* �ػ� */
    TAF_MTC_POWER_ON,                                                           /* ���� */

    TAF_MTC_POWER_STATE_BUTT
};
typedef VOS_UINT8 TAF_MTC_POWER_STATE_ENUM_UINT8;

/*****************************************************************************
ö����    : TAF_MTC_USIMM_CARD_SERVIC_ENUM
�ṹ˵��  : ��״̬

  1.��    ��   : 2014��06��16��
    ��    ��   : ���±�/j00174725
    �޸�����   : ����ö��
*****************************************************************************/

enum TAF_MTC_USIMM_CARD_SERVIC_ENUM
{
    TAF_MTC_USIMM_CARD_SERVIC_ABSENT        =0,                                 /* �޿� */
    TAF_MTC_USIMM_CARD_SERVIC_UNAVAILABLE   =1,                                 /* �п�,���񲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_SIM_PIN       =2,                                 /* SIM����������PIN��ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_SIM_PUK       =3,                                 /* SIM����������PUK��ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_NET_LCOK      =4,                                 /* SIM������������������ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_IMSI_LCOK     =5,                                 /* SIM����������IMSI����ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_AVAILABLE     =6,                                 /* ������� */

    TAF_MTC_USIMM_CARD_SERVIC_BUTT
};
typedef VOS_UINT16      TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16;

/* Add by j00174725 for TAS2.5, 2014-09-29, Begin */
/*****************************************************************************
ö����    : TAF_MTC_CDMA_USIMM_CARD_ENUM
�ṹ˵��  : ��״̬

  1.��    ��   : 2014��06��16��
    ��    ��   : ���±�/j00174725
    �޸�����   : ����ö��
*****************************************************************************/

enum TAF_MTC_CDMA_USIMM_CARD_ENUM
{
    TAF_MTC_CDMA_USIMM_CARD_UNVALID        =0,                                  /* �޿� */
    TAF_MTC_CDMA_USIMM_CARD_VALID,                                              /* ������� */

    TAF_MTC_CDMA_USIMM_CARD_BUTT
};
typedef VOS_UINT8  TAF_MTC_CDMA_USIMM_CARD_ENUM_UINT8;
/* Add by j00174725 for TAS2.5, 2014-09-29, End */



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
 �ṹ��    : TAF_MTC_CDMA_STATE_INFO_STRU
 �ṹ˵��  : CDMS״̬�ṹ��

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enCsConnSt;                         /* CS����״̬ */
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enPsConnSt;                         /* PS����״̬ */
    TAF_MTC_POWER_STATE_ENUM_UINT8          enPowerState;                       /* ���ػ�״̬ */
    VOS_UINT8                               ucReserved1[1];
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;                       /* ��״̬ */
    VOS_UINT8                               aucReserved2[2];
}TAF_MTC_CDMA_STATE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_CDMA_STATE_IND_STRU
 �ṹ˵��  : ID_MSG_MTC_CDMA_CONN_STATUS����Ϣ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_CDMA_STATE_INFO_STRU        stCdmaState;
}TAF_MTC_CDMA_STATE_IND_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_SRV_CONN_STATE_INFO_STRU
 �ṹ˵��  : ID_MMA_MTC_CONN_STATUS_INFO_IND����Ϣ��Ϣ��Ԫ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPsSrv      : 1;
    VOS_UINT32                          bitOpCsSrv      : 1;
    VOS_UINT32                          bitOpEpsSrv     : 1;
    VOS_UINT32                          bitSpare        : 29;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enEpsSrvConnState;
    VOS_UINT8                           aucReserved[1];
}TAF_MTC_SRV_CONN_STATE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_MODEM_CONN_STATUS_IND_STRU
 �ṹ˵��  : ID_MMA_MTC_CONN_STATUS_INFO_IND����Ϣ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_SRV_CONN_STATE_INFO_STRU    stModemConnStateInfo;
}TAF_MTC_MODEM_CONN_STATUS_IND_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_USIMM_STATUS_IND_STRU
 �ṹ˵��  : ID_MMA_MTC_CONN_STATUS_INFO_IND����Ϣ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;
    VOS_UINT8                               aucReserved[2];
}TAF_MTC_USIMM_STATUS_IND_STRU;

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_MTC_MSG_ID_ENUM_UINT32          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_MTC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MTC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MTC_MSG_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_MTC_MSG_REQ                     stMsgReq;
}TafMtcApi_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
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
);

/*****************************************************************************
 �� �� ��  : TAF_MTC_SetCdmaServiceConnStateInfo
 ��������  : �����ⲿCDMA Modem������״̬(PS&CS)
 �������  : pstCtrl                    - ����ͷ
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
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmsState
);

/*****************************************************************************
 �� �� ��  : TAF_MTC_SetModemServiceConnState
 ��������  : ����modem״̬��Ϣ
 �������  : ulModuleId      ģ��ID
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
);

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
);



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

#endif

