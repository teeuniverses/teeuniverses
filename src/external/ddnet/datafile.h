/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverse.
 * 
 * TeeUniverse is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverse is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverse.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Some parts of this file comes from other projects.
 * These parts are itendified in this file by the following block:
 * 
 * FOREIGN CODE BEGIN: ProjectName *************************************
 * 
 * FOREIGN CODE END: ProjectName ***************************************
 * 
 * If ProjectName is "DDNet", then this part of the code follows the
 * DDNet licence:
 *      (c) Magnus Auvinen. See LICENSE_DDNET in the root of the
 *      distribution for more information. If you are missing that file,
 *      acquire a complete release at teeworlds.com.
 */

#ifndef __DDNET_DATAFILE__
#define __DDNET_DATAFILE__

#include <shared/system/fs.h>

class CStorage;

namespace ddnet
{

/* FOREIGN CODE BEGIN: DDNet ******************************************/

// raw datafile access
class CDataFileReader
{
	struct CDatafile *m_pDataFile;
	void *GetDataImpl(int Index, int Swap);
public:
	CDataFileReader() : m_pDataFile(0) {}
	~CDataFileReader() { Close(); }

	bool IsOpen() const { return m_pDataFile != 0; }

	bool Open(class CStorage *pStorage, const char *pFilename, int StorageType);
	bool Close();

	static bool GetCrcSize(class CStorage *pStorage, const char *pFilename, int StorageType, unsigned *pCrc, unsigned *pSize);

	void *GetData(int Index);
	void *GetDataSwapped(int Index); // makes sure that the data is 32bit LE ints when saved
	int GetDataSize(int Index);
	int GetUncompressedDataSize(int Index);
	void UnloadData(int Index);
	void *GetItem(int Index, int *pType, int *pID);
	int GetItemSize(int Index);
	void GetType(int Type, int *pStart, int *pNum);
	void *FindItem(int Type, int ID);
	int NumItems();
	int NumData();
	void Unload();

	unsigned Crc();
};

// write access
class CDataFileWriter
{
	struct CDataInfo
	{
		int m_UncompressedSize;
		int m_CompressedSize;
		void *m_pCompressedData;
	};

	struct CItemInfo
	{
		int m_Type;
		int m_ID;
		int m_Size;
		int m_Next;
		int m_Prev;
		void *m_pData;
	};

	struct CItemTypeInfo
	{
		int m_Num;
		int m_First;
		int m_Last;
	};

	enum
	{
		MAX_ITEM_TYPES=0xffff,
		MAX_ITEMS=1024,
		MAX_DATAS=1024,
	};

	IOHANDLE m_File;
	int m_NumItems;
	int m_NumDatas;
	int m_NumItemTypes;
	CItemTypeInfo *m_pItemTypes;
	CItemInfo *m_pItems;
	CDataInfo *m_pDatas;

public:
	CDataFileWriter();
	~CDataFileWriter();
	void Init();
	bool OpenFile(class CStorage *pStorage, int StorageType, const char *pFilename);
	bool Open(class CStorage *pStorage, int StorageType, const char *Filename);
	int AddData(int Size, const void *pData);
	int AddDataSwapped(int Size, const void *pData);
	int AddItem(int Type, int ID, int Size, const void *pData);
	int Finish();
};

/* FOREIGN CODE END: TeeWorlds ****************************************/

}

#endif
