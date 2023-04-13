#include "functions.c" //containts all the functions from this program

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * Authors: Daleela Letyaeva, Hamza Saeed , Antonio Jimenez
*/


void main (int argc, char **argv){

    printf("WELCOME TO GROUP 15's AUTO POWER CALCULATOR!!!  !\n");
    printf("reading the input file %s\n", argv[1]);
    
    //check that user enters in/out file name
    if(argc != 3){ 
    printf("Usage: enter input file name and output filename after %s\n", argv[0]);
    exit(1);
    }

    //try to avoid user from confusing the 2 files
    if(strcmp(argv[1],argv[2])== 0){
    printf("please enter different output file name.\n");
    }

    //read input file
    char const *inFILE = argv[1];
    FILE *inputFile = fopen(inFILE, "r");


   //check for file not to be empty
    if(inputFile == NULL){
     printf("error reading file\n");
     exit(1);
    }

    //variable definitions
    int const SIZE_ELE = 100;
    char *BUFFER= (char*)malloc(sizeof(char) * SIZE_ELE);

    int const SIZE_ARR = getFileRows(BUFFER, inputFile);
    printf("---- completed reading %d lines of data\n", SIZE_ARR);

    Car **carArray = (Car**) malloc (sizeof(Car*) * SIZE_ARR); // allocated memory for the general array
        for(int i =0; i < SIZE_ARR; i++){
            carArray[i] = (Car*) malloc (sizeof(Car) * SIZE_ELE); // allocated memory for each element in the general array
        }
    

    Car **sortedArray = (Car**)malloc(sizeof(Car*) * count); //contains only elements which have a positive drag area
        for(int j = 0; j < count; j++){
            sortedArray[j] = (Car*)malloc(sizeof(Car) * SIZE_ELE);
        }
    
    //velocity
    double *VEL = (double*)malloc(sizeof(double) * 4); 
    for (int i = 0; i < 4; i++){
        //init the array with MPH values
        VEL[i] = 60 + (10 * i);

        //converts MPH to meters per second
        VEL[i] = VEL[i] * 0.44704;
    }

    subdivideCarsFromInput(inFILE, carArray, SIZE_ELE, SIZE_ARR, BUFFER);

    //this variable is the value size for new array
    printf("---- Sorting out all cars that have positive drag area\n");
    int count = countPositive(carArray, SIZE_ARR, SIZE_ELE);
    
    if(count == 0){
        printf("sorry, no cars were found with positive drag area - please input a different file");
        exit(1);
    } else {
        printf("---- found %d cars with positive drag area - distributing data to %s\n", count, argv[2]);
    }

   
   
    //sort the old array into new one
    //put into a function later
    eliminateCars(count, SIZE_ELE, SIZE_ARR, carArray, sortedArray);
    
    computePower(sortedArray, count, VEL);
 
    //open output file
    FILE *outputFile = fopen(argv[2],"w");

    printToOutputFile(sortedArray, count, outputFile);
  
    //prints the comparisons of the cars to terminal
    printf("Writing comparisons of drag area to power at 60 MPH\n");
        for(int j = 0; j < count; j++){ //corresponds to the columns
            for(int k=0; k < count; k++){
                if((sortedArray[j]->dragArea > sortedArray[k]->dragArea) && (atof(sortedArray[j]->power[0]) < atof(sortedArray[k]->power[0]))){
                printf("---- The drag area of %s  >  %s, but has lower power comsupation at 60 mph\n", sortedArray[k]->carName, sortedArray[j]->carName);
                }else{
                    continue;
                }
            }
        }


fclose(outputFile);
free(BUFFER);
free(carArray);
free(sortedArray);

return;
}


