import re

LOOK_AFTER = 4

def read_file():
    f = open("poczatki_wikipediowe.txt", 'r')
    lines = f.readlines()
    return lines

def get_synonyms(lines):
    synonyms = []
    for i in range(0,len(lines),3):
        title = lines[i].rstrip("\n")
        title = title[4:]
        definition = lines[i+1].rstrip("\n") # remove newline
        title = re.sub(r'\([^)]*\)', '', title) # remove text in brackets
        title = title.rstrip()
        definition = re.sub("[^a-zA-Z0-9 ,AaĄąBbCcĆćDdEeĘęFfGgHhIiJjKkLlŁłMmNnŃńOoÓóPpRrSsŚśTtUuWwYyZzŹźŻż]+", "", definition) # delete non alphabet chars
        definition = re.findall(r"[\w']+|[,]", definition)
        synonym = find_synonym(title, definition)
        if synonym is not None:
            synonyms.append((title, clean_synonym(title, synonym), definition))

    return synonyms

def clean_synonym(word, synonym):
    noise = word.split() + [',', 'to' ,'w', 'od']
    synonym_s = synonym.split()
    synonym_s = [w for w in synonym_s if w not in noise]
    return ' '.join(synonym_s)



def find_synonym(word, definition):
    translate_words = ['gr', 'ang', 'łac', 'ros']
    start_words = ['lub', 'inaczej', ',', 'także', 'rzadziej', 'oficjalnie']
    ban_words = ['wieś', 'rzeka', 'miasto', 'zm', 'ur', 'miasteczko', 'hala', 'wzgórze', 'góra', 'wzniesienie'\
                 'pomnik', 'meczet', 'imię', 'flaga', 'herb', 'godło']
    word_s = word.split()
    for w in definition:
        if w.lower() in ban_words:
            return None

    num_of_segments = len(word_s)
    if num_of_segments > 1:
        last_part = word_s[-1]
    else:
        last_part = word
        num_of_segments = 2

    if last_part not in definition:
        return None

    pos = definition.index(last_part)
    pass_translation = 0
    for i in range(pos, min(len(definition), pos + LOOK_AFTER + 2), 1):
        if definition[i] in start_words and i+1 < len(definition) and pass_translation == 0:
            if definition[i] == ',' and definition[i+1] in translate_words:
                if definition[i+1] == 'ang' or definition[i+1] == 'łac':
                    pass_translation = num_of_segments
            else:
                synonym = ''
                for j in range(i+1, min(i + num_of_segments + 4, len(definition))):
                    if j-i <= num_of_segments or definition[j] in word_s:
                        synonym += definition[j] + ' '
                if synonym == '':
                    return None
                return synonym
        else:
            pass_translation = max(pass_translation - 1, 0)

    return None

def print_synonyms(synonyms, good_synonyms=None, print_def=True):
    for t, s, d in synonyms:
        if good_synonyms is not None and t in good_synonyms:
            print(t,' <=> ', s)
            if print_def:
                print('def: \n', d, '\n')
            else:
                print('\n')


if __name__ == '__main__':
    good_synonyms = ['Małżeństwo otwarte', 'narzędziownia', 'Opowieść transmedialna', 'Fermentor', 'Masturbacja',
                 'Alternatywa', 'Anarchizm', 'Alleny', 'Astma oskrzelowa', 'Alergia', 'Akcydens', 'Parser',
                 'Antonim', 'Błona komórkowa', 'Bobina', 'Brutto', 'Elektron', 'Epos', 'Eksperyment',
                 'Flauta', 'Fraszka', 'Glukoza', 'Grupa etniczna', 'Gestapo', 'Gra fabularna', 'Cedzak',
                 'Hipoteza', 'Kubryk', 'Konkubinat', 'Algorytm symetryczny', 'Karta dziurkowana', 'Litosfera',
                ]
    lines = read_file()
    print('Read file')
    synonyms = get_synonyms(lines)
    print('Got synonyms list. Printing results:\n')
    print_synonyms(synonyms, good_synonyms, False)

