# 2026-09-29T18:49:51.058951700
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

comp = client.get_component(name="nexys4_microblazeV_2024_2v_0_0_app")
status = comp.clean()

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_0")
status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = comp.clean()

status = comp.clean()

status = platform.build()

comp.build()

vitis.dispose()

