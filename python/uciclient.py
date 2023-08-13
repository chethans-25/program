import sys
from http.client import HTTPSConnection

host="www.uci.edu"
try:
    conn=HTTPSConnection(host,443)
except:
    print("cant connect")
    sys.exit()
try:
    conn.request("GET /",host)
except:
    print("cant request")
    sys.exit()

res=conn.getresponse()

data=res.readlines(800)

for i in range(3):
    print(data[i])
