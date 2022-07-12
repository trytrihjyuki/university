import wikipedia
import spacy
import editdistance
from itertools import product
import random
import re
import time
from gensim.models import KeyedVectors
from collections import defaultdict, Counter
import numpy as np

N_lemmas = 309280
N_docs = 495473

lemma_dict = dict() # word - > lemma
index = defaultdict(set) # lemma -> sets[defs]
global_occurances = defaultdict(lambda: 0) # lemma -> global occurance
docs_lemmas = [] # id -> lemma occurance of document
lemmas = set() # set of all lemmas
words = set() # set of all words
titles = [] # id -> title
idfs = dict() # lemma -> idf

last_cite = -1
last_cites = []

wikipedia.set_lang("pl")
word2vec = KeyedVectors.load("word2vec_100_3_polish.bin")


def search_titles(query):
    return list(wikipedia.search(query))

spacy_model = spacy.load("pl_core_news_sm")


def scaled_editdist(ans, cor):
    ans = ans.lower()
    cor = cor.lower()
    
    return editdistance.eval(ans, cor) / len(cor)
### PREPROCESSING ###

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
                docs_lemmas.append([])
                titles.append(title)
                for word in definition: # index definitions
                    if len(word) <= 1:
                        continue
                    lemma = get_lemma(word)
                    if lemma is not None:
                        index[lemma].add(CNT)
                        docs_lemmas[CNT].append(lemma)
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

def get_lemmas(words):
    lemmas = []
    for word in words:
        if len(word) <= 1:
            continue
        lemma = get_lemma(word)
        if lemma is not None:
            lemmas.append(lemma)
    return lemmas

def get_vector(lemmas):
    vec = np.zeros(100)
    # print(lemmas)
    for lemma in lemmas:
        if lemma in word2vec:
            vec += word2vec[lemma]
    return vec

def get_defs_vectors(lemmas):
    docs = set()
    for l in set(lemmas):
        docs |= index[l]
    defs_scores = np.zeros((len(docs), 100))
    id_to_doc = dict()
    for i,d in enumerate(docs):
        defs_scores[i] = get_vector(docs_lemmas[d])
        id_to_doc[i] = d
    return id_to_doc, defs_scores

def find_similar_def(definition): # P4.2 b)
    start = time.time()
    lemmas = get_lemmas(definition)
    v = get_vector(lemmas)
    id_to_doc, defs_vectors = get_defs_vectors(lemmas)
    cos_distances = defs_vectors@v # ZA DUŻO PAMIĘCI :c
    end = time.time()
    return id_to_doc[cos_distances.argmax()]


def answer(question):
    definition = get_definition(question)
    if definition:
        return titles[find_similar_def(definition)]
    if question[:3] == 'Czy':
        return 'Tak'
    sm = spacy_model(question)
    question_tokens = [token for token in sm if len(token) > 1]
    while question_tokens:
        query = ' '.join(q.text for q in question_tokens)
        search_results = search_titles(query)

        for result in search_results:
            res_tokens = spacy_model(result)

            for t1, t2 in product(res_tokens, question_tokens):                
                if scaled_editdist(t1.text, t2.text) <= 0.5:
                    break
            else:
                paren_index = result.find('(')
                if paren_index != -1:
                    result = result[:paren_index]
                return result

        # if answer not found, remove first token of query
        del question_tokens[0]
    return 'nie mam pojęcia, sorry'


if __name__ == '__main__':
    create_lemma_dict()
    lemmas = set(lemma_dict.values())
    words = set(lemma_dict.keys())
    process_definitions()
    calculate_idfs()
    for q in open("pytania.txt"):   
        q = q.strip()
        print (answer(q))

# if __name__ == '__main__':
#     word2vec = KeyedVectors.load("word2vec_100_3_polish.bin")
#     print(word2vec.similar_by_word("bierut"))
#     print(word2vec['auto'])