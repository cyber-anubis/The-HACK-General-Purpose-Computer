#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <filesystem> // C++17 

using namespace std;
namespace fs = std::filesystem;

int parser(string line, string& arg1, string& arg2);
string ignore_white(string line);
string generator(int comm_type, string arg1, string arg2);
void translate_file (string file);
void translate_directory(vector <string> files_list,string file);

//VM Language commands.
enum type { _FUNC_, _CALL_,_PUSH_, _POP_, _ADD_, _SUB_, _NEG_, _EQ_, _GT_, _LT_, _AND_, _OR_, _NOT_, _RET_,_IF_GOTO_,_GOTO_,_LABEL_};

int jmps = 1;
int lines = 0;
string file_name="";
vector <string> files_list;

int main(int argc, char* argv[])
{
	const std::string pathString = argv[1];
	const fs::path path(pathString); // Constructing the path from a string..
	std::error_code ec; // For using the non-throwing overloads of functions.
	
	string source_file;
	if (fs::is_directory(path, ec))
	{
		for (const auto& entry : fs::directory_iterator(path))
		{
			source_file = entry.path().string();
			files_list.push_back(source_file);
		}

		translate_directory(files_list,argv[1]);
	}
	else if (fs::is_regular_file(path, ec))	translate_file(argv[1]);

	return 0;
}

void translate_directory(vector <string> files_list, string file)
{
	//Constructing the filename for .asm file output.
	string o = "";
	ofstream output_file;
	string dummy_Str = file;

	for (int iter = dummy_Str.size() -1 ; iter >= 0 && isalpha(file[iter]); iter--) file_name += file[iter];
	reverse(file_name.begin(), file_name.end());

	for (int iter = dummy_Str.size() -1 ; iter >= 0; iter--) o += file[iter];
	reverse(o.begin(), o.end());
	o += ".asm";

	output_file.open(o, std::ios_base::app);
	ifstream input_file;

	//Bootstrap code for: 1-initializing the SP and 2-Calling Sys.init.
	//Only done -once- when translating directories. 
	string bootstrap_code = "@256 D=A @SP M=D ";	//Initializing Stack pointer
	bool booted = false;

	//Writing the asm code to the output .asm file.
	stringstream ss(bootstrap_code);
	string str;
	while (ss >> str) { output_file << str << endl; if (str[0] != '(') lines++; }
	
	str = "call Sys.init 0";	//Calling Sys.init
	string arg1, arg2;

	int i = parser(str, arg1, arg2);	//Parse the line: extract the arguments & return the command type.
	string newstr = generator(i, arg1, arg2);	//Generate the asm code for the command type (i) and args: arg1,arg2.
	
	//Writing the asm code to the output .asm file.
	stringstream sss (newstr);
	string dum_str;
	while (sss >> dum_str) { output_file << dum_str << endl; if (str[0] != '(') lines++; }
	
	//Traversing the list of .vm files to translater them.
	for (int index = 0; index < files_list.size(); index++)
	{
		dummy_Str = files_list[index];
		
		//Re-Constructing the file name for unique labels for static variables
		file_name = "";
		for (int iter = dummy_Str.size() - 4; iter >= 0 && (isalpha(dummy_Str[iter]) || isdigit(dummy_Str[iter])); iter--) file_name += dummy_Str[iter];
		reverse(file_name.begin(), file_name.end());
		
		//Ignoring all files but not .vm ones.
		if (dummy_Str[dummy_Str.size() - 1] != 'm' && dummy_Str[dummy_Str.size() - 2] != 'v') continue;
		
		input_file.open(dummy_Str);
		
		while (!input_file.eof())
		{
			string line, out, arg1 = "", arg2 = "";
			getline(input_file, line);
			
			if (line.size() == 0) continue;	//line.size() = 0 for blank lines in Windows machines only!!
			line = ignore_white(line);	//removing leading whitespaces
			if (line[0] == '/') continue;
			output_file << "//" << line << endl;	//Commenting out all VM commands before translating them.

			int i = parser(line, arg1, arg2);	//Parse the line: extract the arguments & return the command type.
			line = generator(i, arg1, arg2);	//Generate the asm code for the command type (i) and args: arg1,arg2.
			
			//Writing the asm code to the output .asm file.
			stringstream ss(line);
			string str;
			while (ss >> str) { output_file << str << endl; if (str[0] != '(') lines++; }
		}
		
		//Closing and clearing the current file to open the next one.
		if (input_file.is_open())
		{
			input_file.close();
			input_file.clear();
		}
	}
}


void translate_file(string file)
{
	//Constructing the filename for .asm file output + for unique lables for static variables.
	string o = "";
	ofstream output_file;
	string dummy_Str = file;

	for (int iter = dummy_Str.size() - 4; iter >= 0 && isalpha(file[iter]); iter--) file_name +=file[iter];
	reverse(file_name.begin(), file_name.end());

	for (int iter = dummy_Str.size() - 4; iter >= 0; iter--) o += file[iter];
	reverse(o.begin(), o.end());
	o += ".asm";
	output_file.open(o, ios::trunc);

	ifstream input_file;
	input_file.open(file);

	while (!input_file.eof())
	{
		string line, out, arg1 = "", arg2 = "";
		getline(input_file, line);
		if (line.size() == 0) continue;	//line.size() = 0 for blank lines in Windows machines only!!
		line = ignore_white(line);	//removing leading whitespaces
		if (line[0] == '/') continue;
		output_file << "//" << line << endl; //Commenting out all VM commands before translating them.

		int i = parser(line, arg1, arg2);	//Parse the line: extract the arguments & return the command type. 
		line = generator(i, arg1, arg2);	//Generate the asm code for the command type (i) and args: arg1,arg2.
		
											//Writing the asm code to the output .asm file.
		stringstream ss(line);
		string str;
		while (ss >> str) { output_file << str << endl; if (str[0] != '(')lines++; }
	}

}


//Simply removes the leading whitespaces
string ignore_white(string line)
{
	string ret = "";
	int index = 0;
	bool done = false;
	for (int i = 0; i < line.size(); i++) {
		if (done) break;
		if (line[i] != ' ') { done = true; index = i; break; }
	}

	for (int i = index; i < line.size(); i++) ret += line[i];
	return ret;
}

int parser(string line, string& arg1, string& arg2)
{
	int comm_type;	//Return value.
	stringstream ss(line);
	string temp = "";

	ss >> temp;
	if (temp == "push") comm_type = _PUSH_;
	else if (temp == "pop") comm_type = _POP_;
	else if (temp == "add") comm_type = _ADD_;
	else if (temp == "sub") comm_type = _SUB_;
	else if (temp == "neg") comm_type = _NEG_;
	else if (temp == "eq") comm_type = _EQ_;
	else if (temp == "gt") comm_type = _GT_;
	else if (temp == "lt") comm_type = _LT_;
	else if (temp == "and") comm_type = _AND_;
	else if (temp == "or") comm_type = _OR_;
	else if (temp == "not") comm_type = _NOT_;
	else if (temp == "if-goto") comm_type = _IF_GOTO_;
	else if (temp == "goto") comm_type = _GOTO_;
	else if (temp == "label") comm_type = _LABEL_;
	else if (temp == "function") comm_type = _FUNC_;
	else if (temp == "return") comm_type = _RET_;
	else if (temp == "call") comm_type = _CALL_;
	else return -1;	//Invalid VM code

	if (comm_type < 4)	ss >> arg1 >> arg2;
	else if (comm_type > 10) ss >> arg1;

	return comm_type;
}

//Function used for generating the asm code for push & pop commands.
string write_push_pop(int comm_type, string arg1, string arg2)
{
	string ret = "";

	if (arg1 == "local" || arg1 == "argument" || arg1 == "this" || arg1 == "that")
	{
		string seg = "";
		if (arg1 == "local") seg = "LCL";
		else if (arg1 == "argument") seg = "ARG";
		else if (arg1 == "this") seg = "THIS";
		else seg = "THAT";

		ret = "@" + arg2 + " " + "D=A ";
		if (comm_type == _PUSH_) ret += "@" + seg + " A=D+M D=M @SP A=M M=D @SP M=M+1";
		else ret += "@" + seg + " D=D+M @R13 M=D @SP M=M-1 A=M D=M @R13 A=M M=D";
	}
	else if (arg1 == "constant") ret = "@" + arg2 + " D=A @SP A=M M=D @SP M=M+1";
	else if (arg1 == "static")
	{
		arg2 = file_name + "." + arg2;
		if (comm_type == _PUSH_) ret = "@" + arg2 + " D=M @SP A=M M=D @SP M=M+1";
		else ret = "@SP M=M-1 A=M D=M @" + arg2 + " M=D";
	}
	else if (arg1 == "temp")
	{
		string str = to_string(5 + stoi(arg2));
		if (comm_type == _PUSH_) ret = "@" + str + " D=M @SP A=M M=D @SP M=M+1";
		else ret = "@SP M=M-1 A=M D=M @" + str + " M=D";
	}
	else if (arg1 == "pointer")
	{
		string str = "";
		if (arg2 == "0") str = "THIS";
		else str = "THAT";

		if (comm_type == _PUSH_) ret = "@" + str + " D=M @SP A=M M=D @SP M=M+1";
		else ret = "@SP M=M-1 A=M D=M @" + str + " M=D";
	}
	return ret;
}


string generator(int comm_type, string arg1, string arg2)
{
	string ret = "";

	if (comm_type < 4)
	{
		if (comm_type == _FUNC_)
		{
			ret = "(" + arg1 + ") ";
			int iter = stoi(arg2);
			for (int i = 0; i < iter; i++)	ret += write_push_pop(_PUSH_, "constant", "0") + " ";
		}
		else if (comm_type == _CALL_)
		{
			int iter = stoi(arg2);

			ret += write_push_pop(_PUSH_, "constant", to_string(lines + 49 + iter)) + " ";	//push the return address.
			ret += "@LCL" + (string)" D=M @SP A=M M=D @SP M=M+1 ";
			ret += "@ARG" + (string)" D=M @SP A=M M=D @SP M=M+1 ";
			ret += "@THIS" + (string)" D=M @SP A=M M=D @SP M=M+1 ";
			ret += "@THAT" + (string)" D=M @SP A=M M=D @SP M=M+1 ";
			ret += "@SP D=M-1 D=D-1 D=D-1 D=D-1 D=D-1 ";

			//Minus nArgs.
			for (int i = 0; i < iter; i++) ret += "D=D-1 ";
			
			ret += "@ARG M=D @SP D=M @LCL M=D ";
			ret += "@"+arg1+" 0;JMP";
		}
		else { ret = write_push_pop(comm_type, arg1, arg2); }
	}
	else
	{
		if (comm_type == _ADD_) ret = "@SP M=M-1 A=M D=M A=A-1 M=D+M";
		else if (comm_type == _SUB_) ret = "@SP M=M-1 A=M D=M A=A-1 M=M-D";
		else if (comm_type == _NEG_) ret = "@SP M=M-1 A=M M=-M @SP M=M+1";
		else if (comm_type == _AND_) ret = "@SP M=M-1 A=M D=M A=A-1 M=D&M";
		else if (comm_type == _OR_) ret = "@SP M=M-1 A=M D=M A=A-1 M=D|M";
		else if (comm_type == _NOT_) ret = "@SP M=M-1 A=M M=!M @SP M=M+1";
		else if (comm_type == _EQ_ || comm_type == _GT_ || comm_type == _LT_)
		{
			string jmp_label = file_name + to_string(jmps), label_end = file_name + to_string(jmps) + "_end"; jmps++;
			if (comm_type == _EQ_) ret = "@SP M=M-1 A=M D=M A=A-1 D=M-D @" + jmp_label + " D;JEQ @SP A=M A=A-1 M=0 @" + label_end + " 0;JMP (" + jmp_label + ") @SP A=M A=A-1 M=-1 (" + label_end + ")";
			else if (comm_type == _GT_) ret = "@SP M=M-1 A=M D=M A=A-1 D=M-D @" + jmp_label + " D;JGT @SP A=M A=A-1 M=0 @" + label_end + " 0;JMP (" + jmp_label + ") @SP A=M A=A-1 M=-1 (" + label_end + ")";
			else ret = "@SP M=M-1 A=M D=M A=A-1 D=M-D @" + jmp_label + " D;JLT @SP A=M A=A-1 M=0 @" + label_end + " 0;JMP (" + jmp_label + ") @SP A=M A=A-1 M=-1 (" + label_end + ")";
		}
		else if (comm_type == _GOTO_) ret = "@" + arg1 + " 0;JMP";
		else if (comm_type == _LABEL_) ret = "(" + arg1 + ")";
		else if (comm_type == _IF_GOTO_) ret = "@SP M=M-1 A=M D=M @" + arg1 + " D;JNE";
		else if (comm_type == _RET_)
		{
			ret = "@LCL D=M @14 M=D A=M-1 A=A-1 A=A-1 A=A-1 A=A-1 D=M @15 M=D ";
			ret += write_push_pop(_POP_, "argument", "0") + " ";
			ret += "@ARG D=M @SP M=D+1 @14 D=M-1 M=D A=D D=M @THAT M=D ";
			ret += "@14 D=M-1 M=D A=D D=M @THIS M=D ";
			ret += "@14 D=M-1 M=D A=D D=M @ARG M=D ";
			ret += "@14 D=M-1 M=D A=D D=M @LCL M=D ";
			ret += "@15 A=M 0;JMP";
		}
	}
	
	return ret;
}
