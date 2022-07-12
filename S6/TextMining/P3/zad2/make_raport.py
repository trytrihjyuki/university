

from email.mime import base


base_ans = []
good_ans = []
idf_ans = []
questions = []

def read_ans(filename, ans_tab):
    f = open(filename, 'r')
    lines = f.readlines()
    for l in lines:
        ans_tab.append(l)

if __name__ == '__main__':
    read_ans('ans_base.txt', base_ans)
    read_ans('ans_idf.txt', idf_ans)
    read_ans('odpowiedzi.txt', good_ans)
    read_ans('pytania.txt', questions)

    for i in range(len(base_ans)):
        if base_ans[i] != idf_ans[i]:
            print(f'QUESTION: {questions[i]}\nIDF: {idf_ans[i]}\nBASE: {base_ans[i]}\nCORRECT:{good_ans[i]}\n\n')