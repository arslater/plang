//
// Created by anita on 2/21/18.
//
//@formatter:off

#include <string.h>
#include "parse.h"

void parseRegex(char * regex, char ** file) {
    printf("Parsing '%s'\n", regex);
    int i = 0;
    int j = 0;
    int k = 0;
    int match_start = -1;
    int match_end   = -1;
    int regex_length = 0;
    char look_ahead=0;
    char *literal = (char *) malloc(sizeof(char) * 100);
    ///////////////////////////////////////
    // Objective 2: try to get the pieces parsed

    elementsStruct *elements = malloc(sizeof(elementsStruct));
    int rep = 0;
    for(i=0;regex[i]!=0;i++)
        regex_length = i;
    i=0;
    //////////////////////////
    // Is this parsing????????
    while(file[j+1] != NULL)
    {
        while (file[j][i] != NULL)
        {
            printf("regex[%d]:%c | file[%d]:%c...", k,regex[k],i,file[j][i]);

            if (regex[k] == 0)
            {
               if((match_end-match_start)>=regex_length) {
                    printf("**********VALID MATCH FOUND********\n");
                   printf("**********VALID MATCH FOUND from pos %d - pos %d ********\n", match_start, match_end);
                    break;
                }
                i=0;
            }

            if(regex[k] == file[j][i])
            {

                if(match_start==-1 || match_end == -1) {
                    match_start = i;
                    match_end = i;
                }
                else
                    match_end++;
                printf("check! Match at char %d\n", match_start);
            }
            else
            {
                if (regex[k] == '+') {
                    printf("regular expression '%c' detected. Checking for valid pattern\n", regex[k]);
                    while (regex[k - 1] == file[j][i]) {
                        printf("The charachter '%c' MATCHES the Line charachter: %c\n", regex[k - 1], file[j][i]);
                        rep = 1;
                        i++;
                        match_end++;
                    }
                    printf("The charater '%c' MISMATCHES the Line character '%c'\n", regex[k - 1], file[j][i]);
                    if ((match_end - match_start) >= regex_length) {
                        printf("**********VALID MATCH FOUND from pos %d - pos %d ********\n", match_start, match_end);
                        break;
                    }
                    k = 0;
                    //printf("On line")
                }
                else
                {
                    printf("fail\n");
                    k = -1;
                }

            }
            k++;
            i++;
            //printf("

            //else
             //   printf("k:%d\n",k);
        }
        match_start = 0;
        match_end = 0;
        j++;
        printf("++++++++++++++++LINE %d++++++++++++++++++\n", j);
        i = 0;
        k = 0;
        (elements -> lineNum)++;
    }
}
void doSplat(char *line, elementsStruct* sp)
{
    printf("On the %d line there is...", sp -> lineNum);
    printf("Literal string '%s' followed by a splat\n", sp -> literal);
}
    /*
     * Okay, so the idea is, that the file gets parsed, line by line.
     * The goal of this is to use a state machine that is triggered by the presence
     * of the regular expressions. For example if given the follownig regex:
     *  abc*[123]
     *  The first thing that will be done is decide if the current character is a
     *  literal or a symbol( something that triggers a state) if it's a literal, save
     *  the literal in the string, literal, that is denoted in the struct.If the character
     *  is a special character, then, using the literal string, see how many it matches
     *  (( the matches are determined by the symbol. Then, look at the file( that is saved
     *  as an array of strings to see what matches. Going character by character, saving ( in
     *  an array, startOccurence, the start point and in another array, the endpoint, end
     *  occurrence. Once that is done for the entire line, the string is then re-examined
     *  using a loop that grabs the string in between the two indexes. Finaly, that string is
     *  then printed out and the loop continues for the next line until completion.
     *      1. Look at input file string
     *      2. Determine if the regex char is special or a literal
     *          a) literal? Add to 'literal' string, goto 2
     *          b) special?
     *              1) Is the present symbol ( from the last iter) special?
     *                  a) no: continue to 3
     *                  b) yes: continue to 3 with the string being the same
     *                     ** the only case where this is relevant is when you have [1234]*
     *                     or [1234]+ . So you can see if there are 0 or more of the characters
     *                     in the range or 1 or more of the charachtes in the range. --edgecase--
     *      3. Determine the character
     *          a) splat:
     *              1. Get literal String
     *              2. Get the string of first line
     *              3. Compare the literal string to character of line
     *              4. Does the line string equal ...
     *                  a) the literal string exactly (goto)
     *                  b) the literal string plus one or more of the last char
     *                  c) the literal string minus the last char
     *                  c) none of these
     *                 Repeat until end of line.
     *           b) plus:
     *               E. Is this an edge case?
     *               1. Get the literal string
     *               2. Get the string of the first line
     *               3. Compare the literal string to the string of line
     *               4. Does the line string equal...
     *                  a) the literal string exactly?
     *                  b) The literal string plus one or more of the last char
     *                  c) none of these
     *                 Repeat until the end of the line.
     *           c) braces
     *              1. Is this a '['
     *                  a) yes: goto 2
     *                  b) no: this is a ']' : goto 3c2
     *              2. Get the literal string ( stuff in brackets)
     *              3. Get the string of the first line
     *              4. Compare the literal string to the string of the first line
     *              5. Does the line string equal...
     *                  a) any single charachter of the literal string
     *                      1) yes: pattern found, move to next term
     *                      2) no, continue to the end of the line, comparing each
     *                         individual charachter in the input string to each literal
     *                         charachter that is within the literal string
     *
     *
     *
     */

