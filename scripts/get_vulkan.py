import os
import subprocess
import sys
from pathlib import Path

import utils

from io import BytesIO
from zipfile import ZipFile

VULKAN_SDK = os.environ.get('VULKAN_SDK')
VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.2.170.0/windows/vulkan_sdk.exe'
ENGINE_VULKAN_VERSION = '1.2.170.0'
OUTPUT_DIRECTORY = "GameEngine/vendor/VulkanSDK"
VULKAN_SDK_EXE_PATH = f"{OUTPUT_DIRECTORY}/VulkanSDK.exe"

VULKAN_SDK_DEBUG_LIBS_URL = 'https://sdk.lunarg.com/sdk/download/1.2.170.0/windows/VulkanSDK-1.2.170.0-DebugLibs.zip'
TEMP_ZIPFILE = f"{OUTPUT_DIRECTORY}/VulkanSDK.zip"

def install_vulkan_sdk():
    os.makedirs(OUTPUT_DIRECTORY, exist_ok=True)
    print('Downloading {} to {}'.format(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH))
    utils.download_file(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
    print("Done!")
    print("Running Vulkan SDK installer...")
    os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
    print("Re-run this script after installation")

def install_vulkan_prompt():
    print("Would you like to install the Vulkan SDK?")
    install = utils.YesOrNo()
    if (install):
        install_vulkan_sdk()
        quit()

def check_vulkan_sdk():
    if (VULKAN_SDK is None):
        print("You don't have the Vulkan SDK installed!")
        install_vulkan_prompt()
        return False
    elif (ENGINE_VULKAN_VERSION not in VULKAN_SDK):
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"You don't have the correct Vulkan SDK version! (GameEngine requires {ENGINE_VULKAN_VERSION})")
        install_vulkan_prompt()
        return False

    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True

def check_vulkan_sdk_debug_libs():
    os.makedirs(OUTPUT_DIRECTORY, exist_ok=True)
    shadercdLib = Path(f"{OUTPUT_DIRECTORY}/Lib/shaderc_sharedd.lib")
    if (not shadercdLib.exists()):
        print(f"No Vulkan SDK debug libs found. (Checked {shadercdLib})")
        print('Downloading {} to {}'.format(VULKAN_SDK_DEBUG_LIBS_URL, TEMP_ZIPFILE))
        utils.download_file(VULKAN_SDK_DEBUG_LIBS_URL, TEMP_ZIPFILE)
        print('Extracting...')
        with ZipFile(TEMP_ZIPFILE) as zfile:
            zfile.extractall(OUTPUT_DIRECTORY)

    print(f"Vulkan SDK debug libs located at {OUTPUT_DIRECTORY}")
    return True