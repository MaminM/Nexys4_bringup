# 2026-06-23T22:57:53.122821500
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

vitis.dispose()

