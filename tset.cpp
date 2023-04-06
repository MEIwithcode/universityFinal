///////////////////////////////////////////////////////////////////////////////
// File generated by HDevelop for HALCON/C++ Version 20.05.0.0
// Non-ASCII strings in this file are encoded in local-8-bit encoding (cp936).
// Ensure that the interface encoding is set to locale encoding by calling
// SetHcppInterfaceStringEncodingIsUtf8(false) at the beginning of the program.
// 
// Please note that non-ASCII characters in string constants are exported
// as octal codes in order to guarantee that the strings are correctly
// created on all systems, independent on any compiler settings.
// 
// Source files with different encoding should not be mixed in one project.
///////////////////////////////////////////////////////////////////////////////



#ifndef __APPLE__
#  include "HalconCpp.h"
#  include "HDevThread.h"
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCONCpp/HalconCpp.h>
#    include <HALCONCpp/HDevThread.h>
#    include <HALCON/HpThread.h>
#  else
#    include <HALCONCppxl/HalconCpp.h>
#    include <HALCONCppxl/HDevThread.h>
#    include <HALCONxl/HpThread.h>
#  endif
#  include <stdio.h>
#  include <CoreFoundation/CFRunLoop.h>
#endif



using namespace HalconCpp;


#ifndef NO_EXPORT_MAIN
// Main procedure 
void action()
{

  // Local iconic variables
  HObject  ho_Image, ho_Rectangle, ho_ImageReduced;
  HObject  ho_Region, ho_ConnectedRegions, ho_SelectedRegions;

  // Local control variables
  HTuple  hv_Width, hv_Height, hv_WindowHandle;
  HTuple  hv_Ra, hv_Rb, hv_Phi, hv_Area, hv_Row, hv_Column;
  HTuple  hv_mean_radius, hv_variance_radius;

  //计算散热孔半径和方差

  //读取图片
  ReadImage(&ho_Image, "progres");

  //获取图像大小
  GetImageSize(ho_Image, &hv_Width, &hv_Height);

  //打开窗口
  SetWindowAttr("background_color","black");
  OpenWindow(0,0,hv_Width,hv_Height,0,"visible","",&hv_WindowHandle);
  HDevWindowStack::Push(hv_WindowHandle);

  //显示图像
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Image, HDevWindowStack::GetActive());

  //设置显示颜色
  if (HDevWindowStack::IsOpen())
    SetColor(HDevWindowStack::GetActive(),"red");
  //设置区域填充方式 显示边缘
  if (HDevWindowStack::IsOpen())
    SetDraw(HDevWindowStack::GetActive(),"margin");

  //设置矩形ROI
  GenRectangle1(&ho_Rectangle, 260, 90, 360, 350);

  //图像裁剪
  ReduceDomain(ho_Image, ho_Rectangle, &ho_ImageReduced);

  //二值化
  Threshold(ho_ImageReduced, &ho_Region, 0, 150);

  //连通域处理
  Connection(ho_Region, &ho_ConnectedRegions);

  //根据面积过滤
  SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 10, 100);

  //获取等效椭圆参数
  EllipticAxis(ho_SelectedRegions, &hv_Ra, &hv_Rb, &hv_Phi);

  //获取区域面积的中心坐标
  AreaCenter(ho_SelectedRegions, &hv_Area, &hv_Row, &hv_Column);

  //重新显示图像
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Image, HDevWindowStack::GetActive());

  //设置显示颜色
  if (HDevWindowStack::IsOpen())
    SetColor(HDevWindowStack::GetActive(),"green");

  //显示区域
  if (HDevWindowStack::IsOpen())
    DispObj(ho_SelectedRegions, HDevWindowStack::GetActive());

  //半径求平均 求和/个数
  hv_mean_radius = (hv_Ra.TupleSum())/(hv_Ra.TupleLength());

  //方差 (半径-平均值)平方/个数
  hv_variance_radius = (((hv_Ra-hv_mean_radius)*(hv_Ra-hv_mean_radius)).TupleSum())/((hv_Ra.TupleLength())-1);


}


#ifndef NO_EXPORT_APP_MAIN

#ifdef __APPLE__
// On OS X systems, we must have a CFRunLoop running on the main thread in
// order for the HALCON graphics operators to work correctly, and run the
// action function in a separate thread. A CFRunLoopTimer is used to make sure
// the action function is not called before the CFRunLoop is running.
// Note that starting with macOS 10.12, the run loop may be stopped when a
// window is closed, so we need to put the call to CFRunLoopRun() into a loop
// of its own.
HTuple      gStartMutex;
H_pthread_t gActionThread;
HBOOL       gTerminate = FALSE;

static void timer_callback(CFRunLoopTimerRef timer, void *info)
{
  UnlockMutex(gStartMutex);
}

static Herror apple_action(void **parameters)
{
  // Wait until the timer has fired to start processing.
  LockMutex(gStartMutex);
  UnlockMutex(gStartMutex);

  try
  {
    action();
  }
  catch (HException &exception)
  {
    fprintf(stderr,"  Error #%u in %s: %s\n", exception.ErrorCode(),
            (const char *)exception.ProcName(),
            (const char *)exception.ErrorMessage());
  }

  // Tell the main thread to terminate itself.
  LockMutex(gStartMutex);
  gTerminate = TRUE;
  UnlockMutex(gStartMutex);
  CFRunLoopStop(CFRunLoopGetMain());
  return H_MSG_OK;
}

static int apple_main(int argc, char *argv[])
{
  Herror                error;
  CFRunLoopTimerRef     Timer;
  CFRunLoopTimerContext TimerContext = { 0, 0, 0, 0, 0 };

  CreateMutex("type","sleep",&gStartMutex);
  LockMutex(gStartMutex);

  error = HpThreadHandleAlloc(&gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleAlloc failed: %d\n", error);
    exit(1);
  }

  error = HpThreadCreate(gActionThread,0,apple_action);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadCreate failed: %d\n", error);
    exit(1);
  }

  Timer = CFRunLoopTimerCreate(kCFAllocatorDefault,
                               CFAbsoluteTimeGetCurrent(),0,0,0,
                               timer_callback,&TimerContext);
  if (!Timer)
  {
    fprintf(stderr,"CFRunLoopTimerCreate failed\n");
    exit(1);
  }
  CFRunLoopAddTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);

  for (;;)
  {
    HBOOL terminate;

    CFRunLoopRun();

    LockMutex(gStartMutex);
    terminate = gTerminate;
    UnlockMutex(gStartMutex);

    if (terminate)
      break;
  }

  CFRunLoopRemoveTimer(CFRunLoopGetCurrent(),Timer,kCFRunLoopCommonModes);
  CFRelease(Timer);

  error = HpThreadHandleFree(gActionThread);
  if (H_MSG_OK != error)
  {
    fprintf(stderr,"HpThreadHandleFree failed: %d\n", error);
    exit(1);
  }

  ClearMutex(gStartMutex);
  return 0;
}
#endif

int main(int argc, char *argv[])
{
  int ret = 0;

  try
  {
#if defined(_WIN32)
    SetSystem("use_window_thread", "true");
#endif

    // file was stored with local-8-bit encoding
    //   -> set the interface encoding accordingly
    SetHcppInterfaceStringEncodingIsUtf8(false);

    // Default settings used in HDevelop (can be omitted)
    SetSystem("width", 512);
    SetSystem("height", 512);

#ifndef __APPLE__
    action();
#else
    ret = apple_main(argc,argv);
#endif
  }
  catch (HException &exception)
  {
    fprintf(stderr,"  Error #%u in %s: %s\n", exception.ErrorCode(),
            (const char *)exception.ProcName(),
            (const char *)exception.ErrorMessage());
    ret = 1;
  }
  return ret;
}

#endif


#endif


