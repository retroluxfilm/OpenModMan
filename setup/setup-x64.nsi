; Open Mod Manager NSIS script for x64 version

;--------------------------------

!include MUI2.nsh
!include OpenModMan.nsh

!define  AAP_ARCH         "x64"


InstallDir                "$PROGRAMFILES64\${APP_NAME}"
Name                      "${APP_NAME} ${AAP_MAJ}.${AAP_MIN}.${AAP_REV}"
OutFile                   "${APP_SHORT_NAME}_${AAP_MAJ}-${AAP_MIN}-${AAP_REV}-${AAP_ARCH}_setup.exe"
RequestExecutionLevel     admin
LicenseData               "..\LICENSE.TXT"

; Registry key to check for directory (so if you install again, it will
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\${APP_REG_NAME}" "Install_Dir"

; Sets the text that is shown at the bottom of the install window
BrandingText " "

; Sets the background color of the license data.
LicenseBkColor /windows

; Use modern Windows theme
XPStyle on

ShowInstDetails show
ShowUnInstDetails show

!define MUI_FINISHPAGE_RUN "$INSTDIR\${APP_EXE_NAME}.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Start ${APP_NAME}"
!define MUI_WELCOMEFINISHPAGE_BITMAP "..\res\images\setup_splash.bmp"

;--------------------------------

; Pages
!insertmacro MUI_PAGE_LICENSE "..\LICENSE.TXT"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

;--------------------------------

; The stuff to install
Section "Install (required)"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put file there
  File "/oname=${APP_EXE_NAME}.exe"     "${REL_64_EXE}"

  File "/oname=libssl-1_1-x64.dll"      "${SSL_64_DLL}"
  File "/oname=libcrypto-1_1-x64.dll"   "${CRYPTO_64_DLL}"
  File "/oname=libcurl-x64.dll"         "${CURL_64_DLL}"

  file "/oname=omm_icon.ico"            "${OMM_ICO}"
  file "/oname=omb_icon.ico"            "${OMB_ICO}"
  file "/oname=omx_icon.ico"            "${OMX_ICO}"
  file "/oname=ozp_icon.ico"            "${OZP_ICO}"
  file "/oname=ozb_icon.ico"            "${OZB_ICO}"

  File "/oname=LICENSE.TXT"             "..\LICENSE.TXT"
  File "/oname=CREDITS.TXT"             "..\CREDITS.TXT"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\${APP_REG_NAME} "Install_Dir" "$INSTDIR"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "DisplayName" "${APP_NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "DisplayIcon" "$INSTDIR\${APP_EXE_NAME}.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "DisplayVersion" "${AAP_MAJ}.${AAP_MIN}.${AAP_REV} (${AAP_ARCH})"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "Publisher" "${APP_PUBLISHER}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}" "NoRepair" 1
  WriteUninstaller "$INSTDIR\uninstall.exe"

  ; file Association
  WriteRegStr HKCR ".omc" "" "${APP_REG_NAME}.Context"
  WriteRegStr HKCR ".omc" "Content Type" "text/xml"
  WriteRegStr HKCR "${APP_REG_NAME}.Context\DefaultIcon" "" "$INSTDIR\omm_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.Context" "" "${APP_NAME} Context"
  WriteRegStr HKCR "${APP_REG_NAME}.Context\shell" "" "open"
  WriteRegStr HKCR "${APP_REG_NAME}.Context\shell\open\command" "" '"$INSTDIR\${APP_EXE_NAME}.exe" "%1"'

  WriteRegStr HKCR ".ozp" "" "${APP_REG_NAME}.Package"
  WriteRegStr HKCR ".ozp" "Content Type" "application/x-zip-compressed"
  WriteRegStr HKCR "${APP_REG_NAME}.Package\DefaultIcon" "" "$INSTDIR\ozp_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.Package" "" "${APP_NAME} Zip Package"

  WriteRegStr HKCR ".ozb" "" "${APP_REG_NAME}.Backup"
  WriteRegStr HKCR ".ozb" "Content Type" "application/x-zip-compressed"
  WriteRegStr HKCR "${APP_REG_NAME}.Backup\DefaultIcon" "" "$INSTDIR\ozb_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.Backup" "" "${APP_NAME} Zip Backup"

  WriteRegStr HKCR ".oml" "" "${APP_REG_NAME}.Location"
  WriteRegStr HKCR ".oml" "Content Type" "text/xml"
  WriteRegStr HKCR "${APP_REG_NAME}.Location\DefaultIcon" "" "$INSTDIR\omx_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.Location" "" "${APP_NAME} Location Definition"

  WriteRegStr HKCR ".omp" "" "${APP_REG_NAME}.Location"
  WriteRegStr HKCR ".omp" "Content Type" "text/xml"
  WriteRegStr HKCR "${APP_REG_NAME}.PkgDef\DefaultIcon" "" "$INSTDIR\omx_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.PkgDef" "" "${APP_NAME} Package Definition"

  WriteRegStr HKCR ".omk" "" "${APP_REG_NAME}.Location"
  WriteRegStr HKCR ".omk" "Content Type" "text/xml"
  WriteRegStr HKCR "${APP_REG_NAME}.BckDef\DefaultIcon" "" "$INSTDIR\omx_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.BckDef" "" "${APP_NAME} Backup Definition"

  WriteRegStr HKCR ".omb" "" "${APP_REG_NAME}.Batch"
  WriteRegStr HKCR ".omb" "Content Type" "text/xml"
  WriteRegStr HKCR "${APP_REG_NAME}.Batch\DefaultIcon" "" "$INSTDIR\omb_icon.ico"
  WriteRegStr HKCR "${APP_REG_NAME}.Batch" "" "${APP_NAME} Batch Definition"

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\${APP_NAME}"
  CreateShortcut "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE_NAME}.exe" "" "$INSTDIR\${APP_EXE_NAME}.exe" 0

SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_REG_NAME}"
  DeleteRegKey HKLM SOFTWARE\${APP_REG_NAME}

  ; Remove files and uninstaller
  Delete $INSTDIR\*.*

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\${APP_NAME}\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\${APP_NAME}"
  RMDir "$INSTDIR"

  ; Remove file association
  DeleteRegKey HKCR ".omc"
  DeleteRegKey HKCR "${APP_REG_NAME}.Context"

  DeleteRegKey HKCR ".ozp"
  DeleteRegKey HKCR "${APP_REG_NAME}.Package"

  DeleteRegKey HKCR ".ozb"
  DeleteRegKey HKCR "${APP_REG_NAME}.Backup"

  DeleteRegKey HKCR ".oml"
  DeleteRegKey HKCR "${APP_REG_NAME}.Location"

  DeleteRegKey HKCR ".omp"
  DeleteRegKey HKCR "${APP_REG_NAME}.PkgDef"

  DeleteRegKey HKCR ".omk"
  DeleteRegKey HKCR "${APP_REG_NAME}.BckDef"

  DeleteRegKey HKCR ".omb"
  DeleteRegKey HKCR "${APP_REG_NAME}.Batch"

SectionEnd
