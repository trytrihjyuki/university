import random
import requests 

def sentence_end(w):
    end = None
    stop = ['.', '...', '!', '!!!', '?', '?!']
    if len(w) >= 3 and w[-3:] in stop:
        end = w[-3:]
    elif len(w) >= 2 and w[-2:] in stop:
        end = w[-2:]
    elif w[-1:] in stop:
        end = w[-1:]
    return end 
 
def uprosc_zdanie(teskt, max_word_len, max_sentence):
    short_words = []
    endings = []

    for w in teskt.split():
        w_end = sentence_end(w)
        if w_end is not None:
            endings.append(w_end)

        pure_word = ''.join(l for l in w if l.isalnum()).lower()  
        if len(pure_word) <= max_word_len:
            short_words.append((pure_word, len(endings), w_end))

    endings.append('') # in case no puncation ending
    short_words.append(('',-1)) #guard
    out_words = []
    begin = 0
    sentence_id = short_words[0][1]

    for i, (w, end_id, w_end) in enumerate(short_words[:-1]):
        words = [pw for (pw, eid, w_end) in short_words[begin: i+1]]
        words.append('') #guard
        if w_end is not None or sentence_id != end_id or i == len(short_words)-2: 
            num_words = i - begin + 1
            if num_words > max_sentence:
                sample = random.sample(words[:-1], max_sentence)
                first_word = True
                for sw in words[:-1]:
                    if sw in sample:
                        if first_word:
                            out_words.append(sw.capitalize())
                            first_word = False
                        else:
                            out_words.append(sw)
                if i != len(short_words) - 2:
                    print(len(out_words), len(endings), end_id)
                    out_words[-1] += endings[end_id]
            else:
                words[0] = words[0].capitalize()
                out_words.extend(words[:-1])
            begin = i + 1
        sentence_id = end_id

    out_words[0] = out_words[0].capitalize()
    return ' '.join(out_words) + '.'

if __name__ == '__main__':
    tekst = "Podział peryklinalny inicjałów wrzecionowatych \
            kambium charakteryzuje się ścianą podziałową inicjowaną \
            w płaszczyźnie maksymalnej."
    print(uprosc_zdanie(tekst, 10, 5))

    url = 'https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt'
    data = requests.get(url).text
    #print(uprosc_zdanie(data, 10, 8))

