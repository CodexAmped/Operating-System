#include <print.h>

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

// Char to represent array of characters for video memory
struct Char {
    unit8_t character; // each character is respresented with ASCII character itself
    unit8_t color; // 8 bits color code
};

struct Char* buffer = (struct Char*) 0xb8000; // Reference to the video memory
size_t col = 0;
size_t row = 0;
unit8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;


void clear_rows(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };
    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}
void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_rows(i);
    }
}
void print_newline() {
    // reset column to 0
    col = 0;

    // check to see if we not at the last row
    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }
    // loop through the second row upwards
    for (size_t row = 1; row < NUM_ROWS; row++) {
        // iterate over all the columns
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character; // move the character by one row
        }
    } 
    // clear the row before we do any printing on it
    clear_row(NUM_COLS - 1);
}
void print_char(char character) {
    // print new line if the character is a new line character
    if (character == '\n') {
        print_newline();
        return;
    }
    // print new line if current column exceeds number of columns
    if (col > NUM_COLS) {
        print_newline();
    }
    // update the character in the buffer
    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (unit8_t) character, //set the ASCII character to the character passed in the function
        color: color, // set color to the current color
    }; 
    // increment the current column number
    col++;
}
void print_str(char* str) {
    // loop through each character in the string
    for (size_t i = 0; 1; i++) {
        char character = (unit8_t) str[i]; // the current character at position i

        // return the function if we come across a no-character
        if(character == '\0') {
            return;
        }
        print_char(character);
    }
}
void print_set_color(unit8_t foreground, unit8_t background) {
    // foreground takes up the first 4 bits and background takes up the other 4 bits by
    // bit-shifiting back by 4 bits
    color = foreground + (background << 4);
}