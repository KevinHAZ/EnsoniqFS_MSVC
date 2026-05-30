//----------------------------------------------------------------------------
// EnsoniqFS plugin for TotalCommander
//
// MAIN MODULE header file
//----------------------------------------------------------------------------
//
// (c) 2006 Thoralt Franz
//
// MSVC PATCH (EnsoniqFS_VS project):
//   This file shadows ensoniqfs\EnsoniqFS.h in the include search order.
//   Change from the original:
//     The Fs* function declarations no longer carry DLLEXPORT.
//     fsplugin.h already declared them without __declspec(dllexport).
//     MSVC (unlike GCC) forbids adding dllexport in a redeclaration.
//     The .def file (EnsoniqFS.def) drives all exports instead.
//----------------------------------------------------------------------------
//
// License: GPL v2 (unchanged from original)
//----------------------------------------------------------------------------

#ifndef _ENSONIQFS_H_
#define _ENSONIQFS_H_

/* DLLEXPORT is defined as empty by msvc_compat.h (forced-include).
   We keep the macro usage below so the file still compiles identically
   under GCC if needed. */

#define FILE_TYPE_EMPTY           0x00
#define FILE_TYPE_DIRECTORY       0x02
#define FILE_TYPE_EPS_BANK        0x04
#define FILE_TYPE_PARENT_DIRECTORY 0x08
#define FILE_TYPE_EPS16_BANK      0x17
#define FILE_TYPE_ASR_SONG        0x1D
#define FILE_TYPE_ASR_BANK        0x1E
#define FILE_TYPE_ASR_AUDIOTRACK  0x1F

//----------------------------------------------------------------------------
// structs for Ensoniq directory
//----------------------------------------------------------------------------
typedef struct _ENSONIQDIRENTRY
{
    char cName[13], cLegalName[13];
    unsigned char ucType, ucMultiFileIndex;
    DWORD dwContiguous, dwStart, dwLen;
} ENSONIQDIRENTRY;

typedef struct _VIRTUALWAVEFILE
{
    char cName[13], cLegalName[13];
    DWORD dwContiguous1, dwStart1, dwLen1;
    DWORD dwContiguous2, dwStart2, dwLen2;
    unsigned char ucIsStereo;
} VIRTUALWAVEFILE;

typedef struct _ENSONIQDIR
{
    ENSONIQDIRENTRY Entry[39];
    unsigned char ucDirectory[1024];
    DWORD dwDirectoryBlock;
    VIRTUALWAVEFILE VirtualWaveEntry[58]; /* max. 39 waves + 19 stereo pairs */
} ENSONIQDIR;

//----------------------------------------------------------------------------
// handle struct for find operations
//----------------------------------------------------------------------------
typedef struct _FIND_HANDLE
{
    struct _FIND_HANDLE *pNext, *pPrevious;
    char cPath[260];
    int iNextDirIndex;
    ENSONIQDIR EnsoniqDir;
    DISK *pDisk;
} FIND_HANDLE;

//----------------------------------------------------------------------------
// file type constants
//----------------------------------------------------------------------------
#define FILETYPE_UNKNOWN  0
#define FILETYPE_GKH      1
#define FILETYPE_PLAIN    2
#define FILETYPE_MODE1CD  3
#define FILETYPE_GIEBLER  4

//----------------------------------------------------------------------------
// copy mode constants
//----------------------------------------------------------------------------
#define COPY_DOS     0
#define COPY_ENSONIQ 1

//----------------------------------------------------------------------------
// prototypes
//----------------------------------------------------------------------------
void AddToImageList(char *cName);

/* prototypes for usage in bank.c */
void upcase(char *c);
int ReadDirectoryFromPath(FIND_HANDLE *pHandle, unsigned char ucShowWarning);
DISK *GetDiskFromPath(char *cPath);
int ReadDirectory(DISK *pDisk, ENSONIQDIR *pDir, unsigned char ucShowWarning);

//----------------------------------------------------------------------------
// DLL exports
// MSVC PATCH: DLLEXPORT removed from Fs* declarations.
//   fsplugin.h already declared these without __declspec(dllexport).
//   MSVC rejects adding it in a redeclaration (C2375).
//   Exports are handled by EnsoniqFS.def.
//----------------------------------------------------------------------------
void __stdcall FsSetDefaultParams(FsDefaultParamStruct* dps);
int  __stdcall FsInit(int PluginNr, tProgressProc pProgressProc,
                    tLogProc pLogProc, tRequestProc pRequestProc);
HANDLE __stdcall FsFindFirst(char* cPath, WIN32_FIND_DATA *FindData);
BOOL   __stdcall FsFindNext(HANDLE Handle, WIN32_FIND_DATA *FindData);
int    __stdcall FsFindClose(HANDLE Handle);
void   __stdcall FsGetDefRootName(char* cDefRootName, int iMaxLen);
int    __stdcall FsGetFile(char* RemoteName, char* LocalName,
                    int CopyFlags, RemoteInfoStruct* ri);
BOOL   __stdcall FsMkDir(char* Path);
BOOL   __stdcall FsRemoveDir(char* RemoteName);
BOOL   __stdcall FsDeleteFile(char* RemoteName);
int    __stdcall FsPutFile(char* LocalName, char* RemoteName,
                    int CopyFlags);
void   __stdcall FsStatusInfo(char* RemoteDir, int InfoStartEnd,
                    int InfoOperation);
int    __stdcall FsRenMovFile(char* OldName, char* NewName, BOOL Move,
                    BOOL OverWrite, RemoteInfoStruct* ri);
int    __stdcall FsExecuteFile(HWND MainWin, char* RemoteName,
                    char* Verb);
int    __stdcall FsExtractCustomIcon(char* RemoteName,
                    int ExtractFlags,
                    HICON* TheIcon);

#endif /* _ENSONIQFS_H_ */
