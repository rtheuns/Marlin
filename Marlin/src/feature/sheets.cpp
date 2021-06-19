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

/**
 * sheets.cpp - Sheets feature
 */

#include "../inc/MarlinConfig.h"

#if ENABLED(SHEETS_FEATURE)

#include "sheets.h"
#include "../module/probe.h"
#include "../module/settings.h"

Sheets sheets; // Single instance - this calls the constructor

// public:

sheets_settings_t Sheets::settings;

void Sheets::reset() {
  Sheets::settings.active_sheet = 0;

  char sheetname1[] = SHEETS_SHEET_1;
  initialize_sheet(0, sheetname1, 0, 0);

  char sheetname2[] = SHEETS_SHEET_2;
  initialize_sheet(1, sheetname2, 0, 0);

  char sheetname3[] = SHEETS_SHEET_3;
  initialize_sheet(2, sheetname3, 0, 0);

  char sheetname4[] = SHEETS_SHEET_4;
  initialize_sheet(3, sheetname4, 0, 0);

  char sheetname5[] = SHEETS_SHEET_5;
  initialize_sheet(4, sheetname5, 0, 0);

  char sheetname6[] = SHEETS_SHEET_6;
  initialize_sheet(5, sheetname6, 0, 0);

  char sheetname7[] = SHEETS_SHEET_7;
  initialize_sheet(6, sheetname7, 0, 0);

  char sheetname8[] = SHEETS_SHEET_8;
  initialize_sheet(7, sheetname8, 0, 0);
}

void Sheets::set_active_sheet(uint8_t index) {
  Sheets::settings.active_sheet = index;

  #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
    probe.offset.z = Sheets::settings.sheets_list[index].z_offset;

    #if (SHEETS_AUTOSAVE_EEPROM == true)
      MarlinSettings::save();
    #endif
  #endif
}

void Sheets::set_next_active_sheet() {
  if (Sheets::settings.active_sheet == MAX_SHEETS - 1) {
    set_active_sheet(0);
  } else {
    set_active_sheet(Sheets::settings.active_sheet += 1);
  }
}

void Sheets::update_active_zoffset(float z_offset) {
  Sheets::settings.sheets_list[Sheets::settings.active_sheet].z_offset = z_offset;
}

sheet_t Sheets::get_active_sheet() {
  return Sheets::settings.sheets_list[Sheets::settings.active_sheet];
}


// private:

void Sheets::initialize_sheet(uint8_t index, char *name, float z_offset, uint8_t bed_temp) {
  Sheets::settings.sheets_list[index].sheet_nr = index + 1;
  strcpy_P(Sheets::settings.sheets_list[index].name, name);
  Sheets::settings.sheets_list[index].z_offset = z_offset;
  Sheets::settings.sheets_list[index].bed_temp = bed_temp;
}

#endif