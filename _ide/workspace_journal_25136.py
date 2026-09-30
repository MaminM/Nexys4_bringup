# 2026-09-28T18:01:59.165418500
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

vitis.dispose()

