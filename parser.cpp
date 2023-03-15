#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR AT LINE  " << countLines() <<endl;;
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
    print_tabs();
    t.Print();  

    if (t.tokenType != expected_type){
       // cout<<"Mismatched Token  = ";t.Print();
        syntax_error();
    }
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



int  parser::countStatementsInBlock(int pos, int btype){
    //cout<<"Pos = "<<pos<<endl;
    //cout<<"idmeodi = "<< _lexer.getStatementCount(pos,btype);
    return _lexer.getStatementCount(pos,btype);

 }

  void parser::countDecleration(){
     functionCount =  _lexer.getDecCount();
  }







///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

void parser::Program(){
    //removeNL();
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
    else{
        syntax_error();
    }
    tabs--;
    //removeNL();

}

void parser::DeclarationList(){
    //removeNL();
    // cout<<"functionCOunt = "<<functionCount<<endl;
    if(functionCount==1){
    Declaration();
    }
    else if(functionCount>1) {
     Declaration();DeclarationList(); 
    }
    else{
        ;
    }
    //removeNL();
}




void parser::Declaration(){
    //removeNL();
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
    else
    {
        syntax_error();
    }

    tabs--;
    functionCount--;
   // removeNL();
   
}




void parser::TypeF(){
   // removeNL();
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
    else{
        syntax_error();
    }

    tabs--;
   // removeNL();

}




void parser::TypeID(){
    removeNL();
    print_tabs();
    cout<<"TypeID"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ADAD)
    {
       expect(TokenType::ADAD); 
    }
    else{
        syntax_error();
    }

    tabs--;
    //removeNL();
}


void parser::Parameter(){
    //Parameter → id @ typeV
    //removeNL();
    print_tabs();
    cout<<"P"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        expect(TokenType::AT);
        TypeID();
          
    }else{
        syntax_error();
    }

    tabs--;
  // removeNL();


}




void parser::ParameterList(){
  /// removeNL();
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
    else
    {
        syntax_error();
    }

    tabs--;
  /// removeNL();

}

void parser::FunctionDeclaration(){
   ///removeNL();
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
    else{
        syntax_error();
    }


    tabs--;
    //removeNL();


}




void parser::VariableDeclaration(){
   //removeNL();
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
    else{
        ;
    }

    tabs--;
  // removeNL();
}


void parser::VariableAssignment(){
    print_tabs();
    cout<<"VA"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::RAKHO)
    {
       expect(TokenType::RAKHO);
       expect(TokenType::ID);
       expect(TokenType::ASSIGNOP);
       Expression();
    }
    else{
        ;
    }

    tabs--;
}

void parser::VDSpecifier(){
    //removeNL();
    print_tabs();
    cout<<"VD_S"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ASSIGNOP)
    {
       expect(TokenType::ASSIGNOP);
       Expression();
    }
    else if(_lexer.peek(1).tokenType == TokenType::NL) {
         expect(TokenType::NL);
    }
    else{
        ;
    }

    tabs--;
   //removeNL();

}


void parser::Block(){
    //removeNL();
    print_tabs();
    cout<<"BLOCK"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       expect(TokenType::NL);
       StatementList();
       expect(TokenType::BAS); 
       expect(TokenType::KARO);
       expect(TokenType::NL);
    }

    tabs--;
    //removeNL();

}
void parser::BlockF(){
    //removeNL();
    int Statement =0;
    print_tabs();
    cout<<"BLOCKF"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       expect(TokenType::NL);
       //cout<<"StatementC = "<<statementCount<<endl;
       StatementList();
       //cout<<"this = ";_lexer.peek(1).Print();
       expect(TokenType::KAAM); 
       expect(TokenType::KHATAM);
       expect(TokenType::NL);
    }

    tabs--;
   // removeNL();

}




void parser::StatementList(){
  // removeNL();
    print_tabs();
    cout<<"SL"<<endl;
    tabs++;
    // cout<<"StatementCount = "<<countStatementsInBlock(_lexer.getCurrentPointer()-1,1)<<endl;
    // cout<<"Here";
    // _lexer.peek(1).Print();

    // if(countStatementsInBlock(_lexer.getCurrentPointer()-1,1)==1){
    //    // cout<<"h"<<endl;
    // Statement();
    // }
    // else if(countStatementsInBlock(_lexer.getCurrentPointer()-1,1)>1) {
    //    // cout<<"b";
    //  Statement();StatementList();
    // }
    // else{
    //     cout<<"j";
    //     return;
    // }

    //cout<<"Call "<<_lexer.CheckLast(_lexer.getCurrentPointer())<<endl;

    if(_lexer.CheckLast(_lexer.getCurrentPointer())==1){
    Statement();
    }
    else if(_lexer.CheckLast(_lexer.getCurrentPointer())==0) {
     Statement();StatementList();
    }
    else if(_lexer.CheckLast(_lexer.getCurrentPointer())==-1) {
     return;
    }
    else{
        return;
    }

    tabs--;
   //removeNL();
   
}

void parser::Statement(){
    //removeNL();
    print_tabs();
    cout<<"S"<<endl;
    tabs++;


    if (_lexer.peek(1).tokenType == TokenType::AGAR)
    {
        SelectionStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::JAB){
        IterativeStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::WAPAS){
        ReturnStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::AT){
        VariableDeclaration();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::ASSIGNOP){
        VariableAssignment();
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHALAO){
        FunctionCall();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LO  || _lexer.peek(1).tokenType == TokenType::DEKHAO){
        IOStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID || _lexer.peek(1).tokenType == TokenType::INT){
        Expression();
    }
    else{
        syntax_error();
    }
   
    tabs--;
    //statementCount--;
   // removeNL();

}


void parser::Expression(){

     //removeNL();
    print_tabs();
    cout<<"Ex"<<endl;
    tabs++;

     F(); T_();  
     if (_lexer.peek(1).tokenType != TokenType::RPAREN ){
        expect(TokenType::NL);
     }
    

    tabs--;
     
}
void parser::SelectionStatement(){

}
void parser::IterativeStatement(){
    //IterativeStatement → "jab tak" "(" Expression ")" Block
    print_tabs();
    cout<<"Iter S"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::JAB)
    {
       expect(TokenType::JAB);
       expect(TokenType::TAK);
       expect(TokenType::LPAREN); 
       Expression();
       expect(TokenType::RPAREN);
       Block();
    }
    else {
      
    }

    tabs--;


}
void parser::ReturnStatement(){

}
void parser::FunctionCall(){

}
void parser::IOStatement(){

}






void parser::T_(){
   // removeNL();
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
   // removeNL();
}

void parser::F(){
   // removeNL();
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
    //removeNL();

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