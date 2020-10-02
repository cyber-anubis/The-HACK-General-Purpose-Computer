from pathlib import Path
import sys
import os
import tokenizer
import engine



if len(sys.argv) != 2 :
    print('[+] Error: Need exactly one argument')
else :
    raw_string = r'{}'.format(sys.argv[1])
    p = Path(raw_string)

    if p.is_file() :
        f = open(p)
        lines = f.readlines()

        out_file = raw_string[:-5]
        out_file += '.xml'
        
        sys.stdout = open(out_file, 'w')

        tokens = tokenizer.start_tokenizing(lines)
       
        engine.import_tokens(tokens)
        engine.compile_class()

    elif p.is_dir() :
        for separate_file in os.listdir(p):
            if separate_file[-5:] == '.jack':
                dummy_path = Path(Path(raw_string)/separate_file)
                f = open(str(dummy_path))
                lines = f.readlines()

                out_file = str(dummy_path)[:-5]
                out_file += '.xml'
                sys.stdout = open(out_file, 'w')

                tokens = tokenizer.start_tokenizing(lines)
                engine.import_tokens(tokens)
                engine.compile_class()

