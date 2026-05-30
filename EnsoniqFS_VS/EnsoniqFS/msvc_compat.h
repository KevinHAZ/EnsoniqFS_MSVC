/*
 * msvc_compat.h  —  MSVC compatibility shim for EnsoniqFS
 *
 * Injected via /FI (ForcedIncludeFiles) so no repo source files need editing.
 *
 * Problems addressed
 * ==================
 *
 * 1. DLLEXPORT redeclaration conflict
 *    fsplugin.h declares all Fs* without __declspec(dllexport).
 *    disk.h and EnsoniqFS.h both redefine DLLEXPORT = __declspec(dllexport)
 *    and then re-declare those functions with it — MSVC rejects adding
 *    dllexport in a redeclaration (C2375).
 *    Fix: define DLLEXPORT as empty here; patched disk.h and EnsoniqFS.h
 *    in the project folder shadow the repo copies and omit the redeclaration.
 *    The .def file handles all exports.
 *
 * 2. disk.h ScanDevices pointer placement → C2165
 *    Original:  DLLEXPORT DISK __stdcall *ScanDevices(...)
 *    MSVC reads __stdcall as a data-pointer modifier → C2165.
 *    Fixed in the patched disk.h:  DLLEXPORT DISK* __stdcall ScanDevices(...)
 *
 * 3. #warning in EnsoniqFS.c → C1021 (fatal error under MSVC)
 *    Handled by the pre-build PowerShell step in the .vcxproj which
 *    produces a cleaned copy of EnsoniqFS.c in the intermediate directory.
 *
 * 4. Pointer-to-DWORD truncation (x64 porting TBD)  — C4311/C4302
 */

#ifndef MSVC_COMPAT_H
#define MSVC_COMPAT_H

/* ── 1. Neutralise DLLEXPORT ── */
#define DLLEXPORT   /* exported via .def */

/* ── 2/4. Suppress warnings ── */
#ifdef _MSC_VER
#  pragma warning(disable: 4311)  /* pointer truncation to DWORD  */
#  pragma warning(disable: 4302)  /* truncation                   */
#  pragma warning(disable: 4047)  /* indirection levels differ    */
#endif

#endif /* MSVC_COMPAT_H */
