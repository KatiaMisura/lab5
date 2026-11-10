#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor {
    int broj;
    struct Cvor* next;
} Cvor;


int unos(Cvor* head, int n) {
    Cvor* p = head;
    int x;

    for (int i = 0; i < n; i++) {
        printf("Unesi %d. broj: ", i + 1);
        if (scanf("%d", &x) != 1)
            return 0;

        if (p != head && x < p->broj) {
            printf("Lista mora biti sortirana!\n");
            return 0;
        }

        Cvor* novi = malloc(sizeof(Cvor));
        if (novi == NULL)
            return 0;

        novi->broj = x;
        novi->next = NULL;

        p->next = novi;
        p = novi;
    }
    return 1;
}


int dodaj(Cvor* head, int x) {
    Cvor* p = head;

    while (p->next != NULL)
        p = p->next;

    Cvor* novi = malloc(sizeof(Cvor));
    if (novi == NULL)
        return 0;

    novi->broj = x;
    novi->next = NULL;
    p->next = novi;

    return 1;
}


int unija(Cvor* L1, Cvor* L2, Cvor* U) {
    Cvor* p = L1->next;
    Cvor* q = L2->next;

    while (p != NULL || q != NULL) {
        int x;

        if (q == NULL || (p != NULL && p->broj < q->broj)) {
            x = p->broj;
            p = p->next;
        }
        else if (p == NULL || q->broj < p->broj) {
            x = q->broj;
            q = q->next;
        }
        else {
            x = p->broj;
            p = p->next;
            q = q->next;
        }

        Cvor* zadnji = U;
        while (zadnji->next != NULL)
            zadnji = zadnji->next;

        if (zadnji == U || zadnji->broj != x) {
            if (!dodaj(U, x))
                return 0;
        }
    }
    return 1;
}


int presjek(Cvor* L1, Cvor* L2, Cvor* P) {
    Cvor* p = L1->next;
    Cvor* q = L2->next;

    while (p != NULL && q != NULL) {
        if (p->broj < q->broj) {
            p = p->next;
        }
        else if (p->broj > q->broj) {
            q = q->next;
        }
        else {
            Cvor* zadnji = P;
            while (zadnji->next != NULL)
                zadnji = zadnji->next;

            if (zadnji == P || zadnji->broj != p->broj) {
                if (!dodaj(P, p->broj))
                    return 0;
            }

            p = p->next;
            q = q->next;
        }
    }
    return 1;
}


void ispis(Cvor* head) {
    Cvor* p = head->next;

    while (p != NULL) {
        printf("%d ", p->broj);
        p = p->next;
    }
    printf("\n");
}


void oslobodi(Cvor* head) {
    Cvor* p = head->next;

    while (p != NULL) {
        Cvor* temp = p;
        p = p->next;
        free(temp);
    }

    head->next = NULL;
}

int main() {
    Cvor L1 = { 0, NULL };
    Cvor L2 = { 0, NULL };
    Cvor U = { 0, NULL };
    Cvor P = { 0, NULL };

    int n, m;
    int uspjeh = 1;

    printf("Broj elemenata L1: ");
    if (scanf("%d", &n) != 1 || n < 0)
        return 1;

    printf("Unesi sortiranu listu L1:\n");
    if (!unos(&L1, n))
        uspjeh = 0;

    if (uspjeh) {
        printf("Broj elemenata L2: ");
        if (scanf("%d", &m) != 1 || m < 0)
            uspjeh = 0;
    }

    if (uspjeh) {
        printf("Unesi sortiranu listu L2:\n");
        if (!unos(&L2, m))
            uspjeh = 0;
    }

    if (uspjeh)
        uspjeh = unija(&L1, &L2, &U);

    if (uspjeh)
        uspjeh = presjek(&L1, &L2, &P);

    if (uspjeh) {
        printf("\nLista L1: ");
        ispis(&L1);

        printf("Lista L2: ");
        ispis(&L2);

        printf("Unija L1 i L2: ");
        ispis(&U);

        printf("Presjek L1 i L2: ");
        ispis(&P);
    }
    else {
        printf("Greska pri unosu ili alokaciji memorije.\n");
    }

    oslobodi(&L1);
    oslobodi(&L2);
    oslobodi(&U);
    oslobodi(&P);

    return uspjeh ? 0 : 1;
}



