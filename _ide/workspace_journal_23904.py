# 2026-06-23T23:27:21.985822500
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

vitis.dispose()

