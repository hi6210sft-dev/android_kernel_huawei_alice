
#ifndef _EXTISP_REG_H_
#define _EXTISP_REG_H_

static u32 misp_al6010_reg_table [] =
{    
// Rx0
// Start = 0xfffa1000, End = 0xfffa11f4
    0xfffa1000,
    0xfffa1028,
    0xfffa1050,
    0xfffa1078,
    0xfffa10a0,
    0xfffa10c8,
    0xfffa10f0,
    0xfffa1118,
    0xfffa1140,
    0xfffa1168,
    0xfffa1190,
    0xfffa11b8,
    0xfffa11e0,
    
// Rx1
// Start = 0xfffa2000, End = 0xfffa21f4
    0xfffa2000,
    0xfffa2028,
    0xfffa2050,
    0xfffa2078,
    0xfffa20a0,
    0xfffa20c8,
    0xfffa20f0,
    0xfffa2118,
    0xfffa2140,
    0xfffa2168,
    0xfffa2190,
    0xfffa21b8,
    0xfffa21e0,
    
// Rx0_phy
// Start = 0xfffa5000, End = 0xfffa510c
    0xfffa5000,
    0xfffa5028,
    0xfffa5050,
    0xfffa5078,
    0xfffa50a0,
    0xfffa50c8,
    0xfffa50f0,
    
// Rx1_phy
// Start = 0xfffa0000, End = 0xfffa010c
    0xfffa0000,
    0xfffa0028,
    0xfffa0050,
    0xfffa0078,
    0xfffa00a0,
    0xfffa00c8,
    0xfffa00f0,
    
// RxLS
// Start = 0xfffa9000, End = 0xfffa9164
    0xfffa9000,
    0xfffa9028,
    0xfffa9050,
    0xfffa9078,
    0xfffa90a0,
    0xfffa90c8,
    0xfffa90f0,
    0xfffa9118,
    0xfffa9140,
    
// TxLM_a
// Start = 0xffede000, End = 0xffede394
    0xffede000,
    0xffede028,
    0xffede050,
    0xffede078,
    0xffede0a0,
    0xffede0c8,
    0xffede0f0,
    0xffede118,
    0xffede140,
    0xffede168,
    0xffede190,
    0xffede1b8,
    0xffede1e0,
    0xffede208,
    0xffede230,
    0xffede258,
    0xffede280,
    0xffede2a8,
    0xffede2d0,
    0xffede2f8,
    0xffede320,
    0xffede348,
    0xffede370,
    
// TxLM_b
// Start = 0xffedd000, End = 0xffedd394
    0xffedd000,
    0xffedd028,
    0xffedd050,
    0xffedd078,
    0xffedd0a0,
    0xffedd0c8,
    0xffedd0f0,
    0xffedd118,
    0xffedd140,
    0xffedd168,
    0xffedd190,
    0xffedd1b8,
    0xffedd1e0,
    0xffedd208,
    0xffedd230,
    0xffedd258,
    0xffedd280,
    0xffedd2a8,
    0xffedd2d0,
    0xffedd2f8,
    0xffedd320,
    0xffedd348,
    0xffedd370,
    
// TxTop
// Start = 0xfffae000, End = 0xfffae16c
    0xfffae000,
    0xfffae028,
    0xfffae050,
    0xfffae078,
    0xfffae0a0,
    0xfffae0c8,
    0xfffae0f0,
    0xfffae118,
    0xfffae140,
    0xfffae168,
    
// Tx
// Start = 0xffeb0000, End = 0xffeb01e4
    0xffeb0000,
    0xffeb0028,
    0xffeb0050,
    0xffeb0078,
    0xffeb00a0,
    0xffeb00c8,
    0xffeb00f0,
    0xffeb0118,
    0xffeb0140,
    0xffeb0168,
    0xffeb0190,
    0xffeb01b8,
    0xffeb01e0,
    
// Tx_Phy
// Start = 0xffeb2000, End = 0xffeb2104
    0xffeb2000,
    0xffeb2028,
    0xffeb2050,
    0xffeb2078,
    0xffeb20a0,
    0xffeb20c8,
    0xffeb20f0,
    
// RawTop1
// Start = 0xfffab000, End = 0xfffab038
    0xfffab000,
    0xfffab028,
    
// RawTop2
// Start = 0xfffab100, End = 0xfffab11c
    0xfffab100,
    
// RawTop3
// Start = 0xfffab150, End = 0xfffab154
    0xfffab150,
    
// CLK1
// Start = 0xffe80200, End = 0xffe80a04
    0xffe80200,
    0xffe80228,
    0xffe80250,
    0xffe80278,
    0xffe802a0,
    0xffe802c8,
    0xffe802f0,
    0xffe80318,
    0xffe80340,
    0xffe80368,
    0xffe80390,
    0xffe803b8,
    0xffe803e0,
    0xffe80408,
    0xffe80430,
    0xffe80458,
    0xffe80480,
    0xffe804a8,
    0xffe804d0,
    0xffe804f8,
    0xffe80520,
    0xffe80548,
    0xffe80570,
    0xffe80598,
    0xffe805c0,
    0xffe805e8,
    0xffe80610,
    0xffe80638,
    0xffe80660,
    0xffe80688,
    0xffe806b0,
    0xffe806d8,
    0xffe80700,
    0xffe80728,
    0xffe80750,
    0xffe80778,
    0xffe807a0,
    0xffe807c8,
    0xffe807f0,
    0xffe80818,
    0xffe80840,
    0xffe80868,
    0xffe80890,
    0xffe808b8,
    0xffe808e0,
    0xffe80908,
    0xffe80930,
    0xffe80958,
    0xffe80980,
    0xffe809a8,
    0xffe809d0,
    0xffe809f8,
    
// CLK2
// Start = 0xffe81000, End = 0xffe81130
    0xffe81000,
    0xffe81028,
    0xffe81050,
    0xffe81078,
    0xffe810a0,
    0xffe810c8,
    0xffe810f0,
    0xffe81118,
    
// CAP
// Start = 0xfff10000, End = 0xfff10fcc
    0xfff10000,
    0xfff10028,
    0xfff10050,
    0xfff10078,
    0xfff100a0,
    0xfff100c8,
    0xfff100f0,
    0xfff10118,
    0xfff10140,
    0xfff10168,
    0xfff10190,
    0xfff101b8,
    0xfff101e0,
    0xfff10208,
    0xfff10230,
    0xfff10258,
    0xfff10280,
    0xfff102a8,
    0xfff102d0,
    0xfff102f8,
    0xfff10320,
    0xfff10348,
    0xfff10370,
    0xfff10398,
    0xfff103c0,
    0xfff103e8,
    0xfff10410,
    0xfff10438,
    0xfff10460,
    0xfff10488,
    0xfff104b0,
    0xfff104d8,
    0xfff10500,
    0xfff10528,
    0xfff10550,
    0xfff10578,
    0xfff105a0,
    0xfff105c8,
    0xfff105f0,
    0xfff10618,
    0xfff10640,
    0xfff10668,
    0xfff10690,
    0xfff106b8,
    0xfff106e0,
    0xfff10708,
    0xfff10730,
    0xfff10758,
    0xfff10780,
    0xfff107a8,
    0xfff107d0,
    0xfff107f8,
    0xfff10820,
    0xfff10848,
    0xfff10870,
    0xfff10898,
    0xfff108c0,
    0xfff108e8,
    0xfff10910,
    0xfff10938,
    0xfff10960,
    0xfff10988,
    0xfff109b0,
    0xfff109d8,
    0xfff10a00,
    0xfff10a28,
    0xfff10a50,
    0xfff10a78,
    0xfff10aa0,
    0xfff10ac8,
    0xfff10af0,
    0xfff10b18,
    0xfff10b40,
    0xfff10b68,
    0xfff10b90,
    0xfff10bb8,
    0xfff10be0,
    0xfff10c08,
    0xfff10c30,
    0xfff10c58,
    0xfff10c80,
    0xfff10ca8,
    0xfff10cd0,
    0xfff10cf8,
    0xfff10d20,
    0xfff10d48,
    0xfff10d70,
    0xfff10d98,
    0xfff10dc0,
    0xfff10de8,
    0xfff10e10,
    0xfff10e38,
    0xfff10e60,
    0xfff10e88,
    0xfff10eb0,
    0xfff10ed8,
    0xfff10f00,
    0xfff10f28,
    0xfff10f50,
    0xfff10f78,
    0xfff10fa0,
    0xfff10fc8,
    
// RDN
// Start = 0xfff86000, End = 0xfff86a58
    0xfff86000,
    0xfff86028,
    0xfff86050,
    0xfff86078,
    0xfff860a0,
    0xfff860c8,
    0xfff860f0,
    0xfff86118,
    0xfff86140,
    0xfff86168,
    0xfff86190,
    0xfff861b8,
    0xfff861e0,
    0xfff86208,
    0xfff86230,
    0xfff86258,
    0xfff86280,
    0xfff862a8,
    0xfff862d0,
    0xfff862f8,
    0xfff86320,
    0xfff86348,
    0xfff86370,
    0xfff86398,
    0xfff863c0,
    0xfff863e8,
    0xfff86410,
    0xfff86438,
    0xfff86460,
    0xfff86488,
    0xfff864b0,
    0xfff864d8,
    0xfff86500,
    0xfff86528,
    0xfff86550,
    0xfff86578,
    0xfff865a0,
    0xfff865c8,
    0xfff865f0,
    0xfff86618,
    0xfff86640,
    0xfff86668,
    0xfff86690,
    0xfff866b8,
    0xfff866e0,
    0xfff86708,
    0xfff86730,
    0xfff86758,
    0xfff86780,
    0xfff867a8,
    0xfff867d0,
    0xfff867f8,
    0xfff86820,
    0xfff86848,
    0xfff86870,
    0xfff86898,
    0xfff868c0,
    0xfff868e8,
    0xfff86910,
    0xfff86938,
    0xfff86960,
    0xfff86988,
    0xfff869b0,
    0xfff869d8,
    0xfff86a00,
    0xfff86a28,
    0xfff86a50,
    
// IDD
// Start = 0xfffa8000, End = 0xfffa8258
    0xfffa8000,
    0xfffa8028,
    0xfffa8050,
    0xfffa8078,
    0xfffa80a0,
    0xfffa80c8,
    0xfffa80f0,
    0xfffa8118,
    0xfffa8140,
    0xfffa8168,
    0xfffa8190,
    0xfffa81b8,
    0xfffa81e0,
    0xfffa8208,
    0xfffa8230,
    
// 3ARLM
// Start = 0xfffac000, End = 0xfffac068
    0xfffac000,
    0xfffac028,
    0xfffac050,
    
// HW3A
// Start = 0xfff22000, End = 0xfff22594
    0xfff22000,
    0xfff22028,
    0xfff22050,
    0xfff22078,
    0xfff220a0,
    0xfff220c8,
    0xfff220f0,
    0xfff22118,
    0xfff22140,
    0xfff22168,
    0xfff22190,
    0xfff221b8,
    0xfff221e0,
    0xfff22208,
    0xfff22230,
    0xfff22258,
    0xfff22280,
    0xfff222a8,
    0xfff222d0,
    0xfff222f8,
    0xfff22320,
    0xfff22348,
    0xfff22370,
    0xfff22398,
    0xfff223c0,
    0xfff223e8,
    0xfff22410,
    0xfff22438,
    0xfff22460,
    0xfff22488,
    0xfff224b0,
    0xfff224d8,
    0xfff22500,
    0xfff22528,
    0xfff22550,
    0xfff22578,

};

static u32 misp_default_reg_table [] ={
	0xffe80200,
	0xffe80228,
	0xffe80250,
	0xffe80278,
	0xffe802a0,
	0xffe802c8,
	0xffe802f0,
	0xffe80318,
	0xffe80340,
	0xffe80368,
	0xffe80390,
	0xffe803b8,
	0xffe803e0,
	0xffe80408,
	0xffe80430,
	0xffe80458,
	0xffe80480,
	0xffe804a8,
	0xffe804d0,
	0xffe804f8,
	0xffe80520,
	0xffe80548,
	0xffe80570,
	0xffe80598,
	0xffe805c0,
	0xffe805e8,
	0xffe80610,
	0xffe80638,
	0xffe80660,
	0xffe80688,
	0xffe806b0,
	0xffe806b0,
	0xffe80700,
	0xffe80728,
	0xffe80750,
	0xffe80778,
	0xffe807a0,
	0xffe807c8,
	0xffe807f0,
	0xffe80818,
	0xffe80840,
	0xffe80868,

	0xffeb0000,
	0xffeb0028,
	0xffeb0050,
	0xffeb0078,
	0xffeb00a0,
	0xffeb00c8,
	0xffeb00f0,
	0xffeb0118,
	0xffeb0140,
	0xffeb0168,

	0xffeb1000,
	0xffeb1028,
	0xffeb1050,
	0xffeb1078,
	0xffeb10a0,
	0xffeb10c8,
	0xffeb10f0,
	0xffeb1118,
	0xffeb1140,
	0xffeb1168,

	0xffeba000,
	0xffeba028,

	0xffebb000,
	0xffebb028,

	0xffedc000,
	0xffedc028,
	0xffedc050,
	0xffedc078,
	0xffedc0a0,
	0xffedc0c8,
	0xffedc0f0,

	0xffedd000,
	0xffedd028,
	0xffedd050,
	0xffedd078,
	0xffedd0a0,
	0xffedd0c8,
	0xffedd0f0,

	0xffede000,
	0xffede028,
	0xffede050,
	0xffede078,
	0xffede0a0,
	0xffede0c8,
	0xffede0f0,

	0xffedf000,
	0xffedf028,
	0xffedf050,
	0xffedf078,
	0xffedf0a0,
	0xffedf0c8,
	0xffedf0f0,
	0xffe30000,

	0xfff10900,
	0xfff10928,

	0xfff18900,
	0xfff18928,

	0xfffa1000,
	0xfffa1028,
	0xfffa1050,
	0xfffa1078,
	0xfffa10a0,
	0xfffa10c8,
	0xfffa10f0,
	0xfffa1118,
	0xfffa1140,
	0xfffa1168,
	0xfffa1190,

	0xfffa2000,
	0xfffa2028,
	0xfffa2050,
	0xfffa2078,
	0xfffa20a0,
	0xfffa20c8,
	0xfffa20f0,
	0xfffa2118,
	0xfffa2140,
	0xfffa2168,
	0xfffa2190,

	0xfffa3000,
	0xfffa3028,

	0xfffa4000,
	0xfffa4028,

	0xfffa9000,
	0xfffa9028,
	0xfffa9050,
	0xfffa9078,
	0xfffa90a0,
	0xfffa90c8,

	0xfffaa000,
	0xfffaa028,
	0xfffaa050,
	0xfffaa078,
	0xfffaa0a0,
	0xfffaa0c8,
};


#endif

