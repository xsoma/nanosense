#pragma once

#include "Structs.hpp"
#include "helpers/VMTManager.hpp"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma warning (disable: 4138) // condition expression is constant

extern std::unique_ptr<ShadowVTManager> g_pClientStateHook;
extern std::unique_ptr<ShadowVTManager> g_pNetChannelHook;

/* PaintTraverse defs */
typedef void(__thiscall *PaintTraverse_t)(void*, unsigned int, bool, bool);
extern PaintTraverse_t o_PaintTraverse;

/* CreateMove defs */
typedef bool(__thiscall *CreateMove_t)(IClientMode*, float, CUserCmd*);
extern CreateMove_t o_CreateMove;

/* EndScene defs */
typedef long(__stdcall *EndScene_t)(IDirect3DDevice9*);
extern EndScene_t o_EndScene;

/* Reset defs */
typedef long(__stdcall *Reset_t)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
extern Reset_t o_Reset;

/* FrameStageNotify defs */
typedef void(__stdcall *FrameStageNotify_t)(ClientFrameStage_t);
extern FrameStageNotify_t o_FrameStageNotify;

/* FireEventClientSide defs */
typedef bool(__thiscall *FireEventClientSide_t)(void*, IGameEvent*);
extern FireEventClientSide_t o_FireEventClientSide;

/* BeginFrame defs */
typedef void(__thiscall *BeginFrame_t)(void*, float);
extern BeginFrame_t o_BeginFrame;

/* OverrideView defs */
typedef int(__stdcall *OverrideView_t)(CViewSetup*);
extern OverrideView_t o_OverrideView;

/* SetKeyCodeState defs */
typedef void(__thiscall* SetKeyCodeState_t) (void*, ButtonCode_t, bool);
extern SetKeyCodeState_t o_SetKeyCodeState;

/* SetMouseCodeState defs */
typedef void(__thiscall* SetMouseCodeState_t) (void*, ButtonCode_t, MouseCodeState_t);
extern SetMouseCodeState_t o_SetMouseCodeState;

/* FireBullets defs */
typedef void(__thiscall* FireBullets_t)(C_TEFireBullets*, DataUpdateType_t);
extern FireBullets_t o_FireBullets;

/* InPrediction defs */
typedef bool(__thiscall* InPrediction_t)(void*);
extern InPrediction_t o_OriginalInPrediction;

/* TempEntities defs */
typedef bool(__thiscall *TempEntities_t)(void*, void*/*SVC_TempEntities*/);
extern TempEntities_t o_TempEntities;

/* SceneEnd defs */
typedef void(__thiscall *SceneEnd_t)(void*);
extern SceneEnd_t o_SceneEnd;

/* SetupBones defs */
typedef bool(__thiscall *SetupBones_t)(void*, matrix3x4_t*, int, int, float);
extern SetupBones_t o_SetupBones;

/* sv_cheats getbool defs */
typedef bool(__thiscall *GetBool_t)(void*);
extern GetBool_t o_GetBool;

/* GetViewmodelFov defs */
typedef float(__thiscall *GetViewmodelFov_t)(void*);
extern GetViewmodelFov_t o_GetViewmodelFov;

/* RunCommand defs */
typedef void(__thiscall *RunCommand_t)(void*, C_BasePlayer*, CUserCmd*, IMoveHelper*);
extern RunCommand_t o_RunCommand;

/* SendDatagram defs */
typedef int(__thiscall *SendDatagram_t)(void*, bf_write*);
extern SendDatagram_t o_SendDatagram;

/* WriteUsercmdDeltaToBuffer defs */
typedef bool(__thiscall *WriteUsercmdDeltaToBuffer_t)(IBaseClientDLL*, int, bf_write*, int, int, bool);
extern WriteUsercmdDeltaToBuffer_t o_WriteUsercmdDeltaToBuffer;

typedef void(__thiscall* DrawModelExecute_t)(void*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t*);
extern DrawModelExecute_t o_DrawModelExecute;

typedef bool(__thiscall* DispatchUserMessage_t)(void*, int, int, int, bf_read&);
extern DispatchUserMessage_t o_DispatchUserMessage;

/* IsBoxVisible defs */
typedef int(__stdcall *IsBoxVisible_t)(const Vector&, const Vector&);
extern IsBoxVisible_t o_IsBoxVisible;

/* IsHLTV defs */
typedef bool(__thiscall *IsHLTV_t)(void*);
extern IsHLTV_t o_IsHLTV;

typedef void(__thiscall *CusorFunc_t)(void*);
extern CusorFunc_t o_LockCursor;
extern CusorFunc_t o_UnlockCursor;

namespace Handlers
{
	void __fastcall PaintTraverse_h(void *thisptr, void*, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
	bool __stdcall CreateMove_h(float smt, CUserCmd *userCMD);
	void __fastcall LockCursor_h(void* ecx, void*);
	void __stdcall FrameStageNotify_h(ClientFrameStage_t stage);
	bool __fastcall FireEventClientSide_h(void *thisptr, void*, IGameEvent *gEvent);
	void __fastcall BeginFrame_h(void *thisptr, void*, float ft);
	void __stdcall OverrideView_h(CViewSetup* pSetup);
	void __fastcall SetKeyCodeState_h(void* thisptr, void* EDX, ButtonCode_t code, bool bDown);
	void __fastcall SetMouseCodeState_h(void* thisptr, void* EDX, ButtonCode_t code, MouseCodeState_t state);
	void __stdcall TEFireBulletsPostDataUpdate_h(DataUpdateType_t updateType);
	bool __stdcall InPrediction_h();
	bool __fastcall TempEntities_h(void* ECX, void* EDX, void* msg);
	void __fastcall SceneEnd_h(void* thisptr, void* edx);
	bool __fastcall SetupBones_h(void* ECX, void* EDX, matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	bool __fastcall GetBool_SVCheats_h(PVOID pConVar, int edx);
	float __fastcall GetViewModelFov_h(void* ECX, void* EDX);
	void __fastcall RunCommand_h(void* ECX, void* EDX, C_BasePlayer* player, CUserCmd* cmd, IMoveHelper* helper);
	bool __fastcall DispatchUserMessage_h(void* thisptr, void*, int msg_type, int unk1, int nBytes, bf_read& msg_data);
	int __fastcall SendDatagram_h(void *ECX, void *EDX, bf_write *data);
	bool __fastcall IsHLTV_h(void *ECX, void *EDX);
	LRESULT __stdcall WndProc_h(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef INSTANT_DEFUSE_PLANT_EXPLOIT
	bool __fastcall WriteUsercmdDeltaToBuffer_h(IBaseClientDLL *ECX, void *EDX, int nSlot, bf_write *buf, int from, int to, bool isNewCmd);
#endif

	int __stdcall IsBoxVisible_h(const Vector &mins, const Vector &maxs);
}

extern HWND window;
extern WNDPROC oldWindowProc;
extern bool pressedKey[256];




#include "vsonyp0wer/vsonyp0wer.h"
#include "vsonyp0wer/vsonyp0wer_impl_dx9.h"
#include "vsonyp0wer/vsonyp0wer_impl_win32.h"


class idirect3ddevice9 : public Singleton<idirect3ddevice9>
{
	typedef HRESULT(__stdcall* reset_t)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	typedef HRESULT(__stdcall* end_scene_t)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
public:
	void ini(IDirect3DDevice9* fix);
	static IDirect3DDevice9* direct_device();
private:
	HWND window;
	WNDPROC original_proc;
	reset_t _reset;
	end_scene_t _end_scene;
	static HRESULT __stdcall reset(IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* param);
	static HRESULT __stdcall end_scene(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
	static LRESULT __stdcall wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#define d3d9hook idirect3ddevice9::Get()
extern vsonyp0wer_IMPL_API LRESULT vsonyp0wer_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
