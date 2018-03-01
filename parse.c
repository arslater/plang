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
    int m = 0;
    int stash = 0;
    int res_ind = 0;
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
        while (file[j][i] != NULL && file[j][m] != NULL)
        {
            stash = i;
            printf("\ncomaparing regex[%d]:%c | file[%d]:%c...",k,regex[k],i,file[j][i]);
            if(regex[k+1] == '+' || regex[k] == '+' || regex[k]=='*' || regex[k+1] == '*'|| regex[k] == '[' || regex[k] == '\\')
            {
                // special charahcter
                printf("Special charahcter '%c' detected ", regex[k]);

                // mathces zero
                if(regex[k+1] == '*') {
                    printf(" throwing in %c.", file[j][i]);

                    printf("\t#1# %c",file[j][i]);
                    //printf(" dem variables are %c and %c ", regex[k], file[j][i]);
                    if(regex[k]!=file[j][i])
                    {
                        printf("&&&&");
                        k ++;
                        i++;
                        match_end++;
                    }
                    match_end--;
                    if(regex_length == 1) {
                        match_end = 0;
                        match_start =0;
                        break;
                    }
                    printf(" dem variables are %c and %c ", regex[k], file[j][i]);
                }
                //matches one & more
                if(regex[k+1] == '+' || regex[k+1] == '*')
                {
                    printf("**");
                    while( regex[k] == file[j][i])
                    {
                        if((regex[k+2] == file[j][i])){
                            printf("$$$$$$$");
                            if(file[j][i+1] != file[j][stash])
                                break;
                        }
                        printf("\t#^^# %c",file[j][i]);
                        printf("\ncomaparing regex[%d]:%c | file[%d]:%c...",k,regex[k],i,file[j][i]);
                        match_end++;
                        i++;
                    }
                    //i--
                    // match_end--;
                    k++;
                }
                else if( regex[k] == '[')
                {
                    while(regex[k] != ']')
                    {
                        if(regex[k] == file[j][i]) {
                            printf("#%%!!# %c", file[j][i]);
                            match_end++;
                        }
                        k++;
                    }
                    k++;
                    i++;
                }
                else
                {
                    printf("\t#&# %c",file[j][i]);
                    if(regex[k] == '*' || regex[k] == '+' || regex[k] == '\\')
                    {
                        k++;
                       // i=stash;
                    }
                   else
                    {
                       i++;
                       match_end++;
                    }

                }
            }
            else if(regex[k] == file[j][i])
            {
                // literal match
                printf("literal match");
                if(match_start == -1|| match_end == -1)
                {
                    // grabbing first occurrence
                    match_start = i;
                    match_end   = i;
                }
                printf("\t\t\t\t\t#@# %c",file[j][i]);
                k++;
                i++;
                match_end++;
            }
            else
            {
                //other
                printf("fail");
                memset(literal,0,sizeof(literal));
                match_end   = -1;
                match_start = -1;
                if (k == 0)
                    i++;
                else
                    i = stash-1;
                k = 0;
                m++;
            }
            if(k == regex_length+1&& match_end != -1 )
            {
                printf("Match found from pos %d to pos %d on line %d\n", match_start, match_end, j);
                break;
            }
            printf(" Current match: start: %d, end%d",match_start,match_end);
        }
        if(match_end == -1)
            printf("ULTRA FAIL\n");
        printf("Final values: start:%d end%d total:%d length:%d Result is \n", match_start, match_end, match_end-match_start, regex_length);
        for(i=match_start;i<match_end+1;i++)
            printf("%c", file[j][i]);
        match_start = -1;
        match_end = -1;
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

