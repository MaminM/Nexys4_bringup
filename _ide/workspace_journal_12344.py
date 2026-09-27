# 2026-06-23T22:14:34.544296100
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

status = client.rescan_embedded_sw_repo()

vitis.dispose()

