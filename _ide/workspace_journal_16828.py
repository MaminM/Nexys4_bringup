# 2026-09-27T13:16:41.375447300
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

platform = client.get_component(name="nexys4_microblazeV")
status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_empty")
comp.build()

component = client.get_component(name="nexys4_microblazeV_empty")

lscript = component.get_ld_script(path="C:\Users\mamin\Documents\GitHub\Nexys4_bringup\nexys4_microblazeV_empty\src\lscript.ld")

lscript.regenerate()

vitis.dispose()

