#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#include <sys/ppu_thread.h>
#include <sys/timer.h>
SYS_MODULE_INFO( xboxStyle, 0, 1, 1);
SYS_MODULE_START( main );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _xboxStyle_export_function, LIBNAME );
typedef int (*cBuf_AddText)(int client,char* text);
typedef int (*Key_IsDown)(int ClientNum, int ButtonEnum);
//printf = (int(*)(const char*, ...))find_export("stdc", 0xC01D9F97);
int dpadUp()
{
	Key_IsDown Key_Down = (Key_IsDown)0x0018EEF8;
	if(Key_Down(0,0x16))
	{
		return 1;
	}
	else return 0;
}
extern "C" int _xboxStyle_export_function(void)
{
    return CELL_OK;
}
void run(uint64_t)
{
	cBuf_AddText Addtext = (cBuf_AddText) 0x002B1734;
	for(;;)
	{
	if(dpadUp())
	{
		Addtext(0,"cg_fov 100");
	}
	 sys_timer_usleep(1000);
	}
}
 void ppu_thread_exit()
{
	system_call_1(41, 0);
}

 int main(size_t args, void *argp)
{
	sys_ppu_thread_t id;
	sys_ppu_thread_create(&id, run, 0, 3000, 0x2000, SYS_PPU_THREAD_CREATE_JOINABLE, "button_thread");
	ppu_thread_exit();
    return SYS_PRX_RESIDENT;
}
