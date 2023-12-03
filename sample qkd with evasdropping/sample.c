#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUBIT_0 0
#define QUBIT_1 1

// Quantum Bit structure
typedef struct
{
    int value; // Qubit value: QUBIT_0 or QUBIT_1
    int basis; // Measurement basis: 0 or 1
} Qubit;

// Quantum Channel structure
typedef struct
{
    Qubit qubit;
    int isEavesdropped;
} QuantumChannel;

// Function to initialize a quantum bit
void initializeQubit(Qubit *qubit)
{
    qubit->value = rand() % 2; // Initialize with random value: 0 or 1
    qubit->basis = rand() % 2; // Initialize with random basis: 0 or 1
}

// Function to perform quantum measurement
int measureQubit(Qubit *qubit, int basis)
{
    if (qubit->basis == basis)
    {
        return qubit->value;
    }
    else
    {
        // Simulate quantum superposition collapse
        qubit->value = rand() % 2;
        return qubit->value;
    }
}

// Function to simulate eavesdropping
void eavesdrop(QuantumChannel *channel)
{
    channel->isEavesdropped = 1;
}

int main()
{
    srand(time(NULL));

    // Alice prepares a quantum bit
    Qubit aliceQubit;
    initializeQubit(&aliceQubit);

    // Bob prepares a measurement basis
    int bobBasis = rand() % 2;

    // Alice sends the quantum bit to Bob through a quantum channel
    QuantumChannel channelToBob;
    channelToBob.qubit = aliceQubit;
    channelToBob.isEavesdropped = 0;

    // Eve, the eavesdropper, attempts to intercept the qubit
    eavesdrop(&channelToBob);

    // Bob measures the qubit
    int bobResult = measureQubit(&channelToBob.qubit, bobBasis);

    // Display results
    printf("Alice's Qubit: %d\n", aliceQubit.value);
    printf("Bob's Measurement Basis: %d\n", bobBasis);
    printf("Eavesdropped: %s\n", channelToBob.isEavesdropped ? "Yes" : "No");
    printf("Bob's Measurement Result: %d\n", bobResult);

    return 0;
}
