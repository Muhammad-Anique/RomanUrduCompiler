#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

void parser::write_symbol_table(){
    ofstream myfile ("symbol_table.txt");
    if (myfile.is_open())
    {
        myfile <<"ID        TYPE        ADDRESS\n";
        for(int i=0;i<symbols.size();i++)
        {
            myfile<<symbols[i].lexeme<<'\t'<<'\t'<<'\t'<<"INT"<<'\t'<<'\t'<<'\t'<<symbols_address[i]<<endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

void parser::print_tabs(){
    for(int i=0;i<tabs;i++)
    {
        cout<<'\t';
    }
}

token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if(t.tokenType == TokenType::NL)
    token t = _lexer.getNextToken();

    print_tabs();
    t.Print();  

    if (t.tokenType != expected_type)
        syntax_error();
    else {

        if(t.tokenType==TokenType::ID){
        symbols.push_back(t);
        symbols_address.push_back(addr);
        addr=addr+4;
        }

    }
    return t;
}



parser::parser(const char filename[])
{
    _lexer = lexer(filename);
    readAndPrintAllInput();
    cout<<"-------------<PARSING>---------------"<<endl<<endl;

    Program();


    while(_lexer.peek(1).tokenType == TokenType::NL)
       _lexer.getNextToken();

    if (_lexer.peek(1).tokenType != TokenType::END_OF_FILE)
    {
       syntax_error();
    }

    write_symbol_table();
   
}



void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }

}



void parser::resetPointer()
{
    _lexer.resetPointer();
}



//this function is for sample purposes only

// void parser::T()
// {
//     resetPointer();
//     cout<<"T"<<endl;
//     tabs++;
//     F();T_();
// }

// void parser::T_(){
//     print_tabs();
//     cout<<"T_"<<endl;
//     tabs++;

//     if (_lexer.peek(1).tokenType == TokenType::PLUS)
//     {
//         expect(TokenType::PLUS); F(); T_(); 
//     }
//     else{
//      ;
//     }
//     tabs--;
// }

// void parser::F(){

//     print_tabs();
//     cout<<"F"<<endl;
//     tabs++;

//     if (_lexer.peek(1).tokenType == TokenType::ID)
//     {
//         expect(TokenType::ID);
//     }
//     else if(_lexer.peek(1).tokenType == TokenType::INT)
//     {
//      expect(TokenType::INT);   
//     }
//     else{
//        ;
//     }
//     tabs--;
// }

// void parser::Statement_List(){
//     resetPointer();
//     cout<<"SL"<<endl;
//     tabs++;

//     if (_lexer.peek(1).tokenType == TokenType::KAAM || _lexer.peek(1).tokenType == TokenType::RAKHO)
//     {
//        Decleration();
//     }

//     tabs--;
// }


// void parser::Decleration(){
    
//     print_tabs();
//     cout<<"D"<<endl;
//     tabs++;
 
//     if (_lexer.peek(1).tokenType == TokenType::KAAM)
//     {
//        Funtion_Decleration();
//     }
//     else if(_lexer.peek(1).tokenType == TokenType::RAKHO){

//         Variable_Decleration();
//     }

//     tabs--;
// }

// void parser::Variable_Decleration()
// {
//     print_tabs();
//     cout<<"VD"<<endl;
//     tabs++;
 
//     if (_lexer.peek(1).tokenType == TokenType::RAKHO)
//     {
//        expect(TokenType::RAKHO);
//        expect(TokenType::ID);
//        expect(TokenType::AT); 
//         expect(TokenType::ADAD); 
//        VD_Specifier();
//     }

//     tabs--;

// }

// void parser::VD_Specifier(){

//     print_tabs();
//     cout<<"VD_S"<<endl;
//     tabs++;
 
//     if (_lexer.peek(1).tokenType == TokenType::ASSIGNOP)
//     {
//        expect(TokenType::ASSIGNOP);
//         F();T_();
//     }

//     tabs--;

// }

// void parser::Funtion_Decleration(){

// }





///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////



 void parser::countStatementsInBlock(int pos, int btype){
    cout<<"idmeodi = "<< _lexer.getStatementCount(pos,btype);
    statementCount = _lexer.getStatementCount(pos,btype);

 }

  void parser::countDecleration(){
     functionCount =  _lexer.getDecCount();
  }







///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

void parser::Program(){

    print_tabs();
    resetPointer();
    countDecleration();
    cout<<"P"<<endl;
    tabs++;
    // cout<<"token = ";
    // _lexer.peek(1).Print();
    if (_lexer.peek(1).tokenType == TokenType::KAAM || _lexer.peek(1).tokenType == TokenType::RAKHO)
    {
       DeclarationList();
    }
    tabs--;

}

void parser::DeclarationList(){

    // cout<<"functionCOunt = "<<functionCount<<endl;
    if(functionCount==1){
    Declaration();
    }
    else if(functionCount>1) {
     Declaration();DeclarationList(); 
    }
}




void parser::Declaration(){
    removeNL();
    print_tabs();
    cout<<"D"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KAAM)
    {
        FunctionDeclaration();
    }
    else if(_lexer.peek(1).tokenType == TokenType::RAKHO){
      
        VariableDeclaration();
    }

    tabs--;
    functionCount--;
    removeNL();
   
}




void parser::TypeF(){
    removeNL();
    print_tabs();
    cout<<"TypeF"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ADAD)
    {
       expect(TokenType::ADAD); 
    }
    else if(_lexer.peek(1).tokenType == TokenType::KHALI){
       expect(TokenType::ADAD); 
    }

    tabs--;
    removeNL();

}




void parser::TypeID(){

    print_tabs();
    cout<<"TypeID"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ADAD)
    {
       expect(TokenType::ADAD); 
    }

    tabs--;

}


void parser::Parameter(){
    //Parameter → id @ typeV
    removeNL();
    print_tabs();
    cout<<"P"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        expect(TokenType::AT);
        TypeID();
          
    }

    tabs--;
    removeNL();


}




void parser::ParameterList(){
    removeNL();
    //ParameterList → Parameter | Parameter `|`  ParameterList 
    print_tabs();
    cout<<"PL"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ID && _lexer.peek(4).tokenType != TokenType::PIPE)
    {
        Parameter();     
    }
    else if(_lexer.peek(4).tokenType == TokenType::PIPE){
        Parameter();
        expect(TokenType::PIPE);
        ParameterList();
    }

    tabs--;
    removeNL();

}

void parser::FunctionDeclaration(){
    removeNL();
    //FunctionDeclaration → “kaam” id “@” typeF "(" ParameterList ")" BlockF

    print_tabs();
    cout<<"FD"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KAAM)
    {
       expect(TokenType::KAAM);
       expect(TokenType::ID);
       expect(TokenType::AT);
       TypeF(); 
       expect(TokenType::LPAREN);
       ParameterList();
       expect(TokenType::RPAREN);
       BlockF();

    }

    tabs--;
    removeNL();


}




void parser::VariableDeclaration(){
    removeNL();
    print_tabs();
    cout<<"VD"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::RAKHO)
    {
       expect(TokenType::RAKHO);
       expect(TokenType::ID);
       expect(TokenType::AT); 
       TypeID(); 
       VDSpecifier();
    }

    tabs--;
    removeNL();
}

void parser::VDSpecifier(){
     removeNL();
    print_tabs();
    cout<<"VD_S"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ASSIGNOP)
    {
       expect(TokenType::ASSIGNOP);
        F();T_();
    }

    tabs--;
    removeNL();

}


void parser::Block(){
    removeNL();
    print_tabs();
    cout<<"BLOCK"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       StatementList();
       expect(TokenType::BAS); 
       expect(TokenType::KARO);
    }

    tabs--;
    removeNL();

}
void parser::BlockF(){
    removeNL();
    print_tabs();
    cout<<"BLOCKF"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       countStatementsInBlock(_lexer.getCurrentPointer()-1,1);
       StatementList();
       expect(TokenType::KAAM); 
       expect(TokenType::KHATAM);
    }

    tabs--;
    removeNL();

}




void parser::StatementList(){
    removeNL();
    print_tabs();
    cout<<"SL"<<endl;
    tabs++;
    cout<<"StatementCount = "<<statementCount<<endl;

    if(statementCount==1){
    Statement();
    }
    else if(statementCount>1) {
     Statement();StatementList();
    }

    tabs--;
    removeNL();
   
}

void parser::Statement(){
    removeNL();
    print_tabs();
    cout<<"S"<<endl;
    tabs++;


     F();T_(); 
     
    tabs--;
    statementCount--;
    removeNL();

}



void parser::T_(){
    removeNL();
    print_tabs();
    cout<<"T_"<<endl;
    tabs++;

    if (_lexer.peek(1).tokenType == TokenType::PLUS)
    {
        expect(TokenType::PLUS); F(); T_(); 
    }
    else{
     ;
    }
    tabs--;
    removeNL();
}

void parser::F(){
    removeNL();
    print_tabs();
    cout<<"F"<<endl;
    tabs++;

    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
    }
    else if(_lexer.peek(1).tokenType == TokenType::INT)
    {
     expect(TokenType::INT);   
    }
    else{
       ;
    }
    tabs--;
    removeNL();
}




 token parser::removeNL(){
    while(_lexer.peek(1).tokenType == TokenType::NL)
     _lexer.getNextToken();
 }


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////







































    // //statements-- > COLON LPAREN start RPAREN
    // if (_lexer.peek(1).tokenType == TokenType::PLUS)
    // {
    //     expect(TokenType::PLUS);
    //     if (_lexer.peek(1).tokenType == TokenType::LPAREN)
    //     {
    //         expect(TokenType::LPAREN);
    //         start();
    //         if (_lexer.peek(1).tokenType == TokenType::RPAREN)
    //         {
    //             expect(TokenType::RPAREN);
    //             return true;
    //         }
    //     }
    // }
    // return false;