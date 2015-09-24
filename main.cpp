#include <iostream>
#include <fstream>

#include "dmtx.h"

using namespace std;

#define DMT_IMAGE_HEIGHT 480
#define DMT_IMAGE_WIDTH  720

int main(int argc, char const *argv[])
{

  DmtxImage      *img;
  DmtxDecode     *dec;
  DmtxRegion     *reg;
  DmtxMessage    *msg;

  unsigned char* pix;
  ifstream::pos_type size;
  ifstream file ("THC(1).dat", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    pix = new unsigned char [size];
    file.seekg (0, ios::beg);
    file.read ((char*)pix, size); // cast to a char* to give to file.read
    file.close();
  }
  else
  cout << "Unable to open file";
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
    printf("dmtxRegionFindNext returned NULLtine\n");
  }
  msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
  dmtxRegionDestroy(&reg);
  dmtxDecodeDestroy(&dec);
  dmtxImageDestroy(&img);




  return 0;
}
