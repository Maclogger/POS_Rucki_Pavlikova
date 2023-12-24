
typedef struct {
    int lesPrav;
    int lukaPrav;
    int skalaPrav;
    int vodaPrav;
} PRAVDEPODOBNOSTI;

void nastav_pravdepodobnosti(PRAVDEPODOBNOSTI *p, int lesPrav, int lukaPrav, int skalaPrav, int vodaPrav) {
    p->lesPrav = lesPrav;
    p->lukaPrav = lukaPrav;
    p->skalaPrav = skalaPrav;
    p->vodaPrav = vodaPrav;
}
