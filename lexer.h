#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	NL = 1,
	INT = 2,
	SEMICOLON = 3,
	ID = 4, //Identifier
	RELOP = 5, //Relational Operator
	COMMENT = 6, //Comment
	IO = 7, //Input/Output Operator
	ASSIGNOP = 8, //Assignment Operator

	LPAREN = 9,
	RPAREN=10,
	PIPE=11,
	COLON=12,
	AT=13,
	BACKTICK=14,
	PLUS=15,
	MINUS=16,
	MULTIPLY=17,
	DIVIDE=18,
	MODOLUS=19,


	STRING =20,

	
	MARKAZI = 21,
	KAAM = 22,
	KARO = 23,
	RAKHO = 24,
	JAB = 25,
	TAK = 26,
	BAS = 27,
	AGAR = 28,
	TO = 29,
	WARNA = 30,
	PHIR = 31,
	DEKHAO = 32,
	LO = 33,
	CHALAO = 34,
	BHAIJO = 35,
	ADAD = 36,
	KHALI = 37,
	KHATAM = 38,
	WAPAS = 39,
	ERROR = 40

};



//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print_Single_Token(token t);
	void Print();
};


class lexer
{
	vector<char> stream;  //used for storing file sample_code.ol content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();//populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();//just print everything as it is present in file
	token getNextToken();//get next token
	void resetPointer();//reset pointer to start getting tokens from start
	int getCurrentPointer();//get where current pointer in tokens vector is
	void setCurrentPointer(int pos);//move current pointer to wherever
	token peek(int);//peek the next token
	int lineCount(int pos){
		int lines =0;
		for(int i=pos;i>=0;i--){
			if(tokens[i].tokenType==TokenType::NL)
			lines++;
		}
		return lines;	

	}

	int getDecCount(){
		int count =0;
		for(int i=0;i<tokens.size()-1;i++){
			if(tokens[i].tokenType==TokenType::KAAM && tokens[i+1].tokenType!=TokenType::KHATAM)
			count++;
		}
		//cout<<"Dec count = "<<count<<endl;
		return count;	
	}

	int CheckLast(int pos){
		//cout<<"AYA = "; tokens[pos].Print();

	    if( tokens[pos].tokenType==TokenType::KAAM  && tokens[pos+1].tokenType==TokenType::KHATAM){
		//cout<<"kaam  khtm khtm";
		return -1;}
		else if( tokens[pos].tokenType==TokenType::BAS && tokens[pos+1].tokenType==TokenType::KARO && tokens[pos+3].tokenType==TokenType::BAS ){
		//cout<<"bas kro khtm";
		return -1;}
		
		while(tokens[pos].tokenType!=TokenType::NL)
		pos++;


		if(tokens[pos].tokenType==TokenType::NL && (tokens[pos+1].tokenType==TokenType::BAS  && tokens[pos+2].tokenType==TokenType::KARO)){
		//cout<<"bas k";
		return 1;}
		else if(tokens[pos].tokenType==TokenType::NL && (tokens[pos+1].tokenType==TokenType::KAAM  && tokens[pos+2].tokenType==TokenType::KHATAM)){
		//cout<<"kaam khtm";
		return 1;}
	

		else{
			return 0;
		}
	}

	int getStatementCount(int pos, int bType){
		int count =0;
		//karo..........bas karo
		//cout<<"In getStatementCount"<<endl;

		cout<<"Pre";tokens[pos-1].Print();
		cout<<"This";tokens[pos].Print();
		cout<<"Next";tokens[pos+1].Print();
		//if(tokens[pos].tokenType==TokenType::NL)
		for(int i=pos+1;i<tokens.size()-1;i++){

		    //cout<<"InLoop";tokens[i].Print();
			if(tokens[i].tokenType==TokenType::BAS && tokens[i+1].tokenType==TokenType::KARO){
				return count;
			}

			else if(tokens[i].tokenType==TokenType::KAAM && tokens[i+1].tokenType==TokenType::KHATAM)
			{
				return count;
			}

			else if((tokens[i].tokenType!=TokenType::BAS  && tokens[i].tokenType!=TokenType::KAAM) && tokens[i+1].tokenType==TokenType::KARO){
				return count + 1;

			}
			
			else if(tokens[i].tokenType==TokenType::NL){
			count++;
			}
		}

		cout<<"c = "<<count<<endl;
		
		return count;	


	}



};

#endif // !_LEXER_H
