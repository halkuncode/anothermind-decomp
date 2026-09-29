#include "common.h"

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", InitGeom);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetRotMatrix);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetTransMatrix);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetGeomOffset);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetGeomScreen);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _patch_gte);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80038E20);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", VSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80038FCC);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ResetCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", InterruptCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DMACallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", VSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", VSyncCallbacks);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StopCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", RestartCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CheckCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetIntrMask);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetIntrMask);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800391F8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800392D0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800394A0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800395E8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039688);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039700);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartIntrVSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003977C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800397E8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039814);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartIntrDMA);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039890);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039A10);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039ABC);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StSetRing);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdGetToc);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdGetToc2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdInit);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039DF4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039E30);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039E58);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80039E80);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdStatus);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdMode);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdLastCom);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdLastPos);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdReset);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdFlush);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdSetDebug);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdComstr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdIntstr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdReady);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdReadyCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdControl);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdControlF);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdControlB);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdMix);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdGetSector);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdGetSector2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdDataCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdDataSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdIntToPos);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdPosToInt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003A644);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_sync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_ready);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_cw);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_vol);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_flush);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_initvol);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_initintr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_init);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_datasync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_getsector);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_getsector2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CD_set_test_parmnum);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003BCCC);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003BDA4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003BDD8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003C04C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ResetCdStateAndRead);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003C304);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003C4A4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", WaitForCdReady);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003C744);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003C758);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CdRead2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003C7F8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StClearRing);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StUnSetRing);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Data_ready_callback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StGetBackloc);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StSetStream);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StFreeRing);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Init_ring_status);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StGetNext);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StSetMask);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StCdInterrupt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003D570);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003D59C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTReset);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTGetEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTPutEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTBufSize);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTin);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTout);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTinSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCToutSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTinCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCToutCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DA04);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DAF4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DB84);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DC10);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DCA4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DD38);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003DD50);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTvlcSize);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DecDCTvlc);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", FlushCache);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003E17C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SystemError);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DeliverEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", OpenEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", CloseEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", EnableEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DisableEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ReturnFromException);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ResetEntryInt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", HookEntryInt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", UnDeliverEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", EnterCriticalSection);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ExitCriticalSection);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetSp);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Open);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ChangeClearPAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ChangeClearRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StopRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ResetRCnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Firstfile);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003E600);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Firstfile2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Puts_A63);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", setjmp);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", strcat);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", strcmp);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", strncmp);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", strcpy);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", memset);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", printf);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", LoadTPage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", LoadClut);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", LoadClut2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDefDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDefDispEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003EA44);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GsGetWorkBase);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDumpFnt);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", FntLoad);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", FntOpen);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", FntFlush);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", FntPrint);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", strlen);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ResetGraph);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetGraphDebug);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetGraphQueue);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetGraphDebug);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DrawSyncCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDispMask);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DrawSync);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8003F8E8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ClearImage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ClearImage2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", LoadImage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StoreImage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", MoveImage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ClearOTag);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ClearOTagR);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DrawPrim);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DrawOTag);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PutDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DrawOTagEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PutDispEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetDispEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetODE);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetTexWindow);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDrawArea);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDrawOffset);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetPriority);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDrawStp);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDrawMode);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDrawEnv);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800409A0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040C10);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040C30);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040CC8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040D60);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040D7C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040DFC);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040E14);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80040EF4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041124);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041360);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800415E0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041604);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041618);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041658);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800416A0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800416D0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800416F4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800419A4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041C04);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041D54);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041E90);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80041EC4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80042008);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", LoadImage2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StoreImage2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", MoveImage2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DrawOTag2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800424C0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800424E8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GPU_cw);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", memcpy);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", OpenTIM);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ReadTIM);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", OpenTMD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ReadTMD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80042890);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800429A8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80042B1C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetTPage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetClut);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", AddPrim);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", TermPrim);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetPrimitiveSemiTrans);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetShadeTexFlag);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetPolyFT4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetPolyG4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetSprt8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetSprt16);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetSpritePrimitive);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetTilePrimitive);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetLineF2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetLineF3);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetDrawTPage);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PCopen);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PCclose);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PCcreat);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", Start);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", __main);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", __do_global_dtors);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", InitHeap);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PCinit);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PCread);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _SN_write);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _card_info);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _card_write);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _new_card);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartMemoryCardSystem);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800443EC);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetInitPadFlag);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", ReadInitPadFlag);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PAD_init);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", InitPAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartPAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StopPAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800445BC);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80044634);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_8004466C);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800446D4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", InitPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StopPAD2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", PAD_init2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SysEnqIntRP);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SysDeqIntRP);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", EnablePAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", DisablePAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _patch_pad);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _remove_ChgclrPAD);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", InitCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StartCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", StopCARD2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800448E4);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80044928);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _patch_card);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _patch_card2);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _copy_memcard_patch);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80044A88);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _SpuInit);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuStart);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_init);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80044EE8);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_FiDMA);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_Fr_);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_t);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_Fw);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_Fr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_FsetRXX);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_FsetRXXa);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_FgetRXXa);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_FsetPCR);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_800456F0);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80045718);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_Fw1ts);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetSpuDmaCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SsUtReverbOff);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", QuitSpu);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuInitMalloc);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetNoiseClock);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetReverb);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _SpuIsInAllocateArea);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _SpuIsInAllocateArea_);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetIRQ);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80045C48);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetIRQAddr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetIRQCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _SpuCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuRead);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuWriteWithCallbackCheck);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetTransferStartAddr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetTransferMode);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SetSpuTransferCallback);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuGetVoiceEnvelope);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuSetReverbModeType);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", _spu_setReverbAttr);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", SpuClearReverbWorkArea);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", WaitEvent);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", func_80046708);

INCLUDE_ASM("asm/jp/nonmatchings/psxsdk", GetCurrentReverbMode);
