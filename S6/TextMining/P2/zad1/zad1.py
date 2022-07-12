import random
import re
import time
from collections import defaultdict, Counter

lemma_dict = dict() # word - > lemma
index = defaultdict(set) # lemma -> list[cite]
lemmas = set() # set of all lemmas
words = set() # set of all words
cites = list()

context_words = ['on', 'ona', 'ono', 'go', 'jej', 'jego']
last_cite = -1
last_cites = []

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

def read_and_split_cites():
    global cites
    lines = read_file('cytaty.txt')
    for l in lines:
        l = l[2:]
        l = re.sub('&lt;br /&gt;[0-9]*.', ' ', l)
        l = l.lstrip().rstrip()
        l = re.split('[!;?.]', l)
        for cite in l:
            process_cite(cite)

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

def process_cite(cite):
    cite = re.sub(r'[^\w\s]','',cite)
    cite = cite.split(' ')
    cite = [w for w in cite if w != '' ]
    global cites
    cite_num = len(cites)
    cites.append(' '.join(cite))
    for word in cite:
        if len(word) <= 1:
            continue
        lemma = get_lemma(word)
        if lemma is not None and cite_num not in index[lemma]:
            index[lemma].add(cite_num)

def sample_cite(counter):
    occurances = counter.most_common()
    occurances = [(w, (o-0.9)**10) for w,o in occurances]
    weights = [occurances[i][1] for i in range(len(occurances))]
    cites_ids = [occurances[i][0] for i in range(len(occurances))]
    for i, cite_id in enumerate(cites_ids):
        global last_cite
        if cite_id == last_cite:
            weights[i] /= 1000000000
        global last_cites
        if cite_id in last_cites:
            weights[i] /= 2

    return random.choices(cites_ids, weights=weights)[0]

def get_some_cite(phrase):
    phrase = phrase.split(' ')
    cites_ids = list()
    used_lemmas = set()
    for word in phrase:
        print(f'word:{word}')
        lemma = get_lemma(word)
        if len(word) > 1 and lemma is not None and lemma not in used_lemmas:
            used_lemmas.add(lemma)
            print(f'lemma:{lemma}')
            if word is not None and len(word) > 1 and lemma not in context_words:
                cites_ids.extend(list(index[lemma]))
    if len(cites_ids) == 0:
        print('[-] GENERAL CITE!')
        return get_some_cite('generalnie myślę że')

    counter = Counter(cites_ids)
    return sample_cite(counter)
        

if __name__ == '__main__':
    create_lemma_dict()
    lemmas = set(lemma_dict.values())
    words = set(lemma_dict.keys())
    read_and_split_cites()
    print('Preprocessing done!')
    while True:
        print('Write phrase:')
        phrase = input()
        cite_id = get_some_cite(phrase)
        print(f'\n\ndebug:\nlast_cite: {last_cite}\nlast_cites: {last_cites}\n')
        last_cite = cite_id
        last_cites.append(cite_id)
        print(f'ANS: {cites[cite_id]}')
        print(f'\n\ndebug:\nlast_cite: {last_cite}\nlast_cites: {last_cites}\n')
