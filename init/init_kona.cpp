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

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
    "system_ext.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void vendor_load_properties()
{
    const std::string bootloader = GetProperty("ro.bootloader", "");

    char const *serial_number_file = SERIAL_NUMBER_FILE;
    std::string serial_number;

    property_override("ro.treble.enabled", "true");
    property_override("rild.libargs", "-d /dev/ttyS0");

    if (ReadFileToString(serial_number_file, &serial_number)) {
        serial_number = Trim(serial_number);
        property_override("ro.serialno", serial_number.c_str());
    }

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    if (bootloader.find("N5100") == 0) {
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/kona3gxx/kona3g:4.4.2/KOT49H/N5100XXSDQA2:user/release-keys");
            set_ro_product_prop(source, "device", "kona3g");
            set_ro_product_prop(source, "model", "GT-N5100");
            set_ro_product_prop(source, "name", "kona3gxx");
        }
        property_override("ro.build.description", "kona3gxx-user 4.4.2 KOT49H N5100XXSDQA2 release-keys");
        property_override("ro.build.product", "n5100");
    } else if (bootloader.find("N5105") == 0) {
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/kona3gjt/kona3g:4.2.2/JDQ39/N5105JVCMI2:user/release-keys");
            set_ro_product_prop(source, "device", "kona3g");
            set_ro_product_prop(source, "model", "GT-N5105");
            set_ro_product_prop(source, "name", "kona3gjt");
        }
        property_override("ro.build.description", "kona3gjt-user 4.2.2 JDQ39 N5105JVCMI2 release-keys");
        property_override("ro.build.product", "kona3g");
    } else if (bootloader.find("N5110") == 0) {
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/konawifixx/konawifi:4.4.2/KOT49H/N5110XXDNF1:user/release-keys");
            set_ro_product_prop(source, "device", "konawifi");
            set_ro_product_prop(source, "model", "GT-N5110");
            set_ro_product_prop(source, "name", "konawifixx");
        }
        property_override("ro.build.description", "konawifixx-user 4.4.2 KOT49H N5110XXDNF1 release-keys");
        property_override("ro.build.product", "n5110");
        property_override("ro.radio.noril", "yes");
    } else if (bootloader.find("N5120") == 0) {
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/konaltexx/konalte:4.4.2/KOT49H/N5120XXDOD1:user/release-keys");
            set_ro_product_prop(source, "device", "konalte");
            set_ro_product_prop(source, "model", "GT-N5120");
            set_ro_product_prop(source, "name", "konaltexx");
        }
        property_override("ro.build.description", "konaltexx-user 4.4.2 KOT49H N5120XXDOD1 release-keys");
        property_override("ro.build.product", "n5120");
} else if (bootloader.find("I467M") == 0) {
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/konaltevl/konaltecan:4.4.2/KOT49H/I467MVLUBNF5:user/release-keys");
            set_ro_product_prop(source, "device", "konaltecan");
            set_ro_product_prop(source, "model", "SGH-I467M");
            set_ro_product_prop(source, "name", "konaltevl");
        }
        property_override("ro.build.description", "konaltevl-user 4.4.2 KOT49H I467MVLUBNF5 release-keys");
        property_override("ro.build.product", "konaltecan");
    } else {
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/kona3gxx/kona3g:4.4.2/KOT49H/N5100XXSDQA2:user/release-keys");
            set_ro_product_prop(source, "device", "kona3g");
            set_ro_product_prop(source, "model", "GT-N5100");
            set_ro_product_prop(source, "name", "kona3gxx");
        }
        property_override("ro.build.description", "konawifixx-user 4.4.2 KOT49H N5110XXDNF1 release-keys");
        property_override("ro.build.product", "n5110");
    }
    const std::string device = GetProperty("ro.product.device", "");
    LOG(INFO) << "Found bootloader " << bootloader << ". " << "Setting build properties for " << device << ".\n";
}
