# 2026-06-24T13:52:15.648309700
import vitis

client = vitis.create_client()
client.set_workspace(path="Nexys4_bringup")

platform = client.create_platform_component(name = "microblazeV",hw_design = "$COMPONENT_LOCATION/../Vivado/microblazeV.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",compiler = "gcc")

platform = client.create_platform_component(name = "microblazeV",hw_design = "$COMPONENT_LOCATION/../Vivado/microblazeV.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",compiler = "gcc")

platform = client.create_platform_component(name = "nexys4_microblazeV",hw_design = "$COMPONENT_LOCATION/../Vivado/microblazeV.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",compiler = "gcc")

comp = client.create_app_component(name="microblazeV_code",platform = "$COMPONENT_LOCATION/../nexys4_microblazeV/export/nexys4_microblazeV/nexys4_microblazeV.xpfm",domain = "standalone_microblaze_riscv_0")

comp = client.create_app_component(name="nexys4_microblazeV_empty",platform = "$COMPONENT_LOCATION/../nexys4_microblazeV/export/nexys4_microblazeV/nexys4_microblazeV.xpfm",domain = "standalone_microblaze_riscv_0",template = "empty_application")

client.delete_component(name="microblazeV_code")

client.delete_component(name="componentName")

platform = client.create_platform_component(name = "nexys4_microblazeV_UART",hw_design = "$COMPONENT_LOCATION/../Vivado/microblazeV_with_UART.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",compiler = "gcc")

comp = client.create_app_component(name="nexys4_uart",platform = "$COMPONENT_LOCATION/../nexys4_microblazeV_UART/export/nexys4_microblazeV_UART/nexys4_microblazeV_UART.xpfm",domain = "standalone_microblaze_riscv_0",template = "empty_application")

