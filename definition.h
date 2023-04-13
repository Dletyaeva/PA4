/*contains definitions of both regular functions and structs
*/
#ifndef DEFINITION_H
#define DEFINITION_H

//pre-reads the input file to figure out how many rows it has ==> how big general array needs to be
int getFileRows(char *BUFFER, FILE *inputFile);

/*opens file in funciton
* process file by read input file line by line and store info in seperately
* closes file once done reading
*/
void subdivideCarsFromInput(char const *inFILE, Car **carArray, int const SIZE_ELE, int const SIZE_ARR, char *BUFFER);

//sorts the old car array into a new array with cars that have positive drag area
int countPositive(Car **carArray, int const SIZE_ARR, int const SIZE_ELE);

   
//sort the old array into new one
//put into a function later
void eliminateCars(int count, int const SIZE_ELE, int const SIZE_ARR, Car **carArray, Car **sortedArray);
/*
* computes the power for each car using the array VEL that has the values for
* 60, 70 and 80 and copies the information to sortedArray using magic of type conversions 
* note this function does not take individual values for MPH instead they are provided in VEL 
* in which they are then immediately converted to M/S
*/
void computePower(Car **sortedArray, int count,double *VEL);

//writes the data from Array to txt file
void printToOutputFile(Car **sortedArray, int count, FILE *outputFile);

#endif