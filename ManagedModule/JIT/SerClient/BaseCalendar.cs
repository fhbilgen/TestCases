using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
        

    public class BaseCalendar
    {
        public static bool IsHalfWorkingDay(CalendarInformation calendar, DateTime date)
        {
            CalendarHolidayInformation calendarHolidayInformation = calendar.Holidays.Find((CalendarHolidayInformation x) => x.HolidayDate == date.Date);
            if (calendarHolidayInformation == null)
            {
                return false;
            }
            return calendarHolidayInformation.IsHalfDay;
        }

        public static bool IsWorkingDay(CalendarInformation calendar, DateTime date)
        {
            if (date.DayOfWeek.GetHashCode() == calendar.OfficialHoliday1.GetHashCode() || date.DayOfWeek.GetHashCode() == calendar.OfficialHoliday2.GetHashCode())
            {
                return false;
            }
            return calendar.Holidays.Find((CalendarHolidayInformation x) => x.HolidayDate == new DateTime(date.Year, date.Month, date.Day) && !x.IsHalfDay) == null;
        }

        public static bool IsWeekendDay(CalendarInformation calendar, DateTime date)
        {
            if (date.DayOfWeek.GetHashCode() != calendar.OfficialHoliday1.GetHashCode())
            {
                return date.DayOfWeek.GetHashCode() == calendar.OfficialHoliday2.GetHashCode();
            }
            return true;
        }

        public static DateTime FindWorkingDay(CalendarInformation calendar, DateTime date, double days)
        {
            int num = 1;
            double num2 = days;
            if (num2 < 0.0)
            {
                num2 = -1.0 * num2;
                num = -1;
            }
            for (int i = 0; (double)i < num2; i++)
            {
                date = date.AddDays(num);
                while (!IsWorkingDay(calendar, date))
                {
                    date = date.AddDays(num);
                }
            }
            return date;
        }

        public static DateTime FindHoliday(CalendarInformation calendar, DateTime date, double days)
        {
            int num = 1;
            double num2 = days;
            if (num2 < 0.0)
            {
                num2 = -1.0 * num2;
                num = -1;
            }
            for (int i = 0; (double)i < num2; i++)
            {
                date = date.AddDays(num);
                while (IsWorkingDay(calendar, date))
                {
                    date = date.AddDays(num);
                }
            }
            return date;
        }

        public static string GetHolidayDescription(CalendarInformation calendar, DateTime date)
        {
            CalendarHolidayInformation calendarHolidayInformation = calendar.Holidays.Find((CalendarHolidayInformation x) => x.HolidayDate == date);
            if (calendarHolidayInformation != null)
            {
                return calendarHolidayInformation.HolidayDescription;
            }
            return "The specified date is not a holiday!";
        }

        public static bool IsLeapYear(int year)
        {
            return DateTime.IsLeapYear(year);
        }

        public static DateTime GetBeginningOfWeekWorkingDay(CalendarInformation calendar, DateTime date)
        {
            DateTime dateTime = GetBeginningOfWeekDay(calendar, date);
            while (!IsWorkingDay(calendar, dateTime))
            {
                dateTime = dateTime.AddDays(1.0);
            }
            return dateTime;
        }

        public static DateTime GetEndOfWeekWorkingDay(CalendarInformation calendar, DateTime date)
        {
            DateTime dateTime = GetEndOfWeekDay(calendar, date);
            while (!IsWorkingDay(calendar, dateTime))
            {
                dateTime = dateTime.AddDays(-1.0);
            }
            return dateTime;
        }

        public static DateTime GetBeginningOfWeekDay(CalendarInformation calendar, DateTime date)
        {
            if (date.DayOfWeek.GetHashCode() == calendar.OfficialHoliday2.GetHashCode())
            {
                date = date.AddDays(-1.0);
            }
            while (date.DayOfWeek.GetHashCode() != calendar.OfficialHoliday2.GetHashCode())
            {
                date = date.AddDays(-1.0);
            }
            date = date.AddDays(1.0);
            return date;
        }

        public static DateTime GetEndOfWeekDay(CalendarInformation calendar, DateTime date)
        {
            while (date.DayOfWeek.GetHashCode() != calendar.OfficialHoliday2.GetHashCode())
            {
                date = date.AddDays(1.0);
            }
            return date;
        }

        public static DateTime GetBeginningOfMonthWorkingDay(CalendarInformation calendar, DateTime date)
        {
            DateTime dateTime = new DateTime(date.Year, date.Month, 1);
            while (!IsWorkingDay(calendar, dateTime))
            {
                dateTime = dateTime.AddDays(1.0);
            }
            return dateTime;
        }

        public static DateTime GetEndOfMonthWorkingDay(CalendarInformation calendar, DateTime date)
        {
            DateTime dateTime = GetEndOfMonthDay(calendar, date);
            while (!IsWorkingDay(calendar, dateTime))
            {
                dateTime = dateTime.AddDays(-1.0);
            }
            return dateTime;
        }

        public static DateTime GetBeginningOfMonthDay(CalendarInformation calendar, DateTime date)
        {
            return new DateTime(date.Year, date.Month, 1);
        }

        public static DateTime GetEndOfMonthDay(CalendarInformation calendar, DateTime date)
        {
            int day = DateTime.DaysInMonth(date.Year, date.Month);
            return new DateTime(date.Year, date.Month, day);
        }

        public static DateTime GetBeginningOfYearWorkingDay(CalendarInformation calendar, DateTime date)
        {
            DateTime dateTime = new DateTime(date.Year, 1, 1);
            while (!IsWorkingDay(calendar, dateTime))
            {
                dateTime = dateTime.AddDays(1.0);
            }
            return dateTime;
        }

        public static DateTime GetEndOfYearWorkingDay(CalendarInformation calendar, DateTime date)
        {
            DateTime dateTime = new DateTime(date.Year, 12, 31);
            while (!IsWorkingDay(calendar, dateTime))
            {
                dateTime = dateTime.AddDays(-1.0);
            }
            return dateTime;
        }

        public static DateTime GetBeginningOfYearDay(CalendarInformation calendar, DateTime date)
        {
            return new DateTime(date.Year, 1, 1);
        }

        public static DateTime GetEndOfYearDay(CalendarInformation calendar, DateTime date)
        {
            return new DateTime(date.Year, 12, 31);
        }

        public static int GetWorkingDaysInYear(CalendarInformation calendar, int year)
        {
            DateTime dateBeginning = new DateTime(year, 1, 1);
            DateTime dateEnding = new DateTime(year, 12, 31);
            int num = 365;
            int num2 = 1;
            if (DateTime.IsLeapYear(year))
            {
                num = 366;
                num2 = 2;
            }
            int num3 = 104;
            DateTime dateTime = dateBeginning.AddDays(364.0);
            for (int i = 0; i < num2; i++)
            {
                dateTime = dateTime.AddDays(1.0);
                if (dateTime.DayOfWeek.GetHashCode() == calendar.OfficialHoliday1.GetHashCode() || dateTime.DayOfWeek.GetHashCode() == calendar.OfficialHoliday2.GetHashCode())
                {
                    num3++;
                }
            }
            List<CalendarHolidayInformation> list = calendar.Holidays.FindAll((CalendarHolidayInformation x) => x.HolidayDate >= dateBeginning && x.HolidayDate <= dateEnding && x.HolidayDate.DayOfWeek.GetHashCode() != calendar.OfficialHoliday1.GetHashCode() && x.HolidayDate.DayOfWeek.GetHashCode() != calendar.OfficialHoliday2.GetHashCode());
            return num - (list.Count + num3);
        }

        public static int GetDaysInYear(int year)
        {
            int result = 365;
            if (DateTime.IsLeapYear(year))
            {
                result = 366;
            }
            return result;
        }

        public static void GetDifferenceInYearsMonthsDays(DateTime firstDate, DateTime secondDate, out int differenceInYears, out int differenceInMonths, out int differenceInDays)
        {
            TimeSpan timeSpan = ((firstDate >= secondDate) ? firstDate.Subtract(secondDate) : secondDate.Subtract(firstDate));
            DateTime dateTime = DateTime.MinValue + timeSpan;
            differenceInYears = dateTime.Year - 1;
            differenceInMonths = dateTime.Month - 1;
            differenceInDays = dateTime.Day - 1;
        }

        public static int GetDifference(CalendarInformation calendar, DateTime startDate, DateTime endDate)
        {
            DateTime value = new DateTime(startDate.Year, startDate.Month, startDate.Day);
            return new DateTime(endDate.Year, endDate.Month, endDate.Day).Subtract(value).Days;
        }

        public static int GetDifferenceForWorkingDays(CalendarInformation calendar, DateTime startDate, DateTime endDate)
        {
            DateTime startDateWoHour = new DateTime(startDate.Year, startDate.Month, startDate.Day);
            DateTime endDateWoHour = new DateTime(endDate.Year, endDate.Month, endDate.Day);
            int num = endDateWoHour.Subtract(startDateWoHour).Days + 1;
            int num2 = num / 7;
            int num3 = num2 * 2;
            for (int i = num2 * 7; i < num; i++)
            {
                if (startDateWoHour.AddDays(i).DayOfWeek.GetHashCode() == calendar.OfficialHoliday1.GetHashCode() || startDateWoHour.AddDays(i).DayOfWeek.GetHashCode() == calendar.OfficialHoliday2.GetHashCode())
                {
                    num3++;
                }
            }
            List<CalendarHolidayInformation> list = calendar.Holidays.FindAll((CalendarHolidayInformation x) => !x.IsHalfDay && x.HolidayDate >= startDateWoHour && x.HolidayDate <= endDateWoHour && x.HolidayDate.DayOfWeek.GetHashCode() != calendar.OfficialHoliday1.GetHashCode() && x.HolidayDate.DayOfWeek.GetHashCode() != calendar.OfficialHoliday2.GetHashCode());
            return num - (list.Count + num3);
        }

        public static int ConvertToInteger(DateTime date)
        {
            return int.Parse(date.Year + date.Month.ToString().PadLeft(2, '0') + date.Day.ToString().PadLeft(2, '0'));
        }

        public static DateTime ForceToBeAWorkingDay(CalendarInformation calendar, DateTime date, bool countForward)
        {
            int num = (countForward ? 1 : (-1));
            while (!IsWorkingDay(calendar, date))
            {
                date = date.AddDays(num);
            }
            return date;
        }

        public static DateTime AddDays(CalendarInformation calendar, DateTime date, double days)
        {
            date = date.AddDays(days);
            return date;
        }

        public static DateTime AddDays(CalendarInformation calendar, DateTime date, DayTypes dayType, double days, bool countForward)
        {
            return AddDays(calendar, date, dayType, DayTypes.All, days, countForward);
        }

        public static DateTime AddDays(CalendarInformation calendar, DateTime date, DayTypes dayType, DayTypes resultDayType, double days, bool countForward)
        {
            int num = (countForward ? 1 : (-1));
            if (dayType == DayTypes.Holidays)
            {
                date = FindHoliday(calendar, date, days);
            }
            if (dayType == DayTypes.WorkingDays)
            {
                date = FindWorkingDay(calendar, date, days);
            }
            if (dayType == DayTypes.All)
            {
                date = AddDays(calendar, date, days);
            }
            if (resultDayType != DayTypes.All)
            {
                while (GetDayType(calendar, date) != resultDayType)
                {
                    date = date.AddDays(num);
                }
            }
            return date;
        }

        public static DateTime AddMonths(CalendarInformation calendar, DateTime date, DayTypes resultDayType, int months, bool countForward)
        {
            date = date.AddMonths(months);
            int num = (countForward ? 1 : (-1));
            if (resultDayType != DayTypes.All)
            {
                while (GetDayType(calendar, date) != resultDayType)
                {
                    date = date.AddDays(num);
                }
            }
            return date;
        }

        public static DateTime AddYears(CalendarInformation calendar, DateTime date, DayTypes resultDayType, int years, bool countForward)
        {
            date = date.AddYears(years);
            int num = (countForward ? 1 : (-1));
            if (resultDayType != DayTypes.All)
            {
                while (GetDayType(calendar, date) != resultDayType)
                {
                    date = date.AddDays(num);
                }
            }
            return date;
        }

        public static DayTypes GetDayType(CalendarInformation calendar, DateTime date)
        {
            if (IsWorkingDay(calendar, date))
            {
                return DayTypes.WorkingDays;
            }
            return DayTypes.Holidays;
        }

        public static DateTime PreviousWorkingDate(CalendarInformation calendar, DateTime date)
        {
            date = date.AddDays(-1.0);
            return ForceToBeAWorkingDay(calendar, date, false);
        }

        public static DateTime NextWorkingDate(CalendarInformation calendar, DateTime date)
        {
            date = date.AddDays(1.0);
            return ForceToBeAWorkingDay(calendar, date, true);
        }

        public static DateTime PreviousDate(CalendarInformation calendar, DateTime date)
        {
            return AddDays(calendar, date, -1.0);
        }

        public static DateTime NextDate(CalendarInformation calendar, DateTime date)
        {
            return AddDays(calendar, date, 1.0);
        }

        public static DateTime FirstWorkingDayOfNextMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(1);
            return GetBeginningOfMonthWorkingDay(calendar, date);
        }

        public static DateTime LastWorkingDayOfNextMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(1);
            return GetEndOfMonthWorkingDay(calendar, date);
        }

        public static DateTime FirstWorkingDayOfPreviousMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(-1);
            return GetBeginningOfMonthWorkingDay(calendar, date);
        }

        public static DateTime LastWorkingDayOfPreviousMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(-1);
            return GetEndOfMonthWorkingDay(calendar, date);
        }

        public static DateTime FirstDayOfNextMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(1);
            return GetBeginningOfMonthDay(calendar, date);
        }

        public static DateTime LastDayOfNextMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(1);
            return GetEndOfMonthDay(calendar, date);
        }

        public static DateTime FirstDayOfPreviousMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(-1);
            return GetBeginningOfMonthDay(calendar, date);
        }

        public static DateTime LastDayOfPreviousMonth(CalendarInformation calendar, DateTime date)
        {
            date = date.AddMonths(-1);
            return GetEndOfMonthDay(calendar, date);
        }

        public static long GetJulianDate(DateTime date)
        {
            int day = date.Day;
            int num = date.Month;
            int num2 = date.Year;
            if (num < 3)
            {
                num += 12;
                num2--;
            }
            return day + (153 * num - 457) / 5 + 365 * num2 + num2 / 4 - num2 / 100 + num2 / 400 + 1721119;
        }
    }

}
