# 2026-06-24T00:02:24.044114200
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

vitis.dispose()

