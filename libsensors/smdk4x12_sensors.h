/*
 * Copyright (C) 2013 Paul Kocialkowski <contact@paulk.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <poll.h>
#include <linux/input.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <hardware/sensors.h>
#include <hardware/hardware.h>

#ifndef _SMDK4x12_SENSORS_H_
#define _SMDK4x12_SENSORS_H_

#define SMDK4x12_SENSORS_NEEDED_API		(1 << 0)

/* conversion of orientation data to degree units */
#define CONVERT_O                   (1.0f/1000.0f)
#define CONVERT_O_A                 (CONVERT_O)
#define CONVERT_O_P                 (CONVERT_O)
#define CONVERT_O_R                 (CONVERT_O)

#define LSG                         (1000.0f)
#define RANGE_A                     (4*GRAVITY_EARTH)
#define RESOLUTION_A                (GRAVITY_EARTH / LSG)

#define SENSORS_ACCELERATION     (1<<ID_A)
#define SENSORS_MAGNETIC_FIELD   (1<<ID_M)
#define SENSORS_ORIENTATION      (1<<ID_O)
#define SENSORS_LIGHT            (1<<ID_L)
#define SENSORS_PROXIMITY        (1<<ID_P)
#define SENSORS_GYROSCOPE        (1<<ID_GY)

#define SENSORS_ACCELERATION_HANDLE     0
#define SENSORS_MAGNETIC_FIELD_HANDLE   1
#define SENSORS_ORIENTATION_HANDLE      2
#define SENSORS_LIGHT_HANDLE            3
#define SENSORS_PROXIMITY_HANDLE        4
#define SENSORS_GYROSCOPE_HANDLE        5

/* For AK8973iB */
#define EVENT_TYPE_MAGV_X           ABS_X
#define EVENT_TYPE_MAGV_Y           ABS_Y
#define EVENT_TYPE_MAGV_Z           ABS_Z

/* For lis3dh */
#define EVENT_TYPE_ACCEL_X          ABS_X
#define EVENT_TYPE_ACCEL_Y          ABS_Y
#define EVENT_TYPE_ACCEL_Z          ABS_Z

struct smdk4x12_sensors_device;

struct smdk4x12_sensors_handlers {
	char *name;
	int handle;

	int (*init)(struct smdk4x12_sensors_handlers *handlers,
		struct smdk4x12_sensors_device *device);
	int (*deinit)(struct smdk4x12_sensors_handlers *handlers);
	int (*activate)(struct smdk4x12_sensors_handlers *handlers);
	int (*deactivate)(struct smdk4x12_sensors_handlers *handlers);
	int (*set_delay)(struct smdk4x12_sensors_handlers *handlers,
		int64_t delay);
	int (*get_data)(struct smdk4x12_sensors_handlers *handlers,
		struct sensors_event_t *event);

	int activated;
	int needed;
	int poll_fd;

	void *data;
};

struct smdk4x12_sensors_device {
	sensors_poll_device_1_t  device;

	struct smdk4x12_sensors_handlers **handlers;
	int handlers_count;

	struct pollfd *poll_fds;
	int poll_fds_count;
};

extern struct smdk4x12_sensors_handlers *smdk4x12_sensors_handlers[];
extern int smdk4x12_sensors_handlers_count;

int smdk4x12_sensors_activate(struct sensors_poll_device_t *dev, int handle,
	int enabled);
int smdk4x12_sensors_set_delay(struct sensors_poll_device_t *dev, int handle,
	int64_t ns);
int smdk4x12_sensors_poll(struct sensors_poll_device_t *dev,
	struct sensors_event_t* data, int count);

/*
 * Input
 */

void input_event_set(struct input_event *event, int type, int code, int value);
int64_t timestamp(struct timeval *time);
int64_t input_timestamp(struct input_event *event);
int uinput_rel_create(const char *name);
void uinput_destroy(int uinput_fd);
int input_open(char *name);
int sysfs_path_prefix(char *name, char *path_prefix);
int64_t sysfs_value_read(char *path);
int sysfs_value_write(char *path, int64_t value);
int sysfs_string_read(char *path, char *buffer, size_t length);
int sysfs_string_write(char *path, char *buffer, size_t length);

/*
 * Sensors
 */

extern struct smdk4x12_sensors_handlers lis3dh_acceleration;
extern struct smdk4x12_sensors_handlers akm8975;
extern struct smdk4x12_sensors_handlers cm36651_proximity;
extern struct smdk4x12_sensors_handlers al3201_light;
extern struct smdk4x12_sensors_handlers yas532_magnetic;
extern struct smdk4x12_sensors_handlers lps331ap;

#endif
