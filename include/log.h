#pragma once

#define LOG Serial.println(String(millis()) + String(" ") + String(__FILE__) + String(":") + String(__LINE__) + String(":") + String(__PRETTY_FUNCTION__))
#define LOGP(p) Serial.println(String(millis()) + String(" ") + String(__FILE__) + String(":") + String(__LINE__) + String(":") + String(__PRETTY_FUNCTION__) + String(" ") + String(p))
