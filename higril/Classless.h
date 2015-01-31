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

#ifndef __CLASSLESS_H_122333444455555__
#define __CLASSLESS_H_122333444455555__

#include <windows.h>

//用于动态链接库的时候，注释掉#else中的第二行
//用于静态库或者源码时，注释掉#else中的第一行
#ifdef PLOTDLL_EXPORTS
#	define PLOTDLL_API __declspec(dllexport)
#else
#	define PLOTDLL_API __declspec(dllimport)
//#	define PLOTDLL_API
#endif

namespace CChart_Classless
{
/////////////////////////////////////////////////////////////////////////////
// 以下函数来自CChartWnd
	// 改变视图类型
	PLOTDLL_API bool	SetChartType(int nType);

	// 粘窗口，最基本形式
	PLOTDLL_API bool	Attach(HWND hWnd);
	// 粘窗口，同时设置绘图类型
	PLOTDLL_API bool	Attach(HWND hWnd, int nType);
	// 粘窗口，同时设置绘图类型，并限制绘图区
	PLOTDLL_API bool	Attach(HWND hWnd, int nType, RECT rtClient);
	// 粘窗口，粘到对话框上, 给定控件句柄
	PLOTDLL_API bool	Attach(HWND hDlg, HWND hCtrl, int nType);
	// 粘窗口，粘到对话框上，给定控件ID
	PLOTDLL_API bool	Attach(HWND hDlg, UINT nCtrlID, int nType);
	// 卸窗口
	PLOTDLL_API bool	Detach();
	// 创建弹出窗口
	HWND	CreatePopupWnd(HWND hWndParent, int nType, TCHAR *wndTitle, int x=0, int y=0, int cx=640, int cy=480, DWORD dwStyle=0);
	// 重绘
	PLOTDLL_API void	ReDraw();

/////////////////////////////////////////////////////////////////////////////
// 以下函数来自CChart
	//初始化GDI+
	PLOTDLL_API void	InitGdiPlus();
	//卸载GDI+
	PLOTDLL_API void	FreeGdiPlus();
	// 设置对话框、右键菜单使用的语言
	PLOTDLL_API	void	SetLangurage(int nLang);
	// 设置曲线是否可以用鼠标移动
	PLOTDLL_API	void	SetOscilloMenus(bool bMoveable);
	// 设置数据处理菜单是否显示
	PLOTDLL_API	void	SetDataProcessing(bool process);
	// 拷贝图像到剪贴板
	PLOTDLL_API	void	CopyImageToClipBoard(HWND hWnd);
	// 保存图像到文件
	PLOTDLL_API	void	SaveImageToFile(HWND hWnd, TCHAR *strFileName, TCHAR *strFileExt);
	// 打印图像
	PLOTDLL_API	void	PrintImage(HWND hWnd);

	// 测试是否启用工具提示
	PLOTDLL_API	bool	IsEnableToolTip();
	// 设置是否启用工具提示
	PLOTDLL_API	void	SetEnableToolTip(bool enable);
	// 设置工具提示字符串类型
	PLOTDLL_API	void	SetToolTipType(int type);
	
	// 测试是否响应鼠标键盘消息
	PLOTDLL_API bool		IsReact();
	// 设置是否响应鼠标键盘消息
	PLOTDLL_API void		SetReact(bool react);
	// 测试是否限制绘图区
	PLOTDLL_API bool		IsRectConfined();
	// 设置是否限制绘图区
	PLOTDLL_API void		SetRectConfined(bool confine);
	// 测试双缓冲是否使用
	PLOTDLL_API bool		IsBuffered();
	// 设置双缓冲是否使用
	PLOTDLL_API void		SetBuffered(bool buffered);
	// 设置绘图区偏移
	PLOTDLL_API void		SetOffsetClient(int offsetX, int offsetY);

	// 增加右键菜单项，插件菜单功能
	PLOTDLL_API void		SetPluginMenu(void (*fcnAddPluginMenu)( void *plot, HMENU addMenu ), int (*fcnInterpretPluginMenu)( void *plot, HWND hWnd, int result ), void *pPara);
	// 隐藏或显示缺省右键菜单，结合插件菜单功能可实现右键菜单全部自定义
	PLOTDLL_API void		SetDefMenus(bool bShow);
	// 用户自定义绘图操作
	PLOTDLL_API void		SetUserDrawingFunc(void	(*fcnUserDrawing)( HDC hDC, RECT clientRect, RECT plotRect, void *pPara ), void *pPara);
	// 用户自定义绘图操作
	PLOTDLL_API void		SetUserDrawingFunc(void	(*fcnUserDrawing)( HDC hDC, RECT clientRect, RECT plotRect, void *pPara ), void *pPara, int nPlotIndex);
	// 用户自定义鼠标移动后操作
	PLOTDLL_API void		SetPostMouseMoveFunc(bool	(*fcnPostMouseMove)( void *plot, HDC hDC, POINT point, UINT ctrlKey, void *para ), void *pPara);


	// 添加曲线，前三个参数是曲线数据
	// 第四个参数主要用于分裂视图、分层视图、共享X轴视图，表示子图序号。后续函数相同
	// 返回值是曲线的ID号，注意不是序号，返回-1表示添加曲线失败。后续函数相同
	PLOTDLL_API int			AddCurve(double *pX, double *pY, int nLen, int nPlotIndex=0);
	// 添加曲线，其中X坐标为时间，用字符串形式输入
	//字符串应为"20130528234428"，即年月日时分秒，共14位数字，否则出错
	PLOTDLL_API int			AddCurve(TCHAR **pStrTime, double *pY, int nLen, int nPlotIndex=0);
	// 添加空曲线
	PLOTDLL_API int			AddCurve(int nPlotIndex=0);
	// 更新曲线数据
	PLOTDLL_API int			UpdateCurve(int nDataIndex, double *pX, double *pY, int nLen, int nPlotIndex=0);
	// 根据ID号更新曲线数据
	PLOTDLL_API int			UpdateCurveByID(int nDataID, double *pX, double *pY, int nLen, int nPlotIndex=0);
	// 从曲线的DataID获得Index
	PLOTDLL_API int			GetIndex(int dataID, int nPlotIndex=0);
	// 从曲线的Index获得DataID
	PLOTDLL_API int			GetDataID(int nIndex, int nPlotIndex=0);
	// 添加饼图的一个值
	PLOTDLL_API int			AddPie(double value);
	// 添加饼图的一个值，同时设置该块饼的标题
	PLOTDLL_API int			AddPie(double value, TCHAR* title);
	// 添加柱图的一个序列
	PLOTDLL_API int			AddStems(double *pData, int nLen);
	// 添加柱图的一个序列，同时设置该序列的标题
	PLOTDLL_API int			AddStems(double *pData, int nLen, TCHAR* title);
	// 添加2维曲线的一个数据点
	// nDataIndex表示曲线的序号,
	// nDataIndex如果等于当前曲线的条数，则新增一条曲线，如果小于0或者大于当前曲线条数，则添加失败
	PLOTDLL_API int			AddPoint2D(double x, double y, int nDataIndex=0, int nPlotIndex=0);
	// 添加数据点，其中X坐标为时间，用字符串形式输入
	//字符串应为"20130528234428"，即年月日时分秒，共14位数字，否则出错
	PLOTDLL_API int			AddPoint2D(TCHAR *strTime, double y, int nDataIndex=0, int nPlotIndex=0);
	// 添加三维曲线的一个数据点
	PLOTDLL_API int			AddPoint3D(double x, double y, double z, int nDataIndex=0);
	// 添加一条三维曲线
	PLOTDLL_API int			AddCurve(double *pX, double *pY, double *pZ, int nLen);	
	// 设置场函数，用于等高线图、云图、三维曲面图
	PLOTDLL_API void		SetFieldFcn(double (*_pFieldFcn) (double, double));
	// 获得场函数指针，用于等高线图、云图、三维曲面图
	PLOTDLL_API double		(*GetFieldFcn( ))( double, double );
	// 清除所有曲线数据
	PLOTDLL_API void		ClearAllData();
	// 清除单子图全部曲线数据
	PLOTDLL_API void		ClearPlotData(int nPlotIndex=0);
	// 清除单条曲线数据
	PLOTDLL_API void		ClearSingleData(int nDataIndex, int nPlotIndex=0);
	// 清空单条曲线数据
	PLOTDLL_API void		EmptySingleData(int nDataIndex, int nPlotIndex=0);
	// 为曲线预留内存空间。主要目的是加快速度
	// CChart内部数据采用vector。如果数据点过多，随着数据点的增加，CChart将不断地为vector重新分配内存，影响速度
	// 如果根据实际情况预留了内存，则会一次性成功分配内存
	PLOTDLL_API void		SetReservedDataLength(int nLen, int nPlotIndex=0);
	// 获得曲线的数据点数
	PLOTDLL_API int			GetDataPointsCount(int nDataIndex, int nPlotIndex=0);
	// 去除曲线上单个数据点
	PLOTDLL_API int			RemoveSinglePoint(int nPointIndex, int nDataIndex, int nPlotIndex=0);
	// 去除曲线上第一个数据点
	PLOTDLL_API int			RemoveFirstPoint(int nDataIndex, int nPlotIndex=0);
	// 去除曲线上最后一个数据点
	PLOTDLL_API int			RemoveLastPoint(int nDataIndex, int nPlotIndex=0);

	// 增加一个图层，用于分层视图、共享X轴视图
	PLOTDLL_API int			AddLayer();
	// 设置子图数量，用于分裂视图，其中mode表示分裂模式，nRows表示列数，nCols表示行数
	// 分裂模式参加本文件头部被注释掉的enum。可以解除注释，就能直接使用这些enum了。
	PLOTDLL_API void		ResizePlots(int mode, int nRows, int nCols);
	// 设置图层数量，用于分层视图、共享X轴视图
	PLOTDLL_API void		ResizePlots(int nLayers);
	
	// 获得图像标题
	PLOTDLL_API const TCHAR*		GetTitle();
	// 获得子图标题，可用于分裂视图、分层视图、共享X轴视图
	PLOTDLL_API const TCHAR*		GetTitle(int nPlotIndex);
	// 设置图像标题
	PLOTDLL_API void		SetTitle(const TCHAR* title);
	// 设置子图标题
	PLOTDLL_API void		SetTitle(const TCHAR* title, int nPlotIndex);
	// 分层视图显示主标题
	PLOTDLL_API void		SetShowParentTitle(bool set);

	// 获得子图数量
	PLOTDLL_API int			GetSubPlotsCount();

	// 获得数据曲线的标题,nDataIndex表示曲线的序号
	PLOTDLL_API const TCHAR*		GetDataTitle(int nDataIndex, int nPlotIndex=0);
	// 设置数据标题
	PLOTDLL_API void		SetDataTitle(const TCHAR* title, int nDataIndex, int nPlotIndex=0);
	// 设置数据颜色
	PLOTDLL_API void		SetDataColor(COLORREF color, int nDataIndex, int nPlotIndex=0);
	// 设置数据颜色
	PLOTDLL_API void		SetDataLineStyle(int nStyle, int nDataIndex, int nPlotIndex=0);
	// 设置数据颜色
	PLOTDLL_API void		SetDataLineSize(int nSize, int nDataIndex, int nPlotIndex=0);
	// 设置曲线的绘制方式
	PLOTDLL_API void		SetPlotType(int nType, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记是否显示
	PLOTDLL_API void		SetMarkerShow(bool bShow, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记是否填充
	PLOTDLL_API void		SetMarkerFill(bool bFill, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记的形状
	PLOTDLL_API void		SetMarkerType(int nType, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点的大小
	PLOTDLL_API void		SetMarkerSize(int nSize, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点标记频率，0表示不标记，正n表示每隔n个点标记一次，负n表示一共标记n个点
	PLOTDLL_API void		SetMarkerFreq(int nFreq, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据点第一个点标记
	PLOTDLL_API void		SetMarkFirstPoint(bool bMark, int nPlotIndex=0);
	// 设置曲线数据点最后一个点标记
	PLOTDLL_API void		SetMarkLastPoint(bool bMark, int nPlotIndex=0);
	// 设置曲线散点显示模式
	PLOTDLL_API void		SetScatter(int nDataIndex, int nPlotIndex=0);
	// 设置曲线填充颜色
	PLOTDLL_API void		SetDataFillColor(bool bFill, COLORREF color, int nOpaque, int nFillMode, int nDataIndex, int nPlotIndex=0);
	// 设置曲线数据棒显示
	PLOTDLL_API void		SetDataBarMode(bool bShowBar, int nBarBase, int nBarSize, int nDataIndex, int nPlotIndex=0);
	// 设置压缩显示模式，主要用于大数据量时的显示
	// 压缩显示模式中，如果相邻数据点在屏幕上显示时的X相同，将压缩成一个数据点，值取平均，
	PLOTDLL_API void		SetDataCompactDraw(bool bCompact, int nDataIndex, int nPlotIndex=0);
	// 设置数据按直方图模式显示
	PLOTDLL_API void		SetDataHistro(bool bHistro, int nDataIndex, int nPlotIndex=0);

	// 移动曲线
	PLOTDLL_API bool		MoveData(double offsetx, double offsety, int nDataIndex, int nPlotIndex=0);
	// 获得曲线的水平偏移
	PLOTDLL_API double		GetDataOffsetX(int nDataIndex, int nPlotIndex=0);
	// 设置曲线的水平偏移
	PLOTDLL_API void		SetDataOffsetX(double offset, int nDataIndex, int nPlotIndex=0);
	// 获得曲线的竖直偏移
	PLOTDLL_API double		GetDataOffsetY(int nDataIndex, int nPlotIndex=0);
	// 设置曲线的竖直偏移
	PLOTDLL_API void		SetDataOffsetY(double offset, int nDataIndex, int nPlotIndex=0);
	// 设置X方向单位，仅仅用于模拟示波器
	PLOTDLL_API void		SetXUnit(TCHAR *unit, int nDataIndex);
	// 设置Y方向单位，仅仅用于模拟示波器
	PLOTDLL_API void		SetYUnit(TCHAR *unit, int nDataIndex);
	// 在图例中仅仅显示Y方向的比例尺，仅仅用于模拟示波器
	PLOTDLL_API void		SetShowYSCaleOnly(bool only);
	// 设置光标绑定到曲线
	PLOTDLL_API void		SetHoldCursorToCurve(bool hold, int nPlotIndex=0);
	// 获得光标绑定的曲线序号
	PLOTDLL_API int			GetIndexToHoldCursor(int nPlotIndex=0);
	// 显示水平光标线，仅仅用于模拟示波器
	PLOTDLL_API void		SetShowHCursor(bool show, int nPlotIndex=0);
	// 显示竖直光标线，仅仅用于模拟示波器
	PLOTDLL_API void		SetShowVCursor(bool show, int nPlotIndex=0);
	// 获得水平光标值，仅仅用于模拟示波器
	PLOTDLL_API double		GetCursorX(int nPlotIndex=0);
	// 设置水平光标值，仅仅用于模拟示波器
	PLOTDLL_API void		SetCursorX( double cursor, int nPlotIndex=0);
	// 获得竖直光标值，仅仅用于模拟示波器
	PLOTDLL_API double		GetCursorY(int nPlotIndex=0);
	// 设置竖直光标值，仅仅用于模拟示波器
	PLOTDLL_API void		SetCursorY( double cursor, int nPlotIndex=0);
	// 显示水平选择区，仅仅用于模拟示波器
	PLOTDLL_API void		SetShowHSel(bool show, int nPlotIndex=0);
	// 显示竖直选择区，仅仅用于模拟示波器
	PLOTDLL_API void		SetShowVSel(bool show, int nPlotIndex=0);
	// 获得水平选择区的下限，仅仅用于模拟示波器
	PLOTDLL_API double		GetHSelLower(int nPlotIndex=0);
	// 设置水平选择区的下限，仅仅用于模拟示波器
	PLOTDLL_API void		SetHSelLower(int val, int nPlotIndex=0);
	// 获得水平选择区的上限，仅仅用于模拟示波器
	PLOTDLL_API double		GetHSelUpper(int nPlotIndex=0);
	// 设置水平选择区的上限，仅仅用于模拟示波器
	PLOTDLL_API void		SetHSelUpper(int val, int nPlotIndex=0);
	// 获得竖直选择区的下限，仅仅用于模拟示波器
	PLOTDLL_API double		GetVSelLower(int nPlotIndex=0);
	// 设置竖直选择区的下限，仅仅用于模拟示波器
	PLOTDLL_API void		SetVSelLower(int val, int nPlotIndex=0);
	// 获得竖直选择区的上限，仅仅用于模拟示波器
	PLOTDLL_API double		GetVSelUpper(int nPlotIndex=0);
	// 设置竖直选择区的上限，仅仅用于模拟示波器
	PLOTDLL_API void		SetVSelUpper(int val, int nPlotIndex=0);
	// 获得水平选择区的宽度，仅仅用于模拟示波器
	PLOTDLL_API double		GetHSelWidth(int nPlotIndex=0);
	// 获得竖直选择区的宽度，仅仅用于模拟示波器
	PLOTDLL_API double		GetVSelWidth(int nPlotIndex=0);
	
	// 增加坐标轴，坐标轴的位置location见本文件头部被注释掉的enum
	PLOTDLL_API void		AddAxis(int location, int nPlotIndex=0);
	// 设置子图坐标轴标题
	PLOTDLL_API void		SetAxisTitle(const TCHAR* title, int location, int nPlotIndex);
	// 设置坐标轴标题
	PLOTDLL_API void		SetAxisTitle(const TCHAR* title, int location);
	// 设置子图时间坐标轴
	PLOTDLL_API void		SetAxisToTime(bool bTime, int location, int nPlotIndex);
	// 设置时间坐标轴
	PLOTDLL_API void		SetAxisToTime(bool bTime, int location);
	// 设置坐标轴是否显示刻度值
	PLOTDLL_API void		SetAxisLabelShow(bool bShow, int location);
	// 设置子图坐标轴是否显示刻度值
	PLOTDLL_API void		SetAxisLabelShow(bool bShow, int location, int nPlotIndex);
	// 设置子图坐标轴浮动标记
	PLOTDLL_API void		SetAxisFloatTicks(bool flt, int nPlotIndex);
	// 设置坐标轴浮动标记
	PLOTDLL_API void		SetAxisFloatTicks(bool flt);
	// 设置坐标轴是否显示
	PLOTDLL_API void		SetAxisShow(bool bShow, int location);
	// 设置子图坐标轴是否显示
	PLOTDLL_API void		SetAxisShow(bool bShow, int location, int nPlotIndex);
	//坐标轴是否显示
	PLOTDLL_API bool		IsAxisShow(int location);
	// 子图坐标轴是否显示
	PLOTDLL_API bool		IsAxisShow(int location, int nPlotIndex);

	// 检测是否使用图例
	PLOTDLL_API bool		IsUseLegend(int nPlotIndex=0);
	// 设置是否使用图例
	PLOTDLL_API void		SetUseLegend(bool bUse, int nPlotIndex=0);
	// 设置图例的最大行数
	PLOTDLL_API void		SetLegendMaxRows(int nRows, int nPlotIndex=0);
	// 设置每行显示的图例数
	PLOTDLL_API void		SetLegendMaxCols(int nCols, int nPlotIndex=0);

	// 设置坐标轴范围
	PLOTDLL_API void		SetPlotRange(double xRange[2], double yRange[2]);
	PLOTDLL_API void		SetXRange(double low, double high, int nPlotIndex);
	PLOTDLL_API void		SetXRange(double low, double high);
	PLOTDLL_API void		SetYRange(double low, double high, int nPlotIndex);
	PLOTDLL_API void		SetYRange(double low, double high);
	// 设置坐标轴范围自动计算
	PLOTDLL_API void		SetXAutoRange(bool bAuto);
	PLOTDLL_API void		SetYAutoRange(bool bAuto);
	PLOTDLL_API void		SetXAutoRange(bool bAuto, int nPlotIndex);
	PLOTDLL_API void		SetYAutoRange(bool bAuto, int nPlotIndex);
	// 设置坐标轴范围与数据范围相同，不向两端扩展
	PLOTDLL_API void		SetExactXRange(bool bExact, int nPlotIndex=0);
	PLOTDLL_API void		SetExactYRange(bool bExact, int nPlotIndex=0);

	// 设置坐标轴等长，只对kTypeXY有效
	PLOTDLL_API void		SetEqualXYAxis(bool bEqual);
	// 设置坐标轴等范围，只对kTypeXY有效
	PLOTDLL_API void		SetEqualXYRange(bool bEqual);
	// 设置坐标轴等比例尺，只对kTypeXY有效
	PLOTDLL_API void		SetEqualXYScale(bool bEqual);

	// 设置图像边框显示
	PLOTDLL_API void		SetEdgeShow(bool bShow);
	// 设置图像边框显示
	PLOTDLL_API void		SetEdgeRoundConor(bool bRound);
	// 设置图像边框颜色
	PLOTDLL_API void		SetEdgeColor(COLORREF color);
	// 设置图像边框宽度
	PLOTDLL_API void		SetEdgeWidth(int width);

	// 设置饼图单个饼的标题
	PLOTDLL_API void		SetPieTitle(const TCHAR* title, int which);
	// 设置饼图单个饼的颜色
	PLOTDLL_API void		SetPieColor(COLORREF color, int which);

	// 设置柱图单根柱子的标签
	PLOTDLL_API void		SetStemLabel(const TCHAR* label, int which);
	// 设置柱图单个序列的标题
	PLOTDLL_API void		SetStemTitle(const TCHAR* title, int nDataIndex);
	// 设置柱图单根柱子所占比例
	PLOTDLL_API void		SetStemRatio(double ratio);

	// 设置等高线图等高线的数量
	PLOTDLL_API void		SetContourLineNum(int num);
	// 设置等高线图等高线绘制的精度，n越大，精度越高，一般5就可以了
	PLOTDLL_API void		SetContourPrecision(int n);

	// 设置云图的起始颜色
	PLOTDLL_API void		SetContourMapColor1(COLORREF cr);
	// 设置云图的最终颜色
	PLOTDLL_API void		SetContourMapColor2(COLORREF cr);

	// 设置背景网格与哪一个子图绑定
	// 用于共享X轴视图
	PLOTDLL_API void		SetGridBindLayer(int nPlotIndex);
	// 检测子图的网格线
	PLOTDLL_API bool		GetGridLine(bool &MajorH, bool &MajorV, bool &MinorH, bool &MinorV, int nPlotIndex);
	// 检测网格线
	PLOTDLL_API bool		GetGridLine(bool &MajorH, bool &MajorV, bool &MinorH, bool &MinorV);
	// 设置子图网格线的绘制
	PLOTDLL_API void		SetGridLine(bool MajorH, bool MajorV, bool MinorH, bool MinorV, int nPlotIndex);
	// 设置网格线的绘制
	PLOTDLL_API void		SetGridLine(bool MajorH=true, bool MajorV=true, bool MinorH=false, bool MinorV=false);
	// 获取子图背景颜色
	PLOTDLL_API COLORREF	GetBkgndColor(int nPlotIndex);
	// 获取背景颜色
	PLOTDLL_API COLORREF	GetBkgndColor();
	// 设置子图背景颜色
	PLOTDLL_API void		SetBkgndColor(COLORREF color, int nPlotIndex);
	// 设置背景颜色
	PLOTDLL_API void		SetBkgndColor(COLORREF color);

	// 保存子图数据到文件
	PLOTDLL_API bool		WriteToFile(TCHAR *pathName, int nPlotIndex);
	// 保存子图某曲线数据到文件
	PLOTDLL_API bool		WriteToFile(TCHAR *pathName, int nDataIndex, int nPlotIndex);

	// 设置图像整体缩放模式
	PLOTDLL_API void		SetZoomMode(bool zoom);
	// 设置图像整体缩放时X方向的缩放系数
	PLOTDLL_API void		SetZoomFactorX(double fact);
	// 设置图像整体缩放时Y方向的缩放系数
	PLOTDLL_API void		SetZoomFactorY(double fact);
	// 设置图像整体缩放时两个方向的缩放系数
	PLOTDLL_API void		SetZoomFactor(double fact);
	// 设置图像整体缩放时的缩放中心，中心的代号见本文件开始被注释掉的enum
	PLOTDLL_API void		SetZoomCenterMode(int center);

	// 设置三维曲线的网格
	PLOTDLL_API void		SetShowXYMajorGrid( bool show );
	PLOTDLL_API void		SetShowYZMajorGrid( bool show );
	PLOTDLL_API void		SetShowZXMajorGrid( bool show );
	PLOTDLL_API void		SetShowXYMinorGrid( bool show );
	PLOTDLL_API void		SetShowYZMinorGrid( bool show );
	PLOTDLL_API void		SetShowZXMinorGrid( bool show );
	PLOTDLL_API void		SetGridLine(bool MajorXY, bool MinorXY, bool MajorYZ, bool MinorYZ, bool MajorZX, bool MinorZX);

	// 在分层视图和分裂视图中，设置第一层显示左坐标轴，第二层显示右坐标轴
	PLOTDLL_API void		SetLRAxis();
	// 在分层视图中，设置第一层显示下坐标轴，第二层显示上坐标轴
	PLOTDLL_API void		SetTBAxis();
	// 底层函数，获取子图的绘图区域
	PLOTDLL_API RECT		GetPlotRect(int nPlotIndex);
	// 底层函数，获取绘图区域
	PLOTDLL_API RECT		GetPlotRect();
	// 底层函数，获取坐标轴的范围
	PLOTDLL_API void		GetPlotRange(double xRange[2], double yRange[2], int nPlotIndex=0);

	// 设置定时器函数
	PLOTDLL_API void		SetTimerFunc(bool (*pFcnTimer)(void *pChart, void *pVoid), void *pPara);
	// 设置定时器的时间间隔，单位为ms
	PLOTDLL_API void		SetTimerInterval(int interval);
	// 设置定时器的精度，单位为ms，只对高精度定时器起作用
	PLOTDLL_API void		SetTimerResolution(int res);
	
	// 启动定时器
	// 高精度定时器采用多媒体定时器，低精度定时器采用WM_TIMER消息
	PLOTDLL_API void		StartTimer(HWND hWnd, bool bHighRes);
	// 停止定时器
	PLOTDLL_API void		StopTimer(HWND hWnd);
	
	// 获得定时器函数指针
	PLOTDLL_API bool		(*GetTimerFunc( ))( void *pChart, void *pVoid );
	// 获得定时器函数传入参数
	PLOTDLL_API void		*GetTimerPara();
}

#ifdef PLOTDLL_API
#	undef PLOTDLL_API
#endif //PLOTDLL_API

#endif //__CLASSLESS_H_122333444455555__
