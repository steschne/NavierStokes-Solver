#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <windows.h>




int main ()

{


char plotstring[50];
char gnuplotbefehl[300];


int T = 10000;
int t;
int diff;
int anfang = 0;
int i;
int j;


for(t=1;t<T;t++)

{
  
  
  diff = t - anfang;
 
if(t<=100){
           
 if(diff == 5){
        
        anfang = t;
        
sprintf(plotstring, "set output 'plotti%d.png' \n",t);


sprintf(gnuplotbefehl,  "plot 'plotti_%d.dat' using ($1*0.01960784313725490):($2*0.01960784313725490):4:5 with vectors \n",t);



FILE *gnuplotPipe = popen("c:\\gnuplot\\bin\\gnuplot -persist","w");
if(gnuplotPipe){ 
                fprintf(gnuplotPipe, "cd 'C:\\Users\\stephan\\Desktop\\Cavity Flow' \n");
                fprintf(gnuplotPipe, "set xrange [0:1]\n");
                fprintf(gnuplotPipe, "set yrange [0:1]\n");
                fprintf(gnuplotPipe, "set terminal png \n");
               fprintf(gnuplotPipe, plotstring );
               
                //fprintf(gnuplotPipe, "set zrange [0:0.2]\n");
                //fprintf(gnuplotPipe, "plot 'plottingmovie.dat' u ($1*0.01960784313725490):($2*0.01960784313725490):4:5 w vec   \n");
                fprintf(gnuplotPipe, gnuplotbefehl);
    // fprintf(gnuplotPipe, "sleep 3\n");

     
  fflush(gnuplotPipe);
  // Sleep(3000);

  //fprintf(stderr,"Press enter to continue...");  
  //fflush(stderr);  
  //getchar();  
 
  // exit gnuplot  
  //fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);
  pclose(gnuplotPipe);
}  
}


} 
  
  
  
  
  
  
if(t>=100&&t<=1000)
{

if(diff == 10){
        
        anfang = t;
        
sprintf(plotstring, "set output 'plotti%d.png' \n",t);


sprintf(gnuplotbefehl,  "plot 'plotti_%d.dat' using ($1*0.01960784313725490):($2*0.01960784313725490):4:5 with vectors \n",t);



FILE *gnuplotPipe = popen("c:\\gnuplot\\bin\\gnuplot -persist","w");
if(gnuplotPipe){ 
                fprintf(gnuplotPipe, "cd 'C:\\Users\\stephan\\Desktop\\Cavity Flow' \n");
                fprintf(gnuplotPipe, "set xrange [0:1]\n");
                fprintf(gnuplotPipe, "set yrange [0:1]\n");
                fprintf(gnuplotPipe, "set terminal png \n");
               fprintf(gnuplotPipe, plotstring );
               
                //fprintf(gnuplotPipe, "set zrange [0:0.2]\n");
                //fprintf(gnuplotPipe, "plot 'plottingmovie.dat' u ($1*0.01960784313725490):($2*0.01960784313725490):4:5 w vec   \n");
                fprintf(gnuplotPipe, gnuplotbefehl);
    // fprintf(gnuplotPipe, "sleep 3\n");

     
  fflush(gnuplotPipe);
  // Sleep(3000);

  //fprintf(stderr,"Press enter to continue...");  
  //fflush(stderr);  
  //getchar();  
 
  // exit gnuplot  
  //fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);
  pclose(gnuplotPipe);
}  
}


}


if(t>=1000&&t<=10000)
{

if(diff == 50){
        
        anfang = t;
        
sprintf(plotstring, "set output 'plotti%d.png' \n",t);


sprintf(gnuplotbefehl,  "plot 'plotti_%d.dat' using ($1*0.01960784313725490):($2*0.01960784313725490):4:5 with vectors \n",t);



FILE *gnuplotPipe = popen("c:\\gnuplot\\bin\\gnuplot -persist","w");
if(gnuplotPipe){ 
                fprintf(gnuplotPipe, "cd 'C:\\Users\\stephan\\Desktop\\Cavity Flow' \n");
                fprintf(gnuplotPipe, "set xrange [0:1]\n");
                fprintf(gnuplotPipe, "set yrange [0:1]\n");
                fprintf(gnuplotPipe, "set terminal png \n");
               fprintf(gnuplotPipe, plotstring );
               
                //fprintf(gnuplotPipe, "set zrange [0:0.2]\n");
                //fprintf(gnuplotPipe, "plot 'plottingmovie.dat' u ($1*0.01960784313725490):($2*0.01960784313725490):4:5 w vec   \n");
                fprintf(gnuplotPipe, gnuplotbefehl);
    // fprintf(gnuplotPipe, "sleep 3\n");

     
  fflush(gnuplotPipe);
  // Sleep(3000);

  //fprintf(stderr,"Press enter to continue...");  
  //fflush(stderr);  
  //getchar();  
 
  // exit gnuplot  
  //fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);
  pclose(gnuplotPipe);
}  
}


}


if(t>=10000 && t<= 30000)
{

if(diff == 1000){
        
        anfang = t;
        
sprintf(plotstring, "set output 'plotti%d.png' \n",t);


sprintf(gnuplotbefehl,  "plot 'plotti_%d.dat' using ($1*0.01960784313725490):($2*0.01960784313725490):4:5 with vectors \n",t);



FILE *gnuplotPipe = popen("c:\\gnuplot\\bin\\gnuplot -persist","w");
if(gnuplotPipe){ 
                fprintf(gnuplotPipe, "cd 'C:\\Users\\stephan\\Desktop\\Cavity Flow' \n");
                fprintf(gnuplotPipe, "set xrange [0:1]\n");
                fprintf(gnuplotPipe, "set yrange [0:1]\n");
                fprintf(gnuplotPipe, "set terminal png \n");
               fprintf(gnuplotPipe, plotstring );
               
                //fprintf(gnuplotPipe, "set zrange [0:0.2]\n");
                //fprintf(gnuplotPipe, "plot 'plottingmovie.dat' u ($1*0.01960784313725490):($2*0.01960784313725490):4:5 w vec   \n");
                fprintf(gnuplotPipe, gnuplotbefehl);
    // fprintf(gnuplotPipe, "sleep 3\n");

     
  fflush(gnuplotPipe);
  // Sleep(3000);

  //fprintf(stderr,"Press enter to continue...");  
  //fflush(stderr);  
  //getchar();  
 
  // exit gnuplot  
  //fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);
  pclose(gnuplotPipe);
}  
}


}


if(t>=200000)
{

if(diff == 10000){
        
        anfang = t;
        
sprintf(plotstring, "set output 'plotti%d.png' \n",t);


sprintf(gnuplotbefehl,  "plot 'plotti_%d.dat' using ($1*0.01960784313725490):($2*0.01960784313725490):4:5 with vectors \n",t);



FILE *gnuplotPipe = popen("c:\\gnuplot\\bin\\gnuplot -persist","w");
if(gnuplotPipe){ 
                fprintf(gnuplotPipe, "cd 'C:\\Users\\stephan\\Desktop\\Cavity Flow' \n");
                fprintf(gnuplotPipe, "set xrange [0:1]\n");
                fprintf(gnuplotPipe, "set yrange [0:1]\n");
                fprintf(gnuplotPipe, "set terminal png \n");
               fprintf(gnuplotPipe, plotstring );
               
                //fprintf(gnuplotPipe, "set zrange [0:0.2]\n");
                //fprintf(gnuplotPipe, "plot 'plottingmovie.dat' u ($1*0.01960784313725490):($2*0.01960784313725490):4:5 w vec   \n");
                fprintf(gnuplotPipe, gnuplotbefehl);
    // fprintf(gnuplotPipe, "sleep 3\n");

     
  fflush(gnuplotPipe);
  // Sleep(3000);

  //fprintf(stderr,"Press enter to continue...");  
  //fflush(stderr);  
  //getchar();  
 
  // exit gnuplot  
  //fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);
  pclose(gnuplotPipe);
}  
}


}







} //ENDE Zeitschleife



}
