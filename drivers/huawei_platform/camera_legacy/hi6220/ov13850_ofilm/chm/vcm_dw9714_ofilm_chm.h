/*BEGIN PN: DTS2015031100578 ,Modified by yangxiao y00285026, 2015/03/12*/
/* BEGIN PN: DTS2014091105433,Modified by jiangtao WX224755, 2014/9/11*/

#ifndef __VCM_DW9714_OFILM_CHM_H__

#define __VCM_DW9714_OFILM_CHM_H__

/*vcm_type*/
/* BEGIN PN: DTS2014111907512 ,Modified by jiangtao jwx224755, 2014/11/21*/
VCM_DW9714_Liteon,
/* END   PN: DTS2014111907512 ,Modified by jiangtao jwx224755, 2014/11/21*/
/*vcm_bits*/
9,     
/*vcm_id*/
0x18,  
/*moveLensAddr*/
{0,0},             /* moveLensAddr can be ommitted for DW9714 */
/*offsetInit*/
0,                 /* maybe different in each AF mode */
/*fullRange*/
1023,              /* maybe different in each AF mode */
/*infiniteDistance*/
0x50,              /* should be calibrated */
/*normalDistanceEnd*/
0x280,
/*normalStep*/
0x10,              /* coarse step */
/*normalStrideRatio*/
0x20,
/*videoDistanceEnd*/
0x200,
/*videoStep*/
0x10,
/*videoStrideRatio*/
0x20,
/*strideOffset*/
0x90,              /* large stride will start at (infiniteDistance+videoStrideOffset), this value must common multiple of videoStep and normalStep*/
/*coarseStep*/
0,                 /*coarseStep will be calculated by other params*/
/*fineStep*/
0,                 /*fineStep will be calculated by other params*/
/*motorResTime*/
10,
/*motorDelayTime*/
12,
/*strideDivideOffset*/
0x60,
/*startCurrentOffset*/
0x40,
/*moveRange*/
RANGE_NORMAL,		/* Added for DTS2012052902948 by j00212990 2012-06-06 */
/*get_vcm_otp*/
NULL,
/*fastShotOffset*/  /*added for fastShot mode focus*/
0x68,
#endif //__VCM_DW9714_OFILM_CHM_H__

/* END   PN: DTS2014091105433,Modified by jiangtao WX224755, 2014/9/11*/
/* END   PN: DTS2015031100578 ,Modified by yangxiao y00285026, 2015/03/12*/