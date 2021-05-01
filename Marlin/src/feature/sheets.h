/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "../inc/MarlinConfig.h"

#define MAX_SHEETS 8

typedef struct {
  uint8_t sheet_nr;
  char name[8];
  float z_offset;
  uint8_t bed_temp;
} sheet_t;

typedef struct {
  sheet_t sheets_list[MAX_SHEETS];
  uint8_t active_sheet;
} sheets_settings_t;

#if ENABLED(SHEETS_FEATURE)

class Sheets {
  private:
    static void initialize_sheet(uint8_t index, char *name, float z_offset, uint8_t bed_temp);

  public:
    static sheets_settings_t settings;

    Sheets() { reset(); }

    static void reset();
    static void load();
    static void set_active_sheet(uint8_t index);
    static void set_next_active_sheet();
    static void update_active_zoffset(float z_offset);
    static sheet_t get_active_sheet();
};

extern Sheets sheets;

#endif
