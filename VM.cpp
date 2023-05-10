#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include "VM.h"
#include<string>
#include <regex>
#pragma warning(disable:4996)
using namespace std;

void VM::start(){
    initialize_OpCode_and_CodeSegment();
    quad = _opCode._quadCode;
    cout<<"--------- THE QUAD CODE In VM -----------"<<endl;
    for(int i=0;i<quad.size();i++){
        quad[i].Print_QUAD_CODE();
    }
    initialize_symbol_tables();
    initialize_data_segmant();

}


void VM::initialize_symbol_tables(){
    ifstream file("symbol_table.txt"); // open file
    string line;

    // read header line and split into vector of column names
    getline(file, line);
    stringstream ss_header(line);
    string header;
    vector<string> headers;
    while (ss_header >> header) {
        headers.push_back(header);
    }

    // create vectors for each column
    int num_columns = headers.size();
    vector<vector<string>> columns(num_columns);

    // read data lines and tokenize each line
    while (getline(file, line)) {
        // replace consecutive spaces with a single space
        line = regex_replace(line, regex("\\s+"), " ");

        // split line into vector of column values
        stringstream ss(line);
        string value;
        for (int i = 0; i < num_columns; i++) {
            if (getline(ss, value, ' ')) {
                columns[i].push_back(value);
            }
        }
    }

    // print column values
    // for (int i = 0; i < num_columns; i++) {
    //     cout << headers[i] << ": ";
    //     // for (string value : columns[i]) {
    //     //     cout << value << " ";
    //     // }
    //     for (int j=0;j<columns[i].size();j++) {
    //         cout <<columns[i][j] << " ";
    //     }
        
    //     cout << endl;
    // }

    file.close(); // close file


    //initializing global table
    int n=0;
    while(columns[3][n]!="func"){
        cout<<columns[3][n]<<" | "<< columns[4][n]<<" |"<<columns[2][n] << "|"<<columns[1][n]<<"|"<<endl;;
        global_ST.add_Entry(columns[4][n], stoi(columns[2][n]), stoi(columns[1][n]));
        global_ST_Context.push_back("var");
        n++;
    }
   
 
    int ind = 0;
    while(n<=columns[3].size()-1){
        if(columns[3][n]=="func")
        {
            global_ST.add_Entry(columns[4][n], ind, 0);ind++;
            global_ST_Context.push_back("func");
            n++;

            Symbol_Table st;
            while(columns[3][n]!="func" && n<=columns[3].size()-1){
              
                st.add_Entry(columns[4][n], stoi(columns[2][n])-4, stoi(columns[1][n]));  n++;
               if(n>columns[3].size()-1)break;
            }
            local_ST.push_back(st);
        }
        else{
            n++;
        }

      
    }


    cout<<"Global Symbol Table"<<endl;
    global_ST.Print_Symbol_Table(global_ST_Context);
     
    for(int i=0;i<local_ST.size();i++)
    {
        cout<<"Local Symbol table "<<i<<endl;
        local_ST[i].Print_Symbol_Table();
    }

}

void VM::initialize_OpCode_and_CodeSegment(){
    _opCode.load_code_in_stream("TAC.txt");
}


void VM::initialize_data_segmant(){
    DataSegment global;
    for(int i=0;i<quad.size()-1;i++){
        cout<<"-----------------------------"<<endl;

        while(quad[i].OP2!=":"){
            if(quad[i].OP1=="HALT")break;
           
            if(quad[i].OP1=="mov"){

               
                if(lookup_global_symbol_table(quad[i].OP2)){    

                    quad[i].OP2 = '&' + to_string(global.add_variable(quad[i].OP2));

                    if(lookup_global_symbol_table(quad[i].OP3)){
                        quad[i].OP3  = '&' + to_string(global.add_variable(quad[i].OP3));
                    }
               }

               QuadCode Q(quad[i]);
               CS.push_back(Q);
            }

            else if(quad[i].OP1=="+" || quad[i].OP1=="-"  || quad[i].OP1=="*"  || quad[i].OP1=="/" || quad[i].OP1=="%" ){

                if(lookup_global_symbol_table(quad[i].OP2)){    

                    quad[i].OP2 = '&' + to_string(global.add_variable(quad[i].OP2));
                }
                    
                if(lookup_global_symbol_table(quad[i].OP3)){
                    quad[i].OP3 = '&' + to_string(global.add_variable(quad[i].OP3));
                }
                
                if(lookup_global_symbol_table(quad[i].OP4)){
                     quad[i].OP4 = '&' + to_string(global.add_variable(quad[i].OP4));
                }

                QuadCode Q(quad[i]);
                CS.push_back(Q);
            }
           
            i++;
        }

       

        break;
    }

    DS.push_back(global);


    initialize_data_segmant_local();


    cout<<"---------------------THE CODE SEGMENT -------------------------"<<endl;

    for(int u=0; u<CS.size(); u++){
       cout<<u<<".    "; CS[u].Print_QUAD_CODE();
    }


    cout<<"---------------------- DATA SEGMENTs ----------------------------"<<endl;
    for(int u=0; u<DS.size(); u++){
        cout<<"-------Segment id  = "<<u<<endl;
        DS[u].Print_Data_Segment();
    }

    Executer_VM();
}


void VM::initialize_data_segmant_local(){

    int i =0;
    int function = 0;
    DataSegment ds;
    string code;
    while(quad[i].OP2!=":")i++;


    while(quad[i].OP1!="HALT"){

        // cout<<"START"<<endl;

        ds.seed = (function + 2) * 1000000;
        // cout<<"Seed = "<<ds.seed<<endl;

        if(quad[i].OP2==":") {
            cout<<"Function => "<<quad[i].OP1<<endl;
            QuadCode Q(quad[i]);
            CS.push_back(Q);
            i++;}

        while(quad[i].OP2!=":" && quad[i].OP1!="HALT"){

            // cout<<"-------s------"<<endl;
            // quad[i].Print_QUAD_CODE();

            if(quad[i].OP1=="mov"){
              code = lookup_variable(quad[i].OP2, function, &ds);  if(code!="NOVAR") quad[i].OP2=code;
              code = lookup_variable(quad[i].OP3, function, &ds);  if(code!="NOVAR") quad[i].OP3=code;
              code = lookup_variable(quad[i].OP4, function, &ds);  if(code!="NOVAR") quad[i].OP4=code;         
            }

            else if(quad[i].OP1=="LT" || quad[i].OP1=="GT" || quad[i].OP1=="EQ" || quad[i].OP1=="NE" || quad[i].OP1=="LE" || quad[i].OP1=="GE"){
              code = lookup_variable(quad[i].OP2, function, &ds);  if(code!="NOVAR") quad[i].OP2=code;
              code = lookup_variable(quad[i].OP3, function, &ds);  if(code!="NOVAR") quad[i].OP3=code;
            }

            else if(quad[i].OP1=="add" || quad[i].OP1=="sub" ||  quad[i].OP1=="div" ||  quad[i].OP1=="mod" || quad[i].OP1=="mul" ){
              code = lookup_variable(quad[i].OP2, function, &ds);  if(code!="NOVAR") quad[i].OP2=code;
              code = lookup_variable(quad[i].OP3, function, &ds);  if(code!="NOVAR") quad[i].OP3=code;
              code = lookup_variable(quad[i].OP4, function, &ds);  if(code!="NOVAR") quad[i].OP4=code;
            }

            else if(quad[i].OP1=="out" || quad[i].OP1=="in" || quad[i].OP1=="param" || quad[i].OP1=="ret"){
              code = lookup_variable(quad[i].OP2, function, &ds);  if(code!="NOVAR") quad[i].OP2=code;
            }


            else if(quad[i].OP1=="call"){
              code = lookup_variable(quad[i].OP4, function, &ds);  if(code!="NOVAR") quad[i].OP4=code;
            }

            
            QuadCode Q(quad[i]);
            // Q.Print_QUAD_CODE();
            CS.push_back(Q);

            //  cout<<"-------e------"<<endl;

            i++;
        }        

        function++;
        DS.push_back(ds);
        ds.ds_clear();


        // cout<<"Function = "<<function<<endl;
        // cout<<"BROKE"<<endl;
    }

    // cout<<"Ending"<<endl;
    
}



bool VM::lookup_global_symbol_table(string var){
    vector<string> val =  global_ST.lookup_table(var, global_ST_Context);
    if(val.size()>=1 && val[0]==var){
        return true;
    }
    else
    return false;    
}



bool VM::lookup_local_table(string var, int i){
    // cout<<"Come"<<endl;
    // cout<<"i = "<<i<<endl;
    vector<string> val = local_ST[i].lookup_table(var);

    if(val.size()>=1 && val[0]==var){
        // cout<<"compared "<<endl;
        return true;
    }
    else
    return false;    
}


string VM::lookup_variable(string var, int func, DataSegment* Ds){
    
    if(lookup_local_table(var, func)){
        return '&' + to_string(Ds->add_variable(var));
    }else{

        if(lookup_global_symbol_table(var)){
            //   cout<<"Found"<<endl;
            string str = to_string(DS[0].get_address_by_var(var));
            //   cout<<str<<endl;
            return str;
        }   
        else 
        return "NOVAR";
    }
    


}





OperationCode VM::convert_condition_to_enum(string Operand1){
    if(Operand1=="mov") return OperationCode::MOV;
    else if(Operand1=="add")  return OperationCode::ADD;
    else if(Operand1=="sub")  return OperationCode::SUB;
    else if(Operand1=="mod")  return OperationCode::MOD;
    else if(Operand1=="div")  return OperationCode::DIV;
    else if(Operand1=="in")  return OperationCode::IN;
    else if(Operand1=="out")  return OperationCode::OUT;
    else if(Operand1=="param")  return OperationCode::PARAM;
    else if(Operand1=="call")  return OperationCode::CALL;
    else if(Operand1=="LE")  return OperationCode::LE;
    else if(Operand1=="LT")  return OperationCode::LT;
    else if(Operand1=="GT")  return OperationCode::GT;
    else if(Operand1=="GE")  return OperationCode::GE;
    else if(Operand1=="EQ")  return OperationCode::EQ;
    else if(Operand1=="NE")  return OperationCode::NE;
    else if(Operand1=="ret")  return OperationCode::RET;
    else if(Operand1=="if")  return OperationCode::IF;
    else if(Operand1==":")  return OperationCode::COLON;





}





int VM::get_ds(string op){
    op.erase(0, 1);
    int modulus = (stoi(op)%1000000);
    int minus = stoi(op) - modulus;
    int divide = minus/1000000;
    int r = divide -1; 
    return r;
}

int VM::get_ds_2(string op){
   
    int modulus = (stoi(op)%1000000);
    int minus = stoi(op) - modulus;
    int divide = minus/1000000;
    int r = divide -1; 
    return r;
}

int VM::get_ind(string op){
    op.erase(0, 1);
    int r = stoi(op)%(((get_ds_2(op))+1)*1000000);
    return r;

}


string VM::clean_the_string(string my_string){
    my_string.erase(remove(my_string.begin(), my_string.end(), '\"'), my_string.end());
    replace(my_string.begin(), my_string.end(), '$', ' ');
    // my_string += '\n';
    return my_string;
}

int VM::updatePC(string label){
    for(int i=0;i<CS.size();i++){
        if(CS[i].OP1==label)
        return i+1;   
    }
}

 void VM::Executer_VM(){
    int Markazi = 0;
   for(int i=0;i<CS.size();i++){
        if(CS[i].OP1=="markazi")
        Markazi=i+1;   
    }

    StackSegment ss;

    cout<<"Markzai = "<<Markazi<<endl;
    cout<<"---------------------Executing the Code----------------------------"<<endl;
    // cout<<"101 % 100 = "<<101%100<<endl;
    // cout<<"201 % 100 = "<<(201 - (201%100))/100<<endl;
    
    int i,j,k,ds_i,ds_j,ds_k;
    for(int pc=Markazi;pc<CS.size();pc++){

        cout<<"CURRENT LINE --> "<<endl;
        CS[pc].Print_QUAD_CODE();
        cout<<"------------------------------"<<endl;
        // cout<<int(convert_condition_to_enum(CS[pc].OP1))<<endl;
        // cout<<"------------------------------"<<endl;

        switch (convert_condition_to_enum(CS[pc].OP1))
        {
            case OperationCode::MOV :
                i =  get_ind(CS[pc].OP2);
                ds_i = get_ds(CS[pc].OP2);
                if(CS[pc].OP3[0]!='&') {
                  DS[ds_i].addresses[i] = stoi(CS[pc].OP3);
                  cout<<"MOVED "<<CS[pc].OP2<<" VALUE " << DS[ds_i].addresses[i]<<endl;
                }  
                else
                {
                 j =  get_ind(CS[pc].OP3);
                 ds_j = get_ds(CS[pc].OP3);
                 DS[ds_i].addresses[i] = DS[ds_j].addresses[j]; 
                   cout<<"MOVED "<<CS[pc].OP2<<" VALUE " << CS[pc].OP2 <<endl;                 
                }
                break;


            case OperationCode::ADD : 
                // i =  stoi(CS[pc].OP4) % seed;
                // ds_i = get_ds(CS[pc].OP4);



                // if(CS[pc].OP2[0]!='&') {
                //   DS[ds_i].addresses[i] = stoi(CS[pc].OP2);
                // }  
                // else
                // {
                //   j =  stoi(CS[pc].OP2) %seed;
                //   ds_j = get_ds(CS[pc].OP2);
                //   DS[ds_i].addresses[i] = DS[ds_j].addresses[j];                  
                // }




                // if(CS[pc].OP3[0]!='&') {
                //   DS[ds_i].addresses[i] += stoi(CS[pc].OP3);
                // }  
                // else
                // {
                //   k =  stoi(CS[pc].OP3) %seed;
                //   ds_k = get_ds(CS[pc].OP3);
                //   DS[ds_i].addresses[i] += DS[ds_k].addresses[k];                  
                // }


            break;
            
            case OperationCode::OUT :
            if(CS[pc].OP2[0]!='&')
            cout<<clean_the_string(CS[pc].OP2);
            else{
            i = get_ind(CS[pc].OP2);
            ds_i =get_ds(CS[pc].OP2);
            cout<<DS[ds_i].addresses[i];
            }
            break;

            case OperationCode::IN :
            i = get_ind(CS[pc].OP2);
            ds_i =get_ds(CS[pc].OP2);
            cin>>DS[ds_i].addresses[i];
            cout<<"The Value Input stored  = "<<DS[ds_i].addresses[i]<<endl;
            break;

            case OperationCode::PARAM:
            i = get_ind(CS[pc].OP2);
            ds_i =get_ds(CS[pc].OP2);
            ss.Stack.push_back(DS[ds_i].addresses[i]);
           
            break;

            case OperationCode::CALL:
            ss.num_of_params = stoi(CS[pc].OP3);
            ss.function_name = CS[pc].OP1;
            ss.return_line = pc+1;
            if(CS[pc].OP4[0]=='&')
            ss.return_value= true;
            pc = updatePC(CS[pc].OP1);
            break;

        


        
        }


    }

    //Execute Markazi
    //Then any other functions

 }