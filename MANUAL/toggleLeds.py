import requests
from bs4 import BeautifulSoup
url = "http://192.168.1.101"
html = requests.get(url).content
soup = BeautifulSoup(html, "html.parser")
alar = soup.find_all("a")
for a in alar:
    myStr = a.get("href")
    if "1" in myStr: # Toggle uzun led (pin1)
        requests.get(url + myStr)
    if "2" in myStr: # Toggle kısa led (pin2)
        requests.get(url + myStr)