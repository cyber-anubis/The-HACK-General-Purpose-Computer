#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <bitset>
using namespace std;

//Symbol tables for mapping HACK machine language pre-defined fields with its corresponding translation.
map <string, string> c_fields_table;
map <string, string> c_dest_table;
map <string, string> symbols;

void Intialization();
string Decode_A_Instruction(string line);
string Decode_C_Instruction(string line);
void first_pass(ifstream &file);
bool is_decimal(string num);
string ignore_white(string line);

int main(int argc, char *argv[])
{
	//Initializing the symbol tables and instruction set fields
	Intialization();

	ofstream output_file;
	output_file.open("out.hack",ios::trunc);

	ifstream input_file;
	input_file.open(argv[1]);

	//Applying the first iteration technique
	first_pass(input_file);

	//Repositioning at the start of the file after the 1st iteration
	input_file.clear();
	input_file.seekg(0);

	while(!input_file.eof())
	{
		string line,out;
		getline(input_file,line);
		if (line.size() == 0) continue;	//line.size() = 0 for blank lines in Windows machines only!!
		line = ignore_white(line);	//removing leading whitespaces
		if (line[0] == '@' && line[0] != '(' && line[0] != '/') {output_file << Decode_A_Instruction(line)<<endl;}
		else if (line[0] != '@' && line[0] != '(' && line[0] != '/') {output_file << Decode_C_Instruction(line)<<endl;}
	}
	return 0;
}

//Simply removes the leading whitespaces
string ignore_white(string line)
{
	string ret="";
	int index=0;
	bool done = false;
	for (int i = 0 ; i < line.size(); i++) {
		if (done) break;
		if (line[i] != ' ') {done=true; index=i; break;}
	}

	for (int i = index; i <line.size(); i++) ret+=line[i];
	//cout<<"RET is "<<endl;
	return ret;
}
//Simply check if all chars in the string are numbers
bool is_decimal(string num)
{
	int cnt = 0;
	for (int i = 0 ; i < num.size(); i++)	if (isdigit(num[i])) cnt++;

	if (cnt == num.size()) return true;
	return false;
}

/*
 * Applying the first iteration through all source file to register new variables and labels
 * In order to evaluate them in the 2nd pass(iteration).
 *
 */
void first_pass(ifstream &file)
{
	//Keeping track of line numbers and variables allocation offset
	int line_cnt=0, allocated=16;

	string line ="";
	//Parsing for labels first for simplicity
	while (file.is_open())
	{
		while(!file.eof())
		{
			getline(file,line);
			line = ignore_white(line);	//removing leading whitespaces
			if (line[0]=='(')	//Label detected
			{
				string constant ="";
				bool new_label = false;					//concatenating the name
				for (int i = 1 ; i<line.size()-1;i++) constant+=line[i];
				if (symbols[constant] =="") {new_label = true;/*cout<<"## Label = "<<constant;*/}
				if(new_label)									//Debugging msg
				{
					bitset<15> no(line_cnt);
					string binary =no.to_string();
					//cout<<" at "<<binary<<endl;	//Debugging msg
					symbols[constant] =binary;
					new_label = false;
				}
			}//Counting the line numbers of REAL instructions, ignoring comments and blank lines
			if (line[0] != '(' && line[0] != '/' && line.size() != 0)	line_cnt++;
		}												//line.size() = 0 for blank lines in Windows machines only!!
		if (file.eof()) break;
	}

	//Repositioning at the start of the file in order to start parsing for variables
	file.clear();
	file.seekg(0);

	while (file.is_open())
		{
		while(!file.eof())
			{
				getline(file,line);
				line = ignore_white(line);	//removing leading whitespaces
				if (line[0] == '@')		//Variable detected (after @ instruction)
				{
					string constant ="";
						bool new_variable = false;			//concatenating the name
						for (int i = 1 ; i<line.size();i++) constant+=line[i];
						if (is_decimal(constant)) break;

						if (symbols[constant] =="") {new_variable = true;/*cout<<"## Variable = "<<constant<<endl;*/}
						if (new_variable)									//Debugging msg
						{
							bitset<15> no(allocated);
							string binary =no.to_string();	//Debugging msg
							symbols[constant] =binary;
							allocated++;	//increasing the offset for the upcoming new variables
							new_variable = false;
						}
				}
			}
			if (file.eof()) break;
		}
}

/*
 * Decoding A-Instructions   16 bits width = 0+address[15]
 *
 */
string Decode_A_Instruction(string line)
{
	string ret= "";
	//Extracting(concatenating) the value after the 1st bit
	string constant="";
	//Flags to differentiate between decimal constant and non-decimal variable
	bool symbol = false,decimal = false;

	//Concatenating the constant
	for (int i = 1 ; i<line.size();i++) constant+=line[i];
	//If decimal constant, set the flag.
	//Else, evaluate it.
	if (is_decimal(constant)) decimal = true;
	else
	{
		ret+='0';	//1st bit (MSB)
		ret+=symbols[constant];	//Get the mapped value from the tables.
	}

	if (decimal)	//decimal value, concatenating the result
	{
	string arg ="";
	for(int i = line.size()-1 ; i > 0 ;i--) arg+=line[i];
	reverse(arg.begin(),arg.end());
	int arg2 =stoi(arg);
	//Using bitset for conversion
	bitset<16> no(arg2);
	string binary =no.to_string();
	ret+=binary;
	}
//Returning the final output
return ret;
}

/*
 * Decoding C-Instructions   16 bits width = 111ac1c2c3c4c5c6d1d2d3j1j2j3
 *
 */
string  Decode_C_Instruction(string line)
{
	string ret="";
	//Concatenating each field of the C-Instruction
	string comp="",des="",jump="";
	//Spliting the fields via '=' and ';' signs
	bool equal_sign = false,semi_colon_sign =false;
	int equal_sign_index =-1,semi_colon_sign_index=-1;

	//Setting field flags and indices
	for(int i = 0 ; i<line.size();i++)	if(line[i]=='=') {equal_sign=true;equal_sign_index=i; break;cout<<"= @ "<<equal_sign_index<<endl;}
	for(int i = 0 ; i<line.size();i++)	if(line[i]==';') {semi_colon_sign=true;semi_colon_sign_index=i;break;}

	/*
	 * According the '=' and ';' signs, we will build a tree to cover every possible test case of the C-Instruction
	 * 												( = ) "must be always available"
	 * 									( ; )					( ; )
	 * 								NO         YES			NO         YES
	 *						    	M=1		  0;JMP        M=D+1      A=-1;J:E
	 *
	 * This is handled in the nested if statements below, then concatenating every field using the '=' and ';' signs.
	 */
	if (equal_sign)
	{
		if (semi_colon_sign)
		{
			for(int i = 0 ; i<equal_sign_index;i++)		{if (line[i]!= ' ') des+=line[i];}
			for(int i = semi_colon_sign_index+1 ; i<line.size();i++)	{if (line[i]!= ' ') jump+=line[i];}
			for(int i = equal_sign_index+1 ; i<semi_colon_sign_index ;i++) 	{if (line[i]!= ' ') comp+=line[i];}
		}
		else
		{
			for(int i = 0 ; i<equal_sign_index;i++)		{if (line[i]!= ' ') des+=line[i];}
			for(int i = equal_sign_index+1 ; i<line.size() ;i++) {if (line[i]!= ' ') comp+=line[i];}
			jump="null";
		}
	}
	else
	{
		if (semi_colon_sign)
		{
			des="null";
			for(int i = semi_colon_sign_index+1 ; i<line.size();i++)	{if (line[i]!= ' ') jump+=line[i];}
			for(int i = 0 ; i<semi_colon_sign_index ;i++) {if (line[i]!= ' ') comp+=line[i];}
		}
		else
		{
			des="null";
			for(int i = equal_sign_index+1 ; i<line.size() ;i++) {if (line[i]!= ' ') comp+=line[i];}
			jump="null";
		}
	}
	//Concatenating the final string to be returned.
	ret+="111";
	ret+=c_fields_table[comp];
	ret+=c_dest_table[des];
	ret+=c_fields_table[jump];
	//cout<<ret<<endl;

return ret;
}

/*
 * Initializing all the symbol table to be used in mapping.
 * Including all predefined symbols and fields as well as the newly dynamically allocated during runtime.
 * All the mapping is done according to the HACK machine language specification.
 */
void Intialization()
{
	//Comp field table
	c_fields_table["0"]="0101010";
	c_fields_table["1"]="0111111";
	c_fields_table["-1"]="0111010";
	c_fields_table["D"]="0001100";
	c_fields_table["A"]="0110000";			c_fields_table["M"]="1110000"  ;
	c_fields_table["!D"]="0001101";
	c_fields_table["!A"]="0110001";			c_fields_table["!M"]="1110001" ;
	c_fields_table["-D"]="0001111";
	c_fields_table["-A"]="0110011";			c_fields_table["-M"]="1110011" ;
	c_fields_table["D+1"]="0011111";
	c_fields_table["1+D"]="0011111";
	c_fields_table["A+1"]="0110111";		c_fields_table["M+1"]="1110111";
	c_fields_table["1+A"]="0110111";		c_fields_table["1+M"]="1110111";
	c_fields_table["D-1"]="0001110";
	c_fields_table["-1+D"]="0001110";
	c_fields_table["A-1"]="0110010";		c_fields_table["M-1"]="1110010";
	c_fields_table["-1+A"]="0110010";		c_fields_table["-1+M"]="1110010";
	c_fields_table["D+A"]="0000010";		c_fields_table["D+M"]="1000010";
	c_fields_table["A+D"]="0000010";		c_fields_table["M+D"]="1000010";
	c_fields_table["D-A"]="0010011";		c_fields_table["D-M"]="1010011";
	c_fields_table["A-D"]="0000111";		c_fields_table["M-D"]="1000111";
	c_fields_table["D&A"]="0000000";		c_fields_table["D&M"]="1000000";
	c_fields_table["D|A"]="0010101";		c_fields_table["D|M"]="1010101";
	c_fields_table["A|D"]="0010101";		c_fields_table["M|D"]="1010101";

	//Destination field table
	c_dest_table["M"]="001";
	c_dest_table["D"]="010";
	c_dest_table["MD"]="011";
	c_dest_table["A"]="100";
	c_dest_table["AM"]="101";
	c_dest_table["AD"]="110";
	c_dest_table["AMD"]="111";
	c_dest_table["null"]="000";

	//Jump field table
	c_fields_table["JGT"]="001";
	c_fields_table["JEQ"]="010";
	c_fields_table["JGE"]="011";
	c_fields_table["JLT"]="100";
	c_fields_table["JNE"]="101";
	c_fields_table["JLE"]="110";
	c_fields_table["JMP"]="111";
	c_fields_table["null"]="000";

	//Virtual registers
	symbols["R0"]="000000000000000";
	symbols["R1"]="000000000000001";
	symbols["R2"]="000000000000010";
	symbols["R3"]="000000000000011";
	symbols["R4"]="000000000000100";
	symbols["R5"]="000000000000101";
	symbols["R6"]="000000000000110";
	symbols["R7"]="000000000000111";
	symbols["R8"]="000000000001000";
	symbols["R9"]="000000000001001";
	symbols["R10"]="000000000001010";
	symbols["R11"]="000000000001011";
	symbols["R12"]="000000000001100";
	symbols["R13"]="000000000001101";
	symbols["R14"]="000000000001110";
	symbols["R15"]="000000000001111";

	//Predefined pointers
	symbols["SP"]="000000000000000";
	symbols["LCL"]="000000000000001";
	symbols["ARG"]="000000000000010";
	symbols["THIS"]="000000000000011";
	symbols["THAT"]="000000000000100";

	//Input & Output pointers
	symbols["SCREEN"]="100000000000000";
	symbols["KBD"]="110000000000000";

	//More symbols will be dynamically added in "runtime" to handle variables and code labels
}
