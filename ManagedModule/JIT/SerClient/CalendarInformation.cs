using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    public class CalendarInformation
    {
        private string _code;

        private CalendarTypes _calendarType;

        private string _calendarDescription;

        private WeekDays _officialHoliday1;

        private WeekDays _officialHoliday2;

        private List<CalendarHolidayInformation> _holidays = new List<CalendarHolidayInformation>();

        public List<CalendarHolidayInformation> Holidays
        {
            get
            {
                return _holidays;
            }
            set
            {
                _holidays = value;
            }
        }

        public CalendarTypes CalendarType
        {
            get
            {
                return _calendarType;
            }
            set
            {
                _calendarType = value;
            }
        }

        public string Code
        {
            get
            {
                return _code;
            }
            set
            {
                _code = value;
            }
        }

        public string CalendarDescription
        {
            get
            {
                return _calendarDescription;
            }
            set
            {
                _calendarDescription = value;
            }
        }

        public WeekDays OfficialHoliday1
        {
            get
            {
                return _officialHoliday1;
            }
            set
            {
                _officialHoliday1 = value;
            }
        }

        public WeekDays OfficialHoliday2
        {
            get
            {
                return _officialHoliday2;
            }
            set
            {
                _officialHoliday2 = value;
            }
        }
    }

}
