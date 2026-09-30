# 2026-09-28T01:31:50.095902500
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

comp = client.get_component(name="nexys4_microblazeV_empty")
status = comp.clean()

platform = client.get_component(name="nexys4_microblazeV")
status = platform.build()

comp.build()

vitis.dispose()

