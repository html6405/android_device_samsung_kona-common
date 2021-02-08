/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2012 The CyanogenMod Project <http://www.cyanogenmod.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _BDROID_BUILDCFG_H
#define _BDROID_BUILDCFG_H

#if N5100
#define BTM_DEF_LOCAL_NAME   "GT-N5100"
#endif
#if N5110
#define BTM_DEF_LOCAL_NAME   "GT-N5110"
#endif
#if N5120
#define BTM_DEF_LOCAL_NAME   "GT-N5120"
#endif

/* Defined if the kernel does not have support for CLOCK_BOOTTIME_ALARM */
#define KERNEL_MISSING_CLOCK_BOOTTIME_ALARM TRUE

#endif
