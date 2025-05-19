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
 * Type definitions
 *
 */

typedef struct sItem
{
  char mFileName[MAX_BUF_SIZE + 1];
  int mFileSize;
  int mCreationTime;
  struct sItem *mNextItem;
} FILE_ITEM, *PFILE_ITEM;





/*
 * Function forward declarations
 *
 */

int addItem(char *pFileName, int pFileSize, int pCreationTime);
void listItems();
void deleteAllItems();
int createDetailedFileListing(char *pDirectory);
int findOldestFile(char *pOldestFile, int pOldestFileBufferSize);
void ringspeicherManager();
//void listFiles(char *pDirectory);


