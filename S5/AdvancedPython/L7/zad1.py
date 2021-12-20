import requests
import threading
import bs4
import re

visited = set()

class Crawler(threading.Thread):
    def __init__(self, url, curr_distance, max_distance):
        self.active = True if curr_distance < max_distance else False
        self.url = url
        self.curr_distance = curr_distance
        self.max_distance = max_distance

        threading.Thread.__init__(self)

    def run(self):
        global visited
        if not checkURL(self.url) or self.curr_distance < 0 or self.url in visited:
            return
        visited.add(self.url)

        content = requests.get(self.url).text
        data = bs4.BeautifulSoup(content, 'html.parser')
        links = [link.get('href') for link in data.find_all('a') if link.get('href') is not None and link.get('href') != '']
        
        cs = []
        for l in links:
            cs.append(Crawler(l, self.curr_distance - 1, self.max_distance))
        for c in cs:
            c.start()
        for c in cs:
            c.join()


def visible(element): # we want to get only visible text from website 
    if element.parent.name in ['style', 'script', '[document]', 'head', 'title']: 
        return False 
    elif re.match('<!--.*-->', str(element.encode('utf-8'))): 
        return False 
    return True           

def pythonic(element):
    return re.search(r'python', element, flags=re.IGNORECASE) is not None

def checkURL(url): # function to check correctness of url, copied from stackoverflow 
    regex = re.compile(
            r'^https?://'  # http:// or https://
            r'(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\.)+[A-Z]{2,6}\.?|'  # domain...
            r'localhost|'  # localhost...
            r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})' # ...or ip
            r'(?::\d+)?'  # optional port
            r'(?:/?|[/?]\S+)$', re.IGNORECASE)
    return url is not None and regex.search(url)


def crawl(start_page, distance, action): # main function
    starter = Crawler(start_page, distance, distance)
    starter.start()
    starter.join()
    global visited
    for url in visited:
        yield (url, action(url))

def get_sentences(url): # funciton that gets sentences with python from url
    if not checkURL(url):
        return []
    content = requests.get(url).content
    soup = bs4.BeautifulSoup(content, 'html.parser')
    data = soup.findAll(text=True) 
    vis_data = filter(visible, data) 
    result = filter(pythonic, vis_data)
    return list(result) 

if __name__ == '__main__':
    cnt = 0
    for (url, out) in crawl('https://docs.python.org/3/', 1, get_sentences):
        if cnt > 5:
            break
        cnt += 1
        print(f'\n\n\nURL:\n{url}\nsentences with \'python\':')
        for s in out:
            print(s)
