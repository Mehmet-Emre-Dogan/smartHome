import requests
from bs4 import BeautifulSoup
url = "http://192.168.1.101"
html = requests.get(url).content
soup = BeautifulSoup(html, "html.parser")
alar = soup.find_all("a")
for a in alar:
    myStr = a.get("href")
    if "3" in myStr: # Toggle fanlar (pin3)
        requests.get(url + myStr)
    if "4" in myStr: # Toggle laptop soğutucu (pin4)
        requests.get(url + myStr)