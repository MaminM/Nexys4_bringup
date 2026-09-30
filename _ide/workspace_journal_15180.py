# 2026-09-28T16:31:29.688040
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

platform = client.get_component(name="nexys4_microblazeV")
status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.3.xsa")

platform = client.create_platform_component(name = "nexys4_microblazeV_v0_1",hw_design = "$COMPONENT_LOCATION/../Vivado/nexys4_microblazeV_v0.3.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.get_component(name="nexys4_microblazeV_empty")
comp.build()

comp.build()

client.delete_component(name="nexys4_microblazeV_empty")

comp = client.create_app_component(name="nexys4_microblazeV_v0_1_app",platform = "$COMPONENT_LOCATION/../nexys4_microblazeV_v0_1/export/nexys4_microblazeV_v0_1/nexys4_microblazeV_v0_1.xpfm",domain = "standalone_microblaze_riscv_0")

platform = client.get_component(name="nexys4_microblazeV_v0_1")
status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_v0_1_app")
comp.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.0.xsa")

status = comp.clean()

vitis.dispose()

