import requests
from json import load, dump
from datetime import datetime
from time import sleep

path = "E:/Programs/Otomasyon/"

def lock():
    with open(path + "confi-onoff.json", "r", encoding="utf-8") as fil:
        settings = load(fil)
    settings["unlocked"] = 0
    with open(path + "confi-onoff.json", "w", encoding="utf-8") as fil:
        dump(settings, fil)

def unlock():
    with open(path + "confi-onoff.json", "r", encoding="utf-8") as fil:
        settings = load(fil)
    settings["unlocked"] = 1
    with open(path + "confi-onoff.json", "w", encoding="utf-8") as fil:
        dump(settings, fil)

def on():
    with open(path + "confi-onoff.json", "r", encoding="utf-8") as fil:
        settings = load(fil)
    i = 1
    while settings["unlocked"] and i <= settings["numTries"]:
        try:
            requests.get(f"http://192.168.1.101/pin3/on")
            requests.get(f"http://192.168.1.101/pin4/on")
            tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
            with open(path + "LOG-ON.txt", "a", encoding="utf-8") as fil:
                fil.write(f"{tarih} --> {i} denemede başarılı. \n")
            break
        except Exception as ex:
            if "WinError 10060" in str(ex):
                tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
                with open(path + "LOG-ON.txt", "a", encoding="utf-8") as fil:
                    fil.write(f"{tarih} --> {i} denemede BAŞARISIZ: {ex}\n")
                break
            i += 1

    if i > settings["numTries"]:
        tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
        with open(path + "LOG-ON.txt", "a", encoding="utf-8") as fil:
            fil.write(f"{tarih} --> {i} denemede BAŞARISIZ. \n")

    if not settings["unlocked"]:
        tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
        with open(path + "LOG-ON.txt", "a", encoding="utf-8") as fil:
            fil.write(f"{tarih} --> Sistem kilitli olduğu için kod çalışmadı. \n")

def off():
    with open(path + "confi-onoff.json", "r", encoding="utf-8") as fil:
        settings = load(fil)
    i = 1
    while settings["unlocked"] and i <= settings["numTries"]:
        try:
            requests.get(f"http://192.168.1.101/pin3/off")
            requests.get(f"http://192.168.1.101/pin4/off")
            tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
            with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
                fil.write(f"{tarih} --> {i} denemede başarılı. \n")
            break
        except Exception as ex:
            if "WinError 10060" in str(ex):
                tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
                with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
                    fil.write(f"{tarih} --> {i} denemede BAŞARISIZ: {ex}\n")
                break
            
            i += 1

    if i > settings["numTries"]:
        tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
        with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
            fil.write(f"{tarih} --> {i} denemede BAŞARISIZ. \n")

    if not settings["unlocked"]:
        tarih = datetime.now().strftime('%d/%m/%Y %H:%M:%S') 
        with open(path + "LOG-OFF.txt", "a", encoding="utf-8") as fil:
            fil.write(f"{tarih} --> Sistem kilitli olduğu için kod çalışmadı. \n")

tercih = input("1- Off and lock\n2- Unlock and on\n--> ")
if tercih == "1":
    off()
    lock()
elif tercih == "2":
    unlock()
    on()
else:
    print("geçersiz seçim")
    sleep(3)