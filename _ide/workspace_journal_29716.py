# 2026-09-30T19:38:22.330713600
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

comp = client.get_component(name="nexys4_microbnlazeV_2024_2_v0_2_app")
status = comp.clean()

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_2")
status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_0")
status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.1.xsa")

status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_2024_2v_0_0_app")
comp.build()

vitis.dispose()

vitis.dispose()

