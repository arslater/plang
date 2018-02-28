//
// Created by anita on 2/21/18.
//

#ifndef PROJ1_PARSE_H
#define PROJ1_PARSE_H

#include<stdio.h>
#include<stdlib.h>

void parseRegex(char *, char **);

typedef struct elementsStruct{
    char * literal;
    enum symbol
    {
        brackets,
        match,
        plus,
        splat
    } operator;

    char *inBraces;
    int lineNum;
} elementsStruct;



#endif //PROJ1_PARSE_H
//test regex like a*b*c* returns empty string