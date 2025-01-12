using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    public abstract class BaseCacheManager<T> where T : BaseCacheItem
    {
        private static Dictionary<string, T> _repository = new Dictionary<string, T>();

        public static Dictionary<string, T> Repository
        {
            get
            {
                return _repository;
            }
            set
            {
                _repository = value;
            }
        }

        public static void Add(string key, T cacheItem)
        {
            lock (_repository)
            {
                if (_repository.ContainsKey(key))
                {
                    _repository.Remove(key);
                }
                cacheItem.ExpirationDate = ((cacheItem.Timeout == 0) ? DateTime.MaxValue : DateTime.Now.AddMinutes(cacheItem.Timeout));
                _repository.Add(key, cacheItem);
            }
        }

        public static void Remove(string key)
        {
            lock (_repository)
            {
                if (_repository.ContainsKey(key))
                {
                    _repository.Remove(key);
                }
            }
        }

        public static T Get(string key)
        {
            lock (_repository)
            {
                if (_repository.ContainsKey(key))
                {
                    T val = _repository[key];
                    if (val.Timeout == 0 || val.ExpirationDate >= DateTime.Now)
                    {
                        return val;
                    }
                    _repository.Remove(key);
                }
            }
            return null;
        }

        public static T Get(Predicate<T> predicate)
        {
            lock (_repository)
            {
                KeyValuePair<string, T> keyValuePair = default(KeyValuePair<string, T>);
                foreach (KeyValuePair<string, T> item in _repository)
                {
                    if (predicate(item.Value))
                    {
                        keyValuePair = item;
                        break;
                    }
                }
                if (keyValuePair.Value != null)
                {
                    if (keyValuePair.Value.Timeout == 0 || keyValuePair.Value.ExpirationDate >= DateTime.Now)
                    {
                        return keyValuePair.Value;
                    }
                    _repository.Remove(keyValuePair.Key);
                }
                return null;
            }
        }

        public static void Clear()
        {
            lock (_repository)
            {
                _repository.Clear();
            }
        }
    }



    public class Calendar
    {
        private static ConcurrentDictionary<Channels, DateTime> _todays = new ConcurrentDictionary<Channels, DateTime>();

        private static CalendarInformation getCalendar(string calendarCode = "TR")
        {
            CalendarCacheItem calendarCacheItem = BaseCacheManager<CalendarCacheItem>.Get(calendarCode);
            if (calendarCacheItem == null)
            {
                Database database = new Database();
                DatabaseParameters databaseParameters = new DatabaseParameters();
                databaseParameters.AddInParameter("Code", calendarCode, DatabaseTypes.String);
                databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
                DataTable dataTable = database.ExecuteDataSet("APP_S_CALENDAR", databaseParameters).Tables[0];
                if (dataTable.Rows.Count == 0)
                {
                    throw new RecordNotFoundException("Code", calendarCode);
                }
                CalendarInformation calendarInformation = new CalendarInformation
                {
                    Code = dataTable.Rows[0]["CODE"].ToString(),
                    CalendarType = (CalendarTypes)((dataTable.Rows[0]["CALENDARTYPE"] != DBNull.Value) ? Convert.ToByte(dataTable.Rows[0]["CALENDARTYPE"]) : 0),
                    CalendarDescription = dataTable.Rows[0]["CALENDARDESCRIPTION"].ToString(),
                    OfficialHoliday1 = (WeekDays)((dataTable.Rows[0]["OFFICIALHOLIDAY1"] == DBNull.Value) ? 6 : Convert.ToByte(dataTable.Rows[0]["OFFICIALHOLIDAY1"])),
                    OfficialHoliday2 = (WeekDays)((dataTable.Rows[0]["OFFICIALHOLIDAY2"] != DBNull.Value) ? Convert.ToByte(dataTable.Rows[0]["OFFICIALHOLIDAY2"]) : 0)
                };
                DTOCalendar calendar = new DTOCalendar
                {
                    Code = dataTable.Rows[0]["CODE"].ToString(),
                    CalendarType = (CalendarTypes)((dataTable.Rows[0]["CALENDARTYPE"] != DBNull.Value) ? Convert.ToByte(dataTable.Rows[0]["CALENDARTYPE"]) : 0),
                    CalendarDescription = dataTable.Rows[0]["CALENDARDESCRIPTION"].ToString(),
                    OfficialHoliday1 = (WeekDays)((dataTable.Rows[0]["OFFICIALHOLIDAY1"] == DBNull.Value) ? 6 : Convert.ToByte(dataTable.Rows[0]["OFFICIALHOLIDAY1"])),
                    OfficialHoliday2 = (WeekDays)((dataTable.Rows[0]["OFFICIALHOLIDAY2"] != DBNull.Value) ? Convert.ToByte(dataTable.Rows[0]["OFFICIALHOLIDAY2"]) : 0)
                };
                DatabaseParameters databaseParameters2 = new DatabaseParameters();
                databaseParameters2.AddInParameter("CalendarId", calendarCode, DatabaseTypes.String);
                databaseParameters2.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
                DataTable dataTable2 = database.ExecuteDataSet("APP_L_CALENDARHOLIDAYBYCAL", databaseParameters2).Tables[0];
                List<DTOCalendarHoliday> list = new List<DTOCalendarHoliday>();
                calendarInformation.Holidays = new List<CalendarHolidayInformation>();
                foreach (DataRow row in dataTable2.Rows)
                {
                    calendarInformation.Holidays.Add(new CalendarHolidayInformation
                    {
                        CalendarCode = row["CALENDARID"].ToString(),
                        HolidayDate = ((row["HOLIDAYDATE"] == DBNull.Value) ? DateTime.MinValue : Convert.ToDateTime(row["HOLIDAYDATE"])),
                        IsHalfDay = (row["ISHALFDAY"] != DBNull.Value && Convert.ToBoolean(row["ISHALFDAY"])),
                        HolidayDescription = row["HOLIDAYDESCRIPTION"].ToString(),
                        IsPermanentHoliday = (row["ISPERMANENTHOLIDAY"] != DBNull.Value && Convert.ToBoolean(row["ISPERMANENTHOLIDAY"]))
                    });
                    list.Add(new DTOCalendarHoliday
                    {
                        CalendarCode = row["CALENDARID"].ToString(),
                        HolidayDate = ((row["HOLIDAYDATE"] == DBNull.Value) ? DateTime.MinValue : Convert.ToDateTime(row["HOLIDAYDATE"])),
                        IsHalfDay = (row["ISHALFDAY"] != DBNull.Value && Convert.ToBoolean(row["ISHALFDAY"])),
                        HolidayDescription = row["HOLIDAYDESCRIPTION"].ToString(),
                        IsPermanentHoliday = (row["ISPERMANENTHOLIDAY"] != DBNull.Value && Convert.ToBoolean(row["ISPERMANENTHOLIDAY"]))
                    });
                }
                DTOCalendarHoliday calendarMaxHolidayInfo = null;
                if (list != null && list.Count > 0)
                {
                    calendarMaxHolidayInfo = list.OrderByDescending((DTOCalendarHoliday x) => x.HolidayDate).First();
                }
                calendarCacheItem = new CalendarCacheItem(calendarInformation)
                {
                    Calendar = calendar,
                    CalendarHolidays = list,
                    CalendarMaxHolidayInfo = calendarMaxHolidayInfo
                };
                BaseCacheManager<CalendarCacheItem>.Add(calendarInformation.Code, calendarCacheItem);
                return calendarInformation;
            }
            return calendarCacheItem.CalendarInfo;
        }

        public static DTOCalendar GetDTOCalendar()
        {
            return GetDTOCalendar("TR");
        }

        public static List<DTOCalendarHoliday> GetDTOCalendarHolidays()
        {
            return GetDTOCalendarHolidays("TR");
        }

        public static void GetDifferenceInYearsMonthsDays(DateTime firstDate, DateTime secondDate, out int differenceInYears, out int differenceInMonths, out int differenceInDays)
        {
            BaseCalendar.GetDifferenceInYearsMonthsDays(firstDate, secondDate, out differenceInYears, out differenceInMonths, out differenceInDays);
        }

        public static DTOCalendar GetDTOCalendar(string calendarCode)
        {
            getCalendar(calendarCode);
            return BaseCacheManager<CalendarCacheItem>.Get(calendarCode).Calendar;
        }

        public static DTOCalendarHoliday GetMaxDTOCalendarHolidayInfo(string calendarCode)
        {
            getCalendar(calendarCode);
            return BaseCacheManager<CalendarCacheItem>.Get(calendarCode).CalendarMaxHolidayInfo;
        }

        public static DTOCalendarHoliday GetMaxDTOCalendarHolidayInfo()
        {
            return GetMaxDTOCalendarHolidayInfo("TR");
        }

        public static List<DTOCalendarHoliday> GetDTOCalendarHolidays(string calendarCode)
        {
            getCalendar(calendarCode);
            return BaseCacheManager<CalendarCacheItem>.Get(calendarCode).CalendarHolidays;
        }

        public static CalendarInformation GetCalendar()
        {
            return getCalendar();
        }

        public static bool IsLeapYear(int year)
        {
            return BaseCalendar.IsLeapYear(year);
        }

        public static int GetDaysInYear(int year)
        {
            return BaseCalendar.GetDaysInYear(year);
        }

        public static int ConvertToInteger(DateTime date)
        {
            return BaseCalendar.ConvertToInteger(date);
        }

        public static DateTime GetToday()
        {
            return GetToday(CallerInformation.Channel);
        }

        public static DateTime GetToday(Channels channel)
        {
            if (ApplicationInformation.Environment == Environments.Development || ApplicationInformation.Environment == Environments.Test || ApplicationInformation.Environment == Environments.PreProduction)
            {
                Database database = new Database();
                DatabaseParameters databaseParameters = new DatabaseParameters();
                databaseParameters.AddInParameter("UserCode", CallerInformation.UserCode, DatabaseTypes.String);
                databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
                DataTable dataTable = database.ExecuteDataSet("APP_S_USERDATE", databaseParameters).Tables[0];
                if (dataTable.Rows.Count != 0)
                {
                    DataRow dataRow = dataTable.Rows[0];
                    if (dataRow["SYSTEMDATE"] != DBNull.Value)
                    {
                        return Convert.ToDateTime(dataRow["SYSTEMDATE"]);
                    }
                    return DateTime.MinValue;
                }
            }
            DateTime date = DateTime.MinValue;
            _todays.TryGetValue(channel, out date);
            if (date.Equals(DateTime.MinValue) || date.DayOfYear != DateTime.Now.DayOfYear || (DateTime.Now.Hour == 23 && DateTime.Now.Minute > 30))
            {
                Database database2 = new Database();
                DatabaseParameters databaseParameters2 = new DatabaseParameters();
                databaseParameters2.AddInParameter("ChannelId", Convert.ToByte(channel), DatabaseTypes.Byte);
                databaseParameters2.AddOutParameter("Date", date, DatabaseTypes.Date);
                database2.ExecuteNonQuery("APP_S_CHANNELDATE", databaseParameters2);
                if (databaseParameters2["Date"].Value == null)
                {
                    throw new RecordNotFoundException("ChannelId", channel.ToString());
                }
                date = Convert.ToDateTime(databaseParameters2["Date"].Value.ToString());
                _todays.AddOrUpdate(channel, date, (Channels key, DateTime oldValue) => date);
            }
            return date;
        }

        public static int GetTodayAsInteger()
        {
            return BaseCalendar.ConvertToInteger(GetToday());
        }

        public static DateTime GetAppDate()
        {
            if (ApplicationInformation.Environment == Environments.Development || ApplicationInformation.Environment == Environments.Test || ApplicationInformation.Environment == Environments.PreProduction)
            {
                Database database = new Database();
                DatabaseParameters databaseParameters = new DatabaseParameters();
                databaseParameters.AddInParameter("UserCode", CallerInformation.UserCode, DatabaseTypes.String);
                databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
                DataTable dataTable = database.ExecuteDataSet("APP_S_USERDATE", databaseParameters).Tables[0];
                if (dataTable.Rows.Count != 0)
                {
                    DataRow dataRow = dataTable.Rows[0];
                    if (dataRow["SYSTEMDATE"] != DBNull.Value)
                    {
                        return DateTime.SpecifyKind(Convert.ToDateTime(dataRow["SYSTEMDATE"]), DateTimeKind.Local);
                    }
                    return DateTime.MinValue;
                }
            }
            return DateTime.Today;
        }

        public static DateTime GetAppDateTime()
        {
            return DateTime.Now;
        }

        public static long GetJulianDate(DateTime date)
        {
            return BaseCalendar.GetJulianDate(date);
        }

        public static CalendarInformation GetCalendar(string calendarCode)
        {
            return getCalendar(calendarCode);
        }

        public static bool IsHalfWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.IsHalfWorkingDay(getCalendar(calendarCode), date);
        }

        public static bool IsWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.IsWorkingDay(getCalendar(calendarCode), date);
        }

        public static bool IsWeekendDay(DateTime date)
        {
            return BaseCalendar.IsWeekendDay(getCalendar(), date);
        }

        public static DateTime FindWorkingDay(string calendarCode, DateTime date, double days)
        {
            return BaseCalendar.FindWorkingDay(getCalendar(calendarCode), date, days);
        }

        public static string GetHolidayDescription(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetHolidayDescription(getCalendar(calendarCode), date);
        }

        public static DateTime GetBeginningOfWeekWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetBeginningOfWeekWorkingDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetEndOfWeekWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetEndOfWeekWorkingDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetBeginningOfWeekDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetBeginningOfWeekDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetEndOfWeekDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetEndOfWeekDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetBeginningOfMonthWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetBeginningOfMonthWorkingDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetEndOfMonthWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetEndOfMonthWorkingDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetBeginningOfMonthDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetBeginningOfMonthDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetEndOfMonthDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetEndOfMonthDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetBeginningOfYearWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetBeginningOfYearWorkingDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetEndOfYearWorkingDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetEndOfYearWorkingDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetBeginningOfYearDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetBeginningOfYearDay(getCalendar(calendarCode), date);
        }

        public static DateTime GetEndOfYearDay(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetEndOfYearDay(getCalendar(calendarCode), date);
        }

        public static int GetWorkingDaysInYear(string calendarCode, int year)
        {
            return BaseCalendar.GetWorkingDaysInYear(getCalendar(calendarCode), year);
        }

        public static int GetDifference(string calendarCode, DateTime startDate, DateTime endDate)
        {
            return BaseCalendar.GetDifference(getCalendar(calendarCode), startDate, endDate);
        }

        public static int GetDifferenceForWorkingDays(string calendarCode, DateTime startDate, DateTime endDate)
        {
            return BaseCalendar.GetDifferenceForWorkingDays(getCalendar(calendarCode), startDate, endDate);
        }

        public static DateTime ForceToBeAWorkingDay(string calendarCode, DateTime date, bool countForward)
        {
            return BaseCalendar.ForceToBeAWorkingDay(getCalendar(calendarCode), date, countForward);
        }

        public static DateTime AddDays(string calendarCode, DateTime date, double days)
        {
            return BaseCalendar.AddDays(getCalendar(calendarCode), date, days);
        }

        public static DateTime AddDays(string calendarCode, DateTime date, DayTypes dayType, double days, bool countForward)
        {
            return BaseCalendar.AddDays(getCalendar(calendarCode), date, dayType, days, countForward);
        }

        public static DateTime AddDays(string calendarCode, DateTime date, DayTypes dayType, DayTypes resultDayType, double days, bool countForward)
        {
            return BaseCalendar.AddDays(getCalendar(calendarCode), date, dayType, resultDayType, days, countForward);
        }

        public static DateTime AddMonths(string calendarCode, DateTime date, DayTypes resultDayType, int months, bool countForward)
        {
            return BaseCalendar.AddMonths(getCalendar(calendarCode), date, resultDayType, months, countForward);
        }

        public static DateTime AddYears(string calendarCode, DateTime date, DayTypes resultDayType, int years, bool countForward)
        {
            return BaseCalendar.AddYears(getCalendar(calendarCode), date, resultDayType, years, countForward);
        }

        public static DayTypes GetDayType(string calendarCode, DateTime date)
        {
            return BaseCalendar.GetDayType(getCalendar(calendarCode), date);
        }

        public static DateTime PreviousWorkingDate(string calendarCode, DateTime date)
        {
            return BaseCalendar.PreviousWorkingDate(getCalendar(calendarCode), date);
        }

        public static DateTime NextWorkingDate(string calendarCode, DateTime date)
        {
            return BaseCalendar.NextWorkingDate(getCalendar(calendarCode), date);
        }

        public static DateTime PreviousDate(string calendarCode, DateTime date)
        {
            return BaseCalendar.PreviousDate(getCalendar(calendarCode), date);
        }

        public static DateTime NextDate(string calendarCode, DateTime date)
        {
            return BaseCalendar.NextDate(getCalendar(calendarCode), date);
        }

        public static DateTime FirstWorkingDayOfNextMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.FirstWorkingDayOfNextMonth(getCalendar(calendarCode), date);
        }

        public static DateTime LastWorkingDayOfNextMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.LastWorkingDayOfNextMonth(getCalendar(calendarCode), date);
        }

        public static DateTime FirstWorkingDayOfPreviousMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.FirstWorkingDayOfPreviousMonth(getCalendar(calendarCode), date);
        }

        public static DateTime LastWorkingDayOfPreviousMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.LastWorkingDayOfPreviousMonth(getCalendar(calendarCode), date);
        }

        public static DateTime FirstDayOfNextMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.FirstDayOfNextMonth(getCalendar(calendarCode), date);
        }

        public static DateTime LastDayOfNextMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.LastDayOfNextMonth(getCalendar(calendarCode), date);
        }

        public static DateTime FirstDayOfPreviousMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.FirstDayOfPreviousMonth(getCalendar(calendarCode), date);
        }

        public static DateTime LastDayOfPreviousMonth(string calendarCode, DateTime date)
        {
            return BaseCalendar.LastDayOfPreviousMonth(getCalendar(calendarCode), date);
        }

        public static bool IsHalfWorkingDay(DateTime date)
        {
            return BaseCalendar.IsHalfWorkingDay(getCalendar(), date);
        }

        public static bool IsWorkingDay(DateTime date)
        {
            return BaseCalendar.IsWorkingDay(getCalendar(), date);
        }

        public static DateTime FindWorkingDay(DateTime date, double days)
        {
            return BaseCalendar.FindWorkingDay(getCalendar(), date, days);
        }

        public static string GetHolidayDescription(DateTime date)
        {
            return BaseCalendar.GetHolidayDescription(getCalendar(), date);
        }

        public static DateTime GetBeginningOfWeekWorkingDay(DateTime date)
        {
            return BaseCalendar.GetBeginningOfWeekWorkingDay(getCalendar(), date);
        }

        public static DateTime GetEndOfWeekWorkingDay(DateTime date)
        {
            return BaseCalendar.GetEndOfWeekWorkingDay(getCalendar(), date);
        }

        public static DateTime GetBeginningOfWeekDay(DateTime date)
        {
            return BaseCalendar.GetBeginningOfWeekDay(getCalendar(), date);
        }

        public static DateTime GetEndOfWeekDay(DateTime date)
        {
            return BaseCalendar.GetEndOfWeekDay(getCalendar(), date);
        }

        public static DateTime GetBeginningOfMonthWorkingDay(DateTime date)
        {
            return BaseCalendar.GetBeginningOfMonthWorkingDay(getCalendar(), date);
        }

        public static DateTime GetEndOfMonthWorkingDay(DateTime date)
        {
            return BaseCalendar.GetEndOfMonthWorkingDay(getCalendar(), date);
        }

        public static DateTime GetBeginningOfMonthDay(DateTime date)
        {
            return BaseCalendar.GetBeginningOfMonthDay(getCalendar(), date);
        }

        public static DateTime GetEndOfMonthDay(DateTime date)
        {
            return BaseCalendar.GetEndOfMonthDay(getCalendar(), date);
        }

        public static DateTime GetBeginningOfYearWorkingDay(DateTime date)
        {
            return BaseCalendar.GetBeginningOfYearWorkingDay(getCalendar(), date);
        }

        public static DateTime GetEndOfYearWorkingDay(DateTime date)
        {
            return BaseCalendar.GetEndOfYearWorkingDay(getCalendar(), date);
        }

        public static DateTime GetBeginningOfYearDay(DateTime date)
        {
            return BaseCalendar.GetBeginningOfYearDay(getCalendar(), date);
        }

        public static DateTime GetEndOfYearDay(DateTime date)
        {
            return BaseCalendar.GetEndOfYearDay(getCalendar(), date);
        }

        public static int GetWorkingDaysInYear(int year)
        {
            return BaseCalendar.GetWorkingDaysInYear(getCalendar(), year);
        }

        public static int GetDifference(DateTime startDate, DateTime endDate)
        {
            return BaseCalendar.GetDifference(getCalendar(), startDate, endDate);
        }

        public static int GetDifferenceForWorkingDays(DateTime startDate, DateTime endDate)
        {
            return BaseCalendar.GetDifferenceForWorkingDays(getCalendar(), startDate, endDate);
        }

        public static DateTime ForceToBeAWorkingDay(DateTime date, bool countForward)
        {
            return BaseCalendar.ForceToBeAWorkingDay(getCalendar(), date, countForward);
        }

        public static DateTime AddDays(DateTime date, double days)
        {
            return BaseCalendar.AddDays(getCalendar(), date, days);
        }

        public static DateTime AddDays(DateTime date, DayTypes dayType, double days, bool countForward)
        {
            return BaseCalendar.AddDays(getCalendar(), date, dayType, days, countForward);
        }

        public static DateTime AddDays(DateTime date, DayTypes dayType, DayTypes resultDayType, double days, bool countForward)
        {
            return BaseCalendar.AddDays(getCalendar(), date, dayType, resultDayType, days, countForward);
        }

        public static DateTime AddMonths(DateTime date, DayTypes resultDayType, int months, bool countForward)
        {
            return BaseCalendar.AddMonths(getCalendar(), date, resultDayType, months, countForward);
        }

        public static DateTime AddYears(DateTime date, DayTypes resultDayType, int years, bool countForward)
        {
            return BaseCalendar.AddYears(getCalendar(), date, resultDayType, years, countForward);
        }

        public static DayTypes GetDayType(DateTime date)
        {
            return BaseCalendar.GetDayType(getCalendar(), date);
        }

        public static DateTime PreviousWorkingDate(DateTime date)
        {
            return BaseCalendar.PreviousWorkingDate(getCalendar(), date);
        }

        public static DateTime NextWorkingDate(DateTime date)
        {
            return BaseCalendar.NextWorkingDate(getCalendar(), date);
        }

        public static DateTime PreviousDate(DateTime date)
        {
            return BaseCalendar.PreviousDate(getCalendar(), date);
        }

        public static DateTime NextDate(DateTime date)
        {
            return BaseCalendar.NextDate(getCalendar(), date);
        }

        public static DateTime FirstWorkingDayOfNextMonth(DateTime date)
        {
            return BaseCalendar.FirstWorkingDayOfNextMonth(getCalendar(), date);
        }

        public static DateTime LastWorkingDayOfNextMonth(DateTime date)
        {
            return BaseCalendar.LastWorkingDayOfNextMonth(getCalendar(), date);
        }

        public static DateTime FirstWorkingDayOfPreviousMonth(DateTime date)
        {
            return BaseCalendar.FirstWorkingDayOfPreviousMonth(getCalendar(), date);
        }

        public static DateTime LastWorkingDayOfPreviousMonth(DateTime date)
        {
            return BaseCalendar.LastWorkingDayOfPreviousMonth(getCalendar(), date);
        }

        public static DateTime FirstDayOfNextMonth(DateTime date)
        {
            return BaseCalendar.FirstDayOfNextMonth(getCalendar(), date);
        }

        public static DateTime LastDayOfNextMonth(DateTime date)
        {
            return BaseCalendar.LastDayOfNextMonth(getCalendar(), date);
        }

        public static DateTime FirstDayOfPreviousMonth(DateTime date)
        {
            return BaseCalendar.FirstDayOfPreviousMonth(getCalendar(), date);
        }

        public static DateTime LastDayOfPreviousMonth(DateTime date)
        {
            return BaseCalendar.LastDayOfPreviousMonth(getCalendar(), date);
        }
    }

}
