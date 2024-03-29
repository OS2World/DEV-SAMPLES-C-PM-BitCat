//================================================
// bitcat2.c : Bitmap demonstration for PM sample.
// Version: 1.02
// License: 3-Clause BSD License
// Authors:
// - Martin Iturbide, 2022
// - Dave Yeo, 2022
// - Charles Petzold, 1999 
//================================================
#define INCL_WIN
#define INCL_GPI

#include <os2.h>

#include <stdlib.h>
#include "BitCat2.h"


MRESULT EXPENTRY ClientWndProc(HWND, ULONG, MPARAM, MPARAM);

HAB                     hab;




int main(void)
   {
      static unsigned char     	szClientClass[] = "BitCat2";
      static ULONG      	flFrameFlags = 	FCF_TITLEBAR      | FCF_SYSMENU  |
						FCF_SIZEBORDER    | FCF_MINMAX   |
						FCF_SHELLPOSITION | FCF_TASKLIST;


      HMQ               hmq;
      HWND              hwndFrame,
                        hwndClient;

      QMSG              qmsg;



      hab = WinInitialize(0);
      hmq = WinCreateMsgQueue(hab, 0);

      WinRegisterClass(hab, szClientClass, ClientWndProc, CS_SIZEREDRAW, 0);

      hwndFrame = WinCreateStdWindow(HWND_DESKTOP, WS_VISIBLE,
                                     &flFrameFlags, szClientClass, NULL,
                                     0L, 0, 0, &hwndClient);

      while ( WinGetMsg(hab, &qmsg, 0, 0, 0) )
            WinDispatchMsg(hab, &qmsg);

      WinDestroyWindow(hwndFrame);
      WinDestroyMsgQueue(hmq);
      WinTerminate(hab);
      return(0);
   }


MRESULT EXPENTRY ClientWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
   {
      static HBITMAP    hbm;
      static HDC        hdcMemory;
      static HPS        hpsMemory;
      static LONG       cxClient,
                        cyClient;
      BITMAPINFO2       *pbmi;
      BITMAPINFOHEADER2 bmp;
      HPS               hps;
      POINTL            aptl[4];
      SIZEL             sizl;



      switch(msg)
         {
            case WM_CREATE:
                  hdcMemory = DevOpenDC(hab, OD_MEMORY, (PSZ)"*", 0L, NULL, 0);

                  sizl.cx = 0;
                  sizl.cy = 0;

                  hpsMemory = GpiCreatePS(hab, hdcMemory, &sizl,
                                          PU_PELS     | GPIF_DEFAULT |
                                          GPIT_MICRO  | GPIA_ASSOC);

                  bmp.cbFix      = sizeof(bmp);
                  bmp.cx         = 32;
                  bmp.cy         = 32;
                  bmp.cPlanes    = 1;
                  bmp.cBitCount  = 1;

                  hbm = GpiCreateBitmap(hpsMemory, &bmp, 0L, NULL, NULL);

                  GpiSetBitmap(hpsMemory, hbm);

                  pbmi = malloc(sizeof(BITMAPINFO) + sizeof(RGB));
                  pbmi->cbFix       = sizeof(bmp);
                  pbmi->cy          = 32;
                  pbmi->cx          = 32;
                  pbmi->cPlanes     = 1;
                  pbmi->cBitCount   = 1;

                  pbmi->argbColor[0].bBlue   = 0;
                  pbmi->argbColor[0].bGreen  = 0;
                  pbmi->argbColor[0].bRed    = 0;
                  pbmi->argbColor[1].bBlue   = 0xff;
                  pbmi->argbColor[1].bGreen  = 0xff;
                  pbmi->argbColor[1].bRed    = 0xff;

                  GpiSetBitmapBits(hpsMemory, 0L, 32L, abBitCat, pbmi);

                  free(pbmi);
                  return(0);

            case WM_SIZE:
                  cxClient = SHORT1FROMMP(mp2);
                  cyClient = SHORT2FROMMP(mp2);
                  return(0);

            case WM_PAINT:
                  hps = WinBeginPaint(hwnd, 0, NULL);

                  aptl[0].x = 0;
                  aptl[0].y = 0;

                  aptl[1].x = cxClient;
                  aptl[1].y = cyClient;

                  aptl[2].x = 0;
                  aptl[2].y = 0;

                  aptl[3].x = 32;
                  aptl[3].y = 32;

                  GpiBitBlt(hps, hpsMemory, 4L, aptl, ROP_SRCCOPY, BBO_AND);

                  aptl[1] = aptl[3];

                  GpiBitBlt(hps, hpsMemory, 3L, aptl, ROP_SRCCOPY, BBO_AND);

                  WinEndPaint(hps);
                  return(0);

            case WM_DESTROY:
                  GpiDestroyPS(hpsMemory);
                  DevCloseDC(hdcMemory);
                  GpiDeleteBitmap(hbm);
                  return(0);
         }
      return(WinDefWindowProc(hwnd, msg, mp1, mp2));
   }

