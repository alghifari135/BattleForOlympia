#include "queuelist.h"
#include "boolean.h"
#include <stdlib.h>


void Alokasi (address *P, infotype X){
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
	*P = (address) malloc(sizeof(ElmtQueue));
	if (*P != Nil){
		Info(*P) = X;
		Next(*P) = Nil;
	}
	else {
		*P = Nil;
	}
}
void Dealokasi (address  P){
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
	free(P);
}
boolean IsEmpty (Queue Q){
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
	return(Head(Q) == Nil);
}
int NbElmt(Queue Q){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
	address P = Head(Q);
	int count = 0;
	while(P){
		count++;
		P = Next(P);
	}
	return(count);
}
/*** Kreator ***/
void CreateEmpty(Queue * Q){
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}
/*** Primitif Add/Delete ***/
void Add (Queue * Q, infotype X){
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
	address P;
	Alokasi(&P,X);
	if(IsEmpty(*Q)){
		Head(*Q) = P;
		Tail(*Q) = P;
	}
	else {
		Next(Tail(*Q)) = P;
		Tail(*Q) = P;
	}
}
void Del(Queue * Q, infotype * X){
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
	address P = Head(*Q);
	if (Head(*Q) == Tail(*Q)){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
	else {
		Head(*Q) = Next(P);
		Next(P) = Nil;
	}
	*X = Info(P);
	Dealokasi(P);
}
