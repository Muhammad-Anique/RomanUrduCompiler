#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
//for future assignments leave it as it is
class parser
{
    lexer _lexer;
    vector<token> symbols;
    vector<int> symbols_address;

public:
    int tabs = 0;
    int addr = 0;
    int line = 0;
    int functionCount =0;
    int globalVarCount =0;
    int statementCount = 0;

    void write_symbol_table();
    void print_tabs();


    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();



    // void Statement_List();
    // void Decleration();
    // void Variable_Decleration();
    // void Funtion_Decleration();
    // void VD_Specifier();

/////////////////////////////////////////////
/////////////////////////////////////////////

    int countLines(){ return _lexer.lineCount(_lexer.getCurrentPointer());}
    int countStatementsInBlock(int pos, int btype);
    void countDecleration();
    void Program();
    void DeclarationList();
    void Declaration();
    void VariableDeclaration();
    void VariableAssignment();
    void FunctionDeclaration();
    void VDSpecifier();
    void TypeF();
    void TypeID();
    void ParameterList();
    void Parameter();
    void Block();
    void BlockF();
    void StatementList();
    void Statement();
    token removeNL();


    //Statement → Expression | SelectionStatement |  IterativeStatement |  ReturnStatement | VariableDeclaration | FunctionCall | IOStatement | ^
    void Expression();
    void SelectionStatement();
    void IterativeStatement();
    void ReturnStatement();
    void FunctionCall();
    void IOStatement();


   


//////////////////////////////////////////////
//////////////////////////////////////////////



    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
	//all your parser function goes here

    void T();
    void T_();
    void F();
};
#endif
