#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", InitGeom);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetRotMatrix);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetTransMatrix);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetGeomOffset);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetGeomScreen);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _patch_gte);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80038E20);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", VSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80038FCC);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ResetCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", InterruptCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DMACallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", VSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", VSyncCallbacks);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StopCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", RestartCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CheckCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetIntrMask);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetIntrMask);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800391F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800392D0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800394A0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800395E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039688);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039700);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartIntrVSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003977C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800397E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039814);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartIntrDMA);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039890);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039A10);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039ABC);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StSetRing);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdGetToc);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdGetToc2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdInit);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039DF4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039E30);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039E58);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80039E80);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdStatus);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdLastCom);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdLastPos);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdReset);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdFlush);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdSetDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdComstr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdIntstr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdReadyCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdControl);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdControlF);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdControlB);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdMix);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdGetSector);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdGetSector2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdDataCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdDataSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdIntToPos);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdPosToInt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003A644);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_sync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_ready);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_cw);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_vol);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_flush);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_initvol);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_initintr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_init);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_datasync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_getsector);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_getsector2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CD_set_test_parmnum);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003BCCC);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003BDA4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003BDD8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003C04C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ResetCdStateAndRead);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003C304);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003C4A4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", WaitForCdReady);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003C744);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003C758);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CdRead2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003C7F8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StClearRing);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StUnSetRing);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Data_ready_callback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StGetBackloc);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StSetStream);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StFreeRing);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Init_ring_status);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StGetNext);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StSetMask);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StCdInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003D570);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003D59C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTReset);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTGetEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTPutEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTBufSize);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTin);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTout);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTinSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCToutSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTinCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCToutCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DA04);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DAF4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DB84);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DC10);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DCA4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DD38);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003DD50);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTvlcSize);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DecDCTvlc);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", FlushCache);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003E17C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SystemError);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DeliverEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", OpenEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", CloseEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", EnableEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DisableEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ReturnFromException);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ResetEntryInt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", HookEntryInt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", UnDeliverEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", EnterCriticalSection);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ExitCriticalSection);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetSp);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Open);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ChangeClearPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ChangeClearRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StopRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ResetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Firstfile);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003E600);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Firstfile2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Puts_A63);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", setjmp);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", strcat);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", strcmp);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", strncmp);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", strcpy);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", memset);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", printf);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", LoadTPage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", LoadClut);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", LoadClut2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDefDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDefDispEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003EA44);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GsGetWorkBase);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDumpFnt);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", FntLoad);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", FntOpen);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", FntFlush);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", FntPrint);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", strlen);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ResetGraph);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetGraphDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetGraphQueue);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetGraphDebug);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DrawSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDispMask);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DrawSync);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8003F8E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ClearImage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ClearImage2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", LoadImage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StoreImage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", MoveImage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ClearOTag);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ClearOTagR);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DrawPrim);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DrawOTag);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PutDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DrawOTagEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PutDispEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetDispEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetODE);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetTexWindow);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDrawArea);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDrawOffset);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetPriority);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDrawStp);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDrawMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800409A0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040C10);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040C30);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040CC8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040D60);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040D7C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040DFC);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040E14);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80040EF4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041124);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041360);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800415E0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041604);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041618);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041658);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800416A0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800416D0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800416F4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800419A4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041C04);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041D54);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041E90);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80041EC4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80042008);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", LoadImage2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StoreImage2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", MoveImage2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DrawOTag2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800424C0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800424E8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GPU_cw);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", memcpy);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", OpenTIM);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ReadTIM);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", OpenTMD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ReadTMD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80042890);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800429A8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80042B1C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetTPage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetClut);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", AddPrim);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", TermPrim);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetPrimitiveSemiTrans);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetShadeTexFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetPolyFT4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetPolyG4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetSprt8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetSprt16);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetSpritePrimitive);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetTilePrimitive);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetLineF2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetLineF3);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetDrawTPage);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PCopen);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PCclose);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PCcreat);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", Start);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", __main);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", __do_global_dtors);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", InitHeap);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PCinit);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PCread);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _SN_write);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _card_info);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _card_write);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _new_card);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartMemoryCardSystem);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800443EC);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetInitPadFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", ReadInitPadFlag);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PAD_init);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", InitPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StopPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800445BC);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80044634);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_8004466C);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800446D4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", InitPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StopPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", PAD_init2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SysEnqIntRP);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SysDeqIntRP);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", EnablePAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", DisablePAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _patch_pad);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _remove_ChgclrPAD);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", InitCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StartCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", StopCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800448E4);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80044928);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _patch_card);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _patch_card2);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _copy_memcard_patch);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80044A88);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _SpuInit);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuStart);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_init);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80044EE8);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_FiDMA);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_Fr_);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_t);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_Fw);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_Fr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_FsetRXX);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_FsetRXXa);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_FgetRXXa);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_FsetPCR);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_800456F0);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80045718);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_Fw1ts);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetSpuDmaCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SsUtReverbOff);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", QuitSpu);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuInitMalloc);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetNoiseClock);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetReverb);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _SpuIsInAllocateArea);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _SpuIsInAllocateArea_);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetIRQ);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80045C48);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetIRQAddr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetIRQCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _SpuCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuRead);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuWriteWithCallbackCheck);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetTransferStartAddr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetTransferMode);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SetSpuTransferCallback);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuGetVoiceEnvelope);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuSetReverbModeType);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", _spu_setReverbAttr);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", SpuClearReverbWorkArea);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", WaitEvent);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", func_80046708);

INCLUDE_ASM("asm/jp/nonmatchings/main/psxsdk", GetCurrentReverbMode);
