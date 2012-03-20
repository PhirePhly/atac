// atac.c -- ASCII to ASCII Converter
// Copyright 2007, 2008 - Kenneth Finnegan.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTER_SPACE "  "
#define FONT_WIDTH	7

#define STRMATCH(a,b)	(strcmp((a),(b)) == 0)

void buf_init(char *buf[], int count);
void buf_free(char *buf[]);
void addspace(char *buf[]);
void addletter(char newletter, char *buf[]);
void display(char *buf[]);

char *commentprefix; // Beginning of every line

main(int argc, char *argv[]) {
	// init vars
	int i, j = 1;
	commentprefix = (char *) malloc(sizeof(char) * 1);
	commentprefix[0] = '\0';

	for (j = 1; j < argc; j++) {
		// Test for -c commentprefix
		if (STRMATCH(argv[j],"-c")) {
			// Set the comment prefix to the next argument
			if (argc < j + 2) {
				fprintf(stderr, \
				"%s: Comment prefix missing after -c\n",\
					argv[0]);
				exit(EXIT_FAILURE);
			}
			free(commentprefix);
			commentprefix = (char *) malloc(sizeof(char) * \
						(strlen(argv[j+1])+2));
			sprintf(commentprefix, "%s ", argv[j+1]);
			j++; // Skip the comment prefix
			continue;
		}

		char *input;
		char *buf[9];

		// scan in line
		input = argv[j];

		// init the buffer
		buf_init(buf, strlen(input));

		for (i=0; i<strlen(input); i++) {
			addletter(input[i], buf);
			if (input[i+1]) {
				addspace(buf);
			}
		}

		// Display buf
		display(buf);

		buf_free(buf);

		// Add a space between lines of text
		if (j != argc - 1)
			printf("\n");
	}

} // END main()

/* void buf_init(char *buf[])
 *
 * mallocs memory for the 9 line buffer for the output.
 * It also adds the comment prefix if there is any.  The comment
 * prefix starts as '\0' so there is no test for it.
 */
void buf_init(char *buf[], int count) {
	int i;
	int buffer_size = count * (FONT_WIDTH + strlen(LETTER_SPACE)) + 2;

	for (i=0; i<9; i++) {
		buf[i] = (char *) malloc(buffer_size);
		if (buf[i] == NULL) {
			fprintf(stderr, "buf_init malloc failed");
			exit(0);
		}
		sprintf(buf[i], "%s", commentprefix);
	}
} // END buf_init

/* buf_free
 *
 * Frees the malloced buffer when it is done with
 */
void buf_free(char *buf[]) {
	int i;

	for (i=0; i<9; i++) {
		free(buf[i]);
	}
} // END buf_free

// display(buf) - Print the buffer to stdout
void display (char *buf[]) {
	int i;

	for (i=0; i<9; i++) {
		printf("%s\n", buf[i]); // prints line to stdout
		sprintf(buf[i], "\0"); // Resets buf
	}
} // END display()

/* void addspace(char *buf[])
 *
 * Adds the font space between letters.  This is usually only one space
 */
void addspace(char *buf[]) {
	int i;
	char space[] = LETTER_SPACE;

	for(i=0; i<9; i++) {
		strcat(buf[i], space);
	}
} // END addspace()

void addletter(char newletter, char *buf[]) {

	switch (newletter) {
		case ' ':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "       ");
			strcat(buf[3], "       ");
			strcat(buf[4], "       ");
			strcat(buf[5], "       ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '!':
			strcat(buf[0], "   !   ");
			strcat(buf[1], "  !!!  ");
			strcat(buf[2], "  !!!  ");
			strcat(buf[3], "  !!!  ");
			strcat(buf[4], "  !!!  ");
			strcat(buf[5], "   !   ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "  !!!  ");
			break;
		case '"':
			strcat(buf[0], "  \" \"  ");
			strcat(buf[1], "  \" \"  ");
			strcat(buf[2], "       ");
			strcat(buf[3], "       ");
			strcat(buf[4], "       ");
			strcat(buf[5], "       ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '#':
			strcat(buf[0], "  #   #");
			strcat(buf[1], "  #   #");
			strcat(buf[2], " #   # ");
			strcat(buf[3], "#######");
			strcat(buf[4], " #   # ");
			strcat(buf[5], "#######");
			strcat(buf[6], " #   # ");
			strcat(buf[7], " #   # ");
			strcat(buf[8], "#   #  ");
			break;
		case '$':
			strcat(buf[0], "  $$$  ");
			strcat(buf[1], "$$ $ $$");
			strcat(buf[2], "$  $  $");
			strcat(buf[3], "$$ $   ");
			strcat(buf[4], "  $$$  ");
			strcat(buf[5], "   $ $$");
			strcat(buf[6], "$  $  $");
			strcat(buf[7], "$$ $ $$");
			strcat(buf[8], "  $$$  ");
			break;
		case '%':
			strcat(buf[0], "      %");
			strcat(buf[1], " %    %");
			strcat(buf[2], "     % ");
			strcat(buf[3], "    %  ");
			strcat(buf[4], "   %   ");
			strcat(buf[5], "  %    ");
			strcat(buf[6], " %     ");
			strcat(buf[7], "%    % ");
			strcat(buf[8], "%      ");
			break;
		case '&':
			strcat(buf[0], "&&&    ");
			strcat(buf[1], "&  &   ");
			strcat(buf[2], "&      ");
			strcat(buf[3], " &     ");
			strcat(buf[4], "  &    ");
			strcat(buf[5], " & &  &");
			strcat(buf[6], "&   & &");
			strcat(buf[7], "&&   & ");
			strcat(buf[8], "  &&& &");
			break;
		case '(':
			strcat(buf[0], "    (  ");
			strcat(buf[1], "   (   ");
			strcat(buf[2], "  (    ");
			strcat(buf[3], "  (    ");
			strcat(buf[4], "  (    ");
			strcat(buf[5], "  (    ");
			strcat(buf[6], "  (    ");
			strcat(buf[7], "   (   ");
			strcat(buf[8], "    (  ");
			break;
		case ')':
			strcat(buf[0], "  )    ");
			strcat(buf[1], "   )   ");
			strcat(buf[2], "    )  ");
			strcat(buf[3], "    )  ");
			strcat(buf[4], "    )  ");
			strcat(buf[5], "    )  ");
			strcat(buf[6], "    )  ");
			strcat(buf[7], "   )   ");
			strcat(buf[8], "  )    ");
			break;
		case '*':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], " * * * ");
			strcat(buf[3], "  ***  ");
			strcat(buf[4], " ***** ");
			strcat(buf[5], "  ***  ");
			strcat(buf[6], " * * * ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '+':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "   +   ");
			strcat(buf[3], "   +   ");
			strcat(buf[4], " +++++ ");
			strcat(buf[5], "   +   ");
			strcat(buf[6], "   +   ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '-':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "       ");
			strcat(buf[3], "       ");
			strcat(buf[4], " ----- ");
			strcat(buf[5], "       ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '/':
			strcat(buf[0], "       ");
			strcat(buf[1], "      /");
			strcat(buf[2], "     / ");
			strcat(buf[3], "    /  ");
			strcat(buf[4], "   /   ");
			strcat(buf[5], "  /    ");
			strcat(buf[6], " /     ");
			strcat(buf[7], "/      ");
			strcat(buf[8], "       ");
			break;
		case '0':
			strcat(buf[0], "  000  ");
			strcat(buf[1], "00   00");
			strcat(buf[2], "0    00");
			strcat(buf[3], "0   0 0");
			strcat(buf[4], "0  0  0");
			strcat(buf[5], "0 0   0");
			strcat(buf[6], "00    0");
			strcat(buf[7], "00   00");
			strcat(buf[8], "  000  ");
			break;
		case '1':
			strcat(buf[0], "   1   ");
			strcat(buf[1], "  11   ");
			strcat(buf[2], " 1 1   ");
			strcat(buf[3], "   1   ");
			strcat(buf[4], "   1   ");
			strcat(buf[5], "   1   ");
			strcat(buf[6], "   1   ");
			strcat(buf[7], "   1   ");
			strcat(buf[8], "1111111");
			break;
		case '2':
			strcat(buf[0], "  222  ");
			strcat(buf[1], " 2   22");
			strcat(buf[2], "      2");
			strcat(buf[3], "     2 ");
			strcat(buf[4], "    2  ");
			strcat(buf[5], "   2   ");
			strcat(buf[6], "  2    ");
			strcat(buf[7], " 2     ");
			strcat(buf[8], "2222222");
			break;
		case '3':
			strcat(buf[0], "  333  ");
			strcat(buf[1], "33   33");
			strcat(buf[2], "3     3");
			strcat(buf[3], "     33");
			strcat(buf[4], "   33  ");
			strcat(buf[5], "     33");
			strcat(buf[6], "3     3");
			strcat(buf[7], "33   33");
			strcat(buf[8], "  333  ");
			break;
		case '4':
			strcat(buf[0], "    4  ");
			strcat(buf[1], "   44  ");
			strcat(buf[2], "  4 4  ");
			strcat(buf[3], " 4  4  ");
			strcat(buf[4], "4444444");
			strcat(buf[5], "    4  ");
			strcat(buf[6], "    4  ");
			strcat(buf[7], "    4  ");
			strcat(buf[8], "    4  ");
			break;
		case '5':
			strcat(buf[0], "5555555");
			strcat(buf[1], "5      ");
			strcat(buf[2], "5      ");
			strcat(buf[3], "5      ");
			strcat(buf[4], "55555  ");
			strcat(buf[5], "     55");
			strcat(buf[6], "5     5");
			strcat(buf[7], "55   55");
			strcat(buf[8], "  555  ");
			break;
		case '6':
			strcat(buf[0], "  666  ");
			strcat(buf[1], "66   6 ");
			strcat(buf[2], "6     6");
			strcat(buf[3], "6      ");
			strcat(buf[4], "666666 ");
			strcat(buf[5], "6    66");
			strcat(buf[6], "6     6");
			strcat(buf[7], "66   66");
			strcat(buf[8], "  666  ");
			break;
		case '7':
			strcat(buf[0], "7777777");
			strcat(buf[1], "      7");
			strcat(buf[2], "      7");
			strcat(buf[3], "     7 ");
			strcat(buf[4], "    7  ");
			strcat(buf[5], "   7   ");
			strcat(buf[6], "  7    ");
			strcat(buf[7], " 7     ");
			strcat(buf[8], "7      ");
			break;
		case '8':
			strcat(buf[0], "  888  ");
			strcat(buf[1], "88   88");
			strcat(buf[2], "8     8");
			strcat(buf[3], "88   88");
			strcat(buf[4], "  888  ");
			strcat(buf[5], "88   88");
			strcat(buf[6], "8     8");
			strcat(buf[7], "88   88");
			strcat(buf[8], "  888  ");
			break;
		case '9':
			strcat(buf[0], "  999  ");
			strcat(buf[1], "99   99");
			strcat(buf[2], "9     9");
			strcat(buf[3], "99   99");
			strcat(buf[4], "  999 9");
			strcat(buf[5], "      9");
			strcat(buf[6], "      9");
			strcat(buf[7], "99   99");
			strcat(buf[8], "  999  ");
			break;
		case ':':
			strcat(buf[0], "       ");
			strcat(buf[1], "   :   ");
			strcat(buf[2], "   :   ");
			strcat(buf[3], "       ");
			strcat(buf[4], "       ");
			strcat(buf[5], "       ");
			strcat(buf[6], "   :   ");
			strcat(buf[7], "   :   ");
			strcat(buf[8], "       ");
			break;
		case ';':
			strcat(buf[0], "       ");
			strcat(buf[1], "   ;   ");
			strcat(buf[2], "   ;   ");
			strcat(buf[3], "       ");
			strcat(buf[4], "       ");
			strcat(buf[5], "       ");
			strcat(buf[6], "   ;   ");
			strcat(buf[7], "   ;   ");
			strcat(buf[8], "  ;    ");
			break;
		case '<':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "     <<");
			strcat(buf[3], "  <<<  ");
			strcat(buf[4], "<<     ");
			strcat(buf[5], "  <<<  ");
			strcat(buf[6], "     <<");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '=':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "       ");
			strcat(buf[3], " ===== ");
			strcat(buf[4], "       ");
			strcat(buf[5], " ===== ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '>':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], ">>     ");
			strcat(buf[3], "  >>>  ");
			strcat(buf[4], "     >>");
			strcat(buf[5], "  >>>  ");
			strcat(buf[6], ">>     ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '?':
			strcat(buf[0], "  ???  ");
			strcat(buf[1], "??   ??");
			strcat(buf[2], "?     ?");
			strcat(buf[3], "     ??");
			strcat(buf[4], "    ?  ");
			strcat(buf[5], "   ?   ");
			strcat(buf[6], "   ?   ");
			strcat(buf[7], "       ");
			strcat(buf[8], "   ?   ");
			break;
		case '@':
			strcat(buf[0], "  @@@  ");
			strcat(buf[1], "@@   @@");
			strcat(buf[2], "@     @");
			strcat(buf[3], "@  @  @");
			strcat(buf[4], "@ @ @ @");
			strcat(buf[5], "@  @@ @");
			strcat(buf[6], "@    @@");
			strcat(buf[7], "@@   @@");
			strcat(buf[8], "  @@@  ");
			break;
		case 'a':
		case 'A':
			strcat(buf[0], "   A   ");
			strcat(buf[1], "  A A  ");
			strcat(buf[2], " A   A ");
			strcat(buf[3], "A     A");
			strcat(buf[4], "AAAAAAA");
			strcat(buf[5], "A     A");
			strcat(buf[6], "A     A");
			strcat(buf[7], "A     A");
			strcat(buf[8], "A     A");
			break;
		case 'b':
		case 'B':
			strcat(buf[0], "BBBBB  ");
			strcat(buf[1], "B   BB ");
			strcat(buf[2], "B    BB");
			strcat(buf[3], "B   BB ");
			strcat(buf[4], "BBBBB  ");
			strcat(buf[5], "B   BB ");
			strcat(buf[6], "B    BB");
			strcat(buf[7], "B   BB ");
			strcat(buf[8], "BBBBB  ");
			break;
		case 'c':
		case 'C':
			strcat(buf[0], "  CCC  ");
			strcat(buf[1], " CC CC ");
			strcat(buf[2], "CC    C");
			strcat(buf[3], "C      ");
			strcat(buf[4], "C      ");
			strcat(buf[5], "C      ");
			strcat(buf[6], "CC    C");
			strcat(buf[7], " CC CC ");
			strcat(buf[8], "  CCC  ");
			break;
		case 'd':
		case 'D':
			strcat(buf[0], "DDDD   ");
			strcat(buf[1], "D  DDD ");
			strcat(buf[2], "D    DD");
			strcat(buf[3], "D     D");
			strcat(buf[4], "D     D");
			strcat(buf[5], "D     D");
			strcat(buf[6], "D    DD");
			strcat(buf[7], "D  DDD ");
			strcat(buf[8], "DDDD   ");
			break;
		case 'e':
		case 'E':
			strcat(buf[0], "EEEEEEE");
			strcat(buf[1], "E      ");
			strcat(buf[2], "E      ");
			strcat(buf[3], "E      ");
			strcat(buf[4], "EEEE   ");
			strcat(buf[5], "E      ");
			strcat(buf[6], "E      ");
			strcat(buf[7], "E      ");
			strcat(buf[8], "EEEEEEE");
			break;
		case 'f':
		case 'F':
			strcat(buf[0], "FFFFFFF");
			strcat(buf[1], "F      ");
			strcat(buf[2], "F      ");
			strcat(buf[3], "F      ");
			strcat(buf[4], "FFFF   ");
			strcat(buf[5], "F      ");
			strcat(buf[6], "F      ");
			strcat(buf[7], "F      ");
			strcat(buf[8], "F      ");
			break;
		case 'g':
		case 'G':
			strcat(buf[0], "  GGGGG");
			strcat(buf[1], " GG    ");
			strcat(buf[2], "GG     ");
			strcat(buf[3], "G      ");
			strcat(buf[4], "G      ");
			strcat(buf[5], "G  GGGG");
			strcat(buf[6], "GG    G");
			strcat(buf[7], " GG  GG");
			strcat(buf[8], "  GGGG ");
			break;
		case 'h':
		case 'H':
			strcat(buf[0], "H     H");
			strcat(buf[1], "H     H");
			strcat(buf[2], "H     H");
			strcat(buf[3], "H     H");
			strcat(buf[4], "HHHHHHH");
			strcat(buf[5], "H     H");
			strcat(buf[6], "H     H");
			strcat(buf[7], "H     H");
			strcat(buf[8], "H     H");
			break;
		case 'i':
		case 'I':
			strcat(buf[0], "IIIIIII");
			strcat(buf[1], "   I   ");
			strcat(buf[2], "   I   ");
			strcat(buf[3], "   I   ");
			strcat(buf[4], "   I   ");
			strcat(buf[5], "   I   ");
			strcat(buf[6], "   I   ");
			strcat(buf[7], "   I   ");
			strcat(buf[8], "IIIIIII");
			break;
		case 'j':
		case 'J':
			strcat(buf[0], "JJJJJJJ");
			strcat(buf[1], "     J ");
			strcat(buf[2], "     J ");
			strcat(buf[3], "     J ");
			strcat(buf[4], "     J ");
			strcat(buf[5], "     J ");
			strcat(buf[6], "J    J ");
			strcat(buf[7], " J  JJ ");
			strcat(buf[8], "  JJJ  ");
			break;
		case 'k':
		case 'K':
			strcat(buf[0], "K    K ");
			strcat(buf[1], "K   K  ");
			strcat(buf[2], "K  K   ");
			strcat(buf[3], "K K    ");
			strcat(buf[4], "KK     ");
			strcat(buf[5], "K K    ");
			strcat(buf[6], "K  K   ");
			strcat(buf[7], "K   K  ");
			strcat(buf[8], "K    K ");
			break;
		case 'l':
		case 'L':
			strcat(buf[0], "L      ");
			strcat(buf[1], "L      ");
			strcat(buf[2], "L      ");
			strcat(buf[3], "L      ");
			strcat(buf[4], "L      ");
			strcat(buf[5], "L      ");
			strcat(buf[6], "L      ");
			strcat(buf[7], "L      ");
			strcat(buf[8], "LLLLLLL");
			break;
		case 'm':
		case 'M':
			strcat(buf[0], "M     M");
			strcat(buf[1], "MM   MM");
			strcat(buf[2], "M M M M");
			strcat(buf[3], "M  M  M");
			strcat(buf[4], "M     M");
			strcat(buf[5], "M     M");
			strcat(buf[6], "M     M");
			strcat(buf[7], "M     M");
			strcat(buf[8], "M     M");
			break;
		case 'n':
		case 'N':
			strcat(buf[0], "N     N");
			strcat(buf[1], "NN    N");
			strcat(buf[2], "N N   N");
			strcat(buf[3], "N N   N");
			strcat(buf[4], "N  N  N");
			strcat(buf[5], "N   N N");
			strcat(buf[6], "N   N N");
			strcat(buf[7], "N    NN");
			strcat(buf[8], "N     N");
			break;
		case 'o':
		case 'O':
			strcat(buf[0], "  OOO  ");
			strcat(buf[1], " O   O ");
			strcat(buf[2], "O     O");
			strcat(buf[3], "O     O");
			strcat(buf[4], "O     O");
			strcat(buf[5], "O     O");
			strcat(buf[6], "O     O");
			strcat(buf[7], " O   O ");
			strcat(buf[8], "  OOO  ");
			break;
		case 'p':
		case 'P':
			strcat(buf[0], "PPPP   ");
			strcat(buf[1], "P   PP ");
			strcat(buf[2], "P    PP");
			strcat(buf[3], "P   PP ");
			strcat(buf[4], "PPPP   ");
			strcat(buf[5], "P      ");
			strcat(buf[6], "P      ");
			strcat(buf[7], "P      ");
			strcat(buf[8], "P      ");
			break;
		case 'q':
		case 'Q':
			strcat(buf[0], "  QQQ  ");
			strcat(buf[1], " Q   Q ");
			strcat(buf[2], "Q     Q");
			strcat(buf[3], "Q     Q");
			strcat(buf[4], "Q     Q");
			strcat(buf[5], "Q     Q");
			strcat(buf[6], "Q   Q Q");
			strcat(buf[7], " Q   Q ");
			strcat(buf[8], "  QQQ Q");
			break;
		case 'r':
		case 'R':
			strcat(buf[0], "RRRR   ");
			strcat(buf[1], "R   RR ");
			strcat(buf[2], "R    RR");
			strcat(buf[3], "R   RR ");
			strcat(buf[4], "RRRR   ");
			strcat(buf[5], "R RR   ");
			strcat(buf[6], "R   R  ");
			strcat(buf[7], "R    R ");
			strcat(buf[8], "R     R");
			break;
		case 's':
		case 'S':
			strcat(buf[0], "  SSS  ");
			strcat(buf[1], "SS   SS");
			strcat(buf[2], "S      ");
			strcat(buf[3], "SS     ");
			strcat(buf[4], "  SSS  ");
			strcat(buf[5], "     SS");
			strcat(buf[6], "      S");
			strcat(buf[7], "SS   SS");
			strcat(buf[8], "  SSS  ");
			break;
		case 't':
		case 'T':
			strcat(buf[0], "TTTTTTT");
			strcat(buf[1], "   T   ");
			strcat(buf[2], "   T   ");
			strcat(buf[3], "   T   ");
			strcat(buf[4], "   T   ");
			strcat(buf[5], "   T   ");
			strcat(buf[6], "   T   ");
			strcat(buf[7], "   T   ");
			strcat(buf[8], "   T   ");
			break;
		case 'u':
		case 'U':
			strcat(buf[0], "U     U");
			strcat(buf[1], "U     U");
			strcat(buf[2], "U     U");
			strcat(buf[3], "U     U");
			strcat(buf[4], "U     U");
			strcat(buf[5], "U     U");
			strcat(buf[6], "U     U");
			strcat(buf[7], " U   U ");
			strcat(buf[8], "  UUU  ");
			break;
		case 'v':
		case 'V':
			strcat(buf[0], "V     V");
			strcat(buf[1], "V     V");
			strcat(buf[2], "V     V");
			strcat(buf[3], " V   V ");
			strcat(buf[4], " V   V ");
			strcat(buf[5], " V   V ");
			strcat(buf[6], "  V V  ");
			strcat(buf[7], "  VVV  ");
			strcat(buf[8], "   V   ");
			break;
		case 'w':
		case 'W':
			strcat(buf[0], "W     W");
			strcat(buf[1], "W     W");
			strcat(buf[2], "W     W");
			strcat(buf[3], "W     W");
			strcat(buf[4], "W     W");
			strcat(buf[5], "W  W  W");
			strcat(buf[6], "W  W  W");
			strcat(buf[7], " W W W ");
			strcat(buf[8], "  W W  ");
			break;
		case 'x':
		case 'X':
			strcat(buf[0], "X     X");
			strcat(buf[1], "X     X");
			strcat(buf[2], " X   X ");
			strcat(buf[3], "  X X  ");
			strcat(buf[4], "   X   ");
			strcat(buf[5], "  X X  ");
			strcat(buf[6], " X   X ");
			strcat(buf[7], "X     X");
			strcat(buf[8], "X     X");
			break;
		case 'y':
		case 'Y':
			strcat(buf[0], "Y     Y");
			strcat(buf[1], " Y   Y ");
			strcat(buf[2], "  Y Y  ");
			strcat(buf[3], "   Y   ");
			strcat(buf[4], "   Y   ");
			strcat(buf[5], "   Y   ");
			strcat(buf[6], "   Y   ");
			strcat(buf[7], "   Y   ");
			strcat(buf[8], "   Y   ");
			break;
		case 'z':
		case 'Z':
			strcat(buf[0], "ZZZZZZZ");
			strcat(buf[1], "      Z");
			strcat(buf[2], "     Z ");
			strcat(buf[3], "    Z  ");
			strcat(buf[4], "   Z   ");
			strcat(buf[5], "  Z    ");
			strcat(buf[6], " Z     ");
			strcat(buf[7], "Z      ");
			strcat(buf[8], "ZZZZZZZ");
			break;
		case '[':
			strcat(buf[0], " [[[[[ ");
			strcat(buf[1], " [     ");
			strcat(buf[2], " [     ");
			strcat(buf[3], " [     ");
			strcat(buf[4], " [     ");
			strcat(buf[5], " [     ");
			strcat(buf[6], " [     ");
			strcat(buf[7], " [     ");
			strcat(buf[8], " [[[[[ ");
			break;
		case '\\':
			strcat(buf[0], "       ");
			strcat(buf[1], "\\      ");
			strcat(buf[2], " \\     ");
			strcat(buf[3], "  \\    ");
			strcat(buf[4], "   \\   ");
			strcat(buf[5], "    \\  ");
			strcat(buf[6], "     \\ ");
			strcat(buf[7], "      \\");
			strcat(buf[8], "       ");
			break;
		case ']':
			strcat(buf[0], " ]]]]] ");
			strcat(buf[1], "     ] ");
			strcat(buf[2], "     ] ");
			strcat(buf[3], "     ] ");
			strcat(buf[4], "     ] ");
			strcat(buf[5], "     ] ");
			strcat(buf[6], "     ] ");
			strcat(buf[7], "     ] ");
			strcat(buf[8], " ]]]]] ");
			break;
		case '^':
			strcat(buf[0], "   ^   ");
			strcat(buf[1], "  ^ ^  ");
			strcat(buf[2], " ^   ^ ");
			strcat(buf[3], "       ");
			strcat(buf[4], "       ");
			strcat(buf[5], "       ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		case '_':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "       ");
			strcat(buf[3], "       ");
			strcat(buf[4], "       ");
			strcat(buf[5], "       ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "_______");
			break;
		case '{':
			strcat(buf[0], "   {{{ ");
			strcat(buf[1], "   {   ");
			strcat(buf[2], "   {   ");
			strcat(buf[3], "   {   ");
			strcat(buf[4], " {{    ");
			strcat(buf[5], "   {   ");
			strcat(buf[6], "   {   ");
			strcat(buf[7], "   {   ");
			strcat(buf[8], "   {{{ ");
			break;
		case '|':
			strcat(buf[0], "   |   ");
			strcat(buf[1], "   |   ");
			strcat(buf[2], "   |   ");
			strcat(buf[3], "   |   ");
			strcat(buf[4], "   |   ");
			strcat(buf[5], "   |   ");
			strcat(buf[6], "   |   ");
			strcat(buf[7], "   |   ");
			strcat(buf[8], "   |   ");
			break;
		case '}':
			strcat(buf[0], " }}}   ");
			strcat(buf[1], "   }   ");
			strcat(buf[2], "   }   ");
			strcat(buf[3], "   }   ");
			strcat(buf[4], "    }} ");
			strcat(buf[5], "   }   ");
			strcat(buf[6], "   }   ");
			strcat(buf[7], "   }   ");
			strcat(buf[8], " }}}   ");
			break;
		case '~':
			strcat(buf[0], "       ");
			strcat(buf[1], "       ");
			strcat(buf[2], "       ");
			strcat(buf[3], " ~~    ");
			strcat(buf[4], "~  ~  ~");
			strcat(buf[5], "    ~~ ");
			strcat(buf[6], "       ");
			strcat(buf[7], "       ");
			strcat(buf[8], "       ");
			break;
		default:
			strcat(buf[0], "???????");
			strcat(buf[1], "?U////?");
			strcat(buf[2], "?N////?");
			strcat(buf[3], "?K////?");
			strcat(buf[4], "?N////?");
			strcat(buf[5], "?O////?");
			strcat(buf[6], "?W////?");
			strcat(buf[7], "?NCHAR?");
			strcat(buf[8], "???????");
			break;
	} // END switch (newletter)
} // END addletter()

// atac.c -- ASCII to ASCII Converter
// Copyright 2007, 2008 - Kenneth Finnegan.
