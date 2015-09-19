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
  int n;
  ifstream file ("THC.dat", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    pix = new unsigned char [size];
    file.seekg (0, ios::beg);
    file.read ((char*)pix, size); // cast to a char* to give to file.read
    // for (int l=0; l<size; l++)
    // {
    //   cout <<  (int)pix[l] << endl;
    // }
    n=size;
    file.close();
    // delete[] pix;
  }
  else
  cout << "Unable to open file";

  for(int i=0;i<n;i++)
  {
    cout<<(int)pix[i]<<endl;
  }


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

  /*
  To test if this is happening, try using the dmtxDecodeCreateDiagnostic() function in your program after the calls to dmtxImageCreate() and dmtxImageSetProp().
  This function will return a pointer to a copy of your image in PNM format, which your program can write to the filesystem to be viewed with any image viewer.
  At that point it should be immediately apparent if there is a mapping issue somewhere.
  Check out the WriteDiagnosticImage() function in dmtxread.c to see a working example of this function being used.
  If you find that your image appears upside-down, add the following call after dmtxImageCreate():
  dmtxImageSetProp(img, DmtxPropImageFlip, DmtxFlipY);
  */
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int totalBytes, headerBytes;
  unsigned char* pnm;
  FILE *fp;
  fp=fopen("debug.pnm","wb");
  pnm = dmtxDecodeCreateDiagnostic(dec, &totalBytes, &headerBytes, 0);
  if(pnm==NULL)
    printf("Unable to create diagnostic image \n");
  fwrite(pnm, sizeof(unsigned char), totalBytes, fp);
  fclose(fp);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


  return 0;
}
