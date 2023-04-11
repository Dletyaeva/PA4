#include "functions.c" //containts all the functions from this program

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * Authors: Daleela Letyaeva
*/

void main (int argc, char **argv){
    double const MPH[4] = {60.0, 70.0, 80.0}; //also the velocity in the equation

    //check that user enters in/out file name
    if(argc != 3){ //FIXME LATER
    printf("Usage: enter input file name and output filename after %s\n", argv[0]);
    exit(1);
    }

    //try to avoid user from confusing the 2 files
    if(strcmp(argv[1],argv[2])== 0){
    printf("please enter different output file name.");
    }
    
    //read input file
    char const *inFILE = argv[1];
    FILE *inputFile = fopen(inFILE, "r");
    

   //check for file not to be empty
    if(inputFile == NULL){
     printf("error reading file");
     exit(1);
    }

    //variable definitions 
    int const SIZE_ELE = 100;
    char *BUFFER= (char*)malloc(sizeof(char) * SIZE_ELE);

    int const SIZE_ARR = getFileRows(BUFFER, inputFile);
    printf("# of file rows = %d\n", SIZE_ARR);
    
    Car **carArray = (Car**) malloc (sizeof(Car*) * SIZE_ARR); // allocated memory for the general array
        for(int i =0; i < SIZE_ARR; i++){
            carArray[i] = (Car*) malloc (sizeof(Car) * SIZE_ELE); // allocated memory for each element in the general array
        }

    //opens file in funciton
    //process file by read input file line by line and store info in seperately
    //closes file once done reading
    subdivideCarsFromInput(inFILE, carArray, SIZE_ELE, SIZE_ARR, BUFFER);

    //this variable is the value size for new array
    int count = countPositive(carArray, SIZE_ARR, SIZE_ELE); 

    Car **sortedArray = (Car**)malloc(sizeof(Car*) * count);
        for(int j = 0; j < count; j++){
            sortedArray[j] = (Car*)malloc(sizeof(Car) * SIZE_ELE);
        }

    //sort the old array into new one
    //put into a function later
    eliminateCars(count, SIZE_ELE, SIZE_ARR, carArray, sortedArray);
    
    //open output file
    FILE *outputFile = fopen(argv[2],"w");

    //writes the data from Array to txt file
    printToOutputFile(sortedArray, count, outputFile);

    //function that computes power
    //computePower();

    //function that compares the data of two cars 
    //carCmp();


fclose(outputFile);
free(BUFFER);
free(carArray);
free(sortedArray);

return;
}