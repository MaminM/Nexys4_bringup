# 2026-09-27T17:41:33.695960100
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

comp = client.clone_component(name="nexys4_microblazeV_UART",new_name="nexys4_microblazeV")

platform = client.get_component(name="nexys4_microblazeV")
status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.3.xsa")

comp = client.get_component(name="nexys4_microblazeV_empty")
status = comp.clean()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

status = comp.clean()

status = platform.build()

comp.build()

