mystr = ''
with open("data.html", "r", encoding="utf-8") as fil:
    for line in fil:
        line = line.replace("\"", "'")
        mystr += line

print(mystr)