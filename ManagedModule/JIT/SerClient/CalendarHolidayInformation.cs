using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    [Serializable]
    public class CalendarHolidayInformation
    {
        private string _calendarCode;

        private DateTime _holidayDate;

        private string _holidayDescription;

        private bool _isHalfDay;

        private bool _isPermanentHoliday;

        public DateTime HolidayDate
        {
            get
            {
                return _holidayDate;
            }
            set
            {
                _holidayDate = value;
            }
        }

        public string HolidayDescription
        {
            get
            {
                return _holidayDescription;
            }
            set
            {
                _holidayDescription = value;
            }
        }

        public bool IsHalfDay
        {
            get
            {
                return _isHalfDay;
            }
            set
            {
                _isHalfDay = value;
            }
        }

        public bool IsPermanentHoliday
        {
            get
            {
                return _isPermanentHoliday;
            }
            set
            {
                _isPermanentHoliday = value;
            }
        }

        public string CalendarCode
        {
            get
            {
                return _calendarCode;
            }
            set
            {
                _calendarCode = value;
            }
        }
    }
}
