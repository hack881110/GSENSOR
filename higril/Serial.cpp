// Serial.cpp: implementation of the CSerial class.
//
//////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "Serial.h"
#include "stdio.h"
extern int mycount;
CSerial::CSerial()
{
	m_hCom = INVALID_HANDLE_VALUE;
	m_bExit = FALSE;
	m_hThread = NULL;
	m_dwMaskEvent = DEFAULT_COM_MASK_EVENT; 
	m_dwNotifyNum = 0;
	m_dcb.DCBlength = sizeof(DCB);
	m_hNotifyWnd = NULL;

	// ��ʼ���ص��ṹ
	memset(&m_ReadOl, 0, sizeof(m_ReadOl));
	memset(&m_WriteOl, 0, sizeof(m_WriteOl));
	memset(&m_WaitOl, 0, sizeof(m_WaitOl));
	m_ReadOl.hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_WriteOl.hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_WaitOl.hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
}

CSerial::~CSerial()
{
	// �رմ���
	Close();
	// �ͷ��¼�����
	::CloseHandle(m_ReadOl.hEvent);
	::CloseHandle(m_WriteOl.hEvent);
	::CloseHandle(m_WaitOl.hEvent);
}
/********************************************************************************************************
** �������ƣ�Open()
** �������ܣ��򿪴���
** ��ڲ�����DWORD dwPort���˿ںţ�DWORD dwBaudRate��������
** ���ڲ�����
*********************************************************************************************************/
BOOL CSerial::Open(DWORD dwPort, DWORD dwBaudRate)
{
	if(dwPort<1 || dwPort>1024)
	{
		return FALSE;
	}

	// �򿪴���
	if(!OpenCommPort(dwPort))
	{
		return FALSE;
	}

	// ����Ĭ������
	// �������������������С
	if(!::SetupComm(m_hCom, 4096, 4096))
	{
		return FALSE;
	}
	// ���ó�ʱ
	COMMTIMEOUTS co;
	if(!::GetCommTimeouts(m_hCom, &co))
		return FALSE;

	co.ReadIntervalTimeout = 0;
	co.ReadTotalTimeoutMultiplier = 1;
	co.ReadTotalTimeoutConstant = 1000;
	co.WriteTotalTimeoutMultiplier = 1;
	co.WriteTotalTimeoutConstant = 1000;
	if(!::SetCommTimeouts(m_hCom, &co))
		return FALSE;
	// ����������������
	if(!::PurgeComm(m_hCom, 
		PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR))
		return FALSE;


	return SetState(dwBaudRate);
}

BOOL CSerial:: Purge(DWORD dwFlags)
{
	if(!IsOpen())
		return FALSE;

	return ::PurgeComm(m_hCom, dwFlags);
}


BOOL CSerial::OpenCommPort(DWORD dwPort)
{
	if(m_hCom != INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	//strcpy_s(m_szComm, "\\\\.\\COM");
	////char sz[5];
	//_ltoa(dwPort, sz, 10);

	//strcat(m_szComm, sz);
	sprintf_s(m_szComm,16,"%s%d","\\\\.\\COM",dwPort);

	m_hCom = ::CreateFileA(m_szComm, GENERIC_READ | GENERIC_WRITE, 
						0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if(m_hCom == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwId;
	m_bExit = FALSE;
	m_hThread = ::CreateThread(NULL, 0, SerialThreadProc, this, 0, &dwId);
	if(m_hThread == NULL)
	{
		::CloseHandle(m_hCom);
		m_hCom = INVALID_HANDLE_VALUE; // 
		return FALSE;
	}

	// here to 
	return TRUE;
}

/********************************************************************************************************
** �������ƣ�Close()
** �������ܣ��رմ���
** ��ڲ�����
** ���ڲ�����
*********************************************************************************************************/
void CSerial::Close()
{
	if(!IsOpen())
		return;

	// wait thread to exit
	m_bExit = TRUE;

	::SetEvent(m_WaitOl.hEvent);

	DWORD dwExitCode;
	int n = 0;
	do
	{
		::Sleep(10);
		if(n++ > 5)
			break;
	}while(!::GetExitCodeThread(m_hThread, &dwExitCode));

	::CloseHandle(m_hThread);
	m_hThread = NULL;

	::CloseHandle(m_hCom);
	m_hCom = INVALID_HANDLE_VALUE;
}

/********************************************************************************************************
** �������ƣ�SetState()
** �������ܣ����ô��ڲ���
** ��ڲ�����DWORD dwBaudRate��������, DWORD dwByteSize������, DWORD dwPatity����żУ��λ, DWORD dwStopBits��ֹͣλ
** ���ڲ�����
*********************************************************************************************************/
BOOL CSerial::SetState(DWORD dwBaudRate, 
				DWORD dwByteSize, DWORD dwPatity, DWORD dwStopBits)
{
	if(IsOpen())
	{
		if(!::GetCommState(m_hCom, &m_dcb))
		{
			return FALSE;
		}
		m_dcb.BaudRate = dwBaudRate;
		m_dcb.ByteSize = (UCHAR)dwByteSize;
		m_dcb.StopBits = (UCHAR)dwStopBits;
		m_dcb.Parity = (UCHAR)dwPatity;
		if(dwPatity != NOPARITY)
			m_dcb.fParity = TRUE;

		return ::SetCommState(m_hCom, &m_dcb);
	}
	return FALSE;
}

/********************************************************************************************************
** �������ƣ�ThreadProc()
** �������ܣ����������߳�
** ��ڲ�����
** ���ڲ�����
*********************************************************************************************************/
DWORD CSerial::ThreadProc()
{
	if(!::SetCommMask(m_hCom, m_dwMaskEvent))
	{
		::MessageBoxA(m_hNotifyWnd, " SetCommMask failed", "", 0);
		return -1;
	}

	DWORD dwError, dwMask, dwTrans;
	COMSTAT Stat;


	while(!m_bExit)
	{
		dwMask = 0;
		if(!::WaitCommEvent(m_hCom, &dwMask, &m_WaitOl))
		{
			if(::GetLastError() == ERROR_IO_PENDING)
			{
				::GetOverlappedResult(m_hCom, &m_WaitOl, &dwTrans, TRUE);
			}
			else
				continue;
		}


		switch(dwMask)
		{
			case EV_RXCHAR:
				{   
					// �����ݽ�����  ��ȡ���ݴ�С
					::ClearCommError(m_hCom, &dwError, &Stat);
					if(Stat.cbInQue >= m_dwNotifyNum)
					{
						OnReceive();
					}
				}
				break;
			
			case EV_TXEMPTY:		// ����������е����һ���ַ���������
				OnTXEmpty();
				break;
			case EV_CTS:			// clear-to-send�źŸı�
				OnCTS();
				break;

			case EV_DSR:			// data-set-ready�źŸı�
				OnDSR();
				break;

			case EV_RING:		
				OnRing();
				break;

			case EV_RLSD:		
				OnRLSD();
				break;

			case EV_BREAK:
				OnBreak();
				break;

			case EV_ERR:
				OnError();
				break;
			default:
				continue;
		}
	}
	return 0;
}
	
DWORD WINAPI CSerial::SerialThreadProc(LPVOID lpParam)
{
	CSerial *pThis = (CSerial *)lpParam;
	return pThis->ThreadProc();
}

BOOL CSerial::ReadData(LPVOID Buffer, DWORD dwReadLen, DWORD dwWaitTime)
{
	if(!IsOpen())
		return FALSE;

	COMSTAT Stat;
	DWORD dwError;

	BOOL bError = FALSE;  // 

	DWORD dwRead = 0;
	while(TRUE)
	{
		if(::ClearCommError(m_hCom, &dwError, &Stat))
		{
			if(dwError > 0)
			{
				 bError = TRUE;  
			}
			
			if(Stat.cbInQue >= dwReadLen)
			{
				dwRead = Read(Buffer, Stat.cbInQue, dwWaitTime);
				break;
			}
			else
			{
				::Sleep(10);
			 	dwWaitTime -= 10;
			}
		}
		else
		{
			MessageBoxA(NULL, " ClearCommError failed ", "CSerial::ReadData", 0);
			return FALSE;
		}

		if(dwWaitTime <= 0)
			return FALSE;
	}


	if(dwRead == dwReadLen && !bError)
		return TRUE;
	else
		return FALSE; 
}

DWORD CSerial::Read(LPVOID Buffer, DWORD dwBufferLen, DWORD dwWaitTime)
{
	if(!IsOpen())
		return 0;


	COMSTAT Stat;
	DWORD dwError;
	// �д�������
	if(::ClearCommError(m_hCom, &dwError, &Stat) && dwError > 0)
	{
		// �������������������׳��Ķ�����
		::PurgeComm(m_hCom, PURGE_RXABORT|PURGE_RXCLEAR);
		return 0;
	}

	if(!Stat.cbInQue)
	{
		return 0;
	}

	DWORD dwReadLen = 0;
	if(dwBufferLen > Stat.cbInQue)
		dwBufferLen = Stat.cbInQue;

	if(!::ReadFile(m_hCom, Buffer, dwBufferLen, &dwReadLen, &m_ReadOl))
	{
		if(::GetLastError() == ERROR_IO_PENDING)
		{
			::WaitForSingleObject(m_ReadOl.hEvent, dwWaitTime);
			// 

			if(!::GetOverlappedResult(m_hCom, &m_ReadOl, &dwReadLen, FALSE))
			{
				if(::GetLastError() != ERROR_IO_INCOMPLETE)
				{
					dwReadLen  = 0;
				}
			}
		}
		else
		{
			dwReadLen  = 0;
		}
	}
	return dwReadLen;
}



DWORD CSerial::Write(LPVOID Buffer, DWORD dwBufferLen)
{
	if(!IsOpen())
		return 0;


	COMSTAT Stat;
	DWORD dwError;
	// �д�������
	if(::ClearCommError(m_hCom, &dwError, &Stat) && dwError > 0)
	{
		// �������������������׳��Ķ�����
		::PurgeComm(m_hCom, PURGE_RXABORT|PURGE_RXCLEAR);
		return 0;
	}

	DWORD dwWrite = 0;
	if(!::WriteFile(m_hCom, Buffer, dwBufferLen, &dwWrite, &m_WriteOl))
	{
		if( ::GetLastError() == ERROR_IO_PENDING)
		{
			::GetOverlappedResult(m_hCom, &m_WriteOl, &dwWrite, TRUE);
		}
	}
//	if(pollflag==1&&cmdmod==1)
  //     SetTimer(m_hNotifyWnd,1,3000,NULL); //���ö�ʱ��
//	if(pollflag==1&&cmdmod==2)
 //      SetTimer(m_hNotifyWnd,1,180000,NULL); //���ö�ʱ��
	return dwWrite;
}




// ���ô��ڻ������Ĵ�С 
BOOL CSerial::SetBufferSize(DWORD dwInputSize, DWORD dwOutputSize)
{
	return IsOpen() ? ::SetupComm(m_hCom, dwInputSize, dwOutputSize) : FALSE;
}


void CSerial::SetWnd(HWND hWnd)
{
	m_hNotifyWnd = hWnd;
}

void CSerial::SetNotifyNum(DWORD dwNum)
{
	m_dwNotifyNum = dwNum;
}

BOOL CSerial::SetTimeouts(LPCOMMTIMEOUTS lpCO)
{
	return IsOpen() ? ::SetCommTimeouts(m_hCom, lpCO) : FALSE;
}

BOOL CSerial::SetDTR(BOOL OnOrOff)
{
	return IsOpen() ? ::EscapeCommFunction(m_hCom, OnOrOff ? SETDTR:CLRDTR): FALSE;
}

BOOL CSerial::SetRTS(BOOL OnOrOff)
{
	return IsOpen() ? ::EscapeCommFunction(m_hCom, OnOrOff ? SETRTS:CLRRTS):FALSE;
}

BOOL CSerial::SetBreak(BOOL OnOrOff)
{
	return IsOpen() ? ::EscapeCommFunction(m_hCom, OnOrOff ? SETBREAK:CLRBREAK):FALSE;
}

void CSerial::SetMaskEvent(DWORD dwMask)
{
	m_dwMaskEvent = dwMask;
}

void CSerial::OnCTS()
{
	if(::IsWindow(m_hNotifyWnd))
	{
		DWORD dwStatus;
		if(GetCommModemStatus(m_hCom, &dwStatus))
			::SendMessage(m_hNotifyWnd, WM_COM_CTS, 0, dwStatus&MS_CTS_ON ? 1:0);
	}
}

void CSerial::OnDSR()
{
	if(::IsWindow(m_hNotifyWnd))
	{
		DWORD dwStatus;
		if(::GetCommModemStatus(m_hCom, &dwStatus))
		{
			::SendMessage(m_hNotifyWnd, WM_COM_DSR, 0, dwStatus&MS_DSR_ON ? 1:0);
		}
	}
}

void CSerial::OnRing()
{
	if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_RING, 0, 0);
}

void CSerial::OnRLSD()
{
	if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_RLSD, 0, 0);
}

void CSerial::OnBreak()
{
	if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_BREAK, 0, 0);
}

void CSerial::OnError()
{
	DWORD dwError;
	::ClearCommError(m_hCom, &dwError, NULL);
	if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_ERROR, 0, dwError);
}

void CSerial::OnReceive()
{
	if(::IsWindow(m_hNotifyWnd))
	{   
		KillTimer(m_hNotifyWnd,1);
		Sleep(10);
		::SendMessage(m_hNotifyWnd, WM_COM_RECEIVE, 0, 0);
		
	}
}

void CSerial::OnTXEmpty()
{
	if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_TXEMPTY, 0, 0);
}









	

