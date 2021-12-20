import requests
import urllib
import bs4
import re

def visible(element): # we want to get only visible text from website 
    if element.parent.name in ['style', 'script', '[document]', 'head', 'title']: 
        return False 
    if re.match('<!--.*-->', str(element.encode('utf-8'))): 
        return False 
    return True           

def checkURL(url): # function to check correctness of url, copied from stackoverflow 
    regex = re.compile(
            r'^(https?:/)?/'  # http:// or https://
            r'(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\.)+[A-Z]{2,6}\.?|'  # domain...
            r'localhost|'  # localhost...
            r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})' # ...or ip
            r'(?::\d+)?'  # optional port
            r'(?:/?|[/?]\S+)$', re.IGNORECASE)
    return url is not None and regex.search(url)

def get_urls(parent, start_page, distance, visited): # gettin urls
    if not checkURL(start_page) or distance < 0 or start_page in visited:
        return
    
    if start_page[:4] != 'http':
        start_page = urllib.parse.urljoin(parent, start_page)

    visited.add(start_page)

    content = requests.get(start_page).text
    data = bs4.BeautifulSoup(content, 'html.parser')
    links = [link.get('href') for link in data.find_all('a') if link.get('href') is not None and link.get('href') != '']
    
    for l in links:
        get_urls(start_page, l, distance - 1, visited)



def crawl(start_page, distance, action): # main function
    visited = set()
    get_urls(None, start_page, distance, visited)
    print(len(visited))
    for url in visited:
        yield (url, action(url))

def get_sentences(url): # funciton that gets sentences with python from url
    if not checkURL(url):
        return []
    content = requests.get(url).content
    soup = bs4.BeautifulSoup(content, 'html.parser')
    data = soup.findAll(text=True) 
    vis_data = filter(visible, data) 
    result = []
    for e in list(vis_data):
        snts = re.findall(r'([A-Z][^\.!?]*(?i:python)[^\.!?]*[\.!?])', e)
        result.extend(snts)
    return list(result) 



cnt = 0
for (url, out) in crawl('https://sites.google.com/cs.uni.wroc.pl/boehm/python_parsing', 1, get_sentences):
    if cnt > 5:
        break
    cnt += 1
    print(f'\n\n\nURL:\n{url}\nsentences with \'python\':')
    for s in out:
        print(s)
