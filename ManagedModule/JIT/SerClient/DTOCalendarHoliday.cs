using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    [Serializable]
    [DataContract]
    public class DTOCalendarHoliday : BaseDataTransferObject, IDataTransferObject
    {
        private string _calendarCode;

        private DateTime _holidayDate;

        private bool _isHalfDay;

        private string _holidayDescription;

        private DateTime _startDate;

        private DateTime _endDate;

        private bool _isPermanentHoliday;

        private CalendarHolidayWorkflowTypes _calendarHolidayWorkflowType;

        private CalendarHolidayTypes _calendarHolidayType;

        [Required(true)]
        [StringLength(MinLength = 0L, MaxLength = 3L)]
        [DataMember(EmitDefaultValue = false)]
        public string CalendarCode
        {
            get
            {
                return _calendarCode;
            }
            set
            {
                if (_calendarCode != value)
                {
                    _calendarCode = value;
                    OnPropertyChanged("CalendarCode");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public DateTime HolidayDate
        {
            get
            {
                return _holidayDate;
            }
            set
            {
                if (_holidayDate != value)
                {
                    _holidayDate = value;
                    OnPropertyChanged("HolidayDate");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public DateTime StartDate
        {
            get
            {
                return _startDate;
            }
            set
            {
                if (_startDate != value)
                {
                    _startDate = value;
                    OnPropertyChanged("StartDate");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public DateTime EndDate
        {
            get
            {
                return _endDate;
            }
            set
            {
                if (_endDate != value)
                {
                    _endDate = value;
                    OnPropertyChanged("EndDate");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public bool IsHalfDay
        {
            get
            {
                return _isHalfDay;
            }
            set
            {
                if (_isHalfDay != value)
                {
                    _isHalfDay = value;
                    OnPropertyChanged("IsHalfDay");
                }
            }
        }

        [StringLength(MinLength = 0L, MaxLength = 20L)]
        [DataMember(EmitDefaultValue = false)]
        public string HolidayDescription
        {
            get
            {
                return _holidayDescription;
            }
            set
            {
                if (_holidayDescription != value)
                {
                    _holidayDescription = value;
                    OnPropertyChanged("HolidayDescription");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public bool IsPermanentHoliday
        {
            get
            {
                return _isPermanentHoliday;
            }
            set
            {
                if (_isPermanentHoliday != value)
                {
                    _isPermanentHoliday = value;
                    OnPropertyChanged("IsPermanentHoliday");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        [DefaultValue(CalendarHolidayWorkflowTypes.None)]
        public CalendarHolidayWorkflowTypes CalendarHolidayWorkflowType
        {
            get
            {
                return _calendarHolidayWorkflowType;
            }
            set
            {
                if (_calendarHolidayWorkflowType != value)
                {
                    _calendarHolidayWorkflowType = value;
                    OnPropertyChanged("CalendarHolidayWorkflowType");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public CalendarHolidayTypes CalendarHolidayType
        {
            get
            {
                return _calendarHolidayType;
            }
            set
            {
                if (_calendarHolidayType != value)
                {
                    _calendarHolidayType = value;
                    OnPropertyChanged("CalendarHolidayType");
                }
            }
        }

        public new BaseDataTransferObject Copy()
        {
            DTOCalendarHoliday dTOCalendarHoliday = new DTOCalendarHoliday();
            dTOCalendarHoliday.CalendarCode = CalendarCode;
            dTOCalendarHoliday.HolidayDate = HolidayDate;
            dTOCalendarHoliday.IsHalfDay = IsHalfDay;
            dTOCalendarHoliday.HolidayDescription = HolidayDescription;
            dTOCalendarHoliday.StartDate = StartDate;
            dTOCalendarHoliday.EndDate = EndDate;
            dTOCalendarHoliday.IsPermanentHoliday = IsPermanentHoliday;
            dTOCalendarHoliday.CalendarHolidayWorkflowType = CalendarHolidayWorkflowType;
            dTOCalendarHoliday.CalendarHolidayType = CalendarHolidayType;
            dTOCalendarHoliday.FillBaseProperties(this);
            return dTOCalendarHoliday;
        }
    }
}
