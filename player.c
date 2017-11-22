
#include "player.h"
#include "boolean.h"
#include "listdpUnit.h"
#include "unit.h"
#include <stdio.h>
#include <stdlib.h>

void AttackU (Unit U1, Unit U2)
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1
{
	HP(U2) -= DamagePoints(U1);
	if (HP(U2) <= 0) { // Jika HP dari U2 habis
        // DelP(&UnitList(ArrPlayer[Owner(U2)]), Locate(U2));
		U2 = NullUnit();
	} else if ((Tipe(U2) == 'K' || AttackType(U1) == AttackType(U2)) && HP(U2) > 0 ) {
		HP(U1) -= DamagePoints(U2);

		if (HP(U1) <= 0) { // Jika HP dari U1 habis setelah counter attack
        	// DelP(&UnitList(ArrPlayer[Owner(U2)]), Locate(U1));
			U1 = NullUnit();
		}
	}
}

/*** BUAT QUEUE PLS JGN DIGANGGU GUGAT ***/

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{	/* ALGORTIMA */
	return ((Head(Q) == Nol) && (Tail(Q) == Nol));
}

boolean IsQFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{	/* ALGORTIMA */
	return ((Head(Q) == (Tail(Q) + 1)) || ((Head(Q) == 1) && (Tail(Q) == MaxEl(Q))));
}

int NBElmtQ (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{	/* ALGORTIMA */
	if (IsQEmpty(Q)) {
		return 0;
	}
	else if (Tail(Q) > Head(Q)) {
		return (Tail(Q) - Head(Q) + 1);
	}
	else {
		return (MaxEl(Q) - Head (Q) + 1 + Tail(Q));
	}
}


/* *** Kreator *** */
void CreateEmptyQ (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{	/* ALGORTIMA */
	(* Q).T = (infotypeQ *) malloc ((Max + 1) * sizeof(infotypeQ));
	if ((*Q).T != NULL) {
		MaxEl(*Q) = Max;
		Head(*Q) = Nol;
		Tail(*Q) = Nol;
	}
	else {
	MaxEl(*Q) = 0;
	}
}


/* *** Destruktor *** */
void DeAlokasiQ(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{	/* ALGORTIMA */
    MaxEl(* Q) = 0;
    free((* Q).T);
}


/* *** Primitif Add/Delete *** */
void AddQ (Queue * Q, infotypeQ X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{	/* ALGORTIMA */
	if (IsQEmpty(* Q)) {
		Head(* Q) = 1;
		Tail(* Q) = 1;
	}
	else if (Tail(* Q) == MaxEl(* Q)) {
		Tail(* Q) = 1;
	}
	else {
		Tail(* Q) = Tail(* Q) + 1;
	}
	InfoTail(* Q) = X;
}

void DelQ (Queue * Q, infotypeQ * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{	/* ALGORTIMA */
	(* X) = InfoHead(* Q);
	if (NBElmtQ(* Q) == 1) {
		Head(* Q) = 0;
		Tail(* Q) = 0;
	}
	else if (Head(* Q) == MaxEl(* Q)) {
		Head(* Q) = 1;
	}
	else {
		++Head(* Q);
	}
}

void CreateTurn (Queue * Q, Player P1, Player P2) {
	/* Membuat turn dengan urutan 1 dan 2 */
	/* ALGORITMA */
	CreateEmptyQ(Q, 2);
	AddQ(Q, &P1);
	AddQ(Q, &P2);
}

void NextTurn (Queue * Q) {
	/* Mengubah head -> tail dan tail -> head */
	infotypeQ X;
	/* ALGORITMA */
	DelQ(Q, &X);
	AddQ(Q, X);
}

infotypeQ CurrentTurn (Queue Q) {
	/* Mengambilkan turn saat ini */
	return InfoTail(Q);
}