/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2013 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */

#ifndef __CHART_H_122333444455555__
#define __CHART_H_122333444455555__

#include <windows.h>
#include <tchar.h>

//用于动态链接库的时候，注释掉#else中的第二行
//用于静态库或者源码时，注释掉#else中的第一行
#ifdef PLOTDLL_EXPORTS
#	define PLOTDLL_API __declspec(dllexport)
#else
#	define PLOTDLL_API __declspec(dllimport)
//#	define PLOTDLL_API
#endif

// CChart包装类支持的绘图类型
enum
{
	kTypeXY,							//0 折线图
	kTypePie,							//1 饼图
	kTypeStem,							//2 柱图
	kTypeOscillo,						//3 模拟示波器图
	kTypeContourLine,					//4 等高线图
	kTypeContourMap,					//5 等高云图

	kTypeSingleLayerCount,				// 单层视图数目

	kTypeSplit = kTypeSingleLayerCount,	//6 分裂视图
	kTypeShareX,						//7 共享X轴视图
	kTypeLayered,						//8 分层视图
	
	kType2DCount,						// 二维视图数目

	kType3DLine = kType2DCount,			//9 3维折线图
	kType3DSurface,						//10 3维曲面图

	kTypeCount							//CChart所支持的视图类型数
};

//typedef double (*FieldFunction)(double, int);

/*

// 曲线绘制方式
enum
{
	kXYPlotScatter = 0,		//0 散点图
	kXYPlotConnect = 1,		//1 连线图
	kXYPlotStepHV = 2,		//2 台阶图先水平再竖直
	kXYPlotStepVH = 3,		//3 台阶图先竖直再水平
	kXYPlotStepHVH = 4,		//4 台阶图水平竖直水平
	kXYPlotStepVHV = 5,		//5 台阶图竖直水平竖直
	kXYPlotBezier = 6,		//6 贝塞尔连线图
  
	kPlotTypeCount
};


// 数据标记的形状
enum
{
	kXYMarkerNone = 0,			//0 无标记
	kXYMarkerCircle = 1,		//1 圆圈标记
	kXYMarkerSquareUpright = 2,	//2 正正方形
	kXYMarkerSquareOblique = 3,	//3 斜正方形
	kXYMarkerTriangleLeft = 4,	//4 左向三角形
	kXYMarkerTriangleRight = 5,	//5 右向三角形
	kXYMarkerTriangleUp = 6,	//6 上三角形
	kXYMarkerTriangleDown = 7,	//7 下三角形
	kXYMarkerX = 8,				//8 斜十字
	kXYMarkerCross = 9,			//9 正十字
	kXYMarkerBar = 10,			//10颜色棒
	kXYMarkerDot = 11,			//11点
		
	kMarkerTypeCount
};

 // 曲线填充的方式
enum
{
	kDataFillClosed = 0,			//0 封闭填充
	kDataFillFromBottomAxis = 1,	//1 底轴填充
	kDataFillFromTopAxis = 2,		//2 顶轴填充
	kDataFillFromLeftAxis = 3,      //3 左轴填充
	kDataFillFromRightAxis = 4,		//4 右轴填充
  
	kDataFillModeCount
};
// 数据棒显示方式
enum
{
	kDataBarBaseBottom,		//0 从底部开始
	kDataBarBaseTop,		//1 从顶部开始
	kDataBarBaseLeft,		//2 从左部开始
	kDataBarBaseRight,		//3 从右部开始
		
	kDataBarBaseCount
};

// 分裂视图的分裂模式
// 如果取消注释，可以直接用代号，否则用代码，例如2表示左一右二的三分裂
enum
{
	kSplitNot=0,		//0 不分裂
	kSplitNM=1,			//1 行列分割
	kSplit3L1R2=2,		//2 左1右2
	kSplit3L2R1=3,		//3 左2右1
	kSplit3T1B2=4,		//4 上1下2
	kSplit3T2B1=5,		//5 上2下1
		
	kSplitModeCount
};

// 坐标轴位置
// 如果取消注释，可以直接用代号，否则用代码
enum
{
	kLocationLeft = 0,	//0 左轴
	kLocationBottom,	//1 下轴
	kLocationRight,		//2 右轴
	kLocationTop,		//3 上轴
	kLocationCenterVL,	//4 中轴竖直偏左
	kLocationCenterVR,	//5 中轴竖直偏右
	kLocationCenterHB,	//6 中轴水平偏下
	kLocationCenterHT,	//7 中轴水平偏上
  
	kLocationTDX,		//8 三维X轴
	kLocationTDY,		//9 三维Y轴
	kLocationTDZ,		//10三维Z轴
	
	kLocationCount
};

// 图像整体缩放时的缩放中心
// 如果取消注释，可以直接用代号，否则用代码
enum
{
	kZoomCenterLT,		//0 左上
	kZoomCenterLB,		//1 左下
	kZoomCenterRT,		//2 右上
	kZoomCenterRB,		//3 右下
	kZoomCenterCT,		//4 中心
	kZoomCenterARB,		//5 任意点，主要用于鼠标位置
  
	kZoomCenterCount
};

 // how to show the mouse tool tip
 enum
{
	kDesCoords,
	kDesXY,
	kDesElements,
	kDesXAndYAll,
		
	kDesCount
};

// 对话框、右键菜单使用的语言
enum
{
	kLangEnglish,		//0 英语
	kLangChinese,		//1 汉语
	kLangCount
};
*/

///////////////////////////////////////////////////////////////////////////////////////////
// Declaration of CChart

class	PLOTDLL_API	CChart
{
public:	
	// CChart内部数据结构
	struct CChartPara;
	// 获得内部数据的指针
	CChartPara *GetPara();
protected:
	// 内部数据
	CChartPara	*m_pPara;
	// 释放内部资源
	void		Release();	

public:
	CChart();
	virtual	~CChart();

public:
	// 初始化GDI+
	static	void	InitGdiPlus();
	// 释放GDI+
	static	void	FreeGdiPlus();
	
	// 设置对话框、右键菜单使用的语言
	static	void	SetLangurage(int nLang);

	// 设置是否显示示波器模式的菜单和对话框
	static	void	SetOscilloMenus(bool bOscillo);
	// 设置数据处理菜单是否显示
	static	void	SetDataProcessing(bool process);

	// 拷贝图像到剪贴板
	static	void	CopyImageToClipBoard(HWND hWnd);
	// 保存图像到文件
	static	void	SaveImageToFile(HWND hWnd, TCHAR *strFileName, TCHAR *strFileExt);
	// 打印图像
	static	void	PrintImage(HWND hWnd);

	// 测试是否启用工具提示
	static	bool	IsEnableToolTip();
	// 设置是否启用工具提示
	static	void	SetEnableToolTip(bool enable);
	// 设置分裂视图子图数
	static	bool			ResizeSplit(CChart *pChart, int nSubPlots);

public:
	// 工具提示状态下，设置是否显示过鼠标点的横线
	void		SetAccompanyHLine(bool bDraw);
	// 工具提示状态下，设置是否显示过鼠标点的竖线
	void		SetAccompanyVLine(bool bDraw);

	// 检测子图序号是否在范围内
	bool		CheckSubPlotIndex(int nPlotIndex);

public:
	// 获得工具提示字符串
	TCHAR		*GetDescriptionByMousePos(HDC hDC, POINT point);
	// 设置工具提示字符串类型
	void		SetToolTipType(int type);

public:
	// 测试是否响应鼠标键盘消息
	bool		IsReact();
	// 设置是否响应鼠标键盘消息
	void		SetReact(bool react);
	// 设置是否响应鼠标移动消息
	void		SetNoMouseMove(bool nomm);
	// 测试是否限制绘图区
	bool		IsRectConfined();
	// 设置是否限制绘图区
	void		SetRectConfined(bool confine);
	// 测试双缓冲是否使用
	bool		IsBuffered();
	// 设置双缓冲是否使用
	void		SetBuffered(bool buffered);
	// 设置绘图区偏移
	void		SetOffsetClient(int offsetX, int offsetY);

public:
	// 对窗口句柄绘图
	virtual	void		OnDraw(HWND hWnd);
	// 对设备上下文绘图
	virtual	void		OnDraw(HDC hDC);
	// 在窗口上选择区域绘图
	virtual	void		OnDraw(HDC hDC, RECT destRect);
	// 在设备上下文对应的窗口上，选择区域绘图
	virtual	void		OnDraw(HWND hWnd, RECT destRect);

public:
	// 单个的鼠标键盘消息
	virtual	bool		OnLButtonDown( HWND hWnd, POINT point, UINT ctrlKey );
	virtual	bool		OnLButtonUp( HWND hWnd, POINT point, UINT ctrlKey );
	virtual	bool		OnLButtonDblClk( HWND hWnd, POINT point, UINT ctrlKey );
	virtual	bool		OnMouseMove( HWND hWnd, POINT point, UINT ctrlKey );
	virtual	bool		OnMouseLeave( HWND hWnd, POINT point, UINT ctrlKey );
	virtual	bool		OnMouseWheel( HWND hWnd, POINT point, UINT ctrlKey );
	virtual	bool		OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
	virtual	bool		OnKeyDown( HWND hWnd, UINT key );

	// 响应消息，但不重绘
	virtual	bool		OnEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// 响应消息并重绘
	virtual	void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// 增加右键菜单项，插件菜单功能
	void		SetPluginMenu(void (*fcnAddPluginMenu)( void *plot, HMENU addMenu ), int (*fcnInterpretPluginMenu)( void *plot, HWND hWnd, int result ), void *pPara);
	// 隐藏或显示缺省右键菜单，结合插件菜单功能可实现右键菜单全部自定义
	void		SetDefMenus(bool bShow);
	// 用户自定义绘图操作
	void		SetUserDrawingFunc(void	(*fcnUserDrawing)( HDC hDC, RECT clientRect, RECT plotRect, void *pPara ), void *pPara);
	// 用户自定义绘图操作
	void		SetUserDrawingFunc(void	(*fcnUserDrawing)( HDC hDC, RECT clientRect, RECT plotRect, void *pPara ), void *pPara, int nPlotIndex);
	// 用户自定义鼠标移动后操作
	void		SetPostMouseMoveFunc(bool	(*fcnPostMouseMove)( void *plot, HDC hDC, POINT point, UINT ctrlKey, void *para ), void *pPara);

public:
	// 获取内部Plot指针
	void		*GetPlot();
	// 获取图像类型编码
	int			GetType();
	// 设置图像类型编码
	bool		SetType(int nType);
	// 设置图像类型编码，并设置绘图窗口，主要用于三维视图，二维视图将忽略hWnd
	bool		SetType(int nType, HWND hWnd);
	
	// 设置限制区域
	bool		SetConfineRect(RECT ConfineRect);
	// 获取限制区域
	RECT		GetConfinedRect();

	// 测试内部是否无数据
	bool		IsEmpty();

public:	
	// 添加曲线，前三个参数是曲线数据
	// 第四个参数主要用于分裂视图、分层视图、共享X轴视图，表示子图序号。后续函数相同
	// 返回值是曲线的ID号，注意不是序号，返回-1表示添加曲线失败。后续函数相同
	int			AddCurve(double *pX, double *pY, int nLen, int nPlotIndex=0);
	// 添加曲线，其中X坐标为时间，用字符串形式输入
	//字符串应为"20130528234428"，即年月日时分秒，共14位数字，否则出错
	int			AddCurve(TCHAR **pStrTime, double *pY, int nLen, int nPlotIndex=0);
	// 添加空曲线
	int			AddCurve(int nPlotIndex=0);
	// 更新曲线数据
	int			UpdateCurve(int nDataIndex, double *pX, double *pY, int nLen, int nPlotIndex=0);
	// 根据ID号更新曲线数据
	int			UpdateCurveByID(int nDataID, double *pX, double *pY, int nLen, int nPlotIndex=0);
	// 从曲线的DataID获得Index
	int			GetIndex(int dataID, int nPlotIndex=0);
	// 从曲线的Index获得DataID
	int			GetDataID(int nIndex, int nPlotIndex=0);
	// 设置曲线的dataID，特殊用途，属于倚天剑屠龙刀，不要随便调用
	void		SetDataID(int newID, int nIndex, int nPlotIndex=0);
	// 添加饼图的一个值
	int			AddPie(double value);
	// 添加饼图的一个值，同时设置该块饼的标题
	int			AddPie(double value, TCHAR* title);
	// 添加柱图的一个序列
	int			AddStems(double *pData, int nLen);
	// 添加柱图的一个序列，同时设置该序列的标题
	int			AddStems(double *pData, int nLen, TCHAR* title);
	// 添加2维曲线的一个数据点
	// nDataIndex表示曲线的序号,
	// nDataIndex如果等于当前曲线的条数，则新增一条曲线，如果小于0或者大于当前曲线条数，则添加失败
	int			AddPoint2D(double x, double y, int nDataIndex=0, int nPlotIndex=0);
	// 添加数据点，其中X坐标为时间，用字符串形式输入
	//字符串应为"20130528234428"，即年月日时分秒，共14位数字，否则出错
	int			AddPoint2D(TCHAR *strTime, double y, int nDataIndex=0, int nPlotIndex=0);
	// 添加三维曲线的一个数据点
	int			AddPoint3D(double x, double y, double z, int nDataIndex=0);
	// 添加一条三维曲线
	int			AddCurve(double *pX, double *pY, double *pZ, int nLen);	
	// 设置场函数，用于等高线图、云图、三维曲面图
	void		SetFieldFcn(double (*_pFieldFcn) (double, double));
	// 获得场函数指针，用于等高线图、云图、三维曲面图
	double		(*GetFieldFcn( ))( double, double );

	// 清除所有曲线数据
	void		ClearAllData();
	// 清除单子图全部曲线数据
	void		ClearPlotData(int nPlotIndex=0);
	// 清除单条曲线数据
	void		ClearSingleData(int nDataIndex, int nPlotIndex=0);
	// 清空单条曲线数据
	void		EmptySingleData(int nDataIndex, int nPlotIndex=0);
	// 为曲线预留内存空间。主要目的是加快速度
	// CChart内部数据采用vector。如果数据点过多，随着数据点的增加，CChart将不断地为vector重新分配内存，影响速度
	// 如果根据实际情况预留了内存，则会一次性成功分配内存
	void		SetReservedDataLength(int nLen, int nPlotIndex=0);
	// 获得曲线的数据点数
	int			GetDataPointsCount(int nDataIndex, int nPlotIndex=0);
	// 去除曲线上单个数据点
	int			RemoveSinglePoint(int nPointIndex, int nDataIndex, int nPlotIndex=0);
	// 去除曲线上第一个数据点
	int			RemoveFirstPoint(int nDataIndex, int nPlotIndex=0);
	// 去除曲线上最后一个数据点
	int			RemoveLastPoint(int nDataIndex, int nPlotIndex=0);

public:
	// 增加一个图层，用于分层视图、共享X轴视图
	int			AddLayer();
	// 设置子图数量，用于分裂视图，其中mode表示分裂模式，nRows表示列数，nCols表示行数
	// 分裂模式参加本文件头部被注释掉的enum。可以解除注释，就能直接使用这些enum了。
	void		ResizePlots(int mode, int nRows, int nCols);
	// 设置图层数量，用于分层视图、共享X轴视图
	void		ResizePlots(int nLayers);
	
public:
	// 获得图像标题
	TCHAR*		GetTitle();
	// 获得子图标题，可用于分裂视图、分层视图、共享X轴视图
	TCHAR*		GetTitle(int nPlotIndex);
	// 设置图像标题
	void		SetTitle(const TCHAR* title);
	// 设置子图标题
	void		SetTitle(const TCHAR* title, int nPlotIndex);
	// 分层视图显示主标题
	void		SetShowParentTitle(bool set);

	// 获得子图数量
	int			GetSubPlotsCount();
	// 获得曲线数量，对于多层视图为子图曲线条数
	int			GetDataSetCount(int nPlotIndex=0);
	// 获得数据曲线的标题,nDataIndex表示曲线的序号
	const TCHAR*		GetDataTitle(int nDataIndex, int nPlotIndex=0);
	// 设置数据标题
	void		SetDataTitle(const TCHAR* title, int nDataIndex, int nPlotIndex=0);
	// 设置数据颜色
	void		SetDataColor(COLORREF color, int nDataIndex, int nPlotIndex=0);
	// 设置数据颜色
	void		SetDataLineStyle(int nStyle, int nDataIndex, int nPlotIndex=0);
	// 设置数据颜色
	void		SetDataLineSize(int nSize, int nDataIndex, int nPlotIndex=0);
	// 设置曲线的绘制方式
	void		SetPlotType(int nType, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记是否显示
	void		SetMarkerShow(bool bShow, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记是否填充
	void		SetMarkerFill(bool bFill, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记的形状
	void		SetMarkerType(int nType, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点的大小
	void		SetMarkerSize(int nSize, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记频率，0表示不标记，正n表示每隔n个点标记一次，负n表示一共标记n个点
	void		SetMarkerFreq(int nFreq, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点第一个点标记
	void		SetMarkFirstPoint(bool bMark, int nPlotIndex=0);
	// 设置曲线数据点最后一个点标记
	void		SetMarkLastPoint(bool bMark, int nPlotIndex=0);
	// 设置曲线散点显示模式
	void		SetScatter(int nDataIndex, int nPlotIndex=0);
	// 设置曲线填充颜色
	void		SetDataFillColor(bool bFill, COLORREF color, int nOpaque, int nFillMode, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据棒显示
	void		SetDataBarMode(bool bShowBar, int nBarBase, int nBarSize, int nDataIndex, int nPlotIndex=0);
	// 设置压缩显示模式，主要用于大数据量时的显示
	// 压缩显示模式中，如果相邻数据点在屏幕上显示时的X相同，将压缩成一个数据点，值取平均，
	void		SetDataCompactDraw(bool bCompact, int nDataIndex, int nPlotIndex=0);
	// 设置数据按直方图模式显示
	void		SetDataHistro(bool bHistro, int nDataIndex, int nPlotIndex=0);

	// 移动曲线
	bool		MoveData(double offsetx, double offsety, int nDataIndex, int nPlotIndex=0);
	// 获得曲线的水平偏移
	double		GetDataOffsetX(int nDataIndex, int nPlotIndex=0);
	// 设置曲线的水平偏移
	void		SetDataOffsetX(double offset, int nDataIndex, int nPlotIndex=0);
	// 获得曲线的竖直偏移
	double		GetDataOffsetY(int nDataIndex, int nPlotIndex=0);
	// 设置曲线的竖直偏移
	void		SetDataOffsetY(double offset, int nDataIndex, int nPlotIndex=0);
	// 设置X方向单位，仅仅用于模拟示波器
	void		SetXUnit(TCHAR *unit, int nDataIndex);
	// 设置Y方向单位，仅仅用于模拟示波器
	void		SetYUnit(TCHAR *unit, int nDataIndex);
	// 在图例中仅仅显示Y方向的比例尺，仅仅用于模拟示波器
	void		SetShowYSCaleOnly(bool only);
	// 设置光标绑定到曲线
	void		SetHoldCursorToCurve(bool hold, int nPlotIndex=0);
	// 获得光标绑定的曲线序号
	int			GetIndexToHoldCursor(int nPlotIndex=0);
	// 显示水平光标线，仅仅用于模拟示波器
	void		SetShowHCursor(bool show, int nPlotIndex=0);
	// 显示竖直光标线，仅仅用于模拟示波器
	void		SetShowVCursor(bool show, int nPlotIndex=0);
	// 获得水平光标值，仅仅用于模拟示波器
	double		GetCursorX(int nPlotIndex=0);
	// 设置水平光标值，仅仅用于模拟示波器
	void		SetCursorX( double cursor, int nPlotIndex=0);
	// 获得竖直光标值，仅仅用于模拟示波器
	double		GetCursorY(int nPlotIndex=0);
	// 设置竖直光标值，仅仅用于模拟示波器
	void		SetCursorY( double cursor, int nPlotIndex=0);
	// 显示水平选择区，仅仅用于模拟示波器
	void		SetShowHSel(bool show, int nPlotIndex=0);
	// 显示竖直选择区，仅仅用于模拟示波器
	void		SetShowVSel(bool show, int nPlotIndex=0);
	// 获得水平选择区的下限，仅仅用于模拟示波器
	double		GetHSelLower(int nPlotIndex=0);
	// 设置水平选择区的下限，仅仅用于模拟示波器
	void		SetHSelLower(int val, int nPlotIndex=0);
	// 获得水平选择区的上限，仅仅用于模拟示波器
	double		GetHSelUpper(int nPlotIndex=0);
	// 设置水平选择区的上限，仅仅用于模拟示波器
	void		SetHSelUpper(int val, int nPlotIndex=0);
	// 获得竖直选择区的下限，仅仅用于模拟示波器
	double		GetVSelLower(int nPlotIndex=0);
	// 设置竖直选择区的下限，仅仅用于模拟示波器
	void		SetVSelLower(int val, int nPlotIndex=0);
	// 获得竖直选择区的上限，仅仅用于模拟示波器
	double		GetVSelUpper(int nPlotIndex=0);
	// 设置竖直选择区的上限，仅仅用于模拟示波器
	void		SetVSelUpper(int val, int nPlotIndex=0);
	// 获得水平选择区的宽度，仅仅用于模拟示波器
	double		GetHSelWidth(int nPlotIndex=0);
	// 获得竖直选择区的宽度，仅仅用于模拟示波器
	double		GetVSelWidth(int nPlotIndex=0);
	
	// 增加坐标轴，坐标轴的位置location见本文件头部被注释掉的enum
	void		AddAxis(int location, int nPlotIndex=0);
	// 设置子图坐标轴标题
	void		SetAxisTitle(const TCHAR* title, int location, int nPlotIndex);
	// 设置坐标轴标题
	void		SetAxisTitle(const TCHAR* title, int location);
	// 设置子图时间坐标轴
	void		SetAxisToTime(bool bTime, int location, int nPlotIndex);
	// 设置时间坐标轴
	void		SetAxisToTime(bool bTime, int location);
	// 设置坐标轴是否显示刻度值
	void		SetAxisLabelShow(bool bShow, int location);
	// 设置子图坐标轴是否显示刻度值
	void		SetAxisLabelShow(bool bShow, int location, int nPlotIndex);
	// 设置子图坐标轴浮动标记
	void		SetAxisFloatTicks(bool flt, int nPlotIndex);
	// 设置坐标轴浮动标记
	void		SetAxisFloatTicks(bool flt);
	// 设置坐标轴是否显示
	void		SetAxisShow(bool bShow, int location);
	// 设置子图坐标轴是否显示
	void		SetAxisShow(bool bShow, int location, int nPlotIndex);
	//坐标轴是否显示
	bool		IsAxisShow(int location);
	// 子图坐标轴是否显示
	bool		IsAxisShow(int location, int nPlotIndex);

	// 检测是否使用图例
	bool		IsUseLegend(int nPlotIndex=0);
	// 设置是否使用图例
	void		SetUseLegend(bool bUse, int nPlotIndex=0);
	// 设置图例的最大行数
	void		SetLegendMaxRows(int nRows, int nPlotIndex=0);
	// 设置每行显示的图例数
	void		SetLegendMaxCols(int nCols, int nPlotIndex=0);

	// 设置坐标轴范围
	void		SetPlotRange(double xRange[2], double yRange[2]);
	void		SetXRange(double low, double high, int nPlotIndex);
	void		SetXRange(double low, double high);
	void		SetYRange(double low, double high, int nPlotIndex);
	void		SetYRange(double low, double high);
	// 设置坐标轴范围自动计算
	void		SetXAutoRange(bool bAuto);
	void		SetYAutoRange(bool bAuto);
	void		SetXAutoRange(bool bAuto, int nPlotIndex);
	void		SetYAutoRange(bool bAuto, int nPlotIndex);
	// 设置坐标轴范围与数据范围相同，不向两端扩展
	void		SetExactXRange(bool bExact, int nPlotIndex=0);
	void		SetExactYRange(bool bExact, int nPlotIndex=0);

	// 设置坐标轴等长，只对kTypeXY有效
	void		SetEqualXYAxis(bool bEqual);
	// 设置坐标轴等范围，只对kTypeXY有效
	void		SetEqualXYRange(bool bEqual);
	// 设置坐标轴等比例尺，只对kTypeXY有效
	void		SetEqualXYScale(bool bEqual);

	// 设置图像边框显示
	void		SetEdgeShow(bool bShow);
	// 设置图像边框显示
	void		SetEdgeRoundConor(bool bRound);
	// 设置图像边框颜色
	void		SetEdgeColor(COLORREF color);
	// 设置图像边框宽度
	void		SetEdgeWidth(int width);

public:
	// 设置饼图单个饼的标题
	void		SetPieTitle(const TCHAR* title, int which);
	// 设置饼图单个饼的颜色
	void		SetPieColor(COLORREF color, int which);

public:
	// 设置柱图单根柱子的标签
	void		SetStemLabel(const TCHAR* label, int which);
	// 设置柱图单个序列的标题
	void		SetStemTitle(const TCHAR* title, int nDataIndex);
	// 设置柱图单根柱子所占比例
	void		SetStemRatio(double ratio);

public:
	// 设置等高线图等高线的数量
	void		SetContourLineNum(int num);
	// 设置等高线图等高线绘制的精度，n越大，精度越高，一般5就可以了
	void		SetContourPrecision(int n);

	// 设置云图的起始颜色
	void		SetContourMapColor1(COLORREF cr);
	// 设置云图的最终颜色
	void		SetContourMapColor2(COLORREF cr);

public:
	// 设置背景网格与哪一个子图绑定，用于共享X轴视图
	void		SetGridBindLayer(int nPlotIndex);
	// 检测子图的网格线
	bool		GetGridLine(bool &MajorH, bool &MajorV, bool &MinorH, bool &MinorV, int nPlotIndex);
	// 检测网格线
	bool		GetGridLine(bool &MajorH, bool &MajorV, bool &MinorH, bool &MinorV);
	// 设置子图网格线的绘制
	void		SetGridLine(bool MajorH, bool MajorV, bool MinorH, bool MinorV, int nPlotIndex);
	// 设置网格线的绘制
	void		SetGridLine(bool MajorH=true, bool MajorV=true, bool MinorH=false, bool MinorV=false);
	// 获取子图背景颜色
	COLORREF	GetBkgndColor(int nPlotIndex);
	// 获取背景颜色
	COLORREF	GetBkgndColor();
	// 设置子图背景颜色
	void		SetBkgndColor(COLORREF color, int nPlotIndex);
	// 设置背景颜色
	void		SetBkgndColor(COLORREF color);

public:
	// 保存子图数据到文件
	bool		WriteToFile(TCHAR *pathName, int nPlotIndex);
	// 保存子图某曲线数据到文件
	bool		WriteToFile(TCHAR *pathName, int nDataIndex, int nPlotIndex);

public:
	// 设置图像整体缩放模式
	void		SetZoomMode(bool zoom);
	// 设置图像整体缩放时X方向的缩放系数
	void		SetZoomFactorX(double fact);
	// 设置图像整体缩放时Y方向的缩放系数
	void		SetZoomFactorY(double fact);
	// 设置图像整体缩放时两个方向的缩放系数
	void		SetZoomFactor(double fact);
	// 设置图像整体缩放时的缩放中心，中心的代号见本文件开始被注释掉的enum
	void		SetZoomCenterMode(int center);
protected:
	// 内部调用函数
	RECT		GetZoomedRect(RECT destRect);

public:
	// 设置三维曲线的网格
	void		SetGridLine(bool MajorXY, bool MinorXY, bool MajorYZ, bool MinorYZ, bool MajorZX, bool MinorZX);
	// 设置XY屏幕主网格
	void		SetShowXYMajorGrid( bool show );
	// 设置YZ屏幕主网格
	void		SetShowYZMajorGrid( bool show );
	// 设置ZX屏幕主网格
	void		SetShowZXMajorGrid( bool show );
	// 设置XY屏幕副网格
	void		SetShowXYMinorGrid( bool show );
	// 设置YZ屏幕副网格
	void		SetShowYZMinorGrid( bool show );
	// 设置ZX屏幕副网格
	void		SetShowZXMinorGrid( bool show );
	

public:
	// 在分层视图和分裂视图中，设置第一层显示左坐标轴，第二层显示右坐标轴
	void		SetLRAxis();
	// 在分层视图中，设置第一层显示下坐标轴，第二层显示上坐标轴
	void		SetTBAxis();
	// 底层函数，获取子图的绘图区域
	RECT		GetPlotRect(int nPlotIndex);
	// 底层函数，获取绘图区域
	RECT		GetPlotRect();
	// 底层函数，获取坐标轴的范围
	void		GetPlotRange(double xRange[2], double yRange[2], int nPlotIndex=0);

public:
	// 设置定时器函数
	void		SetTimerFunc(bool (*pFcnTimer)(void *pChart, void *pVoid), void *pPara);
	// 设置定时器的时间间隔，单位为ms
	void		SetTimerInterval(int interval);
	// 设置定时器的精度，单位为ms，只对高精度定时器起作用
	void		SetTimerResolution(int res);
	
	// 启动定时器
	// 高精度定时器采用多媒体定时器，低精度定时器采用WM_TIMER消息
	void		StartTimer(HWND hWnd, bool bHighRes);
	// 停止定时器
	void		StopTimer(HWND hWnd);

	// 获得定时器函数指针
	bool		(*GetTimerFunc( ))( void *pChart, void *pVoid );
	// 获得定时器函数传入参数
	void		*GetTimerPara();
};

///////////////////////////////////////////////////////////////////////////////////////////
// Declaration of CChartWnd

// 窗口类，包装了消息处理函数
class	PLOTDLL_API	CChartWnd
{
public:
	// CChartWnd内部所用的数据结构
	struct	CChartWndPara;
	// 获得内部数据的指针
	CChartWndPara *GetPara();
protected:
	// 内部数据
	CChartWndPara *m_pPara;
	
	// 释放内部资源
	void	Release();

public:
	CChartWnd();
	virtual	~CChartWnd();

public:
	// 获取CChart类的指针，以调用其函数
	CChart	*GetChart();
	// 设置CChart类对象，主要用于子类化
	void	SetChart(CChart *pChart);
	// 改变视图类型
	virtual	bool	SetChartType(int nType);
	
	// 粘窗口，最基本形式
	virtual	bool	Attach(HWND hWnd);
	// 粘窗口，同时设置绘图类型
	virtual	bool	Attach(HWND hWnd, int nType);
	// 粘窗口，同时设置绘图类型，并限制绘图区
	virtual	bool	Attach(HWND hWnd, int nType, RECT rtClient);
	// 粘窗口，粘到对话框上, 给定控件句柄
	virtual	bool	Attach(HWND hDlg, HWND hCtrl, int nType);
	// 粘窗口，粘到对话框上，给定控件ID
	virtual	bool	Attach(HWND hDlg, UINT nCtrlID, int nType);
	// 卸窗口
	bool	Detach();
	// 创建弹出窗口
	HWND	CreatePopupWnd(HWND hWndParent, int nType, TCHAR *wndTitle, int x=0, int y=0, int cx=640, int cy=480, DWORD dwStyle=0);

	// 重绘
	void	ReDraw();
};

///////////////////////////////////////////////////////////////////////////////////////////
// Declaration of CCommWnd

const int nBaudRates = 15;
const int aBaudRates[]=
{
	110,
		300,
		600,
		1200,
		2400,
		4800,
		9600,
		14400,
		19200,
		38400,
		56000,
		57600,
		115200,
		128000,
		256000
};

const struct Parity
{
	BYTE btParity;
	TCHAR sParity[24];
}Paritys[] = 
{
	{NOPARITY    ,_T("NO")},
	{ODDPARITY   ,_T("ODD")},
	{EVENPARITY  ,_T("EVEN")},
	{MARKPARITY  ,_T("MARK")},
	{SPACEPARITY ,_T("SPACE")}
};

const BYTE ByteSizes[] = {4, 5, 6, 7, 8};

const struct StopBit
{
	BYTE btStopBit;
	TCHAR sStopBit[24];
}StopBits[] = 
{
	{ONESTOPBIT   ,_T("ONESTOPBIT")},
	{ONE5STOPBITS ,_T("ONE5STOPBITS")},
	{TWOSTOPBITS  ,_T("TWOSTOPBITS")},
};

enum
{
	NoFlowControl,
		CtsRtsFlowControl,
		CtsDtrFlowControl,
		DsrRtsFlowControl,
		DsrDtrFlowControl,
		XonXoffFlowControl
};
const struct FlowControl
{
	BYTE btFlowCtrl;
	TCHAR sFlowCtrl[24];
}FlowControls[] =
{
	{NoFlowControl	,_T("No")},
	{CtsRtsFlowControl	,_T("CtsRts")},
	{CtsDtrFlowControl	,_T("CtsDtr")},
	{DsrRtsFlowControl	,_T("DsrRts")},
	{DsrDtrFlowControl	,_T("DsrDtr")},
	{XonXoffFlowControl	,_T("XonXoff")},
};

// 串口驱动窗口类
class	PLOTDLL_API	CCommWnd : public CChartWnd
{
public:
	// CCommWnd内部所用的数据结构
	struct	CCommWndPara;
	// 获得内部数据的指针
	CCommWndPara *GetPara();
protected:
	// 内部数据
	CCommWndPara *m_pPara;
	// 释放内部资源
	void	Release();
public:
	CCommWnd();
	virtual	~CCommWnd();

	// 设置视图类型
	bool	SetChartType(int nType);

public:
	// 获取串口参数
	bool	GetCommPara(int nChannelIndex, DWORD &dwPort, DWORD &dwBaudRate, BYTE &btParity, BYTE &btByteSize, BYTE &btStopBits, BYTE &btFlowCtrl, bool &bOpen);
	// 获取指定串口参数
	bool	GetCommPara(DWORD dwPort, DWORD &dwBaudRate, BYTE &btParity, BYTE &btByteSize, BYTE &btStopBits, BYTE &btFlowCtrl, bool &bOpen);
	// 直接打开串口
	/*! \param[in] dwPort 串口序号 1~1024 \param[in] dwBaudRate 波特率 \param[in] btParity  奇偶校验 \param[in] btByteSize 数据位数	\param[in] btStopBits 停止位数	*/
	//! 直接打开串口 缺省 9600, n, 8, 1 \sa bool Open(DWORD dwPort, LPCTSTR szSetStr)
	bool	OpenCommPort(DWORD dwPort, TCHAR *strTitle = _T(""), DWORD dwBaudRate = 9600, BYTE btParity = NOPARITY, BYTE btByteSize = 8, BYTE btStopBits = ONESTOPBIT, BYTE btFlowCtrl = NoFlowControl);
	// 关闭指定端口串口，并删除相关资源(曲线等)
	void	CloseCommPort(DWORD dwPort);
	// 关闭指定通道的串口，并删除相关资源(曲线等)
	void	CloseCommCh(int nChannelIndex);
	// 关闭所有通道串口，并删除相关资源(曲线等)
	void	CloseComms();
	// 调出预备串口的对话框，根据bOpen确定是否打开
	bool	ShowCommDlg(bool bOpen);
	// 准备一个串口，但不打开
	bool	PrepareCommPort(DWORD dwPort, TCHAR *strTitle = _T(""), DWORD dwBaudRate = 9600, BYTE btParity = NOPARITY, BYTE btByteSize = 8, BYTE btStopBits = ONESTOPBIT, BYTE btFlowCtrl = NoFlowControl);
	// 修改指定端口的串口参数
	bool	ModifyComm(DWORD dwPort, TCHAR *strTitle = _T(""), DWORD dwBaudRate = 9600, BYTE btParity = NOPARITY, BYTE btByteSize = 8, BYTE btStopBits = ONESTOPBIT, BYTE btFlowCtrl = NoFlowControl);
	// 修改串口序列中指定位置的串口参数
	bool	ModifyComm(int nChannelIndex, DWORD dwPort, TCHAR *strTitle = _T(""), DWORD dwBaudRate = 9600, BYTE btParity = NOPARITY, BYTE btByteSize = 8, BYTE btStopBits = ONESTOPBIT, BYTE btFlowCtrl = NoFlowControl);
	// 打开提前预备好的串口
	bool	StartComms();
	// 停止全部串口
	void	StopComms();
	// 重置端口接收到的数据
	void	ResetComms();
	// 触发：清空数据并启动端口
	void	Trig();
	// 获取通道数量
	int		GetChannels();
	// 获取有效端口数量
	int		GetValidPorts();
	// 获取有效端口号
	int		GetValidPorts(int nChannelIndex);
	// 获得时间间隔
	double	GetInterval();
	// 设置时间间隔
	void	SetInterval(double fInterval);
	// 是否有预备好的端口正在运行
	bool	IsAnyRunning();
	// 是否有预备好的端口不在运行
	bool	IsAnyPausing();
	// 获取每通道最大点数
	int		GetMaxChPoints();
	// 设置每通道最大点数
	void	SetMaxChPoints(int nPts);
	// 通道满点后是否清空
	bool	IsMaxChReset();
	// 设置通道满点后是否清空
	void	SetMaxChReset(bool	reset);
	// 保存通道数据
	bool	WriteToFile(TCHAR *pathName, int nChannel);
};

///////////////////////////////////////////////////////////////////////////////////////////
// Declaration of CDBaseWnd

// 数据库驱动窗口类
class	PLOTDLL_API	CDBaseWnd : public CChartWnd
{
public:
	// CDBaseWnd内部所用的数据结构
	struct	CDBaseWndPara;
	// 获得内部数据的指针
	CDBaseWndPara *GetPara();
protected:
	// 内部数据
	CDBaseWndPara *m_pPara;
	// 释放内部资源
	void	Release();

public:
	CDBaseWnd();
	virtual	~CDBaseWnd();

public:
	int		AddCurve(TCHAR *strXField, TCHAR *strYField, TCHAR *strTableName, TCHAR *strDSN, int nPlotIndex = 0, TCHAR *strUserName = _TEXT(""), TCHAR *strPswd = _TEXT(""));
	int		UpdateCurve(int nDataIndex, int nPlotIndex=0);
	void	ClearSingleData(int nDataIndex, int nPlotIndex=0);
};

///////////////////////////////////////////////////////////////////////////////////////////
// Declaration of CSocketWnd

// 套接字驱动窗口类
class	PLOTDLL_API	CSocketWnd : public CChartWnd
{
public:
	// CSocketWnd内部所用的数据结构
	struct	CSocketWndPara;
	// 获得内部数据的指针
	CSocketWndPara *GetPara();
protected:
	// 内部数据
	CSocketWndPara *m_pPara;
	// 释放内部资源
	void	Release();
	
public:
	CSocketWnd();
	virtual	~CSocketWnd();
	
public:
	int		StartCurve(bool bConnected, int nPort, double fDx = 1.0, char *symbol = " ", int nPlotIndex=0);
	void	CloseCurve(int nDataIndex, int nPlotIndex=0);
};

///////////////////////////////////////////////////////////////////////////////////////////
// aliases
typedef	CChart		MyChart;
typedef	CChartWnd	MyChartWnd;

#ifdef PLOTDLL_API
#	undef PLOTDLL_API
#endif //PLOTDLL_API

#endif //__CHART_H_122333444455555__
///////////////////////////////////////////////////////////////////////////////////////////
