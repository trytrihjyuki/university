from sklearn import neighbors
from tqdm import tqdm
from queue import PriorityQueue
polish_words = set()
visited = dict()
valid = set()

cheap_letters = {'a':'ą', 'ą':'a', 'ć':'c', 'c':'ć', 'ę':'e', 'ę':'e', 'l':'ł', 'ł':'l', 'ń':'n',
                 'n':'ń', 'o':'ó', 'ó':'o', 's':'ś', 'ś':'s', 'z':'ź', 'z':'ż', 'ż':'z', 'ź':'z'}
close_letters = {
    'a': 'zwsedcrf',
    'b': 'edcrftgyhnujm',
    'c': 'qazwsedrftgb',
    'd': 'qazwsecrftgb',
    'e': 'qazwsdcrftgb',
    'f': 'wsedcrtgbyhn',
    'g': 'edcrftbyhnujm',
    'h': 'rftgbynujmik',
    'i': 'yhnujmkopl',
    'j': 'tgbyhnumiklo',
    'k': 'yhnujmiopl',
    'l': 'pyhnujmikopb',
    'm': 'tgbyhnujikolp',
    'n': 'rftgbyhujikmo',
    'o': 'yhnujmiklp',
    'p': 'yhnujimkol',
    'r': 'wsedcftgbyhn',
    's': 'qazwedcrf',
    't': 'edcrfgbyhnujm',
    'u': 'tgbyhnjmikopl',
    'w': 'azwsedcrf',
    'y': 'rftgbhnujmik',
    'q': 'azwsedcrfv',
    'x': 'azwsedcrf',
    'v': 'wsedcrftgbyhn',
    'z': 'awsedcrf'
}
def get_polish_words():
    f = open('polish_words.txt', 'r')
    for l in f.readlines():
        polish_words.add(l.lstrip().rstrip())

def correct(w):
    q = PriorityQueue()
    q.put((0,w))
    while not q.empty():
        global visited
        cost, w = q.get()
        # assert w != 'lokomotywa'
        # print(w, ' ', cost)
        # print(len(set(visited.keys())))
        if cost > 2:
            continue
        if w in visited and visited[w] < cost:
            continue
        visited[w] = cost

        if w.upper() in polish_words:
            return wp, cost

        # delete
        for i in range(len(w)):
            wp = w[:i] + w[i+1:]

            if False and wp.upper() in polish_words:
                return wp, cost + 0.1
            else:
                if i+1 < len(w) and w[i] == w[i+1]:
                    if wp not in visited or visited[w] > cost:
                        visited[wp] = cost + 0.1
                        q.put((cost + 0.1, wp))
                else:
                    if wp not in visited or visited[w] > cost:
                        visited[wp] = cost + 0.4
                        q.put((cost + 0.4, wp))

        # add
        for l in 'aąbcćdeęfghijklłmnoóprsśtuvwxzżź':
            for i in range(len(w)+1):
                wp = w[:i] + l + w[i+1:]

                if False and  wp.upper() in polish_words:
                    return wp, cost + 1.0
                else:
                    if wp not in visited or visited[w] > cost:
                        visited[wp] = cost + 1.0
                        q.put((cost + 1.0, wp))
        # replace
        for i in range(len(w)):
            if w[i] in close_letters:
                for l in close_letters[w[i]]:
                    wp = w[:i] + l + w[i+1:]
                    if False and  wp.upper() in polish_words:
                        print(wp)
                        return wp, cost + 0.2
                    else:
                        if wp not in visited or visited[w] > cost:
                            visited[wp] = cost + 0.2
                            q.put((cost + 0.2, wp))
            else:
                for l in close_letters[cheap_letters[w[i]]]:
                    wp = w[:i] + l + w[i+1:]
                    if False and  wp.upper() in polish_words:
                        print(wp)
                        return wp, cost+0.2
                    else:
                        if wp not in visited or visited[w] > cost:
                            visited[wp] = cost + 0.2
                            q.put((cost + 0.2, wp))

        #swap
        for i in range(len(w)):
            for j in range(i+1, len(w)):
                wp = list(w)
                wp[j], wp[i] = wp[i], wp[j]
                wp = ''.join(wp)
                if False and  wp.upper() in polish_words:
                    return wp, cost+0.1
                else:
                    if wp not in visited or visited[w] > cost:
                        visited[wp] = cost + 0.1
                        q.put((cost + 0.1, wp))

        # alt + or -
        for i in range(len(w)):
            if w[i] in cheap_letters:
                wp = w[:i] + cheap_letters[w[i]] + w[i+1:]
                if False and  wp.upper() in polish_words:
                    return wp, cost + 0.15
                else:
                    if wp not in visited or visited[w] > cost:
                        visited[wp] = cost + 0.15
                        q.put((cost + 0.15, wp))

if __name__ == '__main__':
    get_polish_words()
    print('Loaded polish words!')
    score = 0.0 
    f = open('literowki1.txt', 'r')
    words = [l.lstrip().rstrip().split(' ') for l in f.readlines()]
    for w_correct, w in tqdm(words):
        cand, cost = correct(w)
        # cand = min(valid, key = lambda x: x[1]) if len(valid) else (None,None)
        if score:
            break
        if cand == w_correct:
            score += 1
        #     print('gituwa')
        # else:
        #     print('lipa')
        # print(cand,' vs. ', w_correct)
        # print(f'cost: {cost}')
        visited = dict()
        valid = set()
    
    print(f'Score: {score/len(words)}')