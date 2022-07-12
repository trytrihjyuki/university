import random

def sample_cite(counter, last_cite, last_cites):
    occurances = counter.most_common()
    weights = [occurances[i][1] for i in range(len(occurances))]
    cites_ids = [occurances[i][0] for i in range(len(occurances))]
    for i, cite_id in enumerate(cites_ids):
        if cite_id == last_cite:
            weights[i] /= 20
        if cite_id in last_cites:
            weights[i] /= 2

    return random.choices(cites_ids, weights=weights)[0]
