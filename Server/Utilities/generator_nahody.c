
double getRandomDouble(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

int getRandomInt(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

SMER getRandomSmerVetru() {
    int cisloVetru = getRandomInt(0, 3);
    switch(cisloVetru) {
        case 0: return SEVER;
        case 1: return JUH;
        case 2: return VYCHOD;
        case 3: return ZAPAD;
    }
    return BEZVETRIE;
}