#include <stdlib.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;

#define SERIAL_NUMBER_FILE "/efs/FactoryApp/serial_no"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    const std::string bootloader = GetProperty("ro.bootloader", "");
    const std::string platform = GetProperty("ro.board.platform", "");

    char const *serial_number_file = SERIAL_NUMBER_FILE;
    std::string serial_number;

    if (ReadFileToString(serial_number_file, &serial_number)) {
        serial_number = Trim(serial_number);
        property_override("ro.serialno", serial_number.c_str());
    }

    if (bootloader.find("N5100") != std::string::npos) {
        property_override_dual("ro.product.model", "ro.vendor.product.model", "GT-N5100");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "kona3g");
        property_override_dual("ro.product.device", "ro.vendor.product.name", "kona3gxx");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "kona3gxx-user 4.4.2 KOT49H N5100XXSDQA2 release-keys");
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/kona3gxx/kona3g:4.4.2/KOT49H/N5100XXSDQA2:user/release-keys");
        property_override("ro.build.product", "n5100");
    } else if (bootloader.find("N5110") != std::string::npos) {
        property_override_dual("ro.product.model", "ro.vendor.product.model", "GT-N5110");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "konawifi");
        property_override_dual("ro.product.name", "ro.vendor.product.name", "konawifixx");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "konawifixx-user 4.4.2 KOT49H N5110XXDNF1 release-keys");
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/konawifixx/konawifi:4.4.2/KOT49H/N5110XXDNF1:user/release-keys");
        property_override("ro.build.product", "n5110");
    } else if (bootloader.find("N5120") != std::string::npos) {
        property_override_dual("ro.product.model", "ro.vendor.product.model", "GT-N5120");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "konalte");
        property_override_dual("ro.product.name", "ro.vendor.product.name", "konaltexx");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "konaltexx-user 4.4.2 KOT49H N5120XXDOD1 release-keys");
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/konaltexx/konalte:4.4.2/KOT49H/N5120XXDOD1:user/release-keys");
        property_override("ro.build.product", "n5120");
    } else {
        /* Fall back to GT-N5110 (Wifi version) */
        property_override_dual("ro.product.model", "ro.vendor.product.model", "GT-N5110");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "konawifi");
        property_override_dual("ro.product.name", "ro.vendor.product.name", "konawifixx");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "konawifixx-user 4.4.2 KOT49H N5110XXDNF1 release-keys");
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/konawifixx/konawifi:4.4.2/KOT49H/N5110XXDNF1:user/release-keys");
        property_override("ro.build.product", "n5110");
    }

    const std::string device = GetProperty("ro.product.device", "");
    LOG(INFO) << "Found bootloader " << bootloader << ". " << "Setting build properties for " << device << ".\n";
}
