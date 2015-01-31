#ifndef _SERIAL_H_
#define _SERIAL_H_


//  CSerial类向主窗口发送的消息
#define WM_COM_RECEIVE WM_USER + 101
#define WM_COM_CTS WM_USER + 102
#define WM_COM_DSR WM_USER + 103
#define WM_COM_RING WM_USER + 104
#define WM_COM_RLSD WM_USER + 106
#define WM_COM_BREAK WM_USER + 107
#define WM_COM_TXEMPTY WM_USER + 108
#define WM_COM_ERROR WM_USER + 109

#define DEFAULT_COM_MASK_EVENT EV_RXCHAR | EV_ERR  \
				| EV_CTS | EV_DSR | EV_BREAK | EV_TXEMPTY | EV_RING | EV_RLSD

class CSerial  
{
public:
	CSerial();
	virtual ~CSerial();

	BOOL IsOpen() { return m_hCom != INVALID_HANDLE_VALUE; }

	// 使用默认设置打开串口
	BOOL Open(DWORD dwPort, DWORD dwBaudRate = 9600);
	void Close();

	// 设置串口状态
	BOOL SetState(DWORD dwBaudRate, DWORD dwByteSize = 8, 
				DWORD dwPatity = NOPARITY, DWORD dwStopBits = ONESTOPBIT);
	BOOL SetTimeouts(LPCOMMTIMEOUTS lpCO);
	BOOL SetBufferSize(DWORD dwInputSize, DWORD dwOutputSize);
	void SetWnd(HWND hWnd);
	void SetNotifyNum(DWORD dwNum);
	void SetMaskEvent(DWORD dwMask);

	// 读写串口
	DWORD Write(LPVOID Buffer, DWORD dwBufferLen);
	DWORD Read(LPVOID Buffer, DWORD dwBufferLen, DWORD dwWaitTime = 20);
	// 读取指定字节的数据
	BOOL  ReadData(LPVOID Buffer, DWORD dwReadLen, DWORD dwWaitTime = 100);
	

	BOOL Purge(DWORD dwFlags = PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

	// 设置电平
	BOOL SetDTR(BOOL OnOrOff);
	BOOL SetRTS(BOOL OnOrOff);
	BOOL SetBreak(BOOL OnOrOff);

protected:		
	BOOL OpenCommPort(DWORD dwPort);

	// 事件处理函数
	virtual void OnCTS();
	virtual void OnDSR();
	virtual void OnRing();
	virtual void OnRLSD();
	virtual void OnBreak();
	virtual void OnError();
	virtual void OnReceive();
	virtual void OnTXEmpty();
    
	// 线程函数，等待处理串口上发生的事件
	virtual DWORD ThreadProc();	
	static DWORD WINAPI SerialThreadProc(LPVOID lpParam);
protected:
	HANDLE m_hCom;
	OVERLAPPED m_ReadOl;
	OVERLAPPED m_WriteOl;
	OVERLAPPED m_WaitOl;
	BOOL m_bExit;
	HANDLE m_hThread;
	DCB m_dcb;
	DWORD m_dwMaskEvent;
	HWND m_hNotifyWnd;
	DWORD m_dwNotifyNum;
	char m_szComm[16];
};




#endif 