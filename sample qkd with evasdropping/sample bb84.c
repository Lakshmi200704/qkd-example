#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUBIT_0 0
#define QUBIT_1 1
#define BASIS_X 0
#define BASIS_Z 1

typedef struct
{
    int value;
    int basis;
} Qubit;

typedef struct
{
    Qubit qubit;
    int isEavesdropped;
} QuantumChannel;

void initializeQubit(Qubit *qubit)
{
    qubit->value = rand() % 2;
    qubit->basis = rand() % 2;
}

int measureQubit(Qubit *qubit, int basis)
{
    if (qubit->basis == basis)
    {
        return qubit->value;
    }
    else
    {
        qubit->value = rand() % 2;
        return qubit->value;
    }
}

void eavesdrop(QuantumChannel *channel)
{
    channel->isEavesdropped = 1;
}

int main()
{
    srand(time(NULL));

    // Alice prepares qubits
    Qubit aliceQubits[100];
    for (int i = 0; i < 100; i++)
    {
        initializeQubit(&aliceQubits[i]);
    }

    // Alice randomly chooses bases for encoding
    int aliceBases[100];
    for (int i = 0; i < 100; i++)
    {
        aliceBases[i] = rand() % 2;
    }

    // Bob randomly chooses bases for measurement
    int bobBases[100];
    for (int i = 0; i < 100; i++)
    {
        bobBases[i] = rand() % 2;
    }

    // Alice sends qubits to Bob through a quantum channel
    QuantumChannel channelToBob[100];
    for (int i = 0; i < 100; i++)
    {
        channelToBob[i].qubit = aliceQubits[i];
        channelToBob[i].isEavesdropped = 0;
    }

    // Eve, the eavesdropper, attempts to intercept the qubits
    for (int i = 0; i < 100; i++)
    {
        eavesdrop(&channelToBob[i]);
    }

    // Bob measures the qubits
    int bobResults[100];
    for (int i = 0; i < 100; i++)
    {
        bobResults[i] = measureQubit(&channelToBob[i].qubit, bobBases[i]);
    }

    // Alice and Bob reveal their bases
    printf("Alice's Bases: ");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", aliceBases[i]);
    }
    printf("\n");

    printf("Bob's Bases: ");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", bobBases[i]);
    }
    printf("\n");

    // Alice and Bob share their bases and discard measurements with mismatched bases
    printf("Alice's Key Bits: ");
    for (int i = 0; i < 100; i++)
    {
        if (aliceBases[i] == bobBases[i])
        {
            printf("%d ", aliceQubits[i].value);
        }
    }
    printf("\n");
    printf("Bob's Key Bits: ");
    for (int i = 0; i < 100; i++)
    {
        if (aliceBases[i] == bobBases[i])
        {
            printf("%d ", bobResults[i]);
        }
    }
    printf("\n");

    // Alice and Bob perform a security check by comparing a subset of their key bits
    int securityCheckBits = 10;  // Number of bits used for security check
    int securityCheckPassed = 1; // Flag indicating if security check passed

    for (int i = 0; i < securityCheckBits; i++) {
        if (aliceBases[i] == bobBases[i]) {
            // The bases match, compare the values
            if (aliceQubits[i].value != bobResults[i]) {
                securityCheckPassed = 0; // Security check failed
                break;
            }
        }
    }

    if (securityCheckPassed) {
        printf("Security check passed. Key exchange successful!\n");

        // Extract the shared key from the remaining bits
        printf("Shared Key: ");
        for (int i = securityCheckBits; i < 100; i++) {
            if (aliceBases[i] == bobBases[i]) {
                printf("%d ", aliceQubits[i].value);
            }
        }
        printf("\n");

        // Alice and Bob can use the shared key for secure communication
    } else {
        printf("Security check failed. Possible eavesdropping detected!\n");
        // Alice and Bob should abort the key exchange process
    }

    return 0;
}
