#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <time.h>

// globale Physikalische Konstanten

#define RHO 1; // (relative) Dichte
#define RE 200000.0;



// Numerische Konstanten

double GY = 0; // Erdanziehung in y-Richtung
double GX = 0.0;  // Erdanziehung in x-Richtung
double DT; // Schrittweite für t (aus der Stabilitätsbedingung)
double GAMMA; // Gewichtungsfaktor 
double A = 1.0; // x-LÃ¤nge der Nische
double B = 1.0; // y-LÃ¤nge der Nische
double DX = 1.0/50.0;//0.01960784313725490 ; // Schrittweite in x-Richtung 
double DY = 1.0/50.0; //0.01960784313725490; // Schrittweite in y-Richtung
int I_MAX = 52; // Diskretisierung in x-Richtung (50 Felder)
int J_MAX = 52; // "" y-Richtung ""
double OMEGA = 0.7;//0.7;   //Relaxationsfaktor 
  // Reynolds Zahl
double reziprokRE = 1/RE ; //     1/RE
double REhalbe = 200000.0/2.0 ;  //RE/2
double EPSILON = 1; //Abbruchfaktor
int T = 1000000;//Zeitdauer 
 double tau = 0.5;
double diff;
double anfang = 200000;
char dateistring[50];



//Selbstaufrunende Funktionen

        
  
int main ()

{
  // Initialisierung der Felder und Variablen:
// Benennung der Variablen: u - Geschwindigkeit in x-Richtung ; v- Geschwindigkeit in y-Richtung


double u[I_MAX][J_MAX];
double v[I_MAX][J_MAX];
double unext[I_MAX][J_MAX];
double vnext[I_MAX][J_MAX];
double p[I_MAX][J_MAX];
double F[I_MAX][J_MAX];
double G[I_MAX][J_MAX];     
double RHS[I_MAX][J_MAX];
double resitplus1[I_MAX][J_MAX];
double pit[I_MAX][J_MAX];
double pitplus1[I_MAX][J_MAX];
double normresitplus1; 
double pit0[I_MAX][J_MAX];
double normpit0;
double minimum;
   int k;     




//fÃ¼r die Ableitungen zum Testen

double u2[I_MAX][J_MAX];




// Initialisieren der Felder u_IJ und v_IJ zum Zeitpunkt t=0 
int J;
int I;
for (I=0; I< I_MAX; I++){
for (J=0; J< J_MAX; J++){
u[I][J]=0; 
v[I][J]=0;

}
}


//RÄNDER RANDZELLEN füllen von pit0

//OBEN
for (I=1; I< I_MAX-1; I++){
//pit0[I][J_MAX-1]= -17*((I*DX-25*DX)*(I*DX-25*DX)) + 4; //Parabelanfangswert
pit0[I][J_MAX-1]= 0; // Anfangswert

}

//Unten
for (I=1; I<I_MAX-1;I++){
    pit0[I][0] = 0;
}
//rechts

for (J=1; J<J_MAX-1;J++){
    pit0[I_MAX-1][J] = 0;
}
//links

for(J=1;J<J_MAX-1;J++){
                     pit0[0][J] = 0;
}

//Innenbereich Startwert für den Anfangsdruck
for(J=1;J< J_MAX-1;J++){
for(I=1;I< I_MAX-1;I++){
           pit0[I][J] = 0;
           }
           }


//Initialisieren von pit mit pit0

for (I=0; I< I_MAX;I++){
for (J=0; J< J_MAX; J++){
pit[I][J]=pit0[I][J]; 
}
}

//____________________________________________________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________________________________________________
//BEGGGGGINNNN DER ZEIIITSCHLEIFE
//--------------------------------------------------------------------------------------------------------------------------------------------------------
int t;
for(t=1;t<T;t++){


//Zeitschrittweitensteuerung
//_----------------------------------------------------------------------
//Suche umax und vmax

long double umax;
long double vmax;
umax = fabs(u[I_MAX-1][J_MAX-1]);
vmax = fabs(v[I_MAX-1][J_MAX-1]);
for(J=J_MAX-2; J<=0;J--){
               for(I = I_MAX-2; I<= 0;I--){
                     if(fabs(u[I][J]) > umax){umax = fabs(u[I][J]);}
                     if(fabs(v[I][J]) > vmax){vmax = fabs(v[I][J]);}
                     }
                     }

//----------------------------------------------------------------------
                     
   long double bedingungen[3];
    bedingungen[0] = REhalbe*(1.0/((1/(DX*DX))+(1/(DY*DY))));
    if(umax > 0){ bedingungen[1] = DX/(umax);} else bedingungen[1] = DX/0.5;
    if(vmax > 0) {bedingungen[2] = DY/(vmax);} else bedingungen[2] = DY;
 
  
   
    minimum = bedingungen[2];
                     for(k=1;k>=0; k--){
                                   if(bedingungen[k] < minimum){minimum = bedingungen[k];}
                                   }
                                              
//Berechnung vom Zeitschritt;

DT = tau * minimum;







// Randwerte/Zellen initialisieren (Geisterfelder initialisieren) von u und v

for (J=1; J<J_MAX-1; J++){// linker Rand fÃ¼r u
u[0][J]=0;}

for (J=1; J<J_MAX-1; J++){// linker Rand fÃ¼r v
v[0][J]= -v[1][J];}

for (J=1; J<J_MAX-1; J++){// rechter Rand fÃ¼r u
u[I_MAX-2][J]=0;}

for (J=1; J<J_MAX-1; J++){// rechter Rand fÃ¼r v
v[I_MAX-1][J]= - v[I_MAX-2][J];}


for (I=1; I<I_MAX-1; I++){// unterer Rand fÃ¼r v
v[I][0]=0;}

for (I=1; I<I_MAX-1; I++){// unterer Rand fÃ¼r u
u[I][0]= -u[I][1];}

for (I=1; I<I_MAX-1; I++){// oberer Rand fÃ¼r v
v[I][J_MAX-2]=0;}

for (I=1; I<I_MAX-1; I++){// oberer Rand fÃ¼r u //HHIER IST die 4 durch die Mittelung mit const geschwindigkeit 2
u[I][J_MAX-1]= 1.0 - u[I][J_MAX-2];}



//GAMMMAAA
float gammamax1;
float gammamax2;
gammamax1 = (u[I_MAX-1][J_MAX-1]*DT)/DX;
gammamax2 = (v[I_MAX-1][J_MAX-1]*DT)/DY;
for(I=I_MAX-2;I>=0;I--){
                 for(J=J_MAX-2;J>=0;J--){
                                      if( (fabs(u[I][J])*DT)/DX > gammamax1) {gammamax1 = (fabs(u[I][J])*DT)/DX;}
                                      if ((fabs(v[I][J])*DT)/DY > gammamax2){gammamax2 = (fabs(v[I][J])*DT)/DY;}
                                      }
                                      }  
if(gammamax1 > gammamax2){GAMMA = gammamax1;}else{GAMMA = gammamax2;}



// Berechnung von Fij und Gij IMPULSGLEICHUNGEN
for (I=1; I< I_MAX-2; I++){
for (J=1; J<J_MAX-1; J++){
F[I][J] = u[I][J] + DT* ( (reziprokRE)*( (((u[I+1][J]-2*u[I][J]+u[I-1][J])/(DX*DX)))   + (((u[I][J+1]-2*u[I][J]+u[I][J-1])/(DY*DY)))  ) - ( (1.0/DX)*( ((u[I][J]+u[I+1][J])/2) * ((u[I][J]+u[I+1][J])/2) -  ((u[I-1][J]+u[I][J])/2) * ((u[I-1][J]+u[I][J])/2) )+ GAMMA *(1.0/DX)*( ((fabs(u[I][J] + u[I+1][J]))/2) * ((u[I][J] - u[I+1][J] )/2) - ((fabs(u[I-1][J]+u[I][J]))/2) * ((u[I-1][J]-u[I][J] )/2) )   ) - ((1.0/DY)*( ((v[I][J] + v[I+1][J])/2) * ((u[I][J] + u[I][J+1] )/2) - ((v[I][J-1] + v[I+1][J-1])/2) * ((u[I][J-1]+u[I][J] )/2) ) +GAMMA *(1/DY)*( ((fabs(v[I][J] + v[I+1][J]))/2) * ((u[I][J] - u[I][J+1] )/2) - ((fabs(v[I][J-1] + v[I+1][J-1]))/2) * ((u[I][J-1] - u[I][J] )/2) ) ) + GX    );
}
}




for (I=1; I< I_MAX-1; I++){
for (J=1; J<J_MAX-2; J++){
G[I][J] = v[I][J] + DT*( (reziprokRE) * ( (((v[I+1][J]-2*v[I][J]+v[I-1][J])/(DX*DX))) + (((v[I][J+1]-2*v[I][J]+v[I][J-1])/(DY*DY))) ) - ((1.0/DX)*( ((u[I][J] + u[I][J+1])/2) * ((v[I][J] + v[I+1][J] )/2) - ((u[I-1][J] + u[I-1][J+1])/2) * ((v[I-1][J] + v[I][J] )/2) ) +GAMMA *(1.0/DX)*( ((fabs(u[I][J] + u[I][J+1]))/2) * ((v[I][J] - v[I+1][J] )/2) - ((fabs(u[I-1][J] + u[I-1][J+1]))/2) * ((v[I-1][J] - v[I][J] )/2) )) - ((1.0/DY)*( ((v[I][J] + v[I][J+1])/2) * ((v[I][J] + v[I][J+1])/2) -  ((v[I][J-1] + v[I][J])/2) * ((v[I][J-1] + v[I][J])/2) )+ GAMMA *(1/DY)*( ((fabs(v[I][J] + v[I][J+1]))/2) * ((v[I][J] - v[I][J+1] )/2) - ((fabs(v[I][J-1] + v[I][J]))/2) * ((v[I][J-1] - v[I][J] )/2) )) + GY );
}
}


//LINKS  für F
   
   for(J=1;J<J_MAX-1;J++){
                          F[0][J] = u[0][J];
                          }
  //Rechts für F
  
  for (J=1;J<J_MAX-1;J++){
     F[I_MAX-2][J] = u[I_MAX-2][J];
}

  //uunten für G
  
  for (I=1;I<I_MAX-1;I++){
      G[I][0] = v[I][0];
      }
  //oben für G
  for(I=1;I<I_MAX-1;I++){
                       G[I][J_MAX-2] = v[I][J_MAX-2];
                       }
  



//________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
//________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

//DRUCKGLEICHUNG 



 //Bestimmung von Rechte Seite 
for (I=1; I<I_MAX-1; I++){
for (J=1; J<J_MAX-1; J++){
RHS[I][J] = (1.0/DT)*(   ((F[I][J] - F[I-1][J])/(DX)) + ((G[I][J]-G[I][J-1])/(DY)) );     
}
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


     
     
    //MAXIMUMSNORM VON PIT0  ANFANGSBEDINGUNG DES DRUCKS
     
    //Berechne alle Reihensummen
    float Reihensumme[I_MAX];
    
    for(I=0;I<I_MAX;I++){
                         for (J=0;J<J_MAX;J++){
                             Reihensumme[I] += pit0[I][J];
    }
    }
    //Suche Maximum
    float max = Reihensumme[I_MAX-1];
    for(I=I_MAX -2; I>=0;I--){
                if(Reihensumme[I] > max){max = Reihensumme[I];}
                }
    
    
    normpit0 = max;
    
  // fprintf( zeiger," %e \n", normpit0);    
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//damit ich in die Schleife reinkomme
normresitplus1 = 2 ;

int N;

//Bestimmung von p zum nächsten Zeitpunkt für alle Zellen I J 
//while(  normresitplus1 < EPSILON*normpit0  /*BEDINGUNG mit Residuum  */  ){    //Beginn der SOR Schleife (Iterationsschleife) Annäherung an die Lösung zum nächsten Zeitpunkt für jede I J Kombination

for(N=1;N<20;N++){   //zum selber testen für die anzahl der Iteration
   //-----------------------------------------------------------------------------------------
//ÜBERTRAGEN DER ALTEN DRUCK WERTE DEr NACHBARZELLEN IN DIE GEISTERZELLEN ( RANDZELLEN)   
   
  //LINKS
   
   for(J=1;J<J_MAX-1;J++){
                          pitplus1[0][J] = pit[1][J];
                          }
  //Rechts
  
  for (J=1;J<J_MAX-1;J++){
      pitplus1[I_MAX-1][J] = pit[I_MAX-2][J];
}

  //uunten
  
  for (I=1;I<I_MAX-1;I++){
      pitplus1[I][0] = pit[I][1];
      }
  //oben
  for(I=1;I<I_MAX-1;I++){
                       pitplus1[I][J_MAX-1] = pit[I][J_MAX-2];
                       }
  

   
   //----------------------------------------------------ITERATIONSSCHRITT--------------------------------------------------------------------------------------------------------------------------------------
   
   
   
for (J=1; J<J_MAX-1; J++){   //für jede J Zelle
for (I=1; I<I_MAX-1; I++){  //für jede I Zelle

   //Iterationsschritt
     pitplus1[I][J] = (1- OMEGA) * pit[I][J] + ((OMEGA)/(2*(1/(DX*DX) +1/(DY*DY))))* ( (pit[I+1][J]+ pitplus1[I-1][J])/(DX*DX) + (pit[I][J+1] + pitplus1[I-1][J-1])/(DY*DY)  -RHS[I][J] );           


}
}
//Nun haben wir für alle I und J den ersten Iterationsschritt auuser den rand
 //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 

/*

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//--->> Berechnung des Residuums beim ersten Iterationsschritt

for (I=1; I< I_MAX-1; I++){  //für jede I Zelle
for (J=1; J<J_MAX-1; J++){   //für jede J Zelle
    resitplus1[I][J] = (pitplus1[I+1][J] - 2*pitplus1[I][J] + pitplus1[I-1][J] )/(DX*DX) + (pitplus1[I][J+1] - 2*pitplus1[I][J] + pitplus1[I][J-1])/(DY*DY) ;    //rechte seite prüfen Hier Beispiel mit -2 p(x,y) bzw. -2 p_ij    
}
}//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//BERECHNE MAXIMUMNORM VON RESITPLUS1

  //Berechne alle Reihensummen
    float Reihensumme2[I_MAX];
    
    for(I=1;I<I_MAX-1;I++){
                         for (J=1;J<J_MAX-1;J++){
                             Reihensumme2[I] += resitplus1[I][J];
    }
    }
    //Suche Maximum
    float maxres = Reihensumme2[I_MAX-1];
    for(I=I_MAX -2; I>=0;I--){
                if(Reihensumme2[I] > maxres){maxres = Reihensumme2[I];}
                }
    
    
    normresitplus1 = maxres;

    //fprintf( zeiger," %e \n", normresitplus1);
 
 
 
*/ 
   
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//ITERATIONSENDE ÜBERSCHREIBEN DES ANFANGSWERTS 
     
for (I=0; I< I_MAX; I++){  //für jede I Zelle
for (J=0; J<J_MAX; J++){   //für jede J Zelle     
     
     pit[I][J] = pitplus1[I][J];   //Überschreibe den Anfangswert mit dem neuen Iterationswert
}
}   
   

   
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------   
   
     
} //Ende SOR SChleife


//___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________




//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

//Berechne neue Geschwindigkeitskomponenten
for(J=1;J<J_MAX-1;J++){
for(I=1;I<I_MAX-2;I++){
unext[I][J] = F[I][J] - DT * ((pitplus1[I+1][J] - pitplus1[I][J])/DX);
}
}


for(J=1;J<J_MAX-2;J++){
for(I=1;I<I_MAX-1;I++){
vnext[I][J] = G[I][J] - DT* ((pitplus1[I][J+1] - pitplus1[I][J])/DY);
}
}

//Überschreiben der alten u und v werte

for(J=1;J<J_MAX-1; J++){
for(I=1;I<I_MAX-2;I++){
u[I][J] = unext[I][J];
}
}
for(J=1;J<J_MAX-2; J++){
for(I=1;I<I_MAX-1;I++){
v[I][J] = vnext[I][J];
}
}



// Test Ausgabe in dat files 

      diff = t - anfang;  
        
        
/*        
if(t<= 100){
      if(diff == 10){       
       
    anfang = t;   
sprintf(dateistring,"plot_%d.dat",t);  

FILE *zeiger = fopen(dateistring,"w"); //Speichern in eine Datei (Eigentlich dateistring anstatt plottingmovie



for (I=1; I< I_MAX-1; I++){
  fprintf(zeiger,"\n");  
for (J=1; J< J_MAX-1; J++){
fprintf( zeiger,"%d %d %e %e %e \n", I, J, pitplus1[I][J], u[I][J],v[I][J]); 
}
}


}   
       
}   
       
       
       
        
        
if(t >= 100 && t<= 1000){        
if(diff == 500){
        
                
anfang = t;   
sprintf(dateistring,"plot_%d.dat",t);  

FILE *zeiger = fopen(dateistring,"w"); //Speichern in eine Datei (Eigentlich dateistring anstatt plottingmovie



for (I=1; I< I_MAX-1; I++){
  fprintf(zeiger,"\n");  
for (J=1; J< J_MAX-1; J++){
fprintf( zeiger,"%d %d %e %e %e \n", I, J, pitplus1[I][J], u[I][J],v[I][J]); 
}
}


}


}


if(t >= 1000 && t<= 10000){        
if(diff == 1000){
        
                
anfang = t;   
sprintf(dateistring,"plot_%d.dat",t);  

FILE *zeiger = fopen(dateistring,"w"); //Speichern in eine Datei (Eigentlich dateistring anstatt plottingmovie



for (I=1; I< I_MAX-1; I++){
  fprintf(zeiger,"\n");  
for (J=1; J< J_MAX-1; J++){
fprintf( zeiger,"%d %d %e %e %e \n", I, J, pitplus1[I][J], u[I][J],v[I][J]); 
}
}


}
}


if(t >= 10000 && t<= 30000){        
if(diff == 10000){
        
                
anfang = t;   
sprintf(dateistring,"plot_%d.dat",t);  

FILE *zeiger = fopen(dateistring,"w"); //Speichern in eine Datei (Eigentlich dateistring anstatt plottingmovie



for (I=1; I< I_MAX-1; I++){
  fprintf(zeiger,"\n");  
for (J=1; J< J_MAX-1; J++){
fprintf( zeiger,"%d %d %e %e %e \n", I, J, pitplus1[I][J], u[I][J],v[I][J]); 
}
}


}
}
*/
	
if(t >= 200000){        
if(diff == 200){
        
                
anfang = t;   
sprintf(dateistring,"plot_%d.dat",t);  

FILE *zeiger = fopen(dateistring,"w"); //Speichern in eine Datei (Eigentlich dateistring anstatt plottingmovie



for (I=1; I< I_MAX-1; I++){
  fprintf(zeiger,"\n");  
for (J=1; J< J_MAX-1; J++){
fprintf( zeiger,"%d %d %e %e %e \n", I, J, pitplus1[I][J], u[I][J],v[I][J]); 
}
}


}
}	
  
  
  
  
} //ENDE ZEITSCHLEIFE













} //Ende Main Programm


//Funktionen der Ableitungen DISKRETISIERUNG

/*

 //LINEAR
double d2u_dx2(int i, int j,  double U[] ){  //zweite Ableitung von u nach x
double output;
output = ((u[I+1][J]-2*u[I][J]+u[I-1][J])/(DX*DX))
return ouput ;  //passt
}



d2u_dy2(int I,int J,double U[][]){  // zweite Ableitung von u nach y
double output;
output =  ((u[I][J+1]-2*u[I][J]+u[I][J-1])/(DY*DY)); //
return output;
}



double d2v_dx2(int I, int J,double v[I][J]){ // zweite Ableitung von v nach x
double output;
output =((v[I+1][J]-2*v[I][J]+v[I-1][J])/(DX*DX));
return output;
}

d2v_dy2(int I,int J,double v[I][J]){  // zweite Ableitung von v nach y
double output;
output =  ((v[I][J+1]-2*v[I][J]+v[I][J-1])/(DY*DY));
return output;
}

//NICHTLINEAR!!!!!
double du2_dx(int I, int J,double u[I][J]){  //Ableitung von uÂ² nach x
double output;
output= (1/DX)*( ((u[I][J]+u[I+1][J])/2) * ((u[I][J]+u[I+1][J])/2) -  ((u[I-1][J]+u[I][J])/2) * ((u[I-1][J]+u[I][J])/2) )+ GAMMA *(1/DX)*( ((abs(u[I][J] + u[I+1][J]))/2) * ((u[I][J] - u[I+1][J] )/2) - ((abs(u[I-1][J]+u[I][J]))/2) * ((u[I-1][J]-u[I][J] )/2) );
return output; //stimmt //kein syntaxfehler
}

double duv_dy(int I, int J,double u[I][J],double v[I][J]){ //Ableitung von u*v nach y
double output;
output = (1/DY)*( ((v[I][J] + v[I+1][J])/2) * ((u[I][J] + u[I][J+1] )/2) - ((v[I][J-1] + v[I+1][J-1])/2) * ((u[I][J-1]+u[I][J] )/2) ) +GAMMA *(1/DY)*( ((abs(v[I][J] + v[I+1][J]))/2) * ((u[I][J] - u[I][J+1] )/2) - ((abs(v[I][J-1] + v[I+1][J-1]))/2) * ((u[I][J-1] - u[I][J] )/2) );
return output;
}  //kein syntaxfehler

double dv2_dy(int I, int J,double v[I][J]){  //Ableitung von vÂ² nach y
double output;
output=(1/DY)*( ((v[I][J] + v[I][J+1])/2) * ((v[I][J] + v[I][J+1])/2) -  ((v[I][J-1] + v[I][J])/2) * ((v[I][J-1] + v[I][J])/2) )+ GAMMA *(1/DY)*( ((abs(v[I][J] + v[I][J+1]))/2) * ((v[I][J] - v[I][J+1] )/2) - ((abs(v[I][J-1] + v[I][J]))/2) * ((v[I][J-1] - v[I][J] )/2) );
return output; //kein syntaxfehler
}

double duv_dx(int I, int J,double u[I][J],double v[I][J]){ //Ableitung von u*v nach x
double output;
output =(1/DX)*( ((u[I][J] + u[I][J+1])/2) * ((v[I][J] + v[I+1][J] )/2) - ((u[I-1][J] + u[I-1][J+1])/2) * ((v[I-1][J] + v[I][J] )/2) ) +GAMMA *(1/DX)*( ((abs(u[I][J] + u[I][J+1]))/2) * ((v[I][J] - v[I+1][J] )/2) - ((abs(u[I-1][J] + u[I-1][J+1]))/2) * ((v[I-1][J] - v[I][J] )/2) );
return output;  //stimmt //kein syntaxfehler
}

*/
