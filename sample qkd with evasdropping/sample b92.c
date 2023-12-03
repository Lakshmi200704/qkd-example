#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUBIT_0 0
#define QUBIT_1 1

typedef struct {
    int value;
    int basis;
} Qubit;

typedef struct {
    Qubit qubit;
    int isEavesdropped;
} QuantumChannel;

void initializeQubit(Qubit *qubit) {
    qubit->value = rand() % 2;
    qubit->basis = rand() % 2;
}

int measureQubit(Qubit *qubit, int basis) {
    if (qubit->basis == basis) {
        return qubit->value;
    } else {
        // Measurement in the wrong basis, introduce an error
        qubit->value = rand() % 2;
        return qubit->value;
    }
}

void eavesdrop(QuantumChannel *channel) {
    channel->isEavesdropped = 1;
}

int main() {
    srand(time(NULL));

    // Alice prepares qubits
    Qubit aliceQubits[100];
    for (int i = 0; i < 100; i++) {
        initializeQubit(&aliceQubits[i]);
    }

    // Alice sends qubits to Bob through a quantum channel
    QuantumChannel channelToBob[100];
    for (int i = 0; i < 100; i++) {
        channelToBob[i].qubit = aliceQubits[i];
        channelToBob[i].isEavesdropped = 0;
    }

    // Eve, the eavesdropper, attempts to intercept the qubits
    for (int i = 0; i < 100; i++) {
        eavesdrop(&channelToBob[i]);
    }

    // Bob measures the qubits
    int bobResults[100];
    for (int i = 0; i < 100; i++) {
        bobResults[i] = measureQubit(&channelToBob[i].qubit, channelToBob[i].qubit.basis);
    }

    // Alice and Bob extract the shared key
    printf("Shared Key: ");
    for (int i = 0; i < 100; i++) {
        if (aliceQubits[i].basis == channelToBob[i].qubit.basis) {
            printf("%d ", bobResults[i]);
        }
    }
    printf("\n");

    return 0;
}
