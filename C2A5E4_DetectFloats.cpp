// Aladin Sidahmed U08614258 
// aladin.sidahmed@gmail.com
// C/C++ Programming II 
// Section 145010 Ray Mitchell 
// 17 FEB 2020
// C2A5E4_DetectFloats.cpp
// Operating System: Windows 7 
// Visual Studio Community 2019 Version 16.3.2 
//
// This file contains one function:
//      DetectFloats: Implements a function that detects
//      hexadecimal floating literals of a string passed 
//      in the variable chPtr
//

#include <cstring>
#include "C2A5E4_StatusCode-Driver.h"

StatusCode DetectFloats(const char *chPtr)
{
    enum States 
    {
        START,
        PREFIX_START,
        PREFIX,
        NO_WHOLE,
        FRACT,
        WHOLE,
        BINARY_EXP,
        SIGN,
        DIGIT_SEQUENCE,
        FLOAT,
        LONG_DOUBLE
    } state = START;

    for (int characterIndex = 0; characterIndex < (int)strlen(chPtr); 
        characterIndex++)
    {
        switch (state)
        {
        // START looks for a 0 character or exits
        case START:
            switch (chPtr[characterIndex]) 
            {
            case '0':
                state = PREFIX_START;
                break;
            default:
                return NO_MATCH;
            }
            break; 
            
        // PREFIX_START looks for x or X or exits
        case PREFIX_START:
            switch (chPtr[characterIndex])
            {
            case 'x': case 'X':
                state = PREFIX;
                break;
            default:
                return NO_MATCH;
            }
            break; 
            
        // PREFIX : 
        // '.'  moves to to NO_WHOLE
        // Hex digit moves to WHOLE
        // Anything else exits
        case PREFIX:
            switch (chPtr[characterIndex])
            {
            case '.':
                state = NO_WHOLE;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F': case 'a': case 'b': case 'c': case 'd':
            case 'e': case 'f':
                state = WHOLE;
                break;
            default:
                return NO_MATCH;
            }
            break; 

        // WHOLE:
        // '.' moves to FRACT
        // Hex digit stays in WHOLE
        // p or P moves to BINARY_EXP
        // anything else exits
        case WHOLE:
            switch (chPtr[characterIndex])
            {
            case '.':
                state = FRACT;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F': case 'a': case 'b': case 'c': case 'd':
            case 'e': case 'f':
                state = WHOLE;
                break;
            case 'p': case 'P':
                state = BINARY_EXP;
                break;
            default:
                return NO_MATCH;
            }
            break; 

        // NO_WHOLE
        // Hex digit moves to FRACT
        // anything else exits
        case NO_WHOLE:
            switch (chPtr[characterIndex])
            {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F': case 'a': case 'b': case 'c': case 'd':
            case 'e': case 'f':
                state = FRACT;
                break;
            default:
                return NO_MATCH;
            }
            break; 

        // FRACT
        // Hex digit stays in FRACT
        // P or p moves to BINARY_EXP
        // anything else exits
        case FRACT:
            switch (chPtr[characterIndex])
            {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F': case 'a': case 'b': case 'c': case 'd':
            case 'e': case 'f':
                state = FRACT;
                break;
            case 'p': case 'P':
                state = BINARY_EXP;
                break;
            default:
                return NO_MATCH;
            }
            break; 

        // BINARY_EXP
        // '-' or '+' moves to SIGN
        // digits moves to DIGIT_SEQUENCE
        // anything else exits
        case BINARY_EXP:
            switch (chPtr[characterIndex])
            {
            case '-': case '+':
                state = SIGN;
                break;
            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                state = DIGIT_SEQUENCE;
                break;
            default:
                return NO_MATCH;
            }
            break; 

        // SIGN
        // digit moves to DIGIT_SEQUENCE
        // anything else exits
        case SIGN:
            switch (chPtr[characterIndex])
            {
            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                state = DIGIT_SEQUENCE;
                break;
            default:
                return NO_MATCH;
            }
            break;

        // DIGIT_SEQUENCE
        // digit stays in DIGIT_SEQUENCE
        // l or L moves to LONG_DOUBLE
        // f or F moves to FLOAT
        // end of string will return TYPE_DOUBLE on exiting the loop
        // anything else exits
        case DIGIT_SEQUENCE:
            switch (chPtr[characterIndex])
            {
            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                state = DIGIT_SEQUENCE;
                break;
            case 'l': case 'L':
                state = LONG_DOUBLE;
                break;

            case 'f': case 'F':
                state = FLOAT;
                break;
            default:
                return NO_MATCH;
            }
            break; 

        // LONG_DOUBLE
        // end of string will return TYPE_LDOUBLE
        // anything else will exit
        case LONG_DOUBLE:
            switch (chPtr[characterIndex])
            {
            case 'L': case 'l':
            default:
                return NO_MATCH;
            }
 
        // FLOAT
        // end of string will return TYPE_FLOAT
        // anything else will exit
        case FLOAT:
            switch (chPtr[characterIndex])
            {
            case 'f': case 'F':
            default:
                return NO_MATCH;
            }

        default:
            break;
        }
    }

    switch (state)
    {
    case DIGIT_SEQUENCE:
        return TYPE_DOUBLE;
    case LONG_DOUBLE:
        return TYPE_LDOUBLE;
    case FLOAT:
        return TYPE_FLOAT;
    default:
        return NO_MATCH;
    } 
}
