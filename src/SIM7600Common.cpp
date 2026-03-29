/**
 * SPDX-FileCopyrightText: 2025 Maximiliano Ramirez <maximiliano.ramirezbravo@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyMiscUseAnonymousNamespace
#include "SIM7600Common.h"


const char* SIM7600::statusToString(Status status)
{
#define X(name) #name,
	static const char* status_strings[] = {SIM7600_STATUS_LIST};
#undef X

	return status_strings[static_cast<uint8_t>(status)];
}

static void skipWhitespace(const char** s)
{
	while (isspace(**s)) (*s)++;
}

#ifdef TARGET_AVR

/**
 * @details Alternative implementation of vsscanf for boards without native support (e.g., Mega)
 */
int avr_vsscanf(const char* str, const char* fmt, va_list ap)
{
	int assigned = 0;

	while (*fmt && *str) {
		if (isspace(*fmt)) {
			skipWhitespace(&str);
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
				skipWhitespace(&str);
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
				skipWhitespace(&str);
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
				skipWhitespace(&str);
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
				skipWhitespace(&str);
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
				skipWhitespace(&str);
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

#endif