using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    public abstract class BaseCacheItem
    {
        private DateTime _expirationDate;

        private int _timeout;

        public int Timeout
        {
            get
            {
                return _timeout;
            }
            set
            {
                _timeout = value;
            }
        }

        public DateTime ExpirationDate
        {
            get
            {
                return _expirationDate;
            }
            internal set
            {
                _expirationDate = value;
            }
        }
    }

    public class CalendarCacheItem : BaseCacheItem
    {
        private CalendarInformation _calendarInformation;

        private DTOCalendar _calendar;

        private List<DTOCalendarHoliday> _calendarHolidays;

        private DTOCalendarHoliday _calendarMaxHolidayInfo;

        public CalendarInformation CalendarInfo
        {
            get
            {
                return _calendarInformation;
            }
            set
            {
                _calendarInformation = value;
            }
        }

        public DTOCalendar Calendar
        {
            get
            {
                return _calendar;
            }
            set
            {
                _calendar = value;
            }
        }

        public List<DTOCalendarHoliday> CalendarHolidays
        {
            get
            {
                return _calendarHolidays;
            }
            set
            {
                _calendarHolidays = value;
            }
        }

        public DTOCalendarHoliday CalendarMaxHolidayInfo
        {
            get
            {
                return _calendarMaxHolidayInfo;
            }
            set
            {
                _calendarMaxHolidayInfo = value;
            }
        }

        public CalendarCacheItem(CalendarInformation calendarInformation)
        {
            _calendarInformation = calendarInformation;
        }
    }
}
