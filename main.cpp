#include <bits/stdc++.h>

using namespace std;

//The single and double precision arrays
int singlePrecision[32], doublePrecision[64];

//The number to be read
double x;

void Read(){

    //Reading the number in base 10
    cout << "Number in base 10: ";

    cin >> x;
}

void toFloatingPoint(){

    //If x is 0, skip the algorithm
    if(!x)  return;

    //If x is negative, make it positive and make the sign bit 1
    if(x < 0){
        singlePrecision[0] = doublePrecision[0] = 1;
        x *= -1;
    }

    //Declaring all the variables
    int exponent = 127, integerPart = (int) x, maxPow = 1, integerBits = 0, fractionalBits = 0, currentPower = 1, currentBit = 1;


    double fractionalPart = x - integerPart, minPow = 1;

    //Determining the number of bits of the integer part and the maximum power of 2 with those bits
    while(maxPow * 2 <= integerPart){
        integerBits++;    maxPow *= 2;
    }

    //Determining the number of bits of the fractional part and the minimum power of 2 with those bits
    while(fractionalPart < minPow && fractionalPart != 0){
        fractionalBits++;    minPow /= 2;
    }

    //If there exist bits in the integer part, increase the exponent with the number of integer bits,
    //else decrease the exponent with the number of fractional bits:
    if(integerBits)   exponent += integerBits;

    else    exponent -= fractionalBits;

    //Determining the largest power of 2 written with the number of bits used to write the exponent
    while(currentPower * 2 < exponent)  currentPower *= 2;

    //Transforming the exponent in base 2 and writing it in both single and double precision arrays
    while(currentPower){

        singlePrecision[currentBit] = doublePrecision[currentBit] = (exponent - currentPower >= 0) ? 1 : 0;

        if(exponent - currentPower >= 0)    exponent -= currentPower;

        currentPower /= 2;

        currentBit++;
    }

    if(integerBits){

        //If exists an integer part, eliminating the first bit from the normalized form of the number:
        integerPart -= maxPow;  maxPow /= 2;

        //Transforming the integer part in base 2 and writing it in both single and double precision arrays
        while(maxPow){

            singlePrecision[currentBit] = doublePrecision[currentBit] = (integerPart - maxPow >= 0) ? 1 : 0;

            if(integerPart - maxPow >= 0)    integerPart -= maxPow;

            maxPow /= 2;

            currentBit++;
        }
    }

    //If there is only a fractional part, bringing it to normal form
    if(!integerBits)
        for(int i = 0; i < fractionalBits; i++) {
            fractionalPart *= 2;

            if(fractionalPart >= 1) fractionalPart--;
        }

    //Transforming the fractional part in base 2 and writing it in both single and double precision arrays
    while(currentBit < 32 && fractionalPart != 0){

        singlePrecision[currentBit] = doublePrecision[currentBit] = (2 * fractionalPart >= 1) ? 1 : 0;

        fractionalPart *= 2;

        if(fractionalPart >= 1)   fractionalPart -= 1;

        currentBit++;
    }

    //Writing the remaining bits of the double precision form:
    while(currentBit < 64 && fractionalPart != 0){

        doublePrecision[currentBit] = (2 * fractionalPart >= 1) ? 1 : 0;

        fractionalPart *= 2;

        if(fractionalPart >= 1)   fractionalPart -= 1;

        currentBit++;
    }

    cout << '\n';
}

void Print(){

    //Printing the number in binary, single precision
    cout << "\n\nSingle precision binary: ";
    for(int i = 0; i < 32; i++){

        cout << singlePrecision[i];

        if((i + 1) % 4 == 0)    cout << ' ';
    }

    //Printing the number in binary, double precision
    cout << "\n\nDouble precision binary: ";
    for(int i = 0; i < 64; i++){

        cout << doublePrecision[i];

        if((i + 1) % 4 == 0)    cout << ' ';
    }

    //Printing the number in HEX, single precision
    cout << "\n\nSingle precision HEX: ";
    for(int i = 0; i < 32; i += 4){

        int sum = singlePrecision[i] * 8 + singlePrecision[i + 1] * 4 + singlePrecision[i + 2] * 2 + singlePrecision[i + 3];

        switch(sum){

            case 10:    cout << 'A';    break;
            case 11:    cout << 'B';    break;
            case 12:    cout << 'C';    break;
            case 13:    cout << 'D';    break;
            case 14:    cout << 'E';    break;
            case 15:    cout << 'F';    break;

            default:    cout << sum;
        }
    }

    //Printing the number in HEX, double precision
    cout << "\n\nDouble precision HEX: ";
    for(int i = 0; i < 64; i += 4){

        int sum = doublePrecision[i] * 8 + doublePrecision[i + 1] * 4 + doublePrecision[i + 2] * 2 + doublePrecision[i + 3];

        switch(sum){

            case 10:    cout << 'A';    break;
            case 11:    cout << 'B';    break;
            case 12:    cout << 'C';    break;
            case 13:    cout << 'D';    break;
            case 14:    cout << 'E';    break;
            case 15:    cout << 'F';    break;

            default:    cout << sum;
        }
    }


    cout << "\n\n\n";
}

int main(){

    Read();

    toFloatingPoint();

    Print();

    return 0;
}
