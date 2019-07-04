#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SWEDISH 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SWEDISH,
  BACKLIT,
  RGBRST,
  SCREENSHOT,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

enum unicode_names {
  AAU,
  AAL,
  AEU,
  AEL,
  OEU,
  OEL,
};

const uint32_t PROGMEM unicode_map[] = {
  [AAU]  = 0x00C5,
  [AAL] =  0x00E5,

  [AEU]  = 0x00C4,
  [AEL] =  0x00E4,

  [OEU]  = 0x00D6,
  [OEL] =  0x00F6,
};

#define KC______ KC_TRNS
#define KC_XOX   KC_TRNS
#define KC_XXXXX KC_NO
#define KC_XP    XP
#define KC_TG    TG
#define KC_MO    MO
#define KC_TO    TO
#define KC_HYPP  HYPR
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_SCREENSHOT SCREENSHOT
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       GESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,BSLASH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  LALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                MO(_LOWER), GUIEI,  BSPC,   ENT, SPC, MO(_RAISE)  \
                              //`--------------------'  `--------------------'
  ),

  [_SWEDISH] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   XOX,   XOX,   XOX,   XOX,   XOX,XP(AAL,AAU),\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   XOX,   XOX,   XOX,   XOX,  XP(AEL,AEU),XP(OEL,OEU),\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   XOX,   XOX,   XOX,   XOX,   XOX, TO(_QWERTY),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   XOX,   XOX,   XOX,     XOX,   XOX,   XOX \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      GRAVE,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,BSLASH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,   XOX,   XOX,   XOX,   XOX,   XOX,                   LBRC,   XOX,   XOX,  MINS,   EQL,  RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,     F8,   F9,   F10,  LALT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 XOX,   XOX,   XOX,     XOX,   XOX,   MO(_ADJUST)  \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        XOX,   XOX,   XOX,   XOX,   XOX,   XOX,                   LPRN,   XOX,   UP,   MINS,   EQL,  RPRN,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        XOX,   XOX,_VOLUP,  MPLY,   XOX,   XOX,                   LBRC,  LEFT,  DOWN, RIGHT,   XOX,  RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        XOX,   XOX,_VOLDOWN,_MUTE,  XOX,   XOX,                   LABK,  XOX,   XOX,    XOX,   XOX,  RABK,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 MO(_ADJUST),   XOX,   XOX,     XOX,   XOX,   XOX  \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST,    NO,    NO,    NO,    NO,             SCREENSHOT,    NO, HYPP(KC_UP),    NO,    NO,    NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,    NO,    NO,             HYPP(KC_F),HYPP(KC_LEFT),HYPP(KC_DOWN),HYPP(KC_RIGHT),    NO,    NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,    NO,    NO,                     NO,    NO,    NO,    NO,    NO,TG(_SWEDISH),\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 XOX,   XOX,   XOX,     XOX,   XOX,   XOX  \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
const char *read_dmg(void);
const char *read_qmk(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
const char *read_stroke_count(void);

void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_OSX);
}

void matrix_scan_user(void) {
   iota_gfx_task();
}

char layer_state_str[24];

void set_layer_state_text(char* text) {
  snprintf(layer_state_str, sizeof(layer_state_str), text);
}

const char *read_layer_state2(void) {
  if(IS_LAYER_ON(_ADJUST)) {
    set_layer_state_text("Layer: Adjust");
  } else if(IS_LAYER_ON(_RAISE)) {
    set_layer_state_text("Layer: Raise");
  } else if(IS_LAYER_ON(_LOWER)) {
    set_layer_state_text("Layer: Lower");
  } else if(IS_LAYER_ON(_SWEDISH)) {
    set_layer_state_text("Layer: Swedish");
  } else if(IS_LAYER_ON(_QWERTY)) {
    set_layer_state_text("Layer: Base");
  } else{
    set_layer_state_text("Layer: Unknown");
  }

  return layer_state_str;
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    matrix_write_ln(matrix, read_layer_state2());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_stroke_count());
  } else {
    if(IS_LAYER_ON(_SWEDISH)) {
      matrix_write(matrix, read_dmg());
    } else if(IS_LAYER_ON(_ADJUST) || IS_LAYER_ON(_RAISE) || IS_LAYER_ON(_LOWER)) {
      matrix_write(matrix, read_qmk());
    } else {
      matrix_write(matrix, read_logo());
    }
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case SCREENSHOT:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)"4"SS_UP(X_LGUI)SS_UP(X_LCTRL)SS_UP(X_LSHIFT));
      }
      break;
    case RESET:
      if (record->event.pressed) {
        eeconfig_init();
      }
      break;
  }
  return true;
}
