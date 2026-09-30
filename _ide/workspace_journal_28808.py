# 2026-09-28T18:12:53.723881300
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

client.delete_component(name="nexys4_microblazeV_v0_1")

client.delete_component(name="nexys4_microblazeV_UART")

client.delete_component(name="nexys4_uart")

client.delete_component(name="nexys4_microblazeV_v0_1_app")

platform = client.create_platform_component(name = "nexys4_microblazeV_2024_2_v0_0",hw_design = "$COMPONENT_LOCATION/../Vivado_2024_2/nexys4_microblazeV_2024_2_v0.0.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="nexys4_microblazeV_2024_2v_0_0_app",platform = "$COMPONENT_LOCATION/../nexys4_microblazeV_2024_2_v0_0/export/nexys4_microblazeV_2024_2_v0_0/nexys4_microblazeV_2024_2_v0_0.xpfm",domain = "standalone_microblaze_riscv_0")

platform = client.get_component(name="nexys4_microblazeV_2024_2_v0_0")
status = platform.build()

comp = client.get_component(name="nexys4_microblazeV_2024_2v_0_0_app")
comp.build()

status = platform.build()

comp.build()

