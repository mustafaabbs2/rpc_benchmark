# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=test - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to test - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "test - Win32 Release" && "$(CFG)" != "test - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "test - Win32 Debug"

!IF  "$(CFG)" == "test - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f test.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "test.exe"
# PROP BASE Bsc_Name "test.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "test.exe"
# PROP Bsc_Name "test.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f test.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "test.exe"
# PROP BASE Bsc_Name "test.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "test.exe"
# PROP Bsc_Name "test.bsc"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ENDIF 

################################################################################
# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"

!IF  "$(CFG)" == "test - Win32 Release"

".\test.exe" : 
   NMAKE /f Makefile

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

".\test.exe" : 
   NMAKE /f Makefile

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MAKEFILE

!IF  "$(CFG)" == "test - Win32 Release"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
