#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;


string removeNewlineChars( string s ) {

    int last = s.size() - 1;
    while ( last >= 0 && ( s[last] == '\n' || s[last] == '\r' ) )
        --last;
    return s.substr(0, last + 1);

}

string getVariableName( string name ) {

    if ( name.substr( 0, 9 ).compare("HOODEDMAN") == 0 && name.size() > 9 ) {
        return "std::string( (argc >= " + to_string( stoi( name.substr( 9, name.size() ) ) + 1 ) + ") ? std::string(argv[" + name.substr( 9, name.size() ) + "]) : \"no friends\" )";
    } else {
        return name;
    }

}


string constructIntermediateCPP( vector<string> lines ) {

    string cppCode = "#include <iostream> \nint main (int argc, char* argv[]) {\n\n";
    {
        for ( int i = 0; i < lines.size(); i++ ) {
            string baneBlock[3] = "";
            int baneLines = 0;
            string cppBlock = "";

            while ( i < lines.size() && removeNewlineChars( lines.at(i) ).compare("") != 0 ) {
                baneBlock[baneLines] = lines.at(i) + "\n";
                baneLines++;
                i++;
            }

            istringstream iss( baneBlock[0].substr( 0, baneBlock[0].size() ) );
            vector<string> line1_tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };

            if ( removeNewlineChars( baneBlock[1] ).compare("for you") == 0 ) {

                cppBlock += "\tstd::cout << " + getVariableName( removeNewlineChars(baneBlock[0]) ) + " << \"\\n\";\n";

            } else if ( line1_tokens.size() == 8 &&  line1_tokens.at(1).compare("refused") == 0 && line1_tokens.at(3).compare("offer") == 0 && line1_tokens.at(4).compare("in") == 0 && line1_tokens.at(5).compare("favour") == 0 && line1_tokens.at(6).compare("of") == 0 ) {
                
                cppBlock += "\tstd::string " + line1_tokens.at(0) + " = ( " + getVariableName(line1_tokens.at(2)) + ".compare(" + getVariableName(line1_tokens.at(7)) + ") == 0 ) ? " + getVariableName(removeNewlineChars(baneBlock[1])) + " : " + getVariableName(removeNewlineChars(baneBlock[2])) + ";\n";
                
            } else if ( baneBlock[1].substr(0,11).compare("it would be") == 0 ) {

                istringstream iss(baneBlock[1].substr(12,baneBlock[1].size()));
                vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

                cppBlock += "\tstd::string " + removeNewlineChars(baneBlock[0]) + " = " + getVariableName(tokens.at(0)) + " + " + getVariableName(tokens.at(1)) + ";\n";

            } else {

                cppBlock += "\tstd::string " + removeNewlineChars(baneBlock[0]) + " = \"" + getVariableName(removeNewlineChars(baneBlock[1])) + "\";\n";

            }

            cppCode += cppBlock;
        }
    }
    cppCode += "\n\treturn 0;\n}\n";

    return cppCode;

}

void compileIntermediateCPP( string name, string code ) {

    ofstream tmp;
        tmp.open("tmp.cpp");
        tmp << code;
        tmp.close();

    string gppCall = "g++ -I./ -o ./" + name.substr( 0, name.size() - 5 ) + " ./tmp.cpp";
    system( gppCall.c_str() );
    system("rm ./tmp.cpp");

}


bool showSteps = false;

int main( int argc, char* argv[] ) 
{
    if ( argc < 2 ) return 1;

    string filename = argv[1];
    {
        showSteps && cout << " |-----------|\n";
        showSteps && cout << " | src file: |\n";
        showSteps && cout << " |-----------|\n\n";
        showSteps && cout << filename + "\n";
    }


    vector<string> lines;
    {
        ifstream file( filename );
        string s;
        while ( getline(file, s) )
            lines.push_back(s);
    }

    // construct intermediateCPP
    string cppCode = constructIntermediateCPP( lines );
    {
        showSteps && cout << "\n\n |-----------|\n";
        showSteps && cout << " | src code: |\n";
        showSteps && cout << " |-----------|\n\n";
        showSteps && cout << cppCode;
    }
    
    // compile intermediateCPP
    compileIntermediateCPP(filename, cppCode);

    return 0; 
}