#
# Copyright (C) 2016 The CyanogenMod Project
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

-include device/samsung/smdk4412-common/BoardCommonConfig.mk

LOCAL_PATH := device/samsung/kona-common

# For KK blobs
MALLOC_SVELTE := true
TARGET_NEEDS_PLATFORM_TEXT_RELOCATIONS := true

# Inline kernel building
TARGET_KERNEL_SOURCE := kernel/samsung/kona

# Recovery
TARGET_RECOVERY_DENSITY := mdpi

TW_THEME := portrait_mdpi
TW_ROTATION := 270

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)/bluetooth

# Camera
BOARD_GLOBAL_CFLAGS += -DCAMERA_WITH_CITYID_PARAM

# Graphics
TARGET_REQUIRES_SYNCHRONOUS_SETSURFACE := true

# Lights
BOARD_EXYNOS4X12_TABLET_HAS_LED_BUTTONS := true

# Charger
NO_CHARGER_LED := true

# Selinux
BOARD_SEPOLICY_DIRS += device/samsung/kona-common/selinux
