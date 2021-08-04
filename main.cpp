#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


void place_correct(double  *A, double *B, long *M, short *Radius, double *Speedx, double *Speedy, short *Color, int numbers){
    int i, j;
    for(i = 0; i < numbers - 1;  i++){
        for(j = i + 1; j < numbers; j++){
            if(sqrt((A[i] - A[j]) * (A[i] - A[j]) + (B[i] - B[j]) * (B[i] - B[j]) ) <= 5 + Radius[i] + Radius[j]){
                printf("The coordinates of ball %d and %d are wrong.Change their coordinates or change their radius\n",i+1,j+1);
                closegraph();
                system("pause");
                exit(1);
            }
        }
    }

    for(i = 0; i < numbers; i++){
        if(A[i] < 0 || A[i] > 600){
                printf("The permitted values for x-coordinates are between 0 and 600\n");
                closegraph();
                system("pause");
                exit(1);
            }
            else if(B[i] < 0 || B[i] > 400){
                printf("The permitted values for y-coordinates are between 0 and 400\n");
                closegraph();
                system("pause");
                exit(1);
            }
            else if(Color[i] < 0 || Color[i] > 15){
                printf("The permitted values for color are between 0 and 15\n");
                closegraph();
                system("pause");
                exit(1);
            }
            else if(M[i] < 0 || M[i] > 10000){
                printf("The permitted values for mass are between 0 and 10000\n");
                closegraph();
                system("pause");
                exit(1);
            }
            else if(Radius[i] < 1 || Radius[i] > 100){
                printf("The permitted values for radius are between 1 and 100\n");
                closegraph();
                system("pause");
                exit(1);
            }
            else if(Speedx[i] < -100 || Speedx[i] > 100){
                printf("The permitted values for x-speed are between -100 and 100\n");
                closegraph();
                system("pause");
                exit(1);
            }
            else if(Speedy[i] < -100 || Speedy[i] > 100){
                printf("The permitted values for y-speed are between -100 and 100  %d \n",i);
                closegraph();
                system("pause");
                exit(1);
            }

            if(A[i] + Radius[i] >= getmaxx() || A[i] - Radius[i] <=0){
                printf("The x-coordinates of ball %d have crossed the limits. Fix it or decrease the radius\n",i+1);
                closegraph();
                system("pause");
                exit(1);
            }

            else if(B[i] + Radius[i] >=getmaxy() || B[i] - Radius[i] <=0){
                printf("The y-coordinates of ball %d have crossed the limits. Fix it or decrease the radius\n",i+1);
                closegraph();
                system("pause");
                exit(1);
            }
        }
        return;
}

void graph(double*, double*, long*, short*, double*, double*, short*, int);
void text(){
    FILE *pointer;
    int numbers, i;

    pointer = fopen("ab.txt","r");
    if(pointer != NULL){
        double *A, *B, *Speedx, *Speedy;
        short *Color, *Radius;
        long *M;
        fscanf(pointer,"%d",&numbers);

        A = (double*)malloc(numbers * sizeof(double));
        B = (double*)malloc(numbers * sizeof(double));
        Color = (short*)malloc(numbers * sizeof(short));
        M = (long*)malloc(numbers * sizeof(long));
        Radius = (short*)malloc(numbers * sizeof(short));
        Speedx = (double*)malloc(numbers * sizeof(double));
        Speedy = (double*)malloc(numbers * sizeof(double));

        if(ferror(pointer)){
            printf("There is an error \n");
            system("pause");
            exit(1);
        }

        if(A == NULL || B == NULL || M == NULL || Speedx == NULL || Speedy == NULL || Radius == NULL || Color == NULL){
            printf("There is not enough memory for %d balls. Remove some of them\n",numbers);
            fclose(pointer);
            closegraph();
            system ("pause");
            exit(1);
        }
        else{
            for(i = 0; i < numbers; i++){
                fscanf(pointer,"%lf",&A[i]);
                fscanf(pointer,"%lf",&B[i]);
                fscanf(pointer,"%hu",&Color[i]);
                fscanf(pointer,"%li",&M[i]);
                fscanf(pointer,"%hu",&Radius[i]);
                fscanf(pointer,"%lf",&Speedx[i]);
                fscanf(pointer,"%lf",&Speedy[i]);
                if(feof(pointer)){
                    closegraph();
                    fclose(pointer);
                    printf("You need to add some information in notepad or to reduce the number of balls \n");
                    system("pause");
                    exit(1);
                }
            }

            fclose(pointer);
            place_correct(A,B,M,Radius,Speedx,Speedy,Color,numbers);
            //graph(A,B,M,Radius,Speedx,Speedy,Color,numbers);
            if(numbers == 1)
                exit(1);
        }
    }

    else{
        printf("An error has occurred! Close the program and check the notepad.\n");
        fclose(pointer);
        closegraph();
        system ("pause");
        exit(1);
    }
}

void graph(double  *A, double *B, long *M, short *Radius, double *Speedx, double *Speedy, short *Color, int numbers){
    int i,j;
    double helper1, helper2, step;
    clock_t start, finish, previous;
    start = clock();
    previous = start;
    do{
        finish = clock();
        step = (finish - previous) * 1.0/CLOCKS_PER_SEC;
        if (step >= 0.03){
            text();
            previous = finish;
            setfillstyle(SOLID_FILL,BLACK);
            setcolor(BLACK);
            for(i = 0; i < numbers; i++){
                fillellipse(A[i],B[i],Radius[i],Radius[i]);
            }
            for(i = 0 ; i < numbers; i++){
                A[i] += Speedx[i] * step;
                B[i] += Speedy[i] * step;
            }
            for(i  = 0; i < numbers; i++){
                if (A[i] + Radius[i] >= getmaxx() || A[i] - Radius[i] <=0)
                    Speedx[i] *= -1;

                if (B[i] + Radius[i] >=getmaxy() || B[i] - Radius[i] <=0)
                    Speedy[i] *= -1;
            }

            for(i = 0; i < numbers - 1; i++){
                for(j = i + 1; j < numbers; j++){
                    if(sqrt((A[i] - A[j]) * (A[i] - A[j]) + (B[i] - B[j]) * (B[i] - B[j]) ) <= Radius[i] + Radius[j]){
                        helper1 = (2 * M[j] * Speedx[j] + (M[i] - M[j]) * Speedx[i]) / (M[i] + M[j]);
                        Speedx[j] = (2 * M[i] * Speedx[i] + (M[j] - M[i]) * Speedx[j]) / (M[i] + M[j]);
                        helper2 = (2 * M[j] * Speedy[j] + (M[i] - M[j]) * Speedy[i]) / (M[i] + M[j]);
                        Speedy[j] = (2 * M[i] * Speedy[i] + (M[j] - M[i]) * Speedy[j]) / (M[i] + M[j]);
                        Speedx[i] = helper1;
                        Speedy[i] = helper2;
                    }
                }
            }
            for(i = 0; i < numbers; i++){
                setfillstyle(SOLID_FILL,Color[i]);
                setcolor(Color[i]);
                fillellipse(A[i],B[i],Radius[i],Radius[i]);
            }
        }
    }while (!kbhit());
    closegraph();
}

int main(){
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, " ");
    errorcode = graphresult();
    if (errorcode != grOk){
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      system ("pause");
      exit(1);
    }
    text();
    graph(A,B,M,Radius,Speedx,Speedy,Color,numbers);
}
