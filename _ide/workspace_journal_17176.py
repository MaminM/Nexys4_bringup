# 2026-09-29T20:56:53.583075300
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

status = comp.clean()

status = platform.build()

comp.build()

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

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.2.xsa")

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.1.xsa")

platform = client.create_platform_component(name = "nexys4_microblazeV_2024_2_v0_2",hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.2.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="nexys4_microbnlazeV_2024_2_v0_2_app",platform = "$COMPONENT_LOCATION/../nexys4_microblazeV_2024_2_v0_2/export/nexys4_microblazeV_2024_2_v0_2/nexys4_microblazeV_2024_2_v0_2.xpfm",domain = "standalone_microblaze_riscv_0")

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_2")
status = platform.build()

comp = client.get_component(name="nexys4_microbnlazeV_2024_2_v0_2_app")
comp.build()

status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = comp.clean()

status = comp.clean()

status = platform.build()

comp.build()

