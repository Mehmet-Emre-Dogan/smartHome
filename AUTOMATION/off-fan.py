import requests
from json import load
from datetime import datetime

path = "E:/Programs/Otomasyon/" # Put your path where you copied the codes

with open(path + "confi-onoff.json", "r", encoding="utf-8") as fil:
    settings = load(fil)
i = 1
while settings["unlocked"] and i <= settings["numTries"]:
    try:
        requests.get(f"http://192.168.1.101/pin3/off") # Change your powerbox's IP address if it is different
        requests.get(f"http://192.168.1.101/pin4/off")

        cutomDT = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
        with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
            fil.write(f"{cutomDT} --> success at {i} tries \n")
        break
    except:
        i += 1

if i > settings["numTries"]:
    cutomDT = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
    with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
        fil.write(f"{cutomDT} --> FAIL at {i} tries. \n")

if not settings["unlocked"]:
    cutomDT = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
    with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
        fil.write(f"{cutomDT} --> Autorun is locked. \n")
