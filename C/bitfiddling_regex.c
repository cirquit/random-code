#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <regex.h>

// 7654 3210  -- Bit Number (we start from 0)
// 0000 0000

//  ^ : XOR
//  & : AND
//  | : OR
//  ~ : Negate bitwise   (x = -x - 1)

// Infos:
//    *) every number except of 0 is True
//    *) 0 is False

// Create a number with the 'x' bit set:
//    *) 1 << x
int
crtbit(int i)
{
  return 1 << i;
}

// Clear a bit 'x'
//
int
clearbit(int x, int i)
{
  return x & ~(1 << i);
}

// Set a bit 'x'
//
int
setbit(int x, int i)
{
  return x | (1 << i);
}

// Clear bits from x-y (y > x)
//
int
clearrange(int x, int i, int j)
{
  return x & ~((~(~0 << (j-i+1))) << i);
}

// Checks if the bit i is set
// 
int
checkbit(int x, int i)
{
  return x & (1 << i);
}

// int main(int argc, char const *argv[])
// {

//     unsigned int a = 0b1111;

//     printf("%d\n", clearrange(a, 0, 1));

//     return 0;
// }



// Endianness


// Little-Endian (least significant byte gets the lowest adress)

/* 0x 12 AB CD
       |  |  |
       |  |  |------> [ A ]  CD
       |  |---------> [A+1]  AB
       |------------> [A+2]  12
                      [A+3]
*/

// Big-Endian (most significant byte gets the lowest adress)

/* 0x 12 AB CD
       |  |  |
       |------------> [ A ]  12
          |---------> [A+1]  AB
             |------> [A+2]  CD
                      [A+3]
*/



/* Regex

    *) ^REG  := matches REG at the start of the line
    *) REG$  := matches REG at the end of the line
    *) [abc] := character class, matches any char between []
    *) .     := any char
    *) [^ab] := negates character class, matches no char between []
    *) predefined character classes
        **) [a-z]
        **) [A-Z]
        **) [0-9]
        **) \d - digit: [0-9]
        **) \D - non-digit: [^0-9]
        **) \s - whitespace character: [ \t\n\x0B\f\r]
        **) \S - non-whitespace character: [^\s]
        **) \w - word character: [a-zA-Z_0-9]
        **) \W - non-word character: [^\w]
    *) Repetition of character classes
        **) [REG]*   - matches the char class zero or more times
        **) [REG]+   - matches the char class one  or more times
        **) [REG]?   - matches the char class zero or one  time
        **) [REG]{x} - matches the char class exactly x    times
        **) [REG]*?  - just like *, not greedy
        **) [REG]+?  - just like +, not greedy
        **) [REG]??  - just like ?, not greedy



a) IT-Kompetenz
b) ^IT
c) Kompetenz$
d) [iI][tT]
e) [a-zA-Z][aAeEiIuUoO][a-zA-Z]
f) [a-zA-Z][^aAeEiIuUoO][a-zA-Z]
g) ^...$
h) [a-z][a-zA-Z0-9_]*
i) "[^"]*"

*/

/*
regex_t regex;
int reti;
char msgbuf[100];

int
main(int argc, char const *argv[])
{
    reti = regcomp(&regex, "\"\\([^\"]*\\)\"", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression 
    reti = regexec(&regex, "\"Hello world!\"", 0, NULL, 0);
    if (!reti) {
        puts("Match");
    }
    else if (reti == REG_NOMATCH) {
        puts("No match");
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    
    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}

*/