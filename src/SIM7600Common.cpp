/**
 * SPDX-FileCopyrightText: 2025 Maximiliano Ramirez <maximiliano.ramirezbravo@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "SIM7600Common.h"

const char* SIM7600::statusToString(SIM7600::Status status)
{
#define X(name) #name,
	static const char* status_strings[] = {SIM7600_STATUS_LIST};
#undef X

	return status_strings[static_cast<uint8_t>(status)];
}

static void skip_ws(const char** s)
{
	while (isspace(**s)) (*s)++;
}

int my_vsscanf(const char* str, const char* fmt, va_list ap)
{
	int assigned = 0;

	while (*fmt && *str) {
		if (isspace(*fmt)) {
			skip_ws(&str);
			fmt++;
			continue;
		}

		if (*fmt != '%') {
			if (*fmt != *str) break;
			fmt++;
			str++;
			continue;
		}

		fmt++; // skip '%'

		switch (*fmt) {
			case 'd':
			{
				skip_ws(&str);
				char* end;
				long  val = strtol(str, &end, 10);
				if (end == str) return assigned;
				*va_arg(ap, int*) = (int) val;
				str               = end;
				assigned++;
				break;
			}

			case 'u':
			{
				skip_ws(&str);
				char*         end;
				unsigned long val = strtoul(str, &end, 10);
				if (end == str) return assigned;
				*va_arg(ap, unsigned int*) = (unsigned int) val;
				str                        = end;
				assigned++;
				break;
			}

			case 'x':
			{
				skip_ws(&str);
				char*         end;
				unsigned long val = strtoul(str, &end, 16);
				if (end == str) return assigned;
				*va_arg(ap, unsigned int*) = (unsigned int) val;
				str                        = end;
				assigned++;
				break;
			}

			case 'f':
			{
				skip_ws(&str);
				char* end;
				float val = strtod(str, &end);
				if (end == str) return assigned;
				*va_arg(ap, float*) = val;
				str                 = end;
				assigned++;
				break;
			}

			case 's':
			{
				skip_ws(&str);
				char* out = va_arg(ap, char*);
				int   i   = 0;
				while (*str && !isspace(*str)) {
					out[i++] = *str++;
				}
				out[i] = '\0';
				assigned++;
				break;
			}

			case 'c':
			{
				char* out = va_arg(ap, char*);
				*out      = *str++;
				assigned++;
				break;
			}

			case '%':
			{
				if (*str != '%') return assigned;
				str++;
				break;
			}

			default:
				// unsupported specifier
				return assigned;
		}

		fmt++;
	}

	return assigned;
}
