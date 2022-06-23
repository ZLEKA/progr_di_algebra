#include <iostream>
#include <vector>

using namespace std;
const int N=10 ;
//Calcola la norma infinito di una matrice---------------------------------------------------------------------------
int infNorm(int** m, int righe, int colonne){
	long int max=0;
	if(m==NULL){
		perror("matrice vuota\n");	
		return 0;
	}
	for(int i=0; i<righe; i++){
		int sum=0;
		for(int j=0; j<colonne; j++){
			sum += abs(m[i][j]);
		}
		if (sum > max) max=sum;
	}
	return max;
	
}

//Calcolare il fattoriale di un numero----------------------------------------------------------------------------------------

long int fact(int n){
	if(n>1)
		return n*fact(n-1);
	else
		return 1;
}

//Creazione della matrice------------------------------------------------------------------------------------------------

int** newMatrix(int righe, int colonne){
	int** m = new int*[righe];     //int** alloca prima le righe  e poi le colonne
		for(int i =0;i<righe;i++){
			m[i]=new int[colonne];
		}
	
	return m;
}	
//creazione della matrice in float(pricisione singola)------------------------------------------------------------------

float** newMatrixFloat(int righe, int colonne){
	float** m = new float*[righe];     //float** alloca prima le righe  e poi le colonne
		for(int i =0;i<righe;i++){
			m[i]=new float[colonne];
		}
	
	return m;
}	
//stampa la matrice---------------------------------------------------------------------

void stampMatrix(int** m, int righe, int colonne){
	if(m==NULL){
		perror("matrice vuota\n");
		return ;
	}
	for(int i=0;i<righe;i++){
		for(int j=0;j<colonne;j++){
			cout<<m[i][j]<<" ";
		}
		cout << endl;
		
	}
}
//stampa la matrice float -------------------------------------------------------------

void printMatrix(float** m, int righe, int colonne){
	
	for(int i=0;i<righe;i++){
		for(int j=0;j<colonne;j++){
			cout<<m[i][j]<<" ";
		}
		cout << endl;
		
	}
}

//genero il vettore X:={1,1,1,1,....,1} in base al numero di righe---------------------------------------------

float* getX(int righe){
	if(righe<1)return 0;
	float* x=new float[righe];
	for(int i=0;i<righe;i++) x[i]=1;
	return x;
}

//calcolo i rultati (cioè b)----------------------------------------------------------------------------------------

float* findB(float** matrix,int righe, int colonne, float* x){
	int i,j;
	if(matrix==NULL){
		perror("matrice vuota\n");
		return 0;
	}
	if(x==NULL){
		perror("vettore incognite vuoto\n");
		return 0;
	}
	float *sum=new float[righe];
	for(i=0;i<righe;i++) sum[i]=0;
	for(i=0;i<righe;i++){
		for(j=0;j<colonne;j++){
			sum[i]+=matrix[i][j]*x[i];
			
		}
	}
	return sum;
}
//cerco il pivot------------------------------------------------------------------------------------------------------------

void findpivot(float** matrix, int righe , int colonna, float*b){
	float backup=0;
	int aux;
	for(int i=colonna;i<righe;i++){
		if(matrix[i][colonna]==1 ){
			backup=matrix[i][colonna];//salvo il valore maggiore sulla colonna corrente
			aux=i;//salvo la posizione
			break;
		}else if(backup<matrix[i][colonna] || backup<(matrix[i][colonna]*-1)){//controllo il numero | | maggiore 
			backup=matrix[i][colonna];//salvo il valore maggiore sulla colonna corrente
			aux=i;//salvo la posizione
			}
		}
//scambio rige
	if(aux!=colonna){//controllo che non sia in prima posizione
		float *p,auxB;// *p per punntare al puntatore della righa auxB come becup per l'array dei risultati
		//faccio lo scambio sulla matrice
		p=matrix[aux];
		matrix[aux]=matrix[colonna];
		matrix[colonna]=p;
		//faccio lo scambio sui risultati
		auxB=b[colonna];
		b[colonna]=b[aux];
		b[aux]=auxB;
		
	}
}
	
//risolvo il sistema usando Gauss-----------------------------------------------------------------------------------------------

int gauss(float** matrixOld,int righe, int colonne, float* b){
	if(matrixOld==NULL){
		perror("matrice vuota\n");
		return -1;
	}
	if(b==NULL){
		perror("vettore risultati vuoto\n");
		return -1;
	}
	float **matrix;
	matrix=matrixOld;
	float pivot_moltiplicatore;
	
	for(int i=0;i<colonne-1;i++){//l'ultima righa è già risolta
		findpivot(matrix,righe, i,b);//cerco il pivot e lo posiziono in cima 
		
		for(int j=i+1;j<righe;j++){//parto dalla righa i+1 in modo da saltare le righe che ho gia ordinato
			
			if(matrix[j][i]==0)return -1;//da correggere se il pivot è zero allora det=0
			
			else pivot_moltiplicatore=matrix[j][i]/matrix[i][i];//calcolo la differenza tra i
			
			for(int k=i;k<colonne;k++){
			//faccio l'operazione lineare per tutte le colonne dalla riga
			matrix[j][k]-=matrix[i][k]*pivot_moltiplicatore;
			
			}
			//quando ho risolto la righa della matrice risolvo anche b (i rulstati)
			b[j]-=b[j-1]*pivot_moltiplicatore;
			
		}
	
	
	}
	matrixOld=matrix;
	return 0;
	
}
//inserice i valori nella matrice -----------------------------------------------------------------------

void insertValori(int **matrix,int righe ,int colonne,int* valori){
	int countV=0;
		for(int i=0; i<righe; i++){
			for(int j=0; j<colonne; j++){
				matrix[i][j] = valori[countV];
				countV++;
			}
		}
		

}

void calcolo_x(float** matrix,int righe,int colonne, float* X,float* b){
	float* summ=new float[righe];
	for(int i=0;i<righe;i++) summ[i]=0;//inizializzo a 0 il vettore delle somme
	
	for(int i=0;i<righe;i++){
		for(int j=0;j<colonne;j++) summ[i]+=matrix[i][j]; //sommo per ogni riga i valori nella matrice triangolare sup
		X[i]=b[i]/summ[i];//trovo le x dividendo i risulati b con la somma dei valori riga i della matrice
	}



}
int main(){

	//ES 1 -------------------------------------------------------------------------------------------------------------------------------------------------------/

	//ES 1A
		int righeA=4;
		int colonneA=4;
		int** A = newMatrix(righeA, colonneA);
		
		int valoriA[(righeA)*(colonneA)] = {3, 1, -1, 0, 0, 7, -3, 0, 0, -3, 9, -2, 0, 0, 4, -10};
		
		insertValori(A,righeA,colonneA,valoriA);
		
		stampMatrix(A, righeA, colonneA);
		
		cout << "NORMA A: " << infNorm(A, righeA, colonneA) << endl;
		

		int countV;
		
		int righeB=4;
		int colonneB=4;
		int** B = newMatrix(righeB, colonneB);
		
		int valoriB[(righeB)*(colonneB)] = {2, 4, -2, 0, 1, 3, 0, 1, 3, -1, 1, 2, 0, -1, 2, 1};
		
		insertValori(B,righeB,colonneB,valoriB);
		
		stampMatrix(B, righeB, colonneB);
		
		cout << "NORMA B: " << infNorm(B, righeB, colonneB) << endl;
		
		
		
	//ES 1B
		
		int righeP=N;
		int colonneP=N;
		int** P = newMatrix(righeP, colonneP);
		
		for(int i=0; i<righeP; i++){
			for(int j=0; j<colonneP; j++){
				P[i][j] = (fact((i+1)+(j+1)-2))/( fact((i+1)-1)*fact((j+1)-1) );
			}
		}
		
		stampMatrix(P, righeP, colonneP);
		
		cout << "NORMA P: " << infNorm(P, righeP, colonneP) << endl;
	
		
	
	
	
	//es 1c

	int ** T=newMatrix(righeP,colonneP);
	 for(int i=0; i<righeP;i++){
	 	for(int j=0; j<colonneP; j++){
			if(j==i) T[i][j]=2;
			else if(abs(i-j)==1) T[i][j]=-1;
			else T[i][j]=0;
		}
	 
	 }
	stampMatrix(T,righeP,colonneP);
	cout<<"norma "<<infNorm(T,righeP,colonneP)<<endl;
	
		
	//ES 2 -----------------------------------------------------------------------------------------------------------------------------------------------------------/
	//A--------------------------------------------------------
	int gaussControllo;//intero di controllo funzione gauss
	float *x=new float[righeA]; //dichiaro il vettore x 
	float *ris=new float[righeA];//dichiaro il vettore dei risultati
	float **A_float=newMatrixFloat(righeA, colonneA); 
	int valoriAF[(righeA)*(colonneA)] = {3, 1, -1, 0, 0, 7, -3, 0, 0, -3, 9, -2, 0, 0, 4, -10};
	/*
	//reinserico i valori
	countV=0;
	for(int i=0;i<righeA;i++){
		for(int j=0;j<colonneA;j++){
			A_float[i][j]=valoriAF[countV];
			countV++;
		}
	}
	
	
	x=getX(righeA); //creo il vettore x{1,1,1,..,1}
	ris=findB(A_float,righeA,colonneA,x);//calcolo i riusltati
	
	//stampo i risultati
	for(int i=0;i<15;i++) cout<<"----";
	cout<<"\n GAUSS\n\n";
	cout<<" -- risultato A del sistema calcolato--\n";
	for(int i=0;i<righeA;i++) cout<<i<<":  "<<ris[i]<<endl;
	cout<<"\n\n";
	
	//chiamo l'algoritmo di gauss
	if((gaussControllo==gauss(A_float,righeA, colonneA,ris))<0) cout<<"matrice con determinante = 0 \n\n";
	//stampo la matrice ridotta
	cout<<" -- matrice A ridotta -- \n";
	printMatrix(A_float,righeA,colonneA);
	//stampo i riultati computati
	cout<<" -- risultati A dopo gauss -- \n";
	for(int i=0;i<righeA;i++) cout<<i<<":  "<<ris[i]<<endl;
	
	float* A_X=new float[righeA];//dichiaro un nuovo vettore per contenere le X
	//chiamo una funzione che mi trova le X
	calcolo_x(A_float,righeA,colonneA,A_X,ris);
	//stampo i risultati
	cout<<" -- souzione delle incognite di A -- \n";
	for(int i=0;i<righeA;i++) cout<<i<<"A_X:  "<<A_X[i]<<endl;
	*/
	//B--------------------------------------------------------------------------------------------------------------
	float *xB=new float[righeB]; //dichiaro il vettore x 
	float *risB=new float[righeB];//dichiaro il vettore dei risultati
	float **B_float=newMatrixFloat(righeB, colonneB); 
	int valoriBF[(righeB)*(colonneB)] = {2, 4, -2, 0, 1, 3, 0, 1, 3, -1, 1, 2, 0, -1, 2, 1};
	
	//reinserico i valori
	countV=0;
	for(int i=0;i<righeB;i++){
		for(int j=0;j<colonneB;j++){
			B_float[i][j]=valoriBF[countV];
			countV++;
		}
	}
	
	
	xB=getX(righeB); //creo il vettore x{1,1,1,..,1}
	risB=findB(B_float,righeB,colonneB,xB);//calcolo i riusltati
	
	//stampo i risultati
	for(int i=0;i<15;i++) cout<<"----";
	cout<<"\n\n";
	cout<<" -- risultato B del sistema calcolato--\n";
	for(int i=0;i<righeB;i++) cout<<i<<":  "<<risB[i]<<endl;
	cout<<"\n\n";
	
	//chiamo l'algoritmo di gauss
	
	if((gaussControllo==gauss(B_float,righeB, colonneB,risB))<0)cout<<"matrice con determinante = 0 \n\n";
	//stampo la matrice ridotta
	cout<<" -- matrice B ridotta -- \n";
	printMatrix(B_float,righeB,colonneB);
	//stampo i riultati computati
	cout<<" -- risultati B dopo gauss -- \n";
	for(int i=0;i<righeB;i++) cout<<i<<":  "<<risB[i]<<endl;
	
	float* B_X=new float[righeB];//dichiaro un nuovo vettore per contenere le X
	//chiamo una funzione che mi trova le X
	calcolo_x(B_float,righeB,colonneB,B_X,risB);
	//stampo i risultati
	cout<<" -- souzione delle incognite di B -- \n";
	for(int i=0;i<righeB;i++) cout<<i<<"B_X:  "<<B_X[i]<<endl;
		
		return 0;
}
