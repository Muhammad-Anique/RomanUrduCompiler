Assignment 1:
First we created a single DFA for Identifiers, integers, string, comment, realtional operators and IO operators. Then we moved one and wrote the regular definition of these by consulting 
the DFA. Lastly we did the coding part by writing a program that identifies token and their respevctive lexenes for keywords, relational operators, special characters, arithmetic operators,
other constructs, strings, comments, assignment operator, starting block, closing block and IO operators. We followed both the DFA (i.e it's states represent cases) and regular defintion 
(i.e for token names) while coding for dentifiers, integers, string, comment, realtional operators and IO operators while the others were did so independently. We did not encounter any 
problems while doing the assignment and were able to complete it without any hassle.

Assignment 2:
First we created a CFG for the Roman Urdu language and then we converted it into LL(1) grammar by setting operator precedence and association, removing left recursion and ambiguity and left
factoring. After that we wrote the code to implement the Parser by following the LL(1) grammar. Next we generated a Parse Tree as well. We did not encounter any problems while doing the 
assignment and were able to complete it without any hassle.

ASsignment 3:
First we created a a rough translation cheme for the Roman Urdu language and then we used it to test three address code. After that we finalize our output actions and included these actions in 
our grammar file. We created Symbol Table and Three Address code using output actions which incude the use of vectors and variables. in three address code we have used temp variables for compitation.
Due to update in assignment, we faced a huge problem and we got panic. We have completed the assignment long before as per the requirements. On Due Date when we were about to submit the assignment, we saw update
in three address code example and Symbol table. Due to which we have to commit a lot of changes in our assignment. 


Assignment#4 :

I have done following steps

1. Read TAC.txt  line by line in vector<string>
2. Clean It --> remove more than one empty spaces EXECUTION
3. Remove unnecessary things
4. Tokenize the the strings of line on space  [but replace $ with space in out "string"]
5. Store it in Opcode class which contain 6 tokens of tyoe string
6. from the symbol table file i have made mulitlevel symbol table for every function
7. then based on these tokens translated the code into QUAD OPCODE which also a structure contain 4 OPs of type string
8. then made DataSegment for every function and map the addresses in quad 
9. then executed the code based on operations and Operand1
10. Function call is done using StackSegment every function has a different Stack Segment 
11. Code Runs Fine and Every thing id Fine 
12 As Function Call was optional BONUS MArks Should BE GIVEN. 