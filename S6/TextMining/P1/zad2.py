import unicodedata
from collections import defaultdict as dd

from sklearn.cluster import KMeans
import numpy as np

f = open("znaki_wikipedii.txt", 'r')
chars = f.read().split()

cat = dd(list)

for r in chars:
    cat[unicodedata.category(r)].append(r)


lower_unicode = np.array([[ord(c)] for c in cat['Ll']])
upper_unicode = np.array([[ord(c)] for c in cat['Lu']])


num_clusters = 11

kmeans_l = KMeans(num_clusters, max_iter=500).fit(lower_unicode)
clusters = {i: [] for i in range(num_clusters)}
for i, label in enumerate(kmeans_l.labels_):
    clusters[label].append(chr(lower_unicode[i][0]))

for label in range(num_clusters):
    print(label,':', clusters[label],'\n')
