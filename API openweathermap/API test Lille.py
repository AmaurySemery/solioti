import requests
import json

api_key = "7f9054c4edb12a97316c2da4d6fed6c9"
lat = "50.633333"
lon = "3.066667"
url = "https://api.openweathermap.org/data/2.5/onecall?lat=%s&lon=%s&appid=%s&units=metric" % (lat, lon, api_key)

response = requests.get(url)
data = json.loads(response.text)
print(data)