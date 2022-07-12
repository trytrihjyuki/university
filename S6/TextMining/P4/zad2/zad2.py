import random
import re
import time
from collections import defaultdict, Counter
import numpy as np

N_lemmas = 309280
N_docs = 495473

lemma_dict = dict() # word - > lemma
index = defaultdict(set) # lemma -> sets[defs]
global_occurances = defaultdict(lambda: 0) # lemma -> global occurance
docs_lemmas_occurances = [] # id -> lemma occurance of document
lemmas = set() # set of all lemmas
words = set() # set of all words
titles = [] # id -> title
idfs = dict() # lemma -> idf

last_cite = -1
last_cites = []

#### PREPROCESSING ###

def read_file(file_name):
    f = open(file_name, 'r')
    lines = f.readlines()
    return lines

def create_lemma_dict():
    global lemma_dict
    lines = read_file('formy.txt')
    for l in lines:
        if ' ' not in l:
            lemma, word = l.split(';')
            word = word.rstrip()
            lemma_dict[word] = lemma

def get_lemma(word):
    global lemma_dict
    global words
    if word in words:
        return lemma_dict[word]
    elif word.title() in words:
        return lemma_dict[word.title()]
    elif word.lower() in words:
        return lemma_dict[word.lower()]
    return None

def calculate_idfs():
    for l in lemmas:
        idfs[l] = np.log(N_docs / (global_occurances[l]+1e-9))

def process_definitions():
    lines = read_file('poczatki_wikipediowe.txt')
    CNT = 0
    for i in range(0,len(lines),3):
        title = lines[i].rstrip("\n")
        title = title[4:]
        definition = lines[i+1].rstrip("\n") # remove newline
        title = re.sub(r'\([^)]*\)', '', title) # remove text in brackets
        title = title.rstrip()
        if 'Kategoria' in title or 'Szablon' in title or 'Wikipedia' in title:
            continue
        for j in range(len(definition)):
            if definition[j] == '-':
                definition = definition[j+1:]
                break
            elif definition[j] == '–':
                definition = definition[j+1:]
                break
        if title:
            definition = re.sub("-"," ", definition)
            definition = re.sub("[^a-zA-Z0-9 ,AaĄąBbCcĆćDdEeĘęFfGgHhIiJjKkLlŁłMmNnŃńOoÓóPpRrSsŚśTtUuWwYyZzŹźŻż]+", "", definition) # delete non alphabet chars
            definition = re.findall(r"[\w']+|[,]", definition)
            if len(definition) > 3:
                docs_lemmas_occurances.append(defaultdict(lambda: 0))
                titles.append(title)
                for word in definition: # index definitions
                    if len(word) <= 1:
                        continue
                    lemma = get_lemma(word)
                    if lemma is not None:
                        index[lemma].add(CNT)
                        docs_lemmas_occurances[CNT][lemma] += 1
                        global_occurances[lemma] += 1
                CNT+=1

#### END OF PREPROCESSING ###

def get_definition(question): # P4.2 a)
    question = question.rstrip()
    question = re.sub(r'[^\w\s]','',question)
    question = question.split(' ')
    if question[0] == 'Jak' and get_lemma(question[1]) == 'nazywać': # jak nazywać OPTIONAl["się"]
        if question[2] == 'się':
           return question[3:]
        else:
            return question[2:]
    elif question[0] == 'Jak' and question[1] == 'w' and \
          get_lemma(question[3]) == 'nazywać' and question[4] == 'się': # jak w [DZIEDZINA] nazywa się
        if question[2] == 'się':
           return question[3:]
        else:
            return question[2:]    
    elif question[0] == 'Jak' and get_lemma(question[1]) == 'mieć' \
         and question[2] == 'na' and question[3] == 'imię': # jak mieć na imię
       return question[4:]
    return ''

def get_lemmas_occurances(words):
    lemmas_occurances = defaultdict(lambda: 0)
    for word in words:
        if len(word) <= 1:
            continue
        lemma = get_lemma(word)
        if lemma is not None:
            lemmas_occurances[lemma] += 1
    return lemmas_occurances

def get_vector(lemmas_occurances, enum_lemma, idf=False):
    vec = np.zeros(len(enum_lemma.keys()))
    for lemma in lemmas_occurances:
        if lemma in enum_lemma:
            vec[enum_lemma[lemma]] = np.log10(lemmas_occurances[lemma]) + 1.0
            if idf:
                vec[enum_lemma[lemma]] *= idfs[lemma]
    return vec / np.sqrt((vec**2).sum())

def get_defs_vectors(lemmas, enum_lemma):
    docs = set()
    for l in lemmas:
        print(f'[{l}]', ':', len(index[l]))
        docs |= index[l]
    defs_scores = np.zeros((len(docs), len(enum_lemma.keys())))
    id_to_doc = dict()
    for i,d in enumerate(docs):
        defs_scores[i] = get_vector(docs_lemmas_occurances[d], enum_lemma, False)
        id_to_doc[i] = d
    return id_to_doc, defs_scores

def find_similar_def(definition): # P4.2 b)
    start = time.time()
    lemmas_occurances_def = get_lemmas_occurances(definition)
    lemmas = set(lemmas_occurances_def.keys())
    enum_lemma = {l: i for i,l in enumerate(lemmas)}
    v = get_vector(lemmas_occurances_def, enum_lemma, True)
    id_to_doc, defs_vectors = get_defs_vectors(lemmas, enum_lemma)
    cos_distances = defs_vectors@v # ZA DUŻO PAMIĘCI :c
    end = time.time()
    print('Finished query with time: ', end-start)
    return id_to_doc[cos_distances.argmax()]

def process_questions():
    print('Answering definition questions:')
    questions = read_file('pytania.txt')
    for q in questions:
        definition = get_definition(q)
        if definition:
            print('question: ', q)
            print('definition: ', ' '.join(definition))
            print('answer:' ,titles[find_similar_def(definition)],'\n')

if __name__ == '__main__':
    create_lemma_dict()
    lemmas = set(lemma_dict.values())
    words = set(lemma_dict.keys())
    process_definitions()
    calculate_idfs()
    print('Preprocessing done!')
    print(len(lemmas))
    print(len(titles))
    process_questions()