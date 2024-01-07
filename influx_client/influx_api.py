import os
from dotenv import load_dotenv
load_dotenv()

import influxdb_client
from influxdb_client.client.write_api import SYNCHRONOUS

bucket = "PotPlant"
org = os.getenv('INFLUX_ORG')
token = os.getenv('INFLUX_TOKEN')
# Store the URL of your InfluxDB instance
url="http://192.168.0.100:8086"

client = influxdb_client.InfluxDBClient(
   url=url,
   token=token,
   org=org
)

write_api = client.write_api(write_options=SYNCHRONOUS)

p = influxdb_client.Point("PlantPot").tag("Plant", "Gummibaum").field("temperature", 25.3).field("hum", 0.5)
write_api.write(bucket=bucket, org=org, record=p)
