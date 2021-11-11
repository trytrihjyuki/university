import string
import requests

def dekompresja(compressed):
    stop = string.punctuation
    txt = ""
    for n, l in compressed:
        txt += n*l
        if l in stop:
            txt += ' '

    return txt


def kompresja(txt):
    compressed = []
    for w in txt.split():
        i = 0
        w += '$' # guard $ sign is excluded
        while i < len(w) - 1:
            cnt = 0
            while i < len(w) - 1 and w[i] == w[i+1]:
                i+=1
                cnt+=1
            if i < len(w) - 1:
                compressed.append((cnt+1, w[i]))
            else:
                compressed.append((cnt+1, w[i-1]))
            i+=1
        compressed.append((1, ' '))

    return compressed







if __name__ == '__main__':
    txt = 'sieeeeeeeeeeemanko, co tam uu ciebieee słyychać???'
    print(kompresja(txt))
    print(dekompresja(kompresja(txt)))

    url = 'https://wolnelektury.pl/media/book/txt/pan-tadeusz.txt'
    data = requests.get(url).text
    #print(kompresja(data))
    #print(dekompresja(kompresja(data)))
