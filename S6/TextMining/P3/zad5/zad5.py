from tqdm import tqdm
from random import sample

errors = []
one_grams = {}

def read_2grams():
    with open('2grams') as file:
        for line in tqdm(file, total=75395184):
            w1, w2 = line.lstrip().rstrip().split(' ')[1:]
            no_space = w1+w2
            if no_space in one_grams and one_grams[no_space] > 65 and len(w1) > 2 and len(w2) > 2:
                errors.append((no_space,(w1, w2)))
            if len(errors) > 10000:
                break

def read_1grams():
    f = open('1grams', 'r')
    lines = f.readlines()
    for l in lines:
        cnt, w = l.lstrip().rstrip().split(' ')
        one_grams[w] = int(cnt)

if __name__ == '__main__':
    read_1grams()
    print('READ 1GRAMS!')
    read_2grams()
    print(len(errors))
    for err in sample(errors, 2000):
        print(f'{err[0]} ≈ {err[1][0]} + {err[1][1]}')
