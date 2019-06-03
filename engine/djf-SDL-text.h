/* Header file for displaying characters with SDL. Written
in pure C. Supports ascii characters 32 to 126. */

#ifndef SDL2_SDL_H
#define SDL2_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

/* This function renders a single character with a renderer.
It returns 0 on success and nonzero on an error. */
int render_char(SDL_Renderer *renderer, /* rendering context */
                float x, /* position of the character */
                float y,
                const char character, /* the actual character to display
                                  (I plan to support the full ascii set when this is done) */
                int r, /* colour is in 8-bit RGB values */
                int g,
                int b,
                int alpha) {
    int error_val;
    error_val += SDL_SetRenderDrawColor(renderer, r, g, b, alpha);

    /* Every character is 8 pixels tall and 5 pixels wide. Upon encountering
    an unrecognized character, it displays a highlighted question mark. */
    switch (character) {
        case ' ':
            break;
        case '!':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+5);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y+7);
            break;
        case '"':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+1, y+1);
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+3, y+1);
            break;
        case '#':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+1, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+4, y+5);
            break;
        case '$':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+5);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+1);
            error_val += SDL_RenderDrawPoint(renderer, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+2, y-1, x+2, y+8);
            break;
        case '%':
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x, y+5);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y);
            error_val += SDL_RenderDrawPoint(renderer, x, y+1);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y+1);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+2);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+5);
            break;
        case '&':
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+1);
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+2, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+4, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+4);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x, y+6);
            break;
        case '\'':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+1);
            break;
        case '(':
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+1, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+5, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+1, y+5);
            break;
        case ')':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+5, x+1, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+2, x+3, y+5);
            break;
        case '*':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+1, y+4);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+2);
            break;
        case '+':
            error_val += SDL_RenderDrawLine(renderer, x+2, y+1, x+2, y+5);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            break;
        case ',':
            error_val += SDL_RenderDrawLine(renderer, x+2, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+5, x+1, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+8);
            break;
        case '-':
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            break;
        case '.':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+6, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+2, y+6);
            break;
        case '/':
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y);
            break;
        case '0':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+5);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+5);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+4, y+2);
            break;
        case '1':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+2, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+6);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case '2':
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x+1, y);
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+4, y+1);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case '3':
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x+1, y);
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+2, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+3, x+4, y+5);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+6, x+1, y+7);
            break;
        case '4':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+4);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            break;
        case '5':
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x, y);
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x+1, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x, y+6);
            break;
        case '6':
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+1, y);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+1);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+6, x+4, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+3, x+1, y+3);
            break;
        case '7':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+1);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+3, y+7);
            break;
        case '8':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            break;
        case '9':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x+1, y+7);
            break;
        case ':':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+3, y+1);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+1, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+6, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+7, x+3, y+6);
            break;
        case ';':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+2, y+1);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+1, x+2, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+5, x+1, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+8);
            break;
        case '<':
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+1);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+6);
            break;
        case '=':
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+4, y+5);
            break;
        case '>':
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x, y+1);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x, y+6);
            break;
        case '?':
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x+1, y);
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+3, x+2, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+4, x+1, y+5);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+7);
            break;
        case '@':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+7, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+2, x+2, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+2, x+2, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+4, x+4, y+4);
            break;
        case 'A':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+4, y+2);
            error_val += SDL_RenderDrawPoint(renderer, x+0, y+3);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+4);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x+4, y+7);
            break;
        case 'B':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+4, x+4, y+6);
            break;
        case 'C':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case 'D':
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            break;
        case 'E':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case 'F':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            break;
        case 'G':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+7, x+4, y+3);
            break;
        case 'H':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            break;
        case 'I':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+6);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case 'J':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+3, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x, y+6);
            break;
        case 'K':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+7);
            break;
        case 'L':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case 'M':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+2, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+2, y+3);
            break;
        case 'N':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y+7);
            break;
        case 'O':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+5);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+5);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+2, y+7);
            break;
        case 'P':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+2);
            break;
        case 'Q':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+5);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+5);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+4, x+4, y+7);
            break;
        case 'R':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+3, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+1, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+4, y+7);
            break;
        case 'S':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+5);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+1);
            error_val += SDL_RenderDrawPoint(renderer, x, y+6);
            break;
        case 'T':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+7);
            break;
        case 'U':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            break;
        case 'V':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+2, y+7);
            break;
        case 'W':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+6);
            break;
        case 'X':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+5);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x, y+5);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+4, y+7);
            break;
        case 'Y':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+2, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x+2, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+4, x+2, y+7);
            break;
        case 'Z':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case '[':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+3, y);
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+3, y+7);
            break;
        case '\\':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y+7);
            break;
        case ']':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case '^':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+2, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+4, y+2);
            break;
        case '_':
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case '`':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y+2);
            break;
        case 'a':
            error_val += SDL_RenderDrawLine(renderer, x+4, y+7, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+2, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+4, x+1, y+4);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case 'b':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            break;
        case 'c':
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x+1, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case 'd':
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+2, x+1, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x+1, y+7);
            break;
        case 'e':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+4);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case 'f':
            error_val += SDL_RenderDrawLine(renderer, x, y+1, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x+3, y);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+1);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+3, y+3);
            break;
        case 'g':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+8);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+9, x+3, y+9);
            break;
        case 'h':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+7);
            break;
        case 'i':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+2, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+2, x+2, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x+4, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y);
            break;
        case 'j':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+2, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+2, x+2, y+8);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+9);
            break;
        case 'k':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+5, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+4, y+7);
            break;
        case 'l':
            error_val += SDL_RenderDrawLine(renderer, x, y, x+2, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x+4, y+7);
            break;
        case 'm':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+3, x+2, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+7);
            break;
        case 'n':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+7);
            break;
        case 'o':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+6);
            break;
        case 'p':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+9);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+6);
            break;
        case 'q':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+3, x+4, y+9);
            break;
        case 'r':
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+4, y+2);
            break;
        case 's':
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+4, y+2);
            error_val += SDL_RenderDrawPoint(renderer, x, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+4, x+3, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+5, x+4, y+6);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+3, y+7);
            break;
        case 't':
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+2, x+3, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            break;
        case 'u':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x+4, y+7);
            break;
        case 'v':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+2, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x+2, y+7);
            break;
        case 'w':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+2, x+2, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x+4, y+7);
            break;
        case 'x':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x, y+7);
            break;
        case 'y':
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x+4, y+8);
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+7, x+3, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+9, x+3, y+9);
            break;
        case 'z':
            error_val += SDL_RenderDrawLine(renderer, x, y+2, x+4, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+4, y+2, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            break;
        case '{':
            error_val += SDL_RenderDrawLine(renderer, x+3, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+1, x+2, y+2);
            error_val += SDL_RenderDrawLine(renderer, x, y+3, x+1, y+3);
            error_val += SDL_RenderDrawLine(renderer, x, y+4, x+1, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+5, x+2, y+6);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+7, x+4, y+7);
            break;
        case '|':
            error_val += SDL_RenderDrawLine(renderer, x+2, y, x+2, y+7);
            break;
        case '}':
            error_val += SDL_RenderDrawLine(renderer, x+1, y, x, y);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+1, x+2, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+3, x+4, y+3);
            error_val += SDL_RenderDrawLine(renderer, x+3, y+4, x+4, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+2, y+5, x+2, y+6);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+1, y+7);
            break;
        case '~':
            error_val += SDL_RenderDrawPoint(renderer, x, y+2);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+1, x+3, y+3);
            error_val += SDL_RenderDrawPoint(renderer, x+4, y+2);
            break;
        default:
            error_val += SDL_RenderDrawLine(renderer, x, y, x, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y, x+4, y);
            error_val += SDL_RenderDrawLine(renderer, x+4, y, x+4, y+7);
            error_val += SDL_RenderDrawLine(renderer, x, y+7, x+4, y+7);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+1);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+2);
            error_val += SDL_RenderDrawPoint(renderer, x+2, y+2);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+3);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+3);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+4);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+4);
            error_val += SDL_RenderDrawLine(renderer, x+1, y+5, x+3, y+5);
            error_val += SDL_RenderDrawPoint(renderer, x+1, y+6);
            error_val += SDL_RenderDrawPoint(renderer, x+3, y+6);
            break;
    }
    return error_val;
}

int render_string(SDL_Renderer *renderer, /* rendering context */
                float x, /* top-left corner of the string */
                float y,
                const char string[],
                int string_length, /* easier to have the programmer
                                    explicitly specify this for us */
                int r, /* colour is in 8-bit RGB values */
                int g,
                int b,
                int alpha) {
    int error_val;
    int i;
    for (i=0; i<string_length; i++) {
        error_val += render_char(renderer, x+(6*i), y, string[i], r, g, b, alpha);
    }
    return error_val;
}
