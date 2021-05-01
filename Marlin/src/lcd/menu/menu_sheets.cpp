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

//
// Steel sheets Menu
//

#include "../../inc/MarlinConfig.h"

#if HAS_LCD_MENU && ENABLED(SHEETS_FEATURE)

#include "menu_item.h"
#include "../../feature/sheets.h"

#define VALUE_ITEM(MSG, VALUE, STYL)    do{ char msg[21]; strcpy_P(msg, PSTR(": ")); strcpy(msg + 2, VALUE); STATIC_ITEM(MSG, STYL, msg); }while(0)

// Variables for temporarily storing menu state
uint8_t selected_sheet_index = 0;
uint8_t loop_sheet_index = 0;

/**
 * Build menu for a sheet
 */
void menu_sheet(uint8_t index) {
  // Init menu
  START_MENU();
  BACK_ITEM(MSG_SHEETS);

  // Temporarily keep current selected sheet index
  selected_sheet_index = index;

  // Create action for setting the current sheet active
  ACTION_ITEM(MSG_SHEET_SETACTIVE, []{ sheets.set_active_sheet(selected_sheet_index); ui.return_to_status(); });

  // Create value item for displaying the z offset
  VALUE_ITEM(MSG_SHEET_ZOFFSET, ftostr63(sheets.settings.sheets_list[selected_sheet_index].z_offset), SS_LEFT);

  // Finalize menu
  END_MENU();
}

/**
 * Build general sheets menu
 */
void menu_sheets() {
  // Init menu
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  // Create active sheet switching menu item
  char activesheet_str[1 + strlen_P(GET_TEXT(MSG_SHEET_ACTIVE))];
  strcpy_P(activesheet_str, GET_TEXT(MSG_SHEET_ACTIVE));
  strcat_P(activesheet_str, PSTR(": "));
  strcat_P(activesheet_str, sheets.settings.sheets_list[sheets.settings.active_sheet].name);

  ACTION_ITEM_P(activesheet_str, []{ sheets.set_next_active_sheet(); menu_sheets(); });

  // Create list of sheet submenu items
  for (uint8_t i = 0; i < MAX_SHEETS; i++) {
    loop_sheet_index = i;
    SUBMENU_P(PSTR(sheets.settings.sheets_list[i].name), []{ menu_sheet(loop_sheet_index); });
  }

  // Finalize menu
  END_MENU();
}

#endif
