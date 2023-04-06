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

// Procedure declarations 
// External procedures 
// Chapter: Graphics / Text
// Short Description: This procedure displays 'Click 'Run' to continue' in the lower right corner of the screen. 
void disp_continue_message (HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box);
// Chapter: Graphics / Text
// Short Description: This procedure writes one or multiple text messages. 
void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
    HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
// Chapter: Graphics / Text
// Short Description: Set font independent of OS 
void set_display_font (HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, HTuple hv_Bold, 
    HTuple hv_Slant);

// Procedures 
// External procedures 
// Chapter: Graphics / Text
// Short Description: This procedure displays 'Click 'Run' to continue' in the lower right corner of the screen. 
void disp_continue_message (HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_GenParamName, hv_GenParamValue, hv_ContinueMessage;

  //This procedure displays 'Press Run (F5) to continue' in the
  //lower right corner of the screen.
  //It uses the procedure disp_message.
  //
  //Input parameters:
  //WindowHandle: The window, where the text shall be displayed
  //Color: defines the text color.
  //   If set to '' or 'auto', the currently set color is used.
  //Box: If set to 'true', the text is displayed in a box.
  //
  //Convert the parameter Box to generic parameters.
  hv_GenParamName = HTuple();
  hv_GenParamValue = HTuple();
  if (0 != (int((hv_Box.TupleLength())>0)))
  {
    if (0 != (int(HTuple(hv_Box[0])==HTuple("false"))))
    {
      //Display no box
      hv_GenParamName = hv_GenParamName.TupleConcat("box");
      hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
    }
    else if (0 != (int(HTuple(hv_Box[0])!=HTuple("true"))))
    {
      //Set a color other than the default.
      hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
      hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[0]));
    }
  }
  if (0 != (int((hv_Box.TupleLength())>1)))
  {
    if (0 != (int(HTuple(hv_Box[1])==HTuple("false"))))
    {
      //Display no shadow.
      hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
      hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
    }
    else if (0 != (int(HTuple(hv_Box[1])!=HTuple("true"))))
    {
      //Set a shadow color other than the default.
      hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
      hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[1]));
    }
  }
  //
  if (0 != (int(hv_Color==HTuple(""))))
  {
    //disp_text does not accept an empty string for Color.
    hv_Color = HTuple();
  }
  //
  //Display the message.
  hv_ContinueMessage = "Press Run (F5) to continue";
  DispText(hv_WindowHandle, hv_ContinueMessage, "window", "bottom", "right", hv_Color, 
      hv_GenParamName, hv_GenParamValue);
  return;
}

// Chapter: Graphics / Text
// Short Description: This procedure writes one or multiple text messages. 
void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
    HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_GenParamName, hv_GenParamValue;

  //This procedure displays text in a graphics window.
  //
  //Input parameters:
  //WindowHandle: The WindowHandle of the graphics window, where
  //   the message should be displayed.
  //String: A tuple of strings containing the text messages to be displayed.
  //CoordSystem: If set to 'window', the text position is given
  //   with respect to the window coordinate system.
  //   If set to 'image', image coordinates are used.
  //   (This may be useful in zoomed images.)
  //Row: The row coordinate of the desired text position.
  //   You can pass a single value or a tuple of values.
  //   See the explanation below.
  //   Default: 12.
  //Column: The column coordinate of the desired text position.
  //   You can pass a single value or a tuple of values.
  //   See the explanation below.
  //   Default: 12.
  //Color: defines the color of the text as string.
  //   If set to [] or '' the currently set color is used.
  //   If a tuple of strings is passed, the colors are used cyclically
  //   for every text position defined by Row and Column,
  //   or every new text line in case of |Row| == |Column| == 1.
  //Box: A tuple controlling a possible box surrounding the text.
  //   Its entries:
  //   - Box[0]: Controls the box and its color. Possible values:
  //     -- 'true' (Default): An orange box is displayed.
  //     -- 'false': No box is displayed.
  //     -- color string: A box is displayed in the given color, e.g., 'white', '#FF00CC'.
  //   - Box[1] (Optional): Controls the shadow of the box. Possible values:
  //     -- 'true' (Default): A shadow is displayed in
  //               darker orange if Box[0] is not a color and in 'white' otherwise.
  //     -- 'false': No shadow is displayed.
  //     -- color string: A shadow is displayed in the given color, e.g., 'white', '#FF00CC'.
  //
  //It is possible to display multiple text strings in a single call.
  //In this case, some restrictions apply on the
  //parameters String, Row, and Column:
  //They can only have either 1 entry or n entries.
  //Behavior in the different cases:
  //   - Multiple text positions are specified, i.e.,
  //       - |Row| == n, |Column| == n
  //       - |Row| == n, |Column| == 1
  //       - |Row| == 1, |Column| == n
  //     In this case we distinguish:
  //       - |String| == n: Each element of String is displayed
  //                        at the corresponding position.
  //       - |String| == 1: String is displayed n times
  //                        at the corresponding positions.
  //   - Exactly one text position is specified,
  //      i.e., |Row| == |Column| == 1:
  //      Each element of String is display in a new textline.
  //
  //
  //Convert the parameters for disp_text.
  if (0 != (HTuple(int(hv_Row==HTuple())).TupleOr(int(hv_Column==HTuple()))))
  {
    return;
  }
  if (0 != (int(hv_Row==-1)))
  {
    hv_Row = 12;
  }
  if (0 != (int(hv_Column==-1)))
  {
    hv_Column = 12;
  }
  //
  //Convert the parameter Box to generic parameters.
  hv_GenParamName = HTuple();
  hv_GenParamValue = HTuple();
  if (0 != (int((hv_Box.TupleLength())>0)))
  {
    if (0 != (int(HTuple(hv_Box[0])==HTuple("false"))))
    {
      //Display no box
      hv_GenParamName = hv_GenParamName.TupleConcat("box");
      hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
    }
    else if (0 != (int(HTuple(hv_Box[0])!=HTuple("true"))))
    {
      //Set a color other than the default.
      hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
      hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[0]));
    }
  }
  if (0 != (int((hv_Box.TupleLength())>1)))
  {
    if (0 != (int(HTuple(hv_Box[1])==HTuple("false"))))
    {
      //Display no shadow.
      hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
      hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
    }
    else if (0 != (int(HTuple(hv_Box[1])!=HTuple("true"))))
    {
      //Set a shadow color other than the default.
      hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
      hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[1]));
    }
  }
  //Restore default CoordSystem behavior.
  if (0 != (int(hv_CoordSystem!=HTuple("window"))))
  {
    hv_CoordSystem = "image";
  }
  //
  if (0 != (int(hv_Color==HTuple(""))))
  {
    //disp_text does not accept an empty string for Color.
    hv_Color = HTuple();
  }
  //
  DispText(hv_WindowHandle, hv_String, hv_CoordSystem, hv_Row, hv_Column, hv_Color, 
      hv_GenParamName, hv_GenParamValue);
  return;
}

// Chapter: Graphics / Text
// Short Description: Set font independent of OS 
void set_display_font (HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, HTuple hv_Bold, 
    HTuple hv_Slant)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_OS, hv_Fonts, hv_Style, hv_Exception;
  HTuple  hv_AvailableFonts, hv_Fdx, hv_Indices;

  //This procedure sets the text font of the current window with
  //the specified attributes.
  //
  //Input parameters:
  //WindowHandle: The graphics window for which the font will be set
  //Size: The font size. If Size=-1, the default of 16 is used.
  //Bold: If set to 'true', a bold font is used
  //Slant: If set to 'true', a slanted font is used
  //
  GetSystem("operating_system", &hv_OS);
  if (0 != (HTuple(int(hv_Size==HTuple())).TupleOr(int(hv_Size==-1))))
  {
    hv_Size = 16;
  }
  if (0 != (int((hv_OS.TupleSubstr(0,2))==HTuple("Win"))))
  {
    //Restore previous behaviour
    hv_Size = (1.13677*hv_Size).TupleInt();
  }
  else
  {
    hv_Size = hv_Size.TupleInt();
  }
  if (0 != (int(hv_Font==HTuple("Courier"))))
  {
    hv_Fonts.Clear();
    hv_Fonts[0] = "Courier";
    hv_Fonts[1] = "Courier 10 Pitch";
    hv_Fonts[2] = "Courier New";
    hv_Fonts[3] = "CourierNew";
    hv_Fonts[4] = "Liberation Mono";
  }
  else if (0 != (int(hv_Font==HTuple("mono"))))
  {
    hv_Fonts.Clear();
    hv_Fonts[0] = "Consolas";
    hv_Fonts[1] = "Menlo";
    hv_Fonts[2] = "Courier";
    hv_Fonts[3] = "Courier 10 Pitch";
    hv_Fonts[4] = "FreeMono";
    hv_Fonts[5] = "Liberation Mono";
  }
  else if (0 != (int(hv_Font==HTuple("sans"))))
  {
    hv_Fonts.Clear();
    hv_Fonts[0] = "Luxi Sans";
    hv_Fonts[1] = "DejaVu Sans";
    hv_Fonts[2] = "FreeSans";
    hv_Fonts[3] = "Arial";
    hv_Fonts[4] = "Liberation Sans";
  }
  else if (0 != (int(hv_Font==HTuple("serif"))))
  {
    hv_Fonts.Clear();
    hv_Fonts[0] = "Times New Roman";
    hv_Fonts[1] = "Luxi Serif";
    hv_Fonts[2] = "DejaVu Serif";
    hv_Fonts[3] = "FreeSerif";
    hv_Fonts[4] = "Utopia";
    hv_Fonts[5] = "Liberation Serif";
  }
  else
  {
    hv_Fonts = hv_Font;
  }
  hv_Style = "";
  if (0 != (int(hv_Bold==HTuple("true"))))
  {
    hv_Style += HTuple("Bold");
  }
  else if (0 != (int(hv_Bold!=HTuple("false"))))
  {
    hv_Exception = "Wrong value of control parameter Bold";
    throw HException(hv_Exception);
  }
  if (0 != (int(hv_Slant==HTuple("true"))))
  {
    hv_Style += HTuple("Italic");
  }
  else if (0 != (int(hv_Slant!=HTuple("false"))))
  {
    hv_Exception = "Wrong value of control parameter Slant";
    throw HException(hv_Exception);
  }
  if (0 != (int(hv_Style==HTuple(""))))
  {
    hv_Style = "Normal";
  }
  QueryFont(hv_WindowHandle, &hv_AvailableFonts);
  hv_Font = "";
  {
  HTuple end_val48 = (hv_Fonts.TupleLength())-1;
  HTuple step_val48 = 1;
  for (hv_Fdx=0; hv_Fdx.Continue(end_val48, step_val48); hv_Fdx += step_val48)
  {
    hv_Indices = hv_AvailableFonts.TupleFind(HTuple(hv_Fonts[hv_Fdx]));
    if (0 != (int((hv_Indices.TupleLength())>0)))
    {
      if (0 != (int(HTuple(hv_Indices[0])>=0)))
      {
        hv_Font = HTuple(hv_Fonts[hv_Fdx]);
        break;
      }
    }
  }
  }
  if (0 != (int(hv_Font==HTuple(""))))
  {
    throw HException("Wrong value of control parameter Font");
  }
  hv_Font = (((hv_Font+"-")+hv_Style)+"-")+hv_Size;
  SetFont(hv_WindowHandle, hv_Font);
  return;
}

#ifndef NO_EXPORT_MAIN
// Main procedure 
void action()
{

  // Local iconic variables
  HObject  ho_Clip, ho_Dark, ho_Single, ho_Selected;

  // Local control variables
  HTuple  hv_Width, hv_Height, hv_WindowID, hv_UsedThreshold;
  HTuple  hv_Phi, hv_Area, hv_Row, hv_Column, hv_Length;

  //clip.hdev: Orientation of clips
  //
  // dev_update_window(...); only in hdevelop
  ReadImage(&ho_Clip, "clip");
  GetImageSize(ho_Clip, &hv_Width, &hv_Height);
  if (HDevWindowStack::IsOpen())
    CloseWindow(HDevWindowStack::Pop());
  SetWindowAttr("background_color","black");
  OpenWindow(0,0,hv_Width/2,hv_Height/2,0,"visible","",&hv_WindowID);
  HDevWindowStack::Push(hv_WindowID);
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Clip, HDevWindowStack::GetActive());
  set_display_font(hv_WindowID, 14, "mono", "true", "false");
  disp_continue_message(hv_WindowID, "black", "true");
  // stop(...); only in hdevelop
  BinaryThreshold(ho_Clip, &ho_Dark, "max_separability", "dark", &hv_UsedThreshold);
  Connection(ho_Dark, &ho_Single);
  SelectShape(ho_Single, &ho_Selected, "area", "and", 5000, 10000);
  if (HDevWindowStack::IsOpen())
    SetDraw(HDevWindowStack::GetActive(),"fill");
  if (HDevWindowStack::IsOpen())
    SetColored(HDevWindowStack::GetActive(),12);
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Selected, HDevWindowStack::GetActive());
  disp_continue_message(hv_WindowID, "black", "true");
  // stop(...); only in hdevelop
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Clip, HDevWindowStack::GetActive());
  if (HDevWindowStack::IsOpen())
    SetColor(HDevWindowStack::GetActive(),"green");
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Selected, HDevWindowStack::GetActive());
  OrientationRegion(ho_Selected, &hv_Phi);
  AreaCenter(ho_Selected, &hv_Area, &hv_Row, &hv_Column);
  if (HDevWindowStack::IsOpen())
    SetLineWidth(HDevWindowStack::GetActive(),3);
  if (HDevWindowStack::IsOpen())
    SetDraw(HDevWindowStack::GetActive(),"margin");
  hv_Length = 80;
  if (HDevWindowStack::IsOpen())
    SetColor(HDevWindowStack::GetActive(),"blue");
  DispArrow(hv_WindowID, hv_Row, hv_Column, hv_Row-(hv_Length*(hv_Phi.TupleSin())), 
      hv_Column+(hv_Length*(hv_Phi.TupleCos())), 4);
  disp_message(hv_WindowID, ((hv_Phi.TupleDeg()).TupleString("3.1f"))+" deg", "image", 
      hv_Row, hv_Column-100, "black", "false");
  // dev_update_window(...); only in hdevelop
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


