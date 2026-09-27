# 2026-06-24T18:15:58.122707800
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

component = client.get_component(name="nexys4_uart")

lscript = component.get_ld_script(path="C:\Users\mamin\Documents\GitHub\Nexys4_bringup\nexys4_uart\src\lscript.ld")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

lscript.regenerate()

lscript.add_memory_region("new_memory_0", "0x0000", "0x8000")

