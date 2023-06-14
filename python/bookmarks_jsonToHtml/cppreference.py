import requests
from bs4 import BeautifulSoup
import re

if __name__ == '__main__':
    url = 'https://en.cppreference.com/w/cpp/symbol_index'
    page = requests.get(url)
    soup = BeautifulSoup(page.text, 'html.parser')
    links = soup.find_all('a')
    for link in links:
        # print(link.get("href"), link.get_text(""))
        if link.get("href") != None and re.match(r"^/w/", link.get("href")) is not  None:
            print(f'<DT><A HREF="https://en.cppreference.com/{link.get("href")}" TAGS="cpp">{link.get_text("").replace("()","").replace("<>","")}</A>')

