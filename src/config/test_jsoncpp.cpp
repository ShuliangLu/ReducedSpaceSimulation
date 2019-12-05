#include<iostream>

#include<fstream>
#include <string>
#include <json/json.h>

#include <cstdio>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getced
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


std::string GetCurretnWorkingDir(void) {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

bool PrintJsonTree(const Json::Value &root,unsigned short depth);
void PrintJsonValue( const Json::Value &val );
int main(int argc,char *argv[])
{
    std::ifstream fin;
    std::stringstream content;
    fin.open(argv[1],std::ios::in);
    if(!fin.is_open()) {
        char filename[FILENAME_MAX];
        std::string cur_dir = GetCurretnWorkingDir();
        sprintf(filename,"%s/%s",cur_dir.c_str(),argv[1]);
        std::cerr << "Fail opening file " << filename << std::endl;
        std::exit(-1);
    }

    std::string line;
    while(getline(fin,line)){
        content << line;
    }
    fin.close();

    Json::Reader reader;
    Json::Value root;

    if(reader.parse(content,root)){
        PrintJsonTree(root,0);
    }
    else
        std::cerr << "Error:Fail parsing Json root" << std::endl;
    return 0;
}

bool PrintJsonTree(const Json::Value &root,unsigned short depth)
{
    depth += 1;
    printf( " {type=[%d], size=%d}", root.type(), root.size() );

    if( root.size() > 0 ) {
        printf("\n");
        for( Json::Value::const_iterator itr = root.begin() ; itr != root.end() ; itr++ ) {
            // Print depth.
            for( int tab = 0 ; tab < depth; tab++) {
                printf("-");
            }
            printf(" subvalue(");
            PrintJsonValue(itr.key());
            printf(") -");
            PrintJsonTree( *itr, depth);
        }
        return true;
    } else {
        printf("->");
        PrintJsonValue(root);
        printf( "\n" );
    }
    return true;
}

void PrintJsonValue( const Json::Value &val )
{
    if( val.isString() ) {
        printf( "string(%s)", val.asString().c_str() );
    } else if( val.isBool() ) {
        printf( "bool(%d)", val.asBool() );
    } else if( val.isInt() ) {
        printf( "int(%d)", val.asInt() );
    } else if( val.isUInt() ) {
        printf( "uint(%u)", val.asUInt() );
    } else if( val.isDouble() ) {
        printf( "double(%f)", val.asDouble() );
    }
    else
    {
        printf( "unknown type=[%d]", val.type() );
    }
}