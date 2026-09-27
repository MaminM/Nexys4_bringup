# 2026-09-27T11:29:44.622880700
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

comp = client.get_component(name="nexys4_microblazeV_empty")
comp.set_app_config(key = "USER_INCLUDE_DIRECTORIES", values = ["C:/Users/mamin/Documents/GitHub/Nexys4_bringup/nexys4_microblazeV"])

comp.set_app_config(key = "USER_INCLUDE_DIRECTORIES", values = [""])

comp.set_app_config(key = "USER_INCLUDE_DIRECTORIES", values = [""])

comp.set_app_config(key = "USER_INCLUDE_DIRECTORIES", values = ["C:/Users/mamin/Documents/GitHub/Nexys4_bringup/nexys4_microblazeV/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/libsrc/gpio/src"])

comp.set_app_config(key = "USER_INCLUDE_DIRECTORIES", values = [""])

comp.set_app_config(key = "USER_LINK_LIBRARIES", values = [""])

