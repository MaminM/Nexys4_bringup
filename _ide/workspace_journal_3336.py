# 2026-09-27T14:13:42.775140200
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

vitis.dispose()

