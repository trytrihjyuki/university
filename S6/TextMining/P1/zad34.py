import nltk
import unicodedata
import string
from spacy.lang.pl import Polish


nltk.download('punkt')

nlp = Polish()
def read_file():
    f = open("cytaty.txt", 'r')
    lines = f.readlines()
    return lines

def clean_word(word):
    i = 0
    prefix = ''
    suffix = ''
    if word[-1:] == '\n':
        word = word[:-1]

    while i < len(word) and unicodedata.category(word[i])[0] == 'P':
        prefix += word[i]
        i+=1

    if len(word) == len(prefix):
        return [word]

    word = word[i:]
    j = len(word) - 1
    while j >= 0 and unicodedata.category(word[j])[0] == 'P':
        suffix += word[j]
        j-=1
    word = word[:j+1]

    ans = []
    for w in [prefix, word, suffix[::-1]]:
        w = [c for c in w if unicodedata.category(c)[0] != 'Z' ]
        w = ''.join(w)
        if w != '':
            ans.append(w)

    return ans


def tokenize(row):
    tokens = []
    curr_word = ''
    for c in row:
        if c == ' ':
            if curr_word != '':
                tokens.extend(clean_word(curr_word))
                curr_word = ''
        else:
            curr_word += c
    if curr_word != '':
        tokens.extend(clean_word(curr_word))
    return tokens


def process(print_diff=True):
    lines = read_file()
    for i, l in enumerate(lines):
        row = tokenize(l)
        nltk_tokens  = nltk.word_tokenize(l)
        spacy_tokens = nlp(l)
        spacy_tokens = [token.text for token in spacy_tokens]
        if (print_diff and set(nltk_tokens) != set(row)) or not print_diff:
            print('og: ',l)
            print('our tokens: ',row)
            print('nltk tokens: ',nltk_tokens)
            print('spacy tokens:', spacy_tokens,'\n')

process()