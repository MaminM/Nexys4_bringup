# 2026-09-29T01:20:01.745838
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_0")
status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_2024_2v_0_0_app")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

