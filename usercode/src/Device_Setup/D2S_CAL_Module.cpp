#include "TestClass.h"
#include "UserAPI.h"
#include "d2sProtocolSSI.h"
#include "string.h"
#include "D2S_CAL_Module.h"
#include "CCWaveformsData.h"
#include <math.h>
#include "Globle_Var.h"
#include "Capture_Function.h"


using namespace PhxAPI;

void RXIQ_Cap_Mac_Module() {

	long i;
	long j;

	//2001C000~2001FFFF, mac address, need to switch to SSI frequency.
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);

	for (i = 0; i < 15; i++) {         //0xc0 to 0xfc, step 4
		d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);

		for (j = 0; j < 127; j++) {       //0 to 0x3ff
			//Call SSI_read_Module(0x0 + 8 * j, , 41);
			//Call SSI_read_Module(0x2 + 8 * j, , 41);
		}
	}
	d2s::d2s_LABEL_END();
}

void Cal_SOC_2G_Init_Module() {

//File:  Cal_init.xlsx
//Sheet: Cal_SOC_2G_Init_Module
//File time: 5/25/2017 5:14:21 AM

//    d2s_test.SSI_write(0x204, 0x0, false);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x80, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x20, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x80, false);
//    d2s_test.SSI_write(0x270, 0x1);
//    d2s_test.SSI_write(0x270, 0x0);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x204, 0x8);
//    d2s_test.SSI_write(0x208, 0x7);
//    d2s_test.SSI_write(0x124, 0x0);
//    d2s_test.SSI_write(0x13C, 0xEE8);
//    d2s_test.SSI_write(0x16C, 0x40);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x0, 0x33);
//    d2s_test.SSI_write(0x0, 0x3F);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x154, 0x0);
//    d2s_test.SSI_write(0x154, 0x1);

//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x218, 0x5);
//    d2s_test.SSI_write(0x218, 0x1);
//    d2s_test.SSI_write(0x140, 0x8E88);
//    d2s_test.SSI_write(0x320, 0x452);
//    d2s_test.SSI_write(0x118, 0x1);
//    d2s_test.SSI_write(0x310, 0x30);
//    d2s_test.SSI_write(0x314, 0x0);
//    d2s_test.SSI_write(0x318, 0x0);
//    d2s_test.SSI_write(0x31C, 0x281);
//    d2s_test.SSI_write(0x33C, 0x19B);
//    d2s_test.SSI_write(0x300, 0xE04);
//    d2s_test.SSI_write(0x300, 0x604);
//    d2s_test.SSI_write(0x304, 0x0);
//    d2s_test.SSI_write(0x324, 0x0);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x118, 0x1);
//    d2s_test.SSI_write(0x11C, 0x1);          //not allowed to write again before switch to SSI frequency.
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false); //Here are some registgers for the LDO//s voltage.
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x1C, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x110, 0x1);
	d2s_test.SSI_write(0x114, 0x1);
	d2s_test.SSI_write(0x11C, 0x100);
	d2s_test.SSI_write(0x11C, 0x101);
	d2s_test.SSI_write(0x120, 0x100);
	d2s_test.SSI_write(0x120, 0x101);
	d2s_test.SSI_write(0x124, 0x30);
	d2s_test.SSI_write(0x300, 0x4);
	d2s_test.SSI_write(0x314, 0x4);
	d2s_test.SSI_write(0x324, 0x0);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x17C, 0x6);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x160, 0x3F);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x22C, 0x1);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x334, 0x1);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x244, 0x0);
	d2s_test.SSI_write(0x25C, 0x0);
	d2s_test.SSI_write(0x250, 0x100);
	d2s_test.SSI_write(0x268, 0x100);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x0, 0xA);
	d2s_test.SSI_write(0x4, 0x0);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x14, 0x1FF);
	d2s_test.SSI_write(0x0, 0x3D);
	d2s_test.SSI_write(0x0, 0x3F);

	d2s_test.SSI_write(0x204, 0x48D1, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x21C, 0xAFA4);

	d2s_test.SSI_write(0x204, 0x48D0, false);
	d2s_test.SSI_write(0x214, 0xEFA4);
	d2s::d2s_LABEL_END();
}

void Cal_SOC_5G_Init_Module() {

	//File:  Cal_init.xlsx
	//Sheet: Cal_SOC_5G_Init_Module
	//File time: 5/25/2017 5:14:21 AM

//    d2s_test.SSI_write(0x204, 0x0, false);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x80, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x20, false);
//    d2s_test.SSI_write(0x4, 0x1151);
//    d2s_test.SSI_write(0x8, 0x1151);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x80, false);
//    d2s_test.SSI_write(0x270, 0x1);
//    d2s_test.SSI_write(0x270, 0x0);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x204, 0x8);
//    d2s_test.SSI_write(0x208, 0x7);
//    d2s_test.SSI_write(0x124, 0x0);
//    d2s_test.SSI_write(0x13C, 0xEE8);
//    d2s_test.SSI_write(0x16C, 0x40);
//
//    d2s_test.SSI_write(0x200, 0x2001, false);
//    d2s_test.SSI_write(0x202, 0x4, false);
//    d2s_test.SSI_write(0x0, 0x33);
//    d2s_test.SSI_write(0x0, 0x3F);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x154, 0x0);
//    d2s_test.SSI_write(0x154, 0x1);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x40, false);
//    d2s_test.SSI_write(0x218, 0x5);
//    d2s_test.SSI_write(0x218, 0x1);
//    d2s_test.SSI_write(0x140, 0x8E88);
//    d2s_test.SSI_write(0x320, 0x452);
//    d2s_test.SSI_write(0x118, 0x1);
//    d2s_test.SSI_write(0x310, 0x30);
//    d2s_test.SSI_write(0x314, 0x0);
//    d2s_test.SSI_write(0x318, 0x0);
//    d2s_test.SSI_write(0x31C, 0x281);
//    d2s_test.SSI_write(0x33C, 0x19B);
//    d2s_test.SSI_write(0x300, 0xE04);
//    d2s_test.SSI_write(0x300, 0x604);
//    d2s_test.SSI_write(0x304, 0x0);
//    d2s_test.SSI_write(0x324, 0x0);
//
//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x0, false);
//    d2s_test.SSI_write(0x118, 0x1);
//    d2s_test.SSI_write(0x11C, 0x1);
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x1C, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x110, 0x1);
	d2s_test.SSI_write(0x114, 0x1);
	d2s_test.SSI_write(0x11C, 0x100);
	d2s_test.SSI_write(0x11C, 0x101);
	d2s_test.SSI_write(0x120, 0x100);
	d2s_test.SSI_write(0x120, 0x101);
	d2s_test.SSI_write(0x124, 0x30);
	d2s_test.SSI_write(0x300, 0x4);
	d2s_test.SSI_write(0x314, 0x4);
	d2s_test.SSI_write(0x324, 0x0);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x17C, 0x6);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x160, 0x3F);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x22C, 0x1);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x334, 0x1);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x244, 0x0);
	d2s_test.SSI_write(0x25C, 0x0);
	d2s_test.SSI_write(0x250, 0x100);
	d2s_test.SSI_write(0x268, 0x100);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x0, 0xA);
	d2s_test.SSI_write(0x4, 0x0);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x14, 0x1FF);
	d2s_test.SSI_write(0x0, 0x3D);
	d2s_test.SSI_write(0x0, 0x3F);

	d2s_test.SSI_write(0x204, 0x48D0, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x21C, 0xD7A4);
	d2s_test.SSI_write(0x214, 0x17A4);

	d2s_test.SSI_write(0x204, 0x81D, false);
	d2s_test.SSI_write(0x0, 0xAE2A);
	d2s::d2s_LABEL_END();
}

void Cal_PHY_2G_Init_Module() {

	//File:  Cal_init.xlsx
	//Sheet: Cal_PHY_2G_Init_Module
	//File time: 5/25/2017 5:14:21 AM
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);    //ProductionMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s_test.SSI_write(0x4, 0x0);
	d2s_test.SSI_write(0x8, 0x1);
	d2s_test.SSI_write(0xC, 0x4);
	d2s_test.SSI_write(0x10, 0x1A);
	d2s_test.SSI_write(0x14, 0x2);
	d2s_test.SSI_write(0x18, 0x1);
	d2s_test.SSI_write(0x20, 0x3);
	d2s_test.SSI_write(0x24, 0x1);

	d2s_test.SSI_write(0x204, 0xC3BE, false);
	d2s_test.SSI_write(0x374, 0xDD6B);

	d2s_test.SSI_write(0x204, 0xC, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x50, 0xE0F4);

	d2s_test.SSI_write(0x204, 0xA1E6, false);
	d2s_test.SSI_write(0x3FC, 0xFAFE);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x1C, 0x0);

	d2s_test.SSI_write(0x204, 0xD8, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x170, 0xF01E);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x44, 0xF);
	d2s_test.SSI_write(0x128, 0x10);
	d2s_test.SSI_write(0x1E0, 0x43F);

	d2s_test.SSI_write(0x204, 0xDBBB, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x39C, 0xBB9B);

	d2s_test.SSI_write(0x204, 0xFDD, false);
	d2s_test.SSI_write(0x3A0, 0xD00F);

	d2s_test.SSI_write(0x204, 0xFFF, false);
	d2s_test.SSI_write(0x3A4, 0xFF00);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x3A8, 0x0);

	d2s_test.SSI_write(0x204, 0xA8A8, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x180, 0xA8A8);

	d2s_test.SSI_write(0x204, 0x8888, false);
	d2s_test.SSI_write(0x184, 0x8888);

	d2s_test.SSI_write(0x204, 0x7979, false);
	d2s_test.SSI_write(0x188, 0x7980);

	d2s_test.SSI_write(0x204, 0x8F8F, false);
	d2s_test.SSI_write(0x18C, 0x8F8F);

	d2s_test.SSI_write(0x204, 0x687A, false);
	d2s_test.SSI_write(0x190, 0x7A7A);

	d2s_test.SSI_write(0x204, 0x7272, false);
	d2s_test.SSI_write(0x194, 0x7272);

	d2s_test.SSI_write(0x204, 0x626A, false);
	d2s_test.SSI_write(0x198, 0x6A6A);

	d2s_test.SSI_write(0x204, 0xCCCC, false);
	d2s_test.SSI_write(0x19C, 0xCCCC);

	d2s_test.SSI_write(0x204, 0x7A8D, false);
	d2s_test.SSI_write(0x1A0, 0xA4CD);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1A4, 0x66);

	d2s_test.SSI_write(0x204, 0xC7C8, false);
	d2s_test.SSI_write(0x1A8, 0xC8C8);

	d2s_test.SSI_write(0x204, 0x767D, false);
	d2s_test.SSI_write(0x1AC, 0x91A8);

	d2s_test.SSI_write(0x204, 0xA8AB, false);
	d2s_test.SSI_write(0x1B0, 0xAEB0);

	d2s_test.SSI_write(0x204, 0x7870, false);
	d2s_test.SSI_write(0x1B4, 0x80A3);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1B8, 0x9EA7);
	d2s_test.SSI_write(0x1C0, 0x8585);

	d2s_test.SSI_write(0x204, 0x8A84, false);
	d2s_test.SSI_write(0x1C4, 0x8485);

	d2s_test.SSI_write(0x204, 0x8D97, false);
	d2s_test.SSI_write(0x1C8, 0x6E78);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1BC, 0x7279);

	d2s_test.SSI_write(0x204, 0x3D, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x394, 0xB03D);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x3C0, 0x1FFF);

	d2s_test.SSI_write(0x204, 0x809A, false);
	d2s_test.SSI_write(0x20C, 0x2000);

	d2s_test.SSI_write(0x204, 0x1E0, false);
	d2s_test.SSI_write(0x240, 0x7205);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x3F0, 0x0);
	d2s_test.SSI_write(0x3F4, 0x0);
	d2s_test.SSI_write(0x3F8, 0x130E);
	d2s_test.SSI_write(0x3FC, 0xE);

	d2s_test.SSI_write(0x204, 0xA0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x15C, 0x9564);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x68, 0x1);
	d2s_test.SSI_write(0xF0, 0x1);
	d2s_test.SSI_write(0xF8, 0x1);
	d2s_test.SSI_write(0x108, 0x69);
	d2s_test.SSI_write(0x40, 0x138);
	d2s_test.SSI_write(0x214, 0x64);
	d2s_test.SSI_write(0x218, 0xAE);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x2DC, 0x64);
	d2s_test.SSI_write(0x2E0, 0x64);
	d2s_test.SSI_write(0x2E4, 0x64);
	d2s_test.SSI_write(0x2E8, 0x14);
	d2s_test.SSI_write(0x2EC, 0x18);
	d2s_test.SSI_write(0x2F0, 0x6);
	d2s_test.SSI_write(0x2F4, 0x7);
	d2s_test.SSI_write(0x2F8, 0xA);
	d2s_test.SSI_write(0x2FC, 0x8);
	d2s_test.SSI_write(0x300, 0xB);

	d2s_test.SSI_write(0x204, 0x144, false);
	d2s_test.SSI_write(0x12C, 0x8400);

	d2s_test.SSI_write(0x204, 0x307, false);
	d2s_test.SSI_write(0x3B4, 0x50);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x64, 0xA);

	d2s_test.SSI_write(0x204, 0x2, false);
	d2s_test.SSI_write(0x4, 0x400);

	d2s_test.SSI_write(0x204, 0x20, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x204, 0x68, false);
	d2s_test.SSI_write(0x10, 0x0);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x14, 0x60);

	d2s_test.SSI_write(0x204, 0x7D7D, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x7D32);

	d2s_test.SSI_write(0x204, 0x2225, false);
	d2s_test.SSI_write(0x24, 0x6FCF);

	d2s_test.SSI_write(0x204, 0x95EA, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0xD8, 0x5500);

	d2s_test.SSI_write(0x204, 0x57FA, false);
	d2s_test.SSI_write(0xDC, 0x95FA);

	d2s_test.SSI_write(0x204, 0xFFA9, false);
	d2s_test.SSI_write(0xE0, 0x5FEA);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0xE4, 0xF);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x38, 0x95);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x170, 0xB40);

	d2s_test.SSI_write(0x204, 0x20, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x18, 0x0);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1C, 0x40);
	d2s_test.SSI_write(0x30, 0x0);
	d2s_test.SSI_write(0x8, 0x1E1E);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x220, 0xA05B);
	d2s_test.SSI_write(0x200, 0xA0);
	d2s_test.SSI_write(0x204, 0x10);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x1FC, 0x7);

	d2s_test.SSI_write(0x204, 0x5110, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x1C, 0x101);

	d2s_test.SSI_write(0x204, 0x1B2F, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x248, 0x53BA);

	d2s_test.SSI_write(0x204, 0x3046, false);
	d2s_test.SSI_write(0x24C, 0xB0B0);

	d2s_test.SSI_write(0x204, 0x3253, false);
	d2s_test.SSI_write(0x25C, 0xE1FC);

	d2s_test.SSI_write(0x204, 0xC0C6, false);
	d2s_test.SSI_write(0x260, 0x9168);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x264, 0x2A0A);

	d2s_test.SSI_write(0x204, 0x1, false);
	d2s_test.SSI_write(0x268, 0x1AA0);

	d2s_test.SSI_write(0x204, 0x9C2, false);
	d2s_test.SSI_write(0x3B0, 0x780A);

	d2s_test.SSI_write(0x204, 0x5DC, false);
	d2s_test.SSI_write(0x3B4, 0x594);

	d2s_test.SSI_write(0x204, 0x148, false);
	d2s_test.SSI_write(0x3B8, 0x7005);

	d2s_test.SSI_write(0x204, 0x3A00, false);
	d2s_test.SSI_write(0x3BC, 0x2A0);

	d2s_test.SSI_write(0x204, 0x19C6, false);
	d2s_test.SSI_write(0x3C0, 0x4005);

	d2s_test.SSI_write(0x204, 0x1D4C, false);
	d2s_test.SSI_write(0x3C4, 0x270);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x3C8, 0x0);           //@2017-06-22, enable IQ compesate

	d2s_test.SSI_write(0x204, 0x206, false);
	d2s_test.SSI_write(0x3D0, 0x4005);

	d2s_test.SSI_write(0x204, 0x3E8, false);
	d2s_test.SSI_write(0x3D4, 0xFA);

	d2s_test.SSI_write(0x204, 0x47FF, false);
	d2s_test.SSI_write(0x3D8, 0xFFFF);

	d2s_test.SSI_write(0x204, 0xFFFF, false);
	d2s_test.SSI_write(0x3DC, 0xFFFF);

	d2s_test.SSI_write(0x204, 0x1FFF, false);
	d2s_test.SSI_write(0x3E0, 0xFFFF);

	d2s_test.SSI_write(0x204, 0xFFFF, false);
	d2s_test.SSI_write(0x3E4, 0xFFFF);

	d2s_test.SSI_write(0x204, 0x5FFF, false);
	d2s_test.SSI_write(0x3E8, 0xFFFF);

	d2s_test.SSI_write(0x204, 0xFFFF, false);
	d2s_test.SSI_write(0x3EC, 0xFFFF);

	d2s_test.SSI_write(0x204, 0x50, false);
	d2s_test.SSI_write(0x16C, 0x2D0);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x44, 0x2147);

	d2s_test.SSI_write(0x204, 0xD4, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x50, 0xE0F4);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x44, 0x20C7);

	d2s_test.SSI_write(0x204, 0x2812, false);
	d2s_test.SSI_write(0x3C, 0x2848);

	d2s_test.SSI_write(0x204, 0xB4, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x120, 0x9999);

	d2s_test.SSI_write(0x204, 0x1C, false);
	d2s_test.SSI_write(0x138, 0x1C28);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x270, 0x1);
	d2s_test.SSI_write(0x274, 0x0);
	d2s_test.SSI_write(0x274, 0x1);
	d2s::d2s_LABEL_END();
}

void Cal_PHY_5G_Init_Module() {

	//File:  Cal_init.xlsx
	//Sheet: Cal_PHY_5G_Init_Module
	//File time: 5/25/2017 5:14:21 AM
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s_test.SSI_write(0x4, 0x0);
	d2s_test.SSI_write(0x8, 0x1);
	d2s_test.SSI_write(0xC, 0x4);
	d2s_test.SSI_write(0x10, 0x1A);
	d2s_test.SSI_write(0x14, 0x2);
	d2s_test.SSI_write(0x18, 0x1);
	d2s_test.SSI_write(0x20, 0x3);
	d2s_test.SSI_write(0x24, 0x1);

	d2s_test.SSI_write(0x204, 0xC3BE, false);
	d2s_test.SSI_write(0x374, 0xDD6B);

	d2s_test.SSI_write(0x204, 0xC, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x50, 0xE0F4);

	d2s_test.SSI_write(0x204, 0xA1E6, false);
	d2s_test.SSI_write(0x3FC, 0xFAFE);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x1C, 0x0);

	d2s_test.SSI_write(0x204, 0xD8, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x170, 0xF01E);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x44, 0xF);
	d2s_test.SSI_write(0x128, 0x10);
	d2s_test.SSI_write(0x1E0, 0x43F);

	d2s_test.SSI_write(0x204, 0xDBBB, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x39C, 0xBB9B);

	d2s_test.SSI_write(0x204, 0xFDD, false);
	d2s_test.SSI_write(0x3A0, 0xD00F);

	d2s_test.SSI_write(0x204, 0xFFF, false);
	d2s_test.SSI_write(0x3A4, 0xFF00);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x3A8, 0x0);

	d2s_test.SSI_write(0x204, 0xA8A8, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x180, 0xA8A8);

	d2s_test.SSI_write(0x204, 0x8888, false);
	d2s_test.SSI_write(0x184, 0x8888);

	d2s_test.SSI_write(0x204, 0x7979, false);
	d2s_test.SSI_write(0x188, 0x7980);

	d2s_test.SSI_write(0x204, 0x8F8F, false);
	d2s_test.SSI_write(0x18C, 0x8F8F);

	d2s_test.SSI_write(0x204, 0x687A, false);
	d2s_test.SSI_write(0x190, 0x7A7A);

	d2s_test.SSI_write(0x204, 0x7272, false);
	d2s_test.SSI_write(0x194, 0x7272);

	d2s_test.SSI_write(0x204, 0x626A, false);
	d2s_test.SSI_write(0x198, 0x6A6A);

	d2s_test.SSI_write(0x204, 0xCCCC, false);
	d2s_test.SSI_write(0x19C, 0xCCCC);

	d2s_test.SSI_write(0x204, 0x7A8D, false);
	d2s_test.SSI_write(0x1A0, 0xA4CD);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1A4, 0x66);

	d2s_test.SSI_write(0x204, 0xC7C8, false);
	d2s_test.SSI_write(0x1A8, 0xC8C8);

	d2s_test.SSI_write(0x204, 0x767D, false);
	d2s_test.SSI_write(0x1AC, 0x91A8);

	d2s_test.SSI_write(0x204, 0xA8AB, false);
	d2s_test.SSI_write(0x1B0, 0xAEB0);

	d2s_test.SSI_write(0x204, 0x7870, false);
	d2s_test.SSI_write(0x1B4, 0x80A3);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1B8, 0x9EA7);
	d2s_test.SSI_write(0x1C0, 0x8585);

	d2s_test.SSI_write(0x204, 0x8A84, false);
	d2s_test.SSI_write(0x1C4, 0x8485);

	d2s_test.SSI_write(0x204, 0x8D97, false);
	d2s_test.SSI_write(0x1C8, 0x6E78);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1BC, 0x7279);

	d2s_test.SSI_write(0x204, 0x3D, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x394, 0xB03D);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x3C0, 0x1FFF);

	d2s_test.SSI_write(0x204, 0x809A, false);
	d2s_test.SSI_write(0x20C, 0x2000);

	d2s_test.SSI_write(0x204, 0x1E0, false);
	d2s_test.SSI_write(0x240, 0x7205);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x3F0, 0x0);
	d2s_test.SSI_write(0x3F4, 0x0);
	d2s_test.SSI_write(0x3F8, 0x130E);
	d2s_test.SSI_write(0x3FC, 0xE);

	d2s_test.SSI_write(0x204, 0xA0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x15C, 0x9564);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x68, 0x1);
	d2s_test.SSI_write(0xF0, 0x1);
	d2s_test.SSI_write(0xF8, 0x1);
	d2s_test.SSI_write(0x108, 0x69);
	d2s_test.SSI_write(0x40, 0x138);
	d2s_test.SSI_write(0x214, 0x64);
	d2s_test.SSI_write(0x218, 0xAE);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x2DC, 0x64);
	d2s_test.SSI_write(0x2E0, 0x64);
	d2s_test.SSI_write(0x2E4, 0x64);
	d2s_test.SSI_write(0x2E8, 0x14);
	d2s_test.SSI_write(0x2EC, 0x18);
	d2s_test.SSI_write(0x2F0, 0x6);
	d2s_test.SSI_write(0x2F4, 0x7);
	d2s_test.SSI_write(0x2F8, 0xA);
	d2s_test.SSI_write(0x2FC, 0x8);
	d2s_test.SSI_write(0x300, 0xB);

	d2s_test.SSI_write(0x204, 0x144, false);
	d2s_test.SSI_write(0x12C, 0x8400);

	d2s_test.SSI_write(0x204, 0x307, false);
	d2s_test.SSI_write(0x3B4, 0x50);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x64, 0xA);

	d2s_test.SSI_write(0x204, 0x2, false);
	d2s_test.SSI_write(0x4, 0x400);

	d2s_test.SSI_write(0x204, 0x20, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x204, 0x68, false);
	d2s_test.SSI_write(0x10, 0x0);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x14, 0x60);

	d2s_test.SSI_write(0x204, 0x7D7D, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x7D32);

	d2s_test.SSI_write(0x204, 0x2225, false);
	d2s_test.SSI_write(0x24, 0x6FCF);

	d2s_test.SSI_write(0x204, 0x95EA, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0xD8, 0x5500);

	d2s_test.SSI_write(0x204, 0x57FA, false);
	d2s_test.SSI_write(0xDC, 0x95FA);

	d2s_test.SSI_write(0x204, 0xFFA9, false);
	d2s_test.SSI_write(0xE0, 0x5FEA);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0xE4, 0xF);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x38, 0x95);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x170, 0xB40);

	d2s_test.SSI_write(0x204, 0x20, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x18, 0x0);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x1C, 0x40);
	d2s_test.SSI_write(0x30, 0x0);
	d2s_test.SSI_write(0x8, 0x1E1E);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x220, 0xA05B);
	d2s_test.SSI_write(0x200, 0xA0);
	d2s_test.SSI_write(0x204, 0x10);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x1FC, 0x7);

	d2s_test.SSI_write(0x204, 0x5110, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x1C, 0x101);

	d2s_test.SSI_write(0x204, 0x1B2F, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x248, 0x53BA);

	d2s_test.SSI_write(0x204, 0x3046, false);
	d2s_test.SSI_write(0x24C, 0xB0B0);

	d2s_test.SSI_write(0x204, 0x3253, false);
	d2s_test.SSI_write(0x25C, 0xE1FC);

	d2s_test.SSI_write(0x204, 0xC0C6, false);
	d2s_test.SSI_write(0x260, 0x9168);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x264, 0x2A0A);

	d2s_test.SSI_write(0x204, 0x1, false);
	d2s_test.SSI_write(0x268, 0x1AA0);

	d2s_test.SSI_write(0x204, 0x9C2, false);
	d2s_test.SSI_write(0x3B0, 0x780A);

	d2s_test.SSI_write(0x204, 0x5DC, false);
	d2s_test.SSI_write(0x3B4, 0x594);

	d2s_test.SSI_write(0x204, 0x148, false);
	d2s_test.SSI_write(0x3B8, 0x7005);

	d2s_test.SSI_write(0x204, 0x3A00, false);
	d2s_test.SSI_write(0x3BC, 0x2A0);

	d2s_test.SSI_write(0x204, 0x19C6, false);
	d2s_test.SSI_write(0x3C0, 0x4005);

	d2s_test.SSI_write(0x204, 0x1D4C, false);
	d2s_test.SSI_write(0x3C4, 0x270);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x3C8, 0x0);           //@2017-06-22, enable IQ compesate

	d2s_test.SSI_write(0x204, 0x206, false);
	d2s_test.SSI_write(0x3D0, 0x4005);

	d2s_test.SSI_write(0x204, 0x3E8, false);
	d2s_test.SSI_write(0x3D4, 0xFA);

	d2s_test.SSI_write(0x204, 0x47FF, false);
	d2s_test.SSI_write(0x3D8, 0xFFFF);

	d2s_test.SSI_write(0x204, 0xFFFF, false);
	d2s_test.SSI_write(0x3DC, 0xFFFF);

	d2s_test.SSI_write(0x204, 0x1FFF, false);
	d2s_test.SSI_write(0x3E0, 0xFFFF);

	d2s_test.SSI_write(0x204, 0xFFFF, false);
	d2s_test.SSI_write(0x3E4, 0xFFFF);

	d2s_test.SSI_write(0x204, 0x5FFF, false);
	d2s_test.SSI_write(0x3E8, 0xFFFF);

	d2s_test.SSI_write(0x204, 0xFFFF, false);
	d2s_test.SSI_write(0x3EC, 0xFFFF);

	d2s_test.SSI_write(0x204, 0x50, false);
	d2s_test.SSI_write(0x16C, 0x2D0);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x44, 0x2147);

	d2s_test.SSI_write(0x204, 0xD4, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x50, 0xE0F4);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x44, 0x20C7);

	d2s_test.SSI_write(0x204, 0x2812, false);
	d2s_test.SSI_write(0x3C, 0x2848);

	d2s_test.SSI_write(0x204, 0xB4, false);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x8C, false);
	d2s_test.SSI_write(0x120, 0x9999);

	d2s_test.SSI_write(0x204, 0x1C, false);
	d2s_test.SSI_write(0x138, 0x1C28);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x270, 0x1);
	d2s_test.SSI_write(0x274, 0x0);
	d2s_test.SSI_write(0x274, 0x1);
	d2s::d2s_LABEL_END();
}

void Cal_ABB_RF_2G_Init_Module() {

	//File:  Cal_init.xlsx
	//Sheet: Cal_ABB_RF_2G_Init_Module
	//File time: 5/25/2017 5:14:21 AM
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);    //ProductionMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s_test.SSI_write(0x4, 0x0);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x2);
	d2s_test.SSI_write(0x10, 0x2);
	d2s_test.SSI_write(0x14, 0x7FF0);
	d2s_test.SSI_write(0x18, 0x7FF0);
	d2s_test.SSI_write(0x1C, 0x1D1D);
	d2s_test.SSI_write(0x20, 0x37);
	d2s_test.SSI_write(0x24, 0x80);
	d2s_test.SSI_write(0x28, 0x80);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0x30, 0x0);
	d2s_test.SSI_write(0x34, 0x4111);
	d2s_test.SSI_write(0x38, 0x113);
	d2s_test.SSI_write(0x3C, 0x444);
	d2s_test.SSI_write(0x40, 0x596);
	d2s_test.SSI_write(0x44, 0x5D7);
	d2s_test.SSI_write(0x48, 0x596);
	d2s_test.SSI_write(0x4C, 0x5D7);
	d2s_test.SSI_write(0x50, 0x416);
	d2s_test.SSI_write(0x54, 0x0);
	d2s_test.SSI_write(0x58, 0x0);
	d2s_test.SSI_write(0x5C, 0x0);
	d2s_test.SSI_write(0x60, 0x0);
	d2s_test.SSI_write(0x64, 0x0);
	d2s_test.SSI_write(0x68, 0x0);
	d2s_test.SSI_write(0x6C, 0x0);
	d2s_test.SSI_write(0x70, 0x7000);
	d2s_test.SSI_write(0x74, 0x8080);
	d2s_test.SSI_write(0x78, 0x8080);
	d2s_test.SSI_write(0x7C, 0x0);
	d2s_test.SSI_write(0x80, 0x0);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x88, 0x0);
	d2s_test.SSI_write(0x8C, 0x0);
	d2s_test.SSI_write(0x90, 0x1B);
	d2s_test.SSI_write(0x94, 0x1B);
	d2s_test.SSI_write(0x98, 0x1B);
	d2s_test.SSI_write(0x9C, 0x3A34);
	d2s_test.SSI_write(0xA0, 0x1B);
	d2s_test.SSI_write(0xA4, 0x1B);
	d2s_test.SSI_write(0xA8, 0x1B);
	d2s_test.SSI_write(0xAC, 0x3A34);
	d2s_test.SSI_write(0xB0, 0x1F);
	d2s_test.SSI_write(0xB4, 0x1F);
	d2s_test.SSI_write(0xB8, 0x1F);
	d2s_test.SSI_write(0xBC, 0x1F);
	d2s_test.SSI_write(0xC0, 0x20);
	d2s_test.SSI_write(0xC4, 0x20);
	d2s_test.SSI_write(0xC8, 0x22);
	d2s_test.SSI_write(0xCC, 0x20);
	d2s_test.SSI_write(0xD0, 0x22);
	d2s_test.SSI_write(0xD4, 0x20);
	d2s_test.SSI_write(0xD8, 0x20);
	d2s_test.SSI_write(0xDC, 0xB8F9);
	d2s_test.SSI_write(0xE0, 0x73A5);
	d2s_test.SSI_write(0xE4, 0x5171);
	d2s_test.SSI_write(0xE8, 0x41);
	d2s_test.SSI_write(0xEC, 0x24);
	d2s_test.SSI_write(0xF0, 0x23);
	d2s_test.SSI_write(0xF4, 0x22);
	d2s_test.SSI_write(0xF8, 0x20);
	d2s_test.SSI_write(0xFC, 0x22);
	d2s_test.SSI_write(0x100, 0x20);
	d2s_test.SSI_write(0x104, 0x20);
	d2s_test.SSI_write(0x108, 0xB8F9);
	d2s_test.SSI_write(0x10C, 0x73A4);
	d2s_test.SSI_write(0x110, 0x5274);
	d2s_test.SSI_write(0x114, 0x42);
	d2s_test.SSI_write(0x12C, 0x1F8);
	d2s_test.SSI_write(0x130, 0x9F1);
	d2s_test.SSI_write(0x134, 0x8600);
	d2s_test.SSI_write(0x138, 0xF942);
	d2s_test.SSI_write(0x13C, 0xD740);
	d2s_test.SSI_write(0x140, 0x24A5);
	d2s_test.SSI_write(0x144, 0xA1);
	d2s_test.SSI_write(0x148, 0x12FF);
	d2s_test.SSI_write(0x14C, 0x830);
	d2s_test.SSI_write(0x150, 0x0);
	d2s_test.SSI_write(0x154, 0x0);
	d2s_test.SSI_write(0x17C, 0xFC);
	d2s_test.SSI_write(0x180, 0xDF);
	d2s_test.SSI_write(0x184, 0x2CC);
	d2s_test.SSI_write(0x188, 0x66);
	d2s_test.SSI_write(0x18C, 0x7E49);
	d2s_test.SSI_write(0x190, 0x130D);
	d2s_test.SSI_write(0x194, 0x1C00);
	d2s_test.SSI_write(0x198, 0xC0C);
	d2s_test.SSI_write(0x19C, 0xC0C);
	d2s_test.SSI_write(0x1A0, 0x815);
	d2s_test.SSI_write(0x1A4, 0x1111);
	d2s_test.SSI_write(0x1A8, 0x110D);
	d2s_test.SSI_write(0x1AC, 0x2226);
	d2s_test.SSI_write(0x1B0, 0x2222);
	d2s_test.SSI_write(0x1B4, 0x1A33);
	d2s_test.SSI_write(0x1B8, 0x2F2F);
	d2s_test.SSI_write(0x1BC, 0x2F2B);
	d2s_test.SSI_write(0x1C0, 0x2010);
	d2s_test.SSI_write(0x1C4, 0x40);
	d2s_test.SSI_write(0x1C8, 0x0);
	d2s_test.SSI_write(0x1D8, 0x1A4C);
	d2s_test.SSI_write(0x1DC, 0x8080);
	d2s_test.SSI_write(0x1E0, 0x8080);
	d2s_test.SSI_write(0x1E4, 0x28D6);
	d2s_test.SSI_write(0x21C, 0x1F8);
	d2s_test.SSI_write(0x220, 0x9F1);
	d2s_test.SSI_write(0x224, 0x8600);
	d2s_test.SSI_write(0x228, 0xF942);
	d2s_test.SSI_write(0x22C, 0xD740);
	d2s_test.SSI_write(0x230, 0x24A5);
	d2s_test.SSI_write(0x234, 0xA1);
	d2s_test.SSI_write(0x238, 0x12FF);
	d2s_test.SSI_write(0x23C, 0x830);
	d2s_test.SSI_write(0x240, 0x0);
	d2s_test.SSI_write(0x244, 0x0);
	d2s_test.SSI_write(0x26C, 0xBC);
	d2s_test.SSI_write(0x270, 0xDF);
	d2s_test.SSI_write(0x274, 0x2CC);
	d2s_test.SSI_write(0x278, 0x66);
	d2s_test.SSI_write(0x27C, 0x7E49);
	d2s_test.SSI_write(0x280, 0x130D);
	d2s_test.SSI_write(0x284, 0x1C00);
	d2s_test.SSI_write(0x288, 0xC0C);
	d2s_test.SSI_write(0x28C, 0xC0C);
	d2s_test.SSI_write(0x290, 0x815);
	d2s_test.SSI_write(0x294, 0x1111);
	d2s_test.SSI_write(0x298, 0x110D);
	d2s_test.SSI_write(0x29C, 0x2226);
	d2s_test.SSI_write(0x2A0, 0x2222);
	d2s_test.SSI_write(0x2A4, 0x1A33);
	d2s_test.SSI_write(0x2A8, 0x2F2F);
	d2s_test.SSI_write(0x2AC, 0x2F2B);
	d2s_test.SSI_write(0x2B0, 0x2010);
	d2s_test.SSI_write(0x2B4, 0x40);
	d2s_test.SSI_write(0x2B8, 0x0);
	d2s_test.SSI_write(0x2BC, 0x0);
	d2s_test.SSI_write(0x2C8, 0x1A4C);
	d2s_test.SSI_write(0x2CC, 0x8080);
	d2s_test.SSI_write(0x2D0, 0x8080);
	d2s_test.SSI_write(0x2D4, 0x28D6);
	d2s_test.SSI_write(0x2D8, 0xC);
	d2s_test.SSI_write(0x2DC, 0x1);
	d2s_test.SSI_write(0x2E0, 0xC);
	d2s_test.SSI_write(0x2E4, 0x0);
	d2s_test.SSI_write(0x2E8, 0x0);
	d2s_test.SSI_write(0x2EC, 0x0);
	d2s_test.SSI_write(0x2F0, 0x0);
	d2s_test.SSI_write(0x2F4, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0xC4, 0x441);
	d2s_test.SSI_write(0xC8, 0x8776);
	d2s_test.SSI_write(0xCC, 0xA998);
	d2s_test.SSI_write(0xD0, 0x3221);
	d2s_test.SSI_write(0xD4, 0x6543);
	d2s_test.SSI_write(0xD8, 0x2222);
	d2s_test.SSI_write(0xDC, 0x0);
	d2s_test.SSI_write(0xE0, 0x1);
	d2s_test.SSI_write(0xE4, 0xDCF2);
	d2s_test.SSI_write(0xE8, 0xDD92);
	d2s_test.SSI_write(0xEC, 0x65B3);
	d2s_test.SSI_write(0xF0, 0xA123);
	d2s_test.SSI_write(0xF4, 0xDD72);
	d2s_test.SSI_write(0xF8, 0xDE12);
	d2s_test.SSI_write(0xFC, 0x6633);
	d2s_test.SSI_write(0x100, 0xA163);
	d2s_test.SSI_write(0x104, 0xDDC2);
	d2s_test.SSI_write(0x108, 0xDE62);
	d2s_test.SSI_write(0x10C, 0x6683);
	d2s_test.SSI_write(0x110, 0xA193);
	d2s_test.SSI_write(0x114, 0xDE32);
	d2s_test.SSI_write(0x118, 0xDED2);
	d2s_test.SSI_write(0x11C, 0x66F3);
	d2s_test.SSI_write(0x120, 0xA1C3);
	d2s_test.SSI_write(0x124, 0x0);
	d2s_test.SSI_write(0x128, 0x0);
	d2s_test.SSI_write(0x12C, 0x0);
	d2s_test.SSI_write(0x130, 0x0);
	d2s_test.SSI_write(0x134, 0x441);
	d2s_test.SSI_write(0x138, 0x8776);
	d2s_test.SSI_write(0x13C, 0xA998);
	d2s_test.SSI_write(0x140, 0x3221);
	d2s_test.SSI_write(0x144, 0x6543);
	d2s_test.SSI_write(0x148, 0x2222);
	d2s_test.SSI_write(0x14C, 0x0);
	d2s_test.SSI_write(0x150, 0x1);
	d2s_test.SSI_write(0x154, 0xDCF2);
	d2s_test.SSI_write(0x158, 0xDD92);
	d2s_test.SSI_write(0x15C, 0x65B3);
	d2s_test.SSI_write(0x160, 0xA123);
	d2s_test.SSI_write(0x164, 0xDD72);
	d2s_test.SSI_write(0x168, 0xDE12);
	d2s_test.SSI_write(0x16C, 0x6633);
	d2s_test.SSI_write(0x170, 0xA163);
	d2s_test.SSI_write(0x174, 0xDDC2);
	d2s_test.SSI_write(0x178, 0xDE62);
	d2s_test.SSI_write(0x17C, 0x6683);
	d2s_test.SSI_write(0x180, 0xA193);
	d2s_test.SSI_write(0x184, 0xDE32);
	d2s_test.SSI_write(0x188, 0xDED2);
	d2s_test.SSI_write(0x18C, 0x66F3);
	d2s_test.SSI_write(0x190, 0xA1C3);
	d2s_test.SSI_write(0x194, 0xC);
	d2s_test.SSI_write(0x198, 0x0);
	d2s_test.SSI_write(0x19C, 0xC);
	d2s_test.SSI_write(0x1A0, 0x1);
	d2s_test.SSI_write(0x1B8, 0x3F7F);
	d2s_test.SSI_write(0x1BC, 0xF1F);
	d2s_test.SSI_write(0x1C0, 0x307);
	d2s_test.SSI_write(0x1C4, 0x1);
	d2s_test.SSI_write(0x1C8, 0xB976);
	d2s_test.SSI_write(0x1CC, 0x115);
	d2s_test.SSI_write(0x1D0, 0xB976);
	d2s_test.SSI_write(0x1D4, 0x115);
	d2s_test.SSI_write(0x1D8, 0xB975);
	d2s_test.SSI_write(0x1DC, 0x115);
	d2s_test.SSI_write(0x1E0, 0xB975);
	d2s_test.SSI_write(0x1E4, 0x115);
	d2s_test.SSI_write(0x1E8, 0xB975);
	d2s_test.SSI_write(0x1EC, 0x115);
	d2s_test.SSI_write(0x1F0, 0xB975);
	d2s_test.SSI_write(0x1F4, 0x115);
	d2s_test.SSI_write(0x1F8, 0xB975);
	d2s_test.SSI_write(0x1FC, 0x115);
	d2s_test.SSI_write(0x200, 0x0);
	d2s_test.SSI_write(0x204, 0x0);
	d2s_test.SSI_write(0x208, 0x0);
	d2s_test.SSI_write(0x20C, 0x0);
	d2s_test.SSI_write(0x210, 0x0);
	d2s_test.SSI_write(0x214, 0x0);
	d2s_test.SSI_write(0x220, 0x3F7F);
	d2s_test.SSI_write(0x224, 0xF1F);
	d2s_test.SSI_write(0x228, 0x307);
	d2s_test.SSI_write(0x22C, 0x1);
	d2s_test.SSI_write(0x230, 0xB975);
	d2s_test.SSI_write(0x234, 0x135);
	d2s_test.SSI_write(0x238, 0xB975);
	d2s_test.SSI_write(0x23C, 0x125);
	d2s_test.SSI_write(0x240, 0xB975);
	d2s_test.SSI_write(0x244, 0x115);
	d2s_test.SSI_write(0x248, 0xB975);
	d2s_test.SSI_write(0x24C, 0x134);
	d2s_test.SSI_write(0x250, 0xB975);
	d2s_test.SSI_write(0x254, 0x115);
	d2s_test.SSI_write(0x258, 0xB975);
	d2s_test.SSI_write(0x25C, 0x115);
	d2s_test.SSI_write(0x260, 0xB965);
	d2s_test.SSI_write(0x264, 0x115);
	d2s_test.SSI_write(0x268, 0x0);
	d2s_test.SSI_write(0x26C, 0x0);
	d2s_test.SSI_write(0x270, 0x0);
	d2s_test.SSI_write(0x274, 0x0);
	d2s_test.SSI_write(0x278, 0x0);
	d2s_test.SSI_write(0x27C, 0x0);
	d2s_test.SSI_write(0x280, 0x37);
	d2s_test.SSI_write(0x284, 0x2070);
	d2s_test.SSI_write(0x288, 0x1F);
	d2s_test.SSI_write(0x28C, 0x37);
	d2s_test.SSI_write(0x290, 0x2070);
	d2s_test.SSI_write(0x294, 0x1F);
	d2s_test.SSI_write(0x298, 0x0);
	d2s_test.SSI_write(0x29C, 0x0);
	d2s_test.SSI_write(0x2A4, 0x4442);
	d2s_test.SSI_write(0x2A8, 0x4542);
	d2s_test.SSI_write(0x2AC, 0x4542);
	d2s_test.SSI_write(0x2B0, 0x4642);
	d2s_test.SSI_write(0x2B4, 0x4642);
	d2s_test.SSI_write(0x2B8, 0x4742);
	d2s_test.SSI_write(0x2BC, 0x4842);
	d2s_test.SSI_write(0x2C0, 0x4441);
	d2s_test.SSI_write(0x2C4, 0x4541);
	d2s_test.SSI_write(0x2C8, 0x4541);
	d2s_test.SSI_write(0x2CC, 0x4642);
	d2s_test.SSI_write(0x2D0, 0x4643);
	d2s_test.SSI_write(0x2D4, 0x4742);
	d2s_test.SSI_write(0x2D8, 0x4845);
	d2s_test.SSI_write(0x2DC, 0x3337);
	d2s_test.SSI_write(0x2E0, 0x3337);
	d2s_test.SSI_write(0x2E4, 0x3337);
	d2s_test.SSI_write(0x2E8, 0x3337);
	d2s_test.SSI_write(0x2EC, 0x222);
	d2s_test.SSI_write(0x2F0, 0x222);
	d2s_test.SSI_write(0x2F4, 0x222);
	d2s_test.SSI_write(0x2F8, 0x222);
	d2s_test.SSI_write(0x2FC, 0x222);
	d2s_test.SSI_write(0x300, 0x222);
	d2s_test.SSI_write(0x304, 0x222);
	d2s_test.SSI_write(0x308, 0x333);
	d2s_test.SSI_write(0x30C, 0x444);
	d2s_test.SSI_write(0x310, 0x555);
	d2s_test.SSI_write(0x314, 0x555);
	d2s_test.SSI_write(0x318, 0x666);
	d2s_test.SSI_write(0x31C, 0x3210);
	d2s_test.SSI_write(0x320, 0x7654);
	d2s_test.SSI_write(0x324, 0x6222);
	d2s_test.SSI_write(0x328, 0x0);
	d2s_test.SSI_write(0x32C, 0x0);
	d2s_test.SSI_write(0x330, 0x0);
	d2s_test.SSI_write(0x334, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x310, 0x4);
	d2s_test.SSI_write(0x314, 0x31);
	d2s_test.SSI_write(0x318, 0x31);
	d2s_test.SSI_write(0x31C, 0x0);
	d2s_test.SSI_write(0x320, 0x0);
	d2s_test.SSI_write(0x324, 0x4444);
	d2s_test.SSI_write(0x328, 0x140);
	d2s_test.SSI_write(0x32C, 0x1133);
	d2s_test.SSI_write(0x330, 0x9577);
	d2s_test.SSI_write(0x334, 0x52C);
	d2s_test.SSI_write(0x338, 0x784);
	d2s_test.SSI_write(0x360, 0x31);
	d2s_test.SSI_write(0x364, 0x31);
	d2s_test.SSI_write(0x368, 0x0);
	d2s_test.SSI_write(0x36C, 0x0);
	d2s_test.SSI_write(0x370, 0x4444);
	d2s_test.SSI_write(0x374, 0x140);
	d2s_test.SSI_write(0x378, 0x1133);
	d2s_test.SSI_write(0x37C, 0x9577);
	d2s_test.SSI_write(0x380, 0x52C);
	d2s_test.SSI_write(0x384, 0x784);
	d2s_test.SSI_write(0x3C0, 0x55);
	d2s_test.SSI_write(0x3C4, 0xA);
	d2s_test.SSI_write(0x3C8, 0x84);
	d2s_test.SSI_write(0x3CC, 0x84);
	d2s_test.SSI_write(0x3D0, 0xCBB8);
	d2s_test.SSI_write(0x3D4, 0x6542);
	d2s_test.SSI_write(0x3D8, 0x405);
	d2s_test.SSI_write(0x3DC, 0x607);
	d2s_test.SSI_write(0x3E0, 0x809);
	d2s_test.SSI_write(0x3E4, 0xA0B);
	d2s_test.SSI_write(0x3E8, 0xC0D);
	d2s_test.SSI_write(0x3EC, 0xE0F);
	d2s_test.SSI_write(0x3F0, 0x1112);
	d2s_test.SSI_write(0x3F4, 0x1314);
	d2s_test.SSI_write(0x3F8, 0x1516);
	d2s_test.SSI_write(0x3FC, 0x1718);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x0, 0x191A);
	d2s_test.SSI_write(0x4, 0x1B1C);
	d2s_test.SSI_write(0x8, 0x1D20);
	d2s_test.SSI_write(0xC, 0x2020);
	d2s_test.SSI_write(0x10, 0x2020);
	d2s_test.SSI_write(0x14, 0x2020);
	d2s_test.SSI_write(0x18, 0x80);
	d2s_test.SSI_write(0x40, 0xA);
	d2s_test.SSI_write(0x44, 0x84);
	d2s_test.SSI_write(0x48, 0x84);
	d2s_test.SSI_write(0x4C, 0xCBB8);
	d2s_test.SSI_write(0x50, 0x6542);
	d2s_test.SSI_write(0x54, 0x405);
	d2s_test.SSI_write(0x58, 0x607);
	d2s_test.SSI_write(0x5C, 0x809);
	d2s_test.SSI_write(0x60, 0xA0B);
	d2s_test.SSI_write(0x64, 0xC0D);
	d2s_test.SSI_write(0x68, 0xE0F);
	d2s_test.SSI_write(0x6C, 0x1112);
	d2s_test.SSI_write(0x70, 0x1314);
	d2s_test.SSI_write(0x74, 0x1516);
	d2s_test.SSI_write(0x78, 0x1718);
	d2s_test.SSI_write(0x7C, 0x191A);
	d2s_test.SSI_write(0x80, 0x1B1C);
	d2s_test.SSI_write(0x84, 0x1D20);
	d2s_test.SSI_write(0x88, 0x2020);
	d2s_test.SSI_write(0x8C, 0x2020);
	d2s_test.SSI_write(0x90, 0x2020);
	d2s_test.SSI_write(0x94, 0x80);
	d2s_test.SSI_write(0x98, 0x0);
	d2s_test.SSI_write(0x9C, 0x0);
	d2s_test.SSI_write(0xA0, 0x0);
	d2s_test.SSI_write(0xA4, 0x550);
	d2s_test.SSI_write(0x350, 0x18A0);
	d2s_test.SSI_write(0x354, 0x4AA8);
	d2s_test.SSI_write(0x358, 0x81);
	d2s_test.SSI_write(0x35C, 0x2A00); //2B00->2A00@2017-08-14 for V210,B00 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x360, 0x0);
	d2s_test.SSI_write(0x364, 0x18A0);
	d2s_test.SSI_write(0x368, 0x4AA8);
	d2s_test.SSI_write(0x36C, 0x81);
	d2s_test.SSI_write(0x370, 0x2A00); //2B00->2A00@2017-08-14 for V210,B00 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x374, 0x0);
	d2s_test.SSI_write(0x378, 0x0);
	d2s_test.SSI_write(0x37C, 0x0);
	d2s_test.SSI_write(0x380, 0x0);
	d2s_test.SSI_write(0x384, 0x0);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xC8, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s_test.SSI_write(0x4, 0x100B);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x8000);
	d2s_test.SSI_write(0x10, 0x52AA);
	d2s_test.SSI_write(0x14, 0xAAAB);
	d2s_test.SSI_write(0x18, 0x4000);
	d2s_test.SSI_write(0x20, 0x12);
	d2s_test.SSI_write(0x24, 0x3000);
	d2s_test.SSI_write(0x28, 0x100);
	d2s_test.SSI_write(0x2C, 0x0); //wl_pll_reg_523  1800->0,to reduce Spur Power @2017-06-23
	d2s_test.SSI_write(0x30, 0xE0);
	d2s_test.SSI_write(0x34, 0x93A8);
	d2s_test.SSI_write(0x38, 0x5004);
	d2s_test.SSI_write(0x3C, 0x90A0);
	d2s_test.SSI_write(0x40, 0x0);
	d2s_test.SSI_write(0x44, 0x1780);
	d2s_test.SSI_write(0x48, 0x0);
	d2s_test.SSI_write(0x4C, 0x0);
	d2s_test.SSI_write(0x50, 0x0);
	d2s_test.SSI_write(0x54, 0x0);
	d2s_test.SSI_write(0x58, 0xC080);
	d2s_test.SSI_write(0x5C, 0x66AE);
	d2s_test.SSI_write(0x60, 0x1E00);
	d2s_test.SSI_write(0x64, 0x8004);
	d2s_test.SSI_write(0x68, 0x7742);
	d2s_test.SSI_write(0x6C, 0x84F);
	d2s_test.SSI_write(0x70, 0x9600);
	d2s_test.SSI_write(0x74, 0xE002);
	d2s_test.SSI_write(0x78, 0x0);
	d2s_test.SSI_write(0x7C, 0x0);
	d2s_test.SSI_write(0x80, 0x9AC8);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x88, 0x4);
	d2s_test.SSI_write(0x8C, 0x0);
	d2s_test.SSI_write(0xC0, 0x0);
	d2s_test.SSI_write(0xC4, 0x404);
	d2s_test.SSI_write(0xC8, 0xC816);
	d2s_test.SSI_write(0xCC, 0x0);
	d2s_test.SSI_write(0xD0, 0x0);
	d2s_test.SSI_write(0xD4, 0x0);
	d2s_test.SSI_write(0xD8, 0x0);
	d2s_test.SSI_write(0xDC, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x350, 0x18A0);
	d2s_test.SSI_write(0x354, 0x4AA8);
	d2s_test.SSI_write(0x358, 0x81);
	d2s_test.SSI_write(0x35C, 0x2A00); //2B00->2A00@2017-08-14 for V210,B00 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x360, 0x0);
	d2s_test.SSI_write(0x364, 0x18A0);
	d2s_test.SSI_write(0x368, 0x4AA8);
	d2s_test.SSI_write(0x36C, 0x81);
	d2s_test.SSI_write(0x370, 0x2A00); //2B00->2A00@2017-08-14 for V210,B00 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x374, 0x0);
	d2s_test.SSI_write(0x378, 0x0);
	d2s_test.SSI_write(0x37C, 0x0);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x8, 0x3233);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x378, 0x100);
	d2s_test.SSI_write(0x37C, 0x4);
	d2s_test.SSI_write(0x380, 0x0);
	d2s_test.SSI_write(0x384, 0x0);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0xC, 0x3233);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x380, 0x100);
	d2s_test.SSI_write(0x384, 0x4);
	d2s::d2s_LABEL_END();
}

void Cal_ABB_RF_5G_Init_Module() {

	//File:  Cal_init.xlsx
	//Sheet: Cal_ABB_RF_5G_Init_Module
	//File time: 5/25/2017 5:14:21 AM
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s_test.SSI_write(0x4, 0x0);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x2);
	d2s_test.SSI_write(0x10, 0x2);
	d2s_test.SSI_write(0x14, 0x7F0F);
	d2s_test.SSI_write(0x18, 0x7F0F);
	d2s_test.SSI_write(0x1C, 0x2121);
	d2s_test.SSI_write(0x20, 0x37);
	d2s_test.SSI_write(0x24, 0x80);
	d2s_test.SSI_write(0x28, 0x80);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0x30, 0x0);
	d2s_test.SSI_write(0x34, 0x111);
	d2s_test.SSI_write(0x38, 0x113);
	d2s_test.SSI_write(0x3C, 0x444);
	d2s_test.SSI_write(0x40, 0x596);
	d2s_test.SSI_write(0x44, 0x5D7);
	d2s_test.SSI_write(0x48, 0x596);
	d2s_test.SSI_write(0x4C, 0x5D7);
	d2s_test.SSI_write(0x50, 0x416);
	d2s_test.SSI_write(0x54, 0x0);
	d2s_test.SSI_write(0x58, 0x0);
	d2s_test.SSI_write(0x5C, 0x0);
	d2s_test.SSI_write(0x60, 0x0);
	d2s_test.SSI_write(0x64, 0x0);
	d2s_test.SSI_write(0x68, 0x0);
	d2s_test.SSI_write(0x6C, 0x0);
	d2s_test.SSI_write(0x70, 0x7000);
	d2s_test.SSI_write(0x74, 0x8080);
	d2s_test.SSI_write(0x78, 0x8080);
	d2s_test.SSI_write(0x7C, 0x0);
	d2s_test.SSI_write(0x80, 0x0);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x88, 0x0);
	d2s_test.SSI_write(0x8C, 0x0);
	d2s_test.SSI_write(0x90, 0x1B);
	d2s_test.SSI_write(0x94, 0x1B);
	d2s_test.SSI_write(0x98, 0x1B);
	d2s_test.SSI_write(0x9C, 0x3A34);
	d2s_test.SSI_write(0xA0, 0x1B);
	d2s_test.SSI_write(0xA4, 0x1B);
	d2s_test.SSI_write(0xA8, 0x1B);
	d2s_test.SSI_write(0xAC, 0x3A34);
	d2s_test.SSI_write(0xB0, 0x1F);
	d2s_test.SSI_write(0xB4, 0x1F);
	d2s_test.SSI_write(0xB8, 0x1F);
	d2s_test.SSI_write(0xBC, 0x1F);
	d2s_test.SSI_write(0xC0, 0x20);
	d2s_test.SSI_write(0xC4, 0x20);
	d2s_test.SSI_write(0xC8, 0x22);
	d2s_test.SSI_write(0xCC, 0x20);
	d2s_test.SSI_write(0xD0, 0x22);
	d2s_test.SSI_write(0xD4, 0x20);
	d2s_test.SSI_write(0xD8, 0x20);
	d2s_test.SSI_write(0xDC, 0xB8F9);
	d2s_test.SSI_write(0xE0, 0x73A5);
	d2s_test.SSI_write(0xE4, 0x5171);
	d2s_test.SSI_write(0xE8, 0x41);
	d2s_test.SSI_write(0xEC, 0x24);
	d2s_test.SSI_write(0xF0, 0x23);
	d2s_test.SSI_write(0xF4, 0x22);
	d2s_test.SSI_write(0xF8, 0x20);
	d2s_test.SSI_write(0xFC, 0x22);
	d2s_test.SSI_write(0x100, 0x20);
	d2s_test.SSI_write(0x104, 0x20);
	d2s_test.SSI_write(0x108, 0xB8F9);
	d2s_test.SSI_write(0x10C, 0x73A4);
	d2s_test.SSI_write(0x110, 0x5274);
	d2s_test.SSI_write(0x114, 0x42);
	d2s_test.SSI_write(0x12C, 0x1F8);
	d2s_test.SSI_write(0x130, 0x9F1);
	d2s_test.SSI_write(0x134, 0x8600);
	d2s_test.SSI_write(0x138, 0xF942);
	d2s_test.SSI_write(0x13C, 0xD740);
	d2s_test.SSI_write(0x140, 0x24A5);
	d2s_test.SSI_write(0x144, 0xA1);
	d2s_test.SSI_write(0x148, 0x12FF);
	d2s_test.SSI_write(0x14C, 0x830);
	d2s_test.SSI_write(0x150, 0x0);
	d2s_test.SSI_write(0x154, 0x0);
	d2s_test.SSI_write(0x17C, 0xFC);
	d2s_test.SSI_write(0x180, 0xDF);
	d2s_test.SSI_write(0x184, 0x2CC);
	d2s_test.SSI_write(0x188, 0x66);
	d2s_test.SSI_write(0x18C, 0x7E49);
	d2s_test.SSI_write(0x190, 0x130D);
	d2s_test.SSI_write(0x194, 0x1C00);
	d2s_test.SSI_write(0x198, 0xC0C);
	d2s_test.SSI_write(0x19C, 0xC0C);
	d2s_test.SSI_write(0x1A0, 0x815);
	d2s_test.SSI_write(0x1A4, 0x1111);
	d2s_test.SSI_write(0x1A8, 0x110D);
	d2s_test.SSI_write(0x1AC, 0x2226);
	d2s_test.SSI_write(0x1B0, 0x2222);
	d2s_test.SSI_write(0x1B4, 0x1A33);
	d2s_test.SSI_write(0x1B8, 0x2F2F);
	d2s_test.SSI_write(0x1BC, 0x2F2B);
	d2s_test.SSI_write(0x1C0, 0x2010);
	d2s_test.SSI_write(0x1C4, 0x40);
	d2s_test.SSI_write(0x1C8, 0x0);
	d2s_test.SSI_write(0x1D8, 0x1A4C);
	d2s_test.SSI_write(0x1DC, 0x8080);
	d2s_test.SSI_write(0x1E0, 0x8080);
	d2s_test.SSI_write(0x1E4, 0x28D6);
	d2s_test.SSI_write(0x21C, 0x1F8);
	d2s_test.SSI_write(0x220, 0x9F1);
	d2s_test.SSI_write(0x224, 0x8600);
	d2s_test.SSI_write(0x228, 0xF942);
	d2s_test.SSI_write(0x22C, 0xD740);
	d2s_test.SSI_write(0x230, 0x24A5);
	d2s_test.SSI_write(0x234, 0xA1);
	d2s_test.SSI_write(0x238, 0x12FF);
	d2s_test.SSI_write(0x23C, 0x830);
	d2s_test.SSI_write(0x240, 0x0);
	d2s_test.SSI_write(0x244, 0x0);
	d2s_test.SSI_write(0x26C, 0xBC);
	d2s_test.SSI_write(0x270, 0xDF);
	d2s_test.SSI_write(0x274, 0x2CC);
	d2s_test.SSI_write(0x278, 0x66);
	d2s_test.SSI_write(0x27C, 0x7E49);
	d2s_test.SSI_write(0x280, 0x130D);
	d2s_test.SSI_write(0x284, 0x1C00);
	d2s_test.SSI_write(0x288, 0xC0C);
	d2s_test.SSI_write(0x28C, 0xC0C);
	d2s_test.SSI_write(0x290, 0x815);
	d2s_test.SSI_write(0x294, 0x1111);
	d2s_test.SSI_write(0x298, 0x110D);
	d2s_test.SSI_write(0x29C, 0x2226);
	d2s_test.SSI_write(0x2A0, 0x2222);
	d2s_test.SSI_write(0x2A4, 0x1A33);
	d2s_test.SSI_write(0x2A8, 0x2F2F);
	d2s_test.SSI_write(0x2AC, 0x2F2B);
	d2s_test.SSI_write(0x2B0, 0x2010);
	d2s_test.SSI_write(0x2B4, 0x40);
	d2s_test.SSI_write(0x2B8, 0x0);
	d2s_test.SSI_write(0x2BC, 0x0);
	d2s_test.SSI_write(0x2C8, 0x1A4C);
	d2s_test.SSI_write(0x2CC, 0x8080);
	d2s_test.SSI_write(0x2D0, 0x8080);
	d2s_test.SSI_write(0x2D4, 0x28D6);
	d2s_test.SSI_write(0x2D8, 0xC);
	d2s_test.SSI_write(0x2DC, 0x1);
	d2s_test.SSI_write(0x2E0, 0xC);
	d2s_test.SSI_write(0x2E4, 0x1);
	d2s_test.SSI_write(0x2E8, 0x0);
	d2s_test.SSI_write(0x2EC, 0x0);
	d2s_test.SSI_write(0x2F0, 0x0);
	d2s_test.SSI_write(0x2F4, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0xC4, 0x441);
	d2s_test.SSI_write(0xC8, 0x8776);
	d2s_test.SSI_write(0xCC, 0xA998);
	d2s_test.SSI_write(0xD0, 0x3221);
	d2s_test.SSI_write(0xD4, 0x6543);
	d2s_test.SSI_write(0xD8, 0x2222);
	d2s_test.SSI_write(0xDC, 0x0);
	d2s_test.SSI_write(0xE0, 0x1);
	d2s_test.SSI_write(0xE4, 0xDCF2);
	d2s_test.SSI_write(0xE8, 0xDD92);
	d2s_test.SSI_write(0xEC, 0x65B3);
	d2s_test.SSI_write(0xF0, 0xA123);
	d2s_test.SSI_write(0xF4, 0xDD72);
	d2s_test.SSI_write(0xF8, 0xDE12);
	d2s_test.SSI_write(0xFC, 0x6633);
	d2s_test.SSI_write(0x100, 0xA163);
	d2s_test.SSI_write(0x104, 0xDDC2);
	d2s_test.SSI_write(0x108, 0xDE62);
	d2s_test.SSI_write(0x10C, 0x6683);
	d2s_test.SSI_write(0x110, 0xA193);
	d2s_test.SSI_write(0x114, 0xDE32);
	d2s_test.SSI_write(0x118, 0xDED2);
	d2s_test.SSI_write(0x11C, 0x66F3);
	d2s_test.SSI_write(0x120, 0xA1C3);
	d2s_test.SSI_write(0x124, 0x0);
	d2s_test.SSI_write(0x128, 0x0);
	d2s_test.SSI_write(0x12C, 0x0);
	d2s_test.SSI_write(0x130, 0x0);
	d2s_test.SSI_write(0x134, 0x441);
	d2s_test.SSI_write(0x138, 0x8776);
	d2s_test.SSI_write(0x13C, 0xA998);
	d2s_test.SSI_write(0x140, 0x3221);
	d2s_test.SSI_write(0x144, 0x6543);
	d2s_test.SSI_write(0x148, 0x2222);
	d2s_test.SSI_write(0x14C, 0x0);
	d2s_test.SSI_write(0x150, 0x1);
	d2s_test.SSI_write(0x154, 0xDCF2);
	d2s_test.SSI_write(0x158, 0xDD92);
	d2s_test.SSI_write(0x15C, 0x65B3);
	d2s_test.SSI_write(0x160, 0xA123);
	d2s_test.SSI_write(0x164, 0xDD72);
	d2s_test.SSI_write(0x168, 0xDE12);
	d2s_test.SSI_write(0x16C, 0x6633);
	d2s_test.SSI_write(0x170, 0xA163);
	d2s_test.SSI_write(0x174, 0xDDC2);
	d2s_test.SSI_write(0x178, 0xDE62);
	d2s_test.SSI_write(0x17C, 0x6683);
	d2s_test.SSI_write(0x180, 0xA193);
	d2s_test.SSI_write(0x184, 0xDE32);
	d2s_test.SSI_write(0x188, 0xDED2);
	d2s_test.SSI_write(0x18C, 0x66F3);
	d2s_test.SSI_write(0x190, 0xA1C3);
	d2s_test.SSI_write(0x194, 0xC);
	d2s_test.SSI_write(0x198, 0x1);
	d2s_test.SSI_write(0x19C, 0xC);
	d2s_test.SSI_write(0x1A0, 0x1);
	d2s_test.SSI_write(0x1B8, 0x3F7F);
	d2s_test.SSI_write(0x1BC, 0xF1F);
	d2s_test.SSI_write(0x1C0, 0x307);
	d2s_test.SSI_write(0x1C4, 0x1);
	d2s_test.SSI_write(0x1C8, 0xB976);
	d2s_test.SSI_write(0x1CC, 0x115);
	d2s_test.SSI_write(0x1D0, 0xB976);
	d2s_test.SSI_write(0x1D4, 0x115);
	d2s_test.SSI_write(0x1D8, 0xB975);
	d2s_test.SSI_write(0x1DC, 0x115);
	d2s_test.SSI_write(0x1E0, 0xB975);
	d2s_test.SSI_write(0x1E4, 0x115);
	d2s_test.SSI_write(0x1E8, 0xB975);
	d2s_test.SSI_write(0x1EC, 0x115);
	d2s_test.SSI_write(0x1F0, 0xB975);
	d2s_test.SSI_write(0x1F4, 0x115);
	d2s_test.SSI_write(0x1F8, 0xB975);
	d2s_test.SSI_write(0x1FC, 0x115);
	d2s_test.SSI_write(0x200, 0x0);
	d2s_test.SSI_write(0x204, 0x0);
	d2s_test.SSI_write(0x208, 0x0);
	d2s_test.SSI_write(0x20C, 0x0);
	d2s_test.SSI_write(0x210, 0x0);
	d2s_test.SSI_write(0x214, 0x0);
	d2s_test.SSI_write(0x220, 0x3F7F);
	d2s_test.SSI_write(0x224, 0xF1F);
	d2s_test.SSI_write(0x228, 0x307);
	d2s_test.SSI_write(0x22C, 0x1);
	d2s_test.SSI_write(0x230, 0xB975);
	d2s_test.SSI_write(0x234, 0x135);
	d2s_test.SSI_write(0x238, 0xB975);
	d2s_test.SSI_write(0x23C, 0x125);
	d2s_test.SSI_write(0x240, 0xB975);
	d2s_test.SSI_write(0x244, 0x115);
	d2s_test.SSI_write(0x248, 0xB975);
	d2s_test.SSI_write(0x24C, 0x134);
	d2s_test.SSI_write(0x250, 0xB975);
	d2s_test.SSI_write(0x254, 0x115);
	d2s_test.SSI_write(0x258, 0xB975);
	d2s_test.SSI_write(0x25C, 0x115);
	d2s_test.SSI_write(0x260, 0xB965);
	d2s_test.SSI_write(0x264, 0x115);
	d2s_test.SSI_write(0x268, 0x0);
	d2s_test.SSI_write(0x26C, 0x0);
	d2s_test.SSI_write(0x270, 0x0);
	d2s_test.SSI_write(0x274, 0x0);
	d2s_test.SSI_write(0x278, 0x0);
	d2s_test.SSI_write(0x27C, 0x0);
	d2s_test.SSI_write(0x280, 0x37);
	d2s_test.SSI_write(0x284, 0x2070);
	d2s_test.SSI_write(0x288, 0x1F);
	d2s_test.SSI_write(0x28C, 0x37);
	d2s_test.SSI_write(0x290, 0x2070);
	d2s_test.SSI_write(0x294, 0x1F);
	d2s_test.SSI_write(0x298, 0x0);
	d2s_test.SSI_write(0x29C, 0x0);
	d2s_test.SSI_write(0x2A4, 0x4442);
	d2s_test.SSI_write(0x2A8, 0x4542);
	d2s_test.SSI_write(0x2AC, 0x4542);
	d2s_test.SSI_write(0x2B0, 0x4642);
	d2s_test.SSI_write(0x2B4, 0x4642);
	d2s_test.SSI_write(0x2B8, 0x4742);
	d2s_test.SSI_write(0x2BC, 0x4842);
	d2s_test.SSI_write(0x2C0, 0x4441);
	d2s_test.SSI_write(0x2C4, 0x4541);
	d2s_test.SSI_write(0x2C8, 0x4541);
	d2s_test.SSI_write(0x2CC, 0x4642);
	d2s_test.SSI_write(0x2D0, 0x4643);
	d2s_test.SSI_write(0x2D4, 0x4742);
	d2s_test.SSI_write(0x2D8, 0x4845);
	d2s_test.SSI_write(0x2DC, 0x3337);
	d2s_test.SSI_write(0x2E0, 0x3337);
	d2s_test.SSI_write(0x2E4, 0x3337);
	d2s_test.SSI_write(0x2E8, 0x3337);
	d2s_test.SSI_write(0x2EC, 0x666);
	d2s_test.SSI_write(0x2F0, 0x222);
	d2s_test.SSI_write(0x2F4, 0x222);
	d2s_test.SSI_write(0x2F8, 0x222);
	d2s_test.SSI_write(0x2FC, 0x222);
	d2s_test.SSI_write(0x300, 0x222);
	d2s_test.SSI_write(0x304, 0x222);
	d2s_test.SSI_write(0x308, 0x333);
	d2s_test.SSI_write(0x30C, 0x444);
	d2s_test.SSI_write(0x310, 0x555);
	d2s_test.SSI_write(0x314, 0x555);
	d2s_test.SSI_write(0x318, 0x666);
	d2s_test.SSI_write(0x31C, 0x3210);
	d2s_test.SSI_write(0x320, 0x7654);
	d2s_test.SSI_write(0x324, 0x6222);
	d2s_test.SSI_write(0x328, 0x0);
	d2s_test.SSI_write(0x32C, 0x0);
	d2s_test.SSI_write(0x330, 0x0);
	d2s_test.SSI_write(0x334, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x310, 0x4);
	d2s_test.SSI_write(0x314, 0x31);
	d2s_test.SSI_write(0x318, 0x31);
	d2s_test.SSI_write(0x31C, 0x0);
	d2s_test.SSI_write(0x320, 0x0);
	d2s_test.SSI_write(0x324, 0x4444);
	d2s_test.SSI_write(0x328, 0x140);
	d2s_test.SSI_write(0x32C, 0x1133);
	d2s_test.SSI_write(0x330, 0x9577);
	d2s_test.SSI_write(0x334, 0x52C);
	d2s_test.SSI_write(0x338, 0x784);
	d2s_test.SSI_write(0x360, 0x31);
	d2s_test.SSI_write(0x364, 0x31);
	d2s_test.SSI_write(0x368, 0x0);
	d2s_test.SSI_write(0x36C, 0x0);
	d2s_test.SSI_write(0x370, 0x4444);
	d2s_test.SSI_write(0x374, 0x140);
	d2s_test.SSI_write(0x378, 0x1133);
	d2s_test.SSI_write(0x37C, 0x9577);
	d2s_test.SSI_write(0x380, 0x52C);
	d2s_test.SSI_write(0x384, 0x784);
	d2s_test.SSI_write(0x3C0, 0x55);
	d2s_test.SSI_write(0x3C4, 0xA);
	d2s_test.SSI_write(0x3C8, 0x84);
	d2s_test.SSI_write(0x3CC, 0x84);
	d2s_test.SSI_write(0x3D0, 0xCBB8);
	d2s_test.SSI_write(0x3D4, 0x6542);
	d2s_test.SSI_write(0x3D8, 0x405);
	d2s_test.SSI_write(0x3DC, 0x607);
	d2s_test.SSI_write(0x3E0, 0x809);
	d2s_test.SSI_write(0x3E4, 0xA0B);
	d2s_test.SSI_write(0x3E8, 0xC0D);
	d2s_test.SSI_write(0x3EC, 0xE0F);
	d2s_test.SSI_write(0x3F0, 0x1112);
	d2s_test.SSI_write(0x3F4, 0x1314);
	d2s_test.SSI_write(0x3F8, 0x1516);
	d2s_test.SSI_write(0x3FC, 0x1718);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x0, 0x191A);
	d2s_test.SSI_write(0x4, 0x1B1C);
	d2s_test.SSI_write(0x8, 0x1D20);
	d2s_test.SSI_write(0xC, 0x2020);
	d2s_test.SSI_write(0x10, 0x2020);
	d2s_test.SSI_write(0x14, 0x2020);
	d2s_test.SSI_write(0x18, 0x80);
	d2s_test.SSI_write(0x40, 0xA);
	d2s_test.SSI_write(0x44, 0x84);
	d2s_test.SSI_write(0x48, 0x84);
	d2s_test.SSI_write(0x4C, 0xCBB8);
	d2s_test.SSI_write(0x50, 0x6542);
	d2s_test.SSI_write(0x54, 0x405);
	d2s_test.SSI_write(0x58, 0x607);
	d2s_test.SSI_write(0x5C, 0x809);
	d2s_test.SSI_write(0x60, 0xA0B);
	d2s_test.SSI_write(0x64, 0xC0D);
	d2s_test.SSI_write(0x68, 0xE0F);
	d2s_test.SSI_write(0x6C, 0x1112);
	d2s_test.SSI_write(0x70, 0x1314);
	d2s_test.SSI_write(0x74, 0x1516);
	d2s_test.SSI_write(0x78, 0x1718);
	d2s_test.SSI_write(0x7C, 0x191A);
	d2s_test.SSI_write(0x80, 0x1B1C);
	d2s_test.SSI_write(0x84, 0x1D20);
	d2s_test.SSI_write(0x88, 0x2020);
	d2s_test.SSI_write(0x8C, 0x2020);
	d2s_test.SSI_write(0x90, 0x2020);
	d2s_test.SSI_write(0x94, 0x80);
	d2s_test.SSI_write(0x98, 0x0);
	d2s_test.SSI_write(0x9C, 0x0);
	d2s_test.SSI_write(0xA0, 0x0);
	d2s_test.SSI_write(0xA4, 0x550);
	d2s_test.SSI_write(0x350, 0x18A0);
	d2s_test.SSI_write(0x354, 0x4AA8);
	d2s_test.SSI_write(0x358, 0x81);
	d2s_test.SSI_write(0x35C, 0x2A00); //2B00->2A00@2017-08-14 for V210,800 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x360, 0x0);
	d2s_test.SSI_write(0x364, 0x18A0);
	d2s_test.SSI_write(0x368, 0x4AA8);
	d2s_test.SSI_write(0x36C, 0x81);
	d2s_test.SSI_write(0x370, 0x2A00); //2B00->2A00@2017-08-14 for V210,800 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x374, 0x0);
	d2s_test.SSI_write(0x378, 0x0);
	d2s_test.SSI_write(0x37C, 0x0);
	d2s_test.SSI_write(0x380, 0x0);
	d2s_test.SSI_write(0x384, 0x0);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xC8, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s_test.SSI_write(0x4, 0x100B);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x8000);
	d2s_test.SSI_write(0x10, 0x6115);
	d2s_test.SSI_write(0x14, 0x5555);
	d2s_test.SSI_write(0x18, 0x4000);
	d2s_test.SSI_write(0x20, 0x12);
	d2s_test.SSI_write(0x24, 0x0);
	d2s_test.SSI_write(0x28, 0x100);
	d2s_test.SSI_write(0x2C, 0x0); //wl_pll_reg_523  1800->0,to reduce Spur Power @2017-06-23
	d2s_test.SSI_write(0x30, 0xE0);
	d2s_test.SSI_write(0x34, 0x9708);
	d2s_test.SSI_write(0x38, 0xD004);
	d2s_test.SSI_write(0x3C, 0x90A0);
	d2s_test.SSI_write(0x40, 0x0);
	d2s_test.SSI_write(0x44, 0x1780);
	d2s_test.SSI_write(0x48, 0x0);
	d2s_test.SSI_write(0x4C, 0x0);
	d2s_test.SSI_write(0x50, 0x0);
	d2s_test.SSI_write(0x54, 0x0);
	d2s_test.SSI_write(0x58, 0xC080);
	d2s_test.SSI_write(0x5C, 0x66AE);
	d2s_test.SSI_write(0x60, 0x1E00);
	d2s_test.SSI_write(0x64, 0x8004);
	d2s_test.SSI_write(0x68, 0x7742);
	d2s_test.SSI_write(0x6C, 0x84F);
	d2s_test.SSI_write(0x70, 0x9600);
	d2s_test.SSI_write(0x74, 0xF002);
	d2s_test.SSI_write(0x78, 0x0);
	d2s_test.SSI_write(0x7C, 0x0);
	d2s_test.SSI_write(0x80, 0x9AC8);
	d2s_test.SSI_write(0x84, 0x80);
	d2s_test.SSI_write(0x88, 0x20);
	d2s_test.SSI_write(0x8C, 0x0);
	d2s_test.SSI_write(0xC0, 0x0);
	d2s_test.SSI_write(0xC4, 0x404);
	d2s_test.SSI_write(0xC8, 0xC818);
	d2s_test.SSI_write(0xCC, 0x0);
	d2s_test.SSI_write(0xD0, 0x0);
	d2s_test.SSI_write(0xD4, 0x0);
	d2s_test.SSI_write(0xD8, 0x0);
	d2s_test.SSI_write(0xDC, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x350, 0x18A0);
	d2s_test.SSI_write(0x354, 0x4AA8);
	d2s_test.SSI_write(0x358, 0x81);
	d2s_test.SSI_write(0x35C, 0x2A00); //2B00->2A00@2017-08-14 for V210,B00 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x360, 0x0);
	d2s_test.SSI_write(0x364, 0x18A0);
	d2s_test.SSI_write(0x368, 0x4AA8);
	d2s_test.SSI_write(0x36C, 0x81);
	d2s_test.SSI_write(0x370, 0x2A00); //2B00->2A00@2017-08-14 for V210,B00 to 2B00 @2017-06-29
	d2s_test.SSI_write(0x374, 0x0);
	d2s_test.SSI_write(0x378, 0x0);
	d2s_test.SSI_write(0x37C, 0x0);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x8, 0x3233);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x378, 0x100);
	d2s_test.SSI_write(0x37C, 0x4);
	d2s_test.SSI_write(0x380, 0x0);
	d2s_test.SSI_write(0x384, 0x0);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0xC, 0x3233);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x380, 0x100);
	d2s_test.SSI_write(0x384, 0x4);
	d2s::d2s_LABEL_END();
}

void RC_Cal_C0_Module(CSiteLong *pReadValue) {

	//char *cReadFlag = "\0";
	char cReadFlag[32] = { "\0" };

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170526.xlsx
	//Sheet: ABB Cal, from line 70 ADC reset
	//File time: 5/25/2017 9:58:32 AM
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);    //ProductionMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x240, 0x111);      //soc
	d2s_test.SSI_write(0x244, 0x1);    //soc
	d2s_test.SSI_write(0x244, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x378, 0x0);    //rf
	d2s_test.SSI_write(0x37C, 0x0);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0xC, 0x2);      //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);    //rf
	d2s_test.SSI_write(0x388, 0x0);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x8, 0x133);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x378, 0x140);      //rf
	d2s_test.SSI_write(0x37C, 0x5);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x24C, 0x111);      //soc
	d2s_test.SSI_write(0x250, 0x1);    //soc
	d2s_test.SSI_write(0x250, 0x101);      //soc

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170526.xlsx
	//Sheet: RC
	//File time: 5/25/2017 9:58:32 AM

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x240, 0x111);
	d2s_test.SSI_write(0x244, 0x1);
	d2s_test.SSI_write(0x244, 0x101);
	d2s_test.SSI_write(0x24C, 0x111);
	d2s_test.SSI_write(0x250, 0x1);
	d2s_test.SSI_write(0x250, 0x101);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);
	d2s_test.SSI_write(0xC, 0x2F);
	d2s_test.SSI_write(0x10, 0x2F);
	d2s_test.SSI_write(0x34, 0x5111);    //LPF set to 24MHz

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x14, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x33C, 0x1B3);        //CMU reserve

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);
	d2s_test.SSI_write(0x24, 0x1);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x34, 0x5111);
	d2s_test.SSI_write(0x3C0, 0x0);
	d2s_test.SSI_write(0x24, 0x120);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);           //DAC Gain

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);           //LPF Gain

	d2s_test.SSI_write(0x7C, 0x7500);
	d2s_test.SSI_write(0x84, 0x1);
	d2s_test.SSI_write(0x70, 0x1003);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);     //TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x1FC, 0x4);    //CALI_TEST_CTRL_NEW

	for (int i = 0; i < 64; i++) {

		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);

		d2s_test.SSI_write(0x44, i + i * 64);    //RC Code
		d2s_test.SSI_write(0x40, i + i * 64);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x98, false);
		d2s_test.SSI_write(0x80, 0x1);         //CW//s amplitude

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x128, 0x30);   //tone_mode
		d2s_test.SSI_write(0x128, 0x30);
		d2s_test.SSI_write(0x128, 0x31);   //tone_en

		d2s_test.wait(0.00001);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//read frequency analysis data for 1M

		d2s_test.SSI_write(0x124, 0x3);
		d2s_test.SSI_write(0x124, 0x7);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.00003);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x17);

		d2s_test.wait(0.00004);

		//Call SSI_read_Module(0x124, , 12);
		//Call SSI_read_Module(0x126, , 12);

		sprintf(cReadFlag, "readdata_reg124_1Mi%d", i);
		d2s_test.SSI_read(0x124, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg126_1Mi%d", i);
		d2s_test.SSI_read(0x126, cReadFlag, 9);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);       //PHY TEST_START set to low

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x7);      //disable spectrum analysis

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		d2s_test.SSI_write(0x128, 0x0);  //tone_en set to 0

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x98, false);
		d2s_test.SSI_write(0x80, 0x1);    //CW Tone//s amplitude

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x128, 0x50);   //tone_Mode
		d2s_test.SSI_write(0x128, 0x50);
		d2s_test.SSI_write(0x128, 0x51);    //tone_en

		d2s_test.wait(0.00001);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//read frequency analysis data for 24M

		d2s_test.SSI_write(0x124, 0x3);
		d2s_test.SSI_write(0x124, 0x7);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.00003);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x17);

		d2s_test.wait(0.00004);

		//Call SSI_read_Module(0x124, , 12);
		//Call SSI_read_Module(0x126, , 12);
		sprintf(cReadFlag, "readdata_reg124_24Mi%d", i);
		d2s_test.SSI_read(0x124, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg126_24Mi%d", i);
		d2s_test.SSI_read(0x126, cReadFlag, 9);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x7);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		d2s_test.SSI_write(0x128, 0x0);

	}

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x80);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0x7C, 0x0);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x70, 0x7000);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);
	d2s::d2s_LABEL_END();

	long long nCapData[256] = { 0 };
	int nsize = sizeof(nCapData) / sizeof(long long);



	if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (int j = 0; j < 64; j++) {
               sprintf(cReadFlag, "readdata_reg124_1Mi%d", j);   //V200
               nCapData[j*4]  = d2s_test.getReadValue(cReadFlag).at(site_id);

               sprintf(cReadFlag, "readdata_reg126_1Mi%d", j);
               nCapData[j*4+1]  = d2s_test.getReadValue(cReadFlag).at(site_id);

               sprintf(cReadFlag, "readdata_reg124_24Mi%d", j);
               nCapData[j*4+2]  = d2s_test.getReadValue(cReadFlag).at(site_id);

               sprintf(cReadFlag, "readdata_reg126_24Mi%d", j);
               nCapData[j*4+3]  = d2s_test.getReadValue(cReadFlag).at(site_id);

		}
		pReadValue->InitDataArray(site_id, nsize);
		pReadValue->CopyElement(site_id,nCapData,nsize);

	FOREACH_ACTIVESITE_END
	} else {

		unsigned long data[4096];

		auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

		for (auto siteData : CAP_Data)
		{
			for (auto pinData : siteData.second)
			{
				int i=0;
				for (auto capData : pinData.second)
				{
					data[i] = capData.iECResult;
					i++;

				}
			}

			for(int n = 0;n<4096;n+=16)
			{
				nCapData[n/16] = ConvertCapData(data+n,16);
			}

			pReadValue->InitDataArray(siteData.first, nsize);
			pReadValue->CopyElement(siteData.first,nCapData,nsize);
		}

	}

//	pReadValue->InitDataArray(site_id, nsize);
//	pReadValue->CopyElement(site_id,nCapData,nsize);






//	FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//	if (!d2s::isProductionMode()) {
//
//		for (int j = 0; j < 64; j++) {
//               sprintf(cReadFlag, "readdata_reg124_1Mi%d", j);   //V200
//               nCapData[j*4]  = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//               cout << "nCapData[0]:" <<nCapData[j*4] <<endl;
//
//
//               sprintf(cReadFlag, "readdata_reg126_1Mi%d", j);
//               nCapData[j*4+1]  = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//               cout << "nCapData[1]:" <<nCapData[j*4+1] <<endl;
//
//               sprintf(cReadFlag, "readdata_reg124_24Mi%d", j);
//               nCapData[j*4+2]  = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//               cout << "nCapData[2]:" <<nCapData[j*4+2] <<endl;
//
//               sprintf(cReadFlag, "readdata_reg126_24Mi%d", j);
//               nCapData[j*4+3]  = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//               cout << "nCapData[3]:" <<nCapData[j*4+3] <<endl;
//
//
//		}
//	} else {
//
//		unsigned long data[4096];
//		DIO_Capture(site_id,"DBB_GPIO7", data);   //V200
//
//		for(int n = 0;n<4096;n+=16)
//		{
//			nCapData[n/16] = ConvertCapData(data+n,16);
//		}
//	}
//
//	pReadValue->InitDataArray(site_id, nsize);
//	pReadValue->CopyElement(site_id,nCapData,nsize);
//
//	FOREACH_ACTIVESITE_END

}

void RC_Cal_C1_Module(CSiteLong *pReadValue) {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170526.xlsx
	//Sheet: ABB Cal, from line 70 ADC reset
	//File time: 5/25/2017 9:58:32 AM
	//char *cReadFlag;
	char cReadFlag[32] = { "\0" };

	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);    //ProductionMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x258, 0x111);      //soc
	d2s_test.SSI_write(0x25C, 0x1);    //soc
	d2s_test.SSI_write(0x25C, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x380, 0x0);    //rf
	d2s_test.SSI_write(0x384, 0x0);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x10, 0x2);     //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);    //rf
	d2s_test.SSI_write(0x388, 0x0);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0xC, 0x133);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x380, 0x140);      //rf
	d2s_test.SSI_write(0x384, 0x5);    //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x264, 0x111);      //soc
	d2s_test.SSI_write(0x268, 0x1);    //soc
	d2s_test.SSI_write(0x268, 0x101);      //soc

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170526.xlsx
	//Sheet: RC
	//File time: 5/25/2017 9:58:32 AM

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x258, 0x111);
	d2s_test.SSI_write(0x25C, 0x1);
	d2s_test.SSI_write(0x25C, 0x101);
	d2s_test.SSI_write(0x264, 0x111);
	d2s_test.SSI_write(0x268, 0x1);
	d2s_test.SSI_write(0x268, 0x101);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);
	d2s_test.SSI_write(0xC, 0x2F);
	d2s_test.SSI_write(0x10, 0x2F);
	d2s_test.SSI_write(0x34, 0x5111);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x14, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x33C, 0x1B3);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);
	d2s_test.SSI_write(0x24, 0x2);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x34, 0x7111);
	d2s_test.SSI_write(0x3C0, 0x0);
	d2s_test.SSI_write(0x28, 0x120);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);

	d2s_test.SSI_write(0x80, 0x7500);
	d2s_test.SSI_write(0x84, 0x100);
	d2s_test.SSI_write(0x70, 0x1060);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x1FC, 0x4);

	for (int i = 0; i < 64; i++) {

		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);

		d2s_test.SSI_write(0x4C, i + i * 64);
		d2s_test.SSI_write(0x48, i + i * 64);   //RC code

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x98, false);
		d2s_test.SSI_write(0x80, 0x1);      //tone amplitude

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x128, 0x30);
		d2s_test.SSI_write(0x128, 0x30);   //tone_mode, 1MHz
		d2s_test.SSI_write(0x128, 0x31);   //tone_en

		d2s_test.wait(0.00001);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//read frequency analysis data

		d2s_test.SSI_write(0x124, 0x3);
		d2s_test.SSI_write(0x124, 0x7);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.00003);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x17);

		d2s_test.wait(0.00004);

		//Call SSI_read_Module(0x124, , 12);
		//Call SSI_read_Module(0x126, , 12);
		sprintf(cReadFlag, "readdata_reg124_1Mi%d", i);
		d2s_test.SSI_read(0x124, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg126_1Mi%d", i);
		d2s_test.SSI_read(0x126, cReadFlag, 9);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x7);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		d2s_test.SSI_write(0x128, 0x0);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x98, false);
		d2s_test.SSI_write(0x80, 0x1);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x128, 0x50);
		d2s_test.SSI_write(0x128, 0x50);  //tone_mode, 24MHz
		d2s_test.SSI_write(0x128, 0x51);  //tone_en

		d2s_test.wait(0.00001);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//read frequency analysis data

		d2s_test.SSI_write(0x124, 0x3);
		d2s_test.SSI_write(0x124, 0x7);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.00003);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x17);

		d2s_test.wait(0.00004);

		//Call SSI_read_Module(0x124, , 12);
		//Call SSI_read_Module(0x126, , 12);
		sprintf(cReadFlag, "readdata_reg124_24Mi%d", i);
		d2s_test.SSI_read(0x124, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg126_24Mi%d", i);
		d2s_test.SSI_read(0x126, cReadFlag, 9);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x124, 0x7);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		d2s_test.SSI_write(0x128, 0x0);

	}

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x80);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0x80, 0x0);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x70, 0x7000);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);
	d2s::d2s_LABEL_END();

	long long nCapData[256] = { 0 };
	int nsize = sizeof(nCapData) / sizeof(long long);



	if (!d2s::isProductionMode()) {
			FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
			for (int j = 0; j < 64; j++) {
	               sprintf(cReadFlag, "readdata_reg124_1Mi%d", j);   //V200
	               nCapData[j*4]  = d2s_test.getReadValue(cReadFlag).at(site_id);

	               sprintf(cReadFlag, "readdata_reg126_1Mi%d", j);
	               nCapData[j*4+1]  = d2s_test.getReadValue(cReadFlag).at(site_id);

	               sprintf(cReadFlag, "readdata_reg124_24Mi%d", j);
	               nCapData[j*4+2]  = d2s_test.getReadValue(cReadFlag).at(site_id);

	               sprintf(cReadFlag, "readdata_reg126_24Mi%d", j);
	               nCapData[j*4+3]  = d2s_test.getReadValue(cReadFlag).at(site_id);

			}
			pReadValue->InitDataArray(site_id, nsize);
			pReadValue->CopyElement(site_id,nCapData,nsize);

			for(int i=0;i<256;i++)
			{
				cout << nCapData[i] << "\t";

			}
			cout << endl;

		FOREACH_ACTIVESITE_END
		} else {

			unsigned long data[4096];

			auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

			for (auto siteData : CAP_Data)
			{

				for (auto pinData : siteData.second)
				{
					int i=0;
					for (auto capData : pinData.second)
					{

						data[i] = capData.iECResult;
						cout <<  data[i] ;
						i++;

					}


					cout << endl;

				}



				for(int n = 0;n<4096;n+=16)
				{
					nCapData[n/16] = ConvertCapData(data+n,16);
					cout << nCapData[n/16]<< "\t";
				}
				cout << endl;
				pReadValue->InitDataArray(siteData.first, nsize);
				pReadValue->CopyElement(siteData.first,nCapData,nsize);
			}
		}


}

void RC_CAL_Final_Module() {

	//write in defalut RC code for C0 and C1, RX and TX, copy from RC sheet.
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x44, 0x5D7);
	d2s_test.SSI_write(0x40, 0x596);
	d2s_test.SSI_write(0x4C, 0x5D7);
	d2s_test.SSI_write(0x48, 0x596);

	//copy from the RC sheet from line 54, C0 and C1 the same. @2017-5-27
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);

	d2s_test.SSI_write(0x50, 0x416);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x40, false);
	d2s_test.SSI_write(0x33C, 0x19B);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x14, 0x2);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x3C0, 0x55);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x2);
	d2s_test.SSI_write(0x10, 0x2);
	d2s::d2s_LABEL_END();
}

void VI_DET_C0_Module(CSiteLong *pReadValue) {

	//File:  1151V200_VI_DET.xlsx
	//Sheet: VI_DET_C0
	//File time: 2017/5/26 17:52:25

	long i;
	char cReadFlag[32] = { "\0" };
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x240, 0x111);
	d2s_test.SSI_write(0x244, 0x1);
	d2s_test.SSI_write(0x244, 0x101);
	d2s_test.SSI_write(0x24C, 0x111);
	d2s_test.SSI_write(0x250, 0x1);
	d2s_test.SSI_write(0x250, 0x101);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);
	d2s_test.SSI_write(0xC, 0x2F);
	d2s_test.SSI_write(0x10, 0x2F);
	d2s_test.SSI_write(0x20, 0x37);    //open LOgen

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);
	d2s_test.SSI_write(0x24, 0x1);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x34, 0x5111);   //local_c1_sel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);     //trx fifo

//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x90, false);
//    d2s_test.SSI_write(0x24, 0x180);    //VGA gain to -1dB, @2017-06-01 Vcal//s VGA gain set to -1dB(0dB,0x180);. @2018-11-30 VGA set in vbt

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	//setup TX PWR calibration chain
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0x90, 0x1E);
	d2s_test.SSI_write(0x94, 0x1E);
	d2s_test.SSI_write(0x98, 0x1E);
	d2s_test.SSI_write(0xB0, 0x1F);
	d2s_test.SSI_write(0xB4, 0x1F);
	d2s_test.SSI_write(0x7C, 0x3500);
	d2s_test.SSI_write(0x84, 0x1D);
	d2s_test.SSI_write(0x70, 0x7008);
	d2s_test.SSI_write(0x20, 0x537);
	d2s_test.SSI_write(0x4, 0x1);

	////////// Set Cal Frequency //////////////////////////////////////////////////////////////////

	d2s_test.SSI_write(0x34, 0x5121);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xC8, false);
	d2s_test.SSI_write(0x10, 0x5191);
	d2s_test.SSI_write(0x14, 0x1111);
	d2s_test.SSI_write(0x4, 0x1000);
	d2s_test.wait(0.00005);
	d2s_test.SSI_write(0x4, 0x1003);
	d2s_test.wait(0.0001);
	d2s_test.SSI_write(0x4, 0x100B);   //wait 150us
	d2s_test.wait(0.00015);
	d2s_test.SSI_write(0x4, 0xB);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x537);    //switch to V det mode
	d2s_test.SSI_write(0x70, 0x7008);   //setup TX2G PA IDET CTRL

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);     //cw amplitude

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x10);   //tone mode
	d2s_test.SSI_write(0x128, 0x10);
	d2s_test.SSI_write(0x128, 0x11);   //tone en

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x168, 0x0);
	d2s_test.SSI_write(0x16C, 0x7F); //modify from 512 to 128 @20171121 For R30

	for (i = 0; i < 64; i++) {

		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x94, i);     //loop 64

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.000005); //modify from 50 to 5 @20171121 For R30

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x164, 0x1);

		d2s_test.wait(0.00005);

		//Call SSI_read_Module(0x0, , 12);  //(bit0:bit21);
		//Call SSI_read_Module(0x2, , 12);
		sprintf(cReadFlag, "readdata_reg0_V%d", i);
		d2s_test.SSI_read(0x0, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg2_V%d", i);
		d2s_test.SSI_read(0x2, cReadFlag, 9);

		d2s_test.SSI_write(0x164, 0x0);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);     //loop end

	}

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x637);         //switch to IDET
	d2s_test.SSI_write(0x70, 0x7018);        //TX2G PA IDET CTL
	d2s_test.SSI_write(0x94, 0x20);     //RECOVER UPC code to 32  @20170918

	d2s_test.SSI_write(0x24, 0x180); //VGA gain to 0dB   @2017-06-01 Ical//s VGA gain set to 0dB.

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);    //tone amplitude

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x10);
	d2s_test.SSI_write(0x128, 0x10);   //tone mask
	d2s_test.SSI_write(0x128, 0x11);   //tone

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x168, 0x0);
	d2s_test.SSI_write(0x16C, 0x7F); //modify from 512 to 128 @20171121 For R30

	for (i = 0; i < 102; i++) {           //@2017-07-29 change from 95 to 101

		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x94, false);
		d2s_test.SSI_write(0x288, i);      //DTC CODE

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.000005); //modify from 50 to 5 @20171121 For R30

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x164, 0x1);

		d2s_test.wait(0.00005);

		//Call SSI_read_Module(0x0, , 12);  //(bit0:bit21);
		//Call SSI_read_Module(0x2, , 12);  //(bit0:bit21);
		sprintf(cReadFlag, "readdata_reg0_I%d", i);
		d2s_test.SSI_read(0x0, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg2_I%d", i);
		d2s_test.SSI_read(0x2, cReadFlag, 9);

		d2s_test.SSI_write(0x164, 0x0);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);

	}

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x288, 0x37); //DTC CODE //RECOVER DTC code to 55 @20170918

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);
	d2s_test.SSI_write(0x1D0, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x80);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0x90, 0x1B);
	d2s_test.SSI_write(0x94, 0x1B);
	d2s_test.SSI_write(0x98, 0x1B);
	d2s_test.SSI_write(0xB0, 0x1F);
	d2s_test.SSI_write(0xB4, 0x1F);
	d2s_test.SSI_write(0x7C, 0x0);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x70, 0x7000);
	d2s_test.SSI_write(0x20, 0x37);
	d2s_test.SSI_write(0x4, 0x0);
	d2s_test.SSI_write(0x20, 0x37);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x2);
	d2s_test.SSI_write(0x10, 0x2);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s::d2s_LABEL_END();

	long long nCapData[332] = { 0 };
	int nsize = sizeof(nCapData) / sizeof(long long);


//	FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//	if(!d2s::isProductionMode()) {
//            for (int j = 0; j < 64; j++) {
//               sprintf(cReadFlag, "readdata_reg0_V%d", j);
//               nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//               sprintf(cReadFlag, "readdata_reg2_V%d", j);
//               nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//            for (int k = 0; k < 102; k++) {
//               sprintf(cReadFlag, "readdata_reg0_I%d", k);
//               nCapData[k*2+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
//               sprintf(cReadFlag, "readdata_reg2_I%d", k);
//               nCapData[k*2+1+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
//            }
//	} else {
//		unsigned long data[5312];
//
//		DIO_Capture(site_id,"DBB_GPIO7", data);
//
//		for(int n = 0;n<5312;n+=16)
//		{
//			nCapData[n/16] = ConvertCapData(data+n,16);
//		}
//	}
//
//	pReadValue->InitDataArray(site_id, nsize);
//	pReadValue->CopyElement(site_id, nCapData,nsize);
//
//	FOREACH_ACTIVESITE_END


	if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (int j = 0; j < 64; j++) {
			   sprintf(cReadFlag, "readdata_reg0_V%d", j);
			   nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
			   sprintf(cReadFlag, "readdata_reg2_V%d", j);
			   nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);

			   cout << nCapData[j*2]<<  "\t" << nCapData[j*2+1] << "\t";

			}
			cout << endl;



			for (int k = 0; k < 102; k++) {
			   sprintf(cReadFlag, "readdata_reg0_I%d", k);
			   nCapData[k*2+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
			   sprintf(cReadFlag, "readdata_reg2_I%d", k);
			   nCapData[k*2+1+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
			}
			pReadValue->InitDataArray(site_id, nsize);
			pReadValue->CopyElement(site_id,nCapData,nsize);

		FOREACH_ACTIVESITE_END
		} else {

			unsigned long data[5312];

			auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

			for (auto siteData : CAP_Data)
			{
				for (auto pinData : siteData.second)
				{
					int i=0;
					for (auto capData : pinData.second)
					{
						data[i] = capData.iECResult;
						i++;

					}
				}
				for(int n = 0;n<5312;n+=16)
				{
					nCapData[n/16] = ConvertCapData(data+n,16);
					cout << nCapData[n/16]<< "\t";
				}

				cout << endl;

				pReadValue->InitDataArray(siteData.first, nsize);
				pReadValue->CopyElement(siteData.first,nCapData,nsize);
			}

		}




}

void VI_DET_C1_Module(CSiteLong *pReadValue) {

	//File:  1151V200_VI_DET.xlsx
	//Sheet: VI_DET_C1
	//File time: 2017/5/26 17:52:25

	long i;
	char cReadFlag[32] = { "\0" };
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x258, 0x111);
	d2s_test.SSI_write(0x25C, 0x1);
	d2s_test.SSI_write(0x25C, 0x101);
	d2s_test.SSI_write(0x264, 0x111);
	d2s_test.SSI_write(0x268, 0x1);
	d2s_test.SSI_write(0x268, 0x101);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);
	d2s_test.SSI_write(0xC, 0x2F);
	d2s_test.SSI_write(0x10, 0x2F);
	d2s_test.SSI_write(0x20, 0x37);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);
	d2s_test.SSI_write(0x24, 0x2);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x34, 0x7111);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);

//    d2s_test.SSI_write(0x200, 0x2000, false);
//    d2s_test.SSI_write(0x202, 0x90, false);
//    d2s_test.SSI_write(0x28, 0x180);     //@2018-11-30 VGA set in vbt

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0xA0, 0x1E);
	d2s_test.SSI_write(0xA4, 0x1E);
	d2s_test.SSI_write(0xA8, 0x1E);
	d2s_test.SSI_write(0xB8, 0x1F);
	d2s_test.SSI_write(0xBC, 0x1F);
	d2s_test.SSI_write(0x80, 0x3500);
	d2s_test.SSI_write(0x84, 0x1D00);
	d2s_test.SSI_write(0x70, 0x7100);
	d2s_test.SSI_write(0x20, 0x5037);
	d2s_test.SSI_write(0x4, 0x2);

	////////// Set Cal Frequency //////////////////////////////////////////////////////////////////

	d2s_test.SSI_write(0x34, 0x7121);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xC8, false);
	d2s_test.SSI_write(0x10, 0x5191);
	d2s_test.SSI_write(0x14, 0x1111);
	d2s_test.SSI_write(0x4, 0x1000);
	d2s_test.wait(0.00005);
	d2s_test.SSI_write(0x4, 0x1003);
	d2s_test.wait(0.0001);
	d2s_test.SSI_write(0x4, 0x100B);   //wait 150us
	d2s_test.wait(0.00015);
	d2s_test.SSI_write(0x4, 0xB);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x5037);
	d2s_test.SSI_write(0x70, 0x7100);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);    //tone amplitude

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x10);
	d2s_test.SSI_write(0x128, 0x10);   //tone mask
	d2s_test.SSI_write(0x128, 0x11);   //tone en

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x168, 0x0);
	d2s_test.SSI_write(0x16C, 0x7F); //modify from 512 to 128 @20171121 For R30

	for (i = 0; i < 64; i++) {

		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0xA4, i);     //loop 64

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.000005); //modify from 50 to 5 @20171121 For R30

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x164, 0x1);

		d2s_test.wait(0.00005);

		//Call SSI_read_Module(0x0, , 12);  //(bit0:bit21);
		//Call SSI_read_Module(0x2, , 12);
		sprintf(cReadFlag, "readdata_reg0_V%d", i);
		d2s_test.SSI_read(0x0, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg2_V%d", i);
		d2s_test.SSI_read(0x2, cReadFlag, 9);

		d2s_test.SSI_write(0x164, 0x0);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);     //loop end

	}

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x6037);        //switch to IDET
	d2s_test.SSI_write(0x70, 0x7300);        //TX2G PA IDET CTL
	d2s_test.SSI_write(0xA4, 0x20);     // //RECOVER UPC code to 32  @20170925

	d2s_test.SSI_write(0x28, 0x180); //VGA gain to 0dB   @2017-06-01 Ical//s VGA gain set to 0dB.

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);    //tone amplitude

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x10);
	d2s_test.SSI_write(0x128, 0x10);   //tone mask
	d2s_test.SSI_write(0x128, 0x11);    //tone en

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x168, 0x0);
	d2s_test.SSI_write(0x16C, 0x7F); //modify from 512 to 128 @20171121 For R30

	for (i = 0; i < 102; i++) {           //@2017-07-29 change from 95 to 101

		d2s_test.SSI_write(0x200, 0x2000, false);
		d2s_test.SSI_write(0x202, 0x94, false);
		d2s_test.SSI_write(0x294, i);    //DTC CODE

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x1);

		d2s_test.wait(0.000005); //modify from 50 to 5 @20171121 For R30

		d2s_test.SSI_write(0x200, 0x2003, false);
		d2s_test.SSI_write(0x202, 0x90, false);
		d2s_test.SSI_write(0x164, 0x1);

		d2s_test.wait(0.00005);

		//Call SSI_read_Module(0x0, , 12);  //(bit0:bit21);
		//Call SSI_read_Module(0x2, , 12);  //(bit0:bit21);
		sprintf(cReadFlag, "readdata_reg0_I%d", i);
		d2s_test.SSI_read(0x0, cReadFlag, 9);

		sprintf(cReadFlag, "readdata_reg2_I%d", i);
		d2s_test.SSI_read(0x2, cReadFlag, 9);

		d2s_test.SSI_write(0x164, 0x0);

		d2s_test.SSI_write(0x200, 0x2001, false);
		d2s_test.SSI_write(0x202, 0x4, false);
		d2s_test.SSI_write(0x6C, 0x0);

	}

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x294, 0x37); //DTC CODE //RECOVER DTC code to 55 @20170925

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);
	d2s_test.SSI_write(0x1D0, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x80);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);
	d2s_test.SSI_write(0xA0, 0x1B);
	d2s_test.SSI_write(0xA4, 0x1B);
	d2s_test.SSI_write(0xA8, 0x1B);
	d2s_test.SSI_write(0xB8, 0x1F);
	d2s_test.SSI_write(0xBC, 0x1F);
	d2s_test.SSI_write(0x80, 0x0);
	d2s_test.SSI_write(0x84, 0x0);
	d2s_test.SSI_write(0x70, 0x7000);
	d2s_test.SSI_write(0x20, 0x37);
	d2s_test.SSI_write(0x4, 0x0);
	d2s_test.SSI_write(0x20, 0x37);
	d2s_test.SSI_write(0x8, 0x0);
	d2s_test.SSI_write(0xC, 0x2);
	d2s_test.SSI_write(0x10, 0x2);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);
	d2s::d2s_LABEL_END();

	long long nCapData[332] = { 0 };
	int nsize = sizeof(nCapData) / sizeof(long long);



//	FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//if	(!d2s::isProductionMode()) {
//            for (int j = 0; j < 64; j++) {
//                sprintf(cReadFlag, "readdata_reg0_V%d", j);
//                nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//                sprintf(cReadFlag, "readdata_reg2_V%d", j);
//                nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//             }
//             for (int k = 0; k < 102; k++) {
//                sprintf(cReadFlag, "readdata_reg0_I%d", k);
//                nCapData[k*2+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
//                sprintf(cReadFlag, "readdata_reg2_I%d", k);
//                nCapData[k*2+1+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
//             }
//	} else {
//		unsigned long data[5312];
//
//		DIO_Capture(site_id,"DBB_GPIO7", data);
//
//		for(int n = 0;n<5312;n+=16)
//		{
//			nCapData[n/16] = ConvertCapData(data+n,16);
//		}
//	}
//
//	//pSiteData->CopyElement(site_id,nCapData,256);
//	pReadValue->InitDataArray(site_id, nsize);
//	pReadValue->CopyElement(site_id, nCapData,nsize);
//
//	FOREACH_ACTIVESITE_END


	if (!d2s::isProductionMode()) {
			FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (int j = 0; j < 64; j++) {
			   sprintf(cReadFlag, "readdata_reg0_V%d", j);
			   nCapData[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
			   sprintf(cReadFlag, "readdata_reg2_V%d", j);
			   nCapData[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
			}
			for (int k = 0; k < 102; k++) {
			   sprintf(cReadFlag, "readdata_reg0_I%d", k);
			   nCapData[k*2+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
			   sprintf(cReadFlag, "readdata_reg2_I%d", k);
			   nCapData[k*2+1+128] = d2s_test.getReadValue(cReadFlag).at(site_id);
			}
			pReadValue->InitDataArray(site_id, nsize);
			pReadValue->CopyElement(site_id,nCapData,nsize);

		FOREACH_ACTIVESITE_END
		} else {

			unsigned long data[5312];

			auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

			for (auto siteData : CAP_Data)
			{
				for (auto pinData : siteData.second)
				{
					int i=0;
					for (auto capData : pinData.second)
					{
						data[i] = capData.iECResult;
						i++;

					}
				}
				for(int n = 0;n<5312;n+=16)
				{
					nCapData[n/16] = ConvertCapData(data+n,16);
				}

				pReadValue->InitDataArray(siteData.first, nsize);
				pReadValue->CopyElement(siteData.first,nCapData,nsize);
			}

		}


}

void PDBUF_C0_C1_Module(CSiteLong *pReadValue0, CSiteLong *pReadValue1) {

	//File:  PD_BUF.xlsx
	//Sheet: 5G_PDBUF_DET_C0
	//File time: 5/31/2017 1:57:34 PM
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    close normal service

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x240, 0x111);      //soc    ADC setting
	d2s_test.SSI_write(0x244, 0x1);    //soc
	d2s_test.SSI_write(0x244, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);      //rf     register control
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf
	d2s_test.SSI_write(0x20, 0x437);       //rf     Open LOGEN

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);     //soc    Select channel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);     //phy    Open phy
	d2s_test.SSI_write(0x24, 0x1);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);        //phy   set TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x180);       //rf   RX gain set
	d2s_test.SSI_write(0x7C, 0x3500);      //rf

	d2s_test.SSI_write(0x70, 0x1008);      //rf

	/*配置*/
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x68, 0x0);
	d2s_test.SSI_write(0x5C, 0xa00);
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x18, 0x82);
	d2s_test.SSI_write(0x94, 0x82);

	/***********************C0 Capture********************************/
	long i;
	long j;
	char cReadFlag[32] = { "\0" };
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG

	d2s_test.wait(0.001);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

	d2s_test.wait(0.00005);

	d2s_test.SSI_write(0x200, 0x2003, false);

	for (i = 0; i < 4; i++) {         //0xc0 to 0xfc, step 4
		d2s_test.SSI_write(0x202, 0xC0 + i * 4, false);

		for (j = 0; j < 128; j++) {       //0 to 0x3ff
			//Call SSI_read_Module(0x0 + 8 * j, True, 8);
			//Call SSI_read_Module(0x2 + 8 * j, True, 8);
			long k = i * 128 + j;
			sprintf(cReadFlag, "readdata0_i%d", k);
			d2s_test.SSI_read(0x0 + 8 * j, cReadFlag, 7);

			sprintf(cReadFlag, "readdata0_q%d", k);
			d2s_test.SSI_read(0x2 + 8 * j, cReadFlag, 7);
		}
	}

	/*********************Restore*****************************/
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy    restroe TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x80);        //rf    restore RX gain
	d2s_test.SSI_write(0x7C, 0x0);         //rf    restore   TX PWR cal path

	d2s_test.SSI_write(0x70, 0x7000);      //rf
	d2s_test.SSI_write(0x68, 0x0);         //rf
	d2s_test.SSI_write(0x5C, 0x0);         //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x18, 0x80);        //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x37);        //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf    close LOGEN
	d2s_test.SSI_write(0xC, 0x2);      //rf    default control
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    restore normal service

	/***********************C1 set**************************/
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    close normal service

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x258, 0x111);      //soc    ADC setting
	d2s_test.SSI_write(0x25C, 0x1);          //soc
	d2s_test.SSI_write(0x25C, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);      //rf     register control
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf
	d2s_test.SSI_write(0x20, 0x4037);      //rf     Open LOGEN

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);    //soc    Select channel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);     //phy    Open phy
	d2s_test.SSI_write(0x24, 0x2);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);        //phy   set TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x180);       //rf   RX gain set
	d2s_test.SSI_write(0x80, 0x3500);      //rf

	d2s_test.SSI_write(0x70, 0x1100);      //rf

	/*配置*/
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x68, 0x0);
	d2s_test.SSI_write(0x5C, 0xa00);
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x18, 0x82);
	d2s_test.SSI_write(0x94, 0x82);

	/***********************C1 Capture********************************/
	long m;
	long n;
	char cReadFlag_q[32] = { "\0" };
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x2F8, 0x1);    //PKTMEM_MODE_CFG

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x2CC, 0x1);    //PKTMEM_SEL

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x2F8, 0x11);   //PKTMEM_MODE_CFG

	d2s_test.wait(0.001);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x2CC, 0x0);    //PKTMEM_SEL

	d2s_test.wait(0.00005);

	d2s_test.SSI_write(0x200, 0x2003, false);

	for (m = 0; m < 4; m++) {         //0xc0 to 0xfc, step 4
		d2s_test.SSI_write(0x202, 0xC0 + m * 4, false);

		for (n = 0; n < 128; n++) {       //0 to 0x3ff
			//Call SSI_read_Module(0x0 + 8 * j, True, 8);
			//Call SSI_read_Module(0x2 + 8 * j, True, 8);
			long k = m * 128 + n;
			sprintf(cReadFlag_q, "readdata1_i%d", k);
			d2s_test.SSI_read(0x4 + 8 * n, cReadFlag_q, 7);

			sprintf(cReadFlag_q, "readdata1_q%d", k);
			d2s_test.SSI_read(0x6 + 8 * n, cReadFlag_q, 7);
		}
	}

	/**************************Restore************************************/
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy    restroe TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x80);        //rf    restore RX gain
	d2s_test.SSI_write(0x80, 0x0);         //rf    restore   TX PWR cal path

	d2s_test.SSI_write(0x70, 0x7000);      //rf

	d2s_test.SSI_write(0x5C, 0x0);         //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x94, 0x80);        //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x37);        //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf    close LOGEN
	d2s_test.SSI_write(0xC, 0x2);      //rf    default control
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    restore normal service

	d2s::d2s_LABEL_END();

	long long nCapData0[1024] = { 0 };
	long long nCapData1[1024] = { 0 };
	int nsize = sizeof(nCapData0) / sizeof(long long);




//	FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
//
//
//	if	(!d2s::isProductionMode()) {
//            for (j = 0; j < 512; j++) {
//                sprintf(cReadFlag, "readdata0_i%d", j);
//
////                nCapData0[j*2] = D2S_GetValue(index,d2s_test,cReadFlag);
//                nCapData0[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);
//
//                sprintf(cReadFlag, "readdata0_q%d", j);
//                nCapData0[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
////                nCapData0[j*2+1] = D2S_GetValue(index,d2s_test,cReadFlag);
//
//                sprintf(cReadFlag_q, "readdata1_i%d", j);
//                nCapData1[j*2] = d2s_test.getReadValue(cReadFlag_q).at(site_id);
////                nCapData1[j*2] = D2S_GetValue(index,d2s_test,cReadFlag_q);
//
//                sprintf(cReadFlag_q, "readdata1_q%d", j);
//                nCapData1[j*2+1] = d2s_test.getReadValue(cReadFlag_q).at(site_id);
////                nCapData1[j*2+1] = D2S_GetValue(index,d2s_test,cReadFlag_q);
//
//            }
//	} else {
//		unsigned long data[32768];
//
//		DIO_Capture(site_id,"DBB_GPIO7", data);
//
//		for(int n = 0;n<16384;n+=16)
//		{
//			nCapData0[n/16] = ConvertCapData(data+n,16);
//		}
//		for(int n = 16384;n<32768;n+=16)
//		{
//			nCapData1[(n-16384)/16] = ConvertCapData(data+n,16);
//		}
//	}
//
//	pReadValue0->InitDataArray(site_id, nsize);
//	pReadValue0->CopyElement(site_id, nCapData0,nsize);
//	pReadValue1->InitDataArray(site_id, nsize);
//	pReadValue1->CopyElement(site_id, nCapData1,nsize);
//
//	FOREACH_ACTIVESITE_END

	if (!d2s::isProductionMode()) {
		FOREACH_ACTIVESITE_BEGIN(site_id,bInterrupt)
		for (j = 0; j < 512; j++) {
			sprintf(cReadFlag, "readdata0_i%d", j);

//                nCapData0[j*2] = D2S_GetValue(index,d2s_test,cReadFlag);
			nCapData0[j*2] = d2s_test.getReadValue(cReadFlag).at(site_id);

			sprintf(cReadFlag, "readdata0_q%d", j);
			nCapData0[j*2+1] = d2s_test.getReadValue(cReadFlag).at(site_id);
//                nCapData0[j*2+1] = D2S_GetValue(index,d2s_test,cReadFlag);

			sprintf(cReadFlag_q, "readdata1_i%d", j);
			nCapData1[j*2] = d2s_test.getReadValue(cReadFlag_q).at(site_id);
//                nCapData1[j*2] = D2S_GetValue(index,d2s_test,cReadFlag_q);

			sprintf(cReadFlag_q, "readdata1_q%d", j);
			nCapData1[j*2+1] = d2s_test.getReadValue(cReadFlag_q).at(site_id);
//                nCapData1[j*2+1] = D2S_GetValue(index,d2s_test,cReadFlag_q);

		}
		pReadValue0->InitDataArray(site_id, nsize);
		pReadValue0->CopyElement(site_id, nCapData0,nsize);
		pReadValue1->InitDataArray(site_id, nsize);
		pReadValue1->CopyElement(site_id, nCapData1,nsize);


		FOREACH_ACTIVESITE_END
		} else {

			unsigned long data[32768];

			auto CAP_Data = TheInst.Digital().PatEng().GetCaptureData("DBB_GPIO7");

			for (auto siteData : CAP_Data)
			{
				for (auto pinData : siteData.second)
				{
					int i=0;
					for (auto capData : pinData.second)
					{
						data[i] = capData.iECResult;
						i++;

					}
				}

				for(int n = 0;n<16384;n+=16)
				{
					nCapData0[n/16] = ConvertCapData(data+n,16);
				}
				for(int n = 16384;n<32768;n+=16)
				{
					nCapData1[(n-16384)/16] = ConvertCapData(data+n,16);
				}

				pReadValue0->InitDataArray(siteData.first, nsize);
				pReadValue0->CopyElement(siteData.first, nCapData0,nsize);
				pReadValue1->InitDataArray(siteData.first, nsize);
				pReadValue1->CopyElement(siteData.first, nCapData1,nsize);
			}

		}

}

void PDBUF_DET_C0_Set_Module() {

	//File:  PD_BUF.xlsx
	//Sheet: 5G_PDBUF_DET_C0
	//File time: 5/31/2017 1:57:34 PM
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    close normal service

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x240, 0x111);      //soc    ADC setting
	d2s_test.SSI_write(0x244, 0x1);    //soc
	d2s_test.SSI_write(0x244, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);      //rf     register control
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf
	d2s_test.SSI_write(0x20, 0x437);       //rf     Open LOGEN

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);     //soc    Select channel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);     //phy    Open phy
	d2s_test.SSI_write(0x24, 0x1);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);        //phy   set TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x180);       //rf   RX gain set
	d2s_test.SSI_write(0x7C, 0x3500);      //rf

	d2s_test.SSI_write(0x70, 0x1008);      //rf
	d2s::d2s_LABEL_END();
}

void PDBUF_DET_C0_Restore_Module() {
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy    restroe TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x80);        //rf    restore RX gain
	d2s_test.SSI_write(0x7C, 0x0);         //rf    restore   TX PWR cal path

	d2s_test.SSI_write(0x70, 0x7000);      //rf
	d2s_test.SSI_write(0x68, 0x0);         //rf
	d2s_test.SSI_write(0x5C, 0x0);         //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x18, 0x80);        //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x37);        //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf    close LOGEN
	d2s_test.SSI_write(0xC, 0x2);      //rf    default control
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    restore normal service
	d2s::d2s_LABEL_END();
}

void PDBUF_DET_C1_Set_Module() {

	//File:  PD_BUF.xlsx
	//Sheet: 5G_PDBUF_DET_C1
	//File time: 5/31/2017 1:57:34 PM
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    close normal service

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x258, 0x111);      //soc    ADC setting
	d2s_test.SSI_write(0x25C, 0x1);          //soc
	d2s_test.SSI_write(0x25C, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x8, 0x3);      //rf     register control
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf
	d2s_test.SSI_write(0x20, 0x4037);      //rf     Open LOGEN

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);    //soc    Select channel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);     //phy    Open phy
	d2s_test.SSI_write(0x24, 0x2);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);        //phy   set TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x180);       //rf   RX gain set
	d2s_test.SSI_write(0x80, 0x3500);      //rf

	d2s_test.SSI_write(0x70, 0x1100);      //rf
	d2s::d2s_LABEL_END();
}

void PDBUF_DET_C1_Restore_Module() {
	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy    restroe TX/RX FIFO

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x80);        //rf    restore RX gain
	d2s_test.SSI_write(0x80, 0x0);         //rf    restore   TX PWR cal path

	d2s_test.SSI_write(0x70, 0x7000);      //rf

	d2s_test.SSI_write(0x5C, 0x0);         //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x94, 0x80);        //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x37);        //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf    close LOGEN
	d2s_test.SSI_write(0xC, 0x2);      //rf    default control
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac    restore normal service
	d2s::d2s_LABEL_END();
}

#if 0
void PD_BUF_Cmmulate_Module(CSiteLong *FEM_PD_data) {

	//File:  PD_BUF.xlsx
	//Sheet: Cmmulate
	//File time: 5/31/2017 1:57:34 PM
	char cReadFlag[32] = { "\0" };

	d2s::d2s_LABEL_BEGIN("ssi", d2s_WorkMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x168, 0x0);    //phy    loop count
	d2s_test.SSI_write(0x16C, 0x1FF);      //phy    accumulate points

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x6C, 0x1);     //soc    set PHY_TEST_START high

	d2s_test.wait(0.00005);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x164, 0x1);    //phy    enable accumulate

	d2s_test.wait(0.00005);

	//Call SSI_read_Module(0x80, , 12);  //(bit0:bit21);
	//Call SSI_read_Module(0x82, , 12);
	d2s_test.SSI_read(0x80, "readdata_1", 9);
	d2s_test.SSI_read(0x82, "readdata_2", 9);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x164, 0x0);    //phy    disable accumulate

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x6C, 0x0);     //soc    set PHY_TEST_START low
	d2s::d2s_LABEL_END();

	long long FEM_PD_data_buf;

	FOREACH_ACTIVESITE_BEGIN(index,bInterrupt)
	//int site_id = api->Get_active_site();


	sprintf(cReadFlag, "readdata_%d", 1);
	long long readvalue1 = D2S_GetValue(index,d2s_test,cReadFlag);

	sprintf(cReadFlag, "readdata_%d", 2);
	long long readvalue2 = D2S_GetValue(index,d2s_test,cReadFlag);

	FEM_PD_data_buf = readvalue1 + ((readvalue2 &0x3F)<<16);//改成迭代器方式

	if(readvalue2&0x20)
	{
		FEM_PD_data_buf = FEM_PD_data_buf - pow(2,22);
	}
	FEM_PD_data->InitDataArray(index, 1);
	FEM_PD_data->CopyElement(index, &FEM_PD_data_buf,1);

	FOREACH_ACTIVESITE_END

}
#endif

void RXIQ_5G_C0_Set_Module() {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
	//Sheet: RXIQ_5G_C0_Module
	//File time: 2017/6/20 19:11:50
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);     //mac

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x1);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x8, 0x3);      //rf
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x240, 0x111);      //soc
	d2s_test.SSI_write(0x244, 0x1);    //soc
	d2s_test.SSI_write(0x244, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x37);        //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);     //soc

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);     //phy
	d2s_test.SSI_write(0x24, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);        //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x1E0);       //rf
	d2s::d2s_LABEL_END();
}

void RXIQ_5G_C0_Restore_Module() {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
	//Sheet: RXIQ_5G_C0_Module
	//File time: 2017/6/20 19:11:50
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x24, 0x80);        //rf
	d2s_test.SSI_write(0x20, 0x37);        //rf
	d2s_test.SSI_write(0x0, 0x0);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf
	d2s_test.SSI_write(0xC, 0x2);      //rf
	d2s_test.SSI_write(0x10, 0x2);            //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac
	d2s::d2s_LABEL_END();
}

void RXIQ_5G_C1_Set_Module() {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
	//Sheet: RXIQ_5G_C1_Module
	//File time: 2017/6/20 19:11:50
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x2);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x8, 0x3);      //rf
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x258, 0x111);      //soc
	d2s_test.SSI_write(0x25C, 0x1);    //soc
	d2s_test.SSI_write(0x25C, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x20, 0x37);        //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);    //soc

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);     //phy
	d2s_test.SSI_write(0x24, 0x2);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);        //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x1E0);       //rf
	d2s::d2s_LABEL_END();
}

void RXIQ_5G_C1_Restore_Module() {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
	//Sheet: RXIQ_5G_C1_Module
	//File time: 2017/6/20 19:11:50
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x28, 0x80);        //rf
	d2s_test.SSI_write(0x20, 0x37);        //rf
	d2s_test.SSI_write(0x0, 0x0);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf
	d2s_test.SSI_write(0xC, 0x2);      //rf
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac
	d2s::d2s_LABEL_END();
}

void Accumu_Receive_Module() {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
	//Sheet: Accumu_Receive_Module
	//File time: 6/20/2017 10:04:46 PM

	long i;
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x168, 0x1F);   //phy
	d2s_test.SSI_write(0x16C, 0x1FF);      //phy

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x6C, 0x1);     //soc

	d2s_test.wait(0.00005);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x164, 0x1);    //phy

	for(int i=0;i<2;i++)
		d2s_test.wait(0.001);

	for (i = 0; i < 124; i = i + 4) {
		//Call SSI_read_Module(0x0 + i, , 12); //(bit0:bit21);
		//Call SSI_read_Module(0x0 + i + 2, , 12); //phy
	}

	for (i = 0; i < 124; i = i + 4) {
		//Call SSI_read_Module(0x80 + i, , 12); //(bit0:bit21);
		//Call SSI_read_Module(0x80 + i + 2, , 12); //phy
	}

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x164, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x6C, 0x0);     //soc
	d2s::d2s_LABEL_END();
}

void TXIQ_5G_C0_Module() {

	//File:  Hi1151_V200_Calibration_Config_for_ATE_20170619.xlsx
	//Sheet: TXIQ_5G_C0_Module
	//File time: 6/20/2017 10:32:13 PM
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x204, 0x0, false);     //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x24C, 0x111);      //soc
	d2s_test.SSI_write(0x250, 0x1);    //soc
	d2s_test.SSI_write(0x250, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x0);      //rf
	d2s_test.SSI_write(0x4, 0x1);      //rf
	d2s_test.SSI_write(0x8, 0x3);      //rf
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);     //soc

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);     //phy
	d2s_test.SSI_write(0x24, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);        //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);    //phy
	d2s_test.SSI_write(0x128, 0x0);    //phy
	d2s_test.SSI_write(0x128, 0x1);    //phy
	d2s::d2s_LABEL_END();
}

void DAC_SPUR_C0_Module() {

	//
	//File time: 6/20/2017 10:32:13 PM
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //close normal business   MAC

//    d2s_test.SSI_write(0x200, 0x2000, false); //ADC
//    d2s_test.SSI_write(0x202, 0x80, false);
//    d2s_test.SSI_write(0x240, 0x111);      //soc
//    d2s_test.SSI_write(0x244, 0x1);    //soc
//    d2s_test.SSI_write(0x244, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x24C, 0x111);      //soc
	d2s_test.SSI_write(0x250, 0x1);    //soc
	d2s_test.SSI_write(0x250, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x1D8, 0xB974);     //DAC @20180321 B974->B977
	d2s_test.SSI_write(0x378, 0x140);    //DAC
	d2s_test.SSI_write(0x37C, 0x5);      //DAC
	d2s_test.SSI_write(0x380, 0x140);    //DAC
	d2s_test.SSI_write(0x384, 0x5);      //DAC

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x8, 0x33);      //CLA2 PHY
	d2s_test.SSI_write(0xC, 0x33);      //CLA2 PHY

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	//d2s_test.SSI_write(0x0, 0x0);      //rf
	//d2s_test.SSI_write(0x4, 0x1);      //rf
	d2s_test.SSI_write(0x8, 0x3);      //rf
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf
	d2s_test.SSI_write(0x20, 0x37);        //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x0);     //soc

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x1);     //phy
	d2s_test.SSI_write(0x24, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x34, 0x2613);     //local_C1_sel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x5);        //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);        //phy DAC Gain

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);        //phy LPF
	d2s_test.SSI_write(0xC8, 0x20);       //phy UPC
	d2s_test.SSI_write(0x1C, 0x2121);        //rf
	d2s_test.SSI_write(0x14, 0x400);        //rf
	d2s_test.SSI_write(0x4, 0x1);           //rf
	//d2s_test.SSI_write(0x34, 0x1434);        //rf  ?????

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xC8, false);
	d2s_test.SSI_write(0x10, 0x582A);        //rf
	d2s_test.SSI_write(0x14, 0xAAAA);        //rf
	d2s_test.SSI_write(0x4, 0x1000);        //rf
	d2s_test.SSI_write(0x4, 0x1003);        //rf
	d2s_test.SSI_write(0x4, 0x100B);        //rf
	d2s_test.wait(0.00015);
	d2s_test.SSI_write(0x4, 0xB);        //rf

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x10);    //phy
	d2s_test.SSI_write(0x128, 0x10);    //phy
	d2s_test.SSI_write(0x128, 0x11);    //phy
	d2s::d2s_LABEL_END();
}

void DAC_SPUR_C1_Module() {

	//
	//File time: 6/20/2017 10:32:13 PM
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //close normal business   MAC
//
//    d2s_test.SSI_write(0x200, 0x2000, false); //ADC
//    d2s_test.SSI_write(0x202, 0x80, false);
//    d2s_test.SSI_write(0x258, 0x111);      //soc
//    d2s_test.SSI_write(0x25C, 0x1);    //soc
//    d2s_test.SSI_write(0x25C, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x264, 0x111);      //soc
	d2s_test.SSI_write(0x268, 0x1);    //soc
	d2s_test.SSI_write(0x268, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x240, 0xB974);     //DAC @20180321 B974->B977
	d2s_test.SSI_write(0x378, 0x140);    //DAC
	d2s_test.SSI_write(0x37C, 0x5);      //DAC
	d2s_test.SSI_write(0x380, 0x140);    //DAC
	d2s_test.SSI_write(0x384, 0x5);      //DAC

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0xA0, false);
	d2s_test.SSI_write(0x8, 0x33);      //CLA2 PHY
	d2s_test.SSI_write(0xC, 0x33);      //CLA2 PHY

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	//d2s_test.SSI_write(0x0, 0x0);      //rf
	//d2s_test.SSI_write(0x4, 0x1);      //rf
	d2s_test.SSI_write(0x8, 0x3);      //rf
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf
	d2s_test.SSI_write(0x20, 0x37);        //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);     //soc

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);     //phy
	d2s_test.SSI_write(0x24, 0x2);     //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x34, 0x7113);     //local_C1_sel

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);        //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x388, 0x0);        //phy DAC Gain

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x2C, 0x5);        //phy LPF
	d2s_test.SSI_write(0xF4, 0x20);       //phy UPC
	d2s_test.SSI_write(0x1C, 0x2121);        //rf
	d2s_test.SSI_write(0x18, 0x400);        //rf
	d2s_test.SSI_write(0x4, 0x2);           //rf
	//d2s_test.SSI_write(0x34, 0x1434);        //rf  ?????

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0xC8, false);
	d2s_test.SSI_write(0x10, 0x582A);        //rf
	d2s_test.SSI_write(0x14, 0xAAAA);        //rf
	d2s_test.SSI_write(0x4, 0x1000);        //rf
	d2s_test.SSI_write(0x4, 0x1003);        //rf
	d2s_test.SSI_write(0x4, 0x100B);        //rf
	d2s_test.wait(0.00015);
	d2s_test.SSI_write(0x4, 0xB);        //rf

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x10);    //phy
	d2s_test.SSI_write(0x128, 0x10);    //phy
	d2s_test.SSI_write(0x128, 0x11);    //phy
	d2s::d2s_LABEL_END();
}

void TXIQ_5G_37p5M_C0_Module() {
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x20, 0x8);

	d2s_test.wait(0.001);

	d2s_test.SSI_write(0x204, 0x8D, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0xC0, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x204, 0x68, false);
	d2s_test.SSI_write(0x4, 0x5F);

	d2s_test.SSI_write(0x204, 0xE, false);
	d2s_test.SSI_write(0x8, 0x8C);

	d2s_test.SSI_write(0x204, 0x3AC, false);
	d2s_test.SSI_write(0xC, 0x71);

	d2s_test.SSI_write(0x204, 0x376, false);
	d2s_test.SSI_write(0x10, 0x1C);

	d2s_test.SSI_write(0x204, 0x387, false);
	d2s_test.SSI_write(0x14, 0x3B8);

	d2s_test.SSI_write(0x204, 0x3D7, false);
	d2s_test.SSI_write(0x18, 0x379);

	d2s_test.SSI_write(0x204, 0x3C, false);
	d2s_test.SSI_write(0x1C, 0x381);

	d2s_test.SSI_write(0x204, 0x82, false);
	d2s_test.SSI_write(0x20, 0x3CA);

	d2s_test.SSI_write(0x204, 0x85, false);
	d2s_test.SSI_write(0x24, 0x30);

	d2s_test.SSI_write(0x204, 0x42, false);
	d2s_test.SSI_write(0x28, 0x7C);

	d2s_test.SSI_write(0x204, 0x3DE, false);
	d2s_test.SSI_write(0x2C, 0x89);

	d2s_test.SSI_write(0x204, 0x38B, false);
	d2s_test.SSI_write(0x30, 0x4E);

	d2s_test.SSI_write(0x204, 0x375, false);
	d2s_test.SSI_write(0x34, 0x3EB);

	d2s_test.SSI_write(0x204, 0x3A7, false);
	d2s_test.SSI_write(0x38, 0x393);

	d2s_test.SSI_write(0x204, 0x7, false);
	d2s_test.SSI_write(0x3C, 0x373);

	d2s_test.SSI_write(0x204, 0x64, false);
	d2s_test.SSI_write(0x40, 0x39C);

	d2s_test.SSI_write(0x204, 0x8D, false);
	d2s_test.SSI_write(0x44, 0x3F9);

	d2s_test.SSI_write(0x204, 0x6D, false);
	d2s_test.SSI_write(0x48, 0x59);

	d2s_test.SSI_write(0x204, 0x15, false);
	d2s_test.SSI_write(0x4C, 0x8B);

	d2s_test.SSI_write(0x204, 0x3B2, false);
	d2s_test.SSI_write(0x50, 0x75);

	d2s_test.SSI_write(0x204, 0x377, false);
	d2s_test.SSI_write(0x54, 0x22);

	d2s_test.SSI_write(0x204, 0x384, false);
	d2s_test.SSI_write(0x58, 0x3BE);

	d2s_test.SSI_write(0x204, 0x3D0, false);
	d2s_test.SSI_write(0x5C, 0x37B);

	d2s_test.SSI_write(0x204, 0x36, false);
	d2s_test.SSI_write(0x60, 0x37E);

	d2s_test.SSI_write(0x204, 0x7F, false);
	d2s_test.SSI_write(0x64, 0x3C4);

	d2s_test.SSI_write(0x204, 0x87, false);
	d2s_test.SSI_write(0x68, 0x29);

	d2s_test.SSI_write(0x204, 0x48, false);
	d2s_test.SSI_write(0x6C, 0x79);

	d2s_test.SSI_write(0x204, 0x3E4, false);
	d2s_test.SSI_write(0x70, 0x8A);

	d2s_test.SSI_write(0x204, 0x38F, false);
	d2s_test.SSI_write(0x74, 0x54);

	d2s_test.SSI_write(0x204, 0x374, false);
	d2s_test.SSI_write(0x78, 0x3F2);

	d2s_test.SSI_write(0x204, 0x3A1, false);
	d2s_test.SSI_write(0x7C, 0x398);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x80, 0x373);

	d2s_test.SSI_write(0x204, 0x5F, false);
	d2s_test.SSI_write(0x84, 0x398);

	d2s_test.SSI_write(0x204, 0x8C, false);
	d2s_test.SSI_write(0x88, 0x3F2);

	d2s_test.SSI_write(0x204, 0x71, false);
	d2s_test.SSI_write(0x8C, 0x54);

	d2s_test.SSI_write(0x204, 0x1C, false);
	d2s_test.SSI_write(0x90, 0x8A);

	d2s_test.SSI_write(0x204, 0x3B8, false);
	d2s_test.SSI_write(0x94, 0x79);

	d2s_test.SSI_write(0x204, 0x379, false);
	d2s_test.SSI_write(0x98, 0x29);

	d2s_test.SSI_write(0x204, 0x381, false);
	d2s_test.SSI_write(0x9C, 0x3C4);

	d2s_test.SSI_write(0x204, 0x3CA, false);
	d2s_test.SSI_write(0xA0, 0x37E);

	d2s_test.SSI_write(0x204, 0x30, false);
	d2s_test.SSI_write(0xA4, 0x37B);

	d2s_test.SSI_write(0x204, 0x7C, false);
	d2s_test.SSI_write(0xA8, 0x3BE);

	d2s_test.SSI_write(0x204, 0x89, false);
	d2s_test.SSI_write(0xAC, 0x22);

	d2s_test.SSI_write(0x204, 0x4E, false);
	d2s_test.SSI_write(0xB0, 0x75);

	d2s_test.SSI_write(0x204, 0x3EB, false);
	d2s_test.SSI_write(0xB4, 0x8B);

	d2s_test.SSI_write(0x204, 0x393, false);
	d2s_test.SSI_write(0xB8, 0x59);

	d2s_test.SSI_write(0x204, 0x373, false);
	d2s_test.SSI_write(0xBC, 0x3F9);

	d2s_test.SSI_write(0x204, 0x39C, false);
	d2s_test.SSI_write(0xC0, 0x39C);

	d2s_test.SSI_write(0x204, 0x3F9, false);
	d2s_test.SSI_write(0xC4, 0x373);

	d2s_test.SSI_write(0x204, 0x59, false);
	d2s_test.SSI_write(0xC8, 0x393);

	d2s_test.SSI_write(0x204, 0x8B, false);
	d2s_test.SSI_write(0xCC, 0x3EB);

	d2s_test.SSI_write(0x204, 0x75, false);
	d2s_test.SSI_write(0xD0, 0x4E);

	d2s_test.SSI_write(0x204, 0x22, false);
	d2s_test.SSI_write(0xD4, 0x89);

	d2s_test.SSI_write(0x204, 0x3BE, false);
	d2s_test.SSI_write(0xD8, 0x7C);

	d2s_test.SSI_write(0x204, 0x37B, false);
	d2s_test.SSI_write(0xDC, 0x30);

	d2s_test.SSI_write(0x204, 0x37E, false);
	d2s_test.SSI_write(0xE0, 0x3CA);

	d2s_test.SSI_write(0x204, 0x3C4, false);
	d2s_test.SSI_write(0xE4, 0x381);

	d2s_test.SSI_write(0x204, 0x29, false);
	d2s_test.SSI_write(0xE8, 0x379);

	d2s_test.SSI_write(0x204, 0x79, false);
	d2s_test.SSI_write(0xEC, 0x3B8);

	d2s_test.SSI_write(0x204, 0x8A, false);
	d2s_test.SSI_write(0xF0, 0x1C);

	d2s_test.SSI_write(0x204, 0x54, false);
	d2s_test.SSI_write(0xF4, 0x71);

	d2s_test.SSI_write(0x204, 0x3F2, false);
	d2s_test.SSI_write(0xF8, 0x8C);

	d2s_test.SSI_write(0x204, 0x398, false);
	d2s_test.SSI_write(0xFC, 0x5F);

	d2s_test.SSI_write(0x204, 0x373, false);
	d2s_test.SSI_write(0x100, 0x0);

	d2s_test.SSI_write(0x204, 0x398, false);
	d2s_test.SSI_write(0x104, 0x3A1);

	d2s_test.SSI_write(0x204, 0x3F2, false);
	d2s_test.SSI_write(0x108, 0x374);

	d2s_test.SSI_write(0x204, 0x54, false);
	d2s_test.SSI_write(0x10C, 0x38F);

	d2s_test.SSI_write(0x204, 0x8A, false);
	d2s_test.SSI_write(0x110, 0x3E4);

	d2s_test.SSI_write(0x204, 0x79, false);
	d2s_test.SSI_write(0x114, 0x48);

	d2s_test.SSI_write(0x204, 0x29, false);
	d2s_test.SSI_write(0x118, 0x87);

	d2s_test.SSI_write(0x204, 0x3C4, false);
	d2s_test.SSI_write(0x11C, 0x7F);

	d2s_test.SSI_write(0x204, 0x37E, false);
	d2s_test.SSI_write(0x120, 0x36);

	d2s_test.SSI_write(0x204, 0x37B, false);
	d2s_test.SSI_write(0x124, 0x3D0);

	d2s_test.SSI_write(0x204, 0x3BE, false);
	d2s_test.SSI_write(0x128, 0x384);

	d2s_test.SSI_write(0x204, 0x22, false);
	d2s_test.SSI_write(0x12C, 0x377);

	d2s_test.SSI_write(0x204, 0x75, false);
	d2s_test.SSI_write(0x130, 0x3B2);

	d2s_test.SSI_write(0x204, 0x8B, false);
	d2s_test.SSI_write(0x134, 0x15);

	d2s_test.SSI_write(0x204, 0x59, false);
	d2s_test.SSI_write(0x138, 0x6D);

	d2s_test.SSI_write(0x204, 0x3F9, false);
	d2s_test.SSI_write(0x13C, 0x8D);

	d2s_test.SSI_write(0x204, 0x39C, false);
	d2s_test.SSI_write(0x140, 0x64);

	d2s_test.SSI_write(0x204, 0x373, false);
	d2s_test.SSI_write(0x144, 0x7);

	d2s_test.SSI_write(0x204, 0x393, false);
	d2s_test.SSI_write(0x148, 0x3A7);

	d2s_test.SSI_write(0x204, 0x3EB, false);
	d2s_test.SSI_write(0x14C, 0x375);

	d2s_test.SSI_write(0x204, 0x4E, false);
	d2s_test.SSI_write(0x150, 0x38B);

	d2s_test.SSI_write(0x204, 0x89, false);
	d2s_test.SSI_write(0x154, 0x3DE);

	d2s_test.SSI_write(0x204, 0x7C, false);
	d2s_test.SSI_write(0x158, 0x42);

	d2s_test.SSI_write(0x204, 0x30, false);
	d2s_test.SSI_write(0x15C, 0x85);

	d2s_test.SSI_write(0x204, 0x3CA, false);
	d2s_test.SSI_write(0x160, 0x82);

	d2s_test.SSI_write(0x204, 0x381, false);
	d2s_test.SSI_write(0x164, 0x3C);

	d2s_test.SSI_write(0x204, 0x379, false);
	d2s_test.SSI_write(0x168, 0x3D7);

	d2s_test.SSI_write(0x204, 0x3B8, false);
	d2s_test.SSI_write(0x16C, 0x387);

	d2s_test.SSI_write(0x204, 0x1C, false);
	d2s_test.SSI_write(0x170, 0x376);

	d2s_test.SSI_write(0x204, 0x71, false);
	d2s_test.SSI_write(0x174, 0x3AC);

	d2s_test.SSI_write(0x204, 0x8C, false);
	d2s_test.SSI_write(0x178, 0xE);

	d2s_test.SSI_write(0x204, 0x5F, false);
	d2s_test.SSI_write(0x17C, 0x68);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x180, 0x8D);

	d2s_test.SSI_write(0x204, 0x3A1, false);
	d2s_test.SSI_write(0x184, 0x68);

	d2s_test.SSI_write(0x204, 0x374, false);
	d2s_test.SSI_write(0x188, 0xE);

	d2s_test.SSI_write(0x204, 0x38F, false);
	d2s_test.SSI_write(0x18C, 0x3AC);

	d2s_test.SSI_write(0x204, 0x3E4, false);
	d2s_test.SSI_write(0x190, 0x376);

	d2s_test.SSI_write(0x204, 0x48, false);
	d2s_test.SSI_write(0x194, 0x387);

	d2s_test.SSI_write(0x204, 0x87, false);
	d2s_test.SSI_write(0x198, 0x3D7);

	d2s_test.SSI_write(0x204, 0x7F, false);
	d2s_test.SSI_write(0x19C, 0x3C);

	d2s_test.SSI_write(0x204, 0x36, false);
	d2s_test.SSI_write(0x1A0, 0x82);

	d2s_test.SSI_write(0x204, 0x3D0, false);
	d2s_test.SSI_write(0x1A4, 0x85);

	d2s_test.SSI_write(0x204, 0x384, false);
	d2s_test.SSI_write(0x1A8, 0x42);

	d2s_test.SSI_write(0x204, 0x377, false);
	d2s_test.SSI_write(0x1AC, 0x3DE);

	d2s_test.SSI_write(0x204, 0x3B2, false);
	d2s_test.SSI_write(0x1B0, 0x38B);

	d2s_test.SSI_write(0x204, 0x15, false);
	d2s_test.SSI_write(0x1B4, 0x375);

	d2s_test.SSI_write(0x204, 0x6D, false);
	d2s_test.SSI_write(0x1B8, 0x3A7);

	d2s_test.SSI_write(0x204, 0x8D, false);
	d2s_test.SSI_write(0x1BC, 0x7);

	d2s_test.SSI_write(0x204, 0x64, false);
	d2s_test.SSI_write(0x1C0, 0x64);

	d2s_test.SSI_write(0x204, 0x7, false);
	d2s_test.SSI_write(0x1C4, 0x8D);

	d2s_test.SSI_write(0x204, 0x3A7, false);
	d2s_test.SSI_write(0x1C8, 0x6D);

	d2s_test.SSI_write(0x204, 0x375, false);
	d2s_test.SSI_write(0x1CC, 0x15);

	d2s_test.SSI_write(0x204, 0x38B, false);
	d2s_test.SSI_write(0x1D0, 0x3B2);

	d2s_test.SSI_write(0x204, 0x3DE, false);
	d2s_test.SSI_write(0x1D4, 0x377);

	d2s_test.SSI_write(0x204, 0x42, false);
	d2s_test.SSI_write(0x1D8, 0x384);

	d2s_test.SSI_write(0x204, 0x85, false);
	d2s_test.SSI_write(0x1DC, 0x3D0);

	d2s_test.SSI_write(0x204, 0x82, false);
	d2s_test.SSI_write(0x1E0, 0x36);

	d2s_test.SSI_write(0x204, 0x3C, false);
	d2s_test.SSI_write(0x1E4, 0x7F);

	d2s_test.SSI_write(0x204, 0x3D7, false);
	d2s_test.SSI_write(0x1E8, 0x87);

	d2s_test.SSI_write(0x204, 0x387, false);
	d2s_test.SSI_write(0x1EC, 0x48);

	d2s_test.SSI_write(0x204, 0x376, false);
	d2s_test.SSI_write(0x1F0, 0x3E4);

	d2s_test.SSI_write(0x204, 0x3AC, false);
	d2s_test.SSI_write(0x1F4, 0x38F);

	d2s_test.SSI_write(0x204, 0xE, false);
	d2s_test.SSI_write(0x1F8, 0x374);

	d2s_test.SSI_write(0x204, 0x68, false);
	d2s_test.SSI_write(0x1FC, 0x3A1);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x78, 0x7F);
	d2s_test.SSI_write(0x20, 0x1);
	d2s_test.SSI_write(0x6C, 0x1);
	d2s::d2s_LABEL_END();
}

void TXIQ_5G_C1_Module() {

	//File:  5G_TXIQ.xlsx
	//Sheet: TXIQ_5G_C1_Module
	//File time: 6/20/2017 10:32:13 PM
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x264, 0x111);      //soc
	d2s_test.SSI_write(0x268, 0x1);    //soc
	d2s_test.SSI_write(0x268, 0x101);      //soc

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x0);      //rf
	d2s_test.SSI_write(0x4, 0x2);      //rf
	d2s_test.SSI_write(0x8, 0x3);      //rf
	d2s_test.SSI_write(0xC, 0x2F);     //rf
	d2s_test.SSI_write(0x10, 0x2F);        //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x94, 0x11);    //soc

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x88, false);
	d2s_test.SSI_write(0x20, 0x2);     //phy
	d2s_test.SSI_write(0x24, 0x2);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0xA);        //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x98, false);
	d2s_test.SSI_write(0x80, 0x1);     //phy

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);    //phy
	d2s_test.SSI_write(0x128, 0x0);    //phy
	d2s_test.SSI_write(0x128, 0x1);    //phy
	d2s::d2s_LABEL_END();
}

void TXIQ_5G_37p5M_C1_Module() {
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x20, 0x8);

	d2s_test.wait(0.001);

	d2s_test.SSI_write(0x204, 0x8D, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0xC0, false);
	d2s_test.SSI_write(0x0, 0x0);

	d2s_test.SSI_write(0x204, 0x68, false);
	d2s_test.SSI_write(0x4, 0x5F);

	d2s_test.SSI_write(0x204, 0xE, false);
	d2s_test.SSI_write(0x8, 0x8C);

	d2s_test.SSI_write(0x204, 0x3AC, false);
	d2s_test.SSI_write(0xC, 0x71);

	d2s_test.SSI_write(0x204, 0x376, false);
	d2s_test.SSI_write(0x10, 0x1C);

	d2s_test.SSI_write(0x204, 0x387, false);
	d2s_test.SSI_write(0x14, 0x3B8);

	d2s_test.SSI_write(0x204, 0x3D7, false);
	d2s_test.SSI_write(0x18, 0x379);

	d2s_test.SSI_write(0x204, 0x3C, false);
	d2s_test.SSI_write(0x1C, 0x381);

	d2s_test.SSI_write(0x204, 0x82, false);
	d2s_test.SSI_write(0x20, 0x3CA);

	d2s_test.SSI_write(0x204, 0x85, false);
	d2s_test.SSI_write(0x24, 0x30);

	d2s_test.SSI_write(0x204, 0x42, false);
	d2s_test.SSI_write(0x28, 0x7C);

	d2s_test.SSI_write(0x204, 0x3DE, false);
	d2s_test.SSI_write(0x2C, 0x89);

	d2s_test.SSI_write(0x204, 0x38B, false);
	d2s_test.SSI_write(0x30, 0x4E);

	d2s_test.SSI_write(0x204, 0x375, false);
	d2s_test.SSI_write(0x34, 0x3EB);

	d2s_test.SSI_write(0x204, 0x3A7, false);
	d2s_test.SSI_write(0x38, 0x393);

	d2s_test.SSI_write(0x204, 0x7, false);
	d2s_test.SSI_write(0x3C, 0x373);

	d2s_test.SSI_write(0x204, 0x64, false);
	d2s_test.SSI_write(0x40, 0x39C);

	d2s_test.SSI_write(0x204, 0x8D, false);
	d2s_test.SSI_write(0x44, 0x3F9);

	d2s_test.SSI_write(0x204, 0x6D, false);
	d2s_test.SSI_write(0x48, 0x59);

	d2s_test.SSI_write(0x204, 0x15, false);
	d2s_test.SSI_write(0x4C, 0x8B);

	d2s_test.SSI_write(0x204, 0x3B2, false);
	d2s_test.SSI_write(0x50, 0x75);

	d2s_test.SSI_write(0x204, 0x377, false);
	d2s_test.SSI_write(0x54, 0x22);

	d2s_test.SSI_write(0x204, 0x384, false);
	d2s_test.SSI_write(0x58, 0x3BE);

	d2s_test.SSI_write(0x204, 0x3D0, false);
	d2s_test.SSI_write(0x5C, 0x37B);

	d2s_test.SSI_write(0x204, 0x36, false);
	d2s_test.SSI_write(0x60, 0x37E);

	d2s_test.SSI_write(0x204, 0x7F, false);
	d2s_test.SSI_write(0x64, 0x3C4);

	d2s_test.SSI_write(0x204, 0x87, false);
	d2s_test.SSI_write(0x68, 0x29);

	d2s_test.SSI_write(0x204, 0x48, false);
	d2s_test.SSI_write(0x6C, 0x79);

	d2s_test.SSI_write(0x204, 0x3E4, false);
	d2s_test.SSI_write(0x70, 0x8A);

	d2s_test.SSI_write(0x204, 0x38F, false);
	d2s_test.SSI_write(0x74, 0x54);

	d2s_test.SSI_write(0x204, 0x374, false);
	d2s_test.SSI_write(0x78, 0x3F2);

	d2s_test.SSI_write(0x204, 0x3A1, false);
	d2s_test.SSI_write(0x7C, 0x398);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x80, 0x373);

	d2s_test.SSI_write(0x204, 0x5F, false);
	d2s_test.SSI_write(0x84, 0x398);

	d2s_test.SSI_write(0x204, 0x8C, false);
	d2s_test.SSI_write(0x88, 0x3F2);

	d2s_test.SSI_write(0x204, 0x71, false);
	d2s_test.SSI_write(0x8C, 0x54);

	d2s_test.SSI_write(0x204, 0x1C, false);
	d2s_test.SSI_write(0x90, 0x8A);

	d2s_test.SSI_write(0x204, 0x3B8, false);
	d2s_test.SSI_write(0x94, 0x79);

	d2s_test.SSI_write(0x204, 0x379, false);
	d2s_test.SSI_write(0x98, 0x29);

	d2s_test.SSI_write(0x204, 0x381, false);
	d2s_test.SSI_write(0x9C, 0x3C4);

	d2s_test.SSI_write(0x204, 0x3CA, false);
	d2s_test.SSI_write(0xA0, 0x37E);

	d2s_test.SSI_write(0x204, 0x30, false);
	d2s_test.SSI_write(0xA4, 0x37B);

	d2s_test.SSI_write(0x204, 0x7C, false);
	d2s_test.SSI_write(0xA8, 0x3BE);

	d2s_test.SSI_write(0x204, 0x89, false);
	d2s_test.SSI_write(0xAC, 0x22);

	d2s_test.SSI_write(0x204, 0x4E, false);
	d2s_test.SSI_write(0xB0, 0x75);

	d2s_test.SSI_write(0x204, 0x3EB, false);
	d2s_test.SSI_write(0xB4, 0x8B);

	d2s_test.SSI_write(0x204, 0x393, false);
	d2s_test.SSI_write(0xB8, 0x59);

	d2s_test.SSI_write(0x204, 0x373, false);
	d2s_test.SSI_write(0xBC, 0x3F9);

	d2s_test.SSI_write(0x204, 0x39C, false);
	d2s_test.SSI_write(0xC0, 0x39C);

	d2s_test.SSI_write(0x204, 0x3F9, false);
	d2s_test.SSI_write(0xC4, 0x373);

	d2s_test.SSI_write(0x204, 0x59, false);
	d2s_test.SSI_write(0xC8, 0x393);

	d2s_test.SSI_write(0x204, 0x8B, false);
	d2s_test.SSI_write(0xCC, 0x3EB);

	d2s_test.SSI_write(0x204, 0x75, false);
	d2s_test.SSI_write(0xD0, 0x4E);

	d2s_test.SSI_write(0x204, 0x22, false);
	d2s_test.SSI_write(0xD4, 0x89);

	d2s_test.SSI_write(0x204, 0x3BE, false);
	d2s_test.SSI_write(0xD8, 0x7C);

	d2s_test.SSI_write(0x204, 0x37B, false);
	d2s_test.SSI_write(0xDC, 0x30);

	d2s_test.SSI_write(0x204, 0x37E, false);
	d2s_test.SSI_write(0xE0, 0x3CA);

	d2s_test.SSI_write(0x204, 0x3C4, false);
	d2s_test.SSI_write(0xE4, 0x381);

	d2s_test.SSI_write(0x204, 0x29, false);
	d2s_test.SSI_write(0xE8, 0x379);

	d2s_test.SSI_write(0x204, 0x79, false);
	d2s_test.SSI_write(0xEC, 0x3B8);

	d2s_test.SSI_write(0x204, 0x8A, false);
	d2s_test.SSI_write(0xF0, 0x1C);

	d2s_test.SSI_write(0x204, 0x54, false);
	d2s_test.SSI_write(0xF4, 0x71);

	d2s_test.SSI_write(0x204, 0x3F2, false);
	d2s_test.SSI_write(0xF8, 0x8C);

	d2s_test.SSI_write(0x204, 0x398, false);
	d2s_test.SSI_write(0xFC, 0x5F);

	d2s_test.SSI_write(0x204, 0x373, false);
	d2s_test.SSI_write(0x100, 0x0);

	d2s_test.SSI_write(0x204, 0x398, false);
	d2s_test.SSI_write(0x104, 0x3A1);

	d2s_test.SSI_write(0x204, 0x3F2, false);
	d2s_test.SSI_write(0x108, 0x374);

	d2s_test.SSI_write(0x204, 0x54, false);
	d2s_test.SSI_write(0x10C, 0x38F);

	d2s_test.SSI_write(0x204, 0x8A, false);
	d2s_test.SSI_write(0x110, 0x3E4);

	d2s_test.SSI_write(0x204, 0x79, false);
	d2s_test.SSI_write(0x114, 0x48);

	d2s_test.SSI_write(0x204, 0x29, false);
	d2s_test.SSI_write(0x118, 0x87);

	d2s_test.SSI_write(0x204, 0x3C4, false);
	d2s_test.SSI_write(0x11C, 0x7F);

	d2s_test.SSI_write(0x204, 0x37E, false);
	d2s_test.SSI_write(0x120, 0x36);

	d2s_test.SSI_write(0x204, 0x37B, false);
	d2s_test.SSI_write(0x124, 0x3D0);

	d2s_test.SSI_write(0x204, 0x3BE, false);
	d2s_test.SSI_write(0x128, 0x384);

	d2s_test.SSI_write(0x204, 0x22, false);
	d2s_test.SSI_write(0x12C, 0x377);

	d2s_test.SSI_write(0x204, 0x75, false);
	d2s_test.SSI_write(0x130, 0x3B2);

	d2s_test.SSI_write(0x204, 0x8B, false);
	d2s_test.SSI_write(0x134, 0x15);

	d2s_test.SSI_write(0x204, 0x59, false);
	d2s_test.SSI_write(0x138, 0x6D);

	d2s_test.SSI_write(0x204, 0x3F9, false);
	d2s_test.SSI_write(0x13C, 0x8D);

	d2s_test.SSI_write(0x204, 0x39C, false);
	d2s_test.SSI_write(0x140, 0x64);

	d2s_test.SSI_write(0x204, 0x373, false);
	d2s_test.SSI_write(0x144, 0x7);

	d2s_test.SSI_write(0x204, 0x393, false);
	d2s_test.SSI_write(0x148, 0x3A7);

	d2s_test.SSI_write(0x204, 0x3EB, false);
	d2s_test.SSI_write(0x14C, 0x375);

	d2s_test.SSI_write(0x204, 0x4E, false);
	d2s_test.SSI_write(0x150, 0x38B);

	d2s_test.SSI_write(0x204, 0x89, false);
	d2s_test.SSI_write(0x154, 0x3DE);

	d2s_test.SSI_write(0x204, 0x7C, false);
	d2s_test.SSI_write(0x158, 0x42);

	d2s_test.SSI_write(0x204, 0x30, false);
	d2s_test.SSI_write(0x15C, 0x85);

	d2s_test.SSI_write(0x204, 0x3CA, false);
	d2s_test.SSI_write(0x160, 0x82);

	d2s_test.SSI_write(0x204, 0x381, false);
	d2s_test.SSI_write(0x164, 0x3C);

	d2s_test.SSI_write(0x204, 0x379, false);
	d2s_test.SSI_write(0x168, 0x3D7);

	d2s_test.SSI_write(0x204, 0x3B8, false);
	d2s_test.SSI_write(0x16C, 0x387);

	d2s_test.SSI_write(0x204, 0x1C, false);
	d2s_test.SSI_write(0x170, 0x376);

	d2s_test.SSI_write(0x204, 0x71, false);
	d2s_test.SSI_write(0x174, 0x3AC);

	d2s_test.SSI_write(0x204, 0x8C, false);
	d2s_test.SSI_write(0x178, 0xE);

	d2s_test.SSI_write(0x204, 0x5F, false);
	d2s_test.SSI_write(0x17C, 0x68);

	d2s_test.SSI_write(0x204, 0x0, false);
	d2s_test.SSI_write(0x180, 0x8D);

	d2s_test.SSI_write(0x204, 0x3A1, false);
	d2s_test.SSI_write(0x184, 0x68);

	d2s_test.SSI_write(0x204, 0x374, false);
	d2s_test.SSI_write(0x188, 0xE);

	d2s_test.SSI_write(0x204, 0x38F, false);
	d2s_test.SSI_write(0x18C, 0x3AC);

	d2s_test.SSI_write(0x204, 0x3E4, false);
	d2s_test.SSI_write(0x190, 0x376);

	d2s_test.SSI_write(0x204, 0x48, false);
	d2s_test.SSI_write(0x194, 0x387);

	d2s_test.SSI_write(0x204, 0x87, false);
	d2s_test.SSI_write(0x198, 0x3D7);

	d2s_test.SSI_write(0x204, 0x7F, false);
	d2s_test.SSI_write(0x19C, 0x3C);

	d2s_test.SSI_write(0x204, 0x36, false);
	d2s_test.SSI_write(0x1A0, 0x82);

	d2s_test.SSI_write(0x204, 0x3D0, false);
	d2s_test.SSI_write(0x1A4, 0x85);

	d2s_test.SSI_write(0x204, 0x384, false);
	d2s_test.SSI_write(0x1A8, 0x42);

	d2s_test.SSI_write(0x204, 0x377, false);
	d2s_test.SSI_write(0x1AC, 0x3DE);

	d2s_test.SSI_write(0x204, 0x3B2, false);
	d2s_test.SSI_write(0x1B0, 0x38B);

	d2s_test.SSI_write(0x204, 0x15, false);
	d2s_test.SSI_write(0x1B4, 0x375);

	d2s_test.SSI_write(0x204, 0x6D, false);
	d2s_test.SSI_write(0x1B8, 0x3A7);

	d2s_test.SSI_write(0x204, 0x8D, false);
	d2s_test.SSI_write(0x1BC, 0x7);

	d2s_test.SSI_write(0x204, 0x64, false);
	d2s_test.SSI_write(0x1C0, 0x64);

	d2s_test.SSI_write(0x204, 0x7, false);
	d2s_test.SSI_write(0x1C4, 0x8D);

	d2s_test.SSI_write(0x204, 0x3A7, false);
	d2s_test.SSI_write(0x1C8, 0x6D);

	d2s_test.SSI_write(0x204, 0x375, false);
	d2s_test.SSI_write(0x1CC, 0x15);

	d2s_test.SSI_write(0x204, 0x38B, false);
	d2s_test.SSI_write(0x1D0, 0x3B2);

	d2s_test.SSI_write(0x204, 0x3DE, false);
	d2s_test.SSI_write(0x1D4, 0x377);

	d2s_test.SSI_write(0x204, 0x42, false);
	d2s_test.SSI_write(0x1D8, 0x384);

	d2s_test.SSI_write(0x204, 0x85, false);
	d2s_test.SSI_write(0x1DC, 0x3D0);

	d2s_test.SSI_write(0x204, 0x82, false);
	d2s_test.SSI_write(0x1E0, 0x36);

	d2s_test.SSI_write(0x204, 0x3C, false);
	d2s_test.SSI_write(0x1E4, 0x7F);

	d2s_test.SSI_write(0x204, 0x3D7, false);
	d2s_test.SSI_write(0x1E8, 0x87);

	d2s_test.SSI_write(0x204, 0x387, false);
	d2s_test.SSI_write(0x1EC, 0x48);

	d2s_test.SSI_write(0x204, 0x376, false);
	d2s_test.SSI_write(0x1F0, 0x3E4);

	d2s_test.SSI_write(0x204, 0x3AC, false);
	d2s_test.SSI_write(0x1F4, 0x38F);

	d2s_test.SSI_write(0x204, 0xE, false);
	d2s_test.SSI_write(0x1F8, 0x374);

	d2s_test.SSI_write(0x204, 0x68, false);
	d2s_test.SSI_write(0x1FC, 0x3A1);

	d2s_test.SSI_write(0x204, 0x0, false);

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);
	d2s_test.SSI_write(0x78, 0x7F);
	d2s_test.SSI_write(0x20, 0x1);
	d2s_test.SSI_write(0x6C, 0x1);
	d2s::d2s_LABEL_END();
}

void TXIQ_5G_Restore_Module() {
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);

	d2s_test.SSI_write(0x20, 0x0);
	d2s_test.SSI_write(0x6C, 0x0);

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x0);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf
	d2s_test.SSI_write(0xC, 0x2);      //rf
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac
	d2s::d2s_LABEL_END();
}

void DAC_SPUR_Restore_Module() {
	d2s::d2s_LABEL_BEGIN("ssi", LearningMode);
	d2sProtocolSSI d2s_test;
	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x128, 0x0);    //phy
	d2s_test.SSI_write(0x1D0, 0x0);    //phy
	d2s_test.SSI_write(0x24, 0x80);    //phy
	d2s_test.SSI_write(0x28, 0x80);    //phy

	d2s_test.SSI_write(0x90, 0x1B);    //rf
	d2s_test.SSI_write(0x94, 0x1B);    //rf
	d2s_test.SSI_write(0x98, 0x1B);    //rf
	d2s_test.SSI_write(0xA0, 0x1B);    //rf
	d2s_test.SSI_write(0xA4, 0x1B);    //rf
	d2s_test.SSI_write(0xA8, 0x1B);    //rf

	d2s_test.SSI_write(0xB0, 0x1F);    //rf
	d2s_test.SSI_write(0xB4, 0x1F);    //rf
	d2s_test.SSI_write(0x7C, 0x1F);    //rf
	d2s_test.SSI_write(0xB8, 0x1F);    //rf
	d2s_test.SSI_write(0xBC, 0x1F);    //rf
	d2s_test.SSI_write(0x80, 0x1F);    //rf

	d2s_test.SSI_write(0x84, 0x0);      //rf
	d2s_test.SSI_write(0x70, 0x7000);      //rf
	d2s_test.SSI_write(0x20, 0x37);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x20, 0x37);         //rf

	d2s_test.SSI_write(0x8, 0x0);      //rf
	d2s_test.SSI_write(0xC, 0x2);      //rf
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x4, false);

	d2s_test.SSI_write(0x20, 0x0);
	d2s_test.SSI_write(0x6C, 0x0);

	d2s_test.SSI_write(0x200, 0x2000, false); //DAC
	d2s_test.SSI_write(0x202, 0x94, false);
	d2s_test.SSI_write(0x1D8, 0xB975);      //DAC
	d2s_test.SSI_write(0x388, 0x100);    //DAC
	d2s_test.SSI_write(0x38C, 0x4);      //DAC
	d2s_test.SSI_write(0x380, 0x100);    //DAC
	d2s_test.SSI_write(0x384, 0x4);      //DAC

	d2s_test.SSI_write(0x200, 0x2003, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x1D0, 0x0);    //phy

	d2s_test.SSI_write(0x200, 0x2000, false);
	d2s_test.SSI_write(0x202, 0x90, false);
	d2s_test.SSI_write(0x0, 0x0);      //rf
	d2s_test.SSI_write(0x4, 0x0);      //rf
	d2s_test.SSI_write(0x8, 0x0);      //rf
	d2s_test.SSI_write(0xC, 0x2);      //rf
	d2s_test.SSI_write(0x10, 0x2);         //rf

	d2s_test.SSI_write(0x200, 0x2001, false);
	d2s_test.SSI_write(0x202, 0x80, false);
	d2s_test.SSI_write(0x0, 0x0);      //mac
	d2s::d2s_LABEL_END();
}
