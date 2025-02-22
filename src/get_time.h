#ifndef ALTSTD_GET_TIME
#define ALTSTD_GET_TIME

using namespace readxlsb;

namespace alt_std {

// Parse string assuming format of %Y-%m-%dT%H:%M:%S
bool get_time(const std::string& src, std::tm* tmb) {
    tmb->tm_isdst = -1;  // Let the system determine daylight saving time

    int year = 0, month = 1, day = 1, hour = 0, minute = 0, second = 0;

    // Try parsing the string in the expected format: YYYY-MM-DDTHH:MM:SS
    if (std::sscanf(src.c_str(), "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &minute, &second) >= 3) {
        tmb->tm_year = year - 1900;  // Adjust year for tm structure
        tmb->tm_mon = month - 1;     // Adjust month (0-based index)
        tmb->tm_mday = day;
        tmb->tm_hour = hour;
        tmb->tm_min = minute;
        tmb->tm_sec = second;

        // Convert to JulianDate and back to handle overflows (if needed)
        double serial = SerialDate::JulianDate(tmb->tm_year + 1900, tmb->tm_mon + 1, tmb->tm_mday,
                                                         tmb->tm_hour, tmb->tm_min, tmb->tm_sec) - BASE_JD;
        SerialDate::BaseTotm(serial, *tmb);

        return true;
    }

    return false;  // Parsing failed
}

}

#endif
