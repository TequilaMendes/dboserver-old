#ifndef _PACKET_H
#define _PACKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "Def.h"

#define HEADER_SIZE sizeof(PACKETHEADER);
#define PACKET_LIMIT_SIZE 0x7FFF

typedef struct PACKETHEADER
{
	WORD		bEncrypt : 1;
	WORD		wPacketLen : 15;
	BYTE		bySequence;
	BYTE		byChecksum;

} PACKETHEADER, *LPPACKETHEADER;

typedef struct PACKETDATA
{
	PACKETDATA() {}
	PACKETDATA(WORD opcode) :wOpCode(opcode) {}
	WORD		wOpCode;
} PACKETDATA, *LPPACKETDATA;

class Packet
{
public:
	Packet();
	Packet(Packet& rhs);
	Packet(BYTE * pAttachBuffer);
	Packet(BYTE * pPacketData, WORD wPacketBodySize, bool encrypt);
	Packet(WORD wPacketBodySize);
	~Packet();
	void Init();
	void Destroy();
	void Attach(BYTE * pPacketBuffer, bool encrypted);
	void AttachData(BYTE * pPacketBuffer, WORD wBufferUsedSize);
	void InitUseInternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize);
	void InitUseExternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize);
	void CopyToBuffer(BYTE * pDestBuffer, int nSize);
	void CopyFromBuffer(BYTE * pSrcBuffer, int nSize);
	void Realloc(int nSize);
	bool IsValidHeader();
	bool IsValidPacket();
	void ReadData(void * pDest, int nSize);
	void WriteData(void * pSrc, int nSize);
	void SetPacket(BYTE * pPacketData, WORD wPacketBodySize);
	void SetPacketLen(WORD wPacketLen);
	void SetUsedSize(WORD wSize) { mDataSize = wSize; }
	void SetPacketLenToUsedSize() { mDataSize = GetPacketLen(); }
	void AdjustPacketLen(WORD wPacketLen) { SetPacketLen(wPacketLen); SetPacketLenToUsedSize(); }
	virtual int	GetHeaderSize() { return HEADER_SIZE; }
	BYTE* GetPacketBuffer() { return mBufferPtr; }
	LPPACKETHEADER GetPacketHeader() { return	pHeader; }
	BYTE* GetPacketData() { return pData; }
	WORD GetPacketLen() { return (WORD)GetHeaderSize() + GetPacketDataSize(); }
	virtual WORD GetPacketDataSize() { return pHeader->wPacketLen; }
	WORD GetUsedSize() { return mDataSize; }

	Packet& operator =(Packet & rhs);
	Packet& operator <<(Packet& rhs);
	Packet& operator >>(Packet& rhs);
	Packet& operator <<(LPTSTR arg);
	Packet& operator >>(LPTSTR arg);
	Packet& operator <<(bool arg);
	Packet& operator >>(bool& arg);
	Packet& operator <<(int arg);
	Packet& operator >>(int& arg);
	Packet& operator <<(long arg);
	Packet& operator >>(long& arg);
	Packet& operator <<(DWORD arg);
	Packet& operator >>(DWORD& arg);

	LPPACKETHEADER pHeader;
	BYTE* mAllocBuffer;
	BYTE* mBufferPtr;
	WORD mDataSize;
	BYTE* pData;
	BYTE* pDataWritePos;
	BYTE* pDataReadPos;
	BYTE* pEndPos;
};

#endif