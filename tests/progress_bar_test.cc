﻿#include "base/progress_bar.h"
#include "base/canvas.h"
#include "base/widget.h"
#include "font_dummy.h"
#include "lcd_log.h"
#include "gtest/gtest.h"
#include <stdlib.h>

TEST(progress_bar, basic) {
  value_t v1;
  value_t v2;
  widget_t* s = progress_bar_create(NULL, 10, 20, 30, 40);

  value_set_int(&v1, 10);
  ASSERT_EQ(widget_set_prop(s, WIDGET_PROP_VALUE, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(s, WIDGET_PROP_VALUE, &v2), RET_OK);
  ASSERT_EQ(value_int(&v1), value_int(&v2));

  value_set_bool(&v1, TRUE);
  ASSERT_EQ(widget_set_prop(s, WIDGET_PROP_VERTICAL, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(s, WIDGET_PROP_VERTICAL, &v2), RET_OK);
  ASSERT_EQ(value_bool(&v1), value_bool(&v2));

  widget_destroy(s);
}

#include "log_change_events.inc"

TEST(ProgressBar, event) {
  widget_t* w = progress_bar_create(NULL, 0, 0, 100, 100);

  progress_bar_set_value(w, 10);

  s_log = "";
  widget_on(w, EVT_VALUE_WILL_CHANGE, on_change_events, NULL);
  widget_on(w, EVT_VALUE_CHANGED, on_change_events, NULL);

  progress_bar_set_value(w, 10);
  ASSERT_EQ(s_log, "");

  progress_bar_set_value(w, 20);
  ASSERT_EQ(s_log, "will_change;change;");

  widget_destroy(w);
}
