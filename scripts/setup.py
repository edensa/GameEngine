import os
import subprocess
import check_python

# Make sure everything we need is installed
check_python.validate_packages()

import get_vulkan

# Change from Scripts directory to root
os.chdir('../')

if (not get_vulkan.check_vulkan_sdk()):
    print("Vulkan SDK not installed.")

if (not get_vulkan.check_vulkan_sdk_debug_libs()):
    print("Vulkan SDK debug libs not found.")

print("Running premake...")
subprocess.call(["vendor/premake/bin/premake5.exe", "vs2019"])