import re

string_quotes = re.compile(r'"')
symbols = re.compile(r'\W')
word_letters = re.compile(r'\w')
string_quotes = re.compile(r'"')
white_comments = re.compile(r'//*')

pre_final = []
final = []
final_final = []


string_list =[]


def get_pretty_strings(para):
    if len(string_quotes.findall(para)) % 2 == 0:
        mutant_line = list(para)
        saved_idx = -1
        ret_list = []
        for start_idx in range(len(para)):
            if para[start_idx] == '"' and start_idx != saved_idx:
                extracted_string = ''
                str_idx = start_idx

                for char_idx in range(str_idx, len(para)):
                    if char_idx == saved_idx:
                        break

                    if para[char_idx] == ' ':
                        dummy = '#'
                        mutant_line[char_idx] = '#'
                    else:
                        dummy = para[char_idx]

                    extracted_string += dummy
                    para = ''.join(mutant_line)

                    if extracted_string[0] == '"' and extracted_string[-1] == '"' and len(extracted_string) != 1:
                        saved_idx = char_idx
             
                        break

    return para



def extract_strings_from_symbols(para):
    temp = ""
    ret = []

    if para[0] == '"' and para[-1] == '"':  # Mark this as string constant
        return para;


    
    if len(string_quotes.findall(para)) % 2 == 0 and len(string_quotes.findall(para)) >= 2:
        flag = True
        dummy_list = list(para)

        for character_idx in range(len(para)):
            if para[character_idx] == '"' and flag == True:
                if len(temp) > 0:
                    ret.append(temp)
                temp = ''
                saved_idx = character_idx

                for char_idx in range(character_idx, len(para)):
                    temp += para[char_idx]
                    dummy_list[char_idx] = '#'

                    if char_idx != saved_idx and para[char_idx] == '"':
                        flag = False
                        ret.append(temp)
                        temp = ''
                        para = ''.join(dummy_list)
                        break
            else:
                if para[character_idx] != '#':
                    temp += para[character_idx]

        if len(temp) > 0:
            ret.append(temp)

        real_ret =[]
        for x in ret:
            real_ret.append(extract_symbols(x))
        return real_ret


    else :
        return extract_symbols(para)

def extract_symbols (para):
    temp =""
    ret =[]

    if para[0] == '"' and para[-1] == '"':  # Mark this as string constant
        return para;


    for character in para:  
        if word_letters.search(character) != None:
            temp += character
        else:
            if temp != "":
                ret.append(temp)
                temp = ""
            ret.append(character)
    if len(temp) > 0:
        ret.append(temp)

    return ret


def categorizing(token):
    keywords = ['class', 'constructor', 'function', 'method', 'field', 'static',
                'var', 'int', 'char', 'boolean', 'void', 'true', 'false', 'null',
                'this', 'let', 'do', 'if', 'else', 'while', 'return']


    if symbols.search(token) != None and len(token) == 1:
        if token == '<':
            return '<symbol> ' + '&lt;' + ' </symbol>'
        elif token == '>':
            return '<symbol> ' + '&gt;' + ' </symbol>'
        elif token == '"':
            return '<symbol> ' + '&quot;' + ' </symbol>'
        elif token == '&':
            return '<symbol> ' + '&amp;' + ' </symbol>'
        else:
            return '<symbol> ' + token + ' </symbol>'

    elif token in keywords:
        return '<keyword> ' + token + ' </keyword>'
    elif token[0].isdecimal():
        return '<integerConstant> ' + token + ' </integerConstant>'
    elif token[0].isalpha() or token[0] == '_':
        return '<identifier> ' + token + ' </identifier>'
    elif token[0] == '"':
        token = token.replace('#', ' ')

        return '<stringConstant> ' + token[1:-1] + ' </stringConstant>'

def extract_from_lists (para):
    for i in para:
        if type(i) == list:
            extract_from_lists(i)
        else :
            final.append(i)


def start_tokenizing(lines):
    global pre_final,final,final_final

    pre_final = []
    final = []
    final_final = []

    for line in lines:
        if line[0:2] == '//' or line[0:3] == '/**' or line[0] == '*' or line[0:2] == ' *' or '*' in line:
            continue

        if len(string_quotes.findall(line)) % 2 == 0 and len(string_quotes.findall(line)) >= 2:
            line = get_pretty_strings(line)


        for term in line.strip().split():

            if white_comments.search(term) != None and term != '/':
                break

            if len(term) != 1 and symbols.search(term) != None:
                
                pre_final.append(extract_strings_from_symbols(term))
            else :
                pre_final.append(term)

 
 
    for x in pre_final:
        if type(x) == list:
            extract_from_lists(x)
        else:
            final.append(x)
   
   

    for _x_ in final:
        if _x_ != None:
            final_final.append(categorizing(_x_))

 
    return final_final

