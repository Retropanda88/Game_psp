#ifndef PSP_H_
#define PSP_H_

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

PSP_MODULE_INFO("GAME", 0, 1, 1);
#define printfpsp pspDebugScreenPrintf

PSP_HEAP_SIZE_KB(20480);
int ExitCallback(int Arg1, int Arg2, void *Common)
{
 sceKernelExitGame();
 return 0;
}

int CallbackThread(SceSize Args, void *Argp)
{
 int CallbackId = sceKernelCreateCallback("Exit Callback", ExitCallback, NULL);
 sceKernelRegisterExitCallback(CallbackId);
 sceKernelSleepThreadCB();
 return 0;
}

int SetupCallbacks(void)
{
 int ThreadId = sceKernelCreateThread("update_thread",CallbackThread,0x11,0xFA0,0,0);
 if(ThreadId >= 0) sceKernelStartThread(ThreadId,0,0);
 return ThreadId;
}

void exit_psp()
{
	sceKernelSleepThread();
}

void init_psp()
{
	SetupCallbacks();
}

//SDL_Joystick *pad; no funciona el joystick en psp
SceCtrlData pad;

void psp_joystick_update(){
	sceCtrlReadBufferPositive(&pad, 1);
}


#endif