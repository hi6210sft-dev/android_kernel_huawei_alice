/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : AppVcomDev.c
  �� �� ��   : ����
  ��    ��   : sunshaohua
  ��������   : 2011��10��05��
  ����޸�   :
  ��������   : ���⴮�ڴ�����

  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��10��05��
    ��    ��   : sunshaohua
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "vos.h"
#include "PsCommonDef.h"
#include "AppVcomDev.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_APP_VCOM_DEV_C
/*lint -e767 */

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/* Added by z00220246 for DSDA Phase I, 2012-11-23, begin */

/* VCOM CTX,���ڱ���VCOM��ȫ�ֱ���*/
APP_VCOM_DEV_CTX_STRU                   g_astVcomCtx[APP_VCOM_MAX_NUM];

/* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
APP_VCOM_DEBUG_INFO_STRU                g_stAppVcomDebugInfo;
/* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */

/* Added by z00220246 for DSDA Phase I, 2012-11-23, end */


/* ���⴮���ļ������ӿ� */
#if (VOS_OS_VER == VOS_WIN32)
static struct file_operations           g_stOperations_Fops;
#else
static const struct file_operations     g_stOperations_Fops =
{
    .owner = THIS_MODULE,
    .read  = APP_VCOM_Read,
    /* Added by A00165503 for DTS2013080604846, 2013-08-06, Begin */
    .poll  = APP_VCOM_Poll,
    /* Added by A00165503 for DTS2013080604846, 2013-08-06, End */
    .write = APP_VCOM_Write,
    .open  = APP_VCOM_Open,
    .release = APP_VCOM_Release,
};
#endif

/* Modified by z00189113 for ErrLog&FTM, 2013-8-23 Begin */

/* APPVCOM�Ĺ���Ӧ��
APPVCOM ID   �����С  ��;           �Ƿ�AT��CLIENT    ModemId
APPVCOM        4K      RIL                   ��         MODEM0
APPVCOM1       4K      RIL                   ��         MODEM0
APPVCOM2       4K      ���̲˵�              ��         MODEM0
APPVCOM3       8K      ����װ��(AT SERVER)   ��         MODEM0
APPVCOM4       4K      audio RIL             ��         MODEM0
APPVCOM5       4K      RIL                   ��         MODEM1
APPVCOM6       4K      RIL                   ��         MODEM1
APPVCOM7       8K      ����װ��(AT SERVER)   ��         MODEM1
APPVCOM8       4K      ���̲˵�/HIDP         ��         MODEM1
APPVCOM9       4K      AGPS                  ��         MODEM0
APPVCOM10      4K      NFC/BIP               ��         MODEM0
APPVCOM11      4K      ISDB                  ��         MODEM0
APPVCOM12      4K      audio ril             ��         MODEM1
APPVCOM13      4K      SIM                   ��         MODEM0
APPVCOM14      4K      SIM                   ��         MODEM1
APPVCOM15      4K      NFC                   ��         MODEM1
APPVCOM16      4K      HIDP                  ��         MODEM0
APPVCOM17      4K      Ԥ��                  ��         MODEM0
APPVCOM18      4K      Ԥ��                  ��         MODEM0
APPVCOM19      4K      Ԥ��                  ��         MODEM0
APPVCOM20      4K      Ԥ��                  ��         MODEM0
APPVCOM21      4K      Ԥ��                  ��         MODEM0
APPVCOM22      4K      Ԥ��                  ��         MODEM0
APPVCOM23      4K      Ԥ��                  ��         MODEM0
APPVCOM24      4K      Ԥ��                  ��         MODEM0
APPVCOM25      4K      Ԥ��                  ��         MODEM0
APPVCOM26      4K      Ԥ��                  ��         MODEM0
APPVCOM27      2M      CBT                   ��         MODEM0
APPVCOM28      4K      T/Lװ��               ��
APPVCOM29      16K     errlog                ��
APPVCOM30      2M      log 3.5               ��
APPVCOM31      2M      log 3.5               ��
*/
#if (FEATURE_ON == FEATURE_VCOM_EXT)
const APP_VCOM_DEV_CONFIG_STRU g_astAppVcomCogfigTab[] =
{
    {APP_VCOM_DEV_NAME_0, APP_VCOM_SEM_NAME_0, 0x1000, 0},                      /* APPVCOM */
    {APP_VCOM_DEV_NAME_1, APP_VCOM_SEM_NAME_1, 0x1000, 0},                      /* APPVCOM1 */
    {APP_VCOM_DEV_NAME_2, APP_VCOM_SEM_NAME_2, 0x1000, 0},                      /* APPVCOM2 */
    {APP_VCOM_DEV_NAME_3, APP_VCOM_SEM_NAME_3, 0x2000, 0},                      /* APPVCOM3 */
    {APP_VCOM_DEV_NAME_4, APP_VCOM_SEM_NAME_4, 0x1000, 0},                      /* APPVCOM4 */
    {APP_VCOM_DEV_NAME_5, APP_VCOM_SEM_NAME_5, 0x1000, 0},                      /* APPVCOM5 */
    {APP_VCOM_DEV_NAME_6, APP_VCOM_SEM_NAME_6, 0x1000, 0},                      /* APPVCOM6 */
    {APP_VCOM_DEV_NAME_7, APP_VCOM_SEM_NAME_7, 0x2000, 0},                      /* APPVCOM7 */
    {APP_VCOM_DEV_NAME_8, APP_VCOM_SEM_NAME_8, 0x1000, 0},                      /* APPVCOM8 */
    {APP_VCOM_DEV_NAME_9, APP_VCOM_SEM_NAME_9, 0x1000, 0},                      /* APPVCOM9 */
    {APP_VCOM_DEV_NAME_10, APP_VCOM_SEM_NAME_10, 0x1000, 0},                    /* APPVCOM10 */
    {APP_VCOM_DEV_NAME_11, APP_VCOM_SEM_NAME_11, 0x1000, 0},                    /* APPVCOM11 */
    {APP_VCOM_DEV_NAME_12, APP_VCOM_SEM_NAME_12, 0x1000, 0},                    /* APPVCOM12 */
    {APP_VCOM_DEV_NAME_13, APP_VCOM_SEM_NAME_13, 0x1000, 0},                    /* APPVCOM13 */
    {APP_VCOM_DEV_NAME_14, APP_VCOM_SEM_NAME_14, 0x1000, 0},                    /* APPVCOM14 */
    {APP_VCOM_DEV_NAME_15, APP_VCOM_SEM_NAME_15, 0x1000, 0},                    /* APPVCOM15 */
    {APP_VCOM_DEV_NAME_16, APP_VCOM_SEM_NAME_16, 0x1000, 0},                    /* APPVCOM16 */
    {APP_VCOM_DEV_NAME_17, APP_VCOM_SEM_NAME_17, 0x1000, 0},                    /* APPVCOM17 */
    {APP_VCOM_DEV_NAME_18, APP_VCOM_SEM_NAME_18, 0x1000, 0},                    /* APPVCOM18 */
    {APP_VCOM_DEV_NAME_19, APP_VCOM_SEM_NAME_19, 0x1000, 0},                    /* APPVCOM19 */
    {APP_VCOM_DEV_NAME_20, APP_VCOM_SEM_NAME_20, 0x1000, 0},                    /* APPVCOM20 */
    {APP_VCOM_DEV_NAME_21, APP_VCOM_SEM_NAME_21, 0x1000, 0},                    /* APPVCOM21 */
    {APP_VCOM_DEV_NAME_22, APP_VCOM_SEM_NAME_22, 0x1000, 0},                    /* APPVCOM22 */
    {APP_VCOM_DEV_NAME_23, APP_VCOM_SEM_NAME_23, 0x1000, 0},                    /* APPVCOM23 */
    {APP_VCOM_DEV_NAME_24, APP_VCOM_SEM_NAME_24, 0x1000, 0},                    /* APPVCOM24 */
    {APP_VCOM_DEV_NAME_25, APP_VCOM_SEM_NAME_25, 0x1000, 0},                    /* APPVCOM25 */
    {APP_VCOM_DEV_NAME_26, APP_VCOM_SEM_NAME_26, 0x1000, 0},                    /* APPVCOM26 */
    {APP_VCOM_DEV_NAME_27, APP_VCOM_SEM_NAME_27, 0x200000, 0},                  /* APPVCOM27 */
    {APP_VCOM_DEV_NAME_28, APP_VCOM_SEM_NAME_28, 0x1000, 0},                    /* APPVCOM28 */
    {APP_VCOM_DEV_NAME_29, APP_VCOM_SEM_NAME_29, 0x4000, 0},                    /* APPVCOM29 */
    /* Modified by f00179208 for DTS2012110606688, 2013-11-06 Begin */
    {APP_VCOM_DEV_NAME_30, APP_VCOM_SEM_NAME_30, 0x200000, 0},                  /* APPVCOM30 */
    {APP_VCOM_DEV_NAME_31, APP_VCOM_SEM_NAME_31, 0x200000, 0}                   /* APPVCOM31 */
    /* Modified by f00179208 for DTS2012110606688, 2013-11-06 End */
    /* Modified by z00189113 for for ErrLog&FTM, 2013-8-23 End */
};
#else
const APP_VCOM_DEV_CONFIG_STRU g_astAppVcomCogfigTab[] =
{
    {APP_VCOM_DEV_NAME_0, APP_VCOM_SEM_NAME_0, 0x1000, 0},                      /* APPVCOM */
    {APP_VCOM_DEV_NAME_1, APP_VCOM_SEM_NAME_1, 0x1000, 0}                       /* APPVCOM1 */
#if 0
    {APP_VCOM_DEV_NAME_2, APP_VCOM_SEM_NAME_2, 0x1000},                         /* APPVCOM2 */
    {APP_VCOM_DEV_NAME_3, APP_VCOM_SEM_NAME_3, 0x2000},                         /* APPVCOM3 */
    {APP_VCOM_DEV_NAME_4, APP_VCOM_SEM_NAME_4, 0x1000}                          /* APPVCOM4 */
#endif
};
#endif

/* Add by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
APP_VCOM_DEBUG_CFG_STRU              g_stAppVcomDebugCfg;
/* Add by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
/*****************************************************************************
   3 ��������������
*****************************************************************************/

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : APP_VCOM_GetVcomCtxAddr
 ��������  : ��ȡ��ǰ�豸��ȫ�ֱ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : APP_VCOM_DEV_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��5��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���

*****************************************************************************/
APP_VCOM_DEV_CTX_STRU* APP_VCOM_GetVcomCtxAddr(VOS_UINT8 ucIndex)
{
    return &(g_astVcomCtx[ucIndex]);
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_GetAppVcomDevEntity
 ��������  : ��ȡ��ǰVCOM���豸ʵ��ָ��
 �������  : VOS_UINT8 ucIndex
 �������  :
 �� �� ֵ  : ���ص�ǰVCOM���豸ʵ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��12��03��
   ��    ��   : z00220246
   �޸�����   : �����ɺ���

*****************************************************************************/
APP_VCOM_DEV_ENTITY_STRU* APP_VCOM_GetAppVcomDevEntity(VOS_UINT8 ucIndex)
{
    return (g_astVcomCtx[ucIndex].pstAppVcomDevEntity);
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_RegDataCallback
 ��������  : VCOM�������ݴ���ģ��ΪATģ���ṩ��ע������AT�������պ����ӿ�
 �������  : VOS_UINT8  ucDevIndex,    SEND_UL_AT_FUNC pFunc
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 APP_VCOM_RegDataCallback(VOS_UINT8 ucDevIndex, SEND_UL_AT_FUNC pFunc)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* �����Ŵ���*/
    if (ucDevIndex >= APP_VCOM_DEV_INDEX_BUTT)
    {
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    /* ����ָ�븳��ȫ�ֱ���*/
    pstVcomCtx->pSendUlAtFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_RegEvtCallback
 ��������  : VCOMΪ�ⲿģ���ṩ��ע��˿��¼��������ӿ�
 �������  : VOS_UINT8  ucDevIndex,    EVENT_FUNC pFunc
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 APP_VCOM_RegEvtCallback(VOS_UINT8 ucDevIndex, EVENT_FUNC pFunc)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* �����Ŵ���*/
    if (ucDevIndex >= APP_VCOM_DEV_INDEX_BUTT)
    {
        return VOS_ERR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    /* ����ָ�븳��ȫ�ֱ���*/
    pstVcomCtx->pEventFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_GetIndexFromMajorDevId
 ��������  : �������豸�ţ��õ��豸��ȫ�ֱ����е�������
 �������  : VOS_UINT32 ulMajorDevId
 �������  : ��
 �� �� ֵ  : VOS_UINT8 �豸������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 APP_VCOM_GetIndexFromMajorDevId(VOS_UINT ulMajorDevId)
{
    VOS_UINT8                           ucLoop;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    for (ucLoop = 0; ucLoop < APP_VCOM_MAX_NUM; ucLoop++)
    {
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucLoop);

        if (pstVcomCtx->ulAppVcomMajorId == ulMajorDevId)
        {
            break;
        }
    }

    return ucLoop;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_InitSpecCtx
 ��������  : ��ʼ��VCOM ģ��ȫ�ֱ���
 �������  : VOS_UINT8 ulDevIndex
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  APP_VCOM_InitSpecCtx(VOS_UINT8 ucDevIndex)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (ucDevIndex >= APP_VCOM_MAX_NUM)
    {
        return;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucDevIndex);

    VOS_MemSet(pstVcomCtx->aucSendSemName, 0, APP_VCOM_SEM_NAME_MAX_LEN);
    VOS_MemSet(pstVcomCtx->aucAppVcomName, 0, APP_VCOM_DEV_NAME_MAX_LEN);

    VOS_MemCpy(pstVcomCtx->aucAppVcomName,
               g_astAppVcomCogfigTab[ucDevIndex].pcAppVcomName,
               VOS_StrLen(g_astAppVcomCogfigTab[ucDevIndex].pcAppVcomName));

    VOS_MemCpy(pstVcomCtx->aucSendSemName,
               g_astAppVcomCogfigTab[ucDevIndex].pcSendSemName,
               VOS_StrLen(g_astAppVcomCogfigTab[ucDevIndex].pcSendSemName));

    pstVcomCtx->ulAppVcomMajorId = APP_VCOM_MAJOR_DEV_ID + ucDevIndex;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_Setup
 ��������  : �����⴮����ӵ��ַ��豸��
 �������  : APP_VCOM_DEV_ENTITY_STRU *pstDev
             VOS_UINT8                 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase I

*****************************************************************************/
VOS_VOID APP_VCOM_Setup(
    APP_VCOM_DEV_ENTITY_STRU *pstDev,
    VOS_UINT8                 ucIndex
)
{
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, begin */
    VOS_INT                             iErr;
    dev_t                               ulDevno;
    static struct class                *pstCom_class;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    ulDevno = MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex);

    cdev_init(&pstDev->stAppVcomDev, &g_stOperations_Fops);

    iErr = cdev_add(&pstDev->stAppVcomDev, ulDevno, 1);
    if (iErr)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Setup cdev_add error! ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        return;
    }

#if (VOS_OS_VER == VOS_WIN32)

#else
    pstCom_class = class_create(THIS_MODULE, pstVcomCtx->aucAppVcomName);

    device_create(pstCom_class,
                  NULL,
                  MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex),
                  "%s",
                  pstVcomCtx->aucAppVcomName);
#endif
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, End */

    return;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_Init
 ��������  : ���⴮�ڳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK    �ɹ�
             VOS_ERR   ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase I
  3.��    ��   : 2013��08��01��
    ��    ��   : j00177245
    �޸�����   : ����appvcom��ʼ��ʱ��
  4.��    ��   : 2013��10��25��
    ��    ��   : j00177245
    �޸�����   : ����appvcom��ά�ɲ��¼���ļ�
  5.��    ��   : 2014��4��22��
    ��    ��   : A00165503
    �޸�����   : DTS2014042208020: ����д�ź�����ʼ��
*****************************************************************************/
VOS_INT __init APP_VCOM_Init(VOS_VOID)
{
    VOS_INT                             iResult1;
    VOS_INT                             iResult2;
    dev_t                               ulDevno;

    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, begin */
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDevp;


    printk("APP_VCOM_Init entry,%u",VOS_GetSlice());

    pstVcomCtx = VOS_NULL_PTR;
    pstVcomDevp  = VOS_NULL_PTR;

    /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
    /* ��ʼ����ά�ɲ�ȫ�ֱ��� */
    VOS_MemSet(&g_stAppVcomDebugInfo, 0x0, sizeof(g_stAppVcomDebugInfo));
    /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */

    /* Add by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    VOS_MemSet(&g_stAppVcomDebugCfg, 0x0, sizeof(g_stAppVcomDebugCfg));
    /* Add by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    /* ��ʼ�������豸 */
    for (ucIndex = 0; ucIndex < APP_VCOM_MAX_NUM; ucIndex++)
    {
        /* ��ʼ��ȫ�ֱ��� */
        APP_VCOM_InitSpecCtx(ucIndex);

        /* ��ȡȫ�ֱ���ָ�� */
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

        /* ���豸��ת����dev_t ���� */
        ulDevno = MKDEV(pstVcomCtx->ulAppVcomMajorId, ucIndex);

        iResult1 = register_chrdev_region(ulDevno, 1, pstVcomCtx->aucAppVcomName);

        /* ע��ʧ����̬�����豸�� */
        if (iResult1 < 0)
        {
            iResult2 = alloc_chrdev_region(&ulDevno, 0, 1, pstVcomCtx->aucAppVcomName);

            if (iResult2 < 0 )
            {
                return VOS_ERROR;
            }

            pstVcomCtx->ulAppVcomMajorId = MAJOR(ulDevno);
        }

        /* ��̬�����豸�ṹ���ڴ� */
        pstVcomCtx->pstAppVcomDevEntity = kmalloc(sizeof(APP_VCOM_DEV_ENTITY_STRU) , GFP_KERNEL);

        if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
        {
            /* ȥע����豸�����ش��� */
            unregister_chrdev_region(ulDevno, 1);
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
            APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Init malloc device Entity fail. ");
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
            return VOS_ERROR;
        }

        /* ��ȡ�豸ʵ��ָ�� */
        pstVcomDevp = pstVcomCtx->pstAppVcomDevEntity;

        VOS_MemSet(pstVcomDevp, 0, sizeof(APP_VCOM_DEV_ENTITY_STRU));

        /* Modified by L60609 for add app vcom��2013-06-17,  Begin */
        pstVcomDevp->pucAppVcomMem = kmalloc(g_astAppVcomCogfigTab[ucIndex].ulAppVcomMemSize, GFP_KERNEL);

        if (VOS_NULL_PTR == pstVcomDevp->pucAppVcomMem)
        {
            /* ȥע����豸�����ش��� */
            unregister_chrdev_region(ulDevno, 1);
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
            APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Init malloc device buff fail. ");
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
            kfree(pstVcomCtx->pstAppVcomDevEntity);
            pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;
            return VOS_ERROR;
        }
        /* Modified by L60609 for add app vcom��2013-06-17,  End */

        init_waitqueue_head(&pstVcomDevp->Read_Wait);

        /* Added by l00373346 for DTS2017041014735, 2017-04-18, Begin */
        mutex_init(&pstVcomDevp->stMutex);
        /* Added by l00373346 for DTS2017041014735, 2017-04-18, End */
        APP_VCOM_Setup(pstVcomDevp, ucIndex);

        /* �����ź��� */
        /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
        sema_init(&pstVcomDevp->stMsgSendSem,1);
        /* Modified by j00174725 for appvcom init, 2013-8-1, end */

        /* Added by A00165503 for DTS2014042208020, 2014-04-22, Begin */
        sema_init(&pstVcomDevp->stWrtSem, 1);
        /* Added by A00165503 for DTS2014042208020, 2014-04-22, End */
    }

   /* Modified by z00220246 for DSDA Phase I, 2012-11-23, End */

    printk("APP_VCOM_Init eixt,%u",VOS_GetSlice());

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_Release
 ��������  : �ļ��رպ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK    �ɹ�
             VOS_ERROR   ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��14��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
*****************************************************************************/
int APP_VCOM_Release(
    struct inode                       *inode,
    struct file                        *filp
)
{
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (VOS_NULL_PTR == inode || VOS_NULL_PTR == filp)
    {
        return VOS_ERROR;
    }

    /* ��ȡ���豸�� */
    ulDevMajor = imajor(inode);

    /* �������豸�ŵõ��豸��ȫ�ֱ����е�����ֵ */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Release ucIndex is error. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        return VOS_ERROR;
    }

    /* ��ȡVCOMȫ�ֱ��� */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Release VcomDevEntity is NULL. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        return VOS_ERROR;
    }

    /* ���豸�ṹ��ָ�븳ֵ���ļ�˽������ָ�� */
    filp->private_data = pstVcomCtx->pstAppVcomDevEntity;

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Release enter. ");
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    if(NULL != pstVcomCtx->pEventFunc)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
		(VOS_VOID)(pstVcomCtx->pEventFunc(APP_VCOM_EVT_RELEASE));
		/* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_Open
 ��������  : �ļ��򿪺���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK    �ɹ�
             VOS_ERROR   ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��14��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase I
*****************************************************************************/
int APP_VCOM_Open(
    struct inode                       *inode,
    struct file                        *filp
)
{
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, begin */
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    if (VOS_NULL_PTR == inode || VOS_NULL_PTR == filp)
    {
        return VOS_ERROR;
    }

    /* ��ȡ���豸�� */
    ulDevMajor = imajor(inode);

    /* �������豸�ŵõ��豸��ȫ�ֱ����е�����ֵ */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Open ucIndex is error. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        return VOS_ERROR;
    }

    /* ��ȡVCOMȫ�ֱ��� */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    if (VOS_NULL_PTR == pstVcomCtx->pstAppVcomDevEntity)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Open VcomDevEntity is NULL. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        return VOS_ERROR;
    }

    /* ���豸�ṹ��ָ�븳ֵ���ļ�˽������ָ�� */
    filp->private_data = pstVcomCtx->pstAppVcomDevEntity;

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Open enter. ");
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, End */

    if(NULL != pstVcomCtx->pEventFunc)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        (VOS_VOID)(pstVcomCtx->pEventFunc(APP_VCOM_EVT_OPEN));
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_Read
 ��������  : ���⴮�ڶ�����
 �������  : struct file *stFilp
             char __user *buf
             size_t       count
             loff_t      *ppos
 �������  : ��
 �� �� ֵ  : ssize_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase I
  3.��    ��   : 2013��08��01��
    ��    ��   : j00177245
    �޸�����   : ����appvcom��ʼ��ʱ��
  4.��    ��   : 2013��10��28��
    ��    ��   : f00179208
    �޸�����   : DTS2013102801414:�ֻ���绰���ҵ绰�����ϲ��VCOM�����0�ֽڵĳ���
*****************************************************************************/
ssize_t APP_VCOM_Read(
    struct file                        *stFilp,
    char __user                        *buf,
    size_t                              count,
    loff_t                             *ppos
)
{
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, begin */
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* ����豸�ṹ��ָ�� */
    pstVcomDev = stFilp->private_data;

    /* ����豸���豸�� */
    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);

    /* ����豸��ȫ�ֱ����е�����ֵ */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if (ucIndex >= APP_VCOM_MAX_NUM)
    {
        return APP_VCOM_ERROR;
    }

    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, read count:%d, current_len:%d. ", count, pstVcomDev->current_len);
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, f_flags:%d. ", stFilp->f_flags);
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, wait_event 111, flag:%d. ", pstVcomDev->ulReadWakeUpFlg);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    if (stFilp->f_flags & O_NONBLOCK)
    {
        return APP_VCOM_ERROR;
    }

#if (VOS_OS_VER == VOS_WIN32)

#else
    /*lint -e730 �޸���:l60609;������:z60575;ԭ��:�����̻߳�ͬʱд��ȫ�ֱ���  */
    /* Modified by f00179208 for DTS2013102801414, 2013-10-28, Begin */
    if (wait_event_interruptible(pstVcomDev->Read_Wait, (pstVcomDev->current_len != 0)))
    {
        return -ERESTARTSYS;
    }
    /* Modified by f00179208 for DTS2013102801414, 2013-10-28, End */
    /*lint +e730 �޸���:l60609;������:z60575;ԭ��:�����̻߳�ͬʱд��ȫ�ֱ���  */
#endif

    /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
    if (0 == pstVcomDev->current_len)
    {
        g_stAppVcomDebugInfo.ulReadLenErr[ucIndex]++;
    }
    /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, wait_event 222,flag:%d. ", pstVcomDev->ulReadWakeUpFlg);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    /* ��ȡ�ź��� */
    /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
    down(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);
    /* Modified by j00174725 for appvcom init, 2013-8-1, end */

    if (count > pstVcomDev->current_len)
    {
        count = pstVcomDev->current_len;
    }

    if (copy_to_user(buf, pstVcomDev->pucAppVcomMem, (VOS_ULONG)count))
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Read, copy_to_user fail. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        /* �ͷ��ź��� */
        /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
        up(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);
        /* Modified by j00174725 for appvcom init, 2013-8-1, end */
        return APP_VCOM_ERROR;
    }

    if ((pstVcomDev->current_len - count) > 0)
    {
        /* FIFO����ǰ�� */
        memmove(pstVcomDev->pucAppVcomMem, (pstVcomDev->pucAppVcomMem + count), (pstVcomDev->current_len - count));

        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, FIFO move. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
    }

    /* ��Ч���ݳ��ȼ�С*/
    pstVcomDev->current_len -= count;

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Read, read %d bytes, current_len:%d. ", count, pstVcomDev->current_len);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    /* �ͷ��ź��� */
    /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
    up(&pstVcomCtx->pstAppVcomDevEntity->stMsgSendSem);
    /* Modified by j00174725 for appvcom init, 2013-8-1, end */

    return (ssize_t)count;
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, End */
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_Write
 ��������  : ���⴮��д����
 �������  : struct file       *stFilp
             const char __user *buf
             size_t             count
             loff_t            *ppos
 �������  : ��
 �� �� ֵ  : ssize_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase I
  3.��    ��   : 2013��10��25��
    ��    ��   : j00177245
    �޸�����  :  ����appvcom��ά�ɲ��¼���ļ�
  4.��    ��   : 2014��4��22��
    ��    ��   : A00165503
    �޸�����   : DTS2014042208020: ����APPVCOM9��APPVCOM12�Ļ��洦��
*****************************************************************************/
ssize_t APP_VCOM_Write(
    struct file                        *stFilp,
    const char __user                  *buf,
    size_t                              count,
    loff_t                             *ppos
)
{
    VOS_UINT8                          *pucDataBuf;
    VOS_INT                             iRst;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;

    /* ����豸�ṹ��ָ�� */
    pstVcomDev = stFilp->private_data;

    /* ����豸���豸�� */
    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);

    /* ����豸��ȫ�ֱ����е�����ֵ */
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    if(ucIndex >= APP_VCOM_MAX_NUM)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, ucIndex fail. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        return APP_VCOM_ERROR;
    }

    /* ���ȫ�ֱ�����ַ */
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

    /* �����ڴ� */
    pucDataBuf = kmalloc(count, GFP_KERNEL);
    if (VOS_NULL_PTR == pucDataBuf )
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, kmalloc fail. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        return APP_VCOM_ERROR;
    }

    /* buffer���� */
    VOS_MemSet(pucDataBuf, 0x00, (VOS_SIZE_T)count);

    if (copy_from_user(pucDataBuf, buf, (VOS_ULONG)count))
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, copy_from_user fail. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        kfree(pucDataBuf);
        return APP_VCOM_ERROR;
    }

    /* Added by A00165503 for DTS2014042208020, 2014-04-22, Begin */
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    if ((APP_VCOM_DEV_INDEX_9 == ucIndex) || (APP_VCOM_DEV_INDEX_12 == ucIndex))
    {
        down(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);

        if (VOS_NULL_PTR != pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer)
        {
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
            APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Write: free buff. ");
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

            kfree(pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer);
            pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer   = VOS_NULL_PTR;
            pstVcomCtx->pstAppVcomDevEntity->ulWrtBufferLen = 0;
        }

        if (VOS_NULL_PTR == pstVcomCtx->pSendUlAtFunc)
        {
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
            APP_VCOM_TRACE_NORM(ucIndex, "APP_VCOM_Write: save buff. ");
            /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

            pstVcomCtx->pstAppVcomDevEntity->pucWrtBuffer   = pucDataBuf;
            pstVcomCtx->pstAppVcomDevEntity->ulWrtBufferLen = count;
            up(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);
            return (ssize_t)count;
        }

        up(&pstVcomCtx->pstAppVcomDevEntity->stWrtSem);
    }
#endif
    /* Added by A00165503 for DTS2014042208020, 2014-04-22, End */

    /* ���ûص���������buf�е�AT����*/
    if (VOS_NULL_PTR == pstVcomCtx->pSendUlAtFunc)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, pSendUlAtFunc is null. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        kfree(pucDataBuf);
        return APP_VCOM_ERROR;
    }

    /* Modified by l00373346 for DTS2017041014735, 2017-04-18, Begin */
    mutex_lock(&pstVcomDev->stMutex);

    iRst = pstVcomCtx->pSendUlAtFunc(ucIndex, pucDataBuf, (VOS_UINT32)count);
    if (VOS_OK != iRst)
    {
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
        g_stAppVcomDebugInfo.ulAtCallBackErr[ucIndex]++;
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(ucIndex, "APP_VCOM_Write, AT_RcvFromAppCom fail. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        /* Added by l00373346 for DTS2017041014735, 2017-04-18, Begin */
        mutex_unlock(&pstVcomDev->stMutex);
        /* Added by l00373346 for DTS2017041014735, 2017-04-18, End */
        kfree(pucDataBuf);

        return APP_VCOM_ERROR;
    }

    mutex_unlock(&pstVcomDev->stMutex);
    /* Modified by l00373346 for DTS2017041014735, 2017-04-18, End */

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Write, write %d bytes, AT_RcvFromAppCom Success.",count);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    /* �ͷ��ڴ� */
    kfree(pucDataBuf);

    return (ssize_t)count;
}

/* Added by A00165503 for DTS2013080604846, 2013-08-06, Begin */
/*****************************************************************************
 �� �� ��  : APP_VCOM_Poll
 ��������  : ���⴮��POLL
 �������  : struct file *fp
             struct poll_table_struct *wait
 �������  : ��
 �� �� ֵ  : 0
             POLLIN | POLLRDNORM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
unsigned int APP_VCOM_Poll(struct file *fp, struct poll_table_struct *wait)
{
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev = VOS_NULL_PTR;
    unsigned int                        mask = 0;

    struct cdev                        *pstCdev;
    VOS_UINT                            ulDevMajor;
    VOS_UINT8                           ucIndex;

    pstVcomDev = fp->private_data;

    pstCdev = &(pstVcomDev->stAppVcomDev);
    ulDevMajor = MAJOR(pstCdev->dev);
    ucIndex = APP_VCOM_GetIndexFromMajorDevId(ulDevMajor);

    poll_wait(fp, &pstVcomDev->Read_Wait, wait);

    if (0 != pstVcomDev->current_len)
    {
        mask |= POLLIN | POLLRDNORM;
    }

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(ucIndex, "APP_VCOM_Poll, mask = %d. ", mask);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    return mask;
}
/* Added by A00165503 for DTS2013080604846, 2013-08-06, End */

/*****************************************************************************
 �� �� ��  : APP_VCOM_Send
 ��������  : ����ATģ���������д���豸��
 �������  : APP_VCOM_DEV_INDEX_UINT8 enDevIndex
             VOS_UINT8  *pData
             VOS_UINT32 uslength
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��20��
    ��    ��   : lijun 00171473
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��23��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase I
  3.��    ��   : 2013��08��01��
    ��    ��   : j00177245
    �޸�����   : ����appvcom��ʼ��ʱ��
  4.��    ��   : 2013��10��25��
    ��    ��   : j00177245
    �޸�����   : ����appvcom��ά�ɲ��¼���ļ�
  5.��    ��   : 2014��4��22��
    ��    ��   : A00165503
    �޸�����   : DTS2014042208020: ����APPVCOM9��APPVCOM12�Ļ��洦��
*****************************************************************************/
VOS_UINT32  APP_VCOM_Send (
    APP_VCOM_DEV_INDEX_UINT8            enDevIndex,
    VOS_UINT8                          *pData,
    VOS_UINT32                          uslength
)
{
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, begin */
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDev;
    /* Added by A00165503 for DTS2014042208020, 2014-04-22, Begin */
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
#endif
    /* Added by A00165503 for DTS2014042208020, 2014-04-22, End */

    if (enDevIndex >= APP_VCOM_MAX_NUM)
    {
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
        g_stAppVcomDebugInfo.ulDevIndexErr++;
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, enDevIndex is error. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */
        return VOS_ERR;
    }

    /* Added by A00165503 for DTS2014042208020, 2014-04-22, Begin */
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    pstVcomCtx = APP_VCOM_GetVcomCtxAddr(enDevIndex);
    if (VOS_NULL_PTR == pstVcomCtx)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, pstVcomCtx is null. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        return VOS_ERR;
    }
#endif
    /* Added by A00165503 for DTS2014042208020, 2014-04-22, End */

    /* ����豸ʵ��ָ�� */
    pstVcomDev = APP_VCOM_GetAppVcomDevEntity(enDevIndex);

    if (VOS_NULL_PTR == pstVcomDev)
    {
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
        g_stAppVcomDebugInfo.ulVcomDevErr[enDevIndex]++;
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_ERR(enDevIndex, "APP_VCOM_Send, pstVcomDev is null. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        return VOS_ERR;
    }

    /* Added by A00165503 for DTS2014042208020, 2014-04-22, Begin */
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    if ((APP_VCOM_DEV_INDEX_9 == enDevIndex) || (APP_VCOM_DEV_INDEX_12 == enDevIndex))
    {
        down(&pstVcomDev->stWrtSem);

        if (VOS_NULL_PTR != pstVcomDev->pucWrtBuffer)
        {
            if (VOS_NULL_PTR != pstVcomCtx->pSendUlAtFunc)
            {
                /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
                APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: handle buff. ");
                /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

                (VOS_VOID)pstVcomCtx->pSendUlAtFunc(enDevIndex,
                                        pstVcomDev->pucWrtBuffer,
                                        pstVcomDev->ulWrtBufferLen);

                kfree(pstVcomDev->pucWrtBuffer);
                pstVcomDev->pucWrtBuffer   = VOS_NULL_PTR;
                pstVcomDev->ulWrtBufferLen = 0;
            }
        }

        up(&pstVcomDev->stWrtSem);
    }
#endif
    /* Added by A00165503 for DTS2014042208020, 2014-04-22, End */

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, uslength:%d, current_len:%d. ", uslength, pstVcomDev->current_len);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    /* ��ȡ�ź��� */
    /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
    down(&pstVcomDev->stMsgSendSem);
    /* Modified by j00174725 for appvcom init, 2013-8-1, end */

    /* ��������ֱ�ӷ��� */
    if (g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize == pstVcomDev->current_len)
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: VCOM MEM FULL. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
        g_stAppVcomDebugInfo.ulMemFullErr[enDevIndex]++;
        /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */

        /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
        up(&pstVcomDev->stMsgSendSem);
        /* Modified by j00174725 for appvcom init, 2013-8-1, end */
        return VOS_ERR;
    }

    /* �������ݴ���ʣ��Buffer��С */
    if (uslength > (g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize - pstVcomDev->current_len))
    {
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
        APP_VCOM_TRACE_NORM(enDevIndex, "APP_VCOM_Send: data more than Buffer. ");
        /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

        uslength = g_astAppVcomCogfigTab[enDevIndex].ulAppVcomMemSize - (VOS_UINT32)pstVcomDev->current_len;
    }

    /* ���Ƶ�BUFFER */
    memcpy(pstVcomDev->pucAppVcomMem + pstVcomDev->current_len, pData, uslength);
    pstVcomDev->current_len += uslength;

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, written %d byte(s), new len: %d. ", uslength, pstVcomDev->current_len);
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    /* �ͷ��ź��� */
    /* Modified by j00174725 for appvcom init, 2013-8-1, begin */
    up(&pstVcomDev->stMsgSendSem);
    /* Modified by j00174725 for appvcom init, 2013-8-1, end */
#ifdef __PC_UT__

#else
    wake_up_interruptible(&pstVcomDev->Read_Wait);
#endif

    /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
    if (0 == pstVcomDev->current_len)
    {
        g_stAppVcomDebugInfo.ulSendLenErr[enDevIndex]++;
    }
    /* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */

    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
    APP_VCOM_TRACE_INFO(enDevIndex, "APP_VCOM_Send, wakeup. ");
    /* Modified by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

    return VOS_OK;
    /* Modified by z00220246 for DSDA Phase I, 2012-11-23, End */
}

/* Added by j00174725 for Appvcom Debug Project, 2013-10-25, begin */
/*****************************************************************************
 �� �� ��  : APP_VCOM_ShowDebugInfo
 ��������  : ��ӡappvcom�Ŀ�ά�ɲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����  : ��������
*****************************************************************************/
VOS_VOID APP_VCOM_ShowDebugInfo(VOS_VOID)
{
    int                                 i;
    vos_printf("App Vcom Debug Info:");
    vos_printf("Index Err: %d\r\n", g_stAppVcomDebugInfo.ulDevIndexErr);

    for (i = 0; i < APP_VCOM_MAX_NUM; i++)
    {
        vos_printf("\r\n");
        vos_printf("AppVcom[%d] Callback Function Return Err Num: %d\r\n", i, g_stAppVcomDebugInfo.ulAtCallBackErr[i]);
        vos_printf("AppVcom[%d] Mem Full Num:                     %d\r\n", i, g_stAppVcomDebugInfo.ulMemFullErr[i]);
        vos_printf("AppVcom[%d] Read Data Length = 0 Num:         %d\r\n", i, g_stAppVcomDebugInfo.ulReadLenErr[i]);
        vos_printf("AppVcom[%d] Send Data Length = 0 Num:         %d\r\n", i, g_stAppVcomDebugInfo.ulSendLenErr[i]);
        vos_printf("AppVcom[%d] Get App Vcom Dev Entity Err Num:  %d\r\n", i, g_stAppVcomDebugInfo.ulVcomDevErr[i]);
    }
}
/* Added by j00174725 for Appvcom Debug Project, 2013-10-25, end */

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 �� �� ��  : APP_VCOM_FreeMem
 ��������  : APPVCOM �����ڴ��ͷź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��24��
    ��    ��   : j00174725
    �޸�����  : ��������
*****************************************************************************/
VOS_VOID APP_VCOM_FreeMem(VOS_VOID)
{
    APP_VCOM_DEV_CTX_STRU              *pstVcomCtx;
    VOS_UINT8                           ucIndex;
    APP_VCOM_DEV_ENTITY_STRU           *pstVcomDevp;

    pstVcomCtx = VOS_NULL_PTR;
    pstVcomDevp  = VOS_NULL_PTR;

   for (ucIndex = 0; ucIndex < APP_VCOM_MAX_NUM; ucIndex++)
    {
        pstVcomCtx = APP_VCOM_GetVcomCtxAddr(ucIndex);

        pstVcomDevp = pstVcomCtx->pstAppVcomDevEntity;

        if (VOS_NULL_PTR != pstVcomDevp->pucAppVcomMem)
        {
            free(pstVcomDevp->pucAppVcomMem);
            pstVcomDevp->pucAppVcomMem = VOS_NULL_PTR;

        }

        if(VOS_NULL_PTR != pstVcomCtx->pstAppVcomDevEntity)
        {
            free(pstVcomCtx->pstAppVcomDevEntity);
            pstVcomCtx->pstAppVcomDevEntity = VOS_NULL_PTR;
        }
    }

   return;
}
#endif

/* Add by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, Begin */
/*****************************************************************************
 �� �� ��  : APP_VCOM_SendDebugNvCfg
 ��������  : ���չ���VCOM Debug ������ص�NV��
 �������  : VOS_UINT32 ulAppVcomDebugNvCfg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��03��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID APP_VCOM_SendDebugNvCfg(
    VOS_UINT32                          ulPortIdMask,
    VOS_UINT32                          ulDebugLevel
)
{
    g_stAppVcomDebugCfg.ulPortIdMask = ulPortIdMask;
    g_stAppVcomDebugCfg.ulDebugLevel = ulDebugLevel;
}

/*****************************************************************************
 �� �� ��  : APP_VCOM_MNTN_LogPrintf
 ��������  : APP VCOM��ά�ɲ�LOG���
 �������  : VOS_CHAR *pcFmt
             ...
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��03��
    ��    ��   : N00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
/*lint -esym(960,69)*/
VOS_VOID APP_VCOM_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuf[APP_VCOM_TRACE_BUF_LEN] = {0};
    VOS_UINT32                          ulPrintLength = 0;

    /* ��ʽ�����BUFFER */
    APP_VCOM_LOG_FORMAT(ulPrintLength, acBuf, APP_VCOM_TRACE_BUF_LEN, pcFmt);

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "%s", acBuf);
#endif
    return;
}
/*lint +esym(960,69)*/
/* Add by n00269697 for V9R1 VCOM DEBUG, 2014-06-03, End */

#if (VOS_LINUX == VOS_OS_VER)
#if (FEATURE_ON == FEATURE_DELAY_MODEM_INIT)
module_init(APP_VCOM_Init);
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


