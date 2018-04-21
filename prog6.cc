/*
Jennifer Utley
jau100020@utdallas.edu
SE 3377.501
Program 6, a C++ program that reads a binary file and outputs the contents to a matrix
*/

#include <iostream>
#include <string>
#include <sstream> //for converting file contents to strings
#include <fstream>
#include <iomanip>
#include <stdint.h> //for uint32_t, etc
#include <stdio.h>
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25 //accommodates the maxRecordStringLength variable in the binary file
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

//defining two classes globally for use in reading binary file header and data records
class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


int main ()
{

  //setting up the matrix
  WINDOW    *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;

  //setting up the row and column headings and sizes
  const char *rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c", "d", "e"};
  const char *columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  //start the CDK screen, check for putty window size, start CDK colors
  window = initscr();
  cdkscreen = initCDKScreen(window);
  initCDKColor();

  //define the matrix
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
	    MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
	    boxTypes, 1, 1, ' ', ROW, true, true, false);

  //quit if failed to create the matrix properly
  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      exit(1);
      }
  
  //draw the matrix
  drawCDKMatrix(myMatrix, true);

  //reading the binary file
  //creating objects for the header record and data records
  BinaryFileHeader *headerRecord = new BinaryFileHeader();
  BinaryFileRecord *dataRecord = new BinaryFileRecord();

  //opening the binary file for input
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  //reading headerRecord
  binInfile.read((char *) headerRecord, sizeof(BinaryFileHeader));

  //holding these values in variables
  uint32_t magNum = headerRecord->magicNumber;
  uint32_t verNum = headerRecord->versionNumber;
  uint64_t numRecNum = headerRecord->numRecords;

  //converting numbers to string for displaying in the matrix
  ostringstream convert;
  ostringstream convert2;
  ostringstream convert3;
  convert << magNum;
  string magic = "Magic: " + convert.str();
  convert2 << verNum;
  string version = "Version: " + convert2.str();
  convert3 << numRecNum;
  string numRec = "NumRecords: " + convert3.str();

  //populate the first row's cells; arguments are matrix, row, column, then message to display (const char*) for arguments
  setCDKMatrixCell(myMatrix, 1, 1, magic.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRec.c_str());

  //loop for reading first four dataRecords
  int row = 2;
  int j = 0;
  ostringstream convertData[5];

  for (int i=0; i<4; i++)
    {
      binInfile.read((char *) dataRecord, sizeof(BinaryFileRecord));

      //holding these values in variables
      int strLenNum = (unsigned)strlen(dataRecord->stringBuffer);
      string stringContents = dataRecord->stringBuffer;

      //converting numbers to string for displaying in the matrix
      convertData[j] << strLenNum;
      string strLen = "Strlen: " + convertData[j].str();
      
      setCDKMatrixCell(myMatrix, row, 1, strLen.c_str());
      setCDKMatrixCell(myMatrix, row, 2, stringContents.c_str());
      
      row = row + 1;
      j++; 
   }
   binInfile.close();
 
  //now draw the matrix with the cells filled with contents from binary file
  drawCDKMatrix(myMatrix, true);

  //pause to view contents then close
  sleep (10);
  endCDK();

}
  
