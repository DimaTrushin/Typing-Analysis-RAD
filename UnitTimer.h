// ---------------------------------------------------------------------------

#ifndef UnitTimerH
#define UnitTimerH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <windows.h>
// ---------------------------------------------------------------------------

namespace NSApplication {
// ---------------------------------------------------------------------------
// Using
// ---------------------------------------------------------------------------

using microseconds = long long;

using roundminutes = int;
using roundhours = int;

using milliseconds = double;
using seconds = double;
using minutes = double;
using hours = double;

using symbolsPerMinute = double;
using wordsPerMinute = double;
// ---------------------------------------------------------------------------
// Declaration of LARGE_INTEGER Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const LARGE_INTEGER& LInteger);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, LARGE_INTEGER& LInteger);
// ---------------------------------------------------------------------------
// Declaration of CTimer
// ---------------------------------------------------------------------------

class CTimer {
public:
  CTimer();

  CTimer(const CTimer&) = delete;
  CTimer(CTimer&&) = delete;
  CTimer& operator=(const CTimer&) = delete;
  CTimer& operator=(CTimer&&) = delete;

  // returns the time in microseconds from the moment of creation of the Timer
  microseconds getTime() const;

  // Conversions from microseconds
  static milliseconds MicroSecondsToMilliSeconds(microseconds Time);
  static seconds MicroSecondsToSeconds(microseconds Time);
  static minutes MicroSecondsToMinutes(microseconds Time);
  static hours MicroSecondsToHours(microseconds Time);
  static roundminutes MicroSecondsToRoundMinutes(microseconds Time);
  static roundhours MicroSecondsToRoundHours(microseconds Time);
  // Conversions to microseconds
  static microseconds MillisecondsToMicroseconds(milliseconds Time);
  static microseconds SecondsToMicroseconds(milliseconds Time);
  static microseconds MinutesToMicroseconds(roundminutes Time);
  static microseconds HoursToMicroseconds(roundhours Time);
  // Conversion time to speed
  static symbolsPerMinute convertTimeToSpeed(microseconds Time);
  // Constants
  static constexpr microseconds microsecondsInOneMillisecond = 1000;
  static constexpr microseconds microsecondsInOneSecond =   1000000;
  static constexpr microseconds microsecondsInOneMinute =  60000000;
  static constexpr microseconds microsecondsInOneHour =  3600000000;

private:
  LARGE_INTEGER startingTime;
  LARGE_INTEGER frequency;

  template<class TStreamer>
  friend TStreamer& operator<<(TStreamer& Streamer, const CTimer& Timer);
  template<class TStreamer>
  friend TStreamer& operator>>(TStreamer& Streamer, CTimer& Timer);
};
// ---------------------------------------------------------------------------
// Declaration of CTimer Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CTimer& Timer);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CTimer& Timer);
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication {
// ---------------------------------------------------------------------------
// Definition of LARGE_INTEGER Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const LARGE_INTEGER& LInteger) {
  Streamer.writePOD(LInteger);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, LARGE_INTEGER& LInteger) {
  Streamer.readPOD(&LInteger);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CTimer Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CTimer& Timer) {
  Streamer << Timer.startingTime;
  Streamer << Timer.frequency;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CTimer& Timer) {
  Streamer >> Timer.startingTime;
  Streamer >> Timer.frequency;
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
