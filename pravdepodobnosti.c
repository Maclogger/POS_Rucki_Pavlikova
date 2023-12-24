
typedef struct {
    int lukaPrav;
    int lesPrav;
    int skalaPrav;
    int vodaPrav;
} PRAVDEPODOBNOSTI;

void nastav_pravdepodobnosti(PRAVDEPODOBNOSTI *p, int lesPrav, int lukaPrav, int skalaPrav, int vodaPrav) {
    if (lesPrav + lukaPrav + skalaPrav + vodaPrav != 100) {
        printf("CHYBA!!! Pravdepodobnosti nie su 100 percent!\n");
        return;
    }
    p->lesPrav = lesPrav;
    p->lukaPrav = lukaPrav;
    p->skalaPrav = skalaPrav;
    p->vodaPrav = vodaPrav;
}
