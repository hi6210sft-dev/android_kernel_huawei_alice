/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasUtranCtrlInterface.h
  �� �� ��   : ����
  ��    ��   : w00167002
  ��������   : 2012��7��12��
  ����޸�   :
  ��������   : ��NAS������ģ��:MM�Ӳ㡢TAF�㡢CM���ѯ�Ľӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��7��12��
    ��    ��   : w00167002
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _NAS_UTRANCTRL_INTERFACE_H_
#define _NAS_UTRANCTRL_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "TTFMem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8
 �ṹ˵��  : MS��ǰ�����UTRANģʽ:WCDMA/TD-SCAMA
 1.��    ��   : 2012��7��27��
   ��    ��   : w00167002
   �޸�����   : �½�
*****************************************************************************/
enum NAS_UTRANCTRL_UTRAN_MODE_ENUM
{
    NAS_UTRANCTRL_UTRAN_MODE_FDD,                                               /* UTRANģʽΪWCDMA */
    NAS_UTRANCTRL_UTRAN_MODE_TDD,                                               /* UTRANģʽΪTDSCDMA */
    NAS_UTRANCTRL_UTRAN_MODE_BUTT
};
typedef VOS_UINT8 NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8;

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


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetCurrUtranMode(VOS_VOID);

/* Added by w00167002 for DTS2013112006986, 2013-11-18, begin */
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg(VOS_VOID);
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg(VOS_VOID);
VOS_UINT8 NAS_UTRANCTRL_IsUtranCsSmcNeeded(VOS_VOID);
VOS_UINT8 NAS_UTRANCTRL_IsUtranPsSmcNeeded(VOS_VOID);
/* Added by w00167002 for DTS2013112006986, 2013-11-18, end */

VOS_UINT32 NAS_UTRANCTRL_SndAsMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       **ppstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(
    VOS_UINT8                           ucRbId,
    TTF_MEM_ST                         *pstData,
    VOS_UINT32                          ulDataBitLen
);

VOS_VOID NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize(
    VOS_UINT8                          ucRbId,
    VOS_UINT32                         ulPduSize,
    VOS_UINT8                          ucCrcSize,
    VOS_UINT32                        *pulUlPduSize
);

VOS_UINT32 NAS_UTRANCTRL_RABM_SendTcDataNotify(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag);

/* Modified by w00176964 for  V7R1C50_GUTL_PhaseII, 2012-8-8, begin */
VOS_VOID NAS_UTRANCTRL_ProcBufferMsg(VOS_VOID);

VOS_UINT32 NAS_UTRANCTRL_MsgProc(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
);
/* Modified by w00176964 for  V7R1C50_GUTL_PhaseII, 2012-8-8, end */

/* Modified by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-16, begin */
VOS_VOID  NAS_UTRANCTRL_InitCtx(
    VOS_UINT8                           ucInitType
);
/* Modified by w00167002 for V7R1C50_GUTL_PhaseII, 2012-8-16, end */

VOS_VOID  NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(
    VOS_UINT8       ucFlg
);

/* Added by w00176964 for  V7R1C50_GUTL_PhaseII, 2012-8-25, begin */
VOS_VOID NAS_UTRANCTRL_SndOutsideContextData( VOS_VOID );
/* Added by w00176964 for  V7R1C50_GUTL_PhaseII, 2012-8-25, end */

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

#endif /* end of NasNAS_UTRANCTRLCtx.h */
