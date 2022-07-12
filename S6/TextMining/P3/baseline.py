import wikipedia
import spacy
import editdistance
from itertools import product

wikipedia.set_lang("pl")


def search_titles(query):
    return list(wikipedia.search(query))

spacy_model = spacy.load("pl_core_news_sm")


def scaled_editdist(ans, cor):
    ans = ans.lower()
    cor = cor.lower()
    
    return editdistance.eval(ans, cor) / len(cor)

def answer(question):
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
    for q in open("pytania.txt"):   
        q = q.strip()
        print (q)
        print (answer(q))
        print ()

