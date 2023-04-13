/*includes both the function implementation functions with structs */

#include "definition.h" //containts all the definitions of the functions

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


typedef struct Car_struct{
    char carName[100];
    char dragCo[20];
    char dragArea[20];
    char power[20][10]; //first one row, second one column
}Car;


int getFileRows(char *BUFFER, FILE *inputFile){
    int i = 0;
    while(fgets(BUFFER, 200, inputFile) != NULL){
        i++;
    }
    fclose(inputFile);
return i;
}


void subdivideCarsFromInput(char const *inFILE, Car **carArray, int const SIZE_ELE, int const SIZE_ARR, char *BUFFER){
    FILE *inputFile = fopen(inFILE, "r");

    if(inputFile == NULL){
     printf("error reading file\n");
     exit(1);
    }
    int i = 0;
    while(fgets(BUFFER, SIZE_ELE, inputFile) != NULL){
        char *cname = strtok(BUFFER, ",");
        strcpy(carArray[i]->carName, cname);
        char *cdragCO = strtok(NULL,",");
        strcpy(carArray[i]->dragCo, cdragCO);
        char *dragarea = strtok(NULL,"\n");
        strcpy(carArray[i]->dragArea, dragarea);
        i++;
        }

    fclose(inputFile);
    }


int countPositive(Car **carArray, int const SIZE_ARR, int const SIZE_ELE){
       int count = 0;
        for(int i = 0; i < SIZE_ARR; i++){
            if(atoi(carArray[i]->dragArea) != -1){
            count++;
            }
        }
    return count;
    }

void eliminateCars(int count, int const SIZE_ELE, int const SIZE_ARR, Car **carArray, Car **sortedArray){
        int i =0;
        for(int k = 0; k < SIZE_ARR; k++){
            if(atoi(carArray[k]->dragArea) != -1){
                sortedArray[i] = carArray[k];
                i++;
            }
        }
}

void computePower(Car **sortedArray, int count,double *VEL){
    double pwrtemp;
    char buf[10];
    double halfP = 0.5 * 1.18;
    for(int i = 0; i < count; i++){
        for(int j = 0; j < 3; j++){
        pwrtemp = atof(sortedArray[i]->dragCo) * halfP * pow(VEL[j], 3) * atof(sortedArray[i]->dragArea);
        //converts the double to a string so it can be stored in sortedArray
        gcvt(pwrtemp, 6, buf);
        strcpy(sortedArray[i]->power[j], buf);
        }
    }
}


void printToOutputFile(Car **sortedArray, int count, FILE *outputFile){
   fputs("Car Name;   Drag Coefficient;    Drag Area;   Power@60;   Power@70;   Power@80;\n", outputFile);
    for(int i = 0; i < count; i++){
        fputs(sortedArray[i]->carName, outputFile);
        fputs(" , ", outputFile);
        fputs(sortedArray[i]->dragCo, outputFile);
        fputs(" , ", outputFile);
        fputs(sortedArray[i]->dragArea, outputFile);
        fputs(" , ", outputFile);
        for(int j =0; j < 2; j++){
            fputs(sortedArray[i]->power[j], outputFile);
            fputs(" , ", outputFile);
        }
        fputs(sortedArray[i]->power[2], outputFile);
        fputs("\n", outputFile);
    }
}




