#include "ConfigFile.h"
/*
  * Copyright (c) 2007, Carnegie Mellon University
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *     * Redistributions of source code must retain the above copyright
  *       notice, this list of conditions and the following disclaimer.
  *     * Redistributions in binary form must reproduce the above copyright
  *       notice, this list of conditions and the following disclaimer in the
  *       documentation and/or other materials provided with the distribution.
  *     * Neither the name of Carnegie Mellon University, nor the
  *       names of its contributors may be used to endorse or promote products
  *       derived from this software without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND ANY
  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR ANY
  * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ConfigFile.h"
#include <iostream>

#define OPT_INT 0
#define OPT_BOOL 1
#define OPT_FLOAT 2
#define OPT_DOUBLE 3
#define OPT_STR 4
//#define OPT_CSTR 5
#define OPT_UINT 6

#define MAX_FILE_LEN 4096

ConfigFile::ConfigFile(): suppressWarnings_(0)
{
    strcpy(stoppingString, "**EOF");
}

// convert string to uppercase
void ConfigFile::upperCase(char * s)
{
    char diff = 'A' - 'a';
    for(unsigned int i=0; i<strlen(s); i++)
    {
        if ((s[i] >= 'a') && (s[i] <= 'z'))
            s[i] += diff;
    }
}

void ConfigFile::removeTrailingCharacters(char * s, char ch)
{
    // remove trailing "ch"s
    char * pos = s;
    while( *pos != '\0' )
        pos++;

    // now pos points to '\0'
    pos--;
    while ((pos != s - 1) && (*pos == ch))
    {
        *pos = '\0';
        pos--;
    }
}

int ConfigFile::getTypeSize(int type)
{
    switch(type)
    {
        case OPT_INT:
            return sizeof(int);
            break;

        case OPT_BOOL:
            return sizeof(bool);
            break;

        case OPT_FLOAT:
            return sizeof(float);
            break;

        case OPT_DOUBLE:
            return sizeof(double);
            break;

        default:
            printf("Error: invalid type requested (1)\n");
            return -1;
            break;
    }
}

// returns the printf format specifier string corresponding to a particular option type
void ConfigFile::getTypeFormatSpecifier(int type, char * fsp)
{
    switch(type)
    {
        case OPT_INT:
            strcpy(fsp,"%d");
            fsp[2] = 0;
            break;

        case OPT_BOOL:
            strcpy(fsp,"%s");
            fsp[2] = 0;
            break;

        case OPT_FLOAT:
            strcpy(fsp,"%f");
            fsp[2] = 0;
            break;

        case OPT_DOUBLE:
            strcpy(fsp,"%lf");
            fsp[3] = 0;
            break;

        case OPT_STR:
            strcpy(fsp,"%s");
            fsp[2] = 0;
            break;

        case OPT_UINT:
            strcpy(fsp,"%u");
            fsp[2] = 0;
            break;
        default:
            printf("Error: invalid type requested (1)\n");
    }
}

ConfigFile::~ConfigFile()
{
}

// finds a particular option name among all specified options
int ConfigFile::seekOption(const char * optionName)
{
    int slen = (int)(strlen(optionName));
    char * upperOptionName = (char*) malloc (sizeof(char) * (slen + 1));
    memcpy(upperOptionName, optionName, sizeof(char) * (slen + 1));

    upperCase(upperOptionName);
    for(unsigned int i=0; i<optionNames.size(); i++)
    {
        if (strcmp(upperOptionName,optionNames[i].c_str()) == 0)
        {
            free(upperOptionName);
            return (int)i;
        }
    }
    free(upperOptionName);
    return -1;
}

void ConfigFile::printOptions()
{
    for(unsigned int i=0; i<optionNames.size(); i++)
    {
        switch(optionTypes[i])
        {
            case OPT_INT:
                printf("%s: %d\n",optionNames[i].c_str(), *(int*)(destLocations[i]));
                break;

            case OPT_BOOL:
                printf("%s: %d\n",optionNames[i].c_str(), *(bool*)(destLocations[i]));
                break;

            case OPT_FLOAT:
                printf("%s: %G\n",optionNames[i].c_str(), *(float*)(destLocations[i]));
                break;

            case OPT_DOUBLE:
                printf("%s: %G\n",optionNames[i].c_str(), *(double*)(destLocations[i]));
                break;

            case OPT_STR:
                printf("%s: %s\n",optionNames[i].c_str(), (char*)(destLocations[i]));
                break;
            case OPT_UINT:
                printf("%s: %u\n",optionNames[i].c_str(), *(unsigned int*)(destLocations[i]));
                break;
            default:
                printf("Error: invalid type requested (1)\n");
        }

    }

}

// a generic routine to add a new option entry to the list of all options
template<class T>
int ConfigFile::addOptionHelper(const char * optionName, T * destLocation)
{
    if (seekOption(optionName) != -1)
    {
        if (!suppressWarnings_)
            printf("Warning: option %s already exists. Ignoring request to re-add it.\n",optionName);
        return 1;
    }

    std::string optionName_(optionName);

    // convert to uppercase
    for(unsigned int i=0; i< optionName_.size(); i++)
        optionName_[i] = toupper(optionName_[i]);

    optionNames.push_back(optionName_);

    destLocations.push_back((void*)destLocation);

    optionSet.push_back(false);

    return 0;
}

int ConfigFile::addOption(const char * optionName, int * destLocation)
{
    int code;
    if ((code = addOptionHelper(optionName, destLocation)) != 0)
        return code;

    optionTypes.push_back(OPT_INT);

    return 0;
}

int ConfigFile::addOption(const char * optionName, bool * destLocation)
{
    int code;
    if ((code = addOptionHelper(optionName,destLocation)) != 0)
        return code;

    optionTypes.push_back(OPT_BOOL);

    return 0;
}

int ConfigFile::addOption(const char * optionName, double * destLocation)
{
    int code;
    if ((code = addOptionHelper(optionName,destLocation)) != 0)
        return code;

    optionTypes.push_back(OPT_DOUBLE);

    return 0;
}

int ConfigFile::addOption(const char * optionName, float * destLocation)
{
    int code;
    if ((code = addOptionHelper(optionName,destLocation)) != 0)
        return code;

    optionTypes.push_back(OPT_FLOAT);

    return 0;
}

int ConfigFile::addOption(const char * optionName, char * destLocation)
{
    int code;
    if ((code = addOptionHelper(optionName,destLocation)) != 0)
        return code;
//
//    optionTypes.push_back(OPT_STR);
    optionTypes.push_back(OPT_STR);
    return 0;
}

int ConfigFile::addOption(const char * optionName, unsigned int *destLocation) {
    int code;
    if ((code = addOptionHelper(optionName,destLocation)) != 0)
        return code;

    optionTypes.push_back(OPT_UINT);

    return 0;
}

template<class T>
int ConfigFile::addOptionOptional(const char * optionName, T * destLocation, T defaultValue)
{
    int code = addOption(optionName,destLocation);
    *destLocation = defaultValue;
    optionSet[optionSet.size()-1] = true;
    return code;
}

int ConfigFile::addOptionOptional(const char * optionName, char * destLocation, const char * defaultValue)
{
    int code = addOption(optionName,destLocation);
    // must use memmove because strings may overlap
    memmove(destLocation, defaultValue, strlen(defaultValue) + 1);
    optionSet[optionSet.size()-1] = true;
    return code;
}

int ConfigFile::parseOptions(const char * filename, int verbose,int format)
{
    FILE * fin = fopen(filename,"r");
    int code;
    if (!fin)
    {
        printf("Error: could not open option file %s\n",filename);
        return 1;
    }

    switch(format){
        case TXT_FORMAT : code = parseOptionsTxt(fin,verbose);break;
        case JSON_FORMAT: code = parseOptionsJson(fin,verbose);break;
        default:    fprintf(stderr,"Unrecognized config file format\n");code = -1;
    }

    fclose(fin);
    return code;
}

int ConfigFile::parseOptionsTxt(FILE * fin, int verbose)
{
    int count = 0;
    char line[4096];
    while (fgets(line,4096,fin) != NULL)
    {
        count++;

        removeTrailingCharacters(line,'\n');
        removeTrailingCharacters(line,' ');

        if (strcmp(line, stoppingString) == 0)
            break;

        // ignore blank lines and comments
        if ((line[0] == '#') || (line[0] == '\0'))
            continue;

        if (line[0] != '*')
        {
            if (verbose)
                printf("Error: invalid line %d: %s\n",count,line);
            return 1;
        }

        int index = seekOption(&line[1]);
        //printf("Read entry: %s . Option index: %d .\n", &line[1], index);
        if (index == -1)
        {
            if ((verbose) && (!suppressWarnings_))
                printf("Warning: unknown option on line %d: %s\n",count,&line[1]);

            // eat next line
            do
            {
                if (fgets(line,4096,fin) == NULL)
                {
                    if (verbose)
                        printf("Error: EOF reached without specifying option value.\n");
                    return 1;
                }
                count++;
            }
            while (line[0] == '#'); // ignore comments

            continue;
        }

        // parse next line to get the data
        char dataEntry[4096];
        do
        {
            if (fgets(dataEntry,4096,fin) == NULL)
            {
                if (verbose)
                    printf("Error: EOF reached without specifying option value.\n");
                return 1;
            }
            count++;
        }
        while (dataEntry[0] == '#'); // ignore comments

        char typeFormatSpecifier[4];
        getTypeFormatSpecifier(optionTypes[index],typeFormatSpecifier);

        // remove any trailing line feed and carriage return
        if (dataEntry[strlen(dataEntry)-1] == 10)
            dataEntry[strlen(dataEntry)-1] = 0;
        if (dataEntry[strlen(dataEntry)-1] == 13)
            dataEntry[strlen(dataEntry)-1] = 0;

        if (optionTypes[index] != OPT_STR)
        {
            char buffer[4096];
            if (sscanf(dataEntry,typeFormatSpecifier,buffer) == 0)
            {
                if (verbose)
                    printf("Error: invalid dataline for option %s: %s\n", optionNames[index].c_str(), dataEntry);
                return 1;
            }

            // convert from string to true/false
            if (optionTypes[index] == OPT_BOOL)
            {
                //printf("Option type: boolean.\n");
                if (strncmp(buffer,"true",4) == 0)
                {
                    bool * target = (bool*) buffer;
                    *target = true;
                }
                else
                if (strncmp(buffer,"false",5) == 0)
                {
                    bool * target = (bool*) buffer;
                    *target = false;
                }
                else
                {
                    bool * target = (bool*) buffer;
                    *target = true;
                    if (verbose)
                        printf("Error: invalid boolean specification: line %d: %s\n",count,dataEntry);
                    return 1;
                }
            }
            memcpy(destLocations[index], buffer, getTypeSize(optionTypes[index]));
        }
        else
        {
            // this is a string option
            strcpy((char*)destLocations[index], dataEntry);
        }

        optionSet[index] = true;
    }

    for(unsigned int i=0; i<optionNames.size(); i++)
    {
        if(!optionSet[i])
        {
            if (verbose)
                printf("Error: option %s didn't have an entry in the config file.\n",optionNames[i].c_str());
            return 1;
        }
    }

    return 0;
}


int ConfigFile::parseOptionsJson(FILE *fin, int verbose) {
    int code = 0;
    char buffer[MAX_FILE_LEN];
    unsigned int count = 0;
    count = fread(buffer,sizeof(char),MAX_FILE_LEN,fin);

    Json::Reader reader;
    Json::Value root;

    std::string document(buffer);

    if(reader.parse(document,root))
        code = parseNode(root,root);
    else {
        fprintf(stderr, "Failed parsing Json file\n");
        return 1;
    }

    for(unsigned int i=0; i<optionNames.size(); i++)
    {
        if(!optionSet[i])
        {
            if (verbose)
                printf("Error: option %s didn't have an entry in the config file.\n",optionNames[i].c_str());
            return 1;
        }
    }

    return code;
}

int ConfigFile::parseNode(const Json::Value &node,const Json::Value &key) {
    int code = 0;
    if(node.size() > 0){
        for(Json::Value::const_iterator iter = node.begin();iter != node.end();++iter){
            code = parseNode(*iter,iter.key());
            if(code != 0) {
                fprintf(stderr, "Failed parsing node[%s]\n",iter.key().asCString());
                break;
            }
        }
    }
//    if this is a parameter
    if(node.size() == 0){
//        if(node == parent){
//            fprintf(stderr,"Empty Json file\n");
//            return 1;
//        }


        int key_index = seekOption(key.asCString());
        if(key_index == -1) {
            code = 1;
            fprintf(stderr,"Failed parsing option (%s)\n",key.asCString());
        }
        else{
            int optionType = optionTypes[key_index];
            void *dest = destLocations[key_index];
            switch (optionType){
                case OPT_INT :  *(int*)dest = node.asInt();break;
                case OPT_BOOL : *(bool*)dest = node.asBool();break;
                case OPT_DOUBLE :   *(double*)dest = node.asDouble();break;
                case OPT_FLOAT  :   *(float*)dest = node.asFloat();break;
                case OPT_STR    :   strcpy((char*)dest,node.asCString());break;
//                case OPT_CSTR   :   strcpy((char*)dest,node.asCString());break;
                case OPT_UINT   :   *(unsigned int*)dest = node.asUInt();break;
            }

            optionSet[key_index] = true;
        }
    }

    return code;
}


void ConfigFile::setStoppingString(const char * stoppingString_)
{
    if (strlen(stoppingString_) >= 32)
    {
        printf("Warning: proposed stopping string %s is too long. Stopping string not modifed.\n", stoppingString_);
        return;
    }

    strcpy(stoppingString, stoppingString_);
}

