#include <msp430.h>

#undef C

#define A BIT3
#define B BIT5
#define C BIT7
#define D BIT1
#define E BIT0
#define F BIT4
#define G BIT6
#define DT BIT2

#define D1 BIT0
#define D2 BIT1
#define D3 BIT2
#define D4 BIT5

#define DELAY_TIME 80000

void clearDisplay();
void initDisplay();
void displayCarusel();
void reversedDisplayCarusel();
void circle_animation();
void printLine();
void printDigit();
void cycle_digit_animation();
void printNumber(int number);
int getTemperature();

int switchDisplay = 1;

const unsigned int symbolForDigit[10] = {
        A | B | C | D | E | F,     // 0
        B | C,                     // 1
        A | B | G | D | E,         // 2
        A | B | G | C | D,         // 3
        B | C | F | G,             // 4
        A | C | D | F | G,         // 5
        A | C | D | E | F | G,     // 6
        A | B | C,                 // 7
        A | B | C | D | E | F | G, // 8
        A | B | C | D | F | G      // 9
};

const unsigned int section[4] = { D1, D2, D3, D4 };






int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    CCTL0 = CCIE;
    TACTL = TASSEL_2 + MC_1 + ID_3;
    CCR0 = 10000;

    initDisplay();
    printLine();

    while (1)
    {

        printNumber(7698);

    }

    return 0;
}








void initDisplay()
{

    P1DIR |= A | B | C | D | E | F | G | DT; // initialize segment
    P2DIR |= D1 | D2 | D3 | D4; // initialize sector

    clearDisplay();

}

void clearDisplay()
{
    P1OUT &= ~(A | B | C | D | E | F | G | DT); // OFF all segment
    P2OUT |= D1 | D2 | D3 | D4; // OFF all sector
}

void printDigit(unsigned int digit, unsigned int numberOfDisplay)
{

    switch (numberOfDisplay)
    {

    case 1:
        P2OUT = ~(section[0]);
        break;
    case 2:
        P2OUT = ~(section[1]);
        break;
    case 3:
        P2OUT = ~(section[2]);
        break;
    case 4:
        P2OUT = ~(section[3]);
        break;
    }

    switch (digit)
    {
    case 0:

        P1OUT = symbolForDigit[0];
        break;
    case 1:

        P1OUT = symbolForDigit[1];
        break;
    case 2:

        P1OUT = symbolForDigit[2];
        break;
    case 3:

        P1OUT = symbolForDigit[3];
        break;
    case 4:

        P1OUT = symbolForDigit[4];
        break;
    case 5:

        P1OUT = symbolForDigit[5];
        break;
    case 6:

        P1OUT = symbolForDigit[6];
        break;
    case 7:

        P1OUT = symbolForDigit[7];
        break;
    case 8:

        P1OUT = symbolForDigit[8];
        break;
    case 9:
        P1OUT = symbolForDigit[9];
        break;

    }
}

void printLine(unsigned int numberOfDisplay)
{
    clearDisplay();
    if (numberOfDisplay == 1)
    {
        P2OUT &= ~D1;
    }
    else if (numberOfDisplay == 2)
    {
        P2OUT &= ~D2;
    }
    else if (numberOfDisplay == 3)
    {
        P2OUT &= ~D3;
    }
    else if (numberOfDisplay == 4)
    {
        P2OUT &= ~D4;
    }
    else
    {
        P2OUT &= ~(D1 | D2 | D3 | D4);
    }
    P1OUT |= G;

}
void printNumber(int number)
{

    int primaryNumber = number;
    int displayCounter = 4;
    int counter = 0;

    if (number < 0)
    {
        number *= -1;
    }
    if ((number > -1000) && (number < 10000))
    {
        while (number > 0)
        {
            int res = number % 10;
            number /= 10;
            clearDisplay();
            printDigit(res, displayCounter);
            displayCounter--;
            __delay_cycles(1000);

        }
        if (primaryNumber < 0)
        {
            printLine(displayCounter);
        }

    }
    else
    {
        printLine(4);
    }

}

void cycle_digit_animation()
{

    const unsigned int delay = 1200000;

    printDigit(0, 1);
    __delay_cycles(delay);
    printDigit(1, 2);
    __delay_cycles(delay);
    printDigit(2, 3);
    __delay_cycles(delay);
    printDigit(3, 4);
    __delay_cycles(delay);
    printDigit(4, 1);
    __delay_cycles(delay);
    printDigit(5, 2);
    __delay_cycles(delay);
    printDigit(6, 3);
    __delay_cycles(delay);
    printDigit(7, 4);
    __delay_cycles(delay);
    printDigit(8, 1);
    __delay_cycles(delay);
    printDigit(9, 2);
    __delay_cycles(delay);
    printLine(4);
    __delay_cycles(delay);

}

void displayCarusel()
{
    P1OUT |= A;
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (A | B);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (C | B);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (C | D);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (D | E);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (E | F);
    __delay_cycles(DELAY_TIME);
    P1OUT &= ~F;
}
void reversedDisplayCarusel()
{
    P1OUT |= A;
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (F | A);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (F | E);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (D | E);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (C | D);
    __delay_cycles(DELAY_TIME);
    P1OUT ^= (B | C);
    __delay_cycles(DELAY_TIME);
    P1OUT &= ~B;
}

void circle_animation()
{

    if (switchDisplay > 0)
    {
        P1OUT &= ~DT;

        P2OUT |= D2;
        P2OUT |= D3;
        P2OUT &= ~ D1;
        P2OUT &= ~ D4;
        displayCarusel();
        P1OUT |= DT;
        switchDisplay *= -1;
    }
    else
    {
        P1OUT &= ~DT;
        P2OUT |= D1;
        P2OUT |= D4;
        P2OUT &= ~ D3;
        P2OUT &= ~ D2;
        reversedDisplayCarusel();
        P1OUT |= DT;
        switchDisplay *= -1;
    }

}

