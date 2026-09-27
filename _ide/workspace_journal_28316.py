# 2026-09-27T14:14:57.619787100
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

platform = client.get_component(name="nexys4_microblazeV")
status = platform.build()

status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_empty")
comp.build()

component = client.get_component(name="nexys4_microblazeV_empty")

lscript = component.get_ld_script(path="C:\Users\mamin\Documents\GitHub\Nexys4_bringup\nexys4_microblazeV_empty\src\lscript.ld")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.1.xsa")

status = platform.build()

comp.build()

lscript.regenerate()

status = comp.clean()

status = platform.build()

comp.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.2.xsa")

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.2.xsa")

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.3.xsa")

status = comp.clean()

status = platform.build()

comp.build()

lscript.regenerate()

client.delete_component(name="nexys4_microblazeV")

client.delete_component(name="componentName")

vitis.dispose()

