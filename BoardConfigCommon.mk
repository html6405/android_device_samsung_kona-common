#
# Copyright (C) 2012 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
include device/samsung/smdk4412-common/BoardCommonConfig.mk

WITHOUT_CAMERA2 := true
WITHOUT_GCAM := true

# Wifi
WIFI_DRIVER_MODULE_PATH :=

# Bionic
MALLOC_SVELTE := true
TARGET_NEEDS_PLATFORM_TEXT_RELOCATIONS := true

# Graphics
TARGET_REQUIRES_SYNCHRONOUS_SETSURFACE := true
BOARD_EGL_WORKAROUND_BUG_10194508 := true
BOARD_GLOBAL_CFLAGS += -DWORKAROUND_BUG_10194508
BOARD_EGL_NEEDS_HANDLE_VALUE := true
TARGET_ENABLE_MEDIADRM_64 := true
SF_PRIMARY_DISPLAY_ORIENTATION := 270

# Lights
BOARD_EXYNOS4X12_TABLET_HAS_LED_BUTTONS := true

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/samsung/kona-common/bluetooth

# Kernel
TARGET_KERNEL_SOURCE := kernel/samsung/smdk4412
TARGET_KERNEL_CONFIG := lineageos_n5110_defconfig

# Filesystem
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1444888576
BOARD_USERDATAIMAGE_PARTITION_SIZE := 12620578800
BOARD_CACHEIMAGE_PARTITION_SIZE := 825638912
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_FLASH_BLOCK_SIZE := 2048
TARGET_RECOVERY_DEVICE_DIRS += device/samsung/kona-common

# Recovery
TARGET_RECOVERY_FSTAB := device/samsung/kona-common/rootdir/fstab.n51xx
TARGET_RECOVERY_DENSITY := mdpi
TARGET_USERIMAGES_USE_F2FS := true
RECOVERY_FSTAB_VERSION := 2

# PowerHAL
TARGET_POWERHAL_VARIANT := pegasusq

TARGET_LD_SHIM_LIBS += \
    /system/vendor/bin/gpsd|libsamsung_symbols.so