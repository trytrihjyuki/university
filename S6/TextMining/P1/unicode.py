import unicodedata
from collections import defaultdict as dd 

txt = ".,‹›«»~{}⟨⟩…©§€£„”-–¿αξłAa갢½∞⩽123Ω$%abcABC🌟"

cat = dd(list)

for r in txt:
    cat[unicodedata.category(r)].append(r)

for c in cat:
    print (c+':', ' '.join(cat[c]))

