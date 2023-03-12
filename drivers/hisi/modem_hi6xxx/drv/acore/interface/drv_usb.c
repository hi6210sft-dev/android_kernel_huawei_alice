/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_usb.c
  �� �� ��   : ����
  ��    ��   : c61362
  ��������   : 2012��3��2��
  ����޸�   :
  ��������   : ������ϲ������װ�Ľӿڲ�
  �޸���ʷ   :
  1.��    ��   : 2012��3��2��
    ��    ��   : c61362
    �޸�����   : �½�Drvinterface.c

  2.��    ��   : 2013��2��19��
    ��    ��   : ��ϲ 220237
    �޸�����   : ��Drvinterface.c�������

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#if (defined BSP_CORE_APP)
#include <linux/module.h>
#endif
#include "BSP.h"
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include "stdio.h"
#include "sys_config.h"
#include "BSP_GLOBAL.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern void ErrlogRegFunc(MNTN_ERRLOGREGFUN ptr);
extern void * getSystemResetInfo(void);
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : MNTN_ERRLOG_REG_FUNC
 ��������  : USB MNTNע���쳣��־�ӿڣ�Porting��Ŀ�д�׮
			    Added by c00204787 for errorlog,20120211
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   ��

*****************************************************************************/
void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    ErrlogRegFunc(pRegFunc);
#endif

#if (defined BSP_CORE_APP)
    return;   /* ��׮ */
#endif
}

/*****************************************************************************
 �� �� ��  : GET_SYSTEM_RESET_INFO
 ��������  : ��ȡϵͳ��λ��Ϣ
			    Added by c00204787 for errorlog,20120211
 �������  : ��

 �������  : �ޡ�
 �� �� ֵ  : ��
 ע������  ��
*****************************************************************************/
void * GET_SYSTEM_RESET_INFO(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return getSystemResetInfo();
#endif

#if (defined BSP_CORE_APP)
    return (void *)0;   /* ��׮ */
#endif
}

/*****************************************************************************
* �� �� ��  : BSP_OM_DspAHBResetCancel
* ��������  : ZSP AHB���߽⸴λ
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
* ����˵��  : ��
*****************************************************************************/
void DRV_DSP_AHB_RESET_CANCEL(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    /* BSP_OM_DspAHBResetCancel(); */
	BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_USB,"stub:DRV_DSP_AHB_RESET_CANCEL\n");
    return;
#endif

#if (defined BSP_CORE_APP)
    return;   /* ��׮ */
#endif
}

/*****************************���翨���START*******************************/

/*****************************************************************************
 �� �� ��  : DRV_AT_SETAPPDAILMODE
 ��������  : ���翨�汾����Ӧ�ý��в��Ż�Ͽ���������
 �������  : unsigned int ulStatus - ���в��Ż�Ͽ�����ָʾ
 �������  : ��
 �� �� ֵ  : VOID
*****************************************************************************/
VOID DRV_AT_SETAPPDAILMODE(unsigned int ulStatus)
{
    return;
#if 0
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
#if( FEATURE_HILINK == FEATURE_ON )
    rndis_app_event_dispatch(ulStatus);
#else
    DRV_PRINTF("Function DRV_AT_SETAPPDAILMODE unsupport!\n");
#endif
#endif
#endif
}

/*****************************���翨���END**********************************/


/************************************************************************
 * FUNCTION
 *       PDP_ACT_DRV_CALLBACK
 * DESCRIPTION
 *       PDP�������õ���Ļص�������ԭ���������ط��ű���Ϣ�����ڴ�׮
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
int PDP_ACT_DRV_CALLBACK(void)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_UdiagValueCheck
 ��������  : ���ӿ����ڼ��NV����USB��ֵ̬�ĺϷ���.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  :
*****************************************************************************/
 int BSP_USB_UdiagValueCheck(unsigned int DiagValue)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;
#endif

#if (defined BSP_CORE_APP)
    return 1;
#endif
}

/********************************************************
����˵����Э��ջ��ѯHSICö��״̬
��������:
�����������
�����������
�����������
����ֵ��  1��ö�����
          0��ö��δ���
********************************************************/
unsigned int BSP_GetHsicEnumStatus(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
    return BSP_FALSE;
#endif
}

/********************************************************
����˵����Э��ջע��HSICȥʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICȥʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
    return BSP_OK;
#endif
}

/********************************************************
����˵����Э��ջע��HSICʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
    return BSP_OK;
#endif
}

/*******************************************************************************
 �� �� ��  : USB_otg_switch_get
 ��������  : ����BALONG��K3�Խ�ʱMODEM��USB PHY״̬��ѯ
 �������  : ��
 �������  : ����USB PHY����״̬

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
******************************************************************************/
int USB_otg_switch_get(UINT8 *pvalue)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
	return BSP_ERROR;
#endif
}

/******************************************************************************
 �� �� ��  : USB_otg_switch_set
 ��������  : ����BALONG��K3�Խ�ʱMODEM�࿪����ر�USB PHY
 �������  : ������ر�
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
******************************************************************************/
int USB_otg_switch_set(UINT8 value)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
	return BSP_ERROR;
#endif
}

/*******************************************************************************
  Function:     USB_otg_switch_signal_set
  Description:  Modem��AP������Ϣ���ͷ�Modem���USB��

  Input:        UINT8 group
                UINT8 pin
                UINT8 value

  Output:
  Return:       GPIO_OK:    �����ɹ�
                GPIO_ERROR: ����ʧ��
  Others:       added by z00187553 20120105
*******************************************************************************/
int USB_otg_switch_signal_set(UINT8 group,UINT8 pin, UINT8 value )
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
	return BSP_ERROR;
#endif
}

unsigned int pcsc_usim_ctrl_cmd(unsigned int CmdTpye, unsigned int Result,
                                        unsigned char *Buf, unsigned int Length)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* ��׮ */
#endif

#if (defined BSP_CORE_APP)
    return 10;  /* �μ�drv_misc_if.c��371�� */
#endif
}

void pcsc_usim_int(pFunAPDUProcess pFun1, GetCardStatus pFun2)
{
#if (defined BSP_CORE_APP)
    return;
#endif
}

#if (defined BSP_CORE_APP)
EXPORT_SYMBOL(pcsc_usim_ctrl_cmd);
EXPORT_SYMBOL(pcsc_usim_int);
#endif

/*****************************************************************************
* �� �� ��  : BSP_NCM_Write_Ready
* ��������  : ׼����������
* �������  : void
* �������  :
* �� �� ֵ  : void
* �޸ļ�¼  : added by l00213811 Balong V300R300C00 TTF������ ʱ���Ż���Infusion�Ż���Ŀ
*****************************************************************************/
void BSP_NCM_Write_Ready(void)
{
	/* ��׮ */
    return;
}

unsigned int BSP_USB_RegIpsTraceCB(USB_IPS_MNTN_TRACE_CB_T pFunc)
{
    return 0;
}

/*move from drv_usb_if.c begin*/
/*****************************************************************************
 �� �� ��  : BSP_USB_GetDiagModeValue
 ��������  : ��ȡ�豸��������
 �������  : unsigned char *dial_mode  : ��������
             unsigned char *cdc_spec   : CDC�淶
 �������  : ��
 �� �� ֵ  : int:��׮ʵ�֣�Ĭ�Ϸ���1��VOS_ERR��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : ��V3R2��ֲ����

*****************************************************************************/
int BSP_USB_GetDiagModeValue(unsigned char *dial_mode, unsigned char *cdc_spec)
{
    return 1;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetLinuxSysType
 ��������  : ��ѯϵͳ�Ƿ�ΪLinux
 �������  : void
 �������  : ��
 �� �� ֵ  : int:��׮ʵ�֣�Ĭ�Ϸ���-1
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
int BSP_USB_GetLinuxSysType(void)
{
    return -1;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetPortMode
 ��������  : ��ȡ�˿���̬ģʽ
 �������  : char* PsBuffer         :���ڴ�Ŷ˿���̬���ƺͶ˿ں�
             unsigned long* Length  :��ȡPsBuffer����
 �������  : ��
 �� �� ֵ  : unsigned char:��׮ʵ�֣�Ĭ�Ϸ���1��VOS_ERR��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned char BSP_USB_GetPortMode(char* PsBuffer, unsigned int* Length )
{
    return 1;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetU2diagDefaultValue
 ��������  : ��ȡ�˿�Ĭ��u2diagֵ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int:��׮ʵ�֣�Ĭ�Ϸ���0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int BSP_USB_GetU2diagDefaultValue(void)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_NASSwitchGatewayRegFunc
 ��������  : ����NASע���л�����֪ͨ�ص�����
 �������  : void
 �������  : ��
 �� �� ֵ  : int :��׮ʵ�֣�Ĭ�Ϸ���0��VOS_OK��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
int BSP_USB_NASSwitchGatewayRegFunc(USB_NET_DEV_SWITCH_GATEWAY switchGwMode)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_SetPid
 ��������  : ����PID��ֵ
 �������  : unsigned char u2diagValue
 �������  : ��
 �� �� ֵ  : int :��׮ʵ�֣�Ĭ�Ϸ���1��VOS_ERR��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
int BSP_USB_SetPid(unsigned char u2diagValue)
{
    return 1;
}

/*****************************************************************************
   ��OAM�Ľӿ�ʵ�֣�������׮ʵ��
*****************************************************************************/






/*****************************************************************************
   ��TTF�Ľӿ�ʵ�֣�������׮ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : USB_ETH_DrvSetRxFlowCtrl
 ��������  : ���ӿ���������
 �������  : unsigned long ulParam1  :����Ϊ��չ��
             unsigned long ulParam2  :����Ϊ��չ��
 �������  : ��
 �� �� ֵ  : unsigned long :��׮ʵ�֣�Ĭ�Ϸ���0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int USB_ETH_DrvSetRxFlowCtrl(unsigned int ulParam1, unsigned int ulParam2)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : USB_ETH_DrvClearRxFlowCtrl
 ��������  : ���ӿڽ������
 �������  : unsigned long ulParam1  :����Ϊ��չ��
             unsigned long ulParam2  :����Ϊ��չ��
 �������  : ��
 �� �� ֵ  : unsigned long :��׮ʵ�֣�Ĭ�Ϸ���0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int USB_ETH_DrvClearRxFlowCtrl(unsigned int ulParam1, unsigned int ulParam2)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_PortTypeValidCheck
 ��������  : �ṩ���ϲ��ѯ�豸�˿���̬���úϷ��Խӿ�
             1���˿�Ϊ��֧�����ͣ�2������PCUI�ڣ�3�����ظ��˿ڣ�4���˵���������16��
             5����һ���豸��ΪMASS��
 �������  : pucPortType  �˿���̬����
             ulPortNum    �˿���̬����
 �������  : ��
 �� �� ֵ  : unsigned int 0-�˿���̬�Ϸ� ����-�˿���̬�Ƿ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��9��
    ��    ��   : ������ 00145324
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned int ulPortNum)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetAvailabePortType
 ��������  : �ṩ���ϲ��ѯ��ǰ�豸֧�ֶ˿���̬�б�ӿ�
 �������  : ulPortMax    Э��ջ֧�����˿���̬����
 �������  : pucPortType  ֧�ֵĶ˿���̬�б�
             pulPortNum   ֧�ֵĶ˿���̬����
 �� �� ֵ  : unsigned int 0-��ȡ�˿���̬�б�ɹ� ����-��ȡ�˿���̬�б�ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��9��
    ��    ��   : ������ 00145324
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int BSP_USB_GetAvailabePortType(unsigned char *pucPortType, unsigned int *pulPortNum, unsigned int ulPortMax)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_PortTypeQuery
 ��������  : ��ѯ��ǰ���豸ö�ٵĶ˿���ֵ̬
 �������  : ��
 �������  : stDynamicPidType  �˿���̬
 �� �� ֵ  : unsigned int 0-��ѯ�ɹ� ����-��ѯʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��9��
    ��    ��   : ������ 00145324
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int BSP_USB_PortTypeQuery(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : l2_notify_register
 ��������  : L2״̬�����˳�֪ͨ�ص�����ע��ӿ�
 �������  : FUNC_USB_LP_NOTIFY *pUSBLPFunc�ص�����ָ��
 �������  : ��
 �� �� ֵ  : 0:    ע��ɹ�
           ������ע��ʧ��
*****************************************************************************/
int l2_notify_register(FUNC_USB_LP_NOTIFY pUSBLPFunc)
{
    return ERROR;
}
/*****************************************************************************
 �� �� ��  : BSP_USB_RegUdiEnableCB
 ��������  : Э��ջ֪ͨUSB�ϲ�Ӧ�ô�UDI�豸�˿�
 �������  : USB_UDI_ENABLE_CB_T pFunc  : USBʹ�ܻص�����ָ��
 �������  : ��
 �� �� ֵ  : unsigned int: 0��ʾ�ɹ� 1��ʾʧ��,��VOS����ķ���ֵ����һ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : ��V3R2��ֲ����

*****************************************************************************/
extern unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc);
unsigned int mdrv_usb_reg_enablecb(USB_UDI_ENABLE_CB_T pFunc)
{
    return BSP_USB_RegUdiEnableCB(pFunc);
}
/*****************************************************************************
 �� �� ��  : BSP_USB_RegUdiDisableCB
 ��������  : Э��ջ֪ͨUSB�ϲ�Ӧ�ùر�UDI�豸�˿�
 �������  : USB_UDI_DISABLE_CB_T pFunc  : USBʹ�ܻص�����ָ��
 �������  : ��
 �� �� ֵ  : unsigned int: 0��ʾ�ɹ� 1��ʾʧ��,��VOS����ķ���ֵ����һ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��15��
    ��    ��   : ���� 00195127
    �޸�����   : ��V3R2��ֲ����

*****************************************************************************/
extern unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc);
unsigned int mdrv_usb_reg_disablecb(USB_UDI_DISABLE_CB_T pFunc)
{
    return BSP_USB_RegUdiDisableCB(pFunc);
}


EXPORT_SYMBOL(BSP_USB_GetDiagModeValue);
EXPORT_SYMBOL(BSP_USB_GetU2diagDefaultValue);
EXPORT_SYMBOL(BSP_USB_SetPid);
EXPORT_SYMBOL(BSP_USB_GetPortMode);
EXPORT_SYMBOL(BSP_USB_GetLinuxSysType);
EXPORT_SYMBOL(BSP_USB_NASSwitchGatewayRegFunc);
EXPORT_SYMBOL(BSP_USB_PortTypeValidCheck);
EXPORT_SYMBOL(BSP_USB_GetAvailabePortType);
EXPORT_SYMBOL(BSP_USB_PortTypeQuery);

/*�ṩ��OAM�Ľӿ�*/
EXPORT_SYMBOL(l2_notify_register);

/*�ṩ��TTF�Ľӿ�*/
EXPORT_SYMBOL(USB_ETH_DrvSetRxFlowCtrl);
EXPORT_SYMBOL(USB_ETH_DrvClearRxFlowCtrl);

/*move from drv_usb_if.c end*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

