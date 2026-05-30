//----------------------------------------------------------------------------
// EnsoniqFS plugin for TotalCommander
//
// DISK I/O FUNCTIONS header file
//----------------------------------------------------------------------------
//
// (c) 2006 Thoralt Franz
//
// MSVC PATCH (EnsoniqFS_VS project):
//   This file shadows ensoniqfs\disk.h in the include search order.
//   Changes from the original:
//     1. DLLEXPORT is NOT redefined here (it is defined in msvc_compat.h
//        as empty, so the .def file drives all exports — no __declspec
//        on declarations needed).
//     2. The return type of ScanDevices is written as "DISK*" so that
//        __stdcall modifies the function, not the pointer, fixing C2165.
//----------------------------------------------------------------------------
//
// License: GPL v2 (unchanged from original)
//----------------------------------------------------------------------------

#ifndef _DISK_H_
#define _DISK_H_

#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include "omniflop.h"
#include "diskstructure.h"

/* DLLEXPORT is intentionally NOT redefined here.
   msvc_compat.h (forced-include) already defines it as empty so that
   declarations in EnsoniqFS.h don't conflict with fsplugin.h.
   Actual exports are driven by EnsoniqFS.def. */

#define READ_AHEAD 256
#define MAX_IMAGE_FILES 16

//----------------------------------------------------------------------------
// Prototypes
//----------------------------------------------------------------------------
BOOL UnlockMediaType(const char *szDrive, BOOL bLog);
BOOL LockMediaType(const char *szDrive, MEDIA_TYPE MediaType, BOOL bLog);
BOOL EnableExtendedFormats(const char *szDrive, BOOL bEnable);
void MakeLegalName(char *cName);
void GetShortEnsoniqFiletype(unsigned char ucType, char *cType);
int ReadBlock(DISK *pDisk, DWORD dwBlock, unsigned char *ucBuf);
int GetContiguousBlocks(DISK *pDisk, DWORD dwNumBlocks);
int GetNextFreeBlock(DISK *pDisk, int iStartingBlock);
int AdjustFreeBlocks(DISK *pDisk, int iAdjust);
int DetectImageFileType(HANDLE h, unsigned char *ucReturnBuf,
    DWORD *dwDataOffset, DWORD *dwGieblerMapOffset);

//----------------------------------------------------------------------------
// DLL exports
// NOTE: DLLEXPORT expands to nothing; .def file handles the exports.
// FIX: ScanDevices return type is "DISK* __stdcall" (pointer outside
//      __stdcall) to avoid C2165 "left-side modifier cannot modify
//      pointers to data".
//----------------------------------------------------------------------------
DLLEXPORT void   __stdcall FreeDiskList(int iShowProgress, DISK *pRoot);
DLLEXPORT int    __stdcall ReadBlocks(DISK *pDisk, DWORD dwBlock,
                     DWORD dwNumBlocks, unsigned char *ucBuf);
DLLEXPORT int    __stdcall WriteBlocks(DISK *pDisk, DWORD dwBlock,
                     DWORD dwNumBlocks, unsigned char *ucBuf);
DLLEXPORT int    __stdcall WriteBlocksUncached(DISK *pDisk, DWORD dwBlock,
                     DWORD dwNumBlocks, unsigned char *ucBuf);
DLLEXPORT int    __stdcall GetFATEntry(DISK *pDisk, DWORD dwBlock);
DLLEXPORT int    __stdcall SetFATEntry(DISK *pDisk, DWORD dwBlock,
                     DWORD dwNewValue);
DLLEXPORT DISK*  __stdcall ScanDevices(DWORD dwAllowNonEnsoniqFilesystems);
DLLEXPORT int    __stdcall GetUsageCount(void);

#endif /* _DISK_H_ */
