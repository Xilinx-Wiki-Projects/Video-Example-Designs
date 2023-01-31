/******************************************************************************
*
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file vidpatgen.c
*
* This is pattern generator source file
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  mpn   02/24/16   Initial Release
*
* </pre>
*
******************************************************************************/
#include "vidpatgen.h"
#include "xil_printf.h"

//YUV/RGB structure.
typedef struct
{
    //union of luma or red.
    union
    {
        int y; //Luma component.
        int r; //Red component.
    };
    //union of u or green.
    union
    {
        int u; //U chroma component.
        int g; //Green component.
    };
    //union of y or blue.
    union
    {
        int v; //V chroma component.
        int b; //Blue component.
    };
} YUV;
typedef YUV RGB;

#define NUM_BARS 8

RGB tpgBarSelRgb[] = {
    {{0xFFFF}, {0xFFFF}, {0xFFFF}}, // White
    {{0xFFFF}, {0xFFFF}, {0x0000}}, // Yellow
    {{0x0000}, {0xFFFF}, {0xFFFF}}, // Cyan
    {{0x0000}, {0xFFFF}, {0x0000}}, // Green
    {{0xFFFF}, {0x0000}, {0xFFFF}}, // Magenta
    {{0xFFFF}, {0x0000}, {0x0000}}, // Red
    {{0x0000}, {0x0000}, {0xFFFF}}, // Blue
    {{0x0000}, {0x0000}, {0x0000}}  // Black
};

YUV tpgBarSelYuv[] = {
    {{255}, {128}, {128}}, // White
    {{225}, {  0}, {148}}, // Yellow
    {{178}, {170}, {  0}}, // Cyan
    {{149}, { 43}, { 21}}, // Green
    {{105}, {212}, {234}}, // Magenta
    {{ 76}, { 85}, {255}}, // Red
    {{ 29}, {255}, {107}}, // Blue
    {{  0}, {128}, {128}}  // Black
};


void PatGen_ColorBars(char* dst,
		              int width,
		              int height,
		              int stride,
		              int startPos,
		              XVidC_ColorFormat colorSpace)
{
    int barWidth = ((width+7) >> 3);
    int hBarSel = 0;
    int x, y;

    if(colorSpace == XVIDC_CSF_YCRCB_420) {
    	xil_printf("ERR:: Video Pattern Generator does not support YUV420 Color Format\r\n");
    	return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            hBarSel = ((startPos + x) / barWidth) % NUM_BARS;

            RGB pixel;

            if(colorSpace == XVIDC_CSF_RGB) {
                pixel.r = tpgBarSelRgb[hBarSel].r;
                pixel.g = tpgBarSelRgb[hBarSel].g;
                pixel.b = tpgBarSelRgb[hBarSel].b;
            } else {
                pixel.y = tpgBarSelYuv[hBarSel].y;
                pixel.u = tpgBarSelYuv[hBarSel].u;
                pixel.v = tpgBarSelYuv[hBarSel].v;
            }

            if(colorSpace != XVIDC_CSF_YCRCB_422) {
                // 4:4:4
                dst[y*stride + x*4]     = pixel.r;
                dst[y*stride + x*4 + 1] = pixel.g;
                dst[y*stride + x*4 + 2] = pixel.b;
                dst[y*stride + x*4 + 3] = 0;
            } else {
                // 4:2:2
                dst[y*stride + x*2]     = pixel.y;
                dst[y*stride + x*2 + 1] = (x&1) ? pixel.v : pixel.u;
            }
        }
    }
}



void PatGen_ColorBars_1(char* dst,
		              int width,
		              int height,
		              int stride,
		              int startPos,
		              XVidC_ColorFormat colorSpace)
{
    int barWidth = ((width+7) >> 3);
    int hBarSel = 0;
    int x, y;

    if(colorSpace == XVIDC_CSF_YCRCB_420) {
    	xil_printf("ERR:: Video Pattern Generator does not support YUV420 Color Format\r\n");
    	return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            hBarSel = ((startPos + x) / barWidth) % NUM_BARS;

            RGB pixel;

            if(colorSpace == XVIDC_CSF_RGB) {
                pixel.r = tpgBarSelRgb[6].r;
                pixel.g = tpgBarSelRgb[6].g;
                pixel.b = tpgBarSelRgb[6].b;
            } else {
                pixel.y = tpgBarSelYuv[6].y;
                pixel.u = tpgBarSelYuv[6].u;
                pixel.v = tpgBarSelYuv[6].v;
            }

            if(colorSpace != XVIDC_CSF_YCRCB_422) {
                // 4:4:4
                dst[y*stride + x*4]     = 255;
                dst[y*stride + x*4 + 1] = 0;
                dst[y*stride + x*4 + 2] = 0;
                dst[y*stride + x*4 + 3] = 0;
            } else {
                // 4:2:2
                dst[y*stride + x*2]     = pixel.y;
                dst[y*stride + x*2 + 1] = (x&1) ? pixel.v : pixel.u;
            }
        }
    }
}

void PatGen_ColorBars_2(char* dst,
		              int width,
		              int height,
		              int stride,
		              int startPos,
		              XVidC_ColorFormat colorSpace)
{
    int barWidth = ((width+7) >> 3);
    int hBarSel = 0;
    int x, y;

    if(colorSpace == XVIDC_CSF_YCRCB_420) {
    	xil_printf("ERR:: Video Pattern Generator does not support YUV420 Color Format\r\n");
    	return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            hBarSel = ((startPos + x) / barWidth) % NUM_BARS;

            RGB pixel;

            if(colorSpace == XVIDC_CSF_RGB) {
                pixel.r = tpgBarSelRgb[4].r;
                pixel.g = tpgBarSelRgb[4].g;
                pixel.b = tpgBarSelRgb[4].b;
            } else {
                pixel.y = tpgBarSelYuv[4].y;
                pixel.u = tpgBarSelYuv[4].u;
                pixel.v = tpgBarSelYuv[4].v;
            }

            if(colorSpace != XVIDC_CSF_YCRCB_422) {
                // 4:4:4
                dst[y*stride + x*4]     = 0;
                dst[y*stride + x*4 + 1] = 255;
                dst[y*stride + x*4 + 2] = 0;
                dst[y*stride + x*4 + 3] = 0;
            } else {
                // 4:2:2
                dst[y*stride + x*2]     = pixel.y;
                dst[y*stride + x*2 + 1] = (x&1) ? pixel.v : pixel.u;
            }
        }
    }
}


void PatGen_ColorBars_3(char* dst,
		              int width,
		              int height,
		              int stride,
		              int startPos,
		              XVidC_ColorFormat colorSpace)
{
    int barWidth = ((width+7) >> 3);
    int hBarSel = 0;
    int x, y;

    if(colorSpace == XVIDC_CSF_YCRCB_420) {
    	xil_printf("ERR:: Video Pattern Generator does not support YUV420 Color Format\r\n");
    	return;
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            hBarSel = ((startPos + x) / barWidth) % NUM_BARS;

            RGB pixel;

            if(colorSpace == XVIDC_CSF_RGB) {
                pixel.r = tpgBarSelRgb[7].r;
                pixel.g = tpgBarSelRgb[7].g;
                pixel.b = tpgBarSelRgb[7].b;
            } else {
                pixel.y = tpgBarSelYuv[7].y;
                pixel.u = tpgBarSelYuv[7].u;
                pixel.v = tpgBarSelYuv[7].v;
            }

            if(colorSpace != XVIDC_CSF_YCRCB_422) {
                // 4:4:4
                dst[y*stride + x*4]     = 0;
                dst[y*stride + x*4 + 1] = 0;
                dst[y*stride + x*4 + 2] = 255;
                dst[y*stride + x*4 + 3] = 0;
            } else {
                // 4:2:2
                dst[y*stride + x*2]     = pixel.y;
                dst[y*stride + x*2 + 1] = (x&1) ? pixel.v : pixel.u;
            }
        }
    }
}
