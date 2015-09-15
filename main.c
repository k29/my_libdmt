#include <stdio.h>
#include <stdlib.h>
#include "dmtx.h"

#define DMT_IMAGE_HEIGHT 480
#define DMT_IMAGE_WIDTH  720

int main(int argc, char const *argv[])
{
  DmtxEncode     *enc;
  DmtxImage      *img;
  DmtxDecode     *dec;
  DmtxRegion     *reg;
  DmtxMessage    *msg;

  char *pix;

  //TODO: pix=pPECFrame;

  /*Creates and Initializes a new DmtxImage structure using pixel data passed as a parameter.*/
		img = dmtxImageCreate(pix,DMT_IMAGE_WIDTH, DMT_IMAGE_HEIGHT, DmtxPack8bppK);
		if(img == NULL)
		{
			printf("dmtxImageCreate returned NULL\n");
		}

		dec = dmtxDecodeCreate(img, 1);
		if(dec == NULL)
		{
			printf("dmtxDecodeCreate returned NULL\n");
		}

		reg = dmtxRegionFindNext(dec, NULL);
		if(reg == NULL)
		{
			printf("dmtxRegionFindNext returned NULL\n");
		}

		msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);

		if(msg != NULL)
		{
			printf("Output: %u\n", *msg->output );
			dmtxMessageDestroy(&msg);
		}
		dmtxRegionDestroy(&reg);


		dmtxDecodeDestroy(&dec);
		dmtxImageDestroy(&img);
		free(pix);

  return 0;
}
