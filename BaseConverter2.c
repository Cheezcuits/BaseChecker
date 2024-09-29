#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char inputNumber[100]; 
int BaseInput, BaseOutput;

void WelcomeMessage() {
    printf("Hai hello welcome to a base converter thing, good luck with this mess...\n");
}

void InputMessage() {
    printf("Please enter a number (you can use fractions):\n");
    scanf("%s", inputNumber);  // Reading input as a string
    printf("What base is your number?\n");
    printf("1. Binary\n2. Decimal\n3. Octal\n4. Hexadecimal\n");
    scanf("%d", &BaseInput);
    printf("Please select a base you are going to convert to:\n");
    printf("1. Binary\n2. Decimal\n3. Octal\n4. Hexadecimal\n");
    scanf("%d", &BaseOutput);
}


double FractionToDecimal(const char* fracPart, int base) {
    double fracValue = 0;
    double basePower = base;  
    for (int i = 0; fracPart[i] != '\0'; i++) {
        int digit = (fracPart[i] >= 'A') ? (fracPart[i] - 'A' + 10) : (fracPart[i] - '0');
        fracValue += digit / basePower;
        basePower *= base;
    }
    return fracValue;
}


void DecimalToBinary(double decimalValue) {
    long intPart = (long)decimalValue;
    double fracPart = decimalValue - intPart;
    char binary[100] = "";  // To store binary result
    int i = 0;

    if (intPart == 0) {
        printf("0");
    } else {
        while (intPart > 0) {
            binary[i++] = (intPart % 2) + '0';
            intPart /= 2;
        }
        for (int j = i - 1; j >= 0; j--) {
            printf("%c", binary[j]);
        }
    }

    if (fracPart > 0) {
        printf(".");
        for (i = 0; i < 10 && fracPart > 0; i++) {  
            fracPart *= 2;
            if (fracPart >= 1) {
                printf("1");
                fracPart -= 1;
            } else {
                printf("0");
            }
        }
    }
    printf("\n");
}

void DecimalToOctal(double decimalValue) {
    long intPart = (long)decimalValue;
    double fracPart = decimalValue - intPart;
    char octal[100] = "";
    int i = 0;

    if (intPart == 0) {
        printf("0");
    } else {
        while (intPart > 0) {
            octal[i++] = (intPart % 8) + '0';
            intPart /= 8;
        }
        for (int j = i - 1; j >= 0; j--) {
            printf("%c", octal[j]);
        }
    }

    
    if (fracPart > 0) {
        printf(".");
        for (i = 0; i < 10 && fracPart > 0; i++) { 
            fracPart *= 8;
            printf("%d", (int)fracPart);
            fracPart -= (int)fracPart;
        }
    }
    printf("\n");
}

void DecimalToHexadecimal(double decimalValue) {
    long intPart = (long)decimalValue;
    double fracPart = decimalValue - intPart;
    char hex[100] = "";
    int i = 0;

    // Convert integer part to hexadecimal
    if (intPart == 0) {
        printf("0");
    } else {
        while (intPart != 0) {
            int remainder = intPart % 16;
            if (remainder < 10) {
                hex[i] = remainder + '0';
            } else {
                hex[i] = remainder - 10 + 'A';
            }
            i++;
            intPart /= 16;
        }
        for (int j = i - 1; j >= 0; j--) {
            printf("%c", hex[j]);
        }
    }

    if (fracPart > 0) {
        printf(".");
        for (i = 0; i < 10 && fracPart > 0; i++) {  // Limit to 10 hex places
            fracPart *= 16;
            int digit = (int)fracPart;
            if (digit < 10) {
                printf("%d", digit);
            } else {
                printf("%c", 'A' + digit - 10);
            }
            fracPart -= digit;
        }
    }
    printf("\n");
}

int main() {
    char continueLoop = 'y';
    while (continueLoop == 'y' || continueLoop == 'Y') {
        WelcomeMessage();
        InputMessage();

        char* integerPart = strtok(inputNumber, ".");
        char* fractionalPart = strtok(NULL, ".");

        long decimalIntValue = 0;
        double decimalFractionalValue = 0;

        switch (BaseInput) {
            case 1:  // Binary input
                decimalIntValue = strtol(integerPart, NULL, 2);  // Binary to Decimal
                if (fractionalPart) {
                    decimalFractionalValue = FractionToDecimal(fractionalPart, 2);
                }
                break;
            case 2:  // Decimal input
                decimalIntValue = strtol(integerPart, NULL, 10);  // Already Decimal
                if (fractionalPart) {
                    decimalFractionalValue = atof(fractionalPart) / pow(10, strlen(fractionalPart));
                }
                break;
            case 3:  // Octal input
                decimalIntValue = strtol(integerPart, NULL, 8);  // Octal to Decimal
                if (fractionalPart) {
                    decimalFractionalValue = FractionToDecimal(fractionalPart, 8);
                }
                break;
            case 4:  // Hexadecimal input
                decimalIntValue = strtol(integerPart, NULL, 16);  // Hexadecimal to Decimal
                if (fractionalPart) {
                    decimalFractionalValue = FractionToDecimal(fractionalPart, 16);
                }
                break;
            default:
                printf("Invalid input base selection.\n");
                return 1;
        }

        double totalDecimalValue = decimalIntValue + decimalFractionalValue;

        switch (BaseOutput) {
            case 1:  // Decimal to Binary
                DecimalToBinary(totalDecimalValue);
                break;
            case 2:  // Decimal to Decimal
                printf("Decimal: %lf\n", totalDecimalValue);
                break;
            case 3:  // Decimal to Octal
                DecimalToOctal(totalDecimalValue);
                break;
            case 4:  // Decimal to Hexadecimal
                DecimalToHexadecimal(totalDecimalValue);
                break;
            default:
                printf("Invalid output base selection.\n");
                break;
        }

        printf("Do you want to convert another number? (y/n): ");
        scanf(" %c", &continueLoop);  
    }

    printf("Good luck with MMW!\n");
    return 0;
}
