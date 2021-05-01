#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h> 
extern void iri_sub_(int[] , int *, float *, float *, int *, int * , float *, float *, float *, float *, float[][20], float[]);
//extern void iri_web_(int[] , int *, float *, float *, int *, int * , float *,float *, int * , int * ,int *, float *, float *, float *, float[][20], float[]);

 //    HEIBEG,HEIEND,HEISTP,OUTF,OARR)
int main()
{
     int line_count = 0;
    
    int jf[50]={true,true,true,false,false,
                false,true,true,true,true, 
                true,true,true,true,true,
                true,true,true, true,true,
                false,true, false,true,true,
                false, true,false,false,false, 
                true,true,false,true, false,
                true,true,true, false,true,
                true,true,true, true,true,
                true,false, true,true, true};
   
    int jmag;
    float alati;
    float along;
    int iyyy;
    int mmdd;
    float dhour;
    float begin;
    float end;
    float step;
    float oarr[100];
    float out[1000][20];
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;
float height =100; // height in km
         int h_tec_max  =0; //no TEC otherwise upper boundary for integral
         int  iut=1;// for UT       =0 for LT
          int ivar =1; 

    fp = fopen("params", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        //printf("%s\n", line);
        if (line_count==0)
        {
            jmag== atoi(line);
            printf("%i\n", jmag);
        }
        else if (line_count==1)
        {
            alati= atof(line);
            printf("%f\n", alati);
        }
        else if (line_count==2)
        {
            along = atof(line);
            printf("%f\n", along);
        }
        else if (line_count==3)
        {
            iyyy = atoi(line);
            printf("%i\n", iyyy);
        }
        else if (line_count==4)
        {
            mmdd = atoi(line);
            printf("%i\n", mmdd);
        }
        else if (line_count==5)
        {
            dhour =atof(line);
            printf("%f\n", dhour);
        }
        else if (line_count==6)
        {
            begin =atof(line);
            printf("%f\n", begin);
        }
        else if (line_count==7)
        {
            end =atof(line);
            printf("%f\n", end);
        }
        else if (line_count==8)
        {
            step =atof(line);
            printf("%f\n", step);
        }
        line_count++;
        printf("%d\n",line_count);
    }
    fclose(fp);
    printf("%i, %f, %f,%i, %i, %f, %f, %f, %f\n", jmag, alati, along, iyyy,mmdd,dhour, begin, end, step);
    //iri_web_(jf, &jmag, &alati, &along, &iyyy, &mmdd , &dhour,&height , &h_tec_max,&iut, &ivar, &begin , &end, &step,  out, oarr);
    iri_sub_(jf, &jmag, &alati, &along, &iyyy, &mmdd , &dhour, &begin , &end, &step,  out, oarr);
    printf("computed iri model\n");
    /* File pointer to hold reference to our file */
    FILE * fPtr;


    /* 
     * Open file in w (write) mode. 
     * "data/file1.txt" is complete path to create file
     */
    fPtr = fopen("output.dat", "w");
    printf("saving the iri model\n");

    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

   

    for (int i = 0 ; i<1000 ;i++)
    {
       
        for (int j =0 ; j<1 ; j++)
        {
            if (out[i][j]!=-1.0)
            {
                fprintf(fPtr,"%f ",out[i][j]);
                fprintf(fPtr,"%f",begin+i*step);
                 fprintf(fPtr,"\n");
            }
        }
    }
    

    /* Close file to save file data */
    fclose(fPtr);


    /* Success message */
    printf("File created and saved successfully. :) \n");
   return 0;
}