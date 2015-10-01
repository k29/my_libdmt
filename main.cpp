#include <iostream>
#include <fstream>
#include <time.h>

#include "dmtx.h"

using namespace std;

#define DMT_IMAGE_HEIGHT 480
#define DMT_IMAGE_WIDTH  720

int main(int argc, char const *argv[])
{
  clock_t start, end;
  double cpu_time_used;

  DmtxImage      *img;
  DmtxDecode     *dec;
  DmtxRegion     *reg;
  DmtxMessage    *msg;

  unsigned char* pix;
  ifstream::pos_type size;
  int n;
  ifstream file ("THC(1).dat", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    pix = new unsigned char [size];
    file.seekg (0, ios::beg);
    file.read ((char*)pix, size); // cast to a char* to give to file.read
    n=size;
    file.close();
  }
  else
  cout << "Unable to open file";

  for(int i=0;i<n;i++)
  {
    cout<<(int)pix[i]<<endl;
  }

  start=clock();

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

  int totalBytes, headerBytes;
  unsigned char* pnm;
  FILE *fp;
  fp=fopen("debug.pnm","wb");
  pnm = dmtxDecodeCreateDiagnostic(dec, &totalBytes, &headerBytes, 0);
  if(pnm==NULL)
    printf("Unable to create diagnostic image \n");
  fwrite(pnm, sizeof(unsigned char), totalBytes, fp);
  fclose(fp);

  reg = dmtxRegionFindNext(dec, NULL);
  if(reg == NULL)
  {
    printf("dmtxRegionFindNext returned NULLtine\n");
  }

  msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);

  if(msg != NULL)
  {
    fputs("output: \"", stdout);
    fwrite(msg->output, sizeof(unsigned char), msg->outputIdx, stdout);
    fputs("\"\n", stdout);
    dmtxMessageDestroy(&msg);
  }
  end=clock();
  dmtxRegionDestroy(&reg);
  dmtxDecodeDestroy(&dec);
  dmtxImageDestroy(&img);

  cpu_time_used=(((double)(end-start))/CLOCKS_PER_SEC);

  cout<<cpu_time_used<<endl;


  return 0;
}
