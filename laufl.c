# Copyright (c) 2010, Bjoern Heller <tec@hellercom.de>. All rights reserved
# This code is licensed under GNU/ GPL

#include <inttypes.h>                                               // Allgemeine Bibliotheken
#include <avr/io.h>
#include <avr/interrupt.h>

#define sbi(ADDRESS,BIT) ((ADDRESS) |= (1<<(BIT)))
#define cbi(ADDRESS,BIT) ((ADDRESS) &amp;= ~(1<<(BIT)))

void warte(uint16_t t) {                                            // Funktion "Warteschleife"
        uint16_t i, j;

        for (i=0;i<t;i++) {                                         // Verschachtelte Schleife mit Befehl NOP="Tue nichts", damit
                for (j=1;j<300;j++) {                               // die Schleife nicht wegoptimiert wird.
                        asm volatile ("nop");
                }
        }
}

int main (void) {
        uint8_t lauflicht;

        DDRB=0xFF;                                                  // Port B auf Ausgang
        PORTB=0xFF;                                                 // Alle Ausgänge auf 1

        DDRD=0xFF;                                                  // Port D auf Ausgang
        PORTD=0xFF;                                                 // Alle Ausgänge auf 1

        lauflicht=1;
        for (;;) {                                                  // Endlosschleife
                PORTB=~lauflicht;                                   // Untere 8 Bit auf PORT B ausgegeben
                lauflicht=lauflicht<<1;                             // Lauflicht um 1 Bit nach links weiterschieben
                if (lauflicht==0)                                   // Wenn Lauflicht durchgelaufen ist, dann wieder am Anfang beginnen
                lauflicht=1;
                warte(50);                                        // Warten
        }
}
