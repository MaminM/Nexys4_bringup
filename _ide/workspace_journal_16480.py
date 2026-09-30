# 2026-09-28T23:18:32.018888
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_0")
status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_2024_2v_0_0_app")
comp.build()

status = platform.build()

comp.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.1.xsa")

status = comp.clean()

status = platform.build()

comp.build()

vitis.dispose()

