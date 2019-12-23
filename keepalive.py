
import requests
import time
import sys

url = "http://34.94.3.143/dcf00e6075/"

while True:
	r = requests.get(url)
	if r.status_code == 200:
		print("Pinged, instance alive")
		time.sleep(10*60)
	elif r.status_code == 404:
		print("Pinged, dead")
		print("Exiting...")
		sys.exit(1)
	else:
		print("Pinged, unknown response received: " + r.status_code)
		print("Exiting...")
		sys.exit(1)
