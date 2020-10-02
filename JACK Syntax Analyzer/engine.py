idx = 0
indentation = 0
my_list =[]

def peek_compile_type():
    global idx
    if '<keyword> int' in my_list[idx] or '<keyword> char' in my_list[idx] or '<keyword> boolean' in my_list[idx] or '<identifier>' in my_list[idx]:
        return True
    return False


def compile_type():
    global idx,indentation
    if '<keyword> int' in my_list[idx] or '<keyword> char' in my_list[idx] or '<keyword> boolean' in my_list[idx] or '<identifier>' in my_list[idx]:
        #print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

def compile_parameter_list():
    global idx, indentation

    print(' '* indentation +'<parameterList>')
    indentation +=2

    #print(end='\n')
    compile_type()

    if '<identifier>' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    while '<symbol> ,' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

        compile_type()

        if '<identifier>' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

        if idx >= len(my_list):
            break

    indentation -=2
    print(' '* indentation,end='')
    print('</parameterList>')


def compile_class_var_dec():
    global idx,indentation

    print(' ' * indentation + '<classVarDec>', end='')
    indentation += 2

    if '<keyword> static' in my_list[idx] or '<keyword> field' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    compile_type()

    if '<identifier>' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    while '<symbol> ,' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

        if '<identifier>' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

        if idx >= len(my_list):
            break

    if '<symbol> ;' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</classVarDec>')


def compile_var_dec():
    global idx,indentation

    if '<keyword> var' in my_list[idx]:
        print(' ' * indentation + '<varDec>', end='')
        indentation += 2

        print(end='\n')
        print(' ' * indentation + my_list[idx])     #prints '<keyword> var'
        idx += 1

        compile_type()

    if '<identifier>' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    while '<symbol> ,' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

        if '<identifier>' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

        if idx >= len(my_list):
            break

    if '<symbol> ;' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</varDec>')


def compile_subroutine_body():
    global idx,indentation

    print(' '* indentation +'<subroutineBody>',end='')
    indentation += 2

    if '<symbol> {' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    while '<keyword> var' in my_list[idx]:
        compile_var_dec()

        if idx >= len(my_list):
            break

    compile_statements()

    if '<symbol> }' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</subroutineBody>')


def compile_subroutine_dec():
    global idx,indentation

    print(' ' * indentation + '<subroutineDec>', end='')
    indentation += 2

    if '<keyword> constructor' in my_list[idx] or '<keyword> function' in my_list[idx] or '<keyword> method' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    if 'void' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1
    else:
        compile_type()

    if '<identifier>' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<symbol> (' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    compile_parameter_list()

    if '<symbol> )' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    compile_subroutine_body()

    indentation -=2
    print(' '* indentation,end='')
    print('</subroutineDec>')

def compile_class ():
    global idx,indentation

    #print(my_list)

    print(' '* indentation +'<class>',end='')
    indentation+=2

    if '<keyword> class'in my_list[idx]:
        print(end='\n')
        print(' '*indentation + my_list[idx])
        idx += 1
    if '<identifier>' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<symbol> {' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1


    while '<keyword> static' in my_list[idx] or '<keyword> field' in my_list[idx] :
        compile_class_var_dec()
        if idx >= len(my_list):
            break

    while 'constructor' in my_list[idx] or 'function' in my_list[idx] or 'method' in my_list[idx]:
        compile_subroutine_dec()
        if idx >= len(my_list):
            break


    if '<symbol> }' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation-=2
    print(' '* indentation,end='')
    print('</class>')


def compile_let ():
    global idx,indentation

    print(' '* indentation +'<letStatement>',end='')
    indentation += 2

    if '<keyword> let' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<identifier>' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    if '<symbol> [' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

        if peek_term(idx):
            compile_expression()

        if '<symbol> ]' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

    if '<symbol> =' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    if peek_term(idx):
        compile_expression()

    if '<symbol> ;' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</letStatement>')

def compile_if ():
    global idx,indentation

    print(' '* indentation +'<ifStatement>',end='')
    indentation += 2

    if '<keyword> if' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<symbol> (' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    if peek_term(idx):
        compile_expression()

    if '<symbol> )' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<symbol> {' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    compile_statements()

    if '<symbol> }' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    if '<keyword> else' in my_list[idx]:
        if '<keyword> else' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1
        if '<symbol> {' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

        compile_statements()

        if '<symbol> }' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</ifStatement>')

def compile_while ():
    global idx,indentation

    print(' '* indentation +'<whileStatement>',end='')
    indentation += 2

    if '<keyword> while' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<symbol> (' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    if peek_term(idx):
        compile_expression()

    if '<symbol> )' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1
    if '<symbol> {' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    compile_statements()

    if '<symbol> }' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</whileStatement>')


def compile_do ():
    global idx,indentation

    print(' '* indentation +'<doStatement>',end='')
    indentation += 2

    if '<keyword> do' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    compile_subroutine_call()

    if '<symbol> ;' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</doStatement>')


def compile_return () :
    global idx,indentation

    print(' '* indentation +'<returnStatement>',end='')
    indentation += 2

    if '<keyword> return' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    if peek_term(idx):
        compile_expression()

    if '<symbol> ;' in my_list[idx]:
        print(' ' * indentation + my_list[idx])
        idx += 1

    indentation -= 2
    print(' '* indentation,end='')
    print('</returnStatement>')


def compile_subroutine_call ():
    global idx,indentation

    if '<identifier>' in my_list[idx] and '<symbol> (' in my_list[idx+1]:
        if '<identifier>' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1
        if '<symbol> (' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

        compile_expression_list()

        if '<symbol> )' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

    ##################################################
    elif '<identifier>' in my_list[idx] and '<symbol> .' in my_list[idx+1]:
        if '<identifier>' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1
        if  '<symbol> .' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1
        if '<identifier>' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1
        if '<symbol> (' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

        compile_expression_list()

        if '<symbol> )' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1


def compile_statements ():
    global idx,indentation

    print(' ' * indentation + '<statements>')
    indentation += 2

    while '<keyword> do' in my_list[idx] or '<keyword> let' in my_list[idx] or '<keyword> if' in my_list[idx] or '<keyword> while' in my_list[idx] or '<keyword> return' in my_list[idx] :

        if '<keyword> do' in my_list[idx]:
            compile_do()
        elif '<keyword> let' in my_list[idx]:
            compile_let()
        elif '<keyword> if' in my_list[idx] :
            compile_if()
        elif '<keyword> while' in my_list[idx] :
            compile_while()
        elif '<keyword> return' in my_list[idx] :
            compile_return()

        if idx >= len(my_list):
            break

    print(' '* indentation,end='')
    print('</statements>')


def compile_expression_list ():
    global idx, indentation

    print(' '* indentation +'<expressionList>',end='')
    indentation += 2

    print(end='\n')
    if peek_term(idx):
        compile_expression()

        while '<symbol> ,' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

            compile_expression()

            if idx >= len(my_list):
                break

    indentation -= 2
    print(' '* indentation,end='')
    print('</expressionList>')



def compile_expression () :
    global  idx,indentation

    print(' '* indentation +'<expression>',end='')
    indentation += 2

    print(end='\n')
    compile_term()

    while peek_op(idx):
        print(' ' * indentation + my_list[idx])
        idx += 1

        compile_term()

        if idx >= len(my_list):
            break

    indentation -= 2
    print(' '* indentation,end='')
    print('</expression>')



def peek_term (para):
    if '<integerConstant>' in my_list[para] or '<stringConstant>' in my_list[para] or '<keyword> true' in my_list[para] or '<keyword> false' in my_list[para] or '<keyword> null' in my_list[para] or '<keyword> this' in my_list[para] or '<identifier>' in my_list[para] or '<symbol> (' in my_list[para] or '<symbol> -' in my_list[para] or '<symbol> ~' in my_list[para] :
       return True
    return False

def peek_op (para):
    if '<symbol> +' in my_list[para] or '<symbol> -' in my_list[para] or '<symbol> *' in my_list[para] or '<symbol> /' in my_list[para] or '<symbol> &' in my_list[para] or '<symbol> |' in my_list[para] or '<symbol> <' in my_list[para] or '<symbol> >' in my_list[para] or '<symbol> =' in my_list[para] :
        return True
    return False

def compile_term ():
    global idx, indentation

    print(' '* indentation +'<term>',end='')
    indentation += 2

    if '<integerConstant>' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    elif '<stringConstant>' in my_list[idx] :
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    elif '<keyword> true' in my_list[idx] or '<keyword> false' in my_list[idx] or '<keyword> null' in my_list[idx] or '<keyword> this' in my_list[idx] :
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    elif '<identifier>' in my_list[idx] and '<symbol> [' in my_list[idx+1]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1
        print(' ' * indentation + my_list[idx])
        idx += 1

        compile_expression()

        if '<symbol> ]' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

    elif ('<identifier>' in my_list[idx] and '<symbol> (' in my_list[idx+1]) or ('<identifier>' in my_list[idx] and '<symbol> .' in my_list[idx+1]):
        print(end='\n')
        compile_subroutine_call()

    elif '<symbol> (' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

        compile_expression()

        if '<symbol> )' in my_list[idx]:
            print(' ' * indentation + my_list[idx])
            idx += 1

    elif '<identifier>' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

    elif '<symbol> -' in my_list[idx] or '<symbol> ~' in my_list[idx]:
        print(end='\n')
        print(' ' * indentation + my_list[idx])
        idx += 1

        compile_term()

    indentation -= 2
    print(' '* indentation,end='')
    print('</term>')


def import_tokens(final):
    global my_list , idx , indentation
    idx = 0
    indentation = 0
    my_list = final





